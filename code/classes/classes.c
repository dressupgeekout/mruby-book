/*
 * classes.c
 * Charlotte Koch <cfkoch@sdf.lonestar.org>
 *
 * In this program, we define a class Person, which is a subclass of class
 * Object. Then we instantiate a person and send #inspect to it, which
 * returns a Ruby String. We "extract" the C string from the String object
 * and write the result to the standard output.
 */

#include <stdio.h>
#include <stdlib.h>

#include <mruby.h>
#include <mruby/string.h>

int
main(void)
{
  mrb_state *R;
  struct RClass *person_class;
  mrb_value person;
  mrb_value person_string;

  R = mrb_open();
  person_class = mrb_define_class(R, "Person", R->object_class);
  person = mrb_obj_new(R, person_class, 0, NULL);
  person_string = mrb_inspect(R, person);
  printf("%s\n", mrb_str_to_cstr(R, person_string));
  mrb_close(R);
  return EXIT_SUCCESS;
}
