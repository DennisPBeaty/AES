
// CPP program to convert string
// to char array
#include <iostream>
#include <cstring>

 
using namespace std;

char const hex_chars[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };
 
// driver code
int main()
{
    

    const string s = "00112233445566778899aabbccddeeff";
    int n = s.length();
    char char_array[n];
    strcpy(char_array, s.c_str());
    
    
    for (int i = 0; i < n; i = i+2)
    {
        char upper_byte = char_array[i];
        char lower_byte = char_array[i+1];
        char bytes[] = {upper_byte, lower_byte};
        uint8_t converted = strtol(bytes, NULL, 16);
    
        
        cout << converted;
        
        cout << endl;
        
            char const byte = converted;
        
            char test1 = hex_chars[ ( byte & 0xF0 ) >> 4 ];
            char test2 = hex_chars[ ( byte & 0x0F ) >> 0 ];
            
            cout << test1 << test2;
        
        cout << endl;
        cout << endl;
    }
    return 0;
}