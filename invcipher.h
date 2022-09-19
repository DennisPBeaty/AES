#include <iomanip>

// This transformation substitutes each byte in the State with its corresponding value from the invS-Box.
void invSubBytes(vector<vector<unsigned char>>& state)
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
            state[i][j] = InvsBox[k][l];
        }
    }
}

// This transformation performs the inverse of shiftRows() on each row in the State
void invShiftRows(vector<vector<unsigned char>>& state)
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
            state[i][0] = temp4;
            state[i][1] = temp1;
            state[i][2] = temp2;
            state[i][3] = temp3;
        }
    }
}

// This transformation is the inverse of mixColumns
void invMixColumns(vector<vector<unsigned char>>& state)
{
    unsigned char state0, state1, state2, state3;

    //Loop through every column within the state
    for (int i = 0; i < 4; i++)
    {
        //First Row Value Change
        state0 = ffadd(ffadd(ffadd(ffmultiply(0x0e, state[0][i]), ffmultiply(0x0b, state[1][i])), ffmultiply(0x0d, state[2][i])), ffmultiply(0x09, state[3][i]));
        //Second Row Value Change
        state1 = ffadd(ffadd(ffadd(ffmultiply(0x09, state[0][i]), ffmultiply(0x0e, state[1][i])), ffmultiply(0x0b, state[2][i])), ffmultiply(0x0d, state[3][i]));
        //Third Row Value Change
        state2 = ffadd(ffadd(ffadd(ffmultiply(0x0d, state[0][i]), ffmultiply(0x09, state[1][i])), ffmultiply(0x0e, state[2][i])), ffmultiply(0x0b, state[3][i]));
        //Fourth Row Value Change
        state3 = ffadd(ffadd(ffadd(ffmultiply(0x0b, state[0][i]), ffmultiply(0x0d, state[1][i])), ffmultiply(0x09, state[2][i])), ffmultiply(0x0e, state[3][i]));

        //Assign Calculated Values
        state[0][i] = state0;
        state[1][i] = state1;
        state[2][i] = state2;
        state[3][i] = state3;
    }
}

void invCipher(vector<vector<unsigned char>> cipher, vector<unsigned char> key, vector<vector<unsigned char>>& plain, vector<unsigned int>& w, int Nk, int Nr)
{
    vector<unsigned int> word;

    word.assign(next(w.begin(), Nr*4), next(w.begin(), (Nr+1)*4));

    cout << "round[ 0].iinput    "; printState(cipher); cout << endl; 
    cout << "round[ 0].ik_sch    "; printVecInt(word); cout << endl;

    addRoundKey(cipher, word);

    for (int i = Nr-1; i > 0; i--)
    {
        cout << "round[" << setw(2) << Nr-i << "].istart    "; printState(cipher); cout <<  endl;
        invShiftRows(cipher);
        cout << "round[" << setw(2) << Nr-i << "].is_row    "; printState(cipher); cout << endl;
        invSubBytes(cipher);
        cout << "round[" << setw(2) << Nr-i << "].is_box    "; printState(cipher); cout << endl;
        word.assign(next(w.begin(), i*(4)), next(w.begin(), (i+1)*4));
        cout << "round[" << setw(2) << Nr-i << "].ik_sch    "; printVecInt(word); cout << endl;
        addRoundKey(cipher, word);
        cout << "round[" << setw(2) << Nr-i << "].ik_add    "; printState(cipher); cout << endl;
        invMixColumns(cipher);
    }
    cout << "round[" << setw(2) << Nr << "].istart    "; printState(cipher); cout <<  endl;
    invShiftRows(cipher);
    cout << "round[" << setw(2) << Nr << "].is_row    "; printState(cipher); cout << endl;
    invSubBytes(cipher);
    cout << "round[" << setw(2) << Nr << "].is_box    "; printState(cipher); cout << endl;
    word.assign(w.begin(), next(w.begin(), 4));
    cout << "round[" << setw(2) << Nr << "].ik_sch    "; printVecInt(word); cout << endl;
    addRoundKey(cipher, word);

    plain = cipher;
    cout << "round[" << setw(2) << Nr << "].ioutput   "; printState(cipher); cout << endl << endl;
}
