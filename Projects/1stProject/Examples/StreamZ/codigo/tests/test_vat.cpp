#include "vat.h"

TEST_CASE("VAT", "[vat]"){
    REQUIRE_THROWS_AS(VAT("0123456789abcdef"), VAT::InvalidVAT);
    REQUIRE_NOTHROW(VAT("0123456789ABCDE"));
}

TEST_CASE("VAT input/output", "[vat-io]"){
    {
        VAT v("0123456789ABCDE");
        std::stringstream ss; ss << v;
        REQUIRE(ss.str() == "0123456789ABCDE");
    }
    {
        std::stringstream ss("0123456789ABCDE\n");
        VAT w;
        ss >> w;
        std::stringstream ss2; ss2 << w; REQUIRE(ss2.str() == "0123456789ABCDE");
    }
}
