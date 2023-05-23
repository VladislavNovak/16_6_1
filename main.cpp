#include <iostream>
#include <algorithm>
#include <cmath> // round

using std::cout;
using std::endl;

enum class SpeedType { MIN = 0, MAX = 150 };

// Получаем true если элемент `item` хоть раз встречается в диапазоне `range`
bool isIncludes(const std::string &range, const char &item) {
    return std::any_of(range.begin(),
                       range.end(),
                       [&item](const char &c) { return c == item; });
}

std::string getJoinRange(const std::string &range) {
    char const TERMINATOR = '.';
    char const JOIN = ',';

    std::string joinRange;
    for (int i = 0; i < range.size(); ++i) {
        joinRange += range[i];
        joinRange += (i != range.size() - 1) ? JOIN : TERMINATOR;
    }

    return joinRange;
}

// 1.1 Получаем char-символ в обозначенном диапазоне `range`
template<typename T>
T getUserChar(std::string const &range) {
    T input;

    while (true) {
        std::cin >> input;
        // Если введено значение из диапазона - сбрасываем
        if (isIncludes(range, input)) break;
        printf("Error. Symbol %c not in range: %s Repeat: ", input, getJoinRange(range).c_str());
        // Сбрасываем коматозное состояние cin
        std::cin.clear();
        // Очищаем поток ввода
        fflush(stdin);
    }

    return input;
}

// Возвращает true при введении Y/y или false при N/n. Другие символы запрещены
bool hasDialogYesNo(const std::string &proposition, bool whatNext = false) {
    std::string next = whatNext ? "continue" : "deny";
    printf("%s Press 'Y/y' to agree or 'N/n' to %s: ", proposition.c_str(), next.c_str());
    return isIncludes("Yy", getUserChar<char>("YyNn"));
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

void showWarning(const double currentSpeed, SpeedType speedType) {
    char buffer[150];
    double diff = (double) speedType - currentSpeed;
    std::string warningType = diff < 0 ? "less" : "greater";
    sprintf(buffer, "Speed cannot be %s then %i, but you can reach it by dialing %2.1f\n", warningType.c_str(), static_cast<int>(speedType), diff);
    cout << buffer;
}

bool checkSpeedForValidity(const double currentSpeed, const double test) {
    bool isValid = true;
    if (test > (double) SpeedType::MAX) {
        showWarning(currentSpeed, SpeedType::MAX);
        isValid = false;
    } else if (test < (double) SpeedType::MIN) {
        showWarning(currentSpeed, SpeedType::MIN);
        isValid = false;
    }

    return isValid;
}

int main() {
    bool isProcessStatus = true;
    auto currentSpeed = (double) SpeedType::MIN;

    while (isProcessStatus) {
        double uInput = getUserDouble();
        double test = currentSpeed + uInput;

        if (!checkSpeedForValidity(currentSpeed, test)) continue;

        char result[4];
        currentSpeed = test;
        sprintf(result, "%.2f", currentSpeed);
        cout << "Current speed is " << result << endl;

        isProcessStatus = hasDialogYesNo("Do you want to continue?", false);
    }

    currentSpeed = (double) SpeedType::MIN;
    cout << "Speed reset to zero: " << currentSpeed << endl;
    cout << "GAME is OVER" << endl;
}
