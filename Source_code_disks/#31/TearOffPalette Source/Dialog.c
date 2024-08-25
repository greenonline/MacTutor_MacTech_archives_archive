/*
--------------------------------------------------------
T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright (C)1987, 1988 by Impulse Technologies, 
 Inc., all rights reserved. 
 
 Filename:Dialog.c
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
--------------------------------------------------------EXTERNAL FUNCTION 
DECLARATIONS */

extern short GoodResource();/* Error.c */
extern short GetMenuBarHeight(); /* Interface.c */

/*
--------------------------------------------------------
FORWARD FUNCTION DECLARATIONS */

void DoAbout();
short PositionDialog();
pascal Boolean DialogFilter();



/*
--------------------------------------------------------
DO ABOUT */

void DoAbout() {
 DialogRecord theDialogRecord;
 short itemHit;
 
 if(PositionDialog(ABOUT_DIALOG_ID)) {
 (void) GetNewDialog(ABOUT_DIALOG_ID, 
 &theDialogRecord, BRING_TO_FRONT);
 ShowWindow(&theDialogRecord);
 
 do {
 ModalDialog(DialogFilter, &itemHit);
 }
 while(itemHit == 0);
 
 CloseDialog(&theDialogRecord);
 }
}

/*
--------------------------------------------------------
POSITION DIALOG

 PositionDialog() centers a DITL resource horizontally and positions 
it one-third down
the screen vertically. */

short PositionDialog(whichID)
short whichID;
{
 Point where;
 DialogTHndl theTemplate;
 
 if(!GoodResource(theTemplate = (DialogTHndl) 
 GetResource('DLOG', whichID))) {
 return(false);
 }
 OffsetRect(&(*theTemplate)->boundsRect,
 - (*theTemplate)->boundsRect.left
 + ((screenBits.bounds.right
 - screenBits.bounds.left)
 - ((*theTemplate)->boundsRect.right
 - (*theTemplate)->boundsRect.left)) / 2,
 - (*theTemplate)->boundsRect.top
 + (((screenBits.bounds.bottom
 - screenBits.bounds.top-GetMenuBarHeight())
 - ((*theTemplate)->boundsRect.bottom
 - (*theTemplate)->boundsRect.top)) / 3)
 + GetMenuBarHeight());
 return(true);
}

/*
--------------------------------------------------------
DIALOG FILTER

 DialogFilter() allows exit of ModalDialog() on any mouseDown or keyDown 
event. */

pascal Boolean DialogFilter(whichDialog, whichEvent, 
 whichItem)
DialogPtr whichDialog;
EventRecord *whichEvent;
short *whichItem;
{
 WindowPtr whichWindow;
 
 if((whichEvent->what == mouseDown) || 
 (whichEvent->what == keyDown)) {
 
 if((FindWindow(whichEvent->where, &whichWindow) 
 == inMenuBar)
 || ((whichEvent->what == keyDown) && 
 (whichEvent->modifiers & cmdKey))) {
 /* Re-post event and ignore any error. */
 (void) PostEvent(whichEvent->what, 
 whichEvent->message);
 }
 *whichItem = 1;
 return(true);
 }
 else {
 return(false);
 }
}

 