#include "phonenumber.h"

TEST_CASE("Phone number", "[phonenumber]") {
    REQUIRE_NOTHROW(PhoneNumber("+"));
    REQUIRE_NOTHROW(PhoneNumber(" "));
    REQUIRE_NOTHROW(PhoneNumber("(+351) 912 345 678"));
    REQUIRE_THROWS_AS(PhoneNumber("+351ç"), PhoneNumber::InvalidPhoneNumber);
}

TEST_CASE("Phone number input/output", "[phonenumber-io]") {
    PhoneNumber p("(+351) 912 345 678");
    std::stringstream ss; ss << p << std::endl;
    PhoneNumber q;
    ss >> q;
    REQUIRE(q == p);
}
