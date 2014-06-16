# Errors and Exceptions

In Ruby, errors and exceptions are represented by classes.

    #include <mruby.h>

    /* macros to get typical exception objects
       note:
       + those E_* macros requires mrb_state* variable named mrb.
       + exception objects obtained from those macros are local to mrb
    */
    #define E_RUNTIME_ERROR     (mrb_class_get(mrb, "RuntimeError"))
    #define E_TYPE_ERROR        (mrb_class_get(mrb, "TypeError"))
    #define E_ARGUMENT_ERROR    (mrb_class_get(mrb, "ArgumentError"))
    #define E_INDEX_ERROR       (mrb_class_get(mrb, "IndexError"))
    #define E_RANGE_ERROR       (mrb_class_get(mrb, "RangeError"))
    #define E_NAME_ERROR        (mrb_class_get(mrb, "NameError"))
    #define E_NOMETHOD_ERROR    (mrb_class_get(mrb, "NoMethodError"))
    #define E_SCRIPT_ERROR      (mrb_class_get(mrb, "ScriptError"))
    #define E_SYNTAX_ERROR      (mrb_class_get(mrb, "SyntaxError"))
    #define E_LOCALJUMP_ERROR   (mrb_class_get(mrb, "LocalJumpError"))
    #define E_REGEXP_ERROR      (mrb_class_get(mrb, "RegexpError"))

    #define E_NOTIMP_ERROR      (mrb_class_get(mrb, "NotImplementedError"))
    #define E_FLOATDOMAIN_ERROR (mrb_class_get(mrb, "FloatDomainError"))

    #define E_KEY_ERROR         (mrb_class_get(mrb, "KeyError"))


There are also a bunch of functions:

    #include <mruby.h>

    mrb_value mrb_exc_new(mrb_state *mrb, struct RClass *c, const char *ptr, long len);
    void mrb_exc_raise(mrb_state *mrb, mrb_value exc);

    void mrb_raise(mrb_state *mrb, struct RClass *c, const char *msg);
    void mrb_raisef(mrb_state *mrb, struct RClass *c, const char *fmt, ...);
    void mrb_name_error(mrb_state *mrb, mrb_sym id, const char *fmt, ...);
    void mrb_warn(mrb_state *mrb, const char *fmt, ...);
    void mrb_bug(mrb_state *mrb, const char *fmt, ...);
    void mrb_print_backtrace(mrb_state *mrb);
    void mrb_print_error(mrb_state *mrb);


## Raising an exception

You can raise an exception with the `mrb_raise()` function:

    mrb_raise(R, E_TYPE_ERROR, "I was expecting a String");

**XXX This doesn't work, the `E_*` macros require the state to be named `mrb`.
Redefine them?**

    #define E_TYPE_ERROR (mrb_class_get(R, "TypeError"))
