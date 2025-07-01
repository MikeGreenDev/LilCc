all: main.c scan.c
	cc -o testbed -g main.c scan.c

clean:
	rm -f testbed *.o
