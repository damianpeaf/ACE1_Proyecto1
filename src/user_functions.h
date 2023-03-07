#ifndef USER_FUNCTIONS_H
#define USER_FUNCTIONS_H

#include <Arduino.h>
#include "user.h"
#include "eeprom_manager.h"

char characters[] = { '7','8','9','C','4','5','6','D','1','2','3','E','A','0','B','F' };

User login_user(String nickname, String password);
String get_user_token();

User login_user(String nickname, String password){

    for(int i = 0; i < get_user_count(); i++){
        User user = get_user(i);
        if(user.validate_credentials(nickname, password)){
            return user;
        }
    }

    return User();
}

String get_user_token(){

    String token = "";

    for(int i = 0; i < 6; i++){
       token += characters[random(0, sizeof(characters)-1)];
    }

    return token;

}

#endif