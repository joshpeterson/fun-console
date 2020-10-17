# Fun C++: Console

[![Build
Status](https://travis-ci.com/joshpeterson/fun-console.svg?branch=master)](https://travis-ci.com/joshpeterson/fun-console)

C++ should be fun! This project allows for printing to the console with colors,
bold, italics, and emojis!

## The Kitchen Sink

Check out
[everything](https://github.com/joshpeterson/fun-console/blob/master/src/main.cpp)
Fun Console can do:

```cpp
#include "console.h"

void kitchenSink()
{
  fun::console("A new line is printed by default.");
  fun::console("Emojis are supported: :musical note: Baby :shark:, do do "
               ":musical note:");
  fun::console("*Bold* and _italic_ markdown text is supported.");
  fun::console("And "
               "[red]c[/red][cyan]o[/cyan][yellow]l[/yellow][green]o[/"
               "green][blue]r[/blue][magenta]s[/magenta]!");
}

int main()
{
  kitchenSink();
  return 0;
}
```

## Build it!

Fun Console works on Windows, macOS, and Linux. To build it, you will need to
install CMake, Ninja, and a C++ compiler. Once you have those just run this
command from a terminal:

```
> ./build # or build.bat on Windows
```

Check out the `artifacts/Debug/src` directory - the Kitchen Sink demo should be
there in an executable named `fun-console` (or `fun-console.exe` on Windows).

## Use it!

Check out this [example project](https://github.com/joshpeterson/fun-console-cmake)
to see how to use Fun Console in your C++ project with CMake.
