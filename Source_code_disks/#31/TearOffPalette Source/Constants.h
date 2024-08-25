/*
----------T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright, 1987, 1988 by Impulse Technologies,
 Inc., all rights reserved. 
 
 Filename:Constants.h
 Font:  Courier, 9 point
 Tab setting:    2
 Compiler:LightspeedC 2.15
 Project type:   APPL
 Creator: TOPD */

/*
----------------------------------------
INCLUDE DEFINITIONS */

#include "Color.h"
#include "ColorToolbox.h"
#include "ControlMgr.h"
#include "DeskMgr.h"
#include "DialogMgr.h"
#include "EventMgr.h"
#include "FileMgr.h"
#include "FontMgr.h"
#include "MacTypes.h"
#include "MemoryMgr.h"
#include "MenuMgr.h"
#include "OSUtil.h"
#include "PackageMgr.h"
#include "Quickdraw.h"
#include "ResourceMgr.h"
#include "SegmentLdr.h"
#include "StdFilePkg.h"
#include "TextEdit.h"
#include "ToolboxUtil.h"
#include "WindowMgr.h"

/*
--------------------------------------------------------
SYSTEM CONSTANTS */

#define nil 0
#define NULL 0
#define zoomDocProc 8
#define zoomNoGrow 12

/*
--------------------------------------------------------
ENVIRONMENT */

#define VERSION_REQUESTED 1

#define WAIT_NEXT_EVENT_TRAP_NUMBER 0x60
#define UNIMPLEMENTED_TRAP_NUMBER 0x9f

/*
--------------------------------------------------------
MEMORY */

#define MEMORY_BUFFER_SIZE 0x8000 /* 32K. */

/*
--------------------------------------------------------
EVENTS */

#define SLEEP_DURATION 50

/*
--------------------------------------------------------
WINDOWS */

#define VISIBLE true
#define NOT_VISIBLE false
#define BRING_TO_FRONT (WindowPtr) -1
#define SEND_BEHIND nil
#define GO_AWAY_BOX true
#define NO_GO_AWAY_BOX false
#define NO_REFCON nil

/*
--------------------------------------------------------
PALETTES */

enum {
 TOOL_PALETTE,
 PATTERN_PALETTE,
 COLOR_PALETTE,
 DOCUMENT_WINDOW
};

#define PALETTE_COUNT 3

#define PALETTE_WDEF_ID 128
#define TEAROFF_MDEF_ID 128

/*
--------------------------------------------------------
TEAROFF MENU GLOBALS */

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

/*
--------------------------------------------------------
TOOL PALETTE */

#define TOOLS_ACROSS 4
#define TOOLS_DOWN 4
#define TOOL_COUNT ((TOOLS_ACROSS * TOOLS_DOWN) + 1)
#define DEFAULT_TOOL 4
#define TOOL_PICT_ID 128

/*
--------------------------------------------------------
PATTERN PALETTE */

#define PATTERNS_ACROSS 8
#define PATTERNS_DOWN 8

#define PATTERN_COUNT ((PATTERNS_ACROSS 
 * PATTERNS_DOWN) + 1)

#define PATTERN_ITEM_WIDTH 16
#define PATTERN_ITEM_HEIGHT 16

#define DEFAULT_PATTERN 1
#define PATTERNS_ID 128

/*
--------------------------------------------------------
COLOR PALETTE */

#define COLORS_ACROSS 16
#define COLORS_DOWN 16
#define COLOR_COUNT ((COLORS_ACROSS * COLORS_DOWN) + 1)
#define COLOR_ITEM_WIDTH 8
#define COLOR_ITEM_HEIGHT 8
#define DEFAULT_COLOR 1

/*
--------------------------------------------------------
DOCUMENTS */


#define TITLE_BAR_HEIGHT 18
#define SCROLL_BAR_SIZE 16
#define SCREEN_MARGIN 4
#define MIN_WINDOW_WIDTH 80
#define MIN_WINDOW_HEIGHT 80
#define HORIZONTAL_WINDOW_OFFSET 8
#define VERTICAL_WINDOW_OFFSET 8
#define DOCUMENT_COUNT 8
#define DOCUMENT_TITLE_STRING_ID 128

/*
--------------------------------------------------------
MENUS */

enum {
 APPLE_MENU_INDEX,
 FILE_MENU_INDEX,
 EDIT_MENU_INDEX,
 TOOL_MENU_INDEX,
 PATTERN_MENU_INDEX,
 COLOR_MENU_INDEX
};

enum {
 APPLE_MENU_ID = 128,
 FILE_MENU_ID,
 EDIT_MENU_ID,
 TOOL_MENU_ID,
 PATTERN_MENU_ID,
 COLOR_MENU_ID
};

#define MENU_COUNT 6
#define MENU_ID_OFFSET APPLE_MENU_ID

#define TEAR_OFF_MARGIN 15
#define MOVE_PALETTE_ITEM (-1)

/*
--------------------------------------------------------
APPLE MENU ITEMS */

#define ABOUT_ITEM 1

/*
--------------------------------------------------------
EDIT MENU ITEMS */

enum {
 UNDO_ITEM = 1,
 CUT_ITEM = 3,
 COPY_ITEM,
 PASTE_ITEM,
 CLEAR_ITEM
};

/*
--------------------------------------------------------
FILE MENU ITEMS */

enum {
 NEW_ITEM = 1,
 CLOSE_ITEM = 3,
 QUIT_ITEM = 5
};

/*
--------------------------------------------------------
ABOUT DIALOG */

#define ABOUT_DIALOG_ID 128


