<a name="range"></a>
# Ranges

## The relevant functions

    #include <mruby.h>
    #define E_RANGE_ERROR (mrb_class_get(mrb, "RangeError"))

    #include <mruby/range.h>
    mrb_value mrb_range_new(mrb_state *mrb, mrb_value beg, mrb_value end, int excl);
    mrb_int mrb_range_beg_len(mrb_state *mrb, mrb_value range, mrb_int *begp, mrb_int *lenp, mrb_int len)

## Create a new Range

You can create a new `Range` object with `mrb_range_new()`. The last
parameter to that function, `int exl`, specifies whether the `end` value
should be excluded from the range. **XXX RESEARCH THIS**: If `excl` is
nonzero, then `end` is not excluded from the range; if zero, then it is
excluded. 

    # Ruby
    range1 = (0...10) # excludes 10
    range2 = (0..10) # includes 10

    /* C */ /* XXX fixme!! */
    #include <stdbool.h>
    mrb_value range1 = mrb_range_new(R, 0, 10, true); /* excludes 10 */
    mrb_value range2 = mrb_range_new(R, 0, 10, false); /* includes 10 */
