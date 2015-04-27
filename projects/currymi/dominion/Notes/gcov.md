### Miles A. Curry (currymi)
### Github: Micurry
### CS-362-400 - Spring 2015
### Notes on gcov


gcov - GCC's Test Coverage Program
==================================

gocv helps you determine which modules should be optimized.


It generates the following statistics:

    * How often each line of code executes
    * What lines of code are actually executed
    * how much computing time each section of code uses


Notes Using Gcov
----------------

gocv should be ran under the following conditions:

    * With optimizations off
    * Each line should have only one statement
    * And not use complicated macro (ie function macros (plus no one likes those
      anyway.))
    
gcov only works with the GCC compiler.

The .gcov logfile
----------------

The sourcefile.gcov logfiles contains the amount of times each line in the
source file was executed.











Personal Notes
==============

Because gcov reports on the time each section of code uses, this would be a
good way to determine what parts of a program can benefit from threading -
parallel processing.
