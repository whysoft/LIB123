
²ÎÊý:
##PARA0#£º	SOCKET
##PARA1#£º	pointer
##PARA2#	len

###
if(##PARA0#!=INVALID_SOCKET)  
{
	int i;
	 long  k;

	k = 0;
	for(;;)
	{
		i = (int)::send( ##PARA0#, (char*)(##PARA1#) +k, (int)(##PARA2#-k), 0);

		k +=i;
		if( i == 0 )break;
		if(k>=len) break;
	}

}