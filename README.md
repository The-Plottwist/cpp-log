# cpp-log

Header only logging library.

# Benefits

- Fast

- Easy to use

- Portable (Not tested on OS X)

- Supports all of the fundamental types, except for **char16_t** and **char32_t**

# Usage

### Constructor:

Constructor takes four arguments. These are:

- FILE NAME

- DIRECTORY or PATH

- CONSOLE LEVEL

- FILE LEVEL

respectively.

The levels on the other hand are:

- DEBUG

- INFO

- ERROR

- WARNING

- CRITICAL

- DISABLED

So an example would be:

```cpp
LOG lg{"Experiment.log", "LOG", LOG::LEVEL::WARNING, LOG::LEVEL::DEBUG};
```

which the log file can be found in "Program_dir/LOG/Experiment.log". With the **console level** set to WARNING and the **file level** set to DEBUG.

### Logging functions:

```cpp
debug("");       //or debug("", variable);
info("");        //or info("", variable);
error("");       //or error("", variable);
warning("");     //or warning("", variable);
critical("");    //or critical("", variable);
```

variable types can be any type except for char16_t and char32_t.

### File operation:

All of the below functions accecpts arguments. If no argument is given, then they will return their value in string form.

```cpp
path();             //accepts string
file_name();        //accepts string

console_level();    //accepts levels (LOG::LEVEL::DEBUG/INFO/...)
file_level();       //accepts levels (LOG::LEVEL::DEBUG/ERROR/...)
```

# Examples

```cpp
#include "cpp-log/Log.h"

LOG lg{"Experiment.log", "LOG", LOG::LEVEL::WARNING, LOG::LEVEL::DEBUG};

int main () {

  const int x{-123};
  const int y{521};

  lg.debug("This message will not appear in the console but will in the log file");
  lg.warning("This message will appear both in the console and in the log file");

  lg.critical("The X: ", x);
  lg.critical("The Y: ", y);  //or lg.critical("The X: " + std::to_string(x) + ", The Y: ", y);

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
[25-08-2020] [19:49:18] 0ms :DEBUG: This message will not appear in the console but will in the log file
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

#### Contribution:

You can contact me at mail.fyegin@gmail.com (first dot is not neccessary)
