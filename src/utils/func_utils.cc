/****************************************************************************
 *   Copyright (C) 2020 by Music Box Games                                  *
 *                                                                          *
 *   This file is part of WaifuEngine                                       *
 *                                                                          *
 *   WaifuEngine is free software: you can redistribute it and/or modify it *
 *   under the terms of the MIT License.                                    *
 *                                                                          *
 *   WaifuEngine is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   MIT License for more details.                                          *
 *                                                                          *
 *   You should have received a copy of the MIT License along with          *
 *   WaifuEngine.  If not, see https://opensource.org/licenses/MIT          *
 ****************************************************************************/

/******************************************************************************/
/**
* @file   func_utils.hpp
* @author Ryan Hanson
* @date   27 Oct 2020
* @par    email: iovita\@musicboxgames.net
* @brief  Function utilities
*
*/
/******************************************************************************/

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#include <Windows.h>
#include <DbgHelp.h>

#include "func_utils.hpp"

namespace waifuengine
{
  namespace utils
  {
    std::string function_name_from_addr(long long addr)
    {
      // https://docs.microsoft.com/en-us/windows/win32/debug/retrieving-symbol-information-by-address
#if 0
      DWORD64 dwDisplacement = 0;
      DWORD64 dwAddress = addr;


      char buffer[sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR)];
      PSYMBOL_INFO pSymbol = (PSYMBOL_INFO)buffer;

      pSymbol->SizeOfStruct = sizeof(SYMBOL_INFO);
      pSymbol->MaxNameLen = MAX_SYM_NAME;

      if (SymFromAddr(hProcess, dwAddress, &dwDisplacement, pSymbol))
      {
        // SymFromAddr returned success
        return pSymbol->Name;
      }
      else
      {
        // SymFromAddr failed
        DWORD error = GetLastError();
      }
#endif // Windows specific code
      return "unimplemented";
    }
  }
}
