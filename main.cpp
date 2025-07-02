
#include <iostream>
#include "LoginScreen.h"



int main()

{
    while (true) {
    
        if (!LoginScreen::showLoginScreen()) {
            break;
        }
    
    }

    system("pause>0");
    return 0;
}
