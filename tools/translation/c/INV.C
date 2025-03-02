//#define DEBUGMODE

#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <allegro.h>
#include "inv.h"
#include "globals.h"
#include "engine.h"
#include "IDATA.H"

//initialization of inventory
void inventory_init()
{
    //initialize data
    inventory.numObjects = 0;
    inventory.page = 0;
    inventory.refresh = true;   //for redrawn
    for (int i = 0; i < MAX_INV_OBJECTS; i++)
        inventory.objIndex[i] = 0;
    
    //create inventory bitmap buffer to draw objects
    if (!inventoryImage)
        inventoryImage = create_bitmap(INV_REGION_W, INV_REGION_H);
    //clear inventory bitmap buffer
    clear_bitmap(inventoryImage);

}

#ifdef DEBUGMODE
void get_all_inv_objects()
{
    //get all inventory
    if (!debug.allInvObjects)
    {
        for (int i = 0; i < id_COUNT; i++)
        {
            inventory.objIndex[i] = i + 1;
            inventory.numObjects++;
        }
    }
    debug.allInvObjects = true;
    inventory.refresh = true;
}
#endif

//function to destroy inventory (free resources)
void inventory_destroy()
{
    TRACE("Destroy INVENTORY system\n");
    
    destroy_bitmap(inventoryImage);

    TRACE("Destroy INVENTORY system\n");
}

//add object to inventory
void inventory_add(uint8_t numObject)
{
    //ASSERT(inventory.numObjects < MAX_INV_OBJECTS);
    
    if (inventory.numObjects < MAX_INV_OBJECTS)
    {
        inventory.numObjects++;
        inventory.objIndex[inventory.numObjects - 1] = (numObject + 1);
        //go to last inventory page
        inventory.page = inventory.numObjects <= INV_OBJECTS_PER_PAGE ? 0 : ((inventory.numObjects - 1) / INV_OBJECTS_PER_ROW) - 1;                
        //refresh inventory
        inventory.refresh = true;
        TRACE("Adding numObject %i to inventory array position %i\n", numObject, inventory.numObjects - 1);
    }
    else
        //this should not happen...
        say("I can't fit any more items\n in the inventory...");
}

//remove object to inventory
void inventory_remove(uint8_t numObject)
{
    //inventory number must be higher than zero to remove
    ASSERT(inventory.numObjects > 0);

    //run for existing inventory items
    for (int i = 0; i < inventory.numObjects; i++)
    {
        //on founded
        if (inventory.objIndex[i] == (numObject + 1))
        {
            //remove inventory item
            inventory.objIndex[i] = 0;
            //run for next inventory items to move position
            for (int j = i; j < inventory.numObjects; j++)
            {
                if (j < inventory.numObjects - 1)
                    //move next item to previous
                    inventory.objIndex[j] = inventory.objIndex[j + 1];
                else
                    //clearlast item
                    inventory.objIndex[j] = 0;
            }
        }
    }

    inventory.numObjects--;
    inventory.refresh = true;
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
            
            clear_bitmap(inventoryImage);
            //run for inventory objects of active page
            for (int i = 0; i < inventory.numObjects && i < INV_OBJECTS_PER_PAGE; i++)
            {
                //calculate paginated object index
                objIndex = i + (inventory.page * INV_OBJECTS_PER_ROW);
                //check limits
                if (objIndex < MAX_INV_OBJECTS)
                {
                    //if inventory pos has object
                    if (inventory.objIndex[objIndex] > 0)
                    {
                        //calculate icon position
                        invX = ((INV_ICON_X_OFFSET * (objIndex % INV_OBJECTS_PER_ROW)) + (INV_ICON_X_OFFSET>>1)) + ((objIndex % INV_OBJECTS_PER_ROW) * INV_ICON_MARGIN) - ((((BITMAP *)inventoryDataFile[inventory.objIndex[objIndex]-1].dat)->w)>>1);
                        invY = ((INV_ICON_Y_OFFSET * (objIndex / (INV_OBJECTS_PER_ROW * (inventory.page + 1)))) + (INV_ICON_Y_OFFSET>>1)) + ((objIndex / (INV_OBJECTS_PER_ROW * (inventory.page + 1))) * INV_ICON_MARGIN) - ((((BITMAP *)inventoryDataFile[inventory.objIndex[objIndex]-1].dat)->h)>>1);
                        //blit inventory icon on inventory image
                        draw_sprite(inventoryImage, (BITMAP *)inventoryDataFile[inventory.objIndex[objIndex]-1].dat, invX, invY);
                        //debug: print inv object index
                        #ifdef DEBUGMODE
                            //textprintf_centre_ex(inventoryImage, font, invX, invY, makecol(255,255,255), -1, "%i", objIndex);
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
            draw_sprite(buffer, inventoryImage, INV_POS_X, INV_POS_Y);
        }
    }
}

//calculate the inventory position based on colorCode
uint8_t get_inv_obj_position(uint8_t colorCode)
{
    if (colorCode > (INV_COLOR_OFFSET + INV_OBJECTS_PER_PAGE))
        return 0;
    else
        return (uint8_t)((colorCode % INV_COLOR_OFFSET) + (inventory.page * INV_OBJECTS_PER_ROW) + 1);
}

//get inventory object value based on inventory position
uint8_t get_inv_obj_id(uint8_t invPosition)
{
    return (inventory.objIndex[invPosition] - 1);
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
            case id_answers:
                strcpy(s, "Answers sheet");
            break;
            case id_bathMat             :
                strcpy(s, "Bath Mat");
            break;
            case id_blackBrain          :
                    strcpy(s, "Black Brain");
                break;
            case id_blackStarClock      :
                    strcpy(s, "Black Clock");
                break;
            case id_book                :
                    strcpy(s, "Book");
                break;
            case id_bookSheets          :
                    strcpy(s, "Book sheets");
                break;
            case id_brain               :
                    strcpy(s, "Brain");
                break;
            case id_califications       :
                    strcpy(s, "Califications");
                break;
            case id_cassette            :
                    strcpy(s, "Cassette");
                break;
            case id_coin                :
                    strcpy(s, "Quarter");
                break;
            case id_emptyCartridge      :
                    strcpy(s, "Empty cartridge");
                break;
            case id_folder              :
                    strcpy(s, "Folder");
                break;
            case id_fullCartridge       :
                    strcpy(s, "Cartridge full");
                break;
            case id_fullFolder          :
                    strcpy(s, "Folder llena");
                break;
            case id_gel                 :
                    strcpy(s, "Gel");
                break;
            case id_guitar              :
                    strcpy(s, "Guitar");
                break;
            case id_jeans               :
                    strcpy(s, "Jeans");
                break;
            case id_key                 :
                    strcpy(s, "Key");
                break;
            case id_knife               :
                    strcpy(s, "Scalpel");
                break;
            case id_money               :
                    strcpy(s, "Money");
                break;
            case id_oat                 :
                    strcpy(s, "Oat");
                break;
            case id_openedEmptyCartridge:
                    strcpy(s, "Empty cartridge");
                break;
            case id_openedFullCartridge :
                    strcpy(s, "Cartridge full");
                break;
            case id_paintBucket         :
                    strcpy(s, "Paint bucket");
                break;
            case id_photocopy           :
                    strcpy(s, "Photocopy");
                break;
            case id_photocopySchedule   :
                    strcpy(s, "Photocopy");
                break;
            case id_schedule            :
                    strcpy(s, "Schedule");
                break;
            case id_sheet               :
                    strcpy(s, "Sheet");
                break;
            case id_shirt               :
                    strcpy(s, "T-shirt");
                break;
            case id_spatula             :
                    strcpy(s, "Spatula");
                break;
            case id_starClock           :
                    strcpy(s, "Clock");
                break;
            case id_starShirt           :
                    strcpy(s, "T-shirt");
                break;
            case id_oatMixed:
                    strcpy(s, "Oat viscosa");
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
        switch (roomScript.object)
        {
            case id_answers:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("They are the answers to the mathematics exam");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_bathMat             :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's the mat of the bathroom");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_blackBrain          :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A black painted brain");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_blackStarClock      :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The star-shaped kitchen clock painted black");
                                break;
                            case 1:
                                script_say("Drips paint yet");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_shirt:
                                start_script(STAR_SHIRT_SCRIPT);
                            break;
                        }
                    break;
                }
                break;            
            case id_book                :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                if (get_game_var(SPORT_BOOK_VAR) == 0)
                                    script_say("\"You also get out of the sport\"");
                                else
                                    roomScript.step++;
                            break;
                            case 1:
                                switch (get_game_var(SPORT_BOOK_VAR))
                                {
                                    case 0:
                                        script_say("Chapter 1: Laziness is your ally");
                                    break;
                                    case 1:
                                        script_say("Chapter 2: Take Care of Your Knees");
                                    break;
                                    case 2:
                                        script_say("Chapter 3: Sports Diseases");
                                    break;
                                }
                            break;
                            case 2:
                                switch (get_game_var(SPORT_BOOK_VAR))
                                {
                                    case 0:
                                        script_say("Everything that involves an effort can be postponed");
                                    break;
                                    case 1:
                                        script_say("Recent studies show the relationship between playing sports and the deterioration of your knees");
                                    break;
                                    case 2:
                                        script_say("The best way to get rid of sport is with an illness that prevents you from doing it");
                                    break;
                                }
                            break;
                            case 3:
                                switch (get_game_var(SPORT_BOOK_VAR))
                                {
                                    case 0:
                                        script_say("Leave for tomorrow what you don't want to do today");
                                    break;
                                    case 1:
                                        script_say("A healthy body is a rested body");
                                    break;
                                    case 2:
                                        script_say("Skin diseases can have a lumpy and in some cases viscous texture");
                                    break;
                                }
                            break;
                            default:
                                if (get_game_var(SPORT_BOOK_VAR) < 2)
                                    inc_game_var(SPORT_BOOK_VAR);
                                else
                                    set_game_var(SPORT_BOOK_VAR, 0);
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_remove_inv_object(id_book);
                                break;
                            case 1:
                                script_add_inv_object(id_bookSheets);
                                play_sound(sd_paper);
                                break;
                            case 2:
                                script_say("I have torn out the sheets of the book that I found interesting");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                }
                break;            
            case id_bookSheets          :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("They are the sheets torn from the sports book");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_folder:
                                start_script(SPORT_WORK_SCRIPT);
                            break;
                        }
                    break;
                }
                break;            
            case id_brain               :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Could this be the brain of some former student?");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_paintBucket:
                                start_script(BLACK_BRAIN_SCRIPT);
                            break;
                            case id_openedFullCartridge:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("It may be a good idea to paint the brain");
                                    break;
                                    case 1:
                                        script_say("But there's not enough paint on the cartridge to paint it");
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                        }
                    break;
                }
                break;            
            case id_califications       :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("These are my high school califications");
                                break;
                            case 1:
                                if (is_game_flag(HISTORY_APPROVED_FLAG) &&
                                    is_game_flag(MATH_APPROVED_FLAG) &&
                                    is_game_flag(PE_APPROVED_FLAG))
                                {
                                    script_say("I have approved everything!");
                                    end_script();
                                }
                                else
                                    script_say("He suspendido Mathematics, History and Physical Education");
                                break;
                            case 2:
                                if (is_game_flag(HISTORY_APPROVED_FLAG) ||
                                    is_game_flag(MATH_APPROVED_FLAG) ||
                                    is_game_flag(PE_APPROVED_FLAG))
                                    script_say("But I've already passed:");
                                else
                                    end_script();
                                break;    
                            case 3:
                                if (is_game_flag(MATH_APPROVED_FLAG))
                                    script_say("Mathematics");
                                else
                                    roomScript.step++;
                                break;
                            case 4:
                                if (is_game_flag(HISTORY_APPROVED_FLAG))
                                {
                                    if (is_game_flag(PE_APPROVED_FLAG))
                                        script_say("History");
                                    else if (is_game_flag(MATH_APPROVED_FLAG))
                                        script_say("e History");
                                    else
                                        script_say("History");
                                }
                                else
                                    roomScript.step++;
                                break;
                            case 5:
                                if (is_game_flag(PE_APPROVED_FLAG))
                                {
                                    if (is_game_flag(MATH_APPROVED_FLAG) || is_game_flag(HISTORY_APPROVED_FLAG))
                                        script_say("and Physical Education");
                                    else
                                        script_say("Physical Education");
                                }
                                else
                                    roomScript.step++;
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_cassette            :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A cassette of the last \"The Repeat Offenders\" record");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_coin                :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A one quarter coin");
                                break;
                            case 1:
                                script_say("It's not a fortune but it's a start");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_money:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        start_script(COMBINE_MONEY_SCRIPT);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                        }
                    break;
                }
                break;            
            case id_emptyCartridge      :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("An empty printer ink cartridge");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_folder              :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A very nice green folder");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_bookSheets:
                                start_script(SPORT_WORK_SCRIPT);
                            break;
                        }
                    break;
                }
                break;            
            case id_fullCartridge       :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A printer ink cartridge");
                                break;
                            case 1:
                                script_say("Looks like it has ink yet");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's very solid. I can't with my hands");
                                break;
                            case 1:
                                script_say("I would need to use something");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_knife:
                                start_script(OPEN_FULL_CARTRIDGE_SCRIPT);
                            break;
                            case id_starClock:
                                begin_script();
                                script_say("I would have to open the cartridge somehow to be able to use the ink inside");
                                end_script();
                            break;
                        }
                    break;
                }
                break;            
            case id_fullFolder          :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The folder is filled with the sheets of the sports book");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_gel                 :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch(roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A bottle full of shower gel");
                                break;
                            case 1:
                                script_say("Looks pretty slimy");
                                break;
                            default:
                                end_script();
                                break;
                        }
                        break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_oat:
                                start_script(OAT_MIXED_SCRIPT);
                            break;
                        }
                    break;
                }
                break;            
            case id_guitar              :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Guitar");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_jeans               :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I hope no one needed these pants...");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_key                 :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("The key to the maintenance warehouse");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_knife               :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A sharp scalpel");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_fullCartridge:
                                start_script(OPEN_FULL_CARTRIDGE_SCRIPT);
                            break;
                        }
                    break;
                }
                break;            
            case id_money               :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("29 bucks and 75 pennies that my father has given me for passing the subjects");
                                break;
                            case 1:
                                script_say("I'm one quarter away from being able to buy the concert ticket!");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch (roomScript.invObject)
                        {
                            case id_coin:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        start_script(COMBINE_MONEY_SCRIPT);
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                        }
                    break;
                }
                break;            
            case id_oat                 :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A box of oat flakes");
                                break;
                            case 1:
                                script_say("It says that they are flakes but to me they look like grains");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case OPEN:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("These oat grains are a little dry");
                                break;
                            case 1:
                                script_say("I should mix them with something");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_gel:
                                start_script(OAT_MIXED_SCRIPT);
                            break;
                        }
                    break;
                }
                break;            
            case id_openedEmptyCartridge:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("An empty printer ink cartridge y abierto");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_openedFullCartridge :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A printer ink cartridge abierto y con tinta");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_starClock:
                                start_script(BLACK_STAR_CLOCK_SCRIPT);
                            break;
                            case id_brain:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("It may be a good idea to paint the brain");
                                    break;
                                    case 1:
                                        script_say("But there's not enough paint on the cartridge to paint it");
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                        }
                    break;
                }
                break;            
            case id_paintBucket:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's a bucket of black paint");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_brain:
                                start_script(BLACK_BRAIN_SCRIPT);
                            break;
                            case id_starClock:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("The idea of painting the star clock is not a bad one");
                                    break;
                                    case 1:
                                        script_say("But I don't need as much paint for it and I'm sure I need it for something else");
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                        }
                    break;
                }
                break;            
            case id_photocopy           :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A photocopy of the Dragon Ball series");
                                break;
                            case 1:
                                script_say("And I think it's Goku's!");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_photocopySchedule   :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's a photocopy of Dragon Ball with the high school schedule printed above");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_schedule            :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It is the high school schedule printed on both sides");
                                break;
                            case 1:
                                script_say("Not that I want it. I'm not going to class");
                            break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_sheet               :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("An empty sheet");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;            
            case id_shirt               :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("I have a t-shirt of the same color");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_blackStarClock:
                                start_script(STAR_SHIRT_SCRIPT);
                            break;
                            case id_starClock:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        change_player_dir(DIR_FRONT);
                                        script_say("That's it?");
                                    break;
                                    case 1:
                                        script_say("Is that what you think?”");
                                    break;
                                    case 2:
                                        script_wait(5);
                                    break;
                                    case 3:
                                        script_say("Did you expect that by pairing a watch with a t-shirt it would become a star t-shirt?");
                                    break;
                                    case 4:
                                        script_wait(5);
                                    break;
                                    case 5:
                                        script_say("Like some kind of magic?");
                                    break;
                                    case 6:
                                        script_wait(5);
                                    break;
                                    case 7:
                                        script_say("That by bringing it closer, his silhouette is transferred?");
                                    break;
                                    case 8:
                                        script_wait(5);
                                    break;
                                    case 9:
                                        script_say("I don't think so ");
                                    break;
                                    default:
                                        change_player_dir(DIR_RIGHT);
                                        end_script();
                                    break;
                                }
                            break;
                        }
                    break;
                }
                break;            
            case id_spatula             :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A kitchen spatula for applying concoctions");
                            break;
                            case 1:
                                script_say("Or anything viscous");
                            break;
                            default:
                                end_script();
                            break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_oatMixed:
                                start_script(APPLY_OAT_SCRIPT);
                            break;
                        }
                    break;
                }
                break;            
            case id_starClock           :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A stupid star-shaped kitchen clock ");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_openedFullCartridge:
                                start_script(BLACK_STAR_CLOCK_SCRIPT);
                            break;
                            case id_shirt:
                                begin_script();
                                script_say("Did you expect that by pairing a watch with a t-shirt it would become a star t-shirt?");
                                end_script();
                            break;
                            case id_fullCartridge:
                                begin_script();
                                script_say("I would have to open the cartridge somehow to be able to use the ink inside");
                                end_script();
                            break;
                            case id_paintBucket:
                                switch (roomScript.step)
                                {
                                    case 0:
                                        begin_script();
                                        script_say("The idea of painting the star clock is not a bad one");
                                    break;
                                    case 1:
                                        script_say("But I don't need as much paint for it and I'm sure I need it for something else");
                                    break;
                                    default:
                                        end_script();
                                    break;
                                }
                            break;
                        }
                    break;
                }
                break;            
            case id_starShirt           :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("A t-shirt with a black star printed in the middle");
                                break;
                            case 1:
                                script_say("Now it is nailed to mine");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;                    
                }
                break;
            case id_oatMixed:
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("It's the oat flakes mixed with the shower gel");
                                break;
                            case 1:
                                script_say("They have formed a lumpy viscous mass");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("You don't want to touch this dough with your hands");
                                break;
                            case 1:
                                script_say("Need something to apply it to");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
                    case USE_WITH:
                        switch(roomScript.invObject)
                        {
                            case id_spatula:
                                start_script(APPLY_OAT_SCRIPT);
                            break;
                        }
                    break;
                }
                break;            
            case BLACK_BRAIN_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        play_sound_rnd(sd_paint);
                        script_combine_inv_object(id_brain, id_paintBucket, id_blackBrain);
                    break;
                    case 1:
                        script_say("Now I have a nice brain painted black");
                    break;
                    default:
                        end_script();
                    break;
                }
            break;
            case BLACK_STAR_CLOCK_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        play_sound_rnd(sd_greasy);
                        script_combine_inv_object(id_starClock, id_openedFullCartridge, id_blackStarClock);
                    break;
                    case 1:
                        script_say("The star-shaped clock is now covered in black paint");
                    break;
                    case 3:
                        script_say("And the paint stains yet...");
                    break;
                    default:
                        end_script();
                    break;
                }
            break;
            case OPEN_FULL_CARTRIDGE_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        script_combine_inv_object(id_fullCartridge, 0, id_openedFullCartridge);
                    break;
                    case 1:
                        script_say("I was able to open the cartridge and it is full of black ink");
                    break;
                    default:
                        end_script();
                    break;
                }
            break;
            case STAR_SHIRT_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        play_sound_rnd(sd_paint);
                        script_combine_inv_object(id_shirt, id_blackStarClock, id_starShirt);
                    break;
                    case 1:
                        script_say("The ink-covered clock has left a star-shaped stain on the t-shirt");
                    break;
                    default:
                        end_script();
                    break;
                }
            break;
            case OAT_MIXED_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        play_sound_rnd(sd_paint);
                        script_combine_inv_object(id_gel, id_oat, id_oatMixed);
                    break;
                    case 1:
                        script_say("The oat flakes mixed with the gel have formed a viscous lumpy mass");
                    break;
                    default:
                        end_script();
                    break;
                }
            break;
            case SPORT_WORK_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        script_combine_inv_object(id_bookSheets, id_folder, id_fullFolder);
                        play_sound(sd_paper);
                    break;
                    case 1:
                        script_say("I have put the sheets of the sports book in the folder");
                    break;
                    default:
                        end_script();
                    break;
                }
            break;
            case APPLY_OAT_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        if (!is_game_flag(INFO_SPORT_WORK_FLAG))
                        {
                            script_say("The idea of stuffing myself with oats is not bad but, what is the reason for doing it?");
                            end_script();
                        }
                        else if (get_actual_room() != PE_OFFICE_ROOM_NUM)
                        {
                            script_say("If I put this lumpy mass on my body, maybe I can simulate a disease");
                        }
                        else
                            script_remove_inv_object(id_oatMixed);
                    break;
                    case 1:
                        if (get_actual_room() != PE_OFFICE_ROOM_NUM)
                            script_say("But I shouldn't do this here");
                        else
                            script_move_player(200, 142);
                    break;
                    case 2:
                        if (get_actual_room() != PE_OFFICE_ROOM_NUM)
                            end_script();
                        else
                        {
                            change_player_dir(DIR_RIGHT);
                            script_play_player_animation(ANIM_PLY_APPLY_OAT_1);
                        }
                    break;
                    case 3:
                        play_player_animation(ANIM_PLY_APPLY_OAT_STILL);
                        script_play_sound_wait(sd_paint);
                    break;
                    case 4:
                        script_play_player_animation(ANIM_PLY_APPLY_OAT_2);
                    break;
                    case 5:
                        script_play_player_animation(ANIM_PLY_APPLY_OAT_STILL_2);
                    break;
                    default:
                        set_game_flag(SHOW_DISEASE_FLAG);
                        set_game_flag(APPLIED_OAT_FLAG);
                        end_script();
                    break;
                }
            break;
            case COMBINE_MONEY_SCRIPT:
                switch(roomScript.step)
                {
                    case 0:
                        begin_script();
                        script_combine_inv_object(id_money, id_coin, id_guitar);
                    break;
                    case 1:
                        script_say("AT LAST!");
                    break;
                    case 2:
                        script_say("I ALREADY HAVE THE MONEY FOR THE TICKET!");
                    break;
                    case 3:
                        set_game_flag(GAME_END_FLAG);
                        end_script();
                    default:
                        end_script();
                    break;
                }
            break;
        }
    }
}
