
2个参数
##PARA0#：ushort类型 ,port
##PARA1#：返回 SOCKET,	如果不，返回 INVALID_SOCKET 。

###
if(##PARA0#)
{
	struct	sockaddr_in	 saddr;
	u_long a_in_addrip = INADDR_ANY;
	int listener_num = 4;

	##PARA1# = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

	if( ##PARA1# != INVALID_SOCKET )
	{
		//we should zero mem here.
		memset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET; 
		saddr.sin_port = htons( (u_short)##PARA0# );
		saddr.sin_addr.s_addr = a_in_addrip;	
		
		if( SOCKET_ERROR != bind( ##PARA1#, (struct sockaddr *)&saddr, sizeof(saddr) ) )
		{
			if( 0 != ::listen( ##PARA1#, listener_num ) )
			{
				##PARA1# = INVALID_SOCKET;
			}
		}
		else
		{
			##PARA1# = INVALID_SOCKET;
		}
	}
}
else
{ 
	##PARA1# = INVALID_SOCKET;
}