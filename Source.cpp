#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <iomanip>
#include <ctime>
#include <fstream>

using namespace std;

struct User {
	char* first_name = new char[32];
	char* second_name = new char[32];
	int age;
	int* date = new int[3];
	int salary;
	int id;
	User* next;
};

void printList(User* first);
void printUser(User* first);
User* createUser(int* vacant_id);
User* createUserRand(int* vacant_id);
User* fillUser(int* vacant_id);
User* fillUserRand(int* vacant_id);
void addAtEnd(User** first, User* nUser);
void addAtBegin(User** root, User* nUser);
void add_set(User** head, int* global_id);
User* reverse(User* x);	
void deleteUser(User** head, User* someUser);
void insert(User** head, User* next_User, User* prev_User);
User* search_set(User* user);
User* search_id(User* user);
User* search_f_name(User* user);
User* search_s_name(User* user);
User* search_age(User* user);
User* search_brday(User* user);
void sort_set(User** head);
void action_set(User** head, int* global_id);
void setDownload(User** head, int* vacant_id);
void setUpload(User* head);
void fromFile(User** head, int* vacant_id, const char* type);
void fromBinFileAlt(User** head, int* vacant_id);
void inFile(User* head, const char* type);
void selection_sort_shit(User** head, bool(*cmp)(User* frst, User* scnd));
void changeSalary(User** head);
int fool(int beg, int end);
bool condit(const char* field, User* frst, User* scnd);
User* min_create();
void swap(User** head, User* tmp1_prev, User* tmp1_ptr, User* tmp2_prev, User* tmp2_ptr);
bool condit_f_n(User* frst, User* scnd);
bool condit_s_n(User* frst, User* scnd);
bool condit_id(User* frst, User* scnd);
bool condit_age(User* frst, User* scnd);
bool condit_date(User* frst, User* scnd);


int main() {

	srand(time(nullptr));

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	User* head = nullptr;
	int g_id = 1200;

	for (int i = 0; i < 6; i++) {
		addAtEnd(&head, createUserRand(&g_id));
	}
	printList(head);

	while (1) {
		action_set(&head, &g_id);
	}

	//_getch();
	//return 0;
}

void printList(User* first) {
	User* temp = first;
	
	cout << "ID" << setw(12) << "Имя" << setw(12) << "Фамилия" << setw(13) << "Полных лет" << setw(15) << "Дата рождения" << setw(10) << "Оклад" << endl;

	while (temp != nullptr) {
		std::cout << temp->id << setw(12) << temp->first_name << setw(12) << temp->second_name << setw(10) << temp->age << setw(9);
		std::cout << temp->date[0] << "." << temp->date[1] << "." << temp->date[2] << setw(10) << temp->salary << std::endl;

		temp = temp->next;
	}
	std::cout << std::endl;
}

void printUser(User* first){
	User* temp = first;
	if (temp != nullptr) {
		cout << "ID" << setw(11) << "Имя" << setw(9) << "Фамилия" << setw(13) << "Полных лет" << setw(15) << "Дата рождения" << setw(10) << "Оклад" << endl;

		std::cout << temp->id << setw(11) << temp->first_name << setw(9) << temp->second_name << setw(10) << temp->age << setw(9);
		std::cout << temp->date[0] << "." << temp->date[1] << "." << temp->date[2] << setw(10) << temp->salary << std::endl;

		std::cout << std::endl;
	}else {
		cout << endl << "ERROR: Не найдено данных!" << endl;
	}
}

User* fillUser(int* vacant_id) {
	User* tmpUser = new User;
	std::cout << "Имя: ";  std::cin.ignore(1); ::cin.getline(tmpUser->first_name, 32);
	std::cout << "Фамилия: "; std::cin.getline(tmpUser->second_name, 32);
	std::cout << "Возраст: "; std::cin >> tmpUser->age;
	std::cout << "День: ";    std::cin >> tmpUser->date[0];
	std::cout << "Месяц: "; std::cin >> tmpUser->date[1];
	std::cout << "Год: ";   std::cin >> tmpUser->date[2];
	std::cout << "Оклад: ";   std::cin >> tmpUser->salary;
	(*vacant_id)++;
	tmpUser->id = *vacant_id;	
	tmpUser->next = nullptr;

	return tmpUser;
}

User* fillUserRand(int* vacant_id) {
	const char* f_names[] = { "Иван", "Сергей", "Дмитрий", "Александр", "Арсений", "Данил", "Михаил", "Илья" };
	const char* s_names[] = { "Смирнов", "Иванов", "Кузнецов", "Соколов", "Попов", "Лебедев", "Алексеев", "Орлов" };

	User* tmpUser = new User;
	strcpy(tmpUser->first_name, f_names[rand() % 8]);	//tmpUser->first_name = f_names[rand() % 8];
	strcpy(tmpUser->second_name, s_names[rand() % 8]);	//tmpUser->second_name = s_names[rand() % 8];
	tmpUser->age = rand() % 40 + 22;
		tmpUser->date[0] = rand() % 30 + 1;
		tmpUser->date[1] = rand() % 12 + 1;
		tmpUser->date[2] = 2018 - tmpUser->age;
	tmpUser->salary = (rand() % 80 + 20)*1000;
	(*vacant_id)++;
	tmpUser->id = *vacant_id;
		tmpUser->next = nullptr;
	return tmpUser;
}

User* createUser(int* vacant_id) {
	User * nUser = new User;
	nUser = fillUser(vacant_id);
	return nUser;
}

User* createUserRand(int* vacant_id) {
	User * nUser = new User;
	nUser = fillUserRand(vacant_id);
	return nUser;
}

void add_set(User** head, int* global_id) {
	cout << endl << "1-Добавить имитированного пользователя / 2-Добавть нового пользователя " << endl;
	cout << "Введите вариант пользователя: ";
	int set1 = 0;
	cin >> set1;

	cout << endl << "1-Добавить в начало / 2-Добавить в конец / 3-Добавить перед ячейкой " << endl;
	cout << "Введите вариант добавления: ";
	int set2 = 0;
	cin >> set2;
	
	if (set1 == 1) {
		switch (set2) {
		case 1: addAtBegin(head, createUserRand(global_id));
			break;
		case 2: addAtEnd(head, createUserRand(global_id));
			break;
		case 3: insert(head, search_set(*head), createUserRand(global_id));
			break;
		}
	}else if (set1 == 2) {
		switch (set2) {
		case 1: addAtBegin(head, createUser(global_id));
			break;
		case 2: addAtEnd(head, createUser(global_id));
			break;
		case 3: insert(head, search_set(*head), createUser(global_id));
			break;
		}
	}
}
	
void addAtEnd(User** first, User* nUser) {
	User* temp = *first;
	if (temp == NULL) {
		*first = nUser;
	}else {
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = nUser;
	}
}

void addAtBegin(User** root, User* nUser) {
	nUser->next = *root;
	*root = nUser;
}

void insert(User** head, User* next_User, User* prev_User) { // insert new User before next_User
	if (next_User == *head) {
		prev_User->next = *head;
		*head = prev_User;
	}else {
		User* tmp = *head;
		while (tmp->next != next_User) {
			tmp = tmp->next;
		}
		prev_User->next = next_User;
		tmp->next = prev_User;
	}
}

void deleteUser(User** head, User* someUser) {
	if (someUser != nullptr) {
		if (someUser == *head) {
			*head = (*head)->next;
			delete someUser;
		}
		else {
			User* tmp = *head;
			while (tmp->next != someUser) {
				tmp = tmp->next;
			}
			tmp->next = someUser->next;
			delete someUser;
		}
	}
}

User* reverse(User* x) {
	User* tmp, *y = x, *r = nullptr;
	while (y != nullptr) {
		tmp = y->next;
		y->next = r;
		r = y;
		y = tmp;
	}
	return r;
}

User* search_set(User* user) {
	cout << " 1-id / 2-Имя / 3-Фамилия / 4-Возраст / 5-День Рождения " << endl;
	cout << "Введите параметр поиска: ";
	int set;
	cin >> set;

	switch (set) {
		case 1: return search_id(user);
			break;
		case 2: return search_f_name(user);
			break;
		case 3: return search_s_name(user);
			break;
		case 4: return search_age(user);
			break;
		case 5: return search_brday(user);
			break;
	}
}

User* search_id(User* user) {

	cout << "Введите id: ";
	int val;
	cin >> val;
	while (user != nullptr && user->id != val) {
		user = user->next;
	}
	return user; 
}

User* search_f_name(User* user) {

	cout << "Введите имя: ";
	char* val = new char[32];
	cin.getline(val, 32);
	cin >> val;
	while (user != nullptr && strcmp(user->first_name,val) != 0) {
		user = user->next;
	}
	return user;
}

User* search_s_name(User* user) {

	cout << "Введите фамилию: ";
	char* val = new char[32];
	cin.getline(val, 32);
	cin >> val;
	while (user != nullptr && strcmp(user->second_name,val) !=0) {
		user = user->next;
	}
	return user;
}

User* search_age(User* user) {

	cout << "Введите возраст: ";
	int val;
	cin >> val;
	while (user != nullptr && user->age != val) {
		user = user->next;
	}
	return user;
}

User* search_brday(User* user) {

	cout << "Введите число: ";
	int val;
	cin >> val;
	while (user != nullptr && user->date[0] != val) {
		user = user->next;
	}
	return user;
}

void action_set(User** head, int* global_id) {
	cout << endl << " 0-Показать список / 1-Добавить нового пользователя / 2-Удалить пользователя /" << endl
		 << " 3-Сортировать список / 4-Загрузить список / 5-Сохранить список в файл / 6-Изменить оклад / 7-Выход " << endl;
	cout << "Выберите действие: ";
	int set;
	set = fool(0, 7);

	switch(set){
	case 0: printList(*head);
		break;
	case 1: add_set(head, global_id);
		break;
	case 2: deleteUser(head, search_set(*head));
		break;
	case 3: sort_set(head);
		break;
	case 4: setDownload(head, global_id);
		break;
	case 5: setUpload(*head);
		break;
	case 6: changeSalary(head);
		break;
	case 7: TerminateProcess(GetCurrentProcess(), 0);
		break;
	}
}

void sort_set(User** head) {
	cout << " 1-id / 2-Имя / 3-Фамилия / 4-Возраст / 5-День Рождения " << endl;
	cout << "Введите параметр сортировки: ";
	int set;
	cin >> set;

	switch (set) {
	case 1: selection_sort_shit(head, condit_id);
		break;
	case 2: selection_sort_shit(head, condit_f_n);
		break;
	case 3: selection_sort_shit(head, condit_s_n);
		break;
	case 4: selection_sort_shit(head, condit_age);
		break;
	case 5: selection_sort_shit(head, condit_date);
		break;
	}
}

void selection_sort_shit(User** head, bool(*cmp)(User* frst, User* scnd)) {
	User* tmp1_ptr = new User;
	User* tmp2_ptr = new User;
	User* step1 = new User;
	User* step2 = new User;
	step1 = *head;
	step2 = (*head)->next;
	User* min = new User;
	User* tmp1_prev = new User;
	User* tmp2_prev = new User;
	int count = 0;
	while (step2 != NULL) {
		tmp1_ptr = step1;
		tmp2_ptr = step2;
		min = min_create();
		tmp1_prev = *head;
		tmp2_prev = *head;
		while (tmp2_ptr != NULL) {		//ищем минимальный элемент в неотсортированной части списка
			if (cmp(tmp2_ptr, min)){
				min = tmp2_ptr;
			}
			tmp2_ptr = tmp2_ptr->next;
		}
		tmp2_ptr = min;
		if (tmp1_ptr != *head) {
			while (tmp1_prev->next != tmp1_ptr) {//ищем элемент перед первым обмениваемым элементом
				tmp1_prev = tmp1_prev->next;
			}
		}
		while (tmp2_prev->next != tmp2_ptr) {//ищем элемент перед вторым обмениваемым элементом
			tmp2_prev = tmp2_prev->next;
		}
		int flag_super = 0;
		if (cmp(tmp2_ptr, tmp1_ptr)){
			flag_super = 1;
		}
		if (flag_super == 1) {//обмен элементов местами	
			swap(head, tmp1_prev, tmp1_ptr, tmp2_prev, tmp2_ptr);
		}
		count++;
		step1 = *head;
		for (int i = 0; i < count; i++) {	//переход на следующий шаг в цикле
			step1 = step1->next;
		}step2 = step1->next;
	}
}

void setDownload(User** head, int* vacant_id) {
	cout << " 1 - .txt / 2 - .bin: " << endl;
	cout << "Введите тип загружаемого файла: "; 
	int set = 1;
	cin >> set;

	switch (set) {
	case 1: fromFile(head, vacant_id, "txt");
		break;
	case 2: fromFile(head, vacant_id, "bin");
		break;
	}

}

void setUpload(User* head) {
	cout << "1 - .txt / 2 - .bin: " << endl;
	cout << "Введите тип выгружаемого файла: ";
	int set = 1;
	cin >> set;

	switch (set) {
	case 1: inFile(head, "txt");
		break;
	case 2: inFile(head, "bin");
		break;
	}

}

void fromFile(User** head, int* vacant_id, const char* type) {
	fstream in;
	
	if (strcmp(type, "txt") == 0) {
		in.open("AddList.txt");
	}else if (strcmp(type, "bin") == 0) {
		in.open("AddList.bin", ios::binary | ios::in);
	}
	if (!in) {
		cout << "ERROR: no such file or directory " << endl;
	}
	char* f_name = new char[32];
	char* s_name = new char[32];

	int i = 0;
	int tmp_age = 42, tmp_date[3];
	while (in >> f_name >> s_name >> tmp_age >> tmp_date[0] >> tmp_date[1] >> tmp_date[2]) {
		User* nUser = new User;

		nUser->age = tmp_age;
		for (int i = 0; i < 3; i++) {
			nUser->date[i] = tmp_date[i];
		}
		strcpy(nUser->first_name, f_name);
		strcpy(nUser->second_name, s_name);
		
		(*vacant_id)++;
		nUser->id = *vacant_id;

		nUser->next = nullptr;
		addAtEnd(head, nUser);
	}
	in.close();
}

void fromBinFileAlt(User** head, int* vacant_id) {
	fstream in;

	in.open("AddList.bin", ios::binary|ios::in);
	if (!in) {
		cout << "ERROR: no such file or directory " << endl;
	}
	char* f_name = new char[32];
	char* s_name = new char[32];

	int i = 0;
	int tmp_age = 42, tmp_date[3];
	User* tmpUser = new User;
	while (in.read((char*)&tmpUser, 32)) {
		User* nUser = new User;
		*nUser = *tmpUser;
		(*vacant_id)++;
		nUser->id = *vacant_id;

		nUser->next = nullptr;
		addAtEnd(head, nUser);
	}
	in.close();
}

void inFile(User* head, const char* type) {
	ofstream out;
	if (strcmp(type, "txt") == 0) {
		out.open("out.txt", ios::out);
	}else if (strcmp(type, "bin") == 0) {
		out.open("out.bin", ios::binary | ios::out);
	}
	
	if (!out) {
		cout << "ERROR: no such file or directory" << endl;
	}

	User* tmp = head;
	while (tmp != nullptr) {
		out << tmp->id << " " << tmp->first_name << " " << tmp->second_name << " " << tmp->age << " " << tmp->date[0] << "." << tmp->date[1] << "." << tmp->date[2] << tmp->salary << endl;
		tmp = tmp->next;
	}
	out.close();
}

void changeSalary(User** head) {
	User* sub = new User;
	sub = nullptr;
	sub = search_set(*head);
	while(sub == nullptr) {
		cout << "Введите корректное значение: ";
		sub = search_set(*head);
	}
	printUser(sub);
	int new_salary = 0;
	cout << "Введите новый оклад: "; cin >> new_salary;
	sub->salary = new_salary;
}

int fool(const int beg, const int end) {
	int val;
		cin >> val;
		while (val < beg || val > end) {
			cout << "Введите корректное значение: ";
			cin >> val;
		}
	return val;
}

bool condit_f_n(User* frst, User* scnd) {
	return strcmp(frst->first_name, scnd->first_name) < 0;
}
bool condit_s_n(User* frst, User* scnd) {
	return (strcmp(frst->second_name, scnd->second_name) < 0);
}
bool condit_id(User* frst, User* scnd) {
	return (frst->id < scnd->id);
}
bool condit_age(User* frst, User* scnd) {
	return (frst->age < scnd->age);
}
bool condit_date(User* frst, User* scnd) {
	return ((frst->date[2] < scnd->date[2] || (frst->date[2] == scnd->date[2] && frst->date[1] < scnd->date[1]) || (frst->date[2] == scnd->date[2] && frst->date[1] == scnd->date[1] && frst->date[0] < scnd->date[0])));
}

User* min_create() {
	User* min = new User;
	min->first_name = "яяяяяяяяяяяяяя";
	min->second_name = "яяяяяяяяяяяяяя";
	min->id = 100000;
	min->age = 100;
	for (int i = 0; i < 3; i++) {
		min->date[i] = 3000;
	}
	return min;
}

void swap(User** head, User* tmp1_prev, User* tmp1_ptr, User* tmp2_prev, User* tmp2_ptr) {
	User* tmp3 = new User;
	tmp3 = nullptr;
	if (tmp1_ptr == tmp2_prev && tmp1_ptr != *head) {
		tmp1_ptr->next = tmp2_ptr->next;
		tmp2_ptr->next = tmp1_ptr;

		tmp1_prev->next = tmp2_ptr;
	}
	else if (tmp1_ptr == tmp2_prev && tmp1_ptr == *head) {
		tmp1_ptr->next = tmp2_ptr->next;
		tmp2_ptr->next = tmp1_ptr;

		*head = tmp2_ptr;
	}
	else if (tmp1_ptr != tmp2_prev && tmp1_ptr != *head) {
		tmp3 = tmp1_ptr->next;
		tmp1_ptr->next = tmp2_ptr->next;
		tmp2_ptr->next = tmp3;

		tmp1_prev->next = tmp2_ptr;
		tmp2_prev->next = tmp1_ptr;
	}
	else if (tmp1_ptr != tmp2_prev && tmp1_ptr == *head) {
		tmp3 = tmp1_ptr->next;
		tmp1_ptr->next = tmp2_ptr->next;
		tmp2_ptr->next = tmp3;

		tmp2_prev->next = tmp1_ptr;
		*head = tmp2_ptr;
	}
}

