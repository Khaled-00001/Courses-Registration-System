#ifndef ADMIN_H
#define ADMIN_H

#include <string>
using namespace std;

class Admin {
private:
    string username;
    string password;

public:
    Admin();
    Admin(string user, string pass);

    void setUsername(string user);
    string getUsername();

    void setPassword(string pass);
    string getPassword();

    bool login(string user, string pass);
};

#endif
