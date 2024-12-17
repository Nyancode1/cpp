#include "Game.h"
#include "SaveManager.h"
#include <iostream>

using namespace std;

int main() {
    SaveManager saveManager("game_save.txt");

    while (true) {
        // ���� �޴� ���
        cout << "=== ���� �޴� ===\n";
        cout << "1. ���� ����\n";
        cout << "2. ���̺� ���� �ҷ�����\n";
        cout << "3. ����\n";
        cout << "����: ";

        int menuChoice;
        cin >> menuChoice;

        if (menuChoice == 1) {
            // ���� ����
            int difficulty;
            cout << "���̵��� �����ϼ���: (1) ���� (2) ���� (3) �����\n";
            cin >> difficulty;

            Game game(difficulty);

            // ���� ����
            while (!game.isGoalAchieved() && !game.isHpMinus()) {
                game.showStatus();
                int choice;
                cout << "������ �Ͻðڽ��ϱ�? (1) �밡�� (2) ���� (3) ���� (4) ���� (5) �κ��丮 (6) ���ڱ�\n";
                cin >> choice;

                if (game.isNight() && choice != 6) {
                    cout << "(6) ���ڱ⸸ �����մϴ�.\n";
                    continue;
                }

                switch (choice) {
                case 1:
                    game.work();
                    break;
                case 2:
                    if (game.isClosed(1)) {
                        cout << "���� ������ ���� ���� �ֽ��ϴ�.\n";
                        continue;
                    }
                    game.visitBank();
                    break;
                case 3:
                    game.playGamble();
                    break;
                case 4:
                    if (game.isClosed(2)) {
                        cout << "���� ������ ���� ���� �ֽ��ϴ�.\n";
                        continue;
                    }
                    game.visitShop();
                    break;
                case 5:
                    game.showInventory();
                    break;
                case 6:
                    game.sleep();
                    saveManager.saveGame(game); // ���ڱ� ���� �� ������ ����
                    break;
                default:
                    cout << "�߸��� �����Դϴ�.\n";
                    cin.clear();
                    cin.ignore(10, '\n');
                    break;
                }
                system("cls");
            }

            // ���� ��� ���
            if (!game.isHpMinus()) {
                cout << "�����մϴ�! ��ǥ �ڱ��� �޼��߽��ϴ�.\n";
            }
            else {
                cout << "���� ����! �ǰ��� �Ҿ����ϴ�.\n";
            }

        }
        else if (menuChoice == 2) {
            // ���̺� ���� �ҷ�����
            Game game(1); // �⺻ ��ü ����
            if (saveManager.loadGame(game)) {
                cout << "����� �����͸� �ҷ��Խ��ϴ�.\n";
                // ���� ���� ����
                while (!game.isGoalAchieved() && !game.isHpMinus()) {
                    game.showStatus();
                    int choice;
                    cout << "������ �Ͻðڽ��ϱ�? (1) �밡�� (2) ���� (3) ���� (4) ���� (5) �κ��丮 (6) ���ڱ�\n";
                    cin >> choice;

                    if (game.isNight() && choice != 6) {
                        cout << "(6) ���ڱ⸸ �����մϴ�.\n";
                        continue;
                    }

                    switch (choice) {
                    case 1:
                        game.work();
                        break;
                    case 2:
                        if (game.isClosed(1)) {
                            cout << "���� ������ ���� ���� �ֽ��ϴ�.\n";
                            continue;
                        }
                        game.visitBank();
                        break;
                    case 3:
                        game.playGamble();
                        break;
                    case 4:
                        if (game.isClosed(2)) {
                            cout << "���� ������ ���� ���� �ֽ��ϴ�.\n";
                            continue;
                        }
                        game.visitShop();
                        break;
                    case 5:
                        game.showInventory();
                        break;
                    case 6:
                        game.sleep();
                        saveManager.saveGame(game); // ���ڱ� ���� �� ������ ����
                        break;
                    default:
                        cout << "�߸��� �����Դϴ�.\n";
                        cin.clear();
                        cin.ignore(10, '\n');
                        break;
                    }
                    system("cls");
                }

                // ���� ��� ���
                if (!game.isHpMinus()) {
                    cout << "�����մϴ�! ��ǥ �ڱ��� �޼��߽��ϴ�.\n";
                }
                else {
                    cout << "���� ����! �ǰ��� �Ҿ����ϴ�.\n";
                }
            }
            else {
                cout << "����� �����Ͱ� �����ϴ�. ���ο� ������ �����ϼ���.\n";
            }

        }
        else if (menuChoice == 3) {
            // ���α׷� ����
            cout << "���α׷��� �����մϴ�. �����մϴ�.\n";
            break;
        }
        else {
            cout << "�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n";
            cin.clear();
            cin.ignore(10, '\n');
        }
    }

    return 0;
}
