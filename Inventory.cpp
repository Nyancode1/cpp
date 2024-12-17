#include "Inventory.h"
#include <iostream>
using namespace std;

void Inventory::manageInventory(vector<string>& inventory, int& health, int& food, int& sickDaysRemaining) {
    if (inventory.empty()) {
        cout << "�κ��丮�� ��� �ֽ��ϴ�.\n";
        return;
    }

    cout << "�κ��丮:\n";
    for (size_t i = 0; i < inventory.size(); i++) {
        cout << i + 1 << ". " << inventory[i] << "\n";
    }

    int choice;
    cout << "����� �������� ��ȣ�� �Է��ϼ��� (0�� ���): ";
    cin >> choice;

    if (choice == 0) {
        cout << "����Ͽ����ϴ�.\n";
        return;
    }

    if (choice > 0 && choice <= inventory.size()) {
        string item = inventory[choice - 1];
        if (item == "���޻���") {
            health += 20;
            if (health > 100) health = 100;
            cout << "���޻��ڸ� ����Ͽ� ü���� ȸ���߽��ϴ�. ���� ü��: " << health << "\n";
        }
        else if (item == "�����") {
            if ((rand() % 100 < 45)&& (sickDaysRemaining > 0)) {
                sickDaysRemaining--;
                cout << "������� ����Ͽ� ������ ���������ϴ�.  ���� �ϼ�: " << sickDaysRemaining << "\n";
            }
            else {
                cout << "�ƹ��� ȿ���� ���� ���Ͽ����ϴ�."<< "\n";
            }
        }
        else if (item == "����") {
            health += 20;
            if (health > 100) health = 100;
            food += 5;
            cout << "������ ����Ͽ� ü���� ȸ���ϰ�, �ķ��� ������ϴ�. ���� �ķ�: " << food << "\n";
        }
        inventory.erase(inventory.begin() + choice - 1);
    }
    else {
        cout << "�߸��� �����Դϴ�.\n";
        cin.clear();
        cin.ignore(10, '\n');
    }
}
