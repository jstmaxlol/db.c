all:
	cc -o db db.c -Wall -Wextra -pedantic

run: all
	./db

clean:
	rm ./db
