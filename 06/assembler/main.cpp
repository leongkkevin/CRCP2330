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
        if(!isalpha(line[i]) && !isnumber(line[i])){
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
        binStr += comp[preCheck];
        binStr += "000";
        binStr += jump[postCheck];
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

    if(line[0] == '/' || line.length() <= 2 || line[0] == '('){
        return "";
    }

    //Normalize lines
    line = line.substr(0, line.length() - 1);
    if(line[0] == ' '){
        int i = 0;
        while(line[i] == ' '){
            ++i;
        }

        line = line.substr(i, line.length());
    }
    int commCheck;
    for(int i = 0; i < line.length(); ++i){
        if(line[i] == ' '){
            commCheck = i;
           break;
        }
    }
    line = line.substr(0, commCheck);

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

    return binary;
}

void makeMaps(map<string, string> &comp, map<string, string> &dest, map<string, string> &jump,
              map<string, int> &standard){
    comp["0"] = "0101010";
    comp["-1"] = "0111010";
    comp["D"] = "0001100";
    comp["A"] = "0110000";
    comp["!D"] = "0001101";
    comp["!A"] = "0110001";
    comp["-D"] = "0001111";
    comp["-A"] = "0110011";
    comp["D+1"] = "0011111";
    comp["A+!"] = "0110111";
    comp["D-1"] = "0001110";
    comp["A-1"] = "0110010";
    comp["D+A"] = "0000010";
    comp["D-A"] = "0010011";
    comp["A-D"] = "0000111";
    comp["D&A"] = "0000000";
    comp["D|A"] = "0010101";
    comp["M"] = "1110000";
    comp["!M"] = "1110001";
    comp["-M"] = "1110011";
    comp["M+1"] = "1110111";
    comp["M-1"] = "1110010";
    comp["D+M"] = "1000010";
    comp["D-M"] = "1010011";
    comp["M-D"] = "1000111";
    comp["D&M"] = "1000000";
    comp["D|M"] = "1010101";

    dest["null"] = "000";
    dest["M"] = "001";
    dest["D"] = "010";
    dest["A"] = "100";
    dest["MD"] = "011";
    dest["AM"] = "101";
    dest["AD"] = "110";
    dest["AMD"] = "111";

    jump["null"] = "000";
    jump["JGT"] = "001";
    jump["JEQ"] = "010";
    jump["JGE"] = "011";
    jump["JLT"] = "100";
    jump["JNE"] = "101";
    jump["JLE"] = "110";
    jump["JMP"] = "111";

    standard["SP"] = 0;
    standard["LCL"] = 1;
    standard["ARG"] = 2;
    standard["THIS"] = 3;
    standard["THAT"] = 4;
    standard["SCREEN"] = 16384;
    standard["KBD"] = 24576;
}

int main(int argc, char** argv){

    map<string, string> comp;
    map<string, string> dest;
    map<string, string> jump;
    map<string, int> standard;

    makeMaps(comp, dest, jump, standard);

    ifstream fin(argv[argc-1]);
    string file = argv[argc-1];
    int dotLocation = file.find(".",0);
    string hackFile = file.substr(0,dotLocation)+".hack";
    ofstream fout(hackFile.c_str());

    string fileLine;
    while(getline(fin, fileLine)){
        string binaryLine = parse(fileLine, comp, dest, jump, standard);
        if(binaryLine.length() > 0){
            fout << binaryLine << endl;
        }
    }


    return 0;
}

