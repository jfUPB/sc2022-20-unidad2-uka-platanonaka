CC = gcc
CFLGAS = -Wall -g
DEPS = event.h eventList.h

%.o: %.c $(DEPS)
	$(CC) $< $(CFLAGS) -c -g -o $@

main: main.o event.o eventList.o
	$(CC) $(CFLGAS) -o main *.o

clean:
	rm main *.o