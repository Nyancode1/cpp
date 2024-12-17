#include "Shop.h"
#include <iostream>
using namespace std;

void Shop::shopMenu(int& money, int& food, vector<string>& inventory) {
    int choice;
    cout << "���� �޴�:\n";
    cout << "1. �ķ� (5����)\n";
    cout << "2. ���޻��� (10����)\n";
    cout << "3. ����� (5����)\n";
    cout << "4. ���� (30����)\n";
    cout << "5. ���� ������\n";
    cin >> choice;

    switch (choice) {
    case 1:
        if (money >= 5) {
            money -= 5;
            food += 2;
            cout << "�ķ��� �����߽��ϴ�. ���� �ķ�: " << food << ", ���� �ڱ�: " << money << "\n";
        }
        else {
            cout << "���� �����մϴ�.\n";
        }
        break;
    case 2:
        if (money >= 10) {
            money -= 10;
            inventory.push_back("���޻���");
            cout << "���޻��ڸ� �����߽��ϴ�.\n";
        }
        else {
            cout << "���� �����մϴ�.\n";
        }
        break;
    case 3:
        if (money >= 10) {
            money -= 10;
            inventory.push_back("�����");
            cout << "������� �����߽��ϴ�.\n";
        }
        else {
            cout << "���� �����մϴ�.\n";
        }
        break;
    case 4:
        if (money >= 30) {
            money -= 30;
            inventory.push_back("����");
            cout << "������ �����߽��ϴ�.\n";
        }
        else {
            cout << "���� �����մϴ�.\n";
        }
        break;
    case 5:
        system("cls");
        cout << "������ �����ϴ�.\n";
        break;
    default:
        cout << "�߸��� �����Դϴ�.\n";
        cin.clear();
        cin.ignore(10, '\n');
    }
}
