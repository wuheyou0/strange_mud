#pragma once
#include "Item.h"
#include <memory>
class ItemFactory { public: static Item make(const std::string &id); };
