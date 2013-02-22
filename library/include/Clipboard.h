/*
 some kind of legalese stuff goes here
*/

#pragma once
#include "Pragma.h"
#include "Export.h"
#include <string>

namespace DFHack
{
    namespace Clipboard
    {
        DFHACK_EXPORT bool CopyText(const std::string & str);
    }
}