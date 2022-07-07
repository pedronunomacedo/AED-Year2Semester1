#include "service.h"

TEST_CASE("Service", "[service]") {
    Client c("Rosvaldo de Albuquerque e Sousa",
             PhoneNumber("(+351) 91 234 56 78"),
             "rosvaldoas", "aminhapassworderosvaldo",
             Address("Rua das Oliveiras, 25", "4020-318", "BACIAS", "Trás-os-Montes", "Portugal"),
             VAT("0123456789ABCDE")
            );

    Service s(c.get_username(), c, c,
              "wooden tables", 5000, 0,
              Time("20190125_124322"), Time("20190203_120001"),
              Address("Rua das Oliveiras, 25", "4020-318", "BACIAS", "Trás-os-Montes", "Portugal"),
              Address("Rua das Margaridas, 396", "4020-318", "BACIAS", "Trás-os-Montes", "Portugal"),
              new Cargo(1000, Cargo::Type::Normal, Cargo::DangerLevel::None, 1000, std::pair<float,float>(-50,100)));
}
