#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include "Restaurant.h"
using namespace std;

class User
{
public:
	string id;
	string pw;
	vector<Restaurant> restaurant;
	User();
	User(string id, string pw);
	~User();
};

