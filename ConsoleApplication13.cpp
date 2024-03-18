#include <iostream>
#include <string>
#include <locale>
using namespace std;

class bankaccount {
private:
    int accountnumber;
    double balance;
    double interestrate;

public:
    bankaccount(int accnumber, double initialbalance) : accountnumber(accnumber), balance(initialbalance), interestrate(0) {
    }

    void deposit(double amount) {
        balance += amount;
    }

    bool withdraw(double amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        else {
            cout << "Недостаточно средств для снятия!" << endl;
            return false;
        }
    }

    double getbalance() {
        return balance;
    }

    double getinterest() {
        return balance * interestrate * (1 / 12.0);
    }

    void setinterestrate(double rate) {
        interestrate = rate;
    }

    int getaccountnumber() {
        return accountnumber;
    }

    friend bool transfer(bankaccount& account1, bankaccount& account2, double amount);
};

bool transfer(bankaccount& account1, bankaccount& account2, double amount) {
    if (account1.balance >= amount) {
        account1.balance -= amount;
        account2.balance += amount;
        return true;
    }
    else {
        cout << "Недостаточно денег для перевода!" << endl;
        return false;
    }
}

int main() {
    setlocale(LC_ALL, "russian");
    int accnum1, accnum2;
    double initialbalance1 = 0, initialbalance2 = 0, depositamount = 0, withdrawamount = 0, transferamount = 0, interestrate = 0;
    cout << "Введите номер вашей карты (8 цифр): ";
    cin >> accnum1;

    if (to_string(accnum1).length() == 8) {
        bankaccount account1(accnum1, initialbalance1);
        int choice;
        do {
            cout << "Выберите действие:\n";
            cout << "1. Пополнить баланс текущей карты\n";
            cout << "2. Перевести деньги на другую карту\n";
            cout << "3. Рассчитать проценты\n";
            cout << "4. Вывести текущий счет\n";
            cout << "5. Вывести номер банковской карты\n";
            cout << "6. Изменить процентную ставку\n";
            cout << "9. Выход\n";

            cin >> choice;
            double interest = 0.0;
            switch (choice) {

            case 1:
                cout << "Вы выбрали пополнить баланс текущей карты\n";
                cout << "Введите сумму для пополнения: ";
                cin >> depositamount;
                account1.deposit(depositamount);
                cout << "баланс карты " << account1.getaccountnumber() << " успешно пополнен на " << depositamount << " рублей\n";
                break;

            case 2:
                cout << "Введите номер второй карты (8 цифр): ";
                cin >> accnum2;

                if (to_string(accnum2).length() == 8) {
                    bankaccount account2(accnum2, initialbalance2);

                    cout << "Введите сумму для перевода: ";
                    cin >> transferamount;

                    if (transfer(account1, account2, transferamount)) {
                        cout << "Перевод средств на карту " << account2.getaccountnumber() << " выполнен успешно\n";
                    }
                }
                else {
                    cout << "Номер второй карты должен состоять из 8 цифр!\n";
                }
                break;

            case 3:
                interest = account1.getinterest();
                cout << "Проценты по счету: " << interest << " рублей" << endl;
                break;

            case 4:
                cout << "Текущий баланс карты " << account1.getaccountnumber() << ": " << account1.getbalance() << " рублей" << endl;
                break;


            case 5:
                cout << "Номер банковского счета: " << account1.getaccountnumber() << endl;
                break;

            case 6:
                double newinterestrate;
                cout << "Введите новую процентную ставку: ";
                cin >> newinterestrate;
                account1.setinterestrate(newinterestrate);
                cout << "Процентная ставка успешно изменена!" << endl;
                break;

            case 9:
                return 0;
                break;

            default:
                cout << "Некорректный выбор\n";
            }
        } while (choice != 9);
    }
    else {
        cout << "Номер карты должен состоять из 8 цифр!\n";
    }

    return 0;
}