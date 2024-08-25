
/*
--------------------------------------------------------
T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright (C)1987, 1988 by Impulse Technologies,
 Inc., all rights reserved. 
 
 Filename:Variables.h
 Font:  Courier, 9 point
 Tab setting:    2
 Compiler:LightspeedC 2.15
 Project type:   APPL
 Creator: TOPD */



/*
--------------------------------------------------------
GLOBAL VARIABLE DECLARATIONS */

#ifdef GLOBAL_VARIABLES

SysEnvRec Environment;
EventRecord Event;

GDHandle MaxDevice;

MenuHandle Menus[MENU_COUNT];

TearOffMGlobalsHdl TearOffs[PALETTE_COUNT];
WindowPtr Palettes[PALETTE_COUNT];

WindowPtr TopWindow;
WindowPtr TopPalette;
WindowPtr BottomPalette;
WindowPtr TopDocument;

Rect ToolRects[TOOL_COUNT];
Rect PatternRects[PATTERN_COUNT];
Rect ColorRects[COLOR_COUNT];

short PositionCounter;

long Sleep;

Boolean ClosingAll;
Boolean Quitting;
Boolean Finished;

Boolean OutOfMemory;
Boolean WNEIsImplemented;
Boolean MouseInMenu;

Boolean ColorMenuVisible;
Boolean PalettesVisible[PALETTE_COUNT];

Handle MemoryBuffer;

#else

extern SysEnvRec Environment;
extern EventRecord Event;

extern GDHandle MaxDevice;

extern MenuHandle Menus[MENU_COUNT];

extern TearOffMGlobalsHdl TearOffs[PALETTE_COUNT];
extern WindowPtr Palettes[PALETTE_COUNT];

extern WindowPtr TopWindow;
extern WindowPtr TopPalette;
extern WindowPtr BottomPalette;
extern WindowPtr TopDocument;

extern Rect ToolRects[TOOL_COUNT];
extern Rect PatternRects[PATTERN_COUNT];
extern Rect ColorRects[COLOR_COUNT];

extern short PositionCounter;

extern long Sleep;

extern Boolean ClosingAll;
extern Boolean Quitting;
extern Boolean Finished;

extern Boolean OutOfMemory;

extern Boolean OutOfMemory;
extern Boolean WNEIsImplemented;
extern Boolean MouseInMenu;

extern Boolean ColorMenuVisible;
extern Boolean PalettesVisible[PALETTE_COUNT];

extern Handle MemoryBuffer;

#endif


