#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define SIZE 32768

ofstream m_log("m_log.txt");

class Machine {
    private:
        uint16_t reg[8] = { 0 };
        uint16_t mem[SIZE] = { 0 };
        uint16_t PC = 0;
        vector<uint16_t> stack;

        uint16_t read_val(uint16_t PC);
        void halt();
        void set();
        void push();
        void pop();
        void eq();
        void gt();
        void jmp();
        void jt();
        void jf();
        void add();
        void mult();
        void mod();
        void m_and();
        void m_or();
        void m_not();
        void rmem();
        void wmem();
        void call();
        void ret();
        void out();
        void in();
        void noop();
        void (Machine::*opc[22])() = {
            halt, set, push, pop, eq, gt, jmp, jt, jf, add, mult, mod, m_and, m_or, m_not, rmem, wmem, call, ret, out, in, noop
        };
    public:
        void load_rom(ifstream &in);
        void run();
};

uint16_t Machine::read_val(uint16_t PC) {
    return (mem[PC] < SIZE) ? (mem[PC]) : (reg[mem[PC] - SIZE]);
}

//halt: 0
// stop execution and terminate the program
void Machine::halt() {
    m_log << "RECEIVED OPCODE HALT\nterminating program...\n";
    exit(0);
}

// set: 1 a b
// set register <a> to the value of <b>
void Machine::set() {
    m_log << "opcode: set()\n";
    reg[mem[++PC] - SIZE] = read_val(++PC);

    PC++;
}

// push: 2 a
// push <a> onto the stack
void Machine::push() {
    m_log << "opcode: push()\n";
    stack.push_back(read_val(++PC));

    PC++;
}


// pop: 3 a
// remove the top element from the stack and write it into <a>; empty stack = error
void Machine::pop() {
    m_log << "opcode: pop()\n";
    reg[mem[++PC] - SIZE] = stack.back();
    stack.pop_back();

    PC++;
}

// eq: 4 a b c
// set <a> to 1 if <b> is equal to <c>; set it to 0 otherwise
void Machine::eq() {
    m_log << "opcode: eq()\n";
    reg[mem[++PC] - SIZE] = (read_val(++PC) == read_val(++PC)) ? (1) : (0);

    PC++;
}

// gt: 5 a b c
// set <a> to 1 if <b> is greater than <c>; set it to 0 otherwise
void Machine::gt() {
    m_log << "opcode: gt()\n";
    reg[mem[++PC] - SIZE] = (read_val(++PC) > read_val(++PC)) ? (1) : (0);

    PC++;
}

// jmp: 6 a
// jump to <a>
void Machine::jmp() {
    m_log << "opcode: jmp()\n";
    PC = read_val(++PC);
}

// jt: 7 a b
// if <a> is nonzero, jump to <b>
void Machine::jt() {
    m_log << "opcode: jt()\n";
    PC = (read_val(++PC) != 0) ? (read_val(++PC)) : (PC++);
}

// jf: 8 a b
// if <a> is zero, jump to <b>
void Machine::jf() {
    m_log << "opcode: jf()\n";
    PC = (read_val(++PC) == 0) ? (read_val(++PC)) : (PC++);
}

// add: 9 a b c
// assign into <a> the sum of <b> and <c> (modulo 32768)
void Machine::add() {
    m_log << "opcode: add()\n";
    reg[mem[++PC] - SIZE] = (read_val(++PC) + read_val(++PC)) % SIZE;

    PC++;
}

// mult: 10 a b c
// store into <a> the product of <b> and <c> (modulo 32768)
void Machine::mult() {
    m_log << "opcode: mult()\n";
    reg[mem[++PC] - SIZE] = (read_val(++PC) * read_val(++PC)) % SIZE;

    PC++;
}

// mod: 11 a b c
// store into <a> the remainder of <b> divided by <c>
void Machine::mod() {
    m_log << "opcode: mod()\n";
    reg[mem[++PC] - SIZE] = read_val(++PC) % read_val(++PC);

    PC++;
}


// and: 12 a b c
// stores into <a> the bitwise and of <b> and <c>
void Machine::m_and() {
    m_log << "opcode: and()\n";
    reg[mem[++PC] - SIZE] = read_val(++PC) & read_val(++PC);

    PC++;
}

// or: 13 a b c
// stores into <a> the bitwise or of <b> and <c>
void Machine::m_or() {
    m_log << "opcode: or()\n";
    reg[mem[++PC] - SIZE] = read_val(++PC) | read_val(++PC);

    PC++;
}

// not: 14 a b
// stores 15-bit bitwise inverse of <b> in <a>
void Machine::m_not() {
    m_log << "opcode: not()\n";
    reg[mem[++PC] - SIZE] = ~(read_val(++PC));

    PC++;
}

// rmem: 15 a b
// read memory at address <b> and write it to <a>
void Machine::rmem() {
    m_log << "opcode: rmem()\n";
    reg[mem[++PC] - SIZE] = read_val(++PC);

    PC++;
}

// wmem: 16 a b
// write the value from <b> into memory at address <a>
void Machine::wmem() {
    m_log << "opcode: wmem()\n";
    mem[++PC] = read_val(++PC);

    PC++;
}

// call: 17 a
// write the address of the next instruction to the stack and jump to <a>
void Machine::call() {
    m_log << "opcode: call()\n";
    stack.push_back(PC+2);
    jmp();
}

// ret: 18
// remove the top element from the stack and jump to it; empty stack = halt
void Machine::ret() {
    m_log << "opcode: ret()\n";
    PC = stack.back();
    stack.pop_back();
}

// out: 19 a
// write the character represented by ascii code <a> to the terminal
void Machine::out() {
    m_log << "opcode: out()\n";
    cout << (char)read_val(++PC);

    PC++;
}

// NOTE: it can be assumed that once input starts, it will continue until a newline is encountered; 
// this means that you can safely read whole lines from the keyboard and trust that they will be fully read
// in: 20 a
// read a character from the terminal and write its ascii code to <a>
void Machine::in() {
    m_log << "opcode: in()\n";
    char c;
    cout << ">> ";
    cin >> c;

    reg[mem[++PC] - SIZE] = (uint16_t)(c);
}

// noop: 21
// no operation
void Machine::noop() {
    m_log << "opcode: noop()\n";
    PC++;
}

void Machine::run() {
    (this->*opc[mem[PC]])();;
}

// reads a file in binary mode and loads it into memory starting at address 0
void Machine::load_rom(ifstream &in) {
    int i = 0;
    m_log << "START - LOADING ROM\n";
    while(!in.eof()) {
        in.read((char *)&mem[i], sizeof(uint16_t));
        m_log << mem[i] << endl;
        i++;
    }
    m_log << "END - LOADING ROM\n";
}

string selector() {
    cout << "1. challenge.bin\n";
    cout << "2. other\n";
    cout << "IDX >> ";
    int k; 
    do cin >> k; while(k < 1 || k > 2);
    switch(k) {
        case 1: default:
            return "challenge.bin";
        case 2:
            string s;
            cout << "ROM NAME >> ";
            cin >> s;
            return s;
    }
}

int main() {
    ifstream rom(selector(), ios::in | ios::binary);

    Machine m;
    m.load_rom(rom);

    while(true) m.run();
}