#pragma once
#ifndef HW1_3_H
#define HW1_3_H
#include <iostream>
#include <vector>
#include <string>
#include <time.h>
#include <sstream>

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
};

class student {
private:
	std::string major;
	std::string student_number;
	std::string name;
	std::string birthday;
	int age;

public:
	student();
	void get_info(std::vector<std::string>, date);
	void get_birthday(std::string, date);
	void print_info();
	void print_age();
};

std::vector<std::string> split(std::string, char);


#endif
