
无参数
##PARA0#： 
##PARA1#： 

###

void foo2(void *)
{
	while(1)
	{
		if( soc1 == INVALID_SOCKET )
		{
			return ;
		}
		
		while(1)
		{
			接受连入_1进1出.C{ soc1 ### soc2 };

			if( soc2 == INVALID_SOCKET )
			{
				break;
			}

			//传送 
			发送_3进.C{ soc2 ### p ### len };
			//、、

			break;
		}

		shutdown( soc2, 2 ); 
		closesocket(soc2); 
	}
}

