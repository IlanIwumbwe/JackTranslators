CXX = g++
CXXFLAGS = -std=c++17

all: compiler 

compiler: Compiler/Lexer.cpp Compiler/helper_funcs.cpp Compiler/JackTokeniser.cpp Compiler/JackAnalyser.cpp Compiler/Compiler.cpp Compiler/VMtranslator.cpp 
	$(CXX) $(CXXFLAGS) -o compiler Compiler/Lexer.cpp Compiler/helper_funcs.cpp Compiler/JackTokeniser.cpp Compiler/JackAnalyser.cpp Compiler/Compiler.cpp Compiler/VMtranslator.cpp 

clean:
	rm -f compiler