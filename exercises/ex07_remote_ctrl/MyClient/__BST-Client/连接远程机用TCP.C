
²ÎÊý:
##PARA0#£º	SOCKET, output
##PARA1#£º	ipstring, const char*, input
##PARA2#	port, input	
##PARA3#	rc, output

###
if( ##PARA1# )  
{
	struct sockaddr_in saddr;

	##PARA0# = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	if( ##PARA0# == INVALID_SOCKET )
	{
		##PARA3# = 0;
	}
	else
	{
		memset( (void*)&saddr, 0, sizeof(saddr) );
			
		saddr.sin_family = AF_INET; 
		saddr.sin_addr.s_addr = inet_addr( ##PARA1# );
		saddr.sin_port = htons( (u_short)##PARA2# );

		if(SOCKET_ERROR == ::connect( ##PARA0#, (struct sockaddr *)&saddr, sizeof(saddr) )  )
		{
			##PARA3# = 0;
		}
		else
			##PARA3# = 1;
	}
}

