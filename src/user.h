#ifndef USER_H
#define USER_H

struct User {
    char name[16];
    char nickname[10];
    char password[10];
    int credits;
    unsigned int address;
    bool isAdmin;

    bool validate_credentials(String nickname, String password) {
        return (strcmp(this->nickname, nickname.c_str()) == 0) && (strcmp(this->password, password.c_str()) == 0);
    }

    bool is_valid() {
        return strcmp(this->nickname, "") != 0;
    }
};

#endif