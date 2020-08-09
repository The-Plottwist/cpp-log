# cpp-log
### Description:
Single file logging library for c++. (Available opreating systems are Linux and Windows)

### Why:

I don't like complicated solutions for simple tasks.
Whenever i look for logging libraries for c++ i found complicated multi-file libraries.
For me its a preference.
You can always clone an 'a library'. It's all up to you.
What i give you is that a single header file. Which only uses standard c++ library.

# Syntax:
```c++
//Usage of curly paranthesis on initialization encouraged for C++ 11 and onwards.
Log lg{FİLE_NAME, DIR_NAME/PATH, CONSOLE_LEVEL, FILE_LEVEL};
```

### Available functions:
```c++
lg.path();
lg.file_name();

lg.debug("");
lg.info("");
lg.error("");
lg.warning("");
lg.critical("");
```
Other than the first two all of the above functions can take three arguments.
* string.
* int, bool, float or double.
* int, bool, float or double.

Last two are optional.   

# Example program:
```c++
#include "cpp-log/Log.h"

Log lg{"Experiment.log", "LOG", LEVEL::WARNING, LEVEL::DEBUG};

int main () {

  const int x{-123};
  const int y{521};
  
  lg.debug("This message won't appear in console but will appear in the log file");
  lg.warning("This message will appear both in the console and in the log file");
  lg.critical("Same as above with higher priority and has variables: ", x, y);
  return 0;
 }
```
### In console this will possibly result with:
```console
[21-06-2020] [15:47:44] 0ms :WARNING: This message will appear both in the console and in the log file
[21-06-2020] [15:47:44] 0ms :CRITICAL: Same as above with higher priority and has variables: -123, 521
```
### In log file this will possibly result with:
```
[21-06-2020] [15:47:44] 0ms :DEBUG: This message won't appear in console but will appear in the log file
[21-06-2020] [15:47:44] 0ms :WARNING: This message will appear both in the console and in the log file
[21-06-2020] [15:47:44] 0ms :CRITICAL: Same as above with higher priority and has variables: -123, 521
```
# Contribution:
All contributions, suggestions, tips etc. are welcomed.
With an exception. I do this as a hobby and i am a University student. So i can't guarantee you about responding to your feedbacks. But feel free to contact me.
