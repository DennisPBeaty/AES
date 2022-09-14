#include <stdint.h>

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
void addRoundKey(uint8_t **state, int round, uint32_t *w)
{
    uint8_t **buffer, **key;

    //Find the key
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            key[i][j] = (w[round*4+j] >> ((3-i)*8)) & 0xFF;
        }
    }

    //Xor with key/Add
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[i][j] = ffadd(key[i][j], state[i][j]);
        }
    }
}

void cipher(string plain, string key, int Nk, int Nr)
{
    uint8_t **state = stringTo2dArray(plain);
    uint8_t **key_convert = stringTo2dArray(key);
}