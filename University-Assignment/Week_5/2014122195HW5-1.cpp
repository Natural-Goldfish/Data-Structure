#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <vector>
#include <utility>

// ==================================          ERROR MESSAGES         ================================== //

const std::string EXCEPTION_EXIT = "ERROR_EXIT";
const std::string EXCEPTION_AGAIN = "ERROR_AGAIN";
const std::string NO_PROBLEM = "NO ERROR";

// ================================== CLASS AND FUNCTION DESCRIPTION  ================================== //

class Polynomial;

std::vector<std::string> split(std::string target, const char* keyword);
std::vector<std::pair<int, int>> combine(const std::vector<std::pair<int, int>>& target);

void input_function(Polynomial& Ax, Polynomial& Bx, Polynomial& Cx, int& x);
void output_function(const Polynomial& Ax, const Polynomial& Bx, const Polynomial& Cx, const Polynomial& Tx, const Polynomial& Dx, const int x);
void make_sorted_pair_list(std::vector<std::pair<int, int>> * target);

template <typename T>
inline void swap(T * A, T * B);
inline void move_pair_list(std::vector<std::pair<int, int>> * A, const std::vector<std::pair<int, int>> B);

// ==================================         POLYNOMIAL CLASS         ================================== //

class Polynomial {
private:
	std::string formula;
	std::string state;
public:
	// =================    VARIABLE   ================= //
	std::vector<std::pair<int, int>> object_info;
	std::string input;
	
	// =================    FUNCTION   ================= //
	Polynomial();

	std::string print_Formula() const;
	std::string print_state() const;
	void Error_Define_Input();
	void get_Formula();
	void reset();

	int result(const int x) const;

	friend Polynomial operator+(const Polynomial& polynomial_1, const Polynomial& polynomial_2);
	friend Polynomial operator*(const Polynomial& polynomial_1, const Polynomial& polynomial_2);
	friend std::istream & operator>>(std::istream& is, const Polynomial & polynomial);
	friend std::ostream & operator<<(std::ostream & os, const Polynomial& polynomial);

};

Polynomial::Polynomial() {
	this->input = "NULL";
	this->formula = "";
	this->state = "NOTHING";
}

std::string Polynomial::print_Formula() const {
	return this->formula;
}

std::string Polynomial::print_state() const {
	return this->state.c_str();
}

// 1��
void Polynomial::Error_Define_Input() {
	std::vector<std::string> temp_;

	try {
		if (this->input == ".") {
			std::cout << "'.'�Է� ->";
			throw EXCEPTION_EXIT;
		}
		else if (this->input == ",") {
			std::cout << "','�Է� ->";
			throw EXCEPTION_AGAIN;
		}
		else if (this->input == "NULL") {
			std::cout << "�Է¾ȵ� ->";
			throw EXCEPTION_AGAIN;
		}
		temp_ = split(this->input, ")");

		for (int i = 0; i < temp_.size(); i++) {
			this->object_info.push_back(std::make_pair(atoi(&temp_[i][1]), atoi(&temp_[i][3])));
		}

		for (int i = 0; i < object_info.size(); i++) {
			if (object_info[i].first < 0 || object_info[i].first >= 10 || object_info[i].second < 0 || object_info[i].second >= 10) {
				std::cout << "���� �� ����� 0 ~ 9 ->";
				throw EXCEPTION_AGAIN;
			}
		}
		this->get_Formula();
	}
	catch (std::string err) {
		if (err == EXCEPTION_EXIT) {
			this->state = EXCEPTION_EXIT;
		}
		else {
			this->state = EXCEPTION_AGAIN;
		}
	}
}

void Polynomial::get_Formula() {
	std::vector<std::string> temp_;

	make_sorted_pair_list(&this->object_info);
	this->object_info = combine(this->object_info);

	for (int i = 0; i < this->object_info.size(); i++) {
		if (this->object_info[i].first == 0) {
			continue;
		}
		else if (this->object_info[i].first == 1) {
			if (this->object_info[i].second == 0) {
				temp_.push_back("1");
			}
			else if (this->object_info[i].second == 1) {
				temp_.push_back("x");
			}
			else {
				temp_.push_back("x^" + std::to_string(this->object_info[i].second));
			}
		}
		else {
			if (this->object_info[i].second == 0) {
				temp_.push_back(std::to_string(this->object_info[i].first));
			}
			else if (this->object_info[i].second == 1) {
				temp_.push_back(std::to_string(this->object_info[i].first) + "x");
			}
			else {
				temp_.push_back(std::to_string(this->object_info[i].first) + "x^" + std::to_string(this->object_info[i].second));
			}
		}
	}

	if (temp_.size() == 0) {
		this->formula = "0";
	}
	else {
		for (int i = 0; i < temp_.size(); i++) {
			if (i == temp_.size() - 1) {
				this->formula += temp_[i];
			}
			else {
				this->formula += temp_[i] + " + ";
			}
		}
	}
}

void Polynomial::reset() {
	this->input = "NULL";
	this->formula = "";
	this->state = "NOTHING";
	this->object_info.clear();
}

// 3��
int Polynomial::result(const int x) const{
	int result = 0;
	int temp_result = 1;

	for (int i = 0; i < object_info.size(); i++) {
		for (int j = 0; j < object_info[i].second; j++) {
			temp_result *= x;
		}
		result += (object_info[i].first)*temp_result;
		temp_result = 1;
	}

	return result;
}

// 5��
Polynomial operator+(const Polynomial& poly_A, const Polynomial& poly_B) {
	Polynomial temp;

	std::vector<int> target_list;
	std::vector<std::pair<int, int>> temp_pair_list;

	move_pair_list(&temp_pair_list, poly_A.object_info);
	move_pair_list(&temp_pair_list, poly_B.object_info);
	make_sorted_pair_list(&temp_pair_list);
	move_pair_list(&temp.object_info, combine(temp_pair_list));
	temp.get_Formula();

	return temp;
}

// 2��, 4�� // 2���� ��� *�� ���� ó�� ������ -> �Լ� ������ �ʿ伺 ������ ����
Polynomial operator*(const Polynomial& poly_A, const Polynomial& poly_B) {
	Polynomial temp;
	std::vector<std::pair<int, int>> temp_pair_list;

	for (int i = 0; i < poly_A.object_info.size(); i++) {
		for (int j = 0; j < poly_B.object_info.size(); j++) {
			temp_pair_list.push_back(std::make_pair(poly_A.object_info[i].first * poly_B.object_info[j].first, poly_A.object_info[i].second + poly_B.object_info[j].second));
		}
	}

	make_sorted_pair_list(&temp_pair_list);
	move_pair_list(&temp.object_info, combine(temp_pair_list));
	temp.get_Formula();

	return temp;
}

// 6��
std::istream& operator>>(std::istream& is, Polynomial & polynomial) {
	std::string input;

	std::cin >> input;
	polynomial.input = input;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Polynomial & polynomial){
	std::cout << polynomial.print_Formula().c_str();
	return os;
}

// ==================================         CUSTOM FUNCTIONS         ================================== //

std::vector<std::string> split(std::string target, const char* keyword) {

	std::vector<std::string> splited_list;
	char * c_target = &target[0];
	char * tok = strtok(c_target, keyword);

	while (tok != NULL) {
		splited_list.push_back(tok);
		tok = strtok(NULL, keyword);
	}
	return splited_list;
}

std::vector<std::pair<int, int>> combine(const std::vector<std::pair<int, int>>& target) {

	std::vector<std::pair<int, int>> result;
	int sum = 0;
	int next = 0;

	for (int i = 0; i < target.size();) {
		sum = target[i].first;
		if (i == target.size() - 1) {
			result.push_back(std::make_pair(sum, target[i].second));
			break;
		}
		for (int j = i + 1; j < target.size(); j++) {
			if (target[i].second == target[j].second) {
				sum += target[j].first;
				next = j + 1;
			}
			else {
				next = j;
				break;
			}
		}
		result.push_back(std::make_pair(sum, target[i].second));
		i = next;
	}
	return result;
}

void input_function(Polynomial& Ax, Polynomial& Bx, Polynomial& Cx, int& x) {
	std::cout << "�Է� : ";
	std::cin >> Ax >> Bx >> Cx >> x;

	Ax.Error_Define_Input();
	Bx.Error_Define_Input();
	Cx.Error_Define_Input();

	do {
		if (Ax.print_state() == EXCEPTION_EXIT || Bx.print_state() == EXCEPTION_EXIT || Cx.print_state() == EXCEPTION_EXIT) {
			std::cout << "���α׷�����" << std::endl;
			exit(0);
		}
		if (Ax.print_state() == EXCEPTION_AGAIN || Bx.print_state() == EXCEPTION_AGAIN || Cx.print_state() == EXCEPTION_AGAIN) {
			std::cout << "���Է��ϼ���" << std::endl;
			std::cin.clear();
			while (std::cin.get() != '\n') {
				continue;
			}
			Ax.reset();
			Bx.reset();
			Cx.reset();
			input_function(Ax, Bx, Cx, x);
		}
	} while (Ax.print_state() == NO_PROBLEM && Bx.print_state() == NO_PROBLEM && Cx.print_state() == NO_PROBLEM);
}

void output_function(const Polynomial& Ax, const Polynomial& Bx, const Polynomial& Cx, const Polynomial& Tx, const Polynomial& Dx, const int x) {
	std::cout << "A(x) = " << Ax << std::endl;
	std::cout << "B(x) = " << Bx << std::endl;
	std::cout << "C(x) = " << Cx << std::endl;
	std::cout << "T(x) = " << Tx << std::endl;
	std::cout << "D(x) = " << Dx << std::endl;
	std::cout << "x = " << x << " --> " << Dx.result(x) << std::endl;
}

void make_sorted_pair_list(std::vector<std::pair<int, int>> * target) {
	int next;

	for (int i = 0; i < target[0].size() - 1; i++) {
		next = i + 1;
		for (next; next < target[0].size(); next++) {
			if (target[0][i].second < target[0][next].second) {
				swap(target[0][i], target[0][next]);
			}
		}
	}
}

template <typename T>
inline void swap(T * A, T * B) {

	T temp;
	temp = *A;
	*A = *B;
	*B = temp;
}

inline void move_pair_list(std::vector<std::pair<int, int>> * A, const std::vector<std::pair<int, int>> B) {
	for (int i = 0; i < B.size(); i++) {
		A[0].push_back(std::make_pair(B[i].first, B[i].second));
	}
}

// ==================================           MAIN FUNCTION           ================================== //

int main() {
	Polynomial Ax, Bx, Cx, Tx, Dx;
	int x;

	input_function(Ax, Bx, Cx, x);
	Tx = Ax * Bx;
	Dx = Tx + Cx;
	output_function(Ax, Bx, Cx, Tx, Dx, x);

	return 0;
}