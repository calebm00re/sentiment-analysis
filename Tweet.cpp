//
// Created by Caleb Moore on 2/1/21.
//
#include "Tweet.h"

//tweet constructor with all three parameters
Tweet::Tweet(DSString& new_sentiment,  DSString& new_ID,  DSString& new_comment){
    ID = new_ID;
    sentiment = new_sentiment;
    comment = new_comment;
}

//comment getter
DSString Tweet::get_comment(){
    return comment;
}

//this one is a little jank but it separates out tweets and disreguards the last word in case of weird punctuation and such
void Tweet::separate_tweet(){
    //make variables for navigating the entire tweet
    int length = 0;
    int start = 0;
    //loop through the whole tweet
    for(int i = 0; i < comment.getLength(); ++i){
        //check for spaces
        if(comment[i] == ' '){
            //get rid of little words that are less likely to be impactful on the sentiment
            if(length > 4) {
                //add single words to their vectors
                if(start > 0) {
                    --length;
                }
                DSString *temp = new DSString(comment.substring(start, length));
                separate_words.push_back(temp);
            }
            //increment important variables
            start = i + 1;
            length = 0;
        }
        ++length;
    }
}

//returns a word in the tweets comment word by word
DSString Tweet::at(int p){
    return *(separate_words.at(p));
}

//return the length of the tweets comment in number of words
int Tweet::get_size(){
    return separate_words.size();
}

//tweets sentiment getter
DSString Tweet::get_sentiment(){
    return sentiment;
}

//tweet constructor for the analyzing tweets that do not have a sentiment until assigned
Tweet::Tweet(DSString &new_ID, DSString &new_comment) {
    ID = new_ID;
    comment = new_comment;
}

//for adding or subtracting from a net sentiment analyzer
void Tweet::add(int& a) {
    guess += a;
}

//to return the net number made from analyzing words in the tweet
int Tweet::get_idea() {
    return guess;
}

//to manually set the sentiment after guessing it
void Tweet::set_sentiment(DSString& g) {
    sentiment = g;
}


