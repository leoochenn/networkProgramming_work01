CC = gcc
CFLAGS = -Wno-implicit-function-declaration -g -MD
LFLAGS = -lreadline
INC = -Iinclude

SRCS = $(wildcard src/*.c)
OBJS = $(patsubst src/%.c, obj/%.o, ${SRCS})

.PHONY: $(OBJS:.o=.d)

all: shell

-include $(DEPS)

shell: $(OBJS)
	@$(CC) $^ -o shell $(LFLAGS)

obj/%.o: src/%.c
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	@rm shell obj/*.o obj/*.d
