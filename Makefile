OBJ=ai.o ai2.o aitest.o ending.o level.o main.o player.o point.o start.o
CC=gcc -Wall -g

shannon:	$(OBJ) shannon.h
		$(CC) $(OBJ) -o shannon

%.o:		%.c
		$(CC) -c $<

clean:
	@rm -f *.o
	@rm -f core
	@rm -f *~
