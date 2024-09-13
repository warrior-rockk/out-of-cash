# Development info

## Game files structure

* GAME.EXE
* CWSDPMI.EXE
* DATAFILES:
	* **GDATA.DAT**: *gui, hud, cursor...(persistent data)*
	* **PDATA.DAT**: *player animations (persistent data)*
	* **IDATA.DAT**: *inventory objects (load once object on required?)*
	* **RNNDATA.DAT**: *room data (images, objects, music...) (load once datafile on required?)*
	
## Room files definition

*NN is 2-digit room number*

* **roomNN.bmp**: *main room image*
* **roomNNhs.bmp**: *hotspot room image*
* **roomNNw.bmp**: *room walk map image*
* **roomNNf.bmp**: *front layer room image*

## Room data load

*For load a room we need:*
	
* **Datafile loaded**
* **Pointers to needed images**: (main, hotspot and walk)
* **Pointers to room functions**: (room_init, room_update, room_get_hotspot_name, room_get_object ...)
* **Start player position**
* **Num room objects**

*We need to load room resources with only the int room number.*

```
//room data file
close_datafile(actualRoom.dataFile);
strRoomDataFile = //compose datafile string name with actualRoomNumber "RNNDATA.DAT"
actualRoom.datafile = load_datafile(strRoomDataFile)

//room images (fixed datafile order for room images: 0-main 1-hotspot 2-walk...)
actualRoom.image = 		(BITMAP *)actualRoom.datafile[0].dat
actualRoom.hsImage = 	(BITMAP *)actualRoom.datafile[1].dat
actualRoom.wImage = 	(BITMAP *)actualRoom.datafile[2].dat

//room pointers to functions and room vars:

//Global header with roomData structure that is an array of the needed data for describe the room.
//Every room defines a preprocessor directive with the initialization of their array position

//On Summary, instead of having a rooms structure array (except images) on game.h, move to rooms.h and each room has preprocessor directive to initialize room structure data

//GAME.H:

struct actualRoom
{
	(DATAFILE *) datafile;
	(BITMAP *) image;
	(BITMAP *) hsImage;
	(BITMAP *) wImage;
}

//ROOMS.H

typedef struct tRoomData
{
    //default start player position on room
    int start_pos_x;
    int start_pos_y;
    //room num objects
    uint8_t room_num_objects;
    
    //function pointer to init room
    void (*room_init)(void);
    //function pointer to update room
    void (*room_update)(void);
    //function pointer to get hotspot name
    void (*room_get_hotspot_name)(uint8_t, char *s);
    //function pointer to get default hotspot verb
    enum verbs (*room_get_default_hotspot_verb)(uint8_t);
    //function pointer to get object info
    tObject* (*room_get_object_info)(uint8_t numObject);
} tRoomData;

//initialize room data
tRoomData roomData[NUM_GAME_ROOMS] = {
    {R01_DATA},
    {R02_DATA}
};

```
	

	
