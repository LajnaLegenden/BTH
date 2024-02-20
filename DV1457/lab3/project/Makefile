# Compiler and options
CC=gcc
BISON=bison
FLEX=flex
CFLAGS=-c -I$(SRC_DIR)
OFLAGS=-o 
BIN_DIR=./bin/
SRC_DIR=./lexyacc-code/
ARTIFACTS_DIR=./artifacts/

# Targets
all: $(BIN_DIR)calc3a.exe $(BIN_DIR)calc3b.exe $(BIN_DIR)calc3g.exe $(BIN_DIR)calc3i.exe

$(BIN_DIR)calc3a.exe: $(ARTIFACTS_DIR)y.tab.o $(ARTIFACTS_DIR)lex.yy.o $(ARTIFACTS_DIR)calc3a.o
	$(CC) $(ARTIFACTS_DIR)y.tab.o $(ARTIFACTS_DIR)lex.yy.o $(ARTIFACTS_DIR)calc3a.o $(OFLAGS) $(BIN_DIR)calc3a.exe

$(BIN_DIR)calc3b.exe: $(ARTIFACTS_DIR)y.tab.o $(ARTIFACTS_DIR)lex.yy.o $(ARTIFACTS_DIR)calc3b.o
	$(CC) $(ARTIFACTS_DIR)y.tab.o $(ARTIFACTS_DIR)lex.yy.o $(ARTIFACTS_DIR)calc3b.o $(OFLAGS) $(BIN_DIR)calc3b.exe

$(BIN_DIR)calc3g.exe: $(ARTIFACTS_DIR)y.tab.o $(ARTIFACTS_DIR)lex.yy.o $(ARTIFACTS_DIR)calc3g.o
	$(CC) $(ARTIFACTS_DIR)y.tab.o $(ARTIFACTS_DIR)lex.yy.o $(ARTIFACTS_DIR)calc3g.o $(OFLAGS) $(BIN_DIR)calc3g.exe

$(BIN_DIR)calc3i.exe: $(ARTIFACTS_DIR)y.tab.o $(ARTIFACTS_DIR)lex.yy.o $(ARTIFACTS_DIR)calc3i.o
	$(CC) $(ARTIFACTS_DIR)y.tab.o $(ARTIFACTS_DIR)lex.yy.o $(ARTIFACTS_DIR)calc3i.o $(OFLAGS) $(BIN_DIR)calc3i.exe

$(ARTIFACTS_DIR)y.tab.o: $(SRC_DIR)calc3.y
	$(BISON) -y -d $(SRC_DIR)calc3.y
	$(CC) $(CFLAGS) y.tab.c -o $(ARTIFACTS_DIR)y.tab.o

$(ARTIFACTS_DIR)lex.yy.o: $(SRC_DIR)calc3.l
	$(FLEX) $(SRC_DIR)calc3.l
	$(CC) $(CFLAGS) lex.yy.c -o $(ARTIFACTS_DIR)lex.yy.o

$(ARTIFACTS_DIR)calc3a.o: $(SRC_DIR)calc3a.c
	$(CC) $(CFLAGS) $(SRC_DIR)calc3a.c -o $(ARTIFACTS_DIR)calc3a.o

$(ARTIFACTS_DIR)calc3b.o: $(SRC_DIR)calc3b.c
	$(CC) $(CFLAGS) $(SRC_DIR)calc3b.c -o $(ARTIFACTS_DIR)calc3b.o

$(ARTIFACTS_DIR)calc3g.o: $(SRC_DIR)calc3g.c
	$(CC) $(CFLAGS) $(SRC_DIR)calc3g.c -o $(ARTIFACTS_DIR)calc3g.o

$(ARTIFACTS_DIR)calc3i.o: $(SRC_DIR)calc3i.c
	$(CC) $(CFLAGS) $(SRC_DIR)calc3i.c -o $(ARTIFACTS_DIR)calc3i.o

clean:
	rm -f $(ARTIFACTS_DIR)*.o $(BIN_DIR)*.exe y.tab.c lex.yy.c y.tab.h
