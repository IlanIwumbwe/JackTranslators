#! /bin/sh

# cleanup
make -f Compiler/makefile.mk clean

# build compiler 
make -j -C Compiler/ -f makefile.mk
echo "Finished building compiler in Compiler/ directory"