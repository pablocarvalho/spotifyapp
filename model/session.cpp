#include "session.h"

Session::Session(User usr, QString token)
{

    user = usr;
    this->token = token;

}

Session::Session(){

}

void Session::setUser(User user){
    this->user = user;
}

User& Session::getUser(){
    return user;
}

void Session::setToken(QString token){
    this->token = token;
}

QString Session::getToken()
{
    return token;
}
