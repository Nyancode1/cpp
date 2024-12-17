#include "Game.h"
#include <cstdlib>
#include <ctime>

//���� �ʱⰪ ����
Game::Game(int difficulty) : health(100), hour(8), maxHealth(100), isSick(false), sickDaysRemaining(0), savings(0), selectEvent(false){
    srand(time(0)); // ���� �õ� ����
    if (difficulty == 1) {
        money = 150;
        goalMoney = 1500;
        food = 10;
        workMoney = 5;
        debt = 100;         // ����: �� ����
        debtRate = 0.02;  // �� ������ 2%
        savingsRate = 0.1; // ���� ������ 10%
        sicknessChance = 30;
    } else if (difficulty == 2) {
        money = 100;
        goalMoney = 4000;
        food = 5;
        workMoney = 7;
        debt = 1500;       // ����: �ʱ� �� 100
        debtRate = 0.05;  // �� ������ 5%
        savingsRate = 0.01; // ���� ������ 2%
        sicknessChance = 35;
    } else {
        money = 50;
        goalMoney = 7000;
        food = 2;
        workMoney = 10;
        debt = 3000;       // �����: �ʱ� �� 300
        debtRate = 0.05;   // �� ������ 5%
        savingsRate = 0.03; // ���� ������ 3%
        sicknessChance = 45;
    }
    setupEvents();
}

// ���� ���� ���
void Game::showStatus() {
    cout << "���� �ڱ�: " << money << "����\n";
    cout << "��ǥ �ڱ�: " << goalMoney << "����\n";
    cout << "���� �ķ�: " << food << "��ġ\n";
    cout << "���� �ǰ�: " << health << "/" << maxHealth << "\n";
    cout << "���� �ð�: " << hour << ":00\n";
    cout << "����: " << savings << "���� (���� ������: " << savingsRate * 100 << "%)\n";
    cout << "��: " << debt << "���� (�� ������: " << debtRate * 100 << "%)\n";
    if (isSick) {
        cout << "���� ����: ���� (���� �ϼ�: " << sickDaysRemaining << ")\n";
    } else {
        cout << "���� ����: �ǰ�\n";
    }
}




//�밡�� �Լ�
void Game::work() {
    if (health < 20) {
        cout << "ü���� �����Ͽ� ���� �� �� �����ϴ�.\n";
        return;
    }
    if (food < 1) {
        cout << "�ķ��� �����Ͽ� ���� �� �� �����ϴ�.\n";
        return;
    }
    food -= 1;
    if (rand() % 100 < 50) {
        workMoney += rand() % 5;
    }
    else {
        workMoney -= rand() % 5;
    }
    money += 30 + workMoney;
    hour += 4;
    health -= (isSick ? 25 : 20); // ���� ������ �� �߰� ü�� ����
    cout << "�밡�ٸ� �Ϸ��߽��ϴ�! "<< 30 + workMoney <<" ������ �������ϴ�.\n";

    handleEvent();
    checkSickness();
}
//���� �Լ�
void Game::playGamble() {
    gamble.play(money, health);
    hour += 1;

    handleEvent();
    checkSickness();
}
//���� �Լ�
void Game::visitShop() {
    shop.shopMenu(money, food, inventory);
    hour += 1;

    handleEvent();
    checkSickness();
}
//�κ��丮 �Լ�
void Game::showInventory() {
    inventoryManager.manageInventory(inventory, health, food, sickDaysRemaining);
}
//���� �ý���
void Game::visitBank() {
    int choice;
    cout << "\n[���� �ý���]\n";
    cout << "1. ���� �Ա�\n";
    cout << "2. ���� ���\n";
    cout << "3. �� ��ȯ\n";
    cout << "4. ���� ������\n";
    cin >> choice;

    switch (choice) {
    case 1: {
        int deposit;
        cout << "�Ա��� �ݾ��� �Է��ϼ���: ";
        cin >> deposit;
        if (deposit > money) {
            cout << "���� �ڱ��� �����մϴ�.\n";
        } else {
            money -= deposit;
            savings += deposit;
            cout << deposit << "������ �����߽��ϴ�. ���� ����: " << savings << "����.\n";
        }
        break;
    }
    case 2: {
        int withdraw;
        cout << "����� �ݾ��� �Է��ϼ���: ";
        cin >> withdraw;
        if (withdraw > savings) {
            cout << "���� �ݾ��� �����մϴ�.\n";
        } else {
            savings -= withdraw;
            money += withdraw;
            cout << withdraw << "������ ����߽��ϴ�. ���� ����: " << savings << "����.\n";
        }
        break;
    }
    case 3: {
        int repayment;
        cout << "��ȯ�� �ݾ��� �Է��ϼ���: ";
        cin >> repayment;
        if (repayment > money) {
            cout << "���� �ڱ��� �����մϴ�.\n";
        } else {
            money -= repayment;
            debt -= repayment;
            if (debt < 0) debt = 0; // ���� ������ �������� �ʵ���
            cout << repayment << "������ ��ȯ�߽��ϴ�. ���� ��: " << debt << "����.\n";
        }
        break;
    }
    case 4:
        system("cls");
        cout << "������ �����ϴ�.\n";
        break;
    default:
        cout << "�߸��� �����Դϴ�.\n";
        cin.clear();
        cin.ignore(10, '\n');
    }
}
//���� ���� ����
void Game::applyInterest() {
    if (debt > 0) {
        debt += static_cast<int>(debt * debtRate); // �� ���� ����
        cout << "[����] ���� " << static_cast<int>(debt * debtRate) << "������ŭ �����߽��ϴ�. ���� ��: " << debt << "����.\n";
    }
    if (savings > 0) {
        savings += static_cast<int>(savings * savingsRate); // ���� ���� ����
        cout << "[����] ������ " << static_cast<int>(savings * savingsRate) << "������ŭ �����߽��ϴ�. ���� ����: " << savings << "����.\n";
    }
}


//�̺�Ʈ ����
void Game::setupEvents() {
    // ���� �̺�Ʈ
    events.push_back([this]() {
        if (rand() % 100 < sicknessChance) { // ���̵��� ���� Ȯ��
            isSick = true;
            sickDaysRemaining = 3; // 3�� ���� ����
            maxHealth -= 20; // �ִ� ü�� ����
            cout << "\n[�̺�Ʈ: ���� �߻�!]\n";
            cout << "����� ���� �ɷȽ��ϴ�. 3�� ���� �ൿ �� ü���� �� �����մϴ�.\n";
        }
    });

    //������ ���� �G ���� �̺�Ʈ
    events.push_back([this]() {
        debtGrowthRate = ((int)(rand() % 2 + 1)) / 100.0;
        if (rand() % 100 < 50) { // Ȯ��
            debtRate += debtGrowthRate;
            cout << "\n[�̺�Ʈ: �� ������ ����!]\n";
            cout << "������ �� �������� " << (int)(debtGrowthRate*100) <<"% �ö����ϴ�.\n";
        }
        else {
            if (debtRate - debtGrowthRate <= 0) {
                debtGrowthRate = 0.00;
                debtRate = 0.01;
            }
            debtRate -= debtGrowthRate;
            cout << "\n[�̺�Ʈ: �� ������ ����!]\n";
            cout << "������ �� �������� " << (int)(debtRate*100) << "%�� �����߽��ϴ�.\n";
        }
        });

    // ���� �̺�Ʈ�� �߰��� �� ����...
    // �̺�Ʈ 1: ������ ���� ��û
    events.push_back([this]() {
        cout << "\n[�̺�Ʈ: �������� ����� ������ ��û�մϴ�]\n";
        cout << "1. ������ �ش�. (ü�� -10, �� +20)\n";
        cout << "2. �����Ѵ�.\n";

        bool hasSpecialItem = false;
        for (const string& item : inventory) {
            if (item == "����") {
                hasSpecialItem = true;
                break;
            }
        }

        if (hasSpecialItem) {
            cout << "3. ������ ����� ���´�. (ü�� -5, �� +30)\n";
        }

        int choice;
        while (!selectEvent) {
            cin >> choice;
            switch (choice) {
            case 1:
                health -= 10;
                money += 20;
                cout << "������ �־����ϴ�. ü�� -10, �� +20.\n";
                selectEvent = true;
                break;
            case 2:
                cout << "�����ϰ� �����ƽ��ϴ�.\n";
                selectEvent = true;
                break;
            case 3:
                if (hasSpecialItem) {
                    health -= 5;
                    money += 30;
                    cout << "������ ����Ͽ� ������ �־����ϴ�. ü�� -5, �� +30.\n";
                    selectEvent = true;
                }
                else {
                    cout << "�߸��� �����Դϴ�.\n";
                }
                break;
            default:
                cout << "�߸��� �����Դϴ�.\n";
                break;
            }
        }
    });

    // �̺�Ʈ 2: ���� ���� ���� �߰�
    events.push_back([this]() {
        cout << "\n[�̺�Ʈ: ���� ���� ���� �߰��߽��ϴ�!]\n";
        cout << "1. ���� �ֿ��.\n";
        cout << "2. �ֺ��� ���캻��.\n";

        int choice;
        while (!selectEvent) {
            cin >> choice;
            switch (choice) {
            case 1:
                if (rand() % 100 > sicknessChance) {
                    money += 50;
                    cout << "���� �ֿ����ϴ�. �� +50.\n";
                    selectEvent = true;
                }
                else {
                    debt += 100;
                    cout << "�������� �ɷȽ��ϴ�. ���� +100.\n";
                    selectEvent = true;
                }
                break;
            case 2:
                hour += 1;
                cout << "�ֺ��� ���������, ���ٸ� ���� �������ϴ�. �ð� +1.\n";
                selectEvent = true;
                break;
            default:
                cout << "�߸��� �����Դϴ�.\n";
                break;
            }
        }
        });

    // �̺�Ʈ 3: �ķ� ����
    events.push_back([this]() {
        cout << "\n[�̺�Ʈ: �谡 ���Ŵϴ�]\n";
        cout << "1. �ķ��� �Դ´�. (�ķ� -1, ü�� +10)\n";
        cout << "2. ������� ���´�. (ü�� -10)\n";

        int choice;
        while (!selectEvent) {
            cin >> choice;
            switch (choice) {
            case 1:
                if (food > 0) {
                    food -= 1;
                    health += 10;
                    cout << "�ķ��� �Ծ����ϴ�. �ķ� -1, ü�� +10.\n";
                    selectEvent = true;
                }
                else {
                    cout << "�ķ��� �����մϴ�!\n";
                }
                break;
            case 2:
                health -= 10;
                cout << "������� ���ҽ��ϴ�. ü�� -10.\n";
                selectEvent = true;
                break;
            default:
                cout << "�߸��� �����Դϴ�.\n";
                break;
            }
        }
        });

    // �̺�Ʈ 4: ���� ����
    events.push_back([this]() {
        cout << "\n[�̺�Ʈ: �糪�� ���� �����մϴ�]\n";
        cout << "1. ����ģ��. (ü�� -15)\n";

        bool hasSpecialItem = false;
        for (const string& item : inventory) {
            if (item == "����") {
                hasSpecialItem = true;
                break;
            }
        }

        if (hasSpecialItem) {
            cout << "2. ������ ����� �i�Ƴ���. (ü�� -5, �ķ� +1)\n";
        }

        int choice;
        while (!selectEvent) {
            cin >> choice;
            switch (choice) {
            case 1:
                health -= 15;
                cout << "�����̵� �����ƽ��ϴ�. ü�� -15.\n";
                selectEvent = true;
                break;
            case 2:
                if (hasSpecialItem) {
                    health -= 5;
                    food += 1;
                    cout << "������ ����Ͽ� ���� �i�� �������ϴ�. ü�� -5, �ķ� +1.\n";
                    selectEvent = true;
                }
                else {
                    cout << "�߸��� �����Դϴ�.\n";
                }
                break;
            default:
                cout << "�߸��� �����Դϴ�.\n";
                break;
            }
        }
        });
}
//�̺�Ʈ Ȯ�� �� ����
void Game::handleEvent() {
    if (rand() % 100 < 30) { // 30% Ȯ���� �̺�Ʈ �߻�
        selectEvent = false;
        int eventIndex = rand() % events.size(); // ������ �̺�Ʈ ����
        events[eventIndex](); // ���õ� �̺�Ʈ ����
        checkSickness();
    }
}
// ��������
void Game::checkSickness() {
    if (isSick) {
        if (health > maxHealth) {
            health = maxHealth; // ���� ü���� �ִ� ü�� ���Ϸ� ����
        }
        health -= 5;
    }
}


//���� ��
bool Game::isNight() {
    return hour >= 23;
}
//����, ����, ���ݱ�
bool Game::isClosed(int a) {
    if (a == 1) {
        return hour >= 16;
    }
    if (a == 2) {
        return hour >= 21;
    }
}


//���� ���� ���� (1)
bool Game::isGoalAchieved() {
    return money >= goalMoney;
}
//���� ���� ���� (2)
bool Game::isHpMinus(){
    return health <= 0;
}


void Game::sleep() {
    if (hour >= 12) {
        int sleepHours = 24 - hour;
        hour = 8; // ���� �� ��ħ 8�÷� �ʱ�ȭ

        if (food > 0) {
            food -= 1; // �ķ� 1 �Ҹ�
            health += sleepHours * 5; // ü�� ȸ��
            if (health > maxHealth) health = maxHealth; // ü���� ���� �ִ� ü�±����� ȸ��
            cout << "���� �ڰ� �Ͼ���ϴ�. ü���� ȸ���ǰ� �ķ��� �Ҹ��߽��ϴ�.\n";
        } else {
            health -= 10; // �ķ��� ������ ü�� ����
            if (health < 0) health = 0; // ü���� ������ ���� �ʵ���
            cout << "�ķ��� �����Ͽ� �ǰ��� ���������ϴ�. ü�� -10.\n";
        }

        applyInterest(); // ���� ��ħ ���� ����

        if (isSick) {
            sickDaysRemaining -= 1;
            if (sickDaysRemaining <= 0) {
                isSick = false;
                maxHealth += 20;
                cout << "���� ���ҽ��ϴ�. �ִ� ü���� �����Ǿ����ϴ�.\n";
            }
        }
    } else {
        cout << "���� ���� �� �� �����ϴ�. 12:00 ���Ŀ� �����մϴ�.\n";
    }
}


// ���� ����
void Game::setGameState(int money, int goalMoney, int food, int health, int hour, int maxHealth,
    bool isSick, int sickDaysRemaining, int debt, int savings,
    double debtRate, double savingsRate) {
    this->money = money;
    this->goalMoney = goalMoney;
    this->food = food;
    this->health = health;
    this->hour = hour;
    this->maxHealth = maxHealth;
    this->isSick = isSick;
    this->sickDaysRemaining = sickDaysRemaining;
    this->debt = debt;
    this->savings = savings;
    this->debtRate = debtRate;
    this->savingsRate = savingsRate;
}

// ���� ����
int Game::getMoney() const { return money; }
int Game::getGoalMoney() const { return goalMoney; }
int Game::getFood() const { return food; }
int Game::getHealth() const { return health; }
int Game::getHour() const { return hour; }
int Game::getMaxHealth() const { return maxHealth; }
bool Game::getisSick() const { return isSick; }
int Game::getSickDaysRemaining() const { return sickDaysRemaining; }
int Game::getDebt() const { return debt; }
int Game::getSavings() const { return savings; }
double Game::getDebtRate() const { return debtRate; }
double Game::getSavingsRate() const { return savingsRate; }