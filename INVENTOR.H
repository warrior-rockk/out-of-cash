#ifndef H_INVENTORY
#define H_INVENTORY

#define INV_COLOR_OFFSET        20
#define MAX_INV_OBJECTS         16
#define INV_OBJECTS_PER_PAGE    8

//data structures
struct inventory
{
    uint8_t numObjects;
    uint8_t objIndex[MAX_INV_OBJECTS];
    uint8_t page;
    bool refresh;
} inventory;

//funtion definitions
void inventory_init();
void inventory_update();
uint8_t get_inv_obj_position(uint8_t colorCode);
void get_inv_obj_name(uint8_t objIndex, char *s);

#endif //H_INVENTORY
