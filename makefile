all: listKnights

listKnights: listKnights.c
	gcc listKnights.c -o listKnights

clean:
	rm -rf listKnights
