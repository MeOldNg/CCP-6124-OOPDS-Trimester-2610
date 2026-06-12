#include <iostream>
#include <string>
#include <iomanip>
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

        // GEt register
        GeneralRegister& getRegister(int index) {
            if(index < 0 || index >= 8) {
                throw out_of_range("Invalid Register Index");
            }

            return registers[index];
        }

        // Reegister Name Lookup (Runner Needed)
        int getRegisterIndex(string reg) {
            if(reg == "R0") return 0;
            if(reg == "R1") return 1;
            if(reg == "R2") return 2;
            if(reg == "R3") return 3;
            if(reg == "R4") return 4;
            if(reg == "R5") return 5;
            if(reg == "R6") return 6;
            if(reg == "R7") return 7;

            return -1; // Change it to exception later
        }

        // Get PC
        ProgramCounter& getPC() {
            return pc;
        }
        
        // PC increment after execution
        void incrementPC() {
            pc.increment();
        }

        // Display format
        void printState() {
            cout << "#Begin#" << endl;
            cout << "#Registers#" << endl;

            for(int i = 0; i < 8; i++) {
                cout << setw(4) << setfill('0') << (int)registers[i].getValue() << "#";
            }
            cout << endl;
            
            // Flags

            cout << "#PC#" << setw(4) << setfill('0') << (int)pc.getPC() << "#" << endl;

            // Memory

            cout << "End" << endl;
        }
};

// Test
int main() {
    CPU cpu;
    
    // Set R0 = 10
    cpu.getRegister(0).setValue(10);
        
    // Execute an instruction
    cpu.incrementPC();
        
    // Display state(for assignment request. final output)
    cpu.dumpState();

    return 0;
}