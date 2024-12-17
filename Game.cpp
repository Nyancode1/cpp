#include "Game.h"
#include <cstdlib>
#include <ctime>

//게임 초기값 설정
Game::Game(int difficulty) : health(100), hour(8), maxHealth(100), isSick(false), sickDaysRemaining(0), savings(0), selectEvent(false){
    srand(time(0)); // 랜덤 시드 설정
    if (difficulty == 1) {
        money = 150;
        goalMoney = 1500;
        food = 10;
        workMoney = 5;
        debt = 100;         // 쉬움: 빚 없음
        debtRate = 0.02;  // 빚 이자율 2%
        savingsRate = 0.1; // 저축 이자율 10%
        sicknessChance = 30;
    } else if (difficulty == 2) {
        money = 100;
        goalMoney = 4000;
        food = 5;
        workMoney = 7;
        debt = 1500;       // 보통: 초기 빚 100
        debtRate = 0.05;  // 빚 이자율 5%
        savingsRate = 0.01; // 저축 이자율 2%
        sicknessChance = 35;
    } else {
        money = 50;
        goalMoney = 7000;
        food = 2;
        workMoney = 10;
        debt = 3000;       // 어려움: 초기 빚 300
        debtRate = 0.05;   // 빚 이자율 5%
        savingsRate = 0.03; // 저축 이자율 3%
        sicknessChance = 45;
    }
    setupEvents();
}

// 현재 상태 출력
void Game::showStatus() {
    cout << "현재 자금: " << money << "만원\n";
    cout << "목표 자금: " << goalMoney << "만원\n";
    cout << "보유 식량: " << food << "일치\n";
    cout << "현재 건강: " << health << "/" << maxHealth << "\n";
    cout << "현재 시간: " << hour << ":00\n";
    cout << "저축: " << savings << "만원 (저축 이자율: " << savingsRate * 100 << "%)\n";
    cout << "빚: " << debt << "만원 (빚 이자율: " << debtRate * 100 << "%)\n";
    if (isSick) {
        cout << "현재 상태: 질병 (남은 일수: " << sickDaysRemaining << ")\n";
    } else {
        cout << "현재 상태: 건강\n";
    }
}




//노가다 함수
void Game::work() {
    if (health < 20) {
        cout << "체력이 부족하여 일을 할 수 없습니다.\n";
        return;
    }
    if (food < 1) {
        cout << "식량이 부족하여 일을 할 수 없습니다.\n";
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
    health -= (isSick ? 25 : 20); // 질병 상태일 때 추가 체력 감소
    cout << "노가다를 완료했습니다! "<< 30 + workMoney <<" 만원을 벌었습니다.\n";

    handleEvent();
    checkSickness();
}
//도박 함수
void Game::playGamble() {
    gamble.play(money, health);
    hour += 1;

    handleEvent();
    checkSickness();
}
//상점 함수
void Game::visitShop() {
    shop.shopMenu(money, food, inventory);
    hour += 1;

    handleEvent();
    checkSickness();
}
//인벤토리 함수
void Game::showInventory() {
    inventoryManager.manageInventory(inventory, health, food, sickDaysRemaining);
}
//은행 시스템
void Game::visitBank() {
    int choice;
    cout << "\n[은행 시스템]\n";
    cout << "1. 저축 입금\n";
    cout << "2. 저축 출금\n";
    cout << "3. 빚 상환\n";
    cout << "4. 은행 나가기\n";
    cin >> choice;

    switch (choice) {
    case 1: {
        int deposit;
        cout << "입금할 금액을 입력하세요: ";
        cin >> deposit;
        if (deposit > money) {
            cout << "보유 자금이 부족합니다.\n";
        } else {
            money -= deposit;
            savings += deposit;
            cout << deposit << "만원을 저축했습니다. 현재 저축: " << savings << "만원.\n";
        }
        break;
    }
    case 2: {
        int withdraw;
        cout << "출금할 금액을 입력하세요: ";
        cin >> withdraw;
        if (withdraw > savings) {
            cout << "저축 금액이 부족합니다.\n";
        } else {
            savings -= withdraw;
            money += withdraw;
            cout << withdraw << "만원을 출금했습니다. 현재 저축: " << savings << "만원.\n";
        }
        break;
    }
    case 3: {
        int repayment;
        cout << "상환할 금액을 입력하세요: ";
        cin >> repayment;
        if (repayment > money) {
            cout << "보유 자금이 부족합니다.\n";
        } else {
            money -= repayment;
            debt -= repayment;
            if (debt < 0) debt = 0; // 빚이 음수로 내려가지 않도록
            cout << repayment << "만원을 상환했습니다. 현재 빚: " << debt << "만원.\n";
        }
        break;
    }
    case 4:
        system("cls");
        cout << "은행을 나갑니다.\n";
        break;
    default:
        cout << "잘못된 선택입니다.\n";
        cin.clear();
        cin.ignore(10, '\n');
    }
}
//이자 증가 설정
void Game::applyInterest() {
    if (debt > 0) {
        debt += static_cast<int>(debt * debtRate); // 빚 이자 증가
        cout << "[이자] 빚이 " << static_cast<int>(debt * debtRate) << "만원만큼 증가했습니다. 현재 빚: " << debt << "만원.\n";
    }
    if (savings > 0) {
        savings += static_cast<int>(savings * savingsRate); // 저축 이자 증가
        cout << "[이자] 저축이 " << static_cast<int>(savings * savingsRate) << "만원만큼 증가했습니다. 현재 저축: " << savings << "만원.\n";
    }
}


//이벤트 설정
void Game::setupEvents() {
    // 질병 이벤트
    events.push_back([this]() {
        if (rand() % 100 < sicknessChance) { // 난이도에 따른 확률
            isSick = true;
            sickDaysRemaining = 3; // 3일 동안 지속
            maxHealth -= 20; // 최대 체력 감소
            cout << "\n[이벤트: 질병 발생!]\n";
            cout << "당신은 병에 걸렸습니다. 3일 동안 행동 시 체력이 더 감소합니다.\n";
        }
    });

    //이자율 증가 밎 감소 이벤트
    events.push_back([this]() {
        debtGrowthRate = ((int)(rand() % 2 + 1)) / 100.0;
        if (rand() % 100 < 50) { // 확률
            debtRate += debtGrowthRate;
            cout << "\n[이벤트: 빚 이자율 증가!]\n";
            cout << "은행의 빚 이자율이 " << (int)(debtGrowthRate*100) <<"% 올랐습니다.\n";
        }
        else {
            if (debtRate - debtGrowthRate <= 0) {
                debtGrowthRate = 0.00;
                debtRate = 0.01;
            }
            debtRate -= debtGrowthRate;
            cout << "\n[이벤트: 빚 이자율 감소!]\n";
            cout << "은행의 빚 이자율이 " << (int)(debtRate*100) << "%로 감소했습니다.\n";
        }
        });

    // 기존 이벤트를 추가할 수 있음...
    // 이벤트 1: 간단한 도움 요청
    events.push_back([this]() {
        cout << "\n[이벤트: 지나가던 사람이 도움을 요청합니다]\n";
        cout << "1. 도움을 준다. (체력 -10, 돈 +20)\n";
        cout << "2. 무시한다.\n";

        bool hasSpecialItem = false;
        for (const string& item : inventory) {
            if (item == "도구") {
                hasSpecialItem = true;
                break;
            }
        }

        if (hasSpecialItem) {
            cout << "3. 도구를 사용해 돕는다. (체력 -5, 돈 +30)\n";
        }

        int choice;
        while (!selectEvent) {
            cin >> choice;
            switch (choice) {
            case 1:
                health -= 10;
                money += 20;
                cout << "도움을 주었습니다. 체력 -10, 돈 +20.\n";
                selectEvent = true;
                break;
            case 2:
                cout << "무시하고 지나쳤습니다.\n";
                selectEvent = true;
                break;
            case 3:
                if (hasSpecialItem) {
                    health -= 5;
                    money += 30;
                    cout << "도구를 사용하여 도움을 주었습니다. 체력 -5, 돈 +30.\n";
                    selectEvent = true;
                }
                else {
                    cout << "잘못된 선택입니다.\n";
                }
                break;
            default:
                cout << "잘못된 선택입니다.\n";
                break;
            }
        }
    });

    // 이벤트 2: 길을 가다 돈을 발견
    events.push_back([this]() {
        cout << "\n[이벤트: 길을 가다 돈을 발견했습니다!]\n";
        cout << "1. 돈을 주운다.\n";
        cout << "2. 주변을 살펴본다.\n";

        int choice;
        while (!selectEvent) {
            cin >> choice;
            switch (choice) {
            case 1:
                if (rand() % 100 > sicknessChance) {
                    money += 50;
                    cout << "돈을 주웠습니다. 돈 +50.\n";
                    selectEvent = true;
                }
                else {
                    debt += 100;
                    cout << "경찰에게 걸렸습니다. 벌금 +100.\n";
                    selectEvent = true;
                }
                break;
            case 2:
                hour += 1;
                cout << "주변을 살펴봤지만, 별다른 것은 없었습니다. 시간 +1.\n";
                selectEvent = true;
                break;
            default:
                cout << "잘못된 선택입니다.\n";
                break;
            }
        }
        });

    // 이벤트 3: 식량 부족
    events.push_back([this]() {
        cout << "\n[이벤트: 배가 고픕니다]\n";
        cout << "1. 식량을 먹는다. (식량 -1, 체력 +10)\n";
        cout << "2. 배고픔을 참는다. (체력 -10)\n";

        int choice;
        while (!selectEvent) {
            cin >> choice;
            switch (choice) {
            case 1:
                if (food > 0) {
                    food -= 1;
                    health += 10;
                    cout << "식량을 먹었습니다. 식량 -1, 체력 +10.\n";
                    selectEvent = true;
                }
                else {
                    cout << "식량이 부족합니다!\n";
                }
                break;
            case 2:
                health -= 10;
                cout << "배고픔을 참았습니다. 체력 -10.\n";
                selectEvent = true;
                break;
            default:
                cout << "잘못된 선택입니다.\n";
                break;
            }
        }
        });

    // 이벤트 4: 개와 조우
    events.push_back([this]() {
        cout << "\n[이벤트: 사나운 개와 조우합니다]\n";
        cout << "1. 도망친다. (체력 -15)\n";

        bool hasSpecialItem = false;
        for (const string& item : inventory) {
            if (item == "도구") {
                hasSpecialItem = true;
                break;
            }
        }

        if (hasSpecialItem) {
            cout << "2. 도구를 사용해 쫒아낸다. (체력 -5, 식량 +1)\n";
        }

        int choice;
        while (!selectEvent) {
            cin >> choice;
            switch (choice) {
            case 1:
                health -= 15;
                cout << "다행이도 도망쳤습니다. 체력 -15.\n";
                selectEvent = true;
                break;
            case 2:
                if (hasSpecialItem) {
                    health -= 5;
                    food += 1;
                    cout << "도구를 사용하여 개를 쫒아 내었습니다. 체력 -5, 식량 +1.\n";
                    selectEvent = true;
                }
                else {
                    cout << "잘못된 선택입니다.\n";
                }
                break;
            default:
                cout << "잘못된 선택입니다.\n";
                break;
            }
        }
        });
}
//이벤트 확률 및 실행
void Game::handleEvent() {
    if (rand() % 100 < 30) { // 30% 확률로 이벤트 발생
        selectEvent = false;
        int eventIndex = rand() % events.size(); // 랜덤한 이벤트 선택
        events[eventIndex](); // 선택된 이벤트 실행
        checkSickness();
    }
}
// 질병상태
void Game::checkSickness() {
    if (isSick) {
        if (health > maxHealth) {
            health = maxHealth; // 현재 체력을 최대 체력 이하로 유지
        }
        health -= 5;
    }
}


//밤일 때
bool Game::isNight() {
    return hour >= 23;
}
//가게, 은행, 문닫기
bool Game::isClosed(int a) {
    if (a == 1) {
        return hour >= 16;
    }
    if (a == 2) {
        return hour >= 21;
    }
}


//게임 종료 조건 (1)
bool Game::isGoalAchieved() {
    return money >= goalMoney;
}
//게임 종료 조건 (2)
bool Game::isHpMinus(){
    return health <= 0;
}


void Game::sleep() {
    if (hour >= 12) {
        int sleepHours = 24 - hour;
        hour = 8; // 다음 날 아침 8시로 초기화

        if (food > 0) {
            food -= 1; // 식량 1 소모
            health += sleepHours * 5; // 체력 회복
            if (health > maxHealth) health = maxHealth; // 체력은 현재 최대 체력까지만 회복
            cout << "잠을 자고 일어났습니다. 체력이 회복되고 식량을 소모했습니다.\n";
        } else {
            health -= 10; // 식량이 없으면 체력 감소
            if (health < 0) health = 0; // 체력이 음수가 되지 않도록
            cout << "식량이 부족하여 건강이 나빠졌습니다. 체력 -10.\n";
        }

        applyInterest(); // 매일 아침 이자 적용

        if (isSick) {
            sickDaysRemaining -= 1;
            if (sickDaysRemaining <= 0) {
                isSick = false;
                maxHealth += 20;
                cout << "병이 나았습니다. 최대 체력이 복구되었습니다.\n";
            }
        }
    } else {
        cout << "아직 잠을 잘 수 없습니다. 12:00 이후에 가능합니다.\n";
    }
}


// 상태 세터
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

// 상태 게터
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