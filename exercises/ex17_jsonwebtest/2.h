
#ifndef K1__2_H
#define K1__2_H


#ifdef _MT
#define WINENV_
#else
#define LINUENV_
#endif

//#ifdef macintosh
//#ifdef Macintosh
#ifdef __APPLE__ 
//#ifdef __MACH__
#define OS_MACOSX_
#endif

#ifdef LINUENV_
//#include "gtk/gtk.h"
//#include <gdk/gdk.h>
//#include <glib.h>
//#include <glib/gprintf.h>
//#include <gdk/gdkkeysyms.h>
//#include <X11/Xlib.h>
#include "list"
#ifdef OS_MACOSX_
#include "1_u8.h"
#else
#include "1.h"
#endif
#else
#pragma warning(disable: 4996)
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <windows.h>
#include <shellapi.h>
//#include "atlstr.h" //CString in here
//#import "msado27.tlb" rename("EOF", "adoEOF")  
#include "list"
//#include "\a2\dup\mydup04\CDUP\w_alls.h"
//#include "\a2\dup\mydup04\CDUP\w_allw.h"
//#include "\a2\dup\mydup04\CDUP\net\a01ref_net.h"
#include "1.h"
#endif
#include <stack>

//#include "SelfIpPicker_t.h"

using namespace wl;


#define SADDR(s)  (&(s[0]))
 

#define MYAUTOLOCK2(Suffix,obj)   WCrsc aLoc_myLck_ ## Suffix (&(obj))
#define MYAUTOLOCK1(Suffix,obj) MYAUTOLOCK2(Suffix,obj)
#define MYAUTOLOCK(obj) MYAUTOLOCK1(__COUNTER__,obj)

#define MYLYOBJ2(Suffix,classname)    classname ly__ ## Suffix 
#define MYLYOBJ1(Suffix,classname)    MYLYOBJ2(Suffix,classname)
#define MYLYOBJ(classname) MYLYOBJ1(__COUNTER__,classname)


typedef	 void *	PVOID_t;



#ifdef WINENV_
#define WINSTRUPACK1STYLE_
#else
#define LINSTRUPACK1STYLE_
#endif

//typedef unsigned char  U8;       /* defined for unsigned 8-bits integer variable 	  无符号8位整型变量  */



#endif


