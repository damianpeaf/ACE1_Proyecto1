#ifndef USER_H
#define USER_H

struct User {
    char name[16];
    char nickname[10];
    char password[10];
    int credits;
    unsigned int address;
    bool isAdmin;
};

#endif