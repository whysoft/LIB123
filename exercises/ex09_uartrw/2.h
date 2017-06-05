
#ifndef K1__2_H
#define K1__2_H


#ifdef _MT
#define WINENV_
#else
#define LINUENV_
#endif


#ifdef LINUENV_
//#include "gtk/gtk.h"
//#include <gdk/gdk.h>
//#include <glib.h>
//#include <glib/gprintf.h>
//#include <gdk/gdkkeysyms.h>
//#include <X11/Xlib.h>
#include "list"
#include "1.h"
#else
#pragma warning(disable: 4996)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <windows.h> 
#include <shellapi.h>
#include "atlstr.h" //CString in here
//#import "msado27.tlb" rename("EOF", "adoEOF")  
#include "list"
#include "\a1\\a\k\mydup04\CDUP\w_alls.h"
#include "\a1\a\k\mydup04\CDUP\w_allw.h"
#include "\a1\a\k\mydup04\CDUP\net\a01ref_net.h"
#include "1.h"
#endif

//#include "SelfIpPicker_t.h"

using namespace wl;


#define SADDR(s)  (&(s[0]))

#define LOGPOSI  ( SDte::GetNow().Get_now_mtime() + "|" + std::string(__FUNCTION__) + "|" + SStrf::sltoa(__LINE__) + "\t" ).c_str()
#define LOGSTREAM2(Suffix,logobj,streamexp)  do{std::stringstream stream1a ## Suffix ; stream1a ## Suffix<<streamexp; (logobj).LogPrintStr( stream1a ## Suffix.str() ); }while(0)
#define LOGSTREAM1(Suffix,logobj,streamexp) LOGSTREAM2(Suffix,logobj,streamexp)
#define LOGSTREAM(logobj,streamexp) LOGSTREAM1(__LINE__,logobj,streamexp)


#define MYAUTOLOCK2(Suffix,obj)   WCrsc aLoc_myLck_ ## Suffix (&(obj))
#define MYAUTOLOCK1(Suffix,obj) MYAUTOLOCK2(Suffix,obj)
#define MYAUTOLOCK(obj) MYAUTOLOCK1(__COUNTER__,obj)




extern bool IsOsWin(); 


#endif

