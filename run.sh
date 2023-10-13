#! /bin/sh

# cleanup
rm -f compiler

# build compiler 
make -j -f makefile compiler

# run compiler executable
./compiler