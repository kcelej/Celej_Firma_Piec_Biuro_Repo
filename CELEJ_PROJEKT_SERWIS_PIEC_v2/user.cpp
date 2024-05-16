#include "stdafx.h"
#include "user.h"

// get current user's data
string userSingleton::getLogin() { return login; }
string userSingleton::getPassword() { return password; }
bool userSingleton::getStatus() { return loggedIn; }
string userSingleton::getName() { return name; }
string userSingleton::getSurname() { return surname; }
string userSingleton::getPosition() { return position;  }

// set current user's data
void userSingleton::setLogin(string l) { login = l; }
void userSingleton::setPassword(string p) { password = p; }
void userSingleton::setStatus(bool s) { loggedIn = s; }
void userSingleton::setName(string n) { name = n; }
void userSingleton::setSurname(string s) { surname = s; }
void userSingleton::setPosition(string p) { position = p; }

// create the current user as a single instance object
userSingleton userSingleton::s("", "");