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


## What mruby is Good For

### Let your C program be scriptable with Ruby

.


### Make your C program more object-oriented without too much fuss

When you linking your C program against mruby, you don't _have_ to expose a
user-facing Ruby interface. Instead, you can use use mruby on a purely
internal basis. If you want a more flexible alternative to structs, but you
don't want to incur too much overhead, you can use mruby's encapsulation and
automatic memory management features. In other words, you can use mruby as
an alternative to GObject.

Despite being extremely portable, GLib is notoriously difficult to compile
on Microsoft Windows and Mac OS X.
