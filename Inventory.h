#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <string>
using namespace std;

class Inventory {
public:
    void manageInventory(vector<string>& inventory, int& health, int& food, int& sickDaysRemaining);
};

#endif // INVENTORY_H
