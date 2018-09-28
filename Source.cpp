#include <iostream>
#include <conio.h>
#include <string.h>
#include <stdio.h>

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
void addAtEnd(User** first, User* nUser);
void addAtBegin(User** root, User* nUser);
User* reverse(User* x);	
User* deleteUser(User* head, User* someUser);
User* search(User* user, int val);
User* insert(User* head, User* next_User, User* prev_User);

int main() {

	User* head = NULL;

	for (int i = 0; i < 1; i++) {
		addAtEnd(&head, createUser());
	}

	printList(head);



	_getch();
	return 0;
}

void printList(User* first) {
	User* temp = first;
	while (temp != NULL) {
		std::cout << temp->first_name << std::endl; 
		std::cout << temp->second_name << std::endl;
		std::cout << temp->age << std::endl;
		for (int i = 0; i < 3; ++i) {
			std::cout << *temp->date << std::endl;
			temp->date = temp->date + 1;
		}
		temp = temp->next;
	}
	std::cout << std::endl;
}

User* createUser() {
	User * nUser = new User;
	std::cout << "First name: "; std::cin.getline(nUser->first_name, 32); 
	std::cout << "Second name: "; std::cin.getline(nUser->second_name, 32);
	std::cout << "Age: "; std::cin >> nUser->age;
	std::cout << "day: ";    std::cin >> nUser->date[0];
	std::cout << "mounth: "; std::cin >> nUser->date[1];
	std::cout << "year: ";   std::cin >> nUser->date[2];
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

User* insert(User* head, User* next_User, User* prev_User) {
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







