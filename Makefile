make: miniserver.c
	gcc -o miniserver miniserver.c -lev
run20kb: miniserver
	./miniserver 20kb
run500b: miniserver
	./miniserver 500b
clean:
	rm miniserver
