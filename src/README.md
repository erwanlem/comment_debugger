The project has the following structure:

- **main.c** : entry point of the program
- **command.h** : parse user entry to create a structured request stored in the structure `command`. This structure will be used to open the correct file and to apply the correct operation on this file.
- **lexer/lexer.l** : lexical analyzer that extract debug comments from user files.
- **reader.h** : Get debug comment using `lexer.l` and generate *gdb* corresponding requests. Then it sends requests to the provider. It finally gets structured outputs from `parser.h`.
- **provider.h** : Interface between gdb and main program. Send gdb input and get gdb output.
- **parser.y** : *YACC* parser for gdb grammar.
- **parser.h** : parse gdb output
- **print.h** : get structured outputs from `reader.h` and print them in an appropiate format.