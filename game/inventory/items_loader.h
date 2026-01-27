#include <vector>
#include <iostream>
#include <array>
#include <map>
#include <cstdint>
#include <unordered_map>
#include "../common/types.h"
#include "../config.h"

#ifndef ITEMS_LOADER_H
#define ITEMS_LOADER_H

using namespace std;

extern map <uint8_t, InventoryItemData> all_items_data;

extern map <string, uint8_t> item_name_to_item_id;

#endif
