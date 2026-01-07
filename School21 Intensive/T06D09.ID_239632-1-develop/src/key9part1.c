/*------------------------------------
        Здравствуй, человек!
        Чтобы получить ключ
        поработай с комментариями.
-------------------------------------*/

#include <stdio.h>

void input(int *buffer, int *length);
void output(int *buffer, int length);
int sum_numbers(int *buffer, int length);
int find_numbers(int *buffer, int length, int number, int *numbers);

/*------------------------------------
        Функция получает массив данных
        через stdin.
        Выдает в stdout особую сумму
        и сформированный массив
        специальных элементов
        (выбранных с помощью найденной суммы):
        это и будет частью ключа
-------------------------------------*/
int main() {
    int n;
    int arr[10];
    int new_arr[10];

    input(arr, &n);

    if (n == -1) {
        printf("n/a\n");
        return 0;
    }

    int sum = sum_numbers(arr, n);
    if (sum == 0) {
        printf("n/a\n");
        return 0;
    }

    printf("%d\n", sum);

    int new_len = find_numbers(arr, n, sum, new_arr);
    if (new_len == 0) {
        printf("n/a\n");
        return 0;
    }

    output(new_arr, new_len);

    return 0;
}

/*------------------------------------
        Функция должна находить
        сумму четных элементов
        с 0-й позиции.
-------------------------------------*/
int sum_numbers(int *buffer, int length) {
    int sum = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && buffer[i] % 2 == 0) {
            sum += buffer[i];
        }
    }

    return sum;
}

/*------------------------------------
        Функция должна находить
        все элементы, на которые нацело
        делится переданное число и
        записывает их в выходной массив.
-------------------------------------*/
int find_numbers(int *buffer, int length, int number, int *numbers) {
    int k = 0;

    for (int i = 0; i < length; i++) {
        if (buffer[i] != 0 && number % buffer[i] == 0) {
            numbers[k++] = buffer[i];
        }
    }

    return k;
}

/*------------------------------------
        Функция получает массив из stdin
        и его длину. Проверяет ошибки.
-------------------------------------*/
void input(int *buffer, int *length) {
    if (scanf("%d", length) != 1 || *length < 1 || *length > 10) {
        *length = -1;
        return;
    }

    for (int i = 0; i < *length; i++) {
        if (scanf("%d", &buffer[i]) != 1) {
            *length = -1;
            return;
        }
    }
}

/*------------------------------------
        Функция выводит массив через stdout
        с разделителем пробел и финальным \n
-------------------------------------*/
void output(int *buffer, int length) {
    for (int i = 0; i < length; i++) {
        printf("%d", buffer[i]);
        if (i < length - 1) printf(" ");
    }
    printf("\n");
}