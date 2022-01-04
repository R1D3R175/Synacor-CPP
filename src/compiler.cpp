#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>

#define REG 32768

inline uint16_t to_le(std::uint16_t value) {
    return ((value >> 8) | (value << 8));
}

class Compiler {
    private:
        std::ofstream *_out;
        

    public:
        Compiler(std::ofstream *out) 
        {
            _out = out;
        }
        
        int PC = -1;
        void halt(); // 0
        void set(const uint16_t a, const uint16_t b); // 1
        void push(const uint16_t a); // 2
        void pop(const uint16_t a); // 3
        void eq(const uint16_t a, const uint16_t b, const uint16_t c); // 4
        void gt(const uint16_t a, const uint16_t b, const uint16_t c); // 5
        void jmp(const uint16_t a); // 6
        void jt(const uint16_t a, const uint16_t b); // 7
        void jf(const uint16_t a, const uint16_t b); // 8
        void add(const uint16_t a, const uint16_t b, const uint16_t c); // 9
        void mult(const uint16_t a, const uint16_t b, const uint16_t c); // 10
        void mod(const uint16_t a, const uint16_t b, const uint16_t c); // 11
        void m_and(const uint16_t a, const uint16_t b, const uint16_t c); // 12
        void m_or(const uint16_t a, const uint16_t b, const uint16_t c); // 13
        void m_not(const uint16_t a, const uint16_t b); // 14
        void rmem(const uint16_t a, const uint16_t b); // 15
        void wmem(const uint16_t a, const uint16_t b); // 16
        void call(const uint16_t a); // 17
        void ret(); // 18
        void out(const std::string s); // 19
        void in(const uint16_t a); // 20
        void noop(); // 21
};

void Compiler::halt() { // 0
    PC += 1;
    _out->write((char *)"\x00\x00", 2);
}

void Compiler::set(const uint16_t a, const uint16_t b) // 1
{
    PC += 3;
    _out->write((char *)"\x01\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
}

void Compiler::push(const uint16_t a) { // 2
    PC += 2;
    _out->write((char *)"\x02\x00", 2);
    _out->write((char *)(&a), 2);
}

void Compiler::pop(const uint16_t a) { // 3
    PC += 2;
    _out->write((char *)"\x03\x00", 2);
    _out->write((char *)(&a), 2);
}

void Compiler::eq(const uint16_t a, const uint16_t b, const uint16_t c) { // 4
    PC += 4;
    _out->write((char *)"\x04\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
    _out->write((char *)(&c), 2);
}

void Compiler::gt(const uint16_t a, const uint16_t b, const uint16_t c) {
    PC += 4;
    _out->write((char *)"\x05\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
    _out->write((char *)(&c), 2);
}

void Compiler::jmp(const uint16_t a) { // 6
    PC += 2;
    _out->write((char *)"\x06\x00", 2);
    _out->write((char *)(&a), 2);
}

void Compiler::jt(const uint16_t a, const uint16_t b) { // 7
    PC += 3;
    _out->write((char *)"\x07\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
}

void Compiler::jf(const uint16_t a, const uint16_t b) { // 8
    PC += 3;
    _out->write((char *)"\x08\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
}

void Compiler::add(const uint16_t a, const uint16_t b, const uint16_t c) { // 9
    PC += 4;
    _out->write((char *)"\x09\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
    _out->write((char *)(&c), 2);
}

void Compiler::mult(const uint16_t a, const uint16_t b, const uint16_t c) { // 10
    PC += 4;
    _out->write((char *)"\x0A\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
    _out->write((char *)(&c), 2);
}

void Compiler::mod(const uint16_t a, const uint16_t b, const uint16_t c) { // 11
    PC += 4;
    _out->write((char *)"\x0B\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
    _out->write((char *)(&c), 2);
}

void Compiler::m_and(const uint16_t a, const uint16_t b, const uint16_t c) { // 12
    PC += 4;
    _out->write((char *)"\x0C\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
    _out->write((char *)(&c), 2);
}

void Compiler::m_or(const uint16_t a, const uint16_t b, const uint16_t c) { // 13
    PC += 4;
    _out->write((char *)"\x0D\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
    _out->write((char *)(&c), 2);
}

void Compiler::m_not(const uint16_t a, const uint16_t b) { // 14
    PC += 3;
    _out->write((char *)"\x0E\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
}

void Compiler::rmem(const uint16_t a, const uint16_t b) { // 15
    PC += 3;
    _out->write((char *)"\x0F\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
}

void Compiler::wmem(const uint16_t a, const uint16_t b) { // 16
    PC += 3;
    _out->write((char *)"\x10\x00", 2);
    _out->write((char *)(&a), 2);
    _out->write((char *)(&b), 2);
}

void Compiler::call(const uint16_t a) { // 17
    PC += 2;
    _out->write((char *)"\x11\x00", 2);
    _out->write((char *)(&a), 2);
}

void Compiler::ret() { // 18
    PC += 1;
    _out->write((char *)"\x12\x00", 2);
}

void Compiler::out(std::string s) { // 19
    std::stringstream ss;   
    ss << std::hex << std::setfill('0');

    for(size_t i = 0; i < s.length(); i++) { 
        ss << std::setw(4) << to_le(0x13);
        PC++;

        if(s[i] == '!') ss << std::setw(4) << to_le(32768 + (int)(s[++i]-'0'));
        else if(s[i] == '\\' && s[i+1] == 'n') { ss << std::setw(4) << to_le(10); i++; }
        else ss << std::setw(4) << to_le(s[i]);
        PC++;
    }

    s = ss.str();
    
    for(size_t i = 0; i < s.length(); i += 2) {
        uint16_t k = std::stoi(s.substr(i, 2), 0, 16);
        _out->write((char *) &k, sizeof(char));
    }

} // 19

void Compiler::in(const uint16_t a) { // 20
    PC += 2;
    _out->write((char *)"\x14\x00", 2);
    _out->write((char *)(&a), 2);
}

void Compiler::noop() { // 21
    PC += 1;
    _out->write((char *)"\x15\x00", 2);
}

int main() {
    std::ofstream out("test.bin", std::ios::out | std::ios::binary);

    Compiler a(&out);
    a.out("TEST ROM\\n\\n");     

    a.out("should set first reg to 48 (ascii value for 0) and print it.\\n");   
    a.set(REG, 48);     
    a.out("reg[0] = !0\\n\\n");     

    a.out("should push 48 to the stack (ascii value for 0), write it to reg[1] and pop it.\\n");     
    a.push(48);      
    a.pop(REG+1);      
    a.out("reg[1] = !1\\n\\n");      

    a.out("the program should not halt since reg[2] is 1\\n");      
    a.eq(REG+2, REG, REG+1);   
    a.jt(REG+2, a.PC+2);  
    a.halt();    
    int t = a.PC;  
    a.out("success.\\n\\n");      

    a.out("the program should not halt since reg[3] is 1\\n");      
    a.gt(REG+3, REG+1, REG+2);      
    a.jf(REG+3, t);      
    a.out("success.\\n\\n");      

    a.out("the program should skip the following halt instruction.\\n");      
    a.jmp(a.PC+2);      
    a.halt();      
    a.out("success.\\n\\n");      

    a.out("the program should add reg[0](48) and reg[1](48) together, then print the result (96, ` in ASCII)\\n");      
    a.add(REG+4, REG, REG+1);      
    a.out("reg[4] = !4\\n\\n");      

    a.out("the program should multiply reg[1] with 3, then print the result (144, É in ASCII)\\n");        
    a.mult(REG+5, REG+1, 3);      
    a.out("reg[5] = !5\\n\\n");      

    a.out("the program should do the bitwise AND between reg[5](144) and reg[1](48),\\nthen multiply the result by 3 and then print the result(48, 0 in ASCII)\\n"); // 1408
    a.m_and(REG+6, REG+5, REG+1);      
    a.mult(REG+6, REG+6, 3);      
    a.out("reg[6] = !6\\n\\n");      


    out.close();
}