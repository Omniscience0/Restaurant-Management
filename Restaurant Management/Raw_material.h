#pragma once
#include <iostream>
using namespace std;
#include <string>

class Raw_material { //Ô­²ÄÁÏ
public:
	Raw_material() {
		this->R_name = "";
		this->R_price = 0.0;
	}

	Raw_material(string name, double price) {
		R_name = name;
		R_price = price;
	}
	void show_info() {
		cout << "Raw Material name: " << R_name << " Price: " << R_price << endl;
	}

	string R_name;
	double R_price;
};