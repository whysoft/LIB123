
#ifndef V1_3AA_MATES_T_20170817_184551
#define V1_3AA_MATES_T_20170817_184551

 
///////////////////////////////////////////////////////
//Contents:	The row class type definition of a_mates_t
//Name:	a_mates_t_rowtype
class a_mates_t_rowtype {
 
public:

	int		m_RES01;			// .	[保留] 
	std::string		m_name;			// .	姓名 
	std::string		m_num;			// .	学号 
	std::string		m_class;			// .	班级 
	double		m_money;			// .	已交费额 
	NaL2S		m_RES02;			// .	[保留] 
	std::string		m_take;			// .	是否参加 
	//#. RES
	int		m_RES03;			// .	[保留] 
	ui8arr_t<2>		m_RES05;			// .	[保留] 
	//#. RES
	NaL2L		m_RES07;			// .	[保留] 
	std::string		m_stamp_create;			// .	创建日期 
	std::string		m_stamp_modi;			// .	修改日期 
	std::string		m_ip;			// .	访问者IP 
 
public:

	a_mates_t_rowtype()
	{
		m_RES01 = 0;
		//m_name = //use default
		//m_num = //use default
		//m_class = //use default
		m_money = 0;
		//m_RES02 = //use default
		//m_take = //use default
		m_RES03 = 0;
		//m_RES05 = //use default
		//m_RES07 = //use default
		m_stamp_create = SDte::GetNow().ReadString();
		m_stamp_modi = SDte::GetNow().ReadString();
		//m_ip = //use default
	}

	virtual ~a_mates_t_rowtype(){;}
	

	//operator == 
	bool operator == (const a_mates_t_rowtype & rhs) const
	{
		return this == &rhs;
	}

	//operator > 
	bool operator > (const a_mates_t_rowtype & rhs) const
	{
		return this > &rhs;
	}

	//operator < 
	bool operator < (const a_mates_t_rowtype & rhs) const
	{
		return this < &rhs;
	}

 
protected:

	template< class T > T decode2( void *p ) 
	 { T x; memcpy( &x, p, sizeof(T) ); return x; }

	//serialize unserialize

	static void en( const char *src, long len, char *destbuf )
	{
		static char strHexPtr[] = "0123456789ABCDEF";
		char *pdest=destbuf;
		pdest[0]=pdest[1]=0;
		pdest[2]=0;pdest[3]=0;
		for( long i = 0; i<len; i++ )
		{
			//int iVal = (unsigned char)src[i];
			pdest[0] = strHexPtr[ (unsigned char)src[i] / 16 % 16 ];
			pdest[1] = strHexPtr[ (unsigned char)src[i] % 16 ];
			pdest += 2;
		}
		*pdest = 0;
	}

	static char *de( char *src )
	{
		long i,k;
		int nReturn=0;
		for( i=k=0; ; )
		{
			if(src[i]=='/'||src[i]==0) break;
			if ( src[i]>='0'&& src[i] <= '9' ) nReturn =        16 + src[i] - '0';
			else if ( src[i] >= 'A'&& src[i] <= 'F' ) nReturn = 16 + src[i] - 'A' + 10;
			i++;nReturn *=16;
			if(src[i]=='/'||src[i]==0) break;
			if ( src[i]>='0'&& src[i] <= '9' ) nReturn +=        src[i] - '0';
			else if ( src[i] >= 'A'&& src[i] <= 'F' ) nReturn += src[i] - 'A' + 10;
			i++; src[k++] = (char)(unsigned char)nReturn;
		}
		if(src[i]==0) return src+i;
		return src+i+1;
	}

 
public:

	//serialize unserialize

	std::string & Serialize( std::string & strOut )
	{
		strOut = "";
		const char *buf1;
		long len1;
		char *buf2;
		std::vector< char > v;
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES01));
		len1 = sizeof(m_RES01);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_name.c_str();
		len1 = (long)(m_name.length()*sizeof(char)+sizeof(char));
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_num.c_str();
		len1 = (long)(m_num.length()*sizeof(char)+sizeof(char));
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_class.c_str();
		len1 = (long)(m_class.length()*sizeof(char)+sizeof(char));
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_money));
		len1 = sizeof(m_money);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_RES02.serialize_hold_addr();
		len1 = m_RES02.serialize_hold_len();
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_take.c_str();
		len1 = (long)(m_take.length()*sizeof(char)+sizeof(char));
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES03));
		len1 = sizeof(m_RES03);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES05));
		len1 = sizeof(m_RES05);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_RES07.serialize_hold_addr();
		len1 = m_RES07.serialize_hold_len();
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_stamp_create.c_str();
		len1 = (long)(m_stamp_create.length()*sizeof(char)+sizeof(char));
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_stamp_modi.c_str();
		len1 = (long)(m_stamp_modi.length()*sizeof(char)+sizeof(char));
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_ip.c_str();
		len1 = (long)(m_ip.length()*sizeof(char)+sizeof(char));
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		return strOut;
	}

	std::string Serialize()
	{
		std::string strOut;
		return this->Serialize(strOut);
	}

	a_mates_t_rowtype & Unserialize( const char * strIn )
	{
		const char *buf1;
		char *buf2;
		buf1 = strIn;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_RES01 = *(int*)buf2; }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_name = (char*)buf2; }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_num = (char*)buf2; }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_class = (char*)buf2; }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_money = decode2<double>(buf2); }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_RES02.unserialize((char*)buf2); }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_take = (char*)buf2; }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_RES03 = *(int*)buf2; }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_RES05 = *(ui8arr_t<2>*)buf2; }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_RES07.unserialize((char*)buf2); }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_stamp_create = (char*)buf2; }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_stamp_modi = (char*)buf2; }else return *this; 
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );  
		 /*if( *buf2!='}')*/ m_ip = (char*)buf2; }else return *this; 
		return *this;
	}

	 
#ifdef X014FASTSERI_

	wl::SCake & Serialize( wl::SCake & ckOut )
	{
		ckOut.redim(0);
		const char *buf1;
		wl::tuint32 len1;
		wl::SCakel ckl;
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES01));
		len1 = sizeof(m_RES01);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_name.c_str();
		len1 = (long)(m_name.length()*sizeof(char)+sizeof(char));
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_num.c_str();
		len1 = (long)(m_num.length()*sizeof(char)+sizeof(char));
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_class.c_str();
		len1 = (long)(m_class.length()*sizeof(char)+sizeof(char));
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_money));
		len1 = sizeof(m_money);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_RES02.serialize_hold_addr();
		len1 = m_RES02.serialize_hold_len();
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_take.c_str();
		len1 = (long)(m_take.length()*sizeof(char)+sizeof(char));
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES03));
		len1 = sizeof(m_RES03);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES05));
		len1 = sizeof(m_RES05);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_RES07.serialize_hold_addr();
		len1 = m_RES07.serialize_hold_len();
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_stamp_create.c_str();
		len1 = (long)(m_stamp_create.length()*sizeof(char)+sizeof(char));
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_stamp_modi.c_str();
		len1 = (long)(m_stamp_modi.length()*sizeof(char)+sizeof(char));
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_ip.c_str();
		len1 = (long)(m_ip.length()*sizeof(char)+sizeof(char));
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		ckl.collectb();
		return ckOut=*ckl.get0();
	}

	a_mates_t_rowtype & Unserialize( wl::tchar * p_begin, wl::tchar ** pp_end )
	{
		char *buf1 = p_begin;
		char *buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES01 = *(int*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_name = (char*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_num = (char*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_class = (char*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_money = decode2<double>(buf2);
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES02 = buf2COL.unserialize((char*)buf2);
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_take = (char*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES03 = *(int*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES05 = *(ui8arr_t<2>*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES07 = buf2COL.unserialize((char*)buf2);
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_stamp_create = (char*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_stamp_modi = (char*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_ip = (char*)buf2;
		*pp_end = buf1;
		return *this;
	}

	 
#endif

 
public:

/////////////////////////////////////////////////////////////
//Function:	GetCol_RES01
//Effect:	get ref of col. col is RES01
//Return:	int & 
	int & GetCol_RES01(void)
	{
		return m_RES01;
	}

/////////////////////////////////////////////////////////
//Function:	GetCol_name
//Effect:	get ref of col. col is name
//Return:	std::string & 
	std::string & GetCol_name(void)
	{
		return m_name;
	}

///////////////////////////////////////////////////////////////
//Function:	GetCol_num
//Effect:	get ref of col. col is num
//Return:	std::string & 
	std::string & GetCol_num(void)
	{
		return m_num;
	}

/////////////////////////////////////////////////////////////
//Function:	GetCol_class
//Effect:	get ref of col. col is class
//Return:	std::string & 
	std::string & GetCol_class(void)
	{
		return m_class;
	}

////////////////////////////////////////////////////////////
//Function:	GetCol_money
//Effect:	get ref of col. col is money
//Return:	double & 
	double & GetCol_money(void)
	{
		return m_money;
	}

//////////////////////////////////////////////////////////
//Function:	GetCol_RES02
//Effect:	get ref of col. col is RES02
//Return:	NaL2S & 
	NaL2S & GetCol_RES02(void)
	{
		return m_RES02;
	}

////////////////////////////////////////////////////////////////
//Function:	GetCol_take
//Effect:	get ref of col. col is take
//Return:	std::string & 
	std::string & GetCol_take(void)
	{
		return m_take;
	}

////////////////////////////////////////////////////////////////
//Function:	GetCol_RES03
//Effect:	get ref of col. col is RES03
//Return:	int & 
	int & GetCol_RES03(void)
	{
		return m_RES03;
	}

///////////////////////////////////////////////////////////////
//Function:	GetCol_RES05
//Effect:	get ref of col. col is RES05
//Return:	ui8arr_t<2> & 
	ui8arr_t<2> & GetCol_RES05(void)
	{
		return m_RES05;
	}

////////////////////////////////////////////////////////
//Function:	GetCol_RES07
//Effect:	get ref of col. col is RES07
//Return:	NaL2L & 
	NaL2L & GetCol_RES07(void)
	{
		return m_RES07;
	}

////////////////////////////////////////////////////////////////
//Function:	GetCol_stamp_create
//Effect:	get ref of col. col is stamp_create
//Return:	std::string & 
	std::string & GetCol_stamp_create(void)
	{
		return m_stamp_create;
	}

//////////////////////////////////////////////////////////////
//Function:	GetCol_stamp_modi
//Effect:	get ref of col. col is stamp_modi
//Return:	std::string & 
	std::string & GetCol_stamp_modi(void)
	{
		return m_stamp_modi;
	}

////////////////////////////////////////////////////////////
//Function:	GetCol_ip
//Effect:	get ref of col. col is ip
//Return:	std::string & 
	std::string & GetCol_ip(void)
	{
		return m_ip;
	}

 
public:

//////////////////////////////////////////////////////////
//Function:	GetColAmount
//Effect:	get column amount
//Return:	return the column amount, int.
	int GetColAmount() 
	{
		return 13;
	}

///////////////////////////////////////////////////////
//Function:	GetColName
//Effect:	get column name, input col number base on 0.
//Return:	return col's name in string format.
	std::string GetColName( int iColNum )
	{
		if( iColNum == 0 )
		{
			return "RES01";
		}
		if( iColNum == 1 )
		{
			return "name";
		}
		if( iColNum == 2 )
		{
			return "num";
		}
		if( iColNum == 3 )
		{
			return "class";
		}
		if( iColNum == 4 )
		{
			return "money";
		}
		if( iColNum == 5 )
		{
			return "RES02";
		}
		if( iColNum == 6 )
		{
			return "take";
		}
		if( iColNum == 7 )
		{
			return "RES03";
		}
		if( iColNum == 8 )
		{
			return "RES05";
		}
		if( iColNum == 9 )
		{
			return "RES07";
		}
		if( iColNum == 10 )
		{
			return "stamp_create";
		}
		if( iColNum == 11 )
		{
			return "stamp_modi";
		}
		if( iColNum == 12 )
		{
			return "ip";
		}
		return "";
	}

////////////////////////////////////////////////////////
//Function:	GetColNumber
//Effect:	input col name, get col number
//Return:	return the column number, int.
	int GetColNumber( std::string strColName ) 
	{
		if( strColName == "RES01" )
		{
			return 0;
		}
		if( strColName == "name" )
		{
			return 1;
		}
		if( strColName == "num" )
		{
			return 2;
		}
		if( strColName == "class" )
		{
			return 3;
		}
		if( strColName == "money" )
		{
			return 4;
		}
		if( strColName == "RES02" )
		{
			return 5;
		}
		if( strColName == "take" )
		{
			return 6;
		}
		if( strColName == "RES03" )
		{
			return 7;
		}
		if( strColName == "RES05" )
		{
			return 8;
		}
		if( strColName == "RES07" )
		{
			return 9;
		}
		if( strColName == "stamp_create" )
		{
			return 10;
		}
		if( strColName == "stamp_modi" )
		{
			return 11;
		}
		if( strColName == "ip" )
		{
			return 12;
		}
		return -1;
	}

///////////////////////////////////////////////////////////
//Function:	GetColStr
//Effect:	get column value, input col number base on 0.
//Return:	return col value in string format.
	template<class STRINGT>
	STRINGT GetColStr( int iColNum )
	{
		if( iColNum == 0 )
		{
			return wl::SStrf::sltoa(m_RES01);
		}
		if( iColNum == 1 )
		{
			return m_name;
		}
		if( iColNum == 2 )
		{
			return m_num;
		}
		if( iColNum == 3 )
		{
			return m_class;
		}
		if( iColNum == 4 )
		{
			return wl::SStrf::sftoa(m_money);
		}
		if( iColNum == 5 )
		{
			return m_RES02.serialize();
		}
		if( iColNum == 6 )
		{
			return m_take;
		}
		if( iColNum == 7 )
		{
			return wl::SStrf::sltoa(m_RES03);
		}
		if( iColNum == 8 )
		{
			return wl::SStrf::b2s(m_RES05);
		}
		if( iColNum == 9 )
		{
			return m_RES07.serialize();
		}
		if( iColNum == 10 )
		{
			return m_stamp_create;
		}
		if( iColNum == 11 )
		{
			return m_stamp_modi;
		}
		if( iColNum == 12 )
		{
			return m_ip;
		}
		return GetColStr<STRINGT>(0);
	}

	template<class STRINGT>
	STRINGT & GetColStr( int iColNum , STRINGT & sBuf ) { return sBuf = GetColStr<STRINGT>(iColNum); }

////////////////////////////////////////////////////////
//Function:	GetColStr
//Effect:	get column value, input col name.
//Return:	return col value in string format.
	template<class STRINGT>
	STRINGT GetColStr( std::string strColName )
	{
		if( strColName == "RES01" )
		{
			return GetColStr<STRINGT>(0);
		}
		if( strColName == "name" )
		{
			return GetColStr<STRINGT>(1);
		}
		if( strColName == "num" )
		{
			return GetColStr<STRINGT>(2);
		}
		if( strColName == "class" )
		{
			return GetColStr<STRINGT>(3);
		}
		if( strColName == "money" )
		{
			return GetColStr<STRINGT>(4);
		}
		if( strColName == "RES02" )
		{
			return GetColStr<STRINGT>(5);
		}
		if( strColName == "take" )
		{
			return GetColStr<STRINGT>(6);
		}
		if( strColName == "RES03" )
		{
			return GetColStr<STRINGT>(7);
		}
		if( strColName == "RES05" )
		{
			return GetColStr<STRINGT>(8);
		}
		if( strColName == "RES07" )
		{
			return GetColStr<STRINGT>(9);
		}
		if( strColName == "stamp_create" )
		{
			return GetColStr<STRINGT>(10);
		}
		if( strColName == "stamp_modi" )
		{
			return GetColStr<STRINGT>(11);
		}
		if( strColName == "ip" )
		{
			return GetColStr<STRINGT>(12);
		}
		return GetColStr<STRINGT>(0);
	}

	template<class STRINGT>
	STRINGT& GetColStr( std::string strColName, STRINGT & sBuf ) { return sBuf = GetColStr<STRINGT>(strColName); }

////////////////////////////////////////////////////////
//Function:	SetColVal
//Effect:	set column value, input col number base on 0, and input value in string format.
//Return:	no return.
	template<class STRINGT>
	void SetColVal( int iColNum, STRINGT strValPARA )
	{
		if( iColNum == 0 )
		{
			m_RES01=wl::SStrf::satol(strValPARA);
		}
		if( iColNum == 1 )
		{
			m_name=strValPARA;
		}
		if( iColNum == 2 )
		{
			m_num=strValPARA;
		}
		if( iColNum == 3 )
		{
			m_class=strValPARA;
		}
		if( iColNum == 4 )
		{
			m_money=wl::SStrf::satof(strValPARA);
		}
		if( iColNum == 5 )
		{
			m_RES02.unserialize(strValPARA);
		}
		if( iColNum == 6 )
		{
			m_take=strValPARA;
		}
		if( iColNum == 7 )
		{
			m_RES03=wl::SStrf::satol(strValPARA);
		}
		if( iColNum == 8 )
		{
			wl::SStrf::s2b(strValPARA,m_RES05);
		}
		if( iColNum == 9 )
		{
			m_RES07.unserialize(strValPARA);
		}
		if( iColNum == 10 )
		{
			m_stamp_create=strValPARA;
		}
		if( iColNum == 11 )
		{
			m_stamp_modi=strValPARA;
		}
		if( iColNum == 12 )
		{
			m_ip=strValPARA;
		}
	}

/////////////////////////////////////////////////////////////////
//Function:	SetColVal
//Effect:	set column value, input col number base on 0, and input value in string format.
//Return:	no return.
	template<class STRINGT>
	void SetColVal( std::string strColName, STRINGT strValPARA )
	{
		if( strColName == "RES01" )
		{
			SetColVal<STRINGT>(0,strValPARA);
		}
		if( strColName == "name" )
		{
			SetColVal<STRINGT>(1,strValPARA);
		}
		if( strColName == "num" )
		{
			SetColVal<STRINGT>(2,strValPARA);
		}
		if( strColName == "class" )
		{
			SetColVal<STRINGT>(3,strValPARA);
		}
		if( strColName == "money" )
		{
			SetColVal<STRINGT>(4,strValPARA);
		}
		if( strColName == "RES02" )
		{
			SetColVal<STRINGT>(5,strValPARA);
		}
		if( strColName == "take" )
		{
			SetColVal<STRINGT>(6,strValPARA);
		}
		if( strColName == "RES03" )
		{
			SetColVal<STRINGT>(7,strValPARA);
		}
		if( strColName == "RES05" )
		{
			SetColVal<STRINGT>(8,strValPARA);
		}
		if( strColName == "RES07" )
		{
			SetColVal<STRINGT>(9,strValPARA);
		}
		if( strColName == "stamp_create" )
		{
			SetColVal<STRINGT>(10,strValPARA);
		}
		if( strColName == "stamp_modi" )
		{
			SetColVal<STRINGT>(11,strValPARA);
		}
		if( strColName == "ip" )
		{
			SetColVal<STRINGT>(12,strValPARA);
		}
	}

}
; 
//end of class a_mates_t_rowtype
 
 
///////////////////////////////////////////////////////
//Contents:	The tbl class type definition
//Name:	a_mates_t
class a_mates_t {
 
private:

	a_mates_t_rowtype m_EmptyRow;
	std::vector<a_mates_t_rowtype>  m_DATAcorpora;
 
public:

	typedef a_mates_t_rowtype 	ROWTYPE;
	typedef std::vector<long> 	RPSTYPE; //RPS(return pointer set) type definition
	typedef std::vector<a_mates_t_rowtype>::iterator 	TBLITTYPE;
 
public:

	a_mates_t()
	{
	}

	virtual ~a_mates_t(){;}
	

	//operator == 
	bool operator == (const a_mates_t & rhs) const
	{
		return this == &rhs;
	}

	//operator > 
	bool operator > (const a_mates_t & rhs) const
	{
		return this > &rhs;
	}

	//operator < 
	bool operator < (const a_mates_t & rhs) const
	{
		return this < &rhs;
	}

 
public:

	//serialize unserialize

	std::string &  Serialize( std::string & strOut )	
	{
		strOut = "";
		for(long i=0;i<(long)GetRowCount();i++)
		{
			std::string strTmp;
			GetRow(i).Serialize(strTmp);
			strOut += strTmp + "}";
		}
		return strOut;
	}

	std::string Serialize()
	{
		std::string strOut;
		return this->Serialize(strOut);
	}

	a_mates_t &  Unserialize( const char * strIn , int biAppend = 0 ) //if append==0, it would over-write the current tbl. 
	{
		char *p1,*p2;
		p1 = (char*)strIn;
		if(biAppend==0) Clear();
		do
		{
			p2 = p1;
			if(!*p2) return *this;
			ROWTYPE row;
			while( !( *p2=='}' ) && *p2 ) p2++;
			row.Unserialize( p1 );
			Add(row);
			p1=p2+1;
		}while(*p2);
		return *this;
	}

	 
#ifdef X014FASTSERI_

	wl::SCake & Serialize( wl::SCake & ckOut )
	{
		wl::SCakel ckl;
		ckOut.redim(0);
		for(long i=0;i<(long)GetRowCount();i++)
		{
			wl::SCake ck;
			GetRow(i).Serialize(ck);
			ckl.add(ck);
		}
		ckl.collectb(&ckOut);
		return ckOut;
	}

	a_mates_t & Unserialize( wl::SCake & ckIn , int biAppend = 0 )
	{
		char *p1,*p2;
		p1 = p2 = (char*)ckIn.buf();
		if(biAppend==0) Clear();
		do 
		{
			p1 = p2;
			ROWTYPE row;
			row.Unserialize( p1, &p2 );
			Add(row);
			if( p2 >= ckIn.buf() + ckIn.len() ) break;
		}while(1);
		return *this;
	}

	 
#endif

 
public:

////////////////////////////////////////////////////////
//Function:	Clear
//Effect:	clear the tbl.
//Return:	no return
	void Clear(void)
	{
		m_DATAcorpora.clear();
	}

///////////////////////////////////////////////////////
//Function:	GetRowCount
//Effect:	get row count of the tbl
//Return:	long
	long GetRowCount( )
	{
		return (long)m_DATAcorpora.size();
	}

///////////////////////////////////////////////////////
//Function:	GetRowCount
//Effect:	get row count of the tbl according to RPS
//Return:	long
	long GetRowCount(const std::vector<long> & vRps)
	{
		return (long)vRps.size();
	}

///////////////////////////////////////////////////////////
//Function:	GetRow
//Effect:	get one appointed row
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & GetRow(long lRowNum)
	{
		if(lRowNum>=0&&lRowNum<(long)m_DATAcorpora.size())
		return m_DATAcorpora[lRowNum];
		else 
		{
			a_mates_t_rowtype tmpEmptyrow;
			m_EmptyRow = tmpEmptyrow;
			return m_EmptyRow;
		}
	}

////////////////////////////////////////////////////////////
//Function:	GetRow
//Effect:	get one appointed row within RPS
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & GetRow(const std::vector<long> & vRps, long lRowNum)
	{
		long ltmp;
		do{
		{
			a_mates_t_rowtype tmpEmptyrow;
			m_EmptyRow = tmpEmptyrow;
		}
		ltmp = lRowNum;
		if(ltmp<0) return m_EmptyRow;
		if(ltmp>=(long)vRps.size()) return m_EmptyRow;
		ltmp = vRps[lRowNum];
		if(ltmp<0) return m_EmptyRow;
		if(ltmp>=(long)m_DATAcorpora.size()) return m_EmptyRow;
		return m_DATAcorpora[ltmp];
		}while(0);
	}

/////////////////////////////////////////////////////////////
//Function:	Add
//Effect:	add one appointed row and build the indexes, if any.
//Return:	no return
	void Add(const a_mates_t_rowtype & varRow)
	{
		m_DATAcorpora.push_back( varRow);
	}

/////////////////////////////////////////////////////////////
//Function:	AddDefaultRow
//Effect:	add one default row using Add function.
//Return:	no return
	void AddDefaultRow()
	{
		Add( a_mates_t_rowtype());
	}

/////////////////////////////////////////////////////////////
//Function:	ReIdx
//Effect:	re-build the indexes, if any.
//Return:	no return
	void ReIdx()
	{
	}

////////////////////////////////////////////////////////
//Function:	DelInternal
//Effect:	Internally del one appointed row number
//Return:	no return
	void DelInternal( long lRowNum )
	{
		if(!(lRowNum>=0&&lRowNum<(long)m_DATAcorpora.size())) return;
		m_DATAcorpora.erase( m_DATAcorpora.begin()+lRowNum);
	}

//////////////////////////////////////////////////////////////
//Function:	Del
//Effect:	Del one appointed row number. Rebuild indexes, if any.
//Return:	no return
	void Del( long lRowNum )
	{
		a_mates_t * p = new a_mates_t;
		*p = *this;
		p->DelInternal(lRowNum);
		Clear();
		for( long i = 0; i < p->GetRowCount(); i++ ) Add( p->GetRow(i) );
		delete p;
	}

///////////////////////////////////////////////////////////
//Function:	SelE_RES01
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_RES01(int iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES01==iVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

//////////////////////////////////////////////////////////
//Function:	SelE1_RES01
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_RES01(int iVal) 
	{
		std::vector<long> vRps ;
		SelE_RES01( iVal, vRps );
		return GetRow( vRps, 0 );
	}

///////////////////////////////////////////////////////
//Function:	SelEc_RES01
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_RES01(int iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_RES01(iVal, vRps, pRefRps);
	}

/////////////////////////////////////////////////////////////
//Function:	SelE_name
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_name(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_name==strVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

///////////////////////////////////////////////////////////////
//Function:	SelE1_name
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_name(std::string strVal) 
	{
		std::vector<long> vRps ;
		SelE_name( strVal, vRps );
		return GetRow( vRps, 0 );
	}

///////////////////////////////////////////////////////////////
//Function:	SelEc_name
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_name(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_name(strVal, vRps, pRefRps);
	}

////////////////////////////////////////////////////////////
//Function:	SelE_num
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_num(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_num==strVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

//////////////////////////////////////////////////////////
//Function:	SelE1_num
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_num(std::string strVal) 
	{
		std::vector<long> vRps ;
		SelE_num( strVal, vRps );
		return GetRow( vRps, 0 );
	}

////////////////////////////////////////////////////////////////
//Function:	SelEc_num
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_num(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_num(strVal, vRps, pRefRps);
	}

//////////////////////////////////////////////////////////////
//Function:	SelE_class
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_class(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_class==strVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

/////////////////////////////////////////////////////////////////
//Function:	SelE1_class
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_class(std::string strVal) 
	{
		std::vector<long> vRps ;
		SelE_class( strVal, vRps );
		return GetRow( vRps, 0 );
	}

/////////////////////////////////////////////////////////////////
//Function:	SelEc_class
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_class(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_class(strVal, vRps, pRefRps);
	}

////////////////////////////////////////////////////////////
//Function:	SelE_money
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_money(double dVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_money==dVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

////////////////////////////////////////////////////////
//Function:	SelE1_money
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_money(double dVal) 
	{
		std::vector<long> vRps ;
		SelE_money( dVal, vRps );
		return GetRow( vRps, 0 );
	}

////////////////////////////////////////////////////////////
//Function:	SelEc_money
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_money(double dVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_money(dVal, vRps, pRefRps);
	}

/////////////////////////////////////////////////////////
//Function:	SelE_RES02
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_RES02(NaL2S aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES02==aVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

////////////////////////////////////////////////////////////////
//Function:	SelE1_RES02
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_RES02(NaL2S aVal) 
	{
		std::vector<long> vRps ;
		SelE_RES02( aVal, vRps );
		return GetRow( vRps, 0 );
	}

/////////////////////////////////////////////////////////
//Function:	SelEc_RES02
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_RES02(NaL2S aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_RES02(aVal, vRps, pRefRps);
	}

///////////////////////////////////////////////////////////////
//Function:	SelE_take
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_take(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_take==strVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

////////////////////////////////////////////////////////////////
//Function:	SelE1_take
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_take(std::string strVal) 
	{
		std::vector<long> vRps ;
		SelE_take( strVal, vRps );
		return GetRow( vRps, 0 );
	}

/////////////////////////////////////////////////////////////////
//Function:	SelEc_take
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_take(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_take(strVal, vRps, pRefRps);
	}

/////////////////////////////////////////////////////////////////
//Function:	SelE_RES03
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_RES03(int iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES03==iVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

/////////////////////////////////////////////////////////////
//Function:	SelE1_RES03
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_RES03(int iVal) 
	{
		std::vector<long> vRps ;
		SelE_RES03( iVal, vRps );
		return GetRow( vRps, 0 );
	}

///////////////////////////////////////////////////////////
//Function:	SelEc_RES03
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_RES03(int iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_RES03(iVal, vRps, pRefRps);
	}

/////////////////////////////////////////////////////////
//Function:	SelE_RES05
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_RES05(ui8arr_t<2> aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES05==aVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

//////////////////////////////////////////////////////////
//Function:	SelE1_RES05
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_RES05(ui8arr_t<2> aVal) 
	{
		std::vector<long> vRps ;
		SelE_RES05( aVal, vRps );
		return GetRow( vRps, 0 );
	}

////////////////////////////////////////////////////////////////
//Function:	SelEc_RES05
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_RES05(ui8arr_t<2> aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_RES05(aVal, vRps, pRefRps);
	}

///////////////////////////////////////////////////////
//Function:	SelE_RES07
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_RES07(NaL2L aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES07==aVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

///////////////////////////////////////////////////////////
//Function:	SelE1_RES07
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_RES07(NaL2L aVal) 
	{
		std::vector<long> vRps ;
		SelE_RES07( aVal, vRps );
		return GetRow( vRps, 0 );
	}

////////////////////////////////////////////////////////
//Function:	SelEc_RES07
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_RES07(NaL2L aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_RES07(aVal, vRps, pRefRps);
	}

//////////////////////////////////////////////////////////////
//Function:	SelE_stamp_create
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_stamp_create(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_stamp_create==strVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

///////////////////////////////////////////////////////
//Function:	SelE1_stamp_create
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_stamp_create(std::string strVal) 
	{
		std::vector<long> vRps ;
		SelE_stamp_create( strVal, vRps );
		return GetRow( vRps, 0 );
	}

///////////////////////////////////////////////////////
//Function:	SelEc_stamp_create
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_stamp_create(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_stamp_create(strVal, vRps, pRefRps);
	}

/////////////////////////////////////////////////////////////////
//Function:	SelE_stamp_modi
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_stamp_modi(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_stamp_modi==strVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

//////////////////////////////////////////////////////////
//Function:	SelE1_stamp_modi
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_stamp_modi(std::string strVal) 
	{
		std::vector<long> vRps ;
		SelE_stamp_modi( strVal, vRps );
		return GetRow( vRps, 0 );
	}

//////////////////////////////////////////////////////////
//Function:	SelEc_stamp_modi
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_stamp_modi(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_stamp_modi(strVal, vRps, pRefRps);
	}

/////////////////////////////////////////////////////////////
//Function:	SelE_ip
//Effect:	select and build RPS where col=val use traverse
//Return:	no return
	void SelE_ip(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //(ni)
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_ip==strVal)
		if( !pRefRps || !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) vRps.push_back( ltmp );
	}

//////////////////////////////////////////////////////////////
//Function:	SelE1_ip
//Effect:	select 1st row where col=val, or return default row.
//Return:	a_mates_t_rowtype&
	a_mates_t_rowtype & SelE1_ip(std::string strVal) 
	{
		std::vector<long> vRps ;
		SelE_ip( strVal, vRps );
		return GetRow( vRps, 0 );
	}

////////////////////////////////////////////////////////////////
//Function:	SelEc_ip
//Effect:	select and build RPS where col=val. clear rps first.
//Return:	no return
	void SelEc_ip(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) //()
	{
		vRps.clear();
		SelE_ip(strVal, vRps, pRefRps);
	}

//////////////////////////////////////////////////////////////
//Function:	RpsAnd
//Effect:	set intersection for RPSs. the varRpsSource1 is also the result.
//Return:	RPSTYPE &
	RPSTYPE & RpsAnd( RPSTYPE & varRpsSource1, RPSTYPE & varRpsSource2 )
	{
		std::sort( varRpsSource1.begin(), varRpsSource1.end() );
		std::sort( varRpsSource2.begin(), varRpsSource2.end() );
		RPSTYPE source3(varRpsSource1.size()+varRpsSource2.size());
		RPSTYPE::iterator itNewEnd2 = std::set_intersection( 
		 varRpsSource1.begin(), varRpsSource1.end(), varRpsSource2.begin(), varRpsSource2.end(), source3.begin() );
		varRpsSource1.clear();
		for(RPSTYPE::iterator it=source3.begin();it!=itNewEnd2;++it) varRpsSource1.push_back(*it);
		return varRpsSource1;
	}

////////////////////////////////////////////////////////////
//Function:	RpsAnd
//Effect:	set intersection for RPSs. the rps3 is the result. sortflag: 10=rps1 sorted. 01=rps2 sorted.
//Return:	RPSTYPE &
	RPSTYPE & RpsAnd( RPSTYPE & varRpsSource1, RPSTYPE & varRpsSource2, RPSTYPE & vRps3, int sort_flag = 0 )
	{
		if( (sort_flag & 2 ) == 0 ) std::sort( varRpsSource1.begin(), varRpsSource1.end() );
		if( (sort_flag & 1 ) == 0 ) std::sort( varRpsSource2.begin(), varRpsSource2.end() ); 
		vRps3.clear();
		std::set_intersection( 
		 varRpsSource1.begin(), varRpsSource1.end(), varRpsSource2.begin(), varRpsSource2.end(), std::insert_iterator<RPSTYPE>(vRps3,vRps3.begin()) );
		return vRps3;
	}

/////////////////////////////////////////////////////////
//Function:	RpsOr
//Effect:	set union for RPSs. the varRpsSource1 is also the result.
//Return:	RPSTYPE &
	RPSTYPE & RpsOr( RPSTYPE & varRpsSource1, RPSTYPE & varRpsSource2 )
	{
		std::sort( varRpsSource1.begin(), varRpsSource1.end() );
		std::sort( varRpsSource2.begin(), varRpsSource2.end() );
		RPSTYPE source3(varRpsSource1.size()+varRpsSource2.size());
		RPSTYPE::iterator itNewEnd2 = std::set_union( 
		 varRpsSource1.begin(), varRpsSource1.end(), varRpsSource2.begin(), varRpsSource2.end(), source3.begin() );
		varRpsSource1.clear();
		for(RPSTYPE::iterator it=source3.begin();it!=itNewEnd2;++it) varRpsSource1.push_back(*it);
		return varRpsSource1;
	}

 
}
; 
//end of class a_mates_t


#endif

