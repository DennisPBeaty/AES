#include <stdint.h>

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