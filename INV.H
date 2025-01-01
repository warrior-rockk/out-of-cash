#ifndef H_INVENTORY
#define H_INVENTORY

#define INV_COLOR_OFFSET        20
#define MAX_INV_OBJECTS         32
#define MAX_INV_PAGE            ((MAX_INV_OBJECTS - 1) / INV_OBJECTS_PER_ROW) - 1
#define INV_OBJECTS_PER_PAGE    8
#define INV_OBJECTS_PER_ROW     4

#define INV_REGION_W            155
#define INV_REGION_H            55
#define INV_POS_X               134
#define INV_POS_Y               182
#define INV_ICON_X_OFFSET       38
#define INV_ICON_Y_OFFSET       28 //27
#define INV_ICON_MARGIN         1

#define INV_SCROLL_UP_CODE      18
#define INV_SCROLL_DOWN_CODE    19

//custom scripts id (inventory scripts > 1000)
#define BLACK_BRAIN_SCRIPT          1000
#define BLACK_STAR_CLOCK_SCRIPT     1001
#define OPEN_FULL_CARTRIDGE_SCRIPT  1002
#define STAR_SHIRT_SCRIPT           1003
#define OAT_MIXED_SCRIPT            1004
#define SPORT_WORK_SCRIPT           1005
#define APPLY_OAT_SCRIPT            1006

//data structures
struct inventory
{
    uint8_t numObjects;
    uint8_t objIndex[MAX_INV_OBJECTS];
    uint8_t page;
    bool refresh;
} inventory;

//global vars
extern DATAFILE *inventoryDataFile;
static BITMAP *inventoryImage;

//funtion definitions
void inventory_init();
void inventory_add(uint8_t numObject);
void inventory_remove(uint8_t numObject);
void inventory_update();
void inventory_draw();
uint8_t get_inv_obj_position(uint8_t colorCode);
void get_inv_obj_name(uint8_t objIndex, char *s);
uint8_t get_inv_obj_id(uint8_t invPosition);

#endif //H_INVENTORY
