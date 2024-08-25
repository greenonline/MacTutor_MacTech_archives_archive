/*
------------------------------------
T E A R O F F   P A L E T T E

 version 1.0
 by Don Melton and Mike Ritter
 
 Copyright (C)1987, 1988 by Impulse Technologies, 
 Inc., all rights reserved. 
 
 Filename:Error.c
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

/* None */

/*
--------------------------------------------------------
FORWARD FUNCTION DECLARATIONS */

short GoodNewPtr();
short GoodNewHandle();
short GoodResource();

pascal long RecoverMemory();

/*
--------------------------------------------------------
GOOD NEW POINTER */

short GoodNewPtr(whichPtr)
Ptr whichPtr;
{
 if((whichPtr != nil) && (MemErr == noErr)) {
 return(true);
 }
 return(false);
}

/*
--------------------------------------------------------
GOOD NEW HANDLE */

short GoodNewHandle(whichHandle)
Handle whichHandle;
{
 if(whichHandle != nil) {
 return(GoodNewPtr(*whichHandle));
 }
 return(false);
}


/*
--------------------------------------------------------
GOOD RESOURCE */

short GoodResource(whichHandle)
Handle whichHandle;
{
 if((whichHandle != nil) && (ResError() == noErr)) {
 
 if(*whichHandle != nil) {
 return(true);
 }
 }
 return(false);
}


/*
--------------------------------------------------------
RECOVER MEMORY

 RecoverMemory() is a very simple grow zone function designed to prevent 
the ROM or resident software such as desk accessories from generating 
out of memory errors. After this function is called, the application 
will quit before processing the next event.
 
 See 'Inside Macintosh Volume II,' pages 42-43, about setting up grow 
zone functions. */

pascal long RecoverMemory(memoryNeeded)
Size memoryNeeded;
{
 long bufferSize;
 
 SetUpA5();
 
 bufferSize = GetHandleSize(MemoryBuffer);
 
 if(bufferSize != 0) {
 DisposHandle(MemoryBuffer);
 }
 OutOfMemory = true;
 
 RestoreA5();
 
 return(bufferSize);
}


