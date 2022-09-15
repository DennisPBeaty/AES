#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#ifndef Conversions
#define Conversions

using namespace std;

vector<vector<unsigned char>> stringTo2dArray(string hex)
{
    vector<unsigned char> bytes;

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }

    vector<vector<unsigned char>> state(4, vector<unsigned char>(4, 0x0));
    int x = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = bytes[x];
                x++;
        }
    }

    return state;
}

char chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

//NEEDS CHANGE NEEDS CHANGE NEEDS CHANGE
vector<unsigned char> stringTo1dArray(string hex) {
    vector<unsigned char> bytes;

    for (unsigned int i = 0; i < hex.length(); i += 2) {
        string byteString = hex.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(byteString.c_str(), NULL, 16);
        bytes.push_back(byte);
    }

    return bytes;
}

void printState(vector<vector<unsigned char>> & state)
{
    for(auto i : state)
    {
        for (auto j: i)
        {
            printf("%x", j);
        }
    }
}

void printKey(vector<unsigned char> & key)
{
        for (auto j: key)
        {
            printf("%x", j);
        }
}

#endif