# Example to reproduce a negative reference count crash

I've used swig 4.0.1 and python 3.9.2. I had no luck with swig 4.0.2 neither.

Steps to reproduce

1. Download the files. 
2. Open EndInterpreterNegativeRefCnt\ConsoleApplication\ConsoleApplication.sln in Visual Studio 2017
3. Set ConsoleApplication as start-up project 
4. Set platform/configuration to Debug and x86 (at least I used those)
5. Follow the comments in ConsoleApplication.cpp 
6. Run ConsoleApplication in debugger 

-> Debugger will break due to a negative reference count. The values in 
   the debugger looks like the object has been deleted already.
