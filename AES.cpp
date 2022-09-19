//Dennis Preston Beaty
//COSC 483
//AES Project
//September 9th, 2022

using namespace std;

#include <stdio.h>
#include <stdint.h>
#include <iostream>
#include <vector>
#include "const.h"
#include "ffFunctions.h"
#include "KeyExpansion.h"
#include "cipher.h"
#include "invcipher.h"
#include "Conversions.h"

int main (int argc, char *argv[]) 
{
    //-------------------------------------------------------------------------------
    //                           C.1   AES-128 (Nk=4, Nr=10)
    //-------------------------------------------------------------------------------
    int Nk = 4;
    int Nr = 10;
    string plaintext = "00112233445566778899aabbccddeeff";
    string key = "000102030405060708090a0b0c0d0e0f";

    vector<unsigned char> key_format = stringTo1dVector(key);
    vector<vector<unsigned char>> plaintext_format = stringTo2dVector(plaintext);

    cout << "C.1   AES-128 (Nk=" << Nk << ", Nr=" << Nr << ")" << endl << endl;

    cout << "PLAINTEXT:          " << plaintext << endl;
    cout << "KEY:                " << key << endl << endl;

    cout << "CIPHER (ENCRYPT):"  << endl;

    vector<vector<unsigned char>> cipher_result;
    vector<unsigned int> k_sch (4*(Nr+1), 0x0);

    cipher(plaintext_format, key_format, cipher_result, k_sch, Nk, Nr);

    cout << endl << "INVERSE CIPHER (DECRYPT):" << endl;

    vector<vector<unsigned char>> plain_result;
    invCipher(cipher_result, key_format, plain_result, k_sch, Nk, Nr);

    //-------------------------------------------------------------------------------
    //                           C.2   AES-192 (Nk=6, Nr=12)
    //-------------------------------------------------------------------------------
    Nk = 6;
    Nr = 12;
    plaintext = "00112233445566778899aabbccddeeff";
    key = "000102030405060708090a0b0c0d0e0f1011121314151617";

    key_format = stringTo1dVector(key);
    plaintext_format = stringTo2dVector(plaintext);

    cout << "C.2   AES-192 (Nk=" << Nk << ", Nr=" << Nr << ")" << endl << endl;

    cout << "PLAINTEXT:          " << plaintext << endl;
    cout << "KEY:                " << key << endl << endl;

    cout << "CIPHER (ENCRYPT):"  << endl;

    vector<unsigned int> k_sch2 (4*(Nr+1), 0x0);

    cipher(plaintext_format, key_format, cipher_result, k_sch2, Nk, Nr);

    cout << endl << "INVERSE CIPHER (DECRYPT):" << endl;

    invCipher(cipher_result, key_format, plain_result, k_sch2, Nk, Nr);

    //-------------------------------------------------------------------------------
    //                           C.3   AES-256 (Nk=8, Nr=14)
    //-------------------------------------------------------------------------------
    Nk = 8;
    Nr = 14;
    plaintext = "00112233445566778899aabbccddeeff";
    key = "000102030405060708090a0b0c0d0e0f101112131415161718191a1b1c1d1e1f";

    key_format = stringTo1dVector(key);
    plaintext_format = stringTo2dVector(plaintext);

    cout << "C.3   AES-256 (Nk=" << Nk << ", Nr=" << Nr << ")" << endl << endl;

    cout << "PLAINTEXT:          " << plaintext << endl;
    cout << "KEY:                " << key << endl << endl;

    cout << "CIPHER (ENCRYPT):"  << endl;

    vector<unsigned int> k_sch3 (4*(Nr+1), 0x0);

    cipher(plaintext_format, key_format, cipher_result, k_sch3, Nk, Nr);

    cout << endl << "INVERSE CIPHER (DECRYPT):" << endl;

    invCipher(cipher_result, key_format, plain_result, k_sch3, Nk, Nr);
}