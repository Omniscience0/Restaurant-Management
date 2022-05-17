#pragma once
#include <iostream>
using namespace std;
#include <string>
#define Material_File "Raw_Material.txt"
#define Menu_File "Menu.txt"
#define Customer_File "Customer.txt"
#include "Raw_material.h"
#include "Dishes.h"
#include <fstream>
#include "Customer.h"

class Worker {
public:
	//Worker(); //用文件保存 save

	virtual void init_value() = 0;

	virtual int get_Num() = 0;

	virtual void save() = 0;

	virtual void Browse() = 0;

	virtual void Add() = 0;

	virtual void Amend() = 0;

	virtual void Delete() = 0;

	virtual void show_Menu() = 0;

	virtual void research() = 0;

	//~Worker()

	Raw_material* raw_array;
	int m_RawNum;
	bool m_FileIsEmpty;

	Dishes* Dish_array;
	int m_DishNum;
	bool m_MenuIsEmpty;

	Customer** Cust_array;
	int m_CustNum;
	bool m_CustIsEmpty;
};

class Material : public Worker {
public:
	Material() {
		ifstream ifs; //创建文件
		ifs.open(Material_File, ios::in);

		if (!ifs.is_open()) { //文件未创建
			this->m_RawNum = 0;
			this->raw_array = NULL;
			m_FileIsEmpty = true;
			ifs.close();
			return;
		}

		char ch; ifs >> ch; //文件存在并且没有记录
		if (ifs.eof()) { //当前为尾部
			this->m_RawNum = 0;
			this->m_FileIsEmpty = true;
			this->raw_array = NULL;
			ifs.close();
			return;
		}

		int num = this->get_Num(); // 文件存在且不为空
		this->m_RawNum = num;

		//开辟空间
		this->raw_array = new Raw_material[this->m_RawNum];
		this->init_value();
	}

	virtual int get_Num() {
		ifstream ifs;
		ifs.open(Material_File, ios::in);

		double price;
		string name;
		int num = 0;

		while (ifs >> name && ifs >> price) {
			num++;
		}
		return num;
	}

	virtual void init_value() {
		ifstream ifs;
		ifs.open(Material_File, ios::in);

		double price;
		string name;

		int index = 0;
		while (ifs >> name && ifs >> price) {
			Raw_material material(name, price);
			this->raw_array[index] = material;
			++index;
		}
		ifs.close();
	}

	virtual void save() {
		ofstream ofs;
		ofs.open(Material_File, ios::out);

		for (int i = 0; i < this->m_RawNum; i++) {
			ofs << this->raw_array[i].R_name << " "
				<< this->raw_array[i].R_price << endl;
		}
		ofs.close();
	}

	virtual void Browse() {
		for (int i = 0; i < this->get_Num(); ++i) {
			this->raw_array[i].show_info();
		}
	}

	virtual void Add() {
		int newSize = this->m_RawNum + 1;
		Raw_material* newSpace = new Raw_material[newSize];

		if (this->raw_array != NULL) {
			for (int i = 0; i < this->m_RawNum; i++) {
				newSpace[i] = this->raw_array[i];
			}
		}

		string name;		//输入新数据
		double price;
		cout << "Please input the Raw material name" << endl;
		cin >> name;

		cout << "Please input the Raw material price" << endl;
		cin >> price;
		Raw_material R_M(name, price);

		newSpace[this->m_RawNum] = R_M;

		delete[] this->raw_array;
		this->raw_array = newSpace;
		this->m_RawNum = newSize;

		this->save();
		cout << "You have successfully added raw materials!" << endl;
	}

	virtual void Amend() {
		string name;
		cout << "Please enter the raw material name you want to modify: " << endl;
		cin >> name;

		for (int i = 0; i < this->m_RawNum; ++i) {
			if (raw_array[i].R_name == name) {
				string new_name;
				double new_price;

				cout << "Please enter new raw material name: " << endl;
				cin >> new_name;
				this->raw_array[i].R_name = new_name;

				cout << "Please enter new raw material price: " << endl;
				cin >> new_price;
				this->raw_array[i].R_name = new_price;

				this->save();
			}
			else {
				cout << "No raw materials you entered!" << endl;
			}
		}
	}

	virtual void Delete() {

		string name;
		int deleteNum = 0;
		cout << "Please enter the raw material name you want to delete: " << endl;
		cin >> name;

		for (int i = 0; i < this->m_RawNum; ++i) {
			if (raw_array[i].R_name == name) {
				deleteNum = i;
			}
		}
		for (int i = deleteNum; i < this->m_RawNum; i++) {

			this->raw_array[i] = this->raw_array[i + 1]; //覆盖

		}

		this->m_RawNum--;
		this->save();

		cout << "Successful deletion!" << endl;
	}

	virtual void show_Menu() {
		cout << "Please input your choice: " << endl;
		cout << "1. Browse the information of raw materials." << endl;
		cout << "2. Add a new raw material." << endl;
		cout << "3. Amend the raw material." << endl;
		cout << "4. Delete the raw maqterial." << endl;
	}

	virtual void research() {

		string name;
		cout << "Please enter the raw material name you want to research: " << endl;
		cin >> name;

		for (int i = 0; i < this->m_RawNum; ++i) {
			if (raw_array[i].R_name == name) {
				raw_array[i].show_info();
			}
			else {
				cout << "The raw materials you are looking for do not exist!" << endl;
			}
		}
	}

	~Material() {
		if (this->raw_array != NULL) {
			delete[] this->raw_array;
			this->m_RawNum = 0;
		}
	}


};

class Menu : public Worker {
public:

	Menu() {
		ifstream ifs; //创建文件
		ifs.open(Menu_File, ios::in);

		if (!ifs.is_open()) { //文件未创建
			this->m_DishNum = 0;
			this->Dish_array = NULL;
			m_MenuIsEmpty = true;
			ifs.close();
			return;
		}

		char ch; ifs >> ch; //文件存在并且没有记录
		if (ifs.eof()) { //当前为尾部
			this->m_DishNum = 0;
			this->m_MenuIsEmpty = true;
			this->Dish_array = NULL;
			ifs.close();
			return;
		}

		int num = this->get_Num(); // 文件存在且不为空
		this->m_DishNum = num;


		//开辟空间
		this->Dish_array = new Dishes[this->m_DishNum];
		this->init_value();
	}

	virtual int get_Num() {
		ifstream ifs;
		ifs.open(Menu_File, ios::in);
		int id_num;
		double price;
		string name;
		string R_name;
		int num = 0;

		while (ifs >> id_num && ifs >> name && ifs >> price && ifs >> R_name) {
			num++;
		}
		return num;
	}

	virtual void init_value() {
		ifstream ifs;
		ifs.open(Menu_File, ios::in);

		int id_num;
		double price;
		string name;
		string raw_name;

		int index = 0;
		while (ifs >> id_num && ifs >> name && ifs >> price && ifs >> raw_name) {
			for (int i = 0; i < this->m_RawNum; i++) {
				if (this->raw_array[i].R_name == raw_name) {
					Dishes D_M(id_num, name, price, raw_array[i]);
					this->Dish_array[index] = D_M;
				}
			}
			++index;
		}
		ifs.close();
	}

	virtual void save() {
		ofstream ofs;
		ofs.open(Menu_File, ios::out);

		for (int i = 0; i < this->m_DishNum; i++) {
			ofs << this->Dish_array[i].D_num << " "
				<< this->Dish_array[i].D_name << " "
				<< this->Dish_array[i].D_price << " "
				<< this->Dish_array[i].D_make.R_name << endl;
		}
		ofs.close();
	}

	virtual void Browse() {
		for (int i = 0; i < this->get_Num(); ++i) {
			this->Dish_array[i].show_info();
		}
	}

	virtual void Add() {
		int newSize = this->m_DishNum + 1;
		Dishes* newSpace = new Dishes[newSize];

		if (this->Dish_array != NULL) {
			for (int i = 0; i < this->m_RawNum; i++) {
				newSpace[i] = this->Dish_array[i];
			}
		}

		int id_num;
		string name;		//输入新数据
		double price;
		string raw_name;

		cout << "Please input the Dish_id" << endl;
		cin >> id_num;
		cout << "Please input the Dish_name" << endl;
		cin >> name;
		cout << "Please input the Dish price" << endl;
		cin >> price;
		cout << "Please input the Raw material name" << endl;
		cin >> raw_name;

		worker = new Material();
		worker->init_value();


		for (int i = 0; i < worker->m_RawNum; i++) {
			if (worker->raw_array[i].R_name == raw_name) {

				Dishes D_M(id_num, name, price, worker->raw_array[i]);
				newSpace[this->m_DishNum] = D_M;

				delete[] this->Dish_array;
				this->Dish_array = newSpace;

				this->m_DishNum = newSize;
				this->save();
				cout << "You have successfully added raw materials!" << endl;
			}
		}


	}

	virtual void Amend() {
		int id_num;
		cout << "Please enter the Dish ID you want to modify: " << endl;
		cin >> id_num;

		for (int i = 0; i < this->m_DishNum; ++i) {
			if (Dish_array[i].D_num == id_num) {
				int new_id;
				string new_name;
				double new_price;
				string new_Rname;
				Dishes new_D_make;

				cout << "Please enter new Dish ID: " << endl;
				cin >> new_id;
				this->Dish_array[i].D_num = new_id;

				cout << "Please enter new Dish name: " << endl;
				cin >> new_name;
				this->Dish_array[i].D_name = new_name;

				cout << "Please enter new Dish Price: " << endl;
				cin >> new_price;
				this->Dish_array[i].D_price = new_price;

				cout << "Please enter new Dish Material: " << endl;
				cin >> new_Rname;
				for (int j = 0; j < this->m_RawNum; j++) {
					if (this->raw_array[j].R_name == new_Rname) {
						this->Dish_array[i].D_make = raw_array[j];
					}
				}
				this->save();
			}
			else {
				cout << "No raw materials you entered!" << endl;
			}
		}
	}

	virtual void Delete() {
		int id_num;
		int deleteNum = 0;
		cout << "Please enter the Dish ID you want to delete: " << endl;
		cin >> id_num;

		for (int i = 0; i < this->m_DishNum; ++i) {
			if (Dish_array[i].D_num == id_num) {
				deleteNum = i;
			}
		}
		for (int i = deleteNum; i < this->m_DishNum; i++) {

			this->Dish_array[i] = this->Dish_array[i + 1]; //覆盖

		}
		this->m_RawNum--;
		this->save();

		cout << "Successful deletion!" << endl;
	}

	virtual void show_Menu() {
		cout << "Please input your choice: " << endl;
		cout << "1. Browse the information of Meun." << endl;
		cout << "2. Add a new dish in Meun." << endl;
		cout << "3. Amend the Meun." << endl;
		cout << "4. Delete the Meun." << endl;
	}

	virtual void research() {
		int id_num;
		cout << "Please enter the Dish ID you want to research: " << endl;
		cin >> id_num;

		for (int i = 0; i < this->m_DishNum; ++i) {
			if (Dish_array[i].D_num == id_num) {
				Dish_array[i].show_info();
			}
			else {
				cout << "The Dish you are looking for do not exist!" << endl;
			}
		}
	}

	~Menu() {
		if (this->Dish_array != NULL) {
			delete[] this->Dish_array;
			this->m_DishNum = 0;
		}
	}

	Worker* worker;
};

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

