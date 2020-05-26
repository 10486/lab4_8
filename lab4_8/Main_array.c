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
int main() {
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int tmp, counter = 0, input;
	Note* arr[15];
	do
	{
		// вводим структуру
		arr[counter] = input_struct();
		counter++;
		printf("Все структуры:\n");
		for (size_t i = 0; i < counter; i++)
		{
			printf("----------------------------------------------\n");
			output_struct(arr[i]);
		}
		printf("продолжить ввод (1-да, 0-нет)\n");
		scanf("%d", &tmp);
	} while (tmp);
	// сортируем
	// arr - указатель на начало массива
	// counter - кол-во элементов
	// sizeof(Note*) - размер элементов
	// compare_by_number - функция для сравнения
	qsort(arr, counter, sizeof(Note*), compare_by_names);
	char flag = 0;
	printf("Введите месяц: ");
	scanf("%d", &input);
	for (size_t i = 0; i < counter; i++)
	{
		// выводим только совпадающие по месяцу рождения стуктуры
		if (arr[i]->birthday[1] == input) {
			printf("----------------------------------------------\n");
			output_struct(arr[i]);
			flag = 1;
		}
	}
	if (!flag) {
		printf("Структур с таким значением месяца нет\n");
	}
	// Выводим все структуры
	printf("Все структуры:\n");
	for (size_t i = 0; i < counter; i++)
	{
		printf("----------------------------------------------\n");
		output_struct(arr[i]);
	}
}