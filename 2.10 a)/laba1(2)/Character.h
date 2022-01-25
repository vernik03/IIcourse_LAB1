#include <iostream>
#include <windows.h>
#include <regex>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>
#pragma once

using namespace std;

class Character
{
public:
	unsigned int GetId();
	string GetName();	
	void SetId(string str);
	void SetName(string str);

private:
	unsigned int id;
	string name;
};

