
/*
--------------------------------------------------------
T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright (C)1987, 1988 by Impulse Technologies, 
 Inc., all rights reserved. 
 
 Filename:Menu.c
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

/* None */

/*
--------------------------------------------------------FORWARD FUNCTION 
DECLARATIONS */

pascal void DrawToolMenu();
pascal short FindToolItem();
pascal void HiliteToolItem();

pascal void DrawPatternMenu();
pascal short FindPatternItem();
pascal void HilitePatternItem();

pascal void DrawColorMenu();
pascal short FindColorItem();
pascal void HiliteColorItem();

void MovePalette();



/*
----------------------------------------------
DRAW TOOLS */

pascal void DrawToolMenu(destRect)
Rect *destRect;
{
 DrawPicture(GetPicture(TOOL_PICT_ID), destRect);
}

/*
----------------------------
DRAW PATTERNS */

pascal void DrawPatternMenu(destRect)
Rect *destRect;
{
 short index;
 Rect drawRect;
 Pattern thePattern;
 
 if(MouseInMenu) {
 EraseRect(destRect);
 }
 for(index = 1; index < PATTERN_COUNT; index++) {
 drawRect = PatternRects[index];
 drawRect.top += 1;
 drawRect.left += 1;
 OffsetRect(&drawRect, destRect->left, 
 destRect->top);
 
 GetIndPattern(&thePattern, PATTERNS_ID, index);
 FillRect(&drawRect, &thePattern);
 }
}

/*
----------------------------
DRAW COLORS */

pascal void DrawColorMenu(destRect)
Rect *destRect;
{
 CTabPtr colorTable;
 RGBColor saveColor;
 short index;
 Rect drawRect;
 
 if(MouseInMenu) {
 EraseRect(destRect);
 }
 HLock((*(*MaxDevice)->gdPMap)->pmTable);
 colorTable = *(*(*MaxDevice)->gdPMap)->pmTable;
 
 GetForeColor(&saveColor);
 
 for(index = 1; index < COLOR_COUNT; index++) {
 RGBForeColor(&colorTable->ctTable[index - 1].rgb);
 drawRect = ColorRects[index];
 drawRect.top += 1;
 drawRect.left += 1;
 OffsetRect(&drawRect, destRect->left,
 destRect->top);
 
 /* Remember black is a Color QuickDraw pattern. */
 FillRect(&drawRect, black);
 }
 RGBForeColor(&saveColor);
 
 HUnlock((*(*MaxDevice)->gdPMap)->pmTable);
}

/*
--------------------------------------------------------
FIND TOOL ITEM */

pascal short FindToolItem(mousePt)
Point mousePt;
{
 short index;
 
 for(index = 1; index < TOOL_COUNT; index++) {
 
 if(PtInRect(mousePt, &ToolRects[index])) {
 return(index);
 }
 }
 return(0);
}

/*
------------------------
FIND PATTERN ITEM */

pascal short FindPatternItem(mousePt)
Point mousePt;
{
 short index;
 Rect patternRect;
 
 for(index = 1; index < PATTERN_COUNT; index++) {
 
 patternRect = PatternRects[index];
 patternRect.bottom += 1;
 patternRect.right += 1;
 
 if(PtInRect(mousePt, &patternRect)) {
 return(index);
 }
 }
 return(0);
}

/*
----------------------
FIND COLOR ITEM */

pascal short FindColorItem(mousePt)
Point mousePt;
{
 short index;
 Rect colorRect;
 
 for(index = 1; index < COLOR_COUNT; index++) {
 
 colorRect = ColorRects[index];
 colorRect.bottom += 1;
 colorRect.right += 1;
 
 if(PtInRect(mousePt, &colorRect)) {
 return(index);
 }
 }
 return(0);
}

/*
----------------------------
HILITE TOOL ITEM */

pascal void HiliteToolItem(destRect, item, hilite)
Rect *destRect;
short item;
Boolean hilite;
{
 Rect hiliteRect;
 
 hiliteRect = ToolRects[item];
 hiliteRect.bottom -= 1;
 hiliteRect.right -= 1;
 OffsetRect(&hiliteRect, destRect->left, 
 destRect->top);
 InvertRect(&hiliteRect);
}

/*
----------------------------
HILITE PATTERN ITEM */

pascal void HilitePatternItem(destRect, item, hilite)
Rect *destRect;
short item;
Boolean hilite;
{
 Rect hiliteRect;
 PenState savePen;
 Pattern thePattern;
 
 hiliteRect = PatternRects[item];
 hiliteRect.top += 1;
 hiliteRect.left += 1;
 OffsetRect(&hiliteRect, destRect->left, 
 destRect->top);
 
 if(hilite) {
 GetPenState(&savePen);
 
 PenSize(2, 2);
 FrameRect(&hiliteRect);
 
 PenSize(1, 1);
 PenMode(patBic);
 InsetRect(&hiliteRect, 2, 2);
 FrameRect(&hiliteRect);
 
 SetPenState(&savePen);
 }
 else {
 GetIndPattern(&thePattern, PATTERNS_ID, item);
 FillRect(&hiliteRect, &thePattern);
 }
}

/*
------------------------------------------------
HILITE COLOR ITEM */

pascal void HiliteColorItem(destRect, item, hilite)
Rect *destRect;
short item;
Boolean hilite;
{
 PenState savePen;
 Rect hiliteRect;
 RGBColor saveColor;
 CTabPtr colorTable;
 
 GetPenState(&savePen);
 
 hiliteRect = ColorRects[item];
 hiliteRect.bottom += 1;
 hiliteRect.right += 1;
 OffsetRect(&hiliteRect, destRect->left, 
 destRect->top);
 
 if(hilite) {
 FrameRect(&hiliteRect);
 
 PenMode(patBic);
 InsetRect(&hiliteRect, 1, 1);
 FrameRect(&hiliteRect);
 
 SetPenState(&savePen);
 }
 else {
 GetForeColor(&saveColor);
 
 HLock((*(*MaxDevice)->gdPMap)->pmTable);
 colorTable = *(*(*MaxDevice)->gdPMap)->pmTable;
 
 PenMode(patBic);
 FrameRect(&hiliteRect);
 
 SetPenState(&savePen);
 RGBForeColor(&colorTable->ctTable[item - 1].rgb);
 
 InsetRect(&hiliteRect, 1, 1);
 /* Remember black is a Color QuickDraw pattern. */
 FillRect(&hiliteRect, black);
 
 HUnlock((*(*MaxDevice)->gdPMap)->pmTable);
 
 RGBForeColor(&saveColor);
 }
}

/*
--------------------------------------------------------
MOVE PALETTE */

void MovePalette(whichPalette, position)
WindowPtr whichPalette;
Point position;
{
 MoveWindow(whichPalette, position.h, position.v, 
 false);
 
 if((TopWindow != nil) && (((WindowPeek) 
 TopWindow)->windowKind != userKind)) {
 
 /* The TopWindow is a non-application document. */
 if(((WindowPeek) whichPalette)->visible) {
 /* The palette is visible. Bring it to the 
 front and generate an activate event. */
 SelectWindow(whichPalette);
 }
 else {
 BringToFront(whichPalette);
 /* Make the palette visible and generate an 
 activate event. */
 ShowWindow(whichPalette);
 }
 }
 else {
 /* The TopWindow is an application window or it is 
 equal to nil. */
 BringToFront(whichPalette);
 
 if(TopWindow == nil) {
 /* Make the palette visible and generate an 
 activate event. */
 ShowWindow(whichPalette);
 }
 else {
 /* Make the palette visible but don't generate 
 an activate event. */
 ShowHide(whichPalette, true);
 HiliteWindow(whichPalette, true);
 }
 }
}

