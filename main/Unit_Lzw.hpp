#include <bits/stdc++.h>

using namespace std;

// For Reset Map string -> int with default ASCII values
void reset_map_St_In(map<string, int> &mp)
{
    mp.clear();
    for (int i = 0; i <= 255; i++)
    {
        string ch(1, char(i));
        mp[ch] = i;
    }
}

// For Reset Map int -> string with default ASCII values
void reset_map_In_St(map<int, string> &mp)
{
    mp.clear();
    for (int i = 0; i <= 255; i++)
    {
        string ch(1, char(i));
        mp[i] = ch;
    }
}

class LZW
{
private:
    string SourceFileName, DestFilename;
    map<string, int> mp1;
    map<int, string> mp2;
    const int max_map_size = numeric_limits<int>::max();
    fstream Source, Dest;

public:
    LZW(string s, string d)
    {
        this->SourceFileName = s;
        this->DestFilename = d;
    }

    // Function For Compressing Given File
    void compression()
    {

        map<string, int> mp;
        Source.open(SourceFileName, ios::in);
        if (!Source.is_open())
        {
            cerr << "Failed to open the source file." << endl;
            exit(0);
        }

        Dest.open(DestFilename, ios::out | ios::binary);
        if (!Dest.is_open())
        {
            cerr << "Failed to open the destination file." << endl;
            exit(0);
        }
        if (Source.peek() == ifstream::traits_type::eof())
        {
            cerr << "Source file is empty." << endl;
            exit(0);
        }

        reset_map_St_In(mp);

        char c;
        Source.get(c);

        string s = "";
        s += c;

        int code = 256;

        while (Source.get(c))
        {
            s += c;

            if (mp.size() == max_map_size)
                reset_map_St_In(mp);

            if (mp.find(s) == mp.end())
            {
                mp[s] = code;
                code++;

                s.pop_back();

                int out = mp[s];

                Dest.write(reinterpret_cast<char *>(&out), sizeof(int));

                s = c;
            }
        }
        int out = mp[s];
        Dest.write(reinterpret_cast<char *>(&out), sizeof(int));

        Source.close();
        Dest.close();
    }

    void decompression()
    {

        Source.open(SourceFileName, ios::in | ios::binary);
        if (!Source.is_open())
        {
            cerr << "Failed to open the source file." << endl;
            exit(0);
        }

        Dest.open(DestFilename, ios::out | ios::binary);
        if (!Dest.is_open())
        {
            cerr << "Failed to open the destination file." << endl;
            exit(0);
        }

        if (Source.peek() == fstream::traits_type::eof())
        {
            cerr << "Source file is empty." << endl;
            exit(0);
        }

        int newcode;
        int oldcode;

        int code = 256;

        map<int, string> mp;
        reset_map_In_St(mp);

        string s = "";

        Source.read(reinterpret_cast<char *>(&newcode), sizeof(newcode));

        if (Source.gcount() != sizeof(newcode))
        {
            cerr << "Failed to read from the source file Or This file may be corrupted" << endl;
            return;
        }

        Dest.write(mp[newcode].c_str(), mp[newcode].size());
        oldcode = newcode;

        char c = mp[newcode][0];

        while (Source.read(reinterpret_cast<char *>(&newcode), sizeof(newcode)))
        {
            if (mp.size() == max_map_size)
            {
                reset_map_In_St(mp);
            }

            if (newcode > code)
            {
                cerr << "This is not our encoded file Or Error in decompression of this file" << endl;
                return;
            }

            if (mp.find(newcode) != mp.end())
            {
                s = mp[newcode];
            }

            else
            {
                s = mp[oldcode] + c;
            }

            Dest.write(s.c_str(), s.size());

            mp[code] = mp[oldcode] + s[0];
            code++;
            c = s[0];
            oldcode = newcode;
        }

        Source.close();
        Dest.close();
    }
};
