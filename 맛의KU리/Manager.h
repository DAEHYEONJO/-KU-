#pragma once
#include "User.h"
class Manager
{
public:
	vector<User> user;
	void signUp();
	void logIn();
	void mainMenu();
	void addRestaurant();
	void searchRestaurant();

	Manager();
	~Manager();
};

