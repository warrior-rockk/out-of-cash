#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include "inventor.h"
#include "inv.h"

//initialization of inventory
void inventory_init()
{
    //test
    inventory.numObjects = 2;
    inventory.objIndex[0] = dInv_Cassette + 1;
    inventory.objIndex[1] = dInv_Guitar + 1;
}

//calculate the inventory position based on colorCode
uint8_t get_inv_obj_position(uint8_t colorCode)
{
    if (colorCode > (INV_COLOR_OFFSET + INV_OBJECTS_PER_PAGE))
        return 0;
    else
        return (uint8_t)((colorCode % INV_COLOR_OFFSET) + (inventory.page * INV_OBJECTS_PER_PAGE) + 1);
}

//get inventory object name
void get_inv_obj_name(uint8_t objIndex, char *s)
{
    //check inventory limit
    if (objIndex > inventory.numObjects || objIndex == 0)
        strcpy(s, "");
    else
    {
        //get inventory object name
        switch (inventory.objIndex[objIndex - 1] - 1)
        {
            case dInv_Cassette:
                strcpy(s, "Casete");
                break;
            case dInv_Guitar:
                strcpy(s, "Guitarra");
                break;
            default:
                strcpy(s, "");
                break;
        }
    }
}

//funcion to update inventory script
void r01_room_update()
{
    //if nothing selected
    if (invScript.active)
    {
        //sequence actions
        switch (invScript.object)
        {
            case dInvCassette:
                switch(invScript.verb)
                {
                    case LOOK:
                        switch (invScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es un casete de Reincidentes");
                                break;
                            case 1:
                                script_wait(4);
                                break;
                            case 2:
                                script_say("Gran grupo");
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                }
                break;
            case Guitarra:
                switch(roomScript.verb)
                {
                    case LOOK:
                        begin_script();
                        script_say("Mi guitarra");
                        end_script();
                        break;
                }
                break;
        }
    }
}
