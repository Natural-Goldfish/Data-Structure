#include "2014122195HW2_3.h"

const std::string default_message = "ȯ���մϴ�! �а���, �й�, �̸�, �������(yyyy/mm/dd)�� �Է��ϼ��� >";

int main() {
	std::string input;
	std::vector<std::string> temp_vector;
	date d;
	student me;
	int again = 0;
	do {
		try {
			std::cout << default_message;
			std::getline(std::cin, input);
			temp_vector = split(input, ',');
			again = me.get_info(temp_vector, d);
		}
		catch (int a) {
			again = 1;
		}
	} while (again == 1);
	
	std::cout << ">>";
	me.print_info();
	d.print_present_time();
	me.print_age();

	std::cin >> again;
	return 0;
}