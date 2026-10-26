#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

using namespace std;

int a;
int b;

vector<char> tape = {'&','#','&'};

void ToTape(int num1, int num2) {
    for (int i = 0; i < num1; i++) {
        tape.insert(tape.begin() + 1,'1');
    }
    for (int i = 0; i < num2; i++) {
        tape.insert(tape.end() - 1, '1');
    }
}

void PrintTape() {
    for (int i = 0; i < tape.size(); i++) {
        cout << tape[i] << " ";
    }
    cout << endl;
}

// No se me ha ocurrido ningun nombre mejor para estas funciones por ahora UwU (WiP)

int CheckPos() {
    for (int i = 0; i < tape.size(); i++) {
        if (tape[i] == '#') {
            return i;
        }
    }
    throw std::logic_error("Tape separator is missing");
}

void Multiplication1(int num2, int pos) {
    for (int i = 0; i < num2; i++) {
        if (tape[CheckPos() + (i + 1)] == '1') {
            tape[CheckPos() + (i + 1)] = '@';
            return;
        }
    }
}

void Multiplication2(int num1) {
    for (int i = 0; i < num1; i++) {
        if (tape[i + 1] == '1') {
            tape[i + 1] = '@';
        }
    }
}

void Add1() {
    int i = 0;
    do {
        if (tape[i + 1] == '@') {
            tape.push_back('1');
        }
        i++;
    } while (tape[i] != '#');
}

void Replace1(int num1) {
    for (int i = 0; i < num1; i++) {
        if (tape[i + 1] == '@') {
            tape[i + 1] = '1';
        }
    }
}

void All1() {
    for (int i = 0; i < tape.size(); i++) {
        if (tape[i] == '@') {
            tape[i] = '1';
        }
    }
}

int main()
{
    cout << "Operacion: a x b" << endl;
    cout << "Dame a: " << endl;
    cin >> a;
    cout << "Dame b: " << endl;
    cin >> b;
    cout << "En la cinta: " << endl;
    ToTape(a, b);
    PrintTape();

    for (int i = 0; i < b; i++) {
        Multiplication1(b, CheckPos());
        PrintTape();
        Multiplication2(a);
        PrintTape();
        Add1();
        PrintTape();
        Replace1(a);
        PrintTape();
    }
    All1();
    PrintTape();
}
