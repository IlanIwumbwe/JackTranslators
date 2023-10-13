# JackTranslators

Current workflow:
- Run the compiler, input a directory to `.jack` files, or a single `.jack` file which get converted into assembly.
- Run the assembler, input a directory to `.asm` files, or a single `.asm` file which gets converted into machine code for the Hack computer.
### Running the compiler
- Use the command `./run.sh` to build the project and create a `compiler` executable, which will also be run automatically. 
- Use `./compiler` to run the executable at later times   
This will ask you for the path of the Jack files, and output an assembly files, and optionally, .xml files with the parse trees and tokens of the program. These files will be in the same directory as input directory.

### Running the assembler
The assembler is in Python at the moment. Run it using `python3 Assembler/assembler.py`, and input the path of the assembly files. 
This will output machine code in .hack files in the same directory.