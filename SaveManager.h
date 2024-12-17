#pragma once
#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>
#include "Game.h"

class SaveManager {
private:
    std::string saveFileName; // ������ ���� �̸�
public:
    SaveManager(const std::string& fileName);

    // ���� �����͸� �����ϴ� �Լ�
    void saveGame(const Game& game);

    // ���� �����͸� �ҷ����� �Լ�
    bool loadGame(Game& game);
};

#endif // SAVEMANAGER_H
