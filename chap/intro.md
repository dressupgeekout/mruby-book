<a name="intro"></a>
# Introduction

**mruby** is the lightweight implementation of Ruby.


## Isn't ERB "Embedded Ruby?"

Yes and no. The meaning of "embedded" in ERB is different than what it means
for mruby.

To make matters even more confusing, there exists a mruby gem called "merb"
which performs ERB-like templating inside mruby. To make matters confusing
still, there was "regular" Ruby web framework called Merb, which supposedly
stands for "Mongrel plus ERB." This Merb was merged into Ruby on Rails back
in 2008.


## Isn't there already a C API for Ruby?

Yes, there is. But it is quite bulky and it is not at all _embeddable._
Unlike the "vanilla" Ruby distribution (MRI, or "Matz's Ruby Interpreter"),
it and it is very straightforward to simply "vendor" the entire mruby source
code into your own project. That is simply not possible with any other Ruby
implementation.

With mruby, the Ruby language can now fill the same niche that Lua has found
for itself.

