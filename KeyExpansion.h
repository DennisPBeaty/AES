#include <stdint.h>

// takes a four-byte input word and substitutes each byte in that word with its appropriate value from the S-Box
unsigned int subWord(unsigned int word)
{
    vector<unsigned int> buffer;

    //Add individual bytes to buffer
    buffer.push_back((word & 0xFF000000) >> 24);
    buffer.push_back((word & 0xFF0000) >> 16);
    buffer.push_back((word & 0xFF00) >> 8);
    buffer.push_back(word & 0xFF);

    unsigned int result = 0x0;
    //Perform substitution of each byte with its corresponding location in Sbox
    for (int i = 0; i < buffer.size(); i++)
    {
        unsigned int j = (buffer[i] & 0xF0) >> 4;
		unsigned int k = buffer[i] & 0xF;

        result = (result << 8) + sBox[j][k];
    }

    return result;
}

// performs a cyclic permutation on its input word
unsigned int rotWord(unsigned int word)
{
    unsigned int result = (word << 8) & 0xFFFFFFFF;

    return (result | ((word >> 24) & 0xFF));
}

//Routine used to generate a series of Round Keys from the Cipher Key. 
void KeyExpansion(vector<unsigned char>key, vector<unsigned int>w, int Nk, int Nr)
{
    int buff_word = 0x0;
    unsigned int buff;
    int i = 0; 

    for (i = 0; i < Nk; i++) {
        buff_word = 0x0;
        //First 8 bit
        buff_word = buff_word | key[4*i];
        buff_word = buff_word << 8;
        //Second 8 bit
        buff_word = buff_word | key[4*i + 1];
        buff_word = buff_word << 8;
        //Third 8 bit
        buff_word = buff_word | key[4*i + 2];
        buff_word = buff_word << 8;
        //Fourth 8 bit
        buff_word = buff_word | key[4*i + 3];   
        //Set val
        w[i] = buff_word;
    }

    i = Nk;

    for (i = 0; i < (4*(Nr+1)); i++)
    {
        buff = w[i-1];
        if (i % Nk == 0)
        {
            buff = subWord(rotWord(buff)) ^ Rcon[i/Nk];
        }
        else if ((Nk > 6) && (i % Nk == 4))
        {
            buff = subWord(buff);
        }
        w[i] = w[i-Nk] ^ buff;
    }
}