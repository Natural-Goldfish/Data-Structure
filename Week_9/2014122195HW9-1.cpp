#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

/*

	Input format : Three Polynomials and one value for calculation 
				(Coeficient, Exponential)
	Example)
			INPUT : (1,0)(2,0)(3,1) (2,2) (3,1) 2



			
			A(x) : (1,0)(2,0)(3,1) -> 3x + 3
			B(x) : (2,2)           -> 2x^2
			C(x) : (3,1)           -> 3x
			T(x) = A(x) * B(x)     == 6x^3 + 6x^2
			D(x) = T(x) + C(x)     == 6x^3 + 6x^2 + 3x
			D(2) : 78


*/

// ================================================================================    CLASS AND FUNCTION DESCRIPTION    ================================================================================ //

template <typename T1, typename T2> class Custom_pair;
class Node;
class Iterator;
class LinkedList;
class Polynomial;

std::vector<std::string> split(std::string target, const char* keyword);
void dynamic_memory_free(Polynomial& _object1, Polynomial& _object2, Polynomial& _object3, Polynomial& _object4, Polynomial& _object5);

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

// ================================================================================              CUSTOM_PAIR              ================================================================================ //

template <typename T1, typename T2> class Custom_pair {
private:
	T1 first_value;
	T2 second_value;

public:
	Custom_pair<T1, T2>() {
		this->first_value = NULL;
		this->second_value = NULL;
	};
	Custom_pair<T1, T2>(T1 _first_value, T2 _second_value) : first_value(_first_value), second_value(_second_value) {};

	T1 get_first() const;
	T2 get_second() const;
	void set_first(T1 _first_value);
	void set_second(T2 _second_value);

	friend Custom_pair<T1, T2> custom_make_pair(const T1 _first_value, const T2 _second_value);
};

template <typename T1, typename T2> T1 Custom_pair<T1, T2>::get_first() const {
	return this->first_value;
}

template <typename T1, typename T2> T2 Custom_pair<T1, T2>::get_second() const {
	return this->second_value;
}

template <typename T1, typename T2> void Custom_pair<T1, T2>::set_first(T1 _first_value) {
	this->first_value = _first_value;
}

template <typename T1, typename T2> void Custom_pair<T1, T2>::set_second(T2 _second_value) {
	this->second_value = _second_value;
}

template <typename T1, typename T2> Custom_pair<T1, T2> custom_make_pair(const T1 _first_value, const T2 _second_value) {
	return Custom_pair<T1, T2>(_first_value, _second_value);
}

// ================================================================================                  NODE                  ================================================================================ //

class Node {
public:
	Custom_pair<int, int> node_values;
	Node * next;

	Node() {
		this->node_values = custom_make_pair(NULL, NULL);
		this->next = nullptr;
	}
	Node(Custom_pair<int, int> _value) : node_values(_value) {};
};

// ================================================================================                ITERATOR                ================================================================================ //

class Iterator {
	friend class LinkedList;
private:
	Node * cur;

public:
	Iterator();
	Iterator(Node * _ptr);
	Node* get_current_node_pointer() const;
	Custom_pair<int, int>& operator*() const;
	Iterator& operator++();
	bool operator==(const Iterator& _compare) const;
	bool operator!=(const Iterator& _compare) const;
	
};

Iterator::Iterator() {
	this->cur = nullptr;
}

Iterator::Iterator(Node * _ptr) {
	this->cur = _ptr;
}

Node* Iterator::get_current_node_pointer() const {
	return this->cur;
}

Custom_pair<int, int>& Iterator::operator*() const {
	return this->cur->node_values;
}

Iterator& Iterator::operator++() {
	this->cur = this->cur->next;
	return *this;
}

bool Iterator::operator==(const Iterator& _compare) const {
	return this->cur == _compare.cur;
}

bool Iterator::operator!=(const Iterator& _compare) const {
	return this->cur != _compare.cur;
}

// ================================================================================                LINKEDLIST                ================================================================================ //
//
//                                                                                FIRST                                                             LAST                 
//                                                   ++++++++++++++           ++++++++++++++                          ++++++++++++++           ++++++++++++++          
//                                             +     +  V   +     +      +    +  V   +     +      +                   +  V   +     +      +    +  V   +     +      
//                                              +    +  A   +  N  +       +   +  A   +  N  +       +                  +  A   +  N  +       +   +  A   +  N  +       
//                                       +++++++++   +  L   +  E  ++++++++++  +  L   +  E  ++++++++++      * * *      +  L   +  E  ++++++++++  +  L   +  E  ++++++++++
//                                       +      +    +  U   +  X  +       +   +  U   +  X  +       +                  +  U   +  X  +       +   +  U   +  X  +        +
//                                       +     +     +  E   +  T  +      +    +  E   +  T  +      +                   +  E   +  T  +      +    +  E   +  T  +        +
//                                       +           +  S   +     +           +  S   +     +                          +  S   +     +           +  S   +     +        +
//                                       +           ++++++++++++++           ++++++++++++++                          ++++++++++++++           ++++++++++++++        +
//                                       +              HEAD NODE                                                                                                    +
//                                       +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
// This LinkedList is a circular linkedlist.
// This LinkedLIst has a head node. 
// 
// =========================================================================================================================================================================================================== //
class LinkedList {
	friend class Polynomial;

private:
	Node head_node;
	Node * last;
	void combine_same_values();

public:
	LinkedList();

	void sort(bool _activate);
	const int size() const;
	void push_back(Custom_pair<int, int> _value);
	void push_front(Custom_pair<int, int> _value);

	Custom_pair<int, int> pop_front();
	Custom_pair<int, int> pop(int _index);

	Iterator begin() const;
	Iterator end() const;

	friend LinkedList operator+(LinkedList& _object1, LinkedList& _object2);
};

LinkedList::LinkedList() {
	this->head_node.next = nullptr;
	this->last = &this->head_node;
	this->last->next = &this->head_node;
}

void LinkedList::sort(bool _activate) {
	//Selection sorting method is used and this is descending sort
	if (this->last != &this->head_node && this->size() > 1) {
		
		int max = NULL;
		Node * cur_ptr = nullptr;
		Node * max_cur_ptr = nullptr;
		Node * inner_cur_ptr = nullptr;
		Iterator iter = this->begin();
		
		do {
			Iterator inner_iter = iter;
			if (iter == this->head_node.next) {
				cur_ptr = this->head_node.next;
			}

			max_cur_ptr = cur_ptr;

			do {
				if (inner_iter == iter) {
					inner_cur_ptr = cur_ptr;
					max = inner_cur_ptr->node_values.get_second();
				}
				else {
					if (inner_iter.get_current_node_pointer()->node_values.get_second() > max) {
						max_cur_ptr = inner_iter.get_current_node_pointer();
						max = inner_iter.get_current_node_pointer()->node_values.get_second();
					}
				}
				
				++inner_iter;
				inner_cur_ptr = inner_iter.get_current_node_pointer();

			} while (inner_iter != this->end());

			Custom_pair<int, int> temp_ = max_cur_ptr->node_values;
			max_cur_ptr->node_values = cur_ptr->node_values;
			cur_ptr->node_values = temp_;
		
			++iter;
			cur_ptr = iter.get_current_node_pointer();

		} while (iter != this->end());
	}
	if (_activate == true) { LinkedList::combine_same_values(); }
}

void LinkedList::combine_same_values() {
	if (this->last != &this->head_node && this->size() > 1) {
		int idx = 0;
		int inner_idx = 0;
		Iterator iter = this->begin();
		Node * cur = nullptr;
		Node * this_next = nullptr;
		do {
			Iterator inner_iter = iter;
			cur = iter.get_current_node_pointer();
			int sum = cur->node_values.get_first();
			int target = cur->node_values.get_second();
			inner_idx = idx;
			do {
				if (inner_iter == iter) {
					++inner_iter;
					inner_idx++;
				}
				else {
					this_next = inner_iter.get_current_node_pointer();
					
					if (target == this_next->node_values.get_second()) {
						sum += this_next->node_values.get_first();
						++inner_iter;
						LinkedList::pop(inner_idx);
					}
					else { 
						++inner_iter; 
						inner_idx++;
					}
				}
			} while (inner_iter != this->end());
			cur->node_values.set_first(sum);
			idx++;
			++iter;
		} while (iter != this->end());
	}
}

const int LinkedList::size() const {
	if (this->head_node.next != nullptr) {

		Iterator iter = this->begin();
		int count = 0;

		do {
			count++;
			++iter;
		} while (iter != this->end());
		count;
		return count;
	}
	else { return NULL; }
}

void LinkedList::push_front(Custom_pair<int, int> _value) {

	if (this->last == &this->head_node) {
		this->head_node.next = new Node(_value);
		this->last = this->head_node.next;
		this->last->next = &this->head_node;
	}
	else {
		Node * temp = this->head_node.next;
		this->head_node.next = new Node(_value);
		this->head_node.next->next = temp;
	}
}

void LinkedList::push_back(Custom_pair<int, int> _value) {

	if (this->head_node.next == nullptr) {
		this->head_node.next = new Node(_value);
		this->last = this->head_node.next;
		this->last->next = &this->head_node;
	}
	else {
		Node * temp = this->last;
		this->last = new Node(_value);
		this->last->next = &this->head_node;
		temp->next = this->last;
	}
}

Custom_pair<int, int> LinkedList::pop_front() {

	if (this->last != &this->head_node) {
		Custom_pair<int, int> return_value = this->head_node.next->node_values;
		if (this->head_node.next == this->last) {
			delete this->head_node.next;
			this->head_node.next = nullptr;
			this->last = &this->head_node;
			this->last->next = &this->head_node;
			return return_value;
		}
		else {
			Node * temp = this->head_node.next->next;
			delete this->head_node.next;
			this->head_node.next = temp;
			return return_value;
		}
	}
}

Custom_pair<int, int> LinkedList::pop(int _index) {

	if (this->last != &this->head_node && (_index < this->size() && _index >= 0)) {
		
		int this_index = 0;
		Node * temp = nullptr;
		Node * before_ptr = nullptr;
		Node * cur_ptr = nullptr;
		Iterator iter = this->begin();
		Custom_pair<int, int> return_value;

		do {
			if (this_index == _index) {
				cur_ptr = iter.get_current_node_pointer();
				break;
			}
			if (cur_ptr == nullptr && this_index == 0) { 
				before_ptr = this->head_node.next;
			}
			else if(cur_ptr == nullptr && this_index != 0){
				before_ptr = before_ptr->next;
			}
			this_index++;
			++iter;
		} while (iter != this->end());

		//When the node you want to pop is the frist node
		if (this_index == 0) {
			// There is only one node in this LinkedList
			if (this->head_node.next == this->last) {
				return_value = this->head_node.next->node_values;

				delete this->head_node.next;

				this->head_node.next = nullptr;
				this->last = &this->head_node;
				this->last->next = &this->head_node;

				return return_value;
			}
			// There are more than one node in this LinkedList
			else {
				return_value = cur_ptr->node_values;
				Node * temp = cur_ptr->next;
				delete this->head_node.next;
				this->head_node.next = temp;

				return return_value;
			}
		}
		else {
			// When the node you want to pop is the last node	
			if (cur_ptr == this->last) {
				return_value = cur_ptr->node_values;
				before_ptr->next = &this->head_node;
				this->last = before_ptr;
				delete cur_ptr;

				return return_value;
			}
			//when the node you wnat to pop is in the middle
			else {
				return_value = cur_ptr->node_values;
				before_ptr->next = cur_ptr->next;
				delete cur_ptr;

				return return_value;
			}
		}
	}
	else {
		while (true) { std::cout << "THERE IS SOME PROBLEMS IN POP FUNCTION" << std::endl; }
	}
}

Iterator LinkedList::begin() const {
	return Iterator(this->head_node.next);
}

Iterator LinkedList::end() const {
	return Iterator(this->last->next);
}

LinkedList operator+(LinkedList& _object1, LinkedList& _object2) {
	const int iter_num = _object2.size();

	for (int i = 0; i < iter_num; i++) {
		_object1.push_back(_object2.pop(0));
	}

	return _object1;
}

// ============================================================================================    POLYNOMIAL    ============================================================================================ //


class Polynomial{
	friend void dynamic_memory_free(Polynomial& _object1, Polynomial& _object2, Polynomial& _object3, Polynomial& _object4, Polynomial& _object5);

private:
	LinkedList linked_list;
	std::string formula;

	void initialize_formula();
	void memory_free();
public:
	Polynomial();
	Polynomial(LinkedList _linked_list);

	void make_formula();
	int evaluation(const int _x) const;

	friend Polynomial operator+( Polynomial& _object1, Polynomial& _object2);
	friend Polynomial operator*(Polynomial& _object1,Polynomial& _object2);
	friend std::ostream& operator<<(std::ostream& , Polynomial& _object);
	friend std::istream& operator>>(std::istream&, Polynomial& _object);
};

Polynomial::Polynomial() {
	this->formula = "";
}

Polynomial::Polynomial(LinkedList _linked_list) {
	this->linked_list.head_node.next = _linked_list.head_node.next;
	this->linked_list.last = _linked_list.last;
	this->linked_list.last->next = &this->linked_list.head_node;
}

void Polynomial::memory_free() {
	const Node * end_ptr = this->linked_list.last->next;
	Node * iter_ = this->linked_list.head_node.next;
	for (; iter_ != end_ptr;) {
		Node * temp = this->linked_list.head_node.next->next;
		delete this->linked_list.head_node.next;
		this->linked_list.head_node.next = temp;
		iter_ = temp;
	}
	this->initialize_formula();
	this->linked_list.last = &this->linked_list.head_node;
	this->linked_list.last->next = &this->linked_list.head_node;
}

void Polynomial::initialize_formula() {
	this->formula = "";
}

void Polynomial::make_formula() {
	Iterator iter = this->linked_list.begin();
	for (; iter != this->linked_list.end(); ) {
		int coef = iter.get_current_node_pointer()->node_values.get_first();
		int expo = iter.get_current_node_pointer()->node_values.get_second();

		if (coef != 0) {
			if (expo == 0) {
				if (this->formula != "") {
					this->formula += " + " + std::to_string(coef);
				}
				else { this->formula += std::to_string(coef); }
			}
			else if (expo == 1) {
				if (this->formula != "") {
					if (coef == 1) { this->formula += " + x"; }
					else { this->formula += " + " + std::to_string(coef) + "x"; }
				}
				else {
					if (coef == 1) { this->formula += "x"; }
					else { this->formula += std::to_string(coef) + "x"; }
				}
			}
			else {
				if (this->formula != "") {
					if (coef == 1) { this->formula += " + x^" + std::to_string(expo); }
					else { this->formula += " + " + std::to_string(coef) + "x^" + std::to_string(expo); }
				}
				else {
					if (coef == 1) { this->formula += "x^" + std::to_string(expo); }
					else { this->formula += std::to_string(coef) + "x^" + std::to_string(expo); }
				}
			}
		}
		++iter;
	}
}

int Polynomial::evaluation(const int _x) const {
	Iterator iter = this->linked_list.begin();
	if(this->linked_list.last != &this->linked_list.head_node){
	//if (this->linked_list.head_node.next != nullptr) {
		int result = 0;
		do {
			int inner_result = NULL;
			int coef = iter.get_current_node_pointer()->node_values.get_first();
			int expo = iter.get_current_node_pointer()->node_values.get_second();
			for (int i = 0; i < expo; i++) {
				if (i == 0) { inner_result = _x; }
				else { inner_result *= _x; }
			}
			if (expo == 0) { result += coef; }
			else { result += coef * inner_result; }
			++iter;
		} while (iter != this->linked_list.end());
		return result;
	}
	else { 
		std::cout << "THERE ARE SOME PROBLEMS IN EVALUATION FUNCTION";
		return NULL; 
	}
}

Polynomial operator+(Polynomial& _object1, Polynomial& _object2) {
	LinkedList _linked_list;
	Iterator iter_object1 = _object1.linked_list.begin();
	Iterator iter_object2 = _object2.linked_list.begin();
	do {
		_linked_list.push_back(custom_make_pair(iter_object1.get_current_node_pointer()->node_values.get_first(), iter_object1.get_current_node_pointer()->node_values.get_second()));
		//_linked_list.push_front(custom_make_pair(iter_object1.get_current_node_pointer()->node_values.get_first(), iter_object1.get_current_node_pointer()->node_values.get_second())); //push_front() is also available to use
		++iter_object1;
	} while (iter_object1 != _object1.linked_list.end());

	do {
		_linked_list.push_back(custom_make_pair(iter_object2.get_current_node_pointer()->node_values.get_first(), iter_object2.get_current_node_pointer()->node_values.get_second()));
		//_linked_list.push_front(custom_make_pair(iter_object2.get_current_node_pointer()->node_values.get_first(), iter_object2.get_current_node_pointer()->node_values.get_second())); //push_front() is also available to use
		++iter_object2;
	} while (iter_object2 != _object2.linked_list.end());

	_linked_list.sort(true);
	return Polynomial(_linked_list);
}

Polynomial operator*(Polynomial& _object1, Polynomial& _object2) {
	LinkedList _linked_list;
	Iterator iter_object1 = _object1.linked_list.begin();
	do {
		Iterator iter_object2 = _object2.linked_list.begin();
		int coef_object1 = iter_object1.get_current_node_pointer()->node_values.get_first();
		int expo_object1 = iter_object1.get_current_node_pointer()->node_values.get_second();

		do {
			int coef_object2 = iter_object2.get_current_node_pointer()->node_values.get_first();
			int expo_object2 = iter_object2.get_current_node_pointer()->node_values.get_second();
			_linked_list.push_back(custom_make_pair((coef_object1 * coef_object2), (expo_object1 + expo_object2)));
			//_linked_list.push_back(custom_make_pair((coef_object1 * coef_object2), (expo_object1 + expo_object2))); //push_front() is also available to use
			++iter_object2;
		} while (iter_object2 != _object2.linked_list.end());

		++iter_object1;
	} while (iter_object1 != _object1.linked_list.end());

	_linked_list.sort(true);
	return Polynomial(_linked_list);
}

std::ostream& operator<<(std::ostream& cout, Polynomial& _object) {
	std::cout << _object.formula;
	return cout;
}

std::istream& operator>>(std::istream& cin, Polynomial& _object) {
	std::string temp;	
	cin >> temp;

	if (temp == ".") { exit(1); }

	std::vector<std::string> temp_list = split(temp, ")");

	for (int i = 0; i < temp_list.size(); i++) {
		_object.linked_list.push_back(custom_make_pair<int, int>(atoi(&temp_list[i][1]), atoi(&temp_list[i][3])));
		//_object.linked_list.push_back(custom_make_pair<int, int>(atoi(&temp_list[i][1]), atoi(&temp_list[i][3]))); //push_front() is also available to use
	}

	_object.linked_list.sort(true);
	return cin;
}

void dynamic_memory_free(Polynomial& _A, Polynomial& _B, Polynomial& _C, Polynomial& _T, Polynomial& _D) {
	_A.memory_free();
	_B.memory_free();
	_C.memory_free();
	_T.memory_free();
	_D.memory_free();
}

// ============================================================================================    MAIN FUNCTION    ============================================================================================ //

int main() {
	int x;
	Polynomial A, B, C, T, D;
	while (true) {
		std::cin >> A >> B >> C >> x;
		T = A * B;
		D = T + C;
		A.make_formula(), B.make_formula(), C.make_formula(), T.make_formula(), D.make_formula();
		std::cout << "A(x) : " << A << std::endl << "B(x) : " << B << std::endl << "C(x) : " << C << std::endl;
		std::cout << "T(x) : " << T << std::endl << "D(x) : " << D << std::endl;
		std::cout << "D(" << std::to_string(x) << ") : " << D.evaluation(x) << std::endl;

		dynamic_memory_free(A, B, C, T, D);
	}
	return 0;
}