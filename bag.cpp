#include "bag.h"

// Item 构造函数实现
Item::Item(std::string n, ItemCategory c, int p, int hp, int mp, std::string d)
    :name(n), category(c), slot(SLOT_NONE), price(p), hp_effect(hp), mp_effect(mp),
    add_hp(0), add_mp(0), add_atk(0), add_def(0), bag_capacity(0), desc(d)
{
}

Item::Item(std::string n, EquipSlot s, int p, int ahp, int amp, int aatk, int adef, std::string d)
    :name(n), category(CAT_EQUIP), slot(s), price(p), hp_effect(0), mp_effect(0),
    add_hp(ahp), add_mp(amp), add_atk(aatk), add_def(adef), bag_capacity(0), desc(d)
{
}

Item::Item(std::string n, int cap, int p, std::string d)
    :name(n), category(CAT_EQUIP), slot(SLOT_BAG), price(p), hp_effect(0), mp_effect(0),
    add_hp(0), add_mp(0), add_atk(0), add_def(0), bag_capacity(cap), desc(d)
{
}

InventorySlot::InventorySlot(Item i, int c)
    :item(i), count(c)
{
}

//Backpack实现
Backpack::Backpack()
{
    equip_slots[SLOT_HELM] = nullptr;
    equip_slots[SLOT_ARMOR] = nullptr;
    equip_slots[SLOT_WEAPON] = nullptr;
    equip_slots[SLOT_SHOES] = nullptr;
    equip_slots[SLOT_BAG] = nullptr;
    equip_slots[SLOT_SOUL] = nullptr;
}

Backpack::~Backpack()
{
    for (auto& p : equip_slots)
    {
        delete p.second;
    }
}

int Backpack::getExtraCapacity()
{
    if (equip_slots.count(SLOT_BAG) && equip_slots[SLOT_BAG] != nullptr)
    {
        return equip_slots[SLOT_BAG]->bag_capacity;
    }
    return 0;
}

int Backpack::findStackableSlot(const Item& newItem)
{
    for (int i = 0; i < (int)inventory.size(); i++)
    {
        if (inventory[i].item.name == newItem.name && inventory[i].count < MAX_STACK)
        {
            return i;
        }
    }
    return -1;
}

bool Backpack::addItem(const Item& newItem)
{
    if (newItem.category == CAT_EQUIP)
    {
        EquipSlot target_slot = newItem.slot;
        if (equip_slots[target_slot] == nullptr)
        {
            equip_slots[target_slot] = new Item(newItem);
            std::cout << "[装备]自动穿戴：" << newItem.name << "\n";
            return true;
        }
        else
        {
            std::cout << "[提示]" << newItem.name << "对应槽已有装备，移入物品栏\n";
        }
    }

    int stackIdx = findStackableSlot(newItem);
    if (stackIdx != -1)
    {
        inventory[stackIdx].count += 1;
        std::cout << "[堆叠]获得 " << newItem.name << "\n";
        return true;
    }

    int total_max = INVENTORY_MAX_SLOT + getExtraCapacity();
    if ((int)inventory.size() >= total_max)
    {
        std::cout << "[系统]物品栏已满，无法获得：" << newItem.name << "\n";
        return false;
    }

    inventory.emplace_back(newItem, 1);
    std::cout << "[获得物品]" << newItem.name << "\n";
    return true;
}

bool Backpack::equipItem(int invIndex)
{
    if (invIndex < 0 || invIndex >= (int)inventory.size())
    {
        std::cout << "[系统]无效格子\n";
        return false;
    }
    InventorySlot& slot = inventory[invIndex];
    if (slot.item.category != CAT_EQUIP)
    {
        std::cout << "[系统]该物品不能穿戴\n";
        return false;
    }
    EquipSlot es = slot.item.slot;

    if (equip_slots[es] != nullptr)
    {
        inventory.emplace_back(*equip_slots[es], 1);
        delete equip_slots[es];
    }

    equip_slots[es] = new Item(slot.item);
    slot.count--;
    if (slot.count <= 0)
    {
        inventory.erase(inventory.begin() + invIndex);
    }
    std::cout << "[穿戴成功] " << equip_slots[es]->name << "\n";
    return true;
}

bool Backpack::unEquip(EquipSlot slotId)
{
    if (!equip_slots.count(slotId) || equip_slots[slotId] == nullptr)
    {
        std::cout << "[系统]该槽位没有装备\n";
        return false;
    }
    int total_max = INVENTORY_MAX_SLOT + getExtraCapacity();
    if ((int)inventory.size() >= total_max)
    {
        std::cout << "[系统]物品栏满，无法卸下装备！\n";
        return false;
    }
    inventory.emplace_back(*equip_slots[slotId], 1);
    delete equip_slots[slotId];
    equip_slots[slotId] = nullptr;
    std::cout << "[卸下装备完成]\n";
    return true;
}

bool Backpack::useItem(int invIndex, int& hp, int& mp, int& atk, int& def)
{
    if (invIndex < 0 || invIndex >= (int)inventory.size())
    {
        std::cout << "[系统]格子不存在\n";
        return false;
    }
    InventorySlot& slot = inventory[invIndex];
    Item& it = slot.item;

    if (it.category == CAT_CONSUME)
    {
        hp += it.hp_effect;
        mp += it.mp_effect;
        std::cout << "[使用]" << it.name << " " << it.desc << "\n";
        slot.count -= 1;
        if (slot.count <= 0)
        {
            inventory.erase(inventory.begin() + invIndex);
        }
        return true;
    }
    else if (it.category == CAT_TAROT)
    {
        std::cout << "[塔罗发动]" << it.desc << "\n";
        slot.count -= 1;
        if (slot.count <= 0)
        {
            inventory.erase(inventory.begin() + invIndex);
        }
        return true;
    }
    std::cout << "[系统]该物品无法直接使用，请穿戴\n";
    return false;
}

void Backpack::getEquipBonus(int& bonusHp, int& bonusMp, int& bonusAtk, int& bonusDef)
{
    bonusHp = bonusMp = bonusAtk = bonusDef = 0;
    for (auto& p : equip_slots)
    {
        if (p.second != nullptr)
        {
            bonusHp += p.second->add_hp;
            bonusMp += p.second->add_mp;
            bonusAtk += p.second->add_atk;
            bonusDef += p.second->add_def;
        }
    }
}

void Backpack::showBackpack()
{
    std::cout << "\n==========【背包】==========\n";
    std::cout << "--------【装备栏】--------\n";
    std::vector<std::pair<std::string, EquipSlot>> slotNames = {
        {"头盔",SLOT_HELM},
        {"护甲",SLOT_ARMOR},
        {"武器",SLOT_WEAPON},
        {"鞋子",SLOT_SHOES},
        {"储物袋",SLOT_BAG},
        {"兽魂",SLOT_SOUL}
    };
    for (auto& sp : slotNames)
    {
        std::cout << std::left << std::setw(8) << sp.first << ":";
        Item* eq = equip_slots[sp.second];
        if (eq == nullptr)
        {
            std::cout << "【空】\n";
        }
        else
        {
            std::cout << eq->name;
            if (sp.second == SLOT_BAG)
            {
                std::cout << " (额外格子+" << eq->bag_capacity << ")";
            }
            if (sp.second == SLOT_SOUL)
            {
                std::cout << " [属性加成 hp+" << eq->add_hp << " atk+" << eq->add_atk << "]";
            }
            std::cout << "\n";
        }
    }

    std::cout << "\n--------【物品栏】共" << inventory.size() << "/"
        << INVENTORY_MAX_SLOT + getExtraCapacity() << "格（单格最多堆叠" << MAX_STACK << "）--------\n";
    for (int i = 0; i < (int)inventory.size(); i++)
    {
        std::cout << "[" << i << "] " << std::left << std::setw(15) << inventory[i].item.name;
        if (inventory[i].count > 1)
        {
            std::cout << "*" << inventory[i].count;
        }
        std::cout << " | " << inventory[i].item.desc << "\n";
    }
}

Item* Backpack::getEquip(EquipSlot s)
{
    return equip_slots[s];
}

InventorySlot* Backpack::getInvSlot(int idx)
{
    if (idx < 0 || idx >= (int)inventory.size()) return nullptr;
    return &inventory[idx];
}

std::vector<InventorySlot>& Backpack::getInventory()
{
    return inventory;
}

std::map<EquipSlot, Item*>& Backpack::getEquipSlots()
{
    return equip_slots;
}
