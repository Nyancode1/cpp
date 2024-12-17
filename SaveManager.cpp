#include "SaveManager.h"
#include <fstream>
#include <iostream>

SaveManager::SaveManager(const std::string& fileName) : saveFileName(fileName) {}

// 게임 데이터를 저장
void SaveManager::saveGame(const Game& game) {
    std::ofstream saveFile(saveFileName);
    if (!saveFile.is_open()) {
        std::cerr << "게임 데이터를 저장할 수 없습니다.\n";
        return;
    }

    // Game 객체의 상태를 파일에 저장
    saveFile << game.getMoney() << " " << game.getGoalMoney() << " " << game.getFood() << " "
        << game.getHealth() << " " << game.getHour() << " " << game.getMaxHealth() << " "
        << game.getisSick() << " " << game.getSickDaysRemaining() << " "
        << game.getDebt() << " " << game.getSavings() << " "
        << game.getDebtRate() << " " << game.getSavingsRate();

    saveFile.close();
    std::cout << "게임 데이터가 저장되었습니다.\n";
}

// 게임 데이터를 불러오기
bool SaveManager::loadGame(Game& game) {
    std::ifstream saveFile(saveFileName);
    if (!saveFile.is_open()) {
        std::cerr << "저장된 파일을 찾을 수 없습니다.\n";
        return false;
    }

    int money, goalMoney, food, health, hour, maxHealth, isSickInt, sickDaysRemaining, debt, savings;
    double debtRate, savingsRate;

    // 저장된 데이터를 읽어서 Game 객체로 복원
    saveFile >> money >> goalMoney >> food >> health >> hour >> maxHealth >> isSickInt
        >> sickDaysRemaining >> debt >> savings >> debtRate >> savingsRate;

    bool isSick = static_cast<bool>(isSickInt); // 정수값을 bool로 변환
    game.setGameState(money, goalMoney, food, health, hour, maxHealth, isSick,
        sickDaysRemaining, debt, savings, debtRate, savingsRate);

    saveFile.close();
    std::cout << "게임 데이터를 불러왔습니다.\n";
    return true;
}
