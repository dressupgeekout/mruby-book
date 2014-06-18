# Booleans and Other Special Constants

If you have ever played with the C API for MRI, you may have encountered the
constants `Qnil`, `Qfalse` and so on. They strike back in mruby, too!

    #include <mruby/value.h>

    enum mrb_special_consts {
      MRB_Qnil    = 0,
      MRB_Qfalse  = 2,
      MRB_Qtrue   = 4,
      MRB_Qundef  = 6,
    };
