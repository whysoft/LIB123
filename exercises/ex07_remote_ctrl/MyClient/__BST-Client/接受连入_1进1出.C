
2个参数
##PARA0#：SOCKET 类型 ,侦听者
##PARA1#：返回 SOCKET,	如果不，返回 INVALID_SOCKET 。

###
if(##PARA0# != INVALID_SOCKET)
{
	struct	sockaddr_in	 from;
	int nSize;
	
	nSize= sizeof(from);

	##PARA1# = ::accept( ##PARA0#, (struct sockaddr *)&from, &nSize ); //  now have a new value
	
}
else
{ 
	##PARA1# = INVALID_SOCKET;
}