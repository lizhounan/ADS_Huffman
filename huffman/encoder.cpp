#include "encoder.h"

void read(std::map<int, int>& freq, std::string filename)
{
    int a;
    std::ifstream infile(filename);
    std::string str;
    while (!infile.eof())
    {
        
        std::getline(infile, str);
        if (str.empty())
        {
            break;
        }
        a = std::stoi(str);
        if (freq.find(a) == freq.end())
        {
            freq[a] = 1;
        }
        else
        {
            freq[a]++;
        }
    }

    infile.close();
}

void del(Tree* proot)
{
    if (proot == nullptr)
        return;
    del(proot->left);
    del(proot->right);
    delete proot;
}
void print_Code(Tree* proot, std::string st, std::map<int, std::string>& encode)
{
    if (proot == NULL)
        return;
    if (proot->left)
    {
        print_Code(proot->left, st + '0', encode);
    }
    if (proot->right)
    {
        print_Code(proot->right, st + '1', encode);
    }
    if (!proot->left && !proot->right)
    {
        
        encode[proot->key] = st;
    }

}

// huffman for d-way heap
void huffman(std::map<int, int>& freq, DaryHeap th, std::map<int, std::string>& encode)
{
    int i;
    std::string c;
    int fr;
    auto it = freq.begin();
    while (it != freq.end()) {
        Tree* pt = new Tree;
        pt->key = it->first;
        pt->freq = it->second;
        it++;
        th.Insert(pt);
    }
    // construct Huffman Tree
    while (true)
    {
        Tree* proot = new Tree;
        pTree pl, pr;
        pl = th.findMin();
        th.Delete(1);
        if (th.isEmpty()) {
            th.Insert(pl);
            break;
        }

        pr = th.findMin();
        th.Delete(1);
        proot->freq = pl->freq + pr->freq;
        proot->left = pl;
        proot->right = pr;
        th.Insert(proot);
    }
    std::string s = "";
    print_Code(th.findMin(), s, encode);

    del(th.findMin());
}

// huffman for pairing heap, 
// because these two data structure has one function different -- deleteMin()
void huffman(std::map<int, int>& freq, PairingHeap ph, std::map<int, std::string>& encode)
{
    int i;
    std::string c;
    int fr;
    auto it = freq.begin();
    while (it != freq.end()) {
        Tree* pt = new Tree;
        pt->key = it->first;
        pt->freq = it->second;
        it++;
        ph.Insert(pt);
    }
    // construct Huffman Tree
    while (true)
    {
        Tree* proot = new Tree;
        pTree pl, pr;
        pl = ph.findMin();
        ph.deleteMin();
        if (ph.isEmpty()) {
            ph.Insert(pl);
            break;
        }

        pr = ph.findMin();
        ph.deleteMin();
        proot->freq = pl->freq + pr->freq;
        proot->left = pl;
        proot->right = pr;
        ph.Insert(proot);
    }
    std::string s = "";
    print_Code(ph.findMin(), s, encode);

    del(ph.findMin());
}
std::map<int, std::string> encoder(std::string filename)
{
    std::map<int, int> freq;
    std::map<int, std::string> encode;
    DaryHeap th2(1000000, 2);
    DaryHeap th4(1000000, 4);
    PairingHeap ph;

    read(freq, filename);
    std::cout << "read_freq_over" << std::endl;

    // the encode process start
    const clock_t begin_time = clock();

    // construct the huffmanTree, and get the code map -- encode
    //huffman(freq, ph, encode);
    //huffman(freq, th2, encode);
    huffman(freq, th4, encode);

    // save to code_table
    std::ofstream fout_dict("code_table.txt", std::ios::out);
    std::map<int, std::string>::iterator iter;
    iter = encode.begin();
    while (iter != encode.end()) {
        fout_dict << iter->first << " " << iter->second << std::endl;
        iter++;
    }
    fout_dict.close();


    std::cout << "code table saved" << std::endl;

    // encode the input.txt into a string ss
    std::ifstream infile(filename);
    std::string ss = "";
    int cnt = 0;
    while (!infile.eof())
    {

        std::string str;
        std::getline(infile, str);
        if (str.empty())
        {
            break;
        }
        int a = std::stoi(str);
        ss += encode[a];
        cnt += 1;
    }
    infile.close();
    // encoded process end
    


    // write to the encode.txt
    std::ofstream fout("encoded.bin", std::ios::out | std::ios::binary);
    unsigned char buf = 0;
    int count = 0;
    int i = 0;
    while (i < ss.length())
    {
        buf = buf | ((ss[i++] - '0') << (7 - count));
        count++;
        if (count == 8)
        {
            count = 0;
            fout << buf;
            buf = 0;
        }
    }
    if (count != 0)
        fout << buf;
    fout.close();

    

    return encode;
}