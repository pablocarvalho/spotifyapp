#ifndef SESSION_H
#define SESSION_H

#include <QString>
#include "user.h"

class Session
{
public:    
    Session(User usr, QString token);
    Session();

    void setUser(User user);
    User& getUser();
    void setToken(QString token);

    QString getToken();
private:
    User user;
    QString token;
};

#endif // SESSION_H
