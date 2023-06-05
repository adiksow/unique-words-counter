# Unique words counter

Program that counts the number of distinct unique words in a file whose name is passed as an argument to a program.
For example, given the file content "a horse and a dog" the program must output "4" (the word 'a' appears twice but only accounts for one distinct unique occurrence).
The input text is guaranteed to contain only 'a'..'z' and space characters in ASCII encoding.
The program is able to handle large inputs (e.g. 32 GiB)
It is assumed that all unique words fit into memory when using the data structure.
Solution utilize all available CPU resources.

## Features

* **CMake** configuration;

* Cross-platform app; 

## Getting Started

These instructions will get you a copy of the project up and running on your local
machine for development and testing purposes.

### Prerequisites

* **CMake v3.16+** - found at [https://cmake.org/](https://cmake.org/)

* **C++ Compiler** - needs to support at least the **C++17** standard, i.e. *MSVC*,
*GCC*, *Clang*

### Installing and building

```bash
mkdir build
cd build
cmake ..
cmake --build .
./uwc ../test_data/test_1.txt
```

## Authors

* **Andrii Dubyk** - [@andrewDubyk](https://github.com/andrewDubyk)

## License

This project is licensed under the [Unlicense](https://unlicense.org/) - see the
[LICENSE](LICENSE) file for details