#include <iostream>
#include <string>
#include <vector>
//Тут сделаль
std::vector<int> findAll(const std::string& text, const std::string& substring, int startIndex, int endIndex, int occurrencesCount = 0)
{
    std::vector<int> indexes;
    int textLength = text.length();
    int subLength = substring.length();

    if (subLength > textLength || startIndex < 0 || endIndex >= textLength)
    {
        return indexes;
    }

    int skipTable[256];
    for (int i = 0; i < 256; i++)
    {
        skipTable[i] = subLength;
    }
    for (int i = 0; i < subLength - 1; i++)
    {
        skipTable[substring[i]] = subLength - i - 1;
    }

    int i = startIndex + subLength - 1;
    int j = subLength - 1;
    while (i <= endIndex)
    {
        if (text[i] == substring[j])
        {
            if (j == 0)
            {
                indexes.push_back(i);
                occurrencesCount--;
                if (occurrencesCount == 0)
                {
                    return indexes; // достигнуто заданное количество вхождений
                }
                i += subLength;
                j = subLength - 1;
            }
            else
            {
                i--;
                j--;
            }
        }
        else
        {
            i = i + skipTable[text[i]];
            j = subLength - 1;
        }
    }

    return indexes;
}

// Остальной код без изменений
int findFirst(const std::string& text, const std::string& substring, int startIndex, int endIndex)
{
    std::vector<int> indexes = findAll(text, substring, startIndex, endIndex, 1);

    if (indexes.empty())
    {
        return -1;
    }

    return indexes[0];
}

int main()
{
    std::string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    std::string substring = "tor";
    std::vector<int> indexes = findAll(text, substring, 0, text.length() - 1, 0);
    std::cout << "Indexes of all occurrences in the whole text: ";
    for (int i = 0; i < indexes.size(); i++)
    {
        std::cout << indexes[i] << " ";
    }
    std::cout << std::endl;

    indexes = findAll(text, substring, 17, text.length() - 1, 0);
    std::cout << "Indexes of all occurrences in the substring: ";
    for (int i = 0; i < indexes.size(); i++)
    {
        std::cout << indexes[i] << " ";
    }
    std::cout << std::endl;

    indexes = findAll(text, substring, 28, 36, 1);
    std::cout << "Indexes of the first occurrence in the range (28, 36): ";
    for (int i = 0; i < indexes.size(); i++)
    {
        std::cout << indexes[i] << " ";
    }
    std::cout << std::endl;

    int firstIndex = findFirst(text, substring, 0, text.length() - 1);
    std::cout << "First occurrence in the whole text: " << firstIndex << std::endl;

    firstIndex = findFirst(text, substring, 17, text.length() - 1);
    std::cout << "First occurrence in the substring: " << firstIndex << std::endl;

    firstIndex = findFirst(text, substring, 28, 36);
    std::cout << "First occurrence in the range (28, 36): " << firstIndex << std::endl;

    return 0;
}




















