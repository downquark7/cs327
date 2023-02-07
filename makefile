main.o: main.c map/*
	gcc -g main.c map/* -o main.o

clean:
	rm -rf *.o
	rm -rf map/*.gch
