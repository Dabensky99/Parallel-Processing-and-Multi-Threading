
all: mandel mandelmovie

mandel: mandel.o bitmap.o
	gcc mandel.o bitmap.o -o mandel -lpthread

mandel.o: mandel.c
	gcc -Wall -g -c mandel.c -o mandel.o

bitmap.o: bitmap.c
	gcc -Wall -g -c bitmap.c -o bitmap.o

mandelmovie: mandelmovie.o bitmap.o
	gcc mandelmovie.o bitmap.o -o mandelmovie -lpthread

mandelmovie.o: mandelmovie.c
	gcc -Wall -g -c mandelmovie.c -o mandelmovie.o

clean:
	rm -f mandel.o bitmap.o mandelmovie.o mandel mandelmovie
