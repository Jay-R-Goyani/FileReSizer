//Date   : 20-6-2024
//Author : Jay_Goyani
//Email  : jaygoyani2004@gmail.com

//******************************************************************************************************//
//******************************************************************************************************//

#include <bits/stdc++.h>
#include <ctime>
#include <unistd.h>
#include "Unit_LZW.hpp"
#include "Unit_Huffman.hpp"

using namespace std;
int main()
{
    const string RED = "\033[31m";
    const string PINK = "\033[35m";
    const string YELLOW = "\033[33m";
    const string BLUE = "\033[34m";
    const string MAGENTA = "\033[35m";
    const string CYAN = "\033[36m";
    const string BOLD = "\033[1m";
    const string RESET = "\033[0m";

    do
    {
        int choice;
        cout << endl;
        cout << "-------------------------------------------------------WELCOME TO "
             << RED << "File" << RESET
             << PINK << "Re" << RESET
             << BLUE << "Sizer" << RESET
             << "--------------------------------------------------------------"
             << endl;
        sleep(1);
        cout << endl;
        cout << RED << "--> Enter " << BOLD << 1 << RESET << RED << " for Compressing a file." << RESET << endl;
        sleep(1);
        cout << PINK << "--> Enter " << BOLD << 2 << RESET << PINK << " for Decompressing a file." << RESET << endl;
        sleep(1);
        cout << BLUE << "--> Enter " << BOLD << 3 << RESET << BLUE << " for Exiting." << RESET << endl;
        cin >> choice;

        if (choice == 1)
        {
            int pref;
            cout << "-------------------------------------------------------Compressing File Using "
                 << RED << "File" << RESET
                 << PINK << "Re" << RESET
                 << BLUE << "Sizer" << RESET
                 << "--------------------------------------------------"
                 << endl;
            sleep(1);
            cout << MAGENTA << "--> Enter " << BOLD << 1 << RESET << MAGENTA << " for Compressing file using Lempel-Ziv-Welch Algorithm " << RESET << endl;
            sleep(1);
            cout << BLUE << "--> Enter " << BOLD << 2 << RESET << BLUE << " for Compressing file using Huffman Algorithm" << RESET << endl;
            sleep(1);
            cout << CYAN << "--> Enter " << BOLD << 3 << RESET << CYAN << " for Back" << RESET << endl;
            sleep(1);
            cin >> pref;
            cout << endl;

            if (pref == 3)
            {
                continue;
            }

            string Source_file_name;
            cout << "Enter the file Name to be compressed : ";
            cin >> Source_file_name;
            string Destination_file_name;
            cout << "Enter the file Name to be saved : ";
            cin >> Destination_file_name;

            cout << endl;

            if (Source_file_name == Destination_file_name)
            {
                cout << "Please Enter Different Source and Destination Because Operation In Same File leads To Data Loss" << endl;
                continue;
            }

            clock_t tStart = clock();
            ifstream f1(Source_file_name, ios::binary | ios::ate);
            int before = f1.tellg();

            if (pref == 1)
            {
                LZW f(Source_file_name, Destination_file_name);
                f.compression();
            }
            else
            {

                Huffman f(Source_file_name, Destination_file_name);
                f.compression();
            }

            cout << endl;
            cout << "Compressed Successfully to file : " << YELLOW << Destination_file_name << RESET << endl;
            sleep(1);

            cout << "Time taken: " << YELLOW << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << RESET << " sec" << endl;
            sleep(1);

            ifstream f2(Destination_file_name, ios::binary | ios::ate);
            cout << "File Size Before Compressing : " << YELLOW << before << RESET << " Bytes" << endl;
            sleep(1);

            int after = f2.tellg();
            cout << "File Size After Compressing : " << YELLOW << after << RESET << " Bytes" << endl;
            sleep(1);

            double compression_Percentage = (double)after * 100 / before;
            cout << "The Size Of Compressed File Is " << YELLOW << fixed << setprecision(2) << compression_Percentage << RESET << " %" << " Of The Given File." << endl;
        }
        else if (choice == 2)
        {
            int pref;
            cout << "-------------------------------------------------------DeCompressing File Using "
                 << RED << "File" << RESET
                 << PINK << "Re" << RESET
                 << BLUE << "Sizer" << RESET
                 << "------------------------------------------------"
                 << endl;
            sleep(1);
            cout << MAGENTA << "--> Enter " << BOLD << 1 << RESET << MAGENTA << " for Decompressing file using Lempel-Ziv-Welch Algorithm " << RESET << endl;
            sleep(1);
            cout << BLUE << "--> Enter " << BOLD << 2 << RESET << BLUE << " for Decompressing file using Huffman Algorithm" << RESET << endl;
            sleep(1);
            cout << CYAN << "--> Enter " << BOLD << 3 << RESET << CYAN << " for Back" << RESET << endl;

            cin >> pref;
            cout << endl;

            if (pref == 3)
            {
                continue;
            }
            string Source_file_name;
            cout << "Enter the file Source_file_name to be decompressed : ";
            cin >> Source_file_name;
            string Destination_file_name;
            cout << "Enter the file Source_file_name to be saved : ";
            cin >> Destination_file_name;

            cout << endl;
            if (Source_file_name == Destination_file_name)
            {
                cout << "Please Enter Different Source and Destination Because Operation In Same File leads To Data Loss" << endl;
                continue;
            }

            clock_t tStart = clock();

            if (pref == 1)
            {
                LZW f(Source_file_name, Destination_file_name);
                f.decompression();
            }
            else
            {

                Huffman f(Source_file_name, Destination_file_name);
                f.decompression();
            }

            ifstream f1(Source_file_name, ios::binary | ios::ate);
            int after = f1.tellg();
            cout << endl;
            cout << "File Size After Decompressing : " << YELLOW << after << RESET << " Bytes" << endl;
            sleep(1);
            cout << "DeCompressed Successfully to file : " << YELLOW << Destination_file_name << RESET << endl;
            sleep(1);
            cout << "Time taken: " << YELLOW << (1.0 * (clock() - tStart) / CLOCKS_PER_SEC) << RESET << " sec" << endl;
        }
        else if (choice == 3)
        {
            cout<<CYAN<<"Thank You ! Have A Nice Day"<<RESET<<endl;
            exit(0);
        }
        else
        {
            cout << RED << "Invalid choice" << RESET << endl;
        }
    } while (1);
    return 0;
}
