# Example to reproduce a negative refcnt crash

I've used swig 4.0.1 and python 3.9.2. I had no luck with swig 4.0.2 neither.

Just download the files. Follow the comments in ConsoleApplication.cpp and run
the ConsoleApplication. Debugger will break due to a negative reference count.
The values in the Debugger looks like the object has been deleted already.
