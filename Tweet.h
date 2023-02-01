//
// Created by Caleb Moore on 2/1/21.
//

#ifndef INC_21S_PA01_TWEET_H
#define INC_21S_PA01_TWEET_H
#include "DSString.h"
#include <vector>

class Tweet{
private:
    //private variables
    DSString ID;
    DSString sentiment;
    DSString comment;
    std::vector<DSString*> separate_words;
    int guess = 0;

public:

    //make constructor for learning tweets, all three parameters
    Tweet(DSString& new_sentiment,  DSString& new_ID,  DSString& new_comment);

    //make constructor for analyzing new tweets, two parameters
    Tweet(DSString& new_ID, DSString& new_comment);

    //getter for comment
    DSString get_comment();

    //function to separate out a tweets comment into words
    void separate_tweet();

    //to return the word at a specific index in the comment
    DSString at(int p);

    //to return the size of a comment (how many words over four char long)
    int get_size();

    //return the sentiment of a tweet
    DSString get_sentiment();

    //add to the net guess of a tweet sentiment based on the words used and recognized in the tweet
    void add(int& a);

    //to return the net number guessed in adding up the significant words
    int get_idea();

    //to manually set the tweets sentiment
    void set_sentiment(DSString& g);




};
#endif //INC_21S_PA01_TWEET_H
