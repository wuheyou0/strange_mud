#include "ItemFactory.h"
Item ItemFactory::make(const std::string &id){ return Item{id, "Item"}; }
