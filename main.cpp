#include "Game.h"
#include "SaveManager.h"
#include <iostream>

using namespace std;

int main() {
    SaveManager saveManager("game_save.txt");

    while (true) {
        // 메인 메뉴 출력
        cout << "=== 메인 메뉴 ===\n";
        cout << "1. 게임 시작\n";
        cout << "2. 세이브 파일 불러오기\n";
        cout << "3. 종료\n";
        cout << "선택: ";

        int menuChoice;
        cin >> menuChoice;

        if (menuChoice == 1) {
            // 게임 시작
            int difficulty;
            cout << "난이도를 선택하세요: (1) 쉬움 (2) 보통 (3) 어려움\n";
            cin >> difficulty;

            Game game(difficulty);

            // 게임 루프
            while (!game.isGoalAchieved() && !game.isHpMinus()) {
                game.showStatus();
                int choice;
                cout << "무엇을 하시겠습니까? (1) 노가다 (2) 은행 (3) 도박 (4) 상점 (5) 인벤토리 (6) 잠자기\n";
                cin >> choice;

                if (game.isNight() && choice != 6) {
                    cout << "(6) 잠자기만 가능합니다.\n";
                    continue;
                }

                switch (choice) {
                case 1:
                    game.work();
                    break;
                case 2:
                    if (game.isClosed(1)) {
                        cout << "현재 은행은 문이 닫혀 있습니다.\n";
                        continue;
                    }
                    game.visitBank();
                    break;
                case 3:
                    game.playGamble();
                    break;
                case 4:
                    if (game.isClosed(2)) {
                        cout << "현재 상점은 문이 닫혀 있습니다.\n";
                        continue;
                    }
                    game.visitShop();
                    break;
                case 5:
                    game.showInventory();
                    break;
                case 6:
                    game.sleep();
                    saveManager.saveGame(game); // 잠자기 실행 후 데이터 저장
                    break;
                default:
                    cout << "잘못된 선택입니다.\n";
                    cin.clear();
                    cin.ignore(10, '\n');
                    break;
                }
                system("cls");
            }

            // 게임 결과 출력
            if (!game.isHpMinus()) {
                cout << "축하합니다! 목표 자금을 달성했습니다.\n";
            }
            else {
                cout << "게임 오버! 건강을 잃었습니다.\n";
            }

        }
        else if (menuChoice == 2) {
            // 세이브 파일 불러오기
            Game game(1); // 기본 객체 생성
            if (saveManager.loadGame(game)) {
                cout << "저장된 데이터를 불러왔습니다.\n";
                // 게임 루프 진행
                while (!game.isGoalAchieved() && !game.isHpMinus()) {
                    game.showStatus();
                    int choice;
                    cout << "무엇을 하시겠습니까? (1) 노가다 (2) 은행 (3) 도박 (4) 상점 (5) 인벤토리 (6) 잠자기\n";
                    cin >> choice;

                    if (game.isNight() && choice != 6) {
                        cout << "(6) 잠자기만 가능합니다.\n";
                        continue;
                    }

                    switch (choice) {
                    case 1:
                        game.work();
                        break;
                    case 2:
                        if (game.isClosed(1)) {
                            cout << "현재 은행은 문이 닫혀 있습니다.\n";
                            continue;
                        }
                        game.visitBank();
                        break;
                    case 3:
                        game.playGamble();
                        break;
                    case 4:
                        if (game.isClosed(2)) {
                            cout << "현재 상점은 문이 닫혀 있습니다.\n";
                            continue;
                        }
                        game.visitShop();
                        break;
                    case 5:
                        game.showInventory();
                        break;
                    case 6:
                        game.sleep();
                        saveManager.saveGame(game); // 잠자기 실행 후 데이터 저장
                        break;
                    default:
                        cout << "잘못된 선택입니다.\n";
                        cin.clear();
                        cin.ignore(10, '\n');
                        break;
                    }
                    system("cls");
                }

                // 게임 결과 출력
                if (!game.isHpMinus()) {
                    cout << "축하합니다! 목표 자금을 달성했습니다.\n";
                }
                else {
                    cout << "게임 오버! 건강을 잃었습니다.\n";
                }
            }
            else {
                cout << "저장된 데이터가 없습니다. 새로운 게임을 시작하세요.\n";
            }

        }
        else if (menuChoice == 3) {
            // 프로그램 종료
            cout << "프로그램을 종료합니다. 감사합니다.\n";
            break;
        }
        else {
            cout << "잘못된 선택입니다. 다시 시도하세요.\n";
            cin.clear();
            cin.ignore(10, '\n');
        }
    }

    return 0;
}
