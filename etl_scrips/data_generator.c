#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

/*
This script is to generate random numbers for a Spark pipeline in a Lambda architecture

Author: Gustavo Cardoso

Usage: ./data_generator --mode b
*/

// RAND_QTY is a const int that represents how many random numbers I want.
// const int RAND_QTY = 100;

// // RAND_RANGE is a const int that represents the range of random values. If set to 100, it means
// // that it will generate numbers between 1 and 100.
const int RAND_RANGE = 10000;

// // Number of seconds to wait between each write. Used in the sleep() function
// const int INTERVAL = 50;

// The batch/stream ratio of data writing. If set to 2, the stream writing will be 2x faster, ou seja,
// for each batch number there will be 2 stream numbers. It should be an integer
const int BATCH_STREAM_RATIO = 3;


int generate_numbers();


int main(int argc, char *argv[])
{

    long interval_arg = strtol(argv[1], NULL, 10);
    long batch_size_arg = strtol(argv[2], NULL, 10);


    while (1)
    {
        generate_numbers(batch_size_arg);
        sleep(interval_arg);
        printf("\n ------------------------------------ \n");
        printf("Successfully generated random numbers.\n");
        printf("\n ------------------------------------ \n");
    }

    
    return 0;
}


int generate_numbers(int batch_size)
{
    time_t seed;
    FILE *file_ptr_batch, *file_ptr_stream;

    file_ptr_batch = fopen("../data_lake/batch/batch.txt", "a");
    file_ptr_stream = fopen("../data_lake/stream/stream.txt", "a");

    if ((file_ptr_batch == NULL) || (file_ptr_stream == NULL))
    {
        printf("Error opening file. \n");
        return 1;
    }

    srand((unsigned) time(&seed));

    for (int i = 0; i < batch_size; i++)
    {
        fprintf(file_ptr_batch, "%d\n", rand() % RAND_RANGE);
        for (int j = 0; j < BATCH_STREAM_RATIO; j++)
        {
            fprintf(file_ptr_stream, "%d\n", rand() % RAND_RANGE);            
        }
        
    }
    fclose(file_ptr_batch);
    fclose(file_ptr_stream);

    return 0;

}