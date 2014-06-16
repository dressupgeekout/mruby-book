<a name="strings"></a>
# Strings

The mruby API ships with an impressive selection of functions to deal with
strings.

## The relevant functions

    #include <mruby/string.h>

    #define mrb_str_ptr(s)    ((struct RString*)(mrb_ptr(s)))
    #define RSTRING(s)        ((struct RString*)(mrb_ptr(s)))
    #define RSTRING_PTR(s)    (RSTRING(s)->ptr)
    #define RSTRING_LEN(s)    (RSTRING(s)->len)
    #define RSTRING_CAPA(s)   (RSTRING(s)->aux.capa)
    #define RSTRING_END(s)    (RSTRING(s)->ptr + RSTRING(s)->len)

    void mrb_gc_free_str(mrb_state*, struct RString*);
    void mrb_str_modify(mrb_state*, struct RString*);
    mrb_value mrb_str_literal(mrb_state*, mrb_value);
    void mrb_str_concat(mrb_state*, mrb_value, mrb_value);
    mrb_value mrb_str_plus(mrb_state*, mrb_value, mrb_value);
    mrb_value mrb_ptr_to_str(mrb_state *, void*);
    mrb_value mrb_obj_as_string(mrb_state *mrb, mrb_value obj);
    mrb_value mrb_str_resize(mrb_state *mrb, mrb_value str, mrb_int len);
    mrb_value mrb_str_substr(mrb_state *mrb, mrb_value str, mrb_int beg, mrb_int len);
    mrb_value mrb_string_type(mrb_state *mrb, mrb_value str);
    mrb_value mrb_check_string_type(mrb_state *mrb, mrb_value str);
    mrb_value mrb_str_buf_new(mrb_state *mrb, mrb_int capa);
    mrb_value mrb_str_buf_cat(mrb_state *mrb, mrb_value str, const char *ptr, size_t len);

    char *mrb_string_value_cstr(mrb_state *mrb, mrb_value *ptr);
    char *mrb_string_value_ptr(mrb_state *mrb, mrb_value ptr);
    int mrb_str_offset(mrb_state *mrb, mrb_value str, int pos);
    mrb_value mrb_str_dup(mrb_state *mrb, mrb_value str);
    mrb_value mrb_str_intern(mrb_state *mrb, mrb_value self);
    mrb_value mrb_str_cat_cstr(mrb_state *, mrb_value, const char *);
    mrb_value mrb_str_to_inum(mrb_state *mrb, mrb_value str, int base, int badcheck);
    double mrb_str_to_dbl(mrb_state *mrb, mrb_value str, int badcheck);
    mrb_value mrb_str_to_str(mrb_state *mrb, mrb_value str);
    mrb_int mrb_str_hash(mrb_state *mrb, mrb_value str);
    mrb_value mrb_str_buf_append(mrb_state *mrb, mrb_value str, mrb_value str2);
    mrb_value mrb_str_inspect(mrb_state *mrb, mrb_value str);
    mrb_bool mrb_str_equal(mrb_state *mrb, mrb_value str1, mrb_value str2);
    mrb_value mrb_str_dump(mrb_state *mrb, mrb_value str);
    mrb_value mrb_str_cat(mrb_state *mrb, mrb_value str, const char *ptr, size_t len);
    mrb_value mrb_str_append(mrb_state *mrb, mrb_value str, mrb_value str2);

    int mrb_str_cmp(mrb_state *mrb, mrb_value str1, mrb_value str2);
    char *mrb_str_to_cstr(mrb_state *mrb, mrb_value str);
    mrb_value mrb_str_pool(mrb_state *mrb, mrb_value str);


## Creating strings

    #include <mruby.h>

    mrb_value mrb_str_new(mrb_state *mrb, const char *p, size_t len);
    mrb_value mrb_str_new_cstr(mrb_state*, const char*);
    mrb_value mrb_str_new_static(mrb_state *mrb, const char *p, size_t len);

You can create a Ruby String object from a regular null-terminated C string:

    # Ruby
    foo = "chunky bacon"

    /* C */
    mrb_value foo = mrb_str_new_cstr(R, "chunky bacon");


## Concatenating strings

The following functions will help with string concatenation:

    #include <mruby/string.h>

    void mrb_str_concat(mrb_state*, mrb_value, mrb_value);
    mrb_value mrb_str_plus(mrb_state*, mrb_value, mrb_value);
    mrb_value mrb_str_buf_cat(mrb_state *mrb, mrb_value str, const char *ptr, size_t len);
    mrb_value mrb_str_cat_cstr(mrb_state *, mrb_value, const char *);
    mrb_value mrb_str_buf_append(mrb_state *mrb, mrb_value str, mrb_value str2);
    mrb_value mrb_str_cat(mrb_state *mrb, mrb_value str, const char *ptr, size_t len);
    mrb_value mrb_str_append(mrb_state *mrb, mrb_value str, mrb_value str2);


### Concatenating Ruby String objects

The `mrb_str_plus()` function will concatenate two Ruby String objects, as
if they were using the "plus" operator:

    # Ruby
    first = "Marco"
    last = "Polo"
    together = first + last
    puts together

    /* C */
    #include <stdio.h>
    #include <mruby.h>
    #include <mruby/string.h>

    mrb_value first = mrb_str_new_cstr(R, "Marco");
    mrb_value last = mrb_str_new_cstr(R, "Polo");
    mrb_value together = mrb_str_plus(R, first, last);
    printf("%s\n", mrb_str_to_cstr(R, together));


### Retrieving a C string from a Ruby String

You can get a C string from a Ruby String with the `mrb_str_to_cstr()`
function.

    char *result;

    result = malloc(RSTRING_LEN(str) + 1);
    result = mrb_str_to_cstr(R, str);
    printf("%s\n", result);
    free(result);
