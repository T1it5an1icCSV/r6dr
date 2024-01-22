#include<iostream>
#include<cmath>
#include<locale>

double addition(double a, double b) {
    return a + b;
}

double subtraction(double a, double b) {
    return a - b;
}

double multiplication(double a, double b) {
    return a * b;
}

double division(double a, double b) {
    if (b != 0)
        return a / b;
    else {
        std::cout << "ошибка: деление на ноль" << std::endl;
        return 0;
    }
}


double exponentiation(double base, int exponent) {
    return pow(base, exponent);
}


double squareroot(double a) {
    return sqrt(a);
}

double percent(double a) {
    return a * 0.01;
}

int factorial(int n) {
    if (n < 0) {
        std::cout << "ошибка: факториал определен только для неотрицательных чисел" << std::endl;
        return 0;
    }
    else if (n == 0)
        return 1;
    else
        return n * factorial(n - 1);
}

int main() {
    setlocale(LC_ALL, "Russian"); 
    int choice;
    double num1, num2;

    while (true) {
        std::cout << "выберите операцию:" << std::endl;
        std::cout << "1. сложение" << std::endl;
        std::cout << "2. вычитание" << std::endl;
        std::cout << "3. умножение" << std::endl;
        std::cout << "4. деление" << std::endl;
        std::cout << "5. возведение в степень" << std::endl;
        std::cout << "6. нахождение квадратного корня" << std::endl;
        std::cout << "7. нахождение 1 процента от числа" << std::endl;
        std::cout << "8. найти факториал числа" << std::endl;
        std::cout << "9. выйти из программы" << std::endl;
        std::cout << "введите номер операции: ";
        std::cin >> choice;

        if (choice == 9) {
            std::cout << "программа завершена." << std::endl;
            break;
        }

        switch (choice) {
        case 1:
            std::cout << "введите первое число: ";
            std::cin >> num1;
            std::cout << "введите второе число: ";
            std::cin >> num2;
            std::cout << "результат: " << addition(num1, num2) << std::endl;
            break;
        case 2:
            std::cout << "введите первое число: ";
            std::cin >> num1;
            std::cout << "введите второе число: ";
            std::cin >> num2;
            std::cout << "результат: " << subtraction(num1, num2) << std::endl;
            break;
        case 3:
            std::cout << "введите первое число: ";
            std::cin >> num1;
            std::cout << "введите второе число: ";
            std::cin >> num2;
            std::cout << "результат: " << multiplication(num1, num2) << std::endl;
            break;
        case 4:
            std::cout << "введите делимое: ";
            std::cin >> num1;
            std::cout << "введите делитель: ";
            std::cin >> num2;
            std::cout << "результат: " << division(num1, num2) << std::endl;
            break;
        case 5:
            std::cout << "введите число: ";
            std::cin >> num1;
            std::cout << "введите степень: ";
            std::cin >> num2;
            std::cout << "результат: " << exponentiation(num1, static_cast<int>(num2)) << std::endl;
            break;
        case 6:
            std::cout << "введите число: ";
            std::cin >> num1;
            std::cout << "результат: " << squareroot(num1) << std::endl;
            break;
        case 7:
            std::cout << "введите число: ";
            std::cin >> num1;
            std::cout << "результат: " << percent(num1) << std::endl;
            break;
        case 8:
            int n;
            std::cout << "введите число: ";
            std::cin >> n;
            std::cout << "результат: " << factorial(n) << std::endl;
            break;
        default:
            std::cout << "ошибка: некорректный выбор операции." << std::endl;
            break;
        }
        std::cout << std::endl;
    }
    return 0;
}
