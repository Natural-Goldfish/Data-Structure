#include "2014122195HW2_3.h"

const int KAU_STUDENT_NUMBER_LENGTH = 11;
const std::string EXCEPTION = ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> PLEASE CHECK THE INPUT FORMAT AND TRY AGAIN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<\n";

enum {	_start = 1, 
		_end = 2,
		KOREAN_BEGIN = 0xAC00,
		KOREAN_END = 0xD7A3,
		NUMBER_ZERO = 0x30,
		NUMBER_NINE = 0x39,
		SPACE = 32};

/////////////////////////// FUNCTION PRE-DEFINE //////////////////////////

int find_(std::vector<wchar_t>, int);
std::vector<wchar_t> string2vector_unicode(std::string);

//////////////////////////      DATE CLASS      //////////////////////////

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
	this->present_time = " 현재 "
		+ std::to_string(this->year) + "년 "
		+ std::to_string(this->month) + "월 "
		+ std::to_string(this->day) + "일 ";
	std::cout << this->present_time;
}

int date::print_cur_year() {
	this->renewal_time();
	return this->year;
}

int date::print_cur_month() {
	this->renewal_time();
	return this->month;
}

int date::print_cur_day() {
	this->renewal_time();
	return this->day;
}
////////////////////////// B_DATA  CLASS //////////////////////////

b_data::b_data() {
	this->year = 0;
	this->month = 0;
	this->day = 0;
}

////////////////////////// STUDENT CLASS //////////////////////////

student::student() {
	this->major = "과가 없습니다.";
	this->student_number = "학번이 없습니다.";
	this->name = "홍길동";
	this->birthday = "0000/00/00";
	this->age = 0;
	this->birthday_int = b_data::b_data();
}

void student::get_major(std::string _major) {
	std::vector<wchar_t> w_target = string2vector_unicode(_major);
	int start = find_(w_target, _start);
	int end = find_(w_target, _end);

	for (int i = start; i < end + 1; i++) {
		if((w_target[i] < KOREAN_BEGIN && w_target[i] != SPACE) || (w_target[i] > KOREAN_END && w_target[i] != SPACE)){
			std::cout << "THAT IS NOT CORRECT KOREAN FOR MAJOR INFORMATION" << std::endl;
			throw EXCEPTION;
		}
	}
	this->major = _major;
}

void student::get_student_number(std::string _student_number) {

	std::vector<wchar_t> w_target = string2vector_unicode(_student_number);

	int start = find_(w_target, _start);
	int end = find_(w_target, _end);
	int student_number_length = end - start + 2;

	if (student_number_length != KAU_STUDENT_NUMBER_LENGTH) { 
		std::cout << "KOREA AEROSPACE UNIVERSITY'S STUDENT NUMBER IS CONSTRUCTED BY 10 LETTERS." << std::endl;
		throw EXCEPTION; 
	}
	for (int i = start; i < end + 1; i++) {
		if (!(NUMBER_ZERO <= w_target[i] && w_target[i] <= NUMBER_NINE)) {
			std::cout << "Only Number" << std::endl;
			throw EXCEPTION;
		}
	}
	this->student_number = _student_number;
}

void student::get_name(std::string _name) {

	std::vector<wchar_t> w_target = string2vector_unicode(_name);
	int start = find_(w_target, _start);
	int end = find_(w_target, _end);
	
	for (int i = start; i < end+1; i++) {
		if ( w_target[i] < KOREAN_BEGIN || w_target[i] > KOREAN_END) {
			if (w_target[i] == SPACE) {
				std::cout << "NO SPACE IN THE NAME" << std::endl;
				throw EXCEPTION;
			}
			std::cout << "ONLY KOREAN NAME IS AVAILABLE" << std::endl;
			throw EXCEPTION;
		}
	}
	this->name = _name;
}

void student::get_birthday(std::string birthday, date d) {
	std::vector<std::string> temp = split(birthday, '/');
	if (temp.size() != 3) { 
		std::cout << "YOUR BIRTHDAY INPUT FORMAT IS NOT AVAILABLE." << std::endl;
		throw EXCEPTION; 
	}
	else {
		this->get_birth_int(temp[0], temp[1], temp[2]);
		this->birthday = temp[0] + "년 " + temp[1] + "월 " + temp[2] + "일생";
		this->get_age(birthday_int, d);
	}
}

void student::print_info() {
	std::cout << this->major << this->student_number << this->name << "님" << this->birthday;
}

void student::print_age() {
	std::cout <<  this->age << "세 입니다.";
}

void student::get_age(b_data _birthday_int, date d) {
	if (d.print_cur_year() < _birthday_int.year) { 
		std::cout << "YOU ARE BORN ON THE FUTURE." << std::endl;
		throw EXCEPTION; 
	}
	if (d.print_cur_year() == _birthday_int.year && d.print_cur_month() < _birthday_int.month) { 
		std::cout << "YOU ARE BORN ON THE FUTURE." << std::endl;
		throw EXCEPTION;
	}
	if (d.print_cur_year() == _birthday_int.year && d.print_cur_month() == _birthday_int.month && d.print_cur_day() < _birthday_int.day) { 
		std::cout << "YOU ARE BORN ON THE FUTURE." << std::endl;
		throw EXCEPTION;
	}

	this->age = d.print_cur_year() - _birthday_int.year + 1;
}

void student::get_birth_int(std::string _year, std::string _month, std::string _day) {
	int _year_int = atoi(_year.c_str());
	int _month_int = atoi(_month.c_str());
	int _day_int = atoi(_day.c_str());

	if (_year_int < 0) {
		std::cout << "YEAR MUST BE BIGGER THAN 0" << std::endl;
		throw EXCEPTION;
	}
	if (_month_int < 1 || _month_int > 12) {
		std::cout << "MONTH MUST BE BIGGER THAN 0 AND LESS THAN 13." << std::endl;
		throw EXCEPTION;
	}
	if ((_month_int !=2 && _day_int < 1) || (_month_int !=2 && _day_int > 31)) {
		std::cout << "EXCEPT FOR FEB, DAY MUST BE BIGGER THAN 0 AND LESS THAN 32." << std::endl;
		throw EXCEPTION;
	}
	if ((_month_int == 2 && _day_int < 1) || (_month_int ==2 && _day_int > 29)) {
		std::cout << "ON FEB, DAY MUST BE BIGGER THAN 0 AND LESS THAN 30." << std::endl;
		throw EXCEPTION;
	}
	this->birthday_int.year = _year_int;
	this->birthday_int.month = _month_int;
	this->birthday_int.day = _day_int;
}

int student::get_info(std::vector<std::string> information_list, date d) {
	try {
		int list_size = information_list.size();
		if (list_size != 4) {
			std::cout << "INPUT MUST HAVE FOUR INFORMATION (MAJOR, STUDENT NUMBER, NAME, BIRTHDAY)" << std::endl;
			std::cout << "ALSO EACH SECTION IS DISTINGUISED BY \",\"" << std::endl;
			std::cout << "IN THE CASE YOU WRITE THE BIRTHDAY, THE FORMAT IS YEAR/MONTH/DAY." << std::endl;
			throw EXCEPTION; 
		}
		else {
			this->get_major(information_list[0]);
			this->get_student_number(information_list[1]);
			this->get_name(information_list[2]);
			this->get_birthday(information_list[3], d);
		}
	}
	catch (std::string exp) {
		std::cout << EXCEPTION << std::endl;
		return 1;
	}
}
//////////////////////////        SPLIT FUNCTION        //////////////////////////

std::vector<std::string> split(std::string target, char keyward) {
	std::vector<std::string> output;
	std::string temp;
	std::istringstream _istringstream(target);
	while (std::getline(_istringstream, temp, keyward)) {
		output.push_back(temp);
	}
	return output;
}

//////////////////////////     MULTYBYTE TO WIDE     //////////////////////////
std::vector<wchar_t> string2vector_unicode(std::string _target) {

	setlocale(LC_ALL, "");

	size_t sizeDes = 0;
	mbstowcs_s(&sizeDes, nullptr, 0, _target.c_str(), 0);
	wchar_t * wchar_temp = new wchar_t[sizeDes];
	wmemset(wchar_temp, 0, sizeDes);
	mbstowcs_s(&sizeDes, wchar_temp, sizeDes, _target.c_str(), sizeDes);
	std::wstring w_string = wchar_temp;
	delete[] wchar_temp;
	std::vector<wchar_t> result(w_string.begin(), w_string.end());

	/*
	USES_CONVERSION;
	std::wstring temp(A2W(_target.c_str()));

	std::vector<wchar_t> result(temp.begin(), temp.end());
	*/
	return result;
}

////////////////////////// FINE THE START AND END POINT //////////////////////////
int find_(std::vector<wchar_t> _temp, int _target) {

	int target = 0;
	switch (_target) {
	case _start:
		for (int i = 0; i < _temp.size(); i++) {
			if (_temp[i] == 32) target++;
			else break;
		}
		break;
	case _end:
		target = _temp.size() - 1;
		for (int i = _temp.size() - 1; i > 0; i--) {
			if (_temp[i] == 32) target--;
			else break;
		}
		break;
	}
	return target;
}