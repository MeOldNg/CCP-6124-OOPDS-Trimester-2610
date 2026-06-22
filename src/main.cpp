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

        void arithmetics() {
            
        }
};

int main() {
    
}