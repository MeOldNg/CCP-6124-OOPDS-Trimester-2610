#include <iostream>
#include <string>
using namespace std;

// Register
class Register {
    private:
        signed char value;  // -128 to 127

    public:
        Register() {
            value = 0;
        }
        
        signed char getValue() const {
            return value;
        }
        
        void setValue(int v) {
            value = static_cast<signed char>(v);
            // Flag update logic add here later
        }
};

// General Register
class GeneralRegister : public Register {
    private:
        string name; // R0, R1, ...

    public:
        GeneralRegister(string n = "") {
            name = n;
        }
        
        string getName() const {
            return name;
        }
        
        void setName(string n) {
            name = n;
        }
};

// Program Counter
class ProgramCounter {
    private:
        unsigned char pc;  // Range 0-255

    public:
        ProgramCounter() {
            pc = 0;
        }
        
        unsigned char getPC() const {
            return pc;
        }
        
        void increment() {
            pc++;
        }
        
        void reset() {
            pc = 0;
        }
};

// CPU
class CPU {
    private:
        GeneralRegister registers[8]; // R0-R7
        ProgramCounter pc;

    public:
        CPU() {
            // Initialize 8 register
            registers[0].setName("R0");
            registers[1].setName("R1");
            registers[2].setName("R2");
            registers[3].setName("R3");
            registers[4].setName("R4");
            registers[5].setName("R5");
            registers[6].setName("R6");
            registers[7].setName("R7");
            
        }
};

// Test
int main() {
    CPU cpu;


    return 0;
}