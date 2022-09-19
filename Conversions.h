vector<unsigned char> stringTo1dVector(string text) {
    vector<unsigned char> result;

    for (unsigned int i = 0; i < text.length(); i += 2) {
        string result1 = text.substr(i, 2);
        unsigned char byte = (unsigned char) strtol(result1.c_str(), NULL, 16);
        result.push_back(byte);
    }

    return result;
}

vector<vector<unsigned char>> stringTo2dVector(string text)
{
    vector<unsigned char> result = stringTo1dVector(text);

    vector<vector<unsigned char>> state(4, vector<unsigned char>(4, 0x0));
    int k = 0;

    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            state[j][i] = result[k];
                k++;
        }
    }

    return state;
}