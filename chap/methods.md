# Methods

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
