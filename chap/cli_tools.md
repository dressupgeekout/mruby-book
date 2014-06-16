<a name="cli-tools"></a>
# The Command-Line Tools

## mruby(1)

    Usage: mruby [switches] programfile
      switches:
      -b           load and execute RiteBinary (mrb) file
      -c           check syntax only
      -e 'command' one line of script
      -v           print version number, then run in verbose mode
      --verbose    run in verbose mode
      --version    print the version
      --copyright  print the copyright


## mirb(1)

    Usage: mirb [switches]
      switches:
      -v           print version number, then run in verbose mode
      --verbose    run in verbose mode
      --version    print the version
      --copyright  print the copyright

mirb(1) is the equivalent to the regular irb(1) program that ships with MRI.
The primary difference is mirb is nowhere near as powerful as IRB. You will
find yourself relying less on mirb when developing with mruby than you have
relied on IRB for doing regular Ruby development.

"Verbose mode" is actually quite interesting from a debugging perspective.
After each method call, you get a sort of stack trace that looks like this:

    XXX YYY ZZZ
    XXX YYY ZZZ
    XXX YYY ZZZ
    XXX YYY ZZZ


## mrbc(1)


    Usage: mrbc [switches] programfile
      switches:
      -c           check syntax only
      -o<outfile>  place the output into <outfile>
      -v           print version number, then turn on verbose mode
      -g           produce debugging information
      -B<symbol>   binary <symbol> output in C language format
      --verbose    run at verbose mode
      --version    print the version
      --copyright  print the copyright

The purpose of the mrbc(1) utility is to compile your Ruby scripts into a
bytecode representation &mdash; something that Rubyists have been missing
for too long. Most notably, Python and Lua code has been distributed in this
manner since their inception.

This book won't go into the design and implementation of mruby bytecode.
The primary things to take away are that (1) it works, (2) you now _can_
easily ship Ruby code in a form that is not Ruby source, and (3) this
bytecode can execute in any host program which embeds mruby!

