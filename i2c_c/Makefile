CROSS_COMPILE = arm-linux-gnueabihf-
CFLAGS = -static
CC = $(CROSS_COMPILE)gcc
test : main.o      
	$(CC) $(CFLAGS) -o test main.o
	#gcc -o test main.o
main.o : main.c i2c.h 
	$(CC) -c main.c
#	gcc -c main.c
clean :
	rm main.o test
