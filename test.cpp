#include <iostream>
#include <string>
#include <iomanip>
#include <stdexcept>
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

// SI Register
class StackIndex {
    private:
        unsigned char si; // Range 0-255

    public:
        StackIndex() {
            si = 0;
        }

        unsigned char getSI() const {
            return si;
        }

        void increment() {
            si++;
        }

        void decrement() {
            if(si == 0) {
                throw underflow_error("Stack Underflow");
            }

            si--;
        }

        void reset() {
            si = 0;
        }
};

// Flags
class Flags {
    private:
        bool of; // Overflow Flag
        bool uf; // Underflow Flag
        bool cf; // Carry Flag
        bool zf; // Zero Flag

    public:
        Flags() : of(false), uf(false), cf(false), zf(false) {}

        // Setters
        void setOF(bool val) { of = val; }
        void setUF(bool val) { uf = val; }
        void setCF(bool val) { cf = val; }
        void setZF(bool val) { zf = val; }

        // Getters
        bool getOF() const { return of; }
        bool getUF() const { return uf; }
        bool getCF() const { return cf; }
        bool getZF() const { return zf; }

        // Reset all of the flags
        void reset() {
            of = uf = cf = zf = false;
        }
};

// System Stack
class SystemStack {
    private:
        signed char data[8]; // 8 bytes stack

    public:
        SystemStack() {
            for(int i = 0; i < 8; i++) {
                data[i] = 0; // Initialize stack to 0
            }
        }

        // Write value to stack at index (0-7)
        void write(int index, signed char value) {
            if(index < 0 || index >= 8) {
                throw overflow_error("Stack Memory Overflow");
            }
            data[index] = value;
        }

        // Read value from stack at index (0-7)
        signed char read(int index) const {
            if(index < 0 || index >= 8) {
                throw out_of_range("Invalid Stack Access");
            }

            return data[index];
        }
};

// Main Memory
class MainMemory {
    private:
        signed char data[64]; // 64 bytes array

    public:
        MainMemory() {
            for(int i = 0; i < 64; i++) {
                data[i] = 0; // Initialize to 0
            }
        }

        // Write operation to main memory
        void write(int address, signed char value) {
            if(address < 0 || address >= 64) {
                throw out_of_range("Memory Write Out of Range (0-63 only)");
            }
            data[address] = value;
        }

        // Read operation from main memory
        signed char read(int address) const {
            if(address < 0 || address >= 64) {
                throw out_of_range("Memory Read Out of Range (0-63 only)");
            }
            return data[address];
        }
};

// CPU
class CPU {
    private:
        GeneralRegister registers[8]; // R0-R7
        ProgramCounter pc;
        StackIndex si;
        SystemStack stack;
        Flags flags;
        MainMemory memory;

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

            return -1; // Change it to exception later?
        }

        // Get PC
        ProgramCounter& getPC() {
            return pc;
        }
        
        // Get SI
        StackIndex& getSi() {
            return si;
        }

        // Get Flags
        Flags& getFlags() {
            return flags;
        }

        // Get Memory
        MainMemory& getMemory() {
            return memory;
        }

        // Stack operation: push
        void pushStack(signed char value) {
            if(si.getSI() >= 8) {
                throw overflow_error("Stack Overflow");
            }

            stack.write(si.getSI(), value); // Write value to stack
            si.increment(); // Move SI to nest position
        }

        // Stack operation: pop
        signed char popStack() {
            si.decrement(); // Move SI to previous position(auto underflow check)
            int newIndex = si.getSI();
            return stack.read(newIndex); // Take out value from stack
        }

        // PC increment after execution
        void incrementPC() {
            pc.increment();
        }

        // Display format
        void printState() {
            cout << "#Begin#" << endl;
            cout << "#Registers#";

            for(int i = 0; i < 8; i++) {
                cout << setw(4) << setfill('0') << (int)registers[i].getValue() << "#";
            }
            cout << endl;
            
            // Flags
            cout << "#Flags#OF#" << flags.getOF() 
                 << "#UF#" << flags.getUF() 
                 << "#CF#" << flags.getCF() 
                 << "#ZF#" << flags.getZF() << "#" << endl;

            // PC
            cout << "#PC#" << setw(4) << setfill('0') << (int)pc.getPC() << "#" << endl;

            // Memory
            cout << "#Memory#" << endl;
            for(int i=0; i < 64; i++) {
                if(i % 8 == 0) {
                    cout << "#"; // Add # at the new line first
                }
                cout << setw(4) << setfill('0') << (int)memory.read(i) << "#";
                if(i % 8 == 7) {
                    cout << endl; // Change to the next line when already have 8 memory
                }
            }

            cout << "#End#" << endl;
        }
};

// Test
int main() {
    CPU cpu;
    
    try {
        // Set R0 = 10
        cpu.getRegister(0).setValue(10);
        
        // Execute an instruction
        cpu.incrementPC();
        
        // Display state(for assignment request. final output)
        cpu.printState();

        // Test if out of range exception work
        cpu.getRegister(100);
    
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    try {
        for(int i = 0; i <= 9; i++) {
            cpu.pushStack(i * 10); // Shoold throw error when i = 8
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}