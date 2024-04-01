CFLAGS=-Wall -g

clean:
	rm -f data_generator ../data_lake/batch/batch.txt ../data_lake/stream/stream.txt

all:
	make data_generator

run:
	make clean all && ./data_generator 2 1000

test:
	./data_generator 2 1000