
/*
--------------------------------------------------------
T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright (C)1987, 1988 by Impulse Technologies, 
 Inc., all rights reserved. 
 
 Filename:Initialize.c
 Font:  Courier, 9 point
 Tab setting:    2
 Compiler:LightspeedC 2.15
 Project type:   APPL
 Creator: TOPD
 Segment: Initialize
 
 IMPORTANT! Use ResEdit to set the code resource of this segment to unlocked. 
*/

/*
--------------------------------------------------------GLOBAL CONSTANT 
DEFINITIONS AND VARIABLE DECLARATIONS */

#include "Constants.h"
#include "Variables.h"

/*
--------------------------------------------------------
EXTERNAL FUNCTION DECLARATIONS */

extern short GoodNewPtr();  /* Error.c */
extern short GoodNewHandle(); /* Error.c */
extern short GoodResource();/* Error.c */
extern pascal long RecoverMemory();/* Error.c */

extern pascal void DrawToolMenu(); /* Menu.c */
extern pascal short FindToolItem();/* Menu.c */
extern pascal void HiliteToolItem(); /* Menu.c */
extern pascal void DrawPatternMenu();/* Menu.c */
extern pascal short FindPatternItem(); /* Menu.c */
extern pascal void HilitePatternItem();/* Menu.c */
extern pascal void DrawColorMenu();/* Menu.c */
extern pascal short FindColorItem(); /* Menu.c */
extern pascal void HiliteColorItem();/* Menu.c */

/*
--------------------------------------------------------
FORWARD FUNCTION DECLARATIONS */

void Initialize();

void SetupEnvironment();
void SetupMemory();

void SetupPalettes();
void SetupToolPalette();
void SetupPatternPalette();
void SetupColorPalette();
void SetupPaletteRects();

void SetupMenus();



/*
--------------------------------------------------------
INITIALIZE */

void Initialize() {

 InitGraf(&thePort);
 InitFonts();
 InitWindows();
 InitMenus();
 TEInit();
 InitDialogs(nil);
 InitCursor();
 
 FlushEvents(everyEvent, 0);
 
 SetupEnvironment();
 SetupMemory();
 SetupPalettes();
 SetupMenus();

 TopWindow = TopPalette = TopDocument = nil;
 BottomPalette = BRING_TO_FRONT;
 
 PositionCounter = 0;
 
 Sleep = SLEEP_DURATION;
 
 ClosingAll = Quitting = Finished = false;
}

/*
--------------------------------------------------------
SETUP ENVIRONMENT */

void SetupEnvironment() {

 if(SysEnvirons(VERSION_REQUESTED, &Environment)
  == envBadSel) {
 ExitToShell();
 }
 if(Environment.machineType >= envMachUnknown) {
 WNEIsImplemented =
 NGetTrapAddress 
 (WAIT_NEXT_EVENT_TRAP_NUMBER,ToolTrap)
 != NGetTrapAddress  
 (UNIMPLEMENTED_TRAP_NUMBER, ToolTrap);
 }
 else {
 WNEIsImplemented = false;
 }
}

/*
--------------------------------------------------------
SETUP MEMORY */

void SetupMemory() {

 MaxApplZone();
 
 MoreMasters();
 MoreMasters();
 
 if(!GoodNewHandle(MemoryBuffer = 
 NewHandle(MEMORY_BUFFER_SIZE))) {
 ExitToShell();
 }
 OutOfMemory = false;
 
 /* Setup a simple grow zone function. */
 SetGrowZone(RecoverMemory);
}

/*
--------------------------------------------------------SETUP PALETTES 
*/

void SetupPalettes() {
 short index;
 TearOffMGlobalsPtr whichTearOff;
 Rect windowRects[PALETTE_COUNT];
 short attributes;
 
 for(index = 0; index < PALETTE_COUNT; index++) {
 
 /* Get a handle to TearOffMenuGlobals. */
 if(!GoodResource(TearOffs[index]
 = (TearOffMGlobalsHdl)
 GetResource(TEAR_OFF_MENU_GLOBALS_TYPE,
 TOOL_MENU_ID + index))) {
 ExitToShell();
 }
 MoveHHi(TearOffs[index]);
 HLock(TearOffs[index]);
 whichTearOff = *TearOffs[index];
 
 switch(index) {
 
 case TOOL_PALETTE:
 SetupToolPalette(whichTearOff, 
 &windowRects[index]);
 break;
 
 case PATTERN_PALETTE:
 SetupPatternPalette(whichTearOff, 
 &windowRects[index]);
 break;
 
 case COLOR_PALETTE:
 SetupColorPalette(whichTearOff, 
 &windowRects[index]);
 }
 if(Environment.hasColorQD) {
 /* Create a color port. */
 if(!GoodNewPtr(Palettes[index]
 = NewCWindow(nil,
 &windowRects[index],
 NULL,
 NOT_VISIBLE,
 /* Set procedure ID based on 
 PaletteWDEF resource ID. */
 (16 * PALETTE_WDEF_ID)
 + noGrowDocProc,
 BRING_TO_FRONT,
 GO_AWAY_BOX,
 (long) index))) {
 ExitToShell();
 }
 }
 else {
 /* Create an old-style port. */
 if(!GoodNewPtr(Palettes[index]
 = NewWindow(nil,
 &windowRects[index],
 NULL,
 NOT_VISIBLE,
 /* Set procedure ID based on 
 PaletteWDEF resource ID. */
 (16 * PALETTE_WDEF_ID)
 + noGrowDocProc,
 BRING_TO_FRONT,
 GO_AWAY_BOX,
 (long) index))) {
 ExitToShell();
 }
 }
 /* Finish Initializing TearOffMenuGlobals 
 structure. */
 whichTearOff->environment = &Environment;
 whichTearOff->paletteWindow = Palettes[index];
 
 HUnlock(TearOffs[index]);
 }
}

/*
--------------------------------------------------------
SETUP TOOL PALETTE */

void SetupToolPalette(whichTearOff, windowRect)
TearOffMGlobalsPtr whichTearOff;
Rect *windowRect;
{
 PicHandle toolPicture;
 
 if(!GoodResource(toolPicture = 
 GetPicture(TOOL_PICT_ID))) {
 ExitToShell();
 }
 HNoPurge(toolPicture);
 
 /* Calculate palette's portRect from toolPicture. */
 *windowRect = (*toolPicture)->picFrame;
 OffsetRect(windowRect, -windowRect->left, 
 -windowRect->top);
 
 SetupPaletteRects(&ToolRects,
 TOOLS_ACROSS,
 TOOLS_DOWN,
 (windowRect->right + 1) / TOOLS_ACROSS,
 (windowRect->bottom + 1) / TOOLS_DOWN);
 
 /* Initialize the TearOffMenuGlobals structure. */
 whichTearOff->currentItem = DEFAULT_TOOL;
 whichTearOff->drawMenuProc = DrawToolMenu;
 whichTearOff->findItemProc = FindToolItem;
 whichTearOff->hiliteItemProc = HiliteToolItem;
}

/*
--------------------------------------------------------
SETUP PATTERN PALETTE */

void SetupPatternPalette(whichTearOff, windowRect)
TearOffMGlobalsPtr whichTearOff;
Rect *windowRect;
{
/* Calculate the portRect from number of patterns. */
 windowRect->left = 0;
 windowRect->top = 0;
 windowRect->right = (PATTERNS_ACROSS
 * (PATTERN_ITEM_WIDTH + 1)) + 1;
 windowRect->bottom = (PATTERNS_DOWN 
 * (PATTERN_ITEM_HEIGHT + 1)) + 1;
 
 SetupPaletteRects(&PatternRects,
 PATTERNS_ACROSS,
 PATTERNS_DOWN,
 PATTERN_ITEM_WIDTH + 1,
 PATTERN_ITEM_HEIGHT + 1);
 
 /* Initialize the TearOffMenuGlobals structure. */
 whichTearOff->currentItem = DEFAULT_PATTERN;
 whichTearOff->drawMenuProc = DrawPatternMenu;
 whichTearOff->findItemProc = FindPatternItem;
 whichTearOff->hiliteItemProc = HilitePatternItem;
}

/*
--------------------------------------------------------
SETUP COLOR PALETTE */

void SetupColorPalette(whichTearOff, windowRect)
TearOffMGlobalsPtr whichTearOff;
Rect *windowRect;
{
/* Calculate the portRect from the number of colors. */
 windowRect->left = 0;
 windowRect->top = 0;
 windowRect->right = (COLORS_ACROSS 
 * (COLOR_ITEM_WIDTH + 1)) + 1;
 windowRect->bottom = (COLORS_DOWN 
 * (COLOR_ITEM_HEIGHT + 1)) + 1;
 
 SetupPaletteRects(&ColorRects,
 COLORS_ACROSS,
 COLORS_DOWN,
 COLOR_ITEM_WIDTH + 1,
 COLOR_ITEM_HEIGHT + 1);
 
 /* Initialize the TearOffMenuGlobals structure. */
 whichTearOff->currentItem = DEFAULT_COLOR;
 whichTearOff->drawMenuProc = DrawColorMenu;
 whichTearOff->findItemProc = FindColorItem;
 whichTearOff->hiliteItemProc = HiliteColorItem;
}

/*
--------------------------------------------------------
SETUP PALETTE RECTS */

void SetupPaletteRects(whichRects, itemsAcross, 
 itemsDown, itemWidth, itemHeight)
Rect *whichRects;
short itemsAcross;
short itemsDown;
short itemWidth;
short itemHeight;
{
 short index;
 short across;
 short down;
 
 whichRects->left = 0;
 whichRects->top = 0;
 whichRects->right = 0;
 whichRects->bottom = 0;
 
 index = 1;
 
 for(down = 0; down < itemsDown; down++) {
 
 for(across = 0; 
 across < itemsAcross; across++) {
 (whichRects + index)->left 
 = across * itemWidth;
 (whichRects + index)->top 
 = down * itemHeight;
 (whichRects + index)->right 
 = (across + 1) * itemWidth;
 (whichRects + index)->bottom 
 = (down + 1) * itemHeight;
 index += 1;
 }
 }
}

/*
--------------------------------------------------------
SETUP MENUS */

void SetupMenus() {
 short index;
 
 for(index = APPLE_MENU_INDEX; 
 index < MENU_COUNT - 1; index++) {
 Menus[index] = GetMenu(index + MENU_ID_OFFSET);
 InsertMenu(Menus[index], 0);
 }
 AddResMenu(Menus[APPLE_MENU_INDEX], 'DRVR');
 
 ColorMenuVisible = false;
 
 if(Environment.hasColorQD) {
 MaxDevice = GetMaxDevice(&(*GrayRgn)->rgnBBox);
 
 Menus[COLOR_MENU_INDEX] =GetMenu(COLOR_MENU_ID);
 
 if((*(*MaxDevice)->gdPMap)->pixelSize == 8) {
 /* Insert Color menu if 256 colors. */
 InsertMenu(Menus[COLOR_MENU_INDEX], 0);
 ColorMenuVisible = true;
 }
 }
 DrawMenuBar();
}

