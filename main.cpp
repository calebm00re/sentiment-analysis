#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include "File.h"
#include "DSString.h"

int main(int argc, char** data) {
    //run the sentiment analysis with 4 command line arguments
    if (argc == 5){

        //make a file object and run the tweet files through it in stages to analyze recurring words and assign sentiments accordingly
        File file;
        file.fill_tweets(data[1]);
        file.narrow_search();
        file.analyze(data[2]);
        file.compare_guess(data[3]);
        file.print_final(data[4]);

    }
    //run the catch with zero
    else if(argc == 1){
        Catch::Session().run();
    }
    //otherwise, ask for the correct number
    else{
        std::cout << "please give the correct number of command line arguments" << std::endl;
    }
    return 0;

}
