//
// Created by Caleb Moore on 2/11/21.
//
#include "catch.hpp"
#include "DSString.h"

using namespace std;

TEST_CASE("String class", "[DSString]"){
    //test assignment through multiple forms of construction
    SECTION("Equals Check") {
        //checks different forms of construction
        DSString one = "Testing";
        DSString two("secondary");
        DSString four;
        four = "Testing";

        REQUIRE_FALSE(one == two);
        REQUIRE(one == "Testing");
        REQUIRE(four == one);
    }
    //test + operator overload
    SECTION("+ Check"){
        DSString first = "good";
        DSString second = "morning";

        REQUIRE(first + second == "goodmorning");
        REQUIRE(first + "good" == "goodgood");
    }
    //test substring
    SECTION("Substring Check"){
        DSString whole = "Racecar";

        REQUIRE(whole.substring(0, 4) == "Race");
    }
    //test comparison operators
    SECTION("Comparison Check"){
        DSString shorter = "shortOne";
        DSString longer = "muchMuchLonger";

        REQUIRE(shorter < longer);
        REQUIRE_FALSE(shorter > longer);
    }
    //test the index-using char selector
    SECTION("[] Check"){
        DSString test = "index Testing";

        REQUIRE(test[0] == 'i');
        REQUIRE(test[5] == ' ');
        REQUIRE_FALSE(test[6] == 't');
        REQUIRE(test[6] == 'T');
    }
    //test the get length function
    SECTION("Length Check"){
        DSString testing_four = "four";
        DSString testing_seven = "buffalo";

        REQUIRE(testing_four.getLength() == 4);
        REQUIRE(testing_seven.getLength() == 7);
        REQUIRE_FALSE(testing_seven.getLength() == 0);
    }
    //test delete function
    SECTION("Delete Check"){
        DSString testing = "test";

        REQUIRE(testing == "test");
    }
}