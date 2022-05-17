#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "Raw_material.h"

class Dishes { //dishes ²ËÆ·
public:

	Dishes() {
		this->D_num = 0;
		this->D_name = "";
		this->D_price = 0.0;
	}

	Dishes(int num, string name, double price, Raw_material make) {
		D_make = make;
		D_num = num;
		D_name = name;
		D_price = price;
	}

	void show_info() {
		cout << "Dish NO: " << D_num << " Dish name: " << D_name << " Price: " << D_price
			<< " Raw materials neede: " << D_make.R_name << endl;
	}

	Raw_material D_make;
	int D_num;
	string D_name;
	double D_price;
};