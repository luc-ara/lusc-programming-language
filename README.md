# LUSC Programming Language
_This is my attempt at creating a programming language from scratch. It will be written in `C`, using `flex` and `bison` for lexing and parsing. The main goal is to learn the entire process of developing a complex `C` project and showcase my knowledge to potential employers. Creating a useful language is a desirable outcome, but secondary to the learning experience and the ability to experiment with a variety of language features._

_Expected results include knowledge about `C`, `git`, `flex`, `bison`, `makefile`, `bash`, regular expressions, `EBNF`, and eventually `ncurses` and assembly language. The project will be developed incrementally, starting with a simple interpreter, followed by gradual feature additions, and eventually a compiler._

## Description
The initial concept is a simple lisp/scheme language with dynamic types implemented using nanboxing. Following Lisp tradition, the language will use prefix notation with fully parenthesized S-expressions. For example, `a + b * c / d - e` becomes `(- (+ a (/ (* b c) d)) e)`. While seemingly harder to understand, this notation eliminates the need for operator precedence and associativity, simplifying the parser.

Using nanboxing, every object can be represented by a 64-bit word, allowing efficient type handling. Doubles, booleans, characters, and integers are stored in specific bit layouts, while strings and pairs are represented as pointers to a `Cons` cell, an array of two words.

## Requirements
- **GCC**
- **Flex**
- **Bison**
- **Make**

## Installation
```
sudo apt install flex bison
git clone git@github.com:luc-ara/lusc-programming-language.git
cd lusc-programming-language
make all
```