/*
Module : CryptoWrappersDefaultContext.H
Purpose: Defines the interface for a C++ wrapper class for a CryptoAPI HCRYPTDEFAULTCONTEXT
History: PJN / 01-08-2014 1. Initial public release

Copyright (c) 2014 - 2016 by PJ Naughter (Web: www.naughter.com, Email: pjna@naughter.com)

All rights reserved.

Copyright / Usage Details:

You are allowed to include the source code in any product (commercial, shareware, freeware or otherwise) 
when your product is released in binary form. You are allowed to modify the source code in any way you want 
except you cannot modify the copyright details at the top of each module. If you want to distribute source 
code with your application, then you are only allowed to distribute versions released by the author. This is 
to maintain a single distribution point for the source code. 

*/


////////////////////////// Macros / Defines ///////////////////////////////////

#pragma once

#ifndef __CRYPTOWRAPPERSDEFAULTCONTEXT_H__
#define __CRYPTOWRAPPERSDEFAULTCONTEXT_H__

#pragma comment(lib, "Crypt32.lib")  //Automatically link in the Crypto dll


////////////////////////// Includes ///////////////////////////////////////////

#ifndef __WINCRYPT_H__
#pragma message("To avoid this message, please put wincrypt.h in your pre compiled header (normally stdafx.h)")
#include <wincrypt.h>
#endif //#ifndef __WINCRYPT_H__


////////////////////////// Classes ////////////////////////////////////////////

namespace CryptoWrappers
{


//Encapsulates a CryptoAPI HCRYPTDEFAULTCONTEXT
class CDefaultContext
{
public:
//Constructors / Destructors
  CDefaultContext() : m_hCtx(nullptr)
  {
  }
  
  CDefaultContext(_In_ CDefaultContext& ctx) : m_hCtx(NULL)
  {
    Attach(ctx.Detach());
  }
  
  explicit CDefaultContext(_In_opt_ HCRYPTDEFAULTCONTEXT hCtx) : m_hCtx(hCtx)
  {
  }

  ~CDefaultContext()
  {
    if (m_hCtx != nullptr)
      Uninstall();
  }
  
//Methods
  CDefaultContext& operator=(_In_ CDefaultContext& ctx)
  {
    if (this != &ctx)
    {
      if (m_hCtx != nullptr)
        Uninstall();
      Attach(ctx.Detach());
    }
    
    return *this;
  }

  _Success_(return != FALSE)
  BOOL Uninstall()
  {
    //Validate our parameters
    ATLASSERT(m_hCtx != nullptr);

    BOOL bResult = CryptUninstallDefaultContext(m_hCtx, 0, nullptr);
    m_hCtx = nullptr;
    return bResult;
  }

  HCRYPTDEFAULTCONTEXT Handle() const
  {
    return m_hCtx;
  }

  void Attach(_In_opt_ HCRYPTDEFAULTCONTEXT hCtx)
  {
    //Validate our parameters
    ATLASSERT(m_hCtx == nullptr);
    
    m_hCtx = hCtx;
  }

  HCRYPTDEFAULTCONTEXT Detach()
  {
    HCRYPTDEFAULTCONTEXT hCtx = m_hCtx;
    m_hCtx = nullptr;
    return hCtx;
  }

//Member variables
  HCRYPTDEFAULTCONTEXT m_hCtx;
};


}; //namespace CryptoWrappers

#endif //#ifndef __CRYPTOWRAPPERSDEFAULTCONTEXT_H__
