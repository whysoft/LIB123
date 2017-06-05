
void foo1(void *Para )
{
	int conn_rc = 0;
	WTcpCellc cc;
	if(Para)
	{
		struct MoustBeh_t *pMb = (MoustBeh_t*)Para;
		conn_rc = cc.Conn( ipaddress, beh_port );
		int *p = (int*)Para;
		for( int j = 0; j < 4; j++ )
			cc.send_bin( (unsigned long)(*(p + j)) );
		cc.DisConn();
		return;
	}
	SOCKET	socRemote=-1;

	while(1)
	{
		i++; //Õ¼ÓÃ´ËºÅ	

		Sleep(20);
		 
		conn_rc = cc.Conn( ipaddress, pic_port );

		if( conn_rc )
		{
			long len,len_out;

			SCake ck;
			cc.recv_len( ck, 4 );
			len_out = ck.len();
			if( len_out == 4 ) len = *(int*)ck.buf();
			else len = 0;
			cc.recv_all_f( ck );
			//save the file
			WFile fl;
			fl.bind( filename[i&1] );
			fl.write(ck);
		}	
		cc.DisConn();
		//shutdown( soc2, 2 ); 
		//closesocket(soc2); 
	}
}

