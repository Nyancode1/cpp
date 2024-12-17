#include "SaveManager.h"
#include <fstream>
#include <iostream>

SaveManager::SaveManager(const std::string& fileName) : saveFileName(fileName) {}

// ���� �����͸� ����
void SaveManager::saveGame(const Game& game) {
    std::ofstream saveFile(saveFileName);
    if (!saveFile.is_open()) {
        std::cerr << "���� �����͸� ������ �� �����ϴ�.\n";
        return;
    }

    // Game ��ü�� ���¸� ���Ͽ� ����
    saveFile << game.getMoney() << " " << game.getGoalMoney() << " " << game.getFood() << " "
        << game.getHealth() << " " << game.getHour() << " " << game.getMaxHealth() << " "
        << game.getisSick() << " " << game.getSickDaysRemaining() << " "
        << game.getDebt() << " " << game.getSavings() << " "
        << game.getDebtRate() << " " << game.getSavingsRate();

    saveFile.close();
    std::cout << "���� �����Ͱ� ����Ǿ����ϴ�.\n";
}

// ���� �����͸� �ҷ�����
bool SaveManager::loadGame(Game& game) {
    std::ifstream saveFile(saveFileName);
    if (!saveFile.is_open()) {
        std::cerr << "����� ������ ã�� �� �����ϴ�.\n";
        return false;
    }

    int money, goalMoney, food, health, hour, maxHealth, isSickInt, sickDaysRemaining, debt, savings;
    double debtRate, savingsRate;

    // ����� �����͸� �о Game ��ü�� ����
    saveFile >> money >> goalMoney >> food >> health >> hour >> maxHealth >> isSickInt
        >> sickDaysRemaining >> debt >> savings >> debtRate >> savingsRate;

    bool isSick = static_cast<bool>(isSickInt); // �������� bool�� ��ȯ
    game.setGameState(money, goalMoney, food, health, hour, maxHealth, isSick,
        sickDaysRemaining, debt, savings, debtRate, savingsRate);

    saveFile.close();
    std::cout << "���� �����͸� �ҷ��Խ��ϴ�.\n";
    return true;
}
