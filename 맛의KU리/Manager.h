#pragma once
#include "User.h"

class Manager
{
public:
	vector<User> user;
	User current_user;
	int signUp();
	int logIn();
	void loginMenu();
	int mainMenu();
	void registerRestaurant();
	void searchRestaurant();
	void readInfoTextFile();
	bool isQuit(string str);
	bool isSpace(string str);
	Manager();
	~Manager();
};

