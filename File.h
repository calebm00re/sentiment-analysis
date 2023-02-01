//
// Created by Caleb Moore on 2/1/21.
//

#ifndef INC_21S_PA01_FILE_H
#define INC_21S_PA01_FILE_H
#include "Tweet.h"
#include <vector>
#include "DSString.h"
#include <iostream>
#include <fstream>
#include <iomanip>


class File{
private:
    //make private variables
    std::vector<Tweet*> known_tweet_vec;
    std::vector<Tweet*> analyze_tweet_vec;
    std::vector<DSString*> key_words;
    std::vector<int> count;
    std::vector<DSString*> incorrectly_guessed;
    int correct;


public:
    //default constructor
    File();

    //populate tweet vector
    void fill_tweets(DSString training);

    //get rid of one-off or insignificant words
    void narrow_search();

    //take in the testing data set and store their tweet vec
    void analyze(DSString testing);

    //used to look at the sentiment known in comparison with the guess and count those correct
    void compare_guess(DSString compare);

    //used to send out the final to the output file
    void print_final(DSString output_name);

    //used in testing and developing but not in the actual execution of the project
    void printing();


};
#endif //INC_21S_PA01_FILE_H
