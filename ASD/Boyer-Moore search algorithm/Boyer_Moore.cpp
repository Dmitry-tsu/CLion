#include <iostream>
#include <string>

int findFirst(const std::string& text, const std::string& substring) {
    return text.find(substring);
}

int main() {
    std::string text = "std::move_iterator is an iterator adaptor which behaves exactly like the underlying iterator";
    std::string substring = "tor";

    int firstIndex = findFirst(text, substring);
    std::cout << "First Index: " << firstIndex << std::endl;

    return 0;
}



