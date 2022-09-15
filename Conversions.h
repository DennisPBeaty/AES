#include <iostream>
#include <stdio.h>
#include <string.h>
#include <vector>

#ifndef Conversions
#define Conversions

using namespace std;

vector<unsigned char> stringTo1dVector(string text) {
    vector<unsigned char> result;

    for (unsigned int i = 0; i < text.length(); i += 2) {
        string result1 = text.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(result1.c_str(), NULL, 16);
        result.push_back(byte);
    }

    return result;
}

vector<vector<unsigned char>> stringTo2dVector(string text)
{
    vector<unsigned char> result;

    for (unsigned int i = 0; i < text.length(); i += 2) {
        string result1 = text.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(result1.c_str(), NULL, 16);
        result.push_back(byte);
    }

    vector<vector<unsigned char>> state(4, vector<unsigned char>(4, 0x0));
    int x = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = result[x];
                x++;
        }
    }

    return state;
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