# Development info

## Game files structure

* GAME.EXE
* CWSDPMI.EXE
* DATAFILES:
	* **GAME.DAT**: *gui, hud, cursor...(persistent data)*
	* **PLAYER.DAT**: *player animations (persistent data)*
	* **INVENTORY.DAT**: *inventory objects (load once object on required?)*
	* **ROOMNN.DAT**: *room data (images, objects, music...) (load once datafile on required?)*
	
## Room files definition

*NN is 2-digit room number*

* **roomNN.bmp**: *main room image*
* **roomNNhs.bmp**: *hotspot room image*
* **roomNNw.bmp**: *room walk map image*
* **roomNNf.bmp**: *front layer room image*

	
