/*
 some kind of legalese stuff goes here
*/

#include "Clipboard.h"

#ifdef WIN32

#include "windows.h"

bool DFHack::Clipboard::CopyText(const std::string & str)
{
    HGLOBAL hglbCopy;
    LPTSTR  lptstrCopy; 

    if (!OpenClipboard(NULL)) 
        return false; 
    EmptyClipboard(); 

    hglbCopy = GlobalAlloc(GMEM_MOVEABLE, 
        (str.length() + 1) * sizeof(TCHAR)); 
    if (hglbCopy == NULL) 
    { 
        CloseClipboard(); 
        return false; 
    } 

    lptstrCopy = (LPTSTR) GlobalLock(hglbCopy); 
    memcpy(lptstrCopy, &(str[0]), 
        str.length() * sizeof(TCHAR)); 
    lptstrCopy[str.length()] = (TCHAR) 0;    
    GlobalUnlock(hglbCopy); 

    SetClipboardData(CF_TEXT, hglbCopy); 
    CloseClipboard();

    return true; 
}

#elif _LINUX

//ok, well, I have no idea if any of this works

#include <X11/Xlib.h>
#include <X11/Xatom.h>

int size = 0;
unsigned char* board = NULL;

bool DFHack::Clipboard::Copy(const string & str)
{
    //X doesn't have a global clipboard memory location, 
    // so we need to hold on to anything we select ourselves, 
    // and since we aren't listening for X events, this is until
    // we select something new
    free(board);
        size = 0;

    Display* disp = XOpenDisplay(NULL);
    if(!disp) {
        return false;
    }         
    
    Window w;   // focused window
    int wstate;      // focus state
    XGetInputFocus(disp, &wstate, &w);

    //TODO: we really ought to check to see if the focus window
    // is something we control, to guarantee not-crazy behavior

    if(w == None) {
        return false;
    }


    size = (str.length() + 1)*sizeof(char);
    char* strboard = (char*) malloc(size);
    
    memcpy(strboard, &(str[0]), 
        str.length() * sizeof(char)); 
    strboard[str.length()] = (char) 0;  

    board = (unsigned char*) strboard;


    XSetSelectionOwner (disp, XA_PRIMARY, w, CurrentTime);

    XChangeProperty(disp, w,
        XA_PRIMARY, XA_STRING,
        8, //char format
        PropModeReplace,
        board,
        size);

    return true;
}

#elif _DARWIN

bool DFHack::Clipboard::Copy(const string & str)
{
    return false;
}

#else 

bool DFHack::Clipboard::Copy(const string & str)
{
    return false;
}

#endif