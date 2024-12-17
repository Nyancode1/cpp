#pragma once
#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>
#include "Game.h"

class SaveManager {
private:
    std::string saveFileName; // 저장할 파일 이름
public:
    SaveManager(const std::string& fileName);

    // 게임 데이터를 저장하는 함수
    void saveGame(const Game& game);

    // 게임 데이터를 불러오는 함수
    bool loadGame(Game& game);
};

#endif // SAVEMANAGER_H
