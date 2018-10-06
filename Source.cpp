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
void selection_sort_f_name(User* head);
void selection_sort_age(User** head);
void action_set(User** head, int* global_id);
void fromTextFile(User** head, int* vacant_id);


int main() {

	srand(time(0));

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

User* fillUser(int* vacant_id) {
	User* tmpUser = new User;
	std::cout << "First name: ";  std::cin.ignore(1); ::cin.getline(tmpUser->first_name, 32);
	std::cout << "Second name: "; std::cin.getline(tmpUser->second_name, 32);
	std::cout << "Age: "; std::cin >> tmpUser->age;
	std::cout << "day: ";    std::cin >> tmpUser->date[0];
	std::cout << "mounth: "; std::cin >> tmpUser->date[1];
	std::cout << "year: ";   std::cin >> tmpUser->date[2];
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

	//user = nullptr;  WWTF?

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

void action_set(User** head, int* global_id) {
	cout << endl << " 0-Показать список / 1-Добавить нового пользователя / 2-Удалить пользователя /" << endl
		 << " 3-Сортировать список / 4-Загрузить список / 5-Сохранить список в файл / 6-Выход " << endl;
	cout << "Выберите действие: ";
	int set;
	cin >> set;

	switch(set){
	case 0: printList(*head);
		break;
	case 1: add_set(head, global_id);
		break;
	case 2: deleteUser(head, search_set(*head));
		break;
	case 3: selection_sort_age(head);
		break;
	case 4: fromTextFile(head, global_id);
		break;
	case 6: TerminateProcess(GetCurrentProcess(), 0);
		break;
	}
}

void selection_sort_f_name(User* head) {
	User* tmp1 = head;			//первая сравниваемая ячейка
	User* tmp2 = head->next;	//вторая сравниваемая ячейка
	User* tmp3 = new User;
	User* min = new User;
		min->first_name = "яяяяяяяяяяя";
	while (tmp1->next != NULL) {
		while (tmp2->next != NULL) {
			tmp2 = tmp2->next;
			if (tmp2->first_name < min->first_name) {
				min->first_name = tmp2->first_name;
			}
		}
		if (min->first_name < tmp1->first_name) { //обмен двух ячеек стека местами
			User* tmp1_next = new User;	//turn out the circle
			User* tmp2_next = new User;	//turn out the circle
			
			tmp1_next->next = tmp1->next;
			tmp2_next->next = tmp2->next;
			
			tmp3 = tmp1;
			tmp1 = min;
			min = tmp3;

			tmp2->next = tmp2_next->next;
			tmp1->next = tmp1_next->next;
		}
		tmp1 = tmp1->next;
		tmp2 = tmp1->next;
	}
}

void selection_sort_age(User** head) {
	User* tmp1_ptr = new User;
	User* tmp2_ptr = new User;

	tmp1_ptr = *head;
	tmp2_ptr = (*head)->next;

	User* step1 = new User;
	User* step2 = new User;
	step1 = *head;
	step2 = (*head)->next;

	User* min = new User;
	min->age = INT_MAX;

	User* tmp1_prev = new User;
	User* tmp2_prev = new User;
	User* tmp3 = new User;
	int count = 0;

	while (step2 != NULL) {
		min = new User;
		min->age = INT_MAX;
		tmp1_prev = *head;
		tmp2_prev = *head;
		tmp3 = NULL;
		while (tmp2_ptr != NULL) {		//ищем минимальный элемент в неотсортированной части списка
			if(tmp2_ptr->age < min->age){
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
		if (tmp1_ptr->age > tmp2_ptr->age) {//обмен элементов местами	
			if (tmp1_ptr == tmp2_prev && tmp1_ptr != *head) {
				tmp1_ptr->next = tmp2_ptr->next;
				tmp2_ptr->next = tmp1_ptr;

				tmp1_prev->next = tmp2_ptr;
			}else if(tmp1_ptr == tmp2_prev && tmp1_ptr == *head){
				tmp1_ptr->next = tmp2_ptr->next;
				tmp2_ptr->next = tmp1_ptr;

				*head = tmp2_ptr;
			}else if (tmp1_ptr != tmp2_prev && tmp1_ptr != *head) {
				tmp3 = tmp1_ptr->next;			
				tmp1_ptr->next = tmp2_ptr->next;
				tmp2_ptr->next = tmp3;

				tmp1_prev->next = tmp2_ptr;
				tmp2_prev->next = tmp1_ptr;
			}else if (tmp1_ptr != tmp2_prev && tmp1_ptr == *head) {
				tmp3 = tmp1_ptr->next;
				tmp1_ptr->next = tmp2_ptr->next;
				tmp2_ptr->next = tmp3;

				tmp2_prev->next = tmp1_ptr;
				*head = tmp2_ptr;
			}	
		}

		count++;
		step1 = *head;
		for (int i = 0; i < count; i++) {	//переход на следующий шаг в цикле
			step1 = step1->next;
		}
		step2 = step1->next;
		
		tmp1_ptr = step1;
		tmp2_ptr = step2;
	}
}

void fromTextFile(User** head, int* vacant_id) {
	fstream in;
	in.open("AddList.txt");
	if (!in) {
		cout << "ERROR: no such file or directory ";
	}

	User* nUser = new User;
	char* f_name = new char[32];
	char* s_name = new char[32];
	while (in >> f_name >> s_name >> nUser->age >> nUser->date[0] >> nUser->date[1] >> nUser->date[2]) {
		(*vacant_id)++;
		nUser->id = *vacant_id;
		strcpy(nUser->first_name, f_name);
		strcpy(nUser->second_name, s_name);

		nUser->next = nullptr;
		
		addAtEnd(head, nUser);

	}
	in.close();
}

