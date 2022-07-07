#include "currency.h"

TEST_CASE("Currency", "[currency]") {
    {
        (Currency)620.33;
    }
    {
        Currency c(620);
    }
}

TEST_CASE("Currency input/output", "[currency-io]") {
    {
        Currency c(620.33);
        std::stringstream ss;
        ss << c;
        Currency d;
        ss >> d;
        REQUIRE(d == Currency(620.33));
    }
    {
        for(long long int i = -10000; i <= 10000; ++i){
            std::stringstream ss1, ss2;
            ss1 << Currency(double(i)/100.0L);
            ss2 << std::setprecision(2) << std::fixed << double(i)/100.0L;
            REQUIRE(ss1.str() == ss2.str());
        }
    }
}
