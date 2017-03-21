
#ifndef A__2_H
#define A__2_H


#ifdef _MT
#define WINENV_
#else
#define LINUENV_
#endif
#ifdef WINENV_
#include <windows.h> 
#include <shellapi.h>
#pragma comment( lib, "ws2_32.lib" )
#include <winsock.h>
#include "atlstr.h" //CString in here
#import "msado27.tlb" rename("EOF", "adoEOF")  
#endif
#include "list"
#include "1.h"
using namespace wl;


#endif


