#pragma once
#include "User.h"

class Manager
{
public:
	vector<User> user;
	User* current_user;
	int signUp();
	int logIn();
	void loginMenu();
	int mainMenu();
	void registerRestaurant();
	void ManageRestaurant();
	void searchRestaurant();
	void readInfoTextFile();
	static bool isQuit(string str);//static Ãß°¡
	bool isSpace(string str);
	Manager();
	~Manager();
};

