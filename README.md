# Compile Time Brainfuck

## What is Brainfuck?
Brainfuck is an esoteric, Turing complete, minimalist programming language. See https://en.wikipedia.org/wiki/Brainfuck for more details.

## What is this project?
This project is a Brainfuck interpreter written in C++. However, the Brainfuck program is interpreted at compile time, and the output is generated as a C++ compile error. That is, attempting to compile the C++ program is how the interpreter is run. When compiled with `g++`, the output will be in the form:
```
...variable ‘print<std::array<unsigned char, 4096>{"<THE OUTPUT HERE>"....
```

The interpreter looks for the Brainfuck program and input in macros named `BF_PROGRAM` and `BF_INPUT`, respectively.

## Examples

### Hello World
```
$ g++ main.cpp -std=c++20 -DBF_PROGRAM="++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++."
main.cpp: In function ‘int main()’:
main.cpp:86:23: error: variable ‘print<std::array<unsigned char, 4096>{"Hello World!\012"}> _’ has initializer but incomplete type
   86 |         print<output> _{};
      |                       ^
```
Notice that the interpreter in run by calling `g++`

## Echo back first 3 chars
```
g++ main.cpp -std=c++20 -DBF_PROGRAM=',.,.,.' -DBF_INPUT='abc'
main.cpp: In function ‘int main()’:
main.cpp:86:23: error: variable ‘print<std::array<unsigned char, 4096>{"abc"}> _’ has initializer but incomplete type
   86 |         print<output> _{};

```

## Printing my name
```
sohaib@sohaib-X551MA:~/Documents/cpp/consteval_bf$ g++ main.cpp -std=c++20 -DBF_PROGRAM='++[---------->+<]>.-[------>+<]>-.+++.+.--[--->+<]>-.[->+++<]>++.[--->+<]>+++.-[---->+<]>++.>-[--->+<]>--.[--->+<]>--.-------.-------.++++++++.-------.'
main.cpp: In function ‘int main()’:
main.cpp:86:23: error: variable ‘print<std::array<unsigned char, 4096>{"Made by Sohaib"}> _’ has initializer but incomplete type
   86 |         print<output> _{};
      |                       ^
```
