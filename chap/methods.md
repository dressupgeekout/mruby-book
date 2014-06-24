# Methods

## Conventions

It is recommended that you name your C functions using the same conventions
the mruby developers have employed for the mruby standard library:

  - If the Ruby method name ends with a "?", then the C function name should
    end with "\_p". Example: `#empty?` becomes `empty_p()`.

  - If the Ruby method name ends with a "!", then the C function name should
    end with "\_bang". Example: `#collect!` becomes `collect_bang()`.


## Getting arguments with mrb\_get\_args()

From src/class.c:

    /*
      retrieve arguments from mrb_state.

      mrb_get_args(mrb, format, ...)

      returns number of arguments parsed.

      format specifiers:

        string  mruby type     C type                 note
        --------------------------------------------------------------------
        o:      Object         [mrb_value]
        C:      class/module   [mrb_value]
        S:      String         [mrb_value]
        A:      Array          [mrb_value]
        H:      Hash           [mrb_value]
        s:      String         [char*,int]            Receive two arguments.
        z:      String         [char*]                NUL terminated string.
        a:      Array          [mrb_value*,mrb_int]   Receive two arguments.
        f:      Float          [mrb_float]
        i:      Integer        [mrb_int]
        b:      Boolean        [mrb_bool]
        n:      Symbol         [mrb_sym]
        &:      Block          [mrb_value]
        *:      rest argument  [mrb_value*,int]       Receive the rest of the arguments as an array.
        |:      optional                              Next argument of '|' and later are optional.
     */
    int mrb_get_args(mrb_state *mrb, const char *format, ...)

  - "o" &mdash; Object &mdash; `mrb_value`
  - "C" &mdash; class/module &mdash; `mrb_value`
  - "S" &mdash; String &mdash; `mrb_value`
  - "A" &mdash; Array &mdash; `mrb_value`
  - "H" &mdash; Hash &mdash; `mrb_value`
  - "s" &mdash; String &mdash; `[char*, int]`
  - "z" &mdash; String &mdash; `char*`
  - "a" &mdash; Array &mdash; `[mrb_value*, mrb_int]`
  - "f" &mdash; Float &mdash; `mrb_float`
  - "i" &mdash; Integer &mdash; `mrb_int`
  - "b" &mdash; Boolean &mdash; `mrb_bool`
  - "n" &mdash; Symbol &mdash; `mrb_sym`
  - "&" &mdash; Block &mdash; `mrb_value`
  - "\*" &mdash; "rest" &mdash; `[mrb_value*, int]`
  - "|" &mdash; optional

Some examples:

    /* Require 1 Object */
    mrb_get_args(R, "o", ...);

    /* Require 2 integers with an optional block */
    mrb_get_args(R, "ii|&", ...);

## The relevant functions

    #include <mruby.h>
    mrb_value mrb_funcall(mrb_state*, mrb_value, const char*, int,...);
    mrb_value mrb_funcall_argv(mrb_state*, mrb_value, mrb_sym, int, mrb_value*);
    mrb_value mrb_funcall_with_block(mrb_state*, mrb_value, mrb_sym, int, mrb_value*, mrb_value);

## Define an instance method

.


## Define a class method

.


## Invoke an instance method

.


## Invoke a class method

.


## Procs 

### The relevant functions

    #include <mruby/proc.h>

    struct RProc *mrb_proc_new(mrb_state*, mrb_irep*);
    struct RProc *mrb_proc_new_cfunc(mrb_state*, mrb_func_t);
    struct RProc *mrb_closure_new(mrb_state*, mrb_irep*);
    struct RProc *mrb_closure_new_cfunc(mrb_state *mrb, mrb_func_t func, int nlocals);
    void mrb_proc_copy(struct RProc *a, struct RProc *b);

Note that there is no typedef for `struct RProc`. There is no `mrb_proc`
type.

**XXX What is the difference between mruby's "proc" and "closure" ? Probably
closure == block.**


-----

## Example

This is an excerpt from src/kernel.c. Do you see how the Ruby method
translates in to C?

    /* 15.3.1.3.22 */
    /*
     *  call-seq:
     *     obj.instance_variable_set(symbol, obj)    -> obj
     */
    mrb_value
    mrb_obj_ivar_set(mrb_state *mrb, mrb_value self)
    {
      mrb_sym iv_name_id;
      mrb_value iv_name, val;

      mrb_get_args(mrb, "oo", &iv_name, &val);

      iv_name_id = get_valid_iv_sym(mrb, iv_name);
      mrb_iv_set(mrb, self, iv_name_id, val);
      return val;
    }

The `mrb_obj_ivar_set()` function is referenced at the end of the file,
inside the definition of `mrb_init_kernel()`. Here is an excerpt: 

    void
    mrb_init_kernel(mrb_state *mrb)
    {
      struct RClass *krn;

      krn = mrb->kernel_module = mrb_define_module(mrb, "Kernel");

      /* ... */

      /* 15.3.1.3.22 */
      mrb_define_method(mrb, krn, "instance_variable_set", mrb_obj_ivar_set,
        MRB_ARGS_REQ(2));

      /* ... */

      mrb_include_module(mrb, mrb->object_class, mrb->kernel_module);
      mrb_alias_method(mrb, mrb->module_class, mrb_intern_lit(mrb, "dup"),
        mrb_intern_lit(mrb, "clone"));
    }

In other words:

  - `mrb_define_method()` tells the mruby state that we are creating an
    instance method. (You would use `mrb_define_class_method()` if you
    wanted to create a class method.)

