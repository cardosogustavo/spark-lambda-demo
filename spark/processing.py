from pyspark.sql import SparkSession
from pyspark import SparkConf
from pyspark.sql.functions import split, explode, col

if __name__ == '__main__':

    # Init app
    spark = SparkSession \
        .builder \
        .appName("lambda-etl-spark") \
        .getOrCreate()
    
    # Creating dataframes
    df_batch = spark.read.text("/media/gustavo/second_storage/dev/luminatorch/data_projects/spark-lambda/data_lake/batch/batch.txt")
    df_stream = spark.read.text("/media/gustavo/second_storage/dev/luminatorch/data_projects/spark-lambda/data_lake/stream/stream.txt")

    # Applying transformations
    df_batch = df_batch.select(explode(split(df_batch.value, "\n")).alias("number"))
    df_stream = df_stream.select(explode(split(df_stream.value, "\n")).alias("number"))

    batch_result = df_batch.groupBy("number").count().orderBy("number")
    stream_result = df_stream.groupBy("number").count().orderBy("number")

    batch_result.write.mode("append").json("batch")
    stream_result.write.mode("append").json("stream")
