#ifndef BAG_H
#define BAG_H

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <iomanip>
#include <random>

//物品大类
enum ItemCategory
{
    CAT_CONSUME,    //消耗品
    CAT_EQUIP,      //装备
    CAT_TAROT,      //塔罗牌
    CAT_MISC
};

//装备子类型
enum EquipSlot
{
    SLOT_HELM,      //头盔
    SLOT_ARMOR,     //护甲
    SLOT_WEAPON,    //武器
    SLOT_SHOES,     //鞋子
    SLOT_BAG,       //储物袋
    SLOT_SOUL,      //兽魂
    SLOT_NONE       //不是装备
};

//物品数据结构
struct Item
{
    std::string name;
    ItemCategory category;
    EquipSlot slot;
    int price;
    int hp_effect;
    int mp_effect;

    int add_hp;
    int add_mp;
    int add_atk;
    int add_def;

    int bag_capacity;
    std::string desc;

    Item(std::string n, ItemCategory c, int p, int hp, int mp, std::string d);
    Item(std::string n, EquipSlot s, int p, int ahp, int amp, int aatk, int adef, std::string d);
    Item(std::string n, int cap, int p, std::string d);
};

//物品栏格子
struct InventorySlot
{
    Item item;
    int count;
    InventorySlot(Item i, int c);
};

//背包类
class Backpack
{
private:
    std::map<EquipSlot, Item*> equip_slots;
    const int INVENTORY_MAX_SLOT = 10;
    const int MAX_STACK = 10;
    std::vector<InventorySlot> inventory;

    int getExtraCapacity();
    int findStackableSlot(const Item& newItem);

public:
    Backpack();
    ~Backpack();

    bool addItem(const Item& newItem);
    bool equipItem(int invIndex);
    bool unEquip(EquipSlot slotId);
    bool useItem(int invIndex, int& hp, int& mp, int& atk, int& def);
    void getEquipBonus(int& bonusHp, int& bonusMp, int& bonusAtk, int& bonusDef);
    void showBackpack();

    Item* getEquip(EquipSlot s);
    InventorySlot* getInvSlot(int idx);
    std::vector<InventorySlot>& getInventory();
    std::map<EquipSlot, Item*>& getEquipSlots();
};

#endif

