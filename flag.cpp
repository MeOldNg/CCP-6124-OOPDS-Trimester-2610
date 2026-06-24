#include <iostream>
#include <string>
using namespace std;

class FlagRegister {
private:
    int CF; // Carry
    int OF; // Overflow
    int UF; // Underflow
    int ZF; // Zero

public:
    FlagRegister() : CF(0), OF(0), UF(0), ZF(0) {}

    void setCF(int v) { CF = v ? 1 : 0; }
    void setOF(int v) { OF = v ? 1 : 0; }
    void setUF(int v) { UF = v ? 1 : 0; }
    void setZF(int v) { ZF = v ? 1 : 0; }

    int getCF() const { return CF; }
    int getOF() const { return OF; }
    int getUF() const { return UF; }
    int getZF() const { return ZF; }

    void updateFlags(int result) {
        OF = (result > 127)  ? 1 : 0;
        UF = (result < -128) ? 1 : 0;
        CF = (result > 127 || result < -128) ? 1 : 0;
        ZF = (result == 0)   ? 1 : 0;
    }

    void reset(const string& flag) {
        if (flag == "CF") CF = 0;
        else if (flag == "OF") OF = 0;
        else if (flag == "UF") UF = 0;
        else if (flag == "ZF") ZF = 0;
    }
};

    int main() {
    FlagRegister reg;
    int number;
    cout << "Enter a number: ";
    cin >> number;

    reg.updateFlags(number);

    cout << "\nResult: " << endl;
    cout << "OF (overflow): " << reg.getOF() << endl;
    cout << "UF (underflow): " << reg.getUF() << endl;
    cout << "CF (carry): " << reg.getCF() << endl;
    cout << "ZF (zero): " << reg.getZF() << endl;

    cout << "\nResetting CF..." << endl;
    reg.reset("CF");
    cout << "CF after reset: " << reg.getCF() << endl;

    return 0;
}