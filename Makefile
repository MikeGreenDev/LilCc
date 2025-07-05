all: program1

program1: main.c scan.c expression.c astTree.c casmTranslator.c translator.c
	cc -o testbed -g main.c scan.c expression.c astTree.c casmTranslator.c translator.c 

clean:
	rm -f testbed *.o out out.s
