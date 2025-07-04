all: program1

program1: main.c scan.c expression.c astTree.c casmTranslator.c translator.c
	cc -o testbed -g main.c scan.c expression.c astTree.c casmTranslator.c translator.c 

test: program1 out.s
	cc -o out out.s

clean:
	rm -f testbed *.o out out.s
