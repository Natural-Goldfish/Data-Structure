#pragma once
#ifndef HW1_3_H
#define HW1_3_H
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <sstream>
#include <stdlib.h>
//#include <atlcore.h>

/////////////////////////////////////////B_DATA CLASS///////////////////////////////////////////
class b_data {

public:
	int year;
	int month;
	int day;
	b_data();
};
/////////////////////////////////////////DATE CLASS///////////////////////////////////////////
class date {

private:
	int year;
	int month;
	int day;
	int hour;
	int min;
	int sec;

	std::string present_time;

public:

	date();
	void renewal_time();
	void print_present_time();
	
	int print_cur_year();
	int print_cur_month();
	int print_cur_day();

};


/////////////////////////////////////////STUDENT CLASS///////////////////////////////////////////
class student {
private:
	std::string major;
	std::string student_number;
	std::string name;
	std::string birthday;
	b_data birthday_int;
	int age;

public:
	student();
	int get_info(std::vector<std::string>, date);

	void get_major(std::string);
	void get_student_number(std::string);
	void get_name(std::string);
	void get_birthday(std::string, date);
	void get_birth_int(std::string, std::string, std::string);
	void get_age(b_data, date);

	void print_info();
	void print_age();
};

std::vector<std::string> split(std::string, char);


#endif
