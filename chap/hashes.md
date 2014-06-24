<a name="hashes"></a>
# Hashes

## The relevant functions

    #include <mruby/hash.h>

    mrb_value mrb_hash_new_capa(mrb_state*, int);
    mrb_value mrb_hash_new(mrb_state *);

    void mrb_hash_set(mrb_state *, mrb_value hash, mrb_value key, mrb_value val);
    mrb_value mrb_hash_get(mrb_state *, mrb_value hash, mrb_value key);
    mrb_value mrb_hash_fetch(mrb_state *, mrb_value hash, mrb_value key, mrb_value def);
    mrb_value mrb_hash_delete_key(mrb_state *, mrb_value hash, mrb_value key);
    mrb_value mrb_hash_keys(mrb_state *, mrb_value hash);
    mrb_value mrb_check_hash_type(mrb_state *, mrb_value hash);
    mrb_value mrb_hash_empty_p(mrb_state *, mrb_value self);
    mrb_value mrb_hash_clear(mrb_state *, mrb_value hash);


## Creating hashes

We use the `mrb_hash_new()` function to create a new `Hash`. If you know
your hash is not going to have more than a certain number of key-value
pairs, you can specify this capacity with the `mrb_hash_new_capa()`
function.


## An Example

In Ruby:

    dragon = {
      :name => "Saphira",
      :color => :blue,
    }
    dragon.delete(:color)

In C:

    mrb_value dragon = mrb_hash_new(R);
    mrb_hash_set(R, dragon, mrb_intern_cstr(R, "name"), mrb_str_new_cstr(R, "Saphira"));
    mrb_hash_set(R, dragon, mrb_intern_cstr(R, "color"), mrb_intern_cstr(R, "blue"));
    mrb_hash_delete_key(R, dragon, mrb_intern_cstr(R, "color"));

Remember that hash keys in Ruby can be _any_ kind of object. That means, for
example, it is necessary to explicitly state that a key should be `Symbol`
and not a `String`.

`mrb_hash_clear()` is equivalent to the Ruby method `Hash#clear`. It is a
destructive method even though its name does not end with an exclamation
mark ("!").
