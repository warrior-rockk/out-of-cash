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
* **Pointers to needed images**: (main, hotpost, walk and layers)
* **Pointers to room functions**: (room_init, room_update, room_get_hotspot_name, room_get_object ...)
* **Start player position**
* **Num room objects**

*We need to load room resources with only the int room number.*

```
//room data file
close_datafile(actualRoom.dataFile);
strRoomDataFile = //compose datafile string name with actualRoomNumber "RNNDATA.DAT"
actualRoom.datafile = load_datafile(strRoomDataFile)

//room images (fixed position for room images? 0-main 1-hotspot 2-walk... Loop for room layers? room var to get number and position of layers?)
actualRoom.image = (BITMAP *)actualRoom.datafile[0].dat
actualRoom.hsImage = (BITMAP *)actualRoom.datafile[1].dat
actualRoom.wImage = (BITMAP *)actualRoom.datafile[2].dat

//room pointers to functions

//proposal: on engine.h, global array of pointers to functions for each function.
//for example: room_get_hotspot_name[NUM_MAX_ROOMS]

//THe room header defines his room number and sets the pointer:
rooms_get_hotspot_name[R01_ROOM_NUMBER] = &r01_get_hotspot_name;

//And game reads of this array
actualRoom.get_hotspot_name = rooms_get_hotspot_name[actualRoomNumber];


//room vars (init position and num objects) 

//same as array of pointers to functions. Array of start_pos_x, y and numObjects

actualRoom.start_pos_x = rooms_start_pos_x[actualRoomNumber]
actualRoom.start_pos_y = rooms_start_pos_y[actualRoomNumber]
actualRoom.room_num_objects = rooms_num_objects[actualRoomNumber]

//On Summary, instead of having a rooms structure array (except images) on game.h, move to engine.h and allow each room to write on the structure data directly except the images

//GAME.H:

struct actualRoom
{
	(DATAFILE *) datafile;
	(BITMAP *) image;
	(BITMAP *) hsImage;
	(BITMAP *) wImage;
	(BITMAP *) fImage;
	(MIDI*)    song;
}

//ENGINE.H

struct roomData[MAX_ROOMS]
{
    //variables
	int start_pos_x;
    int start_pos_y;
    uint8_ numObjects;
    
	//pointers to functions
	void (*room_get_hotspot_name)(uint8_t, char *s);
    enum verbs (*room_get_default_hotspot_verb)(uint8_t);
    tObject* (*room_get_object_info)(uint8_t numObject);
    void (*room_init)(void);
    void (*room_update)(void);	
}

//instead of put roomData on ENGINE.H, create a ROOMS.H with all the definitions of the rooms for separation
```
	

	
