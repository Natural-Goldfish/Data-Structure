#include <iostream>
#include <string>
#include <vector>

////////////////////////////////////////////     TEMPLATE STACK CLASS     //////////////////////////////////////////// 

template <typename T>
class Stack{
	private : 
		std::vector<T> list;

	public:
		void push_back(T value);
		void delete_contents();
		T pop_back();
		int size() const;
};

template <typename T> void Stack<T>::push_back(T value) {
	this->list.push_back(value);
}

template<typename T> T Stack<T>::pop_back() {
	return this->list[this->list.size()-1];
}

template<typename T> void Stack<T>::delete_contents() {
	this->list.pop_back();
}
 
template<typename T> int Stack<T>::size() const {
	return this->list.size();
}

////////////////////////////////////////////     FUNCTION DEFINITIONS     //////////////////////////////////////////// 

void Input_Function(std::string &input);
void Make_Postfix_Formula(std::string  input, std::string &postfix_formula);
void Insert_Space(std::string & postfix_formula);
inline void Print_Postfix_Formula(const std::string & postfix_formula);
void Calculation(std::string postfix_formula, double & result);
inline double Sub_Cal(Stack<double> & temp, const char keyword);
void Initialize(std::string & input, std::string & postfix_formula, double & result);
inline int ctoi(const char c);

void Input_Function(std::string &input) {
	std::cout << "  INFIX FORMULA : ";
	getline(std::cin, input);
		if (input == ".") {
			std::cout << "Program exit";
			exit(-1);
		}
}

void Make_Postfix_Formula(std::string input, std::string & postfix_formula) {

	const int size_of_input = input.size();
	Stack<char> intermidate = Stack<char>();

	for (int i = 0; i < size_of_input; i++) {
		int temp_int = ctoi(input[i]);
		if (0 <= temp_int && temp_int <= 9) postfix_formula.push_back(input[i]);
		else {
			char keyword = input[i];
			switch (keyword) {
				case '(': intermidate.push_back('('); break;
					
				case ')':
					while (intermidate.pop_back() != '(') {
						postfix_formula.push_back(intermidate.pop_back());
						intermidate.delete_contents();
					}
					if (intermidate.size() != 0 && intermidate.pop_back() == '(') {
						intermidate.delete_contents();
					}
					break;

				case '+':
					while((intermidate.size() != 0 && intermidate.pop_back() != ')' && intermidate.pop_back() != '('))
					{
						postfix_formula.push_back(intermidate.pop_back());
						intermidate.delete_contents();
					}
					intermidate.push_back('+');

					break;

				case '-':
					while ((intermidate.size() != 0 && intermidate.pop_back() != ')' && intermidate.pop_back() != '('))
					{
						postfix_formula.push_back(intermidate.pop_back());
						intermidate.delete_contents();
					}
					intermidate.push_back('-');
					break;

				case '*': intermidate.push_back('*'); break;

				case '/': intermidate.push_back('/'); break;
			}
		}
	}
	if (intermidate.size() != 0) {
		const int loop = intermidate.size();
		for (int i = 0; i < loop; i++) {
			postfix_formula.push_back(intermidate.pop_back());
			intermidate.delete_contents();
		}
	}
}

void Insert_Space(std::string & postfix_formula) {
	const int size = postfix_formula.size();
	bool check = false;
	std::string temp = "";
	for (int i = 0; i < size; i++) {
		if (check == true) temp += " "; check = false;
		temp += postfix_formula[i];
		check = true;
	}
	postfix_formula = temp;
}

inline void Print_Postfix_Formula(const std::string & postfix_formula) {
	std::cout << "POSTFIX FORMULA : " << postfix_formula.c_str() << std::endl;
}

void Calculation(std::string postfix_formula, double & result) {
	Stack<double> temp_ = Stack<double>();
	const int formula_size = postfix_formula.size(); 
	int target;
	
	for (int i = 0; i < formula_size; i++) {
		target = ctoi(postfix_formula[i]);
;		if (0 <= target && target <= 9) {
			temp_.push_back((double)target);
		}
		else {
			if (postfix_formula[i] == '+') {
				temp_.push_back(Sub_Cal(temp_, '+'));
			}
			if (postfix_formula[i] == '-') {
				temp_.push_back(Sub_Cal(temp_, '-'));
			}
			if (postfix_formula[i] == '*') {
				temp_.push_back(Sub_Cal(temp_, '*'));
			}
			if (postfix_formula[i] == '/') {
				temp_.push_back(Sub_Cal(temp_, '/'));
			}
		}
	}
	result = temp_.pop_back();
}

inline double Sub_Cal(Stack<double> & temp, const char keyword) {
	double result_ = 0.0;
	double a = temp.pop_back();
	temp.delete_contents();
	double b = temp.pop_back();
	temp.delete_contents();

	switch (keyword) {
		case '+':
			result_ = a + b; break;
		case '-':
			result_ = b - a; break;
		case '*':
			result_ = a * b; break;
		case '/':
			result_ = b / a; break;
	}
	return result_;
}

void Initialize(std::string & input, std::string & postfix_formula, double & result) {
	input = "";
	postfix_formula = "";
	result = 0.0;
}

inline int ctoi(const char c) {
	int return_value = (int)c - 48;
	return return_value;
}

////////////////////////////////////////////          MAIN FUNCTION          //////////////////////////////////////////// 

int main() {
	std::string input;
	std::string postfix_formula;
	double result;

	while (true) {
		Input_Function(input);
		Make_Postfix_Formula(input, postfix_formula);
		Insert_Space(postfix_formula);
		Print_Postfix_Formula(postfix_formula);
		Calculation(postfix_formula, result);
		std::cout << "=====RESULT=====: " << result << std::endl << std::endl;
		Initialize(input, postfix_formula, result);
	}

	return 0;
}