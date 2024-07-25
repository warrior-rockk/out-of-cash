#ifndef H_INVENTORY
#define H_INVENTORY

#define INV_COLOR_OFFSET        20
#define MAX_INV_OBJECTS         16
#define INV_OBJECTS_PER_PAGE    8
#define INV_OBJECTS_PER_ROW     4

#define INV_REGION_W            155
#define INV_REGION_H            55
#define INV_POS_X               134
#define INV_POS_Y               20
#define INV_ICON_X_OFFSET       38
#define INV_ICON_Y_OFFSET       27
#define INV_ICON_MARGIN         1

#define INV_SCROLL_UP_CODE      18
#define INV_SCROLL_DOWN_CODE    19

//data structures
struct inventory
{
    uint8_t numObjects;
    uint8_t objIndex[MAX_INV_OBJECTS];
    uint8_t page;
    BITMAP *image;
    bool refresh;
} inventory;

//funtion definitions
void inventory_init();
void inventory_update();
void inventory_draw();
uint8_t get_inv_obj_position(uint8_t colorCode);
void get_inv_obj_name(uint8_t objIndex, char *s);

#endif //H_INVENTORY
