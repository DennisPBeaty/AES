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
    unsigned int temp;
    int i = 0; 

    int temp_word = 0x0;

    while (i < Nk) {
        temp_word = temp_word | key[4*i];
        temp_word = temp_word << 8;

        temp_word = temp_word | key[4*i + 1];
        temp_word = temp_word << 8;

        temp_word = temp_word | key[4*i + 2];
        temp_word = temp_word << 8;

        temp_word = temp_word | key[4*i + 3];   

        w[i] = temp_word;

        temp_word = 0x0;
        i++;
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
}