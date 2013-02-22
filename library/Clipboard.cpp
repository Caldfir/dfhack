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

//#elif UNIX

#else 

bool DFHack::Clipboard::Copy(const string & str)
{
    return false;
}

#endif