#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

int main()
{
    int num1, num2;
    char opr;
    bool flag = true;
    int fact = 1; // Здесь инициализируем переменную fact

    while (flag)
    {
        cout << "Enter two integers: ";
        cin >> num1 >> num2;
        cout << endl;
        cout << "Enter operator: + (addition), - (subtraction), * (multiplication), / (division), ^ (exponentiation), s (square root), % (percent), ! (factorial), 9 (exit): ";
        cin >> opr;
        cout << endl;
        cout << num1 << " " << opr << " " << num2 << " = ";

        switch (opr)
        {
        case '+':
            cout << num1 + num2 << endl;
            break;
        case '-':
            cout << num1 - num2 << endl;
            break;
        case '*':
            cout << num1 * num2 << endl;
            break;
        case '/':
            if (num2 != 0)
                cout << num1 / num2 << endl;
            else
                cout << "ERRORnCannot divide by zero" << endl;
            break;
        case '^':
            cout << pow(num1, num2) << endl;
            break;
        case 's':
            cout << sqrt(num1) << endl;
            break;
        case '%':
            cout << num1 * 0.01 * num2 << endl;
            break;
        case '!':
            fact = 1; // Cбрасываем значение переменной перед каждым вычислением факториала
            for (int i = 1; i <= num1; i++)
            {
                fact *= i;
            }
            cout << fact << endl;
            break;
        case '9':
            flag = false;
            break;
        default:
            cout << "Illegal operation" << endl;
        }

        if (flag)
        {
            cout << "Enter '9' to quit or any other key to continue: ";
            char choice;
            cin >> choice;
            cout << endl;

            if (choice == '9')
                flag = false;
        }
    }

    return 0;
}
