#include <iostream>
#include <string>

int findFirst(const std::string& text, const std::string& substring) {
    int textLength = text.length();
    int subLength = substring.length();

    if (subLength > textLength) {
        return -1; // если длина подстроки больше текста, она не может быть найдена
    }

    int skipTable[256];

    for (int i = 0; i < 256; i++) {
        skipTable[i] = subLength; // устанавливаем длину подстроки в качестве значения по умолчанию
    }

    for (int i = 0; i < subLength - 1; i++) {
        skipTable[substring[i]] = subLength - i - 1; // заполняем таблицу последнего вхождения символа в подстроке
    }

    int i = subLength - 1; // указатель на текущий символ в тексте
    int j = subLength - 1; // указатель на текущий символ в подстроке

    while (i < textLength) {
        if (text[i] == substring[j]) {
            // если символы совпадают, продолжаем сравнивать предыдущие символы
            if (j == 0) {
                return i; // если все символы подстроки совпали, возвращаем индекс первого символа подстроки
            }
            i--;
            j--;
        }
        else {
            // если символы не совпадают, сдвигаем указатель в тексте вправо на основе таблицы последнего вхождения
            i = i + skipTable[text[i]];
            j = subLength - 1; // сбрасываем указатель на последний символ подстроки
        }
    }

    return -1; // если подстрока не была найдена
}

int main() {
    std::string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    std::string substring = "tor";
    int index = findFirst(text, substring);
    std::cout << "First occurrence index: " << index << std::endl;
    return 0;
}


