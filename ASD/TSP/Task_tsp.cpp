#include <iostream>

void nextPermutation(int* arr, int n, int& minWay, int** matr) {
    // 1. Находим максимальное значение i
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    // Если такого i не существует, процесс завершен
    if (i < 0) {
        return;
    }

    // 2. Находим максимальное значение j
    int j = n - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }

    // 3. Меняем P[i] и P[j] местами
    int temp = arr[i];
    arr[i] = arr[j];
    arr[j] = temp;

    // 4. Упорядочиваем «хвост» по возрастанию
    for (int k = i + 1; k < n - 1; k++) {
        for (int l = i + 1; l < n - 1 - (k - i); l++) {
            if (arr[l] > arr[l + 1]) {
                int temp = arr[l];
                arr[l] = arr[l + 1];
                arr[l + 1] = temp;
            }
        }
    }

    // Вычисляем вес маршрута
    int way = 0;
    for (int k = 0; k < n - 1; k++) {
        way += matr[arr[k] - 1][arr[k + 1] - 1];
    }
    way += matr[arr[n - 1] - 1][arr[0] - 1];

    // Если полученный маршрут меньше минимального, обновляем значения
    if (way < minWay) {
        minWay = way;
    }
}

int main() {
    int count_city = 4; // Количество городов

    // Создаем и заполняем матрицу стоимостей маршрутов
    int** Matr_Way_Weight = new int*[count_city];
    for (int i = 0; i < count_city; i++) {
        Matr_Way_Weight[i] = new int[count_city];
        for (int j = 0; j < count_city; j++) {
            // Заполнение случайными значениями
            Matr_Way_Weight[i][j] = rand() % 20 + 1;
        }
    }

    int* Way = new int[count_city + 1]; // Массив маршрута
    int minWay; // Минимальный вес маршрута

    // Инициализация массива маршрута
    for (int i = 0; i < count_city + 1; i++) {
        Way[i] = i + 1;
    }

    // Вычисляем вес начального маршрута
    minWay = 0;
    for (int i = 0; i < count_city; i++) {
        minWay += Matr_Way_Weight[Way[i] - 1][Way[i + 1] - 1];
    }

    // Генерируем все перестановки
    /* do {
        nextPermutation(Way, count_city + 1, minWay, Matr_Way_Weight);
    } while (true); */

    // Выводим минимальный маршрут и его вес
    std::cout << "Минимальный маршрут: ";
    for (int i = 0; i < count_city + 1; i++) {
        std::cout << Way[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Вес минимального маршрута: " << minWay << std::endl;

    // Освобождаем память
    for (int i = 0; i < count_city; i++) {
        delete[] Matr_Way_Weight[i];
    }
    delete[] Matr_Way_Weight;
    delete[] Way;

    return 0;
}


