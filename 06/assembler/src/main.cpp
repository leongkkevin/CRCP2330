//
// Created by Kevin Leong on 4/27/21.
//
#include <iostream>
#include <string>
#include <fstream>;

using namespace std;

string parse(string line){
    string binary;

    if(line[0] == '/' || line.length() == 2){
        return "";
    }
}

int main(int argc, char** argv){

    string inFileName = argv[1];
    int nameP1 = inFileName.find_last_of('/') + 1;
    int nameP2 = inFileName.length() - nameP1 - 4;
    string outFileName = inFileName.substr(nameP1, nameP2);

    ifstream input;
    input.open(argv[1]);
    string fileLine;
    while(getline(input, fileLine)){
        string binaryLine = parse(fileLine);

    }


    return 0;
}

