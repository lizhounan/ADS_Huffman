#include "decoder.h"

void decode(std::map<int, std::string>& encode, Tree* proot)
{
    // we need to reconstruct the huffman tree according to the encode infomation
    auto it = encode.begin();
    Tree* p = proot;
    while (it != encode.end())
    {
        int key = it->first;
        std::string s = it->second;
        int i = 0;
        while (i < s.length()) {
            if (s[i] == '0') {
                if (proot->left == nullptr)
                    proot->left = new Tree;
                proot = proot->left;
            }
            else {
                if (proot->right == nullptr)
                    proot->right = new Tree;
                proot = proot->right;
            }
            i++;
        }
        proot->key = key;
        proot = p;
        it++;
    }
}
void decoder()
{
    // read code_table.txt
    std::map<int, std::string> encode;
    std::ifstream code_table("code_table.txt", std::ios::in);
    std::string line;
    std::string  key;
    std::string code;
    while (getline(code_table, line))
    {
        std::stringstream ss(line);
        ss >> key >> code;
        encode[std::stoi(key)] = code;
    }

    //recover from encoded.bin
    //recontruct the huffman tree according to the dic

    Tree* proot = new Tree;
    decode(encode, proot);
    //read the encoded.bin file, read the content into a string.
    std::string m;
    std::ifstream f("encoded.bin", std::ios::in | std::ios::binary);
    char c = 0;
    while (f.get(c))
    {
        std::stringstream a;
        for (int i = 7; i > 0; i--)
            a << ((c >> i) & 1);
        a << (c & 1);
        m += a.str();
    }
    f.close();



    //follow the huffman tree to reconstruct the word.
    //there is no situation that one instance's encoded word is another's prefix, so it is pretty easy to decode.
    std::ofstream fout_decoded("decoded.txt", std::ios::out);
    int i = 0;
    Tree* p = proot;
    int cnt = 1;
    while (i < m.length())
    {
        if (m[i] == '0' && proot->left != nullptr)
        {
            proot = proot->left;
            i++;
        }
        else if (m[i] == '1' && proot->right != nullptr)
        {
            proot = proot->right;
            i++;
        }
        else
        {
            fout_decoded << proot->key << std::endl;
            proot = p;
        }
    }
    if (proot->left == nullptr and proot->right == nullptr)
    {
        fout_decoded << proot->key;
    }
}