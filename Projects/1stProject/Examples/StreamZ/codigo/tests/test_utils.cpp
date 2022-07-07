#include "utils.h"

TEST_CASE("Utilities", "[utils]") {
    REQUIRE(utils::itos(123L) == "123");
    REQUIRE(utils::itos(539678576738205678L) == "539678576738205678");
}

TEST_CASE("Utilities: URL-encoding", "[utils-url]") {
    REQUIRE(utils::urlencode("Um pão e uma bênção") == "Um%20p%C3%A3o%20e%20uma%20b%C3%AAn%C3%A7%C3%A3o");
    std::vector<std::string> v = {
        "Um pão e uma bênção"
    };
    for(const std::string &s:v)
        REQUIRE(utils::urldecode(utils::urlencode(s)) == s);
}

int RandomNumber() { return (std::rand()%1000); }

TEST_CASE("Utilities: mergesort", "[utils-mergesort]") {
    for(size_t i = 1; i < 1000; ++i){
        std::vector<int> v1(i);
        std::generate(v1.begin(), v1.end(), RandomNumber);
        std::vector<int> v2 = v1;
        std::sort(v1.begin(), v1.end());
        utils::mergesort(v2);
        REQUIRE(v1 == v2);
    }
}
