CC = gcc
CFLAGS = -I include

main: obj/main.o obj/autor.o obj/livro.o obj/reserva.o obj/usuario.o
	@ $(CC) $^ -o main

obj/autor.o: include/autor.h
	@ $(CC) $(CFLAGS) -c src/autor.c -o obj/autor.o 

obj/livro.o: include/livro.h
	@ $(CC) $(CFLAGS) -c src/livro.c -o obj/livro.o

obj/reserva.o: include/reserva.h
	@ $(CC) $(CFLAGS) -c src/reserva.c -o obj/reserva.o

obj/usuario.o: include/usuario.h
	@ $(CC) $(CFLAGS) -c src/usuario.c -o obj/usuario.o

obj/main.o: src/main.c obj/autor.o obj/livro.o obj/usuario.o obj/reserva.o
	@ $(CC) $(CFLAGS) -c src/main.c -o obj/main.o

clean:
	@ rm -f main obj/*.o