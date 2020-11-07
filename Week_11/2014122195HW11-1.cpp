#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <string.h>
#include <vector>

#define LEFT 0
#define RIGHT 1


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


template <typename T1> class Node {
private:
	Node<T1> * Left;
	Node<T1> * Right;
	T1 value;

public:
	Node<T1>() {
		this->Left = nullptr;
		this->Right = nullptr;
		this->value = NULL; 
	}

	Node<T1>(T1 _value) {
		this->Left = nullptr;
		this->Right = nullptr;
		this->value = _value;
	}

	void set_left(Node<T1>* _left_ptr);
	void set_right(Node<T1>* _right_ptr);
	void set_value(T1 _value);

	Node<T1>* get_left() const;
	Node<T1>* get_right() const;
	T1 get_value() const;
};

template<typename T1> Node<T1>* Node<T1>::get_left() const {
	return this->Left;
}
template<typename T1> Node<T1>* Node<T1>::get_right() const {
	return this->Right;
}
template<typename T1> T1 Node<T1>::get_value() const {
	return this->value;
}
template<typename T1> void Node<T1>::set_left(Node<T1>* _left_ptr){
	this->Left = _left_ptr;
}
template<typename T1> void Node<T1>::set_right(Node<T1>* _right_ptr) {
	this->Right = _right_ptr;
}
template<typename T1> void Node<T1>::set_value(T1 _value) {
	this->value = _value;
}
template <typename T1> class Iterator {
private:
	Node<T1>* ptr;

public:
	Iterator<T1>() {
		this->ptr = nullptr;
	};
	Iterator<T1>(Node<T1>* _ptr) {
		this->ptr = _ptr;
	};

	void set_ptr(Node<T1>* _ptr);
	Node<T1>* root_ptr() const;
	Node<T1>* next_ptr(int _direction) const;
	bool operator==(const Iterator<T1>& _ptr) const;
	bool operator!=(const Iterator<T1>& _ptr) const;
};

template <typename T1> void Iterator<T1>::set_ptr(Node<T1>* _ptr) {
	this->ptr = _ptr;
}

template <typename T1> Node<T1>* Iterator<T1>::root_ptr() const {
	return this->ptr;
}

template <typename T1> Node<T1>* Iterator<T1>::next_ptr(int _direction) const {
	if (_direction == LEFT) {
		return this->root_ptr()->get_left();
	}
	else {
		return this->root_ptr()->get_right();
	}
}

template <typename T1> bool Iterator<T1>::operator==(const Iterator<T1>& _ptr) const{
	if (this->ptr == _ptr.root_ptr()) {
		return true;
	}
	else {
		return false;
	}
}

template <typename T1> bool Iterator<T1>::operator!=(const Iterator<T1>& _ptr) const{
	if (this->ptr != _ptr.root_ptr()) {
		return true;
	}
	else {
		return false;
	}
}

template <typename T1> class Linked_List {
	template <typename T2> friend class Binary_Search_Tree; // 수정
private:
	Node<T1> Root_Node;
	Node<T1>* Root_Node_ptr;

	Node<T1>* get_root_ptr() const;
	bool exist(const Node<T1>* _ptr, int _direction) const;
	void search_for_insert(Node<T1>* _next_node_ptr, T1 _value);
	void search_for_show(Node<T1>* _next_node_ptr) const;

public:
	Linked_List() {
		this->Root_Node_ptr = &this->Root_Node;
	};
	void insert(T1 _value);
	void show() const;
	void memory_free(Node<T1>* _next_ptr);
};

template <typename T1> Node<T1>* Linked_List<T1>::get_root_ptr() const{
	return this->Root_Node_ptr;
}

template <typename T1> bool Linked_List<T1>::exist(const Node<T1>* _cur_node_ptr, int _direction) const {
	if (_direction == LEFT) {
		if (_cur_node_ptr->get_left() != nullptr) { return true; }
		else { return false; }
	}
	else if (_direction == RIGHT) {
		if (_cur_node_ptr->get_right() != nullptr) { return true; }
		else { return false; }
	}
}

template <typename T1> void Linked_List<T1>::search_for_insert(Node<T1>* _next_node_ptr, T1 _value) {
	Node<T1>* _cur_node_ptr = _next_node_ptr;

	if (_cur_node_ptr->get_value() > _value) {
		if (this->exist(_cur_node_ptr, LEFT) == true) {
			this->search_for_insert(_cur_node_ptr->get_left(), _value);
			return;
		}
		else {
			Node<T1>* temp = new Node<T1>(_value);
			_cur_node_ptr->set_left(temp);
			return;
		}
	}
	else {
		if (this->exist(_cur_node_ptr, RIGHT) == true) {
			this->search_for_insert(_cur_node_ptr->get_right(), _value);
			return;
		}
		else {
			Node<T1>* temp = new Node<T1>(_value);
			_cur_node_ptr->set_right(temp);
			return;
		}
	}
}

template <typename T1> void Linked_List<T1>::search_for_show(Node<T1>* _next_node_ptr) const {
	Node<T1>* _cur_node_ptr = _next_node_ptr;

	if (this->exist(_cur_node_ptr, LEFT) == true) {
		search_for_show(_cur_node_ptr->get_left());
	}
	std::cout << _cur_node_ptr->get_value() << " ";

	if (this->exist(_cur_node_ptr, RIGHT) == true) {
		search_for_show(_cur_node_ptr->get_right());
	}
}

template <typename T1> void Linked_List<T1>::insert(T1 _value) {
	Iterator<T1> iter(this->get_root_ptr());

	if (iter.root_ptr()->get_value() == NULL && iter.next_ptr(LEFT) == nullptr && iter.next_ptr(RIGHT) == nullptr) {
		iter.root_ptr()->set_value(_value);
		return;
	}
	this->search_for_insert(iter.root_ptr(), _value);
}

template <typename T1> void Linked_List<T1>::show() const {
	Iterator<T1> iter(this->get_root_ptr());
	if (iter.root_ptr()->get_value() == NULL) {
		std::cout << "THIS TREE IS EMPTY" << std::endl;
		return;
	}
	else {
		this->search_for_show(iter.root_ptr());
	}
}

template <typename T1> void Linked_List<T1>::memory_free(Node<T1>* _next_ptr) {
	Node<T1>* cur_ptr = _next_ptr;
	Iterator<T1> iter(cur_ptr);
	if (this->exist(iter.root_ptr(), LEFT)) {
		this->memory_free(iter.next_ptr(LEFT));
	}
	if (this->exist(iter.root_ptr(), RIGHT)) {
		this->memory_free(iter.next_ptr(RIGHT));
	}

	cur_ptr->set_left(nullptr);
	cur_ptr->set_right(nullptr);
	cur_ptr->set_value(NULL);
	if (cur_ptr != this->get_root_ptr()) {
		delete cur_ptr;
	}	
	return;
}

template <typename T1> class Binary_Search_Tree {
/*
private:
	Linked_List<T1> Linkedlist;
*/
public:
	Linked_List<T1> Linkedlist;
	void memory_free();
	void insert(T1 _value);
	void show();
	template <typename T2> friend std::istream& operator>>(std::istream& cin, Binary_Search_Tree<T1>& _object); // 수정
};

template <typename T1> void Binary_Search_Tree<T1>::insert(T1 _value) {
	this->Linkedlist.insert(_value);
}

template <typename T1> void Binary_Search_Tree<T1>::show() {
	std::cout << "OUTPUT : ";
	this->Linkedlist.show();
	std::cout << std::endl;
}

template <typename T1> std::istream& operator>>(std::istream& cin, Binary_Search_Tree<T1>& _object) {
	std::string temp;
	std::cout << "INPUT  : ";
	std::getline(std::cin, temp);

	if (temp == ".") { exit(1); }

	std::vector<std::string> temp_list = split(temp, " ");

	for (int i = 0; i < temp_list.size(); i++) {
		_object.Linkedlist.insert(atoi(&temp_list[i][0]));
	}

	return cin;
}

template <typename T1> void Binary_Search_Tree<T1>::memory_free() {
	this->Linkedlist.memory_free(this->Linkedlist.get_root_ptr());
}

int main() {
	Binary_Search_Tree<int> bst;

	while (true) {
		std::cin >> bst;
		bst.show();
		bst.memory_free();
	}
	return 0;
}	