#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include <functional>
#include <string>
#include "Shop.h"
#include "Gamble.h"
#include "Inventory.h"

using namespace std;

class Game {
private:
    int money;
    int workMoney;
    int goalMoney;
    int food;
    int health;
    int maxHealth;
    int hour;

    bool isSick;
    int sickDaysRemaining;
    int sicknessChance;

    bool selectEvent; // ���ÿϷ�

    int debt;       // ��
    int savings;    // ����
    double debtRate;  // �� ������
    double savingsRate; // ���� ������
    double debtGrowthRate;

    vector<string> inventory;
    Shop shop;
    Gamble gamble;
    Inventory inventoryManager;

    vector<function<void()>> events;

public:
    Game(int difficulty);
    void showStatus();

    void work();
    void playGamble();
    void visitShop();
    void showInventory();
    void sleep();

    void visitBank();  // ���� �ý���
    void applyInterest(); // ���� ����

    void handleEvent();
    void setupEvents();
    void checkSickness();

    bool isNight();
    bool isClosed(int a);
    bool isGoalAchieved();
    bool isHpMinus();

    // ��
    void setGameState(int money, int goalMoney, int food, int health, int hour, int maxHealth,
        bool isSick, int sickDaysRemaining, int debt, int savings,
        double debtRate, double savingsRate);

    // ���� ����
    int getMoney() const;
    int getGoalMoney() const;
    int getFood() const;
    int getHealth() const;
    int getHour() const;
    int getMaxHealth() const;
    bool getisSick() const;
    int getSickDaysRemaining() const;
    int getDebt() const;
    int getSavings() const;
    double getDebtRate() const;
    double getSavingsRate() const;
};

#endif // GAME_H
