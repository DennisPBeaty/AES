#include <iomanip>

// This transformation substitutes each byte in the State with its corresponding value from the S-Box.
void subBytes(vector<vector<unsigned char>>& state)
{
    //Loop through every byte within the state
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            //Find the correct substitution within the sbox
            unsigned char current = state[i][j];

            int k = (current & 0xF0) >> 4;
            int l = (current & 0xF);

            //Insert value to state
            state[i][j] = sBox[k][l];
        }
    }
}

// This transformation performs a circular shift on each row in the State (see Section 5.1.2)
void shiftRows(vector<vector<unsigned char>>& state)
{
    //Loop through every row within the state
    for (int i = 1; i < 4; i++)
    {
        for (int j = 0; j < i; j++)
        {
            //Create buffer for each element in array
            unsigned char temp1 = state[i][0];
            unsigned char temp2 = state[i][1];
            unsigned char temp3 = state[i][2];
            unsigned char temp4 = state[i][3];
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
void mixColumns(vector<vector<unsigned char>>& state)
{
    unsigned char state0, state1, state2, state3;

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
void addRoundKey(vector<vector<unsigned char>>& state, vector<unsigned int> w)
{
    for (int i = 0; i < 4; i++)
    {
        //Xor with key/Add
        state[0][i] ^= (w[i] >> 24);
        state[1][i] ^= (w[i] >> 16);
        state[2][i] ^= (w[i] >> 8);
        state[3][i] ^= (w[i]);
    }
}

// Print helper function
void printState(vector<vector<unsigned char>> state)
{
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%02x",state[j][i]);
        }
    }
}

void printVecInt(vector<unsigned int> input)
{
    for (int i = 0; i < 4; i++) {
        printf("%08x",input[i]);
    }
}

void cipher(vector<vector<unsigned char>> plain, vector<unsigned char> key, vector<vector<unsigned char>>& cipher, vector<unsigned int>& w, int Nk, int Nr)
{
    vector<unsigned int> word;
    KeyExpansion(key, w, Nk, Nr);
    word.assign(w.begin(), next(w.begin(), 4));

    cout << "round[ 0].input     "; printState(plain); cout << endl; 
    cout << "round[ 0].k_sch     "; printVecInt(word); cout << endl;
    
    addRoundKey(plain, word);
    
    for (int i = 1; i < Nr; i++)
    {
        cout << "round[" << setw(2) << i << "].start     "; printState(plain); cout <<  endl;
        subBytes(plain);
        cout << "round[" << setw(2) << i << "].s_box     "; printState(plain); cout << endl;
        shiftRows(plain);
        cout << "round[" << setw(2) << i << "].s_row     "; printState(plain); cout << endl;
        mixColumns(plain);
        cout << "round[" << setw(2) << i << "].m_col     "; printState(plain); cout << endl;
        word.assign(next(w.begin(), i*(4)), next(w.begin(), (i+1)*4));
        cout << "round[" << setw(2) << i << "].k_sch     "; printVecInt(word); cout << endl;
        addRoundKey(plain, word);
    }
    word.assign(next(w.begin(), Nr*(4)), next(w.begin(), (Nr+1)*4));
    cout << "round[" << setw(2) << Nr << "].start     "; printState(plain); cout <<  endl;
    subBytes(plain);
    cout << "round[" << setw(2) << Nr << "].s_box     "; printState(plain); cout << endl;
    shiftRows(plain);
    cout << "round[" << setw(2) << Nr << "].s_row     "; printState(plain); cout << endl;
    addRoundKey(plain, word);
    cout << "round[" << setw(2) << Nr << "].k_sch     "; printVecInt(word); cout << endl;
    cipher = plain;
    cout << "round[" << setw(2) << Nr << "].output    "; printState(cipher); cout << endl;
}   