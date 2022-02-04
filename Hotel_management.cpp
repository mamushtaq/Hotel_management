#include <iostream>
#include< stdlib.h > //This library is included to use system("clr")
#include <fstream>
#include<string>
#include <windows.h>//Windows.h and shellapi.h included to open a website link from program.
#include <shellapi.h>
using namespace std;

class Date {
protected:
	int day, month, year;
public:
	friend class Room;
	friend class Single_room;
	friend class Double_room;
	Date(int d = 1, int m = 1, int y = 2021) : day(d), month(m), year(y) {}
	bool check_date() {
		if (year == 2022 || year == 2023) {
			if (month <= 12 && month >= 1) {
				if (day >= 1) {
					if (month == 2 && day <= 28) {
						return true;
					}
					else if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day <= 31) {
						return true;
					}
					else if (day <= 30) {
						return true;
					}
					else {
						return false;
					}
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
		return false;
	}
	Date add_days(int days) {
		Date temp;
		temp.day = day + days;
		temp.month = month;
		temp.year = year;
		temp.adjust_day();
		return temp;
	}
	void display() {
		cout << day << " " << month << " " << year << endl;
	}
	Date remove_days(int days) {
		Date temp;
		temp.day = day - days;
		temp.month = month;
		temp.year = year;
		temp.adjust_day();
		return temp;
	}
	Date operator ++ () {
		return add_days(1);
	}
	Date operator ++ (int) {
		Date temp;
		temp = *this;
		this->add_days(1);
		return temp;
	}
	Date operator -- () {
		return remove_days(1);
	}
	Date operator -- (int) {
		Date temp;
		temp = *this;
		this->remove_days(1);
		return temp;
	}
	bool operator == (const Date & obj1) {
		if (day == obj1.day && month == obj1.month && year == obj1.year) {
			return true;
		}
		else {
			return false;
		}
	}



	void adjust_day() {
		if (month == 2) {
			if (day > 28) {
				int extra = day - 28;
				day = extra;
				++month;
				adjust_month();
			}
			else if (day < 1) {
				day = day + 28;
				--month;
				adjust_month();
			}
		}
		else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
			if (day > 31) {
				day = day - 31;
				++month;
				adjust_month();
			}
			else if (day < 1) {
				day = day + 30;
				--month;
				adjust_month();
			}
		}
		else if (month == 4 || month == 6 || month == 9 || month == 11) {
			if (day > 30) {
				day = day - 30;
				cout << month;
				++month;
				adjust_month();
			}
			else if (day < 1) {
				day = day + 31;
				--month;
				adjust_month();
			}
		}
		return;
	}
	void adjust_month() {
		if (month > 12) {
			int extra = month - 12;
			month = extra;
			++year;
		}
		else if (month < 1) {
			int extra = month + 12;
			month = extra;
			--year;
		}
		return;
	}
};
class Hotel {
	static char hotel_name[50];
public:
	Hotel() {
		strcpy_s(hotel_name, "Serena Hotel");
	}
	static void display();
	void main_page() const;
	static bool continue_or_not();
};
class Customer : public Hotel {
protected:
	char gender[50], firstname[50], lastname[50], username[50], password[50], email_address[50], phone_number[50];
	double price;
	int age;
	int id, current_room_no;
	bool currently_staying;
	static int total_customers;
public:
	Customer() : firstname(""), lastname(""), username(""), password(""), age(0), phone_number(""), gender(""), id(0), current_room_no(0), currently_staying(false), price(0), Hotel() {}
	void log_in();
	void register_account();
	void create_login_id_and_pass();
	bool user_available(char username1[], int option);
	void write();
	void display() const;
	void account_already_created() const;
	void main_page();
	void set_first_name(char firstname1[]);
	void set_last_name(char lastname1[]);
	void set_email(char email[]);
	void set_username(char user[]);
	void set_password(char pass[]);
	void set_gender(char gend[]);
	void set_phone(char phone[]);
	void set_age(int a);
	void setting();
	void overwrite(int id_obj, Customer obj);
	void read(char username1[]);
	void set_total_customers();
	void check_in();
	void check_out();
};
class Room:public Hotel {
protected:
	int Room_no;
	bool available;
	char customer_id[50];
	int number_night;
	Date start, end;
	double price;
	char room_type[50], filename[50];
public:
	Room() :Room_no(0), available(true), customer_id(""), number_night(0), price(0), room_type("") {}
	virtual void create_room(char file_name[], int tf) = 0;
	virtual void write() = 0;
	virtual void read(char file_name[]) = 0;
	virtual void display() = 0;
	virtual void check_into_room(char temp_id[]) = 0;
	virtual int check_out() = 0;
	//virtual void overwrite(int rnum, char file_name[], Room& temp_obj) = 0;
	virtual void find_room(char file_name[], int rnum) = 0;
	virtual bool room_exist(char file_name[], int rnum) = 0;
	virtual void complete_display() = 0;
	virtual int get_room_no() const = 0;
	virtual bool get_available() const = 0;
	virtual void set_price(double p) = 0;
	virtual double get_price() = 0;
	virtual void set_customer_id(char temp[]) = 0;
	//virtual string get_customer_id() = 0;
	virtual int get_number_of_nights() = 0;
	virtual void set_number_of_nights(int n) = 0;
	virtual void set_start_date(Date s) = 0;
	virtual Date get_start_date() = 0;
	virtual void calculate_end_date() = 0;
	virtual Date get_end_date() = 0;
	virtual void set_room_type(char temp[]) = 0;
	//virtual string get_room_type() const = 0;
};
class Single_room :public Room{
protected:
	static int total_rooms;
public:
	Single_room() :Room() {
		price = 15;
	}
	void create_room(char file_name[], int tf);
	void write();
	void read(char file_name[]);
	void check_into_room(char temp_id[]);
	int check_out();
	void display();
	void overwrite(int rnum, char file_name[], Single_room& temp_obj);
	void find_room(char file_name[], int rnum);
	bool room_exist(char file_name[], int rnum);
	int find_position(int rnum, char file_name[]);
	void complete_display();
	int get_room_no() const;
	bool get_available() const;
	void set_price(double p);
	double get_price();
	void set_customer_id(char temp[]);
	//string get_customer_id();
	int get_number_of_nights();
	void set_number_of_nights(int n);
	void set_start_date(Date s);
	Date get_start_date();
	void calculate_end_date();
	Date get_end_date();
	void set_room_type(char temp[]);
	//string get_room_type() const;
};
class Double_room :public Room{
protected:
	static int total_rooms;
public:
	Double_room() :Room() {
		price = 25;
	}
	void create_room(char file_name[], int tf);
	void write();
	void read(char file_name[]);
	void check_into_room(char temp_id[]);
	int check_out();
	void display();
	void overwrite(int rnum, char file_name[], Double_room& temp_obj);
	int find_position(int rnum, char file_name[]);
	void find_room(char file_name[], int rnum);
	bool room_exist(char file_name[], int rnum);
	void complete_display();
	int get_room_no() const;
	bool get_available() const;
	void set_price(double p);
	double get_price();
	void set_customer_id(char temp[]);
	//string get_customer_id();
	int get_number_of_nights();
	void set_number_of_nights(int n);
	void set_start_date(Date s);
	Date get_start_date();
	void calculate_end_date();
	Date get_end_date();
	void set_room_type(char temp[]);
	//string get_room_type() const;
};	
class Floor :public Hotel {
protected:
	//room obj;
	int floor_number;
	static int total_floors;
	bool rooms_available;
	char floor_file[50];
public:
	friend class Customer;
	friend class Manager;
	Floor() :floor_number(0), rooms_available(true), floor_file("") {}
	void add_floor();
	void write();
	void find_total_floors();
	void read_all_rooms();
	bool find_room(int rnum);
};
class Manager : public Hotel {
protected:
	char username[50], password[50];
public:
	Manager():username(""), password("") {}
	void write();
	void read();
	void set_username(char user_temp[]);
	void set_password(char user_temp[]);
	void setting();
	void log_in();
	void main_page();
	//void find_user();
	bool operator == (const Manager obj);
};
class Cafeteria:public Hotel {
public:
	void menu();
	void add_new_item();
	void overwrite();
	void order();
};
class Food : public Hotel {
protected:
	char foodname[50];
	double price;
public:
	friend Cafeteria;
	Food():foodname(""), price(0) {}
	void add_food();
	void write();
	void read();
	void read_specific(int pos);
	void display() const;
	void food_menu();
	void setting();
	int find_position(char temp[]);
	void overwrite(int rnum, Food& fobj);
	void change_food();
	void order_food();
};
class Drinks : public Hotel {
protected:
	char drinkname[50];
	double price;
public:
	friend Cafeteria;
	Drinks():drinkname(""), price(0) {}
	void add_drink();
	void write();
	void read();
	void read_specific(int pos);
	void display() const;
	void drink_menu();
	void setting();
	int find_position(char temp[]);
	void overwrite(int rnum, Drinks& fobj);
	void change_drink();
	void order_drink();
};

//...................................................................................................................................................

void Hotel:: display() {	
		system("CLS");
		cout << "\n    <============================================================================================================================================================================================>";
		cout << "\n    **\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**";
		cout << "\n    **\t\t\t\t\t\t\t\t\t\t<--------------------------------->\t\t\t\t\t\t\t\t\t\t**";
		cout << "\n    **\t\t\t\t\t\t\t\t\t\t**   WELCOME TO "<<hotel_name<<"  **\t\t\t\t\t\t\t\t\t\t**";
		cout << "\n    **\t\t\t\t\t\t\t\t\t\t<--------------------------------->\t\t\t\t\t\t\t\t\t\t**";
		cout << "\n    **\t\t\t\t\t\t\t\t\t<------------------------------------------------>\t\t\t\t\t\t\t\t\t**";
		cout << "\n    **\t\t\t\t\t\t\t\t\t**   We provide the best accomodation services  **\t\t\t\t\t\t\t\t\t**";
		cout << "\n    **\t\t\t\t\t\t\t\t\t<------------------------------------------------>\t\t\t\t\t\t\t\t\t**";
cout << "\n    **\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t**";
cout << "\n    <============================================================================================================================================================================================>\n\n";

	}
void Hotel::main_page() const {
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t**   Home Page  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t==================";
		cout << "\n\n\n    \t\t\t\t\t\t\tHi there! This is the welcome lobby of the Hotel. It's our pleasure to have you with us. You can: \n";
		cout << "\n    \t\t\t\t\t\t\t\t\t1. Register as a new customer";
		cout << "\n    \t\t\t\t\t\t\t\t\t2. Log into your account";
		cout << "\n    \t\t\t\t\t\t\t\t\t3. Log in as Manager";
		cout << "\n    \t\t\t\t\t\t\t\t\t4. Visit Hotel Website";
		cout << "\n    \t\t\t\t\t\t\t\t\t5. Display all rooms";
		cout << "\n    \t\t\t\t\t\t\t\t\t0. Quit";
	}
bool Hotel::continue_or_not() {
		bool option;
		cout << "\n\n    \t\t\t\t\t\t\tWould you like to conitnue (Enter 1) or return to homepage (Enter 0)? : "; cin >> option;
		return option;
	}

char Hotel::hotel_name[];

	//...................................................................................................................................................

void Customer::log_in() {
		bool quit = false;
		while (quit == false) {
			cin.ignore();
			Hotel::display();
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Log in to your Account  **";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t===============================";
			cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your username and Id to log in.\n";
			cout << "\n    \t\t\t\t\t\t\t\t\tYour username:         "; cin.get(username, 50); cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tYour password:         "; cin.get(password, 50); cin.ignore();
			//cout << "\n    \t\t\t\t\t\t\t\t\tYour ID:     "; cin >> id; cin.ignore();
			Customer temp;
			if (!temp.user_available(username, 1) && !temp.user_available(password, 5)) {
				cout << "\n\n\n    \t\t\t\t\t\t\t\t\t\t!!   Logged in successfully   !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
				char username1[100];
				strcpy_s(username1, username);
				read(username1);
				main_page();
				quit = true;
			}
			else {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t!!   username or password is wrong  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t!!             Try Again            !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t======================================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
				if (Hotel::continue_or_not()) {
					continue;
				}
				else {
					quit = true;
				}
			}
		}
	}
void Customer::register_account() {
		bool quit = false;
		while (!quit) {
			cin.clear();
			Hotel::display();
			int gend;
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Register as a New Customer  **";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
			cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to register:\n";
			cout << "\n    \t\t\t\t\t\t\t\t\tYour First name:         "; cin.get(firstname, 50); cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tYour Last name:          "; cin.get(lastname, 50); cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tYour Email Address:      "; cin.get(email_address, 50); cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tYour Phone no.:          "; cin.get(phone_number, 50); cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tYour age:                "; cin >> age;
			cout << "\n    \t\t\t\t\t\t\t\t\tYour Gender(1 for 'M' and 2 for 'F'): "; cin >> gend; cin.clear();
			currently_staying = false;
			current_room_no = 0;
			price = 0;
			if (gend == 1) {
				strcpy_s(gender, "Male");
			}
			else if (gend == 2) {
				strcpy_s(gender, "Female");
			}
			else {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				system("pause");
				if (Hotel::continue_or_not()) {
					continue;
				}
				else {
					break;
				}
			}

			if (firstname[0] == '\0' || lastname[0] == '\0' || email_address[0] == '\0') {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				system("pause");
				break;
			}

			Customer temp;
			if (!temp.user_available(email_address, 4) && !temp.user_available(firstname, 2) && !temp.user_available(lastname, 3)) {
				account_already_created();
				quit = true;
			}
			else {
				create_login_id_and_pass();
				write();
				log_in();
				quit = true;
			}
		}
		return;
	}
void Customer::create_login_id_and_pass() {
		cin.ignore();
		bool quit = false;
		while (quit == false) {
			Hotel::display();
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Register as a New Customer  **";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
			cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your username and Id to register.\n";
			cout << "\n   \t\t\t\t\t\t\t\t\t\tRecommended username: " << firstname[0] << lastname;
			cout << "\n    \t\t\t\t\t\t\t\t\tYour username:         "; cin.get(username, 50); cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tYour password:         "; cin.get(password, 50); cin.ignore();
			if (sizeof(username) <= 4) {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!     Username Too short    !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t!!          Try Again         !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
				system("pause");
			}
			else {
				Customer temp;
				if (temp.user_available(username, 1)) {
					quit = true;
					break;
				}
				else {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!   Username Already Exists  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t!!          Try Again         !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
			}
		}
		return;
	}
bool Customer::user_available(char username1[], int option) { //option will be 1 to check username. 2 to check first name. 3 to check last name. 4 to check email. 5 to check password
			ifstream customer_file;
			int number_of_times = 0;
			customer_file.open("customers.dat", ios::binary);//binary means opening this file in binary mode.
			if (!customer_file) {
				return true;
			}
			else {
				while (!customer_file.eof()) {
					//infile.seekg(pn * sizeof(person)) this is used to get specific person. Sending to direct location. Sizeof gives bites. So the product tells the function to move number of bytes to get to that person.
					customer_file.read((char*)this, sizeof(Customer));
					switch (option)
					{
					case 1:
						if (strcmp(username1, username) == 0) {
							++number_of_times;
						}
						break;
					case 2:
						if (strcmp(username1, firstname) == 0) {
							++number_of_times;
						}
						break;
					case 3:
						if (strcmp(username1, lastname) == 0) {
							++number_of_times;
						}
						break;
					case 4:
						if (strcmp(username1, email_address) == 0) {
							++number_of_times;
						}
						break;
					case 5:
						if (strcmp(username1, password) == 0) {
							++number_of_times;
						}
						break;
					default:
						break;
					}
				}
			}
			customer_file.close();
			if (number_of_times == 0) {
				return true;
			}
			else {
				return false;
			}
	}
void Customer::write() {
		ofstream customer_file;
		customer_file.open("customers.dat", ios::app , ios::binary);
		customer_file.write((char*)this, sizeof(Customer));
		customer_file.close();
		set_total_customers();
		++total_customers;
		id = total_customers - 2;
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!       Account Created      !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t!!           Your ID: " << id << "         !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t!!      Log in to continue    !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
		system("pause");
		return;
	}
void Customer::display() const {
		cout << "\n    \t\t\t\t\t\t\t\t\t1. First Name:    " << firstname;
		cout << "\n    \t\t\t\t\t\t\t\t\t2. Last Name:     " << lastname;
		cout << "\n    \t\t\t\t\t\t\t\t\t3. Email Address: " << email_address;
		cout << "\n    \t\t\t\t\t\t\t\t\t4. Age:           " << age;
		cout << "\n    \t\t\t\t\t\t\t\t\t5. Gender:        " << gender;
		cout << "\n    \t\t\t\t\t\t\t\t\t6. Phone Number:  " << phone_number;
		cout << "\n    \t\t\t\t\t\t\t\t\t7. Username:      " << username;
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
		system("pause");
	}
void Customer::account_already_created() const {
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!   Account Already Exists  !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t!!      Log in Instead       !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
		system("pause");
	}
void Customer::main_page() {
		int option;
		bool quit = false;
		while (quit == false) {
			Hotel::display();
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t**   User Menu  **";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t==================";
			cout << "\n\n\n    \t\t\t\t\t\t\t\t\t1. Check In";
			cout << "\n    \t\t\t\t\t\t\t\t\t2. Check Out";
			cout << "\n    \t\t\t\t\t\t\t\t\t3. View All Rooms";
			cout << "\n    \t\t\t\t\t\t\t\t\t4. Account settings";
			cout << "\n    \t\t\t\t\t\t\t\t\t5. View your Room details";
			cout << "\n    \t\t\t\t\t\t\t\t\t6. Visit Cafeteria";
			cout << "\n    \t\t\t\t\t\t\t\t\t7. Order Food";
			cout << "\n    \t\t\t\t\t\t\t\t\t0. Quit";
			cout << "\n\n    \t\t\t\t\t\t\tEnter the serial number of option you want to choose: ";
			cin >> option;
			switch (option)
			{
			case 0:
				quit = true;
				break;
			case 1:
			{
				if (!currently_staying) {
					check_in();
					overwrite(this->id, *this);
				}
				else {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t!!   You are currently staying in Room number: " << current_room_no << "  !!";
					cout <<   "\n    \t\t\t\t\t\t\t\t\t!!                      Check out                   !!";
					cout <<   "\n    \t\t\t\t\t\t\t\t\t======================================================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
			}
				break;
			case 2:
				if (currently_staying) {
					check_out();
					price = 0;
					overwrite(this->id, *this);
				}
				else {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t!!   You are currently not staying in any room.  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t!!                  Check in first               !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t===================================================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				break;
			case 3:
			{
				Floor temp;
				temp.read_all_rooms();
				break;
			}
			case 4:
				setting();
				break;
			case 5:
				if (currently_staying) {
					Floor temp;
					temp.find_room(current_room_no);
					int temp1 = current_room_no / 10;
					if ((temp1 % 10) == 0) {
						Single_room room_obj;
						room_obj.find_room(temp.floor_file, current_room_no);
						room_obj.complete_display();
					}
					else if ((temp1 % 10) == 1) {
						Double_room room_obj;
						room_obj.find_room(temp.floor_file, current_room_no);
						room_obj.complete_display();
					}
				}
				else {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t!!   You are currently not staying in any room.  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t!!                  Check in first               !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t===================================================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				break;
			case 6:
			{
				Cafeteria temp;
				temp.menu();
			} break;
			case 7:
			{
				Cafeteria temp;
				temp.order();
			} break;
			default:
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				system("pause");
				break;
			}
		}
	}
void Customer::set_first_name (char firstname1[]) {
		strcpy_s(firstname, firstname1);
	}
void Customer::set_last_name(char lastname1[]) {
		strcpy_s(lastname, lastname1);
	}
void Customer::set_email(char email[]) {
		strcpy_s(email_address, email);
	}
void Customer::set_username(char user[]) {
		strcpy_s(username, user);
	}
void Customer::set_password(char pass[]) {
		strcpy_s(password, pass);
	}
void Customer::set_gender(char gend[]) {
		strcpy_s(gender, gend);
	}
void Customer::set_phone(char phone[]) {
		strcpy_s(phone_number, phone);
	}
void Customer::set_age(int a) {
		age = a;
	}
void Customer::setting() {
		int option;
		bool quit = false;
		while (quit == false) {
			Hotel::display();
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t**   Account Settings  **";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t=========================";
			cout << "\n\n\n    \t\t\t\t\t\t\tEnter the serial number of attribute you want to change: ";
			display();
			cout << "\n    \t\t\t\t\t\t\t\t\t8. Password:      ******";
			cout << "\n    \t\t\t\t\t\t\t\t\t0. Quit";
			cout << "\n\n    \t\t\t\t\t\t\tEnter the serial number of option you want to choose: ";
			cin >> option;
			cin.ignore();
			switch (option)
			{
			case 0:
				quit = true;
				overwrite(id, *this);
				break;
			case 1:
			{
				cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";
				char temp[50];
				cin.clear();
				cout << "\n    \t\t\t\t\t\t\t\t\tYour First name:         "; cin.get(temp, 50); cin.ignore();
				if (temp[0] == '\0') {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				else {
					set_first_name(temp);
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Task Completed  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				break;
			}
			case 2:
			{
				char temp[50];
				cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";

				cout << "\n    \t\t\t\t\t\t\t\t\tYour Last name:         "; cin.get(temp, 50); cin.ignore();
				if (temp[0] == '\0') {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				else {
					set_last_name(temp);
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Task Completed  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
			}
				break;
			case 3:
			{
				char temp[50];
				cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";

				cout << "\n    \t\t\t\t\t\t\t\t\tYour Email Address:         "; cin.get(temp, 50); cin.ignore();
				if (temp[0] == '\0') {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				else {
					set_email(temp);
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Task Completed  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
			}
				break;
			case 4:
				try {
					int temp;
					cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";

					cout << "\n    \t\t\t\t\t\t\t\t\tYour age:                "; cin >> temp;
					if (temp < 15) {
						throw temp;
					}
					else {
						set_age(temp);
					}
				}
				catch (...) {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!! Should be older than 15 !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!         Try Again       !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t=============================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				break;
			case 5:
				try {
					int temp;
					cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";

					cout << "\n    \t\t\t\t\t\t\t\t\tYour Gender(1 for 'M' and 2 for 'F'): "; cin >> temp; cin.clear();
					if (temp == 1) {
						char temp[50];
						strcpy_s(temp, "Male");
						set_gender(temp);
					}
					else if (temp == 2) {
						char temp[50];
						strcpy_s(temp, "Female");
						set_gender(temp);
					}
					else {
						throw temp;
					}
				}
				catch (...) {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				break;
			case 6:
			{
				char temp[50];
				cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";

				cout << "\n    \t\t\t\t\t\t\t\t\tYour Phone Number:         "; cin.get(temp, 50); cin.ignore();
				if (temp[0] == '\0') {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				else {
					set_phone(temp);
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Task Completed  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
			}
			break;
			case 7:
			{
				char temp[50];
				cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";

				cout << "\n    \t\t\t\t\t\t\t\t\tYour Username:         "; cin.get(temp, 50); cin.ignore();
				if (sizeof(temp) < 4) {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!     Username Too short    !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t!!          Try Again         !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				else {
					Customer temp1;
					if (temp1.user_available(temp, 1)) {
						set_username(temp);
						break;
					}
					else {
						cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!   Username Already Exists  !!";
						cout << "\n    \t\t\t\t\t\t\t\t\t\t!!          Try Again         !!";
						cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
						cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
						system("pause");
					}
				}
			}
			break;
			case 8:
			{
				cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";

				char temp[50];
				cout << "\n    \t\t\t\t\t\t\t\t\tYour Password:         "; cin.get(temp, 50); cin.ignore();
				if (temp[0] == '\0') {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				else {
					set_password(temp);
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Task Completed  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
			}
			break;
			default:
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				system("pause");
				break;
			}
		}
	}
void Customer::overwrite(int id_obj, Customer obj) {
		int position = (id_obj - 1) * sizeof(Customer);
		fstream fout;
		fout.open("customers.dat", ios::in | ios::out | ios::binary | ios::ate);
		//fout.seekp(0, ios::beg);//beg sets position to the start
		fout.seekp(position, ios::cur);//cur sets position to the object we want to find
		fout.write((char*)&obj, sizeof(Customer));
		fout.close();
		return;
	}
void Customer::read(char username1[]) {
		ifstream customer_file;
		int number = 0;
		customer_file.open("customers.dat", ios::binary);//binary means opening this file in binary mode.
		customer_file.read((char*)this, sizeof(Customer));
		while (!customer_file.eof()) {
			if (!strcmp(username1, username)) {
				break;
			}
			customer_file.read((char*)this, sizeof(Customer));
		}
		customer_file.close();
	}
void Customer::set_total_customers() {
		total_customers = 0;
		ifstream customer_file;
		customer_file.open("customers.dat", ios::binary);//binary means opening this file in binary mode.
		system("pause");
		while (!customer_file.eof()) {
			//system("pause");
			customer_file.read((char*)this, sizeof(Customer));
			total_customers++;
		}
		customer_file.close();
	}
void Customer::check_in() {
	Floor temp;
	int option;
	bool quit = false;
	while (quit == false) {
		temp.read_all_rooms();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t**   Room Booking  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t=====================";
		cout << "\n\n\n    \t\t\t\t\t\t\tEnter the room number of the room you want to select: "; cin >> option;
		if (temp.find_room(option)) {
			int temp1 = option / 10;
			if ((temp1 % 10) == 0) {
				Single_room room_obj;
				room_obj.find_room(temp.floor_file, option);
				if (!room_obj.get_available()) {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        Room is not available        !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t=========================================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
					system("pause");
					continue;
				}
				char username1[50];
				strcpy_s(username1, username);
				cout << username1;
				room_obj.check_into_room(username1);
				currently_staying = true;
				current_room_no = room_obj.get_room_no();
				quit = true;
			}
			else if ((temp1 % 10) == 1) {
				Double_room room_obj;
				room_obj.find_room(temp.floor_file, option);
				if (!room_obj.get_available()) {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        Room is not available        !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t=========================================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
					system("pause");
					continue;
				}
				char username1[50];
				strcpy_s(username1, username);
				cout << username1;
				room_obj.check_into_room(username1);
				currently_staying = true;
				current_room_no = room_obj.get_room_no();
				quit = true;
			}
			else {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        Room does not exist        !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
				system("pause");
				if (Hotel::continue_or_not()) {
					continue;
				}
				else {
					break;
				}
			}
		}
		else {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        Room does not exist        !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
			system("pause");
			if (Hotel::continue_or_not()) {
				continue;
			}
			else {
				break;
			}
		}
	}
}
void Customer::check_out() {
	Floor temp;
	temp.find_room(current_room_no);
	int numberofnights;
	int temp1 = current_room_no / 10;
	if ((temp1 % 10) == 0) {
		Single_room room_obj;
		room_obj.find_room(temp.floor_file, current_room_no);
		numberofnights = room_obj.check_out();
		if (numberofnights == -1) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!      You have not checked out     !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
			system("pause");
		}
		else {
			currently_staying = false;
			current_room_no = 0;
			double current_price = numberofnights * room_obj.get_price();
			price = price + current_price;
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        You have paid " << price << "$        !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
			system("pause");
		}
	}
	else if ((temp1 % 10) == 1) {
		Double_room room_obj;
		room_obj.find_room(temp.floor_file, current_room_no);
		numberofnights = room_obj.check_out();
		if (numberofnights == -1) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!      You have not checked out     !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
			system("pause");
		}
		else {
			currently_staying = false;
			current_room_no = 0;
			double current_price = numberofnights * room_obj.get_price();
			price = price + current_price;
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        You have paid " << price << "$        !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
			system("pause");
		}
	}
}
int Customer::total_customers = 0;

//............................................................................................................................................

int Single_room::get_room_no() const {
		return Room_no;
	}
bool Single_room:: get_available() const {
		return available;
	}
void Single_room :: set_price(double p) {
		price = p;
	}
double Single_room :: get_price()
	{
		return price;
	}
void Single_room :: set_customer_id(char temp[])
	{
		strcpy_s(customer_id, temp);
	}
//string Single_room:: get_customer_id()
	//{
		//return customer_id;
	//}
int Single_room:: get_number_of_nights()
	{
		return number_night;
	}
void Single_room:: set_number_of_nights(int n) {
		number_night = n;
	}
void Single_room:: set_start_date(Date s) {
		start = s;
	}
Date Single_room:: get_start_date() {
		return start;
	}
void Single_room:: calculate_end_date() {
		end = start.add_days(number_night);
	}
Date Single_room:: get_end_date() {
		return end;
	}
void Single_room:: set_room_type(char temp[]) {
		strcpy_s(room_type, temp);
	}
//string Single_room:: get_room_type() const {
//		return room_type;
//	}
void Single_room:: create_room(char file_name[], int tf) { //tf is floor number
		bool quit = false;
		cin.clear();
		Hotel::display();
		Room_no = (tf * 100) + total_rooms;
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**        Create a New Room       **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**     Room Number: " << Room_no << "   **";
		cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter Room data to create a room:\n";
		cout << "\n    \t\t\t\t\t\t\t\t\tRoom Type:         "; cin.get(room_type, 50); cin.ignore();
		available = true;
		strcpy_s(filename, file_name);
		write();
		return;
	}
void Single_room:: write() {
		ofstream room_file;
		room_file.open(filename, ios::app, ios::binary);
		room_file.write((char*)this, sizeof(Single_room));
		room_file.close();
		total_rooms++;
		return;
	}
void Single_room::read(char file_name[]) {
		double price = this->price;
		ifstream room_file;
		room_file.open(file_name, ios::binary);//binary means opening this file in binary mode.
		room_file.read((char*)this, sizeof(Single_room));
		while (!room_file.eof()) {
			if (this->price != price) {
				room_file.read((char*)this, sizeof(Single_room));
				continue;
			}
			else {
				Single_room::display();
				room_file.read((char*)this, sizeof(Single_room));

			}		}
		room_file.close();
		this->price = price;
	}
void Single_room::check_into_room(char temp_id[]) {
		bool quit = false;
		while (!quit) {
			cin.clear();
			Hotel::display();
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Check into Room No: " << Room_no << "  **";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
			cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter the following data to check-in:\n";
			cout << "\n    \t\t\t\t\t\t\t\t\tToday's Date:         ";
			try {
				cout << "\n    \t\t\t\t\t\t\t\t\t\tDay:         "; cin >> start.day;
				cout << "    \t\t\t\t\t\t\t\t\t\tMonth:         "; cin >> start.month;
				cout << "    \t\t\t\t\t\t\t\t\t\tYear:         "; cin >> start.year;
				if (!start.check_date()) {
					throw start.day;
				}
			}
			catch (...) {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				system("pause");
				continue;
			}
			cout << "\n    \t\t\t\t\t\t\t\t\tNumber of nights you want to stay: "; cin >> number_night;
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Your total price will be "<<price * number_night <<"$  **";
			cout <<   "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
			end = start.add_days(number_night - 1);
			strcpy_s(customer_id, temp_id);
			if (Hotel::continue_or_not()) {
				available = false;
				Single_room temp = *this;
				temp.overwrite(Single_room::find_position(Room_no, filename), filename, temp);
				quit = true;
			}
			else {
				quit = true;
			}
		}
	}
int Single_room::check_out() {
	bool quit = false;

	while (!quit) {
		Date dtemp;
		cin.clear();
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Check out of Room No: " << Room_no << "  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t=====================================";
		cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter the following data to check-in:\n";
		cout << "\n    \t\t\t\t\t\t\t\t\tToday's Date:         ";
		try {
			cout << "\n    \t\t\t\t\t\t\t\t\t\tDay:         "; cin >> dtemp.day;
			cout << "    \t\t\t\t\t\t\t\t\t\tMonth:         "; cin >> dtemp.month;
			cout << "    \t\t\t\t\t\t\t\t\t\tYear:         "; cin >> dtemp.year;
			if (!dtemp.check_date()) {
				throw dtemp.day;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
		int number_of_nights_spent = 0;
		Date dtemp2;
		dtemp2 = start;
		while (true) {
			if (dtemp2 == dtemp) {
				break;
			}
			dtemp2 = ++dtemp2;
			++number_of_nights_spent;
		}
		cout << "\n    \t\t\t\t\t\t\t\t\tNumber of nights you have stayed: "; cout << number_of_nights_spent;
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Your total price is " << price * number_of_nights_spent << "$  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
		if (number_night > number_of_nights_spent) {
			cout << "\n    \t\t\t\t\t\t\t\t\tYou are checking out " << number_night - number_of_nights_spent << " nights early.";

		}
		else if (number_night < number_of_nights_spent) {
			cout << "\n    \t\t\t\t\t\t\t\t\tYou are checking out " << number_of_nights_spent - number_night<< " nights late.";
		}
		if (Hotel::continue_or_not()) {
			available = true;
			strcpy_s(customer_id, "");
			Date dtemp3;
			start = dtemp3;
			end = dtemp3;
			Single_room temp = *this;
			temp.overwrite(Single_room::find_position(Room_no, filename), filename, temp);
			quit = true;
			return number_of_nights_spent;
		}
		else {
			quit = true;
		}
	}
	return -1;
}
void Single_room::overwrite(int rnum,char file_name[], Single_room& temp_obj) {
	//int p = find_position(temp_obj.Room_no, temp_obj.filename);
	int position = rnum * sizeof(Single_room);
	fstream fout;
	fout.open(file_name, ios::in | ios::out | ios::binary | ios::ate);
	fout.seekp(0, ios::beg);//beg sets position to the start
	fout.seekp(position, ios::cur);//cur sets position to the object we want to 
	fout.write((char*)&temp_obj, sizeof(Single_room));
	fout.close();
	return;
}
int Single_room::find_position(int rnum, char file_name[]) {
	int position = 0;
	ifstream fin;
	fin.open(filename);
	fin.read((char*)this, sizeof(Single_room));
	while (!fin.eof()) {
		if (rnum == Room_no) {
			break;
		}
		position++;
		fin.read((char*)this, sizeof(Single_room));
	}
	return position;
}
void Single_room::display(){
	if (available) {
		cout << "\n    \t\t\t\t\t\t\t\tRoom no:" << Room_no << "\tPrice: " << price << "$  per night" << "\t\t\t\tRoom Type : " << room_type;
	}
	else {
		cout << "\n    \t\t\t\t\t\t\t\tRoom no:" << Room_no << "\tPrice: " << price << "$  per night" << "\t Room not available" << "\tRoom Type : " << room_type;
	}
}
void Single_room::find_room(char file_name[], int rnum) {
	int number_of_times = 0;
	ifstream room_file;
	room_file.open(file_name, ios::binary);//binary means opening this file in binary mode.
	room_file.read((char*)this, sizeof(Single_room));
	while (!room_file.eof()) {
		if (Room_no == rnum) {
			break;
		}
		room_file.read((char*)this, sizeof(Single_room));
	}
	room_file.close();
}
bool Single_room::room_exist(char file_name[], int rnum) {
	int number_of_times = 0;
	ifstream room_file;
	room_file.open(file_name, ios::binary);//binary means opening this file in binary mode.
	room_file.read((char*)this, sizeof(Single_room));
	while (!room_file.eof()) {
		if (Room_no == rnum) {
			number_of_times++;
			break;
		}
		room_file.read((char*)this, sizeof(Single_room));
	}
	room_file.close();
	if (number_of_times == 0) {
		return false;
	}
	else {
		return true;
	}
}
void Single_room::complete_display() {
	Hotel::display();
	cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Room no: " << Room_no << "  **";
	cout << "\n    \t\t\t\t\t\t\t\t\t\t=====================";
	cout << "\n    \t\t\t\t\t\t\t\t\tPrice per night:   "<< price << "$";
	cout << "\n    \t\t\t\t\t\t\t\t\tRoom Type:         "; cout << room_type;
	if (available) {
		cout << "\n    \t\t\t\t\t\t\t\t\tAvailable:         Yes";
	}
	else {
		cout << "\n    \t\t\t\t\t\t\t\t\tAvailable:         No";
		cout << "\n    \t\t\t\t\t\t\t\t\tCustomer Staying:  "; cout << customer_id;
		cout << "\n    \t\t\t\t\t\t\t\t\tStaying since:     "; start.display();
		cout << "    \t\t\t\t\t\t\t\t\tStaying till:      "; end.display();
		cout << "    \t\t\t\t\t\t\t\t\tPrice to be paid:  " << number_night * price << "$";
	}
	cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
	system("pause");
}

	//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,

int Double_room::get_room_no() const {
	return Room_no;
}
bool Double_room::get_available() const {
	return available;
}
void Double_room::set_price(double p) {
	price = p;
}
double Double_room::get_price()
{
	return price;
}
void Double_room::set_customer_id(char temp[])
{
	strcpy_s(customer_id, temp);
}
//string Double_room::get_customer_id()
//{
//	return customer_id;
//}
int Double_room::get_number_of_nights()
{
	return number_night;
}
void Double_room::set_number_of_nights(int n) {
	number_night = n;
}
void Double_room::set_start_date(Date s) {
	start = s;
}
Date Double_room::get_start_date() {
	return start;
}
void Double_room::calculate_end_date() {
	end = start.add_days(number_night);
}
Date Double_room::get_end_date() {
	return end;
}
void Double_room::set_room_type(char temp[]) {
	strcpy_s(room_type, temp);
}
//string Double_room::get_room_type() const {
//	return room_type;
//}
void Double_room:: create_room(char file_name[], int tf) {
		bool quit = false;
		cin.clear();
		Hotel::display();
		Room_no = (tf * 100) + total_rooms + 10;
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**     Create a New Room    **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t==============================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**     Room Number: " << Room_no << "   **";
		cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter Room data to create a room:\n";
		cout << "\n    \t\t\t\t\t\t\t\t\tRoom Type:         "; cin.get(room_type, 50); cin.ignore();
		available = true;
		strcpy_s(filename, file_name);
		write();
		return;
	}
void Double_room::write() {
		ofstream room_file;
		room_file.open(filename, ios::app, ios::binary);
		room_file.write((char*)this, sizeof(Double_room));
		room_file.close();
		total_rooms++;
		return;
	}
void Double_room::read(char file_name[]) {
		double price = this->price;
		ifstream room_file;
		room_file.open(file_name, ios::binary);//binary means opening this file in binary mode.
		room_file.read((char*)this, sizeof(Double_room));
		while (!room_file.eof()) {
			if (this->price != price) {
				room_file.read((char*)this, sizeof(Double_room));
				continue;
			}
			else {
				Double_room::display();
				room_file.read((char*)this, sizeof(Double_room));
			}
		}
		room_file.close();
		this->price = price;
	}
void Double_room::check_into_room(char temp_id[]) {
	bool quit = false;
	while (!quit) {
		cin.clear();
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Check into Room No: "<< Room_no <<"  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
		cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter the following data to check-in:\n";
		cout << "\n    \t\t\t\t\t\t\t\t\tToday's Date:         ";
		try {
			cout << "\n    \t\t\t\t\t\t\t\t\t\tDay:         "; cin >> start.day;
			cout << "    \t\t\t\t\t\t\t\t\t\tMonth:         "; cin >> start.month;
			cout << "    \t\t\t\t\t\t\t\t\t\tYear:         "; cin >> start.year;
			if (!start.check_date()) {
				throw start.day;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
		cout << "\n    \t\t\t\t\t\t\t\t\tNumber of nights you want to stay: "; cin >> number_night;
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Your total price will be " << price * number_night << "$  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
		end = start.add_days(number_night - 1);
		strcpy_s(customer_id, temp_id);
		if (Hotel::continue_or_not()) {
			available = false;
			Double_room temp = *this;
			temp.overwrite(Double_room::find_position(Room_no, filename), filename, temp);
			quit = true;
		}
		else {
			quit = true;
		}
	}
	}
int Double_room::check_out() {
	bool quit = false;

	while (!quit) {
		Date dtemp;
		cin.clear();
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Check out of Room No: " << Room_no << "  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t==================================";
		cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter the following data to check-in:\n";
		cout << "\n    \t\t\t\t\t\t\t\t\tToday's Date:         ";
		try {
			cout << "\n    \t\t\t\t\t\t\t\t\t\tDay:         "; cin >> dtemp.day;
			cout << "    \t\t\t\t\t\t\t\t\t\tMonth:         "; cin >> dtemp.month;
			cout << "    \t\t\t\t\t\t\t\t\t\tYear:         "; cin >> dtemp.year;
			if (!dtemp.check_date()) {
				throw dtemp.year;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
		int number_of_nights_spent = 0;
		Date dtemp2;
		dtemp2 = start;
		while (true) {
			if (dtemp2 == dtemp) {
				break;
			}
			dtemp2 = ++dtemp2;
			++number_of_nights_spent;
		}
		cout << "\n    \t\t\t\t\t\t\t\t\tNumber of nights you have stayed: "; cout << number_of_nights_spent;
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Your total price is " << price * number_of_nights_spent << "$  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
		if (number_night > number_of_nights_spent) {
			cout << "\n    \t\t\t\t\t\t\t\t\tYou are checking out " << number_night - number_of_nights_spent << " nights early.";

		}
		else if (number_night < number_of_nights_spent) {
			cout << "\n    \t\t\t\t\t\t\t\t\tYou are checking out " << number_of_nights_spent - number_night << " nights late.";
		}
		if (Hotel::continue_or_not()) {
			available = true;
			strcpy_s(customer_id, "");
			Date dtemp3;
			start = dtemp3;
			end = dtemp3;
			Double_room temp = *this;
			temp.overwrite(Double_room::find_position(Room_no, filename), filename, temp);
			quit = true;
			return number_of_nights_spent;
		}
		else {
			quit = true;
		}
	}
	return -1;
}
void Double_room::display(){
	if (available) {
		cout << "\n    \t\t\t\t\t\t\t\tRoom no:" << Room_no << "\tPrice: " << price << "$  per night" << "\t\t\t\tRoom Type : " << room_type;
	}
	else {
		cout << "\n    \t\t\t\t\t\t\t\tRoom no:" << Room_no << "\tPrice: " << price << "$  per night" << "\t Room not available" << "\tRoom Type : " << room_type;
	}
}
void Double_room::overwrite(int rnum, char file_name[], Double_room& temp_obj) {
	int position = rnum * sizeof(Double_room);
	fstream fout;
	fout.open(file_name, ios::in | ios::out | ios::binary | ios::ate);
	fout.seekp(0, ios::beg);//beg sets position to the start
	fout.seekp(position, ios::cur);//cur sets position to the object we want to 
	fout.write((char*)&temp_obj, sizeof(Double_room));
	fout.close();
	return;
}
int Double_room::find_position(int rnum, char file_name[]) {
	int position = 0;
	ifstream fin;
	fin.open(filename);
	fin.read((char*)this, sizeof(Double_room));
	while (!fin.eof()) {
		if (rnum == Room_no) {
			break;
		}
		position++;
		fin.read((char*)this, sizeof(Double_room));
	}
	return position;
}
void Double_room::find_room(char file_name[], int rnum) {
	ifstream room_file;
	room_file.open(file_name, ios::binary);//binary means opening this file in binary mode.
	room_file.read((char*)this, sizeof(Double_room));
	while (!room_file.eof()) {
		if (Room_no == rnum) {
			break;
		}
		room_file.read((char*)this, sizeof(Double_room));
	}
	room_file.close();
}
bool Double_room::room_exist(char file_name[], int rnum) {
	int number_of_times = 0;
	ifstream room_file;
	room_file.open(file_name, ios::binary);//binary means opening this file in binary mode.
	room_file.read((char*)this, sizeof(Double_room));
	while (!room_file.eof()) {
		if (Room_no == rnum) {
			number_of_times++;
			break;
		}
		room_file.read((char*)this, sizeof(Double_room));
	}
	room_file.close();
	if (number_of_times == 0) {
		return false;
	}
	else {
		return true;
	}
}
void Double_room::complete_display() {
	Hotel::display();
	cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Room no: " << Room_no << "  **";
	cout << "\n    \t\t\t\t\t\t\t\t\t\t=====================";
	cout << "\n    \t\t\t\t\t\t\t\t\tPrice per night:   " << price << "$";
	cout << "\n    \t\t\t\t\t\t\t\t\tRoom Type:         "; cout << room_type;
	if (available) {
		cout << "\n    \t\t\t\t\t\t\t\t\tAvailable:         Yes";
	}
	else {
		cout << "\n    \t\t\t\t\t\t\t\t\tAvailable:         No";
		cout << "\n    \t\t\t\t\t\t\t\t\tCustomer Staying:  "; cout << customer_id;
		cout << "\n    \t\t\t\t\t\t\t\t\tStaying since:     "; start.display();
		cout << "    \t\t\t\t\t\t\t\t\tStaying till:      "; end.display();
		cout << "    \t\t\t\t\t\t\t\t\tPrice to be paid:  " << number_night * price << "$";
	}
	cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
	system("pause");
}

	//.....................................................................................................................................

int Single_room::total_rooms = 0;
int Double_room::total_rooms = 0;

void Floor::add_floor() {
		bool quit = false;
		find_total_floors();
		while (!quit) {
			cin.clear();
			Hotel::display();
			int single_r, double_r;
			floor_number = total_floors;
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Add a New Floor  **";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t========================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   The floor number is " << floor_number << "  **";
			cout << "\n\n\n    \t\t\t\t\t\t\tEnter the number of rooms of each type on these floors: ";
			try {
				cout << "\n    \t\t\t\t\t\t\t\t\tSingle Rooms:         "; cin >> single_r; cin.ignore();
				cout << "\n    \t\t\t\t\t\t\t\t\tDouble Rooms:         "; cin >> double_r; cin.ignore();
				if (single_r + double_r > 7) {
					throw single_r;
				}
				else if (single_r + double_r < 7) {
					throw double_r;
				}
				else {
					Room* ptr;
					bool single_rooms_created = false, double_rooms_created = false;
					cout << "\n    \t\t\t\t\t\t\t\t\tEnter Floor file name: "; cin.get(floor_file, 50); cin.ignore();
					for (int i = 0; i < single_r; i++) {
						ptr = new Single_room;
						ptr->create_room(floor_file, floor_number);
						cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!   Single Room: " << i + 1 << " Created  !!";
						cout << "\n    \t\t\t\t\t\t\t\t\t\t===============================";
						cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
						system("pause");
					}
					for (int i = 0; i < double_r; i++) {
						ptr = new Double_room;
						ptr->create_room(floor_file, floor_number);
						cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!   Double Room: " << i + 1 << " Created  !!";
						cout << "\n    \t\t\t\t\t\t\t\t\t\t===============================";
						cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
						system("pause");
					}
					write();
					quit = true;
				}
			}
			catch (...) {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Total rooms must be 7  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!         Try Again        !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t==============================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				system("pause");
			}
		}
		return;
	}
void Floor::write() {
		ofstream floor_file;
		floor_file.open("Floors.dat", ios::app, ios::binary);
		floor_file.write((char*)this, sizeof(Floor));
		floor_file.close();
		total_floors++;
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        Floor Created        !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t";
		system("pause");
		return;
	}
void Floor::find_total_floors() {
		total_floors = 1;
		ifstream floor_file;
		floor_file.open("Floors.dat", ios::binary);//binary means opening this file in binary mode.
		floor_file.read((char*)this, sizeof(Floor));
		if (floor_file) {
			while (!floor_file.eof()) {
				total_floors++;
				floor_file.read((char*)this, sizeof(Floor));

			}
		}
		floor_file.close();
	}
void Floor::read_all_rooms() {
		Hotel::display();
		ifstream floor_file;
		floor_file.open("Floors.dat", ios::binary);//binary means opening this file in binary mode.
		floor_file.read((char*)this, sizeof(Floor));
		if (!floor_file) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        File does not exist        !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
			system("pause");
		}
		else {
			while (!floor_file.eof()) {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t**   All Single Rooms of floor: " << floor_number << "  **";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t=====================================";
				Room* ptr;
				ptr = new Single_room;
				ptr->read(this->floor_file);
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t**   All Double Rooms of floor: " << floor_number << "  **";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t=====================================";
				ptr = new Double_room;
				ptr->read(this->floor_file);
				floor_file.read((char*)this, sizeof(Floor));
			}
		}
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
		system("pause");
		floor_file.close();
	}
bool Floor::find_room(int rnum) {
	bool temp = false;
	Hotel::display();
		ifstream floor_file;
		floor_file.open("Floors.dat", ios::binary);//binary means opening this file in binary mode.
		floor_file.read((char*)this, sizeof(Floor));
		if (!floor_file) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        File does not exist        !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
			system("pause");
		}
		else {
			while (!floor_file.eof()) {
				int temp1 = rnum / 100;
				int temp2 = rnum / 10;
				cout << temp1;
				if (floor_number == temp1) {
					Room *ptr;
					if (temp2 % 10 == 1) {
						ptr = new Double_room;
						temp = ptr->room_exist(this->floor_file, rnum);
						break;
					}
					else if (temp2 % 10 == 0) {
						ptr = new Single_room;
						temp = ptr->room_exist(this->floor_file, rnum);
						break;
					}
					else {
						//cout << rnum;
						cout << "here";
						cout << "\n\n    \t\t\t\t\t\t\t\t\t\t!!        Room does not exist        !!";
						cout << "\n    \t\t\t\t\t\t\t\t\t\t=======================================";
						cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
						system("pause");
						break;
					}
				}
				floor_file.read((char*)this, sizeof(Floor));
			}
		}
		floor_file.close();
		return temp;
}

void Manager::write() {
	ofstream manager_file;
	manager_file.open("manager.dat", ios::binary);
	manager_file.write((char*)this, sizeof(Manager));
	manager_file.close();
	return;
}
void Manager::read() {
	ifstream manager_file;
	manager_file.open("manager.dat", ios::binary);//binary means opening this file in binary mode.
	if (!manager_file) {
		strcpy_s(username, "admin");
		strcpy_s(password, "admin");
	}
	else {
		manager_file.read((char*)this, sizeof(Manager));
	}
	manager_file.close();
	return;
}
void Manager::set_username(char user_temp[]) {
	strcpy_s(username, user_temp);
}
void Manager::set_password(char user_temp[]) {
	strcpy_s(password, user_temp);
}
void Manager::setting() {
	int option;
	bool quit = false;
	while (quit == false) {
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t**   Account Settings  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t=========================";
		cout << "\n\n\n    \t\t\t\t\t\t\tEnter the serial number of attribute you want to change: ";
		cout << "\n    \t\t\t\t\t\t\t\t\t1. Username:      " << username;
		cout << "\n    \t\t\t\t\t\t\t\t\t2. Password:      ******";
		cout << "\n    \t\t\t\t\t\t\t\t\t0. Quit";
		cout << "\n\n    \t\t\t\t\t\t\tEnter the serial number of option you want to choose: ";
		cin >> option;
		cin.ignore();
		switch (option)
		{
		case 0:
			quit = true;
			write();
			break;
		case 1:
		{
			cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";
			char temp[50];
			cin.clear();
			try {
				cout << "\n    \t\t\t\t\t\t\t\t\tYour username:         "; cin.get(temp, 50); cin.ignore();
				if (sizeof(temp) < 4) {
					throw temp;
				}
				else {
					set_username(temp);
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Task Completed  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
			}
			catch (...) {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Username too short  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t===========================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				system("pause");
			}
			break;
		}
		case 2:
		{
			cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your data to change:\n";
			char temp[50];
			cin.clear();
			try {
				cout << "\n    \t\t\t\t\t\t\t\t\tYour username:         "; cin.get(temp, 50); cin.ignore();
				if (sizeof(temp) < 4) {
					throw temp;
				}
				else {
					set_password(temp);
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Task Completed  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
			}
			catch (...) {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Password too short  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t===========================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				system("pause");
			}
			break;
		}
		default:
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			break;
		}
	}
}
void Manager::log_in() {
	bool quit = false;
	while (quit == false) {
		cin.ignore();
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**   Log in to your Account  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t===============================";
		cout << "\n\n\n    \t\t\t\t\t\t\tPlease Enter your username and Id to log in.\n";
		cout << "\n    \t\t\t\t\t\t\t\t\tYour username:         "; cin.get(username, 50); cin.ignore();
		cout << "\n    \t\t\t\t\t\t\t\t\tYour password:         "; cin.get(password, 50); cin.ignore();
		//cout << "\n    \t\t\t\t\t\t\t\t\tYour ID:     "; cin >> id; cin.ignore();
		Manager temp;
		temp.read();
		cout << username;
		cout << password;
		cout << temp.username;
		cout << temp.password;
		if (*this == temp) {
			cout << "\n\n\n    \t\t\t\t\t\t\t\t\t\t!!   Logged in successfully   !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t================================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
			main_page();
			quit = true;
		}
		else {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t!!   username or password is wrong  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t!!             Try Again            !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t======================================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t   ";
			if (Hotel::continue_or_not()) {
				continue;
			}
			else {
				quit = true;
			}
		}
	}
}
//void Manager::find_user() {
//	char temp_user[50];
//	cin.clear();
//	cout << "\n    \t\t\t\t\t\t\tEnter the username of Customer: "; cin.get(temp_user, 50);
//	Customer temp;
//	if (temp.user_available(temp_user, 1)) {
//		Hotel::display();
//		temp.display();
//	}
//	else {
//		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   User Does not exist  !!";
//		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!        Try Again       !!";
//		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t==========================";
//		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
//		system("pause");
//	}
//}
void Manager::main_page() {
	int option;
	bool quit = false;
	while (quit == false) {
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t**   User Menu  **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t==================";
		cout << "\n\n\n    \t\t\t\t\t\t\t\t\t1. Create a new Floor";
		cout << "\n    \t\t\t\t\t\t\t\t\t2. View All Rooms";
		cout << "\n    \t\t\t\t\t\t\t\t\t3. View specific room";
		cout << "\n    \t\t\t\t\t\t\t\t\t4. Account settings";
		cout << "\n    \t\t\t\t\t\t\t\t\t5. View Cafeteria Menu";
		cout << "\n    \t\t\t\t\t\t\t\t\t6. Change Cafeteria Menu";
		cout << "\n    \t\t\t\t\t\t\t\t\t7. Add to Cafeteria Menu";
		cout << "\n    \t\t\t\t\t\t\t\t\t0. Quit";
		cout << "\n\n    \t\t\t\t\t\t\tEnter the serial number of option you want to choose: ";
		cin >> option;
		switch (option)
		{
		case 0:
			quit = true;
			break;
		case 1:
		{
			Floor temp;
			temp.add_floor();
		}
		break;
		case 2:
		{
			Floor temp;
			temp.read_all_rooms();
		}
			break;
		case 3:
		{
			int room;
			Floor temp;
			temp.read_all_rooms();
			cout << "\n    \t\t\t\t\t\t\tEnter the room number of room you want to view: "; cin >> room;
			temp.find_room(room);
			if ((room / 10) % 10 == 1) {
				Double_room temp_room;
				temp_room.find_room(temp.floor_file, room);
				temp_room.complete_display();
			}
			else if ((room / 10) % 10 == 0) {
				Single_room temp_room;
				temp_room.find_room(temp.floor_file, room);
				temp_room.complete_display();
			}
			else {
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				system("pause");
			}
		}break;
		case 4:
			setting();
			break;
		case 5:
		{
			Cafeteria temp;
			temp.menu();
		}
			break;
		case 6:
		{
			Cafeteria temp;
			temp.overwrite();
		}
		break;
		case 7:
		{
			Cafeteria temp;
			temp.add_new_item();
		}
		break;
		default:
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			break;
		}
	}
}
bool Manager::operator == (const Manager obj) {
	if (strcmp(username, obj.username) == 0 && strcmp(password, obj.password) == 0) {
		return true;
	}
	else {
		return false;
	}
}

int Floor::total_floors = 1;

void Cafeteria::menu() {
	Food temp;
	Drinks dtemp;
	Hotel::display();
	cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**           Cafeteria           **";
	cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
	cout << "\n\n\n    \t\t\t\t\t\t\t\tThis is the menu of Cafeteria:\n";
	temp.food_menu();
	dtemp.drink_menu();
	cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
	system("pause");
}
void Cafeteria::add_new_item() {
	bool quit = false;
	int option;
	while (!quit) {
		cin.clear();
		Hotel::display();
		menu();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**          Add new Item         **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t1. Food";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t2. Drinks";
		try {
			cout << "\n\n    \t\t\t\t\t\t\t\t\tEnter the serial number of type of item you want to add or 0 to exit: "; cin >> option;
			switch (option)
			{
			case 0:
				quit = true;
				break;
			case 1:
			{
				Food temp;
				temp.add_food();
			}
			break;
			case 2:
			{
				Drinks temp;
				temp.add_drink();
			}
			break;
			default:
				throw option;
				break;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
		break;
	}
	return;
}
void Cafeteria::overwrite() {
	bool quit = false;
	int option;
	while (!quit) {
		cin.clear();
		Hotel::display();
		menu();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**       Overwrite the Item      **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
		cout << "\n    \t\t\t\t\t\t\t\t\t1. Food";
		cout << "\n    \t\t\t\t\t\t\t\t\t2. Drink";
		try {
			cout << "\n    \t\t\t\t\t\t\t\t\tEnter the serial number of type of item you want to change, or 0 to exit: "; cin >> option;
			switch (option)
			{
			case 0:
				quit = true;
				break;
			case 1:
			{
				Food temp;
				temp.change_food();
			}
			break;
			case 2:
			{
				Drinks temp;
				temp.change_drink();
			}
			break;
			default:
				throw option;
				break;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
	}
	return;
}
void Cafeteria::order() {
	bool quit = false;
	int option;
	while (!quit) {
		cin.clear();
		Hotel::display();
		menu();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**       Order the Item      **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t===============================";
		cout << "\n    \t\t\t\t\t\t\t\t\t1. Food";
		cout << "\n    \t\t\t\t\t\t\t\t\t2. Drink";
		try {
			cout << "\n    \t\t\t\t\t\t\t\t\tEnter the serial number of type of item you want to change, or 0 to exit: "; cin >> option;
			switch (option)
			{
			case 0:
				quit = true;
				break;
			case 1:
			{
				Food temp;
				temp.order_food();
			}
			break;
			case 2:
			{
				Drinks temp;
				temp.order_drink();
			}
			break;
			default:
				throw option;
				break;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
	}
	return;
}

void Food::add_food() {
	bool quit = false;
	while (!quit) {
		cin.clear();
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**       Add a new Food          **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
		cout << "\n\n\n    \t\t\t\t\t\t\tPlease enter the following data:\n";
		try {
			cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tTitle of food:         "; cin.get(foodname, 50); cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tPrice per serving:     "; cin >> price; cin.ignore();
			if (price <= 0 || !foodname) {
				throw price;
			}
			write();
			break;
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
	}
	return;
}
void Food::write() {
	ofstream food_file;
	food_file.open("food.dat", ios::app, ios::binary);
	food_file.write((char*)this, sizeof(Food));
	food_file.close();
	return;
}
void Food::read() {
	ifstream food_file;
	food_file.open("food.dat", ios::binary);
	int number = 1;
	if (!food_file) {
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   File Does Not Exist  !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
		system("pause");
	}
	else {
		food_file.read((char*)this, sizeof(Food));
		while (!food_file.eof()) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t" << number << ". ";
			display();
			number++;
			food_file.read((char*)this, sizeof(Food));
		}
	}
}
void Food::read_specific(int pos) {
	ifstream food_file;
	food_file.open("food.dat", ios::binary);
	int number = 1;
	if (!food_file) {
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   File Does Not Exist  !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
		system("pause");
	}
	else {
		food_file.read((char*)this, sizeof(Food));
		for (int i = 0; i < pos; i++) {
			food_file.read((char*)this, sizeof(Food));
		}
	}
}
void Food::food_menu() {
	cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**              Food             **";
	cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
	read();
}
void Food::display() const {
	cout << "Food Name:         " << foodname << "\t\tPrice: " << price << "$";
}
void Food::setting() {
	bool quit = false;
	int option;
	while (quit == false) {
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**          Food Detail          **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
		cout << "\n\n\n    \t\t\t\t\t\t\t\t"; display();
		try {
			cout << "\n\n    \t\t\t\t\t\t\t\t\tEnter 1 to change Food name, 2 to change price and 0 to exit: "; cin >> option;
			if (option > 0 || option < 2) {
				switch (option)
				{
				case 0:
					quit = true;
					break;
				case 1:
				{
					char temp[50];
					cin.ignore();
					cout << "\n    \t\t\t\t\t\t\t\t\tTitle of food:         "; cin.get(temp, 50); cin.clear();
					Food temp1;
					temp1 = *this;
					strcpy_s(foodname, temp);
					int pos = temp1.find_position(temp1.foodname);
					overwrite(pos, *this);

				}
				break;
				case 2:
				{
					double p;
					cout << "\n    \t\t\t\t\t\t\t\t\tPrice of food:         "; cin >> p;
					if (p <= 0) {
						throw p;
					}
					else {
						Food temp1;
						temp1 = *this;
						price = p;
						int pos = temp1.find_position(temp1.foodname);
						temp1.overwrite(pos, *this);
					}
				}
				break;
				default:
					throw option;
					break;
				}
			}
			else {
				throw option;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
		}
	}
}
int Food::find_position(char temp[]) {
	int position = 0;
	ifstream fin;
	cout << "here";
	fin.open("food.dat", ios::binary);
	fin.read((char*)this, sizeof(Food));
	cout << foodname;
	cout << temp;
	while (!fin.eof()) {
		if (strcmp(foodname, temp) == 0) {
			break;
		}
		position++;
		fin.read((char*)this, sizeof(Food));
	}
	return position;
}
void Food::overwrite(int rnum, Food &fobj) {
	int position = rnum * sizeof(Food);
	fstream fout;
	fout.open("food.dat", ios::in | ios::out | ios::binary | ios::ate);
	fout.seekp(0, ios::beg);//beg sets position to the start
	fout.seekp(position, ios::cur);//cur sets position to the object we want to 
	fout.write((char*)&fobj, sizeof(Food));
	fout.close();
	return;
}
void Food::order_food() {
	bool quit = false;
	int option;
	while (!quit) {
		cin.clear();
		Hotel::display();
		food_menu();
		try {
			cout << "\n    \t\t\t\t\t\t\t\t\tEnter the serial number of item you want to change (Enter -1 to exit): "; cin >> option;
			if (option == -1) {
				break;
			}
			else if (option < 0) {
				throw option;
			}
			else if (option > 0) {
				int quantity;
				double tprice = 0;
				cout << "\n    \t\t\t\t\t\t\t\t\tEnter the quantity of this specific item: "; cin >> quantity;
				read_specific(option - 1);
				tprice = price * quantity;
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   You have to pay " << tprice << "$  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t=============================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				if (Hotel::continue_or_not()) {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Your food is on the way  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t================================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				else {
					quit = true;
				}
			}
			else {
				throw option;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
	}
	return;
}
void Food::change_food() {
	bool quit = false;
	int option;
	while (!quit) {
		cin.clear();
		Hotel::display();
		food_menu();
		try {
			cout << "\n    \t\t\t\t\t\t\t\t\tEnter the serial number of item you want to order (Enter -1 to exit): "; cin >> option;
			if (option == -1) {
				break;
			}
			else if (option < 0) {
				cout << "here";
				throw option;
			}
			else if (option > 0) {
				read_specific(option - 1);
				setting();
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
	}
	return;
}

void Drinks::add_drink() {
	bool quit = false;
	while (!quit) {
		cin.clear();
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**       Add a new Drink          **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
		cout << "\n\n\n    \t\t\t\t\t\t\tPlease enter the following data:\n";
		try {
			cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tTitle of drink:         "; cin.get(drinkname, 50); cin.ignore();
			cout << "\n    \t\t\t\t\t\t\t\t\tPrice per serving:     "; cin >> price; cin.ignore();
			if (price <= 0 || !drinkname) {
				throw price;
			}
			write();
			break;
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
	}
	return;
}
void Drinks::write() {
	ofstream food_file;
	food_file.open("drink.dat", ios::app, ios::binary);
	food_file.write((char*)this, sizeof(Drinks));
	food_file.close();
	return;
}
void Drinks::read() {
	ifstream food_file;
	food_file.open("drink.dat", ios::binary);
	int number = 1;
	if (!food_file) {
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   File Does Not Exist  !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
		system("pause");
	}
	else {
		food_file.read((char*)this, sizeof(Drinks));
		while (!food_file.eof()) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t" << number << ". ";
			display();
			number++;
			food_file.read((char*)this, sizeof(Drinks));
		}
	}
}
void Drinks::read_specific(int pos) {
	ifstream food_file;
	food_file.open("drink.dat", ios::binary);
	int number = 1;
	if (!food_file) {
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   File Does Not Exist  !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
		system("pause");
	}
	else {
		food_file.read((char*)this, sizeof(Drinks));
		for (int i = 0; i < pos; i++) {
			food_file.read((char*)this, sizeof(Drinks));
		}
	}
}
void Drinks::drink_menu() {
	cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**              Drinks             **";
	cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
	read();
}
void Drinks::display() const {
	cout << "Drink Name:         " << drinkname << "\t\tPrice: " << price << "$";
}
void Drinks::setting() {
	bool quit = false;
	int option;
	while (quit == false) {
		Hotel::display();
		cout << "\n\n    \t\t\t\t\t\t\t\t\t\t**          Detail Detail          **";
		cout << "\n    \t\t\t\t\t\t\t\t\t\t===================================";
		cout << "\n\n\n    \t\t\t\t\t\t\t\t"; display();
		try {
			cout << "\n\n    \t\t\t\t\t\t\t\t\tEnter 1 to change drink name, 2 to change price and 0 to exit: "; cin >> option;
			if (option > 0 || option < 2) {
				switch (option)
				{
				case 0:
					quit = true;
					break;
				case 1:
				{
					char temp[50];
					cin.ignore();
					cout << "\n    \t\t\t\t\t\t\t\t\tTitle of drink:         "; cin.get(temp, 50); cin.clear();
					Drinks temp1;
					temp1 = *this;
					strcpy_s(drinkname, temp);
					int pos = temp1.find_position(temp1.drinkname);
					overwrite(pos, *this);

				}
				break;
				case 2:
				{
					double p;
					cout << "\n    \t\t\t\t\t\t\t\t\tPrice of drink:         "; cin >> p;
					if (p <= 0) {
						throw p;
					}
					else {
						Drinks temp1;
						temp1 = *this;
						price = p;
						int pos = temp1.find_position(temp1.drinkname);
						temp1.overwrite(pos, *this);
					}
				}
				break;
				default:
					throw option;
					break;
				}
			}
			else {
				throw option;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
		}
	}
}
int Drinks::find_position(char temp[]) {
	int position = 0;
	ifstream fin;
	fin.open("drink.dat", ios::binary);
	fin.read((char*)this, sizeof(Drinks));
	while (!fin.eof()) {
		if (strcmp(drinkname, temp) == 0) {
			break;
		}
		position++;
		fin.read((char*)this, sizeof(Drinks));
	}
	return position;
}
void Drinks::overwrite(int rnum, Drinks& fobj) {
	int position = rnum * sizeof(Food);
	fstream fout;
	fout.open("drink.dat", ios::in | ios::out | ios::binary | ios::ate);
	fout.seekp(0, ios::beg);//beg sets position to the start
	fout.seekp(position, ios::cur);//cur sets position to the object we want to 
	fout.write((char*)&fobj, sizeof(Drinks));
	fout.close();
	return;
}
void Drinks::change_drink() {
	bool quit = false;
	int option;
	while (!quit) {
		cin.clear();
		Hotel::display();
		drink_menu();
		try {
			cout << "\n    \t\t\t\t\t\t\t\t\tEnter the serial number of item you want to change (Enter -1 to exit): "; cin >> option;
			if (option == -1) {
				break;
			}
			else if (option < 0) {
				cout << "here";
				throw option;
			}
			else if (option > 0) {
				read_specific(option - 1);
				setting();
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
	}
	return;
}
void Drinks::order_drink() {
	bool quit = false;
	int option;
	while (!quit) {
		cin.clear();
		Hotel::display();
		drink_menu();
		try {
			cout << "\n    \t\t\t\t\t\t\t\t\tEnter the serial number of item you want to change (Enter -1 to exit): "; cin >> option;
			if (option == -1) {
				break;
			}
			else if (option < 0) {
				throw option;
			}
			else if (option > 0) {
				int quantity;
				double tprice = 0;
				cout << "\n    \t\t\t\t\t\t\t\t\tEnter the quantity of this specific item: "; cin >> quantity;
				read_specific(option - 1);
				tprice = price * quantity;
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   You have to pay " << tprice << "$  !!";
				cout << "\n    \t\t\t\t\t\t\t\t\t\t\t=============================";
				cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
				if (Hotel::continue_or_not()) {
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Your food is on the way  !!";
					cout << "\n    \t\t\t\t\t\t\t\t\t\t\t================================";
					cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
					system("pause");
				}
				else {
					quit = true;
				}
			}
			else {
				throw option;
			}
		}
		catch (...) {
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			continue;
		}
	}
	return;
}

int main() {
	bool quit = false;
	int option;
	Hotel obj1;
	Customer customer;
	while (quit == false) {
		obj1.display();
		obj1.main_page();
		cout << "\n\n\n    \t\t\t\t\t\t\tPlease enter the serial number of the option you want to choose: ";
		cin >> option;
		cin.ignore();
		switch (option)
		{
		case 0:
			quit = true;
			break;
		case 1:
			customer.register_account();
			break;
		case 2:
			customer.log_in();
			break;
		case 3:
		{
			Manager manager;
			manager.read();
			manager.log_in();
		}
			break;
		case 4:
			ShellExecute(0, 0, L"https://www.serenahotels.com/islamabad", 0, 0, SW_SHOW); //Opens website
			break;
		case 5:
		{
			Floor temp;
			temp.read_all_rooms();
			break;
		}
		default:
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t\t!!   Invalid Input  !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t!!     Try Again    !!";
			cout << "\n    \t\t\t\t\t\t\t\t\t\t\t======================";
			cout << "\n\n    \t\t\t\t\t\t\t\t\t\t   ";
			system("pause");
			break;
		}

	}
	return 0;
}