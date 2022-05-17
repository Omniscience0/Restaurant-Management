#pragma once
#include <iostream>
using namespace std;
#include <fstream>
#include <string>
#define Material_File "Raw_Material.txt"
#include "Raw_material.h"
#include "Dishes.h"
#include "Customer.h"
#include "Worker.h"
#include "Cust_info.h"
#include "Material.h"

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