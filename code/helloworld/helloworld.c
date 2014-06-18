/*
 * helloworld.c
 * Christian Koch <cfkoch@sdf.lonestar.org>
 *
 * This is the canonical "Hello World" program. It uses mrb_load_string(),
 * which is a very high-level (and slightly slower) way of acheiving this.
 */

#include <stdlib.h>

#include <mruby.h>
#include <mruby/compile.h>

int
main(void)
{
  mrb_state *R;

  R = mrb_open();
  mrb_load_string(R, "puts 'hello, world'");
  mrb_close(R);
  return EXIT_SUCCESS;
}
