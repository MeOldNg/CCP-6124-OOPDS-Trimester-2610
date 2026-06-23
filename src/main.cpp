#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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

class arithmeticInstructions : public Runner {
    private:
    public:
        void ADD() {

        }
        
        void SUB() {

        }

        void MUL() {

        }

        void DIV() {

        }
};

class IOInstructions : public Runner {

};

class shiftInstructions : public Runner {

};

int main() {
    
}