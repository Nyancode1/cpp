#include "Shop.h"
#include <iostream>
using namespace std;

void Shop::shopMenu(int& money, int& food, vector<string>& inventory) {
    int choice;
    cout << "상점 메뉴:\n";
    cout << "1. 식량 (5만원)\n";
    cout << "2. 구급상자 (10만원)\n";
    cout << "3. 감기약 (5만원)\n";
    cout << "4. 도구 (30만원)\n";
    cout << "5. 상점 나가기\n";
    cin >> choice;

    switch (choice) {
    case 1:
        if (money >= 5) {
            money -= 5;
            food += 2;
            cout << "식량을 구매했습니다. 현재 식량: " << food << ", 남은 자금: " << money << "\n";
        }
        else {
            cout << "돈이 부족합니다.\n";
        }
        break;
    case 2:
        if (money >= 10) {
            money -= 10;
            inventory.push_back("구급상자");
            cout << "구급상자를 구매했습니다.\n";
        }
        else {
            cout << "돈이 부족합니다.\n";
        }
        break;
    case 3:
        if (money >= 10) {
            money -= 10;
            inventory.push_back("감기약");
            cout << "감기약을 구매했습니다.\n";
        }
        else {
            cout << "돈이 부족합니다.\n";
        }
        break;
    case 4:
        if (money >= 30) {
            money -= 30;
            inventory.push_back("도구");
            cout << "도구를 구매했습니다.\n";
        }
        else {
            cout << "돈이 부족합니다.\n";
        }
        break;
    case 5:
        system("cls");
        cout << "상점을 나갑니다.\n";
        break;
    default:
        cout << "잘못된 선택입니다.\n";
        cin.clear();
        cin.ignore(10, '\n');
    }
}
