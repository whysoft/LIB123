
 参数
##PARA0#： the char
##PARA1#： 没有


###
if( ##PARA0# )
{
	BYTE c;
	c = (BYTE)(##PARA0#);
	keybd_event(c, 0, 0,			 	0);
	keybd_event(c, 0, KEYEVENTF_KEYUP,  0);
}
