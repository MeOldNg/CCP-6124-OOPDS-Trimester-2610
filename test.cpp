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

};

class CPU {
    private:

    public:

};

// Test
int main() {
    CPU cpu;


    return 0;
}