//
// Created by Kevin Leong on 4/27/21.
//
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char** argv){

    string inFileName = argv[1];
    int nameP1 = inFileName.find_last_of('/') + 1;
    int nameP2 = inFileName.length() - nameP1 - 4;
    string outFileName = inFileName.substr(nameP1, nameP2);

    


    return 0;
}

