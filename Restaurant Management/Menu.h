#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#define Menu_File "Menu.txt"
#include "Raw_material.h"
#include "Dishes.h"
#include "Customer.h"
#include "Worker.h"
#include "Material.h"


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