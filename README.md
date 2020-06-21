# cpp-log
### Description:
Single file logging library for c++. (Available opreating systems are Linux and Windows)

### Why:

I don't like complicated solutions for simple tasks.
Whenever i looked for logging libraries for c++ i found complicated multi-file libraries.
For me its a preference.
You can always clone an 'a library'. It's all up to you.
What i give you is that a single header file. Which only uses standard c++ library.

# Usage:
### First, declare a global object:
```c++
Log lg{"Experiment.log", "LOG", "warning", "debug"};
```
  * First argument: Name of the log file.
  * Second argument: Path or directory name.
  * Third argument: Console level. (The logging level that you want to print to the console.)
  * Fourth and last argument: File level. (The logging level that you want to write to the file.)
### Second, use that object to execute functions:
Available functions are:
```c++
lg.debug("");
lg.info("");
lg.error("");
lg.warning("");
lg.critical("");
```
All functions can take three arguments.
* string.
* double.
* double.

Last two arguments are optional and also you can send in other types like int, bool or float.

# Example program:
```c++
#include "Log.h"

Log lg{"Experiment.log", "LOG", "warning", "debug"};

int main () {

  const int x{-123};
  const int y{521};
  
  lg.debug("This message won't appear in console but will appear in the log file");
  lg.warning("This message will appear both in the console and in the log file");
  lg.critical("The x, y coordinates are: ", x, y);
  return 0;
 }
```
### In console this will result with:
```console
[21-06-2020] [15:47:44] 0ms :WARNING: This message will appear both in the console and in the log file
[21-06-2020] [15:47:44] 0ms :CRITICAL: The x, y coordinates are: -123, 521
```
### In log file this will result with:
```
[21-06-2020] [15:47:44] 0ms :DEBUG: This message won't appear in console but will appear in the log file
[21-06-2020] [15:47:44] 0ms :WARNING: This message will appear both in the console and in the log file
[21-06-2020] [15:47:44] 0ms :CRITICAL: The x, y coordinates are: -123, 521
```
# Contribution:
All contributions, suggestions, tips etc. are welcomed.
With an exception. I do this as a hobby and i am a University student. So i can't guarantee you about responding to your feedbacks. But fell free to contact me.
