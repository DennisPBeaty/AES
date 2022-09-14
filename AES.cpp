//Dennis Preston Beaty
//COSC 483
//AES Project
//September 9th, 2022

using namespace std;

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include <Sbox.h>
#include <Rcon.h>
#include <ffFunctions.h>
#include <KeyExpansion.h>
#include <CipherFunction.h>
#include <InvCipherFunction.h>
#include <Conversions.h>

int main (int argc, char *argv[]) 
{
    int Nk = 4;
    int Nr = 10;
    string plaintext = "00112233445566778899aabbccddeeff";
    string key = "000102030405060708090a0b0c0d0e0f";

    cout << "C.1   AES-128 (Nk=" << Nk << ", Nr=" << Nr << ")" << endl << endl;

    cout << "PLAINTEXT:          " << plaintext << endl;
    cout << "KEY:                " << key << endl << endl;

    cout << "CIPHER (ENCRYPT):"  << endl;

    uint8_t **state = cipher(plaintext, key, Nk, Nr);

    cout << endl << "INVERSE CIPHER (DECRYPT):" << endl;

    invCipher(state, key, Nk, Nr);

    return 0;
}