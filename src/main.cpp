#include <iostream>
#include "source/company.h"

static string OCONNOR = R"(
          ___   ____ ___  _   _ _   _  ___  ____       _    ___ ____  ____   ___  ____ _____ ____
         / _ \ / ___/ _ \| \ | | \ | |/ _ \|  _ \     / \  |_ _|  _ \|  _ \ / _ \|  _ \_   _/ ___|
        | | | | |  | | | |  \| |  \| | | | | |_) |   / _ \  | || |_) | |_) | | | | |_) || | \___ \
        | |_| | |__| |_| | |\  | |\  | |_| |  _ <   / ___ \ | ||  _ <|  __/| |_| |  _ < | |  ___) |
         \___/ \____\___/|_| \_|_| \_|\___/|_| \_\ /_/   \_\___|_| \_\_|    \___/|_| \_\|_| |____/
)";

int main() {

    try{
    Company OConnor = Company(OCONNOR);

    while (!showMenu(OConnor)){}

    cout << "\tThe Program will close. ";

    _getwch();
    }catch(const string &e){
        cout << e << endl << " Press Any Key... ";
        _getwch();
    }
    catch(...){
        cout << endl << "\tUnknown failure occurred. Possible memory corruption or uncaught Exception. " << endl << "Press Any Key to close this Program... ";
        _getwch();
    }
    return 0;
}

