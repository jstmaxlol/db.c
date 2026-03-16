CC      = gcc
IN      = db.c
OUT     = db
LIBS 	= -lcrypt
OPTS 	= -O0 -g -Wall -Wextra -pedantic

all:
	$(CC) -o$(OUT) $(LIBS) $(OPTS) $(IN)

run: all
	./$(OUT)

clean:
	rm $(OUT)
