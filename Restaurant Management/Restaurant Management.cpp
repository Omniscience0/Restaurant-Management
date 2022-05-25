#include <iostream>
using namespace std;
#include <string>
#include <fstream>
#include <vector>
#define Material_File "Raw_Material.txt"
#define Menu_File "Menu.txt"
#define Customer_File "Customer.txt"
#define Order_File "Order.txt"

class Raw_material { //原材料
public:
	Raw_material() {
		this->R_name = { 0 };
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

class Dishes { //dishes 菜品
public:

	Dishes() {
		this->D_price = 0.0;
	}

	Dishes(int num, string name, double price, Raw_material make) {
		D_make = make;
		D_num = num;
		D_name = name;
		D_price = price;
	}

	void show_info() {
		cout << "Dish NO: " << this->D_num << " Dish name: " << this->D_name << " Price: " << this->D_price
			<< " Raw materials neede: " << this->D_make.R_name << endl;
	}

	Raw_material D_make;
	int D_num;
	string D_name;
	double D_price;
};

class Customer { //顾客
public:

	virtual void show_info() = 0;

	void show_Menu() {
		cout << "Welcome to Customer Page!" << endl;
		cout << "Please input your choice: " << endl;
		cout << "1. View the Menu." << endl;
		cout << "2. Take order." << endl;
		cout << "3. Check out." << endl;
		cout << "4. exit." << endl;
	}

	void C_order();

	bool Dish_check(int Dish_id) {
		for (int i = 0; i < Dish_num; i++) {
			if (this->D_array[i].D_num == Dish_id) {

				return false;
			}
		}
		return true;
	}

	virtual double check_out() = 0;

	int is_Exist(int Dish_id);

	string C_name;
	string C_gender;
	string C_phone;
	Dishes* D_array;
	int Dish_num;
	int Dep_id;
};

class Vip_Cust : public Customer {
public:

	Vip_Cust(string name, string gender, string phone, int dep_id);

	virtual void show_info() {
		cout << "Name: " << C_name << " Gender: " << C_gender << " Phone Number: " << C_phone << endl;
	}

	virtual double check_out() {
		double sum = 0, Raw_Cost = 0.0;
		for (int i = 0; i < this->Dish_num; i++) {
			sum += this->D_array[i].D_price;
			Raw_Cost += this->D_array[i].D_make.R_price;
		}
		ofstream ofs;
		ofs.open(Order_File, ios::out);

		ofs << this->C_name << " "
			<< sum * 0.7 << " "
			<< Raw_Cost << endl;
		ofs.close();
		return sum * 0.7;
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
		double sum = 0,Raw_Cost = 0.0;
		for (int i = 0; i < this->Dish_num; i++) {
			sum += this->D_array[i].D_price;
			Raw_Cost += this->D_array[i].D_make.R_price;
		}
		ofstream ofs;
		ofs.open(Order_File, ios::out);

		ofs << this->C_name << " "
			<< sum << " "
			<< Raw_Cost << endl;
		ofs.close();
		return sum * 0.8;

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
		//worker = new Menu();
	}

	virtual void show_info() {
		cout << "Name: " << C_name << " Gender: " << C_gender << " Phone Number: " << C_phone << endl;
	}

	virtual double check_out() {
		double sum = 0, Raw_Cost = 0.0;
		for (int i = 0; i < this->Dish_num; i++) {
			sum += this->D_array[i].D_price;
			Raw_Cost += this->D_array[i].D_make.R_price;
		}
		ofstream ofs;
		ofs.open(Order_File, ios::out);

		ofs << this->C_name << " "
			<< sum << " "
			<< Raw_Cost << endl;
		ofs.close();
		return sum;
	}

};

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
//浏览、添加、修改和删除原材料信息、菜单信息和客户信息；
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

	int get_Num() {
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

	void init_value() {
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

	void save() {
		ofstream ofs;
		ofs.open(Material_File, ios::out);

		for (int i = 0; i < this->m_RawNum; i++) {
			ofs << this->raw_array[i].R_name << " "
				<< this->raw_array[i].R_price << endl;
		}
		ofs.close();
	}

	void Browse() {
		if (m_FileIsEmpty) {
			cout << "There is no raw material!" << endl;
			system("pause");
			system("cls");
			return;
		}
		for (int i = 0; i < this->get_Num(); ++i) {
			this->raw_array[i].show_info();
		}
		system("pause");
	}

	void Add() {
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
		system("pause");
		system("cls");
	}

	void Amend() {
		string name;
		cout << "Please enter the raw material name you want to modify: " << endl;
		cin >> name;

		int record = -1;
		for (int i = 0; i < this->m_RawNum; ++i) {
			if (raw_array[i].R_name == name) {
				string new_name;
				double new_price;

				cout << "Please enter new raw material name: " << endl;
				cin >> new_name;
				this->raw_array[i].R_name = new_name;

				cout << "Please enter new raw material price: " << endl;
				cin >> new_price;
				this->raw_array[i].R_price = new_price;

				this->save();
				cout << "you have successfully modified a raw material!" << endl;
				system("pause");
				record = i;
			}
		}
		if (record == -1) {
			cout << "The raw material you entered doesn't exist!" << endl;
			system("pause");
		}
	}

	void Delete() {

		string name;
		int deleteNum = 0;
		cout << "Please enter the raw material name you want to delete: " << endl;
		cin >> name;

		for (int i = 0; i < this->m_RawNum; ++i) {
			if (raw_array[i].R_name == name) {
				deleteNum = i;
			}
		}
		for (int i = deleteNum; i < this->m_RawNum - 1; i++) {

			this->raw_array[i] = this->raw_array[i + 1]; //覆盖

		}

		this->m_RawNum--;
		this->save();

		cout << "Successful deletion!" << endl;
	}

	void show_Menu() {
		system("cls");
		cout << "Please input your choice: " << endl;
		cout << "1. Browse the information of raw materials." << endl;
		cout << "2. Add a new raw material." << endl;
		cout << "3. Amend the raw material." << endl;
		cout << "4. Delete the raw maqterial." << endl;
		cout << "5. Return to the previous interface." << endl;
	}

	void research() {
		bool found = false;
		string name;
		cout << "Please enter the raw material name you want to research: " << endl;
		cin >> name;

		for (int i = 0; i < this->m_RawNum; ++i) {
			if (raw_array[i].R_name == name) {
				raw_array[i].show_info();
				found = true;
			}

		}
		if (!found) {
			cout << "The raw materials you are looking for do not exist!" << endl;
		}
		system("pause");
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

		worker->init_value();

		int num = this->get_Num(); // 文件存在且不为空
		this->m_DishNum = num;


		//开辟空间
		this->Dish_array = new Dishes[this->m_DishNum];
		this->init_value();
	}

	int get_Num() {
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

	void init_value() {
		ifstream ifs;
		ifs.open(Menu_File, ios::in);

		int id_num;
		double price;
		string name;
		string raw_name;


		int index = 0;
		while (ifs >> id_num && ifs >> name && ifs >> price && ifs >> raw_name) {
			for (int i = 0; i < worker->m_RawNum; i++) {
				if (worker->raw_array[i].R_name == raw_name) {
					Dishes D_M(id_num, name, price, worker->raw_array[i]);
					this->Dish_array[index] = D_M;
				}
			}
			++index;
		}

		ifs.close();
	}

	void save() {
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

	void Browse() {
		if (m_MenuIsEmpty) {
			cout << "There is no dish on the menu!" << endl;
			system("pause");
			system("cls");
			return;
		}
		for (int i = 0; i < this->m_DishNum; ++i) {
			cout << "ID: " << Dish_array[i].D_num << " Name: " << Dish_array[i].D_name
				<< " Price : " << Dish_array[i].D_price << " Raw material: " << Dish_array[i].D_make.R_name << endl;
		}
		system("pause");
	}

	void Add() {

		int newSize = this->m_DishNum + 1;
		Dishes* newSpace = new Dishes[newSize];

		if (this->Dish_array != NULL) {
			for (int i = 0; i < this->m_DishNum; i++) {
				newSpace[i] = this->Dish_array[i];
			}
		}

		int id_num;
		string name;		//输入新数据
		double price;
		string raw_name;
		bool rawFound = false;

		cout << "Please input the Dish_id" << endl;
		cin >> id_num;

		int record = -1;
		for (int i = 0; i < this->m_DishNum; i++) {
			if (id_num == this->Dish_array[i].D_num)
				record = i;
		}
		if (record != -1) {
			cout << "The Dish is already exist, please input a new Dish !" << endl;
			this->Add();
		}
		cout << "Please input the Dish_name" << endl;
		cin >> name;
		cout << "Please input the Dish price" << endl;
		cin >> price;
		cout << "Please input the Raw material name" << endl;
		cin >> raw_name;

		for (int i = 0; i < worker->m_RawNum; i++) {
			if (worker->raw_array[i].R_name == raw_name) {
				rawFound = true;
				Dishes D_M(id_num, name, price, worker->raw_array[i]);
				newSpace[this->m_DishNum] = D_M;

				delete[] this->Dish_array;

				this->Dish_array = newSpace;
				this->m_DishNum = newSize;

				this->save();
				cout << "You have successfully added a new dish!" << endl;
				system("pause");
				system("cls");
			}
		}
		if (!rawFound) {
			cout << "There are no raw material needed to make this dish!" << endl;
			system("pause");
			system("cls");
			return;
		}
	}

	void Amend() {
		int id_num;
		cout << "Please enter the Dish ID you want to modify: " << endl;
		cin >> id_num;
		bool Dish_found = false;

		for (int i = 0; i < this->m_DishNum; ++i) {
			if (Dish_array[i].D_num == id_num) {
				Dish_found = true;
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
				bool material_found = false;
				for (int j = 0; j < this->m_RawNum; j++) {
					if (this->raw_array[j].R_name == new_Rname) {
						material_found = true;
						this->Dish_array[i].D_make = raw_array[j];
					}
				}
				if (!material_found) {
					cout << "The raw material of this dish doesn't exist!" << endl;
					system("pause");
					return;
				}
				this->save();
				cout << "You have successfully amended a dish!" << endl;
				system("pause");
			}
		}
		if (!Dish_found) {
			cout << "The dish ID you entered doesn't exist!" << endl;
			system("pause");
		}
	}

	void Delete() {
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
		this->m_DishNum--;
		this->save();

		cout << "Successful deletion!" << endl;
		system("pause");
	}

	void show_Menu() {
		system("cls");
		cout << "Please input your choice: " << endl;
		cout << "1. Browse the information of Meun." << endl;
		cout << "2. Add a new dish in Meun." << endl;
		cout << "3. Amend the Meun." << endl;
		cout << "4. Delete the Meun." << endl;
		cout << "5. Return to the  previous interface." << endl;
	}

	void research() {
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
	Worker* worker = new Material();

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
		cout << "Customer information: " << endl;
		for (int i = 0; i < this->get_Num(); ++i) {
			this->Cust_array[i]->show_info();
			system("pause");
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

		system("cls");
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
		system("cls");
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
		for (int i = deleteNum; i < this->m_CustNum - 1; i++) {

			this->Cust_array[i] = this->Cust_array[i + 1]; //覆盖

		}
		this->m_RawNum--;
		this->save();

		cout << "Successful deletion!" << endl;
	}

	virtual void show_Menu() {
		system("cls");
		cout << "Please input your choice: " << endl;
		cout << "1. Browse the customer information ." << endl;
		cout << "2. Add a new customer." << endl;
		cout << "3. Amend customer information." << endl;
		cout << "4. Delete customer information." << endl;
		cout << "5. Return to the previous interface" << endl;
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

void Customer::C_order() {
	int Dish_num;
	int Dish_id;
	Worker* worker = new Menu();
	for (int i = 0; i < worker->get_Num(); i++) {
		worker->Dish_array[i].show_info();
	}
	cout << "Please input the numbers of your dishes: " << endl;
	cin >> Dish_num;
	if (Dish_num > 0) {
		this->D_array = new Dishes[Dish_num];
		this->Dish_num += Dish_num;
		for (int i = 0; i < Dish_num; i++) {
			cout << "Please input your ordered dish (please input the ID number):" << endl;
			cin >> Dish_id;
			int found = is_Exist(Dish_id);
			if (!Dish_check(Dish_id)) {
				cout << "You have already order the dish" << endl;
				system("pause");
				i--;
			}
		    else if (found == -1) {
				cout << "The dish you ordered doesn't exist!" << endl;
				system("pause");
				i--;
			}
			else if (found != -1 && Dish_check(Dish_id)) {
				this->D_array[i] = worker->Dish_array[found];
				cout << "You have successfully ordered a dish!" << endl;
				system("pause");
			}
		}
	}
	else {
		cout << "Invalid input!" << endl;
	}

}


int Customer::is_Exist(int Dish_id) {
	Worker* worker = new Menu;
	for (int i = 0; i < worker->m_DishNum; i++) {
		if (worker->Dish_array[i].D_num == Dish_id)
			return i;
	}
	return -1;
}

Vip_Cust::Vip_Cust(string name, string gender, string phone, int dep_id) {
	this->C_name = name;
	this->C_gender = gender;
	this->C_phone = phone;
	this->Dep_id = dep_id;
	this->D_array = NULL;
}



void Manager_Operation() {
	Worker* worker;
	char input;
	double Raw_Cost = 0.0, Cost = 0.0, Profit = 0.0;
	string name;
	ifstream ifs;
	while (1) {
		system("cls");
		cout << "Welcome to Manager Page!" << endl;
		cout << "Please input your choice: " << endl;
		cout << "1. Raw materials interface." << endl;
		cout << "2. Menu interface." << endl;
		cout << "3. Customer interface." << endl;
		cout << "4. View turnover." << endl;
		cout << "5. Return to the previous interface." << endl;
		cin >> input;
		switch (input)
		{
		case '1':
			worker = new Material();
			while (1) {
				worker->show_Menu();
				char input1;
				cin >> input1;
				switch (input1)
				{
				case '1':
					worker->Browse();
					break;
				case '2':
					worker->Add();
					break;
				case '3':
					worker->Amend();
					break;
				case '4':
					worker->Delete();
					break;
				case '5':
					system("cls");
					return;
				default:
					cout << "Invalid input" << endl;
					system("pause");
					break;

				}
			}
			break;
		case '2':
			worker = new Menu();
			while (1) {
				worker->show_Menu();
				char input2;
				cin >> input2;
				switch (input2)
				{
				case '1':
					worker->Browse();
					break;
				case '2':
					worker->Add();
					break;
				case '3':
					worker->Amend();
					break;
				case '4':
					worker->Delete();
					break;
				case '5':
					system("cls");
					return;
				default:
					cout << "Invalid input" << endl;
					system("pause");
					break;
				}
			}
			break;

		case '3':
			worker = new Cust_info();
			while (1) {
				worker->show_Menu();
				char input3;
				cin >> input3;
				switch (input3)
				{
				case '1':
					worker->Browse();
					break;
				case '2':
					worker->Add();
					break;
				case '3':
					worker->Amend();
					break;
				case '4':
					worker->Delete();
					break;
				case '5':
					system("cls");
					return;
				default:
					cout << "Invalid input" << endl;
					system("pause");
					break;

				}
			}
			break;

		case '4':
			ifs.open(Order_File, ios::in);

			while (ifs >> name && ifs >> Cost && ifs >> Raw_Cost) {
				Profit += Cost - Raw_Cost;
			}
			ifs.close();
			cout << "The restaurant has a total profit of " << Profit << " dollors!" << endl;
			Profit = 0.0;
			Cost = 0.0;
			Raw_Cost = 0.0;
			system("pause");

			break;
		case '5':
			system("cls");
			return;
			break;
		default:
			cout << "Error input!" << endl;
			system("pause");
			system("cls");
			break;
		}
	}
}

void Chef_Operation() {
	char input;
	Worker* worker = NULL;
	while (1) {
		system("cls");
		cout << "Welcome to Chef Page!" << endl;
		cout << "Please input your choice: " << endl;
		cout << "1. Search raw material." << endl;
		cout << "2. Browse raw material." << endl;
		cout << "3. Edit the Menu." << endl;
		cout << "4. Rerurn to the previous interface." << endl;
		cin >> input;
		switch (input)
		{
		case '1':
			worker = new Material();
			worker->research();
			break;
		case '2':
			worker = new Material();
			worker->Browse();
			break;
		case '3':
			worker = new Menu();
			worker->show_Menu();
			char select;
			cin >> select;
			switch (select)
			{
			case '1':
				worker->Browse();
				break;
			case '2':
				worker->Add();
				break;
			case '3':
				worker->Amend();
				break;
			case '4':
				worker->Delete();
				break;
			case '5':
				system("cls");
				break;
			}
			break;
		case '4':
			system("cls");
			return;
		default:
			cout << "Invalid input!" << endl;
			system("pause");
			break;
		}
	}
};

void show_interface() {

	cout <<"Welcome to restaurant managment system!" << "+" << endl;
	cout << "Please choose the correct identity: " << "|" << endl;
	cout << "1. Manager"  << endl;
	cout << "2. Chef"<< endl;
	cout << "3. Customer" << endl;
	cout << "4. Exit" << endl;
}

void Customer_Operation(Customer* Cust, Worker* worker) {

	while (true) {
		system("cls");
		double cost;
		Cust->show_Menu();
		char input;
		cin >> input;
		switch (input) {
		case '1':
			worker->Browse();
			break;
		case '2':
			Cust->C_order();
			break;
		case '3':
			cost = Cust->check_out();
			cout << "you have to pay " << cost << " in total" << endl;;
			system("pause");
			break;
		case '4':
			exit(0);
		default:
			cout << "Please choose again" << endl;
			break;
		}
	}

}

int main()
{
	char id_Choice;
	int choice;
	int record = -1;
	while (1) {
		show_interface();
		cin >> id_Choice;
		string name;
		Worker* worker = NULL;

		switch (id_Choice)
		{
		case '1':
			system("cls");

			Manager_Operation();
			break;
		case '2':
			system("cls");
			Chef_Operation();
			break;
		case '3':
			system("cls");
			worker = new Cust_info();
			cout << "Log-in interface" << endl;
			cout << "Please input you name: ";
			cin >> name;
	
			for (int i = 0; i < worker->m_CustNum; i++) {
				if (worker->Cust_array[i]->C_name == name) {
					Customer_Operation(worker->Cust_array[i], new Menu());
					record = i;
				}
			}
			if(record == -1){

				cout << "You do not have a count" << endl;
				cout << "Would you like to add a new count ? (1:Yes, 2:No)" << endl;

				cin >> choice;
				if(choice == 1)
					worker->Add();
				system("pause");
				system("cls");
			}
			break;
		case '4':
			exit(0);
		default:
			cout << "Error input." << endl;
			system("pause");
			system("cls");
			break;
		}
	}
	return 0;
}
