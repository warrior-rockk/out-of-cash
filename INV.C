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

//add object to inventory
void inventory_add(uint8_t numObject)
{
    //ASSERT(inventory.numObjects < MAX_INV_OBJECTS);
    
    if (inventory.numObjects < MAX_INV_OBJECTS)
    {
        inventory.numObjects++;
        inventory.objIndex[inventory.numObjects - 1] = (numObject + 1);
        inventory.refresh = true;
        TRACE("Adding numObject %i to inventory array position %i\n", numObject, inventory.numObjects - 1);
    }
    else
        //this should not happen...
        say("No me caben mas objetos\n en el inventario...");
}

//remove object to inventory
void inventory_remove(uint8_t numObject)
{
    //inventory number must be higher than zero to remove
    ASSERT(inventory.numObjects > 0);
    
    for (int i = 0; i < inventory.numObjects; i++)
    {
        if (inventory.objIndex[i] == (numObject + 1))
        {
            inventory.objIndex[i] = 0;
            for (int j = i; j < inventory.numObjects - 1; j++)
            {
                inventory.objIndex[j] = inventory.objIndex[j + 1];
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
                            textprintf_centre_ex(inventoryImage, font, invX, invY, makecol(255,255,255), -1, "%i", objIndex);
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
                strcpy(s, "Hoja respuestas");
            break;
            case id_bathMat             :
                strcpy(s, "Alfombrilla");
            break;
            case id_blackBrain          :
                    strcpy(s, "Cerebro Negro");
                break;
            case id_blackStarClock      :
                    strcpy(s, "Reloj Negro");
                break;
            case id_book                :
                    strcpy(s, "Libro");
                break;
            case id_bookSheets          :
                    strcpy(s, "Hojas libro");
                break;
            case id_brain               :
                    strcpy(s, "Cerebro");
                break;
            case id_califications       :
                    strcpy(s, "Notas");
                break;
            case id_cassette            :
                    strcpy(s, "Casete");
                break;
            case id_coin                :
                    strcpy(s, "Moneda");
                break;
            case id_emptyCartridge      :
                    strcpy(s, "Cartucho vac¡o");
                break;
            case id_folder              :
                    strcpy(s, "Carpeta");
                break;
            case id_fullCartridge       :
                    strcpy(s, "Cartucho lleno");
                break;
            case id_fullFolder          :
                    strcpy(s, "Carpeta llena");
                break;
            case id_gel                 :
                    strcpy(s, "Gel");
                break;
            case id_guitar              :
                    strcpy(s, "Guitarra");
                break;
            case id_jeans               :
                    strcpy(s, "Pantalones");
                break;
            case id_key                 :
                    strcpy(s, "Llave");
                break;
            case id_knife               :
                    strcpy(s, "Escalpelo");
                break;
            case id_money               :
                    strcpy(s, "Dinero");
                break;
            case id_oat                 :
                    strcpy(s, "Avena");
                break;
            case id_openedEmptyCartridge:
                    strcpy(s, "Cartucho vac¡o");
                break;
            case id_openedFullCartridge :
                    strcpy(s, "Cartucho lleno");
                break;
            case id_paintBucket         :
                    strcpy(s, "Bote pintura");
                break;
            case id_photocopy           :
                    strcpy(s, "Fotocopia");
                break;
            case id_photocopySchedule   :
                    strcpy(s, "Fotocopia");
                break;
            case id_schedule            :
                    strcpy(s, "Horario");
                break;
            case id_sheet               :
                    strcpy(s, "Hoja");
                break;
            case id_shirt               :
                    strcpy(s, "Camiseta");
                break;
            case id_spatula             :
                    strcpy(s, "Esp tula");
                break;
            case id_starClock           :
                    strcpy(s, "Reloj");
                break;
            case id_starShirt           :
                    strcpy(s, "Camiseta");
                break;
            case id_oatMixed:
                    strcpy(s, "Avena viscosa");
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
                                script_say("Son las respuestas del examen de matem ticas");
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
                                script_say("Es la alfombrilla del ba¤o");
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
                                script_say("Un cerebro pintado de negro");
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
                                script_say("El reloj de cocina en forma de estrella pintado de negro");
                                break;
                            case 1:
                                script_say("A£n gotea la pintura");
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
                                script_say("Un libro titulado: Del deporte tambi‚n se sale");
                                break;
                            case 1:
                                script_say("Eso es lo que he dicho yo siempre...");
                                break;
                            default:
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
                                break;
                            case 2:
                                script_say("He arrancado las hojas del libro que me parec¡an interesantes");
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
                                script_say("Son las hojas arrancadas del libro de deporte");
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
                                script_say("¨Ser  este cerebro de alg£n antiguo alumno?");
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
                                script_say("Son mis notas del instituto");
                                break;
                            case 1:
                                if (is_game_flag(HISTORY_APPROVED_FLAG) &&
                                    is_game_flag(MATH_APPROVED_FLAG) &&
                                    is_game_flag(PE_APPROVED_FLAG))
                                {
                                    script_say("­He aprobado todo!");
                                    end_script();
                                }
                                else
                                    script_say("He suspendido Matem ticas, Historia y Educaci¢n F¡sica");
                                break;
                            case 2:
                                if (is_game_flag(HISTORY_APPROVED_FLAG) ||
                                    is_game_flag(MATH_APPROVED_FLAG) ||
                                    is_game_flag(PE_APPROVED_FLAG))
                                    script_say("Pero ya he aprobado:");
                                break;    
                            case 3:
                                if (is_game_flag(MATH_APPROVED_FLAG))
                                    script_say("Matem ticas");
                                else
                                    roomScript.step++;
                                break;
                            case 4:
                                if (is_game_flag(HISTORY_APPROVED_FLAG))
                                {
                                    if (is_game_flag(PE_APPROVED_FLAG))
                                        script_say("Historia");
                                    else
                                        script_say("e Historia");
                                }
                                else
                                    roomScript.step++;
                                break;
                            case 5:
                                if (is_game_flag(PE_APPROVED_FLAG))
                                {
                                    if (is_game_flag(MATH_APPROVED_FLAG) || is_game_flag(HISTORY_APPROVED_FLAG))
                                        script_say("y Educaci¢n F¡sica");
                                    else
                                        script_say("Educaci¢n F¡sica");
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
                                script_say("Un casete del £ltimo disco de Reincidentes");
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
                                script_say("Una moneda de 100 pesetas");
                                break;
                            case 1:
                                script_say("No es una fortuna pero por algo se empieza");
                                break;
                            default:
                                end_script();
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
                                script_say("Un cartucho de tinta de impresora vac¡o");
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
                                script_say("Una carpeta verde muy bonita");
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
                                script_say("Un cartucho de tinta de impresora");
                                break;
                            case 1:
                                script_say("Parece que a£n tiene tinta");
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
                                script_say("La carpeta est  llena de las hojas del libro de deporte");
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
                                script_say("Un bote lleno de gel de ducha");
                                break;
                            case 1:
                                script_say("Parece bastante viscoso");
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
                                script_say("Guitarra");
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
                                script_say("Espero que nadie necesitara estos pantalones...");
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
                                script_say("La llave del almac‚n de mantenimiento");
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
                                script_say("Un escalpelo afilado");
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
                                script_say("4900 pelas que mi padre me ha dado por aprobar las asignaturas");
                                break;
                            case 1:
                                script_say("­Ya estoy mas cerca de poder comprar la entrada!");
                                break;
                            default:
                                end_script();
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
                                script_say("Una caja de copos de avena");
                                break;
                            case 1:
                                script_say("Pone que son copos pero a mi me parecen granos");
                                break;
                            default:
                                end_script();
                                break;
                        }
                    break;
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
                                script_say("Un cartucho de tinta de impresora vac¡o y abierto");
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
                                script_say("Un cartucho de tinta de impresora abierto y con tinta");
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
                        }
                    break;
                }
                break;            
            case id_paintBucket         :
                switch(roomScript.verb)
                {
                    case LOOK:
                        switch (roomScript.step)
                        {
                            case 0:
                                begin_script();
                                script_say("Es un bote de pintura negra");
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
                                script_say("Una fotocopia de la serie Dragon Ball");
                                break;
                            case 1:
                                script_say("­Ademas creo que es de Goku!");
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
                                script_say("Es una fotocopia de Dragon Ball con el horario del instituto impreso por encima");
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
                                script_say("Es el horario del instituto impreso por ambas caras");
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
                                script_say("Una hoja vac¡a");
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
                                script_say("Yo tengo una camiseta del mismo color");
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
                                script_say("Una esp tula de cocina para aplicar mejunges");
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
                                script_say("Un est£pido reloj de cocina en forma de estrella");
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
                                script_say("Una camiseta con una estrella negra impresa en medio");
                                break;
                            case 1:
                                script_say("Ahora si que es clavadita a la m¡a");
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
                                script_say("Son los copos de avena mezclados con el gel de ducha");
                                break;
                            case 1:
                                script_say("Han formado una masa viscosa grumosa");
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
                                script_say("No querr¡a tocar esta masa con las manos");
                                break;
                            case 1:
                                script_say("Necesitar¡a algo con lo que aplicarlo");
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
                        script_combine_inv_object(id_brain, id_paintBucket, id_blackBrain);
                    break;
                    case 1:
                        script_say("Ahora tengo un bonito cerebro pintado de negro");
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
                        script_combine_inv_object(id_starClock, 0, id_blackStarClock);
                    break;
                    case 1:
                        script_say("El reloj con forma de estrella ahora est  cubierto de pintura negra");
                    break;
                    case 3:
                        script_say("Y la pintura a£n mancha...");
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
                        script_say("He podido abrir el cartucho y est  lleno de tinta negra");
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
                        script_combine_inv_object(id_shirt, id_blackStarClock, id_starShirt);
                    break;
                    case 1:
                        script_say("El reloj cubierto de tinta ha dejado una mancha en la camiseta en forma de estrella");
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
                        script_combine_inv_object(id_gel, id_oat, id_oatMixed);
                    break;
                    case 1:
                        script_say("Los copos de avena mezclados con el gel han formado una masa viscosa y grumosa");
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
                    break;
                    case 1:
                        script_say("He metido las hojas del libro de deporte en la carpeta");
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
                            script_say("La idea de aplicarme avena no es mala pero, ¨cual es el motivo de hacerlo?");
                            end_script();
                        }
                        else if (get_actual_room() != PE_OFFICE_ROOM_NUM)
                        {
                            script_say("No deber¡a hacer esto aqu¡. Se me puede resbalar y caer");
                            end_script();
                        }
                        else
                            script_remove_inv_object(id_oatMixed);
                    break;
                    case 1:
                        script_say("Emm... ¨Profesor?");
                    break;
                    default:
                        set_game_flag(SHOW_DISEASE_FLAG);
                        end_script();
                    break;
                }
            break;
        }
    }
}
