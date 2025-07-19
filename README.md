# LilCC - A C Compiler

To learn how a computer actually does things like math, comparisons, scoped variables, etc. I've decided to create my own little C compiler.
This compiler is for educational purposes and should not actually be used.

### Target Language

Since I have the most knowledge & most comfortable in C. I've decided to choose to compile C down to ASM. It is a happy coincidence that C is one step above ASM which should make the translation easier than some higher-level languages.
C also is pretty bare bones, so I won't have to implement a ton of libraries. Also I'm not going to implement an entire standard of C (not yet atleast). I'm only going to implement enough so that the compiler can compile itself.

### Goals

Short Term Goals

    [] - Add If/Else (no Else if) statements
    [] - Add Loops (for & while)
    [] - Types

Long Term Goal
    [] - Can self compile itself

### My Dev Environment

This compiler (for now) is only going to be tested on my machine that I'm developing it on. That machine is Arch Linux 6.15.4-arch2-1. I'm also going to be using clang & gcc to compile the compiler while it's in development

### References

While I'm building my own compiler, I will look at and maybe borrow some code from similar projects like the ones listed below:

  + [SubC](http://www.t3x.org/subc/) by Nils M Holm
  + [acwj](https://github.com/DoctorWkt/acwj) by DoctorWkt
  + [Swieros C Compiler](https://github.com/rswier/swieros/blob/master/root/bin/c.c) by Robert Swierczek
  + [catc](https://github.com/yui0/catc) by Yuichiro Nakada
  + [amacc](https://github.com/jserv/amacc) by Jim Huang
  + [Small C](https://en.wikipedia.org/wiki/Small-C) by Ron Cain,
  James E. Hendrix, derivatives by others
