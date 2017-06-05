无参数
##PARA0#： 
##PARA1#： 

短连接 

###

void foo1(void *)
{
	SOCKET	socRemote;
	char *ipaddress = "192.168.107.129";
	int picport = 8100;
	int connrc = 0;

	while(1)
	{
		i++;

		connrc = 0;

		连接远程机用TCP.C{ socRemote ### ipaddress ### picport ### connrc };

		if( connrc )
		{
			long len,len_out;
			char *p = (char*)(&len);

			接收_3进1出.C{ socRemote ### p ### 4 ### len_out };
			
			SCake ck;
			ck.redim( len_out );

		}
		
		 

		shutdown( soc2, 2 ); 
		closesocket(soc2); 
	}
}

