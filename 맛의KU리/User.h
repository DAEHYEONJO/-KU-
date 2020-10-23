#pragma once
#include <iostream>
#include <string>
#include "Restaurant.h"
using namespace std;

class User
{
public:
	string id;
	string pw;
	vector<Restaurant> restaurant;
	User();
	~User();
};

