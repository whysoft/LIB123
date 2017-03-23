
 ²ÎÊý
##PARA0#£º x
##PARA1#£º y


###
 
double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1; 
double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1; 
fScreenWidth=MYWIDTH;fScreenHeight=MYHEIGHT;
double fx = (double)##PARA0# / 800.0 * fScreenWidth;
double fy = (double)##PARA1# / 600.0 * fScreenHeight;
		double ffx = ##PARA0#*(65535.0f/MYWIDTH);
		double ffy = ##PARA1#*(65535.0f/MYHEIGHT);
		mouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, static_cast<DWORD>(ffx), static_cast<DWORD>(ffy), 0, 0 );
mouse_event ( MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0 );
mouse_event ( MOUSEEVENTF_LEFTUP,    0, 0, 0, 0 );
mouse_event ( MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0 );
mouse_event ( MOUSEEVENTF_LEFTUP,    0, 0, 0, 0 );
