
/*
--------------------------------------------------------
T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright (C)1987, 1988 by Impulse Technologies, 
 Inc., all rights reserved. 
 
 Filename:TearOffPalette.c
 Font:  Courier, 9 point
 Tab setting:    2
 Compiler:LightspeedC 2.15
 Project type:   APPL
 Creator: TOPD
 Segment: Main

--------------------------------------------------------
DESCRIPTION

 TearOffPalette is a demonstration of a very portable method of implementing 
tear-off menus and floating palettes. This technique uses external MDEF 
and WDEF code resources. The MDEF communicates with the application via 
a TearOffMenuGlobals structure in a TOMG resource.
 
 See TearOffMDEF.c for an explanation of the TearOffMenuGlobals structure 
and the routines an application must contain to use TearOffMDEF.
 
 See PaletteWDEF.c for an explanation of the behavior and use of PaletteWDEF.
 
 TearOffPalette is designed to keep palettes floating above documents 
without directly writing to low-memory Window Manager globals.
 
 A Color menu and palette will be displayed when Color QuickDraw is present 
and the depth of the screen allows 256 colors.
 
 Under MultiFinder and at any Suspend or Resume event, TearOffPalette 
will hide or show all visible palettes.
 
 IMPORTANT! TearOffPalette.project.rsrc must contain the TearOffMDEF 
and PaletteWDEF resources created by compiling their respective source 
files. */

/*
--------------------------------------------------------
GLOBAL CONSTANT 
DEFINITIONS AND VARIABLE DECLARATIONS */

#define GLOBAL_VARIABLES

#include "Constants.h"
#include "Variables.h"

/*
--------------------------------------------------------
EXTERNAL FUNCTION 
DECLARATIONS */

extern void Initialize();         /* Initialize.c */

extern void DoAbout();             /* Dialog.c */

extern void AdjustInterface();         /* Interface.c */

extern void LocateWindows();          /* Palette.c */
extern short ActiveWindow();          /* Palette.c */
extern void DoSelectWindow();           /* Palette.c */
extern void DoDragWindow();           /* Palette.c */
extern void HiliteUserWindows();        /* Palette.c */

extern void ActivateDocument();         /* Window.c */
extern void UpdateDocument();           /* Window.c */
extern void SizeDocument();           /* Window.c */
extern void UpdatePalette();          /* Window.c */
extern void NewDocument();          /* Window.c */
extern void CloseDocument();          /* Window.c */

extern pascal short FindToolItem();     /* Menu.c */
extern pascal void HiliteToolItem();    /* Menu.c */
extern pascal short FindPatternItem();  /* Menu.c */
extern pascal void HilitePatternItem(); /* Menu.c */
extern pascal short FindColorItem();    /* Menu.c */
extern pascal void HiliteColorItem();   /* Menu.c */
extern void MovePalette();          /* Menu.c */

/*
--------------------------------------------------------
FORWARD FUNCTION DECLARATIONS */

void DoEvent();
void MouseDownEvent();
void KeyEvent();
void ActivateEvent();
void UpdateEvent();
void SuspendResumeEvent();
void MenuEvent();

void AppleMenu();
void FileMenu();
void EditMenu();
void ToolMenu();
void PatternMenu();
void ColorMenu();

void ContentEvent();
void GrowEvent();
void InvalGrow();
void CloseEvent();

/*
--------------------------------------------------------
TEAROFF PALETTE */

main() {

 Initialize();
 UnloadSeg(Initialize);
 
 DoAbout();
 
 while((!Finished) && (!OutOfMemory)) {
 AdjustInterface();
 DoEvent();
 }
}

/*
--------------------------------------------------------
DO EVENT */

void DoEvent() {
Boolean result;

 if(WNEIsImplemented) {
 result = WaitNextEvent(everyEvent, &Event, Sleep, 
 nil);
 }
 else {
 SystemTask();
 result = GetNextEvent(everyEvent, &Event);
 }
 /* Find all application windows in the window list, 
 and adjust their order if necessary. 
 IMPORTANT! Always call LocateWindows() after getting 
 the event. */
 LocateWindows();
 
 if(result) {
 
 switch(Event.what) {
 
 case mouseDown:
 
 if(!(ClosingAll || Quitting)) {
 MouseDownEvent();
 }
 break;
 
 case keyDown:
 case autoKey:
 
 if(!(ClosingAll || Quitting)) {
 KeyEvent();
 }
 break;
 
 case updateEvt:
 UpdateEvent();
 break;
 
 case activateEvt:
 ActivateEvent();
 break;
 
 case app4Evt:
 SuspendResumeEvent();
 }
 }
 else {
 
 if((ClosingAll || Quitting) && (Event.what
 == nullEvent)) {
 /* If the application is quitting or the option 
 key was held down when closing a window, the
 top visible window is closed during each pass 
 through the event loop until all windows are
 closed. */
 
 if(TopWindow != nil) {
 CloseEvent(TopWindow);
 }
 else {
 ClosingAll = false;
 
 if(Quitting) {
 Finished = true;
 }
 }
 }
 }
}
 
/*
--------------------------------------------------------MOUSEDOWN EVENT

 AcitiveWindow() replaces most traditional calls to FrontWindow(). All 
use of SelectWindow() and DragWindow() is replaced by calls to DoSelectWindow() 
and DoDragWindow(). This ensures mouseDown events in application windows 
handle floating palettes properly. */

void MouseDownEvent() {
 WindowPtr whichWindow;
 short whichPart;
 
 MouseInMenu = false;
 
 whichPart = FindWindow(Event.where, &whichWindow);
 
 switch(whichPart) {
 
 case inMenuBar:
 MouseInMenu = true;
 MenuEvent(MenuSelect(Event.where));
 break;
 
 case inSysWindow:
 SystemClick(&Event, whichWindow);
 break;
 
 case inContent:  
 if(!ActiveWindow(whichWindow)) {
 DoSelectWindow(whichWindow);
 }
 else {
 ContentEvent(whichWindow);
 }
 break;
 
 case inDrag: 
 DoDragWindow(whichWindow);
 break;
 
 case inGrow: 
 if(!ActiveWindow(whichWindow)) {
 DoSelectWindow(whichWindow);
 }
 else {
 GrowEvent(whichWindow);
 }
 break;
 
 case inGoAway: 
 if(!ActiveWindow(whichWindow)) {
 DoSelectWindow(whichWindow);
 }
 else {
 if(TrackGoAway(whichWindow, Event.where)) {
 CloseEvent(whichWindow);
 }
 }
 break;
 
 case inZoomIn:
 case inZoomOut:
 if(TrackBox(whichWindow, Event.where, 
 whichPart)) {
 SetPort(whichWindow);
 EraseRect(&whichWindow->portRect);
 ZoomWindow(whichWindow, whichPart, false);
 SizeDocument(whichWindow);
 }
 }
}

/*
--------------------------------------------------------
KEYDOWN AND AUTOKEY EVENT */

void KeyEvent() {
 char whichChar;
 
 whichChar = Event.message & charCodeMask;

 if((Event.modifiers & cmdKey) != 0) {
 
 if(Event.what != autoKey) {
 MenuEvent(MenuKey(whichChar));
 }
 }
}

/*
--------------------------------------------------------
ACTIVATE EVENT */

void ActivateEvent() {
 WindowPtr whichWindow;
 
 /* Ensure all application windows are hilited 
 correctly. */
 HiliteUserWindows();
 whichWindow = (WindowPtr) Event.message;
 
 if(((WindowPeek) whichWindow)->refCon 
 != DOCUMENT_WINDOW) {
 /* Pass activate event from palette to
 TopDocument. */
 whichWindow = TopDocument;
 }
 if(whichWindow != nil) {
 /* Ensure document window's controls are properly 
 visible and hilited. */
 ActivateDocument(whichWindow, Event.modifiers
 & activeFlag);
 }
}

/*
--------------------------------------------------------
UPDATE EVENT */

void UpdateEvent() {
 WindowPtr whichWindow;
 
 whichWindow = (WindowPtr) Event.message;
 
 SetPort(whichWindow);
 
 BeginUpdate(whichWindow);
 
 if(((WindowPeek) whichWindow)->refCon 
 == DOCUMENT_WINDOW) {
 UpdateDocument(whichWindow);
 }
 else {
 UpdatePalette(whichWindow);
 }
 DrawControls(whichWindow);
 DrawGrowIcon(whichWindow);
 
 EndUpdate(whichWindow);
}

/*
--------------------------------------------------------
SUSPEND/RESUME EVENT 

 Hide all palettes when the application is not the active layer. This 
leaves the screen much less cluttered. */

void SuspendResumeEvent() {
 short index;
 
 for(index = 0; index < PALETTE_COUNT; index++) {
 
 if((Event.message & 1) == 0) {
 PalettesVisible[index] = ((WindowPeek) 
 Palettes[index])->visible;
 ShowHide(Palettes[index], false);
 }
 else {
 ShowHide(Palettes[index], 
 PalettesVisible[index]);
 PalettesVisible[index] = false;
 }
 }
 LocateWindows();
 HiliteUserWindows();
 
 if((((WindowPeek) TopWindow)->windowKind == userKind) 
 && (TopDocument != nil)) {
 /* Ensure the TopDocument's controls are properly 
 visible and unhilited. */
 ActivateDocument(TopDocument, Event.message & 1);
 }
}

/*
--------------------------------------------------------
MENU AND COMMAND KEY EVENT */

void MenuEvent(menuChoice)
long menuChoice;
{
 short whichMenu;
 short whichItem;
 
 /* HiWord(menuChoice). */
 whichMenu = menuChoice >> 16;
 /* LoWord(menuChoice). */
 whichItem = menuChoice & 0xFFFF;
 
 switch(whichMenu) {
 
 case APPLE_MENU_ID:
 AppleMenu(whichItem);
 break;
 
 case FILE_MENU_ID:
 FileMenu(whichItem);
 break;
 
 case EDIT_MENU_ID:
 EditMenu(whichItem);
 break;
 
 case TOOL_MENU_ID:
 ToolMenu(whichItem);
 break;
 
 case PATTERN_MENU_ID:
 PatternMenu(whichItem);
 break;
 
 case COLOR_MENU_ID:
 ColorMenu(whichItem);
 }
 HiliteMenu(0);
}

/*
--------------------------------------------------------
SELECT APPLE MENU ITEM */

void AppleMenu(whichItem)
short whichItem;
{
 Str255 daName;
 
 if(whichItem == ABOUT_ITEM) {
 DoAbout();
 }
 else {
 GetItem(Menus[APPLE_MENU_INDEX], whichItem, 
 &daName);
 /* Ignore the result returned by the ROM. */
 (void) OpenDeskAcc(&daName);
 }
}

/*
--------------------------------------------------------
SELECT FILE MENU ITEM */

void FileMenu(whichItem)
short whichItem;
{
 switch(whichItem) {
 
 case NEW_ITEM:
 NewDocument();
 break;
 
 case CLOSE_ITEM:
 CloseEvent(TopDocument);
 break;
 
 case QUIT_ITEM:
 Quitting = true;
 Sleep = 0;
 }
}

/*
--------------------------------------------------------
SELECT EDIT MENU ITEM */

void EditMenu(whichItem)
short whichItem;
{
 (void) SystemEdit(whichItem - 1);
}

/*
--------------------------------------------------------
SELECT TOOL MENU ITEM */

void ToolMenu(whichItem)
short whichItem;
{
 WindowPtr paletteWindow;
 
 paletteWindow = Palettes[TOOL_PALETTE];
 
 if(whichItem == MOVE_PALETTE_ITEM) {
 /* The menu has been torn off. */
 MovePalette(paletteWindow, (*TearOffs[TOOL_PALETTE])->position);
 }
 else {
 
 if(whichItem
 != (*TearOffs[TOOL_PALETTE])
 ->currentItem) {
 SetPort(Palettes[TOOL_PALETTE]);
 
 /* Unhilte the old item. */
 HiliteToolItem(&paletteWindow->portRect, 
 (*TearOffs[TOOL_PALETTE])->currentItem, 
 false);
 /* Hilite the new item. */
 HiliteToolItem(&paletteWindow->portRect, 
 whichItem, true);
 
 /* Set currentItem equal to the new item. */
 (*TearOffs[TOOL_PALETTE])->currentItem 
 = whichItem;
 }
 }
}

/*
--------------------------------------------------------
SELECT PATTERN MENU ITEM */

void PatternMenu(whichItem)
short whichItem;
{
 WindowPtr paletteWindow;
 
 paletteWindow = Palettes[PATTERN_PALETTE];
 
 if(whichItem == MOVE_PALETTE_ITEM) {
 /* The menu has been torn off. */
 MovePalette(paletteWindow, (*TearOffs[PATTERN_PALETTE])->position);
 }
 else {
 
 if(whichItem 
 != (*TearOffs[PATTERN_PALETTE])
 ->currentItem) {
 SetPort(Palettes[PATTERN_PALETTE]);
 
 /* Unhilte the old item. */
 HilitePatternItem(&paletteWindow->portRect, 
 (*TearOffs[PATTERN_PALETTE])
 ->currentItem, false);
 /* Hilite the new item. */
 HilitePatternItem(&paletteWindow->portRect, 
 whichItem, true);
 
 /* Set currentItem equal to the new item. */
 (*TearOffs[PATTERN_PALETTE])->currentItem = 
 whichItem;
 }
 }
}

/*
--------------------------------------------------------
SELECT COLOR MENU ITEM */

void ColorMenu(whichItem)
short whichItem;
{
 WindowPtr paletteWindow;
 
 paletteWindow = Palettes[COLOR_PALETTE];
 
 if(whichItem == MOVE_PALETTE_ITEM) {
 /* The menu has been torn off. */
 MovePalette(paletteWindow, 
 (*TearOffs[COLOR_PALETTE])->position);
 }
 else {
 
 if(whichItem
 != (*TearOffs[COLOR_PALETTE])
 ->currentItem) {
 SetPort(Palettes[COLOR_PALETTE]);
 
 /* Unhilte the old item. */
 HiliteColorItem(&paletteWindow->portRect, 
 (*TearOffs[COLOR_PALETTE])->currentItem, 
 false);
 /* Hilite the new item. */
 HiliteColorItem(&paletteWindow->portRect, 
 whichItem, true);
 
 /* Set currentItem equal to the new item. */
 (*TearOffs[COLOR_PALETTE])->currentItem = 
 whichItem;
 }
 }
}

/*
--------------------------------------------------------
CONTENT EVENT */

void ContentEvent(whichWindow)
WindowPtr whichWindow;
{
 Point mousePt;
 short item;
 
 SetPort(whichWindow);
 
 mousePt = Event.where;
 GlobalToLocal(&mousePt);
 
 /* Use the window's refCon to determine what type of    application 
window received the event. */
 switch(((WindowPeek) whichWindow)->refCon) {
 
 case TOOL_PALETTE:
 item = FindToolItem(mousePt);
 
 if(item
 != (*TearOffs[TOOL_PALETTE])
 ->currentItem) {
 /* Unhilte the old item. */
 HiliteToolItem(&whichWindow->portRect, 
 (*TearOffs[TOOL_PALETTE])->
 currentItem, false);
 /* Hilite the new item. */
 HiliteToolItem(&whichWindow->portRect, item, 
 true);
 
 /* Set currentItem equal to the new item. */
 (*TearOffs[TOOL_PALETTE])->currentItem 
 = item;
 }
 break;
 
 case PATTERN_PALETTE:
 item = FindPatternItem(mousePt);
 
 if(item 
 != (*TearOffs[PATTERN_PALETTE])
 ->currentItem) {
 /* Unhilte the old item. */
 HilitePatternItem(&whichWindow->portRect, 
 (*TearOffs[PATTERN_PALETTE])
 ->currentItem, false);
 /* Hilite the new item. */
 HilitePatternItem(&whichWindow->portRect, 
 item, true);
 
 /* Set currentItem equal to the new item. */
 (*TearOffs[PATTERN_PALETTE])->currentItem 
 = item;
 }
 break;
 
 case COLOR_PALETTE:
 item = FindColorItem(mousePt);
 
 if(item 
 != (*TearOffs[COLOR_PALETTE])
 ->currentItem) {
 /* Unhilte the old item. */
 HiliteColorItem(&whichWindow->portRect, 
 (*TearOffs[COLOR_PALETTE])
 ->currentItem, false);
 /* Hilite the new item. */
 HiliteColorItem(&whichWindow->portRect, 
 item, true);
 
 /* Set currentItem equal to the new item. */
 (*TearOffs[COLOR_PALETTE])->currentItem
 = item;
 }
 }
}

/*
--------------------------------------------------------
GROW EVENT */

void GrowEvent(whichWindow)
WindowPtr whichWindow;
{
 Rect growRect;
 long size;
 short width;
 short height;
 
 growRect.left = MIN_WINDOW_WIDTH;
 growRect.top = MIN_WINDOW_HEIGHT;
 growRect.right = (*GrayRgn)->rgnBBox.right;
 growRect.bottom = (*GrayRgn)->rgnBBox.bottom 
 - TITLE_BAR_HEIGHT;
 
 size = GrowWindow(whichWindow, Event.where, 
 &growRect);
 
 if(size != 0) {
 SetPort(whichWindow);
 
 InvalGrow(whichWindow);
 
 height = size >> 16; /* HiWord(size). */
 width = size & 0xFFFF; /* LoWord(size). */
 
 SizeWindow(whichWindow, width, height, true);
 /* Redraw the scroll bars and grow icon. */
 SizeDocument(whichWindow);
 }
}

/*
--------------------------------------------------------
INVAL GROW

 Invalidate the grow region of the window. This includes the area occupied 
by the scroll bars. */

void InvalGrow(whichWindow)
WindowPtr whichWindow;
{
 Rect updateRect;
 
 updateRect = whichWindow->portRect;
 
 updateRect.top = updateRect.bottom - SCROLL_BAR_SIZE;
 InvalRect(&updateRect);
 
 updateRect.top = whichWindow->portRect.top;
 
 updateRect.left = updateRect.right - SCROLL_BAR_SIZE;
 InvalRect(&updateRect);
}

/*
--------------------------------------------------------
CLOSE EVENT */

void CloseEvent(whichWindow)
WindowPtr whichWindow;
{
 WindowPeek front;
 
 if(Event.modifiers & optionKey) {
 ClosingAll = true;
 }
 if ((front = (WindowPeek) TopWindow) != nil) {
 
 if(front->windowKind < 0) {
 CloseDeskAcc(front->windowKind);
 }
 else {
 
 if((front->windowKind == userKind) 
 && (whichWindow != nil)) {
 
 if(((WindowPeek) whichWindow)->refCon 
 == DOCUMENT_WINDOW) {
 CloseDocument(whichWindow);
 
 if(TopPalette == TopWindow) {
 /* Find the new TopDocument. */
 LocateWindows();
 
 if(TopDocument != nil) {
 /* Ensure the TopDocument and its 
 controls are hilited properly. */
 ActivateDocument(TopDocument, 
 true);
 }
 }
 }
 else {
 
 if(TopDocument != nil) {
 /* Don't generate any events that 
 might cause the TopDocument to be 
 unhilited. */
 ShowHide(whichWindow, false);
 }
 else {
 /* Ensure an activate event is 
 generated in case the next visible 
 window does not belong to the 
 application. */
 HideWindow(whichWindow);
 }
 }
 }
 }
 }
}
