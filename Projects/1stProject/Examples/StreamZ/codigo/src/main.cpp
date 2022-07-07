#include "app.h"

#ifdef _WIN32
    #include <windows.h>
    #include <cstdio>
    #define ENABLEPT()  SetConsoleOutputCP(CP_UTF8)
#else
    #define ENABLEPT()
#endif

int main(){
    try {
        ENABLEPT();
        App app("data/","managers/managers.txt",
                        "drivers/drivers.txt",
                        "clients/clients.txt",
                        "brands/brands.txt",
                        "trucks/trucks.txt",
                        "services/services.txt",
                        "workshops/workshops.txt");
        app.start();
    } catch (std::ios_base::failure &fail) {
        App::error(fail.what());
        return 1;
    } catch (std::exception &ex) {
        App::error(ex.what());
        return 1;
    }
    return 0;
}
