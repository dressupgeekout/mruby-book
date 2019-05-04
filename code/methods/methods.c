/*
 * methods.c
 * Charlotte Koch <cfkoch@sdf.lonestar.org>
 */

#include <stdlib.h>
#include <stdio.h>

#include <mruby.h>

#if 0
static mrb_value my_special_function(mrb_state *R, mrb_value v);

static mrb_value
my_special_function(mrb_state *R, mrb_value v)
{
}
#endif


int
main(void)
{
  mrb_state *R;

  R = mrb_open();
  mrb_close(R);
  return EXIT_SUCCESS;
}
