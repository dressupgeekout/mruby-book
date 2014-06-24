# Classes and Modules

## OK

The top-level header file `<mruby.h>` specifies an interface.

    #include <mruby.h>

    typedef mrb_value (*mrb_func_t)(mrb_state *mrb, mrb_value);
    struct RClass *mrb_define_class(mrb_state *, const char*, struct RClass*);
    struct RClass *mrb_define_module(mrb_state *, const char*);
    mrb_value mrb_singleton_class(mrb_state*, mrb_value);
    void mrb_include_module(mrb_state*, struct RClass*, struct RClass*);

    void mrb_define_method(mrb_state*, struct RClass*, const char*, mrb_func_t, mrb_aspec);
    void mrb_define_class_method(mrb_state *, struct RClass *, const char *, mrb_func_t, mrb_aspec);
    void mrb_define_singleton_method(mrb_state*, struct RObject*, const char*, mrb_func_t, mrb_aspec);
    void mrb_define_module_function(mrb_state*, struct RClass*, const char*, mrb_func_t, mrb_aspec);
    void mrb_define_const(mrb_state*, struct RClass*, const char *name, mrb_value);
    void mrb_undef_method(mrb_state*, struct RClass*, const char*);
    void mrb_undef_class_method(mrb_state*, struct RClass*, const char*);
    mrb_value mrb_obj_new(mrb_state *mrb, struct RClass *c, int argc, mrb_value *argv);
    #define mrb_class_new_instance(mrb,argc,argv,c) mrb_obj_new(mrb,c,argc,argv)
    mrb_value mrb_instance_new(mrb_state *mrb, mrb_value cv);
    struct RClass * mrb_class_new(mrb_state *mrb, struct RClass *super);
    struct RClass * mrb_module_new(mrb_state *mrb);
    mrb_bool mrb_class_defined(mrb_state *mrb, const char *name);
    struct RClass * mrb_class_get(mrb_state *mrb, const char *name);
    struct RClass * mrb_class_get_under(mrb_state *mrb, struct RClass *outer, const char *name);

    mrb_value mrb_obj_dup(mrb_state *mrb, mrb_value obj);
    mrb_value mrb_check_to_integer(mrb_state *mrb, mrb_value val, const char *method);
    mrb_bool mrb_obj_respond_to(mrb_state *mrb, struct RClass* c, mrb_sym mid);
    struct RClass * mrb_define_class_under(mrb_state *mrb, struct RClass *outer, const char *name, struct RClass *super);
    struct RClass * mrb_define_module_under(mrb_state *mrb, struct RClass *outer, const char *name);

`<mruby/class.h>` defines further stuff:

    #include <mruby/class.h>

    #define mrb_class_ptr(v)    ((struct RClass*)(mrb_ptr(v)))
    #define RCLASS_SUPER(v)     (((struct RClass*)(mrb_ptr(v)))->super)
    #define RCLASS_IV_TBL(v)    (((struct RClass*)(mrb_ptr(v)))->iv)
    #define RCLASS_M_TBL(v)     (((struct RClass*)(mrb_ptr(v)))->mt)

    #define MRB_SET_INSTANCE_TT(c, tt) c->flags = ((c->flags & ~0xff) | (char)tt)
    #define MRB_INSTANCE_TT(c) (enum mrb_vtype)(c->flags & 0xff)

    struct RClass* mrb_define_class_id(mrb_state*, mrb_sym, struct RClass*);
    struct RClass* mrb_define_module_id(mrb_state*, mrb_sym);
    struct RClass *mrb_vm_define_class(mrb_state*, mrb_value, mrb_value, mrb_sym);
    struct RClass *mrb_vm_define_module(mrb_state*, mrb_value, mrb_sym);
    void mrb_define_method_vm(mrb_state*, struct RClass*, mrb_sym, mrb_value);
    void mrb_define_method_raw(mrb_state*, struct RClass*, mrb_sym, struct RProc *);
    void mrb_define_method_id(mrb_state *mrb, struct RClass *c, mrb_sym mid, mrb_func_t func, mrb_aspec aspec);
    void mrb_alias_method(mrb_state *mrb, struct RClass *c, mrb_sym a, mrb_sym b);

    struct RClass *mrb_class_outer_module(mrb_state*, struct RClass *);
    struct RProc *mrb_method_search_vm(mrb_state*, struct RClass**, mrb_sym);
    struct RProc *mrb_method_search(mrb_state*, struct RClass*, mrb_sym);

    struct RClass* mrb_class_real(struct RClass* cl);

    void mrb_gc_mark_mt(mrb_state*, struct RClass*);
    size_t mrb_gc_mark_mt_size(mrb_state*, struct RClass*);
    void mrb_gc_free_mt(mrb_state*, struct RClass*);


## The Base Classes

Some classes are so fundamental to the Ruby language, they are accessible
directly from the mruby state. In other words, no matter where or when you
need the mruby state, these classes always come along for the ride. This is
an excerpt from the definition of the `mrb_state` structure:

    #include <mruby.h>

    typedef struct mrb_state {
      /* ... */

      struct RClass *object_class;
      struct RClass *class_class;
      struct RClass *module_class;
      struct RClass *proc_class;
      struct RClass *string_class;
      struct RClass *array_class;
      struct RClass *hash_class;

      /* ... */

      struct RClass *float_class;
      struct RClass *fixnum_class;
      struct RClass *true_class;
      struct RClass *false_class;
      struct RClass *nil_class;
      struct RClass *symbol_class;
      struct RClass *kernel_module;

      /* ... */

      struct RClass *eException_class;
      struct RClass *eStandardError_class;

      /* ... */
    } mrb_state;

Any time you need to reference one of these classes, you don't need to call
`mrb_class_get()`. Instead, it is faster to directly refer to the `struct
RClass *` that is already defined in the mruby state.

    /* This is inefficient: */
    mrb_value person_class =
      mrb_define_class(R, "Person", mrb_class_get(R, "Object"));

    /* This is better: */
    mrb_value person_class =
      mrb_define_class(R, "Person", R->object_class);


## Where is BasicObject?

You may have heard of Ruby's `BasicObject`, which is a class that ships with
the Ruby standard library that has an incredibly limited interface. It is
essentially just like a regular `Object` but with the entire `Kernel` module
taken out. The reason we tend to create classes that inherit from `Object`
and not `BasicObject` in the first place is because we usually want all of
the methods inside the `Kernel` module.

You may want to use the `BasicObject` class if your application is
particularly conservative about resources. However, the `mrb_state`
structure does not contain a direct reference to the `BasicObject` class. In
this case you are going to have to search for it with `mrb_class_get():`

    mrb_value basicobject_class = mrb_class_get(R, "BasicObject");


## What's the difference between "struct RClass" and "Class" ?

There is a subtle but significant difference between `struct RClass` and
`Class`. `struct RClass` is _not_ a Ruby object. It is the C implementation
of classes. `Class`, on the other hand, _is_ a Ruby object.


## Note

Notice that `struct RClass` represents both Ruby classes and Ruby modules.
Also notice that a class must have a superclass, whereas a module must not.

    #include <mruby.h>
    struct RClass *mrb_define_class(mrb_state *, const char *name, struct RClass *super);
    struct RClass *mrb_define_module(mrb_state *, const char *name);


## The mruby function type

mruby defines a kind of function pointer called `mrb_funct_t`:

    typedef mrb_value (*mrb_func_t)(mrb_state *mrb, mrb_value obj);

In plain English, this means "a variable of type `mrb_func_t` is a function
with two arguments: the mruby state and a value, and returns a value."


## Including a module inside a class

To include a module inside of a class, we use the `mrb_include_module()`
function:

    void mrb_include_module(mrb_state*, struct RClass *klass, struct RClass *module);

As an example, let's make a `RecordCollection` class Enumerable:

    # Ruby
    class RecordCollection
      include Enumerable
    end

<!-- -->

    /* C */
    struct RClass *record_collection = mrb_class_get(R, "RecordCollection");
    struct RClass *enumerable = mrb_class_get(R, "Enumerable");
    mrb_include_module(R, record_collection, enumerable);

Note that this is not a complete implementation of the `RecordCollection`
class. Specifically, the definition of `RecordCollection#each` is missing,
which is required in order to make `Enumerable` useful. The point is to
illustrate what the mruby code looks like.
