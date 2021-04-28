//
// Created by Kevin Leong on 4/27/21.
//
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include "stdlib.h"

using namespace std;

string cInstruction(string line, map<string, string> &comp, map<string, string> &dest, map<string, string> &jump){
    string binStr = "111";

    string preCheck;
    int mid;
    char checkType;
    for(int i = 0; i < line.length(); ++i){
        if(!isalpha(line[i])){
            checkType = line[i];
            mid = i;
            break;
        } else {
            preCheck += line[i];
        }
    }

    string postCheck = line.substr(mid + 1, line.find_last_of('\\'));

    if(checkType == '='){
        binStr += comp[postCheck];
        binStr += dest[preCheck];
        binStr += "000";
    } else if(checkType == ';'){

    }

    return binStr;

}

string aInstruction(int integer){
    string binStr;

    while(integer > 0){
        string binPart;
        int intBinPart = (integer % 2);
        binStr.append(to_string(intBinPart));

        integer /= 2;
    }

    while(binStr.length() < 16){
        binStr.append("0");
    }

    reverse(binStr.begin(), binStr.end());

    return binStr;

}

string parse(string line, map<string, string> &comp, map<string, string> &dest, map<string, string> &jump, map<string, int> &standard){
    string binary;

    if(line[0] == '/' || line.length() <= 2){
        return "";
    }

    //Normalize lines
    line = line.substr(0, line.length() - 1);


    //A instruction
    if (line[0] == '@') {
        string passStr;
        for(int i = 1; i < line.length(); ++i){
            if(isnumber(line[i])){
                passStr += line[i];
            }
        }
        if(passStr.length() == 0){
            string checkMap = line.substr(1, line.length() - 1);
            binary = aInstruction(standard[checkMap]);
        } else{
            binary = aInstruction(stoi(passStr));
        }
    } else {
        binary = cInstruction(line,comp, dest, jump);
    }

    cout << binary << endl;
    return binary;
}


int main(int argc, char** argv){

    map<string, string> comp;
    map<string, string> dest;
    map<string, string> jump;
    map<string, int> standard;

    makeMaps(comp, dest, jump, standard);

    string inFileName = argv[1];
    int nameP1 = inFileName.find_last_of('/') + 1;
    int nameP2 = inFileName.length() - nameP1 - 4;
    string outFileName = inFileName.substr(nameP1, nameP2);

    ifstream input;
    input.open(argv[1]);
    string fileLine;
    while(getline(input, fileLine)){
        string binaryLine = parse(fileLine, comp, dest, jump, standard);
    }


    return 0;
}

