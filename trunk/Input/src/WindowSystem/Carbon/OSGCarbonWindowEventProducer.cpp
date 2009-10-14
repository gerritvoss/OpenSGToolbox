/*---------------------------------------------------------------------------*\
 *                     OpenSG ToolBox UserInterface                          *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                         www.vrac.iastate.edu                              *
 *                                                                           *
 *   Authors: David Kabala, Alden Peterson, Lee Zaniewski, Jonathan Flory    *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                License                                    *
 *                                                                           *
 * This library is free software; you can redistribute it and/or modify it   *
 * under the terms of the GNU Library General Public License as published    *
 * by the Free Software Foundation, version 2.                               *
 *                                                                           *
 * This library is distributed in the hope that it will be useful, but       *
 * WITHOUT ANY WARRANTY; without even the implied warranty of                *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU         *
 * Library General Public License for more details.                          *
 *                                                                           *
 * You should have received a copy of the GNU Library General Public         *
 * License along with this library; if not, write to the Free Software       *
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.                 *
 *                                                                           *
\*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*\
 *                                Changes                                    *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
 *                                                                           *
\*---------------------------------------------------------------------------*/

//---------------------------------------------------------------------------
//  Includes
//---------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>

#define OSG_COMPILEINPUTLIB

#include <OpenSG/OSGConfig.h>

#include "OSGCarbonWindowEventProducer.h"

#ifdef __APPLE__

//#include <Quicktime/Movies.h>
//#include <CarbonEvents.h>


OSG_BEGIN_NAMESPACE

/***************************************************************************\
 *                            Description                                  *
\***************************************************************************/

/*! \class osg::CarbonWindowEventProducer
CarbonWindowEventProducer Class.  
*/

#define KeyBackspace 	51
#define KeyEnter 	76
#define KeyHome 	115
#define KeyEnd 	119
#define KeyPageDown 	121
#define KeyPageUp 	116
#define KeyReturn 	36 	
#define KeyDelete 	117
#define KeyTab 	48
#define KeySpacebar 	49
#define KeyShift 	56 	
#define KeyControl 	59 	
#define KeyMenu 	58
//#define KeyPrintScreen 	*
#define KeyEscape 	53
#define KeyCapsLock 	57
#define KeyHelp 	114
#define KeyF1 	122
#define KeyF2 	120
#define KeyF3 	99
#define KeyF4 	118
#define KeyF5 	96
#define KeyF6 	97
#define KeyF7 	98
#define KeyF8 	100
#define KeyF9 	101
#define KeyF10 	109
#define KeyF11 	103
#define KeyF12 	111
#define KeyMacFn 	63
#define KeyMacOption 	58
#define KeyMacCommand 	55
#define KeyWinApplication 	110
#define KeyQ 	12
#define KeyW 	13
#define KeyE 	14 	
#define KeyR 	15 	
#define KeyT 	17 	
#define KeyY 	16 	
#define KeyU 	32 	
#define KeyI 	34 	
#define KeyO 	31 	
#define KeyP 	35 	
#define KeyA 	0 	
#define KeyS 	1 	
#define KeyD 	2 	
#define KeyF 	3 	
#define KeyG 	5 	
#define KeyH 	4 	
#define KeyJ 	38 	
#define KeyK 	40 	
#define KeyL 	37 	
#define KeyZ 	6 	
#define KeyX 	7 	
#define KeyC 	8 	
#define KeyV 	9 	
#define KeyB 	11 	
#define KeyN 	45 	
#define KeyM 	46 	
#define Key0 	29
#define Key1 	18
#define Key2 	19
#define Key3 	20
#define Key4 	21
#define Key5 	23
#define Key6 	22
#define Key7 	26
#define Key8 	28
#define Key9 	25
#define KeyPeriod 	47
#define KeyComma 	43
#define KeySlash 	44
#define KeyNum0 	82
#define KeyNum1 	83
#define KeyNum2 	84
#define KeyNum3 	85
#define KeyNum4 	86
#define KeyNum5 	87
#define KeyNum6 	88
#define KeyNum7 	89
#define KeyNum8 	91
#define KeyNum9 	92
#define KeyMultiply 	67
#define KeyAdd 	69
#define KeySubtract 	78
#define KeyDivide 	75
#define KeyDecimal 	65
#define KeyNumEqual 	81

#define KeyBackquote 50
#define KeyMinus 27
#define KeyEquals 24
#define KeyLeftBracket 33
#define KeyRightBracket 30
#define KeyBackslash 42
#define KeySemicolon 41
#define KeyApostrophe 39
#define KeyClear 71
#define KeyUp 126
#define KeyDown 125
#define KeyLeft 123
#define KeyRight 124

/***************************************************************************\
 *                           Class variables                               *
\***************************************************************************/

CarbonWindowEventProducer::CarbonWindowToProducerMap CarbonWindowEventProducer::_CarbonWindowToProducerMap;

/***************************************************************************\
 *                           Class methods                                 *
\***************************************************************************/

void CarbonWindowEventProducer::initMethod (void)
{
	// A magic method that allows applications to react to events even
	// when they are not organized in a bundle
	ProcessSerialNumber psn = { 0, kCurrentProcess };
	TransformProcessType(&psn, kProcessTransformToForegroundApplication);
	SetFrontProcess(&psn);
}

OSStatus CarbonWindowEventProducer::eventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    UInt32 WindowId(*static_cast<UInt32*>(userData));
        
   if(_CarbonWindowToProducerMap.find(WindowId) != _CarbonWindowToProducerMap.end())
   {
      return _CarbonWindowToProducerMap[WindowId]->internalEventHandler(nextHandler, event,
                           userData);
   }
   else
   {
        return eventNotHandledErr;
   }
}

UInt32 CarbonWindowEventProducer::getUndefinedWindowId(void)
{
    UInt32 i(1);
    while(_CarbonWindowToProducerMap.find(i) != _CarbonWindowToProducerMap.end())
    {
        ++i;
    }
    return i;
}

void  CarbonWindowEventProducer::mainLoop(void)
{
	// Main loop ( event dispatching )
    EventRef theEvent;    
    EventTargetRef theTarget;    
    theTarget = GetEventDispatcherTarget(); 
    while (true)
    {
        while  ( ReceiveNextEvent(0, NULL,0 /*kEventDurationForever*/ ,true,
                                 &theEvent)== noErr)
        {
            SendEventToEventTarget (theEvent, theTarget);        
            ReleaseEvent(theEvent);
            
        }
	
        CarbonWindowToProducerMap::iterator MapItor;
        for( MapItor = _CarbonWindowToProducerMap.begin(); MapItor != _CarbonWindowToProducerMap.end(); ++MapItor)
        {
            MapItor->second->update();
            MapItor->second->draw();
        }
        if(_CarbonWindowToProducerMap.size() == 0)
        {
            break;
        }

    }
}

/***************************************************************************\
 *                           Instance methods                              *
\***************************************************************************/

void CarbonWindowEventProducer::setShowCursor(bool show)
{
    if(show)
    {
        ShowCursor();
    }
    else
	{
        HideCursor();
	}
}

bool CarbonWindowEventProducer::getShowCursor() const
{
    //TODO:Implement
	return true;//_CursorShown;
}

void CarbonWindowEventProducer::setAttachMouseToCursor(bool attach)
{
    CGAssociateMouseAndMouseCursorPosition(attach);
}

bool CarbonWindowEventProducer::getAttachMouseToCursor(void) const
{
    //TODO:Implement
	return true;//_CursorShown;
}


osg::Vec2f CarbonWindowEventProducer::getDesktopSize() const
{

    HIRect DesktopRect;
    OSStatus status = HIWindowGetAvailablePositioningBounds(kCGNullDirectDisplay, kHICoordSpaceScreenPixel, &DesktopRect);
    if(status == noErr)
    {
        return Vec2f(DesktopRect.size.width, DesktopRect.size.height);
    }
    else
    {
        SWARNING << "CarbonWindowEventProducer::getDesktopSize: Error" << std::endl;
        return Vec2f();
    }
}

// TRY TO CONVERT AN AEDesc TO AN FSSpec
//     As per Apple Technical Q&A QA1274
//     eg: http://developer.apple.com/qa/qa2001/qa1274.html
//     Returns 'noErr' if OK,
//             or an 'OSX result code' on error.
//
int AEDescToFSSpec(const AEDesc* desc, FSSpec* fsspec) {
    OSStatus err = noErr;
    AEDesc coerceDesc;
    // If AEDesc isn't already an FSSpec, convert it to one
    if ( desc->descriptorType != typeFSS ) {
        if ( ( err = AECoerceDesc(desc, typeFSS, &coerceDesc) ) == noErr ) {
        // Get FSSpec out of AEDesc
            err = AEGetDescData(&coerceDesc, fsspec, sizeof(FSSpec));
            AEDisposeDesc(&coerceDesc);
        }
    } else {
        err = AEGetDescData(desc, fsspec, sizeof(FSSpec));
    }
    return( err );
}

// CONVERT REGULAR PATH -> FSSpec
//     If file does not exist, expect fnfErr.
//     Returns 'noErr' if OK,
//             or an 'OSX result code' on error.
//
static OSStatus PathToFSSpec(const char *path, FSSpec &spec) {
    OSStatus err;
    FSRef ref;
    if ((err = FSPathMakeRef((const UInt8*)path, &ref, NULL)) != noErr) {
    return(err);
    }
    // FSRef -> FSSpec
    if ((err = FSGetCatalogInfo(&ref, kFSCatInfoNone, NULL, NULL, &spec,
                                     NULL)) != noErr) {
    return(err);
    }
    return(noErr);
}

std::vector<Path> CarbonWindowEventProducer::openFileDialog(const std::string& WindowTitle,
		const std::vector<FileDialogFilter>& Filters,
		const Path& InitialDir,
		bool AllowMultiSelect)
{
	std::vector<osg::Path, std::allocator<osg::Path> > FilesToOpen;
    OSStatus status;
    NavDialogRef OpenFileDialog;

    NavDialogCreationOptions dialogOptions;

    //Default options for dialog
    status = NavGetDefaultDialogCreationOptions(&dialogOptions);
    if(status != noErr)
    {
        SWARNING << "CarbonWindowEventProducer::openFileDialog: NavGetDefaultDialogCreationOptions Error: "<< status << std::endl;
	    return FilesToOpen;
    }

   // Make the window app-wide modal
   dialogOptions.modality = kWindowModalityAppModal;
   dialogOptions.parentWindow = _WindowRef;
   dialogOptions.windowTitle = CFStringCreateWithCString(NULL, WindowTitle.c_str(), WindowTitle.size());
   if(AllowMultiSelect)
   {
       dialogOptions.optionFlags = dialogOptions.optionFlags | kNavAllowMultipleFiles;
   }
   else
   {
       dialogOptions.optionFlags = dialogOptions.optionFlags ^ kNavAllowMultipleFiles;
   }
   
   status = NavCreateGetFileDialog (
       &dialogOptions,
       NULL,
       NULL,//_EventHandlerUPP,
       NULL,
       NULL,//NavObjectFilterUPP inFilterProc,
       NULL,//void *inClientData,
       &OpenFileDialog);
    
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindowEventProducer::openFileDialog: NavCreateGetFileDialog Error: "<< status << std::endl;
	    return FilesToOpen;
    }
    
    // Image Browser can open files with the ".imagebrowser" extension
    CFMutableArrayRef identifiers = CFArrayCreateMutable( kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks );
    if(identifiers == NULL)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindowEventProducer::openFileDialog: CFArrayCreateMutable Error: NULL " <<  std::endl;
	    return FilesToOpen;
    }

    //Initial directory 
    FSSpec spec;
    status = PathToFSSpec(InitialDir.string().c_str(), spec);
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindowEventProducer::openFileDialog: PathToFSSpec Error: "<< status << std::endl;
	    return FilesToOpen;
    }

    AEDesc DefaultLocationAEDesc;
    status = AECreateDesc(typeFSS, &spec, sizeof(FSSpec), &DefaultLocationAEDesc);
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindowEventProducer::openFileDialog: AECreateDesc Error: "<< status << std::endl;
	    return FilesToOpen;
    }
    status = NavCustomControl( OpenFileDialog, kNavCtlSetLocation, &DefaultLocationAEDesc );
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindowEventProducer::openFileDialog: NavCustomControl Error: "<< status << std::endl;
	    return FilesToOpen;
    }
    AEDisposeDesc(&DefaultLocationAEDesc);

    //Filters
    for(std::vector<FileDialogFilter>::const_iterator Itor(Filters.begin()) ; Itor != Filters.end(); ++Itor)
    {
        if(Itor->getFilter().compare("*") != 0)
        {
            // create the image browser UTI conforming to "public.data" because it's a data file rather than a bundle 
            CFStringRef FilterCFString = UTTypeCreatePreferredIdentifierForTag( kUTTagClassFilenameExtension, CFStringCreateWithCString(NULL, Itor->getFilter().c_str(), Itor->getFilter().size()),kUTTypeData );

            if(FilterCFString == NULL)
            {
                NavDialogDispose(OpenFileDialog);
                SWARNING << "CarbonWindowEventProducer::openFileDialog: UTTypeCreatePreferredIdentifierForTag Error: NULL " <<  std::endl;
                return FilesToOpen;
            }
            //Itor->getName();
            CFArrayAppendValue( identifiers, FilterCFString );
        }
    }
    
    // filter by image browser UTI
    status = NavDialogSetFilterTypeIdentifiers( OpenFileDialog, identifiers );
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindowEventProducer::openFileDialog: NavDialogRun Error: "<< status << std::endl;
        return FilesToOpen;
    }
 
    //Open the dialog
    status = NavDialogRun(OpenFileDialog);
    if(status != noErr)
    {
        NavDialogDispose(OpenFileDialog);
        SWARNING << "CarbonWindowEventProducer::openFileDialog: NavDialogRun Error: "<< status << std::endl;
        return FilesToOpen;
    }

    //Get Reply
    NavReplyRecord replyRecord;
    status = NavDialogGetReply(OpenFileDialog, &replyRecord);
    NavDialogDispose(OpenFileDialog);
    //If user canceled then return empty
    if (!replyRecord.validRecord ||  status == userCanceledErr )
    {
        NavDisposeReply(&replyRecord);
        return FilesToOpen;
    }
    
    //Other Errors
    if(status != noErr)
    {
        NavDisposeReply(&replyRecord);
        SWARNING << "CarbonWindowEventProducer::openFileDialog: NavDialogGetReply Error: "<< status << std::endl;
        return FilesToOpen;
    }
    // How many items selected?
    long count = 0;
    if ( AECountItems(&replyRecord.selection, &count) != noErr ) 
    {
        NavDisposeReply(&replyRecord);
        SWARNING << "CarbonWindowEventProducer::openFileDialog: AECountItems Error: "<< status << std::endl;
        return FilesToOpen;
    }

    // Walk list of pathnames selected
    for (unsigned int index=1; index<=count; index++)
    {
        FSRef parentDirectory;
        if (AEGetNthPtr(&(replyRecord.selection), index, typeFSRef, NULL, NULL, &parentDirectory, sizeof(FSRef), NULL)== noErr)
        {
            UInt8 FilePath[2048];
            if( FSRefMakePath (&parentDirectory, FilePath, sizeof(FilePath)) == noErr)
            {
                FilesToOpen.push_back(Path(reinterpret_cast<Char8*>(FilePath)));
            }
        }
    }
    NavDisposeReply(&replyRecord);
    
    return FilesToOpen;
}

Path CarbonWindowEventProducer::saveFileDialog(const std::string& DialogTitle,
                const std::vector<FileDialogFilter>& Filters,
                const std::string& InitialFile,
                const Path& InitialDirectory,
                bool PromptForOverwrite
                )
{
	Path FileToSave;
    OSStatus status;
    NavDialogRef SaveFileDialog;

    NavDialogCreationOptions dialogOptions;

    //Default options for dialog
    status = NavGetDefaultDialogCreationOptions(&dialogOptions);
    if(status != noErr)
    {
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: NavGetDefaultDialogCreationOptions Error: "<< status << std::endl;
	    return FileToSave;
    }

   // Make the window app-wide modal
   dialogOptions.modality = kWindowModalityAppModal;
   dialogOptions.parentWindow = _WindowRef;
   dialogOptions.optionFlags = kNavDefaultNavDlogOptions;
   dialogOptions.windowTitle = CFStringCreateWithCString(NULL, DialogTitle.c_str(), DialogTitle.size());
   if(PromptForOverwrite)
   {
       dialogOptions.optionFlags = dialogOptions.optionFlags ^ kNavDontConfirmReplacement;
   }
   else
   {
       dialogOptions.optionFlags = dialogOptions.optionFlags | kNavDontConfirmReplacement;
   }
   
   status = NavCreatePutFileDialog (
       &dialogOptions,
       kUnknownType,
       kUnknownType,
       NULL,
       NULL,
       &SaveFileDialog);
    
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: NavCreateGetFileDialog Error: "<< status << std::endl;
	    return FileToSave;
    }
    
    // Image Browser can open files with the ".imagebrowser" extension
    CFMutableArrayRef identifiers = CFArrayCreateMutable( kCFAllocatorDefault, 0, &kCFTypeArrayCallBacks );
    if(identifiers == NULL)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: CFArrayCreateMutable Error: NULL " <<  std::endl;
	    return FileToSave;
    }

    //Initial directory 
    FSSpec spec;
    status = PathToFSSpec(InitialDirectory.string().c_str(), spec);
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: PathToFSSpec Error: "<< status << std::endl;
	    return FileToSave;
    }
    AEDesc DefaultLocationAEDesc;
    status = AECreateDesc(typeFSS, &spec, sizeof(FSSpec), &DefaultLocationAEDesc);
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: AECreateDesc Error: "<< status << std::endl;
	    return FileToSave;
    }
    status = NavCustomControl( SaveFileDialog, kNavCtlSetLocation, &DefaultLocationAEDesc );
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: NavCustomControl Error: "<< status << std::endl;
	    return FileToSave;
    }
    AEDisposeDesc(&DefaultLocationAEDesc);
    
    //Initial filename
    status = NavDialogSetSaveFileName(SaveFileDialog,CFStringCreateWithCString(NULL, InitialFile.c_str(), InitialFile.size()));
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: NavDialogSetSaveFileName Error: "<< status << std::endl;
	    return FileToSave;
    }


    //Filters
    for(std::vector<FileDialogFilter>::const_iterator Itor(Filters.begin()) ; Itor != Filters.end(); ++Itor)
    {
        // create the image browser UTI conforming to "public.data" because it's a data file rather than a bundle 
        if(Itor->getFilter().compare("*") != 0)
        {
            CFStringRef FilterCFString = UTTypeCreatePreferredIdentifierForTag( kUTTagClassFilenameExtension, CFStringCreateWithCString(NULL, Itor->getFilter().c_str(), Itor->getFilter().size()),kUTTypeData );

            if(FilterCFString == NULL)
            {
                NavDialogDispose(SaveFileDialog);
                SWARNING << "CarbonWindowEventProducer::saveFileDialog: UTTypeCreatePreferredIdentifierForTag Error: NULL " <<  std::endl;
                return FileToSave;
            }
            //Itor->getName();
            CFArrayAppendValue( identifiers, FilterCFString );
        }
    }
    
    // filter by UTI
    //status = NavDialogSetFilterTypeIdentifiers( SaveFileDialog, identifiers );
    //if(status != noErr)
    //{
        //NavDialogDispose(SaveFileDialog);
        //SWARNING << "CarbonWindowEventProducer::saveFileDialog: NavDialogRun Error: "<< status << std::endl;
        //return FileToSave;
    //}
 
    //Open the dialog
    status = NavDialogRun(SaveFileDialog);
    if(status != noErr)
    {
        NavDialogDispose(SaveFileDialog);
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: NavDialogRun Error: "<< status << std::endl;
        return FileToSave;
    }

    //Get Reply
    NavReplyRecord replyRecord;
    status = NavDialogGetReply(SaveFileDialog, &replyRecord);
    NavDialogDispose(SaveFileDialog);
    //If user canceled then return empty
    if (!replyRecord.validRecord ||  status == userCanceledErr )
    {
        NavDisposeReply(&replyRecord);
        return FileToSave;
    }
    
    //Other Errors
    if(status != noErr)
    {
        NavDisposeReply(&replyRecord);
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: NavDialogGetReply Error: "<< status << std::endl;
        return FileToSave;
    }

    //Path to save file to
    long count = 0;
    if ( AECountItems(&replyRecord.selection, &count) != noErr ) 
    {
        NavDisposeReply(&replyRecord);
        SWARNING << "CarbonWindowEventProducer::saveFileDialog: AECountItems Error: "<< status << std::endl;
        return FileToSave;
    }

    // Get Path
    if (count==1)
    {
        FSRef parentDirectory;
        if (AEGetNthPtr(&(replyRecord.selection), 1, typeFSRef, NULL, NULL, &parentDirectory, sizeof(FSRef), NULL)== noErr)
        {
            UInt8 FilePath[2048];
            if( FSRefMakePath (&parentDirectory, FilePath, sizeof(FilePath)) == noErr)
            {
                FileToSave = Path(reinterpret_cast<Char8*>(FilePath));
            }
        }
    }
    NavDisposeReply(&replyRecord);

    //Filename
    CFStringRef SaveFileCFString = NavDialogGetSaveFileName(SaveFileDialog);
	char FileName[1024];
	CFStringGetCString(SaveFileCFString, FileName, sizeof(FileName), 0);
    FileToSave                   = FileToSave / Path(FileName);

    return FileToSave;
}

CGKeyCode CarbonWindowEventProducer::getKeyCode(osg::KeyEvent::Key TheKey)
{
    switch(TheKey)
    {
	////Alphabet
    case KeyEvent::KEY_A:
      return KeyA;
      break;
    case KeyEvent::KEY_B:
      return KeyB;
      break;
    case KeyEvent::KEY_C:
      return KeyC;
      break;
    case KeyEvent::KEY_D:
      return KeyD;
      break;
    case KeyEvent::KEY_E:
      return KeyE;
      break;
    case KeyEvent::KEY_F:
      return KeyF;
      break;
    case KeyEvent::KEY_G:
      return KeyG;
      break;
    case KeyEvent::KEY_H:
      return KeyH;
      break;
    case KeyEvent::KEY_I:
      return KeyI;
      break;
    case KeyEvent::KEY_J:
      return KeyJ;
      break;
    case KeyEvent::KEY_K:
      return KeyK;
      break;
    case KeyEvent::KEY_L:
      return KeyL;
      break;
    case KeyEvent::KEY_M:
      return KeyM;
      break;
    case KeyEvent::KEY_N:
      return KeyN;
      break;
    case KeyEvent::KEY_O:
      return KeyO;
      break;
    case KeyEvent::KEY_P:
      return KeyP;
      break;
    case KeyEvent::KEY_Q:
      return KeyQ;
      break;
    case KeyEvent::KEY_R:
      return KeyR;
      break;
    case KeyEvent::KEY_S:
      return KeyS;
      break;
    case KeyEvent::KEY_T:
      return KeyT;
      break;
    case KeyEvent::KEY_U:
      return KeyU;
      break;
    case KeyEvent::KEY_V:
      return KeyV;
      break;
    case KeyEvent::KEY_W:
      return KeyW;
      break;
    case KeyEvent::KEY_X:
      return KeyX;
      break;
    case KeyEvent::KEY_Y:
      return KeyY;
      break;
    case KeyEvent::KEY_Z:
      return KeyZ;
      break;
    //Numbers
    case KeyEvent::KEY_0:
      return Key0;
      break;
    case KeyEvent::KEY_1:
      return Key1;
      break;
    case KeyEvent::KEY_2:
      return Key2;
      break;
    case KeyEvent::KEY_3:
      return Key3;
      break;
    case KeyEvent::KEY_4:
      return Key4;
      break;
    case KeyEvent::KEY_5:
      return Key5;
      break;
    case KeyEvent::KEY_6:
      return Key6;
      break;
    case KeyEvent::KEY_7:
      return Key7;
      break;
    case KeyEvent::KEY_8:
      return Key8;
      break;
    case KeyEvent::KEY_9:
      return Key9;
      break;

    //Other
    case KeyEvent::KEY_MINUS:
      return KeyMinus;
      break;
    case KeyEvent::KEY_EQUALS:
      return KeyEquals;
      break;
    case KeyEvent::KEY_BACK_QUOTE:
      return KeyBackquote;
      break;
    case KeyEvent::KEY_TAB:
      return KeyTab;
      break;
    case KeyEvent::KEY_SPACE:
      return KeySpacebar;
      break;
    case KeyEvent::KEY_OPEN_BRACKET:
      return KeyLeftBracket;
      break;
    case KeyEvent::KEY_CLOSE_BRACKET:
      return KeyRightBracket;
      break;
    case KeyEvent::KEY_SEMICOLON:
      return KeySemicolon;
      break;
    case KeyEvent::KEY_COMMA:
      return KeyComma;
      break;
    case KeyEvent::KEY_PERIOD:
      return KeyPeriod;
      break;
    case KeyEvent::KEY_BACK_SLASH:
      return KeyBackslash;
      break;
    case KeyEvent::KEY_APOSTROPHE:
      return KeyApostrophe;
      break;
    case KeyEvent::KEY_SLASH:
      return KeySlash;
      break;

    //Non-visible
    case KeyEvent::KEY_ESCAPE:
      return KeyEscape;
      break;
    case KeyEvent::KEY_SHIFT:
      return KeyShift;
      break;
    case KeyEvent::KEY_CONTROL:
      return KeyControl;
      break;
    case KeyEvent::KEY_META:
      return KeyMacCommand;
      break;
    case KeyEvent::KEY_ALT:
      return KeyMenu;
      break;
    case KeyEvent::KEY_ENTER:
      return KeyReturn;
      break;
    //case KeyEvent::KEY_CANCEL:
      //return KeyCancel;
    //  break;
    case KeyEvent::KEY_CLEAR:
      return KeyClear;
      break;
    //case KeyEvent::KEY_PAUSE:
      //return KeyPause;
    //  break;
    case KeyEvent::KEY_CAPS_LOCK:
      return KeyCapsLock;
      break;
    case KeyEvent::KEY_END:
      return KeyEnd;
      break;
    case KeyEvent::KEY_HOME:
      return KeyHome;
      break;
    case KeyEvent::KEY_PAGE_UP:
      return KeyPageUp;
      break;
    case KeyEvent::KEY_PAGE_DOWN:
      return KeyPageDown;
      break;
    case KeyEvent::KEY_UP:
      return KeyUp;
      break;
    case KeyEvent::KEY_DOWN:
      return KeyDown;
      break;
    case KeyEvent::KEY_LEFT:
      return KeyLeft;
      break;
    case KeyEvent::KEY_RIGHT:
      return KeyRight;
      break;
    //case KeyEvent::KEY_PRINTSCREEN:
      //return KeySNAPSHOT;
    //  break;
    //case KeyEvent::KEY_INSERT:
      //return KeyInsert;
    //  break;
    case KeyEvent::KEY_DELETE:
      return KeyDelete;
      break;
    case KeyEvent::KEY_HELP:
      return KeyHelp;
      break;
    //case KeyEvent::KEY_NUM_LOCK:
      //return KeyNUMLOCK;
    //  break;
    //case KeyEvent::KEY_SCROLL_LOCK:
      //return KeySCROLL;
    //  break;
    case KeyEvent::KEY_BACK_SPACE:
      return KeyBackspace;
      break;

    //Function Keys
    case KeyEvent::KEY_F1:
      return KeyF1;
      break;
    case KeyEvent::KEY_F2:
      return KeyF2;
      break;
    case KeyEvent::KEY_F3:
      return KeyF3;
      break;
    case KeyEvent::KEY_F4:
      return KeyF4;
      break;
    case KeyEvent::KEY_F5:
      return KeyF5;
      break;
    case KeyEvent::KEY_F6:
      return KeyF6;
      break;
    case KeyEvent::KEY_F7:
      return KeyF7;
      break;
    case KeyEvent::KEY_F8:
      return KeyF8;
      break;
    case KeyEvent::KEY_F9:
      return KeyF9;
      break;
    case KeyEvent::KEY_F10:
      return KeyF10;
      break;
    case KeyEvent::KEY_F11:
      return KeyF11;
      break;
    case KeyEvent::KEY_F12:
      return KeyF12;
      break;
      
    //Numpad Keys
    case KeyEvent::KEY_NUMPAD_0:
      return KeyNum0;
      break;
    case KeyEvent::KEY_NUMPAD_1:
      return KeyNum1;
      break;
    case KeyEvent::KEY_NUMPAD_2:
      return KeyNum2;
      break;
    case KeyEvent::KEY_NUMPAD_3:
      return KeyNum3;
      break;
    case KeyEvent::KEY_NUMPAD_4:
      return KeyNum4;
      break;
    case KeyEvent::KEY_NUMPAD_5:
      return KeyNum5;
      break;
    case KeyEvent::KEY_NUMPAD_6:
      return KeyNum6;
      break;
    case KeyEvent::KEY_NUMPAD_7:
      return KeyNum7;
      break;
    case KeyEvent::KEY_NUMPAD_8:
      return KeyNum8;
      break;
    case KeyEvent::KEY_NUMPAD_9:
      return KeyNum9;
      break;
    case KeyEvent::KEY_MULTIPLY:
      return KeyMultiply;
      break;
    case KeyEvent::KEY_ADD:
      return KeyAdd;
      break;
    case KeyEvent::KEY_SUBTRACT:
      return KeySubtract;
      break;
    case KeyEvent::KEY_DIVIDE:
      return KeyDivide;
      break;
    case KeyEvent::KEY_DECIMAL:
      return KeyDecimal;
      break;
    case KeyEvent::KEY_NUMPAD_EQUALS:
      return KeyNumEqual;
      break;
	
    case KeyEvent::KEY_UNKNOWN:
	default:
	  return 0;
	}
}

osg::KeyEvent::KeyState CarbonWindowEventProducer::getKeyState(osg::KeyEvent::Key TheKey) const
{
    if(CGEventSourceKeyState(kCGEventSourceStateCombinedSessionState,getKeyCode(TheKey)))
	{
        return KeyEvent::KEY_STATE_DOWN;
	}
	else
	{
		return KeyEvent::KEY_STATE_UP;
	}
}

WindowPtr CarbonWindowEventProducer::initWindow(void)
{
	WindowPtr MyWindow = Inherited::initWindow();
    
    attachWindow();
    
    EventTypeSpec eventList[] =
    {
		{ kEventClassKeyboard, kEventRawKeyDown},
        { kEventClassKeyboard, kEventRawKeyRepeat},
        { kEventClassKeyboard, kEventRawKeyUp},
        { kEventClassKeyboard, kEventRawKeyModifiersChanged},
        { kEventClassMouse, kEventMouseDown },
        { kEventClassMouse, kEventMouseUp },
        { kEventClassMouse, kEventMouseMoved },
        { kEventClassMouse, kEventMouseDragged },
        { kEventClassMouse, kEventMouseWheelMoved },
        //{ kEventClassWindow, kEventWindowActivate },
        //{ kEventClassWindow, kEventWindowDeactivate },
        { kEventClassWindow, kEventWindowCollapsed },
        { kEventClassWindow, kEventWindowExpanded },
        { kEventClassWindow, kEventWindowClose },
        { kEventClassWindow, kEventWindowClosed },
        { kEventClassWindow, kEventWindowDrawContent },
        { kEventClassWindow, kEventWindowBoundsChanged },
        { kEventClassWindow, kEventAppActivated },
        { kEventClassWindow, kEventAppDeactivated },
    };
    InstallWindowEventHandler(_WindowRef, _EventHandlerUPP, GetEventTypeCount(eventList), eventList, &(_WindowId), 0);

    // Initialize OpenGL
    GLint attribs[] = { AGL_RGBA, AGL_DOUBLEBUFFER, AGL_DEPTH_SIZE, 16, AGL_STENCIL_SIZE, 8, AGL_ACCELERATED, AGL_NO_RECOVERY, AGL_NONE };
    //GLint attribs[] = { AGL_RGBA, AGL_DOUBLEBUFFER, AGL_DEPTH_SIZE, 16, AGL_STENCIL_SIZE, 8,  AGL_NONE };
    AGLPixelFormat pixelFormat = aglChoosePixelFormat(0, 0, attribs);
    if (pixelFormat == 0)
        std::cerr << "Cannot choose pixel format" << std::endl;
    _Context = aglCreateContext(pixelFormat, 0);
    aglDestroyPixelFormat(pixelFormat);
    if (_Context == 0)
        std::cerr << "Cannot create context" << std::endl;
    aglSetWindowRef(_Context,_WindowRef);
    
    //Attach Window
    beginEditCP(CarbonWindow::Ptr::dcast(getWindow()), CarbonWindow::ContextFieldMask);
        CarbonWindow::Ptr::dcast(getWindow())->setContext(_Context);
    endEditCP(CarbonWindow::Ptr::dcast(getWindow()), CarbonWindow::ContextFieldMask);
	
    return MyWindow;
}


OSStatus CarbonWindowEventProducer::internalEventHandler(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    ::UInt32 eventClass = GetEventClass(event);
    switch (eventClass)
    {
    // Mouse events
    case kEventClassMouse:
		return handleMouseEvent(nextHandler, event, userData);

    // Key press events
    case kEventClassKeyboard:
		return handleKeyEvent(nextHandler, event, userData);

    // Window events
    case kEventClassWindow:
		return handleWindowEvent(nextHandler, event, userData);

    //App events
    case kEventClassApplication:
		return handleAppEvent(nextHandler, event, userData);

    default:
        return eventNotHandledErr;
    }   
    return noErr;
}


OSStatus CarbonWindowEventProducer::handleMouseEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

    // Get the window
    WindowRef window;
    err = GetEventParameter(event, kEventParamWindowRef, typeWindowRef, 0, sizeof(window), 0, &window);
    if (err != noErr)
        return err;

    SetPortWindowPort(window);

    // Get the location of the cursor
    ::HIPoint location;
    err = GetEventParameter(event, kEventParamWindowMouseLocation, typeHIPoint, 0, sizeof(location), 0, &location);
    if (err != noErr)
        //std::vector<osg::Path, std::allocator<osg::Path> >;
        return err;
    location.y -= 22.0f;

    //Check that the mouse is withing the content area
    WindowPartCode part;
    GetEventParameter (event, kEventParamWindowPartCode, typeWindowPartCode,
            NULL, sizeof(part), NULL, &part);

    if(part != inContent)
    {
        return eventNotHandledErr;
    }

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    //Get Mouse Delta
    Vec2f MouseDelta;
    switch(eventKind)
    {
        case kEventMouseMoved:
        case kEventMouseDragged:
            {
                ::HIPoint delta;
                err = GetEventParameter(event, kEventParamMouseDelta, typeHIPoint, 0, sizeof(delta), 0, &delta);
                if (err != noErr)
                    return err;
                MouseDelta.setValues(delta.x,delta.y);
            }
            break;
    }

    //Get Mouse Button
    MouseEvent::MouseButton TheMouseButton;
    switch(eventKind)
    {
        case kEventMouseDown:
        case kEventMouseUp:
        case kEventMouseDragged:
            {
                // Get the mouse button
                EventMouseButton mouseButton;
                err = GetEventParameter(event, kEventParamMouseButton, typeMouseButton, 0, sizeof(mouseButton), 0, &mouseButton);
                if (err != noErr)
                    return err;

                switch (mouseButton)
                {
                    case kEventMouseButtonPrimary: // left button
                        TheMouseButton = MouseEvent::BUTTON1;
                        break;
                    case kEventMouseButtonSecondary: // right button
                        TheMouseButton = MouseEvent::BUTTON3;
                        break;
                    case kEventMouseButtonTertiary: // middle button
                        TheMouseButton = MouseEvent::BUTTON2;
                        break;
                    case 4:
                        TheMouseButton = MouseEvent::BUTTON4;
                        break;
                    case 5:
                        TheMouseButton = MouseEvent::BUTTON5;
                        break;
                    case 6:
                        TheMouseButton = MouseEvent::BUTTON6;
                        break;
                    case 7:
                        TheMouseButton = MouseEvent::BUTTON7;
                        break;
                    case 8:
                        TheMouseButton = MouseEvent::BUTTON8;
                        break;
                    case 9:
                        TheMouseButton = MouseEvent::BUTTON9;
                        break;
                    case 10:
                        TheMouseButton = MouseEvent::BUTTON10;
                        break;
                    default:
                        TheMouseButton = MouseEvent::NO_BUTTON;
                        break;
                }
                break;
            }
    }
    switch (eventKind)
    {
        // mouse button pressed
        case kEventMouseDown:
            produceMousePressed(TheMouseButton, Pnt2f(location.x, location.y));
            break;


            // mouse button released
        case kEventMouseUp:
            produceMouseReleased(TheMouseButton, Pnt2f(location.x, location.y));
            break;

            //Mouse Moved
        case kEventMouseMoved:
            produceMouseMoved(Pnt2f(location.x, location.y), MouseDelta);
            break;

            // mouse moved while a button is pressed
        case kEventMouseDragged:
            produceMouseMoved(Pnt2f(location.x, location.y), MouseDelta);
            produceMouseDragged(TheMouseButton, Pnt2f(location.x, location.y), MouseDelta);
            break;

            // mouse wheel moved
        case kEventMouseWheelMoved:
            {
                EventMouseWheelAxis axis;
                SInt32 delta;

                err = GetEventParameter( event, kEventParamMouseWheelAxis, 
                        typeMouseWheelAxis, NULL, sizeof(axis), NULL, &axis );
                if (err != noErr)
                    return err;

                err = GetEventParameter( event, kEventParamMouseWheelDelta, 
                        typeLongInteger, NULL, sizeof(delta), NULL, &delta );
                if (err != noErr)
                    return err;

                if ( axis == kEventMouseWheelAxisY )
                {
                    produceMouseWheelMoved(delta, Pnt2f(location.x, location.y));
                }
            }
            break;

        default:
            std::cerr << "handleMouseEvent event not handled" << std::endl;
            break;

    }

    // We have to return eventNotHandledErr, otherwise the system is
    // not able to operate the menu and the window border
    return eventNotHandledErr;
}

OSStatus CarbonWindowEventProducer::handleWindowEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

    // Get the window
    WindowRef window;
    err = GetEventParameter(event, kEventParamDirectObject, typeWindowRef, 0, sizeof(window), 0, &window);
    if (err != noErr)
        return err;

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    switch (eventKind)
    {
    // Quit the application when the user closes the window
    case kEventWindowClosed:
            aglDestroyContext(_Context);
            produceWindowClosing();
            DisposeEventHandlerUPP(_EventHandlerUPP);
            _CarbonWindowToProducerMap.erase(_CarbonWindowToProducerMap.find(_WindowId));
            produceWindowClosed();
            return noErr;
		  break;
    
	 // Quit the application when the user closes the window
    case kEventWindowClose:
          disposeWindow();
        return noErr;
		  break;

    case kEventWindowCollapsed:
		  produceWindowIconified();
        return noErr;
		  break;

    case kEventWindowExpanded:
		  produceWindowDeiconified();
        return noErr;
		  break;

    // Draw the contents of the window
    case kEventWindowDrawContent:
        internalDraw();
        return noErr;

    case kEventWindowBoundsChanged:
        {
            // Update the GL context
            aglUpdateContext(CarbonWindow::Ptr::dcast(getWindow())->getContext());

            // Find out if we have a move or a resize situation
            ::UInt32 attributes;
            GetEventParameter(event, kEventParamAttributes, typeUInt32, 0, sizeof(attributes), 0, &attributes);

            if ((attributes & kWindowBoundsChangeSizeChanged) != 0)
            {
                // Get the new bounds of the window
                Rect bounds;
                GetEventParameter(event, kEventParamCurrentBounds, typeQDRectangle, 0, sizeof(Rect), 0, &bounds);

                // Resize the OpenSG Window
                GLsizei width = bounds.right - bounds.left;
                GLsizei height = bounds.bottom - bounds.top;
				getWindow()->resize(width, height );
				internalReshape(Vec2f(width, height));
            }

            return noErr;
        }

    default:
        return eventNotHandledErr;
    }
}

OSStatus CarbonWindowEventProducer::handleAppEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

    // Get the window
    WindowRef window;
    err = GetEventParameter(event, kEventParamDirectObject, typeWindowRef, 0, sizeof(window), 0, &window);
    if (err != noErr)
        return err;

    // Handle the different kinds of events
    ::UInt32 eventKind = GetEventKind(event);
    switch (eventKind)
    {
    case kEventAppActivated:
		  produceWindowActivated();
        return noErr;
		  break;

    case kEventAppDeactivated:
		  produceWindowDeactivated();
        return noErr;
		  break;
	 }
}
OSStatus CarbonWindowEventProducer::handleKeyEvent(EventHandlerCallRef nextHandler, EventRef event, void *userData)
{
    OSStatus err;

	::UInt32 key;
	err = GetEventParameter(event, kEventParamKeyCode, typeUInt32, 0, sizeof(key), 0, &key);
	if (err != noErr)
		return err;
	
	
	::UInt32 keyModifiers;
	err = GetEventParameter(event, kEventParamKeyModifiers, typeUInt32, 0, sizeof(keyModifiers), 0, &keyModifiers);
	if (err != noErr)
		return err;
		
    ::UInt32 eventKind = GetEventKind(event);
	switch(eventKind)
	{
		case kEventRawKeyDown:
			produceKeyPressed(determineKey(key),determineKeyModifiers(keyModifiers));				
			break;
		case kEventRawKeyUp:
			produceKeyReleased(determineKey(key),determineKeyModifiers(keyModifiers));
			break;
		case kEventRawKeyRepeat:
			produceKeyPressed(determineKey(key),determineKeyModifiers(keyModifiers));
			break;
		case kEventRawKeyModifiersChanged:
			if((determineKeyModifiers(keyModifiers) & KeyEvent::KEY_MODIFIER_META) &&
			   !(_modifierKeyState & KeyEvent::KEY_MODIFIER_META))
			{
				//Meta key pressed
				produceKeyPressed(KeyEvent::KEY_META, determineKeyModifiers(keyModifiers));
			}
			if(!(determineKeyModifiers(keyModifiers) & KeyEvent::KEY_MODIFIER_META) &&
			   (_modifierKeyState & KeyEvent::KEY_MODIFIER_META))
			{
				//Meta key released
				produceKeyReleased(KeyEvent::KEY_META, determineKeyModifiers(keyModifiers));
			}
			if((determineKeyModifiers(keyModifiers) & KeyEvent::KEY_MODIFIER_ALT) &&
			   !(_modifierKeyState & KeyEvent::KEY_MODIFIER_ALT))
			{
				//Alt key pressed
				produceKeyPressed(KeyEvent::KEY_ALT, determineKeyModifiers(keyModifiers));
			}
			if(!(determineKeyModifiers(keyModifiers) & KeyEvent::KEY_MODIFIER_ALT) &&
			   (_modifierKeyState & KeyEvent::KEY_MODIFIER_ALT))
			{
				//Alt key released
				produceKeyReleased(KeyEvent::KEY_ALT, determineKeyModifiers(keyModifiers));
			}
			if((determineKeyModifiers(keyModifiers) & KeyEvent::KEY_MODIFIER_CONTROL) &&
			   !(_modifierKeyState & KeyEvent::KEY_MODIFIER_CONTROL))
			{
				//Control key pressed
				produceKeyPressed(KeyEvent::KEY_CONTROL, determineKeyModifiers(keyModifiers));
			}
			if(!(determineKeyModifiers(keyModifiers) & KeyEvent::KEY_MODIFIER_CONTROL) &&
			   (_modifierKeyState & KeyEvent::KEY_MODIFIER_CONTROL))
			{
				//Control key released
				produceKeyReleased(KeyEvent::KEY_CONTROL, determineKeyModifiers(keyModifiers));
			}
			_modifierKeyState = determineKeyModifiers(keyModifiers);
			break;
		default:
			break;
	}

    return noErr;
}

UInt32 CarbonWindowEventProducer::determineKeyModifiers(::UInt32 keyModifiers)
{
   UInt32 Modifiers = 0;

   if(keyModifiers & shiftKey)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_SHIFT;
   }
   if(keyModifiers & controlKey)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_CONTROL;
   }
   if(keyModifiers & optionKey)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_ALT;
   }
   if(keyModifiers & alphaLock)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_CAPS_LOCK;
   }
   if(keyModifiers & cmdKey)
   {
      Modifiers |= KeyEvent::KEY_MODIFIER_META;
   }
   //if(GetKeyState(VK_NUMLOCK)>0)
   //{
   //   Modifiers |= KeyEvent::KEY_MODIFIER_NUM_LOCK;
   //}
   //if(GetKeyState(VK_SCROLL)>0)
   //{
   //   Modifiers |= KeyEvent::KEY_MODIFIER_SCROLL_LOCK;
   //}
   return Modifiers;
}

KeyEvent::Key CarbonWindowEventProducer::determineKey(::UInt32 key)
{
    KeyEvent::Key OSGKey;
	switch(key)
	{
	//Alphabet
	case KeyA:
	  OSGKey = KeyEvent::KEY_A;
	  break;
	case KeyB:
	  OSGKey = KeyEvent::KEY_B;
	  break;
	case KeyC:
	  OSGKey = KeyEvent::KEY_C;
	  break;
	case KeyD:
	  OSGKey = KeyEvent::KEY_D;
	  break;
	case KeyE:
	  OSGKey = KeyEvent::KEY_E;
	  break;
	case KeyF:
	  OSGKey = KeyEvent::KEY_F;
	  break;
	case KeyG:
	  OSGKey = KeyEvent::KEY_G;
	  break;
	case KeyH:
	  OSGKey = KeyEvent::KEY_H;
	  break;
	case KeyI:
	  OSGKey = KeyEvent::KEY_I;
	  break;
	case KeyJ:
	  OSGKey = KeyEvent::KEY_J;
	  break;
	case KeyK:
	  OSGKey = KeyEvent::KEY_K;
	  break;
	case KeyL:
	  OSGKey = KeyEvent::KEY_L;
	  break;
	case KeyM:
	  OSGKey = KeyEvent::KEY_M;
	  break;
	case KeyN:
	  OSGKey = KeyEvent::KEY_N;
	  break;
	case KeyO:
	  OSGKey = KeyEvent::KEY_O;
	  break;
	case KeyP:
	  OSGKey = KeyEvent::KEY_P;
	  break;
	case KeyQ:
	  OSGKey = KeyEvent::KEY_Q;
	  break;
	case KeyR:
	  OSGKey = KeyEvent::KEY_R;
	  break;
	case KeyS:
	  OSGKey = KeyEvent::KEY_S;
	  break;
	case KeyT:
	  OSGKey = KeyEvent::KEY_T;
	  break;
	case KeyU:
	  OSGKey = KeyEvent::KEY_U;
	  break;
	case KeyV:
	  OSGKey = KeyEvent::KEY_V;
	  break;
	case KeyW:
	  OSGKey = KeyEvent::KEY_W;
	  break;
	case KeyX:
	  OSGKey = KeyEvent::KEY_X;
	  break;
	case KeyY:
	  OSGKey = KeyEvent::KEY_Y;
	  break;
	case KeyZ:
	  OSGKey = KeyEvent::KEY_Z;
	  break;
	//Numbers
	case Key0:
	  OSGKey = KeyEvent::KEY_0;
	  break;
	case Key1:
	  OSGKey = KeyEvent::KEY_1;
	  break;
	case Key2:
	  OSGKey = KeyEvent::KEY_2;
	  break;
	case Key3:
	  OSGKey = KeyEvent::KEY_3;
	  break;
	case Key4:
	  OSGKey = KeyEvent::KEY_4;
	  break;
	case Key5:
	  OSGKey = KeyEvent::KEY_5;
	  break;
	case Key6:
	  OSGKey = KeyEvent::KEY_6;
	  break;
	case Key7:
	  OSGKey = KeyEvent::KEY_7;
	  break;
	case Key8:
	  OSGKey = KeyEvent::KEY_8;
	  break;
	case Key9:
	  OSGKey = KeyEvent::KEY_9;
	  break;

	//Other
	case KeyMinus:
	  OSGKey = KeyEvent::KEY_MINUS;
	  break;
	case KeyEquals:
	  OSGKey = KeyEvent::KEY_EQUALS;
	  break;
	case KeyBackquote:
	  OSGKey = KeyEvent::KEY_BACK_QUOTE;
	  break;
	case KeyTab:
	  OSGKey = KeyEvent::KEY_TAB;
	  break;
	case KeySpacebar:
	  OSGKey = KeyEvent::KEY_SPACE;
	  break;
	case KeyLeftBracket:
	  OSGKey = KeyEvent::KEY_OPEN_BRACKET;
	  break;
	case KeyRightBracket:
	  OSGKey = KeyEvent::KEY_CLOSE_BRACKET;
	  break;
	case KeySemicolon:
	  OSGKey = KeyEvent::KEY_SEMICOLON;
	  break;
	case KeyComma:
	  OSGKey = KeyEvent::KEY_COMMA;
	  break;
	case KeyPeriod:
	  OSGKey = KeyEvent::KEY_PERIOD;
	  break;
	case KeyBackslash:
	  OSGKey = KeyEvent::KEY_BACK_SLASH;
	  break;
	case KeyApostrophe:
	  OSGKey = KeyEvent::KEY_APOSTROPHE;
	  break;
	case KeySlash:
	  OSGKey = KeyEvent::KEY_SLASH;
	  break;

	//Non-visible
	case KeyEscape:
	  OSGKey = KeyEvent::KEY_ESCAPE;
	  break;
	case KeyShift:
	  OSGKey = KeyEvent::KEY_SHIFT;
	  break;
	case KeyControl:
	  OSGKey = KeyEvent::KEY_CONTROL;
	  break;
	case KeyMacCommand:
	  OSGKey = KeyEvent::KEY_META;
	  break;
	case KeyMenu:
	  OSGKey = KeyEvent::KEY_ALT;
	  break;
	case KeyReturn:
	  OSGKey = KeyEvent::KEY_ENTER;
	  break;
	//case KeyCancel:
	//  OSGKey = KeyEvent::KEY_CANCEL;
	//  break;
	case KeyClear:
	  OSGKey = KeyEvent::KEY_CLEAR;
	  break;
	//case KeyPause:
	//  OSGKey = KeyEvent::KEY_PAUSE;
	//  break;
	case KeyCapsLock:
	  OSGKey = KeyEvent::KEY_CAPS_LOCK;
	  break;
	case KeyEnd:
	  OSGKey = KeyEvent::KEY_END;
	  break;
	case KeyHome:
	  OSGKey = KeyEvent::KEY_HOME;
	  break;
	case KeyPageUp:
	  OSGKey = KeyEvent::KEY_PAGE_UP;
	  break;
	case KeyPageDown:
	  OSGKey = KeyEvent::KEY_PAGE_DOWN;
	  break;
	case KeyUp:
	  OSGKey = KeyEvent::KEY_UP;
	  break;
	case KeyDown:
	  OSGKey = KeyEvent::KEY_DOWN;
	  break;
	case KeyLeft:
	  OSGKey = KeyEvent::KEY_LEFT;
	  break;
	case KeyRight:
	  OSGKey = KeyEvent::KEY_RIGHT;
	  break;
	//case KeySNAPSHOT:
	//  OSGKey = KeyEvent::KEY_PRINTSCREEN;
	//  break;
	//case KeyInsert:
	//  OSGKey = KeyEvent::KEY_INSERT;
	//  break;
	case KeyDelete:
	  OSGKey = KeyEvent::KEY_DELETE;
	  break;
	case KeyHelp:
	  OSGKey = KeyEvent::KEY_HELP;
	  break;
	//case KeyNUMLOCK:
	//  OSGKey = KeyEvent::KEY_NUM_LOCK;
	//  break;
	//case KeySCROLL:
	//  OSGKey = KeyEvent::KEY_SCROLL_LOCK;
	//  break;
	case KeyBackspace:
	  OSGKey = KeyEvent::KEY_BACK_SPACE;
	  break;

	//Function Keys
	case KeyF1:
	  OSGKey = KeyEvent::KEY_F1;
	  break;
	case KeyF2:
	  OSGKey = KeyEvent::KEY_F2;
	  break;
	case KeyF3:
	  OSGKey = KeyEvent::KEY_F3;
	  break;
	case KeyF4:
	  OSGKey = KeyEvent::KEY_F4;
	  break;
	case KeyF5:
	  OSGKey = KeyEvent::KEY_F5;
	  break;
	case KeyF6:
	  OSGKey = KeyEvent::KEY_F6;
	  break;
	case KeyF7:
	  OSGKey = KeyEvent::KEY_F7;
	  break;
	case KeyF8:
	  OSGKey = KeyEvent::KEY_F8;
	  break;
	case KeyF9:
	  OSGKey = KeyEvent::KEY_F9;
	  break;
	case KeyF10:
	  OSGKey = KeyEvent::KEY_F10;
	  break;
	case KeyF11:
	  OSGKey = KeyEvent::KEY_F11;
	  break;
	case KeyF12:
	  OSGKey = KeyEvent::KEY_F12;
	  break;
	  
	//Numpad Keys
	case KeyNum0:
	  OSGKey = KeyEvent::KEY_NUMPAD_0;
	  break;
	case KeyNum1:
	  OSGKey = KeyEvent::KEY_NUMPAD_1;
	  break;
	case KeyNum2:
	  OSGKey = KeyEvent::KEY_NUMPAD_2;
	  break;
	case KeyNum3:
	  OSGKey = KeyEvent::KEY_NUMPAD_3;
	  break;
	case KeyNum4:
	  OSGKey = KeyEvent::KEY_NUMPAD_4;
	  break;
	case KeyNum5:
	  OSGKey = KeyEvent::KEY_NUMPAD_5;
	  break;
	case KeyNum6:
	  OSGKey = KeyEvent::KEY_NUMPAD_6;
	  break;
	case KeyNum7:
	  OSGKey = KeyEvent::KEY_NUMPAD_7;
	  break;
	case KeyNum8:
	  OSGKey = KeyEvent::KEY_NUMPAD_8;
	  break;
	case KeyNum9:
	  OSGKey = KeyEvent::KEY_NUMPAD_9;
	  break;
	case KeyMultiply:
	  OSGKey = KeyEvent::KEY_MULTIPLY;
	  break;
	case KeyAdd:
	  OSGKey = KeyEvent::KEY_ADD;
	  break;
	case KeySubtract:
	  OSGKey = KeyEvent::KEY_SUBTRACT;
	  break;
	case KeyDivide:
	  OSGKey = KeyEvent::KEY_DIVIDE;
	  break;
	case KeyDecimal:
	  OSGKey = KeyEvent::KEY_DECIMAL;
	  break;
	case KeyNumEqual:
	  OSGKey = KeyEvent::KEY_NUMPAD_EQUALS;
	  break;
	  
	default:
	  OSGKey = KeyEvent::KEY_UNKNOWN;
	  break;
	}
	return OSGKey;
}

void CarbonWindowEventProducer::setPosition(Pnt2f Pos)
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
	
	Vec3s Size(GlobalBounds.right - GlobalBounds.left, GlobalBounds.bottom - GlobalBounds.top);
	GlobalBounds.left = Pos.x();
	GlobalBounds.top = Pos.y();
	GlobalBounds.right = GlobalBounds.left + Size.x();
	GlobalBounds.bottom = GlobalBounds.top + Size.y();
	SetWindowBounds(_WindowRef,kWindowStructureRgn, &GlobalBounds);
}

Pnt2f CarbonWindowEventProducer::getPosition(void) const
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
    return Pnt2f(GlobalBounds.left, GlobalBounds.top);
}


void CarbonWindowEventProducer::setSize(Vec2us Size)
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
	
	GlobalBounds.right = GlobalBounds.left + Size.x();
	GlobalBounds.bottom = GlobalBounds.top + Size.y();
	SetWindowBounds(_WindowRef,kWindowStructureRgn, &GlobalBounds);
}

Vec2f CarbonWindowEventProducer::getSize(void) const
{
	::Rect GlobalBounds;
	GetWindowBounds(_WindowRef, kWindowStructureRgn, &GlobalBounds);
    return Vec2f(GlobalBounds.right - GlobalBounds.left, GlobalBounds.bottom - GlobalBounds.top);
}

void CarbonWindowEventProducer::setFocused(bool Focused)
{
	ActivateWindow(_WindowRef, Focused);
}

bool CarbonWindowEventProducer::getFocused(void) const
{
    return IsWindowActive(_WindowRef);
}

void CarbonWindowEventProducer::setVisible(bool Visible)
{
	if(Visible)
	{
		ShowWindow(_WindowRef);
	}
	else
	{
		HideWindow(_WindowRef);
	}
}

bool CarbonWindowEventProducer::getVisible(void) const
{
    return IsWindowVisible(_WindowRef);
}

void CarbonWindowEventProducer::setIconify(bool Iconify)
{
	CollapseWindow(_WindowRef, Iconify);
}

bool CarbonWindowEventProducer::getIconify(void) const
{
    return IsWindowCollapsed(_WindowRef);
}

void CarbonWindowEventProducer::setFullscreen(bool Fullscreen)
{
	if(Fullscreen)
	{
		::Ptr      _OldScreenState;
      assert(false && "Not Implemented");
		//CGCaptureAllDisplays();
		//BeginFullScreen(&_OldScreenState, NULL, 0, 0, &_WindowRef, NULL, 0);
	}
	else
	{
		//EndFullScreen(NULL, NULL);
	}
}

bool CarbonWindowEventProducer::getFullscreen(void) const
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
}

void CarbonWindowEventProducer::setTitle(const std::string& TitleText)
{
    SetWindowTitleWithCFString(_WindowRef, CFStringCreateWithCString(NULL, TitleText.c_str(), TitleText.size()));
}

std::string CarbonWindowEventProducer::getTitle(void)
{
	CFStringRef AppleString;
	CopyWindowTitleAsCFString(_WindowRef, &AppleString);
	char value[1024];
	CFStringGetCString(AppleString, value, sizeof(value), 0);
	CFRelease(AppleString);
	
    return std::string(value);
}

void CarbonWindowEventProducer::setRisizable(bool IsResizable)
{
	//_WindowRef->kWindowResizableAttribute = (1L << 4);

	
    //TODO: Implement
    assert(false && "Not Implemented");
	
}

bool CarbonWindowEventProducer::getRisizable(void)
{
	WindowAttributes Attributes;
	GetWindowAttributes(_WindowRef, &Attributes);
	
    //TODO: Implement
	
    
    return (Attributes & kWindowResizableAttribute);
	
}

void CarbonWindowEventProducer::setDrawBorder(bool DrawBorder)
{
    //TODO: Implement
    assert(false && "Not Implemented");
}

bool CarbonWindowEventProducer::getDrawBorder(void)
{
    //TODO: Implement
    assert(false && "Not Implemented");
    return false;
}


void CarbonWindowEventProducer::draw(void)
{
    internalDraw();
}

void CarbonWindowEventProducer::update(void)
{
    //Updating
    Time Now(getSystemTime());
    Time ElapsedTime(Now - getLastUpdateTime());
    if(ElapsedTime > 0.0 && ElapsedTime < 10.0)
    {
        produceUpdate(ElapsedTime);
    }

    beginEditCP(CarbonWindowEventProducerPtr(this), LastUpdateTimeFieldMask);
        setLastUpdateTime(Now);
    endEditCP(CarbonWindowEventProducerPtr(this), LastUpdateTimeFieldMask);
}

bool CarbonWindowEventProducer::attachWindow(void)
{
    assert(_WindowId != 0);
    
    if(_CarbonWindowToProducerMap.find(_WindowId) != _CarbonWindowToProducerMap.end())
    {
        return false;
    }
    
    _CarbonWindowToProducerMap[_WindowId] = CarbonWindowEventProducerPtr(this);
    
    return true;
}

UInt32 CarbonWindowEventProducer::getKeyModifiers(void) const
{
    return determineKeyModifiers(GetCurrentEventKeyModifiers());
}

Pnt2f CarbonWindowEventProducer::getMousePosition(void) const
{
	::Point MousePositioon;
	GetGlobalMouse(&MousePositioon);
	
	//SetPortWindowPort(_WindowRef);

    return Pnt2f(MousePositioon.h, MousePositioon.v-22.0f) - Vec2f(getPosition());
}


std::string CarbonWindowEventProducer::getClipboard(void) const
{
    OSStatus            err = noErr;
    std::string Result("");
    
    //Create clipboard reference
    PasteboardRef theClipboard;
    err = PasteboardCreate( kPasteboardClipboard, &theClipboard );
    if(err != noErr)
    {
        SWARNING << "CarbonWindowEventProducer::getClipboard: PasteboardCreate Error: "<< err << std::endl;
        return Result;
    }

    PasteboardSyncFlags syncFlags;
    ItemCount           itemCount;

    syncFlags = PasteboardSynchronize( theClipboard );// 1
    if(syncFlags&kPasteboardModified)
    {
        SWARNING << "CarbonWindowEventProducer::getClipboard: PasteboardSynchronize Error: badPasteboardSyncErr "<< badPasteboardSyncErr << std::endl;
        CFRelease (theClipboard);
        return Result;
    }

    err = PasteboardGetItemCount( theClipboard, &itemCount );// 2
    if(err != noErr)
    {
        SWARNING << "CarbonWindowEventProducer::getClipboard: PasteboardGetItemCount Error: "<< err << std::endl;
        CFRelease (theClipboard);
        return Result;
    }

    for( UInt32 itemIndex = 1; itemIndex <= itemCount; itemIndex++ )
    {
        PasteboardItemID    itemID;
        CFArrayRef          flavorTypeArray;
        CFIndex             flavorCount;

        err = PasteboardGetItemIdentifier( theClipboard, itemIndex, &itemID );// 3
        if(err != noErr)
        {
            SWARNING << "carbonwindoweventproducer::getclipboard: PasteboardGetItemIdentifier error: "<< err << std::endl;
            CFRelease (theClipboard);
            return Result;
        }

        err = PasteboardCopyItemFlavors( theClipboard, itemID, &flavorTypeArray );// 4
        if(err != noErr)
        {
            SWARNING << "carbonwindoweventproducer::getclipboard: PasteboardCopyItemFlavors error: "<< err << std::endl;
            CFRelease (theClipboard);
            return Result;
        }

        flavorCount = CFArrayGetCount( flavorTypeArray );// 5

        for( CFIndex flavorIndex = 0; flavorIndex < flavorCount; flavorIndex++ )
        {
            CFStringRef             flavorType;
            CFDataRef               flavorData;
            CFIndex                 flavorDataSize;

            flavorType = (CFStringRef)CFArrayGetValueAtIndex( flavorTypeArray,// 6
                                                                 flavorIndex );
 

            if (UTTypeConformsTo(flavorType, CFSTR("public.utf8-plain-text")))// 7
            {
                err = PasteboardCopyItemFlavorData( theClipboard, itemID, // 8
                                                    flavorType, &flavorData );
                if(err != noErr)
                {
                    SWARNING << "CarbonWindowEventProducer::getClipboard: PasteboardCopyItemFlavorData Error: "<< err << std::endl;
                    CFRelease (flavorTypeArray);
                    CFRelease (theClipboard);
                    return Result;
                }
                
                flavorDataSize = CFDataGetLength( flavorData );

                for( short dataIndex = 0; dataIndex < flavorDataSize; ++dataIndex )
                {
                    Result += *(CFDataGetBytePtr( flavorData ) + dataIndex);
                }
                
                CFRelease (flavorData);
            }
        }
        CFRelease (flavorTypeArray);
    }
    CFRelease (theClipboard);
    return Result;
}

void CarbonWindowEventProducer::putClipboard(const std::string Value)
{
    OSStatus err = noErr;

    //Create clipboard reference
    PasteboardRef theClipboard;
    err = PasteboardCreate( kPasteboardClipboard, &theClipboard );
    if(err != noErr)
    {
        SWARNING << "CarbonWindowEventProducer::putClipboard: PasteboardCreate Error: "<< err << std::endl;
        return;
    }

    //Add text to clipboard
    PasteboardSyncFlags syncFlags;
    TXNOffset           start, end;
    Handle              dataHandle;
    CFDataRef           textData = NULL;
     

    //Clear clipboard
    err = PasteboardClear( theClipboard );
    if(err != noErr)
    {
        SWARNING << "CarbonWindowEventProducer::putClipboard: PasteboardClear Error: "<< err << std::endl;
        CFRelease (theClipboard);
        return;
    }

    syncFlags = PasteboardSynchronize( theClipboard );
    //if(!(syncFlags&kPasteboardModified))
    //{
        //SWARNING << "CarbonWindowEventProducer::putClipboard: PasteboardSynchronize Error: kPasteboardModified "<< badPasteboardSyncErr << std::endl;
        //return;
    //}
    if(!(syncFlags&kPasteboardClientIsOwner))
    {
        SWARNING << "CarbonWindowEventProducer::putClipboard: PasteboardSynchronize Error: kPasteboardClientIsOwner "<< notPasteboardOwnerErr << std::endl;
        CFRelease (theClipboard);
        return;
    }

    textData = CFDataCreate( NULL, reinterpret_cast<const UInt8*>(Value.c_str()), Value.size() );

    err = PasteboardPutItemFlavor( theClipboard, (PasteboardItemID)1,
                        CFSTR("public.utf8-plain-text"),
                        textData, 0 );
    if(err != noErr)
    {
        SWARNING << "CarbonWindowEventProducer::putClipboard: PasteboardPutItemFlavor Error: "<< err << std::endl;
        CFRelease (theClipboard);
        return;
    }

    CFRelease(theClipboard);
}

void CarbonWindowEventProducer::openWindow(const Pnt2f& ScreenPosition,
				   const Vec2f& Size,
				   const std::string& WindowName)
{
    SetWindowTitleWithCFString(_WindowRef, CFStringCreateWithCString(NULL, WindowName.c_str(),WindowName.size()));
   
    getWindow()->init();
    getWindow()->deactivate();
    
    // Show window
    RepositionWindow(_WindowRef, 0, kWindowCascadeOnMainScreen);
    setPosition(ScreenPosition);

    //For some reason the Viewport is not set up right unless I force the window to resize
    //there must be a better way of doing this
    setSize(Size+Vec2f(-1.0,0.0));
    setSize(Size);
    
    ShowWindow(_WindowRef);
	produceWindowOpened();
    _modifierKeyState = getKeyModifiers();
	
}

void CarbonWindowEventProducer::closeWindow(void)
{
    disposeWindow();
}

void CarbonWindowEventProducer::disposeWindow(void)
{
    DisposeWindow(_WindowRef);
}

void CarbonWindowEventProducer::setCursor(void)
{
	ThemeCursor c;
	switch(getCursorType())
	{
        case CURSOR_HAND:
            c = kThemePointingHandCursor;
            break;
        case CURSOR_I_BEAM:
            c = kThemeIBeamCursor;
            break;
        case CURSOR_WAIT:
            c = kThemeWatchCursor;
            break;
        case CURSOR_RESIZE_W_TO_E:
            c = kThemeResizeLeftRightCursor;
            break;
        case CURSOR_RESIZE_N_TO_S:
            c = kThemeResizeUpDownCursor;
            break;
        case CURSOR_RESIZE_NW_TO_SE:
            c = kThemeResizeUpDownCursor;
            break;
        case CURSOR_RESIZE_SW_TO_NE:
            c = kThemeResizeUpDownCursor;
            break;
        case CURSOR_RESIZE_ALL:
            c = kThemeClosedHandCursor;
            break;
        case CURSOR_NONE:
            c = kThemeArrowCursor;
            break;
        case CURSOR_POINTER:
        default:
            c = kThemeArrowCursor;
            break;
	}
	SetThemeCursor(c);
}

WindowPtr CarbonWindowEventProducer::createWindow(void)
{
    WindowPtr TheCarbonWindow = CarbonWindow::create();
    // Create window
    WindowRef window;
    WindowAttributes windowAttrs =
        kWindowStandardDocumentAttributes |
        kWindowLiveResizeAttribute |
        kWindowStandardHandlerAttribute;
    Rect contentRect;
    SetRect(&contentRect, 0, 0, 400, 400);
    
    CreateNewWindow(kDocumentWindowClass, windowAttrs, &contentRect, &window);
    
    // Install event handler
    _EventHandlerUPP = NewEventHandlerUPP(eventHandler);
    
	_WindowRef = window;
    _WindowId = getUndefinedWindowId();
    return TheCarbonWindow;
}

/*-------------------------------------------------------------------------*\
 -  private                                                                 -
\*-------------------------------------------------------------------------*/

/*----------------------- constructors & destructors ----------------------*/

CarbonWindowEventProducer::CarbonWindowEventProducer(void) :
    Inherited(){
}

CarbonWindowEventProducer::CarbonWindowEventProducer(const CarbonWindowEventProducer &source) :
    Inherited(source)
{
}

CarbonWindowEventProducer::~CarbonWindowEventProducer(void)
{
}

/*----------------------------- class specific ----------------------------*/

void CarbonWindowEventProducer::changed(BitVector whichField, UInt32 origin)
{
    Inherited::changed(whichField, origin);
}

void CarbonWindowEventProducer::dump(      UInt32    , 
                         const BitVector ) const
{
    SLOG << "Dump CarbonWindowEventProducer NI" << std::endl;
}

OSG_END_NAMESPACE

#endif

