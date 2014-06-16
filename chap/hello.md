# Embedded Ruby

## Fetching mruby

At the time of this writing (June 2014), there is only one public release of
mruby: version 1.0.0. You can download the source code in a Zip archive from
http://mruby.org.

Additionally, the source code is also available in a Git repository hosted
at GitHub. If you have Git, you can clone the mruby repository like so:

    $ git clone git@github.com:mruby/mruby.git
    $ cd mruby
    $ # git checkout v1.0.0 tag?


## Building mruby

Compiling mruby itself is very straightforward.

    $ x
    $ y
    $ z

Ideally, the mruby library binary and the C header files would be installed
in an easily reachable place, but since the code is so small, there's no
reason you can't simply include everything in your project: 

    $ ls -F myproject/
    w/  x/  y/  z/


## Hello World

Here is the obligatory first program:

    #include <stdio.h>
    #include <stdlib.h>

    #include <mruby.h>
    #include <mruby/compile.h>

    int
    main(void)
    {
      mrb_state *R;

      R = mrb_open();
      mrb_string_XXX();
      mrb_close(R);
      return EXIT_SUCCESS;
    }


You can compile it with a Makefile that looks like this. (Note that I use
the BSD version of make(1), which actually defines the readable macros
`.TARGET` and `.ALLSRC`.)

    .PHONY: clean
    .SUFFIXES: .c .o

    CC = clang -Wall
    CFLAGS = -I./include
    LDFLAGS = -L./lib
    LIBS = -lmruby -lm

    hello: main.o 
        $(CC) $(LDFLAGS) -o $(.TARGET) $(.ALLSRC) $(LIBS)

    .c.o:
        $(CC) -c $(CFLAGS) -o $(.TARGET) $(.ALLSRC)

    clean:
        rm -f hello

The main thing to notice about the Makefile is that you have to link against
both the mruby and math libraries, that is, `-lmruby -lm`.
  

## Notes

When programming against the Lua API, the convention is to use a variable
named `L` to refer to the Lua state:

    lua_State *L;

I have grown accustomed to this, so I similarly insist that the mruby state
be named `R`:

    mrb_state *R;

Unfortunately, version 1.0.0 of mruby makes some assumptions about the name
of the `mrb_state *` variable. Most notably, the convenience macros listed
in the "Errors and Exceptions" chapter require that the name of the mruby
state be `mrb`. Although this is the convention used throughout mruby's
source, I personally find it extremely difficult to read &mdash; virtually
_every_ function in mruby is prefixed with "mrb\_", so adding yet another
"mrb" for every function call is outright confusing.


## The mruby State

If you want to do anything interesting with mruby, you need to create an
_mruby state_. Don't forget to destroy it when your program terminates!

    #include <mruby.h>

    mrb_state* mrb_open(void);
    mrb_state* mrb_open_allocf(mrb_allocf, void *ud);
    void mrb_close(mrb_state*);

`mrb_state` is an enormous structure which contains virtually everything
anybody would ever need to know about the Ruby interpreter. There is little
to gain from studying it all, but the whole thing is defined in `<mruby.h>`
just in case you want to dig deeper.
