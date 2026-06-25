#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
using namespace std;

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

class CPU;

class Instructions {
    protected:
        string opp;
        string arg1;
        string arg2;
    
        public:
        Instructions(const string& op, const string& a1, const string& a2)
            : opp(op), arg1(a1), arg2(a2) {}

        virtual ~Instructions() {} 


        string getOpp() const {return opp;}
        string getArg1() const {return arg1;}
        string getArg2() const {return arg2;}

        string toString() const {
            string s = opp;
            if (!arg1.empty()) s += " " + arg1;
            if (!arg2.empty()) s += " " + arg2;
            return s;
        }
};

class CPU {
    private:
    public:
        
};

class Runner{
    public:
        void readFile() {
            string fileName;
            cout << "Enter the file name: ";
            cin >> fileName;
            ifstream  file(fileName);
            if (!file.is_open()) {
                cout << "Error! " << endl;
            }

            string line;
            while (getline(file, line)) {
                cout << "The current line is - " << line << endl;
            }

            file.close();
        }

        void MOV() {

        }

        void INC() {
            
        }

        void DEC() {
            
        }

        void ROL() {

        }

        void ROR() {

        }

        void SHL() {

        }

        void SHR() {

        }


};

class IOInstructions : public Instructions {

};

class shiftInstructions : public Instructions {

};

int main() {
    
}