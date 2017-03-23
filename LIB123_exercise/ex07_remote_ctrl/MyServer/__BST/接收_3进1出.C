
参数:
##PARA0#：	SOCKET
##PARA1#：	pointer
##PARA2#	len		指定接收固定长度	
##PARA3#	len_out		成功收到的长度	

###
if( ##PARA0# != INVALID_SOCKET )  
{
	int i;

	##PARA3# = 0;

	for( int j = 0 ; ; j++ )
	{
		i = (int)::recv( ##PARA0#, (char*)(##PARA1#) + ##PARA3# , ##PARA2# - ##PARA3#, 0 );
	
		if(i==SOCKET_ERROR||i==0) break;

		##PARA3# +=i;
	
		if( ##PARA3# >= ##PARA2#) break;
	}

}
