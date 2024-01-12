#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    int num1, num2;
    char opr;
    bool flag = true;

    while (flag)
    {
        cout << "Enter two integers: ";
        cin >> num1 >> num2;
        cout << endl;
        cout << "Enter operator: + (addition), - (subtraction), * (multiplication), / (division): ";
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
                cout << "ERROR nCannot divide by zero" << endl;
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
