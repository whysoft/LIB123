
无参数
##PARA0#： 
##PARA1#： 

###

void foo2(void *)
{
	struct MoustBeh_t Mb;
	int L;

	while(1)
	{
		if( socZUO1 == INVALID_SOCKET )
		{
			return ;
		}
		
		while(1)
		{
			接受连入_1进1出.C{ socZUO1 ### socZUO2 };

			if( socZUO2 == INVALID_SOCKET )
			{
				break;
			}

			//接收 
			接收_3进1出.C{ socZUO2 ### (char*)&Mb ### sizeof(Mb) ### L };
			//、、

			break;
		}

		//处理各事
		if( Mb.itype == 1 )
		{
			A20B10左一次.C{ Mb.x ### Mb.y };
		}

		if( Mb.itype == 2 )
		{
			A20B20左二次.C{ Mb.x ### Mb.y };
		}
		
		if( Mb.itype == 3 )
		{
			A20B30右一次.C{ Mb.x ### Mb.y };
		}
	
		if( Mb.itype == 4 )
		{
			A20B40键盘一个.C{ Mb.x };
		}

		shutdown( socZUO2, 2 ); 
		closesocket(socZUO2); 
	}
}

