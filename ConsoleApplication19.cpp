#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Fish {
public:
    int hunger;
    int stepsWithoutFood;

public:
    Fish() : hunger(0), stepsWithoutFood(0) {}

    virtual void eat() {}
    virtual void reproduce() {}
    virtual void update() {}
    virtual void golodnay_smer() {}
    virtual ~Fish() {}
};

class PredatorFish : public Fish {
public:
    int predatorCount;

    PredatorFish() : predatorCount(0) {} // Инициализация переменной predatorCount

    void eat() override {
        hunger = 0;
    }

    void reproduce() override {
        hunger += 5;
        while (hunger >= 5) {
            predatorCount++;
            hunger -= 5;
        }
    }

    void golodnay_smer() override {
        stepsWithoutFood++;
        if (stepsWithoutFood >= 10) {
            predatorCount--;
            stepsWithoutFood = 0; // Сброс счетчика шагов без еды
        }
    }

};


class PreyFish : public Fish {
public:
    int preyCount;

    PreyFish() : preyCount(0) {} // Инициализация переменной predatorCount
    void eat() override {
        hunger = 0;
    }

    void reproduce() override {
        hunger += 3;
        if (hunger >= 3) {
            preyCount++;
        }
    }
};

class Algae {
private:
    int quantity;

public:
    Algae(int quantity) : quantity(quantity) {}

    void setQuantity(int newQuantity) {
        quantity = newQuantity;
    }

    void reduceQuantity() {
        if (quantity > 0) {
            quantity--;
        }
        else {
            std::cout << "Нельзя снизить количество водорослей ниже нуля!" << std::endl;
        }
    }

    int getQuantity() const {
        return quantity;
    }
};

class Aquarium {
private:
    vector<PredatorFish*> predators;
    vector<PreyFish*> prey;
    Algae* algae;

    int steps;
    int deadPredator;
    int deadFishCount;
    int deadAlgaeCount;
    int preyCount;

public:
    Aquarium() : algae(new Algae(0)), steps(0), deadFishCount(0), deadAlgaeCount(0), deadPredator(0), preyCount(0) {}

    void addPredatorFish(int count) {
        for (int i = 0; i < count; i++) {
            predators.push_back(new PredatorFish());
        }
    }

    void addPreyFish(int count) {
        for (int i = 0; i < count; i++) {
            prey.push_back(new PreyFish());
        }
    }

    void update() {
        interact();
        steps++;
    }

    void interact() {
        int preyCount = 0;
        // Хищники съедают рыб
        for (PredatorFish* predator : predators) {
            if (!prey.empty()) {
                delete prey.back();
                prey.pop_back();
                //deadFishCount++;
            }
            // как только число рыб равняется нулю хищник умирает от голода и умирает
            else {
                deadPredator++;
                if (!predators.empty()) {
                    predators.pop_back(); // Уменьшаем число хищников на одну
                }
            }
        }

        // Рыбы съедают водоросли
        if (!prey.empty() && algae->getQuantity() > 0) {
            algae->setQuantity(algae->getQuantity() - 1);
            deadAlgaeCount++;
        }
        else {
            if (algae->getQuantity() == 0) {
                // Уменьшаем число рыб до нуля, если нет водорослей
                while (!prey.empty()) {
                    prey.pop_back(); // Уменьшаем число рыб на одну
                    deadFishCount++;
                }
            }
            else {
                if (prey.size() > preyCount - deadFishCount) {
                    // Убедимся, что не увеличиваем число мертвых рыб больше, чем число рыб пользователя
                    deadFishCount++;
                    if (!prey.empty()) {
                        prey.pop_back(); // Уменьшаем число рыб на одну
                    }
                }
            }
        }
    }

    void displayStatus() {
        cout << "Количество хищников: " << predators.size() << endl;
        cout << "Количество обычных рыб: " << prey.size() << endl;
        cout << "Количество водорослей: " << algae->getQuantity() << endl;
        cout << "Количество мертвых рыб: " << deadFishCount << endl;
        cout << "Количество мертвых водорослей: " << deadAlgaeCount << endl;
        cout << "Количество мертвых хищников: " << deadPredator << endl;
        cout << "Шаги: " << steps << endl;
    }

    void addAlgae(int count) {
        if (count > 0) {
            algae = new Algae(algae->getQuantity() + count);
        }
    }

    ~Aquarium() {
        for (PredatorFish* predator : predators) {
            delete predator;
        }

        for (PreyFish* fish : prey) {
            delete fish;
        }

        delete algae;
    }
};

string* algae = nullptr;

void addAlgae(int count) {
    if (count > 0) {
        if (algae == nullptr) {
            algae = new string("Добавление водорослей");
        }
        *algae += to_string(count);
    }
}

int main() {
    Aquarium aquarium;
    int choice;

    setlocale(LC_ALL, "Russian");
    do {
        cout << "1. Добавить хищников \n2. Добавить обычных рыб \n3. Добавить водоросли\n4. Показать информацию в аквариуме\n9. Выход" << endl;

        if (!(cin >> choice)) {
            cout << "Недопустимый ввод. Пожалуйста, введите число." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), 'n');
            continue;
        }

        switch (choice) {
        case 1:
            int predatorCount;
            cout << "Сколько хищников добавить?";
            if (!(cin >> predatorCount)) {
                cout << "Недопустимый ввод. Пожалуйста, введите число." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), 'n');
                break;
            }
            aquarium.addPredatorFish(predatorCount);
            break;
        case 2:
            int preyCount;
            cout << "Сколько обычных рыб добавить?";
            if (!(cin >> preyCount)) {
                cout << "Недопустимый ввод. Пожалуйста, введите число." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), 'n');
                break;
            }
            aquarium.addPreyFish(preyCount);
            break;
        case 3:
            int algaeCount;
            cout << "Сколько водорослей добавить?";
            if (!(cin >> algaeCount)) {
                cout << "Недопустимый ввод. Пожалуйста, введите число." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), 'n');
                break;
            }
            aquarium.addAlgae(algaeCount);
            break;
        case 4:
            aquarium.displayStatus();
            break;
        case 9:
            break;
        default:
            cout << "Недопустимый выбор. Выберите допустимую опцию" << endl;
            break;
        }

        aquarium.update();

    } while (choice != 9);


    return 0;
}