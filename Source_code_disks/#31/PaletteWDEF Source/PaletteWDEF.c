/*
----------------------------------------------------------------------------------------------------
P A L E T T E   W I N D O W   D E F I N I T I O N

	version 1.0
	by Don Melton and Mike Ritter
	
	Copyright (C)1987, 1988 by Impulse Technologies, Inc., all rights reserved. 
	
	Filename:			PaletteWDEF.c
	Font:					Monaco, 9 point
	Tab setting:	2
	Compiler:			LightspeedC 2.15, Project type: WDEF, ID: 128, Name: (None)
	
	IMPORTANT! Use ResEdit to set the WDEF resource to non-purgeable.

----------------------------------------------------------------------------------------------------
DESCRIPTION

	PaletteWDEF is a WDEF code resource designed to display windows that mimic the appearance of
	tear-off palettes in HyperCard. However, PaletteWDEF will unhilite a title bar, and PaletteWDEF
	windows have a 3 pixel indented drop shadow just like a menu.
	
	To use PaletteWDEF, an application must calculate the procedure ID of the window to be created, at
	runtime or store it in a WIND or DLOG resource. With PaletteWDEF's resource ID being 128, the
	folllowing code will create a new palette window:
	
	w = NewWindow(p, bounds, title, visible, (16 * 128) + noGrowDocProc, behind, goAwayFlag, refCon);
	
	See 'Inside Macintosh Volume I,' page 298, for more information on calculating the procedure ID.
	
	Note: Although NewCWindow() or GetNewCWindow() can be used with PaletteWDEF, it does not support
	the use of wctb resources for color information, or respond visibly to SetWinColor().
	
	Note: PaletteWDEF will not draw a grow region or zoom box in a window. It completely ignores any
	and all variation codes passed to it. */



/*
----------------------------------------------------------------------------------------------------
INCLUDE DEFINITIONS */

#include "MacTypes.h"
#include "MemoryMgr.h"
#include "Quickdraw.h"
#include "WindowMgr.h"

/*
----------------------------------------------------------------------------------------------------
GLOBAL CONSTANT DEFINITIONS */

typedef struct QuickDraw {
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
} QuickDraw;

#define PALETTE_TITLE_BAR_HEIGHT 10
#define PALETTE_SHADOW_INDENT 3

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

pascal long main();
void DrawWindow();
long TestWindowHit();
void CalcWindowRegions();



/*
----------------------------------------------------------------------------------------------------
PALETTE WINDOW DEFINITION

	The main function is called by the Window Manager in the Macintosh ROM. It's designed to repsond
	to three messages: drawing the window, testing which part of the window has been hit, and
	calculating the various window regions.
	
	See 'Inside Macintosh Volume I,' pages 297-302, for more information on this function. */

pascal long main(variation, whichWindow, message, parameter)
short variation;
WindowPtr whichWindow;
short message;
long parameter;
{
	long result;
	
	result = 0;
	
	/* Use multiple 'if's rather than 'switch' to avoid linking of 400+ bytes of runtime code. */
	
	if(message == wDraw) {
		DrawWindow(whichWindow, parameter);
	}
	else if(message == wHit) {
		result = TestWindowHit(whichWindow, parameter);
	}
	else if(message == wCalcRgns) {
		CalcWindowRegions(whichWindow);
	}
	return(result);
}

/*
----------------------------------------------------------------------------------------------------
DRAW WINDOW */

void DrawWindow(whichWindow, parameter)
WindowPtr whichWindow;
long parameter;
{
	Rect frame;
	Rect goAway;
	PenState savePen;
	short tone;
	short index;
	Pattern hilite;
	QuickDraw *qdGlobals;
	
	/* Set up a pointer to QuickDraw's global variables. */
	qdGlobals = (QuickDraw *)(*(Byte **)CurrentA5
			- (sizeof(QuickDraw) - sizeof(GrafPtr)));
	
	if(((WindowPeek) whichWindow)->visible) {
		/* Calculate the window frame. */
		frame = (*((WindowPeek) whichWindow)->strucRgn)->rgnBBox;
		frame.bottom -= 1;
		frame.right -= 1;
		
		/* Calculate the goAway box. */
		goAway = frame;
		goAway.top += 2;
		goAway.left += 8;
		goAway.bottom = goAway.top + 7;
		goAway.right = goAway.left + 7;
		
		if(parameter != 0) {
			/* Hilite the goAway box. */
			InvertRect(&goAway);
		}
		else {
			/* Draw the window frame, drop shadow, title bar and goAway box. */
			GetPenState(&savePen);
			PenNormal();
			
			/* Draw the frame. */
			FrameRect(&frame);
			
			/* Draw the drop shadow. */
			MoveTo(frame.left + PALETTE_SHADOW_INDENT, frame.bottom);
			LineTo(frame.right, frame.bottom);
			LineTo(frame.right, frame.top + PALETTE_SHADOW_INDENT);
			
			/* Calculate and draw the title bar. */
			frame.bottom = frame.top + (PALETTE_TITLE_BAR_HEIGHT + 1);
			FrameRect(&frame);
			InsetRect(&frame, 1, 1);
			
			if(((WindowPeek) whichWindow)->hilited) {
				/* Adjust pattern and fill title bar. */
				tone = frame.left & 1 ? 0x55 : 0xaa;
				
				for(index = 0; index <= 7; index++) {
					hilite[index] = (index + frame.top) & 1 ? tone : 0;
				}
				FillRect(&frame, &hilite);
				
				/* Draw the goAway box. */
				frame = goAway;
				InsetRect(&frame, -1, -1);
				EraseRect(&frame);
				FrameRect(&goAway);
			}
			else {
				FillRect(&frame, qdGlobals->white);
			}
			SetPenState(&savePen);
		}
	}
}

/*
----------------------------------------------------------------------------------------------------
TEST WINDOW HIT */

long TestWindowHit(whichWindow, parameter)
WindowPtr whichWindow;
long parameter;
{
	Point where;
	Rect drag;
	Rect goAway;
	
	where.v = parameter >> 16; /* HiWord(parameter). */
	where.h = parameter & 0xFFFF; /* LoWord(parameter). */
	
	if(PtInRect(where, &(*((WindowPeek) whichWindow)->contRgn)->rgnBBox)) {
		return(wInContent);
	}
	else {
		/* The mouse is in the window frame. */
		drag = (*((WindowPeek) whichWindow)->strucRgn)->rgnBBox;
		drag.bottom = drag.top + (PALETTE_TITLE_BAR_HEIGHT + 1);
		drag.right -= 1;
		
		if(PtInRect(where, &drag)) {
			goAway = drag;
			goAway.top += 2;
			goAway.left += 8;
			goAway.bottom = goAway.top + 7;
			goAway.right = goAway.left + 7;
			
			if((((WindowPeek) whichWindow)->hilited) && (PtInRect(where, &goAway))) {
				return(wInGoAway);
			}
			return(wInDrag);
		}
	}
	return(wNoHit);
}

/*
----------------------------------------------------------------------------------------------------
CALCULATE WINDOW REGIONS */

void CalcWindowRegions(whichWindow)
WindowPtr whichWindow;
{
	Rect windowRect;
	RgnHandle shadowRgn;
	
	/* Calculate the content region of the window. */
	windowRect = whichWindow->portRect;
	OffsetRect(&windowRect, - whichWindow->portBits.bounds.left, - whichWindow->portBits.bounds.top);
	RectRgn(((WindowPeek) whichWindow)->contRgn, &windowRect);
	
	/* Calculate the structure region of the window. */
	/* First, calculate the window frame. */
	windowRect.top -= PALETTE_TITLE_BAR_HEIGHT + 1;
	windowRect.left -= 1;
	windowRect.bottom += 1;
	windowRect.right += 1;
	RectRgn(((WindowPeek) whichWindow)->strucRgn, &windowRect);
	
	/* Next, calculate the frame's drop shadow. */
	windowRect.top += PALETTE_SHADOW_INDENT;
	windowRect.left += PALETTE_SHADOW_INDENT;
	windowRect.bottom += 1;
	windowRect.right += 1;
	RectRgn(shadowRgn = NewRgn(), &windowRect);
	
	/* Combine the frame and the shadow to calculate the structure. */
	UnionRgn(((WindowPeek) whichWindow)->strucRgn, shadowRgn, ((WindowPeek) whichWindow)->strucRgn);
			
	DisposeRgn(shadowRgn);
}
