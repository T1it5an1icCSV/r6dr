#include <iostream>
#include <string>
#include <algorithm>
#include <random>
#include <locale>
#include <windows.h>

using namespace std;

string reverseWord(string word) {
    reverse(word.begin(), word.end());
    return word;
}

string removeVowels(string word) {
    word.erase(std::remove_if(word.begin(), word.end(),
        [](char c) { return string("аеёиоуыэюяАЕЁИОУЫЭЮЯ").find(c) != string::npos; }), word.end());
    return word;
}

string removeConsonants(string word) {
    word.erase(remove_if(word.begin(), word.end(),
        [](char c) { return string("бвгджзйклмнпрстфхцчшщБВГДЖЗЙКЛМНПРСТФХЦЧШЩ").find(c) != string::npos; }), word.end());
    return word;
}

string shuffleWord(string word) {
    random_device rd;
    mt19937 g(rd());
    shuffle(word.begin(), word.end(), g);
    return word;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, ".1251");

    string word;
    cout << "Введите слово: ";
    cin >> word;

    cout << "Выберите действие: \n";
    cout << "1. Вывести слово задом наперед \n";
    cout << "2. Вывести слово без гласных \n";
    cout << "3. Вывести слово без согласных \n";
    cout << "4. Рандомно раскидать буквы в слове \n";

    int choice;
    cin >> choice;

    switch (choice) {
    case 1:
        cout << "Результат: " << reverseWord(word) << "\n";
        break;
    case 2:
        cout << "Результат: " << removeVowels(word) << "\n";
        break;
    case 3:
        cout << "Результат: " << removeConsonants(word) << "\n";
        break;
    case 4:
        cout << "Результат: " << shuffleWord(word) << "\n";
        break;
    default:
        cout << "Неверный выбор \n";
        break;
    }

    return 0;
}
