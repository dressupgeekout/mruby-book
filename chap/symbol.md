<a name="symbols"></a>
# Symbols

mruby's differentiation between strings and symbols is the same as in MRI:
two symbols with the same content are guaranteed to hold the same position
in memory (i.e., they are guaranteed to be the exact same object), whereas
this is not necessarily the case with strings.

    # XXX need a better way to show object "id" so to speak

    (:hello).hash == (:hello).hash
    # => true

    "hello".hash == "hello".hash
    # => (might be false)

Nevertheless, the internal representation of both mruby symbols _and_
strings is a C string.

## The relevant functions

    #include <mruby.h>

    mrb_sym mrb_intern_cstr(mrb_state*,const char*);
    mrb_sym mrb_intern(mrb_state*,const char*,size_t);
    mrb_sym mrb_intern_static(mrb_state*,const char*,size_t);
    #define mrb_intern_lit(mrb, lit) mrb_intern_static(mrb, (lit), sizeof(lit) - 1)
    mrb_sym mrb_intern_str(mrb_state*,mrb_value);
    mrb_value mrb_check_intern_cstr(mrb_state*,const char*);
    mrb_value mrb_check_intern(mrb_state*,const char*,size_t);
    mrb_value mrb_check_intern_str(mrb_state*,mrb_value);
    const char *mrb_sym2name(mrb_state*,mrb_sym);
    const char *mrb_sym2name_len(mrb_state*,mrb_sym,size_t*);
    mrb_value mrb_sym2str(mrb_state*,mrb_sym);
    mrb_value mrb_str_format(mrb_state *, int, const mrb_value *, mrb_value);


### Convert a C string to a Ruby symbol

.

### Convert a C string to a Ruby string

.


### Get a C string from a Ruby string

.
