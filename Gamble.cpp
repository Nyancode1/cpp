#include "Gamble.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void Gamble::play(int& money, int& health) {
    if (money < 1) {
        cout << "���ڿ� �ʿ��� �ڱ��� �����մϴ�.\n";
        return;
    }

    int bet;
    cout << "���ڿ� �� �ݾ��� �Է��ϼ���: ";
    cin >> bet;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10, '\n');
        cout << "�߸��� ���� �Է��Ͽ����ϴ�.\n";
        return;
    }

    if (bet > money) {
        cout << "���� �ڱݺ��� ū �ݾ��� �� �� �����ϴ�.\n";
        return;
    }

    if (rand() % 100 < 30) {
        money += bet;
        cout << "���ڿ� �����߽��ϴ�! " << bet << "������ ������ϴ�.\n";
    }
    else {
        money -= bet;
        cout << "���ڿ� �����߽��ϴ�. " << bet << "������ �Ҿ����ϴ�.\n";
    }
}
