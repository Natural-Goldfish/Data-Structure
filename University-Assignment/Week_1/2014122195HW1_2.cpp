#include "2014122195HW1_3.h"

////////////////////////// DATE CLASS //////////////////////////

date::date() {
	this->year = 2020;
	this->month = 03;
	this->day = 20;
	this->hour = 00;
	this->min = 00;
	this->sec = 00;
};

void date::renewal_time() {
	struct tm t;
	time_t timer;
	timer = time(NULL);
	localtime_s(&t, &timer);

	this->year = t.tm_year + 1900;
	this->month = t.tm_mon + 1;
	this->day = t.tm_mday;
	this->hour = t.tm_hour;
	this->min = t.tm_min;
	this->sec = t.tm_sec;

}

void date::print_present_time() {
	this->renewal_time();
	this->present_time = " ���� "
						+ std::to_string(this->year) + "�� " 
						+ std::to_string(this->month) + "�� "
						+ std::to_string(this->day) + "�� "
						+ std::to_string(this->hour) + "�� "
						+ std::to_string(this->min) + "�� ";
	std::cout << this->present_time;
}

int date::print_cur_year() {
	this->renewal_time();
	return this->year;
}

////////////////////////// STUDENT CLASS //////////////////////////

student::student() {
	this->major = "���� �����ϴ�.";
	this->student_number = "�й��� �����ϴ�.";
	this->name = "ȫ�浿";
	this->birthday = "0000/00/00";
	this->age = 0;
}

void student::get_info(std::vector<std::string> information_list, date d) {
	if (information_list.size() != 4) {
		std::cout << "�߸��� ����";
	} 
	else {
		this->major = information_list[0];
		this->student_number = information_list[1];
		this->name = information_list[2];
		this->get_birthday(information_list[3], d);

	}
}

void student::get_birthday(std::string birthday, date d) {
	std::vector<std::string> temp = split(birthday, '/');
	this->birthday = temp[0] + "�� " + temp[1] + "�� " + temp[2] + "�ϻ�";
	this->age = d.print_cur_year() - atoi(temp[0].c_str()) + 1;
}

void student::print_info() {
	std::cout << this->major << this->student_number << this->name << "��" << this->birthday;
}

void student::print_age() {
	std::cout <<  this->age << "�� �Դϴ�.";
}

////////////////////////// SPLIT FUNCTION //////////////////////////

std::vector<std::string> split(std::string target, char keyward) {
	std::vector<std::string> output;
	std::string temp;
	std::istringstream _istringstream(target);
	while (std::getline(_istringstream, temp, keyward)) {
		output.push_back(temp);
	}
	return output;
}
