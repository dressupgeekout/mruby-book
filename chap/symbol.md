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

Observe that type `mrb_sym` is actually an integer typedef:

    /* mruby/value.h: line 51 */
    typedef short mrb_sym;

This is evidence that thinking about symbols as "lightweight strings" is not
entirely removed from the truth.


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


## Creating a new Ruby Symbol

We can create a new Symbol object from a zero-terminated C string with the
`mrb_intern_cstr()` function.

    mrb_sym people_sym = mrb_intern_cstr(R, "people");

If the string is not zero-terminated, or if you want to put a restriction on
the size of the C string for extra security, you can use the `mrb_intern()`
function instead:

    char *people_str = "people";
    mrb_sym people_sym = mrb_intern(R, people_str, strlen(people_str));

If you already have a Ruby String object, you can convert it to a Symbol
with `mrb_intern_str()`. This is equivalent to calling `String#to_sym` or
`String#intern`.

    # Ruby
    fox_str = "Fox Small"
    fox_sym = fox_str.to_sym

    /* C */
    mrb_value fox_str = mrb_str_new_cstr(R, "Fox Small");
    mrb_sym fox_sym = mrb_intern_str(R, fox_str);
