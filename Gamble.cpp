#include "Gamble.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void Gamble::play(int& money, int& health) {
    if (money < 1) {
        cout << "도박에 필요한 자금이 부족합니다.\n";
        return;
    }

    int bet;
    cout << "도박에 걸 금액을 입력하세요: ";
    cin >> bet;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "잘못된 값을 입력하였습니다.\n";
        return;
    }

    if (bet > money) {
        cout << "보유 자금보다 큰 금액을 걸 수 없습니다.\n";
        return;
    }

    if (rand() % 100 < 30) {
        money += bet;
        cout << "도박에 성공했습니다! " << bet << "만원을 얻었습니다.\n";
    }
    else {
        money -= bet;
        cout << "도박에 실패했습니다. " << bet << "만원을 잃었습니다.\n";
    }
}
