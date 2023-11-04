CXX = g++
CXXFLAGS = -std=c++17 -Wall 
SRCS = main.cpp
OBJS = $(SRCS:.cpp=.o)
TARGET = compiler

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

main.o: main.cpp helper_funcs.h Lexer.h Tokeniser.h Compiler.h VMtranslator.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

.PHONY: clean

clean:
	rm -f $(OBJS) $(TARGET)
