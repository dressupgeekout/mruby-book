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


## The mruby function type

mruby defines a kind of function pointer called `mrb_funct_t`:

    typedef mrb_value (*mrb_func_t)(mrb_state *mrb, mrb_value);

In plain English, this means "a variable of type `mrb_func_t` is a function
with two arguments: the mruby state and a value, and returns a value."


## Note

Notice that `struct RClass` represents both Ruby classes and Ruby modules.
Also notice that a class must have a superclass, whereas a module does not.

    #include <mruby.h>
    struct RClass *mrb_class_new(mrb_state *mrb, struct RClass *super);
    struct RClass *mrb_module_new(mrb_state *mrb);
