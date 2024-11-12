# TODO list

## Upcoming tasks

- [x] Fix the error with multiline strings
- [x] Allow comments between linebreaks on strings
- [x] Add negative numbers to the scanner
- [x] Create and write a bison file
- [x] Write the number scanners
- [ ] Rewrite the number scanners with at least a semblance of precision
- [ ] Write the escape sequence scanners
- [x] Write tests for the integer scanners
- [x] Write tests for the double scanners
- [ ] Write tests for the escape sequence scanners
- [ ] Write the C code for the parser

## Known issues

- [ ] The scanner doesn't recognize numbers and identifiers at the end of input
    - Possible fix: Implementing syntax errors will remove the need for the delimiter character after

## Distant dreams

- [ ] Simplify the scanners with macros
- [ ] Improve floating point scanning precision
