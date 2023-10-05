#include <iostream>
#include <string>
#include <vector>

std::vector<int> findAll(const std::string& text, const std::string& substring, int startIndex, int endIndex) {
    std::vector<int> indexes;
    int textLength = text.length();
    int subLength = substring.length();

    if (subLength > textLength || startIndex < 0 || endIndex >= textLength) {
        return indexes; // если длина подстроки больше текста или заданы некорректные границы поиска, возвращаем пустой вектор
    }

    int skipTable[256];

    for (int i = 0; i < 256; i++) {
        skipTable[i] = subLength; // устанавливаем длину подстроки в качестве значения по умолчанию
    }

    for (int i = 0; i < subLength - 1; i++) {
        skipTable[substring[i]] = subLength - i - 1; // заполняем таблицу последнего вхождения символа в подстроке
    }

    int i = startIndex + subLength - 1; // указатель на текущий символ в тексте
    int j = subLength - 1; // указатель на текущий символ в подстроке

    while (i <= endIndex) {
        if (text[i] == substring[j]) {
            // если символы совпадают, продолжаем сравнивать предыдущие символы
            if (j == 0) {
                indexes.push_back(i); // если все символы подстроки совпали, добавляем индекс первого символа подстроки в вектор
                i += subLength; // сдвигаем указатель в тексте на длину подстроки
                j = subLength - 1; // сбрасываем указатель на последний символ подстроки
            }
            else {
                i--;
                j--;
            }
        }
        else {
            // если символы не совпадают, сдвигаем указатель в тексте вправо на основе таблицы последнего вхождения
            i = i + skipTable[text[i]];
            j = subLength - 1; // сбрасываем указатель на последний символ подстроки
        }
    }

    return indexes;
}

int main() {
    std::string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    std::string substring = "tor";
    std::vector<int> indexes = findAll(text, substring, 0, text.length() - 1);

    std::cout << "Indexes of all occurrences in the whole text: ";
    for (int i = 0; i < indexes.size(); i++) {
        std::cout << indexes[i] << " ";
    }
    std::cout << std::endl;

    indexes = findAll(text, substring, 17, text.length() - 1);

    std::cout << "Indexes of all occurrences in the substring: ";
    for (int i = 0; i < indexes.size(); i++) {
        std::cout << indexes[i] << " ";
    }
    std::cout << std::endl;

    indexes = findAll(text, substring, 28, 36);

    std::cout << "Indexes of all occurrences in the range (28, 36): ";
    for (int i = 0; i < indexes.size(); i++) {
        std::cout << indexes[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}






