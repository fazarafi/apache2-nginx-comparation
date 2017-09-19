make: miniserver.c
	gcc -o miniserver miniserver.c -lev
run: miniserver
	./miniserver
clean:
	rm miniserver
