#include <string>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <iostream>

uint16_t to_le(std::uint16_t value) {
    return ((value >> 8) | (value << 8));
}

uint16_t OUT = to_le(19);

std::string str_to_synacor(std::string s) {
    std::stringstream ss;   
    ss << std::hex << std::setfill('0');
    for(size_t i = 0; i < s.length(); i++) { 
        ss << std::setw(4) << OUT;
        if(s[i] == '!') ss << std::setw(4) << to_le(32768 + (int)(s[++i]-'0'));
        else if(s[i] == '\\' && s[i+1] == 'n') { ss << std::setw(4) << to_le(10); i++; }
        else ss << std::setw(4) << to_le(s[i]);
    }

    return ss.str();
}

int main() {
    std::string s;
    std::cout << "ROM NAME >> ";
    std::getline(std::cin, s);
    s = "../" + s;
    std::ofstream out(s, std::ios::app | std::ios::binary);

    std::cout << "STRING TO CONVERT >> ";
    std::getline(std::cin, s);
    std::cout << s << " -> ";
    s = str_to_synacor(s);
    std::cout << s << std::endl;
    
    for(size_t i = 0; i < s.length(); i += 2) {
        uint16_t k = std::stoi(s.substr(i, 2), 0, 16);
        out.write((char *) &k, sizeof(char));
    }

    out.close();
}