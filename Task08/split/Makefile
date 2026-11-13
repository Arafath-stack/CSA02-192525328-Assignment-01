CC=gcc
CFLAGS=-Wall -Wextra -O0
OBJS=main.o input.o tariff.o report.o
billing: $(OBJS)
	$(CC) -o $@ $(OBJS)
%.o: %.c billing.h
	$(CC) $(CFLAGS) -c $<
clean:
	rm -f *.o billing
