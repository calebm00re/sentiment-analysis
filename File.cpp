//
// Created by Caleb Moore on 2/1/21.
//

#include "File.h"
#include "Tweet.h"


File::File(){
    //this should be a safe initialization so it will not come up in the important words ever since it is only one character
    DSString* t = new DSString(" ");
    //add an empty spot to just ensure it doesnt start empty
    key_words.push_back(t);
    count.push_back(0);
}

//read in the pre determined sentiment tweets and analyze them
void File::fill_tweets(DSString training){
    //open file of tweets to train of frequent words
    std::ifstream input;
    input.open(training.c_str());

    //make sure the file opens
    if(!input) {
        std::cout << "input file failed to open" << std::endl;
    }

    //put words from the title out of the way since they are unnecessary now and declare useful variables
    char* temp = new char[50];
    input.getline(temp, 50, '\n');
    int endIt = 0;
    DSString pos = "4";
    int repeat_count = 0;

    //traverse what is left in the file
    while(!input.eof()){
        //make temporary buffers for incoming tweet elements
        char* temp_sentiment = new char[2];
        char* temp_ID = new char[12];
        char* temp_comment = new char[1000];
        char* nothing = new char[30];

        //store char* buffers full of incoming tweet elements
        input.getline(temp_sentiment, 2, ',');
        input.getline(temp_ID, 12, ',');
        input.getline(nothing, 30, ',');
        input.getline(nothing, 30, ',');
        input.getline(nothing, 30, ',');
        input.getline(temp_comment, 1000, '\n');

        //put things from buffer into their respective DSString objects
        DSString sentiment(temp_sentiment);
        DSString ID(temp_ID);
        DSString comment(temp_comment);

        //make a pointer to the tweet
        Tweet* tweet = new Tweet(sentiment, ID, comment);

        //parse out the different words in each tweet
        tweet->separate_tweet();

        //check for repeated words and add to key words if its new
        for(int t = 0; t < (tweet->get_size()); ++t){
            DSString *temp_word = new DSString((*(tweet)).at(t));

            //go through current key words
            for(int k = 0; k < key_words.size(); ++k){
                if ((*(key_words[k])) == (*temp_word)) {


                    if (sentiment == pos) {
                        (count[k])++;
                    } else {
                        (count[k])--;
                    }
                    repeat_count++;
                }
            }
            //if the word is not already a key add it to the key words vector
            if(repeat_count == 0){
                key_words.push_back(temp_word);
                if(sentiment == pos){
                    count.push_back(1);
                }
                else{
                    count.push_back(-1);
                }
            }
            repeat_count = 0;
        }
        //add the tweet to the known tweets    much later I have realized this is pointless and would not do this again in the future
        known_tweet_vec.push_back(tweet);
        endIt++;
        //end the reading in of tweets once the 20k has been hit to maximize analysis and minimize runtime
        if(endIt == 20000){
            break;
        }
    }
    input.close();
}

//this function will eliminate key words that do not show up enough to be considered significant
void File::narrow_search() {
    for(int i = 0; i < count.size(); ++i){

        int test = count[i];
        //make sure tweet apears a net 5 times in either a pos or neg tweet
        if(test < 2 && test > -2){
            count.erase(count.begin() + i);
            key_words.erase(key_words.begin() + i);
            i--;
        }
    }
}

//go over the file to be analyzed and assign predicted sentiment values
void File::analyze(DSString testing) {

    //make the input stream
    std::ifstream input;
    input.open(testing.c_str());
    int endIt = 0;

    //make sure the file opened
    if(!input) {
        std::cout << "input file failed to open" << std::endl;
    }

    //put words from the title out of the way since they are unnecessary now
    char* temp = new char[50];
    input.getline(temp, 50, '\n');

    //traverse what is left in the file
    while(!input.eof()){
        //make temporary buffers for incoming tweet elements
        char* temp_ID = new char[12];
        char* temp_comment = new char[1000];
        char* nothing = new char[30];

        //store char* buffers full of incoming tweet elements
        input.getline(temp_ID, 12, ',');
        input.getline(nothing, 30, ',');
        input.getline(nothing, 30, ',');
        input.getline(nothing, 30, ',');
        input.getline(temp_comment, 1000, '\n');

        //put things from buffer into their respective DSString objects
        DSString ID(temp_ID);
        DSString comment(temp_comment);

        //make a pointer to the tweet
        Tweet* tweet = new Tweet(ID, comment);
        tweet->separate_tweet();

        //check for keywords in the tweet
        for(int t = 0; t < tweet->get_size(); ++t){
            DSString temp_word = tweet->at(t);

            //compare against known key words
            for(int k = 0; k < key_words.size(); ++k){
                if((*(key_words[k])) == temp_word){
                    tweet->add(count[k]);
                }
            }
        }

        //turn guess into sentiment prediction
        DSString pos("4");
        DSString neg("0");
        int num = tweet->get_idea();

        //assign the sentiment based on key words
        if(num > 0){
            tweet->set_sentiment(pos);
        }
        else if(num < 0){
            tweet->set_sentiment(neg);
        }
        //if no key words or the tweet seems to be neutral, assign a random sentiment
        else{
            int g = (rand() % 2);
            if(g == 0){
                tweet->set_sentiment(pos);
            }
            else{
                tweet->set_sentiment(neg);
            }
        }
        //add tweet to vector, this could just be a count in the future if revisited
        analyze_tweet_vec.push_back(tweet);
        endIt++;
        //end after looking and assigning 10k tweets their sentiment predictions
        if(endIt == 10000){
            break;
        }
    }
    input.close();
}

//check predicted sentiment against the actual and record how many were guessed correctly
void File::compare_guess(DSString compare) {
    std::ifstream input;
    input.open(compare.c_str());

    //make sure file opened correctly
    if(!input) {
        std::cout << "input file failed to open" << std::endl;
    }

    //put words from the title out of the way since they are unnecessary now
    char* temp = new char[50];
    input.getline(temp, 50, '\n');

    int i = 0;
    int max = analyze_tweet_vec.size();

    //traverse what is left in the file
    while(!input.eof()) {
        //make temporary buffers for incoming tweet elements
        char *temp_sentiment = new char[2];
        char *temp_ID = new char[12];

        //store them in their DSString objects
        input.getline(temp_sentiment, 2, ',');
        input.getline(temp_ID, 12, '\n');

        //compare the sentiments and add to correct count if correct or add ID to incorrect list if wrong
        DSString sentiment(temp_sentiment);
        if(((analyze_tweet_vec[i])->get_sentiment()) == sentiment){
            ++correct;
        }
        else{
            DSString* ID = new DSString(temp_ID);
            incorrectly_guessed.push_back(ID);
        }
        ++i;
        //end at the end of the guessed sentiment tweets
        if(i == max){
            break;
        }
    }
    input.close();
}

//output the accuracy and the IDs of the incorrect tweets to the output file
void File::print_final(DSString output_name) {
    std::ofstream output;

    output.open(output_name.c_str());

    //make sure a file was opened
    if(!output) {
        std::cout << "output file failed to open" << std::endl;
    }

    //send to opened output file
    int length = (analyze_tweet_vec.size());
    double accuracy = (double)correct / (double)length;
    output << std::fixed << std::setprecision(3) << accuracy << std::endl;

    for(int i = 0; i < (incorrectly_guessed.size()); ++i){
        output << (*(incorrectly_guessed[i])) << std::endl;
    }

}

//used for testing throughout the writing process
void File::printing() {
    std::cout << "the length of the training tweets is " << known_tweet_vec.size() << std::endl;
    std::cout << "the length of the key words is " << key_words.size() << std::endl;
    std::cout << "the length of analyze tweets is " << analyze_tweet_vec.size() << std::endl;
    std::cout << "the number correct is " << correct << std::endl;
    std::cout << "the number of incorrect is " << incorrectly_guessed.size() << std::endl;
}
