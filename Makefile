CC = gcc
CFLAGS = pkg-config --cflags gtk+-3.0 -Wall -g
LIBS = pkg-config --libs gtk+-3.0 -lrt -pthread

all: shellgui

shellgui: main.o model.o controller.o
	$(CC) -o shellgui main.o model.o controller.o $(LIBS)

main.o: main.c model.h controller.h
	$(CC) $(CFLAGS) -c main.c

model.o: model.c model.h
	$(CC) $(CFLAGS) -c model.c

controller.o: controller.c controller.h model.h
	$(CC) $(CFLAGS) -c controller.c

clean:
	rm -f *.o shellgui
