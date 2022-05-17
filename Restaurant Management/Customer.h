#pragma once
#include <iostream>
using namespace std;
#include <string>
#include "Raw_material.h"
#include "Dishes.h"
#include "Material.h"
//#include "Worker.h"

class Customer { //¹Ë¿Í
public:

	virtual void show_info() = 0;

	void show_Menu() {
		cout << "Please input your choice: " << endl;
		cout << "1. View the Menu." << endl;
		cout << "2. Take order." << endl;
		cout << "3. Check out." << endl;
	}

	void C_order();

	bool Dish_check(int Dish_id) {
		for (int i = 0; i < Dish_num; i++) {
			if (this->D_array[i].D_num = Dish_id) {
				cout << "You have already order the dish" << endl;
				return false;
			}
		}
		return true;
	}

	virtual double check_out() = 0;

	virtual double profit() = 0;

	int is_Exist(int Dish_id);

	string C_name;
	string C_gender;
	string C_phone;
	Dishes* D_array;
	int Dish_num;
	int Dep_id;
};
void Customer::C_order() {
	int Dish_num;
	int Dish_id;
	Worker* worker = NULL;
	cout << "Please input the numbers of your dishes: " << endl;
	cin >> Dish_num;
	if (Dish_num > 0) {
		for (int i = 0; i < Dish_num; i++) {
			cout << "Please input your ordered dish:" << endl;
			cin >> Dish_id;
			if (is_Exist(Dish_id) != -1 && Dish_check(Dish_id)) {
				this->D_array[i] = worker->Dish_array[is_Exist(Dish_id)];
			}
			else {
				cout << "You have failed!" << endl;
			}
		}
	}
	else {
		cout << "Please input anthor" << endl;
	}

}

int Customer::is_Exist(int Dish_id) {
	Worker* worker = NULL;
	for (int i = 0; i < worker->m_DishNum; i++) {
		if (worker->Dish_array[i].D_num == Dish_id)
			return i;
	}
	return -1;
}


class Vip_Cust : public Customer {
public:

	Vip_Cust(string name, string gender, string phone, int dep_id) {
		this->C_name = name;
		this->C_gender = gender;
		this->C_phone = phone;
		this->Dep_id = dep_id;
		this->D_array = NULL;
	}

	virtual void show_info() {
		cout << "Name: " << C_name << " Gender: " << C_gender << " Phone Number: " << C_phone << endl;
	}

	virtual double check_out() {
		double sum = 0;
		for (int i = 0; i < this->Dish_num; i++) {
			sum += this->D_array[i].D_price;
		}
		return sum * 0.7;
	}

	virtual double profit() {
		double Raw_Cost = 0;
		for (int i = 0; i < this->Dish_num; i++) {
			Raw_Cost += this->D_array[i].D_make.R_price;
		}
		return this->check_out() - Raw_Cost;
	}

};

class Member_Cust : public Customer {
public:

	Member_Cust(string name, string gender, string phone, int dep_id) {
		this->C_name = name;
		this->C_gender = gender;
		this->C_phone = phone;
		this->Dep_id = dep_id;
		this->D_array = NULL;
	}

	virtual void show_info() {
		cout << "Name: " << C_name << " Gender: " << C_gender << " Phone Number: " << C_phone << endl;
	}

	virtual double check_out() {
		double sum = 0;
		for (int i = 0; i < this->Dish_num; i++) {
			sum += this->D_array[i].D_price;
		}
		return sum * 0.8;
	}

	virtual double profit() {
		double Raw_Cost = 0;
		for (int i = 0; i < this->Dish_num; i++) {
			Raw_Cost += this->D_array[i].D_make.R_price;
		}
		return this->check_out() - Raw_Cost;
	}

};

class Ordinary_Cust : public Customer {
public:

	Ordinary_Cust(string name, string gender, string phone, int dep_id) {
		this->C_name = name;
		this->C_gender = gender;
		this->C_phone = phone;
		this->Dep_id = dep_id;
		this->D_array = NULL;
	}

	virtual void show_info() {
		cout << "Name: " << C_name << " Gender: " << C_gender << " Phone Number: " << C_phone << endl;
	}

	virtual double check_out() {
		double sum = 0;
		for (int i = 0; i < this->Dish_num; i++) {
			sum += this->D_array[i].D_price;
		}
		return sum;
	}

	virtual double profit() {
		double Raw_Cost = 0;
		for (int i = 0; i < this->Dish_num; i++) {
			Raw_Cost += this->D_array[i].D_make.R_price;
		}
		return this->check_out() - Raw_Cost;
	}

};
