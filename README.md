# spark-lambda-demo
A short Lambda Architecture demonstration using Apache Spark to process data.

The design can be found here: https://excalidraw.com/#json=NntHcyJ0llQK4e2oNXeDJ,uoI17OPgdtn2YEjDu1S_-w

It is a simple demo, just to show the power and simplicity of Apache Spark.

# data generation
The file **data_generation.c** contains a simple logic to generate random numbers and save them to text files inside **data_lake** folder.

The folder will contain two subfolders after the program runs: batch and stream.

The program works as this:

- You execute the CLI passing two parameters: INTERVAL and BATCH_SIZE
- INTERVAL is the interval which generates numbers, for example 10 seconds (it's an integer)
- BATCH_SIZE is how many random numbers you want generated for each write iteration
- Both parameters can be modified in the **run** tag of the Makefile, first INTERVAL then BATCH_SIZE
- There are two constants inside the code:
  - **BATCH_STREAM_RATIO**: This specifies how faster you want the stream do be, in a line-write ratio. For example,
        if you want to write 2 numbers in the stream file for each batch number in the batch file, you set this number to **2**
  - **RAND_RANGE**: Represents the range of random values. If set to 100, it means that it will generate numbers between 1 and 100

Set your desired values, navigate to **etl_scripts** folder and execute **make run**. To stop generating, press CTRL+C.

# spark processing
The transformation in the PySpark file is very simple. It counts how many instances of each number and saves it to its corresponding folder (batch or stream) in a JSON format.

Spark automaticaly partitions the files depending on the size. So if you want more than one partition, generate a lot of data either by setting a low interval or just let the program run for some time.

It saves data locally, so be careful.
