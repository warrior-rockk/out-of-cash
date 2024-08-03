#define DEBUGMODE

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <allegro.h>
#include "inventor.h"
#include "game.h"    //<<-----FIX THAT! MAY NOT ACCESS BUFFER TO DRAW! SEPARATE RENDER!
#include "engine.h"
#include "inv.h"

//initialization of inventory
void inventory_init()
{
    inventory.image = create_bitmap(INV_REGION_W, INV_REGION_H);
    clear_bitmap(inventory.image);
    
    inventory.page = 0;
    inventory.refresh = true;
    
    //test inventory
    /*
    inventory.numObjects = 9;
    
    inventory.objIndex[0] = dInv_Cassette + 1;
    inventory.objIndex[1] = dInv_Guitar + 1;
    inventory.objIndex[2] = dInv_Soap + 1;
    inventory.objIndex[3] = dInv_Cassette + 1;
    inventory.objIndex[4] = dInv_Guitar + 1;
    inventory.objIndex[5] = dInv_Soap + 1;
    inventory.objIndex[6] = dInv_Cassette + 1;
    inventory.objIndex[7] = dInv_Guitar + 1;
    inventory.objIndex[8] = dInv_Soap + 1;
    */
}

//add object to inventory
void inventory_add(uint8_t numObject)
{
    //ASSERT(inventory.numObjects < MAX_INV_OBJECTS);
    
    if (inventory.numObjects < MAX_INV_OBJECTS)
    {
        inventory.numObjects++;
        inventory.objIndex[inventory.numObjects - 1] = numObject + 1;
        inventory.refresh = true;
    }
    else
        //this should not happen...
        say("No me caben mas objetos\n en el inventario...");
}

//draws the inventory
void inventory_draw()
{
    //if objects on inventory
    if (inventory.numObjects > 0)
    {
        //only compose the inventory if refresh flag
        if (inventory.refresh)
        {
            int invX;
            int invY;
            int objIndex;
            
            clear_bitmap(inventory.image);
            TRACE("INICIO\n");
            //run for inventory objects of active page
            for (int i = 0; i < inventory.numObjects && i < INV_OBJECTS_PER_PAGE; i++)
            {
                //calculate paginated object index
                objIndex = i + (inventory.page * INV_OBJECTS_PER_ROW);
                //check limites
                if (objIndex < MAX_INV_OBJECTS)
                {
                    //if inventory pos has object
                    if (inventory.objIndex[objIndex] > 0)
                    {
                        //calculate icon position
                        invX = ((INV_ICON_X_OFFSET * (objIndex % INV_OBJECTS_PER_ROW)) + (INV_ICON_X_OFFSET>>1)) + ((objIndex % INV_OBJECTS_PER_ROW) * INV_ICON_MARGIN) - ((((BITMAP *)inventoryDataFile[inventory.objIndex[objIndex]-1].dat)->w)>>1);
                        invY = ((INV_ICON_Y_OFFSET * (objIndex / (INV_OBJECTS_PER_ROW * (inventory.page + 1)))) + (INV_ICON_Y_OFFSET>>1)) + ((objIndex / (INV_OBJECTS_PER_ROW * (inventory.page + 1))) * INV_ICON_MARGIN) - ((((BITMAP *)inventoryDataFile[inventory.objIndex[objIndex]-1].dat)->h)>>1);
                        //blit inventory icon on inventory image
                        draw_sprite(inventory.image, (BITMAP *)inventoryDataFile[inventory.objIndex[objIndex]-1].dat, invX, invY);
                        //debug: print inv object index
                        #ifdef DEBUGMODE
                            textprintf_centre_ex(inventory.image, font, invX, invY, makecol(255,255,255), -1, "%i", objIndex);
                        #endif
                    }
                }
            }
            //reset refresh flag
            inventory.refresh = false;
        }
        else
        {
            //draws the last composed inventory image
            draw_sprite(buffer, inventory.image, INV_POS_X, INV_POS_Y + HUD_Y);
        }
    }
    show_debug("Inv Objs", inventory.numObjects);
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
void inventory_update()
{
    //if nothing selected
    if (roomScript.active)
    {
        //sequence actions
        switch (roomScript.object - 1)
        {
            case dInv_Cassette:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
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
            case dInv_Guitar:
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
