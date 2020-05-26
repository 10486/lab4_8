#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <windows.h>
#define NAME_LENGTH 20
#define PHONE_NUMBER_LENGTH 20
#pragma region Struct
typedef struct note {
	char first_name[NAME_LENGTH];
	char second_name[NAME_LENGTH];
	char phone[PHONE_NUMBER_LENGTH];
	int birthday[3];
}Note;
// Выделяет память на структуру и заполняет ее
Note* input_struct() {
	Note* data = (Note*)malloc(sizeof(Note));
	printf("Введите имя: ");
	scanf("%s", &data->first_name);
	printf("Введите фамилию: ");
	scanf("%s", &data->second_name);
	printf("Введите номер телефона(максимум %d цифр): ", PHONE_NUMBER_LENGTH);
	scanf("%s", &data->phone);
	char flag;
	for (size_t i = 0; i < PHONE_NUMBER_LENGTH; i++)
	{
		if (data->phone[i] == '\0')break;
		flag = 0;
		for (size_t j = 0; j < 10; j++)
		{
			if (data->phone[i] == ('0' + j))flag = 1;
		}
		if (data->phone[i] == '-')flag = 1;
		if (!flag) {
			printf("Все хуйня двай по новой");
			exit(1);
		}
	}
	printf("Введите дату рождения дд.мм.гггг (через точки): ");
	scanf("%d.%d.%d", &data->birthday[0], &data->birthday[1], &data->birthday[2]);
	if (data->birthday[0] > 31 || data->birthday[0] < 0) {
		printf("Все хуйня двай по новой");
		exit(1);
	}
	if (data->birthday[1] > 12 || data->birthday[1] < 0) {
		printf("Все хуйня двай по новой");
		exit(1);
	}
	if (data->birthday[2] < 0) {
		printf("Все хуйня двай по новой");
		exit(1);
	}
	return data;
}
// Вывод структуры
void output_struct(Note* data) {
	printf("Имя: %s\n", data->first_name);
	printf("Фамилия: %s\n", data->second_name);
	printf("Номер телефона: %s\n", data->phone);
	printf("Дата рождения : %d.%d.%d\n", data->birthday[0], data->birthday[1], data->birthday[2]);
	return;
}
// Сравнению по алфавиту (сначала фамилия потом имя)
int compare_by_names(const Note* first, const Note* second) {
	char compare_by_second_name = strcmp(first->second_name, second->second_name);
	return (compare_by_second_name ? compare_by_second_name : strcmp(first->first_name, second->first_name));
}
#pragma endregion
#pragma region List
// Элемент списка с данными и ссылкой на следующий элемент
typedef struct node {
	struct node* next;
	Note* data;
}Node;
// Односвязный список
typedef struct list {
	Node* head;
}List;
//Добавление в список
void append(List* list, Note* el) {
	Node* tmp = calloc(1, sizeof(Node));
	tmp->data = el;
	// Вставляем элемент если список пуст
	if (list->head == NULL) {
		list->head = tmp;
	}
	else {
		// Вставляем эелмент если первый элемент больше нового или равен ему
		if (compare_by_names(el, list->head->data) < 0) {
			tmp->next = list->head;
			list->head = tmp;
		}
		else {
			// Идем по списку пока не дойдем до конца или не найдем элемет больше нового
			Node* current = list->head->next;
			if (current != NULL) {
				while (compare_by_names(el, current->data) >= 0) {
					if (current->next == NULL) {
						current->next = tmp;
						return;
					}
					current = current->next;
				}
			}
			list->head->next = tmp;
		}
	}
}
// Вывод всех подходящих структур
void find_in_list(List* list, int month) {
	char flag = 0;
	// крутой проход по списку в цикле for
	for (Node* tmp = list->head; tmp != NULL; tmp = tmp->next)
	{
		// Выводим если мы нашли нужный элемент 
		if (tmp->data->birthday[1] == month) {
			printf("----------------------------------------------\n");
			output_struct(tmp->data);
			flag = 1;
		}
	}
	if (!flag) {
		printf("Структур с таким значением месяца нет\n");
	}
}
#pragma endregion
void main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int counter = 0, tmp, input;
	List* list = calloc(1, sizeof(List));
	Note* t;
	do
	{
		// Вводим структуру
		t = input_struct();
		// Добавляем в список
		append(list, t);
		counter++;
		printf("ВСЕ СТРУКТУРЫ КОТОРЫЕ ЕСТЬ В СПИСКЕ В ТОМ ПОРЯДКЕ КАК ИХ ОТСОРТИРОВАЛИ:\n");
		for (Node* tmp = list->head; tmp != NULL; tmp = tmp->next)
		{
			output_struct(tmp->data);
			printf("----------------------------------------------\n");
		}
		printf("Продолжить ввод (1-да, 0-нет)\n");
		scanf("%d", &tmp);
	} while (tmp);
	char flag = 0;
	printf("Введите месяц: ");
	scanf("%d", &input);
	find_in_list(list, input);
	printf("----------------------------------------------\n");
	//Выводим все структуры
	printf("ВСЕ СТРУКТУРЫ КОТОРЫЕ ЕСТЬ В СПИСКЕ В ТОМ ПОРЯДКЕ КАК ИХ ОТСОРТИРОВАЛИ,\nВСЕ СТРУКТУРЫ ПО ЗАПРОСУ БЫЛИ ВЫВЕДЕНЫ ВЫШЕ:\n");
	for (Node* tmp = list->head; tmp != NULL; tmp = tmp->next)
	{
		output_struct(tmp->data);
		printf("----------------------------------------------\n");
	}
}
