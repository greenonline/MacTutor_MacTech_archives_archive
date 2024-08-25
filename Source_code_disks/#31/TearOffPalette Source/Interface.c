/*
--------------------------------------------------------
T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright (C)1987, 1988 by Impulse Technologies, 
 Inc., all rights reserved. 
 
 Filename:Interface.c
 Font:  Courier, 9 point
 Tab setting:    2
 Compiler:LightspeedC 2.15
 Project type:   APPL
 Creator: TOPD
 Segment: Main */



/*
--------------------------------------------------------GLOBAL CONSTANT 
DEFINITIONS AND VARIABLE DECLARATIONS */

#include "Constants.h"
#include "Variables.h"

/*
--------------------------------------------------------
EXTERNAL FUNCTION DECLARATIONS */

/* None */

/*
--------------------------------------------------------
FORWARD FUNCTION DECLARATIONS */

void AdjustInterface();
short GetMenuBarHeight();



/*
--------------------------------------------------------
ADJUST INTERFACE */

void AdjustInterface() {

 if(Environment.hasColorQD) {
 MaxDevice = GetMaxDevice(&(*GrayRgn)->rgnBBox);
 
 if((*(*MaxDevice)->gdPMap)->pixelSize == 8) {
 
 if(!ColorMenuVisible) {
 /* Insert Color menu if 256 colors. */
 InsertMenu(Menus[COLOR_MENU_INDEX], 0);
 DrawMenuBar();
 ColorMenuVisible = true;
 }
 }
 else {
 
 if(ColorMenuVisible) {
 /* Remove Color menu if < 256 colors. */
 DeleteMenu(COLOR_MENU_ID);
 DrawMenuBar();
 ColorMenuVisible = false;
 
 if(((WindowPeek) 
 Palettes[COLOR_PALETTE])->visible) {
 HideWindow(Palettes[COLOR_PALETTE]);
 }
 PalettesVisible[COLOR_PALETTE] = false;
 }
 }
 }
}

/*
--------------------------------------------------------
GET MENU BAR HEIGHT */

short GetMenuBarHeight() {

 if(Environment.machineType < envMachUnknown) {
 /* Arrggh! Someone has the 64K ROMs. */
 return(20);
 }
 else {
 return(MBarHeight);
 }
}


