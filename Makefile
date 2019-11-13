CC=g++
CFLAGS=-c -Wall -Wextra
LDFLAGS=-fsanitize=address

SRCS=main.cpp stack.cpp
OBJS=$(SRCS:.cpp=.o)
EXEC=a.out

all: clear $(SRCS) $(EXEC)

$(EXEC): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clear:
	rm -r *.o $(EXEC)
