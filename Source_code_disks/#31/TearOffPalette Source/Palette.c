
/*
--------------------------------------------------------
T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright (C)1987, 1988 by Impulse Technologies, 
 Inc., all rights reserved. 
 
 Filename:Palette.c
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

extern void ActivateDocument();    /* Window.c */

extern short GetMenuBarHeight();   /* Interface.c */

/*
--------------------------------------------------------
FORWARD FUNCTION DECLARATIONS */

void LocateWindows();
void HiliteUserWindows();
short ActiveWindow();

void DoDragWindow();
void DoSelectWindow();
void SendToBack();
void Drag();

/*
--------------------------------------------------------LOCATE WINDOWS

 Find the TopWindow whether it belongs to the application or not. Also 
find the TopPalette, the BottomPalette, and the TopDocument. These globals 
will all point to visible windows or nil. If the TopDocument is above 
any visible palette, adjust the order of the windows. If a visible non-application 
window is between any palettes and the TopDocument, adjust the order 
of  the windows. This function replaces most uses of FrontWindow() in 
the application. */

void LocateWindows()
{
 short palettesFound;
 Boolean inOrder;
 WindowPeek next;
 WindowPeek bottom;
 
 /* Initialize globals before search is begun. */
 TopWindow = TopPalette = TopDocument = nil;
 /* Make sure all SendBehind() and NewWindow() calls     bring a window 
to the front if there are no visible palettes. */
 BottomPalette = BRING_TO_FRONT;
 
 palettesFound = 0;
 inOrder = true;
 
 for(next = WindowList; next != nil; 
 next = next->nextWindow) {
 
 if(next->visible) {
 
 if(TopWindow == nil) {
 /* First visible window. */
 TopWindow = (WindowPtr) next;
 }
 if(next->windowKind == userKind) {
 
 if(next->refCon == DOCUMENT_WINDOW) {
 
 if(TopDocument == nil) {
 /* First visible Document. */
 TopDocument = (WindowPtr) next;
 
 if(palettesFound == PALETTE_COUNT) {
 /* If all the palettes are found 
 exit the search loop. */
 break;
 }
 }
 }
 else {
 
 if(TopPalette == nil) {
 /* First visible palette. */
 TopPalette = (WindowPtr) next;
 }
 /* BottomPalette always points to the 
 last visible palette found. */
 BottomPalette = (WindowPtr) next;
 }
 }
 else {
 
 if((TopPalette != nil) 
 || (TopDocument != nil)) {
 /* Shucks, a non-application window is 
 visible between the palettes and 
 TopDocument. */
 inOrder = false;
 }
 }
 }
 /* All windows beforelast palette get here */
 if((next->windowKind == userKind) && (next->refCon 
 != DOCUMENT_WINDOW)) {
 palettesFound++;
 
 if((TopDocument != nil) && (next->visible)) {
 /* A visible palette is beneath the 
 TopDocument. */
 
 if(TopDocument == TopWindow) {
 /* Bring the TopPalette to the front. */
 SelectWindow(next);
 TopWindow = (WindowPtr) next;
 }
 else {
 /* Put TopDocument behind BottomPalette. */
 SendBehind(TopDocument, next);
 }
 next = (WindowPeek) TopDocument;
 
 if(palettesFound == PALETTE_COUNT) {
 /* If all the palettes are found exit the 
 search loop. */
 break;
 }
 }
 }
 }
 if((!inOrder) && (TopPalette != nil)) {
 
 if(TopDocument != nil) {
 bottom = (WindowPeek) TopDocument;
 }
 else {
 bottom = (WindowPeek) BottomPalette;
 }
 for(next = (WindowPeek) TopPalette; next != nil; 
 next = next->nextWindow) {
 
 if(next != bottom) {
 
 if(next->windowKind != userKind) {
 /* Remove the non-application window. */
 SendBehind(next, bottom);
 /* Start over. */
 next = (WindowPeek) TopPalette;
 }
 }
 else {
 break;
 }
 }
 }
}

/*
--------------------------------------------------------
HILITE USER WINDOWS */

void HiliteUserWindows() 
{
 WindowPeek bottom;
 WindowPeek next;
 Boolean hilite;
 short index;
 
 if(TopPalette != nil) {
 
 if(TopWindow == TopPalette) {
 hilite = true;
 }
 else {
 hilite = false;
 }
 for(index = 0; index < PALETTE_COUNT; index++) {
 HiliteWindow(Palettes[index], hilite);
 }
 if(TopDocument != nil) {
 
 HiliteWindow(TopDocument, hilite);
 /* Unhilite the remaining document windows. */
 for(next = ((WindowPeek) 
 TopDocument)->nextWindow; next != nil; 
 next = next->nextWindow) {
 
 if((next->windowKind == userKind) && 
 (next->refCon == DOCUMENT_WINDOW)) {
 ActivateDocument(next, false);
 }
 }
 }
 }
}

/*
--------------------------------------------------------
ACTIVE WINDOW

 Return true if whichWindow is a palette or the TopDocument and the application 
is active. */

short ActiveWindow(whichWindow)
WindowPtr whichWindow;
{
 if(whichWindow != nil) {
 
 if((((WindowPeek) TopWindow)->windowKind 
 == userKind)
 && ((whichWindow == TopDocument)
 || (((WindowPeek) whichWindow)->refCon 
 != DOCUMENT_WINDOW))) {
 return(true);
 }
 }
 return(false);
}

/*
------------------------------------------
DO DRAG WINDOW

 Since DragWindow() automatically brings a window to the front if it's 
not already the front window, it must be replaced by the application 
to keep palettes floating above documents. */

void DoDragWindow(whichWindow)
WindowPtr whichWindow;
{
 if(Event.modifiers & optionKey) {
 /*An optional extension of Macintosh interface. */
 SendToBack(whichWindow);
 }
 else {
 
 if(Event.modifiers & cmdKey) {
 Drag(whichWindow);
 }
 else {
 
 if(!ActiveWindow(whichWindow)) {
 DoSelectWindow(whichWindow);
 }
 else {
 
 if((((WindowPeek) whichWindow)->refCon 
 != DOCUMENT_WINDOW)
 && (whichWindow != TopPalette)) {
 BringToFront(whichWindow);
 /* Force the palette to be updated before 
 it is dragged. */
 SetPort(whichWindow);
 UpdatePalette(whichWindow);
 }
 Drag(whichWindow);
 }
 }
 }
}

/*
--------------------------------------------------------
DO SELECT WINDOW

 Since SelectWindow() brings any window to the front, it must be replaced 
by the application to keep palettes floating above documents. */

void DoSelectWindow(whichWindow)
WindowPtr whichWindow;
{
 RgnHandle updateRgn;
 
 if(((WindowPeek) whichWindow)->refCon 
 == DOCUMENT_WINDOW) {
 
 if(TopPalette != nil) {
 /* Calculate window area not visible that will 
 need to be updated. */
 CopyRgn(whichWindow->visRgn, updateRgn 
 = NewRgn());
 OffsetRgn(updateRgn,(*((WindowPeek) 
 whichWindow)->contRgn)->rgnBBox.left,
 (*((WindowPeek)whichWindow)
 ->contRgn)->rgnBBox.top);
 DiffRgn(((WindowPeek) whichWindow)->strucRgn, 
 updateRgn, updateRgn);
 
 /* Move document below the BottomPalette. */
 SendBehind(whichWindow, BottomPalette);
 CalcVisBehind(whichWindow, updateRgn);
 PaintOne(whichWindow, updateRgn);
 
 DisposeRgn(updateRgn);
 
 if(TopPalette != TopWindow) {
 /* Bring all active application windows 
 forward by generating an activate event. */
 SelectWindow(TopPalette);
 }
 else {
 /* Ensure whichWindow and its controls are 
 hilited properly. */
 ActivateDocument(whichWindow, true);
 } 
 /* Ensure whichWindow and its controls are 
 unhilited properly. */
 ActivateDocument(TopDocument, false);
 }
 else {
 /* No Palettes, bring the document to the front 
 and generate an activate event. */
 SelectWindow(whichWindow);
 }
 }
 else {
 if(((WindowPeek) TopWindow)->windowKind 
 == userKind) {
 /* Bring the palette to the front but don't 
 generate an activate event. */
 BringToFront(whichWindow);
 }
 else {
 /* Bring the palette to the front and generate 
 an activate event. */
 SelectWindow(whichWindow);
 }
 }
}

/*
--------------------------------------------------------
SEND TO BACK */

void SendToBack(whichWindow)
WindowPtr whichWindow;
{
 WindowPeek next;
 WindowPtr below;
 
 if(((WindowPeek) whichWindow)->refCon 
 == DOCUMENT_WINDOW) {
 
 below = whichWindow;
 
 /* Find the document below TopDocument. Documents 
 are always visible. */
 for(next = ((WindowPeek) whichWindow)->nextWindow; 
 next != nil; next = next->nextWindow) {
 
 if((next->windowKind == userKind) && 
 (next->refCon == DOCUMENT_WINDOW)) {
 below = (WindowPtr) next;
 break;
 }
 }
 if(whichWindow != below) {
 /* Send document all the way to the back. */
 SendBehind(whichWindow, nil);
 
 if(TopPalette == TopWindow) {
 /* Ensure whichWindow and its controls are 
 unhilited properly. */
 ActivateDocument(whichWindow, false);
 
 /* Find the new TopDocument. */
 LocateWindows();
 /* Ensure the TopDocument and its controls 
 are hilited properly. */
 ActivateDocument(TopDocument, true);
 }
 }
 } 
 else {
 
 if((whichWindow != BottomPalette) && (TopPalette 
 != BottomPalette)) {
 /* Move palette behind the BottomPalette. */
 SendBehind(whichWindow, BottomPalette);
 }
 }
}

/*
--------------------------------------------------------
DRAG */

void Drag(whichWindow)
WindowPtr whichWindow;
{
 GrafPtr savePort;
 Rect dragLimit;
 RgnHandle dragRgn;
 long result;
 Point move;
 Rect *portBounds;
 
 if(WaitMouseUp()) {
 GetPort(&savePort);
 SetPort(WMgrPort);
 
 SetClip(GrayRgn);
 
 /* Ensure the drag outline does not get drawn 
 through the windows above whichWindow. */
 ClipAbove(whichWindow);
 
 dragLimit = screenBits.bounds;
 dragLimit.top = GetMenuBarHeight();
 
 CopyRgn(((WindowPeek) whichWindow)->strucRgn, 
 dragRgn = NewRgn());
 
 /* Drag outline of window around the screen. */
 result = DragGrayRgn(dragRgn, Event.where, 
 &dragLimit, &dragLimit, noConstraint, nil);
 
 move.v = result >> 16; /* HiWord(result). */
 move.h = result & 0xFFFF; /* LoWord(result). */
 
 if(move.v != 0x8000) {
 
 /* The mouse button has been released inside 
 dragLimit. See 'Inside Macintosh Volume I,' 
 pages 294-295, for expalnation of 0x8000. */
 if(((CGrafPtr) whichWindow)->portVersion 
 & 0xc000) {
 /* The window is a color port. */
 portBounds = &(*((CGrafPtr) 
 whichWindow)->portPixMap)->bounds;
 }
 else {
 /* The window is an old-style port. */
 portBounds = &whichWindow->portBits.bounds;
 }
 move.v += whichWindow->portRect.top 
 - portBounds->top;
 move.h += whichWindow->portRect.left 
 - portBounds->left;
 
 MoveWindow(whichWindow, move.h, move.v, false);
 }
 DisposeRgn(dragRgn);
 SetPort(savePort);
 }
}


