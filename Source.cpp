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
	User* next;
};

void printList(User* first);
User* createUser();
User* createUserRand();
void addAtEnd(User** first, User* nUser);
void addAtBegin(User** root, User* nUser);
User* reverse(User* x);	
User* deleteUser(User* head, User* someUser);
User* search(User* user, int val);
User* insert(User* head, User* next_User, User* prev_User);

int main() {

	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);

	User* head = NULL;


	for (int i = 0; i < 3; i++) {
		addAtEnd(&head, createUserRand());
	}

	printList(head);

	addAtEnd(&head, createUserRand());
	head = insert(head, head, createUserRand());
	addAtBegin(&head, createUserRand());

	printList(head);



	_getch();
	return 0;
}

void printList(User* first) {
	User* temp = first;

	cout << setw(9) << "Фамилия" << setw(9) << "Имя" << setw(13) << "Полных лет" << setw(15) << "Дата рождения" << endl;

	while (temp != NULL) {
		std::cout << setw(9) << temp->first_name << setw(9) << temp->second_name << setw(10) << temp->age << setw(9);

		

		/*User* temp_date = temp;
		for (int i = 0; i < 2; ++i) {
			std::cout << *temp_date->date << ".";
			temp_date->date = temp_date->date + 1;
		}std::cout << *temp_date->date << std::endl;

		//delete temp_date;*/

		temp = temp->next;
	}
	std::cout << std::endl;
}

User* fillUser() {
	User* tmpUser = new User;

	std::cout << "First name: ";  std::cin.getline(tmpUser->first_name, 32);
	std::cout << "Second name: "; std::cin.getline(tmpUser->second_name, 32);
	std::cout << "Age: "; std::cin >> tmpUser->age;
	std::cout << "day: ";    std::cin >> tmpUser->date[0];
	std::cout << "mounth: "; std::cin >> tmpUser->date[1];
	std::cout << "year: ";   std::cin >> tmpUser->date[2];

	return tmpUser;
}

User* createUser() {
	User * nUser = new User;
	std::cout << "First name: ";  std::cin.getline(nUser->first_name, 32);
	std::cout << "Second name: "; std::cin.getline(nUser->second_name, 32);
	std::cout << "Age: "; std::cin >> nUser->age;
	std::cout << "day: ";    std::cin >> nUser->date[0];
	std::cout << "mounth: "; std::cin >> nUser->date[1];
	std::cout << "year: ";   std::cin >> nUser->date[2];
	nUser->next = NULL;
	return nUser;
}

User* createUserRand() {

	char* f_names[] = { "Иван", "Сергей", "Дмитрий", "Александр", "Арсений", "Данил", "Михаил", "Кристина" };
	char* s_names[] = { "Смирнов", "Иванов", "Кузнецов", "Соколов", "Попов", "Лебедев", "Алексеев", "Орлов" };

	User * nUser = new User;
	  nUser->first_name = f_names[rand() % 8];
	  nUser->second_name = s_names[rand() % 8];
      nUser->age = rand() % 40 + 22;
	    nUser->date[0] = rand() % 30 + 1;
		nUser->date[1] = rand() % 12 + 1;
	    nUser->date[2] = 2018 - nUser->age;
	  nUser->next = NULL;
	return nUser;
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

User* search(User* user, int val) {
	while (user != NULL && user->age != val) {
		user = user->next;
	}
	return user;
}

User* insert(User* head, User* next_User, User* prev_User) { // insert new User before next_User
	if (next_User == head) {
		prev_User->next = head;
		head = prev_User;
	}else {
		User* tmp = head;
		while (tmp->next != next_User) {
			tmp = tmp->next;
		}
		prev_User->next = next_User;
		tmp->next = prev_User;
	}
	return head;
}

User* deleteUser(User* head, User* someUser) {
	if (someUser != NULL) {
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
	User* tmp, *y = x, *r = NULL;
	while (y != NULL) {
		tmp = y->next;
		y->next = r;
		r = y;
		y = tmp;
	}
	return r;
}







