#ifndef WINE_H__
#define WINE_H__

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
#include <sstream>

using namespace std;

class Wine
{
	string name;
	int vintage, rating;
	double price;
	string type;

	public : 
	Wine(string nameX, int vintageX, int ratingX, double priceX, string typeX);

	string getName();
	int getVintage();
	int getRating();
	double getPrice();
	string getType();
};

#endif // WINE_H__