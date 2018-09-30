#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <iomanip>



using namespace std;

struct User {
	char* first_name = new char[32];
	char* second_name = new char[32];
	int age;
	int* date = new int[3];
	int id;
	User* next;
};

void printList(User* first);
void printUser(User* first);
User* createUser(int &vacant_id);
User* createUserRand(int &vacant_id);
User* fillUser(int &vacant_id);
User* fillUserRand(int &vacant_id);
void addAtEnd(User** first, User* nUser);
void addAtBegin(User** root, User* nUser);
User* reverse(User* x);	
User* deleteUser(User* head, User* someUser);
void insert(User** head, User* next_User, User* prev_User);
User* search_set(User* user);
User* search_id(User* user);
User* search_f_name(User* user);
User* search_s_name(User* user);
User* search_age(User* user);
User* search_brday(User* user);


int main() {

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	User* head = nullptr;
	int g_id = 1200;


	for (int i = 0; i < 3; i++) {
		addAtEnd(&head, createUserRand(g_id));
	}

	printList(head);

	addAtEnd(&head, createUserRand(g_id));
	insert(&head, head, createUserRand(g_id));
	addAtBegin(&head, createUserRand(g_id));

	//deleteUser(head, search_set(head));

	printList(head);

	printUser(search_set(head));

	_getch();
	return 0;
}

void printList(User* first) {
	User* temp = first;
	
	cout << "ID" << setw(11) << "Имя" << setw(9) << "Фамилия" << setw(13) << "Полных лет" << setw(15) << "Дата рождения" << endl;

	while (temp != nullptr) {
		std::cout << temp->id << setw(11) << temp->first_name << setw(9) << temp->second_name << setw(10) << temp->age << setw(9);
		std::cout << temp->date[0] << "." << temp->date[1] << "." << temp->date[2] << std::endl;

		temp = temp->next;
	}
	std::cout << std::endl;
}

void printUser(User* first){
	User* temp = first;
	if (temp != nullptr) {
		cout << "ID" << setw(11) << "Имя" << setw(9) << "Фамилия" << setw(13) << "Полных лет" << setw(15) << "Дата рождения" << endl;

		std::cout << temp->id << setw(11) << temp->first_name << setw(9) << temp->second_name << setw(10) << temp->age << setw(9);
		std::cout << temp->date[0] << "." << temp->date[1] << "." << temp->date[2] << std::endl;

		std::cout << std::endl;
	}else {
		cout << endl << "ERROR: Не найдено данных!" << endl;
	}
}

User* fillUser(int &vacant_id) {
	User* tmpUser = new User;

	std::cout << "First name: ";  std::cin.getline(tmpUser->first_name, 32);
	std::cout << "Second name: "; std::cin.getline(tmpUser->second_name, 32);
	std::cout << "Age: "; std::cin >> tmpUser->age;
	std::cout << "day: ";    std::cin >> tmpUser->date[0];
	std::cout << "mounth: "; std::cin >> tmpUser->date[1];
	std::cout << "year: ";   std::cin >> tmpUser->date[2];
	vacant_id++;
	tmpUser->id = vacant_id;	
	tmpUser->next = nullptr;

	return tmpUser;
}

User* fillUserRand(int &vacant_id) {

	const char* f_names[] = { "Иван", "Сергей", "Дмитрий", "Александр", "Арсений", "Данил", "Михаил", "Кристина" };
	const char* s_names[] = { "Смирнов", "Иванов", "Кузнецов", "Соколов", "Попов", "Лебедев", "Алексеев", "Орлов" };

	User* tmpUser = new User;
	strcpy(tmpUser->first_name, f_names[rand() % 8]);	//tmpUser->first_name = f_names[rand() % 8];
	strcpy(tmpUser->second_name, s_names[rand() % 8]);	//tmpUser->second_name = s_names[rand() % 8];
	tmpUser->age = rand() % 40 + 22;
		tmpUser->date[0] = rand() % 30 + 1;
		tmpUser->date[1] = rand() % 12 + 1;
		tmpUser->date[2] = 2018 - tmpUser->age;
	vacant_id++;
	tmpUser->id = vacant_id;
		tmpUser->next = nullptr;
	return tmpUser;
}

User* createUser(int &vacant_id) {
	User * nUser = new User;
	nUser = fillUser(vacant_id);
	return nUser;
}

User* createUserRand(int &vacant_id) {
	User * nUser = new User;
	nUser = fillUserRand(vacant_id);
	return nUser;
}

void add_set(User* head, int global_id) {
	int set = 0;
	cout << "1-Добавить в начало / 2-Добавить в конец / 3-Добавить перед ячейкой ";
	cout << "Введите вариант добавления: ";
	
	switch (set) {
		case 1: addAtBegin(&head, createUserRand(global_id));
			break;
		case 2: addAtEnd(&head, createUserRand(global_id));
			break;
		case 3: insert(&head, search_set(), createUserRand(global_id));
			break;
	}
}
	
void addAtEnd(User** first, User* nUser) {
	User* temp = *first;
	if (temp == nullptr) {
		*first = nUser;
	}else {
		while (temp->next != nullptr) {
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


User* deleteUser(User* head, User* someUser) {

	if (someUser != nullptr) {
		if (someUser == head) {
			head = head->next;
			delete someUser;
		}
		else {
			User* tmp = head;
			while (tmp->next != someUser) {
				tmp = tmp->next;
			}
			tmp->next = someUser->next;
			delete someUser;
		}
	}
	return head;
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

	user = nullptr;

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
	while (user != nullptr && user->first_name != val) {
		user = user->next;
	}
	return user;
}

User* search_s_name(User* user) {

	cout << "Введите фамилию: ";
	char* val = new char[32];
	cin.getline(val, 32);
	cin >> val;
	while (user != nullptr && user->second_name != val) {
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

//void menu() {
//	int choose = 0;
//	cout << "Введите параметр поиска: ";
//}



void action_set(User* head) {
	cout << " 0-Показать список / 1-Добавить нового пользователя / 2-Удалить пользователя  / 3-Добавить рандомного пользователя /" << endl
		 << " 4-Сортировать список / 5-Загрузить список / 6-Сохранить список в файл /  " << endl;
	cout << "Введите параметр поиска: ";
	int set;
	cin >> set;

	switch(set){
	case 0: printList(head);
		break;
	case 1: add
	}
}





