//
// Created by Caleb Moore on 2/3/21.
//

#include "DSString.h"
//*****GO TO .h FILE FOR COMMENTS ABOUT FUNCTIONS******

DSString::DSString(const DSString& m) {
    word = new char[strlen(m.word) + 1];
    strcpy(word, m.word);
}

DSString::DSString(){
    word = nullptr;
}

DSString::DSString(const char * s){
    word = new char[strlen(s) + 1];
    strcpy(word, s);
}

DSString& DSString::operator=(const DSString& c){
    if(word != nullptr){
        delete[] word;
    }
    word = new char[strlen(c.word) + 1];
    strcpy(word, c.word);
    return *this;
}

DSString::~DSString(){
    if(word != nullptr){
        delete[] word;
    }
}

DSString &DSString::operator=(const char * c){
    if(word != nullptr){
        delete[] word;
    }
    word = new char[strlen(c) + 1];
    strcpy(word, c);
    return *this;
}

DSString DSString::operator+(const DSString & n){
    DSString temp (word);
    strcat(temp.word, n.word);
    return temp;
}

std::ostream &operator<<(std::ostream & output, const DSString & s){
    output << s.word;
    return output;
}

bool DSString::operator==(const DSString & s) const{
    if(strcmp(word, s.word) == 0){
        return true;
    }
    return false;
}

int DSString::getLength(){
    return strlen(word);
}

bool DSString::operator>(const DSString & s) const{
    if(strlen(word) > strlen(s.word)){
        return true;
    }
    return false;
}

bool DSString::operator<(const DSString & s) const{
    if(strlen(word) < strlen(s.word)){
        return true;
    }
    return false;
}

char &DSString::operator[](const int p){
    return word[p];
}

char* DSString::c_str(){
    return word;
}

//I found help for this one on a stack overflow page on duplicating char*
DSString DSString::substring(int start, int numChars){
    char t[numChars + 1];
    memcpy(t, &word[start], numChars);
    t[numChars] = '\0';
    return t;
}

bool DSString::operator==(const char *& s) const {
    if(strcmp(word, s) == 0){
        return true;
    }
    return false;
}

DSString DSString::operator+(const char *& n) {
    DSString temp (word);
    strcat(temp.word, n);
    return DSString();
}

