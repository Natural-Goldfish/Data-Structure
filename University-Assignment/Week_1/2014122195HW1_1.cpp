#include "2014122195HW1_3.h"

const std::string default_message = "Welcome!, Write your major, student number, name and the birtday(yyyy/mm/dd)! : ";
int main() {
	std::string input;
	std::vector<std::string> temp_vector;
	std::cout << default_message;
	std::getline(std::cin, input);
	date d;
	student me;
	temp_vector = split(input, ',');
	me.get_info(temp_vector, d);

	std::cout << ">>";
	me.print_info();
	d.print_present_time();
	me.print_age();


	return 0;
}