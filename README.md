# cpp-log

Header only logging library.

# Benefits

- Thread safe
  
  - Checks if standard thread library included.
    
    - If so enables mutex.

- Fast
  
  - No type conversion.
    
    - Excluding "short"

- Easy to use
  
  - Has five logging functions & four additional for miscellaneous

- Portable
  
  - Didn't tested in Mac OS X but in theory it should work.

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

# Examples:

### Standard

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

  //OR

  lg.critical("The X: " + std::to_string(x) + ", The Y: ", y);

  return 0;
 }
```

### Possible Output:

##### Console

```console
[25-08-2020] [19:49:18] 0ms :WARNING: This message will appear both in the console and in the log file
[25-08-2020] [19:49:18] 0ms :CRITICAL: The X: -123
[25-08-2020] [19:49:18] 0ms :CRITICAL: The Y: 521
[25-08-2020] [19:49:18] 0ms :CRITICAL: The X: -123, The Y: 521
```

##### Log file

```prolog
[25-08-2020] [19:49:18] 0ms :DEBUG: This message won't appear in console but will appear in the log file
[25-08-2020] [19:49:18] 0ms :WARNING: This message will appear both in the console and in the log file
[25-08-2020] [19:49:18] 0ms :CRITICAL: The X: -123
[25-08-2020] [19:49:18] 0ms :CRITICAL: The Y: 521
[25-08-2020] [19:49:18] 0ms :CRITICAL: The X: -123, The Y: 521
```

---

### Thread

```cpp
#include <thread>
#include "Log.h"

Log lg{"Experiment.log", "LOG", Log::LEVEL::WARNING, Log::LEVEL::DEBUG};

void test (const float &f) {

    lg.debug("Float: ", f);
    lg.info("Float: ", f);
    lg.error("Float: ", f);
    lg.warning("Float: ", f);
    lg.critical("Float: ", f);
}

int main () {

    int i{15123123};
    float f{1098.688};

    std::thread threads[5];

    for (auto &th : threads) th = std::thread(test, f);
    for (auto &th : threads) th.join();

    return 0;
 }
```

### Possible Output:

##### Console

```console
[25-08-2020] [19:58:22] 0ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 0ms :CRITICAL: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :CRITICAL: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :CRITICAL: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :CRITICAL: Float: 1098.69
[25-08-2020] [19:58:22] 2ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 2ms :CRITICAL: Float: 1098.69
```

##### Log File

```console
[25-08-2020] [19:58:22] 0ms :DEBUG: Float: 1098.69
[25-08-2020] [19:58:22] 0ms :INFO: Float: 1098.69
[25-08-2020] [19:58:22] 0ms :ERROR: Float: 1098.69
[25-08-2020] [19:58:22] 0ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 0ms :CRITICAL: Float: 1098.69
[25-08-2020] [19:58:22] 0ms :DEBUG: Float: 1098.69
[25-08-2020] [19:58:22] 0ms :INFO: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :ERROR: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :CRITICAL: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :DEBUG: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :INFO: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :ERROR: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :CRITICAL: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :DEBUG: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :INFO: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :ERROR: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 1ms :CRITICAL: Float: 1098.69
[25-08-2020] [19:58:22] 2ms :DEBUG: Float: 1098.69
[25-08-2020] [19:58:22] 2ms :INFO: Float: 1098.69
[25-08-2020] [19:58:22] 2ms :ERROR: Float: 1098.69
[25-08-2020] [19:58:22] 2ms :WARNING: Float: 1098.69
[25-08-2020] [19:58:22] 2ms :CRITICAL: Float: 1098.69
```

# Contribution:

You can contact me at mail.fyegin@gmail.com OR mailfyegin@gmail.com
