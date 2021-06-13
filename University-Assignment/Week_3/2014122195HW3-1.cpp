#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <stdlib.h>
#include <stdio.h>
//                         ������ Ư������ �ƽ�Ű �ڵ����                              //
// 33(0x21) ~ 47(0x2f), 58(0x3a) ~ 64(0x40), 91(0x5b) ~ 96(0x60), 123(0x7b) ~ 126(0x7d) //
// �ȳ���Ʈ
const std::string input_message = "Please write an word you wanna find in this file >> ";
const std::string file_error_message = "File can not be open, try again\n";
const std::string file_path = "C:\\Users\\sangh\\Desktop\\2020-1\\Data_structure\\week3\\input.txt";
const char * exit_keyword = ".";

// �̿�Ž��
int binarySearch(const char * input, std::vector<std::string> sorted_list) {
	int start_ptr = 0;
	int end_ptr = sorted_list.size();
	int middle = (start_ptr + end_ptr) / 2;
	int target_ptr = -1;
	do{
		if (middle > (sorted_list.size() - 1) || middle < 0) { break; }
		if (strcmp(sorted_list[middle].c_str(), input) > 0) {
			end_ptr = middle - 1;
		}
		else if (strcmp(sorted_list[middle].c_str(), input) < 0) {
			start_ptr = middle + 1;
		}
		else {
			target_ptr = middle;
			break;
		}
		middle = (start_ptr + end_ptr) / 2;
		if (middle > end_ptr || middle < start_ptr) { break; }
	 }while (true);
	if (target_ptr == -1) { return target_ptr; }
	else { return target_ptr; }
}
// �������Ľ� swap���
void swap(std::vector<std::string> *target, int x, int y, int now) {
	std::string temp = target[0][x];
	target[0][x] = target[0][y];
	target[0][y] = temp;
}
// ��������
void selected_sort(std::vector<std::string> *_unsorted_list) {
	int start = 0;
	int end = _unsorted_list->size()-1;
	int min = 0;

	for (start; start < end; start++) {
		int next = start + 1;
		min = start;
		for (next; next < end; next++) {
			if (strcmp(_unsorted_list[0][next].c_str(), _unsorted_list[0][min].c_str()) < 0) {
				min = next;
			}
		}
		swap(_unsorted_list, start, min, start);
	}
}
// �ߺ�����
std::vector<std::string> delete_same_word(std::vector<std::string> *target) {
	std::vector < std::string> result;
	int start = 0;
	int end = target[0].size();
	int next = start + 1;

	for (start; start < end - 1; start++) {
		for (next; next < end - 1; next++) {
			if (strcmp(target[0][start].c_str(), target[0][next].c_str()) == 0) {
				continue;
			}
			else {
				result.push_back(target[0][start].c_str());
				start = next - 1;
				next = start + 2;
				break;
			}
		}
	}
	return result;
}
// Ư������ ����
void delete_special_word(std::vector<std::string> *pre_string_list, std::vector <std::string> *unsorted_word_list) {
	size_t size;
	std::string str;
	int list_num = 0;

	for (int i = 0; i < pre_string_list[0].size(); i++) {
		str = pre_string_list[0][i];

		for (int j = 0; j < str.size(); j++) {
			if (0x21 <= str[j] && str[j] <= 0x2f || 0x3a <= str[j] && str[j] <= 0x40 || 0x5b <= str[j] && str[j] <= 0x60 || 0x7b <= str[j] && str[j] <= 0x7d) {
				str[j] = 0x20;
			}
		}
		size = str.size();
		if (size != 0) {
			char * char_ptr = (char*)malloc(sizeof(char)*size);
			char_ptr = &str[0];
			const char *tok = strtok(char_ptr, " ");
			while (tok != NULL) {
				unsorted_word_list[0].push_back(tok);
				list_num++;
				tok = strtok(nullptr, " ");
			}
		}
	}
}
// �ߺ����� ���� ���� ���� ����Ʈ, �ߺ����� �� ���� ����Ʈ ����Ʈ
void print_list(std::vector<std::string> unsorted_list, std::vector<std::string> unique_sorted_list) {
	int start_unsorted_list = 0;
	int start_unique_list = 0;
	int end_unsorted_list = unsorted_list.size();
	int end_unique_list = unique_sorted_list.size();
	printf("\|=========================\|\|=========================\|\n");
	printf("\|=======SORTED LIST=======\|\|========UNIQUE LIST======\|\n");

	for (start_unsorted_list; start_unsorted_list < end_unsorted_list; start_unsorted_list ++) {
		if (start_unique_list < end_unique_list){
			printf("\|=========================\|\|=========================\|\n");
			printf("\|  Position  \|    Word    \|\|  Position  \|    Word    \|\n");
			printf("\|=========================\|\|=========================\|\n");
			printf("\|  %8d  \|  %8s  \|\|  %8d  \|  %8s  \|\n", start_unsorted_list + 1, unsorted_list[start_unsorted_list].c_str(), start_unique_list + 1, unique_sorted_list[start_unique_list].c_str());
			printf("\|=========================\|\|=========================\|\n");
			start_unique_list++;
		}
		else{
			printf("\|=========================\|\n");
			printf("\|  Position  \|    Word    \|\n");
			printf("\|=========================\|\n");
			printf("\|  %8d  \|  %8s  \|\n", start_unsorted_list + 1, unsorted_list[start_unsorted_list].c_str());
			printf("\|=========================\|\n");
		}
		
	}
}

int main() {
	std::ifstream readFile;

	std::vector<std::string> pre_string_list;
	std::vector<std::string> unsorted_word_list;
	std::vector<std::string> unique_sorted_list;
	
	std::string input;
	std::string str_;

	int search_list_num = NULL;
	// file open �� ���� ���� 
	do {
		try {
			readFile.open(file_path.c_str());
			if (readFile.is_open()) {
				while (!readFile.eof()) {
					std::getline(readFile, str_);
					pre_string_list.push_back(str_);
				}
			}
			else { throw false; }
		}
		catch (bool exp) {
			std::cout << file_error_message.c_str();
		}
	} while (readFile.is_open() != true);

	delete_special_word(&pre_string_list, &unsorted_word_list);
	selected_sort(&unsorted_word_list);
	unique_sorted_list = delete_same_word(&unsorted_word_list);
	print_list(unsorted_word_list, unique_sorted_list);

	do {
		std::cout << input_message.c_str();
		std::cin >> input;
		if (strcmp(input.c_str(), exit_keyword) == 0) { break; }
		search_list_num = binarySearch(input.c_str(), unique_sorted_list);
		if (search_list_num == -1) {
			std::cout << search_list_num << std::endl;
			while (std::cin.get() != '\n') {}
		}
		else {
			while (std::cin.get() != '\n') {}
			printf("\|=========================\|\n");
			printf("\|  Position  \|    Word    \|\n");
			printf("\|=========================\|\n");
			printf("\|  %8d  \|  %8s  \|\n", search_list_num + 1, unique_sorted_list[search_list_num].c_str());
			printf("\|=========================\|\n");
		}
	} while (strcmp(input.c_str(), exit_keyword) != 0);

	return 0;
}