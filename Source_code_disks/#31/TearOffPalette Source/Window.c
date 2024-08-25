/*
----------------------------------------------------------------------------------------------------
T E A R O F F   P A L E T T E

	version 1.0
	by Don Melton and Mike Ritter
	
	Copyright (C)1987, 1988 by Impulse Technologies, Inc., all rights reserved. 
	
	Filename:			Window.c
	Font:					Monaco, 9 point
	Tab setting:	2
	Compiler:			LightspeedC 2.15, Project type: APPL, Creator: TOPD
	Segment:			Main */



/*
----------------------------------------------------------------------------------------------------
GLOBAL CONSTANT DEFINITIONS AND VARIABLE DECLARATIONS */

#include "Constants.h"
#include "Variables.h"

/*
----------------------------------------------------------------------------------------------------
EXTERNAL FUNCTION DECLARATIONS */

extern short GoodNewPtr();									/* Error.c */
extern short GoodResource();								/* Error.c */
extern short GetMenuBarHeight();						/* Interface.c */
extern pascal void DrawToolMenu();					/* Menu.c */
extern pascal void HiliteToolItem();				/* Menu.c */
extern pascal void DrawPatternMenu();				/* Menu.c */
extern pascal void HilitePatternItem();			/* Menu.c */
extern pascal void DrawColorMenu();					/* Menu.c */
extern pascal void HiliteColorItem();				/* Menu.c */

/*
----------------------------------------------------------------------------------------------------
FORWARD FUNCTION DECLARATIONS */

void NewDocument();
Rect *GetDocumentRect();
short NewScrollBars();
Rect *GetHScrollBarRect();
Rect *GetVScrollBarRect();
void CloseDocument();
void ActivateDocument();
void UpdateDocument();
void SizeDocument();
void MoveSizeScrollBar();
void UpdatePalette();



/*
----------------------------------------------------------------------------------------------------
NEW DOCUMENT */

void NewDocument() {
	StringHandle title;
	WindowPtr theDocument;
	Rect windowRect;
	
	if(!GoodResource(title = GetString(DOCUMENT_TITLE_STRING_ID))) {
		return;
	}
	HLock(title);
	
	if(!GoodNewPtr(theDocument = NewWindow(nil,
			GetDocumentRect(&windowRect),
			*title,
			NOT_VISIBLE,
			zoomDocProc,
			BottomPalette,
			GO_AWAY_BOX,
			DOCUMENT_WINDOW))) {
		HUnlock(title);
		
		return;
	}
	if(!NewScrollBars(theDocument)) {
		CloseDocument(theDocument);
		PositionCounter += 1;
		HUnlock(title);
		
		return;
	}
	PositionCounter += 1;
	HUnlock(title);
	
	if(TopPalette != nil) {
	
		if(TopPalette != TopWindow) {
			/* Bring the TopPalette to the front and generate activate event. */
			SelectWindow(TopPalette);
		}
		else {
			HiliteWindow(theDocument, true);
		}
		if(TopDocument != nil) {
			/* Ensure the TopDocument and its controls are unhilited properly. */
			ActivateDocument(TopDocument, false);
		}
	}
	ShowWindow(theDocument);
}

/*
----------------------------------------------------------------------------------------------------
GET DOCUMENT RECT */

Rect *GetDocumentRect(windowRect)
Rect *windowRect;
{
	short position;
	
	position = (PositionCounter + DOCUMENT_COUNT) % DOCUMENT_COUNT;
	
	windowRect->left = SCREEN_MARGIN
			+ (HORIZONTAL_WINDOW_OFFSET * position);
	windowRect->top = GetMenuBarHeight() + TITLE_BAR_HEIGHT + SCREEN_MARGIN
			+ (VERTICAL_WINDOW_OFFSET * position);
	windowRect->right = screenBits.bounds.right - SCREEN_MARGIN
			- (((DOCUMENT_COUNT - 1) - position) * HORIZONTAL_WINDOW_OFFSET);
	windowRect->bottom = screenBits.bounds.bottom - SCREEN_MARGIN
			- (((DOCUMENT_COUNT - 1) - position) * VERTICAL_WINDOW_OFFSET);
	
	return(windowRect);
}

/*
----------------------------------------------------------------------------------------------------
NEW SCROLL BARS */

short NewScrollBars(whichWindow)
WindowPtr whichWindow;
{
	Rect sBRect;
	
	if(GoodNewHandle(NewControl(whichWindow,
			GetHScrollBarRect(whichWindow, &sBRect),
			NULL,
			VISIBLE,
			0, 0, 255,
			scrollBarProc,
			NO_REFCON))) {
		
		if(GoodNewHandle(NewControl(whichWindow,
			GetVScrollBarRect(whichWindow, &sBRect),
				NULL,
				VISIBLE,
				0, 0, 255,
				scrollBarProc,
				NO_REFCON))) {
			return(true);
		}
	}
	return(false);
}

/*
----------------------------------------------------------------------------------------------------
GET HORIZONTAL SCROLL BAR RECTANGLE */

Rect *GetHScrollBarRect(whichWindow, whichRect)
WindowPtr whichWindow;
Rect *whichRect;
{
	*whichRect = whichWindow->portRect;
	
	whichRect->left -= 1;
	whichRect->top = whichRect->bottom - (SCROLL_BAR_SIZE - 1);
	whichRect->right -= (SCROLL_BAR_SIZE - 2);
	whichRect->bottom += 1;
	
	return(whichRect);
}

/*
----------------------------------------------------------------------------------------------------
GET VERTICAL SCROLL BAR RECTANGLE */

Rect *GetVScrollBarRect(whichWindow, whichRect)
WindowPtr whichWindow;
Rect *whichRect;
{
	*whichRect = whichWindow->portRect;
	
	whichRect->left = whichRect->right - (SCROLL_BAR_SIZE - 1);
	whichRect->top -= 1;
	whichRect->right += 1;
	whichRect->bottom -= (SCROLL_BAR_SIZE - 2);
	
	return(whichRect);
}

/*
----------------------------------------------------------------------------------------------------
CLOSE DOCUMENT

	A REAL application would need a more complex CloseDocument() function. This is just a shell. */

void CloseDocument(whichWindow)
WindowPtr whichWindow;
{
	DisposeWindow(whichWindow);
	
	PositionCounter -= 1;
}

/*
----------------------------------------------------------------------------------------------------
ACTIVATE DOCUMENT */

void ActivateDocument(whichWindow, activate)
WindowPtr whichWindow;
Boolean activate;
{
	HiliteWindow(whichWindow, activate);
	
	if(activate) {
		ShowControl(((WindowPeek) whichWindow)->controlList);
		ShowControl((*((WindowPeek) whichWindow)->controlList)->nextControl);
	}
	else {
		SetPort(whichWindow);
		HideControl(((WindowPeek) whichWindow)->controlList);
		ValidRect(&(*((WindowPeek) whichWindow)->controlList)->contrlRect);
		HideControl((*((WindowPeek) whichWindow)->controlList)->nextControl);
		ValidRect(&(*(*((WindowPeek) whichWindow)->controlList)->nextControl)->contrlRect);
	}
	DrawGrowIcon(whichWindow);
}

/*
----------------------------------------------------------------------------------------------------
UPDATE DOCUMENT

	A REAL application would need a more complex UpdateDocument() function. This is just a shell. */

void UpdateDocument(whichDocument)
WindowPtr whichDocument;
{
	EraseRect(&whichDocument->portRect);
}

/*
----------------------------------------------------------------------------------------------------
SIZE DOCUMENT */

void SizeDocument(whichDocument)
WindowPtr whichDocument;
{
	Rect sBRect;
	
	MoveSizeScrollBar(((WindowPeek) whichDocument)->controlList,
			GetHScrollBarRect(whichDocument, &sBRect));
	MoveSizeScrollBar((*((WindowPeek) whichDocument)->controlList)->nextControl,
			GetVScrollBarRect(whichDocument, &sBRect));
	
	BeginUpdate(whichDocument);
	UpdateDocument(whichDocument);
	EndUpdate(whichDocument);
	
	ShowControl(((WindowPeek) whichDocument)->controlList);
	ShowControl((*((WindowPeek) whichDocument)->controlList)->nextControl);
	
	DrawGrowIcon(whichDocument);
}

/*
----------------------------------------------------------------------------------------------------
MOVE AND SIZE SCROLL BAR */

void MoveSizeScrollBar(whichScrollBar, sBRect)
ControlHandle whichScrollBar;
Rect *sBRect;
{
	HideControl(whichScrollBar);
	
	MoveControl(whichScrollBar, sBRect->left, sBRect->top);
	SizeControl(whichScrollBar, sBRect->right - sBRect->left, sBRect->bottom - sBRect->top);
}

/*
----------------------------------------------------------------------------------------------------
UPDATE PALETTE */

void UpdatePalette(whichPalette)
WindowPtr whichPalette;
{
	/* Use the palette's refCon to determine which palette needs updating. */
	switch(((WindowPeek) whichPalette)->refCon) {
	
		case TOOL_PALETTE:
			DrawToolMenu(&whichPalette->portRect);
			HiliteToolItem(&whichPalette->portRect, (*TearOffs[TOOL_PALETTE])->currentItem, true);
			break;
			
		case PATTERN_PALETTE:
			DrawPatternMenu(&whichPalette->portRect);
			HilitePatternItem(&whichPalette->portRect, (*TearOffs[PATTERN_PALETTE])->currentItem, true);
			break;
			
		case COLOR_PALETTE:
			DrawColorMenu(&whichPalette->portRect);
			HiliteColorItem(&whichPalette->portRect, (*TearOffs[COLOR_PALETTE])->currentItem, true);
	}
}
