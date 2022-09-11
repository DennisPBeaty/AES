//Dennis Preston Beaty
//COSC 483
//AES Project
//September 9th, 2022

using namespace std;

#include <stdio.h>
#include <stdint.h>
#include <Sbox.h>
#include <iostream>
#include <vector>

// adds two finite fields
uint8_t ffadd(uint8_t field1, uint8_t field2)
{
    return field1 ^ field2;
}

// multiplies a finite field by x
uint8_t xtime(uint8_t field)
{
    bool needXor = false;
    //Determine whether or not leading bit that is overflowed will be 1 or not
    if (field >> 7 == 0x01)
    {
        needXor = true;
    }
    //Addition
    field = field << 1;

    //Remove overflow by mod if necessary
    if (needXor == true)
    {
        field = field ^ 0x1b;
    }
}

// uses xtime to multiply any finite field by any other finite field
uint8_t ffmultiply(uint8_t a, uint8_t b)
{
    uint32_t sum = 0x00;

    //Loop through bit a
    for (int i = 0; i < 8; i++)
    {
        //Find ai
        uint8_t ai = (a >> i) & 0x01;

        //If Ai is one xor
        if (ai == 0x01)
        {
            sum = sum ^ b;
        }

        //Only multiply b by x if not seven
        if (i != 7)
        {
            b = xtime(b);
        }
    }
}

// takes a four-byte input word and substitutes each byte in that word with its appropriate value from the S-Box
uint32_t subWord(uint32_t word)
{
    vector<uint32_t> buffer;

    //Add individual bytes to buffer
    buffer.push_back((word & 0xFF000000) >> 24);
    buffer.push_back((word & 0xFF0000) >> 16);
    buffer.push_back((word & 0xFF00) >> 8);
    buffer.push_back(word & 0xFF);

    uint32_t result = 0x0;
    //Perform substitution of each byte with its corresponding location in Sbox
    for (int i = 0; i < buffer.size(); i++)
    {
        uint32_t j = (buffer[i] & 0xF0) >> 4;
		uint32_t k = buffer[i] & 0xF;

        result = (result << 8) + sBox[j][k];
    }

    return result;
}
// performs a cyclic permutation on its input word
uint32_t rotWord(uint32_t word)
{
    uint32_t result = (word << 8) & 0xFFFFFFFF;

    return (result | ((word >> 24) & 0xFF));
}

// This transformation substitutes each byte in the State with its corresponding value from the S-Box.
uint8_t ** subBytes(uint8_t **state)
{
    uint8_t **buffer;
    
    //Loop through every byte within the state
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //Find the correct substitution within the sbox
            uint8_t current = state[i][j];

            int k = (current & 0xF0) >> 4;
            int l = (current & 0xF);

            //Insert value to buffer
            buffer[i][j] = sBox[k][l];
        }
    }

    return buffer;
}

// This transformation performs a circular shift on each row in the State (see Section 5.1.2)
uint8_t ** shiftRows(uint8_t **state)
{
    uint8_t **buffer;

    //Loop through every row within the state
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < i; j++)
        {
            //Create buffer for each element in array
            uint8_t temp1 = state[i][0];
            uint8_t temp2 = state[i][1];
            uint8_t temp3 = state[i][2];
            uint8_t temp4 = state[i][3];
            //Rotate each element to the left
            state[i][0] = temp2;
            state[i][1] = temp3;
            state[i][2] = temp4;
            state[i][3] = temp1;
        }
    }
}

// This transformation treats each column in state as a four-term polynomial. This polynomial is multiplied 
// (modulo another polynomial) by a fixed polynomial with coefficients (see Sections 4.3 and 5.1.3).
void mixColumns(uint8_t **state)
{
    uint8_t state0, state1, state2, state3;

    //Loop through every column within the state
    for (int i = 0; i < 4; i++)
    {
        //First Row Value Change
        state0 = ffadd(ffadd(ffadd(ffmultiply(0x02, state[0][i]), ffmultiply(0x03, state[1][i])), state[2][i]), state[3][i]);
        //Second Row Value Change
        state1 = ffadd(ffadd(ffadd(ffmultiply(0x02, state[1][i]), ffmultiply(0x03, state[2][i])), state[3][i]), state[0][i]);
        //Third Row Value Change
        state2 = ffadd(ffadd(ffadd(ffmultiply(0x02, state[2][i]), ffmultiply(0x03, state[3][i])), state[0][i]), state[1][i]);
        //Fourth Row Value Change
        state3 = ffadd(ffadd(ffadd(ffmultiply(0x02, state[3][i]), ffmultiply(0x03, state[0][i])), state[1][i]), state[2][i]);

        //Assign Calculated Values
        state[0][i] = state0;
        state[1][i] = state1;
        state[2][i] = state2;
        state[3][i] = state3;
    }
}

// This transformation adds a round key to the State using XOR.
void addRoundKey(uint8_t **state)
{

}

// This transformation substitutes each byte in the State with its corresponding value from the inverse S-Box,
// thus reversing the effect of a subBytes() operation.
void invSubBytes(uint8_t **state)
{

}

// This transformation performs the inverse of shiftRows() on each row in the State
void invShiftRows(uint8_t **state)
{

}

// This transformation is the inverse of mixColumns
void invMixColumns(uint8_t **state)
{

}

//Add Cipher
//Add InvCipher

int main (int argc, char *argv[]) 
{

    return 0;
}