#include "time.h"

TEST_CASE("Time", "[Time]") {
    {
        std::stringstream ss;
        ss << Time("20191019_011132");
        std::string s; ss >> s;
        REQUIRE(s == "20191019_011132");
    }
}

TEST_CASE("Time input/output", "[Time]") {
    {
        std::stringstream ss;
        ss << Time("20191019_011132");
        Time t;
        std::string s; ss >> t;
        REQUIRE(t.format("%Y-%m-%d %H:%M:%S") == "2019-10-19 01:11:32");
    }
}
