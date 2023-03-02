CC = gcc
CXX = g++
ECHO = echo
RM = rm -f

TERM = "S2023"

CFLAGS = -Wall -Werror -ggdb -funroll-loops -DTERM=$(TERM)
CXXFLAGS = -Wall -Werror -ggdb -funroll-loops -DTERM=$(TERM)

LDFLAGS = -lm

BIN = main $(patsubst %.c,%,$(wildcard */*.c))
OBJS = main.o $(patsubst %.c,%.o,$(wildcard */*.c))

all: $(BIN) etags

$(BIN): $(OBJS)
	@$(ECHO) Linking $@
	@$(CC) $^ -o $@ $(LDFLAGS)

-include $(OBJS:.o=.d)

%.o: %.c
	@$(ECHO) Compiling $<
	@$(CC) $(CFLAGS) -MMD -MF $*.d -c $< -o $@

%.o: %.cpp
	@$(ECHO) Compiling $<
	@$(CXX) $(CXXFLAGS) -MMD -MF $*.d -c $< -o $@

.PHONY: all clean clobber etags

clean:
	@$(ECHO) Removing all generated files
	@$(RM) *.o $(BIN) *.d TAGS core vgcore.* gmon.out

clobber: clean
	@$(ECHO) Removing backup files
	@$(RM) *~ \#* *pgm

etags:
	@$(ECHO) Updating TAGS
	@etags *.[ch]
