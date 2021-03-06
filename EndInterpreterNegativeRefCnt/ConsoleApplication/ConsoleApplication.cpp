// ConsoleApplication5.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "python.h"
#define Py_BUILD_CORE
#include "internal/pycore_pystate.h"
#include "string"
#include "thread"
#include "vector"



int main()
{
  std::vector<PyThreadState*> subinterpreters;
  std::vector<PyObject*> modules;

  Py_SetProgramName(L"ConsoleApplication");
  
  //Adjust the following line and remove the x.

  //The path needs to be set in both projects' settings below 
  // "C++" -> "Additional Include Directories" and "Linker" -> "Additional Library Directories"

  //And copy the python*_d.dll to the output path (e.g. to ConsoleApplication\Debug)
  xPy_SetPythonHome(L"D:\\Python_3_9_2\\Win32"); //assuming the interpreter has been installed to "D:\Python_3_9_2\Win32"

  auto current_path = Py_GetPath();
  //Adjust the following line and remove the x.
  xauto newPath = std::wstring(current_path) + L";" + L"D:\\EndInterpreterNegativeRefCnt";
  Py_SetPath(newPath.c_str());
  Py_InitializeEx(0);

  //save main thread state
  auto mainTs = PyThreadState_Get();
  PyEval_SaveThread();

  for (unsigned int i = 0; i < 8; ++i)
  {  
    //create multiple new sub-interpreters and load a module
    PyEval_RestoreThread(mainTs);
    subinterpreters.push_back(Py_NewInterpreter());
    PyEval_SaveThread();

    PyEval_RestoreThread(subinterpreters.back());
    modules.push_back(PyImport_ImportModule(("module"+std::to_string(i+1)).c_str()));
    PyEval_SaveThread();
  }

  for (unsigned int i = 8; i > 0; --i)
  {
    //stop sub-interpreters
    PyEval_RestoreThread(subinterpreters[i - 1]);
    Py_DecRef(modules[i - 1]);
    Py_EndInterpreter(subinterpreters[i - 1]);
    PyThreadState_Swap(mainTs);
    PyEval_SaveThread();
  }
    
  PyThreadState_Swap(mainTs);  
  Py_FinalizeEx();
  return 0;
}

