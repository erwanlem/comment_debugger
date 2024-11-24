# COMMENTS DEBUGGER (NEED A REAL NAME)

## Motivation

This software aims to change the way we debug our program. A lot of programmers debug their programs with the *print method*. This have the advantage to be easy to learn and quick in use (a least that's what we think). But this method that we could define as "archaic" has also a lot of disadvantages. 

First you have to modify your code. It could seem safe because, after all that's just a print... But who has never made a mistake while modifying a code ? (It's a rhetorical question). 

Ok now let's imagine you are the best programmer on earth and you have never made mistakes while modifying your code. You have a program hard to debug and it took you hours to find that your collaborator didn't free a variable (always the others...). You put prints everywhere in your code and in every file of the project. It's now time to clear everything and after all this work of removing every print you execute your code and something is still printing. You still have to find where it comes from. I think that it illustrates well the problems involved by this method.
If finally you are still not conviced by those arguments, listen to your computer science teachers who said that you have to use a debugger to debug.

The purspose of our software is to create a "clean" alternative to the *print method* by getting debug information from the comments of the program. This has the advantage of being easy to use, easy to learn and last but not least safe. 


## Quick start

Here is an example in C++ of how to use our tool.
``` C++
int divisors = 1;

int main() {
    int n = 2; // @ debugPointName1 divisors

    for (int i = 1; i < n; ++i) {
        if (n % i == 0) {
            divisors++; // @ debugPointName2
        }
    }

}
```

In this example we have 2 breakpoints. The first one (line 16) prints the state of `divisors`. The second one (line 20) prints the state of all alive variables. 

Below you can see the expected output of this program with the use of a debugger.

```txt
******************************************
** At debugPointName1 **
Variable    Address     Value
divisors    0x0000001     1

******************************************
** At debugPointName2 **
Variable    Address     Value
divisors    0x0000001     1
n           0x0000002     2
i           0x0000003     1

```

Another feature of the debugger is to remove every debug comment whenever you want by typing just one command.


## Installation

The current version of the debugger can be build using CMake.

``` Shell
~/comment_debugger/$ mkdir build
~/comment_debugger/$ cd build
~/comment_debugger/$ cmake ../src/
~/comment_debugger/$ make install
~/comment_debugger/$ ../install/bin/debugTool file.cpp
```