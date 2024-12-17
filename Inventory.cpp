#include "Inventory.h"
#include <iostream>
using namespace std;

void Inventory::manageInventory(vector<string>& inventory, int& health, int& food, int& sickDaysRemaining) {
    if (inventory.empty()) {
        cout << "인벤토리가 비어 있습니다.\n";
        return;
    }

    cout << "인벤토리:\n";
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << i + 1 << ". " << inventory[i] << "\n";
    }

    int choice;
    cout << "사용할 아이템의 번호를 입력하세요 (0은 취소): ";
    cin >> choice;

    if (choice == 0) {
        cout << "취소하였습니다.\n";
        return;
    }

    if (choice > 0 && choice <= inventory.size()) {
        string item = inventory[choice - 1];
        if (item == "구급상자") {
            health += 20;
            if (health > 100) health = 100;
            cout << "구급상자를 사용하여 체력을 회복했습니다. 현재 체력: " << health << "\n";
        }
        else if (item == "감기약") {
            if ((rand() % 100 < 45)&& (sickDaysRemaining > 0)) {
                sickDaysRemaining--;
                cout << "감기약을 사용하여 증상이 나아졌습니다.  남은 일수: " << sickDaysRemaining << "\n";
            }
            else {
                cout << "아무런 효과도 보지 못하였습니다."<< "\n";
            }
        }
        else if (item == "도구") {
            health += 20;
            if (health > 100) health = 100;
            food += 5;
            cout << "도구를 사용하여 체력을 회복하고, 식량을 얻었습니다. 현재 식량: " << food << "\n";
        }
        inventory.erase(inventory.begin() + choice - 1);
    }
    else {
        cout << "잘못된 선택입니다.\n";
        cin.clear();
        cin.ignore(10, '\n');
    }
}
