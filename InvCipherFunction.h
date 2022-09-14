#include <stdint.h>

// This transformation substitutes each byte in the State with its corresponding value from the inverse S-Box,
// thus reversing the effect of a subBytes() operation.
uint8_t ** invSubBytes(uint8_t **state)
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
            buffer[i][j] = InvsBox[k][l];
        }
    }

    return buffer;
}

// This transformation performs the inverse of shiftRows() on each row in the State
void invShiftRows(uint8_t **state)
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
            state[i][0] = temp4;
            state[i][1] = temp1;
            state[i][2] = temp2;
            state[i][3] = temp3;
        }
    }
}

// This transformation is the inverse of mixColumns
void invMixColumns(uint8_t **state)
{
    uint8_t state0, state1, state2, state3;

    //Loop through every column within the state
    for (int i = 0; i < 4; i++)
    {
        //First Row Value Change
        state0 = ffadd(ffadd(ffadd(ffmultiply(0x0e, state[0][i]), ffmultiply(0x0b, state[1][i])), ffmultiply(0x0d, state[2][i])), ffmultiply(0x09, state[3][i]));
        //Second Row Value Change
        state1 = ffadd(ffadd(ffadd(ffmultiply(0x09, state[0][i]), ffmultiply(0x0e, state[1][i])), ffmultiply(0x0b, state[2][i])), ffmultiply(0x0d, state[3][i]));
        //Third Row Value Change
        state2 = ffadd(ffadd(ffadd(ffmultiply(0x0b, state[0][i]), ffmultiply(0x09, state[1][i])), ffmultiply(0x0e, state[2][i])), ffmultiply(0x0b, state[3][i]));
        //Fourth Row Value Change
        state3 = ffadd(ffadd(ffadd(ffmultiply(0x0d, state[0][i]), ffmultiply(0x0d, state[1][i])), ffmultiply(0x09, state[2][i])), ffmultiply(0x0e, state[3][i]));

        //Assign Calculated Values
        state[0][i] = state0;
        state[1][i] = state1;
        state[2][i] = state2;
        state[3][i] = state3;
    }
}

void invCipher(string cipher, string key, int Nk, int Nr)
{

}