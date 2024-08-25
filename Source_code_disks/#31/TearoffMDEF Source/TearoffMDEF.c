/*
----------------------------------------------------------------------------------------------------
T E A R O F F   M E N U   D E F I N I T I O N

	version 1.0
	by Don Melton and Mike Ritter
	
	Copyright (C)1987, 1988 by Impulse Technologies, Inc., all rights reserved. 
	
	Filename:			TearOffMDEF.c
	Font:					Monaco, 9 point
	Tab setting:	2
	Compiler:			LightspeedC 2.15, Project type: MDEF, ID: 128, Name: (None)
	
	IMPORTANT! Use ResEdit to set the MDEF resource to non-purgeable.
	
	IMPORTANT! Use ResEdit or FEdit to change hex string '21c809ce' at hex offset 14 in the MDEF
	resource to '4e714e71.' This substitutes two 'nop' instructions for a 'move.l a0,ToolScratch.'

----------------------------------------------------------------------------------------------------
DESCRIPTION

	TearOffMDEF is an MDEF code resource implementing the common actions of tear-off menus for any
	application. It's designed to communicate with an application via a TearOffMenuGlobals structure
	in a TOMG resource. At runtime, TearOffMDEF uses the menuID of the MenuInfo, passed to it by the
	Macintosh ROM, to find a TOMG resource of the same ID. The TearOffMenuGlobals structure contains
	eight elements:
	
		drawMenuProc		A function pointer to a pascal-type procedure which draws the contents of the
										menu in global coordinates within the WMgrPort.
		findItemProc		A function pointer to a pascal-type procedure which returns the number of the
										menu item where the mouse is currently located.
		hiliteItemProc	A function pointer to a pascal-type procedure which hilites or unhilites a
										given menu item.
		environment			A pointer to a SysEnvRec used to test if the 64K ROMs are present.
		paletteWindow		A WindowPtr used to calculate menuWidth, menuHeight, and the structure boundary
										from the window's portRect.
		currentItem			A short int containing the number of the currently hilited menu item.
		position				A Point passed to the application from TearOffMDEF indicating the topLeft point,
										in global coordinates, of a torn-off menu.
		itemHilited			A Boolean used internally by TearOffMDEF.
	
	All of these elements, except position and itemHilited, must be initialized by the application
	before a tear-off menu is inserted into the menu list.
	
	IMPORTANT! The menuProc field of a tear-off MENU resource must equal TearOffMDEF's resource ID.
	
	The application is completely responsible for the appearance of the menu. TearOffMDEF does not
	contain code to draw the contents of a menu, nor does it contain code to hilite menu items. A
	set of the three following procedures must be declared in the application for each tear-off menu:
	
		pascal void DrawMenuProc(destRect)
		Rect *destRect;
		
					destRect	The menu rectangle in the current grafPort.
		
		pascal short FindItemProc(mousePt)
		Point mousePt;
		
					mousePt		The point in which the mouse is currently located, relative to the topLeft of
										the menu rectangle.
										
										The number of the menu item where the mouse is currently located should be
										returned to TearOffMDEF by the application.
		
		pascal void HiliteItemProc(destRect, item, hilite)
		Rect *destRect;
		short item;
		Boolean hilite;
		
					destRect	The menu rectangle in the current grafPort.
					item			The number of the menu item to be hilited or unhilited.
					hilite		A flag indicating the hilite state. Set true to hilite and false to unhilite.
	
	IMPORTANT! The segment in which these procedures are declared must remain locked at runtime.
	
	It's very simple for the application to call these same procedures to draw into the window once
	the user has torn it off.
	
	TearOffMDEF will return -1 to the Menu Manager if a menu has been torn off. It's the
	application's responsibility to move the window into position and make it visible.
	
	Note: TearOffMDEF is not designed to implement pop-up menus. */



/*
----------------------------------------------------------------------------------------------------
INCLUDE DEFINITIONS */

#include "MacTypes.h"
#include "MemoryMgr.h"
#include "MenuMgr.h"
#include "OSUtil.h"
#include "pascal.h"
#include "Quickdraw.h"
#include "ResourceMgr.h"
#include "WindowMgr.h"

/*
----------------------------------------------------------------------------------------------------
GLOBAL CONSTANT DEFINITIONS */

#define nil 0

typedef struct QuickDrawGlobals { 
	char private[76];
	long randSeed;
	BitMap screenBits;
	Cursor arrow;
	Pattern dkGray;
	Pattern ltGray;
	Pattern gray;
	Pattern black;
	Pattern white;
	GrafPtr thePort;
} QuickDrawGlobals;

typedef struct TearOffMenuGlobals {
	void (*drawMenuProc)();
	short (*findItemProc)();
	void (*hiliteItemProc)();
	SysEnvRec *environment;
	WindowPtr paletteWindow;
	Point position;
	short currentItem;
	Boolean itemHilited;
} TearOffMenuGlobals, *TearOffMGlobalsPtr, **TearOffMGlobalsHdl;

#define TEAR_OFF_MENU_GLOBALS_TYPE 'TOMG'

#define TEAR_OFF_MARGIN 15
#define MOVE_PALETTE_ITEM (-1)

#define PALETTE_TITLE_BAR_HEIGHT 10
#define PALETTE_SHADOW_INDENT 3
#define PALETTE_OFFSET 5

/*
----------------------------------------------------------------------------------------------------
GLOBAL VARIABLE DECLARATIONS */

/* None, even though the LightspeedC compiler allows it, others don't. */

/*
----------------------------------------------------------------------------------------------------
EXTERNAL FUNCTION DECLARATIONS */

/* None, they're not allowed. */

/*
----------------------------------------------------------------------------------------------------
FORWARD FUNCTION DECLARATIONS */

pascal void main();
void ChooseItem();
void DragMenu();



/*
----------------------------------------------------------------------------------------------------
TEAROFF MENU DEFINITION

	The main function is called by the Menu Manager in the Macintosh ROM. It's designed to repsond to
	three messages: drawing the menu, choosing an item, and calculating the menu size. It will not
	respond to a pop-up menu request. Before it dispatches to these routines, it first checks to see
	if the TearOffMenuGlobals structure is available on the heap, and locks it down. It does nothing
	if it cannot find this structure.
	
	See 'Inside Macintosh Volume I,' pages 362-363, for more information on this function. */

pascal void main(message, whichMenu, menuRect, hitPt, whichItem)
short message;
MenuHandle whichMenu;
Rect *menuRect;
Point hitPt;
short *whichItem;
{
	TearOffMGlobalsHdl whichTOMGlobalsHdl;
	TearOffMGlobalsPtr tearOffMGlobals;
	
	/* Make sure A5 is valid so the application code can use it's own global variables. */
	SetUpA5();
	
	/* Use the menuID to get a handle to the correct TearOffMenuGlobals structure. */
	whichTOMGlobalsHdl = (TearOffMGlobalsHdl) GetResource(TEAR_OFF_MENU_GLOBALS_TYPE,
			(*whichMenu)->menuID);
	
	if((ResErr == noErr) && (whichTOMGlobalsHdl != nil)) {
		/* Lock the TearOffMenuGlobals structure so it can be dereferenced safely. */
		HLock(whichTOMGlobalsHdl);
		tearOffMGlobals = *whichTOMGlobalsHdl;
	
		/* Dispatch according to the message received from the Macintosh ROM.	Use multiple 'if's
		rather than 'switch' to avoid linking of 400+ bytes of runtime code. */
		
		if(message == mDrawMsg) {
			CallPascal(menuRect, (tearOffMGlobals)->drawMenuProc);
			/* Hilite currentItem here instead of in ChooseItem(). It may not be called immediately. */
			CallPascal(menuRect, (tearOffMGlobals)->currentItem, true,
					(tearOffMGlobals)->hiliteItemProc);
			/* Let ChooseItem() know currentItem has been hilited. */
			(tearOffMGlobals)->itemHilited = true;
		}
		else if(message == mChooseMsg) {
			ChooseItem(tearOffMGlobals, menuRect, hitPt, whichItem);
		}
		else if(message == mSizeMsg) {
			/* Calculate the menuRect from the paletteWindow's portRect. Don't assume that the topLeft of
			the portRect is 0,0. */
			(*whichMenu)->menuWidth
					= ((tearOffMGlobals)->paletteWindow)->portRect.right
					- ((tearOffMGlobals)->paletteWindow)->portRect.left;
			(*whichMenu)->menuHeight
					= ((tearOffMGlobals)->paletteWindow)->portRect.bottom
					- ((tearOffMGlobals)->paletteWindow)->portRect.top;
		}
		HUnlock(whichTOMGlobalsHdl);
	}
	RestoreA5();
}

/*
----------------------------------------------------------------------------------------------------
CHOOSE ITEM

	If the mouse is within the menuRect, ChooseItem() will call the application to find in which item
	the mouse is currently located. The application is also called to hilite or unhilite a single item.
	If the mouse is outside the menuRgn ChooseItem will call DragMenu(). The menuRgn is defined as an
	area made up of the menuRect with a margin and the menu bar. */

void ChooseItem(tearOffMGlobals, menuRect, hitPt, whichItem)
TearOffMGlobalsPtr tearOffMGlobals;
Rect *menuRect;
Point hitPt;
short *whichItem;
{
	short saveItem;
	short hiliteItem;
	Point mousePt;
	Rect marginRect;
	RgnHandle menuRgn;
	RgnHandle tempRgn;
	QuickDrawGlobals *qdGlobals;
	
	/* Set up a pointer to QuickDraw's global variables. */
	qdGlobals = (QuickDrawGlobals *)(*(Byte **)CurrentA5
			- (sizeof(QuickDrawGlobals) - sizeof(GrafPtr)));
	
	saveItem = *whichItem;
	hiliteItem = *whichItem = 0;
	
	/* If the hitPt is empty, the Menu Manager is calling TearOffMDEF repeatedly to flash the item. */
	
	if((hitPt.h != 0) && (hitPt.v != 0)) {
	
		if(PtInRect(hitPt, menuRect)) {
			mousePt.h = hitPt.h - menuRect->left;
			mousePt.v = hitPt.v - menuRect->top;
			
			hiliteItem = *whichItem = CallPascalW(mousePt, (tearOffMGlobals)->findItemProc);
			
			if((tearOffMGlobals)->itemHilited) {
				saveItem = (tearOffMGlobals)->currentItem;
				(tearOffMGlobals)->itemHilited = false;
			}
		}
		else {
		
			if(!(tearOffMGlobals)->itemHilited) {
				hiliteItem = (tearOffMGlobals)->currentItem;
				(tearOffMGlobals)->itemHilited = true;
			}
		}
	}
	if(saveItem != hiliteItem) {
		/* Unhilite the old item. */
		CallPascal(menuRect, saveItem, false, (tearOffMGlobals)->hiliteItemProc);
		/* Hilite the new item. */
		CallPascal(menuRect, hiliteItem, true, (tearOffMGlobals)->hiliteItemProc);
	}
	/* Calculate the menu region. if the mouse is outside this region tear off the menu. */
	marginRect = *menuRect;
	marginRect.left -= TEAR_OFF_MARGIN;
	marginRect.bottom += TEAR_OFF_MARGIN;
	marginRect.right += TEAR_OFF_MARGIN;
	RectRgn(menuRgn = NewRgn(), &marginRect);
	
	RectRgn(tempRgn = NewRgn(), &qdGlobals->screenBits.bounds);
	
	if(tearOffMGlobals->environment->machineType < envMachUnknown) {
		/* Arrggh! Someone has the 64K ROMs. */
		(*tempRgn)->rgnBBox.bottom = 20;
	}
	else {
		(*tempRgn)->rgnBBox.bottom = MBarHeight;
	}
	UnionRgn(menuRgn, tempRgn, menuRgn);
	
	if(!PtInRgn(hitPt, menuRgn)) {
		DragMenu(tearOffMGlobals, hitPt, whichItem, menuRgn, tempRgn, qdGlobals);
	}
	DisposeRgn(tempRgn);
	DisposeRgn(menuRgn);
}

/*
----------------------------------------------------------------------------------------------------
DRAG MENU

	DragMenu() draws an outline of the paletteWindow as the mouse is moved outside the menuRgn. If the
	mouse button is released outside this region, DragMenu() will set whichItem to -1 and exit. */

void DragMenu(tearOffMGlobals, hitPt, whichItem, menuRgn, saveRgn, qdGlobals)
TearOffMGlobalsPtr tearOffMGlobals;
Point hitPt;
short *whichItem;
RgnHandle menuRgn;
RgnHandle saveRgn;
QuickDrawGlobals *qdGlobals;
{
	PenState savePen;
	long finalTicks;
	Rect windowRect;
	RgnHandle structureRgn;
	short hOffset;
	Point oldMouse;
	Point newMouse;
	RgnHandle dragRgn;
	
	GetPenState(&savePen);
	PenSize(1, 1);
	PenMode(notPatXor);
	PenPat(qdGlobals->gray);
	
	/* Since paletteWindow may not be visible, its portRect must be used to calculate structureRgn. */
	/* First, calculate the window frame. */
	windowRect = (tearOffMGlobals->paletteWindow)->portRect;
	
	/* Correct windowRect if the topLeft of the portRect is not 0,0. */
	OffsetRect(&windowRect, -windowRect.left, -windowRect.top);
	
	windowRect.right += 3;
	windowRect.bottom += PALETTE_TITLE_BAR_HEIGHT + 3;
	RectRgn(structureRgn = NewRgn(), &windowRect);
	
	hOffset = windowRect.right / 2;
	
	/* Next, calculate the frame's drop shadow. */
	windowRect.top += PALETTE_SHADOW_INDENT;
	windowRect.left += PALETTE_SHADOW_INDENT;
	windowRect.bottom += 1;
	windowRect.right += 1;
	RectRgn(saveRgn, &windowRect);
	
	/* Combine the frame and the shadow to calculate the structure. */
	UnionRgn(structureRgn, saveRgn, structureRgn);
	
	GetClip(saveRgn);
	SetClip(GrayRgn);
	
	oldMouse = newMouse = hitPt;
	
	CopyRgn(structureRgn, dragRgn = NewRgn());
	OffsetRgn(dragRgn, newMouse.h - hOffset, newMouse.v - PALETTE_OFFSET);
	
	/* Draw first drag outline. */
	FrameRgn(dragRgn);
	
	/* Mimic DragGrayRgn() by staying in a loop until the mouse button is released or the mouse is
	inside the menuRgn again. */
	
	do {
		/* Don't erase old drag outline if the mouse hasn't moved. */
		
		if(!EqualPt(newMouse, oldMouse)) {
			/* Erase old drag outline. */
			FrameRgn(dragRgn);
			
			CopyRgn(structureRgn, dragRgn);
			OffsetRgn(dragRgn, newMouse.h - hOffset, newMouse.v - PALETTE_OFFSET);
			
			/* Draw new drag outline. */
			FrameRgn(dragRgn);
		}
		/* Keep drag outline from flickering. */
		Delay(2, &finalTicks);
		
		oldMouse = newMouse;
		GetMouse(&newMouse);
	}
	while(WaitMouseUp() && !PtInRgn(newMouse, menuRgn));
	
	/* Erase final drag outline. */
	FrameRgn(dragRgn);
	
	if(!PtInRgn(newMouse, menuRgn)) {
		(tearOffMGlobals)->position.h = (*dragRgn)->rgnBBox.left + 1;
		(tearOffMGlobals)->position.v = (*dragRgn)->rgnBBox.top + 11;
		
		/* Tell application the menu was torn off. */
		*whichItem = MOVE_PALETTE_ITEM;
	}
	DisposeRgn(structureRgn);
	DisposeRgn(dragRgn);
	
	SetClip(saveRgn);
	SetPenState(&savePen);
}
