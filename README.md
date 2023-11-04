# JackTranslators

## Running the compiler
- Use `./run.sh` to build. A `compiler` executable will be created.
Run it like so: `./compiler -p <path> -i <initial> -f <final> -t`. 
`<initial>` can be `jack` or `vm`.
`<final>` can only be `asm`
`-t` is an optional flag, which tells the compiler whether or not to save the programs parse tree and tokens in `.xml` files

## Running the assembler
Assembler is in python. 

Run by `python3 assembler.py` in the `Assembler/` directory. 
