#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
using namespace std;

template <typename T>
class MyVector {
    private:
        T* data;
        int size;
        int capacity;

    public:
        MyVector() {
            data = NULL;
            size = 0;
            capacity = 0;
        }

        ~MyVector() {
            delete[] data;
        }

        void push_back(T val) {
            if (size == capacity) {     // if no more space, make new bigger array
                int newCap;
                if (capacity == 0) {
                    newCap = 4;
                } else {
                    newCap = capacity * 2;
                }
                T* newData = new T[newCap];
                for (int i = 0; i < size; i++) {
                    newData[i] = data[i];
                }
                delete[] data;
                data = newData;
                capacity = newCap;
            }
            data[size] = val;
            size++;
        }

        T& operator[](int i) {
            return data[i];
        }

        int getSize() {
            return size;
        }

        bool isEmpty() {
            return size == 0;
        }

        void clear() {
            size = 0;
        }
};

class MyStack {
    private:
        signed char data[8];
        int top;

    public:
        MyStack() {
            top = -1;
            for (int i = 0; i < 8; i++) {
                data[i] = 0;
            }
        }

        bool push(signed char val) {
            if (top >= 7) {
                return false; // stack full
            }
            top++;
            data[top] = val;
            return true;
        }

        bool pop(signed char &val) {
            if (top < 0) {
                return false; // stack empty
            }
            val = data[top];
            top--;
            return true;
        }

        bool isEmpty() {
            return top < 0;
        }

        int getSize() {
            return top + 1;
        }
};

class MyQueue {
    private:
        string data[500]; // max 500 lines should be enough
        int head;        // head of the queue
        int tail;       // tail of the queue
        int count;      // count how many times the queue is being used

    public:
        MyQueue() {    // initialize the value of the queue
            head  = 0;
            tail  = 0;
            count = 0;
        }

        void enqueue(string val) {
            data[tail] = val;
            tail++;
            count++;
        }

        string dequeue() {
            string val = data[head];
            head++;
            count--;
            return val;
        }

        bool isEmpty() {
            return count == 0;
        }
};

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

        void updateAll(int result) {
            if (result > 127) {
                of = true;
            } else {
                of = false;
            }
            if (result < -128) {
                uf = true;
            } else {
                uf = false;
            }
            if (result > 127 || result < -128) {
                cf = true;
            } else {
                cf = false;
            }
            if (result == 0) {
                zf = true;
            } else {
                zf = false;
            }
        }

        void resetOne(string flagName) {
            if (flagName == "OF") of = false;
            if (flagName == "UF") uf = false;
            if (flagName == "CF") cf = false;
            if (flagName == "ZF") zf = false;
        }


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

        bool hasBrackets(string s) {        // check if the string has brackets 
            int len = s.size();

            if (len < 3) {
                return false;
            }

            char firstChar = s[0];
            char lastChar = s[len - 1];

            if (firstChar == '[' && lastChar == ']') {
                return true;
            }

            return false;
        }

        string removeBrackets(string s) {   // remove the brackets when there is brackets presented
            int len = s.size();
            string inside = s.substr(1, len - 2);
            return inside;
        }

        string toBinary(signed char val) {  // convert char to binary string
            unsigned char uval = (unsigned char)val;
            string bits = "";

            int bitPosition = 7;
            while (bitPosition >= 0) {
                unsigned char mask = 1;
                for (int s = 0; s < bitPosition; s++) {
                    mask = mask * 2;
                }

                unsigned char checkBit = uval & mask;
                if (checkBit != 0) {
                    bits = bits + "1";
                } else {
                    bits = bits + "0";
                }

                bitPosition = bitPosition - 1;
            }
            return bits;
        }

        signed char fromBinary(string bits) {
            unsigned char uval = 0;

            for (int i = 0; i < 8; i++) {
                uval = uval * 2;
                char currentChar = bits[i];

                if (currentChar == '1') {
                    uval = uval + 1;
                } else {
                    uval = uval + 0;
                }
            }
            signed char result = (signed char)uval;
            return result;
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
        void printState(ostream &out) {
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

        void dump(string outputFile) {
            printState(cout);
            ofstream ofs(outputFile.c_str());

            if (ofs.is_open()) {
                printState(ofs);
                ofs.close();
            }
        }
};

class Instructions {
    protected:
        string opp;
        string arg1;
        string arg2;
    
    public:
        Instructions() {}

        Instructions( string& op, string& a1, string& a2) {
            opp = op;
            arg1 = a1;
            arg2 = a2;
        }

        virtual ~Instructions() {}

        // every instruction must implement this
        virtual void execute(CPU &cpu) = 0;

        string getOpcode() {
            return opp;
        }
};

class movInstructions : public Instructions {
    public:
        movInstructions(string a1, string a2) {
            opp = "MOV";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "MOV Error: Bad Destination " << arg1 << endl;
                return;     }
            if (cpu.hasBrackets(arg2)) {
                string inside = cpu.removeBrackets(arg2);
                int originalIndex = cpu.getRegisterIndex(inside);
                if (originalIndex < 0) {
                    cout << "MOV Error : Bad Registers inside Brackets" << endl;
                    return;     }
                int address = (unsigned char)cpu.getRegister(originalIndex).getValue();
                signed char memoryValue = cpu.getMemory().read(address);
                cpu.getRegister(destinationIndex).setValue(memoryValue);
                cpu.getFlags().updateAll(memoryValue);
            } else if (cpu.getRegisterIndex(arg2) >= 0) {
                int originalIndex = cpu.getRegisterIndex(arg2);
                int memoryValue = cpu.getRegister(destinationIndex).getValue();
                cpu.getRegister(destinationIndex).setValue(memoryValue);
                cpu.getFlags().updateAll(memoryValue);
            } else {
                int memoryValue = atoi(arg2.c_str());
                cpu.getRegister(destinationIndex).setValue(memoryValue);
                cpu.getFlags().updateAll(memoryValue);      }
        }
};

class arithmeticsInstructions : public Instructions {
    public:
        arithmeticsInstructions() {}

        arithmeticsInstructions(string op, string a1, string a2) {
            opp = op;
            arg1 = a1;
            arg2 = a2;
        }
};

class addInstructions : public arithmeticsInstructions {
    public:
        addInstructions(string a1, string a2) {
            opp = "ADD";
            arg1 = a1;
            arg2 = a2;
        }

    void execute(CPU &cpu) {
        int destinationIndex = cpu.getRegisterIndex(arg1);
        if (destinationIndex < 0) {
            cout << "ADD Error: Bad Destination" << endl;
            return;
        }
        int originalValue;
        int originalIndex = cpu.getRegisterIndex(arg2);
        if (originalIndex >= 0) {
            originalValue = cpu.getRegister(originalIndex).getValue();
        } else {
            originalValue = atoi(arg2.c_str());
        }
        int result = cpu.getRegister(originalIndex).getValue() + originalValue;
        cpu.getFlags().updateAll(result);
        cpu.getRegister(destinationIndex).setValue(result);
    }
};

class subInstructions : public arithmeticsInstructions {
    public:
        subInstructions(string a1, string a2) {
            opp = "SUB";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "SUB Error: Bad Destination" << endl;
                return;
            }

            int originalValue;
            int originalIndex = cpu.getRegisterIndex(arg2);
            if (originalIndex >= 0) {
                originalValue = (int)cpu.getRegister(originalIndex).getValue();
            } else {
                originalValue = atoi(arg2.c_str());
            }

            int result = (int)cpu.getRegister(destinationIndex).getValue() - originalValue;
            cpu.getFlags().updateAll(result);
            cpu.getRegister(destinationIndex).setValue(result);
        }
};

// MUL
class mulInstructions : public arithmeticsInstructions {
    public:
        mulInstructions(string a1, string a2) {
            opp = "MUL";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "MUL Error: Bad Destination" << endl;
                return;
            }

            int originalValue;
            int originalIndex = cpu.getRegisterIndex(arg2);
            if (originalIndex >= 0) {
                originalValue = (int)cpu.getRegister(originalIndex).getValue();
            } else {
                originalValue = atoi(arg2.c_str());
            }

            int result = (int)cpu.getRegister(destinationIndex).getValue() * originalValue;
            cpu.getFlags().updateAll(result);
            cpu.getRegister(destinationIndex).setValue(result);
        }
};

// DIV
class divInstructions : public arithmeticsInstructions {
    public:
        divInstructions(string a1, string a2) {
            opp = "DIV";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "DIV Error: Bad Destination" << endl;
                return;
            }

            int originalValue;
            int originalIndex = cpu.getRegisterIndex(arg2);
            if (originalIndex >= 0) {
                originalValue = (int)cpu.getRegister(originalIndex).getValue();
            } else {
                originalValue = atoi(arg2.c_str());
            }

            if (originalValue == 0) {
                cout << "DIV Error: Cannot be divided by zero" << endl;
                return;
            }

            int result = (int)cpu.getRegister(destinationIndex).getValue() / originalValue;
            cpu.getFlags().updateAll(result);
            cpu.getRegister(destinationIndex).setValue(result);
        }
};

class incInstructions : public arithmeticsInstructions {
    public:
        incInstructions(string a1) {
            opp = "INC";
            arg1 = a1;
            arg2 = "";
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "INC Error: Bad Destination" << endl;
                return;
            }

            int result = (int)cpu.getRegister(destinationIndex).getValue() + 1;
            cpu.getFlags().updateAll(result);
            cpu.getRegister(destinationIndex).setValue(result);
        }
};

// DEC - subtract 1 from a register
class decInstructions : public arithmeticsInstructions {
    public:
        decInstructions(string a1) {
            opp = "INC";
            arg1 = a1;
            arg2 = "";

        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "DEC Error: Bad Destination" << endl;
                return;
            }

            int result = (int)cpu.getRegister(destinationIndex).getValue() - 1;
            cpu.getFlags().updateAll(result);
            cpu.getRegister(destinationIndex).setValue(result);
        }
};

class shiftInstructions : public Instructions {
    public:
        shiftInstructions() {}

        shiftInstructions(string op, string a1, string a2) {
            opp = op;
            arg1 = a1;
            arg2 = a2;
        }
};

// SHL - shift bits left, fill empty spots with 0
class shlInstructions : public shiftInstructions {
    public:
        shlInstructions(string a1, string a2) {
            opp = "SHL";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "SHL Error: Bad Destination" << endl;
                return;
            }

            int count = atoi(arg2.c_str());
            string bits = cpu.toBinary(cpu.getRegister(destinationIndex).getValue());
            string shifted = "";

            if (count >= 8) {
                shifted = "00000000";
            } else {
                // take bits starting from position count, then add zeros at the end
                for (int i = count; i < 8; i++) { shifted += bits[i]; }
                for (int i = 0; i < count; i++) { shifted += "0"; }
            }
            signed char result = cpu.fromBinary(shifted);
            cpu.getRegister(destinationIndex).setValue(result);
            cpu.getFlags().updateAll((int)result);
        }
};

// SHR - shift bits right, fill empty spots with 0
class shrInstructions : public shiftInstructions {
    public:
        shrInstructions(string a1, string a2) {
            opp = "SHR";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "SHR Error: Bad Destination" << endl;
                return;
            }

            int count = atoi(arg2.c_str());
            string bits = cpu.toBinary(cpu.getRegister(destinationIndex).getValue());
            string shifted = "";

            if (count >= 8) {
                shifted = "00000000";
            } else {
                // add zeros at the front, then add the remaining bits
                for (int i = 0; i < count; i++) {
                    shifted += "0";
                }
                for (int i = 0; i < 8 - count; i++) {
                    shifted += bits[i];
                }
            }

            signed char result = cpu.fromBinary(shifted);
            cpu.getRegister(destinationIndex).setValue(result);
            cpu.getFlags().updateAll((int)result);
        }
};

class rotateInstructions : public Instructions {
    public:
        rotateInstructions() {}

        rotateInstructions(string op, string a1, string a2) {
            opp = op;
            arg1 = a1;
            arg2 = a2;
        }
};

// ROL - rotate bits to the left
class rolInstructions : public rotateInstructions {
    public:
        rolInstructions(string a1, string a2) {
            opp = "ROL";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "ROL Error: Bad Destination" << endl;
                return;
            }

            int count = atoi(arg2.c_str());
            count = count % 8; // rotating 8 times is same as not rotating

            string bits = cpu.toBinary(cpu.getRegister(destinationIndex).getValue());
            string rotated = "";

            // take bits from position count to end, then wrap the front bits to the back
            for (int i = count; i < 8; i++) { rotated += bits[i]; }
            for (int i = 0; i < count; i++) { rotated += bits[i]; }

            signed char result = cpu.fromBinary(rotated);
            cpu.getRegister(destinationIndex).setValue(result);
            cpu.getFlags().updateAll((int)result);
        }
};

// ROR - rotate bits to the right
class rorInstructions : public rotateInstructions {
    public:
        rorInstructions(string a1, string a2) {
            opp = "ROR";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "ROR Error: Bad Destination" << endl;
                return;
            }

            int count = atoi(arg2.c_str());
            count = count % 8;

            string bits = cpu.toBinary(cpu.getRegister(destinationIndex).getValue());
            string rotated = "";

            // take the last 'count' bits and put them at the front first
            for (int i = 8 - count; i < 8; i++) {
                rotated += bits[i];
            }
            for (int i = 0; i < 8 - count; i++) {
                rotated += bits[i];
            }

            signed char result = cpu.fromBinary(rotated);
            cpu.getRegister(destinationIndex).setValue(result);
            cpu.getFlags().updateAll((int)result);
        }
};

class memoryInstructions : public Instructions {
    public:
        memoryInstructions() {}

        memoryInstructions(string op, string a1, string a2) {
            opp = op;
            arg1 = a1;
            arg2 = a2;
        }
};

class loadInstructions : public memoryInstructions {
    public:
        loadInstructions(string a1, string a2) {
            opp = "LOAD";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "LOAD Error: Bad Destination" << endl;
                return;
            }
            if (!cpu.hasBrackets(arg2)) {
                cout << "LOAD error: source must be in brackets like [20] or [R2]" << endl;
                return;
            }
            string inside = cpu.removeBrackets(arg2);
            int address;
            int originalIndex = cpu.getRegisterIndex(inside);
            if (originalIndex >= 0) {
                // register holds the address
                address = (unsigned char)cpu.getRegister(originalIndex).getValue();
            } else {
                // it's a direct number
                address = atoi(inside.c_str());
            }
            signed char val = cpu.getMemory().read(address);
            cpu.getRegister(destinationIndex).setValue(val);
            cpu.getFlags().updateAll((int)val);
        }
};

class storeInstructions : public memoryInstructions {
    public:
        storeInstructions(string a1, string a2) {
            opp = "STORE";
            arg1 = a1;
            arg2 = a2;
        }

        void execute(CPU &cpu) {
            if (cpu.hasBrackets(arg1)) {
                string inside = cpu.removeBrackets(arg1);
                int addressRegisterIndex = cpu.getRegisterIndex(inside);
                int originalIndex = cpu.getRegisterIndex(arg2);
                if (addressRegisterIndex < 0 || originalIndex < 0) {
                    cout << "STORE error: bad register" << endl;
                    return; }
                int address = (unsigned char)cpu.getRegister(addressRegisterIndex).getValue();
                cpu.getMemory().write(address, cpu.getRegister(originalIndex).getValue());
                return; }
            if (cpu.hasBrackets(arg2)) {
                int originalIndex = cpu.getRegisterIndex(arg1);
                string inside = cpu.removeBrackets(arg2);
                int addressRegisterIndex = cpu.getRegisterIndex(inside);
                if (originalIndex < 0 || addressRegisterIndex < 0) {
                    cout << "STORE Error: Bad Register" << endl;
                    return; }
                int address = (unsigned char)cpu.getRegister(addressRegisterIndex).getValue();
                cpu.getMemory().write(address, cpu.getRegister(originalIndex).getValue());
                return; }
            bool arg1IsReg = (cpu.getRegisterIndex(arg1) >= 0);
            bool arg2IsReg = (cpu.getRegisterIndex(arg2) >= 0);
            if (!arg1IsReg && arg2IsReg) {
                int address = atoi(arg1.c_str());
                int originalIndex = cpu.getRegisterIndex(arg2);
                cpu.getMemory().write(address, cpu.getRegister(originalIndex).getValue());
                return; }
            if (arg1IsReg && !arg2IsReg) {
                int originalIndex = cpu.getRegisterIndex(arg1);
                int address = atoi(arg2.c_str());
                cpu.getMemory().write(address, cpu.getRegister(originalIndex).getValue());
                return; }
            cout << "STORE Error: format not recognised" << endl; }
};

class IOInstructions : public Instructions {
    public:
        IOInstructions() {}

        IOInstructions(string op, string a1) {
            opp = op;
            arg1 = a1;
            arg2 = "";
        }
};

class inputInstructions : public IOInstructions {
    public:
        inputInstructions(string a1) {
            opp = "INPUT";
            arg1 = a1;
        }

        void execute(CPU &cpu) {
        int destinationIndex = cpu.getRegisterIndex(arg1);
        if (destinationIndex < 0) { cout << "INPUT error: bad register" << endl; return; }

        cout << "?" << endl;
        int val;
        cin >> val;

        // update flags before clamping
        if (val > 127) {
            cpu.getFlags().setOF(1);
        } else {
            cpu.getFlags().setOF(0);
        }

        if (val < -128) {
            cpu.getFlags().setUF(1);
        } else {
            cpu.getFlags().setUF(0);
        }

        if (val == 0) {
            cpu.getFlags().setZF(1);
        } else {
            cpu.getFlags().setZF(0);
        }

        if (val > 127 || val < -128) {
            cpu.getFlags().setCF(1);
        } else {
            cpu.getFlags().setCF(0);
        }

        cpu.getRegister(destinationIndex).setValue((signed char)val);
    }
};

class displayInstructions : public IOInstructions {
    public:
        displayInstructions(string a1) {
            opp = "DISPLAY";
            arg1 = a1;
        }

        void execute(CPU &cpu) {
            int originalIndex = cpu.getRegisterIndex(arg1);
            if (originalIndex < 0) {
                cout << "DISPLAY error: bad register" << endl;
                return;
            }
            cout << (int)cpu.getRegister(originalIndex).getValue() << endl;
        }
};

class stackInstructions : public Instructions {
    public:
        stackInstructions() {}

        stackInstructions(string op, string a1) {
            opp = op;
            arg1 = a1;
            arg2 = "";
        }
};

// PUSH - push register value onto the stack
class pushInstructions : public stackInstructions {
    public:
        pushInstructions(string a1) {
            opp = "PUSH";
            arg1 = a1;
        }

        void execute(CPU &cpu) {
            int originalIndex = cpu.getRegisterIndex(arg1);
            if (originalIndex < 0) {
                cout << "PUSH Error: Bad Register" << endl;
                return;
            }
            try {
                cpu.pushStack(cpu.getRegister(originalIndex).getValue());
            } catch (exception &e) {
                cout << "PUSH Error: " << e.what() << endl;
            }
        }
};

// POP - take top value off the stack and put into register
class popInstructions : public stackInstructions {
    public:
        popInstructions(string a1) {
            opp = "POP";
            arg1 = a1;
        }

        void execute(CPU &cpu) {
            int destinationIndex = cpu.getRegisterIndex(arg1);
            if (destinationIndex < 0) {
                cout << "POP Error: Bad Register" << endl;
                return;
            }
            try {
                signed char val = cpu.popStack();
                cpu.getRegister(destinationIndex).setValue(val);
                cpu.getFlags().updateAll((int)val);
            } catch (exception &e) {
                cout << "FATAL ERROR: " << e.what() << " - program crashed" << endl;
                exit(1);
            }
        }
};

class flagInstructions : public Instructions {
    public:
        flagInstructions(string a1) {
            opp = "RESET";
            arg1 = a1;
            arg2 = "";
        }

        void execute(CPU &cpu) {
            cpu.getFlags().resetOne(arg1);
        }
};

class Runner {
    private:
        CPU cpu;
        MyVector<Instructions*> program;

        // remove spaces from front and back of string
        string trim(string s) {
            int start = 0;
            int end = (int)s.size() - 1;
            while (start <= end && (s[start] == ' ' || s[start] == '\t')) {
                start++;
            }
            while (end >= start && (s[end] == ' ' || s[end] == '\t' || s[end] == '\r' || s[end] == '\n')) {
                end--;
            }
            if (start > end) return "";
            return s.substr(start, end - start + 1);
        }

        // convert string to uppercase letters
        string toUpper(string s) {
            for (int i = 0; i < (int)s.size(); i++) {
                s[i] = toupper(s[i]);
            }
            return s;
        }

        // split "R1, 5" into left = "R1" and right = "5"
        void splitArgs(string s, string &left, string &right) {
            int commaPos = -1;
            for (int i = 0; i < (int)s.size(); i++) {
                if (s[i] == ',') {
                    commaPos = i;
                    break;
                }
            }

            if (commaPos == -1) {
                left  = trim(s);
                right = "";
            } else {
                left  = trim(s.substr(0, commaPos));
                right = trim(s.substr(commaPos + 1));
            }
        }

        // look at one line and return the right instruction object
        Instructions* parseLine(string line, int lineNum) {
            // remove anything after a semicolon (comments)
            for (int i = 0; i < (int)line.size(); i++) {
                if (line[i] == ';') {
                    line = line.substr(0, i);
                    break;
                }
            }

            line = trim(line);
            if (line.empty()) return NULL; // skip blank lines

            // separate the opcode from the arguments
            string opp = "";
            string rest   = "";
            int spacePos  = -1;

            for (int i = 0; i < (int)line.size(); i++) {
                if (line[i] == ' ' || line[i] == '\t') {
                    spacePos = i;
                    break;
                }
            }

            if (spacePos == -1) {
                opp = toUpper(line);
            } else {
                opp = toUpper(trim(line.substr(0, spacePos)));
                rest   = trim(line.substr(spacePos + 1));
            }

            string arg1 = "";
            string arg2 = "";
            splitArgs(rest, arg1, arg2);

            // create the correct instruction object
            if (opp == "MOV")     return new movInstructions(arg1, arg2);
            if (opp == "ADD")     return new addInstructions(arg1, arg2);
            if (opp == "SUB")     return new subInstructions(arg1, arg2);
            if (opp == "MUL")     return new mulInstructions(arg1, arg2);
            if (opp == "DIV")     return new divInstructions(arg1, arg2);
            if (opp == "INC")     return new incInstructions(arg1);
            if (opp == "DEC")     return new decInstructions(arg1);
            if (opp == "ROL")     return new rolInstructions(arg1, arg2);
            if (opp == "ROR")     return new rorInstructions(arg1, arg2);
            if (opp == "SHL")     return new shlInstructions(arg1, arg2);
            if (opp == "SHR")     return new shrInstructions(arg1, arg2);
            if (opp == "LOAD")    return new loadInstructions(arg1, arg2);
            if (opp == "STORE")   return new storeInstructions(arg1, arg2);
            if (opp == "INPUT")   return new inputInstructions(arg1);
            if (opp == "DISPLAY") return new displayInstructions(arg1);
            if (opp == "PUSH")    return new pushInstructions(arg1);
            if (opp == "POP")     return new popInstructions(arg1);
            if (opp == "RESET")   return new flagInstructions(arg1);

            cout << "Error on line " << lineNum << ": unknown instruction '" << opp<< "'" << endl;
            return NULL;
        }

        // delete all instruction objects from memory
        void clearProgram() {
            for (int i = 0; i < program.getSize(); i++) {
                delete program[i];
            }
            program.clear();
        }

    public:
        Runner() {}

        ~Runner() {
            clearProgram();
        }

        // load a .asm file and parse all the lines into instructions
        bool loadFile(string filename) {
            ifstream ifs(filename.c_str());
            if (!ifs.is_open()) {
                cout << "Error: cannot open file '" << filename << "'" << endl;
                return false;
            }

            clearProgram();
            cpu.getPC().reset();

            // put all lines into the queue first
            MyQueue lineQueue;
            string line;
            int lineNum = 0;
            while (getline(ifs, line)) {
                lineNum++;
                lineQueue.enqueue(line);
            }
            ifs.close();

            // now take lines out of the queue and parse them one by one
            int qLine = 0;
            while (!lineQueue.isEmpty()) {
                string l = lineQueue.dequeue();
                qLine++;
                Instructions* instr = parseLine(l, qLine);
                if (instr != NULL) {
                    program.push_back(instr);
                }
            }

            return true;
        }

        // run all the instructions from start to finish
        void run() {
            if (program.isEmpty()) {
                cout << "No program loaded." << endl;
                return;
            }

            cpu.getPC().reset();
            cout << "Start program" << endl;

            while ((int)cpu.getPC().getPC() < program.getSize()) {
                int currentPC = (int)cpu.getPC().getPC();

                // this calls the right execute() through polymorphism
                program[currentPC]->execute(cpu);

                cpu.incrementPC();
            }

            cout << "End of program" << endl;
        }

        // show the final state on screen and save to file
        void dumpResults(string outputFile) {
            cpu.dump(outputFile);
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
            cpu.pushStack(i * 10); // Should throw error when i = 8
        }
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }

    return 0;
}