#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#define Customer_File "Customer.txt"
#include "Raw_material.h"
#include "Dishes.h"
#include "Customer.h"
#include "Worker.h"
#include "Material.h"
#include "Menu.h"

class Cust_info : public Worker {
public:
	Cust_info() {

		ifstream ifs; //创建文件
		ifs.open(Customer_File, ios::in);

		if (!ifs.is_open()) { //文件未创建
			this->m_CustNum = 0;
			this->Cust_array = NULL;
			m_CustIsEmpty = true;
			ifs.close();
			return;
		}

		char ch; ifs >> ch; //文件存在并且没有记录
		if (ifs.eof()) { //当前为尾部
			this->m_CustNum = 0;
			this->m_CustIsEmpty = true;
			this->Cust_array = NULL;
			ifs.close();
			return;
		}

		int num = this->get_Num(); // 文件存在且不为空
		this->m_CustNum = num;

		//开辟空间
		this->Cust_array = new Customer * [this->m_CustNum];
		this->init_value();
	}

	virtual int get_Num() {
		ifstream ifs;
		ifs.open(Customer_File, ios::in);

		string name;
		string gender;
		string phoneNum;
		int Dep_id;
		int num = 0;

		while (ifs >> name && ifs >> gender && ifs >> phoneNum && ifs >> Dep_id) {
			num++;
		}
		return num;
	}

	virtual void init_value() {
		ifstream ifs;
		ifs.open(Customer_File, ios::in);

		string name;
		string gender;
		string phoneNum;
		int Dep_id;

		int index = 0;
		while (ifs >> name && ifs >> gender && ifs >> phoneNum && ifs >> Dep_id) {
			Customer* Cust = NULL;
			if (Dep_id == 1) {
				Cust = new Ordinary_Cust(name, gender, phoneNum, Dep_id);
			}
			else if (Dep_id == 2) {
				Cust = new Member_Cust(name, gender, phoneNum, Dep_id);
			}
			else if (Dep_id == 3) {
				Cust = new Vip_Cust(name, gender, phoneNum, Dep_id);
			}
			this->Cust_array[index] = Cust;
			++index;
		}
		ifs.close();
	}

	virtual void save() {
		ofstream ofs;
		ofs.open(Customer_File, ios::out);

		for (int i = 0; i < this->m_CustNum; i++) {
			ofs << this->Cust_array[i]->C_name << " "
				<< this->Cust_array[i]->C_gender << " "
				<< this->Cust_array[i]->C_phone << " "
				<< this->Cust_array[i]->Dep_id << endl;
		}
		ofs.close();
	}

	virtual void Browse() {

		for (int i = 0; i < this->get_Num(); ++i) {
			this->Dish_array[i].show_info();
		}
	}

	virtual void Add() {
		int newSize = this->m_CustNum + 1;
		Customer** newSpace = new Customer * [newSize];

		if (this->Cust_array != NULL) {
			for (int i = 0; i < this->m_CustNum; i++) {
				newSpace[i] = this->Cust_array[i];
			}
		}

		string name;
		int input;
		string gender;
		string phone;
		int dep_id;

		cout << "Please input the Customer name:" << endl;
		cin >> name;

		cout << "Please input the Customer Gender:" << endl;
		cout << "1. Male" << endl;
		cout << "2. Female" << endl;
		cin >> input;
		gender = input == 1 ? "男" : "女";

		cout << "Please input the Phone Number:" << endl;
		cin >> phone;

		cout << "Please input Customer type:" << endl;
		cout << "1. Ordinary Customer" << endl;
		cout << "2. Member Customer" << endl;
		cout << "3. Vip Customer" << endl;
		cin >> dep_id;

		Customer* Cust = NULL;
		switch (dep_id)
		{
		case 1:
			Cust = new Ordinary_Cust(name, gender, phone, dep_id);
			break;
		case 2:
			Cust = new Member_Cust(name, gender, phone, dep_id);
			break;
		case 3:
			Cust = new Vip_Cust(name, gender, phone, dep_id);
			break;
		default:
			break;
		}
		newSpace[this->m_CustNum] = Cust;

		delete[] this->Cust_array;
		this->Cust_array = newSpace;
		this->m_CustNum = newSize;
		this->save();
		cout << "You have successfully added a Customer!" << endl;
	}

	virtual void Amend() {
		string name;
		cout << "Please enter the Customer name you want to modify: " << endl;
		cin >> name;

		for (int i = 0; i < this->m_CustNum; ++i) {
			if (Cust_array[i]->C_name == name) {
				string new_name;
				int input;
				string new_gender;
				string new_phone;
				int new_dep_id;

				cout << "Please enter new Customer name: " << endl;
				cin >> name;
				this->Cust_array[i]->C_name = new_name;

				cout << "Please enter new Customer gender: " << endl;
				cout << "1. Male" << endl;
				cout << "2. Female" << endl;
				cin >> input;
				new_gender = input == 1 ? "男" : "女";
				this->Cust_array[i]->C_gender = new_gender;

				cout << "Please enter new Phone Number: " << endl;
				cin >> new_phone;
				this->Cust_array[i]->C_phone = new_phone;

				cout << "Please enter new Type of Customer: " << endl;
				cout << "1. Ordinary Customer" << endl;
				cout << "2. Member Customer" << endl;
				cout << "3. Vip Customer" << endl;
				cin >> new_dep_id;

				Customer* Cust = NULL;
				switch (new_dep_id)
				{
				case 1:
					Cust = new Ordinary_Cust(new_name, new_gender, new_phone, new_dep_id);
					break;
				case 2:
					Cust = new Member_Cust(new_name, new_gender, new_phone, new_dep_id);
					break;
				case 3:
					Cust = new Vip_Cust(new_name, new_gender, new_phone, new_dep_id);
					break;
				default:
					break;
				}

				this->Cust_array[i] = Cust;
				this->save();
			}
			else {
				cout << "No Customer you entered!" << endl;
			}
		}
	}

	virtual void Delete() {
		string name;
		int deleteNum = 0;
		cout << "Please enter the Customer name you want to delete: " << endl;
		cin >> name;

		for (int i = 0; i < this->m_CustNum; ++i) {
			if (Cust_array[i]->C_name == name) {
				deleteNum = i;
			}
		}
		for (int i = deleteNum; i < this->m_CustNum; i++) {

			this->Cust_array[i] = this->Cust_array[i + 1]; //覆盖

		}
		this->m_RawNum--;
		this->save();

		cout << "Successful deletion!" << endl;
	}

	virtual void show_Menu() {
		cout << "Please input your choice: " << endl;
		cout << "1. Browse the customer information ." << endl;
		cout << "2. Add a new customer." << endl;
		cout << "3. Amend customer information." << endl;
		cout << "4. Delete customer information." << endl;
	}

	virtual void research() {
		string name;
		cout << "Please enter the Customer name you want to research: " << endl;
		cin >> name;

		for (int i = 0; i < this->m_CustNum; ++i) {
			if (Cust_array[i]->C_name == name) {
				Cust_array[i]->show_info();
			}
			else {
				cout << "The Dish you are looking for do not exist!" << endl;
			}
		}
	}

	~Cust_info() {
		if (this->Cust_array != NULL) {
			delete[] this->Cust_array;
			this->m_CustNum = 0;
		}
	}
};