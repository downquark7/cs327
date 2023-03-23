CC = gcc
CXX = g++
ECHO = echo
RM = rm -f

CFLAGS = -Wall -Werror -ggdb -funroll-loops
CXXFLAGS = -Wall -Werror -ggdb -funroll-loops

LDFLAGS = -lm -lncurses -lmenu

BIN = main $(patsubst %.c,%,$(wildcard */*.c))
OBJS = build-dir/main.o $(patsubst %.c,build-dir/%.o,$(wildcard */*.c))

all: $(BIN) etags

$(BIN): $(OBJS)
	@$(ECHO) Linking $@
ifneq ($(@D),.)
	@mkdir -p $(@D)
endif
	@$(CC) $^ -o $@ $(LDFLAGS)

-include $(OBJS:.o=.d)

build-dir/%.o: %.c
	@$(ECHO) Compiling $<
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -MMD -c $< -o $@

build-dir/%.o: %.cpp
	@$(ECHO) Compiling $<
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) -MMD -c $< -o $@

.PHONY: all clean clobber etags

clean:
	@$(ECHO) Removing all generated files
	@$(RM)r build-dir
	@$(RM) *.o $(BIN) *.d TAGS core vgcore.* gmon.out

clobber: clean
	@$(ECHO) Removing backup files
	@$(RM) *~ \#* *pgm

etags:
	@$(ECHO) Updating TAGS
	@mkdir -p $(@D)
	@etags *.[ch]

run: main
	./main

test: main
	./main --test 1000
