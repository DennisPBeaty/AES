#include <stdint.h>

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

//Routine used to generate a series of Round Keys from the Cipher Key. 
uint32_t * KeyExpansion(uint8_t *key, int Nk, int Nr)
{
    uint32_t temp;
    uint32_t *w;

    int i = 0;
    
    for (i = 0; i < Nk; i++)
    {
        w[i] = (uint32_t(key[4*i]) << 24) | (uint32_t(key[4*i+1]) << 16) | (uint32_t(key[4*i+2]) << 8) | uint32_t(key[4*i+3]);
    }

    i = Nk;

    for (i = 0; i < (4*(Nr+1)); i++)
    {
        temp = w[i-1];
        if (i % Nk == 0)
        {
            temp = subWord(rotWord(temp)) ^ Rcon[i/Nk];
        }
        else if ((Nk > 6) && (i % Nk == 4))
        {
            temp = subWord(temp);
        }
        w[i] = w[i - Nk] ^ temp;
    }
    return w;
}