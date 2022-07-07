#include "person.h"

TEST_CASE("Person", "[person]") {
    REQUIRE_NOTHROW(
        Person("Rosvaldo de Albuquerque e Sousa",
               PhoneNumber("(+351) 91 234 56 78")
              )
    );
    REQUIRE_NOTHROW(
        Client("Rosvaldo de Albuquerque e Sousa",
               PhoneNumber("(+351) 91 234 56 78"),
               "rosvaldoas", "aminhapasswordrosvaldo",
               Address("Rua das Oliveiras, 25", "4020-318", "BACIAS", "Trás-os-Montes", "Portugal"),
               VAT("0123456789ABCDE")
              )
    );
    REQUIRE_NOTHROW(
        Manager("Rosvaldo de Albuquerque e Sousa",
                PhoneNumber("(+351) 91 234 56 78"),
                "rosvaldoas", "aminhapasswordrosvaldo",
                Address("Rua das Oliveiras, 25", "4020-318", "BACIAS", "Trás-os-Montes", "Portugal"),
                VAT("0123456789ABCDE"),
                Currency(1080.22)
              )
    );
    REQUIRE_NOTHROW(
        Driver("Rosvaldo de Albuquerque e Sousa",
               PhoneNumber("(+351) 91 234 56 78"),
               "rosvaldoas", "aminhapasswordrosvaldo",
               Address("Rua das Oliveiras, 25", "4020-318", "BACIAS", "Trás-os-Montes", "Portugal"),
               VAT("0123456789ABCDE"),
               Currency(1080.22)
              )
    );
}
