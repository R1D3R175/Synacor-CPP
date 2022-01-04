CC=g++
VM_FILE = ./src/synacor.cpp
VM_EXEC = vm.exe
ROM_FILE = ./src/compiler.cpp
ROM_EXEC = rom.exe

all: run

$(VM_EXEC): $(VM_FILE)
	$(CC) $^ -o $@

$(ROM_EXEC): $(ROM_FILE)
	$(CC) $^ -o $@
	$(ROM_EXEC)
	rm $(ROM_EXEC)

run: 
	$(ROM_EXEC)
	$(VM_EXEC) test.bin