#pragma once

#include<iostream>
using namespace std;
#include<string>

// class used to store current logged-in user's data
class userSingleton {
	static userSingleton s;
	string login;
	string password;
	string name;
	string surname;
	string position;	// stores the logged-in user's position in the company
	bool loggedIn;	// stores login status: 1 - user logged-in, 0 - user not logged-in
	userSingleton(string l = "", string p = "") : login(l), password(p), loggedIn(0) { } // konstr. domyslny - prywatny
	userSingleton(const userSingleton&); // copying constructor (private)
	userSingleton& operator=(userSingleton&); // assignment operator (private)
public:
	// method for getting a reference to the current user instance
	static userSingleton& instance() { return s; }

	// getters for user's data
	string getLogin();
	string getPassword();
	string getName();
	string getSurname();
	string getPosition();
	bool getStatus();

	// setters for user's data
	void setLogin(string l);
	void setPassword(string p);
	void setStatus(bool s);
	void setName(string n);
	void setSurname(string s);
	void setPosition(string p);
};