all:
	cc -o db db.c -Wall -Wextra -pedantic

clean:
	rm ./db
