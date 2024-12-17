#ifndef SHOP_H
#define SHOP_H

#include <vector>
#include <string>
#include <windows.h>
using namespace std;

class Shop {
public:
    void shopMenu(int& money, int& food, vector<string>& inventory);
};

#endif // SHOP_H
