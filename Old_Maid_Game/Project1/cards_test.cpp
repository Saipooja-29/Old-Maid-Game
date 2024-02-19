// File Name: cards_test.cpp
// Author: Saipooja Kongalla
// Date: 4/3/2023
// Compiler Used: MS build with Microsoft Visual studio c++
// This file is the driver file that contains the main function. 


#include<iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <iterator>
#include <algorithm>
#include <random>
#include <stdlib.h>
#include "old_maid.h"

using namespace std;

int main() {
    srand(time(0));
    //freopen_s(&stream,"full_output.txt", "w",stdout);

    CardGameSimulator cgs;
    cgs.get_user_input();
    //Writing the cout display into a file
    cgs.file_out.open(cgs.outputfile);
    streambuf* cout_sbuf = cout.rdbuf();
    cout.rdbuf(cgs.file_out.rdbuf());
    //Playing games as per the user input
    cgs.play_games();
    cgs.display_statistics();
    //Return contron on cout
    cout.rdbuf(cout_sbuf);
    cgs.file_out.close();
    //fclose(stdout);

    //Display Output on the console
    string text;
    ifstream in_file(cgs.outputfile);
    if (in_file.is_open()) {
        while (in_file.good()) {
            getline(in_file, text);
            cout << text<< endl;
        }
    }
    in_file.close();

    return 0;
}
