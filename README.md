# cpp-log

Header only logging library.

# Benefits

- Thread safe

- Fast
  
  - All fundamental types supported
    
    - Except for char16_t & char32_t
    - Use *`std::to_string`* if that's case

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

# Examples

### Standard

```cpp
#include "cpp-log/Log.h"

LOG lg{"Experiment.log", "LOG", LOG::LEVEL::WARNING, LOG::LEVEL::DEBUG};

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

### Possible output:

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

### Valgrind

---

```console
==8838== HEAP SUMMARY:
==8838==     in use at exit: 0 bytes in 0 blocks
==8838==   total heap usage: 38 allocs, 38 frees, 132,005 bytes allocated
==8838== 
==8838== All heap blocks were freed -- no leaks are possible
==8838== 
==8838== For lists of detected and suppressed errors, rerun with: -s
==8838== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

---

### Thread

```cpp
#include <thread>
#include "cpp-log/Log.h"

LOG lg{"Experiment.log", "LOG", LOG::LEVEL::WARNING, LOG::LEVEL::DEBUG};

void test (const float &f) {

    lg.debug("Float: ", f);
    lg.info("Float: ", f);
    lg.error("Float: ", f);
    lg.warning("Float: ", f);
    lg.critical("Float: ", f);
}

int main () {

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

---

### Valgrind

```console
==8726== HEAP SUMMARY:
==8726==     in use at exit: 0 bytes in 0 blocks
==8726==   total heap usage: 124 allocs, 124 frees, 299,408 bytes allocated
==8726== 
==8726== All heap blocks were freed -- no leaks are possible
==8726== 
==8726== For lists of detected and suppressed errors, rerun with: -s
==8726== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 0 from 0)
```

---

# Warning

### *<u>In case Log file cannot open the program will be asserted.</u>*

# Contribution:

You can contact me at mail.fyegin@gmail.com OR mailfyegin@gmail.com
