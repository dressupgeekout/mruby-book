.PHONY: clean all
.SUFFIXES: .c .o

CC = clang -Wall
CFLAGS = -I../mruby-include
LDFLAGS = -L../mruby-lib
LIBS = -lmruby -lm

COMPILE = $(CC) $(LDFLAGS) -o $(.TARGET) $(.ALLSRC) $(LIBS)

MODULES = \
	helloworld \
	classes \
	methods

all: \
	helloworld/helloworld \
	classes/classes \
	methods/methods

helloworld/helloworld: helloworld/helloworld.o
	$(COMPILE)

classes/classes: classes/classes.o
	$(COMPILE)

methods/methods: methods/methods.o
	$(COMPILE)

.c.o:
	$(CC) -c $(CFLAGS) -o $(.TARGET) $(.ALLSRC)

clean:
	for m in $(MODULES); do \
		rm -fv $${m}/$${m} $${m}/$${m}.o; \
	done

