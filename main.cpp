#include <iostream>
#include <cmath> // round

using std::cout;
using std::endl;

bool getContinueStatus() {
    std::cout << "Do you want to stop the car and get out? (type N/n or any to contiue)?: ";

    while (true) {
        auto uSelect = getchar();
        if (uSelect == 'n' || uSelect == 'N') {
            return false;
        } else if (uSelect >= 33 && uSelect <= 125) {
            return true;
        }
    }
}

// Возвращает введенную пользователем double с двойной точностью
double getUserDouble() {
    double input;

    cout << "Enter speed increment/decrement: ";
    // Пока не будет введено нормальное число, выполняем цикл
    while (!(std::cin >> input)) {
        cout << "Error. Enter a number: ";
        // Сбрасываем коматозное состояние cin
        std::cin.clear();
        // Очищаем поток ввода
        fflush(stdin);
    }

    return round(input * 100) / 100;
}

int main() {
    enum class speed { MIN = 0, MAX = 150 };
    bool isProcess = true;
    auto currentSpeed = (double) speed::MIN;

    while (isProcess) {
        double uInput = getUserDouble();
        double test = currentSpeed + uInput;

        if (test > (double) speed::MAX) {
            cout << "Speed cannot be greater then " << std::to_string(static_cast<int>(speed::MAX)) << endl;
            continue;
        } else if (test < (double) speed::MIN) {
            cout << "Speed cannot be less than " << std::to_string(static_cast<int>(speed::MIN)) << endl;
            continue;
        } else {
            char result[4];
            currentSpeed = test;
            sprintf(result, "%.2f", currentSpeed);

            cout << "Current speed is " << result << endl;

            isProcess = getContinueStatus();
        }
    }

    cout << "GAME is OVER" << endl;
}
