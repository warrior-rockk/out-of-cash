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

//inventory script structure
struct invScript
{
    bool active;
    bool scriptAssigned;
    int object;
    enum verbs verb;
    int step;
    int lastStep;
    int stepTime;
    int hsX;
    int hsY;
} invScript;

//funtion definitions
void inventory_init();
uint8_t get_inv_obj_position(uint8_t colorCode);
void get_inv_obj_name(uint8_t objIndex, char *s);

#endif //H_INVENTORY
