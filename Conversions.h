#include <stdint.h>
#include <iostream>
#include <string.h>

using namespace std;

uint8_t ** stringTo2dArray(string text)
{
    int length = text.length();
    char buffer[length];
    strcpy(buffer, text.c_str());
    
    uint8_t **state;
    for (int i = 0; i < 4; i++)
    {
        state[i] = new uint8_t[4];
    }

    for (int i = 0; i < length; i = i+2)
    {
        char upper_byte = buffer[i];
        char lower_byte = buffer[i+1];
        char bytes[] = {upper_byte, lower_byte};
        uint8_t converted = strtol(bytes, NULL, 16);
        
        state[(i/2)/4][(i/2)%4] = converted;
    }

    return state;
}

char const chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f' };

string arrayToString(uint8_t **array)
{
    string result = "";

    int rows = sizeof(array)/sizeof(array[0]);
    int columns = sizeof(array[0])/sizeof(array[0][0]);

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            uint8_t current = array[i][j];
            
            uint8_t upper = chars[ ( current & 0xF0 ) >> 4 ];
            uint8_t lower = chars[ ( current & 0x0F ) >> 0 ];

            result.push_back(upper);
            result.push_back(lower);
        }
    }
    return result;
}
