CC=gcc
CFLAGS=-std=c99 -Wall -pedantic -g -O3
LDFLAGS=-lfl
LIBS=lex.yy.c

LEXER=flex

all: lexer build

lexer: $(LEXF)
	$(LEXER) accept.l

build: $(LIBS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^