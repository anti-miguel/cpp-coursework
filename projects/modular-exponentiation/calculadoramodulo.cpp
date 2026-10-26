#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to perform modular exponentiation
// It returns (base^exponent) % modulus
unsigned long long mod_exp(unsigned long long base, unsigned long long exponent, unsigned long long modulus) {
    unsigned long long result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1) {
            result = (result * base) % modulus;
        }
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    unsigned long long bases[] = {1308, 606, 417};
    unsigned long long exponent = 17;
    unsigned long long modulus = 3233;

    for (unsigned long long base : bases) {
        unsigned long long result = mod_exp(base, exponent, modulus);
        cout << result << " ";
    }

    return 0;
}