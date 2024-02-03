CPPFLAGS += -std=c++17 -W -Wall -g -I include

.PHONY: default

default: bin/ast_maker

src/parser.tab.cpp src/parser.tab.hpp : src/parser.y
	bison -v -d src/parser.y -o src/parser.tab.cpp

src/lexer.yy.cpp : src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp src/lexer.flex

bin/ast_maker : src/cli.cpp src/compiler.cpp src/parser.tab.o src/lexer.yy.o src/parser.tab.o
	@mkdir -p bin
	g++ $(CPPFLAGS) -o bin/ast_maker $^

clean :
	rm -rf bin/*
	rm -rf src/*.tab.cpp
	rm -rf src/*.yy.cpp
	rm -rf src/parser.output
	rm -rf src/parser.tab.output
