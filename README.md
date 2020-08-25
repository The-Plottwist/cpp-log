# cpp-log

Header only logging library. (For Linux and Windows)

# Goals

- Thread safe
  
  - Checks if standard thread library included (_GLIBCXX_THREAD)
    
    - If so enables mutex.

- Fast
  
  - No type conversion.
    
    - Excluding "short"

- Easy to use
  
  - Has five logging functions & four for miscellaneous

# Functions

### Logging:

```cpp
debug("");
info("");
error("");
warning("");
critical("");
```

- All can take up to two arguments. 
  
  - First type: string
  
  - Second type: int, bool, float, long long int...

### Miscellaneous:

```cpp
set_path("");
set_file_name("");

path();
file_name();
```

- You can set & get your logging directory and its name.
  
  - "set_path" can be a single directory too.
  
  - If it is a path make sure all directories exist.
    
    - **<mark>Has no recurs.</mark>**  Only makes the last directory.

# Example program:

```cpp
#include "cpp-log/Log.h"

Log lg{"Experiment.log", "LOG", Log::LEVEL::WARNING, Log::LEVEL::DEBUG};

int main () {

  const int x{-123};
  const int y{521};

  lg.debug("This message won't appear in console but will appear in the log file");
  lg.warning("This message will appear both in the console and in the log file");
  lg.critical("The X: ", x);
  lg.critical("The Y: ", y);
  return 0;
 }
```

# Possible output:

### Console

```console
[25-08-2020] [18:05:9] 0ms :WARNING: This message will appear both in the console and in the log file
[25-08-2020] [18:05:9] 0ms :CRITICAL: The X: -123
[25-08-2020] [18:05:9] 0ms :CRITICAL: The Y: 521
```

### Log file

```prolog
[25-08-2020] [18:05:9] 0ms :DEBUG: This message won't appear in console but will appear in the log file
[25-08-2020] [18:05:9] 0ms :WARNING: This message will appear both in the console and in the log file
[25-08-2020] [18:05:9] 0ms :CRITICAL: The X: -123
[25-08-2020] [18:05:9] 0ms :CRITICAL: The Y: 521
```

# Contribution:

You can contact me at mail.fyegin@gmail.com OR mailfyegin@gmail.com
