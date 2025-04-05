By- Vivek Anand 
Roll No: 23115109
Branch - CSE(4th Sem)


Custom Instruction Compiler

This project is a simple compiler built in C++ that:
Parses basic arithmetic code.
Optimizes specific patterns using custom instructions (e.g., a*a - b*b -> SQUAREDIFF a, b).
Outputs an assembly-like code.
Also includes a simple interpreter to execute the code.


Project Structure:
Custom_Instruction_Project/
|--- include/
|   |--- ast.hpp
|   |--- lexer.hpp
|   |--- parser.hpp
|   |--- codegen.hpp
|   |--- interpreter.hpp
|--- src/
|   |--- lexer.cpp
|   |--- parser.cpp
|   |--- codegen.cpp
|   |--- interpreter.cpp
|--- main.cpp
|--- input.txt           <- Sample input program
|--- output.asm          <- Generated assembly (after compilation)
|--- my_compiler.exe     <- Generated binary (after building)
|--- output_tokenzation  <- screenshot
|--- output_parsing      <- screenshot


Sample (input.txt)
int a = 4;
int b = 2;
int c = a*a - b*b;
print(c);


The compiler detects(Custom Instruction): 
x*x - y*y

and replaces with a single instruction:
SQUAREDIFF x, y

This mimics how real compilers perform optimization using Peephole techniques or custom ISA support.


How to build:
Make sure you're in the project root directory. Then run:
g++ -std=c++17 -Iinclude src/*.cpp main.cpp -o my_compiler


How to run:
After building, run:
my_compiler.exe      # On Windows

It will:
Tokenize input.txt
Parse and build AST
Generate optimized code to output.asm
Print the interpreted result


Output Example:
<--- Tokenisation --->
(INT, int)
(ID, a)
(ASSIGN, =)
(NUMBER, 4)
...

<--- Parsing --->

<--- Code Generation --->
SQUAREDIFF c, a, b

<--- Interpreting Result(s) --->
4


Built With:
C++
Standard Library (<string>, <memory>, <vector>, <fstream>, <sstream>)
Custom AST, Lexer, Parser, Code Generator, Interpreter

Thank you 😊



