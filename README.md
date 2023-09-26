# JackTranslators

- Recompile the compiler using `make`. 
- Run the compiler using `./compiler`    
This will ask you for the path of the Jack files, and output an assembly files, and optionally, .xml files with the parse trees and tokens of the program. These files will be in the same directory as input directory.

The assembler is in Python at the moment. Run it using `python3 Assembler/assembler.py`, and input the path of the assembly files. 
This will output machine code in .hack files in the same directory.