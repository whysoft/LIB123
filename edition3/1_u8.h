 
/*
* This material is provided "as is", with absolutely no warranty expressed
* or implied. Any use is at your own risk.
* Permission to use or copy this software for any purpose is hereby granted
* without fee, provided the above notices are retained on all copies.
* Permission to modify the code and to distribute modified code is granted,
* provided the above notices are retained, and a notice that the code was
* modified is included with the above copyright notice.
*/
// WARNING: This is an internal header file, included by other C++
// standard library headers. You should attempt to use this header
// file directly.
// This file provides a middle-level interface between the the C standard 
// library, and the C++ .

/*  
2017c06c22c周四-15c42c31.49  
*/  
#ifdef WINENV_
#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(disable: 4786)

#include <shellapi.h>
#pragma comment( lib, "ws2_32.lib" )
#include <winsock.h>




#ifndef X011__H_w_sbase_h
#define X011__H_w_sbase_h


#define X011_NAMESPACE_BEGIN namespace wl {
#define X011_NAMESPACE_END                }


#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>


X011_NAMESPACE_BEGIN


typedef		double					tdouble; 
typedef		char					tint8;
typedef		unsigned char			tuint8;
typedef		short					tint16;
typedef		unsigned short			tuint16;
typedef		long					tint32;
typedef		unsigned long			tuint32;

typedef     __int64                 tint64;
typedef    unsigned __int64         tuint64; 


typedef		tint8				tchar;
typedef		int					tbool;


typedef		tuint32			tsize;
typedef		tint32			toffset;


X011_NAMESPACE_END




#endif





#ifndef X011__H_w_SClib_h
#define X011__H_w_SClib_h


#pragma warning(push)
#pragma warning(disable: 4996)


X011_NAMESPACE_BEGIN


class SClib	
{

public:

	SClib(){;}

	~SClib(){;}

	typedef int (* PT_sscanf)( const char *buffer, const char *format , ... );
	static PT_sscanf p_sscanf() { return sscanf; }

	typedef int (* PT_sprintf)( char *, const char *, ... );
	static PT_sprintf p_sprintf() { return sprintf; }

	typedef int (* PT_vsprintf)( char *, const char *, va_list aaa );
	static PT_vsprintf p_vsprintf() { return vsprintf; }

	typedef char * (* PT_strcpy)( char *strDestination, const char *strSource );
	static PT_strcpy p_strcpy() { return strcpy; }


	typedef tm * (* PT_localtime)( const time_t * );
	static PT_localtime p_localtime() { return localtime; }

	typedef FILE * (* PT_fopen)( const char *filename, const char *mode );
	static PT_fopen p_fopen(){ return fopen; }


	typedef char * (* PT_ltoa)( long value, char *str, int radix );
	static PT_ltoa p_ltoa() { return ltoa; }


}; 




X011_NAMESPACE_END


#pragma warning(pop)


#endif






#ifndef X011__H_w_sstrf_h
#define X011__H_w_sstrf_h


X011_NAMESPACE_BEGIN


class SStrf
{

public:

	
	
	 ~SStrf(){;}

	
	template < class T >
	static T * AddressOf( T & obj )
	{
		return reinterpret_cast<T *>(&reinterpret_cast<char&>(obj));
	}

	
	template< class T >
	static T * newobjptr( T * & p )
	{
		try
		{
			p = new T;
		}
		catch(...)
		{
			p = NULL;
		}

		return p;
	}

	
	template< class T >
	static T * newobjptr()  
	{
		T *  p;
		return newobjptr(p);
	}

	
	static void * smalloc( tsize i )
	{
		return malloc( i );
	}

	
	static void sfree(void *s)
	{
		free(s);
	}


	static tuint16 smkU16( tuint8 c1, tuint8 c2) 
	{
	   tuint16 ilow,ihigh;
	   ilow =  (tuint16)c1;
	   ihigh = (tuint16)c2;
	   ihigh <<= 8;
	   return ihigh + ilow;
	}


	template< class INTData_T >
	static INTData_T MkBlock2INTDataMem( const void *pBlock , tbool Ischgendian = 0 )
	{
		 INTData_T x;
		 memcpy( &x, pBlock, sizeof(INTData_T) );
		if( Ischgendian ) chgendian( x );
		 return x;
	}

	
	template< class INTData_T >
	static INTData_T & MkBlock2INTDataRef( const void *pBlock, INTData_T & x , tbool Ischgendian = 0 )
	{
		 memcpy( &x, pBlock, sizeof(INTData_T) );
		if( Ischgendian ) chgendian( x );
		 return x;
	}

	
	template< class INTData_T >
	static char * MkINTData2BlockMem( const void *pINTData, char *pBlockOut , tbool Ischgendian = 0 )
	{
		if( !Ischgendian ) 
		{
			 memcpy( pBlockOut, pINTData, sizeof(INTData_T) );
			 return pBlockOut;
		}

		
		INTData_T x;
		memcpy( &x, pINTData, sizeof(INTData_T) );
		chgendian( x );
		return MkINTData2BlockMem<INTData_T>( &x, pBlockOut, 0 );
	}

	
	template< class INTData_T >
	static char * MkINTData2BlockRef( const INTData_T &a, char *pBlockOut , tbool Ischgendian = 0 )
	{
		const void *pINTData = &a;
		return MkINTData2BlockMem<INTData_T>( pINTData, pBlockOut, Ischgendian );
	}


	static tbool is_little_endian()
	{
		tuint32 i = 1;
		char *p = (char*)(&i);
		return *p ? 1 : 0;
	}


	template< class T >
	static T & chgendian( T & val )
	{
		if( sizeof(T) != 1 ) srev( (tchar *)&(val), sizeof(T) );
		return val;
	}

	
	template< class T >
	static T chgendian2( T val )
	{
		return chgendian(val);
	}


	
	
	
	
	static tbool readbit_s( void * pbin, int iBytesLen, int sufx )
	{
		if( sufx < 0 || iBytesLen <= 0 || (sufx / 8) >= iBytesLen )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		
		iOffset =  (sufx % 8);

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}


	static tbool readbit_r_s( void * pbin, int iBytesLen, int sufx )
	{
		if( sufx < 0 || iBytesLen <= 0 || (sufx / 8) >= iBytesLen )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		iOffset = 7 - (sufx % 8); 
		

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}


	static tbool readbit_p( void * pbin, int sufx )
	{
		if( sufx < 0 )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		
		iOffset =  (sufx % 8);

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}


	static tbool readbit_r_p( void * pbin, int sufx )
	{
		if( sufx < 0 )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		iOffset = 7 - (sufx % 8); 
		

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}


	template<class T>
	static tbool readbit( T bindata , int sufx )  
	{
		return readbit_s( &bindata, (int)sizeof(T), sufx );
	}


	template<class T>
	static tbool readbit_r( T bindata , int sufx )  
	{
		return readbit_r_s( &bindata, (int)sizeof(T), sufx );
	}


	
	static void writebit( void * pbin , int sufx , tbool val )
	{
		if( sufx < 0 )
		{
			return ;
		}

		val = val?1:0;

		tuint8 * pbin2 = (tuint8 *)pbin;
		int cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		
		iOffset = (sufx % 8);

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;

		if( cSrc == val ) return ;

		int i = 1;
		i <<= iOffset;

		pbin2[sufx / 8] ^= i;
	}


	static void writebit_r( void * pbin , int sufx , tbool val )
	{
		if( sufx < 0 )
		{
			return ;
		}

		val = val?1:0;

		tuint8 * pbin2 = (tuint8 *)pbin;
		int cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		iOffset = 7 - (sufx % 8);
		

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;

		if( cSrc == val ) return ;

		int i = 1;
		i <<= iOffset;

		pbin2[sufx / 8] ^= i;
	}


	static void writebit_s( void * pbin, int iBytesLen, int sufx , tbool val )
	{
		if( sufx < 0 || iBytesLen <= 0 || (sufx / 8) >= iBytesLen )
		{
			return;
		}
		writebit( pbin, sufx , val );
	}


	
	template<class T> 
	static std::string & byte2binstr( T c, std::string & strrtn )
	{
		strrtn = "01234567";
		for( int i = 0; i < 8; i++ ) strrtn[i] = readbit( c, i ) ? '1' : '0' ;
		return strrtn;
	}

	
	template<class T> 
	static std::string byte2binstr( T c )
	{
		std::string str;
		return byte2binstr( c, str );
	}

	
	template<class T> 
	static T & binstr2byte( std::string str, T & c )
	{
		
		str += "00000000";
		for( int i = 0; i < 8; i++ ) writebit( &c, i , str[i]=='0' ? 0 : 1 );
		return c;
	}

	
	static tuint8 binstr2byte( std::string str )
	{
		tuint8 c;
		return binstr2byte( str, c );
	}


	static void initrand( int seed = 0 ) 
	{
		tint32 j=(tint16)(0x0555&(time(0)*seed));
		for(tint32 i=0;i<j;++i) rand();
	}

	
	static tdouble rand1( int iShouldInitSeed = 0 )
	{
		if( iShouldInitSeed ) initrand( iShouldInitSeed );
		return (tdouble)rand()/(tdouble)RAND_MAX;
	}

	
	static void * randfill( void *dest, tsize count )
	{
		unsigned char *p = (unsigned char *)dest;
		for( tsize j = 0; j < count; j++ )
		{
			p[j] = (unsigned char)(rand() & 0xFF );
		}
		return dest;
	}

	
	template< class T >
	static void * randfill( T & dest )
	{
		return randfill( &dest, sizeof(T) );
	}


	static void *smemcpy( void *dest, const void *src, tsize count )
	{
		return memcpy(dest,src,count);
	}

	
	static void * smemset( void *dest, tuint8 c, tsize count )
	{
		return memset( dest, (int)c, (size_t)count );
	}

	
	template< class T >
	static void * smemset( T & dest, tuint8 c = 0 )
	{
		return memset( &dest, (int)c, sizeof(T) );
	}


	static tchar * scpy( tchar *strDestination, const tchar *strSource )
	{
		return (*SClib::p_strcpy())( strDestination, strSource );
	}

	
	static tsize slen( const tchar * s ) 
	{
		if(s==NULL) return (tsize)0;
		return (tsize)strlen(s);
	}

	
	static tbool sishex(tchar c)
	{
		return  (c>='0'&&c<='9')||(c>='A'&&c<='F')||(c>='a'&&c<='f');
	}

	
	static tbool sishex(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sishex(*s)) return 0;
		return 1;
	}

	
	static tbool sisdec(tchar c) 
	{
		return  (c>='0'&&c<='9');
	}

	
	static tbool sisdec(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sisdec(*s)) return 0;
		return 1;
	}

	
	static tbool sisalpha(char c) 
	{
		return sisdec(c) || (c>='A'&&c<='Z')|| (c>='a'&&c<='z');
	}


	static tchar *sltoa( tint32 i, tchar *buf, int radix = 10 )
	{
		return (*SClib::p_ltoa())(i, buf, radix);
	}

	
	static std::string sltoa( tint32 i, int radix = 10 )
	{
		tchar c[55];
		std::string buf;
		buf = sltoa( i, c, radix );
		return buf;
	}

	
	static tint32 satol( const tchar *s ) { return(s==NULL)?0:(tint32)atol(s); }

	
	static tint32 satol( const std::string & s ) { return satol(s.c_str()); }

	
	static tint32 satol_16( std::string s )
	{
		tint32 ii;
		(SClib::p_sscanf())( s.c_str(), "%x", &ii );
		return ii;
	}


	static std::string sultoa( tuint32 i )
	{
		std::stringstream stream;
		stream << i;
		return stream.str();
	}


	static std::string sultoa_h( std::string s1 )
	{
		if( s1.size() <= 3 ) 
		{
			return s1.c_str();
		}

		if( s1.size() <= 6 ) 
		{
			s1.insert( s1.begin() + ( s1.size() - 3 ), '.' );
			s1[ ( s1.size() - 3 ) + 1 ] = 'K';
			s1[ ( s1.size() - 3 ) + 2 ] = 0;
			return s1.c_str();
		}

		
		{
			s1.insert( s1.begin() + ( s1.size() - 6 ), '.' );
			s1[ ( s1.size() - 6 ) + 1 ] = 'M';
			s1[ ( s1.size() - 6 ) + 2 ] = 0;
			return s1.c_str();
		}
	}

	
	static std::string sultoa_h( tuint32 i )
	{
		return sultoa_h( sultoa(i) );
	}


	
	static tuint32 satoul( std::string s )
	{
		return strtoul( s.c_str(), NULL, 10 );
	}

	
	static tuint32 satoul_16( std::string s )
	{
		return strtoul( s.c_str(), NULL, 16 );
	}

	
	static tuint32 satoul_x( std::string s )
	{
		return strtoul( s.c_str(), NULL, 0 );
	}


	static std::string GetBcdStr( tuint8 c1 )
	{
		char s[11];
		(*SClib::p_sprintf())( s, "%02X", (unsigned int)c1 );
		return s;
	}

	
	static std::string GetBcdStr2Str( std::string s1 )
	{
		return GetBcdStr( (tuint8)satol(s1) );
	}

	
	
	
	
	


	static tuint8 GetBcdInt( tuint8 c1 ) 
	{
		return (tuint8)satol(GetBcdStr(c1));
	}

	
	static tuint8 Num2Bcd( tuint8 c1 )
	{
		tint32 ii;
		char s[11];
		(*SClib::p_sprintf())( s, "%d", (unsigned int)c1 );
		(SClib::p_sscanf())( s, "%x", &ii );
		return (tuint8)ii;
	}


	static tchar * sftoa( tdouble f , tchar * buf , int decimal_digits = -1 )
	
	{
		std::string s1;

		if( decimal_digits < 0 )
		{
			s1 = "%f";
		}
		else
		{
			s1 = "%." + sltoa(decimal_digits) + "f";
		}

		(*SClib::p_sprintf())( buf, s1.c_str(), f );

		return buf;
	}

	
	static std::string sftoa( tdouble f , int decimal_digits = -1 )
	{
		if( decimal_digits < -1 ) decimal_digits = -1;

		std::vector<char> v( 66 + decimal_digits );
		tchar * c;

		c = &(v[0]);
		return  sftoa( f, c , decimal_digits );
	}

	
	static tdouble satof( const tchar *s )
	{
		if(s==NULL) return 0.0;
		return (tdouble)atof(s);
	}

	
	static tdouble satof( const std::string & s )
	{
		return satof(s.c_str());
	}

	
	static int scmpi( const tchar *a, const tchar *b )	
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		toffset i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i];i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z') c1+=('A'-'a');
			if(c2>='a'&&c2<='z') c2+=('A'-'a');
			if(c1!=c2) return c1-c2;
		}
		return t1[i]-t2[i];
	}

	
	static int scmpin( const tchar *a, const tchar *b, tsize count ) 
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		tsize i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i]&&i<count;i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z')c1+=('A'-'a');
			if(c2>='a'&&c2<='z')c2+=('A'-'a');
			if(c1!=c2)return c1-c2;
		}
		if(i>0) i--;
		return t1[i]-t2[i];
	}


	static int scmpin( const tchar *a, const tchar *b ) 
	{
		return scmpin(a,b,slen(b));
	}



	static int scmpn( const tchar *a, const tchar *b, tsize count )
	{
		if(!count) return 0; 
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1; 
		if(a!=NULL&&b==NULL) return 1;  
		return strncmp(a,b,count);
	}


	static int scmpn( const tchar *a, const tchar *b ) 
	{
		return scmpn(a,b,slen(b));
	}



	static int scmp( const tchar *a, const tchar *b )
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		return strcmp(a,b);
	}


	static tchar * sucase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='a'&&s[i]<='z')s[i] = s[i] -'a' + 'A' ;
		}
		return s;
	}


	static std::string & sucase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		sucase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}


	static tchar * slcase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='A'&&s[i]<='Z')s[i] = s[i] -'A' + 'a' ;
		}
		return s;
	}


	static std::string & slcase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		slcase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}


	
	
	template< class Pchar_CPchar_T >	
	static Pchar_CPchar_T splast( Pchar_CPchar_T s, toffset offset2left = 0  )
	{
		Pchar_CPchar_T t = s;
		if(!s||!*s) return t; 
		toffset i,j ;
		j = (toffset)slen(s);
		i = j - 1 - offset2left ;
		t=s+(i<0?0:i);
		return t;
	}

	
	template< class Pchar_CPchar_T >
	static Pchar_CPchar_T splast( Pchar_CPchar_T s, tsize uiLen, toffset offset2left  )
	{
		Pchar_CPchar_T t = s;
		if(!s||!*s) return t; 
		toffset i,j ;
		j = (toffset)uiLen;
		i = j - 1 - offset2left ;
		t=s+(i<0?0:i);
		return t;
	}


	static const tchar * sstr( const tchar * s, const tchar *substr )
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (const tchar *)strstr(s,substr);
	}

	
	static tchar * sstr( tchar * s, const tchar *substr )
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (tchar *)strstr(s,substr);
	}

	
	template< class Pchar_CPchar_T >
	static Pchar_CPchar_T sstr( Pchar_CPchar_T s, tchar subc )
	{
		tchar t[2];
		t[0]=subc;
		t[1]=0;
		return sstr(s,t) ;
	}




	static tchar * srev( tchar * s, tsize len )
	{
		tsize u;
		toffset  x, y, i, a, b;
		u = len;
		u >>= 1;
		x = u;
		y = (toffset)len - 1;
		for(i=0;i<x;i++) {
			a = i;
			b = y - i;
			s[a] ^= s[b];
			s[b] ^= s[a];
			s[a] ^= s[b];
		}
		return s;
	}

	
	static tchar *srev( tchar * s )
	{
		return srev(s,slen(s));
	}

	
	static tchar * sreplch( tchar * source, tsize len, tchar c1, tchar c2 )	
	{
		tsize i;
		for(i=0;source&&i<len;i++) {
			if(source[i]==c1) source[i]=c2;
		}
		return source;
	}


	static tchar * sreplch( tchar * source, tchar c1, tchar c2 )	
	{
		return sreplch(source, slen(source), c1, c2);
	}


	static std::string & sreplstr( std::string & str, const tchar *string_to_replace, const tchar *new_string )
	{
		if( string_to_replace && new_string )
		{
			
			std::string::size_type   index   =   str.find(string_to_replace);
			
			while(index   !=   std::string::npos)
			{
				
				str.replace(index,   strlen(string_to_replace),   new_string);
				
				index   =   str.find(string_to_replace,   index   +   strlen(new_string));
			}
		}
		return   str;
	}


	static std::string & sreplstr( std::string & str, const std::string & string_to_replace, const std::string & new_string )
	{
		return sreplstr( str, string_to_replace.c_str(), new_string.c_str() ) ;
	}

	
	
	
	

	
	

	
	static std::string Chg2XmlCode( std::string s )
	{
		sreplstr( s, "&",  "&amp;"  );
		sreplstr( s, "<",  "&lt;"   );
		sreplstr( s, ">",  "&gt;"   );
		sreplstr( s, " ",  "&nbsp;"  );
		sreplstr( s, "\"", "&quot;"  );
		return s;
	}


	

	static std::string & str_trim_base( tchar *(*f)( tchar *, const tchar * ), std::string & str, const tchar *str_space="\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = (*f)( pstr, str_space );
		sfree( pstr );
		return str;
	}



	static tchar * strimr( tchar * s, tchar a_space ) 
	{
		toffset i;
		for(i=slen(s)-1;i>=0;i--)
			if(s[i]==a_space)
				s[i]=0;
			else
				break;
		return s;
	}

	static tchar * strimr( tchar * s, const tchar *str_space="\r\n \t" ) 
	{
		toffset i;
		for( i=slen(s)-1; i >= 0; i-- )
			if( sstr(str_space,s[i]) != NULL )
				s[i]=0;
			else
				break;
		return s;
	}

	static std::string & strimr( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strimr, str, str_space );
	}



	static tchar * striml( tchar * s, tchar a_space )	
	{
		return srev( strimr(srev(s), a_space) ) ;
	}

	static tchar * striml( tchar * s, const tchar * str_space = "\r\n \t" )		
	{
		return srev( strimr(srev(s), str_space) ) ;
	}

	static std::string & striml( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = striml( pstr, str_space );
		sfree( pstr );
		return str;
	}



	static tchar * strim( tchar * s, tchar a_space  ) 
	{
		return  striml( strimr(s,a_space), a_space) ;
	}

	static tchar * strim( tchar * s, const tchar * str_space = "\r\n \t" ) 
	{
		return  striml( strimr(s,str_space), str_space) ;
	}

	static std::string & strim( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strim , str, str_space );
	}

	


	static tchar * sleft( tchar * s, tsize n ) 
	{
		if(n>slen(s)) return s;
		s[n]=0;
		return s;
	}


	static tchar * sright( tchar * s, tsize n )
	{
		return srev(sleft(srev(s), n));
	}


	static tchar * smid( tchar * s, tsize a_pos, tsize a_len )
	{
		sright(s, slen(s) - a_pos );
		sleft(s, a_len);
		return s;
	}


	static const tchar * seq_dirno()
	{
		return "0123456789ACEFHKLMPQSTUWXYZ"; 
	}


	static std::string seq( std::string strCurNum, tbool isFixLen = 1, const tchar * s_symbset = NULL )
	{
		static tchar c[1];
		tchar * s_num;
		tint16 *lia ;
		tint16 ulia;
		tint32 i,j,k;

		c[0]=0;
		if(slen(s_symbset)<2) s_symbset = seq_dirno();
		s_num = (tchar*)smalloc( (tsize)strCurNum.size() + 2 );
		if(!s_num) return "";

		scpy( s_num, strCurNum.c_str() );

		lia = (tint16 *)smalloc( (slen(s_num) + 1)*sizeof(tint16) );
		if(!lia)
		{
			sfree(s_num);
			return "";
		}

		if(!(*s_num)) {
			s_num[0]=s_symbset[0];
			s_num[1]=0;
		}

		j = slen(s_num) ;
		for(i=0;i<j;i++)
		{
			const char *t = sstr( s_symbset, s_num[i] );
			if(!t)
				lia[i] = 0;
			else
				lia[i] = (tint16)( t - s_symbset );
		}

		lia[j-1] ++;
		k = slen(s_symbset) ;
		ulia = 0;
		for(i=j-1;i>=0;i--)
		{
			if(lia[i] >= k)
			{
				lia[i] -= (tint16)k;
				if(i>0)
					lia[i-1]++;
				else
					ulia++;
			}
		}

		for( i=0;i<j;i++ )
		{
			s_num[i] = s_symbset[ lia[i] ];
		}

		if( (!isFixLen) && ulia )	
		{
			srev(s_num);
			s_num[j] = s_symbset[ulia];
			s_num[j+1] = 0;
			srev(s_num);
		}

		strCurNum = s_num;
		sfree(s_num);
		sfree(lia);
		return strCurNum;
	}



	static tchar bs_esc() { return 'b'; }


	static tbool bs_inset( tchar c ) 
	{
		if(c==bs_esc()) return 0; 
		if(c>='a'&&c<='z') return 1;
		if(c>='0'&&c<='9') return 1;
		if(c>='A'&&c<='Z') return 1;
		return 0;
	}


	static tsize bs_ensize( const tchar *s, tsize len )
	{
		tsize i;
		tchar *t1, *t2, *t3;
		if(s==NULL) return 0;
		i=0;
		t1=(tchar*)s;
		t3=t1+len;
		for( t2=t1; t2<t3; t2++ )
			i += bs_inset(*t2)?(1*sizeof(tchar)):(3*sizeof(tchar));

		return i+(sizeof(tchar)); 
	}


	static tsize bs_ensize( const tchar *s )
	{
		return bs_ensize( s, slen(s) + 1 );
	}


	static tchar * bs_en( const tchar *s, tsize len, tchar *destbuf )
	{
		tchar *ss1, *ss2, *ss3, *sd1;
		tbool rc;
		int l;
		if(s==NULL||destbuf==NULL) return NULL;
		ss1 = (tchar*)s;
		ss3 = ss1 + len;
		sd1 = destbuf;

		for( ss2=ss1; ss2<ss3; ss2++)
		{
			rc = 0;

			do 
			{
				if( !bs_inset(*ss2) ) 
				{
					rc = 1;
					break;
				}

				*sd1 = *ss2;         
				sd1++;

			}while(0);

			if(rc) {    
				l = (tuint8)(*ss2);
				(*SClib::p_sprintf())( sd1, "%c%02X", bs_esc(), l );
				sd1 += (3*sizeof(tchar));
			}
		}
		*sd1=0;
		return destbuf;
	}


	static tchar * bs_en( const tchar *s, tchar *destbuf )
	{
		return bs_en( s, slen(s) + 1, destbuf );
	}

	static std::string  & bs_en( std::string & strData ) 
	{
		std::string s1( 3 + bs_ensize( strData.c_str(), (tsize)strData.length() ) , 'a' );

		bs_en( strData.c_str(), &(s1[0]) );

		return strData = s1.c_str();
	}

	
	static std::string  & bs_de( std::string & strData , tchar(*apf1)()=bs_esc )
	{
		std::string s1( strData );

		s1 += (*apf1)( ); 
		s1 += "00123";

		strData += (*apf1)( ); 
		strData += "00123";

		bs_de( strData.c_str(), &(s1[0]) , apf1 );

		return strData = s1.c_str();
	}

	
	static tsize bs_desize( const tchar *s , tchar(*apf1)()=bs_esc )
	{
		toffset j,i;
		tsize  k;
		if(s==NULL) return 0;

		for( i=0,j=(toffset)slen(s),k=0;i<j; )
			if(	(i+2<j)				&&
				s[i]==(*apf1)( )	&&
				sishex(s[i+1])		&&
				sishex(s[i+2])  )
			{
				k++;
				i+=3;
			}
			else
			{
				i++;
				k++;
			}
		return k;
	}

	
	static tchar * bs_de( const tchar *s, tchar *dest , tchar(*apf1)()=bs_esc ) 
	{
		if(s==NULL||dest==NULL) return dest;
		toffset i,j,k;
		toffset a1,a2;
		tchar ss[2];
		ss[1]=0;

		for(i=0,j=(toffset)slen(s),k=0;i<j; ) {
			if(	(i+2<j)			&&
				s[i]==(*apf1)( )&&
				sishex(s[i+1])	&&
				sishex(s[i+2])	 )
			{
				ss[0]=s[i+1];
				sucase(ss);
				a1 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) * 16 ;

				ss[0]=s[i+2];
				sucase(ss);
				a2 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) ;

				*(tchar *)(dest+k) = (tuint8)(a1+a2);
				k++;
				i+=3;
			}else{
				dest[k] = s[i];
				k++;
				i++;
			}
		}

		return dest;
	}


	static tchar * bs_de( tchar *source_dest , tchar(*apf1)()=bs_esc ) 
	{
		return bs_de(source_dest,source_dest,apf1);
	}


	static std::string b2s( void *p, long len )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( len * 3 + 12 );
		bs_en( (const char *)p, len, szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
	}

	
	template< class T >
	static std::string b2s(  T & sourcedata )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( sizeof(T) * 3 + 12 );
		bs_en( (const char *)reinterpret_cast<const char *>(&reinterpret_cast< const char& >(sourcedata)), sizeof(T), szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
	}

	
	template< class T >
	static std::string b2s_i( T sourcedata )
	{
		return b2s(sourcedata);
	}

	
	template< class T >
	static std::string b2s_const( const T & sourcedata )
	{
		return b2s_i(sourcedata);
	}

	
	template< class T >
	static T & s2b( std::string strSource, T & destdata )
	{
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}


	template< class T >
	static T s2b( std::string strSource )
	{
		T destdata;
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}


	#if 1
	

	template < class T >
	static T & mkint( T & _out, tuint8 *p1, int len, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		if( biIsIntel )
		{
			tuint8 *p2 = (tuint8 *)&_out;
			int i,j,k,x,signflag;
			j = (int)(sizeof(T)<=len?sizeof(T):len);
			k = (int)sizeof(T);
			signflag = biHaveSign && (p1[len-1] & (tuint8)0x80);
			
			for( i = 0 ; i < j; i++ )
			{
				if( signflag && i == j - 1 && j != k )
					p2[i] = p1[i]; 
				else
					p2[i] = p1[i];
			}
			
			for( x=i; x < k; x++ ) 
			{
				if( signflag )
					p2[x] = (tuint8)0xff;
				else
					p2[x] = (tuint8)0;
			}
		} 
		else
		{
			srev( (tchar *)p1, len );
			mkint( _out, p1, len, 1, biHaveSign );
			srev( (tchar *)p1, len ); 
			chgendian(_out);
		} 

		return _out;
	}

	
	template<class T> static T & mkint( T & _out, tuint8 c1, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		tuint8 c[4];
		c[0] = (tuint8)c1;
		return mkint( _out, c, 1, biIsIntel, biHaveSign );
	}
	
	template<class T> static T & mkint( T & _out, tuint8 c1, tuint8 c2, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		tuint8 c[4];
		c[0] = (tuint8)c1; c[1] = (tuint8)c2;
		return mkint( _out, c, 2, biIsIntel, biHaveSign );
	}
	
	template<class T> static T & mkint( T & _out, tuint8 c1, tuint8 c2, tuint8 c3, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		tuint8 c[4];
		c[0] = (tuint8)c1; c[1] = (tuint8)c2; c[2] = (tuint8)c3;
		return mkint( _out, c, 3, biIsIntel, biHaveSign );
	}
	
	template<class T> static T & mkint( T & _out, tuint8 c1, tuint8 c2, tuint8 c3, tuint8 c4, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		tuint8 c[4];
		c[0] = (tuint8)c1; c[1] = (tuint8)c2; c[2] = (tuint8)c3; c[3] = (tuint8)c4;
		return mkint( _out, c, 4, biIsIntel, biHaveSign );
	}

	
	#endif


	#if 0
	static unsigned char mk_chksumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += sz1[j];

		sz1[iLen-1] = c1;

		return 1;
	}

	static unsigned char chk_chksumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += sz1[j];

		if( sz1[iLen-1] == c1 )
			return 1;
		else
			return 0;
	}
	#endif


	
	#if 0
	static void mk_busycode( unsigned char src, unsigned char *pDest )
	{
		unsigned char mask;
		unsigned char i;

		mask = 0x80;
		pDest[0] = 0;
		pDest[1] = 0;

		for( i = 0; i < 8; i++ )
		{
			if( src & mask ) 
			{
				
				pDest[i/4] <<= 1;
				pDest[i/4] ++;
				if( i != 3 && i != 7 )
					pDest[i/4] <<= 1;
			}
			else
			{
				pDest[i/4] ++;
				pDest[i/4] <<= 1;
				
				if( i != 3 && i != 7 )
					pDest[i/4] <<= 1;
			}
			mask >>= 1;
		}
	}
	#endif

	
	#if 1
	static void mk_busycode( unsigned char src, unsigned char *pDest )
	{
		unsigned char mask;
		unsigned char i;

		

		mask = 0x80;
		for( i = 0; i < 8; i++ )
		{
			if( src & mask ) 
			{
				pDest[i/4] <<= 1;
				pDest[i/4] &= 0xfe;

				pDest[i/4] <<= 1;
				pDest[i/4] |= 1;
			}
			else
			{
				pDest[i/4] <<= 1;
				pDest[i/4] |= 1;

				pDest[i/4] <<= 1;
				pDest[i/4] &= 0xfe;
			}
			mask >>= 1;
		}
	}
	#endif


	
	#if 0
	static unsigned char chk_busycode( unsigned char *p )
	{
		unsigned char mask;
		unsigned char i;
		unsigned char c;

		mask = 0x80;
		c = 0;

		for( i = 0; i < 8; i++ )
		{
			if( !(p[i/4] & mask) ) c++;
			if( i != 7 ) c <<= 1;
			p[i/4] <<= 1;
			p[i/4] <<= 1;
		}
		return c;
	}
	#endif

	
	#if 1
	static unsigned char chk_busycode( unsigned char *p )
	{
		unsigned char i;
		unsigned char c;

		
		for( i = 0; i < 8; i++ )
		{
			if( p[i/4] & 0x80 )
			{
				c <<= 1;
				c &= 0xfe;
			}
			else
			{
				c <<= 1;
				c |= 1;
			}

			p[i/4] <<= 1;
			p[i/4] <<= 1;
		}
		return c;
	}
	#endif


	
	static std::string chg_jian2big( std::string s1, const char * jian, const char *fan, long jf_len )
	{
		char p[] = {0,0,0};
		const char * p1 ;
		long j,k;

		for( j = 0; j < (int)s1.size(); j++ )
		{
			p[0] = s1[j];
			int c = static_cast<int>(p[0]);

			if( c > 0 && c <= 127 )
			{
				continue;
			}
			j++;
			if( j == s1.size() ) break;
			p[1] = s1[j];

			
			k = 0;
			for( p1 = jian; p1 < jian + jf_len + 1; p1++ )
			{
				if( p1[0] == p[0] && p1[1] == p[1] )
				{
					k = 1;
					break;
				}

				int c = static_cast<int>(*p1);

				if( c > 0 && c <= 127 )
				{
				}
				else p1++;
			}
			if( k == 0 ) continue; 

			k = (long)(p1 - jian);

			s1[j-1] = fan[k];
			s1[j] = fan[k+1];
		}

		return s1;
	}


}; 




template < class INT_T, int LEN_T >
class uiarr_t
{
public:
	INT_T a[LEN_T];

	template < class _T >
	bool operator == (const _T & rhs) const
	{
		size_t i1, i2, i3 , i;
		i1 = sizeof(a);
		i2 = sizeof(rhs);
		if( i1 != i2 ) return false;
		if( i1 < i2 ) i3 = i1; else i3 = i2;
		for( i = 0; i < i3; i++ )
		{
			if( a[i] != rhs.a[i] ) return false;
		}
		return true;
	}

	template < class _T >
	bool operator != (const _T & rhs) const
	{
		return !this->operator==(rhs);
	}

	template < class _T >
	bool operator > (const _T & rhs) const
	{
		size_t i1, i2, i3 , i;
		i1 = sizeof(a);
		i2 = sizeof(rhs);
		if( i1 < i2 ) i3 = i1; else i3 = i2;
		for( i = 0; i < i3; i++ )
		{
			if( a[i] > rhs.a[i] ) return true;
			else if( a[i] < rhs.a[i] ) return false;
		}
		if( i1 > i2 ) return true;
		return false;
	}

	template < class _T >
	bool operator >= (const _T & rhs) const
	{
		return (*this > rhs) || (*this == rhs);
	}

	template < class _T >
	bool operator < (const _T & rhs) const
	{
		size_t i1, i2, i3 , i;
		i1 = sizeof(a);
		i2 = sizeof(rhs);
		if( i1 < i2 ) i3 = i1; else i3 = i2;
		for( i = 0; i < i3; i++ )
		{
			if( a[i] < rhs.a[i] ) return true;
			else if( a[i] > rhs.a[i] ) return false;
		}
		if( i1 < i2 ) return true;
		return false;
	}

	template < class _T >
	bool operator <= (const _T & rhs) const
	{
		return (*this < rhs) || (*this == rhs);
	}

	uiarr_t()
	{
		SStrf::smemset(a);
	}

	~uiarr_t()
	{ 	}
};



template < int LEN_T >
class ui8arr_t :public uiarr_t< tuint8 , LEN_T >
{
public:
};


template < int LEN_T >
class ui16arr_t :public uiarr_t< tuint16 , LEN_T >
{
public:
};





X011_NAMESPACE_END




#define MOONLOGSTR  \
	( "**" +  std::string(__FILE__) + "|" + std::string(__FUNCTION__) + "|" + wl::SStrf::sltoa(__LINE__) )






#endif





#ifndef X011__H_w_SCalc_h
#define X011__H_w_SCalc_h


X011_NAMESPACE_BEGIN


class SCalc
{

public:

	
	virtual ~SCalc(){;}


	static tint32 max_divisor( tint32 a, tint32 b) 
	{
		tint32 temp;
		while(b!=0) 
		{
		temp=a%b; 
		a=b;      
		b=temp;   
		}
		return a;
	}

	
	static tbool quadratic_equation_root( tdouble a, tdouble b, tdouble c, tdouble *x1, tdouble *x2) 
	{
		if(b*b<4*a*c) return 0;
		*x1=(sqrt(b*b-4*a*c)-b)/(2*a);
		*x2=(-sqrt(b*b-4*a*c)-b)/(2*a);
		return 1;
	}


	static tuint32 chksum( const tchar *s, tsize len)
	{
		tuint32 j=0;
		if(SStrf::slen(s)==0) return 0;
		while(len--)
		{
			j += (tuint8)s[len]+(len+1);
			j &= 0x7FffFFff;
		}
		return j;
	}


	static tuint32 chksum2( const tchar *s, tsize len)
	{
		tuint32 j=0;
		
		while(len--)
		{
			j += (tuint8)(s[len])+(len+2);
			j &= 0x7FffFFff;
		}
		return j;
	}


	static std::string dseal( const std::string & strData , tsize out_len , const tchar *szMethod = ""  )
	{
		return dseal( strData.c_str(), SStrf::slen( strData.c_str() ) , out_len , szMethod );
	}


	static std::string dseal( const tchar *s, tsize len, tsize out_len, const tchar *szMethod = "" )
	{
		
		tuint32 i, j;
		tchar *t, *t0;
		std::string strOut("");
		if(!s||!out_len||!szMethod) return "";
		for(j=len+out_len,i=0;;i++)
		{
			j = ++j + chksum(s, len) + chksum(szMethod,SStrf::slen(szMethod));
			j = ++j * chksum(strOut.c_str(),(tsize)strOut.size()) * (len^10) * out_len ;
			j = 0x7FffFFff & (j ^ (~j * ~i + (len ^ out_len)) * (~j+~j*~i+~i));
			strOut += SStrf::sltoa(j);
			if( out_len+11 < strOut.size() ) break ;
		}
		t0 = t = (tchar*)SStrf::smalloc( (tsize)strOut.size()+1 );
		if(!t) return "";
		SStrf::scpy( t, strOut.c_str() );
		SStrf::srev(t);
		if(*t=='0') t++;
		t[out_len] = 0;
		strOut=t;
		SStrf::sfree(t0);
		return strOut;
	}


	static std::string dseal2( const tchar *s, tsize len, tsize out_len )
	{
		
		tuint32 i, j;
		tchar *t, *t0;
		std::string strOut("");
		if(!s||!len||!out_len) return "";
		for(j=len+out_len,i=0;;i++)
		{
			j = ++j + chksum2(s, len);	j = ++j * chksum2(strOut.c_str(),(tsize)strOut.size()) * (len^10) * out_len ;
			j = 0x7FffFFff & (j ^ (~j * ~i + (len ^ out_len)) * (~j+~j*~i+~i));			strOut += SStrf::sltoa(j);
			if( out_len+11 < strOut.size() ) break ;
		}
		t0 = t = (tchar*)SStrf::smalloc( (tsize)strOut.size()+1 );
		if(!t) return "";
		SStrf::scpy( t, strOut.c_str() );		SStrf::srev(t);
		if(*t=='0') t++;
		t[out_len] = 0;		strOut=t;		SStrf::sfree(t0);
		return strOut;
	}


	static std::string dseal3( const tchar *s, tsize len, tsize out_len = 33 )
	{
		std::string strOut("");
		const unsigned char *a = (const unsigned char *)s;
		tsize l;
		tuint32 l1 = 0;
		for( l = 0; l < len; l++ )  l1 += (l * a[l]) ^ a[l];
		for( l = 0; l < len; l++ )  l1 += (l | a[l]) * a[l] + a[l];
		strOut = dseal2( s, len, out_len + 22 );
		(*SClib::p_sprintf())( &(strOut[0]), "a%d", (int)l1 );
		return dseal2( strOut.c_str(), (tsize)strOut.size(), out_len );
	}


	static std::string dseal3( const std::string &s, tsize out_len = 33 )
	{
		return dseal3( s.c_str(), (tsize)s.size(), out_len );
	}


	static tchar * xor( tchar * Src, tsize len, tuint8 x )
	{
		tsize i;
		tuint8 *s=(tuint8 *)Src;
		if( !s || !len ) return (tchar*)s;
		for(i=0;i<len;i++) s[i] ^= x;
		return (tchar*)s;
	}


	static unsigned int CRC_16(const unsigned char *str,unsigned int usDataLen)
	{
		static const unsigned char  auchCRCHi[256] = {
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
		} ;

		static const unsigned char  auchCRCLo[256] = {
			0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,0x04,
			0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
			0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
			0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10,
			0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
			0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
			0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
			0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0,
			0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
			0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
			0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C,
			0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
			0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
			0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
			0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
			0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,0x40
		} ;

		unsigned char uchCRCHi = 0xFF ; 
		unsigned char uchCRCLo = 0xFF ; 
		unsigned int uIndex ; 
		while (usDataLen--)
		{
			uIndex = uchCRCHi ^ *str++ ; 
			uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
			uchCRCLo = auchCRCLo[uIndex] ;
		}
		return ( ((int)uchCRCHi) << 8 | uchCRCLo) ;
	}


	
	static tuint16 CRC_16_2(const unsigned char *str,unsigned int usDataLen)	
	{
		static const unsigned short vCrcList[256] =
		{
			0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
			0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
			0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
			0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
			0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
			0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
			0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
			0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
			0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
			0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
			0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
			0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
			0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
			0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
			0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
			0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
			0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
			0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
			0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
			0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
			0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
			0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
			0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
			0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
			0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
			0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
			0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
			0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
			0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
			0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
			0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
			0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
		};

		tuint32 i ,j ;
		tuint32 k;
		tuint16 crc ;
		crc = 0;
		j = usDataLen;
		for( i = 0 ; i < j; i++ )
		{
			k = (crc & 0xFF00) / 256;
			crc = (crc % 256) * 256;
			crc = crc ^ vCrcList[k ^ str[i] ];
		}

		return crc;
	}


	#if 1
	static tbool mk_chksumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += sz1[j];

		sz1[iLen-1] = c1;

		return 1;
	}
	#endif

	#if 1
	static tbool chk_chksumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += sz1[j];

		if( sz1[iLen-1] == c1 )
			return 1;
		else
			return 0;
	}
	#endif


	
	#if 1
	static unsigned char mk_chk2sumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += ( sz1[j] ^ (unsigned char)j );

		if( c1 == 0 || c1 == 255 ) c1 = 1;

		sz1[iLen-1] = c1;

		return 1;
	}
	#endif

	#if 1
	static unsigned char chk_chk2sumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += ( sz1[j] ^ (unsigned char)j );

		if( c1 == 0 || c1 == 255 ) c1 = 1;

		if( sz1[iLen-1] == c1 )
			return 1;
		else
			return 0;
	}
	#endif



}; 




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_sstrvs_h
#define X011__H_w_sstrvs_h


X011_NAMESPACE_BEGIN


class SStrvs
{
public:

	
	virtual ~SStrvs(){;}


	template < class StrT > 
	static tsize vsa_impbylen( const StrT & strsource, typename StrT::size_type ilen, std::vector<StrT> & vecrtn )
	{
		StrT s1(strsource);
		typedef typename StrT::size_type sizetypeB;

		while( !s1.empty() )
		{
			sizetypeB i = ilen <= s1.size() ? ilen : s1.size();
			StrT s2 = s1.substr( 0, i );
			vecrtn.push_back(s2);
			s1.erase( 0, i );	
		}
		return (tsize)vecrtn.size();
	}



	
	template < class StrT > 
	static tsize vsa_imp( const StrT & ssource, const StrT & ssep, tbool istoken, std::vector<StrT> & rtnlst )
	
	{
		std::vector<tint32> vAbuf, vBbuf;
		tint32  ltmpn,ltmpm,ltmpi,ltmpj,ltmpk, ltmpb1, ltmpb2;
		typedef typename StrT::size_type sizetypeB;
		sizetypeB ssti;

		ltmpm = ltmpi = ltmpj = 0;
		ltmpn = (tint32)ssource.size();
		ltmpk = (tint32)ssep.size();

		do 
		{
			if(ltmpk==0)
			{
				rtnlst.push_back(ssource);
				break;
			}

			do
			{
				if(ltmpm>=ltmpn) break;
				ssti = ssource.find( ssep, ltmpm ); 
				if(ssti==StrT::npos) break;
				ltmpi = (tint32)ssti;
				ltmpm = ltmpi;

				vAbuf.push_back(ltmpi);
				ltmpj ++;
				ltmpm += ltmpk;

			} while(1);

			ltmpb1 = 0 ; 
			ltmpb2 = ltmpj - 1 ; 

			ltmpj = 0;
			vBbuf.push_back(ltmpj);
			for(ltmpi=ltmpb1;ltmpi<=ltmpb2;ltmpi++){
				ltmpj = vAbuf[ltmpi];
				vBbuf.push_back(ltmpj);
				vBbuf.push_back(ltmpj+ltmpk);
			}
			vBbuf.push_back( ltmpn );

			ltmpj = (tint32)vBbuf.size();
			for(ltmpi=0;ltmpi<ltmpj;ltmpi+=2)
			{
				ltmpm = vBbuf[ltmpi];
				ltmpn = vBbuf[ltmpi+1];
				ltmpk = ltmpn - ltmpm;

				if(istoken&&ltmpk==0){
					;
				}else
					rtnlst.push_back( ssource.substr( ltmpm, ltmpk ) ); 

			}

		}while(0);

		return (tsize)rtnlst.size();
	}


	template < class StrT > 
	static std::vector<StrT>  vsa_imp( const StrT & ssource, const StrT & ssep, tbool istoken )
	{
		std::vector<StrT>  r;
		vsa_imp( ssource, ssep, istoken, r );
		return r;
	}


	template < class StrT > 
	static tsize vsa_hm( const StrT & ssource, const StrT & ssep, tbool istoken )
	{
		std::vector<StrT> a;
		return vsa_imp( ssource, ssep, istoken, a );
	}


	template < class StrT > 
	static StrT vsa_get( const StrT & ssource, const StrT & ssep, tbool istoken, tsize iwhich )
	
	{
		std::vector<StrT> tmplst;
		if( iwhich<vsa_imp( ssource, ssep, istoken, tmplst ) )
			return tmplst[iwhich];
		else
			return StrT();
	}

	template < class StrT >
	static StrT vsa_get( const StrT & ssource, const typename StrT::value_type *ssep, tbool istoken, tsize iwhich )
	{
			return vsa_get( ssource,  StrT(ssep),  istoken,  iwhich );
	}


	
	template < class StrT >
	static StrT vsa2v_get( const StrT & ssource,

						  const StrT & ssepTR,
						  tbool		istokenTR,
						  const StrT & ssepTD,
						  tbool		istokenTD,

						  tsize iwhichTR,  tsize iwhichTD		)

	{
		std::vector<StrT> tmplst1, tmplst2;
		if( iwhichTR<vsa_imp( ssource, ssepTR, istokenTR, tmplst1 ) )
		{
			if( iwhichTD<vsa_imp( tmplst1[iwhichTR], ssepTD, istokenTD, tmplst2 ) )
				return tmplst2[iwhichTD];
		}
		return StrT();
	}


	
	template < class StrT >
	static std::map<StrT,StrT> & vsa2v_prpt( const StrT & ssource,
											 const StrT & ssepTR,
											 const StrT & ssepTD,
											 std::map<StrT,StrT> & mapRtn	)
	{
		std::vector<StrT> vecTmpTR, vecTmpTD;
		typedef typename std::vector<StrT>::iterator iteratortypeB;
		iteratortypeB itTR;
		vsa_imp( ssource, ssepTR, 1, vecTmpTR );
		for( itTR = vecTmpTR.begin(); itTR!=vecTmpTR.end(); ++itTR)
		{
			vsa_imp( *itTR, ssepTD, 1, vecTmpTD );
			vecTmpTD.push_back( StrT() );
			vecTmpTD.push_back( StrT() );
			mapRtn.insert( std::pair<StrT,StrT>( vecTmpTD[0], vecTmpTD[1] ) );
			vecTmpTD.clear();
		}
		return mapRtn;
	}


};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_SSetu_h
#define X011__H_w_SSetu_h


X011_NAMESPACE_BEGIN


class SSetu
{

public:

	
	virtual ~SSetu(){;}


	template < class CntnrT, class ELET >
	static tsize vs_setch( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 == vset2.end() ) 
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	template < class CntnrT, class ELET >
	static tsize vs_setj( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 != vset2.end() ) 
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent, std::vector<int> & rtnsubsum )
	{
		CntnrT v2, v3; 
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB  it1,  itNewEnd2;
		int i;

		v2 = vsource;
		std::sort( v2.begin(), v2.end() );
		v3 = v2;

		itNewEnd2 = std::unique( v2.begin(), v2.end() );

		for( it1=v2.begin(); it1!=itNewEnd2; it1++)
		{
			rtncontent.push_back( *it1 );
			i = (int)std::count( v3.begin(), v3.end(), *it1 );
			rtnsubsum.push_back(i);
		}
		return (tsize)v2.size();
	}


	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent )
	{
		std::vector<int> v;
		return vs_setgroup( vsource, rtncontent, v );
	}


	template < class ELET >
	static tsize vs_setgroup( std::vector<ELET> & _a_content )  
	{
		std::vector<ELET> _a_aa1;
		tsize i = vs_setgroup( _a_content, _a_aa1 );
		_a_content = _a_aa1;
		return i;
	}




	template < class ELET >
	static ELET vs_groupbig( const std::vector<ELET> & memo, const std::vector<int> & subsum )
	{
		typedef typename std::vector<ELET>::const_iterator iteratortypeB;
		iteratortypeB it1;
		std::vector<int>::const_iterator it2, it3;
		int i;

		if( memo.size() != subsum.size() || memo.size() == 0 ) return ELET();

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2>i )
			{
				i = *it2;  
				it3 = it2; 
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	template < class ELET >
	static ELET vs_groupsmall( const std::vector<ELET> & memo, const std::vector<int> & subsum )
	{
		typename std::vector<ELET>::const_iterator it1;
		std::vector<int>::const_iterator it2, it3;
		int i;

		if( memo.size() != subsum.size() || memo.size() == 0 ) return ELET();

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2<i || i==0 )
			{
				i = *it2;  
				it3 = it2; 
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	template < class ELET >
	static void StableDelOld( std::vector<ELET> & v )
	{
		for( typename std::vector<ELET>::iterator it = v.begin(); it != v.end(); )
		{
			typename std::vector<ELET>::iterator it2;

			it2 = it + 1;

			if( std::find( it2, v.end(), *it ) != v.end() )
			{
				
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}


	template < class CNTNRT, class ELET >
	
	static void StableDel( CNTNRT & v , ELET val )
	{
		for( typename CNTNRT::iterator it = v.begin(); it != v.end(); )
		{
			if( *it == val )
			{
				
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}

};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_scake_h
#define X011__H_w_scake_h



X011_NAMESPACE_BEGIN


template < class CT >
class SCake_base
{
public:
	typedef  CT CkEle_t;

private:

	CT		*m_pbuf;
	tsize	m_mysize; 

	mutable std::vector<CT>  m_FastAppendBuf;

private:

	void init(void) { 	m_pbuf=NULL; 	m_mysize=0; }

	void freeall(void)
	{
		if(m_pbuf) delete [] m_pbuf;
		m_mysize=0;
		init();
	}

public:

	SCake_base() {  init(); }

	SCake_base( const SCake_base<CT> & cakesource )
	{
		init();
		let(cakesource);
	}

	SCake_base( CT c ) { init(); let(&c,1); }

	SCake_base( const CT *psource, tsize isize ) { init(); let(psource,isize); }

	SCake_base( const tchar *psource ) { init(); lets(psource); } 

	SCake_base( const std::string & s) { init(); lets(s); } 


	virtual ~SCake_base( )
	{
		freeall();
	}


	
	
	
	

	
	
	

	void copybuf( const CT *psource, CT *pdest, tsize isize, toffset iDestOffsetWhere = 0 )
	{
		if( psource == pdest && iDestOffsetWhere == 0 ) return;

		if( psource && pdest && isize )
		{
			for( tsize jtmp=iDestOffsetWhere; jtmp<isize+iDestOffsetWhere; jtmp++ )
				pdest[jtmp] = psource[jtmp-iDestOffsetWhere];
		}
	}


	void redim( tsize iNewSize, tbool reserve=0 )
	{
		if( iNewSize <= len() && iNewSize > len()/2 )
		{
			m_mysize = iNewSize;
		}
		else
		{
			CT *lbuf;
			if(iNewSize==0)
			{
				freeall();
				return;
			}
			lbuf = new CT[iNewSize] ;
			if(reserve) copybuf( m_pbuf, lbuf, iNewSize<m_mysize?iNewSize:m_mysize );
			freeall();
			m_pbuf = lbuf;
			m_mysize = iNewSize;
		}
	}

	const CT * buf_const() const
	{
		

		return m_pbuf;
	}


	CT * buf()
	{
		FastAppendEnd();

		return m_pbuf;
	}

	tsize len() const
	{
		return m_mysize;
	}

	void let( const CT *psource, tsize isize ) 
	{
		FastAppendEnd();

		if( (void*)psource==(void*)m_pbuf ) return;

		redim(isize);
		copybuf( psource, m_pbuf, isize );
	}


	void let( const SCake_base<CT> & cakesource )
	{
		let( cakesource.buf_const(), cakesource.len() );
	}


	void lets( const CT *psource, CT c00 )
	{
		tsize i;
		const CT *p2;
		for(i=1,p2=psource;*p2!=c00;p2++)
			i++; 
		let( psource, i );
	}


 	void lets( const tchar *psource ) 
	{
		if( (void*)psource==(void*)m_pbuf ) return;

		if(psource)
		{
			redim( SStrf::slen(psource) + 1 );
			tsize jtmp;
			for( jtmp=0; psource[jtmp]; jtmp++ )
			{
				m_pbuf[jtmp] = psource[jtmp];
			}
			m_pbuf[jtmp] = 0;
		}
	}


	void lets( const std::string & s) { lets(s.c_str()); }

	void lets( tint32 i)  { lets( SStrf::sltoa(i) ); }

	void lets( tdouble d) { lets( SStrf::sftoa(d) ); }

	SCake_base<CT> & dump( SCake_base<CT> & cake2 ) 
	{
		tsize iGoneSize;
		cake2.let( buf(), iGoneSize = ( len() < cake2.len() ? len() : cake2.len() ) ); 
		SCake_base<CT> * ptmpcake = new SCake_base<CT>(*this);
		let( ptmpcake->buf() + iGoneSize, len() - iGoneSize );
		delete ptmpcake;
		return cake2;
	}


	SCake_base<CT> & cut( tsize howmany ) 
	{
		if( howmany<=m_mysize) m_mysize -= howmany;
		else m_mysize = 0;
		return *this;
	}


	SCake_base<CT> & FastAppend( const SCake_base<CT> & cake2 ) 
	{
		if( !this->m_pbuf ) return this->append(cake2);

		if(cake2.len()==0)
		{
			return *this;
		}

		this->m_mysize += cake2.len();
		std::copy( cake2.buf_const(), cake2.buf_const() + cake2.len(), std::back_inserter(m_FastAppendBuf) );

		return *this;
	}

	void FastAppendEnd()
	{
		if( m_FastAppendBuf.empty() ) return;

		std::vector<CT>  FastBuf2(m_FastAppendBuf);

		m_FastAppendBuf.clear(); 
		this->m_mysize -= (tsize)FastBuf2.size();
		this->append( &(FastBuf2[0]), (tsize)FastBuf2.size() );
	}


	SCake_base<CT> & append( const SCake_base<CT> & cake2 ) 
	{
		if(cake2.len()==0)
		{
			
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = cake2.buf_const();
			len1 = len();
			len2 = cake2.len();
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	
	SCake_base<CT> & append( const CT *psource, tsize isize )
	{
		if( isize==0 || !psource )
		{
			
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = psource;
			len1 = len();
			len2 = isize;
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	
	SCake_base<CT> & append( CT val )
	{
		return append( &val, 1 );
	}

	
	std::string ds2( tsize out_len = 33 ) const
	{
		std::string s( out_len, '0' );
		if( this->len() == 0 ) return s;
		return SCalc::dseal2( (const char*)this->buf_const(), this->m_mysize, out_len );
	}

	
	std::string ds3( tsize out_len = 33 ) const
	{
		std::string s( out_len, '0' );
		if( this->len() == 0 ) return s;
		return SCalc::dseal3( (const char*)this->buf_const(), this->m_mysize, out_len );
	}


public:	

	

	SCake_base<CT> & operator = ( const SCake_base<CT> & cake2 )
	{
		let(cake2);
		return *this;
	}


	operator CT * ( )
	{
		return buf();
	}


	operator const CT * ( ) const
	{
		return buf_const();
	}

	int operator < ( const SCake_base<CT> & cake2 ) const
	{
		return ( (int)buf_const() < (int)cake2.buf_const() );
	}


}; 





class SCake : public SCake_base<tchar>
{

public:

	SCake():SCake_base<tchar>( ) { }

	SCake(const SCake & ckSrc):SCake_base<tchar>( ckSrc ) {  }


	SCake(const SCake_base<tchar> & ckSrc):SCake_base<tchar>( ckSrc ) {  }

	SCake( tchar c ):SCake_base<tchar>( c ) {  }
	
	

	SCake(const tchar * psrc, tsize isize):SCake_base<tchar>( psrc, isize ) {  }

	SCake(const tchar *psrc):SCake_base<tchar>( psrc ) {  }

	SCake(const std::string & s):SCake_base<tchar>( s) { }


	SCake & bs_en()
	{
		SCake *pck = new SCake;
		pck->redim( SStrf::bs_ensize( buf(), len() ) );
		SStrf::bs_en( buf(), len(), pck->buf() );
		*this = *pck;
		delete pck;
		return *this;
	}

	SCake & bs_en( std::string & strOut )
	{
		SCake *pck = new SCake;
		*pck = *this;
		pck->bs_en();
		strOut = pck->buf();
		delete pck;
		return *this;
	}

	std::string bs_en( std::string *pstrOut )
	{
		std::string strBuf;
		if( pstrOut == NULL ) pstrOut = &strBuf;
		bs_en( *pstrOut );
		return ( *pstrOut );
	}


	SCake & bs_de() 
	{
		if( buf() == NULL )
		{
			redim(0);
			return *this;
		}
		tsize iDatalen = SStrf::bs_desize( buf() );
		SStrf::bs_de( buf() );
		redim( iDatalen, 1 );
		return *this;
	}

	SCake & bs_de( const std::string & str ) 
	{
		if( str.empty() )
		{
			redim(0);
			return *this;
		}
		redim( (tsize)str.size() + 1 );
		(*SClib::p_strcpy())( buf(), str.c_str() );
		return bs_de();
	}


	tchar * mk_sz()
	{
		append( SCake("") );
		return buf();
	}

	std::string & mk_str( std::string & strOut ) const
	{
		if( this->len() )
		{
			return strOut = std::string( this->buf_const(), this->len() ).c_str(); 
		}
		return strOut = "";
	}

	
	std::string mk_str() const
	{
		std::string s1;
		return mk_str(s1);
	}


	std::string GetReadable_2v( int iLineLen , std::string strTd, std::string strTr ) const
	{
		std::string strOut;

		for( tsize i = 0; i < this->len(); i++ )
		{
			if( i != 0 && ( i % iLineLen ) == 0 )
				strOut += strTr;

			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];

			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;

			(*SClib::p_sprintf())( sz1, "%02X", (int)(*p2) );
			strOut += sz1;

			strOut += strTd;
		}

		return strOut;
	}


	std::string GetReadable() const
	{
		std::string strOut;

		for( tsize i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];

			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;
			(*SClib::p_sprintf())( sz1, "%02X", (int)(*p2) );
			strOut += sz1;
		}

		return strOut;
	}


	std::string GetReadableWithLen() const
	{
		std::string strOut = "L" + SStrf::sltoa( (int)this->len() ) + "-";

		for( tsize i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];

			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;
			(*SClib::p_sprintf())( sz1, "%02X", (int)(*p2) );
			strOut += sz1;
		}

		return strOut;
	}


	
	long ConvStr2Bin( std::string strData, void * pData ) const
	{
		std::vector<std::string> vec1;

		SStrvs::vsa_imp( strData, std::string(" "), 1, vec1 );

		for( std::vector<std::string>::size_type i = 0; pData && i < vec1.size(); i++ )
		{
			int ii;
			(SClib::p_sscanf())( vec1[i].c_str(), "%x", &ii );
			*((tuint8*)pData+i) = (tuint8)ii;
		}

		return (long)vec1.size();
	}

	
	long ConvStr2Bin( std::string strData ) 
	{
		redim( ConvStr2Bin( strData, NULL ) );
		return ConvStr2Bin( strData, buf() );
	}

	
	long ConvPackStr2Bin( std::string s1 ) 
	{
		std::vector<std::string> vec1;

		SStrvs::vsa_impbylen( s1, 2, vec1 );

		s1="";
		for( std::vector<std::string>::size_type i = 0; i < vec1.size(); i++ )
		{
			s1 += vec1[i] + " ";
		}

		return ConvStr2Bin( s1 );
	}


	std::string Seri() const  
	{
		return GetReadable();
	}

	
	long UnSeri( const std::string & s1 ) 
	{
		return ConvPackStr2Bin( s1 ); 
	}

	
	std::string Seri_S() const  
	{
		std::string strOut;
		for( tsize i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];
			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;
			(*SClib::p_sprintf())( sz1, "%02X ", (int)(*p2) );
			strOut += sz1;
		}
		return strOut;
	}

	
	long UnSeri_S( const std::string & s1 ) 
	{
		return ConvStr2Bin( s1 ); 
	}


	long UnSeri2( const std::string & s1 ) 
	{
		for( std::string::const_iterator it = s1.begin(); it != s1.end() ; ++it )
		{
			if( *it == ' ' ) return UnSeri_S( s1 );
		}
		return UnSeri( s1 );
	}

	
	long UnSeri3( const std::string & s1 ) 
	{
		std::string s2;
		for( std::string::size_type i = 0; i < s1.size(); i++ )
		{
			if( wl::SStrf::sishex( s1[i] ) ) s2 += *( s1.c_str() + i );
		}
		return UnSeri( s2 );
	}

	
	long UnSeri10D( const std::string &strData, void * pData ) const
	{
		std::vector<std::string> vec1;

		SStrvs::vsa_imp( strData, std::string(","), 1, vec1 );

		for( std::vector<std::string>::size_type i = 0; pData && i < vec1.size(); i++ )
		{
			int ii;
			(SClib::p_sscanf())( vec1[i].c_str(), "%d", &ii );
			*((tuint8*)pData+i) = (tuint8)ii;
		}

		return (long)vec1.size();
	}

	
	long UnSeri10D( const std::string &strData ) 
	{
		redim( UnSeri10D( strData, NULL ) );
		return UnSeri10D( strData, buf() );
	}

	
	std::string Seri10D() const  
	{
		tsize i;
		std::string strOut;
		for( i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];
			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;
			(*SClib::p_sprintf())( sz1, "%d,", (int)(*p2) );
			strOut += sz1;
		}
		if( !strOut.empty() ) strOut.erase( strOut.end() - 1 );
		return strOut;
	}

public:	

	SCake & operator = ( const SCake & cake2 )
	{
		let(cake2);
		return *this;
	}


}; 





template < class cakeT, class CT >
class SCakel_base2 {

private:

	std::vector<cakeT *> m_vknl;

	
	void collect( tbool szstyle = 1, cakeT  * pscbuff = NULL )
	{
		
		tsize wholesize,copypoint;
		typename std::vector<cakeT *>::iterator it;
		for( wholesize=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			wholesize += (*it)->len( );
			if(szstyle&&(*it)->len( )) wholesize--;
		}
		if(szstyle) wholesize++;

		cakeT  * psc = pscbuff;

		if( pscbuff == NULL ) psc = new cakeT ;
		psc->redim(wholesize);
		for( copypoint=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			psc->copybuf( (*it)->buf(), psc->buf(),	(*it)->len(), copypoint );
			copypoint += (*it)->len();
			if(szstyle) copypoint--;
		}
		clean();

		if( pscbuff == NULL ) m_vknl.push_back( psc );
	}


private:

	SCakel_base2( const SCakel_base2 & ckl )
	{
		;
	}

public:

	SCakel_base2() { ; }

	virtual ~SCakel_base2()
	{
		for( typename std::vector<cakeT *>::iterator it=m_vknl.begin();it!=m_vknl.end();++it)
			delete *it;
	} 


	tsize hm(void) const
	{
		return (tsize)m_vknl.size();
	}


	std::vector<cakeT *> & knl( ) {
		return m_vknl;
	}


	cakeT  * get( tsize iwhere ) const
	{
		return ( hm( )==0 || iwhere>=hm( ) )?NULL:m_vknl[iwhere];
		
		
	}


	cakeT  * get( ) const
	{
		return get( hm( )-1 );
	}


	cakeT  * get0( )
	{
		return get(0);
	}


	void add( const cakeT  & cakesource, tsize iwhere )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );
		if(iwhere>hm()) iwhere=hm();
		m_vknl.insert( m_vknl.begin()+iwhere, psc );
	}


	void add( const cakeT  & cakesource )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );	
		m_vknl.push_back( psc );
	}


	void add0( cakeT  & cakesource ) { add(cakesource,0); }


	void del( tsize iwhere )
	{
		typename std::vector<cakeT *>::iterator it;
		if( !( hm( )==0 || iwhere>=hm( ) ) )
		{
			it = m_vknl.begin( ) + iwhere;
			delete *it;
			m_vknl.erase( it );
		}
	}

	void del()  { del(hm()-1); }

	void del0() { del(0); }


	void clean()
	{
		tsize iremain = 0;
		while( hm() > iremain )
			del();
	}

	void clean( tsize iremain )
	{
		while( hm() > iremain )
			del();
	}


	void clean0( tsize iremain = 0 )
	{
		while( hm() > iremain )
			del0();
	}

	void collectb( cakeT  * pscbuff = NULL ) { collect(0,pscbuff); }

	void collects( cakeT  * pscbuff = NULL ) { collect(1,pscbuff); }


	void scatter( const cakeT  & ckSrc , CT cSepC )
	{
		tsize p1,p2;
		cakeT  ckTmp;
		for(p1=p2=0;p2<ckSrc.len();p2++)
		{
			if( *(ckSrc+p2)==cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				add( ckTmp );
				p1=p2+1;
			}
		}

		
		if(p2) 
		{
			p2--;
			if( *(ckSrc+p2)!=cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				ckTmp.append( cakeT ( &cSepC,1 ) );
				add( ckTmp );
			}
		}
	}


	void scatter( CT cSepC=0 )
	{
		do 
		{
			if(hm()>1)
				collectb();

			if(hm()==0)
				break;

			scatter( *get0() , cSepC );

			del0();

		}while(0);
	}


	SCakel_base2<cakeT,CT> & append( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}


public: 


	operator std::vector<cakeT *> & ( )
	{
		return knl( );
	}


	SCakel_base2<cakeT,CT> & operator = ( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		clean();
		return append(cakel2);
	}


};






template < class CT >
class SCakel_base : public SCakel_base2<  SCake_base<CT>, CT >
{
private:

	SCakel_base( const SCakel_base & ckl )
	{
		;
	}

public:

	SCakel_base() { ; }

	virtual ~SCakel_base() { ; }

public: 

	SCakel_base<CT> & operator = ( const SCakel_base<CT> & cakel2 )
	{
		SCakel_base2<  SCake_base<CT>, CT >::clean();
		return append(cakel2);
	}

};






class SCakel : public SCakel_base2< SCake, tchar >
{
private:

	SCakel( const SCakel & ckl )
	{
		;
	}

public:

	SCakel() { ;	}
	virtual ~SCakel() { ; }

public:

	SCakel & append( const SCakel & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}

	static tsize MkVecCake( const SCake &ckInput, tsize iLen, std::vector< SCake > & vckOut, tbool biLastFull = 1, tuint8 *pFill = NULL )
	{
		tsize i1, i2;
		i1 = 0;
		i2 = iLen;
		vckOut.clear();
		if( ckInput.len() == 0 || iLen == 0 ) return 0;
		for( ; ; i1 += iLen, i2 += iLen )
		{
			SCake ck;
			tbool biLastFlag = 0;

			if( i2 >= ckInput.len() )
			{
				i2 = ckInput.len();
				biLastFlag = 1;
			}

			ck.redim( iLen );
			SStrf::smemset( ck.buf(), pFill ? *pFill : 0, ck.len() );
			SStrf::smemcpy( ck.buf(), ckInput.buf_const() + i1, i2 - i1 );

			if( biLastFlag == 1 && biLastFull == 0 && i2 - i1 != ck.len() )
			{
				ck.redim( i2 - i1, 1 );
			}

			vckOut.push_back( ck );

			if( biLastFlag == 1 )
				return i2 - i1;
		}
	}


public: 

	SCakel & operator = ( const SCakel & cakel2 )
	{
		clean();
		return append(cakel2);
	}

};





#ifdef VC6_COMPATIBLE_X011_
	

#else

class S_dataeater_t
{
private:
	SCake	m_ckBufData;
	int     m_iBufOffset;

public:
	
	S_dataeater_t()
	{
		m_iBufOffset = 0;
	}

	
	S_dataeater_t( const S_dataeater_t & aa )
	{
		m_ckBufData = aa.m_ckBufData;
		m_iBufOffset = aa.m_iBufOffset;
	}

	S_dataeater_t(SCake ckData)
	{
		reset( ckData );
	}

	
	S_dataeater_t(void *p, int iLen )
	{
		reset( p, iLen );
	}

	
	virtual ~S_dataeater_t(){;}

public:

	
	void reset()
	{
	  m_iBufOffset  = 0;
	}

	
	void reset( void *p, int iLen )
	{
		SCake c( (char*)p, iLen);
		reset(c);
	}

	
	void reset( SCake ckData )
	{
		m_ckBufData = ckData;
		m_iBufOffset = 0;
	}

	
	tbool HaveMoreData()
	{
		if( m_ckBufData.len() == 0 ) return 0;
		return ( (tsize)m_iBufOffset >= m_ckBufData.len() ) ? 0 : 1 ;
	}

	
	template<class T>
	T eat_data( tbool biTurnEndian = 1 , tbool biMoveOn = 1 )
	{
		if( !HaveMoreData() )
		{
			
			
			return 0;
		}

		T i;

		
		SStrf::MkBlock2INTDataRef( m_ckBufData.buf() + m_iBufOffset, i , 0 ); 

		if(biMoveOn) m_iBufOffset += sizeof(T);
		if(biTurnEndian)
			if( sizeof(T) > 1 ) SStrf::chgendian( i );
		return i;
	}

	
	std::string eat_str( int iLen )
	{
		std::string s1 = "";
		for( int i = 0; iLen > 0 && i < iLen; i++ )
		{
			if( !HaveMoreData() ) break;
			s1 += this->eat_data<char>();
		}
		return s1.c_str();
	}

	
	tuint32 eat_big3( tbool biTurnEndian = 1 , tbool biMoveOn = 1 )
	{
		tuint32 ul1(0);
		tuint8 *p1 = (tuint8*)&ul1;
		p1[0] = 0;
		p1[1] = eat_data<tuint8>(biTurnEndian,biMoveOn);
		p1[2] = eat_data<tuint8>(biTurnEndian,biMoveOn);
		p1[3] = eat_data<tuint8>(biTurnEndian,biMoveOn);
		if(biTurnEndian)
			SStrf::chgendian( ul1 );
		return ul1;
	}

	
	template<class T>
	T & eat_bin( T & aa , tbool biMoveOn = 1 )
	{
		if( HaveMoreData() && m_ckBufData.len() >= m_iBufOffset + sizeof(T) )
		{
			SStrf::MkBlock2INTDataRef( m_ckBufData.buf() + m_iBufOffset, aa , 0 );
		}
		else
			SStrf::smemset(aa);

		if(biMoveOn) m_iBufOffset += sizeof(T);

		return aa;
	}

	
	void * eat_BinBlock( void *pDest, tsize i, tbool biMoveOn = 1 )
	{
		if( HaveMoreData() && m_ckBufData.len() >= m_iBufOffset + i )
		{
			SStrf::smemcpy( pDest, m_ckBufData.buf() + m_iBufOffset, i );
			return pDest;
		}
		return NULL;
	}


	template<class T>
	void eat_skip()
	{ m_iBufOffset += sizeof(T); }

	
	void eat_skip( int i )
	{ m_iBufOffset += i; }

};

#endif	





class SStrTbl
{
public:

	
	
	static void encodebase64( const char *p1, int ilen, std::string &rtn_str )
	{
		static char basis_64[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????";
		const unsigned char *in = (const unsigned char *)p1;
		unsigned char   oval;
		unsigned        olen;
		SCake ck;
		unsigned long inlen = ilen;

		olen = (inlen + 2) / 3 * 4;
		ck.redim(olen+1);

		unsigned char  *out = (unsigned char *)ck.buf();

	 
		while (inlen >= 3)
		{
	 
			*out++ = basis_64[in[0] >> 2];
			*out++ = basis_64[((in[0] << 4) & 0x30) | (in[1] >> 4)];
			*out++ = basis_64[((in[1] << 2) & 0x3c) | (in[2] >> 6)];
			*out++ = basis_64[in[2] & 0x3f];
			in += 3;
			inlen -= 3;
		}
		if (inlen > 0)
		{
	 
			*out++ = basis_64[in[0] >> 2];
			oval = (in[0] << 4) & 0x30;
			if (inlen > 1)
				oval |= in[1] >> 4;
			*out++ = basis_64[oval];
			*out++ = (inlen < 2) ? '=' : basis_64[(in[1] << 2) & 0x3c];
			*out++ = '=';
		}

		*out = '\0';

		rtn_str = ck.buf();
	}

	
	static std::string encodebase64( const SCake &ckin )
	{
		std::string s;
		encodebase64( ckin.buf_const(), (int)ckin.len(), s );
		return s;
	}

	
	static std::string encodebase64str( const std::string & str_in ) 
	{
		SCake ck;
		ck.lets(str_in);
		ck.cut( 1 );
		return encodebase64(ck);
	}


	static char CHAR64(int c)
	{
		static char  index_64[128] = {
			
			
			
			
			
			
(char)-1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char)
-1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char)
-1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) 62,(char) -1,(char) -1,(char) -1,(char) 63,(char)
52,(char) 53,(char) 54,(char) 55,(char) 56,(char) 57,(char) 58,(char) 59,(char) 60,(char) 61,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char)
-1,(char) 0,(char) 1,(char) 2,(char) 3,(char) 4,(char) 5,(char) 6,(char) 7,(char) 8,(char) 9,(char) 10,(char) 11,(char) 12,(char) 13,(char) 14,(char)
15,(char) 16,(char) 17,(char) 18,(char) 19,(char) 20,(char) 21,(char) 22,(char) 23,(char) 24,(char) 25,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char)
-1,(char) 26,(char) 27,(char) 28,(char) 29,(char) 30,(char) 31,(char) 32,(char) 33,(char) 34,(char) 35,(char) 36,(char) 37,(char) 38,(char) 39,(char) 40,(char)
41,(char) 42,(char) 43,(char) 44,(char) 45,(char) 46,(char) 47,(char) 48,(char) 49,(char) 50,(char) 51,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1

		};
		return (((c) < 0 || (c) > 127) ? -1 : index_64[(c)]);
	}


	static tbool decode64(const char *in, unsigned long inlen, char *out, unsigned long *outlen)
	{
		unsigned int   len = 0;
		unsigned int lup;
		int   c1,	 c2,	 c3,	 c4;

		
		if (in[0] == '+' && in[1] == ' ')
			in += 2;

		if (*in == '\0')
			return 0;

		for (lup = 0; lup < inlen / 4; lup++)
		{
			c1 = in[0];
			if (CHAR64(c1) == (char)-1)
				return 0;
			c2 = in[1];
			if (CHAR64(c2) == (char)-1)
				return 0;
			c3 = in[2];
			if (c3 != '=' && CHAR64(c3) == (char)-1)
				return 0;
			c4 = in[3];
			if (c4 != '=' && CHAR64(c4) == (char)-1)
				return 0;
			in += 4;
			*out++ = (CHAR64(c1) << 2) | (CHAR64(c2) >> 4);
			++len;
			if (c3 != '=')
			{
				*out++ = ((CHAR64(c2) << 4) & 0xf0) | (CHAR64(c3) >> 2);
				++len;
				if (c4 != '=')
				{
					*out++ = ((CHAR64(c3) << 6) & 0xc0) | CHAR64(c4);
					++len;
				}
			}
		}

		*out = 0;                   
		*outlen = len;

		return 1;
	}


	static bool decode64( const std::string & strin, SCake & rtn_ck )
	{
		unsigned long i;

		rtn_ck.redim( (int)strin.size() );
		if( decode64( strin.c_str(), (int)strin.size(), rtn_ck.buf(), &i ) )
		{
			rtn_ck.redim( i, 1 );
			return 1;
		}

		return 0;
	}


	static std::string decode64str( const std::string & str_in ) 
	{
		SCake ck;
		if( !decode64( str_in, ck ) ) return "";
		return std::string( ck.buf(), ck.buf() + ck.len() );
	}


	
	static void seri( const std::vector< std::string > & v_in, std::string & rtn_str )
	{
		std::vector< std::string >::const_iterator it;

		rtn_str = "";
		for( it = v_in.begin(); it != v_in.end(); ++it )
		{
			rtn_str += encodebase64str(*it);
			rtn_str += "}";
		}
	}

	
	static void unseri( const std::string & str_in , std::vector< std::string > & v_rtn )
	{
		v_rtn.clear();
		SStrvs::vsa_imp( str_in, std::string("}"), 0, v_rtn );

		std::vector< std::string >::iterator it;

		for( it = v_rtn.begin(); it != v_rtn.end(); ++it )
		{
			*it = decode64str( *it );
		}

		if( !v_rtn.empty() ) v_rtn.pop_back();
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_sdte_h
#define X011__H_w_sdte_h



X011_NAMESPACE_BEGIN


class SDte_bare
{
public:
	int m_year;
	int m_mon;
	int m_day;
	int m_hour;
	int m_min;
	int m_sec;
	
};


class SDte : public SDte_bare
{


public:

private:

	static tbool d_is_leap_year(int y)
	{
		

		


		return ( y % 400 == 0 ) ||
				( ( y % 4 == 0 ) && ( y % 100 != 0 ) );
	}


	static int d_day_of_year(int y)
	{
		return d_is_leap_year(y)?366:365;
	}


	static int d_day_of_month(int y, int m)
	{
		tint8 Array[]={0, 31, 28, 31,30,31,30,31,31,30,31,30,31};
		if(m<1||m>12) m=1;
		return (int)(m==2 ? Array[m] + (d_is_leap_year(y)?1:0) : Array[m]);
	}


	static tchar * d_odget( SCakel_base<tchar> & abuf, tint32 od )
	{
		abuf.add( SCake_base<tchar>("000000000") );
		if(od<0) od *= -1;
		abuf.add( SCake_base<tchar>( SStrf::sltoa(od) ) );
		abuf.collects( );
		return abuf.get( )->buf( );
	}


	static time_t dt_mk(void)
	{
		struct tm tmm, *tp;
		time_t timer;
		time(&timer);
		tp = (*SClib::p_localtime())(&timer);
		memcpy(&tmm, tp, sizeof(struct tm));
		return mktime(&tmm);
	}


	static int dt_mk( struct tm *ptm , time_t tmr)
	{
		struct tm *tp;
		tp = (*SClib::p_localtime())(&tmr);
		if(ptm!=NULL&&tp!=NULL) memcpy(ptm, tp, sizeof(struct tm));
		return tp!=NULL;
	}


	static void dt_mknow( int& y, int&m, int& d, int& hh, int& mi, int& ss ) 
	{
		struct tm tmm;
		struct tm *tp;
		memset(tp=&tmm, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		y = tp->tm_year+1900;
		m = tp->tm_mon+1;
		d = tp->tm_mday;
		hh = tp->tm_hour;
		mi = tp->tm_min;
		ss = tp->tm_sec;
	}

	

	static struct tm & RegulateTmYear4( struct tm & t )
	{
		if( t.tm_year <= 999 )
		{
			t.tm_year += 1900;
		}
		return t;
	}

	static struct tm & RegulateTmYear2( struct tm & t )
	{
		if( t.tm_year > 1900 )
		{
			t.tm_year -= 1900;
		}
		return t;
	}


	static struct tm & Now( struct tm & t )
	{
		struct tm *tp;
		memset(tp=&t, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		tp->tm_year+=1900;
		return t;
	}


	
	static time_t tm2l( struct tm t )
	{
		RegulateTmYear2(t);

		return mktime(&t);	
	}


	static struct tm l2tm( time_t tmr )
	{
		struct tm *tp;
		struct tm tm2;

		SStrf::smemset(tm2);

		
		tp = (*SClib::p_localtime())(&tmr);

		if(tp!=NULL) memcpy(&tm2, tp, sizeof(struct tm));

		return tm2;
	}


	static tint32 idmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int y, m, d;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d", &y, &m, &d );
		return idmk(y,m,d);
	}


	static tint32 idmk(int y, int m, int d, tint32 offset=0)
	{
		tint32 i,j;
		for(j=0,i=0;i<=(y-1);i++) j += d_day_of_year(i);
		for(i=1;i<=(m-1);i++) j += d_day_of_month(y,i);
		return j = j + d + offset;
	}


	static int odgety( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,3);
		*t=0;
		return (int)SStrf::satol(t-4);
	}


	static int odgetm( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,1);
		*t=0;
		return (int)SStrf::satol(t-2);
	}


	static int odgetd( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,0);
		return (int)SStrf::satol(t-1);
	}


	static tint32 id2o( tint32 id )
	{
		tint32 i1, i2, i3, i4;
		if(id<=0) 	 id=1;
		for(i1=0;id>d_day_of_year(i1);) {
			id -= d_day_of_year(i1);
			i1++;
		}
		for(i2=1;id>d_day_of_month(i1,i2);) {
			id -= d_day_of_month(i1,i2);
			i2++;
		}
		i3 = id;
		return i4 = 10000*i1 + 100*i2 + i3;
	}


	static tint32 od2i( tint32 od )
	{
		return idmk( odgety(od), odgetm(od), odgetd(od) );
	}


	static int idgety( tint32 id ) { return odgety( id2o(id) ); }

	static int idgetm( tint32 id ) { return odgetm( id2o(id) ); }

	static int idgetd( tint32 id ) { return odgetd( id2o(id) ); }

	static tint32 idnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return idmk(y,m,d); }

	static tint32 odnow( ) { return id2o(idnow()); }



	static tint32 itmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int h, m, s, i;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d %d:%d:%d", &i, &i, &i, &h, &m, &s );
		return itmk(h, m, s);
	}


	static tint32 itmk(int h, int m, int s)
	{
		return h*60*60+m*60+s;
	}

	static tint32 itgeth(tint32 it)		{	return it/3600; 	}

	static tint32 itgetm(tint32 it)		{	return it%3600/60; 	}

	static tint32 itgets(tint32 it)		{	return it%60;	}


	static tint32 it2o(tint32 it)
	{
		tchar s[7];
		(*SClib::p_sprintf())( s, "%02d%02d%02d", itgeth(it), itgetm(it), itgets(it) );
		return SStrf::satol(s);
	}


	static tint32 ot2i(tint32 ot)
	{
		SCake_base<tchar> ca("000000", 6);
		ca.append( SCake_base<tchar>(SStrf::sltoa(ot)) );
		int h,m,s;
		(*SClib::p_sscanf())( SStrf::splast(ca.buf(), 5), "%2d%2d%2d", &h,&m,&s);
		return itmk(h,m,s);
	}


	static tint32 itnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return itmk(hh,mi,ss); }

	static tint32 otnow( ) { return it2o(itnow()); }

	static tdouble iemk( tint32 id, tint32 it) { return  id + (tdouble)it/(tdouble)86400; }


	static tdouble ie2o( tint32 id, tint32 it)
	{
		tint8 s[16];
		(*SClib::p_sprintf())(s, "%ld.%06ld", id2o(id), it2o(it) );
		return SStrf::satof(s);
	}

	static tdouble ie2o(tdouble ie)
	{
		tdouble d1, d2;
		d1 = floor(ie);
		d2 = 0.5 + ( (ie - floor(ie)) * 86400 ) ;
		return ie2o((tint32)d1, (tint32)d2);
	}


	static tdouble oe2i(double oe)
	{
		tdouble od, ot;
		od = floor(oe);
		ot = 0.5 + ( (oe - floor(oe)) * 1e6 ) ;
		return iemk( od2i((tint32)od), ot2i((tint32)ot) );
	}


	static tdouble ienow()
	{
		return iemk( idnow(), itnow() );
	}


	static tdouble oenow()
	{
		return ie2o( ienow() );
	}


	static std::string Db_oe( tint32 idNow=0, tint32 itNow=-1 ) 
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 idgety(idNow), idgetm(idNow), idgetd(idNow),
					 itgeth(itNow), itgetm(itNow), itgets(itNow)	);
		return sBuf;
	}


	static std::string Pack_oe( tint32 idNow=0, tint32 itNow=-1 ) 
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		return  SStrf::sftoa( ie2o( iemk( idNow, itNow ) ) );
	}


public:

	SDte()
	{
		m_year= 0;
		m_mon= 0;
		m_day= 0;
		m_hour= 0;
		m_min= 0;
		m_sec= 0;
		
	}

	SDte( std::string str_dte )
	{
		if(str_dte=="") this->MakeNow();
		else
			Make( str_dte );
	}

	SDte( int iHour, int iMin, int iSec )
	{
		this->MakeNow();
		this->m_hour= iHour;
		this->m_min= iMin;
		this->m_sec= iSec;
	}

	virtual ~SDte() { ; }


	static double e_proctime()  
	{
		return (double)clock()/(double)CLOCKS_PER_SEC;
	}

	static int Get_msec() 
	{
		
		
		SYSTEMTIME sys;
		GetLocalTime( &sys );
		return (int)sys.wMilliseconds;
	}

	static std::string Get_now_mtime( int wei = 2 ) 
	{
		int i = Get_msec();
		char ss[33];
		sprintf( ss, "%s.%03d", (SDte::GetNow().ReadStringPack().c_str() + 9),i );
		if( wei == 2 ) ss[9] = 0;
		return ss;
	}


	SDte & Make( std::string str_dte )
	{
		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) != std::string::npos ) 
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d %d:%d:%d", &m_year, &m_mon, &m_day, &m_hour, &m_min, &m_sec );
			return *this;
		}

		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) == std::string::npos ) 
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d", &m_year, &m_mon, &m_day );
			m_hour = 	m_min = m_sec = 0;
			return *this;
		}

		if( str_dte.find( "-" ) == std::string::npos && str_dte.find( ":" ) != std::string::npos ) 
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d:%d:%d", &m_hour, &m_min, &m_sec );
			m_year = m_mon = m_day = 0;
			return *this;
		}

		tint32 oiid, oiit;

		if( str_dte.find( " " ) != std::string::npos ) 
		{
			oiid = (tint32)SStrf::satol( SStrvs::vsa_get( str_dte, std::string(" "), 1, 0 ) );
			oiit = (tint32)SStrf::satol( SStrvs::vsa_get( str_dte, std::string(" "), 1, 1 ) );
		}
		else
		{
			oiid = (tint32)SStrf::satol( str_dte );
			oiit = 0;
		}

		oiid = this->od2i( oiid );
		oiit = this->ot2i( oiit );

		m_year = idgety( oiid );
		m_mon  = idgetm( oiid );
		m_day  = idgetd( oiid );

		m_hour = itgeth( oiit );
		m_min = itgetm(  oiit );
		m_sec = itgets(  oiit );



		tint32 i;

		i = itmk( m_hour, m_min, m_sec );
		m_day += i / 86400;
		i %= 86400;
		m_hour = itgeth( i );
		m_min = itgetm( i );
		m_sec = itgets( i );

		i = idmk( m_year, m_mon, m_day );
		m_year = idgety( i );
		m_mon  = idgetm( i );
		m_day  = idgetd( i );


		return *this;
	}


	static tbool IsValidDate( std::string strVal ) 
	{
		if( strVal.length() != 8 ) return 0;
		std::string s1,s2;
		SDte d1;
		s1 = strVal + " 001122";
		d1.Make( s1 );
		s2 = d1.ReadStringPack();
		SStrf::sreplstr( s1, " ", "." );
		if( s1 != s2 ) return 0;
		return 1;
	}


	static tbool IsValidTime( std::string strVal ) 
	{
		if( strVal.length() != 6 ) return 0;

		std::string s1 ;

		s1 = strVal.substr( 0, 2 );
		int i1 = SStrf::satol( s1 );
		if( i1 >= 24 ) return 0;

		s1 = strVal.substr( 2, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		s1 = strVal.substr( 4, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		return 1;
	}



	static tbool IsValidDateTime( std::string strVal ) 
	{
		if( strVal.length() != 14 ) return 0;

		std::string s1,s2;
		SDte d1;
		s2 = strVal;
		s2.insert( 8, " " );
		d1.Make( s2 );
		s1 = d1.ReadStringPack();
		SStrf::sreplstr( s2, " ", "." );
		if( s1 != s2 ) return 0;
		return 1;
	}




	SDte & MakeNow()
	{
		struct tm  tnow;
		this->Now(tnow);
		m_year= tnow.tm_year;
		m_mon = tnow.tm_mon+1;
		m_day = tnow.tm_mday;
		m_hour= tnow.tm_hour;
		m_min = tnow.tm_min;
		m_sec = tnow.tm_sec;
		return *this;
	}


	static SDte GetNow()  
	{
		SDte s;
		return s.MakeNow();
	}


	tint32 DiffDay( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = this->idmk( m_year, m_mon, m_day ) ;
		d2 = dte2.idmk( dte2.m_year, dte2.m_mon, dte2.m_day ) ;

		return d1 - d2;
	}


	tdouble DiffSec( const SDte & dte2 ) const
	{
		tdouble d1, d2;

		d1 = (double)this->itmk( m_hour, m_min, m_sec );
		d2 = (double)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400.0;
	}


	tint32 DiffSecInt( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = (tint32)this->itmk( m_hour, m_min, m_sec );
		d2 = (tint32)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400;
		
	}


	static tint32 DiffSecToday()
	{
		SDte a;
		return a.itnow();
	}

	
	static tint32 DiffSecOf1day(SDte dt) 
	{
		SDte a=dt;
		SDte b=a;
		b.m_hour=b.m_min=b.m_sec=0;
		return a.DiffSecInt(b);
	}

	
	static tint32 DiffSecOf1day( std::string strTime ) 
	{
		SDte a;
		if( strTime.find( ":" ) != std::string::npos ) 
		{
			(*SClib::p_sscanf())( strTime.c_str(), "%d:%d:%d", &a.m_hour, &a.m_min, &a.m_sec );
			a.m_year = a.m_mon = a.m_day = 0;
			return a.m_hour * 60 * 60 + a.m_min * 60 + a.m_sec;
		}
		return 0;
	}


	int WeekDay() const
	{
		int i2 = this->DiffDay( wl::SDte() );
		return (i2 - 2 ) % 7;
	}


	SDte & Relative_internal( const SDte & dte2 )
	{
		m_year += dte2.m_year;
		m_mon  += dte2.m_mon;
		m_day  += dte2.m_day;
		m_hour += dte2.m_hour;
		m_min  += dte2.m_min;
		m_sec  += dte2.m_sec;

		tint32 i;

		i = itmk( m_hour, m_min, m_sec );
		m_day += i / (int)86400;
		i %= (int)86400;
		m_hour = itgeth( i );
		m_min = itgetm( i );
		m_sec = itgets( i );

		i = idmk( m_year, m_mon, m_day );
		m_year = idgety( i );
		m_mon  = idgetm( i );
		m_day  = idgetd( i );

		return *this;
	}

	SDte & Relative( const SDte & dte2 )
	{
		Relative_internal(dte2);

		if( this->m_hour < 0 || this->m_min < 0 || this->m_sec < 0 )
		{
			SDte dte2;
			dte2.m_year = dte2.m_mon = dte2.m_day = dte2.m_hour = dte2.m_min = 0;
			dte2.m_sec = (int)-86400;
			this->Relative_internal( dte2 );
			dte2.m_sec = (int)86400;
			this->Relative_internal( dte2 );
		}

		return *this;
	}


	SDte & RelativeDay( toffset day2 )
	{
		SDte dte2;
		dte2.m_year = dte2.m_mon = dte2.m_day = dte2.m_hour = dte2.m_min = 0;
		dte2.m_day = (int)day2;
		return Relative(dte2);
	}


	SDte & RelativeSec( toffset sec2 )
	{
		SDte dte2;
		dte2.m_year = dte2.m_mon = dte2.m_day = dte2.m_hour = dte2.m_min = 0;
		dte2.m_sec = (int)sec2;
		return Relative(dte2);
	}

	
	SDte & RelativeSecFF( tuint32 sec2 ) 
	{
		this->RelativeSec( sec2 / 3 );
		this->RelativeSec( sec2 / 3 );
		this->RelativeSec( sec2 / 3 );
		return this->RelativeSec( sec2 -  sec2 / 3 * 3 );
	}


	std::string ReadString() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 m_year, m_mon, m_day,
					 m_hour, m_min, m_sec	);
		return sBuf;
	}


	std::string ReadStringTw( tbool IsShortFmt = 1 ) const 
	{
		tchar sBuf[33];
		if( IsShortFmt )
		{
			(*SClib::p_sprintf())(sBuf,"%d/%02d/%02d %02d:%02d",
						 m_year, m_mon, m_day,
						 m_hour, m_min	);
		}
		else
		{
			(*SClib::p_sprintf())(sBuf,"%d/%02d/%02d %02d:%02d:%02d",
						 m_year, m_mon, m_day,
						 m_hour, m_min	, m_sec	);
		}
		return sBuf;
	}


	std::string ReadStrDate() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d",
					 m_year, m_mon, m_day );
		return sBuf;
	}

	
	std::string ReadStrTime() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d:%02d:%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	
	std::string ReadStringPack( char c = '.' ) const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d%c%02d%02d%02d",
					 m_year, m_mon, m_day,  c ,
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	
	std::string ReadStringPack14() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d%02d%02d%02d",
					 m_year, m_mon, m_day ,
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	
	std::string ReadStrPackDate() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d",
					 m_year, m_mon, m_day 	);
		return sBuf;
	}

	
	std::string ReadStrPackTime() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d%02d%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	
	std::string Read_dt1() const 
	{
		tchar sBuf[33];
		const tchar *s2[] = {"aa","Jan", "Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		(*SClib::p_sprintf())(sBuf,"%d-%s-%d",
								m_day, s2[m_mon], m_year );
		return sBuf;
	}

	
	void GetBcdArr( SCake & ck ) const 
	{
		std::string s1 = ReadStringPack14();
		std::vector<std::string> vec1;

		SStrvs::vsa_impbylen( s1, 2, vec1 );

		s1="";
		for( std::vector<std::string>::size_type i = 0; i < vec1.size(); i++ )
		{
			s1 += vec1[i] + " ";
		}
		ck.ConvStr2Bin(s1);
	}

	
	void GetBcdArr( std::vector<tuint8> & v ) const 
	{
		SCake ck;
		GetBcdArr(ck);
		v.resize(7);
		std::copy( (tuint8*)(ck.buf()), (tuint8*)(ck.buf() + ck.len()), v.begin() );
	}

	
	operator std::string () const
	{
		return ReadStringPack() ;
	}

	
	bool operator != (const SDte & rhs) const { return this->ReadStringPack() != rhs.ReadStringPack(); }
	bool operator == (const SDte & rhs) const { return this->ReadStringPack() == rhs.ReadStringPack(); }
	bool operator >= (const SDte & rhs) const { return this->ReadStringPack() >= rhs.ReadStringPack(); }
	bool operator <= (const SDte & rhs) const { return this->ReadStringPack() <= rhs.ReadStringPack(); }
	bool operator > (const SDte & rhs) const  { return this->ReadStringPack() >  rhs.ReadStringPack(); }
	bool operator < (const SDte & rhs) const  { return this->ReadStringPack() <  rhs.ReadStringPack(); }

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_sfile_h
#define X011__H_w_sfile_h



X011_NAMESPACE_BEGIN


class SFile
{

private:

	std::string m_strFilename;

public:

	SFile()
	{
		bind("");
	}


	SFile( std::string fn )
	{
		bind(fn);
	}


	virtual ~SFile()
	{ ;
	}


	static std::string GetPathSep()
	{
		return "\\";
	}


	static std::string MkDir2Path( std::string strPathOrDir )
	{
		if( strPathOrDir.length() )
		{
			const tchar * t;
			t = SStrf::splast( strPathOrDir.c_str() );
			if( *t == GetPathSep()[0] )
			{
				return strPathOrDir;
			}
		}

		return strPathOrDir + GetPathSep();
	}



	static void Dir2Path( std::string & strPathOrDir )
	{
		strPathOrDir = MkDir2Path(strPathOrDir);
	}

	
	static std::string GetOnlyname( std::string strPfn )
	{
		std::string strChar=GetPathSep();
		std::string::size_type nPos;
		nPos = strPfn.find_last_of( strChar[0] );
		if( nPos != std::string::npos )
		{
			return &(strPfn[nPos+1] );
		}
		return strPfn.c_str();
	}
	
	std::string GetOnlyname() const
	{
		return GetOnlyname(filename());
	}

	
	static std::string GetPath( std::string strPfn )
	{
		std::string strChar=GetPathSep();
		std::string::size_type nPos;
		nPos = strPfn.find_last_of( strChar[0] );
		if( nPos != std::string::npos )
		{
			strPfn[nPos+1] = 0;
		}
		return strPfn.c_str();
	}
	
	std::string GetPath() const
	{
		return GetPath(filename());
	}

	
	static std::string GetDir( std::string strPfn )
	{
		std::string strChar=GetPathSep();
		std::string::size_type nPos;
		nPos = strPfn.find_last_of( strChar[0] );
		if( nPos != std::string::npos )
		{
			strPfn[nPos+0] = 0;
		}
		return strPfn.c_str();
	}
	
	std::string GetDir() const
	{
		return GetDir(filename());
	}


	void bind( std::string fn )
	{
		m_strFilename = fn;
	}


	tbool bind_nofile( std::string strPath, const tchar * pszExt = NULL , int iThreadId = 0 ) 
	{
		static int iName1 = 0;
		tdouble dName2;
		int k=0;
		std::string strNameExt(pszExt?pszExt:".tmp");
		std::string strGoodPathfilename;

		
		strPath = MkDir2Path( strPath );

		if( pszExt && *pszExt!='.' ) strNameExt = std::string(".") + pszExt;

		do
		{
			iName1--;
			dName2 = SStrf::rand1();
			strGoodPathfilename = strPath + "h" + SStrf::sltoa(iName1) + "_" + SStrf::sltoa(iThreadId) + SStrf::sftoa(dName2) + strNameExt;
			bind(strGoodPathfilename);
			if(canoutput()) return 1;
			if( k ++ > 9 )
			{
				if(!erase())
				{
					bind("");
					return 0;
				}
			}
		}while(1);
	}


	std::string filename() const
	{
		return m_strFilename;
	}


	
	


	operator std::string () const
	{
		return m_strFilename;
	}

	
	operator const tchar * () const
	{
		return m_strFilename.c_str();
	}


	static tbool erase(std::string strfilename)
	{
		return 0==remove( strfilename.c_str() )?1:0;
	}

	
	tbool erase()
	{
		return 0==remove( m_strFilename.c_str() )?1:0;
	}


	tbool exists()
	{
		FILE *fp;
		tbool rc;
		if( m_strFilename=="" )
		{
			return 0;
		}
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if(fp==NULL) rc=0;
		if(fp!=NULL)
		{
			rc=1; fclose(fp);
		}
		return rc;
	}

	
	static tbool exists(std::string strfilename)
	{
		SFile fInFile;
		fInFile.bind( strfilename );
		return fInFile.exists();
	}


	tbool caninput()
	{
		return exists();
	}


	tbool canoutputabs()
	{
		FILE *fp;
		fp = (*SClib::p_fopen())(m_strFilename.c_str(),"wb");
		if(fp==NULL) return 0;
		fclose(fp);
		return erase();
	}


	tbool canoutput()
	{	
		if(exists()) return 0;
		return canoutputabs();
	}


	
	tsize len()
	{
		if( !exists() ) return 0;
		tsize flen;
		FILE *fp;
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fclose(fp);
		return flen;
	}

	
	static tsize len( std::string strfilename )
	{
		SFile fInFile;
		fInFile.bind( strfilename );
		return fInFile.len();
	}


	
	tbool read( SCake & ckbuf, long iBeginOff, tsize iLenBytes )
	{
		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if( fp == NULL )
		{
			return 0;
		}

		fseek( fp, iBeginOff, SEEK_SET );

		ckbuf.redim( iLenBytes );
		SStrf::smemset( ckbuf.buf(), 0, iLenBytes );

		tsize a = (tsize)fread( ckbuf.buf(), 1, iLenBytes, fp );

		if( a == iLenBytes )
		{}
		else
		if( a == 0 )
		{
			ckbuf.redim(0);
		}
		else
		{
			ckbuf.cut( iLenBytes - a );
		}

		fclose(fp);

		return ckbuf.len() ? 1 : 0;
	}


	
	tbool read( SCake_base<tchar> & buf, tsize a_extra_bytes = 0 ) 
	{
		if(!this->exists()) return 0;

		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if( fp == NULL )
		{
			return 0;
		}

		tsize flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );


		
		
		

		buf.redim( flen + a_extra_bytes );

		if(a_extra_bytes)
		{
			SStrf::smemset( buf.buf(), 0, flen + a_extra_bytes ); 
			
		}

		if(flen) fread( buf.buf(), flen, 1, fp );

		fclose(fp);

		return 1;
	}


	tbool read( std::vector<char> & buf )
	{
		buf.clear();

		if(!this->exists()) return 0;

		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );

		if( fp == NULL )
		{
			return 0;
		}

		tsize flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );

		buf.resize( flen, 0 );

		if(flen)
			fread( &(buf[0]), flen, 1, fp );

		fclose(fp);

		return 1;
	}


	tbool read_str( SCake_base<tchar> & buf ) 
	{
		return this->read( buf, 1 );
	}


	tbool read_str( std::string & strRtnBuf )
	{
		
		
		
		
		
		

		
		strRtnBuf = "";

		if( !this->exists() ) return 0;
		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if( fp == NULL )
		{
			return 0;
		}

		tsize flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );

		if( flen == 0)
		{
			fclose(fp);
			return 0 ;
		}

		strRtnBuf.resize( flen , 0 );

		if(flen) fread( &(strRtnBuf[0]), flen, 1, fp );

		fclose(fp);

		return 1;
	}


	tbool read_bs( std::string & strRtnBs )
	{
		SCake ck;

		if( !this->read( ck ) ) return 0;
		strRtnBs = ck.len() ? ck.bs_en().buf() : "";

		return 1;
	}


	tbool read_vecstr( std::vector<std::string> & vecLines, std::string strSep, tbool istoken = 1 )
	{
		wl::SCake ckData;
		if( !read_str( ckData ) ) return 0;
		if( !ckData.len() ) return 0;
		SStrvs::vsa_imp( std::string(ckData.buf()), strSep, istoken, vecLines );
		return 1;
	}


	
	std::string read_dseal( int outlen )
	{
		SCake ck;
		read(ck);
		if( ck.len() == 0 ) return "";
		return SCalc::dseal( ck.buf(), ck.len(), outlen );
	}

	
	std::string read_dseal2( int outlen )
	{
		SCake ck;
		read(ck);
		if( ck.len() == 0 ) return "";
		return SCalc::dseal2( ck.buf(), ck.len(), outlen );
	}

	
	std::string read_dseal3( int outlen )
	{
		SCake ck;
		read(ck);
		if( ck.len() == 0 ) return "";
		return SCalc::dseal3( ck.buf(), ck.len(), outlen );
	}


	tbool write( const void * pbuf, tsize len, tbool bIsAppend = 0 ) 
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( len == 0 ) break;
			if( !pbuf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( pbuf, len, 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}


	tbool write( const SCake_base<tchar> & buf, tbool bIsAppend = 0 ) 
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( buf.len()==0 ) break;
			if( !buf.buf_const() ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( buf.buf_const(), buf.len(), 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}


	tbool write() 
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), "wb" );
			if(fp==NULL) break;
			fclose(fp);
			rc = 1;
		}while(0);

		return rc?1:0 ;
	}


	tbool write_bs( const std::string & strBs )
	{
		SCake ck;

		ck.lets( strBs );
		ck.bs_de();

		return write(ck);
	}


	tbool write_str( const tchar * buf, tbool bIsAppend = 0 )
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( NULL == buf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str(), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			if( fwrite( buf, SStrf::slen(buf), 1, fp ) )
			{
				rc = 1;
			}
			else
			{
				rc = 0;
			}
			fclose(fp);

		}while(0);

		return rc?1:0 ;
	}


	tbool write_str( const std::string & buf, tbool bIsAppend = 0 )
	{
		return write_str( buf.c_str(), bIsAppend );
	}


	tbool write_vecstr( const std::vector<std::string> & vecLines, std::string strSep, tbool bIsAppend = 0 )
	{
		std::string strOut;

		for( std::vector<std::string>::const_iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			if( it == (vecLines.end() - 1) && it->empty() )
			{
			}
			else
				strOut += *it + strSep;
		}

		return write_str(strOut, bIsAppend);
	}


	
	tbool cp( std::string strFnSource, std::string strFnDest )
	{
		SCake buf;
		this->bind(strFnSource);
		this->read( buf );
		this->bind(strFnDest);
		return write(buf);
	}


	void cp( std::string strFnSource, std::string strFnDest1, std::string strFnDest2 )
	{
		SCake buf;
		this->bind(strFnSource);
		this->read( buf );
		this->bind(strFnDest1);
		write(buf);
		this->bind(strFnDest2);
		write(buf);
	}


	
	static tbool cp2( std::string strFnSource, std::string strFnDest ) 
	{
		FILE *fp1;
		FILE *fp2;
		SCake ckbuf;
		int iLenBytes = 128;

		fp1 = (*SClib::p_fopen())( strFnSource.c_str(), "rb" );
		if( fp1 == NULL )
			return 0;

		fp2 = (*SClib::p_fopen())( strFnDest.c_str(), "ab" );
		if( fp2 == NULL )
		{
			fclose(fp1);
			return 0;
		}

		ckbuf.redim( iLenBytes );
		SStrf::smemset( ckbuf.buf(), 0, iLenBytes );

		while(1)
		{
			tsize a = (tsize)fread( ckbuf.buf(), 1, iLenBytes, fp1 );

			if( a == iLenBytes )
			{
				fwrite( ckbuf.buf(), iLenBytes, 1, fp2 );
			}
			else if( a == 0 )
			{
				break;
			}
			else
			{
				fwrite( ckbuf.buf(), a, 1, fp2 );
				break;
			}
		}

		fclose(fp1);
		fclose(fp2);

		return 1;
	}


	
	tbool IsHeadOf( SFile & me2 )
	{
		if( !SStrf::scmpi( this->filename().c_str(), me2.filename().c_str() ) ) return 0; 
		if( !this->exists() ) return 0;
		if( !me2.exists()   ) return 0;

		tsize i1, i2;

		if( (i1 = this->len()) == 0 ) return 0;
		if( (i2 = me2.len()) == 0   ) return 0;

		if( i1 > i2 ) return 0;

		SCake ck1, ck2;

		this->read( ck1 );
		me2.read( ck2 );

		if( !memcmp( ck1.buf(), ck2.buf(), i1 ) ) return 1;

		return 0;
	}


	tbool IsHeadOf( std::string strme2 )
	{
		SFile sf2;
		sf2.bind(strme2);
		return IsHeadOf(sf2);
	}


	static std::string ReadFileStr( const std::string & Fn )
	{
		SFile fInFile;
		std::string	 strFileContent;
		fInFile.bind( Fn );
		fInFile.read_str( strFileContent );
		return strFileContent;
	}

};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_w_SBmp_h
#define X011__H_w_w_SBmp_h


X011_NAMESPACE_BEGIN


class SBmp
{
public:
	struct RGB_t
	{
		tuint8 R;
		tuint8 G;
		tuint8 B;
		tuint8 _reserved;
	};

private:
	char  m_ASC_ZK16_NOZK[66];
	char  m_HZ_ZK16_NOZK[66];

protected:
	char *	m_pASC_ZK16;
	char *	m_pHZ_ZK16;
	SCake * m_pckBuf;		
	int     m_iBufWidth;	

public:
	RGB_t   m_DefaultColor;
	int     m_iCHARGAP;

public:
	
	static RGB_t MKRGB( tuint8 R, tuint8 G, tuint8 B )
	{
		RGB_t t;
		t.R = R;  t.G = G; 	t.B = B;
		return t;
	}

	
	static int bitn(int c, int i) {c>>=i;c&=1;return c;}


	void InitZK( char *pASC, char *pHz, SCake * pckbuf=NULL, int iwidth = 0 ) 
	{
		m_pASC_ZK16 = pASC;
		m_pHZ_ZK16 = pHz;
		m_pckBuf = pckbuf;
		if(m_pckBuf)
			SStrf::smemset( m_pckBuf->buf(), 0xff, m_pckBuf->len() );
		m_iBufWidth = iwidth;
		
		
	}

	
	void SaveBufBmpOut( std::string strFn , SCake *pck = NULL, int iDepth = 3, int iBufWidth = 0 )
	{
		if( m_pckBuf || pck )
		{
			SFile fl;
			int width = iBufWidth != 0 ? iBufWidth : m_iBufWidth;

			if( pck == NULL )  pck =m_pckBuf;

			fl.bind( strFn );
			Conv2Bmp( *pck, width, iDepth ); 
			fl.write(*pck);
		}
	}

public:
	
	SBmp()
	{
		m_iCHARGAP = 1;

		m_pASC_ZK16 =
		m_pHZ_ZK16 = NULL;
		m_pckBuf = NULL;
		m_iBufWidth = 0;

		m_DefaultColor = MKRGB( 0x00, 0x0, 0x0 );


		SStrf::smemset( m_ASC_ZK16_NOZK, 0, 66 );
		SStrf::smemset( m_HZ_ZK16_NOZK, 0, 66 );
		m_ASC_ZK16_NOZK[7] = 0x40;
		m_HZ_ZK16_NOZK[7] = 0x40;
	}

	
	virtual ~SBmp()
	{ ;
	}


	
	static tbool Conv2Bmp( SCake & ckPicInOut, tsize iWidth, int iDepth , tbool turnUpDn = 1 )
	{
		int iBMHeaderSize = 0x36;
		if( ckPicInOut.len() == 0 ) return 0;
		if( !( iDepth == 1 || iDepth == 2 || iDepth == 3 || iDepth == 4 ) ) return 0;

		tsize i1, i2;
		tsize iWidthNew;
		tsize iHeight;
		std::vector < tuint8 > v1;
		std::vector < std::vector < tuint8 >::size_type > vIdx1; 
		std::vector < std::vector < tuint8 >::size_type > vIdx2;

		for( iWidthNew = iWidth; ; iWidthNew++ )
		{
			if( iWidthNew % 4 == 0 ) break;
		}

		i1 = 0;
		iHeight = 0;
		v1.resize( iBMHeaderSize, 0 );

		for( ; ; )
		{
			vIdx1.push_back( v1.size() );

			for( i2 = 0; i2 < iWidth; i2++ )
			{
				tuint8 ui1;

				if( iDepth == 1 )
				{
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					v1.push_back(0);
					v1.push_back(0);
				}

				if( iDepth == 2 )
				{
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					v1.push_back(0);
				}

				if( iDepth == 3 )
				{
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
				}

				if( iDepth == 4 )
				{
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					
				}
			}

			
			
			
			
			
			
			for( ;;)
			{
				std::vector < tuint8 >::size_type ioccupy = v1.size() - *vIdx1.rbegin();
				if( ioccupy % 4 == 0 ) break;
				v1.push_back(0);
			}

			iHeight++;

			if( i1 >= ckPicInOut.len() ) break;
		}

		
		if( turnUpDn )
		if( vIdx1.size() >= 2 )
		{
			long ilinelen = (long)(vIdx1[1] - vIdx1[0]);
			std::vector < tuint8 > vlinebuf;
			vlinebuf.resize(ilinelen);
			vIdx2 = vIdx1;
			std::reverse(vIdx2.begin(), vIdx2.end());

			for( i2 = 0; i2 < vIdx1.size() / 2 ; i2++ )
			{
				SStrf::smemcpy( &(vlinebuf[0]),  &(v1[vIdx1[i2]]), ilinelen );
				SStrf::smemcpy( &(v1[vIdx1[i2]]),  &(v1[vIdx2[i2]]), ilinelen );
				SStrf::smemcpy( &(v1[vIdx2[i2]]),  &(vlinebuf[0]), ilinelen );
			}
		}

		*(char*)(&(v1[0])) = 'B';
		*(char*)(&(v1[1])) = 'M';
		*(tuint32*)(&(v1[2])) = (tuint32)v1.size();
		
		

		*(tuint16*)(&(v1[6])) = 0;
		

		*(tuint16*)(&(v1[8])) = 0;
		

		*(tuint32*)(&(v1[0xA])) = 0x36;
		
		

		*(tuint32*)(&(v1[0xE])) = 0x28;
		
		

		*(tuint32*)(&(v1[0x12])) = (tuint32)iWidth;
		
		

		*(tuint32*)(&(v1[0x16])) = (tuint32)iHeight;
		
		

		*(tuint16*)(&(v1[0x1A])) = 1;
		

		*(tuint16*)(&(v1[0x1c])) = 24;
		

		*(tuint32*)(&(v1[0x1E])) = 0;
		
		

		*(tuint32*)(&(v1[0x22])) = (tuint32)v1.size() - 0x36;
		
		

		*(tuint32*)(&(v1[0x26])) = 0;
		
		

		*(tuint32*)(&(v1[0x2a])) = 0;
		
		

		*(tuint32*)(&(v1[0x2e])) = 0;
		
		

		*(tuint32*)(&(v1[0x32])) = 0;
		
		

		ckPicInOut.let( (tchar*)(&(v1[0])), (tuint32)v1.size() );

		return 1;
	}


	virtual tuint8 OnConv2Bmp32( long X, long Y )
	{
		return (tuint8)255;
	}

	
	tbool Conv2Bmp32( const SCake & ckIn, SCake & ckBmpOut, tsize iWidth, tbool turnUpDn = 1 )
	{
		int iBMHeaderSize = 0x36;
		if( ckIn.len() == 0 ) return 0;
		if( iWidth == 0 ) return 0;

		tsize i1, i2;
		tsize iHeight;
		std::vector < tuint8 > v1;
		std::vector < std::vector < tuint8 >::size_type > vIdx1; 
		std::vector < std::vector < tuint8 >::size_type > vIdx2;

		i1 = 0;
		iHeight = 0;
		v1.resize( iBMHeaderSize, 0 );

		for( ; ; )
		{
			vIdx1.push_back( v1.size() );

			for( i2 = 0; i2 < iWidth; i2++ )
			{
				tuint8 ui1;
				long X,Y,H;

				X = i1 / 3;
				Y = X / iWidth;
				H = ckIn.len() / 3 / iWidth;
				Y = H - Y - 1;

				

				
				if( i1 < ckIn.len() ) ui1 = *(tuint8*)(ckIn.buf_const() + i1); else ui1 = 0;
				i1++;
				v1.push_back( ui1 );

				if( i1 < ckIn.len() ) ui1 = *(tuint8*)(ckIn.buf_const() + i1); else ui1 = 0;
				i1++;
				v1.push_back( ui1 );

				if( i1 < ckIn.len() ) ui1 = *(tuint8*)(ckIn.buf_const() + i1); else ui1 = 0;
				i1++;
				v1.push_back( ui1 );

				
				ui1 = OnConv2Bmp32( X, Y );
				v1.push_back( ui1 );

			}

			
			for( ;;)
			{
				std::vector < tuint8 >::size_type ioccupy = v1.size() - *vIdx1.rbegin();
				if( ioccupy % 4 == 0 ) break;
				v1.push_back(0);
			}

			iHeight++;

			if( i1 >= ckIn.len() ) break;
		}

		
		if( turnUpDn )
		if( vIdx1.size() >= 2 )
		{
			long ilinelen = (long)(vIdx1[1] - vIdx1[0]);
			std::vector < tuint8 > vlinebuf;
			vlinebuf.resize(ilinelen);
			vIdx2 = vIdx1;
			std::reverse(vIdx2.begin(), vIdx2.end());

			for( i2 = 0; i2 < vIdx1.size() / 2 ; i2++ )
			{
				SStrf::smemcpy( &(vlinebuf[0]),  &(v1[vIdx1[i2]]), ilinelen );
				SStrf::smemcpy( &(v1[vIdx1[i2]]),  &(v1[vIdx2[i2]]), ilinelen );
				SStrf::smemcpy( &(v1[vIdx2[i2]]),  &(vlinebuf[0]), ilinelen );
			}
		}

		*(char*)(&(v1[0])) = 'B';
		*(char*)(&(v1[1])) = 'M';
		*(tuint32*)(&(v1[2])) = (tuint32)v1.size();
		
		

		*(tuint16*)(&(v1[6])) = 0;
		

		*(tuint16*)(&(v1[8])) = 0;
		

		*(tuint32*)(&(v1[0xA])) = 0x36;
		
		

		*(tuint32*)(&(v1[0xE])) = 0x28;
		
		

		*(tuint32*)(&(v1[0x12])) = (tuint32)iWidth;
		
		

		*(tuint32*)(&(v1[0x16])) = (tuint32)iHeight;
		
		

		*(tuint16*)(&(v1[0x1A])) = 1;
		

		*(tuint16*)(&(v1[0x1c])) = 32;
		

		*(tuint32*)(&(v1[0x1E])) = 0;
		
		

		*(tuint32*)(&(v1[0x22])) = (tuint32)v1.size() - 0x36;
		
		

		*(tuint32*)(&(v1[0x26])) = 0;
		
		

		*(tuint32*)(&(v1[0x2a])) = 0;
		
		

		*(tuint32*)(&(v1[0x2e])) = 0;
		
		

		*(tuint32*)(&(v1[0x32])) = 0;
		
		

		ckBmpOut.let( (tchar*)(&(v1[0])), (tuint32)v1.size() );

		return 1;
	}


	static tbool Conv2Ck( const SCake & ckBmpIn, SCake &ckOut, int & rtn_iWidth, int & rtn_iHeight, int & rtn_iDepth )
	{
		if( ckBmpIn.len() < 0x32 ) return 0;
		if( *ckBmpIn.buf_const() != 'B' ) return 0;
		if( *(ckBmpIn.buf_const()+1) != 'M' ) return 0;

		rtn_iWidth = *(tuint32*)(ckBmpIn.buf_const()+0x12);
		rtn_iHeight = *(tuint32*)(ckBmpIn.buf_const()+0x16);
		rtn_iDepth = *(tuint16*)(ckBmpIn.buf_const()+0x1c);

		if( rtn_iDepth == 24 )
		{
			rtn_iDepth = 3;
		}
		else if( rtn_iDepth == 32 )
		{
			rtn_iDepth = 4;
		}
		else return 0;

		tsize iWidthNew;

		for( iWidthNew = rtn_iWidth; ; iWidthNew++ )
		{
			if( iWidthNew % 4 == 0 ) break;
		}

		if( rtn_iDepth == 3 || rtn_iDepth == 4 ) 
		{
			if( ckBmpIn.len() < iWidthNew * rtn_iHeight * rtn_iDepth )
				return 0;

			ckOut.redim( rtn_iWidth * rtn_iHeight * rtn_iDepth );

			const char *p;
			char *p1;

			p = ckBmpIn.buf_const() + ckBmpIn.len();
			p -= iWidthNew * rtn_iDepth;
			p1 = ckOut.buf();

			for( int j = 0; j < rtn_iHeight; j++ )
			{
				SStrf::smemcpy( p1, p, rtn_iWidth * rtn_iDepth );
				p -= iWidthNew * rtn_iDepth;
				p1 += rtn_iWidth * rtn_iDepth;
			}

			return 1;
		}

		if( rtn_iDepth == 4 )
		{
			return 0;
		}

		return 0;
	}


	static tbool Ck4Ck3( const SCake & ckIn, int iWidthIn, SCake & ckOut )
	{
		int x2,y2;
		const tchar *p1;
		tchar *p2;
		int iHeightIn;

		if( (ckIn.len() % (iWidthIn*4)) != 0 )
			return 0;

		iHeightIn = ckIn.len() / (iWidthIn*4);

		ckOut.redim( ckIn.len() / 4 * 3 );

		for( x2 = 0; x2 < iWidthIn; x2++ )
		{
			for( y2 = 0; y2 < iHeightIn; y2++ )
			{
				p1 = ckIn.buf_const() + ( iWidthIn * y2 + x2 ) * 4;

				p2 = ckOut.buf() + ( iWidthIn * y2 + x2 ) * 3;

				*p2 = *p1;  p1++; p2++;
				*p2 = *p1;  p1++; p2++;
				*p2 = *p1; 
			}
		}

		return 1;
	}


	static tbool Turn_180( const SCake & ckIn, SCake & ckOut )
	{
		const tchar *p1;
		tchar *p2;
		tsize i;

		ckOut.redim( ckIn.len() );

		if( (ckIn.len() % 3) != 0 )
		{
			p1 = ckIn.buf_const();
			p2 = ckOut.buf() + ckOut.len() - 1;

			for( i = 0; i < ckIn.len(); i++ )
			{
				*p2 = *p1;
				p1++;
				p2--;
			}
		}
		else
		{
			p1 = ckIn.buf_const();
			p2 = ckOut.buf() + ckOut.len() - 3;

			for( i = 0; i < ckIn.len(); i+=3 )
			{
				*p2 = *p1;
				p1++; p2++;
				*p2 = *p1;
				p1++; p2++;
				*p2 = *p1;
				p1++; p2++;
				p2 -= 3;
				p2 -= 3;
			}
		}

		return 1;
	}


	static tbool Turn_p90( const SCake & ckIn, int iWidthIn, SCake & ckOut, int & rtn_iWidthOut )
	{
		const tchar *p1;
		tchar *p2;
		int iHeightIn;
		int iHeightOut;
		int x,y;
		int x2,y2;

		if( (ckIn.len() % (iWidthIn*3)) != 0 )
			return 0;

		iHeightIn = ckIn.len() / (iWidthIn*3);
		rtn_iWidthOut = iHeightIn;
		iHeightOut = iWidthIn;

		ckOut.redim( ckIn.len() );
		for( y = 0; y < iHeightIn; y++ )
		{
			for( x = 0; x < iWidthIn; x++ )
			{
				p1 = ckIn.buf_const() + ( iWidthIn * y + x ) * 3;
				x2 = iHeightIn - 1 - y;
				y2 = x;
				p2 = ckOut.buf() + ( rtn_iWidthOut * y2 + x2 ) * 3;

				*p2 = *p1;  p1++; p2++;
				*p2 = *p1;  p1++; p2++;
				*p2 = *p1; 
			}
		}

		return 1;
	}


	virtual void On_Add_pic_func( int x, int y, tuint8 *pcMain, const tuint8 *pcSub )
	{
		*pcMain = *pcSub;  pcMain++; pcSub++;
		*pcMain = *pcSub;  pcMain++; pcSub++;
		*pcMain = *pcSub;
	}

	
	tbool Add_pic( SCake & ckMain, int iWidthMain, int x, int y, const SCake & ckSub, int iWidthSub )
	{
		int x3,y3; 
		int x2,y2; 
		tchar *p1;
		const tchar *p2;

		if( (ckMain.len() % (iWidthMain*3)) != 0 )
			return 0;

		if( (ckSub.len() % (iWidthSub*3)) != 0 )
			return 0;

		int HeightMain = ckMain.len() / (iWidthMain*3);
		int HeightSub = ckSub.len() / (iWidthSub*3);

		y3 = HeightSub + y;
		if( y3 > HeightMain ) y3 = HeightMain;

		x3 = iWidthSub + x;
		if( x3 > iWidthMain ) x3 = iWidthMain;

		for( x2 = x; x2 < x3; x2 ++ )
		{
			for( y2 = y; y2 < y3; y2 ++ )
			{
				p1 = ckMain.buf() + ( iWidthMain * y2 + x2 ) * 3;

				p2 = ckSub.buf_const() + ( iWidthSub * (y2-y) + (x2-x) ) * 3;

				On_Add_pic_func( x2, y2, (tuint8 *)p1, (const tuint8 *)p2 );
			}
		}

		return 1;
	}

	
	tbool Cut_pic( const SCake & ckIn, int iWidthIn, int x, int y, int iCutWidth, int iCutHeight, SCake & ckOut, int & iWidthOut )
	{
		int x3,y3;
		int x2,y2;
		const tchar *p1;
		tchar *p2;
		int iHeightIn;

		if( (ckIn.len() % (iWidthIn*3)) != 0 )
			return 0;

		iHeightIn = ckIn.len() / (iWidthIn*3);

		y3 = iCutHeight + y;
		if( y3 > iHeightIn ) y3 = iHeightIn;

		x3 = iCutWidth + x;
		if( x3 > iWidthIn ) x3 = iWidthIn;

		ckOut.redim( (x3-x) * (y3-y) * 3 );
		iWidthOut = x3-x;

		for( x2 = x; x2 < x3; x2 ++ )
		{
			for( y2 = y; y2 < y3; y2 ++ )
			{
				p1 = ckIn.buf_const() + ( iWidthIn * y2 + x2 ) * 3;

				p2 = ckOut.buf() + ( iWidthOut * (y2-y) + (x2-x) ) * 3;

				*p2 = *p1;  p1++; p2++;
				*p2 = *p1;  p1++; p2++;
				*p2 = *p1; 
			}
		}

		return 1;
	}


	int out1hz( const char *phz, int x=0, int y=0 )
	{
		unsigned char *p = (unsigned char *)phz;
		int n=0, i=0;
		unsigned ch=0,we=0,xoff=0,yoff=0;
		unsigned char *c;
		long aa = 0;

		c = (unsigned char *)m_HZ_ZK16_NOZK;

		if( p[0] == 0xa1 && p[1] == 0xa3 )
		{
			p[0]=0xaa,p[1]=0xae;
		}

		if( (x+xoff) > 79 )
		{
			xoff=0;
			yoff++;
		}

		if( (*p) > 0xa1 )
		{
			ch = ( *p++ - 0xa1) & 0x7f;
			we = ( *p++ - 0xa1) & 0x7f;
			aa = ( ch * 94 + we ) * 32l;
			c = (unsigned char *)m_pHZ_ZK16 + aa;
		}

		if( !m_pHZ_ZK16 ) c = (unsigned char *)m_HZ_ZK16_NOZK;

		for( n = 0; n < 32; n++ )
		{
			for( i = 7; i >= 0; i-- )
			{
				if(bitn(c[n],i))
					OnPoint(x,y);
				else
					OnPoint_bg(x,y);
				x++;
			}
			n++;
			for( i = 7; i >= 0; i--)
			{
				if(bitn(c[n],i))
					OnPoint(x,y);
				else
					OnPoint_bg(x,y);
				x++;
			}
			y++;OnYpp(y);
			x -= 16;
		}
		return x;
	}

	
	int out1hz_scale( const char *phz, int x=0, int y=0, double dRateX = 1.0 , double dRateY = 1.0 )
	{
		int x_ori = x;
		double i = 0;
		double n = 0;
		unsigned char *p = (unsigned char *)phz;
		unsigned ch=0,we=0,xoff=0,yoff=0;
		unsigned char *c;
		long aa = 0;
		double dStep_x = 1.0 / dRateX ;
		double dStep_y = 1.0 / dRateY ;

		if( p[0] == 0xa1 && p[1] == 0xa3 )
		{
			p[0]=0xaa,p[1]=0xae;
		}
		if( (x+xoff) > 79 )
		{
			xoff=0;
			yoff++;
		}

		if( (*p) > 0xa1 )
		{
			ch = ( *p++ - 0xa1) & 0x7f;
			we = ( *p++ - 0xa1) & 0x7f;
			aa = ( ch * 94 + we ) * 32l;
			c = (unsigned char *)m_pHZ_ZK16 + aa;
		}

		if( !m_pHZ_ZK16 ) c = (unsigned char *)m_HZ_ZK16_NOZK;

		for( n = 0; n < 16; n += dStep_y )
		{
			for( i = 0; i < 16; i += dStep_x )
			{
				if( SStrf::readbit_r_p( c + ( ((int)n)*2) , (int)i ) )
					OnPoint( x,y );
				else
					OnPoint_bg(x,y);
				x++;
			}
			y ++; OnYpp(y);
			x = x_ori;
		}
		return x;
	}

	
	int out1asc( const char *pasc, int x=0, int y=0 )
	{
		unsigned char *p = (unsigned char *)pasc;
		int n=0,i=0;
		unsigned char *c;

		c = (unsigned char *)m_pASC_ZK16 + *p*16L;
		
		
		if( !m_pASC_ZK16 ) c = (unsigned char *)m_ASC_ZK16_NOZK;

		for(n=0;n<16;n++) {
		 for(i=7;i>=0;i--) {
				if(bitn(c[n],i)) OnPoint(x,y);
				else OnPoint_bg(x,y);
				x++;
		 }
		 x-=8;
		 y++;OnYpp(y);
		}
		return x;
	}


	int out1asc_scale( const char *pasc, int x=0, int y=0, double dRateX = 1.0 , double dRateY = 1.0 )
	{
		int x_ori = x;
		double i = 0.0;
		double n = 0.0;
		unsigned char *p = (unsigned char *)pasc;
		unsigned char *c;
		double dStep_x = 1.0 / dRateX ;
		double dStep_y = 1.0 / dRateY ;

		c = (unsigned char *)m_pASC_ZK16 + *p*16L;
		if( !m_pASC_ZK16 ) c = (unsigned char *)m_ASC_ZK16_NOZK;

		for( n = 0.0 ; n < 16.0 ; n += dStep_y )
		{
			for( i = 7.0 ; i >= 0.0 ; i -= dStep_x  )
			{
				if( bitn( c[(int)n], (int)i ) )
					OnPoint(x,y);
				else
					OnPoint_bg(x,y);

				x ++;
			}
			x = x_ori;
			y ++; OnYpp(y);
		}
		return x;
	}


	int OutText( const char *pstr, int x=0, int y=0, int RealDraw = 1 )
	{
		int CHARGAP = m_iCHARGAP;
		unsigned char *p = (unsigned char *)pstr;
		int pos;
		unsigned char c[2];
		for(pos=0;p[pos]!=0;pos++)if(iscntrl(p[pos]))p[pos]=' ';
		for(pos=0;p[pos]!=0;) {
			if(p[pos]>0xa0) {
					c[0]=p[pos];c[1]=p[pos+1];
					pos+=2;
					if(RealDraw) { out1hz((char*)c,x,y); OnZipp(x,y); }
					x+=16+ CHARGAP;
			}else{
					c[0]=p[pos++];
					c[1]=0;
					if(RealDraw) { out1asc((char*)c,x,y);OnZipp(x,y); }
					x+=8+ CHARGAP;
			}
		}
		return x;
	}

	
	int OutText_scale( const char *pstr, int x=0, int y=0, double dRateX = 1.0 , double dRateY = 1.0, int RealDraw = 1 )
	{
		int CHARGAP = m_iCHARGAP;
		unsigned char *p = (unsigned char *)pstr;
		int pos;
		unsigned char c[2];
		for(pos=0;p[pos]!=0;pos++)if(iscntrl(p[pos]))p[pos]=' ';
		for(pos=0;p[pos]!=0;) {
			if(p[pos]>0xa0) {
					c[0]=p[pos];c[1]=p[pos+1];
					pos+=2;
					if(RealDraw) { out1hz_scale((char*)c,x,y,dRateX,dRateY); OnZipp(x,y); }
					x += (16*(int)dRateX) + CHARGAP;
			}else{
					c[0]=p[pos++];
					c[1]=0;
					if(RealDraw) { out1asc_scale((char*)c,x,y,dRateX,dRateY); OnZipp(x,y); }
					x += (8*(int)dRateX) + CHARGAP;
			}
		}
		return x;
	}


	int OutTextWidth_scale( const char *pstr, int x2, int y2, int iWidth, double dRateX = 1.0 , double dRateY = 1.0, int RealDraw = 1 , int * ppos = NULL )
	{
		int CHARGAP = m_iCHARGAP;
		int x = x2;
		int y = y2;
		unsigned char *p = (unsigned char *)pstr;
		int pos;
		unsigned char c[3];
		c[2]=0;

		if( ppos ) { *ppos=0; }

		for(pos=0;p[pos]!=0;pos++)
		{
			if( iscntrl(p[pos]) && p[pos] != '\n' ) p[pos]=' ';
		}

		for(pos=0;p[pos]!=0;)
		{
			if( p[pos] == '\n' )
			{
				x = x2;
				y += (int)(16.0 * dRateY) + CHARGAP;

				pos++;

				if( ppos ) { *ppos=pos; return y; } 

				continue;
			}

			if( x - x2 > iWidth )
			{
				x = x2;
				y += (int)(16.0 * dRateY) + CHARGAP;

				if( ppos ) { *ppos=pos; return y; } 
			}
			else 
			{
				int x3 = x;

				if(p[pos]>0xa0)
					x3 += (int)( 16.0 * dRateX ) + CHARGAP;
				else
					x3 += (int)( 8.0 * dRateX ) + CHARGAP;

				if( x3 - x2 > iWidth )
				{
					if( ppos ) { *ppos=pos; return y; } 
				}
			}

			if(p[pos]>0xa0)
			{
				c[0]=p[pos]; c[1]=p[pos+1];
				pos+=2;
				if(RealDraw) { out1hz_scale((char*)c,x,y,dRateX,dRateY); OnZipp(x,y); }
				x += (16*(int)dRateX) + CHARGAP;
			}else
			{
				c[0]=p[pos++]; c[1]=0;
				if(RealDraw) { out1asc_scale((char*)c,x,y,dRateX,dRateY);OnZipp(x,y); }
				x += (8*(int)dRateX) + CHARGAP;
			}
		}
		return y;
	}

	
	int OutTextWidth( const char *pstr, int x2, int y2, int iWidth, int RealDraw = 1, int * ppos = NULL )
	{
		int CHARGAP = m_iCHARGAP;
		int x = x2;
		int y = y2;
		unsigned char *p = (unsigned char *)pstr;
		int pos;
		unsigned char c[3];
		c[2]=0;

		if( ppos ) { *ppos=0; }

		for(pos=0;p[pos]!=0;pos++)
		{
			if( iscntrl(p[pos]) && p[pos] != '\n' ) p[pos]=' ';
		}

		for(pos=0;p[pos]!=0;)
		{
			if( p[pos] == '\n' )
			{
				x = x2;
				y += 16+ CHARGAP;

				pos++;

				if( ppos ) { *ppos=pos; return y; } 

				continue;
			}

			if( x - x2 > iWidth )
			{
				x = x2;
				y += 16+ CHARGAP;

				if( ppos ) { *ppos=pos; return y; } 
			}
			else 
			{
				int x3 = x;

				if(p[pos]>0xa0)
					x3 += 16+ CHARGAP;
				else
					x3 += 8+ CHARGAP;

				if( x3 - x2 > iWidth )
				{
					if( ppos ) { *ppos=pos; return y; } 
				}
			}

			if(p[pos]>0xa0)
			{
				c[0]=p[pos]; c[1]=p[pos+1];
				pos+=2;
				if(RealDraw) { out1hz((char*)c,x,y); OnZipp(x,y); }
				x += 16+ CHARGAP;
			}else
			{
				c[0]=p[pos++]; c[1]=0;
				if(RealDraw) { out1asc((char*)c,x,y);OnZipp(x,y); }
				x += 8+ CHARGAP;
			}
		}
		return y;
	}


	virtual void OnPoint( int x, int y )
	{
		if( m_pckBuf )
		{
			char *buf = m_pckBuf->buf();
			int width = m_iBufWidth;
			int o = y * width + x;
			char *p;

			p = buf + o * 3;
			*p = (char)m_DefaultColor.B;
			p++;
			*p = (char)m_DefaultColor.G;
			p++;
			*p = (char)m_DefaultColor.R;
		}
	}


	virtual void OnPoint_bg( int x, int y ) { ;	}

	virtual void OnYpp( int y ) { ;	}				

	virtual void OnZipp( int x, int y ) { ;	}		

};




class SimpPaper : public SBmp
{
public:
	SCake   m_ckBuf;	
	int     m_width;	
	int     m_height;	
	RGB_t   m_foreColor;
	RGB_t   m_backColor;

public:
	
	SimpPaper()
	{
		m_ckBuf.redim(0);
		m_width = 0;
		m_height = 0;

		m_foreColor = MKRGB( 0x00, 0x00, 0x00 );	
		m_backColor = MKRGB( 0xff, 0xff, 0xff );	

		m_pckBuf = NULL;
		m_iBufWidth = 0;
		m_DefaultColor = m_foreColor;
	}

	
	virtual ~SimpPaper(){}


	tbool Init( int width ) 
	{
		m_width = width;
		m_height = m_ckBuf.len() / m_width / 3;

		return 1;
	}

	
	tbool Init( int width, int height )
	{
		m_width = width;
		m_height = height;
		m_ckBuf.redim( 3 * m_width * m_height );
		m_pckBuf = &m_ckBuf;

		for( int y = 0; y < m_height; y++ )
		{
			for( int x = 0; x < m_width; x++ )
			{
				PaperPutPixel( x, y, m_backColor );
			}
		}

		return 1;
	}

	
	tbool InitFn( std::string strFn )
	{
		SFile fl;
		fl.bind( strFn );
		return Init( fl );
	}

	
	tbool Init( SFile fl )
	{
		m_pckBuf = &m_ckBuf;

		SCake ck;

		fl.read( ck );

		return Init(ck);
	}

	
	tbool Init( const SCake &ckBmp24 )
	{
		tbool rc;
		const SCake &ck(ckBmp24);
		int depth;

		rc = SBmp::Conv2Ck( ck, m_ckBuf, m_width, m_height, depth );

		if( rc == 0 && depth == 3 ) 
		{
			tint32 &L( *(tint32*)(ck.buf_const()+0x16) );
			if( L < 0 )
			{
				L = L * (-1);
				SBmp::Conv2Ck( ck, m_ckBuf, m_width, m_height, depth );
				TurnUpDn();
				return 1;
			}
			return 0;
		}

		return 1;
	}

	
	tbool Init( std::string str, int CrPixelWidth, tbool RealDraw = 1 )
	{
		int y;
		tbool rc;

		y = this->PrintText( str.c_str(), 0, 0, 0, CrPixelWidth );
		if( y == 0 ) return 0;
		rc = Init( CrPixelWidth, y );

		if( !rc ) return rc;
		if( !RealDraw ) return rc;

		rc = Init( CrPixelWidth, y );
		y = this->PrintText( str.c_str(), 0, 0, 1, CrPixelWidth );

		return rc;
	}


	tbool Init_str_scale( std::string str, int CrPixelWidth, double ratex, double ratey )
	{
		int y;
		tbool rc;

		y = this->PrintText( str.c_str(), 0, 0, 0, CrPixelWidth , 1, ratex, ratey );
		if( y == 0 ) return 0;
		rc = Init( CrPixelWidth, y );

		if( !rc ) return rc;

		rc = Init( CrPixelWidth, y );
		y = this->PrintText( str.c_str(), 0, 0, 1, CrPixelWidth , 1, ratex, ratey );

		return rc;
	}


	void AttachHZK( char *pASC, char *pHz )
	{
		InitZK( pASC, pHz, &m_ckBuf , m_width );
	}


	tbool SaveBmp( std::string strFn )
	{
		SFile fl;
		SCake ck;

		ck = m_ckBuf;
		fl.bind( strFn );
		if( !Conv2Bmp( ck, m_width, 3 , 1 ) ) return 0;
		return fl.write(ck);
	}

	
	tbool SaveBmp( SCake &ckBmp )
	{
		ckBmp = m_ckBuf;
		if( !Conv2Bmp( ckBmp, m_width, 3 , 1 ) ) return 0;
		return 1;
	}


	tbool ConvBmp( SCake &ckOut )
	{
		if( !Conv2Bmp( ckOut, m_width, 3 , 1 ) ) return 0;
		return 1;
	}


	void PaperPutPixel( int x, int y, RGB_t color )
	{
		if( x >= m_width ) return;
		if( y >= m_height) return;

		char *buf = m_ckBuf.buf();
		int o = y * m_width + x;
		char *p;

		p = buf + o * 3;
		*p = (char)(color.B);
		p++;
		*p = (char)(color.G);
		p++;
		*p = (char)(color.R);
	}

	
	tbool PaperGetPixel( int x, int y, RGB_t &color )
	{
		if( x >= m_width ) return 0;
		if( y >= m_height) return 0;

		char *buf = m_ckBuf.buf();
		int o = y * m_width + x;
		char *p;

		p = buf + o * 3;
		color.B = (tuint8)(*p);
		p++;
		color.G = (tuint8)(*p);
		p++;
		color.R = (tuint8)(*p);

		return 1;
	}

	
	RGB_t PaperGetPixel( int x, int y )
	{
		if( x >= m_width ) return m_backColor;
		if( y >= m_height) return m_backColor;

		RGB_t color;
		char *buf = m_ckBuf.buf();
		int o = y * m_width + x;
		char *p;

		p = buf + o * 3;
		color.B = (tuint8)(*p);
		p++;
		color.G = (tuint8)(*p);
		p++;
		color.R = (tuint8)(*p);

		return color;
	}


	
	
	virtual void OnPoint( int x, int y )
	{
		PaperPutPixel( x, y, m_foreColor );
	}

	
	
	
	



	tbool TurnUpDn()
	{
		tbool rc;
		SCake ck;
		int width, height, depth;

		ck = m_ckBuf;
		rc = Conv2Bmp( ck, m_width, 3 , 0 );
		if( !rc ) return 0;
		SBmp::Conv2Ck( ck, m_ckBuf, width, height, depth );
		return 1;
	}

	
	tbool TurnP90()
	{
		int iWidth;
		SCake ck;
		tbool rc;

		ck = m_ckBuf;
		rc = Turn_p90( ck, m_width, m_ckBuf, iWidth );
		m_height = m_width;
		m_width= iWidth;
		return rc;
	}

	
	tbool Turn180()
	{
		SCake ck;
		tbool rc;

		ck = m_ckBuf;
		rc = Turn_180( ck , m_ckBuf );
		return rc;
	}

	
	tbool Add( int x, int y, SimpPaper & sp2 )
	{
		return Add_pic( m_ckBuf, m_width, x, y, sp2.m_ckBuf, sp2.m_width );
	}

	
	tbool AddUseTrans( int x, int y, SimpPaper & sp2 , int CopyXor = 0 ) 
	{
		int x3,y3; 
		int x2,y2; 
		int x9,y9; 

		y3 = sp2.m_height + y;
		if( y3 > m_height ) y3 = m_height;

		x3 = sp2.m_width + x;
		if( x3 > m_width ) x3 = m_width;

		for( x2 = x; x2 < x3; x2 ++ )
		{
			x9 = (x2-x);

			for( y2 = y; y2 < y3; y2 ++ )
			{
				y9 = (y2-y);

				RGB_t ColorSub;

				sp2.PaperGetPixel( x9, y9, ColorSub );

				if( m_backColor.R == ColorSub.R && m_backColor.G == ColorSub.G && m_backColor.B == ColorSub.B )
				{
				}
				else
				{
					if( CopyXor == 0 )
					{
						PaperPutPixel( x2,y2, ColorSub );
					}
					else
					{
						RGB_t ColorMain;

						PaperGetPixel( x2,y2, ColorMain );
						ColorMain.R ^= ColorSub.R;
						ColorMain.G ^= ColorSub.G;
						ColorMain.B ^= ColorSub.B;

						PaperPutPixel( x2,y2, ColorMain );
					}
				}
			}
		}

		return 1;
	}

	
	tbool Cut( int x, int y, int iCutWidth, int iCutHeight, SimpPaper & sp2 )
	{
		SCake ck;
		tbool rc;

		rc = Cut_pic( m_ckBuf, m_width, x, y, iCutWidth, iCutHeight, sp2.m_ckBuf, sp2.m_width );
		sp2.Init( sp2.m_width );
		return rc;
	}

	
	tbool Cut2( int x, int y, int x2, int y2, SimpPaper & sp2 )
	{
		return Cut( x, y, x2 - x, y2 - y , sp2 );
	}


	int PrintText( std::string s1, int x, int y, int RealDraw = 1, int CrPixelWidth = 0 , tbool HaveScale = 0 , double dRateX = 1.0 , double dRateY = 1.0 )
	{
		const char *p = s1.c_str();

		m_pckBuf = &m_ckBuf;
		m_DefaultColor = m_foreColor;

		int pos = 0;

		if( p && *p )
		for( ; ; )
		{
			if( HaveScale == 0 )
			{
				OutTextWidth( p, x, y, CrPixelWidth <= 0 ? m_width : CrPixelWidth , RealDraw, &pos );

				p += pos;
				y += 16+ m_iCHARGAP;
				if( pos == 0 ) break;
			}
			else
			{
				
				OutTextWidth_scale( p, x, y, CrPixelWidth <= 0 ? m_width : CrPixelWidth , dRateX , dRateY, RealDraw, &pos );

				p += pos;
				y += (int)( 16.0 * dRateY ) + m_iCHARGAP;
				if( pos == 0 ) break;
			}
		}

		return y;
	}

	
	void Line( int x1, int y1, int x2, int y2 )
	{
		 int dx = x2 - x1;
		 int dy = y2 - y1;
		 int ux = ((dx > 0) << 1) - 1;
		 int uy = ((dy > 0) << 1) - 1;
		 int x = x1, y = y1, eps;

		 eps = 0;dx = abs(dx); dy = abs(dy);
		 if (dx > dy)
		 {
			 for (x = x1; x != x2+ux; x += ux)
			 {
				  PaperPutPixel( x, y, m_foreColor );
				  eps += dy;
				  if ((eps << 1) >= dx)
				  {
					   y += uy; eps -= dx;
				  }
			 }
		 }
		 else
		 {
			 for (y = y1; y != y2+uy; y += uy)
			 {
				  PaperPutPixel( x, y, m_foreColor );
				  eps += dx;
				  if ((eps << 1) >= dy)
				  {
					   x += ux; eps -= dy;
				  }
			 }
		 }
	}

	
	void Rect( int x1, int y1, int x2, int y2 )
	{
		Line( x1, y1, x2, y1 );
		Line( x1, y1, x1, y2 );
		Line( x2, y2, x2, y1 );
		Line( x2, y2, x1, y2 );
	}

	
	void Rect()
	{
		Rect( 0, 0, m_width-1, m_height-1 );
	}

	
	void Circle( int x, int y, int r )
	{
		int tx = 0;
		int ty = r;
		int d = 1 - r;

		RGB_t &color(m_foreColor);

		while(tx <= ty){
			
			PaperPutPixel(x + tx, y + ty, color);
			PaperPutPixel(x + tx, y - ty, color);
			PaperPutPixel(x - tx, y + ty, color);
			PaperPutPixel(x - tx, y - ty, color);
			PaperPutPixel(x + ty, y + tx, color);
			PaperPutPixel(x + ty, y - tx, color);
			PaperPutPixel(x - ty, y + tx, color);
			PaperPutPixel(x - ty, y - tx, color);
			if(d < 0){
				d += 2 * tx + 3;
			}else{
				d += 2 * (tx - ty) + 5;
				ty--;
			}
			tx++;
		}
	}

};






X011_NAMESPACE_END


#endif






#ifndef X011__H_w_SNava_h
#define X011__H_w_SNava_h


X011_NAMESPACE_BEGIN


template< class nameT, class valueT >
class SNava_base
{
public:
	typedef typename std::map< nameT, valueT >::iterator		 MAP_MAPKNL_IT;
	typedef typename std::map< nameT, valueT >::const_iterator   MAP_MAPKNL_CONSTIT;

public:
	std::map< nameT, valueT >  m_mapKnl;

public:

	virtual ~SNava_base() {;}


	void clear()
	{
		m_mapKnl.clear();
	}


	tbool IsEmpty()
	{
		if( m_mapKnl.empty() ) return 1;
		return 0;
	}


	tbool let( const nameT & name, const valueT & val )
	{
		
		m_mapKnl[name] = val; 
		return 1;
	}


	tbool get( const nameT & name, valueT & val )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			val = it->second;
			return 1;
		}
		return 0;
		
	}


	valueT & get( const nameT & name )
	{
		return m_mapKnl[name];
	}


	tbool del( const nameT & name )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			m_mapKnl.erase(it);
			return 1;
		}
		return 0;
	}


	tbool GetFirstName( nameT & Name, MAP_MAPKNL_IT & it4name )
	{
		it4name = it4name.begin();
		if( it4name != m_mapKnl.end() )
		{
			Name = it4name->first;
			return 1;
		}
		return 0;
	}


	tbool GetNextName( nameT & Name, MAP_MAPKNL_IT & it4name )
	{
		it4name ++;
		if( it4name != m_mapKnl.end() )
		{
			Name = it4name->first;
			return 1;
		}
		return 0;
	}


	bool operator < ( const SNava_base & rhs) const
	{
		return  m_mapKnl < rhs.m_mapKnl ;
	}

	bool operator <= ( const SNava_base & rhs) const
	{
		return  m_mapKnl <= rhs.m_mapKnl ;
	}

	bool operator > ( const SNava_base & rhs) const
	{
		return  m_mapKnl > rhs.m_mapKnl ;
	}

	bool operator >= ( const SNava_base & rhs) const
	{
		return m_mapKnl >= rhs.m_mapKnl ;
	}

	bool operator == ( const SNava_base & rhs) const
	{
		return  m_mapKnl == rhs.m_mapKnl ;
	}
};



class SNavass : public SNava_base< std::string, std::string >
{
private:

	static void seri_element_en( SCake & ck )
	{
		if( ck.len() == 0 ) return;
		ck.bs_en();
	}

	static void seri_element_de( SCake & ck )
	{
		if( ck.len() == 0 || !ck.buf() )
		{
			ck.lets("");
			return;
		}

		ck.bs_de();

		if( ck.len() == 0 || !ck.buf() )
		{
			ck.lets("");
			return;
		}

		
	}

public:
	virtual ~SNavass() {;}


	void imp( const std::string & ssource, std::string ssepTR, std::string ssepTD )
	{
		SStrvs::vsa2v_prpt( ssource, ssepTR, ssepTD , m_mapKnl );
	}


	void trimall()
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			SStrf::strim( s1 );
			SStrf::strim( s2 );

			this->let( s1, s2 );
		}
	}


	tbool let( const std::string & name, const std::string & val )
	{
		m_mapKnl[name] = val;
		return 1;
	}


	tbool let( const std::string & name, int val )
	{
		m_mapKnl[name] = SStrf::sltoa(val);
		return 1;
	}


	std::string GetReadable() const
	{
		std::string strOut = "";

		for( MAP_MAPKNL_CONSTIT it = m_mapKnl.begin(); it != m_mapKnl.end(); ++it )
		{
			strOut += it->first;
			strOut += "=";
			strOut +=  it->second;
			strOut += "\r\n";
		}

		return strOut;
	}


	tbool serialize( std::string & strOut ) const
	{
		strOut = "";

		SCake ckTmp;

		for( MAP_MAPKNL_CONSTIT it = m_mapKnl.begin(); it != m_mapKnl.end(); ++it )
		{
			ckTmp.lets( it->first );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += "(";

			ckTmp.lets( it->second );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += ")";
		}

		return 1;
	}


	std::string serialize() const
	{
		std::string strOut;
		serialize(strOut);
		return strOut;
	}


	tbool unserialize( const std::string & strData )
	{
		std::map< std::string, std::string > mapTmp;

		SStrvs::vsa2v_prpt( strData, std::string(")"), std::string("(") , mapTmp );

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			SCake ckTmp1,ckTmp2;

			ckTmp1.lets( it->first );
			seri_element_de( ckTmp1 );

			ckTmp2.lets( it->second );
			seri_element_de( ckTmp2 );

			
			this->let( ckTmp1.mk_str(), ckTmp2.mk_str() );
		}

		return 1;
	}

};



class NaStrarr__bak
{
	SNavass m_navaknl;

public:
	std::string  m_serialize_hold;

	
	void clear()
	{
		m_navaknl.clear();
	}

	
	tbool let( long name, const std::string & val )
	{
		m_navaknl.let( SStrf::sltoa(name) , val );
		return 1;
	}

	
	std::string & get( long name )
	{
		return m_navaknl.get(SStrf::sltoa(name));
	}

	std::string & operator[] (long name )
	{
		return get(name);
	}

	
	tbool del( long name )
	{
		return m_navaknl.del(SStrf::sltoa(name));
	}

	
	const char * serialize_hold()
	{
		m_serialize_hold = m_navaknl.serialize();
		return m_serialize_hold.c_str();
	}

	
	std::string serialize() const
	{
		return m_navaknl.serialize();
	}

	
	tbool unserialize( const std::string & strData )
	{
		return m_navaknl.unserialize(strData);
	}

	
	
	
	

	
	
	
	
};


template< class KeyType_T >		
class NaStrarr_base
{
protected:
	SNavass m_navaknl;
	std::string  m_serialize_hold;

public:
	virtual ~NaStrarr_base() {;}

	
	void clear()
	{
		m_navaknl.clear();
	}

	
	tbool let( KeyType_T name, const std::string & val )
	{
		std::stringstream stream1;
		stream1<<name;
		m_navaknl.let( stream1.str() , val );
		return 1;
	}

	
	std::string & get( KeyType_T name )
	{
		std::stringstream stream1;
		stream1 << name;
		return m_navaknl.get(stream1.str());
	}

	
	std::string & operator[] ( KeyType_T name )
	{
		return get(name);
	}

	
	tbool del( KeyType_T name )
	{
		std::stringstream stream1;
		stream1 << name;
		return m_navaknl.del(stream1.str());
	}

	
	const char * serialize_hold_addr()
	{
		m_serialize_hold = m_navaknl.serialize();
		return m_serialize_hold.c_str();
	}
	
	long serialize_hold_len()
	{
		return (long)m_serialize_hold.size() + 1;
	}

	
	std::string serialize() const
	{
		return m_navaknl.serialize();
	}

	
	tbool unserialize( const std::string & strData )
	{
		return m_navaknl.unserialize(strData);
	}

	
	
	
	

	bool operator <  ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl <  rhs.m_navaknl; 	}
	bool operator <= ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl <= rhs.m_navaknl; 	}
	bool operator >  ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl >  rhs.m_navaknl; 	}
	bool operator >= ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl >= rhs.m_navaknl; 	}
	bool operator == ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl == rhs.m_navaknl; 	}
	bool operator != ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return !(m_navaknl == rhs.m_navaknl);  	}
};



class NaStrarr : public NaStrarr_base< long >
{
public:
	virtual ~NaStrarr() {;}
};



template< class INT_NAME_T, class INT_VAL_T >
class NaIntarr_base : public NaStrarr_base< INT_NAME_T >
{
public:
	virtual ~NaIntarr_base()
	{;}

	
	tbool let( INT_NAME_T name, INT_VAL_T val )
	{
		std::stringstream stream1;
		std::stringstream stream_val;
		stream1 << name;
		stream_val << val;
		NaStrarr_base< INT_NAME_T >::m_navaknl.let( stream1.str() , stream_val.str() );
		return 1;
	}

	
	INT_VAL_T get( INT_NAME_T name )
	{
		std::stringstream stream1;
		std::stringstream stream2;
		INT_VAL_T n;
		stream1 << name;
		if( NaStrarr_base< INT_NAME_T >::m_navaknl.get(stream1.str()).empty() )
		{
			stream2 << "0";
		}
		else
			stream2 << NaStrarr_base< INT_NAME_T >::m_navaknl.get(stream1.str());
		stream2 >> n;
		return n;
	}

	
	INT_VAL_T operator[] ( INT_NAME_T name )
	{
		return get(name);
	}
};



class NaLngarr : public NaIntarr_base< long, long >
{
public:
	virtual ~NaLngarr() {;}

	long addvalue( long name, long val )
	{
		long j = get( name );
		j += val;
		let( name, j );
		return j;
	}
};



	
	

class NaS2S : public NaStrarr_base< std::string >	
{
public:
	virtual ~NaS2S() {;}
};


class NaL2S : public NaStrarr	 	
{
public:
	virtual ~NaL2S() {;}
};


class NaL2L : public NaLngarr	 	
{
public:
	virtual ~NaL2L() {;}
};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_SPeco_h
#define X011__H_w_SPeco_h


X011_NAMESPACE_BEGIN


template < class itT >	
class SPeco
{
public:
	typedef typename std::vector< itT >				RTNVEC_T;
	typedef typename std::vector< itT >::iterator	RTNVEC_IT;

private:
	std::vector< itT >  m_begin;
	std::vector< itT >  m_end;

	std::vector< itT >  m_beginBak;
	std::vector< itT >  m_endBak;

	tbool m_canfetchflag;

	std::set< RTNVEC_T > m_comb_buf;

public:

	SPeco()
	{
		GotoBegin();
	}

	virtual ~SPeco()
	{;
	}

public:

	void Reset()
	{
		m_begin.clear();
		m_end.clear();
		m_beginBak.clear();
		m_endBak.clear();
		m_comb_buf.clear();
		GotoBegin();
	}


	void RegIt( itT itbegin , itT itend )
	{
		if( itbegin != itend )
		{
			m_begin.push_back( itbegin );
			m_end.push_back( itend );

			m_beginBak.push_back( itbegin );
			m_endBak.push_back( itend );
		}
	}


	void GotoBegin() 
	{
		m_begin = m_beginBak;
		m_end = m_endBak;

		m_comb_buf.clear();

		m_canfetchflag = 1;
	}


	tbool Fetch( RTNVEC_T & v_rtn ) 
	{
		v_rtn.clear();

		typename std::vector<itT>::size_type i;
		tbool plusflag = 1;

		if( m_canfetchflag == 0 ) return 0;

		for( i = 0 ; i < m_begin.size() ; i++ )
		{
			itT & myit( m_begin[i] );

			v_rtn.push_back( myit );	

			if( plusflag )
			{
				myit++;
				plusflag = 0;
			}

			if( myit == m_end[i] )
			{
				myit = m_beginBak[i];
				plusflag = 1;
			}
		}

		if( plusflag ) 
		{
			m_canfetchflag = 0;
		}

		return 1;
	}


	tbool FetchNodup( RTNVEC_T & v_rtn ) 
	{
		tbool b;

		for( ; ; )
		{
			b = Fetch( v_rtn );

			if( !b )
				return 0;

			std::vector< itT > v2;

			SSetu::vs_setgroup( v_rtn, v2 );

			if( v_rtn.size() == v2.size() )
				return b;
		}
	}


	void MakeComb( tbool HaveDup = 1 ) 
	{
		m_comb_buf.clear();

		do
		{
			RTNVEC_T v;
			tbool b;

			if( HaveDup ) b = Fetch( v );
			else b = FetchNodup( v );

			if( !b )
			{
				break;
			}

			std::sort( v.begin(), v.end() );

			m_comb_buf.insert( v );

		}while( 1 );
	}


	tbool FetchComb( RTNVEC_T & v_rtn ) 
	{
		if( m_comb_buf.empty() ) return 0;

		v_rtn = * m_comb_buf.begin();

		m_comb_buf.erase( m_comb_buf.begin() );

		return 1;
	}


};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_SAbys_h
#define X011__H_w_SAbys_h



X011_NAMESPACE_BEGIN


class SAbys
{

private:

	SCake		m_knowledge_cake;
	tsize		m_knowledge_cur_pos;
	tdouble		m_data_knowledge_ratio;

	
	

public:

	SAbys()
	{
		init( 23.6 );
	}

	SAbys( tdouble ratio )
	{
		init( ratio );
	}

	SAbys( const SCake & cakeKnow )
	{
		init(cakeKnow);
	}

	virtual ~SAbys( )
	{ ; }


	void init( tdouble data_knowledge_ratio = 1.0 )
	{
		SStrf::initrand();
		SCake ckTmp( SStrf::sftoa( SStrf::rand1() ) + SStrf::sftoa( SStrf::rand1() ) );
		ckTmp.cut(1);
		init( ckTmp , data_knowledge_ratio );
	}


	void init( const SCake & knowledge_cake , tdouble data_knowledge_ratio = 1.0 )
	{
		if(knowledge_cake.len()>0)
			m_knowledge_cake = knowledge_cake;
		else
			init(data_knowledge_ratio);
		m_knowledge_cur_pos = (tsize)(m_knowledge_cake.len() * SStrf::rand1());
		m_data_knowledge_ratio = data_knowledge_ratio>0?data_knowledge_ratio:1;
	}


	void mix( const SCake & ck_Data  ,
			  SCake & ck_Mixeddata  ,
			  tchar chSep = '('		)
	{
		SCake ck_dubious_data = ck_Data;
		ck_dubious_data.bs_en();

		SStrf::srev( ck_dubious_data );
		tsize iKnowLen = (tsize)(ck_Data.len()/m_data_knowledge_ratio);
		ck_Mixeddata.redim( ck_dubious_data.len() + iKnowLen + 1 );
		SStrf::scpy( ck_Mixeddata, ck_dubious_data );
		ck_dubious_data.cut(1);
		tsize iPnt = ck_dubious_data.len();
		*(ck_Mixeddata.buf()+iPnt) = chSep;
		iPnt++;
		for(ck_Mixeddata.cut(1);iPnt!=ck_Mixeddata.len();iPnt++)
		{
			m_knowledge_cur_pos++;
			if(m_knowledge_cur_pos>=m_knowledge_cake.len()) m_knowledge_cur_pos=0;
			*(ck_Mixeddata.buf()+iPnt) = *(m_knowledge_cake.buf()+m_knowledge_cur_pos);
		}
		*(ck_Mixeddata.buf()+iPnt) = 0;
	}

	std::string mix( const SNavass & nv )
	{
		std::string str;
		nv.serialize(str);
		SCake ck1( str );
		SCake ck2;
		mix( ck1, ck2 );
		return ck2.buf();
	}

	std::string & mix( const std::string & str , std::string & strOut )
	{
		SCake ck1( str );
		SCake ck2;
		mix( ck1, ck2 );
		strOut = ck2.buf();
		return strOut;
	}


	void unmix(  const SCake & ck_Mixeddata,		 
				 SCake	 & ck_Data						,
				 tchar chSep = '('		)
	{
		SCake ck0("");
		SCake ckMixDataWriteable( ck_Mixeddata );

		ckMixDataWriteable.append( ck0 );

		tchar strSep[2];

		strSep[0] = chSep;
		strSep[1] = 0;

		ck_Data.lets( SStrvs::vsa_get( std::string(ckMixDataWriteable), std::string(strSep), 1, 0 ) );
		SStrf::srev( ck_Data );
		tsize iDatalen = SStrf::bs_desize( ck_Data );
		
		ck_Data.bs_de();
		ck_Data.redim( iDatalen, 1 );
	}

	void unmix( const std::string & strSource, SNavass & nv )
	{
		SCake ck1( strSource );
		SCake ck2;
		unmix( ck1, ck2 );
		ck2.mk_sz();
		nv.unserialize( std::string(ck2) );
	}

	std::string & unmix( const std::string & strSource, std::string & strOut )
	{
		SCake ck1( strSource );
		SCake ck2;
		unmix( ck1, ck2 );
		ck2.mk_sz();
		strOut = ck2.buf();
		return strOut;
	}


	void envelop( 	const SCake & ckKeyWord,
					const SCake & ckHead, const SCake & ckTail, const SCake & ck_src, SCake & ck_destbuf )
	{
		
	}

	tbool unenvelop( const SCake & ckKeyWord,
					 const SCake & ck_src, SCake & ck_destbuf	)
	{
		return 1;
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_IRice_h
#define X011__H_w_IRice_h



X011_NAMESPACE_BEGIN


class IRice
{
public:
	tbool m_biRecv0Flag;

protected:
	SCake m_ckDataL2CacheBuf;

protected:

	tsize sys_recv( SCake & ckDataBuf )
	{
		on_send_recv_kick();

		int i = on_sys_recv(ckDataBuf); 
		if(i)
		{
			return i;
		}
		else
		{
			ckDataBuf.redim(0);
			m_biRecv0Flag = 1;
			return 0;
		}
	}


	tsize sys_send( const SCake & ckDataBuf )
	{
		on_send_recv_kick();

		return on_sys_send(ckDataBuf);
	}


public:

	IRice( )
	{
		m_biRecv0Flag = 0;
	}


	virtual ~IRice( )
	{ ; }


	void ClearL2Cache()
	{
		m_ckDataL2CacheBuf.redim(0);
	}


	tbool send_str( std::string s ) 
	{
		return send_str(s.c_str());
	}


	tbool send_str( const tchar *s ) 
	{
		SCake ckTmp(s);
		ckTmp.cut(1);
		return send_bin( ckTmp );
	}


	template<class T>
	tbool send_bin_internal( T adata )
	{
		SCake ck;
		ck.let( (SCake::CkEle_t*)&adata, sizeof(T) );
		return send_bin(ck);
	}

	tbool send_bin( tuint8  a ) { return send_bin_internal(a); }
	tbool send_bin( tuint16 a ) { return send_bin_internal(a); }
	tbool send_bin( tuint32 a ) { return send_bin_internal(a); }
	tbool send_bin( tint8  a ) { return send_bin_internal(a); }
	tbool send_bin( tint16 a ) { return send_bin_internal(a); }
	tbool send_bin( tint32 a ) { return send_bin_internal(a); }

	
	tbool send_bin( const SCake & ckData )
	{
		tsize rc, k;
		if(ckData.len()==0) return 0;
		for(k=0;;)
		{
			SCake ckTmp(ckData.buf_const()+k, ckData.len()-k);
			rc = sys_send( ckTmp );
			if(rc==0) return 0;
			k += rc;
			if(k>=ckData.len()) break;
		}
		return 1;
	}

	tbool send_bin_shortdata( const SCake & ckData )
	{
		tsize rc, k;
		if(ckData.len()==0) return 0;
		for(k=0;;)
		{
			rc = sys_send( ckData );
			if(rc==0) return 0;
			break;
		}
		return 1;
	}


	
	
	



	tbool recv_bin( SCake & ckData ) 
	{
		SCake ckTmp;

		if( m_ckDataL2CacheBuf.len() == 0 )
		{
			sys_recv( ckTmp ); 
			m_ckDataL2CacheBuf.append(ckTmp);
		}
		else
		{
			
		}

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_all( SCake & ckData ) 
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; 

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_all_f( SCake & ckData ) 
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			
			m_ckDataL2CacheBuf.FastAppend(ckTmp);

			
		}while(ckTmp.len()>0);

		m_ckDataL2CacheBuf.FastAppendEnd();

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_len( SCake & ckData , tsize iWantDataLen ) 
	{
		SCake ckTmp;

		while( m_ckDataL2CacheBuf.len()< iWantDataLen )
		{
			if( !sys_recv( ckTmp ) ) break;

			
			m_ckDataL2CacheBuf.FastAppend(ckTmp);
		}

		m_ckDataL2CacheBuf.FastAppendEnd();

		ckData.redim(iWantDataLen);
		m_ckDataL2CacheBuf.dump( ckData );
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


	tbool recv_ln( SCake & ckData , const std::vector<std::string> & vecstrSeperate, std::string * pstrRealSep=NULL ) 
	{
		SCake ckTmp;
		tchar * pSep;
		SCake ckSepDumpTmp;

		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();

			pSep = NULL;

			if(pstrRealSep) *pstrRealSep = "";

			
			for( std::vector<std::string>::const_iterator it = vecstrSeperate.begin();
				 it != vecstrSeperate.end();
				 ++it )
			{
				pSep = SStrf::sstr( ckTmpL2Cache2, it->c_str() );
				if( pSep )
				{
					if(pstrRealSep) *pstrRealSep = *it;

					ckSepDumpTmp.lets(*it);
					ckSepDumpTmp.cut(1); 
					break;
				}
			}


			if( pSep )
			{
				
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );

				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); 
				return 1;
			}

			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; 

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_ln( SCake & ckData , const tchar * strSeperate = "\n" ) 
	{
		if( strSeperate && std::string(strSeperate) == "\r\n\r\n\r\n" )
			return recv_ln2( ckData , strSeperate );

		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);

		ckSepDumpTmp.cut(1); 

		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();

			
			pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );

			if( pSep )
			{
				
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );

				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); 
				return 1;
			}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; 

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_ln( SCake & ckData , tchar cSeperate ) 
	{
		tchar t[2];
		t[0]=cSeperate;
		t[1]=0;
		return recv_ln(ckData,t) ;
	}


	tbool recv_ln2( SCake & ckData , const tchar * strSeperate )  
	{
		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);

		ckSepDumpTmp.cut(1);


		std::vector<tchar>  vec_m_ckTmpL2CacheBuf;
		std::copy( m_ckDataL2CacheBuf.buf(), m_ckDataL2CacheBuf.buf() + m_ckDataL2CacheBuf.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) );

		long lLastChkOffset(0);

		do
		{
			vec_m_ckTmpL2CacheBuf.push_back(0);

			pSep = SStrf::sstr( &(vec_m_ckTmpL2CacheBuf[lLastChkOffset]), strSeperate );

			vec_m_ckTmpL2CacheBuf.pop_back();


			if( pSep )
			{
				
				
				if( vec_m_ckTmpL2CacheBuf.empty() )
					m_ckDataL2CacheBuf.redim(0);
				else
					m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

				vec_m_ckTmpL2CacheBuf.clear();
				

				SCake ckTmpL2Cache2;
				ckTmpL2Cache2 = m_ckDataL2CacheBuf;
				ckTmpL2Cache2.mk_sz();

				pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );

				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );

				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp );
				return 1;
			}
			else
			{
				
				lLastChkOffset = (long)vec_m_ckTmpL2CacheBuf.size() - (long)ckSepDumpTmp.len();
				if( lLastChkOffset < 0 ) lLastChkOffset = 0;
			}


			if( !sys_recv( ckTmp ) ) break;

			std::copy( ckTmp.buf(), ckTmp.buf() + ckTmp.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) );
			

			
		}while(ckTmp.len()>0);


		
		if( vec_m_ckTmpL2CacheBuf.empty() )
			m_ckDataL2CacheBuf.redim(0);
		else
			m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

		vec_m_ckTmpL2CacheBuf.clear();
		

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


public:

	virtual void on_send_recv_kick()
	{
		return;
	}

	virtual tbool on_chk_L2CacheLen( const SCake & ckCurrentL2Cache )
	{
		return 1;
	}


	virtual int on_sys_recv( SCake & ckDataBuf ) 
	{
		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		return 0;
	}


};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_ICursor_h
#define X011__H_w_ICursor_h


X011_NAMESPACE_BEGIN


template < class envT, class tblT, class rowT >
class ICursor
{
private:

	tbool		 m_bIsEnvOpen;
	tbool		 m_bIsTblOpen;

public:

	ICursor( )
	{
		m_bIsEnvOpen = m_bIsTblOpen = 0;
	}


	virtual ~ICursor( )
	{
		
	}

public:
	typedef envT envTYPE;
	typedef tblT tblTYPE;
	typedef rowT rowTYPE;

public:
	tbool GetIsEnvOpen()
	{
		return m_bIsEnvOpen;
	}

	tbool GetIsTblOpen()
	{
		return m_bIsTblOpen;
	}

public:
	tbool OpenEnv( envTYPE & _env )
	{
		CloseEnv();
		return m_bIsEnvOpen = OnOpenEnv(_env);
	}

	tbool OpenTbl( tblTYPE & _tbl )
	{
		CloseTbl();
		return m_bIsTblOpen = OnOpenTbl(_tbl);
	}

	tbool FetchRow( rowTYPE & _row )
	{
		return OnFetchRow( _row );
	}

	void CloseTbl()
	{
		if( GetIsTblOpen() ) OnCloseTbl();
		m_bIsTblOpen=0;
	}

	void CloseEnv()
	{
		if( GetIsEnvOpen() ) OnCloseEnv();
		m_bIsEnvOpen=0;
	}

public:
	virtual tbool OnOpenEnv( envTYPE & _env )
	{
		return 0;
	}

	virtual tbool OnOpenTbl( tblTYPE & _tbl )
	{
		return 0;
	}

	virtual tbool OnFetchRow( rowTYPE & _row )
	{
		return 0;
	}

	virtual void OnCloseTbl()
	{
		return;
	}

	virtual void OnCloseEnv()
	{
		return;
	}

};








template < class IDS_ELE_TYPE_T >
class ICursorDsColNames
{
public:
	typedef typename std::map<std::string,int> ColNamesMapTYPE;
	typedef  IDS_ELE_TYPE_T IDS_Ele_TYPE;

public:
	ColNamesMapTYPE  m_mapColNames;
	std::vector<IDS_Ele_TYPE>  m_row;
	IDS_Ele_TYPE m_emptyrow;

public:
	int SetColNames( std::string strColNames )
	{
		std::vector<std::string> rtnlst;
		SStrvs::vsa_imp( strColNames, std::string(","), 0, rtnlst );
		m_mapColNames.clear();
		for( int i = 0; i < (int)rtnlst.size(); i++ )
		{
			m_mapColNames[SStrf::strim(rtnlst[i])] = i;
		}
		return (int)m_mapColNames.size();
	}

	void SetRow( const std::vector<IDS_Ele_TYPE> & r )
	{
		m_row = r;
	}

	ICursorDsColNames & operator = ( const char * szColNames )
	{
		SetColNames(szColNames);
		return *this;
	}

	ICursorDsColNames & operator = ( const std::vector<IDS_Ele_TYPE> & r )
	{
		SetRow(r);
		return *this;
	}

	IDS_Ele_TYPE GetEle( const std::vector<IDS_Ele_TYPE> & row, int iCol )
	{
		if( iCol < 0 || iCol >= (int)row.size() ) return IDS_Ele_TYPE();
		return row[iCol];
	}

	IDS_Ele_TYPE GetEle( int iCol )
	{
		return GetEle( m_row, iCol );
	}

	IDS_Ele_TYPE & operator [] ( int iCol )
	{
		if( iCol < 0 || iCol >= (int)m_row.size() ) return m_emptyrow = IDS_Ele_TYPE();
		return m_row[iCol];
	}

	IDS_Ele_TYPE GetEle( const std::vector<IDS_Ele_TYPE> & row, const std::string & strName )
	{
		ColNamesMapTYPE::const_iterator it = m_mapColNames.find(strName);
		if( it != m_mapColNames.end() )
			return GetEle(row, it->second);
		else
			return IDS_Ele_TYPE();
	}

	IDS_Ele_TYPE GetEle( const std::string & strName )
	{
		return GetEle( m_row, strName );
	}

	IDS_Ele_TYPE & operator [] (const std::string & strName)
	{
		ColNamesMapTYPE::const_iterator it = m_mapColNames.find(strName);
		if( it != m_mapColNames.end() )
		{
			return (*this)[it->second];
		}
		else
			return m_emptyrow = IDS_Ele_TYPE();
	}
};




template < class IDS_ELE_TYPE_T >
class ICursorDs_base : public ICursor < std::string,				 
										std::string,				 
										std::vector<IDS_ELE_TYPE_T>  > 
{
public:
	typedef  IDS_ELE_TYPE_T IDS_Ele_TYPE;

	typedef  ICursorDsColNames<IDS_ELE_TYPE_T> ColNamesTYPE;

public:
	virtual ~ICursorDs_base( )
	{ ;
	}

};




class ICursorDs	: public ICursorDs_base < std::string >
{
public:
	virtual ~ICursorDs( )
	{ ;
	}


};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_wstrvs_h
#define X011__H_w_wstrvs_h


X011_NAMESPACE_BEGIN


class WStrvs {

public:

	
	virtual ~WStrvs(){;}

	template < class CStrT > 
	static tsize vsa_imp( const CStrT & ssource, const CStrT & ssep, tbool istoken, std::vector<CStrT> & rtnlst )
	{
		std::vector<tint32> vAbuf, vBbuf;
		tint32 ltmp_npointer,ltmp_mpointer,ltmp_calci,ltmp_calcj,ltmp_calck, ltmp_boundb1, ltmp_boundb2;
		tint32 findpos;
		ltmp_mpointer = ltmp_calci = ltmp_calcj = 0;
		ltmp_npointer = (tint32)ssource.GetLength();
		ltmp_calck = (tint32)ssep.GetLength();

		do 
		{
			if(ltmp_calck==0)
			{
				rtnlst.push_back(ssource);
				break;
			}

			do
			{
				if(ltmp_mpointer>=ltmp_npointer) break;
				findpos = ssource.Find( ssep, ltmp_mpointer ); 
				if(findpos==-1) break;
				ltmp_calci = (tint32)findpos;
				ltmp_mpointer = ltmp_calci;

				vAbuf.push_back(ltmp_calci);
				ltmp_calcj ++;
				ltmp_mpointer += ltmp_calck;

			} while(1);

			ltmp_boundb1 = 0 ; 
			ltmp_boundb2 = ltmp_calcj - 1 ; 

			ltmp_calcj = 0;
			vBbuf.push_back(ltmp_calcj);
			for(ltmp_calci=ltmp_boundb1;ltmp_calci<=ltmp_boundb2;ltmp_calci++){
				ltmp_calcj = vAbuf[ltmp_calci];
				vBbuf.push_back(ltmp_calcj);
				vBbuf.push_back(ltmp_calcj+ltmp_calck);
			}
			vBbuf.push_back( ltmp_npointer );

			ltmp_calcj = (tint32)vBbuf.size();
			for(ltmp_calci=0;ltmp_calci<ltmp_calcj;ltmp_calci+=2)
			{
				ltmp_mpointer = vBbuf[ltmp_calci];
				ltmp_npointer = vBbuf[ltmp_calci+1];
				ltmp_calck = ltmp_npointer - ltmp_mpointer;

				if(istoken&&ltmp_calck==0){
					;
				}else
					rtnlst.push_back( ssource.Mid( ltmp_mpointer, ltmp_calck ) ); 

			}

		}while(0);

		return (tsize)rtnlst.size();
	}


	template < class StrT > 
	static tsize vsa_hm( const StrT & ssource, const StrT & ssep, tbool istoken )
	{
		return vsa_imp( ssource, ssep, istoken, std::vector<StrT>() );
	}


	template < class StrT > 
	static StrT vsa_get( const StrT & ssource, const StrT & ssep, tbool istoken, tsize iwhich )
	{
		std::vector<StrT> tmplst;
		if( iwhich<vsa_imp( ssource, ssep, istoken, tmplst ) )
			return tmplst[iwhich];
		else return StrT();
	}


	template < class CStrT > 
	static tsize vsa_token( const CStrT &source, const CStrT &tok, std::vector<CStrT> & rtnlst )
	{
		CStrT s1, resToken;
		CStrT sempty;
		int curPos= 0;
		tsize licounter;
		licounter=0;
		s1 = source;
		sempty = "";
		resToken= s1.Tokenize(tok,curPos);
		while( resToken !=sempty )
		{
			licounter++;
			rtnlst.push_back( resToken );
			resToken= s1.Tokenize(tok,curPos);
		}
		return licounter;
	}


	template < class CStrT >
	static tsize vsa_hm( const CStrT & source, const CStrT & tok )
	{
		return vsa_token( source, tok, std::vector<CStrT>() );
	}


	template < class CStrT >
	static CStrT vsa_get( const CStrT & source, const CStrT & tok , tsize iwhich )
	{
		std::vector<CStrT> tmplst;
		if( iwhich<vsa_token( source, tok, tmplst ) )
			return tmplst[iwhich];
		else return CStrT();
	}


}; 




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_wcrsc_h
#define X011__H_w_wcrsc_h


X011_NAMESPACE_BEGIN


class WCrsc
{
private:
	CRITICAL_SECTION * m_pcsFather;
	WCrsc            * m_pCrsc_father;
	int              m_biIsBusy;

private:
	

	

	void LockCrsc( WCrsc & Crsc_father )
	{
		if(Crsc_father.m_pcsSelf)
		{
			EnterCriticalSection( m_pcsFather = Crsc_father.m_pcsSelf );
			m_pCrsc_father = &Crsc_father;
			m_pCrsc_father->SetBusy();
		}
	}

	void InitVars()
	{
		m_pcsFather = NULL;
		m_pCrsc_father=NULL;
		m_pcsSelf = NULL;
		m_biIsBusy = 0;
	}

	
	void SetBusy()
	{
		m_biIsBusy++;
	}

	
	void SetIdle()
	{
		m_biIsBusy--;
	}

public:
	CRITICAL_SECTION * m_pcsSelf;

public:

	WCrsc()
	{
		InitVars();

		m_pcsSelf = new CRITICAL_SECTION;
		InitializeCriticalSection( m_pcsSelf );
	}


private:
	
	
	
	
	WCrsc( WCrsc & Crsc_father)
	{
		InitVars();

		LockCrsc( Crsc_father );
	}


public:
	WCrsc( WCrsc * pCrsc_father)
	{
		InitVars();

		if( pCrsc_father ) LockCrsc( *pCrsc_father );
	}


	virtual ~WCrsc()
	{
		if( m_pcsFather != NULL )
		{
			m_pCrsc_father->SetIdle();
			LeaveCriticalSection( m_pcsFather );
			return;
		}

		if( m_pcsFather == NULL )
		{
			if( m_pcsSelf != NULL )
			{
				DeleteCriticalSection( m_pcsSelf );
				delete m_pcsSelf;
				return;
			}
		}
	}


	WCrsc & operator = (const WCrsc & rhs) 
	{
		
		return *this;
	}


	tbool IsIdle() const
	{
		return m_biIsBusy?0:1;
	}

}; 




X011_NAMESPACE_END

#endif








#ifndef X011__W_WUNITBLCH_H
#define X011__W_WUNITBLCH_H



X011_NAMESPACE_BEGIN



class unitbl_base_t
{
protected:
	

public:
	WCrsc		m_ut_tbl_lck;

public:
	unitbl_base_t() { ;}
	virtual ~unitbl_base_t() {;	}

public:
	virtual void ut_ClearTbl() = 0;

	virtual int ut_GetColAmount() = 0;
	virtual std::string ut_GetColName( int iColNum ) = 0;

	virtual long ut_GetRowAmount() = 0;

	virtual std::string ut_GetRowSeriStr( long lRowNum ) = 0;

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName ) = 0;
	virtual std::string ut_GetItemStr( long lRowNum, int iColNum ) = 0;

	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA  ) = 0;
	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA  ) = 0;


	virtual void _save_readable( std::string strFn ) = 0;
	virtual std::string _get_readable_row( long iRow )  = 0;


	virtual std::string & ut_SeriTblStr( std::string & strOut ) = 0;
	virtual tbool ut_SeriTblFile( SFile & fl ) = 0;
	virtual tbool ut_SeriTblFile( SFile & fl, long lbegin, long lend ) = 0;
	virtual unitbl_base_t & ut_UnseriTblStr( const std::string & strIn, int biAppend ) = 0;

	virtual tbool ut_SeriTblFile( std::string strFn ) = 0;
	virtual unitbl_base_t & ut_UnseriTblFile( std::string strFn ) = 0;


	virtual long ut_AddRow() = 0;	
	virtual long ut_AddRow( std::string strRowSeriStr) = 0;
	virtual void ut_ReIdx() = 0;
	virtual void ut_DelRowf( long lRowNum ) = 0;
	virtual void ut_DelRow( long lRowNum ) = 0;

	virtual void * ut_GetRowAddr( long lRowNum ) = 0;
	virtual std::string ut_GetRowAddrStr( long lRowNum )=0;

	virtual unitbl_base_t * ut_GetDup() = 0;
	virtual void ut_DestroyDup(unitbl_base_t *p) { 	if( p ) delete p; }

	
	void SdbAttachFile( std::string strTblName, std::string strWorkPath ) {	OnSdbAttachFile( strTblName, strWorkPath); }
	tbool SdbLoadFile() { return OnSdbLoadFile(); }
	tbool SdbSaveFile() { return OnSdbSaveFile(); }
	virtual void OnSdbAttachFile( std::string strTblName, std::string strWorkPath ) {return;}
	virtual tbool OnSdbLoadFile() { return 0; }
	virtual tbool OnSdbSaveFile() { return 0; }

};




template<class T>
class unitbl_t : public unitbl_base_t , public T
{
public:
	virtual ~unitbl_t() {;}

public:
	virtual void ut_ClearTbl()
	{
		T::Clear();
	}

	virtual int ut_GetColAmount()
	{
		return T::GetRow(-1).GetColAmount() ;
	}

	virtual std::string ut_GetColName( int iColNum )
	{
		return T::GetRow(-1).GetColName( iColNum );
	}

	virtual long ut_GetRowAmount()
	{
		return T::GetRowCount();
	}

	virtual std::string ut_GetRowSeriStr( long lRowNum )
	{
		return T::GetRow(lRowNum).Serialize();
	}

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( strColName, s1 );
		return s1;
	}

	virtual std::string ut_GetItemStr( long lRowNum, int iColNum )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( iColNum, s1 );
		return s1;
	}

	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA )
	{
		T::GetRow(lRowNum).SetColVal( strColName, strValPARA );
	}

	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA )
	{
		T::GetRow(lRowNum).SetColVal( iColNum, strValPARA );
	}

	
	long _ut_imp( std::string strtblFn, std::string strTD, std::string strTR,  int SrcBeginRownum = 0, int SrcBeginColnum = 0, int TblBeginColnum = 0, tbool WithTrim = 1 , const tchar *str_space="\r\n \t" )
	{
		std::string strtbl;
		SFile fl;
		long lAddedRowNum = 0;

		fl.bind( strtblFn );
		fl.read_str( strtbl );

		tsize x, y,z;
		tsize a, b;

		a = SStrvs::vsa_hm( strtbl, strTR, 1 );

		for( y = 0; y < a; y++ )
		{
			if( (int)y < SrcBeginRownum )
				continue;
			else
			{
				std::string str1 = SStrvs::vsa_get( strtbl, strTR, 1, y );

				if(WithTrim)
					SStrf::strim( str1,str_space );

				b = SStrvs::vsa_hm( str1, strTD, 0 );

				long lNowRowNum = this->ut_AddRow();

				lAddedRowNum++;

				z = TblBeginColnum;

				std::vector< std::string > vecs2;

				SStrvs::vsa_imp( str1, strTD, 0, vecs2 );

				for( x = 0; x < b; x++ )
				{
					if( (int)x < SrcBeginColnum )
						continue;
					else
					{
						std::string str2;

						
						if( x >= (int)vecs2.size() )
						{
							str2 = "";
						}
						else
						{
							str2 = vecs2[x];
						}

						if(WithTrim)
							SStrf::strim( str2 ); 

						
						T::GetRow(lNowRowNum).SetColVal( (int)z, str2 );

						z ++;
					}
				}
			}
		}
		return lAddedRowNum;
	}

	
	void _save_readable( std::string strFn )
	{
		SFile fl;

		fl.bind( strFn );
		fl.erase();
		for( int y = 0; y < this->ut_GetRowAmount(); y++ )
		{
			std::string s2;

			for( int x = 0; x < this->ut_GetColAmount(); x++ )
			{
				s2 += this->ut_GetColName(x) + "=" + this->ut_GetItemStr(y,x);
				if( x != this->ut_GetColAmount() - 1 ) s2 += ", ";
			}
			fl.write_str( s2 + "\r\n", 1 );
		}
	}

	
	std::string _get_readable_row( long iRow )
	{
		int y = iRow;
		std::string s2;

		for( int x = 0; x < this->ut_GetColAmount(); x++ )
		{
			s2 += this->ut_GetColName(x) + "=" + this->ut_GetItemStr(y,x);
			if( x != this->ut_GetColAmount() - 1 ) s2 += ", ";
		}
		return s2;
	}

	virtual std::string & ut_SeriTblStr( std::string & strOut )
	{
		return T::Serialize( strOut );
	}

	virtual tbool ut_SeriTblFile( SFile & fl )
	{
		tbool rc = 0;
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "wb" );
		if(fp==NULL) return rc;
		for(long i=0;i<(long)T::GetRowCount();i++)
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		rc = 1;
		fclose(fp);
		return rc;
	}


	virtual tbool ut_SeriTblFile( SFile & fl, long lbegin, long lend )
	{
		tbool rc = 0;
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "ab" );
		if(fp == NULL) return rc;
		for( long i = lbegin;i<(long)lend + 1; i++ )
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		rc = 1;
		fclose(fp);
		return rc;
	}

	virtual unitbl_base_t & ut_UnseriTblStr( const std::string & strIn, int biAppend )
	{
		T::Unserialize( strIn.c_str() , biAppend )	;
		return *this;
	}


	virtual tbool ut_SeriTblFile( std::string strFn )
	{
		SFile fl;
		fl.bind(strFn);
		return this->ut_SeriTblFile(fl);
	}

	virtual unitbl_base_t & ut_UnseriTblFile( std::string strFn )
	{
		std::string strContent;
		SFile fl;
		tbool rc;

		fl.bind( strFn );
		this->ut_ClearTbl();
		rc = fl.read_str( strContent );
		return this->ut_UnseriTblStr( strContent, 0 );
	}


	virtual long ut_AddRow()
	{
		T::Add(T::GetRow(-1));
		return T::GetRowCount() - 1 ;
	}

	virtual long ut_AddRow( std::string strRowSeriStr )
	{
		typename T::ROWTYPE row1;
		row1.Unserialize( strRowSeriStr.c_str() );
		T::Add(row1);
		return T::GetRowCount() - 1 ;
	}

	virtual void ut_ReIdx()
	{
		T::ReIdx();
		return;
	}

	virtual void ut_DelRowf( long lRowNum )
	{
		T::DelInternal( lRowNum );
	}

	virtual void ut_DelRow( long lRowNum )
	{
		T::Del( lRowNum );
	}

	virtual void * ut_GetRowAddr( long lRowNum )
	{
		return (void*)(&(T::GetRow(lRowNum)));
	}

	
	virtual std::string ut_GetRowAddrStr( long lRowNum )
	{
		void *p= (void*)(&(T::GetRow(lRowNum)));
		return SStrf::b2s(p);
	}

	virtual unitbl_base_t * ut_GetDup()
	{
		
		try
		{
			unitbl_t<T> *p;
			p = new unitbl_t<T>();
			*p = *this;
			return p;
		}
		catch(...)
		{
			return NULL;
		}
	}

};


template<class T>
class SDB_t : public unitbl_t< T >
{
private:
	std::string  m_strTblChkSum1;
	std::string  m_strTblChkSum2;

public:
	std::string  m_strTblName;
	std::string  m_strWorkPath;
	tbool        m_FastSaveFlag;

public:
	tbool        m_Dirty1; 
	tbool        m_Dirty2;

public:
	
	SDB_t()
	{
		m_FastSaveFlag = 0;
		m_Dirty1 = 1;
		m_Dirty2 = 1;
	}

	
	virtual ~SDB_t() {;}

public:

	
	virtual void OnSdbAttachFile( std::string strTblName, std::string strWorkPath )
	{
		InitSDB( strTblName, strWorkPath );
	}
	virtual tbool OnSdbLoadFile() { return Load(); }
	virtual tbool OnSdbSaveFile() { return SaveF(); }

	
	void InitSDB( std::string strTblName, std::string strWorkPath, tbool FastSaveFlag = 0, tbool Dirty1 = 1, tbool Dirty2 = 1 )
	{
		m_strTblName = strTblName;
		m_strWorkPath = SFile::MkDir2Path(strWorkPath);
		m_FastSaveFlag = FastSaveFlag;
		m_Dirty1 = Dirty1;
		m_Dirty2 = Dirty2;
	}

	
	tbool DetectDirty()	
	{
		std::string s1;

		if( this->ut_GetRowAmount() == 0 )
			s1 = "";
		else
		{
			s1 = this->ut_GetRowSeriStr(0);
			s1 += SStrf::sltoa(this->ut_GetRowAmount());
			s1 += this->ut_GetRowSeriStr(this->ut_GetRowAmount()-1);
			s1 += this->ut_GetRowAddrStr(this->ut_GetRowAmount()-1);
		}

		if( m_Dirty1 == 1 || s1 != m_strTblChkSum1 )
		{
			m_strTblChkSum1 = s1;
			m_Dirty1 = 1;
		}

		if( m_Dirty2 == 1 || s1 != m_strTblChkSum2 )
		{
			m_strTblChkSum2 = s1;
			m_Dirty2 = 1;
		}

		if( m_Dirty1 == 0 &&
			m_Dirty2 == 0	)
			return 0;

		return 1;
	}


	tbool Load()
	{
		std::string strPFn1;
		std::string strPFn2;
		std::string strLight1;
		std::string strLight2;
		std::string strContent;
		SFile fl;
		tbool rc;

		strPFn1 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".1.txt";
		strPFn2 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".2.txt";
		strLight1 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".light1.txt";
		strLight2 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".light2.txt";

		fl.bind( strLight1 );
		if( fl.exists() )
		{
			fl.bind( strPFn1 );
			m_Dirty1 = 0;
			m_Dirty2 = 1;
		}
		else
		{
			fl.bind( strPFn2 );
			m_Dirty1 = 1;
			m_Dirty2 = 0;
		}

		this->ut_ClearTbl();
		rc = fl.read_str( strContent );
		this->ut_UnseriTblStr( strContent, 0 );

		
		return rc;
	}

	
	virtual void OnLightFileSync()
	{
		
		
	}

	
	virtual void OnBeforeDataFileDel( SFile & fl )
	{
		
	}

	
	tbool Save( int iWhich = 0 , tbool WithDetectDirty = 1 ) 
	{
		if( iWhich == 0 )
		{
			return this->Save(1,WithDetectDirty) && this->Save(2,WithDetectDirty);
		}

		std::string strPFn1;
		std::string strPFn2;
		std::string strLight1;
		std::string strLight2;
		std::string strContent;
		SFile fl;
		tbool		rcDiskOk1(1);
		tbool		rcDiskOk2(1);

		strPFn1 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".1.txt";
		strPFn2 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".2.txt";
		strLight1 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".light1.txt";
		strLight2 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".light2.txt";

		if( WithDetectDirty ) DetectDirty();

		if( iWhich == 1 && m_Dirty1 )
		{
			unitbl_base_t * p = NULL;  
			unitbl_base_t * pp = NULL;

			
			fl.bind( strLight1 );
			fl.erase();
			OnLightFileSync();

			if( m_FastSaveFlag == 1 )  
			{
				
				p = pp = this->ut_GetDup();
			}

			if( pp == NULL )
				pp = this;

			fl.bind( strPFn1 );
			OnBeforeDataFileDel(fl);
			fl.erase();
			rcDiskOk1 = pp->ut_SeriTblFile(fl);
			if(p)
				this->ut_DestroyDup(p);
			if( rcDiskOk1 )
				m_Dirty1 = 0;

			
			fl.bind( strLight1 );
			fl.write_str( SDte::GetNow().ReadString() );
			OnLightFileSync();
		}

		if( iWhich == 2 && m_Dirty2 )
		{
			unitbl_base_t * p = NULL;  
			unitbl_base_t * pp = NULL;

			
			fl.bind( strLight2 );
			fl.erase();
			OnLightFileSync();

			if( m_FastSaveFlag == 1 )
				p = pp = this->ut_GetDup();

			if( pp == NULL )
				pp = this;

			fl.bind( strPFn2 );
			OnBeforeDataFileDel(fl);
			fl.erase();
			rcDiskOk2 = pp->ut_SeriTblFile(fl);
			if(p)
				this->ut_DestroyDup(p);
			if( rcDiskOk2 )
				m_Dirty2 = 0;

			
			fl.bind( strLight2 );
			fl.write_str( SDte::GetNow().ReadString() );
			OnLightFileSync();
		}

		if( iWhich == 1  )
			return rcDiskOk1;

		
			return rcDiskOk2;
	}

	
	tbool SaveF() 
	{
		SDB_t< T > * p=NULL;

		if(1)
		{
			WCrsc aaLock( &(this->m_ut_tbl_lck) );

			
			DetectDirty();

			if( m_Dirty1 || m_Dirty2 )
			{
				
				p = new SDB_t< T >;
				*p = *this;

				p->m_Dirty1 = m_Dirty1;
				p->m_Dirty2 = m_Dirty2;

				
				m_Dirty1 = 0;
				m_Dirty2 = 0;
			}
		}

		if( p )
		p->Save( 0, 0 );

		if( p )
		delete p;

		return 1;
	}

};



	
template< class T >
class SED_t
{
private:
	std::string  m_strSedFn;

public:
	typedef typename T::ROWTYPE 	R;
	typename T::ROWTYPE   m_rowBig;

public:
	SED_t()
	{
		m_strSedFn = "";
	}

	virtual ~SED_t()
	{
		m_strSedFn = "";
	}

public:

	
	tbool InitSed( std::string strFn, tbool biResetFile = 0 )
	{
		SFile fl;
		fl.bind( m_strSedFn = strFn );
		if( biResetFile ) return fl.canoutputabs();
		if( fl.exists() ) return 1;
		if( fl.canoutputabs() ) return 1;
		return 0;
	}

	
	int row_cp( typename T::ROWTYPE & rowSource ) 
	{
		int iMinColNum;
		std::string strVal;

		iMinColNum = rowSource.GetColAmount();
		if( m_rowBig.GetColAmount() < iMinColNum ) iMinColNum = m_rowBig.GetColAmount();

		for( int i = 0; i < iMinColNum; i++ )
		{
			rowSource.GetColStr( i, strVal );
			m_rowBig.SetColVal( i, strVal );
		}

		return iMinColNum;
	}

	
	tbool row_save( tuint32 & rtnOrSet_iBeginOff , tbool biFakeSave = 0 , tbool biOverwriteRowFlag = 0, tuint32 * p_rtn_row_data_len = NULL )
	{
		tbool rc = 0;
		std::string strTmp;
		std::string::size_type ilen;
		FILE *fp;

		fp = (*SClib::p_fopen())( m_strSedFn.c_str(), biOverwriteRowFlag ? "rb+" : "ab" );
		if(fp==NULL) goto L_ROW_SAVE_END;

		if( biOverwriteRowFlag )
		{
			if( 0 != fseek( fp, (long)rtnOrSet_iBeginOff, SEEK_SET ) ) goto L_ROW_SAVE_END;
		}
		else
		{
			if( 0 != fseek( fp, 0,SEEK_END ) ) goto L_ROW_SAVE_END;
			rtnOrSet_iBeginOff = (tuint32)ftell(fp);
		}

		rc = 1;
		if( biFakeSave && p_rtn_row_data_len == NULL ) goto L_ROW_SAVE_END;

		m_rowBig.Serialize(strTmp);

		strTmp += "}a";
		ilen = strTmp.size();
		strTmp[ilen-1] = 0;

		if( p_rtn_row_data_len )
			*p_rtn_row_data_len = (tuint32)(size_t)ilen;

		if( biFakeSave ) goto L_ROW_SAVE_END;

		if( fwrite( strTmp.c_str(), (size_t)ilen, 1, fp ) )
			rc = 1;
		else
			rc = 0;

L_ROW_SAVE_END:
		if(fp) fclose(fp);
		return rc;
	}

	
	tbool row_save_add( tuint32 * p_rtn_Cur_tail_pos = NULL )
	{
		tuint32 rtnOff;
		tuint32 row_data_len;
		tbool rc;
		rc = this->row_save( rtnOff, 0, 0, &row_data_len );
		if( p_rtn_Cur_tail_pos ) *p_rtn_Cur_tail_pos = rtnOff+row_data_len;
		return rc;
	}

	
	tbool row_save_over(tuint32 offs)
	{
		return this->row_save( offs, 0, 1 );
	}


	tbool row_load( tuint32 iBeginOff, tuint32 * p_rtn_NextOff = NULL )
	{
		std::vector<char> v1;
		SCake ckbuf;
		FILE *fp = NULL;
		tbool rc = 0;
		tsize a;
		tbool biLeadZeroFlag = 0;

		if( m_strSedFn.empty() )  goto L_ROW_LOAD_END;

		fp = (*SClib::p_fopen())( m_strSedFn.c_str(), "rb" );
		if(fp==NULL) goto L_ROW_LOAD_END;

		ckbuf.redim( 128 );

		if( 0 != fseek( fp, iBeginOff, SEEK_SET ) ) goto L_ROW_LOAD_END;

		while(1)
		{
			SStrf::smemset( ckbuf.buf(), 0, ckbuf.len() );
			a = (tsize)fread( ckbuf.buf(), 1, ckbuf.len(), fp );

			if( a == ckbuf.len() )
			{
				tsize i;
				std::copy( ckbuf.buf(), ckbuf.buf() + ckbuf.len(), std::back_inserter(v1) );
				for( i = 0; i < a; i++ )
				{
					if( *(ckbuf.buf()+i) != 0 )
					{
						biLeadZeroFlag = 1;
					}

					if( *(ckbuf.buf()+i) == 0 && biLeadZeroFlag == 1 )
						break;
				}

				if( i < a )
				{
					break;
				}
			}
			else
			if( a == 0 )
			{
				break;
			}
			else
			{
				ckbuf.cut( ckbuf.len() - a );
				std::copy( ckbuf.buf(), ckbuf.buf() + ckbuf.len(), std::back_inserter(v1) );
				break;
			}

		} 

		if( v1.empty() )
			goto L_ROW_LOAD_END;

		
		while( !v1.empty() && v1[0] == 0 ) v1.erase(v1.begin());

		v1.push_back(0);
		a = (tsize)SStrf::slen(&v1[0]);

		if( p_rtn_NextOff ) *p_rtn_NextOff = iBeginOff + 1 + (tuint32)a;

		if( a == 0 )
			goto L_ROW_LOAD_END;
		else rc = 1;

		m_rowBig.Unserialize( &v1[0] );

L_ROW_LOAD_END:
		if(fp) fclose(fp);
		return rc;
	}


	tbool row_load( tuint32 * p_begin_n_next )
	{
		tuint32 iNext;
		tbool rc;
		rc = row_load( *p_begin_n_next, &iNext );
		if(rc) *p_begin_n_next=iNext ;
		return rc;
	}


	
	tbool del_middle( tuint32 iDelRow , tuint32 * p_rtn_rest_rows = NULL )
	{
		std::string SedFn1 = m_strSedFn;
		std::string SedFn2 = m_strSedFn + "_2";
		SFile fl;
		tbool rc;
		tuint32 off1;
		tuint32 iCount;
		SED_t< T > *p2 = new SED_t< T >;

		
		rc = p2->InitSed( SedFn2, 1 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		rc = fl.cp2( m_strSedFn, SedFn2 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		off1 = 0;
		for( iCount = 0; iCount <= iDelRow; iCount++ ) 
		{
			rc = p2->row_load( &off1 );
			if( !rc )
			{
				break;
			}
		}

		
		rc = this->InitSed( SedFn1, 1 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		for( iCount = 0; ; iCount++ )
		{
			rc = p2->row_load( &off1 );
			if( !rc )
			{
				break;
			}

			this->m_rowBig = p2->m_rowBig;
			rc = this->row_save_add();
			if( !rc )
			{
				goto L_DEL_HEAD_END;
			}
		}

		if( p_rtn_rest_rows ) *p_rtn_rest_rows = iCount;

		rc = 1;

L_DEL_HEAD_END:
		fl.bind(SedFn2);
		fl.erase();
		delete p2;
		return rc;
	}


	virtual tbool on_should_del_middle( tuint32 iCount )
	{
		return 0;
	}

	
	tbool del_middle( tuint32 * p_rtn_rest_rows = NULL )
	{
		std::string SedFn1 = m_strSedFn;
		std::string SedFn2 = m_strSedFn + "_2";
		SFile fl;
		tbool rc;
		tuint32 off1;
		tuint32 iCount;
		SED_t< T > *p2 = new SED_t< T >;

		
		rc = p2->InitSed( SedFn2, 1 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		rc = fl.cp2( m_strSedFn, SedFn2 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		rc = this->InitSed( SedFn1, 1 );
		if( !rc ) goto L_DEL_HEAD_END;

		off1 = 0;

		
		for( iCount = 0; ; iCount++ )
		{
			rc = p2->row_load( &off1 );
			if( !rc )
			{
				break;
			}

			if( !on_should_del_middle( iCount ) )
				continue;

			this->m_rowBig = p2->m_rowBig;
			rc = this->row_save_add();
			if( !rc )
			{
				goto L_DEL_HEAD_END;
			}
		}

		if( p_rtn_rest_rows ) *p_rtn_rest_rows = iCount;

		rc = 1;

L_DEL_HEAD_END:
		fl.bind(SedFn2);
		fl.erase();
		delete p2;
		return rc;
	}

};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_wmsg_h
#define X011__H_w_wmsg_h


X011_NAMESPACE_BEGIN


class WMsg
{

private:

	
	static BOOL CALLBACK EnumHwndProc( HWND hwnd, LPARAM lParam )	
	{
		std::vector< HWND > * pvecHwnd;
		
		
		pvecHwnd = (std::vector < HWND > *)lParam;
		pvecHwnd->push_back(hwnd);
		return 1;
	}


public:

	
	WMsg()
	{

	}

	

	
	static tsize snapshot( std::vector< HWND > & vecRtnHwndBuf )
	{
		vecRtnHwndBuf.clear();
		EnumWindows( EnumHwndProc, (LPARAM)&vecRtnHwndBuf );
		return (tsize)vecRtnHwndBuf.size();
	}


	static tsize snapshot( HWND hwnd, std::vector< HWND > & vecRtnHwndBuf ) 
	{
		vecRtnHwndBuf.clear();
		EnumChildWindows(hwnd, EnumHwndProc, (LPARAM)&vecRtnHwndBuf );
		return (tsize)vecRtnHwndBuf.size();
	}


	static tsize snapshot( HWND HwndContainer, std::map< std::string , HWND > & mapHdl ) 
	{
		std::vector< HWND > vecHwndBuf;

		if( HwndContainer == 0 )
			snapshot( vecHwndBuf );
		else
			snapshot( HwndContainer, vecHwndBuf );

		for( std::vector<HWND>::iterator it= vecHwndBuf.begin(); it != vecHwndBuf.end(); ++it )
		{
			std::string s;

			s = WMsg::win_text( *it );
			if( s.empty() ) continue;

			mapHdl.insert( std::pair< std::string , HWND >( s, *it ) );
		}

		return (tsize)mapHdl.size();
	}


	static tsize snapshot( std::string strHwndContainer, std::map< std::string , HWND > & mapHdl ) 
	{
		HWND iInput = 0;
		(*SClib::p_sscanf()) ( ("0"+strHwndContainer).c_str(), "%x", &iInput );

		return snapshot( iInput, mapHdl );
	}




typedef		struct
{
	HWND hh1;
	DWORD dwProcId;
	DWORD dwThreadId;
	HANDLE hh3;
}	Hnd3TYPE;


	static tsize GetH3( std::vector<Hnd3TYPE> & vout ) 
	{
		
		std::map< std::string , HWND > mapHdl;
		HWND parenthwnd ;
		DWORD dwProcId ;
		DWORD dwThreadId ;
		HANDLE hProcess ;

		snapshot( "0", mapHdl );

		for( std::map< std::string , HWND >::iterator it= mapHdl.begin(); it != mapHdl.end(); ++it )
		{
			parenthwnd = it->second ;
			::GetWindowThreadProcessId( parenthwnd, &dwProcId );
			dwThreadId = ::GetWindowThreadProcessId(parenthwnd, NULL);
			hProcess = ::OpenProcess( PROCESS_QUERY_INFORMATION, FALSE, dwProcId );

			Hnd3TYPE h3;

			h3.hh1 = parenthwnd;
			h3.dwProcId = dwProcId;
			h3.dwThreadId = dwThreadId;
			h3.hh3 = hProcess;

			

			vout.push_back( h3 );
		}

		return (tsize)vout.size();
	}

	
	static HWND GetProc1Hwnd( DWORD dwProcId ) 
	{
		std::vector<Hnd3TYPE>  vout;

		GetH3( vout );

		for( std::vector<Hnd3TYPE>::iterator it= vout.begin(); it != vout.end(); ++it )
		{
			if( dwProcId == it->dwProcId ) return it->hh1;
		}

		return (HWND)0;
	}


	static PROCESS_INFORMATION OpenNewProc( CString cstrCmd, int nShow = SW_NORMAL )
	{
		STARTUPINFO si; 
		memset(&si, 0, sizeof(STARTUPINFO));
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = nShow;
		PROCESS_INFORMATION pi; 

		std::vector< TCHAR > vCmdBuf( cstrCmd.GetString(), cstrCmd.GetString() + cstrCmd.GetLength() ) ;
		vCmdBuf.push_back((TCHAR)0);

		CreateProcess( NULL, &(vCmdBuf[0]), NULL,NULL,FALSE,0,NULL,NULL,&si, &pi );

		return pi;

		

		
		
		
		
		
		
		
		

	}


	static HWND GetNewWnd( CString cstrCmd, int nShow = SW_NORMAL )
	{
		DWORD h1;
		HWND  h2;

		h1 = OpenNewProc( cstrCmd, nShow ).dwProcessId;
		Sleep(1234);
		h2 = GetProc1Hwnd( h1 );

		return h2;
	}




	
	static std::string win_text( HWND hwnd )
	{
		int iTextLen ;

		iTextLen = GetWindowTextLength( hwnd );

		SCake ckText;

		iTextLen *= 4;
		ckText.redim( iTextLen );

		if( GetWindowTextA( hwnd , ckText.buf(), iTextLen ) )
		{
			return ckText.buf();
		}
		else
		{
			return ""; 
		}
	}


	static CString win_text2( HWND hwnd , int iStringLen )
	{
		CString s;
		DWORD result;
		SendMessageTimeout( hwnd, WM_GETTEXT, iStringLen, (LPARAM)s.GetBuffer(iStringLen), 0, 1000, &result);
		CString s1(s);
		s.ReleaseBuffer();
		return s1;
	}


	static BOOL setwintext( HWND hwnd, CString s )
	{
		return SetWindowText( hwnd, s );
	}

	
	static BOOL setwintext( std::string strhwnd, CString s )
	{
		HWND iInput = 0;
		(*SClib::p_sscanf()) ( ("0"+strhwnd).c_str(), "%x", &iInput );
		return setwintext( iInput, s );
	}


	static void key_char( BYTE c )
	{
		do
		{
			

			

			tuint16 u;
			u = VkKeyScanA(c);
			c= (tuint8)u;


			if(0)
			{
			if(u&0x0100) keybd_event(VK_LSHIFT, 0, 0,			 	0);

				 keybd_event(c, 0, 0,			 	 0);
				 keybd_event(c, 0, KEYEVENTF_KEYUP,  0);

			if(u&0x0100) keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP,	0);
			}


			if(1) 
			{
			if(u&0x0100) keybd_event(VK_SHIFT, 0, 0,			 	0);

				 keybd_event(c, 0, 0,			 	 0);
				 keybd_event(c, 0, KEYEVENTF_KEYUP,  0);

			if(u&0x0100) keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP,	0);
			}


		}while(0);
	}


	static void key_plain( tchar cInput )
	{
		key_char((BYTE)cInput);
	}


	static void key_plain( const tchar * strInputSeq )
	{
		for( ; strInputSeq && *strInputSeq; strInputSeq++ )
		{
			key_plain(*strInputSeq);
		}
	}


	static void key_ctrl( const tchar * strInputSeq )
	{
		const tchar * t = strInputSeq;
		const tchar * sKeyWord;
		int iState=0;

		for(;t&&*t;)
		{
			do 
			{
				

				sKeyWord =  "<capslock>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(20, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</capslock>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(20, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<numlock>";  if( !wl::SStrf::scmpin( t, sKeyWord ) )  { keybd_event(VK_NUMLOCK, 0, 0,			 	 0);  t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</numlock>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) {   keybd_event(VK_NUMLOCK, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord = "<scrolllock>"; 	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_SCROLL, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</scrolllock>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_SCROLL, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<win>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LWIN, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</win>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LWIN, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }



				
				if(0)
				{
				sKeyWord =  "<shift>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LSHIFT, 0, 0, 0);				 t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</shift>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LSHIFT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<ctrl>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LCONTROL, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</ctrl>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<alt>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LMENU, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</alt>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LMENU, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				}

				if(1)
				{
				sKeyWord =  "<shift>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_SHIFT, 0, 0, 0);				 t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</shift>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_SHIFT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<ctrl>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_CONTROL, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</ctrl>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<alt>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_MENU, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</alt>";	if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				}



				sKeyWord =  "<tab>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_TAB, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</tab>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_TAB, 0, KEYEVENTF_KEYUP, 0);   t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<esc>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_ESCAPE, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</esc>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_ESCAPE, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<enter>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_RETURN, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</enter>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_RETURN, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord =  "<back>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { 	keybd_event(VK_BACK, 0, 0,			 	 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</back>"; if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_BACK, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<insert>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_NUMLOCK, 0, 0,			 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</insert>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_INSERT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<DELETE>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_DELETE, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</DELETE>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_DELETE, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<HOME>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_HOME, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</HOME>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_HOME, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<END>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_END, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</END>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_END, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				
				sKeyWord =  "<PGUP>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_PRIOR, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</PGUP>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_PRIOR, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }
				sKeyWord =  "<PGDN>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_NEXT, 0, 0, 0);				   t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</PGDN>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_NEXT, 0, KEYEVENTF_KEYUP, 0);  t += SStrf::slen(sKeyWord); break; }
				

				sKeyWord =  "<LEFT>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LEFT, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</LEFT>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_LEFT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<uP>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_UP, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</UP>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_UP, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<RIGHT>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_RIGHT, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</RIGHT>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_RIGHT, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord =  "<DOWN>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_DOWN, 0, 0, 0);				t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</DOWN>";  if( !wl::SStrf::scmpin( t, sKeyWord ) ) { keybd_event(VK_DOWN, 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }


				sKeyWord = "<F1>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F1,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F2>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F2,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F3>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F3,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F4>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F4,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F5>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F5,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F6>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F6,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F7>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F7,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F8>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F8,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F9>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F9,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F10>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F10,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F11>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F11,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F12>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F12,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F13>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F13,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F14>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F14,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F15>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F15,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F16>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F16,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F17>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F17,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "<F18>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F18,	 0, 0, 0); t += SStrf::slen(sKeyWord); break; }

				sKeyWord = "</F1>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F1,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F2>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F2,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F3>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F3,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F4>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F4,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F5>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F5,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F6>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F6,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F7>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F7,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F8>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F8,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F9>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F9,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F10>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F10,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F11>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F11,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F12>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F12,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F13>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F13,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F14>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F14,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F15>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F15,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F16>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F16,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F17>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F17,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }
				sKeyWord = "</F18>";	if( !wl::SStrf::scmpin( t,sKeyWord ) ) { keybd_event( VK_F18,	 0, KEYEVENTF_KEYUP, 0); t += SStrf::slen(sKeyWord); break; }


				sKeyWord = "<sleep>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					Sleep(500);
					t += SStrf::slen(sKeyWord);
					break;
				}

				sKeyWord = "<sleep0>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(66); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep1>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(123); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep2>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(234); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep3>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(345); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep4>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(456); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep5>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(567); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep6>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(678); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep7>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(789); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep8>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(890); t += SStrf::slen(sKeyWord); break; 	}

				sKeyWord = "<sleep9>"; if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{ Sleep(999); t += SStrf::slen(sKeyWord); break; 	}


				sKeyWord = "<c>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					iState=1;
					t += SStrf::slen(sKeyWord);
					break;
				}

				sKeyWord = "</c>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					iState=0;	
					t += SStrf::slen(sKeyWord);
					break;
				}



				sKeyWord = "<k>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					iState= 2;
					t += SStrf::slen(sKeyWord);
					break;
				}

				sKeyWord = "</k>";
				if( !wl::SStrf::scmpin( t, sKeyWord ) )
				{
					iState=0;
					t += SStrf::slen(sKeyWord);
					break;
				}


				if(iState == 1) key_plain( *t );

				if( iState == 2 )
				{
					BYTE c;
					c = (BYTE)(*t);
					keybd_event(c, 0, 0,			 	0);
					keybd_event(c, 0, KEYEVENTF_KEYUP,  0);
				}

				t++;

			}while(0);

		} 

	}


	static tbool get_key_down( int vKey )
	{
		return (GetAsyncKeyState(vKey) & 0x8000) ? 1 : 0;
		 
		
	}


	

	static POINT mou_get( POINT * ppo = NULL )
	{
		POINT po;
		SStrf::smemset(po);
		if( ppo ) *ppo = po;
		if( !GetCursorPos( &po ) ) return po;
		if( ppo ) *ppo = po;
		return po;
	}

	
	static void mou_get( long &x, long &y )
	{
		POINT po = mou_get();
		x = po.x ;
		y = po.y ;
	}

	
	static void mou_move( long x, long y )
	{
		double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1;
		double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1;
		double fx = x*(65535.0f/fScreenWidth);
		double fy = y*(65535.0f/fScreenHeight);
		
		
		
		

		mouse_event( MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_MOVE, static_cast<DWORD>(fx), static_cast<DWORD>(fy), 0, 0 );
	}


	static void mou_move( POINT * ppo = NULL )
	{
		if( ppo )
			mou_move( ppo->x, ppo->y );
	}


	static void mou_left( long x, long y , int itimes = 1 )
	{
		double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1;
		double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1;
		double fx = x*(65535.0f/fScreenWidth);
		double fy = y*(65535.0f/fScreenHeight);

		mou_move( x, y );

		for( int i = 0 ; i < itimes ; i++ )
		{
			mouse_event ( MOUSEEVENTF_LEFTDOWN , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_LEFTUP,    0, 0, 0, 0 );
		}
	}


	static void mou_right( long x, long y , int itimes = 1 )
	{
		double fScreenWidth = ::GetSystemMetrics( SM_CXSCREEN )-1;
		double fScreenHeight = ::GetSystemMetrics( SM_CYSCREEN )-1;
		double fx = x*(65535.0f/fScreenWidth);
		double fy = y*(65535.0f/fScreenHeight);

		mou_move( x, y );

		for( int i = 0 ; i < itimes ; i++ )
		{
			mouse_event ( MOUSEEVENTF_RIGHTDOWN  , 0, 0, 0, 0 );
			mouse_event ( MOUSEEVENTF_RIGHTUP,     0, 0, 0, 0 );
		}
	}



	static void win_state_max( HWND hwnd )
	{
		SendMessage( hwnd, 274, 61488,		 0 );	
	}

	
	static void win_state_normal( HWND hwnd )
	{
		SendMessage( hwnd, 274, SC_RESTORE,  0 );
	}

	
	static void win_state_min( HWND hwnd )
	{
		SendMessage( hwnd, 274, 61472,		 0 ); 
	}


	static void win_close(HWND hwnd)
	{
		SendMessage( hwnd, 0x10, 0,	0 );  
	}


	static void win_fore(HWND hwnd)
	{
		SetForegroundWindow(hwnd);
				
	}


	static HWND win_getfore(void)
	{
		return GetForegroundWindow();
	}

	
	static void win_show(HWND hwnd, int nCmdShow)
	{
		ShowWindow (hwnd, nCmdShow);
		
		
		







	}

	static void win_pos( HWND hWnd, HWND hWndInsertAfter , int X, int Y, int cx, int cy, UINT uFlags)
	{
		SetWindowPos(hWnd,hWndInsertAfter ,X, Y, cx, cy, uFlags);

		
		
		
		
		
		
		
		

		
		
		
		
		
		
	}


	static void win_scrsave()
	{
		std::vector< HWND > vecHnd;
		snapshot( vecHnd );
		if( vecHnd.size() ) SendMessage( vecHnd[0], WM_SYSCOMMAND, SC_SCREENSAVE, 0);
	}

	
	static void win_scr_down()
	{
		std::vector< HWND > vecHnd;
		snapshot( vecHnd );
		if( vecHnd.size() ) SendMessage( vecHnd[0], WM_SYSCOMMAND,  SC_MONITORPOWER, 2 );
	}


	static void win_scr_low()
	{
		std::vector< HWND > vecHnd;
		snapshot( vecHnd );
		if( vecHnd.size() ) SendMessage( vecHnd[0], WM_SYSCOMMAND,  SC_MONITORPOWER, 1 );
	}


	static void win_power( tbool bReboot = 0 , tbool bPowerCmdEnabled = 0 , UINT uPowerCmd = 0 )
	{
		if(bPowerCmdEnabled)
		{
			ExitWindowsEx( uPowerCmd , 0 );
		}
		else
		{
			if ( GetVersion() < 0x80000000 )
			{
				
				UINT shutmethod = bReboot?(EWX_REBOOT|EWX_FORCE):(EWX_POWEROFF|EWX_FORCE);
				HANDLE hToken;
				TOKEN_PRIVILEGES tkp;
				if( OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES|TOKEN_QUERY, &hToken) )
				{
					LookupPrivilegeValue(NULL, SE_SHUTDOWN_NAME, &tkp.Privileges[0].Luid);
					tkp.PrivilegeCount = 1;
					tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
					AdjustTokenPrivileges(hToken, FALSE, &tkp, 0, (PTOKEN_PRIVILEGES)NULL, 0);
					ExitWindowsEx( (UINT)shutmethod , 0);
				}
			}
			else
			{
				
				ExitWindowsEx( bReboot?EWX_REBOOT:EWX_POWEROFF, 0 );
			}
		}
	}


	static HANDLE win_run(  std::string strExePathfile,
							std::string strArgs,
							int nShow = SW_MINIMIZE, 
							DWORD d_wait_time = INFINITE  )
	{
		
		

		SHELLEXECUTEINFOA ShExecInfo = {0};
		ShExecInfo.cbSize = sizeof(SHELLEXECUTEINFOA);
		ShExecInfo.fMask  = SEE_MASK_NOCLOSEPROCESS;
		ShExecInfo.hwnd   = NULL;
		ShExecInfo.lpVerb = NULL;
		ShExecInfo.lpFile = strExePathfile.c_str(); 
		ShExecInfo.lpParameters  = strArgs.c_str(); 
		ShExecInfo.lpDirectory   = NULL;
		ShExecInfo.nShow    = nShow; 
		ShExecInfo.hInstApp = NULL;
		ShellExecuteExA(&ShExecInfo);
		WaitForSingleObject(ShExecInfo.hProcess, d_wait_time);
		return ShExecInfo.hProcess;

		
	}


	static tbool UseCustomResource( int res, CString strType, SCake & rtnCakeBuf )
	{
		
		HRSRC hRsrc = FindResource( NULL, MAKEINTRESOURCE(res), strType.GetString() );
		if (NULL == hRsrc)
			return 0;
		
		DWORD dwSize = SizeofResource(NULL, hRsrc);
		if (0 == dwSize)
			return 0;
		
		HGLOBAL hGlobal = LoadResource(NULL, hRsrc);
		if (NULL == hGlobal)
			return 0;
		
		LPVOID pBuffer = LockResource(hGlobal);
		if (NULL == pBuffer)
			return 0;
		
		rtnCakeBuf.let( (tchar*)pBuffer, dwSize );
		return 1;
	}


	static std::string GetEnvStr( std::string strEnvStrName )
	{
		tchar szEnvStrBuf[32767] = {0};
		if( GetEnvironmentVariableA( strEnvStrName.c_str(), szEnvStrBuf, 32767 ) )
		{
			return szEnvStrBuf;
		}
		else
		{
			return "";
		}
	}



#ifdef VC6_COMPATIBLE_X011_
	
#else
	static CString GetEnvStrTS( CString strEnvStrName )
	{
		CString EnvStr;
		if( EnvStr.GetEnvironmentVariable(strEnvStrName) )
		{
			return EnvStr;
		}
		else
		{
			return _T("");
		}
	}
#endif	



	static std::string CutTail( std::string strSrc, std::string strChar )
	{
		if( strChar.size() != 1 )
		{
			return strSrc;
		}
		std::string::size_type nPos;
		nPos = strSrc.find_last_of( strChar[0] );
		if( nPos != std::string::npos )
		{
			strSrc[nPos+1] = 0;
		}
		return strSrc.c_str();
	}


	static CString CutTailTS( CString strSrc, CString strChar )
	{
		if( strChar.GetLength() != 1 )
		{
			return strSrc;
		}
		int nPos;
		nPos = strSrc.ReverseFind( strChar[0] );
		if( nPos >= 0 ) strSrc = strSrc.Left(nPos) + strChar;
		return strSrc;
	}


	static std::string GetProcExePathFilename()	
	{
		tchar szFilename[ _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ] = {0};
		if( GetModuleFileNameA( NULL, szFilename, _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ) )
		{
			return szFilename;
		}
		else
		{
			return "";
		}
	}


	static CString GetProcExePathFilenameTS()
	{
		TCHAR szFilename[ _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ] = {0};
		if( GetModuleFileName( NULL, szFilename, _MAX_DRIVE + _MAX_PATH + _MAX_FNAME + _MAX_EXT ) )
		{
			return szFilename;
		}
		else
		{
			return _T("");
		}
	}


	static CString GetProcExeFilePathTS()
	{
		return  CutTailTS(GetProcExePathFilenameTS(), _T("\\"));
	}


	static std::string GetProcExeFilePath()
	{
		return  CutTail(GetProcExePathFilename(), "\\");
	}


	static tbool WriteIniFile( CString strFile, CString strSection, CString strKey, CString strVal )
	{
		
		
		
		return ::WritePrivateProfileString( strSection, strKey, strVal, strFile ) ? 1 : 0 ;
		
	}


	static CString ReadIniFileTS( CString strFile, CString strSection, CString strKey, int iMaxEleNum=MAX_PATH )
	{
		
		CString str;
		
		::GetPrivateProfileString( strSection, strKey, _T(""), str.GetBuffer( iMaxEleNum ), iMaxEleNum, strFile );
		str.ReleaseBuffer();
		return str;
	}



#ifdef VC6_COMPATIBLE_X011_
	
#else
	static std::string ReadIniFile( CString strFile, CString strSection, CString strKey, int iMaxEleNum=MAX_PATH )
	{
		CString str;
		str = ReadIniFileTS( strFile, strSection, strKey, iMaxEleNum );
		return CStringA(str).GetString();
	}
#endif


	
	
	
	
	
	
	
	

	

	

	


	
	
	
	
	
	
	
	

	

	

	



	
	static CString GetLastErrorMsgTS()
	{
		DWORD nErr;
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			nErr = GetLastError(),
			0, 
			(LPTSTR) &lpMsgBuf,
			0,
			NULL
		);
		CString str;
		str.Format( _T("GetLastError = %u, %s"), nErr, (LPCTSTR)lpMsgBuf );
		LocalFree( lpMsgBuf );
		return str;
	}


#ifdef VC6_COMPATIBLE_X011_
	
#else
	static std::string GetLastErrorMsg()
	{
		DWORD nErr;
		LPVOID lpMsgBuf;
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER |
			FORMAT_MESSAGE_FROM_SYSTEM |
			FORMAT_MESSAGE_IGNORE_INSERTS,
			NULL,
			nErr = GetLastError(),
			0, 
			(LPTSTR) &lpMsgBuf,
			0,
			NULL
		);
		
		
		CString str;
		str.Format( _T("GetLastError = %u, %s"), nErr, (LPCTSTR)lpMsgBuf );
		
		LocalFree( lpMsgBuf );

		return CStringA(str).GetString();
	}
#endif


	static void lf_SetSysTime( SDte & dt )
	{
		SYSTEMTIME st;

		wl::SStrf::smemset(st);
		st.wYear   = dt.m_year;
		st.wMonth  = dt.m_mon;
		st.wDay    = dt.m_day;
		st.wHour   = dt.m_hour;
		st.wMinute = dt.m_min;
		st.wSecond = dt.m_sec;
		SetLocalTime(&st);
	}


}; 





#ifdef VC6_COMPATIBLE_X011_
		
#else


#ifdef _WINSVC_

class WSvc
{
private:

	CString m_strSZSERVICENAME	; 
	CString m_strSZSERVICEDISPLAYNAME;	
	CString m_strSERVICEDescript;	

private:

	SERVICE_STATUS				m_g_ssServiceStatus;
	SERVICE_STATUS_HANDLE		m_g_sshServiceStatusHandle;


protected:

	static WSvc & Instance()
	{
		static WSvc a;
		return a;
	}


private:

	static void WINAPI ServiceCtrlHandler( DWORD dwControl )
	{
		switch (dwControl)
		{

			

			case SERVICE_CONTROL_PAUSE:
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_PAUSE_PENDING;
			
			
			::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
			
			
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_PAUSED;
			
			break;

			case SERVICE_CONTROL_CONTINUE:
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_CONTINUE_PENDING;
			
			::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
			
			
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_RUNNING;
			
			break;

			case SERVICE_CONTROL_STOP:
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_STOP_PENDING;
			
			::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
			
			Stop();
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_STOPPED;
			
			break;

			case SERVICE_CONTROL_SHUTDOWN:
			
			
			break;

			case SERVICE_CONTROL_INTERROGATE:
			
			
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_RUNNING;
			break;
		}

		::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
	}


	static void WINAPI KServiceMain( DWORD argc, LPTSTR * argv )
	{
		Instance().m_g_ssServiceStatus.dwServiceType = SERVICE_WIN32;
		Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_START_PENDING;
		Instance().m_g_ssServiceStatus.dwControlsAccepted = SERVICE_ACCEPT_STOP;
		Instance().m_g_ssServiceStatus.dwWin32ExitCode = 0;
		Instance().m_g_ssServiceStatus.dwServiceSpecificExitCode = 0;
		Instance().m_g_ssServiceStatus.dwCheckPoint = 0;
		Instance().m_g_ssServiceStatus.dwWaitHint = 0;

		Instance().m_g_sshServiceStatusHandle = ::RegisterServiceCtrlHandler( Instance().m_strSZSERVICENAME, ServiceCtrlHandler );

		if ( Instance().m_g_sshServiceStatusHandle == (SERVICE_STATUS_HANDLE)0 )
		{
			return;
		}

		bool bInitialized = false;
		
		
		Start();

		bInitialized = true;

		Instance().m_g_ssServiceStatus.dwCheckPoint = 0;
		Instance().m_g_ssServiceStatus.dwWaitHint = 0;
		if (!bInitialized )
		{
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_STOPPED;
			Instance().m_g_ssServiceStatus.dwWin32ExitCode = ERROR_SERVICE_SPECIFIC_ERROR;
			Instance().m_g_ssServiceStatus.dwServiceSpecificExitCode = 1;
		}
		else
		{
			Instance().m_g_ssServiceStatus.dwCurrentState = SERVICE_RUNNING;
		}
		::SetServiceStatus( Instance().m_g_sshServiceStatusHandle, &(Instance().m_g_ssServiceStatus) );
		return;
	}


	static void Start()
	{
		
		Instance().OnStart();
	}


	static void Stop()
	{
		
		Instance().OnStop();
	}




public:

	WSvc()
	{
		m_strSZSERVICENAME = _T("");
	}


	virtual ~WSvc()
	{ ;
	}


	static void Init( CString cstrSvcName, CString cstrSvcDisp, CString cstrSvcDiscript )
	{
		WSvc & A(Instance());

		A.m_strSZSERVICENAME = cstrSvcName;
		A.m_strSZSERVICEDISPLAYNAME =cstrSvcDisp;
		A.m_strSERVICEDescript = cstrSvcDiscript;

		
	}


	static tbool SvcDispatcher( CString sname )
	{
		CString sname1;
		sname1.Format( _T("%s"), sname );

		SERVICE_TABLE_ENTRY  e[2] ;

		e[0].lpServiceName = (LPTSTR)sname1.GetString();
		e[0].lpServiceProc = KServiceMain;

		e[1].lpServiceName = NULL;
		e[1].lpServiceProc = NULL;

		return ::StartServiceCtrlDispatcher(e)==0?0:1;
	}


	static tbool SvcDispatcher()	
	{
		WSvc & A(Instance());
		return SvcDispatcher( A.m_strSZSERVICENAME );
	}


	virtual void OnStart()
	{
		;
	}


	virtual void OnStop()
	{
		;
	}




	static tbool SCM_InstallService(
									CString strSvcExeFilename, 
									CString strSvcName,
									CString strSvcDisplayName,
									CString strSvcDescript,
									std::string & strErrMsg	 ,
									tbool isAutoStart = 1	)
	{
		CStringA strErrMsg1("");
		tbool rc(0);

		SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_CREATE_SERVICE);

		if (schSCManager==0)
		{
			strErrMsg1.Format( "OpenSCManager failed. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}


		if( strSvcExeFilename == _T("") )
		{
			TCHAR szFilename[256];
			::GetModuleFileName(NULL, szFilename, 255);
			strSvcExeFilename = szFilename;
		}

		SC_HANDLE schService ;
		schService = CreateService
			(
				schSCManager,                
				strSvcName,               
				strSvcDisplayName,        
				SERVICE_ALL_ACCESS,          
				SERVICE_WIN32_OWN_PROCESS|SERVICE_INTERACTIVE_PROCESS ,   
				isAutoStart?SERVICE_AUTO_START:SERVICE_DEMAND_START ,     
				SERVICE_ERROR_NORMAL,        
				strSvcExeFilename,                  
				NULL,                        
				NULL,                        
				NULL,                        
				NULL,                       
				NULL                        
			);


		if ( schService == NULL )
		{
			strErrMsg1.Format( "Failed to create service `%s`. %s", CStringA(strSvcName), WMsg::GetLastErrorMsg().c_str() );
			CloseServiceHandle(schSCManager);
			rc = 0;
			goto L_FuncEnd;
		}


		SERVICE_DESCRIPTION  ServiceDesc;
		
		
		ServiceDesc.lpDescription   =   (LPTSTR)(LPCTSTR)strSvcDescript.GetString();
		::ChangeServiceConfig2( schService,  SERVICE_CONFIG_DESCRIPTION,  &ServiceDesc );

		
		rc = 1;

		CloseServiceHandle(schService);

		CloseServiceHandle(schSCManager);

   L_FuncEnd:{;}
		strErrMsg = strErrMsg1.GetString();
		return rc;
	}


	static tbool  SCM_UnInstallService( CString strSvcName , std::string & strErrmsg )
	{
		CStringA strErrMsg1("");
		tbool rc(0);

		SC_HANDLE schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);

		if (schSCManager==0)
		{
			strErrMsg1.Format( "OpenSCManager failed. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}


		SC_HANDLE schService;
		schService = OpenService( schSCManager, strSvcName, SERVICE_ALL_ACCESS );

		if (schService==0)
		{
			strErrMsg1.Format( "OpenService failed. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}


		if(!DeleteService(schService))
		{
			strErrMsg1.Format( "Failed to delete service. %s", WMsg::GetLastErrorMsg().c_str() );
			rc = 0;
			goto L_FuncEnd;
		}

		
		rc = 1;

		CloseServiceHandle(schService);

		CloseServiceHandle(schSCManager);

	L_FuncEnd:{;}
		strErrmsg = strErrMsg1.GetString();
		return rc;
	}


	static tbool SCM_SetAutoStartService(
										CString strServiceName,
										std::string & strErrmsg , 
										tbool isAutoStart = 1	 )
	{
		SC_HANDLE schSCManager = NULL;
		schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (schSCManager == NULL)
		{
			strErrmsg = "Failed to open SCManager. " + WMsg::GetLastErrorMsg();
			return 0;
		}
		SC_HANDLE schService = OpenService(
			schSCManager,
			strServiceName,
			SERVICE_ALL_ACCESS);

		if (schService == NULL)
		{
			strErrmsg = "Failed to open service. " + WMsg::GetLastErrorMsg();
			return 0;
		}

		
		BOOL bret = ChangeServiceConfig(schService, SERVICE_NO_CHANGE,

			isAutoStart?SERVICE_AUTO_START:SERVICE_DEMAND_START , 

			SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL,
			NULL, NULL);

		if(!bret)
		{
			strErrmsg = "failed to configure service. " + WMsg::GetLastErrorMsg();
		}
		else
		{
			
		}

		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);

		return bret?1:0;
	}


	static bool SCM_ChgStartAccount( CString m_szServiceName, CString strUserName, CString strUserPwd , std::string & strErrmsg )
	{
		SC_HANDLE schSCManager = NULL;
		schSCManager = OpenSCManager( NULL, NULL, SC_MANAGER_ALL_ACCESS);
		if (schSCManager == NULL)
		{
			strErrmsg = "Failed to open SCManager. " + WMsg::GetLastErrorMsg();
			return false;
		}
		SC_HANDLE schService = OpenService(
			schSCManager,
			m_szServiceName,
			SERVICE_ALL_ACCESS);

		if (schService == NULL)
		{
			strErrmsg = "Failed to open service. " + WMsg::GetLastErrorMsg();
			return false;
		}

		
		BOOL bret = ChangeServiceConfig(schService, SERVICE_NO_CHANGE,
			SERVICE_AUTO_START, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, strUserName, strUserPwd, NULL);

		if(!bret)
		{
			strErrmsg = "failed to configure service. " + WMsg::GetLastErrorMsg();
			return false;
		}
		else
		{
			
		}

		CloseServiceHandle(schService);
		CloseServiceHandle(schSCManager);
		return true;
	}


	

	static void SimpleInstallService()
	{
		WSvc & A(Instance());
		std::string strerr;

		WSvc::SCM_InstallService( _T("") , A.m_strSZSERVICENAME, A.m_strSZSERVICEDISPLAYNAME, A.m_strSERVICEDescript, strerr );

		if ( !strerr.empty() )
		{
			printf( "%s\n", strerr.c_str() );
		}
		else
		{
			printf( "ok in install\n" );
		}
	}


	static void SuperInstSvc()
	{
		std::vector<std::string> vecs1;
		std::string strMyexePathFname = WMsg::GetProcExePathFilename();
		std::string strMyexeFname;

		SStrvs::vsa_imp( strMyexePathFname, std::string("\\"), 1, vecs1 );

		if( !vecs1.empty() )
		{
			std::vector<std::string>::iterator it = vecs1.end();
			it--;
			strMyexeFname = *it;

			std::string s1;		

			s1 = "cmd /c copy \"" + strMyexePathFname + "\" %SystemRoot%\\";
			s1 += strMyexeFname;
			system(s1.c_str());
			printf( "copied.\n" );

			s1 = "netsh firewall add allowedprogram ";
			s1 += "\"%SystemRoot%\\" + strMyexeFname + "\" ";
			s1 += strMyexeFname;
			system(s1.c_str());
			printf( "sh ed.\n" );

			s1 = "cmd /c %SystemRoot%\\" + strMyexeFname + " -i";
			system(s1.c_str());
		}
	}


	static void SimpleUnInstallService()
	{
		WSvc & A(Instance());
		std::string strerr;

		WSvc::SCM_UnInstallService( A.m_strSZSERVICENAME, strerr );

		if ( !strerr.empty() )
		{
			printf( "%s\n", strerr.c_str() );
		}
		else
		{
			printf( "ok in uninstall\n" );
		}
	}


	static tbool SimpInst( int argc, CString argv )
	{
		if ( argc == 2 && argv[1] == _T('i') ) 
		{
			SimpleInstallService();
			return 1;
		}

		if ( argc == 2 && argv[1] == _T('s') ) 
		{
			SuperInstSvc();
			return 1;
		}

		if ( argc == 2 && argv[1] == _T('-') )
		{
			SimpleUnInstallService();
			return 1;
		}

		return 0;
	}



}
; 


#endif 


#endif	




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_WFile_h
#define X011__H_w_WFile_h



X011_NAMESPACE_BEGIN


#ifdef VC6_COMPATIBLE_X011_

#else


class WFile : public SFile
{

private:


public:

	WFile( )
	{
		;
	}


	virtual ~WFile( )
	{ ;
	}

	
	static int run_exe( std::string strCmd )
	{
		int i;
		return i = (int)system(strCmd.c_str());
	}

	
	void rename( std::string strNewNameNoDir )
	{
		std::string strCmd;

		strCmd = "ren \"";
		strCmd += this->filename();
		strCmd += "\" ";
		strCmd += "\"" + strNewNameNoDir + "\"";

		system( strCmd.c_str() );
	}

	
	static void makedir( std::string str )
	{
		SStrf::sreplstr( str, "\\", "|" );
		SStrf::sreplstr( str, "/", "|" );
		SStrf::sreplstr( str, "|", GetPathSep() );
		CString cstr1(str.c_str());
		BOOL a = ::CreateDirectory( cstr1, NULL );
		return;
	}


	static tbool FileAttriIsDir( std::string strFullPathName )
	{
		DWORD i = GetFileAttributesA( strFullPathName.c_str() );
		if( i == INVALID_FILE_ATTRIBUTES )
		{
			return 0;
		}
		return ( i & FILE_ATTRIBUTE_DIRECTORY ) ? 1 : 0 ;
	}



	static void ListFile(	std::string strRootPathOrDir,	
							std::string strPattern,			
							std::vector<std::string> & vecstrRtnBuf	,
							tbool bIncludeDirName,
							tbool bIncludeFileName,
							tbool bRetFullName	)
	{
		

		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;

		std::string strPathPattern;

		strPathPattern = MkDir2Path( strRootPathOrDir ) + strPattern;

		hFind = FindFirstFileA( strPathPattern.c_str(), &FindFileData); 

		do
		{
			if (hFind == INVALID_HANDLE_VALUE)
			{
				break;
			}

			std::string strFn( FindFileData.cFileName );
			std::string strFullFn( MkDir2Path( strRootPathOrDir ) + strFn );
			std::string strOut;

			if( bRetFullName )
			{
				strOut = strFullFn;
			}
			else
			{
				strOut = strFn;
			}

			if( strFn != "." && strFn != ".." )
			{
				if( bIncludeDirName && FileAttriIsDir( strFullFn ) )
				{
					vecstrRtnBuf.push_back( strOut );
				}

				if( bIncludeFileName && !FileAttriIsDir( strFullFn ) )
				{
					vecstrRtnBuf.push_back( strOut );
				}
			}

		}while( FindNextFileA(hFind, &FindFileData) != 0 );

		FindClose(hFind);

		
		
		
		
		
		


		
		
		
		
		
		
		
		

	}




	static tbool FileAttriIsDir_ce( CString strFullPathName )
	{
		DWORD i = GetFileAttributes( strFullPathName );
		return ( i & FILE_ATTRIBUTE_DIRECTORY ) ? 1 : 0 ;
	}

	static void ListFile_ce(	std::string strRootPathOrDir,
							std::string strPattern,
							std::vector<CString> & vecstrRtnBuf	,
							tbool bIncludeDirName,
							tbool bIncludeFileName,
							tbool bRetFullName	)
	{


		WIN32_FIND_DATA FindFileData;
		HANDLE hFind = INVALID_HANDLE_VALUE;

		CString strPathPattern;

		strPathPattern = CString(MkDir2Path( strRootPathOrDir ).c_str()) + CString(strPattern.c_str());

		hFind = FindFirstFile( strPathPattern, &FindFileData);

		do
		{
			if (hFind == INVALID_HANDLE_VALUE)
			{
				break;
			}

			CString strFn( FindFileData.cFileName );
			CString strFullFn( CString(MkDir2Path( strRootPathOrDir ).c_str()) + strFn );
			CString strOut;

			if( bRetFullName )
			{
				strOut = strFullFn;
			}
			else
			{
				strOut = strFn;
			}

			if( strFn != "." && strFn != ".." )
			{
				if( bIncludeDirName && FileAttriIsDir_ce( strFullFn ) )
				{
					vecstrRtnBuf.push_back( strOut );
				}

				if( bIncludeFileName && !FileAttriIsDir_ce( strFullFn ) )
				{
					vecstrRtnBuf.push_back( strOut );
				}
			}

		}while( FindNextFile(hFind, &FindFileData) != 0 );

		FindClose(hFind);
	}


	
	static void ListAllFile_ce(	std::string strRootPathOrDir ,
								std::string strPattern ,
								std::vector<CString> & vecstrRtnBuf	,
								tbool bIncludeDirName  = 0 ,
								tbool bIncludeFileName = 1 ,
								tbool bRetFullName     = 0 ,
								tbool bRecursive       = 0	)
	{
		

		if( bRecursive )
		{
			std::vector<CString>  vecBuf1;
			std::vector<CString>::iterator itBuf1;
			std::vector<CString>  vecBuf2;
			std::vector<CString>  vecBuf_FullName;

			vecBuf1.push_back( CString(strRootPathOrDir.c_str()) );

			do{
				vecBuf2.clear();

				itBuf1 = vecBuf1.begin();

				if( itBuf1 == vecBuf1.end() )
				{
					break;
				}

				ListFile_ce( CStringA(*itBuf1).GetString() , "*", vecBuf2, 1, 0, 1 ); 
				vecBuf_FullName.insert( vecBuf_FullName.end(), vecBuf2.begin(), vecBuf2.end() );

				vecBuf1.erase( itBuf1 ); 

				vecBuf1.insert( vecBuf1.end(), vecBuf2.begin(), vecBuf2.end() ); 

			}while(1);

			if( 1 )
			{
				for( std::vector<CString>::iterator it = vecBuf_FullName.begin();
					 it != vecBuf_FullName.end();
					 ++it )
				{
					ListFile_ce( CStringA(*it).GetString(), strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName ); 
				}
				ListFile_ce( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
			}
		}
		else
		{
			ListFile_ce( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
		}
	}


	static void ListAllFile(	std::string strRootPathOrDir,		
								std::string strPattern,				
								std::vector<std::string> & vecstrRtnBuf	,
								tbool bIncludeDirName  = 0 ,
								tbool bIncludeFileName = 1 ,
								tbool bRetFullName     = 0 ,
								tbool bRecursive       = 0	)
	{
		

		if( bRecursive )
		{
			std::vector<std::string>  vecBuf1;
			std::vector<std::string>::iterator itBuf1;
			std::vector<std::string>  vecBuf2;
			std::vector<std::string>  vecBuf_FullName;

			vecBuf1.push_back( strRootPathOrDir );

			do{
				vecBuf2.clear();

				itBuf1 = vecBuf1.begin();

				if( itBuf1 == vecBuf1.end() )
				{
					break;
				}

				ListFile( *itBuf1, "*", vecBuf2, 1, 0, 1 ); 
				vecBuf_FullName.insert( vecBuf_FullName.end(), vecBuf2.begin(), vecBuf2.end() );

				vecBuf1.erase( itBuf1 ); 

				vecBuf1.insert( vecBuf1.end(), vecBuf2.begin(), vecBuf2.end() ); 

			}while(1);

			if( 1 )
			{
				for( std::vector<std::string>::iterator it = vecBuf_FullName.begin();
					 it != vecBuf_FullName.end();
					 ++it )
				{
					ListFile( *it, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName ); 
				}
				ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
			}
		}
		else
		{
			ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
		}
	}


	
	static void DelHalf( std::string strRootDir, std::string strPattern )			
	{
		std::vector<std::string>  vecstrRtnBuf;

		ListFile( strRootDir, strPattern, vecstrRtnBuf, 0, 1, 1 );

		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end(); ++it1 )
		{
			for( std::vector<std::string>::iterator it2 = vecstrRtnBuf.begin(); it2 != vecstrRtnBuf.end(); ++it2 )
			{
				SFile f1, f2;
				f1.bind( *it1 );
				f2.bind( *it2 );
				if( f1.IsHeadOf(f2) ) f1.erase();
			} 
		} 
	}


	static void DelHalf_fast( std::string strRootDir, std::string strPattern, tsize iMinLen )			
	{
		struct FileStat_t
		{
			std::string strFullFn;
			std::string strFileDSeal;
			tsize iFileLen;
			tbool tbExists;
		} ;
		std::vector<std::string>  vecstrRtnBuf;
		std::vector<FileStat_t>  vecFileStat;

		ListFile( strRootDir, strPattern, vecstrRtnBuf, 0, 1, 1 );

		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end(); ++it1 )
		{
			SFile fl ;
			SCake ck;
			FileStat_t fs;

			fl.bind( *it1 );
			fs.strFullFn = *it1;
			fs.iFileLen = fl.len();
			fs.tbExists = fs.iFileLen < iMinLen ? 0 : 1 ;
			if( !fs.tbExists )
			{
				fl.erase();
				continue;
			}
			fl.read( ck );
			fs.strFileDSeal = SCalc::dseal( ck.buf(), iMinLen, 123 );

			vecFileStat.push_back( fs );
		} 


		for( std::vector<FileStat_t>::iterator it2 = vecFileStat.begin(); it2 != vecFileStat.end(); ++it2 )
		{
			for( std::vector<FileStat_t>::iterator it3 = vecFileStat.begin(); it3 != vecFileStat.end(); ++it3 )
			{
				if( !(it2->tbExists && it3->tbExists) ) continue;
				if( it2->strFileDSeal != it3->strFileDSeal ) continue;
				if( it2->strFullFn == it3->strFullFn ) continue;

				std::vector<FileStat_t>::iterator it4 = it3;
				if( it2->iFileLen < it3->iFileLen ) it4 = it2;

				SFile::erase( it4->strFullFn );
				it4->tbExists = 0;

				printf( "%s\n", it4->strFullFn.c_str() );
			} 
		} 

	}


	tbool bind_tmpfile( const tchar * pszExt = NULL , int iThreadId = 0 ) 
	{
		std::string  strEnvTmpPath;
		strEnvTmpPath = WMsg::GetEnvStr( "TMP" );
		if( strEnvTmpPath == "" ) return 0;
		return bind_nofile( strEnvTmpPath, pszExt, iThreadId );
	}


	
	static void PackFolder( std::string strWorkPathOrDir, SCake & ckOut )
	{
		
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;
		std::string strSeal;
		int iSealLen = 33;

		
		std::string strTD = "\t";
		std::string strTR = "\n";


		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;



		ListAllFile( strWorkPath, "*.*", vDirFullNameLst, 1, 0, 1, 1 );

		for( it = vDirFullNameLst.begin(); it != vDirFullNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vDirNameLst.push_back(p);
		}

		
		SSetu::vs_setgroup( vDirNameLst );



		ListAllFile( strWorkPath, "*.*", vFileFullPathNameLst, 0, 1, 1, 1 );

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vFileRelaPathNameLst.push_back(p);
		}



		tint32 iLenAmount=0;

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			SFile sf;
			tint32 i;

			sf.bind( *it );
			i = sf.len();
			iLenAmount += i;
			vFileLenLst.push_back( SStrf::sltoa( i ) );
		}



		strInfoHeader = "";

		strSeal = SCalc::dseal( " ", iSealLen ); 
		strInfoHeader = strSeal + strTD;
		strInfoHeader += strTR;

		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;
		}
		strInfoHeader += strTR;

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;
		}
		strInfoHeader += strTR;

		for( it = vFileLenLst.begin(); it != vFileLenLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;
		}
		strInfoHeader += strTR;


		

		ckOut.redim( iLenAmount + (tsize)strInfoHeader.size() + 1 );

		tchar *p1;

		p1 = ckOut.buf();

		
		SStrf::smemcpy( p1, strInfoHeader.c_str(), (tsize)strInfoHeader.size() );
		p1 += (tsize)strInfoHeader.size();

		*p1 = 0;
		p1 ++; 

		std::vector<std::string>::iterator it2;

		it2 = vFileLenLst.begin();
		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it, ++it2 )
		{
			SCake ck;
			SFile sf;

			sf.bind( *it );
			sf.read( ck );

			if( ck.len() )
			{
				SStrf::smemcpy( p1, ck.buf(), (tint32)ck.len() <  SStrf::satol( *it2 ) ? (tint32)ck.len() :  SStrf::satol( *it2 ) );
			}

			
			p1 += SStrf::satol( *it2 );
		}

		
		strSeal = SCalc::dseal( ckOut.buf() + iSealLen, ckOut.len() - iSealLen, iSealLen );
		SStrf::smemcpy( ckOut.buf(), strSeal.c_str(), (tint32)strSeal.size() );
	}


	static tbool UnPackFolder(      std::string strWorkPathOrDir,
									const SCake & ckIn , tbool biCheckSeal = 1 ,
									tbool biWriteDiskReal = 1 ,
									const char * pWhitePfn = NULL	,
									std::vector<std::string> *pvWhiteLst = NULL ,
									std::vector<std::string> *pvDirFullNameLst = NULL ,
									std::vector<std::string> *pvFileFullPathNameLst = NULL
								)
	{
		if( ckIn.len() == 0 ) return 0;

		
		
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;
		std::string strSeal;
		std::string strSeal2;
		int iSealLen = 33;


		std::string strTD = "\t";
		std::string strTR = "\n";

		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;

		tsize iii3;
		const char * ppp3 = (const char*)ckIn.buf_const();
		for( iii3 = 0; iii3 < ckIn.len(); iii3++ ) if( *(ppp3 + iii3) == 0 ) break;
		strInfoHeader.assign( (const char*)ckIn.buf_const(), (const char*)ckIn.buf_const() + iii3 ); 

		if( biCheckSeal )
		{
			strSeal = SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 );
			strSeal = SStrvs::vsa_get( strSeal, strTD, 0, 0 );

			if( (int)ckIn.len() <= (int)iSealLen ) return 0;
			strSeal2 = SCalc::dseal( ckIn.buf_const() + iSealLen, ckIn.len() - iSealLen, iSealLen );

			if( strSeal != strSeal2 ) return 0;
		}

		
		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 + 1 ), strTD, 1, vDirNameLst );

		std::sort( vDirNameLst.begin(), vDirNameLst.end() ); 

			
		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vDirFullNameLst.push_back( s1 );

			CString cs1;
			cs1 = s1.c_str();
			if( biWriteDiskReal )
			{
				::CreateDirectory( cs1, NULL );
				
			}
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 1 + 1 ), strTD, 1, vFileRelaPathNameLst );

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vFileFullPathNameLst.push_back( s1 );
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 2 + 1 ), strTD, 1, vFileLenLst );


		if( pvDirFullNameLst != NULL ) *pvDirFullNameLst = vDirFullNameLst;
		if( pvFileFullPathNameLst != NULL ) *pvFileFullPathNameLst = vFileFullPathNameLst;



		const tchar *p1;

		p1 = ckIn.buf_const() + strInfoHeader.size() + 1;

		

		for( ; !vFileFullPathNameLst.empty(); )
		{
			std::string s1;
			tint32 i1;

			s1 = vFileFullPathNameLst.front();
			i1 = SStrf::satol( vFileLenLst.front() );

			if( p1 > ckIn.buf_const() + ckIn.len() ) break;

			SFile sf;

			sf.bind( s1 );

			if( biWriteDiskReal )
			{
				if( pvWhiteLst == NULL && pWhitePfn == NULL )
				{
					sf.write( p1, (tsize)i1 );
				}

				if( pvWhiteLst != NULL )
				{
					for( std::vector<std::string>::iterator itwhite = pvWhiteLst->begin(); itwhite != pvWhiteLst->end(); ++itwhite )
					{
						if( MkDir2Path( strWorkPathOrDir ) + *itwhite == s1 )
						{
							sf.write( p1, (tsize)i1 );
							break;
						}
					}
				}

				if( pWhitePfn != NULL )
				{
					std::string sA, sB;
					sA = MkDir2Path( strWorkPathOrDir ) + pWhitePfn;
					sB = s1;
					SStrf::sucase( sA );
					SStrf::sucase( sB );
					if( sA == sB )
					{
						sf.write( p1, (tsize)i1 );
					}
				}
			}

			vFileFullPathNameLst.erase( vFileFullPathNameLst.begin() );
			vFileLenLst.erase( vFileLenLst.begin() );

			p1 += i1;
		}

		return 1;
	}


	

	
	static std::wstring Utf8toWch( const std::string & s )
	{
		int  unicodeLen = MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, NULL, 0 );
		wchar_t *  pUnicode;
		pUnicode = new  wchar_t[unicodeLen+1];
		MultiByteToWideChar( CP_UTF8, 0, s.c_str(), -1, pUnicode, unicodeLen );

		std::wstring ws;
		ws = pUnicode;
		delete [] pUnicode;
		return ws;
	}


	static std::string & ChtoUtf8( std::string & s )
	{
		std::string ss2( 3 * s.length() + 3 , 'a' );
		WideCharToMultiByte(CP_UTF8, 0, CStringW(s.c_str()), -1, &(ss2[0]), (int)ss2.length(), NULL,FALSE);
		return s = ss2.c_str();
	}


	static std::string & Utf8toCh( std::string & s )
	{
		std::wstring ws = Utf8toWch( s );
		 DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,ws.c_str(),-1,NULL,0,NULL,FALSE);
		 char *psText = new char[dwNum];
		 WideCharToMultiByte (CP_OEMCP,NULL, ws.c_str(),-1,psText,dwNum,NULL,FALSE);
		 s = psText;
		 delete []psText;
		 return s;
	}




	
	static std::string & GB_BIG5( std::string & s )
	{
		
		const char* szGBString = s.c_str();
		UINT nCodePage = 936; 
		int nLength=MultiByteToWideChar(nCodePage,0,szGBString,-1,NULL,0);
		wchar_t* pBuffer = new wchar_t[nLength+1];
		MultiByteToWideChar(nCodePage,0,szGBString,-1,pBuffer,nLength);
		pBuffer[nLength]=0;
		

		const wchar_t* szUnicodeString = pBuffer;
		if(1)
		{
			UINT nCodePage = 950; 
			int nLength=WideCharToMultiByte(nCodePage,0,szUnicodeString,-1,NULL,0,NULL,NULL);
			char* pBuffer=new char[nLength+1];
			WideCharToMultiByte(nCodePage,  WC_COMPOSITECHECK , szUnicodeString,-1,pBuffer,nLength,NULL,NULL);
			pBuffer[nLength]=0;
			s = pBuffer;
			delete []pBuffer;
		}

		delete []pBuffer;
		return s;
	}


	static std::string & GB_BIG5aaa( std::string & s )
	{
		
		

		
		
		
		
		
		
		char *p;
		p = &(s[0]);
		int nLen = (int)s.length();
		std::string ss2( 3 * s.length() + 3 , 'a' );
		SStrf::smemset( &(ss2[0]), 0, (int)ss2.length() );
		LCMapStringA( 0x804, 0x4000000, p, nLen,  &(ss2[0]), nLen );
		return s = ss2.c_str();
	}



	
	static std::string MkRUStr()
	{
		static tint32 i = 1;
		int i2 = (int)time(0) * (int)GetCurrentThreadId() * (int)GetCurrentProcessId();
		int j;
		void *p = SStrf::smalloc(3);
		memcpy( &j, &p, sizeof(int) );
		SStrf::sfree(p);

		double dd = SStrf::rand1() * i * i2 * j * SDte::e_proctime();
		std::string s2 = SStrf::sftoa(dd);
		std::string s3 = SStrf::sftoa(dd);

		std::reverse( (char*)(&dd), (char*)(&dd) + sizeof(double) );
		std::reverse( s2.begin(), s2.end() );

		tchar szBuf[35];
		tchar *pp=szBuf;
		SClib::p_sprintf()( szBuf, "%p%x", *(int*)(&dd) + j + i + SStrf::satol(s2) + SStrf::satol(s3) + (int)time(0) + i2 , 0xfff & i );
		i++;

		if( szBuf[0] == '0' && szBuf[1] == 'x' ) pp++;
		return SStrf::slcase(pp);
	}


	

	static tbool SetFileToCurrentTime( std::string strFullPathName )
	{
		SYSTEMTIME st;
		SDte t;
		GetSystemTime(&st);    

		t.m_year  =  st.wYear    ;
		t.m_mon   =  st.wMonth  ;
		t.m_day =  st.wDay   ;
		t.m_hour = st.wHour  ;
		t.m_min  = st.wMinute  ;
		t.m_sec  = st.wSecond  ;

		return SetFileToTheTime( strFullPathName, t );
	}


	static tbool SetFileToTheTime( std::string strFullPathName, SDte __tm )
	{
		HANDLE hFile;

		hFile = CreateFileA( strFullPathName.c_str(),
							  FILE_ALL_ACCESS, FILE_SHARE_WRITE|FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0 );

		if( hFile == INVALID_HANDLE_VALUE )
		{
			return 0;
		}

		
		FILETIME ft;
		BOOL f;

		SYSTEMTIME st;

		SStrf::smemset(st);

		st.wYear =   __tm.m_year;
		st.wMonth  =  __tm.m_mon;
		st.wDay    =  __tm.m_day;
		st.wHour   =  __tm.m_hour;
		st.wMinute =  __tm.m_min;
		st.wSecond =  __tm.m_sec;

		SystemTimeToFileTime( &st, &ft );  

		
		f = SetFileTime(hFile, &ft, &ft, &ft);

		CloseHandle(hFile);

		return f;
	}



	SDte GetFileModiTime()
	{
		SDte t;
		if( GetFileModiTime( this->filename(), t ) ) return t;
		return SDte();
	}


	static tbool GetFileModiTime( std::string strFullPathName , SDte & __tm, DWORD dwDesiredAccess = FILE_SHARE_READ ) 
	{
		HANDLE hFile;

		
		hFile = CreateFileA( strFullPathName.c_str(), dwDesiredAccess, FILE_SHARE_READ, 0, OPEN_EXISTING, FILE_FLAG_BACKUP_SEMANTICS, 0 );

		if( hFile == INVALID_HANDLE_VALUE )
		{
			return 0;
		}

		FILETIME ft;
		FILETIME ft1;
		BOOL f;

		f = GetFileTime(hFile, &ft, &ft, &ft1); 

		CloseHandle(hFile);

		if( !f )
		{
			return 0;
		}

		SYSTEMTIME stUTC, stLocal;

		FileTimeToSystemTime(&ft1, &stUTC);
		SystemTimeToTzSpecificLocalTime(NULL, &stUTC, &stLocal);

		SYSTEMTIME st = stLocal;


#ifdef VC6_COMPATIBLE_X011_
		SDte  t( __tm );	
#else
		SDte & t( __tm ); 
#endif


		SStrf::smemset(t);

		t.m_year  =  st.wYear    ;
		t.m_mon   =  st.wMonth  ;
		t.m_day =  st.wDay   ;
		t.m_hour = st.wHour  ;
		t.m_min  = st.wMinute  ;
		t.m_sec  = st.wSecond  ;

		return f?1:0;
	}


};


#endif	



X011_NAMESPACE_END


#endif







#ifndef X011__H_W_WNAVA_H
#define X011__H_W_WNAVA_H


X011_NAMESPACE_BEGIN


class WNava : public SNavass
{
public:

	WNava()
	{
	}

	WNava( const WNava & aa2 )
	{
		m_mapKnl = aa2.m_mapKnl;
	}

	WNava( const SNavass & aa2 )
	{
		m_mapKnl = aa2.m_mapKnl;
	}


public:

	virtual ~WNava() {;}


	
	
	

	
	void impconf( const std::string & ssource, std::string ssepTR = "\n", std::string ssepTD = "=", std::string strMemoLineHead = "#" )
	{
		

		std::vector<std::string>  vecLines;
		SStrvs::vsa_imp( ssource, ssepTR, 1, vecLines );
		for( std::vector<std::string>::iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			std::string::size_type i;

			i = it->find(ssepTD);
			if( i == std::string::npos ) continue;

			SStrf::strim( *it );
			if( strMemoLineHead != "" && it->find(strMemoLineHead) == 0 ) continue;

			(*it)[i] = 0;
			this->let( it->c_str(), it->c_str() + i + ssepTD.size() );
		}

		this->trimall();
	}

	
	static WNava ReadFileNa( const std::string & Fn )
	{
		SFile fInFile;
		std::string	 strFileContent;
		fInFile.bind( Fn );
		fInFile.read_str( strFileContent );
		WNava nvA;
		nvA.impconf( strFileContent );
		return nvA;
	}


	
	
	
	WNava & InterpCmdLine( int argc, char* argv[] )
	{
		for( int i = 1; i < argc; i += 2 )
		{
			std::string n;
			std::string v = " ";	
			if( i   < argc ) n = argv[i  ];
			if( i+1 < argc ) v = argv[i+1];
			this->let( n, v );
		}
		return *this;
	}



	typedef std::string & (* P_t) ( std::string & );


	void AtoB( P_t pf )
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			(*pf)( s1 );
			(*pf)( s2 );

			let( s1, s2 );
		}
	}


#ifdef VC6_COMPATIBLE_X011_

#else

	void ChtoUtf8()
	{
		AtoB( WFile::ChtoUtf8 );
	}

	void Utf8toCh()
	{
		AtoB( WFile::Utf8toCh );
	}

#endif


	WNava & operator = ( const WNava & aa2 )
	{
		m_mapKnl = aa2.m_mapKnl;
		return *this;
	}

	WNava & operator = ( const SNavass & aa2 )
	{
		m_mapKnl = aa2.m_mapKnl;
		return *this;
	}

};



X011_NAMESPACE_END

#endif






#ifndef X011__H_WReg32_h
#define X011__H_WReg32_h


X011_NAMESPACE_BEGIN


class WReg32 {

private:

public:

	WReg32()
	{
	}

	virtual ~WReg32()
	{
	}


	static tbool ChkSection( HKEY hkPrimKey, LPCSTR lpszSection )
	{
		tbool bRc = 0;

		try
		{
			do
			{
                if( !lpszSection )
				{
					bRc=0;
					break;
				}

				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;

				lResult = RegOpenKeyExA(hkPrimKey, lpszSection, 0, KEY_READ, &hkReg);

				if( lResult != ERROR_SUCCESS )
				{
					bRc=0;
					break;
				}

				bRc = 1;

				lResult = RegCloseKey(hkReg);

			}while(0);
		}
		catch(...)
		{
			return bRc=0;
		}

		return bRc;
	}


	static tbool ChkEntry( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry )
	{
		BOOL fRet = FALSE;

		try
		{
			if( lpszSection )
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;

				lResult = RegOpenKeyExA(hkPrimKey, lpszSection, 0, KEY_READ, &hkReg);

				if( lResult == ERROR_SUCCESS )
				{
					try
					{
						DWORD dwType, dwCount;

						lResult = RegQueryValueExA(hkReg, lpszEntry, NULL, &dwType, NULL, &dwCount);

						if( lResult == ERROR_SUCCESS )
						{
							fRet = TRUE;
						}
					}
					catch(...)	{	;}

					lResult = RegCloseKey(hkReg);
				}
			}
		}
		catch(...)	{;	}

		return fRet?1:0;
	}


	static UINT ReadUInt( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry )
	{
		UINT uiRet = 0;

		try
		{
			if( lpszSection && lpszEntry )
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;
				BOOL fError = TRUE;

				lResult = RegOpenKeyExA(hkPrimKey, lpszSection, 0, KEY_READ, &hkReg);

				if( lResult == ERROR_SUCCESS )
				{
					try
					{
						DWORD dwValue=0;
						DWORD dwType;
						DWORD dwCount = sizeof(DWORD);

						lResult = RegQueryValueExA(hkReg, lpszEntry, NULL, &dwType, (LPBYTE)&dwValue, &dwCount);

						if( lResult == ERROR_SUCCESS )
						{
							uiRet = (UINT)dwValue;
							fError = FALSE;
						}
					}
					catch(...)	{;		}

					lResult = RegCloseKey(hkReg);
				}

			}

		}
		catch(...)	{	;	}

		return uiRet;
	}


	static tbool WriteInt( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry, int iValue )
	{
		BOOL fRet = FALSE;

		try
		{
			BOOL fError = TRUE;

			if( lpszSection && lpszEntry)
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;
				DWORD dw;

				
				lResult = RegCreateKeyExA(hkPrimKey, lpszSection, 0, REG_NONE, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hkReg, &dw);

				if(lResult ==  ERROR_SUCCESS)
				{
					try
					{
						lResult = RegSetValueExA(hkReg, lpszEntry, 0, REG_DWORD, (LPBYTE)&iValue, sizeof(int));

						if (lResult == ERROR_SUCCESS)
						{
							fError = FALSE;
							fRet = TRUE;
						}

						lResult = RegCloseKey(hkReg);
					}
					catch(...)	{	;		}
				}
			}
		}
		catch(...)	{	;}

		return !!fRet;
	}


	static std::string ReadStr( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry )
	{
		SCake ckRet;

		try
		{

			BOOL fError = TRUE;

			if( lpszSection && lpszEntry)
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;

				lResult = RegOpenKeyExA(hkPrimKey, lpszSection, 0, KEY_READ, &hkReg);

				if( lResult == ERROR_SUCCESS )
				{
					try
					{
						DWORD dwType, dwCount;

						lResult = RegQueryValueExA(hkReg, lpszEntry, NULL, &dwType, NULL, &dwCount);

						if( lResult == ERROR_SUCCESS )
						{
							ckRet.redim(dwCount);
							lResult = RegQueryValueExA(hkReg, lpszEntry, NULL, &dwType, (LPBYTE)ckRet.buf(), &dwCount);

							if( lResult == ERROR_SUCCESS )
							{
								fError = FALSE;
							}

						}
					}
					catch(...)		{		;	}

					lResult = RegCloseKey(hkReg);
				}

			}

		}
		catch(...)	{	;	}

		return ckRet.buf()?ckRet.buf():"";
	}


	static tbool WriteStr( HKEY hkPrimKey, LPCSTR lpszSection, LPCSTR lpszEntry, std::string strValue )
	{
		BOOL fRet = FALSE;

		try
		{
			BOOL fError = TRUE;

			if( lpszSection && lpszEntry )
			{
				HKEY hkReg;
				LONG lResult = ERROR_EXCEPTION_IN_SERVICE;
				DWORD dw;

				
				lResult = RegCreateKeyExA(hkPrimKey, lpszSection, 0, REG_NONE, REG_OPTION_VOLATILE, KEY_WRITE, NULL, &hkReg, &dw);

				if(lResult ==  ERROR_SUCCESS)
				{
					try
					{
						lResult = RegSetValueExA(hkReg, lpszEntry, 0, REG_SZ, (LPBYTE)strValue.c_str(), (int)strlen(strValue.c_str()) );
						if (lResult == ERROR_SUCCESS)
						{
							fError = FALSE;
							fRet = TRUE;
						}
						lResult = RegCloseKey(hkReg);
					}
					catch(...)	{;	}
				}
			}
		}
		catch(...)
		{
			;
		}

		return !!fRet;
	}


	static int EnumEntry( HKEY hkPrimKey, LPCSTR lpszSection, std::vector<std::string> & vecRtn )
	{
		enum { MAX_VALUE_NAME = 255, MAX_VALUE_DATA = 4096 	};
		tchar szName[MAX_VALUE_NAME];
		BYTE lpData[MAX_VALUE_DATA];
		DWORD cchName = MAX_VALUE_NAME;
		DWORD ccbData = MAX_VALUE_DATA;
		int iIndex = 0;
		LONG lRet = ERROR_SUCCESS;

		HKEY hKey;

		lRet = RegOpenKeyExA(hkPrimKey, lpszSection, 0,KEY_READ, &hKey);
		if (lRet != ERROR_SUCCESS) return 0;

		for (iIndex=0; lRet != ERROR_NO_MORE_ITEMS; ++iIndex)
		{
			cchName = MAX_VALUE_NAME;
			ccbData = MAX_VALUE_DATA;
			szName[0] = '\0';
			lpData[0] = '\0';
			lRet = RegEnumValueA(hKey, iIndex,szName, &cchName ,NULL ,NULL,lpData, &ccbData);
			if (lRet == ERROR_SUCCESS )
			{
				
					vecRtn.push_back( std::string((tchar*)szName) );
			}
		}

		return iIndex;
	}


	static int EnumSection( HKEY hkPrimKey, LPCSTR lpszSection, std::vector<std::string> & vecRtn )
	{
		enum { MAX_VALUE_NAME = 255, MAX_VALUE_DATA = 4096 	};
		tchar szName[MAX_VALUE_NAME];
		tchar lpData[MAX_VALUE_DATA];
		DWORD cchName = MAX_VALUE_NAME;
		DWORD ccbData = MAX_VALUE_DATA;
		int iIndex = 0;
		LONG lRet = ERROR_SUCCESS;

		HKEY hKey;

		lRet = RegOpenKeyExA(hkPrimKey, lpszSection, 0,KEY_READ, &hKey);
		if (lRet != ERROR_SUCCESS) return 0;

		for (iIndex=0; lRet != ERROR_NO_MORE_ITEMS; ++iIndex)
		{
			cchName = MAX_VALUE_NAME;
			ccbData = MAX_VALUE_DATA;
			szName[0] = '\0';
			lpData[0] = '\0';
			lRet = RegEnumKeyA( hKey, iIndex, lpData, MAX_VALUE_NAME);
			if (lRet == ERROR_SUCCESS )
			{
				
					vecRtn.push_back( std::string((tchar*)lpData) );
			}
		}

		return iIndex;
	}


}; 



X011_NAMESPACE_END

#endif






#ifndef X011__H_w_wthrd_h
#define X011__H_w_wthrd_h







#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED

#else
#include <process.h>
#endif


X011_NAMESPACE_BEGIN




class WThrd
{

private:

	volatile HANDLE	 m_hThread;	
	volatile int m_iAutoDel;
	volatile int m_iShouldBreak;
	volatile int m_iLive;
	volatile int m_iCreationDone;

	volatile int m_iOpened;


private:


#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
static DWORD WINAPI ThreadProc(LPVOID lpParam)
#else
static unsigned int WINAPI ThreadProc(void * lpParam)
#endif
	{
		WThrd *pThis=reinterpret_cast<WThrd*>(lpParam);
		int iAutoDel = pThis->m_iAutoDel; 
		int iAutoDelrc = 0;

		HANDLE	 my_hThread;

		try
		{
			

			pThis->tr_init_rand();
			pThis->tr_on_pre_thrd();
			pThis->tr_on_knl_run();
			pThis->tr_on_post_thrd();

			
			pThis->tr_shouldbrk();

			pThis->m_iLive = 0;

			if(iAutoDel)
			{
				if( !pThis->m_iCreationDone )
				{
					while( !pThis->m_iCreationDone )
						tr_sleep( 1 );

					tr_sleep( 1 );
				}

				tr_sleep( 1 ); 

				
				iAutoDelrc = 1;
				my_hThread = pThis->m_hThread;
			}
		}
		catch(...)
		{ ;	}

		if( iAutoDelrc )
		{
			delete pThis;
			::CloseHandle(my_hThread);
		}

		return (DWORD)0;
	}


private:

	WThrd & operator = (const WThrd & rhs)
	{
		return *this;
	}


	WThrd(const WThrd & rhs)
	{;}


protected:
	volatile int m_idestructed; 

protected:
	
	
	void tr_destruct()
	{
		if( !m_idestructed )
		{
			m_idestructed = 1;

			
			if( !m_iOpened ) return;

			try
			{
				tr_shouldbrk();

				
				
				
				
				

				if( !m_iAutoDel )
				{
					tr_wait();

					tr_closehandl();
				}
			}
			catch(...)
			{; }
			
		}
	}

public:

	WThrd()
	{
		m_hThread = INVALID_HANDLE_VALUE;
		m_iAutoDel = 0;
		m_iShouldBreak = 0;
		m_iLive = 0;
		m_iCreationDone = 0;
		m_iOpened = 0;

		m_idestructed = 0;
	}


	virtual ~WThrd()
	{
		tr_destruct();
	}


public:
	
	static std::string tr_GetCurrentThreadId()
	{
		char sz1[22];
		SClib::p_sprintf()( sz1, "%p", GetCurrentThreadId() );
		return sz1;
	}

	
	HANDLE tr_GetHnd() const
	{
		return m_hThread;
	}

	
	void tr_init_rand()
	{
		SStrf::initrand( (int)((int)time(0) * (int)GetCurrentThreadId()) );


		int j, j2;
		HANDLE h;
		void *p;

		h = tr_GetHnd();
		memcpy( &j,  &h, sizeof(int) < sizeof(h) ? sizeof(int) : sizeof(h) );
		p = (void*)tr_GetCurrentThreadId().c_str();
		memcpy( &j2, &p, sizeof(int) < sizeof(p) ? sizeof(int) : sizeof(p) );

		SStrf::initrand( j + j2 );
	}

	
	static void tr_sleep( int iSec , double dSec = 0.0 ) 
	{
		if( iSec > 0 )
			Sleep( iSec * 1000 );

		if( dSec > 0.0 )
		{
			Sleep( static_cast<int>(dSec * 1000 * 1) );
		}
	}

	
	static void tr_sleepu( double dSec ) 
	{
		if( dSec > 0 )
		{
			tr_sleep( (int)dSec, dSec - (int)dSec );
		}
	}


	
	tbool tr_open()
	{
		m_iCreationDone = 0;

		on_before_tr_open();

		m_hThread = INVALID_HANDLE_VALUE;

		m_iLive = 1;

#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
		
		DWORD i;
		m_hThread = ::CreateThread (
			NULL,			
			0,				
			ThreadProc,		
			reinterpret_cast<LPVOID>(this),	
			0,				
			&i	);			
#else
		
		unsigned int i;
		m_hThread = (HANDLE) ::_beginthreadex(
			NULL,			
			0,				
			ThreadProc,		
			reinterpret_cast<LPVOID>(this),	
			0,				
			&i	);			

#endif

		tbool rc = 1;

		if( !m_hThread )
		{
			m_iLive = 0;
			rc = 0;
		}

		if(rc) on_after_tr_open(); 


		if( tr_isRunning() )
		{
			m_iOpened = 1;
		}

		m_iCreationDone = 1;

		return rc;
	}


	tbool tr_openx() 
	{
		m_iAutoDel = 1;
		return tr_open();
	}



	void tr_shouldbrk()
	{
		m_iShouldBreak = 1;
	}


	int tr_isShouldBrk() const
	{
		return m_iShouldBreak;
	}


	
	int tr_isRunning()
	{
		 return m_iLive;
	}


	void tr_Terminate()
	{
		if( !m_iOpened ) return;

		try
		{
			if( m_hThread != INVALID_HANDLE_VALUE )
			{
				TerminateThread( m_hThread, 0 );
			}
		}
		catch (...)
		{	;
		}
	}

	void tr_closehandl()
	{
		tr_shouldbrk();

		if( m_hThread != INVALID_HANDLE_VALUE )
		{
			try
			{

#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
				::CloseHandle(m_hThread);
#else
				

				::CloseHandle(m_hThread);
#endif
			}
			catch (...)
			{
				;
			}
		}

		try
		{
			m_hThread = INVALID_HANDLE_VALUE;
		}
		catch (...)
		{
			;
		}
	}


	
	
	
	
	int tr_wait( DWORD dwMilliseconds=INFINITE )
	{
		if( !m_iOpened ) return 0;

		if( ! tr_isRunning() ) return 0;

		try
		{
			do
			{
				if( m_hThread == INVALID_HANDLE_VALUE )
					return 0;

				if( WAIT_TIMEOUT==::WaitForSingleObject(m_hThread,dwMilliseconds) )
					return 1;

				return 0;

			}while(0);

		}
		catch(...)
		{
			return 0;
		}
	}



	void tr_priority(int nPrio)
	{

		
		
		
		
		
		::SetThreadPriority(m_hThread,nPrio);
	}



	void tr_priority_high() { 	tr_priority( THREAD_PRIORITY_ABOVE_NORMAL ); }


	void tr_priority_low()  { 	tr_priority( THREAD_PRIORITY_BELOW_NORMAL ); }


	void tr_priority_normal() { 	tr_priority( THREAD_PRIORITY_NORMAL ); }



	
	void tr_suspend()
	{
		::SuspendThread(m_hThread);
	}


	void tr_resume()
	{
		::ResumeThread(m_hThread);
	}



	
	virtual void on_before_tr_open()
	{
	}

	
	virtual void on_after_tr_open()
	{
	}


	virtual void tr_on_knl_run()
	{
		

		while(1)
		{
			if( !tr_on_user_run() ) break;

			if( m_iShouldBreak ) break;
		}
	}

	
	virtual void tr_on_pre_thrd()
	{
	}

	
	virtual void tr_on_post_thrd()
	{
	}

	
	virtual int tr_on_user_run() 
	{
		return 0;
	}

	
	virtual tbool tr_OnMgrPrepare() 
	{
		return 1;
	}

}; 




X011_NAMESPACE_END

#endif








#ifndef X011__H_W_WTHRDMGR_H
#define X011__H_W_WTHRDMGR_H


X011_NAMESPACE_BEGIN






template < class ThreadEle_T , class THREADBASE_T = WThrd >
class WThrdMgr : public THREADBASE_T
{
private:

public:
	typedef	 ThreadEle_T   ThrEle_t;
	volatile tbool         m_biMgrShouldBreak;
	double                 m_FailWaitTimesec; 
	tbool                  m_biIsMultiEleType;

public:
	
	WThrdMgr()
	{
		m_biMgrShouldBreak = 0;
		m_FailWaitTimesec = 0.2;
		m_biIsMultiEleType = 1;
	}

	
	virtual ~WThrdMgr()
	{ THREADBASE_T::tr_destruct();	}

	
	virtual tbool OnMgrPrepare( ThrEle_t & t ) 
	{
		return 1;
	}

	
	virtual int tr_on_user_run()
	{
		BirthEle();

		return 1;
	}

	
	virtual ThrEle_t * MgrPrepare()   
	{
		ThrEle_t * p;

		try{
			p = new ThrEle_t;
		}
		catch(...)
		{p=NULL;}

		if( p==NULL ) return NULL;

		if( !OnMgrPrepare(*p) ) 
		{
			delete p;
			return NULL;
		}

		if( ! p->tr_OnMgrPrepare() ) 
		{
			delete p;
			return NULL;
		}

		return p;
	}



	tbool BirthEle()
	{
		if( m_biMgrShouldBreak ) return 0;

		if( THREADBASE_T::tr_isShouldBrk() ) return 0;

		ThrEle_t * p = MgrPrepare();

		if( p != NULL )
		{
			if( m_biIsMultiEleType )
			{
				p->tr_openx();
			}
			else
			{
				p->tr_open();
				p->tr_wait(); 
				delete p;
			}

			return 1;
		}
		else
		{
			if( m_FailWaitTimesec <= 0 ) return 0;

			WThrd::tr_sleepu( m_FailWaitTimesec );

			return 0;
		}
	}

};




















































class WThrdCity
{
public:

		class WThrd2 : public WThrd
		{

		friend class WThrdCity;

		private:
			WThrdCity * m_pWThrdCity;

			int tr_on_user_run() 
			{
				return OnRun() ;
			}

		public:

			WThrd2()
			{
				m_pWThrdCity = NULL;
			}

			virtual ~WThrd2()
			{
				if( m_pWThrdCity ) m_pWThrdCity->RemoveEle(*this);

				tr_destruct();
			}

			virtual int OnRun()
			{
				return 0;
			}

		};


	typedef  WThrd2  WThrdEle;

	
	friend class WThrd2;


private:

	std::vector< WThrdEle * >  m_vecThrdLst;

	WCrsc m_crscThrdLst;

	WCrsc m_crscThrdOpenFunc;

	
	int AddEle( WThrdEle & t )
	{
		WCrsc aLock( &(this->m_crscThrdLst) );
		WThrdEle * p = SStrf::AddressOf( t );

		m_vecThrdLst.push_back( p );
		return GetThrdAmount();
	}

	
	int RemoveEle( WThrdEle & t )
	{
		WCrsc aLock( &(this->m_crscThrdLst) );
		WThrdEle * p = SStrf::AddressOf( t );

		std::vector< WThrdEle * >::iterator it = std::find( m_vecThrdLst.begin(), m_vecThrdLst.end(), p );
		if( it != m_vecThrdLst.end() )
		{
			m_vecThrdLst.erase( it );
		}
		return GetThrdAmount();
	}

public:
	int m_iLimit;

	tbool m_bWithOpenFailRetry;

public:
	
	WThrdCity( int iLimit = 123 )
	{
		m_iLimit = iLimit;
		m_bWithOpenFailRetry = 0;
	}

	
	virtual ~WThrdCity()
	{;	}

public:
	
	int GetThrdAmount() const
	{
		return (int)m_vecThrdLst.size();
	}

	
	void CleanStoppedThrd()
	{
		WCrsc aLock ( &m_crscThrdOpenFunc );
		WCrsc a2Lock( &m_crscThrdLst );

		std::vector< WThrdEle * >::iterator it;

		for( it = m_vecThrdLst.begin();
			 it != m_vecThrdLst.end();
			 ++it	)
		{
			if( (*it)->tr_isRunning() )
			{
				
			}
			else
			{
				(*it)->m_pWThrdCity = NULL; 
				delete *it;
				it = m_vecThrdLst.erase( it );
			}
		}

	}

	
	tbool OpenThrd( WThrdEle & t )
	{
		WCrsc aLock( &m_crscThrdOpenFunc );

		if( GetThrdAmount() >= m_iLimit )
		{
			
			return 0;
		}

		AddEle( t );

		t.m_pWThrdCity = this;
		t.tr_open();

		return 1;
	}

	
	tbool OpenThrdHp( WThrdEle * t1 ) 
	{
		WCrsc aLock( &m_crscThrdOpenFunc );

		if( !t1 ) return 0;

		if( GetThrdAmount() >= m_iLimit )
		{
			
			return 0;
		}



		AddEle( *t1 ); 

		( *t1 ).m_pWThrdCity = this;
		( *t1 ).tr_openx();

		return 1;
	}

	
	template< class ThrdEle_T >
	tbool OpenThrdHp()
	{
		

		WThrdEle * p = new ThrdEle_T ;

		return OpenThrdHp(p); 
	}


	
	
};


typedef  WThrdCity::WThrd2  WThrdEle;


#ifdef VC6_COMPATIBLE_X011_

#else




template < class TASK_T , class TH_T = WThrd >
class WIdleThrd
{
public:
	typedef  TASK_T  TASK_t;

private:
	std::vector<TASK_T>   m_vecTasks;
	WCrsc                 m_crTasksReadLck;

	WCrsc                 m_crTasksRunLck;

	volatile int          m_iWorkThrdObjRef; 
	WCrsc                 m_crWorkThrdObjRefLck;

	volatile int          m_iWorkThrdWaitingRunfuncRef; 
	WCrsc                 m_crWorkThrdWaitingRunfuncRefLck;

	volatile int          m_iWorkThrdRunRef; 
	WCrsc                 m_crWorkThrdRunRefLck;

	friend class WIdleThrdEle;

	volatile int          m_isLive; 

public:
		
		class WIdleThrdEle : public TH_T
		{
		private:
			WIdleThrd < TASK_T , TH_T >  * m_pWIdleThrd;

			
			int tr_on_user_run()
			{
				if(1)
				{
					WCrsc aaa2 ( &(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck) );
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef++;
				}

				TASK_T t;
				WCrsc aaa ( &(m_pWIdleThrd->m_crTasksRunLck) ); 

				if(1)
				{
					WCrsc aaa2 ( &(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck) );
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef--;
				}

				for( ; m_pWIdleThrd->TakeTask(t); )  
				{
					m_pWIdleThrd->OnRunTask(t);
				}

				return 0;
			}

			
			virtual void tr_on_pre_thrd()
			{
				WCrsc aaa ( &(m_pWIdleThrd->m_crWorkThrdRunRefLck) );
				m_pWIdleThrd->m_iWorkThrdRunRef++;
			}

			
			virtual void tr_on_post_thrd()
			{
				WCrsc aaa ( &(m_pWIdleThrd->m_crWorkThrdRunRefLck) );
				m_pWIdleThrd->m_iWorkThrdRunRef--;
			}

		public: 
			
			WIdleThrdEle( WIdleThrd < TASK_T , TH_T > *p )
			{
				m_pWIdleThrd = p;

				WCrsc aaa ( &(m_pWIdleThrd->m_crWorkThrdObjRefLck) );

				m_pWIdleThrd->m_iWorkThrdObjRef++;
			}

			
			virtual ~WIdleThrdEle()
			{
				if(1)
				{
					WCrsc aaa ( &(m_pWIdleThrd->m_crWorkThrdObjRefLck) );

					m_pWIdleThrd->m_iWorkThrdObjRef--;
				}

				TH_T::tr_destruct();
			}
		};

public:
	
	WIdleThrd()
	{
		m_iWorkThrdObjRef = 0;
		m_iWorkThrdWaitingRunfuncRef = 0;
		m_iWorkThrdRunRef = 0;

		m_isLive = 1;
	}

	
	virtual ~WIdleThrd()
	{
		m_isLive = 0;

		while( GetTasksSize() )
		{
			WThrd::tr_sleep(1);
		}
		while( m_iWorkThrdObjRef > 0 )
		{
			WThrd::tr_sleep(1);
		}
	}

public:
	
	void PostTask( const TASK_T & t, tbool biWithWait = 1, tbool biContribute = 1 )
	{
		if( !m_isLive ) return;

		
		if( biWithWait )
		{
			if   ( m_iWorkThrdObjRef              > 9 ) WThrd::tr_sleep( 0, 0.51 );
			while( m_iWorkThrdWaitingRunfuncRef   > 4 ) WThrd::tr_sleep( 0, 0.51 );
			while( m_iWorkThrdRunRef              > 7 ) WThrd::tr_sleep( 0, 0.51 );
		}
		else
		{
			if   ( m_iWorkThrdObjRef              > 800 )
				WThrd::tr_sleep( 0, 0.51 );

			while( m_iWorkThrdWaitingRunfuncRef   > 300 )
				WThrd::tr_sleep( 0, 0.51 );

			while( m_iWorkThrdRunRef              > 600 )
				WThrd::tr_sleep( 0, 0.51 );
		}

		if(1)
		{
			WCrsc aaa(&m_crTasksReadLck);

			if( OnBeforePushTask(t) )
			{
				m_vecTasks.push_back(t);
				
			}

			if( !m_vecTasks.empty() )
			{
				OnAfterPushTask( *m_vecTasks.rbegin() ) ;
			}

			
			if( biContribute )
			{
				if( m_iWorkThrdWaitingRunfuncRef < 2 ) 
				{
					WIdleThrdEle *p = new WIdleThrdEle(this);
					p->tr_openx();
				}
			}
		}

		return ;
	}

	
	void ContributeTask()
	{
		WCrsc aaa(m_crTasksReadLck);

		if( m_iWorkThrdWaitingRunfuncRef < 2 ) 
		{
			WIdleThrdEle *p = new WIdleThrdEle(this);
			p->tr_openx();
		}
	}


	tbool TakeTask( TASK_T & t )
	{
		WCrsc aaa(&m_crTasksReadLck);
		if( m_vecTasks.empty() ) return 0;
		t = m_vecTasks[0];
		m_vecTasks.erase( m_vecTasks.begin() );
		return 1;
	}

	
	tuint32 GetTasksSize()
	{
		WCrsc aaa(&m_crTasksReadLck);
		return  (tuint32)m_vecTasks.size();
	}

	
	void ClearTask()
	{
		WCrsc aaa(&m_crTasksReadLck);
		m_vecTasks.clear();
	}


	void WaitAllTaskDone()
	{
		while( m_iWorkThrdRunRef > 0 )
		{
			WThrd::tr_sleep(1);
		}
	}


	
	virtual tbool OnBeforePushTask( const TASK_T & t )
	{
		return 1;
	}

	
	virtual void OnAfterPushTask( TASK_T & t )
	{
		return;
	}


	virtual void OnRunTask( TASK_T t ) 
	=0;
	
	
};

#endif	








template < int INT_SEC_T >
class WCrsc2
{
public:
	enum base_son_type1_t    { BASE, SON };
	enum read_write_type2_t  { READ, WRITE };

private:
	WCrsc	   * m_p_base_csc_read;
	WCrsc	   * m_p_base_csc_write;
	WCrsc	   * m_pwrite;
	int          m_reader_ref;
	base_son_type1_t       m_type1;
	read_write_type2_t     m_type2;
	WCrsc2            * m_p_father;

	void InitVars()
	{
		m_p_base_csc_read = NULL;
		m_p_base_csc_write = NULL;
		m_pwrite = NULL;
		m_reader_ref = 0;
		m_type1 = BASE;
		m_type2 = READ;
		m_p_father = NULL;
	}

private:
	
	
	
	
	WCrsc2( WCrsc2 & aa )
	{
	}

public:
	WCrsc2()
	{
		InitVars();

		m_p_base_csc_read = new WCrsc;
		m_p_base_csc_write = new WCrsc;
		m_type1 = BASE;
	}

	WCrsc2( WCrsc2 * pfather, read_write_type2_t type2 = READ , double dSec = 0.10 )
	{
		InitVars();

		m_type1 = SON;
		m_type2 = type2;
		m_p_father = pfather;

		if( m_type2 == READ )
		{
			WCrsc big_csc( m_p_father->m_p_base_csc_write );
			WCrsc small_csc( m_p_father->m_p_base_csc_read );
			m_p_father->m_reader_ref ++;
		}

		if( m_type2 == WRITE )
		{
			m_pwrite = new WCrsc( m_p_father->m_p_base_csc_write );

			while( m_p_father->m_reader_ref != 0 )
			{
				WThrd::tr_sleep( INT_SEC_T , dSec );
			}
		}
	}


	virtual ~WCrsc2()
	{
		if( m_type1 == BASE )
		{
			delete m_p_base_csc_read;
			delete m_p_base_csc_write;
		}

		if( m_type1 == SON && m_type2 == READ )
		{
			WCrsc small_csc( m_p_father->m_p_base_csc_read );
			m_p_father->m_reader_ref --;
		}

		if( m_type1 == SON && m_type2 == WRITE )
		{
			delete m_pwrite;
			m_pwrite = NULL;
		}
	}

	
	WCrsc & operator = (const WCrsc & rhs)
	{
		
		return *this;
	}

};














X011_NAMESPACE_END

#endif








#ifndef X011__w_WSnd_H
#define X011__w_WSnd_H


#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")


X011_NAMESPACE_BEGIN




class WSndConv
{
public:
	
	enum WavStyle_t { R44100D16C2 };
public:
	virtual ~WSndConv() {;}

public:

	
	static tbool Conv( SCake & ckBufInOut, WavStyle_t eStyle = R44100D16C2 )
	{
		if( eStyle == R44100D16C2 && ckBufInOut.len() )
		{
			std::vector<tuint8> v1;

			v1.resize( 0x2c, 0 ); 


			
			
			
			
			v1.insert(v1.end(),   (tuint8*)ckBufInOut.buf(),   (tuint8*)ckBufInOut.buf() + ckBufInOut.len()   );


			*(char*)(&(v1[0])) = 'R';
			*(char*)(&(v1[1])) = 'I';
			*(char*)(&(v1[2])) = 'F';
			*(char*)(&(v1[3])) = 'F';
			*(tuint32*)(&(v1[4])) = (tuint32)v1.size() - 8; 
			
			

			*(char*)(&(v1[8])) = 'W';
			*(char*)(&(v1[9])) = 'A';
			*(char*)(&(v1[0x0a])) = 'V';
			*(char*)(&(v1[0x0b])) = 'E';
			*(char*)(&(v1[0x0c])) =  'f';
			*(char*)(&(v1[0x0d])) =  'm';
			*(char*)(&(v1[0x0e])) =  't';
			*(char*)(&(v1[0x0f])) = 0x20; 
			*(tuint32*)(&(v1[0x10])) = (tuint32)0x00000010; 
			
			

			*(tuint16*)(&(v1[0x14])) = (tuint16)0x0001; 
			

			*(tuint16*)(&(v1[0x16])) = (tuint16)0x0002; 
			

			*(tuint32*)(&(v1[0x18])) = (tuint32)0x0000ac44; 
			
			

			*(tuint32*)(&(v1[0x1c])) = (tuint32)0x0002b110; 
			
			

			*(tuint16*)(&(v1[0x20])) = (tuint16)0x04; 
			

			*(tuint16*)(&(v1[0x22])) = (tuint16)0x10; 
			

			*(char*)(&(v1[0x24])) = 'd';
			*(char*)(&(v1[0x25])) = 'a';
			*(char*)(&(v1[0x26])) = 't';
			*(char*)(&(v1[0x27])) = 'a';
			*(tuint32*)(&(v1[0x28])) = (tuint32)ckBufInOut.len();
			
			

			ckBufInOut.let( (tchar*)(&(v1[0])), (tuint32)v1.size() );

			return 1;
		}

		return 0;
	}
};




class WSnd : public WSndConv
{
public:

public:
	virtual ~WSnd() {;}

public:

	
	static void PlayWav( std::string strFile , tbool *pStop = NULL )
	{
		PlaySoundA( strFile.c_str(),
									 NULL,
											 SND_FILENAME |
											 SND_SYNC			);
	}

};




class WSndQue : public WSnd , public WIdleThrd < std::string >
{
public:
	WCrsc  m_WavLck;
	tbool  m_IsStopFlag;

public:
	WSndQue() { m_IsStopFlag = 0; }
	virtual ~WSndQue() {;}

public:
	
	void Play( std::string strFile )
	{
		StopPlay();
		m_IsStopFlag = 0;
		this->PostTask( strFile, 0, 1 );
	}

	
	void StopPlay()
	{
		m_IsStopFlag = 1;	
		WCrsc aa(&m_WavLck); 
		PlaySoundA( NULL, NULL,
									 SND_FILENAME |
									 SND_ASYNC			);
	}

	
	virtual void OnRunTask( std::string t )
	{
		WCrsc aa(&m_WavLck);

		PlaySoundA( t.c_str(), NULL,
									 SND_FILENAME |
									 SND_ASYNC			);
	}

};





X011_NAMESPACE_END

#endif







#ifndef X011__H_w_WMoonLog_h
#define X011__H_w_WMoonLog_h


X011_NAMESPACE_BEGIN


class WMoonLog
{
private:
	WCrsc       m_LogLck;

	std::string  m_strFnOld;	
	std::string  m_strFnNow;  

	std::string  m_strWorkPath;
	int          m_iRelativeDay;
	int          m_iLogCounter;

public:
	WMoonLog()
	{
		m_strWorkPath = "";
		m_iRelativeDay = 0;
		m_iLogCounter = 0;
	}

	virtual ~WMoonLog(){;}

private:

	
	void WashLogFile()  
	{
		SDte dtold;
		SDte dtnow;
		char szold[22];
		char sznow[22];

		if( m_iRelativeDay >= 0 ) return;

		dtold.MakeNow();
		dtold.RelativeDay( m_iRelativeDay ); 
		dtnow.MakeNow();

		(SClib::p_strcpy())( szold, dtold.ReadStringPack().c_str() );
		(SClib::p_strcpy())( sznow, dtnow.ReadStringPack().c_str() );

		szold[8] = 0;
		sznow[8] = 0;

		m_strFnOld = m_strWorkPath + "log" + std::string( szold + 3 ) + std::string(".txt");
		m_strFnNow = m_strWorkPath + "log" + std::string( sznow + 3 ) + std::string(".txt");

		SFile fl;

		fl.bind(m_strFnOld);
		fl.erase();
	}

	
	static std::string RefineStrVal( const std::string & s )
	{
		if( s.size() < 9 && wl::SStrf::sisdec( s.c_str() ) )
		{
			char ss[22];
			unsigned long ul;

			ul = wl::SStrf::satoul(s);
			(*wl::SClib::p_sprintf())( ss, "(0x%02X)", ul );
			return s + ss;
		}
		else
			return s;
	}

	
	void WriteStr( const std::string & s1 )
	{
		WCrsc aLock(&m_LogLck);

		if( m_iRelativeDay >= 0 ) return;

		if( m_iLogCounter++ >= 10000 ) 
		{
			m_iLogCounter=0;
			WashLogFile();
		}

		SFile fl;

		fl.bind(m_strFnNow);
		fl.write_str( s1 + "\r\n", 1 );
	}

	
	void GetTimeStr( std::string & s )
	{
		s = "." + wl::SStrf::sltoa(wl::SDte::Get_msec());
		s = wl::SDte::GetNow().ReadStringPack() + s;
	}

public:

	
	void InitLog( std::string strWorkPath, int iRelativeDay )
	{
		m_strWorkPath = SFile::MkDir2Path(strWorkPath);
		m_iRelativeDay = iRelativeDay;
		m_iLogCounter = 0;

		WashLogFile();

		std::string s1(88,'-');
		WriteStr( s1 );
	}

	
	template<class T>
	void WriteLog( T val1 )
	{	
		std::stringstream stream1;
		std::string strOut;
		stream1 << val1;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str());
		WriteStr(strOut);
	}

	template<class T1, class T2>
	void WriteLog( T1 val1, T2 val2 )
	{
		std::stringstream stream1, stream2;
		std::string strOut;
		stream1 << val1;
		stream2 << val2;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str()) + "\t" + RefineStrVal(stream2.str());
		WriteStr(strOut);
	}

	template<class T1, class T2, class T3>
	void WriteLog( T1 val1, T2 val2, T3 val3 )
	{
		std::stringstream stream1, stream2, stream3;
		std::string strOut;
		stream1 << val1;
		stream2 << val2;
		stream3 << val3;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str()) + "\t" + RefineStrVal(stream2.str()) + "\t" + RefineStrVal(stream3.str());
		WriteStr(strOut);
	}
};














class WDaydayLog
{
public:

	WCrsc		 m_LogLck;

	std::string  m_strWorkPath;
	std::string  m_strPrefix;  
	int          m_iLogNum;

	int          m_iRelativeDay;
	tbool		 m_biLogEnabled;

	std::string  m_strFnNow;  
	SDte	    m_dtBegin;


public:
	WDaydayLog()
	{
		m_iRelativeDay = -19;
		m_biLogEnabled = 1;
		m_iLogNum = 0;		
	}

	virtual ~WDaydayLog() {}


public:
	void WashLogFile() 		
	{
		SDte dtnow;
		char sznow[22];

		dtnow.MakeNow();

		
		if( dtnow.ReadStrPackDate() == m_dtBegin.ReadStrPackDate() )
		{}
		else
		{
			
			(*SClib::p_strcpy())( sznow, dtnow.ReadStringPack().c_str() );

			sznow[8] = 0;

			m_strFnNow = m_strWorkPath + "log" + m_strPrefix + std::string( sznow + 2 ) + std::string(".txt");

			SDte dtold;
			char szold[22];
			SFile fl;
			std::string  strFnOld;	

			dtold.MakeNow();
			dtold.RelativeDay( m_iRelativeDay );
			for( int i = 0; i < 22; i++ )
			{
				dtold.RelativeDay( -1 );
				(*SClib::p_strcpy())( szold, dtold.ReadStringPack().c_str() );
				szold[8] = 0;
				strFnOld = m_strWorkPath + "log" + m_strPrefix + std::string( szold + 2 ) + std::string(".txt"); 
				fl.bind(strFnOld);
				fl.erase();
			}

			m_dtBegin = dtnow;
		}
	}


	std::string RefineStrVal( const std::string & s )
	{
		if( s.size() < 9 && wl::SStrf::sisdec( s.c_str() ) )
		{
			char ss[22];
			unsigned long ul;

			ul = wl::SStrf::satoul(s);
			(*SClib::p_sprintf())( ss, "(0x%02X)", ul );
			return s + ss;
		}
		else
			return s;
	}


	void GetTimeStr( std::string & s )
	{
		char ss[22];
		(*SClib::p_sprintf())( ss, "%s.%03d", (SDte::GetNow().ReadStringPack().c_str() + 9), SDte::Get_msec() );
		ss[9] = 0;
		s = ss;
	}


	void WriteStr( std::string & s1 )
	{
		WashLogFile();

		SFile fl;

		fl.bind(m_strFnNow);
		fl.write_str( s1 + "\n", 1 );
	}


public:

	void InitLog( std::string strWorkPath, std::string strPrefix, int iLogNum )
	{
		if( strWorkPath.empty() )
			m_strWorkPath = "";
		else
			m_strWorkPath = SFile::MkDir2Path(strWorkPath);

		m_strPrefix = strPrefix;
		m_iLogNum = iLogNum;

		m_dtBegin = SDte("1970-1-1 00:00:00");
		WashLogFile();

		std::string s1(66,'-');

		s1 = SDte::GetNow().ReadStringPack() + s1;

		WriteStr( s1 );
	}


	virtual tbool OnBeforeWriteLog( std::string & strLogstr )
	{
		return 1;
	}


	template<class T>
	void WriteLog( T val1 )
	{
		if( !m_biLogEnabled ) return;

		std::stringstream stream1;
		std::string strOut;
		stream1 << val1;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str());

		if( !OnBeforeWriteLog(strOut) )
		{
			return;
		}

		WriteStr(strOut);
	}


	template<class T1, class T2>
	void WriteLog( T1 val1, T2 val2 )
	{
		if( !m_biLogEnabled ) return;

		std::stringstream stream1, stream2;
		std::string strOut;
		stream1 << val1;
		stream2 << val2;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str()) + "\t" + RefineStrVal(stream2.str());

		if( !OnBeforeWriteLog(strOut) )
		{
			return;
		}

		WriteStr(strOut);
	}


	template<class T1, class T2, class T3>
	void WriteLog( T1 val1, T2 val2, T3 val3 )
	{
		if( !m_biLogEnabled ) return;

		std::stringstream stream1, stream2, stream3;
		std::string strOut;
		stream1 << val1;
		stream2 << val2;
		stream3 << val3;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str()) + "\t" + RefineStrVal(stream2.str()) + "\t" + RefineStrVal(stream3.str());

		if( !OnBeforeWriteLog(strOut) )
		{
			return;
		}

		WriteStr(strOut);
	}

};









	
	

	

	




class WBoxLog_t
{
public:
	WCrsc		 m_LogLck;
	tbool		 m_biLogEnabled;

public:
	WBoxLog_t()
	{
		m_biLogEnabled = 1;
	}

	virtual ~WBoxLog_t() {}

public:
	void LogPrintf( int iSize, const char *szstring, ... )
	{
		va_list			args;
		std::string     StringBuffer;
		int				StringLength;

		if( szstring == NULL || *szstring == 0 ) return;
		if( !m_biLogEnabled ) return;
		if( iSize <= 0 ) return;

		StringBuffer.resize( iSize );

		va_start(args, szstring);
		StringLength = (*SClib::p_vsprintf())( &StringBuffer[0], szstring, args);
		va_end(args);

		WCrsc aLock( &m_LogLck );
		OnLogWrite( &StringBuffer[0] );
	}

	
	void LogPrintf( const char *szstring, ... )
	{
		va_list			args;
		std::string     StringBuffer;
		int				StringLength;
		int			iSize = 0;

		if( szstring == NULL || *szstring == 0 ) return;
		if( !m_biLogEnabled ) return;

		for( int i = 0; szstring[i]; i++ )
		{
			char c(szstring[i]);
			iSize++;
			if( c == '%' ) iSize += 9;
			if( c == 's' ) iSize += 90;
			if( c == ' ' ) iSize += 40;
		}

		if( iSize <= 0 ) return;

		StringBuffer.resize( iSize );

		va_start(args, szstring);
		StringLength = (*SClib::p_vsprintf())( &StringBuffer[0], szstring, args);
		va_end(args);

		WCrsc aLock( &m_LogLck );
		OnLogWrite( &StringBuffer[0] );
	}

	
	void LogPrintStr( const char *sz )
	{
		WCrsc aLock( &m_LogLck );
		OnLogWrite( sz );
	}

public:
	virtual void OnLogWrite( const char *sz )
	{
		printf( "%s\n", sz );
	}
};



class WFileBoxLog_t : public WBoxLog_t
{
private:

public:
	FILE * m_fp;

	std::string  m_strWorkPath;
	std::string  m_strPrefix;
	int          m_iDays;

public:
	WFileBoxLog_t()
	{
		m_fp = NULL;

		m_strWorkPath = "." + SFile::GetPathSep();
		m_strPrefix = "LOG";
		m_iDays = 9;
	}

	virtual ~WFileBoxLog_t()
	{
		if( m_fp != NULL )
		{
			fclose(m_fp); 
			m_fp = NULL;
		}
	}

public:
	tbool Open()
	{
		WCrsc aLock( &m_LogLck );
		std::string strFn;
		SDte	dtLast;
		SDte	dtNow;

		dtNow.MakeNow();
		dtLast.Make( "1970-1-1 0:0:0" );

		strFn.resize( 255 );
		(*SClib::p_sprintf())( &strFn[0], "%s%s%d.TXT", m_strWorkPath.c_str(), m_strPrefix.c_str(), dtNow.DiffDay(dtLast) % m_iDays );

		m_fp = (*SClib::p_fopen())("log.txt","ab");

		if( m_fp == NULL ) return 0;

		return 1;
	}

public:
	virtual void OnLogWrite( const char *sz )
	{
		printf( "%s\n", sz );
	}
};






template < int SEQLEN_T = 7 >		
class LOG4_t
{
private:
	int FILENUMBER_i ;
	int CAPACITY_KB_i;		

	WCrsc		 m_LogLck;
	std::string  m_strWorkPath;
	std::vector< std::pair< std::string, std::string  > > m_vProfile;

	
	void load_profile()
	{
		std::vector<std::string> vecSrcFileList;
		WFile wf;
		std::string s1,s2;

		m_vProfile.clear();
		wf.ListAllFile( m_strWorkPath, "*.*", vecSrcFileList, 0, 1, 0, 0 );
		if( vecSrcFileList.empty() ) return;
		for( int i = 0; i < (int)vecSrcFileList.size(); i++ )
		{
			s1 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 0 );
			s2 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 1 );
			s2 = SStrvs::vsa_get( s2, ".", 1, 0 );
			m_vProfile.push_back( std::pair< std::string, std::string  >(s1,s2) );
		}
		std::sort(m_vProfile.begin(), m_vProfile.end());
	}

	
	tbool numberX_reach()  
	{
		long k=0;

		if( (int)m_vProfile.size() > FILENUMBER_i )
		{
			
			return 1;
		}

		if( CAPACITY_KB_i > 0 )
		{
			for( int i = 0; i < (int)m_vProfile.size(); i++ )
			{
				std::string s1,s2;
				WFile wf;

				s1 = m_vProfile[i].first;
				s2 = m_vProfile[i].second;
				wf.bind( m_strWorkPath + s1 + "_" + s2 + ".txt" );
				k += (long)wf.len();
			}
			k /= 1000;

			if( k > CAPACITY_KB_i )
				return 1;
		}

		return 0;
	}

	
	std::string pack_date_str()
	{
		return on_get_pack_date_str();
	}

	
	virtual std::string on_get_pack_date_str()
	{
		return SDte::GetNow().ReadStrPackDate();
		
	}


	tbool day_change()
	{
		if( m_vProfile.empty() )
			return 1;

		if( m_vProfile.rbegin()->second != pack_date_str() )
			return 1;

		return 0;
	}

	
	void add_file()
	{
		std::string s1, s2;

		if( m_vProfile.empty() )
		{
			int i = SEQLEN_T;
			s1 = std::string(i,' ');
		}
		else
		{
			s1 = m_vProfile.rbegin()->first;
		}

		s1 = SStrf::seq( s1.c_str() );

		s2 = pack_date_str();

		m_vProfile.push_back( std::pair< std::string, std::string  >(s1,s2) );

		std::vector< std::pair< std::string, std::string  > > vPF2;

		vPF2 = m_vProfile;
		std::sort(vPF2.begin(), vPF2.end());

		if( m_vProfile.rbegin()->first < vPF2.rbegin()->first )
		{
			for( int i = 0; i < FILENUMBER_i; i++ )
			{
				Purge();
			}
		}
	}

	
	tbool get_small_probability()
	{
		if ( SStrf::rand1() < 0.003 ) return 1;
		return 0;
	}

	
	void Purge()
	{
		WFile wf;
		std::string s1, s2;

		if( m_vProfile.size() ==0 ) return;

		s1 = m_vProfile[0].first;
		s2 = m_vProfile[0].second;
		wf.bind( m_strWorkPath + s1 + "_" + s2 + ".txt" );
		if( !wf.erase() )
		{
			wf.bind( m_strWorkPath + s1 );
			wf.erase();
		}

		load_profile();
	}

public:

	
	tbool Init( std::string strBeginWorkPath , std::string strPrefixName , int filenumber_i = 9 , int capacity_kb_i = 0 )
	{
		FILENUMBER_i = filenumber_i;
		CAPACITY_KB_i = capacity_kb_i;

		WFile wf;

		m_strWorkPath = WFile::MkDir2Path( WFile::MkDir2Path( strBeginWorkPath ) + strPrefixName );
		wf.makedir(m_strWorkPath);
		load_profile();

		for( int i = 0; i < 5 && numberX_reach(); i++ )
		{

			Purge();
		}

		tbool rc;

		rc = day_change();

		if( rc )
			add_file();

		return 1;
	}

	
	void WriteStr( std::string s1 )
	{
		WFile fl;
		WCrsc aLock( &m_LogLck );

		if( m_vProfile.empty() )
			add_file();

		fl.bind( m_strWorkPath + m_vProfile.rbegin()->first + "_" + m_vProfile.rbegin()->second + ".txt" );
		fl.write_str( s1 + "\r\n", 1 );

		if( get_small_probability() && numberX_reach() )
				Purge();

		if( day_change() ||
			( get_small_probability() && get_small_probability() && numberX_reach() )	)
		{
			add_file();
		}
	}

};






template < int SEQLEN_T = 7 >	
class LOG5_t
{
private:
	int FILENUMBER_i ;
	int CAPACITY_KB_i;	

	WCrsc		 m_LogLck;
	std::string  m_strWorkPath;
	std::string  m_strDeviceName;
	std::vector< std::pair< std::string, std::string  > > m_vProfile;

	
	void load_profile()
	{
		std::vector<std::string> vecSrcFileList;
		WFile wf;
		std::string s1,s2,s3;

		m_vProfile.clear();
		wf.ListAllFile( m_strWorkPath, "*.*", vecSrcFileList, 0, 1, 0, 0 );
		if( vecSrcFileList.empty() ) return;
		for( int i = 0; i < (int)vecSrcFileList.size(); i++ )
		{
			s1 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 0 );
			s2 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 1 );
			s3 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 2 );
			s2 = SStrvs::vsa_get( s3, ".", 1, 0 );
			m_vProfile.push_back( std::pair< std::string, std::string  >(s1,s2) );
		}
		std::sort(m_vProfile.begin(), m_vProfile.end());
	}

	
	tbool numberX_reach() 
	{
		long k=0;

		if( (int)m_vProfile.size() > FILENUMBER_i )
		{
			
			return 1;
		}

		if( CAPACITY_KB_i > 0 )
		{
			for( int i = 0; i < (int)m_vProfile.size(); i++ )
			{
				std::string s1,s2;
				WFile wf;

				s1 = m_vProfile[i].first;
				s2 = m_vProfile[i].second;
				
				wf.bind( get_PFn( s1, s2 ) );
				k += (long)wf.len();

				
			}
			k /= 1000;

			if( k > CAPACITY_KB_i )
				return 1;
		}

		return 0;
	}


	std::string pack_date_str()
	{
		return on_get_pack_date_str();
	}

	
	virtual std::string on_get_pack_date_str()
	{
		return SDte::GetNow().ReadStrPackDate();
		
	}


	tbool day_change()
	{
		if( m_vProfile.empty() )
			return 1;

		if( m_vProfile.rbegin()->second != pack_date_str() )
			return 1;

		return 0;
	}


	std::string get_PFn( std::string s1Num, std::string s2Dte )
	{
		return m_strWorkPath + s1Num + "_" + s2Dte + "_" + m_strDeviceName + ".txt";
	}




	
	void add_file()
	{

		std::string s1, s2;


		if( m_vProfile.empty() )
		{

			int i = SEQLEN_T;
			s1 = std::string(i,' ');
		}
		else
		{

			s1 = m_vProfile.rbegin()->first;
		}


		s1 = SStrf::seq( s1.c_str() );
	

		s2 = pack_date_str();

		m_vProfile.push_back( std::pair< std::string, std::string  >(s1,s2) );

		std::vector< std::pair< std::string, std::string  > > vPF2;


		vPF2 = m_vProfile;
		std::sort(vPF2.begin(), vPF2.end());


		if( m_vProfile.rbegin()->first < vPF2.rbegin()->first )
		{

			for( int i = 0; i < FILENUMBER_i; i++ )
			{

				Purge();
			}

		}

	}

	
	tbool get_small_probability()
	{
		if ( SStrf::rand1() < 0.003 ) return 1;
		return 0;
	}

	
	void Purge()
	{
		WFile wf;
		std::string s1, s2;

		if( m_vProfile.size() ==0 ) return;

		s1 = m_vProfile[0].first;
		s2 = m_vProfile[0].second;
		
		wf.bind( get_PFn( s1, s2 ) );

		if( !wf.erase() )
		{
			wf.bind( m_strWorkPath + s1 );
			wf.erase();
		}

		load_profile();
	}

public:
	
	virtual ~LOG5_t()
	{
	}

	
	tbool Init( std::string strBeginWorkPath , std::string strPrefixName , int filenumber_i = 9 , int capacity_kb_i = 0 )
	{
		FILENUMBER_i = filenumber_i;
		CAPACITY_KB_i = capacity_kb_i;

	
		WFile wf;

		m_strWorkPath = WFile::MkDir2Path( strBeginWorkPath );
		m_strWorkPath = WFile::MkDir2Path( m_strWorkPath + strPrefixName );
		m_strDeviceName = strPrefixName;
		wf.makedir(m_strWorkPath);
		load_profile();

	
	

		for( int i = 0; i < 5 && numberX_reach(); i++ )
		{

			Purge();
		}


		tbool rc;

		rc = day_change();
	

		if( rc )
			add_file();


		return 1;
	}


	void WriteStr( std::string s1 )
	{
		WFile fl;
		WCrsc aLock( &m_LogLck );

		if( m_vProfile.empty() )
			add_file();

		
		fl.bind( get_PFn( m_vProfile.rbegin()->first,  m_vProfile.rbegin()->second ) );

		fl.write_str( s1 + "\r\n", 1 );

		if( get_small_probability() && numberX_reach() )
				Purge();

		if( day_change() ||
			( get_small_probability() && get_small_probability() && numberX_reach() )	)
		{
			add_file();
		}
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_wtcp_a01env_net_env_init_h
#define X011__H_w_wtcp_a01env_net_env_init_h



X011_NAMESPACE_BEGIN




class WNet_lib_env_init
{
private:

	int iOpenedByMe;

	static int Net_lib_open(void)
	{
		int ZEROIFSUCCESSFUL = 0;
		WSADATA		Wa;
		return ZEROIFSUCCESSFUL == WSAStartup( MAKEWORD(2,0), &Wa );
	}

	static int Net_lib_close(void)
	{
		return WSACleanup();
	}

public:

	WNet_lib_env_init()
	{
		SOCKET socTestSock;

		iOpenedByMe = 0;
		socTestSock = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );
		if( socTestSock == INVALID_SOCKET )
		{
			if( Net_lib_open() ) iOpenedByMe = 1;
		}
		else
		{
			closesocket(socTestSock);
		}
	 }

	~WNet_lib_env_init()
	{
		if(iOpenedByMe)
		{
			Net_lib_close();
		}
	}
};


static volatile  WNet_lib_env_init  wl_win_net_lib_env___23dmg3n67_obj;


X011_NAMESPACE_END

#endif





#ifndef X011__H_w_WTcpDisConnable_h
#define X011__H_w_WTcpDisConnable_h


X011_NAMESPACE_BEGIN


class WTcpDisConnable : public IRice
{

private:

	WTcpDisConnable & operator = (const WTcpDisConnable & rhs)
	{
		return *this;
	}

	WTcpDisConnable(const WTcpDisConnable & rhs)
	{;}


public:
	class MyTimeKiller : public WThrd
	{
	public:
		WTcpDisConnable * m_ph;
		volatile int  m_iSec100Limit;
		volatile int  m_iSec100;

		MyTimeKiller( WTcpDisConnable * ph, int iSec100Limit )
		{
			m_ph = ph;
			m_iSec100Limit = iSec100Limit;
			m_iSec100 = 0;
		}

		virtual ~MyTimeKiller()
		{
			m_iSec100 = 0;
			tr_shouldbrk();

			
			
			tr_wait();	
		}


		virtual int tr_on_user_run()
		{
			double dIStep = 0.1;

			if( m_iSec100 < m_iSec100Limit )
			{
				WThrd::tr_sleep( 0, dIStep );
				m_iSec100 ++;
				if( this->tr_isShouldBrk() ) return 0;
				return 1;
			}

			if( this->tr_isShouldBrk() ) return 0;

			if(m_ph)
			{
				m_ph->m_biKillFlag = 1;
				m_ph->DisConnNOclear();
			}

			return 0;
		}
	};

public:
	MyTimeKiller *  m_pkiller;
	tbool			m_biKillFlag;
	WTcpDisConnable * m_pBrother;
	WCrsc           m_killerLock;

public:

	void killer_up( double iMaxSec )
	{
		killer_dn() ;

		if(1)
		{
			WCrsc  aaa( &m_killerLock );

			m_pkiller = new MyTimeKiller( this, (int)(iMaxSec * 10) );
			m_pkiller->tr_open();
		}
	}


	void killer_setbegin()
	{
		WCrsc  aaa( &m_killerLock );

		if( m_pkiller != NULL )
		{
			m_pkiller->m_iSec100 = 0;
		}
	}


	void killer_dn()
	{
		if(1)
		{
			WCrsc  aaa( &m_killerLock );

			if( m_pkiller != NULL )
				m_pkiller->tr_shouldbrk();
		}

		while(1)
		{
			int isLive=0;
			if(1)
			{
				WCrsc  aaa( &m_killerLock );

				if( m_pkiller != NULL )
					isLive = m_pkiller->tr_isRunning();
			}
			if(isLive) WThrd::tr_sleep( 0, 0.5 );
			else break;
		}

		if(1)
		{
			WCrsc  aaa( &m_killerLock );

			if( m_pkiller != NULL )
			{
				delete m_pkiller;  
				m_pkiller = NULL;
			}
		}
	}

public:

	WTcpDisConnable()
	{
		m_pkiller = NULL;
		m_biKillFlag = 0;
		m_pBrother = NULL;
	}

	virtual ~WTcpDisConnable()
	{
		killer_dn() ;
	}


	virtual void DisConn()  
	{
			ClearL2Cache();

		OnDisConn();
	}

	
	virtual void DisConnNOclear()
	{
		OnDisConn();
	}


public:

	virtual void OnDisConn() { ; } 

	virtual void on_send_recv_kick()
	{
		killer_setbegin();
		if( m_pBrother ) m_pBrother->killer_setbegin();
	}

}; 



X011_NAMESPACE_END

#endif







#ifndef X011__H_w_wtcp_cell_h
#define X011__H_w_wtcp_cell_h


X011_NAMESPACE_BEGIN


class WTcpCell : public WTcpDisConnable
{

protected:

	SOCKET			m_socRemote;


private:

	WTcpCell & operator = (const WTcpCell & rhs)
	{
		return *this;
	}

	WTcpCell(const WTcpCell & rhs)
	{;}


public:

	WTcpCell()
	{
		m_socRemote = INVALID_SOCKET;

	}

	virtual ~WTcpCell()
	{
		DisConn();
	}


public:

	SOCKET GetRemoteSoc() const
	{
		return m_socRemote;
	}

	void AttachSoc(SOCKET ss)
	{
		m_socRemote = ss;
	}


	static std::string getselfname()
	{
		tchar ss[1024] = {0};
		gethostname(ss,1024);  
		return ss;
	}


	static std::string getipbyname( std::string name )
	{
		hostent * host;
		std::vector<std::string> vecNameParts;

		wl::SStrvs::vsa_imp( name, std::string("."), 1, vecNameParts );
		if( vecNameParts.size()==4 &&
			SStrf::sisdec(vecNameParts[0].c_str()) &&
			SStrf::sisdec(vecNameParts[1].c_str()) &&
			SStrf::sisdec(vecNameParts[2].c_str()) &&
			SStrf::sisdec(vecNameParts[3].c_str())		)
			return name;

		if( name.size() == 0 )
			name = getselfname();

		host = gethostbyname(name.c_str());

		if(host==NULL)
			return "";

		if( host->h_addr_list[0] )
		{
			struct in_addr addr;
			memmove( &addr, host->h_addr_list[0], 4 );
			return inet_ntoa(addr);
		}

		return "";
	}


	static std::string getnamebyip( std::string strIP )
	{
		DWORD dwIPAddr;
		dwIPAddr = inet_addr(strIP.c_str());
		if(dwIPAddr == INADDR_NONE)
		{
			return "";
		}
		else
		{
			hostent * p=gethostbyaddr( (const char *)&dwIPAddr, 4, PF_INET ); 
			if(!p)
			{
				return "";
			}
			else
			{
				return p->h_name;
			}
		}
	}

	
	static std::string get_machineIP()
	{
		return getipbyname( getselfname() );
	}

	
	static unsigned char * Ipstr2Ipbyte( std::string strIp, unsigned char *pOut )
	{
		std::vector<std::string> v1;

		SStrvs::vsa_imp( strIp, std::string("."), 1, v1 );

		for( int i = 0; i < (int)v1.size(); i ++ )
		{
			std::string str1 = v1[i];

			pOut[i] =  (tuint8)SStrf::satol(str1);
		}

		return pOut;
	}

	
	static std::string Ipbyte2Ipstr( unsigned char *pIn )
	{
		std::string str1;

		for( int i = 0; i < 4; i ++ )
		{
			str1 += SStrf::sltoa(pIn[i]);
			str1 += ".";
		}
		str1.erase( str1.end() - 1 );

		return str1;
	}

public:

	virtual void OnDisConn()
	{
		if( m_socRemote == INVALID_SOCKET ) return;

		try
		{
			shutdown( m_socRemote, 2 );
			closesocket(m_socRemote);
			m_socRemote = INVALID_SOCKET ;
		}
		catch(...)
		{
			m_socRemote = INVALID_SOCKET;
		}
	}


public:

	virtual int on_get_defaultrecv_buf_len() 
	{
		return 256;
	}

	virtual int on_sys_recv( SCake & ckDataBuf ) 
	{
		int iDefaultBufLen = on_get_defaultrecv_buf_len();
		ckDataBuf.redim( iDefaultBufLen );

		int i;
		SOCKET s = m_socRemote;

		if(s==INVALID_SOCKET)
		{
			return 0;
		}

		i = (int)::recv(s, ckDataBuf.buf(), (int)ckDataBuf.len(), 0);
		if(i==SOCKET_ERROR||i==0)
		{
			return i = 0;
		}

		ckDataBuf.cut( iDefaultBufLen-i );

		return i;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		int i;
		SOCKET s = m_socRemote;
		if(s==INVALID_SOCKET) return 0; 

		if( ckDataBuf.len() == 0 || !ckDataBuf.buf_const() ) return 0;

		i = (int)::send(s, ckDataBuf, (int)ckDataBuf.len(), 0);
		

		if(i==SOCKET_ERROR)
			i = 0;

		return i;
	}


}; 



X011_NAMESPACE_END

#endif







#ifndef X011__H_w_wtcp_cellc_h
#define X011__H_w_wtcp_cellc_h


X011_NAMESPACE_BEGIN


class WTcpCellc : public WTcpCell
{

private:

	WTcpCellc & operator = (const WTcpCellc & rhs)
	{
		return *this;
	}

	WTcpCellc(const WTcpCellc & rhs)
	{;}


public:


	WTcpCellc()
	{
	}


	virtual ~WTcpCellc()
	{
	}


	tbool Conn_udp( std::string name, u_short port )
	{
		struct	sockaddr_in		saddr ;

		m_socRemote = socket(AF_INET, SOCK_DGRAM, 0);

		if( m_socRemote == INVALID_SOCKET)
		{
			return 0;
		}

		
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET;
		saddr.sin_port = htons( (u_short)port );
		
		saddr.sin_addr.s_addr = inet_addr( getipbyname(name).c_str() );

		if( 0 != ::connect( m_socRemote, (struct sockaddr *)&saddr, sizeof(saddr) )  )
		{
			return 0;
		}

		return 1;
	}

	
	int send_udp( void *pdata, int ilen )
	{
		return send( m_socRemote, (const char *)pdata, ilen, 0 );
	}

	
	int send_udp( const SCake & ck )
	{
		if( ck.len() == 0 ) return 0;
		return send_udp( (void*)ck.buf_const(), (int)ck.len() );
	}

	
	int recv_udp( char *buf, int ilen )
	{
        return recv( m_socRemote, buf, ilen, 0 );
	}

	
	int recv_udp( SCake & ck )
	{
		if( ck.len() == 0 ) return 0;
		return recv_udp( ck.buf(), (int)ck.len() );
	}



	tbool Conn( std::string name, u_short port )
	{
		struct	sockaddr_in		saddr ;

		DisConn();

		m_socRemote = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socRemote == INVALID_SOCKET )
		{
			return 0;
		}

		
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET;
			
			saddr.sin_addr.s_addr = inet_addr( getipbyname(name).c_str() );
		saddr.sin_port = htons( (u_short)port );

		if(SOCKET_ERROR == ::connect( m_socRemote, (struct sockaddr *)&saddr, sizeof(saddr) )  )
		{
			return 0;
		}

		return 1;
	}



	tbool Conn( std::string name, std::string port )
	{
		return this->Conn( name, static_cast<u_short>(SStrf::satol(port.c_str()) ) );
	}



	tbool Conn( std::string strAddrLst ) 
	{
		std::vector<std::string> vecAddr1;

		SStrvs::vsa_imp( strAddrLst, std::string("|"), 1, vecAddr1 );

		for( int i = 0; i < (int)vecAddr1.size(); i ++ )
		{
			std::string strAddr = vecAddr1[i];

			try
			{
				std::vector<std::string> vecNameParts;
				SStrvs::vsa_imp( strAddr, std::string(":"), 1, vecNameParts );
				vecNameParts.push_back( std::string("") );
				vecNameParts.push_back( std::string("") );
				if( this->Conn( vecNameParts[0], vecNameParts[1] ) ) return 1;
			}
			catch(...)
			{
				
				return 0;
			}
		}

		return 0;
	}


}; 








class WTcpFtp : public WTcpCellc
{
private:

	WTcpFtp & operator = (const WTcpFtp & rhs)
	{
		return *this;
	}

	WTcpFtp(const WTcpFtp & rhs)
	{;}

public:

	WTcpFtp()
	{
	}

	virtual ~WTcpFtp()
	{
	}

public:

	
	std::string read_welcome_msg()
	{
		std::string str1;
		SCake ck;

		do{
			this->recv_ln( ck, "\n" );
			if( ck.len() == 0 ) return "";
			str1 = ck.mk_str();
			if( str1.size() < 3 ) return "";
			if( str1.size() == 3 ) return str1;
			if( str1.size() > 3 && str1[3] != '-' ) return str1;
		}while( str1.size() >= 4 && str1[3] == '-' );

		return "";
	}

	
	tbool FtpLogin( std::string strUser, std::string strPass )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;

		
		
		
		
		
		str1 = read_welcome_msg();


		iRc = this->send_str( "user " + strUser + "\r\n" );
		if( !iRc ) return 0;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 331 ) return 0;

		
		iRc = this->send_str( "pass " + strPass + "\r\n" );
		if( !iRc ) return 0;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 230 ) return 0;

		
		iRc = this->send_str( "type i\r\n" );
		if( !iRc ) return 0;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		return 1;
	}

	
	std::string FtpPwd() 
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;

		
		iRc = this->send_str( "pwd\r\n" );
		if( !iRc ) return "";
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 257 ) return "";
		return str1;
	}

	
	tbool FtpCwd( std::string t ) 
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;

		
		iRc = this->send_str( "cwd " + t + "\r\n" );
		if( !iRc ) return 0;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;
		return 1;
	}

	
	std::string FtpPasv() 
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		std::vector<std::string> vec1;
		long lport;

		
		iRc = this->send_str( "pasv\r\n" );
		if( !iRc ) return "";
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 227 ) return "";

		SStrvs::vsa_imp( str1, std::string("("), 1, vec1 );
		if( vec1.size() < 2 ) return "";

		str1 = vec1[1];
		vec1.clear();

		SStrvs::vsa_imp( str1, std::string(","), 1, vec1 );
		if( vec1.size() < 6 ) return "";
		lport = SStrf::satol(vec1[4]) * 256 + SStrf::satol(vec1[5]);
		str1 = vec1[0] + "." + vec1[1] + "." + vec1[2] + "." + vec1[3] + ":" + SStrf::sltoa(lport);

		return str1;
	}

	
	std::string FtpList()
	{
		std::string str1;
		std::string strRtn;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc c;

		
		str1 = this->FtpPasv();
		if( str1.empty() ) return "";
		if( !c.Conn(str1) ) return "";

		iRc = this->send_str( "list\r\n" );
		if( !iRc ) return "";

		c.recv_all( ck );
		if( ck.len() == 0 ) return "";
		strRtn = ck.mk_str();

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return "";

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return "";

		return strRtn;
	}


	tbool FtpStor( std::string strFn, const SCake & ckData, WTcpCellc *pc = NULL )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc cc;

		if( ckData.len() == 0 ) return 0;

		if( pc == NULL ) pc = &cc;

		
		str1 = this->FtpPasv();
		if( str1.empty() ) return 0;

		if( !pc->Conn(str1) ) return 0;

		iRc = this->send_str( "stor " + strFn + "\r\n" );
		if( !iRc )
		{
			pc->DisConn();
			return 0;
		}

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 )
		{
			pc->DisConn();
			return 0;
		}

		pc->send_bin( ckData );

		pc->DisConn();

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		return 1;
	}


	
	tbool FtpStor_begin( std::string strFn, WTcpCellc &cc )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc *pc;

		pc = &cc;

		
		str1 = this->FtpPasv();
		if( str1.empty() ) return 0;

		if( !pc->Conn(str1) ) return 0;

		iRc = this->send_str( "stor " + strFn + "\r\n" );
		if( !iRc )
		{
			pc->DisConn();
			return 0;
		}

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 )
		{
			pc->DisConn();
			return 0;
		}

		return 1;
	}

	
	tbool FtpStor_mid( const SCake & ckData, WTcpCellc &cc )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc *pc;

		if( ckData.len() == 0 ) return 0;

		pc = &cc;

		pc->send_bin( ckData );

		return 1;
	}


	tbool FtpStor_end( WTcpCellc &cc )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc *pc;

		pc = &cc;

		pc->DisConn();

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		return 1;
	}



	
	tbool FtpRetr( std::string strFn, SCake & ckData, WTcpCellc *pc = NULL )
	{
		std::string str1;
		std::string strRtn;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc cc;

		if( pc == NULL ) pc = &cc;

		
		str1 = this->FtpPasv();
		if( str1.empty() ) return 0;

		if( !pc->Conn(str1) ) return 0;

		iRc = this->send_str( "retr " + strFn + "\r\n" );
		if( !iRc )
		{
			pc->DisConn();
			return 0;
		}

		pc->recv_all_f( ckData );
		if( ckData.len() == 0 )
		{
			pc->DisConn();
			return 0;
		}

		pc->DisConn();

		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		return 1;
	}


	tbool FtpBye()
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;

		
		iRc = this->send_str( "quit\r\n" );
		if( !iRc ) return 1;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 221 ) return 1; 
		return 1;
	}
};





class WDte : public SDte
{
private:

	typedef struct
	{
		tint32 L1;
		tint32 Version;
		tint32 mode;
		char stratum;
		char poll;
		char precision;
		tuint32 root_delay;
		tuint32 root_dispersion;
		tuint32 reference_identifier;
		tint64 reference_timestamp;
		tint64 originate_timestamp;
		tint64 receive_timestamp;
		tint64 transmit_timestamp;
	}	ntp;

	tuint32  TIMEDIFF; 
	tuint32  NTP_HEAD_LEN ; 

	void pack_ntp_data(char *buf, ntp const *ntp_packet)
	{
		memset(buf, 0x00, NTP_HEAD_LEN);

		buf[0] = (char) ( (ntp_packet->L1<<6) | (ntp_packet->Version<<3) | (ntp_packet->mode) );
		buf[1] = ntp_packet->stratum;
		buf[2] = ntp_packet->poll;
		buf[3] = ntp_packet->precision;
		memcpy(buf + 4, &ntp_packet->root_delay, 2);
		
		memcpy(buf + 40, &ntp_packet->transmit_timestamp, 4);
	}

	void unpack_ntp_data(char *data)
	{
		tint64 transmit_time;

		memcpy(&transmit_time, data + 32, 4);
		transmit_time = ntohl((tsize)transmit_time) - TIMEDIFF;
		
		
		
		
		
		
		
		this->Make("1970-1-1 0:0:0");
		this->RelativeSec( (int)transmit_time );
		this->RelativeSec( 8 * 60 * 60 );
	}

public:

public:

	WDte()
	{
		TIMEDIFF = 0x83aa7e80;
		NTP_HEAD_LEN = 48;
	}

	virtual ~WDte() { ; }

	tbool NtpMakeCnTimeNow( std::string strServer , int iPort = 123, int iTimeOutSec = 15 ) 
	{
		WTcpCellc  cc;
		tbool iRc = 0;
		int iRtn;
		ntp ntp_packet;
		char *buf;
		SCake buf2;

		buf2.redim(NTP_HEAD_LEN);
		buf = buf2.buf();

		iRc = cc.Conn_udp( strServer, (u_short)iPort );
		if( !iRc ) return 0;

		ntp_packet.L1 = 0;
		ntp_packet.Version = 3;
		ntp_packet.mode = 3;
		ntp_packet.stratum = 0;
		ntp_packet.poll = 5;
		ntp_packet.root_delay = 0;
		ntp_packet.precision = (char)(-6);
		ntp_packet.transmit_timestamp = 0;

		pack_ntp_data(buf, &ntp_packet);

		if( iTimeOutSec > 0 ) cc.killer_up( iTimeOutSec );
		

		iRtn = cc.send_udp( buf, NTP_HEAD_LEN );
		if ( iRtn != NTP_HEAD_LEN ) return 0;

		iRtn = cc.recv_udp( buf, NTP_HEAD_LEN );

		if( iTimeOutSec > 0 ) cc.killer_dn();

		if( iRtn == NTP_HEAD_LEN )
		{
			unpack_ntp_data(buf);
			return 1;
		}

		return 0;
	}

	tbool NtpMakeCnTimeNow()
	{
		if( NtpMakeCnTimeNow("0.cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("0.tw.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("1.cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("1.tw.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("2.cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("2.tw.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("3.cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("3.tw.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("tw.pool.ntp.org") ) return 1;
		return 0;
	}

};




class WTftp
{
public:

	WTftp()
	{
	}

	virtual ~WTftp() { ; }

public:

	
	tbool TFtpGet2( std::string strServerIp, int iPort, std::string strFn, SCake & ckData )
	{
		WTcpCellc  cc;
		tbool iRc;
		int iRtn;
		char *buf;
		SCake buf2;
		int buflen;


		buf2.redim(555);
		buf = buf2.buf();

		iRc = cc.Conn_udp( strServerIp, (u_short)iPort );
		if( !iRc ) return 0;

		buflen = (*SClib::p_sprintf())( buf, "%c%c%s%c%s%c", 0, 1, strFn.c_str(), 0, "octet", 0 );
		iRtn = cc.send_udp( buf, buflen );
		if ( iRtn != buflen ) return 0;


		char command;
		char serial = 0;

		ckData.redim(0);

		do{
			buflen = cc.recv_udp( buf,516 ); 	

			if(buflen == -1)
			{
				break;
			}

			command = buf[1];
			if(command == 3)
			{
				if(serial < buf[3])
				{
					serial = buf[3];
					ckData.append(buf+4,buflen-4);
				}
				buf[1] = 4;
				cc.send_udp( buf, 4 ); 
			}
			else if(command == 5)
			{
				break;
			}

		}while(buflen == 516);

		return 1;
	}


	tbool TFtpGet( std::string strServerIp, int iPort, std::string strFn, SCake & ckData, int iTimeOutSec = 15 )
	{
		WTcpCellc  cc;
		FILE * fp = NULL;
		unsigned short p_num = 0;
		char buf[516] = "";
		volatile unsigned char cmd = 0;
		volatile unsigned int len = 0;
		struct sockaddr_in addr;
		struct sockaddr_in cliaddr;
		int addrlen = sizeof(addr);
		SOCKET udpfd;

		len = (*SClib::p_sprintf())(buf,"%c%c%s%c%s%c", 0, 1, strFn.c_str(), 0, "octet", 0);    

		addr.sin_family = AF_INET;
		addr.sin_port = htons( (u_short)iPort );
		addr.sin_addr.s_addr = inet_addr( WTcpCell::getipbyname(strServerIp).c_str() );


		if( (udpfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
		{
			return 0;
		}

		cc.AttachSoc(udpfd);

		sendto(udpfd, buf, len, 0, (struct sockaddr *)&addr, sizeof(addr));

		if( iTimeOutSec > 0 ) cc.killer_up( iTimeOutSec );

		do{
			if( iTimeOutSec > 0 ) cc.killer_setbegin();

			
			len = recvfrom(udpfd, buf, sizeof(buf), 0, (struct sockaddr*)&cliaddr, &addrlen);
			cmd = buf[1];
			

			if( cmd == 3 )    
			{
				
				if( p_num < ntohs(*(unsigned short*)(buf+2) ))
				{
					ckData.append(buf+4,len-4);	
					p_num = ntohs(*(unsigned short*)(buf+2));
					
				}
				buf[1] = 4;
				sendto(udpfd, buf, 4, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
			}
			else if( cmd == 6 ) 
			{
				 buf[0] = 0; buf[1] = 4; buf[2] = 0; buf[3] = 0;
				 sendto(udpfd, buf, 4, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
				 continue;
			}
			else if( cmd==5 ) 
			{
				
				closesocket(udpfd);
				return 0;
			}
		}while((len == 516)||(cmd == 6)); 

		if( iTimeOutSec > 0 ) cc.killer_dn();

		closesocket(udpfd);

		if( ckData.len() == 0 ) return 0;

		return 1;
	}

};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_WTcpListener_h
#define X011__H_w_WTcpListener_h


X011_NAMESPACE_BEGIN


class WTcpListener
{

private:

	SOCKET	m_socLocalListener;
	

private:

	WTcpListener & operator = (const WTcpListener & rhs)
	{
		return *this;
	}

	WTcpListener(const WTcpListener & rhs)
	{;}


public:

	u_short		m_port;

	u_long		m_u_in_addr;


	WTcpListener( )
	{
		m_socLocalListener = INVALID_SOCKET;
		
		m_port = 0;
	}

	virtual ~WTcpListener( )
	{
		this->StopListen();
	}


	
	


	tbool Listen( u_short port,  u_long a_in_addrip = INADDR_ANY, int listener_num = 4 )
	{
		struct	sockaddr_in	 saddr;

		m_port = port;
		m_u_in_addr = a_in_addrip;

		if ( 0 == port )
		{
			
		}

		m_socLocalListener = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET;
		saddr.sin_port = htons( (u_short)port );
		
		saddr.sin_addr.s_addr = a_in_addrip;

		if( SOCKET_ERROR == bind( m_socLocalListener, (struct sockaddr *)&saddr, sizeof(saddr) ))
		{
			this->StopListen();
			
			return 0;
		}

		if( 0 == ::listen( m_socLocalListener, listener_num ) )
		{
			return 1;
		}
		else
		{
			
			return 0;
		}
	}


	tbool Listen( u_short uport, const tchar * sz_addrip ) 
	{
		if( sz_addrip && *sz_addrip )
		{
			return this->Listen( uport, inet_addr( sz_addrip ) ) ;
		}

		return this->Listen( uport );
	}


	tbool Listen( std::string strport, const tchar * sz_addrip )
	{
		return this->Listen( (u_short)SStrf::satol(strport) , sz_addrip );
	}


	tbool Listen( std::string straddr ) 
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( straddr, std::string(":"), 1, vecNameParts );
			if( vecNameParts.size() == 1 )
			{
				vecNameParts.insert( vecNameParts.begin(), std::string("") );
			}

			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return Listen( vecNameParts[1], vecNameParts[0].c_str() );
		}
		catch(...)
		{
			return 0;
		}
	}


	void StopListen(void)
	{
		if( m_socLocalListener != INVALID_SOCKET )
		{
			closesocket( m_socLocalListener );
			m_socLocalListener = INVALID_SOCKET;
		}
	}


	tbool AcceptNewSvr( SOCKET & socNewSvr, std::string & strRtnRemoteIP )
	{
		struct	sockaddr_in	 from;
		int nSize;

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		nSize= sizeof(from);
		socNewSvr = ::accept( m_socLocalListener, (struct sockaddr *)&from, &nSize ); 
		if( socNewSvr == INVALID_SOCKET )
		{
			strRtnRemoteIP = "";
			return 0;
		}
		else
		{
			strRtnRemoteIP = inet_ntoa( from.sin_addr ) ; 
			return 1;
		}
	}


}; 



X011_NAMESPACE_END

#endif






#ifndef X011__H_w_wtcp_cells_h
#define X011__H_w_wtcp_cells_h


X011_NAMESPACE_BEGIN


class WTcpCells : public WTcpCell
{

public:

	std::string m_strRemoteIPAddress;


private:

	WTcpCells & operator = (const WTcpCells & rhs)
	{
		return *this;
	}

	WTcpCells(const WTcpCells & rhs)
	{;}


public:

	WTcpCells()
	{
		m_strRemoteIPAddress="";
	}


	virtual ~WTcpCells()
	{	m_strRemoteIPAddress="";
	}


	operator const std::string & () const
	{
		return m_strRemoteIPAddress;
	}


	std::string GetRemoteIPAddress() const
	{
		return m_strRemoteIPAddress;
	}


	tbool Conn( WTcpListener & aListener)
	{
		int iRc;

		iRc = aListener.AcceptNewSvr( m_socRemote , m_strRemoteIPAddress );

		if(!iRc) return 0;

		
		return 1;
	}


	tbool Conn( WTcpListener * pListener)
	{
		if(!pListener)
			return 0;

		return this->Conn(*pListener);
	}


}; 




X011_NAMESPACE_END


#endif






#ifndef X011__H_w_WTcpHttp_h
#define X011__H_w_WTcpHttp_h


X011_NAMESPACE_BEGIN


class WTcpHttp : public WTcpCellc
{
public:

	typedef std::map< std::string, std::string >	MAP_HTTPHEADPARA;
	typedef MAP_HTTPHEADPARA::iterator				MAP_HTTPHEADPARA_IT;
	typedef MAP_HTTPHEADPARA::value_type			MAP_HTTPHEADPARA_VT;


private:

	MAP_HTTPHEADPARA m_mapUrlHeadPara;

	MAP_HTTPHEADPARA m_mapSvrRtnHeadPara;


private:

	WTcpHttp & operator = (const WTcpHttp & rhs)
	{
		return *this;
	}

	WTcpHttp(const WTcpHttp & rhs)
	{;}


public:

	std::string m_strProxyAddr;


public:

	WTcpHttp()
	{
		m_strProxyAddr = "";
		ClearUrlHeadPara();
	}


	WTcpHttp( int iMaxSec ) 
	{
		killer_up( iMaxSec );

		m_strProxyAddr = "";
		ClearUrlHeadPara();
	}


	virtual ~WTcpHttp()
	{
		m_strProxyAddr = "";
	}



	static std::string GetRegIEProxyAddr()
	{
		std::string strProxyAddr("");
		int iProxyEnable;
		SCake ckProxySetting;

		do
		{
			iProxyEnable = WReg32::ReadUInt( HKEY_CURRENT_USER,
											"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
											"ProxyEnable"	);
			if( !iProxyEnable )
			{
				break;
			}

			strProxyAddr = WReg32::ReadStr( HKEY_CURRENT_USER,
											"Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings",
											"ProxyServer"	);

			ckProxySetting.lets( strProxyAddr );

			if( !SStrf::sstr( ckProxySetting, '=' ) ) 
			{
				break;
			}

			std::map<std::string,std::string> mapProxyPrpt;
			SStrf::slcase(ckProxySetting);
			SStrvs::vsa2v_prpt( std::string(ckProxySetting), std::string(";"), std::string("="), mapProxyPrpt );

			strProxyAddr = mapProxyPrpt[std::string("http")];

		}while(0);

		return strProxyAddr;
	}


	const std::string & SetProxyAddr( std::string strPxyAddr )
	{
		return m_strProxyAddr = strPxyAddr;
	}


	const std::string & SetProxyAddrAuto()
	{
		return SetProxyAddr( GetRegIEProxyAddr() );
	}


	void ClearUrlHeadPara()
	{
		m_mapUrlHeadPara.clear();
	}


	void AddUrlHeadPara( std::string strName, std::string strValue )
	{
		m_mapUrlHeadPara.insert( MAP_HTTPHEADPARA_VT( strName, strValue ) );
	}


	void ClearSvrRtnHeadPara()
	{
		m_mapSvrRtnHeadPara.clear();
	}


	static void MakeHeadParaMap( const std::string & strHeadPart , MAP_HTTPHEADPARA & hm )
	{
		hm.clear();

		std::vector<std::string> vecTmpTR, vecTmpTD;
		std::vector<std::string>::iterator itTR;
		SStrvs::vsa_imp( strHeadPart, std::string("\r\n"), 1, vecTmpTR );
		for( itTR = vecTmpTR.begin(); itTR!=vecTmpTR.end(); ++itTR )
		{
			SCake ck;
			ck.lets( itTR->c_str() );
			tchar *p = SStrf::sstr( ck.buf(), ":" );
			if( p )
			{
				*p = 0;
				p++;
				SStrf::strim( p );
			}
			else
			{
				
				p=NULL;
			}

			SStrf::strim( ck.buf() );
			vecTmpTD.push_back( ck.buf() );
			vecTmpTD.push_back( p ? p : "" );

			hm.insert( MAP_HTTPHEADPARA_VT( vecTmpTD[0], vecTmpTD[1] ) );
			vecTmpTD.clear();
		}

	}


	void ImportSvrRtnHeadPara( const std::string & strHeadPart )
	{
		


		MakeHeadParaMap( strHeadPart, m_mapSvrRtnHeadPara );
	}


	void ImportSvrRtnHeadPara( SCake ckHeadPart )
	{
		ImportSvrRtnHeadPara( std::string(ckHeadPart.mk_sz() ) );
	}

	MAP_HTTPHEADPARA GetSvrRtnHeadPara() const
	{
		return m_mapSvrRtnHeadPara;
	}

	std::string GetSvrRtnHeadParaVal( const std::string & strParaName )
	{
		return m_mapSvrRtnHeadPara[strParaName];
	}


	static void GetLine1ParaFromHead( const std::string & strHttpHead ,
										std::string & rstrCmdLine1 ,
										std::string & rstrCmdVerb ,
										std::string & rstrProtocolName ,
										std::string & rstrAddr ,
										std::string & rstrUPfn				)
	{
		SCake ck;
		std::string strSep;
		std::string strAddrTmp;

		std::string strCmdLine1, strCmdVerb, strProtocolName, strAddr;

		ck.lets( strHttpHead );

		strCmdLine1 = SStrvs::vsa_get( strHttpHead, std::string("\n"), 1, 0 );
		SStrf::strim( strCmdLine1 );

		strCmdVerb = SStrvs::vsa_get( strCmdLine1, std::string(" "), 1, 0 );

		
		ck.lets( strCmdLine1 );
		for( char *p = SStrf::splast( ck.buf() ); p != ck.buf(); p-- )
		{
			if( *p == ' ' )
			{
				*p = 0;
				break;
			}
		}

		strAddrTmp = ck.buf();

		
		if( strAddrTmp.find( "/" ) != std::string::npos && strAddrTmp.find( "://" ) == std::string::npos )
		{
			if( strAddrTmp.find( " /" ) != std::string::npos )
			{
				MAP_HTTPHEADPARA m;
				std::string s2(strHttpHead);
				SStrf::slcase( s2 );
				MakeHeadParaMap( s2, m );
				SStrf::sreplstr( strAddrTmp, " ", " http://" + m["host"] );
			}
			else
			{
				SStrf::sreplstr( strAddrTmp, " ", " http://" );
			}
		}


		strProtocolName = SStrvs::vsa_get( strAddrTmp, std::string("://"), 1, 0 );
		ck.lets( strProtocolName );
		SStrf::srev( ck.buf() );
		SStrf::sreplch( ck.buf(), ' ', 0 );
		strProtocolName = SStrf::srev( ck.buf() );


		

		if( strAddrTmp.find( "/" ) != std::string::npos )
		{
			strSep = "/";
		}
		else
		{
			strSep = " ";
		}
		strAddr = SStrvs::vsa_get( strAddrTmp, strSep, 1, 1 );


		if(1)
		{
			std::string str80("80");
			std::string s1(strProtocolName);

			SStrf::slcase( s1 );
			

			if( strAddr.find( ":" ) == std::string::npos ) strAddr += ":" + str80;

			if( *SStrf::splast( strAddr.c_str() ) == ':' ) strAddr += str80;
		}

		
		rstrCmdLine1 = strCmdLine1;
		rstrCmdVerb = strCmdVerb;
		rstrProtocolName = strProtocolName;
		rstrAddr = strAddr;

		rstrUPfn = SStrvs::vsa_get( strCmdLine1, std::string(" "), 1, 1 );
		rstrUPfn = SStrvs::vsa_get( rstrUPfn, std::string(" "), 1, 0 );
	}


	static std::string GetHostAddrFromUrl( std::string  strUrl )
	{
		std::string strConnWho;

		
		

		SStrf::strim( strUrl );
		strUrl = "a " + strUrl + " a"; 

		std::string s1;

		GetLine1ParaFromHead( strUrl, s1, s1, s1, strConnWho, s1 );

		return strConnWho;
	}



	static std::string GetResPathnameFromUrl( std::string  strUrl )
	{
		std::string::size_type ssti;
		std::string s;

		
		s = GetHostAddrFromUrl( strUrl );
		s = SStrvs::vsa_get( std::string(s), std::string(":"), 1, 0 );


		ssti = strUrl.find( s );
		if(ssti==std::string::npos) return "";
		ssti += s.size() /2;


		ssti = strUrl.find( '/', ssti );
		if(ssti==std::string::npos) return "/";	 


		return strUrl.c_str() + ssti;
	}



	tbool ConnUrl( std::string strUrl )
	{
		tbool iRc;
		std::string strConnWho;

		do 
		{
			iRc = 0;

			strConnWho = GetHostAddrFromUrl( strUrl );

			if( m_strProxyAddr.length() ) strConnWho = m_strProxyAddr;

			if( !Conn( strConnWho ) ) break;

			iRc = 1;

		}while(0);

		return iRc;
	}


	tbool SendHttpGet( std::string strUrl, std::string strHttpVer = "HTTP/1.0" , tbool bSmartSendResPathname = 1 , tbool bCleanUrlPara = 1 )
	{
		std::string strSnd;
		tbool iRc;
		std::string strConnWho;

		if(bSmartSendResPathname) 
		{
			

			if( this->m_strProxyAddr != "" ) 
			{
				
			}
			else
			{
				
				strUrl = GetResPathnameFromUrl( strUrl );
			}
		}

		strSnd =  "GET " + strUrl + " " + strHttpVer + "\r\n";

		AddUrlHeadPara( "Accept-language", "zh-cn" );
		
		AddUrlHeadPara( "User-Agent", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322)" );
		
		AddUrlHeadPara( "Pragma", "no-cache" );
		AddUrlHeadPara( "cache_control", "no-cache" );
		AddUrlHeadPara( "Cache-Control", "no-cache" );
		
		
		
		


		for( MAP_HTTPHEADPARA_IT it = m_mapUrlHeadPara.begin(); it != m_mapUrlHeadPara.end(); ++it )
		{
			strSnd += it->first;
			strSnd += ": ";
			strSnd += it->second;
			strSnd += "\r\n";
		}

		if(bCleanUrlPara)
		{
			ClearUrlHeadPara();
		}

		strSnd += "\r\n";


		do
		{
			iRc = 0;

			iRc = send_str( strSnd );

		}while(0);

		return iRc;
	}


#ifdef VC6_COMPATIBLE_X011_
	
#else
	SCake SimpleHttpGetFile( std::string strUrl, int iMaxTimeoutSec = 11 )
	{
		WTcpHttp & h(*this);
		std::string & s(strUrl);
		SCake ckTmp;

		

		
		if( h.ConnUrl( s ) )
		{
			h.killer_up( iMaxTimeoutSec );

			AddUrlHeadPara( "Connection", "close" );
			h.SendHttpGet( s, "HTTP/1.0" );

			h.recv_ln( ckTmp, "\r\n\r\n" );

			h.ImportSvrRtnHeadPara( ckTmp );
			int i;
			i = atol( h.GetSvrRtnHeadParaVal( "Content-Length" ).c_str() );

			if( i <= 0 ) return SCake();

			h.recv_len( ckTmp , i );
			h.DisConn();
		}

		return ckTmp;
	}
#endif


}; 




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_WTcpEmailc_h
#define X011__H_w_WTcpEmailc_h


X011_NAMESPACE_BEGIN


class WTcpEmailc
{
private:

	WTcpEmailc & operator = (const WTcpEmailc & rhs)
	{
		return *this;
	}

	WTcpEmailc(const WTcpEmailc & rhs)
	{;}

protected:
	
	IRice	* m_pCellc;

public:

	WTcpEmailc()
	{
		m_pCellc = NULL;
	}

	virtual ~WTcpEmailc()
	{	;
	}

public:
	
	void LinkCellc( IRice * p )
	{
		m_pCellc = p;
	}
	
	void LinkCellc( IRice & r )
	{
		m_pCellc = &r;
	}

	
	std::string read_ack_msg()
	{
		std::string str1;
		SCake ck;

		do{
			m_pCellc->recv_ln( ck, "\n" );
			if( ck.len() == 0 ) return "";
			str1 = ck.mk_str();
			if( str1.empty() ) return "";
			if( str1[0] == '-' ) return str1;
			if( str1[0] == '+' ) return str1;
		}while(1);

		return "";
	}

	
	std::string read_welcome_msg()
	{
		std::string str1;
		SCake ck;

		do{
			m_pCellc->recv_ln( ck, "\n" );
			if( ck.len() == 0 ) return "";
			str1 = ck.mk_str();
			if( str1.size() < 3 ) return "";
			if( str1.size() == 3 ) return str1;
			if( str1.size() > 3 && str1[3] != '-' ) return str1;
		}while( str1.size() >= 4 && str1[3] == '-' );

		return "";
	}

	
	std::string get_t1( std::string strUser, std::string strPass )  
	{
		SCake ck;
		tbool rc;
		std::string str1;
		int statmax;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		rc = m_pCellc->send_str( "user " + strUser + "\r\n" ); 
		if( !rc ) return "";

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		rc = m_pCellc->send_str( "pass " + strPass + "\r\n" ); 
		if( !rc ) return "";

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		rc = m_pCellc->send_str( "stat\r\n" ); 
		if( !rc ) return "";

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		statmax = SStrf::satol( str1.c_str() + 3 );

		rc = m_pCellc->send_str( "top " + SStrf::sltoa(statmax) + " 1\r\n" ); 
		if( !rc ) return "";

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		std::vector<std::string> vecstrSeperate;

		vecstrSeperate.push_back("\n.\n");
		vecstrSeperate.push_back("\r\n.\r\n");

		m_pCellc->recv_ln( ck, vecstrSeperate );
		str1 = ck.mk_str();

		std::string strUpper = str1;

		SStrf::sucase(strUpper);

		std::string::size_type i = strUpper.find("SUBJECT: ");
		std::string::size_type i2 = i + SStrf::slen("SUBJECT: ");

		
		if(1)
		{
			rc = m_pCellc->send_str( "quit\r\n" ); 
			

			read_ack_msg();
			

		}

		for( ; i != std::string::npos && i < str1.size() ; i++ )
		{
			if( str1[i] == 0x0d || str1[i] == 0x0a )
			{
				str1[i] = 0;
				return &(str1[i2]);
			}
		}

		return str1;
	}

	
	virtual tbool on_before_get_t2_del( std::string strNowTitle, std::string strNowSender )
	{
		return 0;
	}


	tbool get_t2( std::string strUser, std::string strPass, std::vector< std::string > *pvSubject, std::vector< std::string > *pvFrom )
	{
		SCake ck;
		tbool rc;
		std::string str1;
		int statnum;
		int statnum1;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return 0; 

		rc = m_pCellc->send_str( "user " + strUser + "\r\n" ); 
		if( !rc ) return 0;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return 0; 

		rc = m_pCellc->send_str( "pass " + strPass + "\r\n" ); 
		if( !rc ) return 0;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return 0; 

		rc = m_pCellc->send_str( "stat\r\n" ); 
		if( !rc ) return 0;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return 0; 
		statnum = SStrf::satol( str1.c_str() + 3 );

		if(pvSubject) pvSubject->clear();
		if(pvFrom) pvFrom->clear();
		for( statnum1 = 1 ; statnum1 <= statnum; statnum1 ++ )
		{
			rc = m_pCellc->send_str( "top " + SStrf::sltoa(statnum1) + " 1\r\n" ); 
			if( !rc ) return 0;

			str1 = read_ack_msg();
			if( str1.empty() || str1[0] != '+' ) return 0; 

			std::vector<std::string> vecstrSeperate;

			vecstrSeperate.push_back("\n.\n");
			vecstrSeperate.push_back("\r\n.\r\n");

			m_pCellc->recv_ln( ck, vecstrSeperate );
			str1 = ck.mk_str();


			std::string strNowTitle, strNowSender;
			std::string *ps=NULL;

			if(pvSubject) pvSubject->push_back("");
			if(pvFrom) pvFrom->push_back("");

			if(pvSubject) ps = &(*(pvSubject->rbegin()));
			if(1) 
			{
				std::string strKey = "aSUBJECT: ";
				std::string str2 = str1;
				std::string strUpper = str2;

				strKey[0] = 0x0a;
				SStrf::sucase(strUpper);

				std::string::size_type i1 = strUpper.find(strKey);
				std::string::size_type i2 = i1 + SStrf::slen(strKey.c_str());

				if( i1 != std::string::npos ) i1++;

				for( ; i1 != std::string::npos && i1 < str2.size() ; i1++ )
				{
					if( str2[i1] == 0x0d || str2[i1] == 0x0a )
					{
						str2[i1] = 0;
						strNowTitle = &(str2[i2]);
						if(pvSubject) { *ps = &(str2[i2]); break; }
					}
				}
			}

			if(pvFrom) ps = &(*(pvFrom->rbegin()));
			if(1) 
			{
				std::string strKey = "aFROM: ";
				std::string str2 = str1;
				std::string strUpper = str2;

				strKey[0] = 0x0a;
				SStrf::sucase(strUpper);

				std::string::size_type i1 = strUpper.find(strKey);
				std::string::size_type i2 = i1 + SStrf::slen(strKey.c_str());

				if( i1 != std::string::npos ) i1++;

				for( ; i1 != std::string::npos && i1 < str2.size() ; i1++ )
				{
					if( str2[i1] == 0x0d || str2[i1] == 0x0a )
					{
						str2[i1] = 0;

						strNowSender = &(str2[i2]);	

						if( strNowSender.find("<") != std::string::npos )
						{
							str2 = SStrvs::vsa_get( strNowSender, "<", 0, 1 );
							strNowSender = SStrvs::vsa_get( str2, ">", 0, 0 );
						}

						if(pvFrom)
						{
							*ps = strNowSender;
							break;
						}
					}
				}
			}

			tbool biWithDel = 1;

			biWithDel = on_before_get_t2_del( strNowTitle, strNowSender );

			if( biWithDel )
			{
				rc = m_pCellc->send_str( "DELE " + SStrf::sltoa(statnum1) + "\r\n" );   
				if( !rc ) return 0;

				std::string ss = read_ack_msg();
				if( ss.empty() || ss[0] != '+' ) return 0; 
			}

		}

		rc = m_pCellc->send_str( "quit\r\n" ); 
		read_ack_msg();

		return 1;
	}


	tbool send_t1( std::string strEHLO, std::string strUser, std::string strPass, std::string strFromEmailAddr, std::string strToEmailAddr, std::string strSubj, std::string strBody )
	{
		SCake ck;
		tbool rc;
		std::string str1;

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 220 ) return 0;

		
		
		
		
		
		rc = m_pCellc->send_str( "ehlo " + strEHLO + "\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;

		
		rc = m_pCellc->send_str( "auth login\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 334 ) return 0;

		
		rc = m_pCellc->send_str( SStrTbl::encodebase64str(strUser) + "\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 334 ) return 0;

		
		rc = m_pCellc->send_str( SStrTbl::encodebase64str(strPass) + "\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 235 ) return 0;

		
		rc = m_pCellc->send_str( "mail from: <" +  strFromEmailAddr + ">\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;

		
		rc = m_pCellc->send_str( "rcpt to: <" +  strToEmailAddr + ">\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;

		
		rc = m_pCellc->send_str( "data\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 354 ) return 0;

		rc = m_pCellc->send_str(__FUNCTION__);
		rc = m_pCellc->send_str( "\r\n" );
		rc = m_pCellc->send_str(SStrf::sltoa(__LINE__));
		rc = m_pCellc->send_str( "\r\n" );
		rc = m_pCellc->send_str( "Subject: " + strSubj + "\r\n" );

		rc = m_pCellc->send_str( "\r\n" );
		rc = m_pCellc->send_str( strBody );
		rc = m_pCellc->send_str( "\r\n.\r\n" );

		
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;

		rc = m_pCellc->send_str( "quit\r\n" );
		str1 = read_welcome_msg();
		

		return 1;
	}

};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_WComeliProtocol_h
#define X011__H_w_WComeliProtocol_h


X011_NAMESPACE_BEGIN


class WComeliProtocol : public WTcpDisConnable
{

public:

	volatile tbool  m_biComportOpened;
	volatile tbool  m_biShouldDisConn;
	volatile tbool  m_biRecvHaveComTimeoutTrait;


private:

	WComeliProtocol & operator = (const WComeliProtocol & rhs) 	{ 	return *this; }
	WComeliProtocol(const WComeliProtocol & rhs) {;}


public:

	WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
		m_biRecvHaveComTimeoutTrait = 1;

	}

	virtual ~WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
	}


public:

	
	typedef tuint8 (* PfChkSum_t) ( tuint8 a, tuint8 b );

	static tuint8 comesc_xor ( tuint8 a, tuint8 b ) { return a ^ b; };
	static tuint8 comesc_add ( tuint8 a, tuint8 b ) { return a + b; };


	static SCake & comesc_en( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = comesc_add, SCake * pdata2 = NULL ) 
	{
		

		tuint8  ucChkSum(0);
		std::vector<tuint8> v1;
		tuint8 c;

		
		v1.push_back(a1);


		for( tsize i2 = 0; pdata2 && i2 < pdata2->len(); i2++ )
		{
			c = *(tuint8*)(pdata2->buf()+i2);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back( c );
		}


		c = static_cast<tuint8>( ckDataInOut.len() );
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back( c );


		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			c = *(tuint8*)(ckDataInOut.buf()+i);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back(c);
		}


		
		for( tsize i3 = 0; i3 < ckDataInOut.len(); i3++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i3) );
		}
		
		for( tsize i4 = 0; pdata2 && i4 < pdata2->len(); i4++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)((*pdata2).buf()+i4) );
		}
		 
		c = (*pf)( ucChkSum, static_cast<tuint8>( ckDataInOut.len() ) );
		
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back(c);


		
		v1.push_back(a3);


		ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

		return ckDataInOut;
	}


	
	static SCake & comesc_en( SCake ckDataIn, SCake & ckDataOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = comesc_add, SCake * pdata2 = NULL ) 
	{
		return ckDataOut = comesc_en( ckDataIn, a1, a2, a3 , pf, pdata2 );
	}


	
	static int comesc_de( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = NULL , SCake * pdata2 = NULL ) 
	{
		if( ckDataInOut.len() != 0 )
		{
			std::vector<tuint8> v1;
			int flag = 1;

			

			for( tsize i = 0; i < ckDataInOut.len(); i++ )
			{
				tuint8 c = *(tuint8*)(ckDataInOut.buf()+i);
				tuint8 c2;


				if( flag == 1 )
				{
					if( c == a1 && i == 0 )
					{
						flag = 2;
						continue;
					}

					if( c == a1 && i != 0 )
					{
						tuint8 c0 = *(tuint8*)(ckDataInOut.buf()+i-1); 
						if( c == a1 && c0 != a2 ) 
						{
							flag = 2;
							continue;
						}
					}

					continue;
				}


				
				if( i+1 < ckDataInOut.len() )
				{
					
					c2 = *(tuint8*)(ckDataInOut.buf()+i+1);

					if( c == a2 )
					{
						v1.push_back( c2 );
						i++;
					}
					else
					{
						v1.push_back( c );
					}
				}
				else
				{
					
					if( c != a2 && c != a3 ) v1.push_back( c );
				}
			}

			
			if(v1.size()<2)
			{
				ckDataInOut.redim(0);
				return 0;
			}

			if( pdata2 != NULL && pdata2->len() != 0 )
			{
				if( v1.size() - pdata2->len() < 2 )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				for( tsize i2 = 0; i2 < pdata2->len(); i2++ )
				{
					tuint8 c = v1[0];
					*(tuint8*)(pdata2->buf()+i2) = c;
					v1.erase( v1.begin() );
				}
			}

			
			if( v1.size() == 2 )
			{
				ckDataInOut.redim(0);
				return v1[0];
			}

			
			{
				tuint8 ilen = v1[0];
				tuint8 iChkSum = v1[v1.size()-1];
				v1.erase( v1.begin() );
				v1.erase( v1.end() - 1 );

				ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

				
				if( pf )
				{
					tuint8  ucChkSum(0);

					for( tsize i = 0; i < ckDataInOut.len(); i++ )
					{
						ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
					}
					if( iChkSum != ucChkSum )
					{
						ckDataInOut.redim(0);
						return 0;
					}
				}

				if( ilen != ckDataInOut.len() )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				return ilen;
			}
		}

		return 0;
	}


	
	static int comesc_de(  SCake ckDataIn, SCake & ckDataOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = NULL , SCake * pdata2 = NULL )
	{
		int i = comesc_de( ckDataIn, a1, a2, a3 , pf, pdata2 );
		ckDataOut = ckDataIn;
		return i;
	}


	

	static SCake & com_hzo_de( const void * p, tsize iLen, SCake & ckOut )
	{
		tuint8 a1 = 0x06; 
		tuint8 a2 = 0x10;
		tuint8 a3 = 0x03;
		std::vector<tuint8> v1;
		int flag = 1;

		

		for( tsize i = 0; i < iLen; i++ )
		{
			tuint8 c = *((tuint8*)p+i);
			tuint8 c2;

			if( flag == 1 )
			{
				if( c == a1 && i == 0 )
				{
					flag = 2;
					continue;
				}

				if( c == a1 && i != 0 )
				{
					tuint8 c0 = *((tuint8*)p+i-1); 
					if( c == a1 && c0 != a2 ) 
					{
						flag = 2;
						continue;
					}
				}

				continue;
			}

			
			if( i+1 < iLen )
			{
				
				c2 = *((tuint8*)p+i+1);

				if( c == a2 )
				{
					v1.push_back( c2 );
					i++;
				}
				else
				{
					v1.push_back( c );
				}
			}
			else
			{
				
				if( c != a2 && c != a3 ) v1.push_back( c );
			}
		}

		
		if(v1.size()<1)
		{
			ckOut.redim(0);
		}
		else
			ckOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

		return ckOut;
	}


	static SCake & com_hzo_en( const void * p, tsize iLen, SCake & ckOut )
	{
		std::vector<tuint8> v1;
		tuint8 c;
		const tuint8 *p1 = (const tuint8 *)p;

		v1.push_back(0x02);

		for( tsize i2 = 0; i2 < iLen; i2++ )
		{
			c = p1[i2];
			if( c == 0x02	||
				c == 0x03	||
				c == 0x10	||
				c == 0x06	)
			{
				v1.push_back(0x10);
			}
			v1.push_back( c );
		}

		v1.push_back(0x03);

		ckOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

		return ckOut;
	}






	tbool recv_comesc_wrong( SCake & ckData , tuint8 a2, tuint8 a3 )
	{
		SCake ckTmp;
		tsize i = 1;

		do
		{
			if( m_ckDataL2CacheBuf.len() >= 2 )
				for( ; i < m_ckDataL2CacheBuf.len(); i++ )
				{
					tchar c = *(m_ckDataL2CacheBuf.buf()+i);
					tchar c1 = *(m_ckDataL2CacheBuf.buf()+i-1);

					if( c1 != a2 && c == a3 )
					{
						goto L_RECV_ESC; 
					}
				}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

		}while(ckTmp.len()>0);

L_RECV_ESC:
		ckData.redim(i+1);
		m_ckDataL2CacheBuf.dump( ckData );
		
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


	tbool recv_comesc_wrong2( SCake & ckData , tuint8 a2, tuint8 a3 )
	{
		SCake ckTmp;
		tsize i = 1;
		int iState = 0x02;

		do
		{
			if( m_ckDataL2CacheBuf.len() < 2 )
			{
			}
			else
			{
				for( ; i < m_ckDataL2CacheBuf.len(); i++ )
				{
					tuint8 *p1;

					p1 = (tuint8 *)(m_ckDataL2CacheBuf.buf() + i);

					if( iState == 0x02 && *p1 == a2 )
					{
						iState = 0x10;
						continue;
					}

					if( iState == 0x10 )
					{
						iState = 0x02;
						continue;
					}

					if( iState == 0x02 && *p1 == a3 )
					{
						
						goto L_RECV_ESC; 
					}
				}
			}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

		}while(ckTmp.len()>0);

L_RECV_ESC:
		ckData.redim(i+1);
		m_ckDataL2CacheBuf.dump( ckData );
		
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


	
	tbool recv_comesc( SCake & ckData , tuint8 a2, tuint8 a3 )
	{
		SCake ckTmp;
		tsize i = 1;
		unsigned int iCount;

		do
		{
			if( m_ckDataL2CacheBuf.len() < 2 )
			{
			}
			else
			{
				for( ; i < m_ckDataL2CacheBuf.len(); i++ )
				{
					tuint8 *p1;
					tuint8 *p2;

					p1 = (tuint8 *)(m_ckDataL2CacheBuf.buf() + i);

					if( *p1 == a3 )
					{
						iCount = 0;

						for( int ii2 = i - 1; ii2 >= 1; ii2-- )
						{
							p2 = (tuint8 *)(m_ckDataL2CacheBuf.buf() + ii2);
							if( *p2 == a2 )
								iCount++;
							else
								break;
						}

						iCount &= 1;

						if( iCount == 0x00 )
						{
							goto L_RECV_ESC; 
						}
					}
				}
			}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

		}while(ckTmp.len()>0);

L_RECV_ESC:
		ckData.redim(i+1);
		m_ckDataL2CacheBuf.dump( ckData );
		
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


public:

	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;
	}


	virtual int on_get_defaultrecv_buf_len() 
	{
		return 1;
	}


}; 



X011_NAMESPACE_END

#endif







#ifndef X011__H_w_WComeliCell_h
#define X011__H_w_WComeliCell_h


X011_NAMESPACE_BEGIN


class WComeliCell : public WComeliProtocol
{
protected:

	HANDLE  m_hComport;

private:

	WComeliCell & operator = (const WComeliCell & rhs) 	{ 	return *this; }
	WComeliCell(const WComeliCell & rhs) {;}

public:

	WComeliCell()
	{
	}

	virtual ~WComeliCell()
	{
		if( m_biComportOpened )
		{
			CloseHandle(m_hComport); 
			m_biComportOpened = 0;
		}
	}


public:

	
	tbool Conn( std::string strname )
	{
		DisConn();

		WNava nv;
		std::string strComName;

		nv.impconf( strname, ";", "=" );

		strComName = nv.get("com");
		SStrf::strim(strComName);
		if( strComName.empty() )
			return 0;
		

		if( SStrf::sisdec(strComName[0]) )
			strComName = "COM" + nv.get("com");

		if( SStrf::satol(nv.get("com")) > 9 )
			strComName = "\\\\.\\" + strComName;

		m_hComport = CreateFileA( strComName.c_str() ,
														GENERIC_READ | GENERIC_WRITE,
														0,    
														NULL, 
														OPEN_EXISTING,
														0,
														NULL
														);
		if( m_hComport == NULL || m_hComport == INVALID_HANDLE_VALUE )
		{
			
			
			return 0;
		}

		m_biComportOpened = 1;

		DCB PortDCB;
		PortDCB.DCBlength = sizeof(DCB);
		
		GetCommState(m_hComport, &PortDCB);

		PortDCB.fDtrControl = DTR_CONTROL_DISABLE;
		PortDCB.fRtsControl = RTS_CONTROL_DISABLE;

		PortDCB.BaudRate = (int)SStrf::satol( nv.get("speed") );
		PortDCB.ByteSize = (tuint8)SStrf::satol( nv.get("datalen") );
		if( nv.get("parity") == "O" ) PortDCB.Parity = ODDPARITY;
		else if( nv.get("parity") == "E" ) PortDCB.Parity = EVENPARITY;
		else if( nv.get("parity") == "N" ) PortDCB.Parity = NOPARITY;
		else
		{
			CloseHandle(m_hComport); 
			m_biComportOpened = 0;
			return 0;
		}

		if( nv.get("stop") == "1" ) PortDCB.StopBits = ONESTOPBIT;
		else if( nv.get("stop") == "1.5" ) PortDCB.StopBits = ONE5STOPBITS;
		else if( nv.get("stop") == "2" )   PortDCB.StopBits = TWOSTOPBITS;
		else
		{
			CloseHandle(m_hComport); 
			m_biComportOpened = 0;
			return 0;
		}

		if(! SetCommState(m_hComport, &PortDCB))
		{
			
			CloseHandle(m_hComport); 
			m_biComportOpened = 0;
			return 0;
		}

		
		if( (int)( SStrf::satof( nv.get("timeoutsec") ) * 1000 ) < 1 )
		{
			CloseHandle(m_hComport); 
			m_biComportOpened = 0;
			return 0;
		}

		COMMTIMEOUTS CommTimeouts;

		GetCommTimeouts(m_hComport, &CommTimeouts);
		CommTimeouts.ReadIntervalTimeout = MAXDWORD;
		CommTimeouts.ReadTotalTimeoutMultiplier = 10;
		CommTimeouts.ReadTotalTimeoutConstant  = (int)( SStrf::satof( nv.get("timeoutsec") ) * 1000 );
		CommTimeouts.WriteTotalTimeoutMultiplier = 50;
		CommTimeouts.WriteTotalTimeoutConstant = (int)( SStrf::satof( nv.get("timeoutsec") ) * 1000 );
		if (!SetCommTimeouts(m_hComport, &CommTimeouts))
		{
			
			CloseHandle(m_hComport); 
			m_biComportOpened = 0;
			return 0;
		}

		m_biShouldDisConn = 0;

		return 1;
	}


	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;

		if( m_biComportOpened )
		{
			CloseHandle(m_hComport);
			m_biComportOpened = 0;
		}
	}


public:


	virtual int on_sys_recv( SCake & ckDataBuf ) 
	{
		while(1)
		{
			if(m_biShouldDisConn)
			{
				return 0;
			}

			if( !m_biComportOpened )
				return 0;

			ckDataBuf.redim( on_get_defaultrecv_buf_len() );

			DWORD dwBytes;

			ReadFile(m_hComport, ckDataBuf.buf(), ckDataBuf.len(), &dwBytes, 0);

			if(dwBytes == ckDataBuf.len())
				return (int)ckDataBuf.len();

			if( m_biRecvHaveComTimeoutTrait )
				return 0;
			else
				WThrd::tr_sleep( 0, 0.002 );
		}
	}


	
	
	
	
	
	
	


	
	
	
	
	
	virtual int on_sys_send( const SCake & ckDataBuf )
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		if( !m_biComportOpened )
			return 0;

		DWORD ret;

		 DWORD j;

		 j = (int)ckDataBuf.len();
		 

			WriteFile( m_hComport, ckDataBuf.buf_const() , j ,&ret, NULL );

			if( j % 55 == 3 || SStrf::rand1() > 0.98 )
			{
				
			}

		return (int)ret;
	}


}; 




X011_NAMESPACE_END

#endif







#ifndef X011__H_w_WHWPoorCellc_h
#define X011__H_w_WHWPoorCellc_h



X011_NAMESPACE_BEGIN





class HWPoorCellc : public WTcpDisConnable
{
private:

	WComeliCell  m_Comport;

	
	tbool ComportSendAndEcho( std::string str1 ) 
	{
		tbool rc;
		SCake ck;

		rc = m_Comport.send_str( str1 + "\r\n" ); 
		if( !rc ) return 0;

		return ExpectingEcho( str1, 6 );
	}

	
	tbool ExpectingEcho( std::string str1, int ii = 3 , std::string *pstrRtnBuf = NULL )
	{
		tbool rc;
		SCake ck;
		std::string str9;

		
		for( int i = 0; i < ii; i++ )
		{
			rc = m_Comport.recv_ln( ck, "\n" ); 
			str9 = ck.mk_str();
			SStrf::strim(str9);
			
			if( !rc ) return 0;

			if( pstrRtnBuf ) *pstrRtnBuf += str9 + "\r\n";

			if( str1 == str9 ) return 1;

			if( str1.find("|") != std::string::npos )
				if( str1.find(str9) != std::string::npos ) return 1;

			if( !str1.empty() && str1[0] == '*' ) 
			{
				std::string s1 = str1.c_str()+1;
				std::string s9 = str9;
				SStrf::sucase(s1);
				SStrf::sucase(s9);
				if( s9.find(s1) != std::string::npos ) return 1;
			}
		}

		return 0;
	}

private:

	HWPoorCellc & operator = (const HWPoorCellc & rhs) 	{ 	return *this; }
	HWPoorCellc(const HWPoorCellc & rhs) {;}

public:
	int  m_iRecvTimeoutTimes;

public:

	HWPoorCellc()
	{
		m_iRecvTimeoutTimes = 3;
	}

	virtual ~HWPoorCellc()
	{
		CloseEnv1();
	}

public:

	
	tbool OpenEnv1( std::string strname = "com=6;start=1;stop=1;speed=9600;parity=N;datalen=8;timeoutsec=7.890;" )
	{
		tbool rc;
		SCake ck;
		std::string str1;

		WThrd::tr_sleep( 0, 0.5 );

		rc = m_Comport.Conn(strname);
		if( !rc ) return 0;

		
		WThrd::tr_sleep( 1, 0.5 );

		rc = ComportSendAndEcho( "AT+CGDCONT=1,\"IP\",\"CMNET\"" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK", 3 );
		if( !rc ) return 0;

		WThrd::tr_sleep( 1, 0.5 );

		rc = ComportSendAndEcho( "AT%ETCPIP" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK", 3 );
		if( !rc ) return 0;

		return 1;
	}


	std::string AtDns( std::string strDomain ) 
	{
		tbool rc;
		SCake ck;
		std::string str1;

		rc = ComportSendAndEcho( "AT%DNSR=\"" + strDomain + "\"" ); 
		if( !rc ) return "";

		rc = m_Comport.recv_ln( ck, "\n" ); 
		str1 = ck.mk_str();
		SStrf::strim(str1);
		if( !rc ) return "";

		if( str1.find("%DNSR:") == 0 )
		{
			rc = m_Comport.recv_ln( ck, "\n" ); 

			std::string str2 = str1.c_str() + SStrf::slen("%DNSR:");
			return SStrf::strim(str2);
		}

		return "";
	}

	
	std::string getipbyname( std::string name )
	{	return AtDns( name );	}


	tbool AtRst()
	{
		tbool rc;
		SCake ck;
		std::string str1;

		rc = m_Comport.send_str( "AT%RST\r\n" );
		if( !rc ) return 0;

		WThrd::tr_sleep( 1, 0.5 );

		rc = ExpectingEcho( "*Command Interpreter ready", 7 );
		if( !rc ) return 0;

		return 1;
	}

	
	std::string At( std::string strAt, std::string strLastEcho )
	{
		tbool rc;
		std::string str1;

		rc = ComportSendAndEcho( strAt ); 
		if( !rc ) return "";

		rc = ExpectingEcho( "OK|ERROR", 3, &str1 );
		if( !rc ) return "";

		return str1;
	}

	
	tbool LogoutGprs()
	{
		tbool rc;

		rc = ComportSendAndEcho( "AT%IPCLOSE=5" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK|ERROR", 3 );
		if( !rc ) return 0;

		return 1;
	}

	
	tbool CloseEnv1() 
	{
		tbool rc;

		rc = ComportSendAndEcho( "AT%IPCLOSE=5" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK|ERROR", 3 );
		if( !rc ) return 0;

		m_Comport.DisConn();

		return 1;
	}

	
	tbool CloseSingleTcpConn() 
	{
		tbool rc;
		SCake ck;
		std::string str1;

		rc = ComportSendAndEcho( "AT%IPCLOSE" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK|ERROR", 3 );
		if( !rc ) return 0;

		return 1;
	}

	
	tbool Conn( std::string strIp, int iPort )
	{
		tbool rc;
		SCake ck;
		std::string str1;

		rc = ComportSendAndEcho( "AT%IPOPEN=\"TCP\",\"" + strIp + "\"," + SStrf::sltoa(iPort) );
		if( !rc ) return 0;

		rc = ExpectingEcho( "CONNECT", 3 );
		if( !rc ) return 0;

		return 1;
	}

	tbool Conn( std::string strAddrLst ) 
	{
		std::vector<std::string> vecAddr1;

		SStrvs::vsa_imp( strAddrLst, std::string("|"), 1, vecAddr1 );

		for( int i = 0; i < (int)vecAddr1.size(); i ++ )
		{
			std::string strAddr = vecAddr1[i];

			try
			{
				std::vector<std::string> vecNameParts;
				SStrvs::vsa_imp( strAddr, std::string(":"), 1, vecNameParts );
				vecNameParts.push_back( std::string("") );
				vecNameParts.push_back( std::string("") );
				if( this->Conn( vecNameParts[0], static_cast<u_short>(SStrf::satol(vecNameParts[1].c_str()) ) ) ) return 1;
			}
			catch(...)
			{
				return 0;
			}
		}

		return 0;
	}

public:

	
	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		int iPerLen = 22;
		tbool rc;
		SCake ck;
		std::string str1;

		if( !m_Comport.m_biComportOpened ) return 0;
		if( m_Comport.m_biShouldDisConn ) return 0;

		if( ckDataBuf.len() == 0 ) return 0;

		if( (int)ckDataBuf.len() > iPerLen )
		{
			ck.let( ckDataBuf.buf_const(), iPerLen );
		}
		else
		{
			iPerLen = ckDataBuf.len();
			ck.let( ckDataBuf.buf_const(), iPerLen );
		}

		str1 = "AT%IPSEND=\"" + ck.GetReadable() + "\"";

		rc = ComportSendAndEcho( str1 );
		if( !rc ) return 0;

		rc = m_Comport.recv_ln( ck, "\n" );
		str1 = ck.mk_str();
		SStrf::strim(str1);
		if( !rc ) return 0;
		

		rc = ExpectingEcho( "OK", 3 );
		if( !rc ) return 0;

		return iPerLen;
	}

	
	virtual int on_sys_recv( SCake & ckDataBuf ) 
	{
		tbool rc;
		SCake ck;
		std::string str1;
		std::string str2;

		if( !m_Comport.m_biComportOpened ) return 0;
		if( m_Comport.m_biShouldDisConn ) return 0;

		for( int i = 0; i < m_iRecvTimeoutTimes ; i++ )
		{
			rc = m_Comport.recv_ln( ck, "\n" ); 
			str1 = ck.mk_str();
			SStrf::strim(str1);
			if( !rc ) return 0;

			if( str1.find("%IPDATA:") == 0 ) break;

			if( !str1.empty() && str1.find("%IPDATA:") != 0 ) return 0; 

			WThrd::tr_sleep( 0, 0.5 );


			if( !m_Comport.m_biComportOpened ) break;
			if( m_Comport.m_biShouldDisConn ) break;
		}

		str2 = SStrvs::vsa_get( str1, "\"", 0, 1 );

		if( str2.empty() ) return 0;

		ck.ConvPackStr2Bin(str2);

		ckDataBuf = ck;

		return (int)ck.len();
	}


	virtual void OnDisConn()
	{
		CloseSingleTcpConn();
	}

};




X011_NAMESPACE_END

#endif







#ifndef X011__H_w_MOON_MAN_h
#define X011__H_w_MOON_MAN_h


X011_NAMESPACE_BEGIN


template < class CONN_AGENT_T >
class WMoonMan : public WTcpDisConnable
{

private:

	std::string		m_strMManId;
	std::string		m_strMManIdRemote;

	tbool m_iIsConnected;


	int on_sys_recv( SCake & ckDataBuf ) 
	{
		if( !m_iIsConnected ) return 0;
		return OnRecv( ckDataBuf ) ;
	}

	int on_sys_send( const SCake & ckDataBuf ) 
	{
		if( !m_iIsConnected ) return 0;
		return OnSend( ckDataBuf );
	}


protected:

	static std::string MkId()
	{
		return WFile::MkRUStr();
	}


public:

	WMoonMan() :
	  m_iIsConnected(0)
	{
	}

	virtual ~WMoonMan()
	{
	}


public:

	typedef CONN_AGENT_T  CONN_AGENT_TYPET;


public:

	tbool Conn( CONN_AGENT_TYPET  rd ) 
	{
		SetMManId();
		SetMManIdRemote();
		m_iIsConnected = OnConn( rd )?1:0;
		return m_iIsConnected;
	}

	void DisConn()
	{
		m_iIsConnected = 0;

		
		WTcpDisConnable::DisConn();
	}

	tbool IsConnected() const
	{
		return m_iIsConnected;
	}


	void SetMManId( std::string strId = "" )
	{
		if( strId == "" )
			m_strMManId = MkId();
		else
			m_strMManId = strId;
	}


	void SetMManIdRemote( std::string strId = "" )
	{
		if( strId == "" )
			m_strMManIdRemote = MkId();
		else
			m_strMManIdRemote = strId;
	}


	std::string GetMManId() const
	{
		return m_strMManId;
	}


	std::string GetMManIdRemote() const
	{
		return m_strMManIdRemote;
	}


public:

	virtual tbool OnConn( CONN_AGENT_TYPET  rd ) = 0;
	

	virtual void OnDisConn() = 0;
	

	virtual int OnRecv( SCake & ckDataBuf ) = 0;
	

	virtual int OnSend( const SCake & ckDataBuf ) = 0;
	

}; 



X011_NAMESPACE_END


#endif







#ifndef X011__H_w_MOON_box_H
#define X011__H_w_MOON_box_H


X011_NAMESPACE_BEGIN


template < class MoonMan_Ta, class MoonMan_Tb >
class WMoonBox : public WThrd
{

private:

	class WMoonBoxThread : public WThrd
	{
	public:
		WMoonBox * m_Mbox;
		int m_iMManType;

		WMoonBoxThread()
		{;}
		virtual ~WMoonBoxThread()
		{ tr_destruct(); }

		virtual int tr_on_user_run()
		{
			if( m_iMManType == 'a' )
			{
				return m_Mbox->RunMMa();
			}
			else
			{
				return m_Mbox->RunMMb();
			}
		}
	};


private:

	MoonMan_Ta * m_pMMa;
	MoonMan_Tb * m_pMMb;

	WMoonBoxThread m_thrdMMa;
	WMoonBoxThread m_thrdMMb;


	virtual int tr_on_user_run()
	{
		return RunMM3();
	}


	int DeliverAb( WTcpDisConnable * p1, WTcpDisConnable * p2 )
	{
		SCake ckTmp;
		if( p1->recv_bin( ckTmp ) )
		{
			OnDeliverAb( ckTmp );
			p2->send_bin( ckTmp );
			return 1;
		}
		p2->DisConn();
		return 0;
	}


	int DeliverBa( WTcpDisConnable * p1, WTcpDisConnable * p2 )
	{
		SCake ckTmp;
		if( p1->recv_bin( ckTmp ) )
		{
			OnDeliverBa( ckTmp );
			p2->send_bin( ckTmp );
			return 1;
		}
		p2->DisConn();
		return 0;
	}


	int RunMMa()
	{
		return DeliverAb( m_pMMa, m_pMMb ); 
	}


	int RunMMb()
	{
		return DeliverBa( m_pMMb, m_pMMa );
	}


	int RunMM3()
	{
		return OnMoonBoxThrdRun( m_thrdMMa, m_thrdMMb );
	}


public:

	WMoonBox()
	{
		m_pMMa = new MoonMan_Ta();
		m_pMMb = new MoonMan_Tb();
	}


	virtual ~WMoonBox()
	{
		m_thrdMMa.tr_shouldbrk();
		m_thrdMMb.tr_shouldbrk();
		m_pMMa->DisConn();
		m_pMMb->DisConn();
		m_thrdMMa.tr_wait();
		m_thrdMMb.tr_wait();

		if(m_pMMa)
		{
			delete m_pMMa;
		}

		if(m_pMMb)
		{
			delete m_pMMb;
		}

		tr_destruct();
	}


public:

	void Init()
	{
		
		
	}


	MoonMan_Ta & GetMMa()
	{
		return * m_pMMa;
	}


	MoonMan_Tb & GetMMb()
	{
		return * m_pMMb;
	}


	void Launch()
	{
		m_thrdMMa.m_Mbox = this;
		m_thrdMMa.m_iMManType = 'a';
		m_thrdMMb.m_Mbox = this;
		m_thrdMMb.m_iMManType = 'b';

		m_thrdMMa.tr_open();
		m_thrdMMb.tr_open();

		
	}


public:

	virtual int OnMoonBoxThrdRun( WThrd & thrd_a, WThrd & thrd_b )
	{
		thrd_a.tr_wait();
		thrd_b.tr_wait();
		return 0; 
	}


	virtual void OnDeliverAb( SCake & ckTmp )
	{
		
		
		

		return;
	}


	virtual void OnDeliverBa( SCake & ckTmp )
	{
		return;
	}

}; 




X011_NAMESPACE_END


#endif






#ifndef X011__H_w_WMManSimpCellc_h
#define X011__H_w_WMManSimpCellc_h


X011_NAMESPACE_BEGIN


template< class Cellc_T = WTcpCellc >
class WMManSimpCellc : public WMoonMan< std::string >
{
public:
	Cellc_T  m_tcpc;

public:

	virtual tbool OnConn( CONN_AGENT_TYPET strAddr )
	{
		return m_tcpc.Conn( strAddr );
	}

	virtual void OnDisConn()
	{
		m_tcpc.DisConn();
		return;
	}

	virtual int OnRecv( SCake & ckDataBuf )
	{
		m_tcpc.recv_bin(ckDataBuf);
		return ckDataBuf.len();
	}

	virtual int OnSend( const SCake & ckDataBuf )
	{
		if( m_tcpc.send_bin( ckDataBuf ) )
		{
			return ckDataBuf.len();
		}
		return 0;
	}

}; 



X011_NAMESPACE_END


#endif






#ifndef X011__H_w_WMManSimpCells_h
#define X011__H_w_WMManSimpCells_h


X011_NAMESPACE_BEGIN




template< class Cells_T = WTcpCells >
class WMManSimpCells : public WMoonMan< WTcpListener & >
{
public:
	Cells_T m_tcps;

public:

	virtual tbool OnConn( CONN_AGENT_TYPET L )
	{
		return m_tcps.Conn(L);
	}

	virtual void OnDisConn()
	{
		m_tcps.DisConn();
		return;
	}

	virtual int OnRecv( SCake & ckDataBuf )
	{
		m_tcps.recv_bin(ckDataBuf);
		return ckDataBuf.len();
	}

	virtual int OnSend( const SCake & ckDataBuf )
	{
		if( m_tcps.send_bin( ckDataBuf ) )
		{
			return ckDataBuf.len();
		}
		return 0;
	}

}; 



X011_NAMESPACE_END


#endif






#ifndef X011__H_W_WTCPBACKOFFI2_H
#define X011__H_W_WTCPBACKOFFI2_H


X011_NAMESPACE_BEGIN


#ifdef VC6_COMPATIBLE_X011_

#else





class bu_backoffi2_protocol_t
{
public:
	bu_backoffi2_protocol_t(){};
	virtual ~bu_backoffi2_protocol_t(){;}

public:

	tbool Proc2( SCake & ckin, std::string & sout )
	{
		SNavass nvin;
		SNavass nvout;
		std::string s1, s2, s3, s4;

		if( ckin.len() == 0 )
		{
			return 0;
		}

		nvin.unserialize( ckin.mk_str() );
		nvout.clear();

		
		if( OnPreProc(nvin,nvout) )
		{
			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		if( s1 == "hello" )
		{
			nvout.let( "rc", "1" );
			nvout.let( "dt", SDte::GetNow().ReadString() );
			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("data");
		s3 = nvin.get("file");
		if( s1 == "write" && !s2.empty() && !s3.empty() )
		{
			SFile wf;
			SCake ck;

			ck.lets( s2 );
			ck.bs_de();

			if( !OnBeforeWriteBindFile( s3 ) ) goto L_ANS;

			wf.bind( s3 );

			nvout.let( "rc", (int)wf.write(ck,1) );

			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("file");
		s3 = nvin.get("offset");
		s4 = nvin.get("len");
		if( s1 == "read" && !s2.empty() && !s3.empty() && !s4.empty() )
		{
			SCake ck;
			SFile fl;
			std::string strFnData;

			if( !OnBeforeReadBindFile( s2 ) ) goto L_ANS;

			fl.bind( s2 );

			if( !fl.exists() || fl.len() <= (tsize)SStrf::satol(s3) )
			{
				nvout.let( "rc", "0" );
				goto L_ANS;
			}

			nvout.let( "rc", "1" );
			fl.read( ck, (tsize)SStrf::satol(s3) , SStrf::satol(s4) );
			strFnData = ck.len() ? ck.bs_en().buf() : "";
			nvout.let( "data", strFnData );

			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("file");
		if( s1 == "del" && !s2.empty() )
		{
			SCake ck;
			SFile fl;

			if( !OnBeforeDelBindFile( s2 ) ) goto L_ANS;

			fl.bind( s2 );
			if( fl.exists() )  fl.erase();
			nvout.let( "rc", "1" );

			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("file");
		s3 = nvin.get("len");
		if( s1 == "ds2" && !s2.empty() && !s3.empty() )
		{
			SCake ck;
			SFile fl;

			if( !OnBeforeDs2BindFile( s2 ) ) goto L_ANS;

			fl.bind( s2 );

			if( !fl.exists() )
			{
				nvout.let( "rc", "0" );
				goto L_ANS;
			}

			nvout.let( "rc", "1" );
			fl.read( ck );

			std::string s = ck.ds2( SStrf::satol(s3) );

			nvout.let( "data", s );

			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("file");
		if( s1 == "run" && !s2.empty() )
		{
			int i = WFile::run_exe( s2.c_str() );
			nvout.let( "rc", "1" );
			nvout.let( "code", i );

			goto L_ANS;
		}

		
		nvout.let( "rc", "0" );
		nvout.let( "dt", SDte::GetNow().ReadString() );

L_ANS:
		nvout.serialize( sout );
		return 1;
	}

	
	virtual tbool OnPreProc( SNavass & nvin, SNavass & nvout )
	{
		return 0;
	}

	
	virtual tbool OnBeforeWriteBindFile( std::string & strfn ) 	{		return 1;	}
	virtual tbool OnBeforeReadBindFile( std::string & strfn ) 	{		return 1;	}
	virtual tbool OnBeforeDelBindFile( std::string & strfn ) 	{		return 1;	}
	virtual tbool OnBeforeDs2BindFile( std::string & strfn ) 	{		return 1;	}
};



template <
			class THRD_ELE_T = WThrd ,
			class BACKOFFI2_PROTOCOL_T = bu_backoffi2_protocol_t ,
			class TCPSERVER_TRAIT_T = WTcpCells
		>
class bu_backoffi2_ele_t : public THRD_ELE_T , public BACKOFFI2_PROTOCOL_T
{
public:
	TCPSERVER_TRAIT_T  m_tSvr;

public:
	bu_backoffi2_ele_t(){};
	virtual ~bu_backoffi2_ele_t(){ THRD_ELE_T::tr_destruct();}

public:
	virtual int tr_on_user_run()
	{
		WTcpDisConnable &tSvr(m_tSvr);
		SCake ckin;
		SNavass nvin;
		SNavass nvout;
		std::string sout;

		tSvr.recv_ln2( ckin, "\n" );

		if( this->Proc2( ckin, sout ) )
		{
			tbool rc;

			rc = tSvr.send_str( sout + "\n" );
			

			return 1;
		}
		else
		{
			WThrd::tr_sleep(1);
			return 0;
		}
	}
	
	
	
	
};



template	<
				class THRD_MGR_T = WThrd ,
				class THRD_ELE_T = WThrd ,
				class BACKOFFI2_PROTOCOL_T = bu_backoffi2_protocol_t ,
				class TCPSERVER_TRAIT_T = WTcpCells ,
				class TCPLSN_TRAIT_T = WTcpListener
			>
class bu_backoffi2_mgr_t : public WThrdMgr< bu_backoffi2_ele_t< THRD_ELE_T, BACKOFFI2_PROTOCOL_T >, THRD_MGR_T >
{
protected:
	typedef	 bu_backoffi2_ele_t< THRD_ELE_T, BACKOFFI2_PROTOCOL_T, TCPSERVER_TRAIT_T >   ThrEle_t;
public:
	TCPLSN_TRAIT_T  m_tLsn;
	

public:
	bu_backoffi2_mgr_t(){}

	virtual ~bu_backoffi2_mgr_t()
	{
		
		
		THRD_MGR_T::tr_destruct();
	}

public:
	
	
	

	virtual tbool OnMgrPrepare( ThrEle_t & t )	
	{
		if( !t.m_tSvr.Conn( m_tLsn ) )
			return 0;

		return 1;
	}

	static tbool Def( tuint16 port = 9900 ) 
	{
		bu_backoffi2_mgr_t< > *p;
		if( SStrf::newobjptr(p) && p->m_tLsn.Listen( (tuint16)port ) )
		{
			p->tr_openx();
			return 1;
		}
		return 0;
	}
};



class bu_backoffi2_client_base_t
{
public:
	WTcpDisConnable  * m_pCellc;

public:
	bu_backoffi2_client_base_t()
	{
		m_pCellc = NULL;
	}

	virtual ~bu_backoffi2_client_base_t()
	{
	}

public:

	
	tbool ReConn()
	{
		return OnReConn();
	}

	
	virtual tbool OnReConn()
	{
		m_pCellc = NULL;

		return 0;
	}

	
	virtual int OnGetReadBufLen()
	{
		return 64;
	}

	
	virtual int OnGetWriteBufLen()
	{
		return 64;
	}


	tbool Read( std::string strRemotefn, SCake & ckRtn, int iRetry = 9 ) 
	{
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		SCake ck;
		std::string strout;
		long iOffset;
		long iLen;

		ckRtn.redim(0);
		iLen = OnGetReadBufLen();

		if( m_pCellc == NULL )
		{
			if( !ReConn() )
			{
				
				m_pCellc = NULL;

				return 0;
			}
		}

		for( iOffset = 0; ; )
		{
			if( iRetry <= 0 )
			{
				return 0;
			}

			if( m_pCellc == NULL )
			{
				if( !ReConn() )
				{
					WThrd::tr_sleep(2);
					m_pCellc = NULL;

					iRetry--;
					continue;
				}
			}

			nvout.let( "cmd", "read" );
			nvout.let( "file", strRemotefn );
			nvout.let( "offset", SStrf::sltoa(iOffset) );
			nvout.let( "len", SStrf::sltoa(iLen) );

			nvout.serialize( strout );

			if( !m_pCellc->send_str( strout + "\n" ) )
			{
				m_pCellc->DisConn();
				m_pCellc = NULL;

				iRetry--;
				continue;
			}

			m_pCellc->recv_ln( ckin );

			if( ckin.len() == 0 )
			{
				m_pCellc->DisConn();
				m_pCellc = NULL;

				iRetry--;
				continue;
			}

			nvin.unserialize( ckin.mk_str() );

			if( nvin.get("rc") == "1" )
			{
				ck.lets( nvin.get("data") );
				ck.bs_de();
				ckRtn.FastAppend(ck);
				iOffset += (int)ck.len();

				continue;
			}

			if( nvin.get("rc") != "1" )
			{
				break;
			}

			
		} 

		if( iRetry <= 0 )
		{
			return 0;
		}

		if( m_pCellc != NULL )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
		}

		ckRtn.FastAppendEnd();

		return 1;
	}


	tbool Write( std::string strRemotefn, const SCake & ck )
	{
		std::vector< SCake > vck;
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		std::string strout;

		if( ck.len() == 0 ) return 0;

		SCakel::MkVecCake( ck, OnGetWriteBufLen(), vck, 0 );

		if( m_pCellc == NULL )
			if( !ReConn() )
			{
				
				m_pCellc = NULL;
				return 0;
			}


		nvout.let( "cmd", "del" );
		nvout.let( "file", strRemotefn );

		nvout.serialize( strout );

		if( !m_pCellc->send_str( strout + "\n" ) )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
		}
		else
			m_pCellc->recv_ln( ckin );

		for( int i = 0; i < (int)vck.size(); )
		{
			printf( "%d/%d\t", (int)i, (int)vck.size() );

			if( m_pCellc == NULL )
			{
				if( !ReConn() )
				{
					WThrd::tr_sleep(2);
					m_pCellc = NULL;

					continue;
				}
			}

			nvout.let( "cmd", "write" );
			nvout.let( "file", strRemotefn );
			nvout.let( "data", vck[i].bs_en().buf() );

			nvout.serialize( strout );

			if( !m_pCellc->send_str( strout + "\n" ) )
			{
				m_pCellc->DisConn();
				m_pCellc = NULL;

				continue;
			}

			m_pCellc->recv_ln( ckin );

			if( ckin.len() == 0 )
			{
				m_pCellc->DisConn();
				m_pCellc = NULL;

				continue;
			}

			nvin.unserialize( ckin.mk_str() );

			if( nvin.get("rc") == "1" )
			{
				i++;
				continue;
			}

			if( nvin.get("rc") != "1" )
			{
				break;
			}

			
		} 

		printf( "\n" );

		if( m_pCellc != NULL )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
		}

		return 1;
	}


	tbool Ds2( std::string strRemotefn , std::string & strrefRtnDs2_33 )
	{
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		std::string strout;

		if( m_pCellc == NULL )
			if( !ReConn() )
			{
				
				m_pCellc = NULL;
				return 0;
			}


		nvout.let( "cmd", "ds2" );
		nvout.let( "file", strRemotefn );
		nvout.let( "len", "33" );

		nvout.serialize( strout );

		if( !m_pCellc->send_str( strout + "\n" ) )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->recv_ln( ckin );

		if( ckin.len() == 0 )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->DisConn();
		m_pCellc = NULL;

		nvin.unserialize( ckin.mk_str() );

		if( nvin.get("rc") == "1" )
		{
			strrefRtnDs2_33 = nvin.get("data") ;
			return 1;
		}

		return 0;
	}


	tbool RunCmd( std::string strRemotefn, int *piRtn = NULL )
	{
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		std::string strout;

		if( m_pCellc == NULL )
			if( !ReConn() )
			{
				
				m_pCellc = NULL;
				return 0;
			}


		nvout.let( "cmd", "run" );
		nvout.let( "file", strRemotefn );

		nvout.serialize( strout );

		if( !m_pCellc->send_str( strout + "\n" ) )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->recv_ln( ckin );

		if( ckin.len() == 0 )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->DisConn();
		m_pCellc = NULL;

		nvin.unserialize( ckin.mk_str() );

		if( nvin.get("rc") == "1" )
		{
			if(piRtn)
				*piRtn = (int)SStrf::satol( nvin.get("code") );
			return 1;
		}

		return 0;
	}

	
	tbool Del( std::string strRemotefn )
	{
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		std::string strout;

		if( m_pCellc == NULL )
			if( !ReConn() )
			{
				
				m_pCellc = NULL;
				return 0;
			}

		nvout.let( "cmd", "del" );
		nvout.let( "file", strRemotefn );

		nvout.serialize( strout );

		if( !m_pCellc->send_str( strout + "\n" ) )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->recv_ln( ckin );

		if( ckin.len() == 0 )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->DisConn(); 
		m_pCellc = NULL;

		nvin.unserialize( ckin.mk_str() );

		if( nvin.get("rc") == "1" )
		{
			return 1;
		}

		return 0;
	}

};




template< class T >
class bu_backoffi2_client_cellc_t : public bu_backoffi2_client_base_t
{
public:
	
	T		   * m_ptc;
	std::string  m_strAddr;

public:
	bu_backoffi2_client_cellc_t()
	{
		m_ptc = NULL;
	}

	virtual ~bu_backoffi2_client_cellc_t()
	{
	}

public:
	virtual tbool OnReConn()
	{
		if( m_ptc->Conn(m_strAddr) )
		{
			m_pCellc = m_ptc;
			return 1;
		}
		else
		{
			m_pCellc = NULL;
			return 0;
		}
	}
};


class bu_backoffi2_client_t : public bu_backoffi2_client_cellc_t<WTcpCellc>
{
public:
	virtual ~bu_backoffi2_client_t(){}

	
	virtual int OnGetReadBufLen()
	{
		return 2048;
	}

	
	virtual int OnGetWriteBufLen()
	{
		return 1024;
	}
};



class bu_backoffi2_HWclient_t : public bu_backoffi2_client_cellc_t<HWPoorCellc>
{
public:
	virtual ~bu_backoffi2_HWclient_t(){}

	
	virtual int OnGetReadBufLen()
	{
		return 40;
	}

	
	virtual int OnGetWriteBufLen()
	{
		return 40;
	}
};


#endif


X011_NAMESPACE_END


#endif



#ifndef X011__H_w_w_WKeyinput_t_h
#define X011__H_w_w_WKeyinput_t_h


X011_NAMESPACE_BEGIN


#ifdef VC6_COMPATIBLE_X011_

#else


template < class THREADBASE_T = WThrd, class THREADBASE_T_toutman = WThrd >
class WKeyinput : public WIdleThrd< std::string > , public THREADBASE_T
{
public:

private:
	class TimeoutMan : public THREADBASE_T_toutman
	{
	public:
		WKeyinput * m_pFather;

		TimeoutMan(){ m_pFather = NULL; }

		virtual ~TimeoutMan(){ THREADBASE_T_toutman::tr_destruct(); }

		virtual int tr_on_user_run()
		{
			if( m_pFather == NULL || m_pFather->m_timeout_dSec <= 0.001 )
			{
				WThrd::tr_sleepu( 1.2 );
				return 1;
			}
			WThrd::tr_sleepu( m_pFather->m_timeout_dSec );
			if( m_pFather) m_pFather->PostTask( "<timeout>" );
			return 1;
		}
	};

	std::string  m_strkeyaddress;

	WTcpListener  m_tLsn;
	WTcpCells     m_ts;
	WTcpCellc     m_tc;
	WCrsc					  m_KeyBufLck;
	std::list< std::string >  m_KeyBuf;
	volatile WCrsc			* m_pKeyBufTempLock;

	volatile double m_timeout_dSec;

	TimeoutMan	*m_pto;

public:
	WKeyinput()
	{
		m_pto = new TimeoutMan;

		m_pKeyBufTempLock = NULL;
		m_timeout_dSec = 0.0;
	}

	virtual ~WKeyinput()
	{
		m_pto->tr_shouldbrk();
		m_pto->m_pFather = NULL;
		delete m_pto;

		THREADBASE_T::tr_destruct();
	}

public:
	
	tbool KeyiInit( int iPort , int *pPortOut = NULL ) 
	{
		WCrsc aLock( &m_KeyBufLck );
		int iPortOut;

		m_KeyBuf.clear();

		for( int i = 0; i < 9999; i++ )
		{
			m_strkeyaddress = "127.0.0.1:" + SStrf::sltoa( iPortOut = (i + iPort) );

			if( m_tLsn.Listen( m_strkeyaddress ) )
			{
				this->tr_open();

				this->PostTask( "<connect>" );
				WThrd::tr_sleepu(0.61);

				m_pto->m_pFather = this;
				m_pto->tr_open();
				

				if( pPortOut ) *pPortOut = iPortOut;
				return 1;
			}
		}

		return 0;
	}

	
	void SetTimeout( double dSec = 0.0 )
	{
		m_timeout_dSec = dSec;
	}

	
	void Clear()
	{
		WCrsc aLock( &m_KeyBufLck );
		m_KeyBuf.clear();
	}

	
	
	


	std::string GetKey( tbool biWithWait = 1 )
	{
		std::string s;

		do
		{
			if(1)
			{
				volatile WCrsc aLock( &m_KeyBufLck );

				if( m_KeyBuf.empty() )
				{
					if( biWithWait )
						this->PostTask( "<lock>", 0, 1 );
					else
						return "";
				}
				else
				{
					s = *(m_KeyBuf.begin());
					m_KeyBuf.pop_front();
					break;
				}
			}

			WThrd::tr_sleep( 0, 0.25 );
			continue;

		}while(1);

		return s;
	}

	virtual void OnRunTask( std::string t )
	{
		if( t.empty() )
		{
			return;
		}

		if( t == "<connect>" )
		{
			this->m_tc.Conn( m_strkeyaddress );
			return;
		}

		
		this->m_tc.send_str( t + "\n" );
	}

	
	virtual int tr_on_user_run()
	{
		if( !this->m_ts.Conn( this->m_tLsn ) )
		{
			WThrd::tr_sleep(1);
			return 1;
		}

		while(1)
		{
			SCake ck;
			std::string s1;

			if( this->tr_isShouldBrk() )
				break;

			m_ts.recv_ln( ck );
			ck.mk_str(s1);

			if( s1.empty() )
			{
				this->m_ts.DisConn();
				this->PostTask( "<connect>", 1, 1 );

				return 1;
			}

			if( s1 == "<timeout>" )
			{
				if( m_pKeyBufTempLock == NULL )
				{
					m_pKeyBufTempLock = new WCrsc( &m_KeyBufLck );

					m_KeyBuf.push_back( "" );

					delete m_pKeyBufTempLock;
					m_pKeyBufTempLock = NULL;

					continue;
				}

				if( m_pKeyBufTempLock != NULL )
				{
					m_KeyBuf.push_back( "" );

					delete m_pKeyBufTempLock;
					m_pKeyBufTempLock = NULL;

					continue;
				}
			}

			if( s1 == "<lock>" )
			{
				if( m_pKeyBufTempLock == NULL )
				{
					m_pKeyBufTempLock = new WCrsc( &m_KeyBufLck );
					continue;
				}

				if( m_pKeyBufTempLock != NULL )
				{
					continue;
				}
			}

			
			if( m_pKeyBufTempLock == NULL )
			{
				m_pKeyBufTempLock = new WCrsc( &m_KeyBufLck );

				m_KeyBuf.push_back( s1 );

				delete m_pKeyBufTempLock;
				m_pKeyBufTempLock = NULL;

				continue;
			}

			
			if( m_pKeyBufTempLock != NULL )
			{
				m_KeyBuf.push_back( s1 );

				delete m_pKeyBufTempLock;
				m_pKeyBufTempLock = NULL;

				continue;
			}

			
			continue;
		}

		WThrd::tr_sleep(1);
		return 1;
	}

};

#endif	




X011_NAMESPACE_END

#endif




#ifndef WLoUTIL__X013__H
#define WLoUTIL__X013__H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


namespace wlo {


class gmr;
class wl_stru_gmr;
typedef gmr Gmr;





typedef		 char				   wlint8;
typedef		 unsigned char		   wluint8;
typedef		 short				   wlint16;
typedef		 unsigned short		   wluint16;
typedef		 long				   wlint32;
typedef		 unsigned long		   wluint32;
typedef		 int (*wlpfucb) (wlint8 *, wlint8 *);


#ifndef WL_STRU_STRF_H
#define WL_STRU_STRF_H


class wl_stru_strf {


public:

	 wl_stru_strf(){;}

	~wl_stru_strf(){;}


	static wluint16 mk_U16(wluint8 c1, wluint8 c2) 
	{
	   wluint16 ilow,ihigh;
	   ilow =  (wluint16)c1;
	   ihigh = (wluint16)c2;
	   ihigh <<= 8;
	   return ihigh + ilow;
	}

	static wluint32 mk_U32(wluint8 c1, wluint8 c2, wluint8 c3, wluint8 c4)
	{
	   return mk_U32( mk_U16(c1,c2), mk_U16(c3,c4) );
	}

	static wluint32 mk_U32(wluint16 i1 , wluint16 i2 )
	{
	   wluint32 ilow,ihigh;
	   ilow =(wluint32)i1;
	   ihigh=(wluint32)i2;
	   ihigh <<= 16;
	   return ihigh + ilow;
	}


	static wlint8 *mk_xor(wlint8 *s, wlint32 a_len, wlint8 x)
	{
		wlint32 i;
		if(s==NULL) return s;
		if(a_len==0) return s;
		for(i=0;i<a_len;i++) s[i] ^= x;
		return s;
	}


	static wlint32 str_chksum(wlint8 *s)
	{
		return str_chksum( s, str_len(s) );
	}


	static wlint32 str_chksum(wlint8 *s, wlint32 a_len)
	{
		wlint32 i,j;
		if(s==NULL) return 0;
		if(strlen(s)==0) return 0;
		for(i=0,j=0;i<a_len;i++){
			j=j+(wluint8)s[i]+(i+1);
			j &= 0x7FFFffff;
		}
		return (wlint32)j;
	}


	static int str_ishex(wlint8 c)
	{
		return  (c>='0'&&c<='9')||(c>='A'&&c<='F')||(c>='a'&&c<='f');
	}

	static int str_ishex(wlint8 *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!str_ishex(*s)) return 0;
		return 1;
	}


	static int str_isdec(wlint8 c)
	{
		return  (c>='0'&&c<='9') ;
	}

	static int str_isdec(wlint8 *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!str_isdec(*s)) return 0;
		return 1;
	}


	static wlint32 str_len(wlint8 *s)
	{
		if(s==NULL) return 0;
		return (wlint32)strlen(s);
	}




	static wlint8 *str_ltoa(wlint32 i, wlint8 *buf)	{ return str_ltoa(i,10, buf) ;}


	static wlint8 *str_ltoa(wlint32 i, int radix, wlint8 *buf)
	{
		static wlint8 c[33];
		
		return (*wl::SClib::p_ltoa()) (i, buf==NULL?c:buf, radix);
	}


	static wlint32 str_atol(wlint8 *s)
	{
		if(s==NULL) return 0;
		return (wlint32)::atol(s);
	}


	static double str_atof(wlint8 *s)
	{
		if(s==NULL) return 0.0;
		return (double)::atof(s);
	}


    static int str_cmpi(wlint8 *a,wlint8 *b)
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		wlint8 *t1,*t2, c1,c2;
		wlint32 i;
		t1 = a;
		t2 = b;
		for(i=0;t1[i]&&t2[i];i++){
			c1=t1[i];
			c2=t2[i];
			if(c1>='a'&&c1<='z')c1+=('A'-'a');
			if(c2>='a'&&c2<='z')c2+=('A'-'a');
			if(c1!=c2)return c1-c2;
		}
		return t1[i]-t2[i];
	}


	static int str_cmpn(wlint8 *a,wlint8 *b, wlint32 count )
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		return ::strncmp(a,b,(size_t)count);
	}


	static int str_cmp(wlint8 *a,wlint8 *b)
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		return ::strcmp(a,b);
	}


	static wlint8 *str_ucase(wlint8 *s)
	{
		wlint32 i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='a'&&s[i]<='z')s[i] = s[i] -'a' + 'A' ;
		}
		return s;
	}

	static wlint8 *str_lcase(wlint8 *s)
	{
		wlint32 i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='A'&&s[i]<='Z')s[i] = s[i] -'A' + 'a' ;
		}
		return s;
	}


	static wlint8 *str_poslast(wlint8 *s, wlint32 offset2left=0) 
	{
		if(!s||!*s) return s;
		wlint32 i,j ;
		j=str_len(s);
		i = j - 1 - offset2left ;
		return s+(i<0?0:i);
	}


	static wlint32 str_instr(wlint8 *s, wlint8 *substr)
	{													
		wlint8 *t;
		if(!s||!substr||!(*s)||!(*substr)) return -1;
		t = strstr(s,substr);
		if(t==NULL) return -1;
		return (wlint32)(t - s) ;
	}

	static wlint32 str_instr(wlint8 *s, wlint8 subc)
	{
		wlint8 t[2];
		t[0]=subc;
		t[1]=0;
		return str_instr(s,t) ;
	}


	static wlint32 str_instri(wlint8 *s, wlint8 *substr)
	{
		wlint8 *t1,*t2;
		wlint32 i;

		if(s==NULL) return -1;
		if(substr==NULL) return -1;
		t1 = (wlint8 *)malloc( str_len(s)		+ 1 );
		t2 = (wlint8 *)malloc( str_len(substr)	+ 1 );
		if(t1==NULL) return -1;
		if(t2==NULL) { free(t1); return -1; }
		strcpy(t1,s);
		strcpy(t2,substr);
		str_ucase(t1);
		str_ucase(t2);
		i=str_instr(t1,t2);
		free(t1);
		free(t2);
		return i ;
	}


	static wlint8 *str_replchar(wlint8 *s, wlint8 c1, wlint8 c2)
	{
		return str_replchar(s, str_len(s), c1, c2);
	}


	static wlint8 *str_replchar(wlint8 *s, wlint32 len, wlint8 c1, wlint8 c2)
	{
		wlint32 i;
		for(i=0;s&&i<len;i++) {
			if(s[i]==c1) s[i]=c2;
		}
		return s;
	}


	static wlint8 *str_rev(wlint8 *s)
    {
		wluint32 u;
		wlint32  x, y, i;
		wlint32  a, b;
		u = (wluint32)str_len(s);
		u >>= 1;
		x = u;
		y = str_len(s) - 1;
        for(i=0;i<x;i++) {
			a = i;
			b = y - i;
			
			s[a] ^= s[b];
			s[b] ^= s[a];
			s[a] ^= s[b];
		}
		return s;
    }


	static wlint8 *str_rtrim(wlint8 *s, wlint8 c_my_space='\0')
	{
		wlint32 i,j ;
		j=str_len(s);
		for(i=j-1;i>=0;i--) {
			if(s[i]==0x09||s[i]==' '||s[i]==c_my_space)
				s[i]=0;
			else
				break;
		}
		return s;
	}


	static wlint8 *str_ltrim(wlint8 *s, wlint8 c_my_space='\0')
	{
		return  str_rev(str_rtrim(str_rev(s), c_my_space) ) ;
	}


	static wlint8 *str_trim(wlint8 *s, wlint8 c_my_space='\0')
	{
		return  str_ltrim(str_rtrim(s,c_my_space), c_my_space) ;
	}


	static wlint8 *str_left(wlint8 *s, wlint32 n)
	{
		if(n>(wlint32)str_len(s)||n<0) return s;
		s[n]=0;
		return s;
	}


	static wlint8 *str_right(wlint8 *s, wlint32 n)
	{
		return str_rev(str_left(str_rev(s), n));
	}


	static wlint8 *str_mid(wlint8 *s, wlint32 n, wlint32 n2)
	{
		str_right(s, str_len(s) - n );
		str_left(s, n2);
		return s;
	}


	static int str_seq_sort( const void *arg1, const void *arg2 )
	{   
		wlint8 *t1,*t2 ;
		wlint32 i;
		t1 = * ( char ** ) arg1;
		t2 = * ( char ** ) arg2;
		i=str_len(t1)-str_len(t2);

		if(i) return i;
		return str_cmp(t1,t2);
	}


	static wlint8 *str_seq_dirno(void)
	{
		static char t[]=
		 "0123456789ACEFHKLMPQSTUWXYZ"; 
		return t;
	}


	
	
	
	
	
	
	
	
	
	
	
	

	static wlint8 *str_seq(wlint8 *buf=NULL)
	{
		static wlint8 s[34]={0,0,0,0,0,0,0};
		return str_seq(buf==NULL?s:buf, "", 0);
	}

	static wlint8 *str_seq(wlint8 *s_num, const wlint8 *s_symbset1, int isfix=0)
	{
		char *s_symbset=(char*)s_symbset1;
		
		static wlint8 c[1];
		c[0]=0;
		if(s_num==NULL) return c;
		
		if(str_len(s_symbset)<2) s_symbset = str_seq_dirno();

		wlint16 *lia , ulia;
		wlint32 i,j,k;

		lia = (wlint16 *)malloc( (str_len(s_num) + 1)*sizeof(wlint16) );

		if(!(*s_num)) {
			s_num[0]=s_symbset[0];
			s_num[1]=0;
		}

		j = str_len(s_num) ;
		for(i=0;i<j;i++)
		{
			lia[i]=(wlint16)str_instr(s_symbset, s_num[i]);
			if(lia[i]==-1) lia[i]=0;
		}

		lia[j-1] ++;
		k = str_len(s_symbset) ;
		ulia=0;
		for(i=j-1;i>=0;i--)
		{
			if(lia[i]>=k){
				lia[i]-=(wlint16)k;
				if(i>0) lia[i-1]++; else ulia++;
			}
		}

		for(i=0;i<j;i++)
		{
			s_num[i]=s_symbset[lia[i]];
		}

		if((!isfix)&&ulia){
			str_rev(s_num);
			s_num[j]=s_symbset[ulia];
			s_num[j+1]=0;
			str_rev(s_num);
		}

		free(lia);
		return s_num;
	}


	static wlint8 bstr_esc(wlint8 cc)
	{
		if(cc!=0) return cc;
		return 'b';
	}

	static int bstr_in_set(wlint8 c, wlint8 ac_bstresc)
	{
		if(c==bstr_esc(ac_bstresc)) return 0; 
		if(c>='a'&&c<='z') return 1;
		if(c>='0'&&c<='9') return 1;
		if(c>='A'&&c<='Z') return 1;
		return 0;
	}


	static int bstr_iswhole(wlint8 *s, wlint8 ac_bstresc=0)
	{
		wlint32 i;
		switch (i=str_len(s))
			{
			case 0:
				return 1;
			case 1:
				return s[0]!=bstr_esc(ac_bstresc);
			case 2:
				if(s[0]==bstr_esc(ac_bstresc)&&str_ishex(s[1])) return 0;
				return bstr_iswhole(&s[1]);
			default:
				s=s+i-3;
				if(s[0]==bstr_esc(ac_bstresc)&&str_ishex(s[1])&&str_ishex(s[2])) return 1;
				return bstr_iswhole(&s[1]);
			}
	}


	
	static wlint32 bstr_en_size(wlint8 *s,
								wlint32 len,
								wluint8 probability=0 ,
								wlint8 ac_bstresc=0 ,
								int(*apf1)(wlint8,wlint8)=bstr_in_set
								)
	{
		if(s==NULL) return 0;
		if(probability) return len*3+1;

		wlint32 i,j,k;
		for(i=0,j=len,k=0;i<j;i++)
			k += (*apf1)(s[i],ac_bstresc)?1:3;
		return k+1; 
	}
	


	static wlint8 *bstr_en( wlint8 *s  ,
							wlint32 len,
							wluint8 probability=0 ,
							wlint8 ac_bstresc=0 ,
							int(*apf1)(wlint8,wlint8)=bstr_in_set
							)
	{
		static wlint8 c[1];
		c[0]=0;
		wlint8 *t1;
		if(s==NULL) return c;
		t1 = (wlint8 *)malloc( len );
		memcpy(t1,s,len);
		bstr_en(t1,len,s,probability,ac_bstresc,apf1);
		free(t1);
		return s ;
	}

	static wlint8 *bstr_en( wlint8 *s  ,
							wlint32 len,
							wlint8 *dest,
							wluint8 probability=0 ,
							wlint8 ac_bstresc=0 ,
							int(*apf1)(wlint8,wlint8)=bstr_in_set
							)
	{
		static wlint8 c[1];
		c[0]=0;
		if(s==NULL||dest==NULL) return c;
		wlint32 i,j,k,l;
		int rc;

		for(i=0,j=len,k=0;i<j;i++){

			rc = 0;

			do {
				if( !(*apf1)(s[i],ac_bstresc) ) { 
					rc = 1;
					break;
				}

				if( probability	&& ((rand()&0xFF)<probability) ){ 
					rc = 1;
					break;
				}

				dest[k]=s[i];         
				k++;

			}while(0);

			if(rc) {    
				l=(wluint8)s[i];
				sprintf(dest+k, "%c%02X", bstr_esc(ac_bstresc), (unsigned int)l);
				k+=3;
			}
		}
		dest[k]=0;
		return dest;
	}


	static wlint32 bstr_de_size( wlint8 *s ,
								 wlint8 ac_bstresc=0
								)
	{
		if(s==NULL) return 0;
		wlint32 i,j,k;
		for(i=0,j=str_len(s),k=0;i<j; )
			if(	(i+2<j)					    &&
				s[i]==bstr_esc(ac_bstresc)	&&
				str_ishex(s[i+1])			&&
				str_ishex(s[i+2])      ) {
				k++;
				i+=3;
			}else{
				i++;
				k++;
			}
		return k;
	}


	static wlint8 *bstr_de(wlint8 *s, wlint8 ac_bstresc=0)
	{
		return bstr_de(s,s,ac_bstresc);
	}


	static wlint8 *bstr_de(wlint8 *s, wlint8 *dest, wlint8 ac_bstresc=0)
	{
		static wlint8 c[1];
		c[0]=0;
		if(s==NULL||dest==NULL) return c;
		wlint32 i,j,k;
		wlint32 a1,a2;

		wlint8 ss[2];
		ss[1]=0;

		for(i=0,j=str_len(s),k=0;i<j; ) {
			if(	(i+2<j)		&&
				s[i]==bstr_esc(ac_bstresc)	&&
				str_ishex(s[i+1])	&&
				str_ishex(s[i+2])	 ) {

				ss[0]=s[i+1];
				str_ucase(ss);
				a1 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) * 16 ;

				ss[0]=s[i+2];
				str_ucase(ss);
				a2 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) ;

				*(wluint8 *)(dest+k) = (wluint8)(a1+a2);
				k++;
				i+=3;
			}else{
				dest[k] = s[i];
				k++;
				i++;
			}
		}

		
		dest[k]='\0';

		return dest;
	}


	static wlint8 *bstr_b2u(wlint8 *s, wlint8 ac_bstresc=0)
	
	
	{
		wlint8 *t;
		for(t=s;t&&*t;t++){
			if(*t==bstr_esc(ac_bstresc)) *t='%';
			if(*t==' ') *t='+';
		}
		return s;
	}

	static wlint8 *bstr_u2b(wlint8 *s , wlint8 ac_bstresc=0)
	{
		wlint8 *t;
		for(t=s;t&&*t;t++){
			if(*t=='%') *t=bstr_esc(ac_bstresc);
			if(*t=='+') *t=' ';
			if(*t=='?') *t=' ';
		}
		return s;
	}


}; 

#endif


#ifndef WL_STRU_LIST_H
#define WL_STRU_LIST_H

class wl_stru_list {

private:
	wlint8 *lv_lang_wl_stru_list_tp;
	wlint8 *lv_cf_add_t;
	wlint8 *lv_cf_add2_t ;
	wlint32 lv_cf_add2_i;
	wlint8 *lv_cf_add3_t ;
		wlint8 *lv_cf_import_strarr_t, lv_cf_import_strarr_c, lv_cf_import_strarr_c2, *lv_cf_import_strarr_lastt;
		wlint32 lv_cf_import_strarr_i, lv_cf_import_strarr_ti, lv_cf_import_strarr_datalen, lv_cf_import_strarr_seplen;
		wlint32 lv_cf_modi_i;
		int lv_cf_modi_rc;
		wlint8 *lv_cf_modi_t ;
        wlint8 *lv_cf_swap_tp;
		wlint32 lv_cf_swap_j;
		int lv_cf_del_rc;
		wlint32 lv_cf_del_i;
		wlint8 *lv_cf_deltop_tp;
        wlint32 lv_cf_rev_a,lv_cf_rev_b;
		wlint32 lv_cf_rev_x,lv_cf_rev_y,lv_cf_rev_i;
		wluint32 lv_cf_rev_u;
        wlint8 *lv_cf_rev_tp;
        wlint32 lv_cf_sel_low,lv_cf_sel_high,lv_cf_sel_mid,lv_cf_sel_x;
		class wl_stru_list *lv_cf_output_lp;
        wlint32 lv_cf_output_i;
        FILE *lv_cf_output_fp;
		class wl_stru_list *lv_cf_output2_lp;
        wlint32 lv_cf_output2_i;
        FILE *lv_cf_output2_fp;

        wlint8 *lv_init_tp;
        wlint8 *lv_push_tp;
        wlint8 **lv_push_tt;
        wlint32 lv_push_tl,lv_push_ttl;
		wlint32 lv_count_i,lv_count_c;
		wlint8 *lv_chg_tp;
        wlint8 *lv_lcf_free_tp;
        wlint32 lv_cf_qsel_low,lv_cf_qsel_high,lv_cf_qsel_mid,lv_cf_qsel_x;


protected:

    struct  {
        wlint32 depth;
        wlint32 sp;
        wlint8 **stk;
    } str_stack;

	int initdepth ;

	struct {
		int (*cmpf)(const void *,const void *);
		int issorted;							
	} sortstatus;


public:

	int (*iv_mycmp)(const void *,const void *);	

	int iv_fast_del;


public:

    static int cf_sortA_ss( const void *arg1, const void *arg2 )
	{   
		
		return wl_stru_strf::str_cmp( * ( char ** ) arg1, * ( char ** ) arg2 );
	}

	static int cf_sortA_ssi( const void *arg1, const void *arg2 )
	{   
		return wl_stru_strf::str_cmpi( * ( char ** ) arg1, * ( char ** ) arg2 );
	}

	static int cf_sortA_si( const void *arg1, const void *arg2 )
	{   
		return wl_stru_strf::str_atol( *(wlint8 **)arg1) - wl_stru_strf::str_atol( *(wlint8 **)arg2);
	}


	static int cf_sortA_ii( const void *arg1, const void *arg2 )
	{   
		return **(wlint32 **)arg1 - **(wlint32 **)arg2;
	}


public:

	wl_stru_list()	{			wl_stru_list_init_depth(13);	  }
	wl_stru_list(int depth)	{	wl_stru_list_init_depth(depth);    }

    void wl_stru_list_init_depth(int depth)
    {
		initdepth= depth;
        str_stack.stk=NULL;
        str_stack.sp=0;
        init(initdepth);

		cf_setsortf(cf_sortA_ss);
		iv_fast_del = 0;

		sortstatus.cmpf=iv_mycmp;
		sortstatus.issorted=0;
    }

    ~wl_stru_list()
    {
        if(str_stack.stk==NULL) return;
        for(;!isempty();){
            if(isempty()) return ;
            str_stack.sp--;
            lv_lang_wl_stru_list_tp=str_stack.stk[str_stack.sp];
            free(lv_lang_wl_stru_list_tp);
        }
        if(str_stack.stk!=NULL) {
            free(str_stack.stk);
            str_stack.stk=NULL;
        }
    }


	void cf_setsortf(int (*cmpf)(const void *,const void *))
	{
		iv_mycmp = cmpf;
	}


	int cf_copy_str(wl_stru_list *dest, wlint8 *ss_head=NULL, wlint8 *ss_tail=NULL)
	{
		wlint8 *t;
		wlint32 i;
		if(!dest) return 0;
		for(i=0;i<cf_howmany();i++) {
			
			if(-1==dest->cf_add( wl_stru_strf::str_len(cf_read(i))+wl_stru_strf::str_len(ss_head)+wl_stru_strf::str_len(ss_tail)+1 ))
				return 0;
			t = dest->cf_readtop();
			t[0]=0;
			if(ss_head&&*ss_head) ::strcpy(t, ss_head);
			::strcat(t, cf_read(i));
			if(ss_tail&&*ss_tail) ::strcat(t, ss_tail);
		}
		return 1;
	}


	int cf_copy_bstr(wl_stru_list *dest, int want_sz=1, wluint8 probability=0)
	{
		wlint32 i,j,len,sourcelen;
		j=cf_howmany();
		for(i=0;i<j;i++) {
			sourcelen = wl_stru_strf::str_len(cf_read(i));
			len = wl_stru_strf::bstr_en_size(cf_read(i), (want_sz?1:0)+sourcelen, probability);
			if(-1==dest->cf_add(len)) return 0;
			wl_stru_strf::bstr_en(cf_read(i), (want_sz?1:0)+sourcelen, dest->cf_readtop(), probability);
		}
		return 1;
	}


	int cf_plot(wlint32 a_idx) 
	{
		wlint32 i;
		if(a_idx<=cf_howmany()-1) return 1;
		for(i=cf_howmany();i<=a_idx;i++) if(-1==cf_add("")) return 0;
		return 1;
	}


	int cf_collect(void) { return cf_collect(""); }

	int cf_collect(const wlint8 *a_sep1) 
	{
		char*a_sep=(char*)a_sep1;
		wlint32 i,j,k;
		wlint32 a;
		wlint8 *t;

		a = wl_stru_strf::str_len( a_sep );
		j = howmany_AA();
		for(k=i=0;i<j;i++) {
			k += wl_stru_strf::str_len( cf_read(i) );
			k += a;
		}
		k++;
		if(-1==cf_add(k)) return 0;
		t = cf_readtop();
		for(i=0;i<j;i++) {
			strcpy(t, cf_read(i) );
			t += wl_stru_strf::str_len( cf_read(i) );
			strcpy(t, a_sep==NULL?"":a_sep );
			t += a;
		}
		*t='\0';

		if(j!=0) {
			i=cf_swap(0,j);
			if(!i) return 0;
		}
		while(howmany_AA()>1){
			cf_deltop();
		}
		return 1;
	}


	wlint32 cf_add(wlint8 c1, wlint8 c2)
	{
		wlint8 s[3];
		s[0]=c1;
		s[1]=c2;
		s[2]=0;
		return cf_add(s);
	}


	wlint32 cf_add(const wlint8 *s1)
	{
		wlint8 *s=(char*)s1;

			sortstatus.issorted=0;

		lv_cf_add_t = push(s, wl_stru_strf::str_len(s) + 1, 1 );

		if(lv_cf_add_t==NULL) return -1;
		return str_stack.sp - 1;
	}


	wlint32 cf_add(wlint8 *s, wlint32 a_size)
	{
			sortstatus.issorted=0;

		lv_cf_add2_t = push(s, a_size, 0 );

		if(lv_cf_add2_t==NULL) return -1;

		for(lv_cf_add2_i=0;lv_cf_add2_i<a_size;lv_cf_add2_i++) {
		    lv_cf_add2_t[lv_cf_add2_i] = s[lv_cf_add2_i];
		}
		return str_stack.sp - 1;
	}


	wlint32 cf_add(wlint32 a_size)
	{
			sortstatus.issorted=0;

		lv_cf_add3_t = push("", a_size, 0 );

		if(lv_cf_add3_t==NULL) return -1;
		return str_stack.sp - 1;
	}


	wlint32 cf_adda(wlint32 i) 
	{
		wlint8 c[33];
		return cf_add(wl_stru_strf::str_ltoa(i,c) );
	}

	wlint32 cf_addf(double e) 
	{
		wlint8 c[44];
		sprintf(c, "%f", e);
		return cf_add(c);
	}


	wlint32 cf_add32(wlint32 l) 
	{
		return cf_add( (wlint8 *)(&l), sizeof(wlint32) );
		
	}


	wlint8 *cf_read(wlint32 idx) 
	{
        if(idx<0) return NULL;
        if(idx>=howmany_AA()) return NULL;
        if(isempty()) return NULL;
        return  str_stack.stk[idx];
    }


	wlint8 *cf_readtop(void)
	{
		return cf_read( cf_howmany() - 1 );
	}


	wlint32 cf_maxlen(void)
	{
		wlint32 i,j,k,m;
		k=0;
		j=howmany_AA();
		for(i=0;i<j;i++) {
			m=wl_stru_strf::str_len( cf_read(i));
			if(k<m)k=m;
		}
		return k;
	}


	wlint32 cf_sumlen(void)
	{
		wlint32 i,j,k,m;
		k=0;
		j=howmany_AA();
		for(i=0;i<j;i++) {
			m=wl_stru_strf::str_len( cf_read(i));
			k += m;
		}
		return k;
	}


	int cf_import_strarr(wlint8 *as_data, wlint8 ac_sep, int opt_is_token)
	{
		wlint8 t[2];
		t[0]=ac_sep;
		t[1]=0;
		return cf_import_strarr(as_data,t,opt_is_token) ;
	}


	int cf_import_strarr(wlint8 *as_data, wlint8 *as_sep, int opt_is_token)
	{

		if(wl_stru_strf::str_len(as_sep)==1)
			return cf_import_strarr_v1(as_data,as_sep,opt_is_token);

		class wl_stru_list *pA;
		class wl_stru_list *pB;
		wlint32  n,m,i,j,k, b1, b2;
		wlint8 c1 , *t;

		m = i = j = 0;
		n = wl_stru_strf::str_len(as_data);
		k = wl_stru_strf::str_len(as_sep);
		pA = new class wl_stru_list;
		pB = new class wl_stru_list;

		t = (wlint8 *)malloc(n+1);
		if(!t) return 0;
		if(as_data) as_data = ::strcpy(t,as_data);

		do {
			if(m>=n) break;
			i = wl_stru_strf::str_instr(as_data + m, as_sep);
			if(i<0)  break;
			i += m;
			m = i;

			pA->cf_add32(i);
			j ++;
			m += k;

		} while(1);

		b1 = 0 ; 
		b2 = j - 1 ; 

		j = 0;
		pB->cf_add32(j);
		for(i=b1;i<=b2;i++){
			j = *(wlint32 *)pA->cf_read(i);
			pB->cf_add32(j);
			pB->cf_add32(j+k);
		}
		pB->cf_add32(n );

		

		for(i=0;i<pB->cf_howmany();i+=2) {
			m = *(wlint32 *)pB->cf_read(i);
			n = *(wlint32 *)pB->cf_read(i+1);
			k = n - m;
			t = as_data + m;
			c1 = t[k];
			t[k]=0;

			
			if(opt_is_token&&k==0){
				;
			}else
				this->cf_add(t);

			t[k]=c1;
		}

		free(as_data);
		delete pA;
		delete pB;

		return 1;
	}


	int cf_import_strarr_v1(wlint8 *as_data, wlint8 *as_sep, int opt_is_token)
    {
		if(as_data==NULL) return 0;
		if(as_sep==NULL) return 0;
		if(as_data[0]==0&&!opt_is_token) return 1;

			sortstatus.issorted=0;

		lv_cf_import_strarr_datalen = wl_stru_strf::str_len(as_data);
		lv_cf_import_strarr_seplen =  wl_stru_strf::str_len(as_sep);
		lv_cf_import_strarr_t = (char *)malloc( lv_cf_import_strarr_datalen + lv_cf_import_strarr_seplen * 2 + 3 );
		if(lv_cf_import_strarr_t==NULL) return 0;
		strcpy(lv_cf_import_strarr_t, as_data);
		strcat(lv_cf_import_strarr_t, as_sep);

		if(as_sep[0]==0) {
			cf_add(lv_cf_import_strarr_t);
			free(lv_cf_import_strarr_t);
			return 1;
		}

		for(lv_cf_import_strarr_lastt=lv_cf_import_strarr_t,lv_cf_import_strarr_i=0;lv_cf_import_strarr_i<lv_cf_import_strarr_datalen+lv_cf_import_strarr_seplen;){
			lv_cf_import_strarr_ti = lv_cf_import_strarr_i+lv_cf_import_strarr_seplen;
			lv_cf_import_strarr_c = lv_cf_import_strarr_t[lv_cf_import_strarr_ti];
			lv_cf_import_strarr_t[lv_cf_import_strarr_ti] = 0;
			if(!strcmp(lv_cf_import_strarr_t+lv_cf_import_strarr_i,as_sep)){ 
				lv_cf_import_strarr_c2= lv_cf_import_strarr_t[lv_cf_import_strarr_i];
				lv_cf_import_strarr_t[lv_cf_import_strarr_i]=0;
				if(opt_is_token==0){ 
					cf_add(lv_cf_import_strarr_lastt);
				}else{
					if(lv_cf_import_strarr_lastt[0]!=0)cf_add(lv_cf_import_strarr_lastt);
				}
				lv_cf_import_strarr_t[lv_cf_import_strarr_i]=lv_cf_import_strarr_c2;
				lv_cf_import_strarr_i += lv_cf_import_strarr_seplen;
				lv_cf_import_strarr_lastt = lv_cf_import_strarr_t+lv_cf_import_strarr_i;
			}else{
				lv_cf_import_strarr_i ++;
			}
			lv_cf_import_strarr_t[lv_cf_import_strarr_ti]= lv_cf_import_strarr_c;
		}
		free(lv_cf_import_strarr_t);
		return 1;
	}


	wlint32 cf_howmany(void)
	{
		return howmany_AA();
	}


	int cf_modi(wlint32 idx, const wlint8 *s1)
    {
		char *s = (char*)s1;
		
			sortstatus.issorted=0;

        return chg(idx, s, wl_stru_strf::str_len(s) + 1, 1 );
    }


	int cf_modi(wlint32 idx, wlint8 *s, wlint32 a_size)
    {
			sortstatus.issorted=0;

		lv_cf_modi_rc= chg(idx, s, a_size, 0);
		lv_cf_modi_t = cf_read(idx);
		for(lv_cf_modi_i=0;lv_cf_modi_i<a_size;lv_cf_modi_i++)
			lv_cf_modi_t[lv_cf_modi_i] = s[lv_cf_modi_i];
        return lv_cf_modi_rc;
    }


	int cf_modi(wlint32 idx, wlint32 a_size)
    {
			sortstatus.issorted=0;

		lv_cf_modi_rc= chg(idx, "", a_size, 0);
		lv_cf_modi_t = cf_read(idx);
		
			
        return lv_cf_modi_rc;
    }


	int cf_swap(wlint32 idx1, wlint32 idx2)
	{
			sortstatus.issorted=0;

		lv_cf_swap_j= idx1;
        if(lv_cf_swap_j<0) return 0;
        if(lv_cf_swap_j>=cf_howmany()) return 0;
        if(isempty()) return 0;

		lv_cf_swap_j= idx2;
        if(lv_cf_swap_j<0) return 0;
        if(lv_cf_swap_j>=cf_howmany()) return 0;
        if(isempty()) return 0;

		if(idx1==idx2) return 1;

        lv_cf_swap_tp = str_stack.stk[idx1];
		str_stack.stk[idx1] = str_stack.stk[idx2];
		str_stack.stk[idx2] = lv_cf_swap_tp;
        return 1;
    }


	int cf_del(wlint32 idx)
    {

		lv_cf_del_rc = lcf_free(idx);
        if(lv_cf_del_rc==0) return 0;

		if(iv_fast_del){

				sortstatus.issorted=0;

			cf_swap(idx, (howmany_AA() - 1) );
		}else{
			for(lv_cf_del_i=idx;lv_cf_del_i < (howmany_AA() - 1);lv_cf_del_i++)
				cf_swap(lv_cf_del_i, lv_cf_del_i+1);
		}

		str_stack.sp--;
		return 1;
	}


	int cf_ins(wlint32 idx_to)
    {

		wlint32 i;
		if(idx_to<0||idx_to>=cf_howmany()) return 0;

			sortstatus.issorted=0;


		for(i=cf_howmany()-1;i>idx_to;i--){
			cf_swap(i, i-1);
		}

		return 1;
	}


	int cf_deltop(void) 
    {
        if(str_stack.stk==NULL) return 0;
        if(isempty()) return 0;
        str_stack.sp--;
        lv_cf_deltop_tp=str_stack.stk[str_stack.sp];
        free(lv_cf_deltop_tp);
        return 1;
    }


	int cf_clean(void)
	{
		while( cf_howmany()!= 0) { cf_deltop(); }
		return 1;
	}


	int cf_clean(wlint32 remain)
    {
        if(remain<0) remain=0;
		while( cf_howmany()>remain)	{
			cf_del(0);
		}
		return 1;
	}


	int cf_rev(void)
    {
			sortstatus.issorted=0;

		lv_cf_rev_u = (wluint32)cf_howmany();
		lv_cf_rev_u >>= 1;
		lv_cf_rev_x = lv_cf_rev_u;
		lv_cf_rev_y = cf_howmany() - 1;

        for(lv_cf_rev_i=0;lv_cf_rev_i<lv_cf_rev_x;lv_cf_rev_i++) {
			lv_cf_rev_a = lv_cf_rev_i;
			lv_cf_rev_b = lv_cf_rev_y - lv_cf_rev_i;
			lv_cf_rev_tp=str_stack.stk[lv_cf_rev_a];
			str_stack.stk[lv_cf_rev_a]= str_stack.stk[lv_cf_rev_b];
			str_stack.stk[lv_cf_rev_b]= lv_cf_rev_tp;
		}
		return 1;
    }


	void cf_qsort( void )
    { 
        cf_qsort(iv_mycmp);
    }


	void cf_qsort( int (*mycmpf)(const void *,const void *) )
    { 
        iv_mycmp=mycmpf;

			sortstatus.cmpf=iv_mycmp; sortstatus.issorted=1;

        ::qsort((void *)str_stack.stk, (size_t)howmany_AA(), sizeof(char *), iv_mycmp);
    }


	wlint32 cf_sel(void *pvalue )
    {
		return cf_sel(iv_mycmp, pvalue);
	}


	wlint32 cf_sel( int (*mycmpf)(const void *,const void *) , void *pvalue )
    {
	 
     

		if(sortstatus.cmpf==mycmpf&&sortstatus.issorted)
			return cf_qsel(sortstatus.cmpf, pvalue);


		iv_mycmp=mycmpf;

		if(iv_mycmp==NULL) return -1;
        if(str_stack.stk==NULL) return -1;
        lv_cf_sel_low=0;
        lv_cf_sel_high=str_stack.sp - 1;
        while(lv_cf_sel_low<=lv_cf_sel_high) {
            if(1||lv_cf_sel_high-lv_cf_sel_low<=3) {
                for(;lv_cf_sel_low<=lv_cf_sel_high;lv_cf_sel_low++) {
                    lv_cf_sel_mid=lv_cf_sel_low;
                    
					lv_cf_sel_x = (*iv_mycmp) ( (const void *)(&pvalue), (const void *)(&str_stack.stk[lv_cf_sel_mid])  ) ;
					
					
                    if(lv_cf_sel_x==0) return lv_cf_sel_mid;
                }
                return -1;
            }
            lv_cf_sel_mid=(lv_cf_sel_low+lv_cf_sel_high)/2;
            
            if(lv_cf_sel_x<0) lv_cf_sel_high=lv_cf_sel_mid-1;
            else if(lv_cf_sel_x>0) lv_cf_sel_low=lv_cf_sel_mid+1;
            else return 1; 
        }
        return -1;
    }


	wlint32 cf_output(char *pfn)
	{
        return cf_output(pfn, "\r\n");
    }


	wlint32 cf_outputa(char *pfn)
	{
        return cf_output(pfn, "\r\n", "ab");
    }

	wlint32 cf_output(wlint8 *pfn, const wlint8 *ln_sep)
    {
        return cf_output(pfn, (char*)ln_sep, "wb");
    }


	wlint32 cf_output(const wlint8 *pfn1, const wlint8 *ln_sep1, const wlint8 *openMethd1)
    {
		char *pfn=(char*)pfn1;
		char *ln_sep=(char*)ln_sep1;
		char *openMethd=(char*)openMethd1;
		
		lv_cf_output_lp = this;
        lv_cf_output_fp=fopen(pfn,openMethd);
        if(lv_cf_output_fp==NULL) return 0;
        for(lv_cf_output_i=0;lv_cf_output_i<lv_cf_output_lp->cf_howmany();lv_cf_output_i++) {
            fprintf(lv_cf_output_fp,"%s%s",lv_cf_output_lp->cf_read(lv_cf_output_i), ln_sep);
        }
        fclose(lv_cf_output_fp);
        return lv_cf_output_i;
    }


	wlint32 cf_output(char *pfn , wlint32 rec_size)
    {
		lv_cf_output2_lp = this;

        lv_cf_output2_fp=fopen(pfn,"wb");
        if(lv_cf_output2_fp==NULL) return 0;
        for(lv_cf_output2_i=0;lv_cf_output2_i<lv_cf_output2_lp->cf_howmany();lv_cf_output2_i++) {
			fwrite(lv_cf_output2_lp->cf_read(lv_cf_output2_i), rec_size, 1, lv_cf_output2_fp);
        }
        fclose(lv_cf_output2_fp);
        return lv_cf_output2_i;
    }


	

	wlint32 cf_setjiao(class wl_stru_list *pl)
    {
		wlint32 i;
		pl->cf_qsort( iv_mycmp );
		for(i=cf_howmany()-1;i>=0;i--) if(-1==pl->cf_sel(cf_read(i)) )cf_del(i);
		return cf_howmany();
	}


	wlint32 cf_setcha(class wl_stru_list *pl)
    {
		wlint32 i;
		pl->cf_qsort( iv_mycmp );
		for(i=cf_howmany()-1;i>=0;i--) if(!(-1==pl->cf_sel(cf_read(i)) ))cf_del(i);
		return cf_howmany();
	}


	wlint32 cf_setuniq(void)
	{
		return cf_setgroup(NULL);
	}


	wlint32 cf_setgroup(class wl_stru_list *pl)
    {
		wlint32 i,j;
		wlint8 *t1, *t2;
		cf_qsort( ); 
		j=1;
		for(i=cf_howmany()-1;i>=1;i--) {
			t1 = cf_read(i);
			t2 = cf_read(i-1);
			if(!((*iv_mycmp) ( (const void *)(&t1), (const void *)(&t2) ))) {
				cf_del(i);
				j++;
			}else{
				
				
				if(NULL!=pl) {
					
					pl->cf_add32(j);
				}
				j=1;
			}
		}
		if(cf_howmany()>0){
			
			
			if(NULL!=pl) {
				
				pl->cf_add32(j);
			}
		}
		if(NULL!=pl) { pl->cf_rev(); }
		return cf_howmany();
	}


	wlint8 *cf_set_luosuo(void) 
    {
		wlint32 i,j,k1,k2;
		class wl_stru_list *p;

		p = new class wl_stru_list;
		cf_setgroup(p);
		for(j=k1=i=0;i<cf_howmany();i++) {
			k2 = *(wlint32 *)p->cf_read(i);
			if(k2>k1) {
				k1=k2; 
				j=i;   
			}
		}

		if(cf_howmany()&&j>0) {
			cf_swap(0,j);
		}

		while(cf_howmany()>1)
			cf_deltop();

		delete p;
		return cf_read(0);
	}


private:

    int init(long depth)
    {

        if(str_stack.stk!=NULL) {
            for(;!isempty();){
                if(isempty()) break;
                str_stack.sp--;
                lv_init_tp=str_stack.stk[str_stack.sp];
                free(lv_init_tp);
            }
            free(str_stack.stk);
            str_stack.stk=NULL;
        }
        str_stack.stk=(char **)malloc(sizeof(char *)*(depth+2));
        if(str_stack.stk==NULL) return 0;
        str_stack.sp=0;
        str_stack.depth=depth;
        return 1;
    }


    int isempty(void)
    {
        if(str_stack.stk==NULL) return 1;
    	return str_stack.sp-1<0?1:0;
    }


    int isfull(void)
    {
        if(str_stack.sp>str_stack.depth) return 1;
        return 0;
    }


    char *push(const char *s1, wlint32 a_size, wlint8 ifstrcpy)
    {
		char *s=(char*)s1;

        if(str_stack.stk==NULL) { return NULL; }
        if(s==NULL) return NULL;
        if(isfull()) {
            lv_push_tl = 2 + (long)(1.18 * (float)str_stack.depth) + initdepth;
            lv_push_tt = (char **)malloc(sizeof(char *)*lv_push_tl);
            if(lv_push_tt==NULL) return NULL;
            for(lv_push_ttl=0;lv_push_ttl<=str_stack.depth;lv_push_ttl++)
				lv_push_tt[lv_push_ttl]=str_stack.stk[lv_push_ttl];
            free(str_stack.stk);
            str_stack.stk=lv_push_tt;
            str_stack.depth=lv_push_tl-2;
			
        }
        lv_push_tp=(char *)malloc(a_size);
        if(lv_push_tp==NULL) return NULL;
        str_stack.stk[str_stack.sp]=lv_push_tp;
        if(ifstrcpy) strcpy(str_stack.stk[str_stack.sp],s);
        str_stack.sp++;
        return lv_push_tp;
    }


    wlint32 howmany_AA()
    {
        return str_stack.sp;
    }


	long count(char *s) 
	{

		lv_count_c=0;
		for(lv_count_i=0;lv_count_i<howmany_AA();lv_count_i++) {
			if (!strcmp(s, cf_read(lv_count_i))) lv_count_c++;
		}
		return lv_count_c;
	}


	int chg(wlint32 idx, const wlint8 *newvalue1, wlint32 a_size, wlint8 ifstrcpy)
    {
		char *newvalue=(char*)newvalue1;
        if(idx<0) return 0;
        if(idx>=howmany_AA()) return 0;
        if(isempty()) return 0;
        lv_chg_tp=str_stack.stk[idx];
		free(lv_chg_tp);
		lv_chg_tp=(char *)malloc( a_size );
		if(lv_chg_tp==NULL) return 0;
		if(ifstrcpy) strcpy(lv_chg_tp,newvalue);
		str_stack.stk[idx]=lv_chg_tp;
        return 1;
    }


	int lcf_free(wlint32 idx)
    {

        if(idx<0) return 0;
        if(idx>=howmany_AA()) return 0;
        if(isempty()) return 0;
        lv_lcf_free_tp=str_stack.stk[idx];
		free(lv_lcf_free_tp);
		return 1;
	}


	wlint32 cf_qsel( void *pvalue )
	{
		return cf_qsel(iv_mycmp, pvalue);
	}


	wlint32 cf_qsel( int (*mycmpf)(const void *,const void *) , void *pvalue)
    {
		iv_mycmp=mycmpf;

		if(iv_mycmp==NULL) return -1;
        if(str_stack.stk==NULL) return -1;

        lv_cf_qsel_low = 0;
        lv_cf_qsel_high = str_stack.sp - 1 ;
        while(lv_cf_qsel_low<=lv_cf_qsel_high) {
            lv_cf_qsel_mid = (lv_cf_qsel_low+lv_cf_qsel_high)/2;
            lv_cf_qsel_x = (*iv_mycmp) ( (const void *)(&pvalue), (const void *)(&str_stack.stk[lv_cf_qsel_mid])  ) ;
            if(lv_cf_qsel_x<0) lv_cf_qsel_high = lv_cf_qsel_mid - 1;
            else if(lv_cf_qsel_x>0) lv_cf_qsel_low = lv_cf_qsel_mid + 1;
            else return lv_cf_qsel_mid; 
        }
        return  -1;
    }


}; 


#endif


#ifndef WL_STRU_I32QUE_H
#define WL_STRU_I32QUE_H


class wl_stru_i32que {

private:

	wl_stru_list	iv_knl;
	wlint32		iv_width, iv_x , *ivp_base;
	wlint32		iv_init_width;

	int lf_alloc(void)
	{
		int rc;
		rc = -1!=iv_knl.cf_add(iv_width*sizeof(wlint32));
		ivp_base = (wlint32 *)iv_knl.cf_readtop();
		return rc;
	}

	int lf_resize(void)
	{
		wlint32		i;
		i= iv_width;
		iv_width = (wlint32)((double)iv_width*1.18+3.10+iv_init_width);
		if(!lf_alloc())return 0;
		memcpy(iv_knl.cf_read(1), iv_knl.cf_read(0), i*sizeof(wlint32));
		return iv_knl.cf_del(0);
	}

	int wl_stru_i32que_init(wlint32 width)
    {
		iv_init_width = iv_width= (width<=0?2:width);
		iv_x= 0;
		iv_knl.cf_setsortf(iv_knl.cf_sortA_ii);
		return lf_alloc();
    }

public:

	wl_stru_i32que()	{	wl_stru_i32que_init(33);	}


	wl_stru_i32que(wlint32 width)	{	wl_stru_i32que_init(width);    }


	class wl_stru_list *cf_getknl(void)
	{
		return &iv_knl;
	}


	int cf_clean(void)
	{
		iv_x = 0;
		return 1;
	}


	int cf_push(wlint32 i)
	{
		if(iv_x>=iv_width)
			if(!lf_resize()) return 0;
		ivp_base[iv_x++] = i;
		return 1;
	}


	int cf_pop(wlint32 *p)
	{
		iv_x--;
		if(iv_x<0) return 0;
		*p = ivp_base[iv_x];
		return 1;
	}


	int cf_deltop(void)
	{
		iv_x--;
		if(iv_x<0) return 0;
		return 1;
	}


	wlint32 cf_hm(void)
	{
		return (iv_x);
	}


	int cf_read(wlint32 idx, wlint32 *p)
	{
		if(idx<0||idx>=cf_hm()) return *p=0;
		*p=ivp_base[idx];
		return 1;
	}


	wlint32 * cf_read(wlint32 idx)
	{
		if(idx<0||idx>=cf_hm()) return NULL;
		return  ivp_base+idx;
	}


}; 


#endif


#ifndef WL_STRU_SHEET_H
#define WL_STRU_SHEET_H




class wl_stru_sheet {

private:
    class wl_stru_list  iv_aa;
	class wl_stru_list *iv_tp;

		wlint32 lv_wl_stru_sheet_i;
		class wl_stru_sheet *lv_cf_output_lp;
        wlint32 lv_cf_output_x,lv_cf_output_y;
        FILE *lv_cf_output_fp;
		class wl_stru_list *lv_cf_output_tp;

public:

    static int cf_sortA_ss( const void *arg1, const void *arg2 )
	{   
		return ::strcmp( (**( class wl_stru_list ***)arg1)->cf_read(0), (**( class wl_stru_list ***)arg2)->cf_read(0) );
	}


	static int cf_sortA_ii( const void *arg1, const void *arg2 )
	{   
		wlint32 i,j;
		class wl_stru_list *p1, *p2 ;

		p1 = **( class wl_stru_list ***)arg1;
		p2 = **( class wl_stru_list ***)arg2;

		i = *((wlint32 *)(p1->cf_read(0)));
		j = *((wlint32 *)(p2->cf_read(0)));

		return i-j;
	}


public:

    wl_stru_sheet()
    {
		iv_aa.iv_fast_del=0;
		cf_getsheetknl()->cf_setsortf(cf_sortA_ss);
    }

    ~wl_stru_sheet()
    {

		iv_aa.iv_fast_del=0;
		for(lv_wl_stru_sheet_i=iv_aa.cf_howmany()-1;lv_wl_stru_sheet_i>=0;lv_wl_stru_sheet_i--)  cf_delrow(lv_wl_stru_sheet_i);
    }


	int cf_plot(wlint32 a_row, wlint32 a_col) 
	{
		wlint32 i;
		if(a_row<=cf_rowcount()-1) return 1;
		for(i=cf_rowcount();i<=a_row;i++) if(-1==cf_addrow()) return 0;
		for(i=0;i<=a_row;i++) if(!cf_getrow(i)->cf_plot(a_col)) return 0;
		return 1;
		
	}


	wlint32 cf_addrow(void)
	{
		iv_tp =  new class wl_stru_list;
		return iv_aa.cf_add( (wlint8 *)(&iv_tp), sizeof(wl_stru_list *) );
	}


	int cf_delrow(wlint32 idx)
    {
		iv_tp = cf_getrow(idx);
		delete iv_tp;
		return iv_aa.cf_del(idx);
	}


	int cf_dellastrow(void)
    {
		return cf_delrow(cf_rowcount()-1);
	}


	int cf_clean(void)
	{
		while( cf_rowcount()!= 0)
		{
			cf_delrow(cf_rowcount()-1);
		}
		return 1;
	}


	wlint32 cf_rowcount(void)
	{
		return iv_aa.cf_howmany();
	}


	wlint8 *cf_getele(wlint32 row, wlint32 col)
	{
		if(row>=cf_rowcount()) return NULL;
		return (wlint8 *)(cf_getrow(row)->cf_read(col));
	}


	class wl_stru_list *cf_getrow(wlint32 idx)
	{
		class wl_stru_list **t;
		t=(class wl_stru_list **)iv_aa.cf_read(idx);
		return t==NULL?NULL:*t;
	}


	class wl_stru_list *cf_getlastrow(void)
	{
		return cf_getrow(cf_rowcount()-1);
	}


	class wl_stru_list *cf_getsheetknl(void)
	{
		return (&iv_aa) ;
	}


	wlint32 cf_output(wlint8 *pfn)
	{
		return cf_output(pfn, "", "", "\t", "\n");
	}


	wlint32 cf_output(const wlint8 *pfn_1, const wlint8 *quo1_1, const wlint8 *quo2_1, const wlint8 *s_td_1, const wlint8 *s_tr_1)
    {
		char *pfn=(char*)pfn_1;
		char *quo1=(char*)quo1_1;
		char *quo2=(char*)quo2_1;
		char *s_td=(char*)s_td_1;
		char *s_tr=(char*)s_tr_1;
		

		lv_cf_output_lp = this;
        lv_cf_output_fp=fopen(pfn,"w");
        if(lv_cf_output_fp==NULL) return 0;
        for(lv_cf_output_y=0;lv_cf_output_y<(lv_cf_output_lp->cf_getsheetknl())->cf_howmany();lv_cf_output_y++) {
			lv_cf_output_tp = lv_cf_output_lp->cf_getrow(lv_cf_output_y);
			for(lv_cf_output_x=0;lv_cf_output_x<lv_cf_output_tp->cf_howmany();lv_cf_output_x++) {
				fprintf(lv_cf_output_fp,"%s%s%s", quo1, lv_cf_output_tp->cf_read(lv_cf_output_x), quo2);
				if(lv_cf_output_x!=(lv_cf_output_tp->cf_howmany() - 1))fprintf(lv_cf_output_fp,"%s", s_td);
			}
			
			fprintf(lv_cf_output_fp,"%s", s_tr);
        }
        fclose(lv_cf_output_fp);
        return lv_cf_output_y;
    }


	int cf_import_str(const wlint8 *s_data, const wlint8 *s_td, const wlint8 *s_tr)
    {
		return cf_import_str((char*)s_data, (char*)s_td, 0 , (char*)s_tr, 1 );
	}


	int cf_import_str(wlint8 *s_data, wlint8 *s_td, int td_mthd, wlint8 *s_tr, int tr_mthd)
    {
		class wl_stru_list a, b;
		wlint32 i;

		a.cf_import_strarr(s_data, s_tr, tr_mthd);
		for(i=0;i<a.cf_howmany();i++){
			cf_addrow();
			cf_getlastrow()->cf_import_strarr(a.cf_read(i), s_td, td_mthd);
		}
		return 1;
	}


}; 

#endif


#ifndef WL_STRU_PRPT01_H
#define WL_STRU_PRPT01_H


class wl_stru_prpt01  : public wl_stru_list {

public:

    wl_stru_prpt01()
    {
		iv_fast_del = 0;
		cf_setsortf(cf_sortA_ssi);
		sortstatus.cmpf=iv_mycmp;
		sortstatus.issorted=0;
    }


	int cf_clean(void)
	{
		
		return wl_stru_list::cf_clean();
	}


	wlint8 *cf_prpt_new(wlint8 *s_var, wlint8 *s_val) 
	{
		wlint32 i;
		wlint8 *t;

		i = cf_add( wl_stru_strf::str_len(s_var) + wl_stru_strf::str_len(s_val) + 2 );

		::strcpy(cf_read(i), s_var);
		t = ::strcpy(cf_read(i)+wl_stru_strf::str_len(s_var)+1, s_val);

		
		return t;
	}


	wlint8 *cf_prpt_get(const wlint8 *s_var1) 
	{
		wlint8 *s_var=(char*)s_var1;
		wlint32 i;
		static wlint8 c[1];

		c[0]=0;

		
		i = cf_sel(s_var);

		
		if(i==-1) return c;

		return cf_read(i) + wl_stru_strf::str_len(s_var) + 1 ;
	}


	wlint8 *cf_prpt_get(wlint32 i, int i_want_val) 
	{
		static wlint8 c[1];
		c[0]=0;

		if(i<0||i>=cf_howmany()) return c; 

		if(i_want_val) return cf_read(i) + 1+ wl_stru_strf::str_len(cf_read(i)) ;
		else return cf_read(i) ;
	}


	wlint8 *cf_prpt_let(const wlint8 *s_var1, const wlint8 *s_newval1) 
	{
		char *s_var=(char*)s_var1;
		char *s_newval=(char*)s_newval1;
		wlint32 i;

		
		i = cf_sel(s_var);

		if(i==-1) {
			
			return cf_prpt_new(s_var, s_newval);
		}

		class wl_stru_list a;
		a.cf_add(s_var);
		a.cf_add(s_newval);
		s_var = a.cf_read(0);
		s_newval= a.cf_read(1);

		cf_modi(i,  wl_stru_strf::str_len(s_var) + wl_stru_strf::str_len(s_newval) + 2 );
		::strcpy(cf_read(i), s_var);
		return ::strcpy(cf_read(i)+ wl_stru_strf::str_len(s_var)+1, s_newval);
	}


	wlint8 *cf_prpt_let(wlint8 *s_var, wlint32  i_newval) 
	{
		wlint8 c[33];
		wl_stru_strf::str_ltoa(i_newval,c);
		return cf_prpt_let(s_var, c);
	}


	int cf_prpt_del(wlint8 *s_var) 
    {
		wlint32 i;

		
		i = cf_sel(s_var);

		if(i==-1) return 0;
        return cf_del(i);
	}


	wlint8 *cf_prpt_cat(const wlint8 *s_var1, const wlint8 *s_cat_val1) 
	{
		char * s_var=(char*)s_var1;
		char *s_cat_val=(char*)s_cat_val1;
		wl_stru_list a;
		wlint8 *t;

		t = cf_prpt_get(s_var);

		a.cf_add( wl_stru_strf::str_len(t) + wl_stru_strf::str_len(s_cat_val) + 1 ); 

		sprintf(a.cf_readtop(), "%s%s", t, s_cat_val);

		t = cf_prpt_let(s_var, a.cf_readtop());

		return t;
	}


	wlint8 *cf_prpt_add(wlint8 *s_var, wlint8 *s_val1,  wlint8 *s_val2) 
	{
		class wl_stru_list aa;
		aa.cf_add(s_val1);
		aa.cf_add(s_val2);

		cf_prpt_let(s_var, aa.cf_read(0));
		return cf_prpt_cat(s_var, aa.cf_read(1));
	}


	wlint8 *cf_prpt_kuo(wlint8 *s_var, wlint8 *s_kuoval1,  wlint8 *s_kuoval2) 
	{
		cf_prpt_cat(s_var, s_kuoval2);
		return cf_prpt_add(s_var, s_kuoval1, cf_prpt_get(s_var));
	}


	wlint8 *cf_pstr_replace(wlint8 *s_var, wlint8 *s1, wlint8 *s2, int opt)
	{
		class wl_stru_list b;
		class wl_stru_prpt01 a;
		
		a.cf_prpt_let("t", "");
		a.cf_prpt_let("t2", "");
		
		wlint32 i1, i2;

		if(s_var==NULL||s1==NULL||*s_var==0||*s1==0||s2==NULL) return s_var;
		

		
		a.cf_prpt_let("tmp", cf_prpt_get(s_var));
		if(!wl_stru_strf::str_cmp(s1,wl_stru_strf::str_right(a.cf_prpt_get("tmp"), wl_stru_strf::str_len(s1)))){
			a.cf_prpt_let("t2", s2);
		}else{
			a.cf_prpt_let("t2", "");
		}

		
		b.cf_import_strarr(cf_prpt_get(s_var), s1, opt);
		i2 = b.cf_howmany();

		
		

		for(i1=0;i1<i2-1;i1++){
			a.cf_prpt_cat("t", b.cf_read(i1));
			a.cf_prpt_cat("t", s2 );
		}

		
		a.cf_prpt_let("out", a.cf_prpt_get("t") );
		if(i2>0) a.cf_prpt_cat("out", b.cf_read(i2-1) );

		
		
		if(opt&&!wl_stru_strf::str_cmp(s1,wl_stru_strf::str_right(cf_prpt_get(s_var), wl_stru_strf::str_len(s1)))){
			
			a.cf_prpt_cat("out", a.cf_prpt_get("t2") );
		}
		return cf_prpt_let(s_var, a.cf_prpt_get("out") );
	}


	void cf_prpt_sort( void )
    {
        cf_qsort( );
    }


	int cf_import_prpt(char *as_data, char *as_sepTD, char *as_sepTR)
	{
		class wl_stru_list a, b;
		wlint32 i;

		a.cf_import_strarr(as_data, as_sepTR, 0);

		for(i=0;i<a.cf_howmany();i++){
			b.cf_clean();
			b.cf_import_strarr(a.cf_read(i), as_sepTD, 0);
			if(b.cf_howmany()>=2){
				cf_prpt_let(b.cf_read(0), b.cf_read(1));
			}
		}
		cf_prpt_sort();
		return 1;
	}


	int cf_import_prpt(char **p_data, char *as_sepTD )
	{
		class wl_stru_list  b;
		wlint32 i;

		for(i=0;;i++){
            if(p_data[i]==NULL)break;
			b.cf_clean();
			b.cf_import_strarr(p_data[i], as_sepTD, 0);
			if(b.cf_howmany()>=2){
				cf_prpt_let(b.cf_read(0), b.cf_read(1));
			}
		}
		cf_prpt_sort();
		return 1;
	}


	int cf_impfast_prpt(char *as_data, char *as_sepTD, char *as_sepTR)
	{
		class wl_stru_list a, b;
		wlint32 i;

		a.cf_import_strarr(as_data, as_sepTR, 0);

		for(i=0;i<a.cf_howmany();i++){
			b.cf_clean();
			b.cf_import_strarr(a.cf_read(i), as_sepTD, 0);
			if(b.cf_howmany()>=2){
				cf_prpt_new(b.cf_read(0), b.cf_read(1));
			}
		}
		cf_setuniq();
		return 1;
	}


	int cf_impfast_prpt(char **p_data, char *as_sepTD )
	{
		class wl_stru_list  b;
		wlint32 i;

		for(i=0;;i++){
            if(p_data[i]==NULL)break;
			b.cf_clean();
			b.cf_import_strarr(p_data[i], as_sepTD, 0);
			if(b.cf_howmany()>=2){
				cf_prpt_new(b.cf_read(0), b.cf_read(1));
			}
		}
		cf_setuniq();
		return 1;
	}


	wlint32 cf_prpt_output(wlint8 *pfn)
    {
		FILE *fp;
		wlint32 i;
		fp=fopen(pfn,"w");
        if(fp==NULL) return 0;
        for(i=0;i<cf_howmany();i++) {
            fprintf(fp,"%s=%s\n",cf_read(i), cf_prpt_get(cf_read(i)) );
        }
        fclose(fp);
        return i;
    }


	wlint32 cf_prpt_output(wlint8 *pfn, wlint8 *as_var)
    {
		wl_stru_list ll;
		ll.cf_clean();
		ll.cf_add(cf_prpt_get(as_var));
		return ll.cf_output(pfn, "");
    }


}; 


#endif


#ifndef WL_STRU_PRPT_H
#define WL_STRU_PRPT_H


class wl_stru_prpt  {

private:

	class wl_stru_prpt01	 iv_knl;

public:

    wl_stru_prpt()   {  }


	wl_stru_prpt01 *cf_getknl(void)
	{
		return &iv_knl;
	}


	int cf_clean(void)
	{
		return iv_knl.cf_clean();
	}


	wlint32 cf_hm(void)
	{
		return iv_knl.cf_howmany() ;
	}


	wlint8 *cf_new(wlint8 *s_var, wlint8 *s_val) 
	{
		return iv_knl.cf_prpt_new(s_var, s_val);
	}


	int cf_equal(wlint8 *s_var, wlint8 *val) 
	{
		return !wl_stru_strf::str_cmp( cf_get(s_var), val) ;
	}


	wlint8 *cf_get(const wlint8 *s_var1) 
	{
		wlint8 *s_var=(char*)s_var1;
		return iv_knl.cf_prpt_get(s_var) ;
	}


	wlint8 *cf_get(wlint32 i, int i_want_val=1) 
	{
		return iv_knl.cf_prpt_get(i, i_want_val) ;
	}


	int cf_get(wlint8 *s_objname, void *p, wlint32 len) 
	{
		wlint8 *t;
		t = cf_get(s_objname);
		if(!(*t))  return 0;
		memcpy(p, t+1, len );
		return 1;
	}


	wlint8 *cf_let(const wlint8 *s_var1, const wlint8 *s_newval1) 
	{
		wlint8 *s_var=(char*)s_var1;
		wlint8 *s_newval=(char*)s_newval1;
		return iv_knl.cf_prpt_let( s_var, s_newval) ;
	}


	wlint8 *cf_let(wlint8 *s_var, wlint32  i_newval) 
	{
		return iv_knl.cf_prpt_let( s_var, i_newval);
	}


	int cf_let(wlint8 *s_objname, void *p, wlint32 len) 
	{
		wl_stru_list aa;
		wlint8 *t;
		wlint32 i;
		if(len<=0)  return 0;
		len += 2;
		if(aa.cf_add(len)<0)  return 0;
		t = aa.cf_readtop();
		for(i=0;i<len-1;i++) { 
			t[i]='a';
		}
		t[i]=0;
		t = cf_let( s_objname, t );
		memcpy( t+1, p, len-2);
		return 1;
	}


	int cf_del(wlint8 *s_var) 
    {
		return iv_knl.cf_prpt_del(s_var);
	}


	wlint8 *cf_cat(const wlint8 *s_var1, const wlint8 *s_cat_val1) 
	{
		char *s_var=(char*)s_var1;
		char *s_cat_val=(char*)s_cat_val1;
		return iv_knl.cf_prpt_cat( s_var, s_cat_val);
	}

	wlint8 *cf_cat(wlint8 *s_var, wlint32 i) 
	{
		wlint8 c[33];
		return cf_cat(s_var, wl_stru_strf::str_ltoa(i,c) );
	}


	wlint8 *cf_add(wlint8 *s_var, wlint8 *s_val1,  wlint8 *s_val2) 
	{
		return iv_knl.cf_prpt_add( s_var,  s_val1,  s_val2) ;
	}


	wlint8 *cf_kuo(const wlint8 *s_var,const  wlint8 *s_kuoval1, const  wlint8 *s_kuoval2) 
	{
		return iv_knl.cf_prpt_kuo( (char*)s_var,  (char*)s_kuoval1,  (char*)s_kuoval2);
	}


	wlint8 *cf_repl(const wlint8 *s_var, const wlint8 *s1, const wlint8 *s2, int opt)
	{
		return iv_knl.cf_pstr_replace( (char*)s_var,  (char*)s1,  (char*)s2,  opt);
	}


	void cf_sort( void )
    {
        iv_knl.cf_prpt_sort();
    }


	int cf_impt(char *as_data, char *as_sepTD, char *as_sepTR)
	{
		return iv_knl.cf_import_prpt(as_data, as_sepTD, as_sepTR);
	}


	int cf_impt(char **p_data, char *as_sepTD )
	{
		return iv_knl.cf_import_prpt(p_data, as_sepTD);
	}


	int cf_impt(wl_stru_list *pl, char *as_sepTD ) 
	{
		wlint8 *t1, *t2;
		wlint32 i,j;

		for(i=0;i<pl->cf_howmany();i++){
            t1 = pl->cf_read(i);
			if(t1==NULL) continue;
			j = wl_stru_strf::str_instr(t1, as_sepTD);
			if(j<=0) continue; 
			t1[j] = 0;
			t2 = t1 + j + 1;
			cf_new(t1, t2);
		}
		iv_knl.cf_setuniq();
		return 1;
	}


	int cf_impt(wl_stru_sheet *ps)
	{
		static char p[]="";
		wlint8 *t1, *t2;
		wlint32 i;

		for(i=0;i<ps->cf_rowcount();i++){
            t1 = ps->cf_getele(i, 0);
			t2 = ps->cf_getele(i, 1);
			if(t1==NULL) t1=p;
			if(t2==NULL) t2=p;
			cf_new(t1, t2);
		}
		iv_knl.cf_setuniq();
		return 1;
	}


	int cf_imptf(char *as_data, char *as_sepTD, char *as_sepTR)
	{
		return iv_knl.cf_impfast_prpt(as_data, as_sepTD, as_sepTR);
	}


	int cf_imptf(char **p_data, char *as_sepTD )
	{
		return iv_knl.cf_impfast_prpt(p_data, as_sepTD);
	}


	wlint32 cf_output(wlint8 *pfn)
    {
		return iv_knl.cf_prpt_output(pfn);
    }


	wlint32 cf_output(wlint8 *pfn, wlint8 *as_var)
    {
		return iv_knl.cf_prpt_output(pfn, as_var);
    }


}; 


#endif


#ifndef WL_STRU_VBARY_FILE_H
#define WL_STRU_VBARY_FILE_H


class wl_stru_vbary_file{

          
public:
   struct wl_vbary_file_a4352357i647{
   	   int opening; 
       int vbaryOK;
       int vbaryERROR;
       int state;  
       class wl_stru_list  filename ;
       FILE *fp;
       wlint32 filelength;    
       wluint8 *buf ;
       wlint32 buf_size;
       wlint32 buf_ptr1,buf_ptr2;
       wlint32 read_disk_count;   
       wlint32 read_count;        
   }  varray ;

private:
	class wl_stru_list  iv_aa;

public:

   wl_stru_vbary_file(void)
       {
   	      varray.opening=0;
   	      varray.vbaryOK= 1;
          varray.vbaryERROR= 0;
          varray.buf_ptr1=0;
          varray.buf_ptr2=0;
          varray.read_disk_count=0;
          varray.read_count=0;

		  varray.buf_size=1333;
		  iv_aa.cf_add(varray.buf_size);
		  varray.buf = (wluint8 *)iv_aa.cf_read(0);
   	   }

   ~wl_stru_vbary_file(void)
        {
        	if(varray.opening) cf_close();
   	    }


   double cf_getreadv(void) 
       {
          double d;
          if(varray.read_disk_count==0) d=0;
          else if(varray.read_count==0) d=0;
          else d=(double)varray.read_disk_count/(double)(varray.read_count);
          return d;
       }


   wlint32 cf_len(void) { return varray.opening==0?0L:varray.filelength; }


   int cf_open(char *f)
       {
          if(varray.opening) cf_close();

          varray.buf_ptr1=0;
          varray.buf_ptr2=0;     
          varray.read_disk_count=0;
          varray.read_count=0;

          
		  varray.filename.cf_clean() ;
		  varray.filename.cf_add(f);

          varray.fp=fopen((char *)varray.filename.cf_read(0), "rb");
          if(varray.fp==NULL) {
             varray.state=varray.vbaryERROR;
             return varray.vbaryERROR ;
          }
          fseek(varray.fp,0,SEEK_END);
          varray.filelength=ftell(varray.fp);
          fclose(varray.fp);
          varray.fp=fopen((char *)varray.filename.cf_read(0), "rb");
          varray.opening=1;
          cf_read(1);     
		  
		  if(varray.filelength<=1) fread(varray.buf,1,1,varray.fp);
          varray.state=varray.vbaryOK;
          return varray.vbaryOK;
       }


   int cf_close(void)
       {
	      if(varray.opening) {
			  varray.opening=0;
			  fclose(varray.fp);
		  }
		  varray.state=varray.vbaryOK;
		  return varray.vbaryOK;
       }

   wluint8 cf_read(wlint32 Q)
       {
          wluint8 c;
          if(!varray.opening){
              varray.state=varray.vbaryERROR;
              return 0;
          }
          varray.state=varray.vbaryOK;
          varray.read_count++;
          if(Q>=varray.buf_ptr1&&Q<=varray.buf_ptr2) {
             return varray.buf[Q - varray.buf_ptr1];
          }
          if(Q<0||Q>=varray.filelength) {
             varray.state=varray.vbaryERROR;
             return 0;
          }
          fseek(varray.fp,Q,SEEK_SET);

          fread(varray.buf,varray.buf_size,1,varray.fp);
          varray.read_disk_count++;
          varray.buf_ptr1=Q;
          varray.buf_ptr2=Q+varray.buf_size - 1;
          if(varray.buf_ptr2>=varray.filelength) varray.buf_ptr2 = varray.filelength - 1;
          c=varray.buf[0];
          return c;
       }


};

#endif


#ifndef WL_STRU_VBARY_RDR_H
#define WL_STRU_VBARY_RDR_H



class wl_stru_vbary_rdr {


private:
	class wl_stru_vbary_file  iv_v_file;

	class wl_stru_list   iv_v_string;
	wlint32             iv_mem_len;

	wlint8 iv_type;

	class wl_stru_list  iv_aa2;

	int  iv_state;

public:

	wl_stru_vbary_rdr(void)
	{
	   iv_type='n'; 
	   iv_state=0;
	}

	virtual ~wl_stru_vbary_rdr(void) { ;  }


	double cf_getreadv(void) 
	{
	   switch( iv_type )
	   {
	   case 'f' :
		   return iv_v_file.cf_getreadv();
	   case 's' :
		   return 1;
	   default :
		   break;
	   }

	   return iv_state = 1 ;
	}


	wlint32 cf_len(void)
	{
	   switch( iv_type )
	   {
	   case 'f' :
		   return iv_v_file.cf_len();
	   case 's' :
		   return  iv_mem_len ;
	   default :
		   break;
	   }

	   return 0;
	}


	int cf_openf(char *f)
	{
	   cf_close();
	   int i;
	   i = iv_v_file.cf_open(f);
	   iv_state = iv_v_file.varray.state;
	   iv_type = 'f';
	   return i;
	}


	int cf_opens(char *s)
	{
	   cf_close();
	   iv_v_string.cf_clean();
	   iv_state = iv_v_string.cf_add(s)<0? 0:1;
	   iv_mem_len = wl_stru_strf::str_len(s);
	   iv_type = 's';
	   return iv_state;
	}


	int cf_opens(char *mem, wlint32 mem_len)
	{
	   cf_close();
	   iv_v_string.cf_clean();
	   iv_state = iv_v_string.cf_add(mem, mem_len)<0? 0:1;
	   iv_mem_len = mem_len;
	   iv_type = 's';
	   return iv_state;
	}


	int cf_opencol(wl_stru_list *a_list)
	{
		wl_stru_list aa;
		wlint8 *t;
		wlint32 i;
		int rc ;

		rc=0;
		do {
			if(!a_list) break;

			a_list->cf_copy_str(&aa);
			aa.cf_collect();
			t = aa.cf_readtop();
			i = wl_stru_strf::bstr_de_size(t);
			wl_stru_strf::bstr_de(t);
			rc = cf_opens(t,i);

		}while(0);
		return rc ;
	}


	int cf_close(void)
	{
	   switch( iv_type )
	   {
	   case 'f' :
		   return iv_v_file.cf_close();
	   case 's' :
		   return iv_v_string.cf_clean();

	   default :
		   break;
	   }

	   return 0;
	}


	int cf_eof(void)
	{
	   return !iv_state;
	}


	wluint8 cf_read(wlint32 Q)
	{
	   wluint8 u;
	   switch( iv_type )
	   {
	   case 'f' :
		   u = iv_v_file.cf_read(Q);
		   iv_state = iv_v_file.varray.state;
		   return u;
	   case 's' :
		   iv_state = Q<iv_mem_len?1:0;
		   if(iv_state) u = (wluint8)(*(iv_v_string.cf_read(0) + Q)); else u=0;
		   return u;
	   default :
		   break;
	   }

	   return 0;
	}


	wlint8 *cf_read(wl_stru_list *destbuf=NULL)
	{
	   return cf_read(0, cf_len() - 1 , destbuf);
	}


	wlint8 *cf_read(wlint32 Q1, wlint32 Q2, wl_stru_list *destbuf=NULL)
	{
	   wlint8 *tp;

	   if(!destbuf) destbuf= &iv_aa2;
	   destbuf->cf_clean() ;
	   destbuf->cf_add(Q2 - Q1 + 1 + 1); 
	   tp = destbuf->cf_read(0);
	   return cf_read(Q1,Q2,tp);
	}


	wlint8 *cf_read(wlint32 Q1, wlint32 Q2, wlint8 *buf)
	{
	
	   wluint8 *tp;
	   wlint32 i ;

	   tp = (wluint8 *)buf;
	   for(i=Q1;i<=Q2;i++){
		   tp[i - Q1]=cf_read(i);
	   }
	   tp[i-Q1] = 0;
	   return (wlint8 *)tp;
	}


	wlint32 cf_in(wlint8 *s_seek, wlint32 i_from=0)
	{
		wlint8 *t;
		wlint32 i,j ;
		class wl_stru_prpt aa;

		j=wl_stru_strf::str_len(s_seek);
		aa.cf_let("s", s_seek);
		t = aa.cf_get("s");

		for(i=i_from;i<=cf_len()-j;i++){
			if(cf_read(i)!=*(wluint8 *)s_seek) continue;
			cf_read(i, i+j-1, t);
			if(!strcmp(t, s_seek)) return i;
		}
		return -1;
	}


	int cf_write(wlint8 *a_pfn) 
	{
	    FILE *fp;
		wl_stru_list aa(2);
		wlint8 *t;
		int rc ;

		rc=0;
		do {
			if(cf_len()==0) break;

			fp = fopen(a_pfn,"wb");
			if(fp==NULL) break;

			t = cf_read(&aa);
			rc = fwrite(t, cf_len(), 1, fp)?1:0 ;
			fclose(fp);
			

        }while(0);

		return rc?1:0 ;
	}


	wlint32 cf_mkcol(wlint32 a_width, wl_stru_list *a_list, wluint8 a_probability=0) 
	{
		wl_stru_list aa(3);
		wlint8 *t1, *t2, *t3;
		wlint32 i,j,k;

		i=0;
		do{
			if(!a_list) break;

			if(a_width<=0) break;

			if(cf_len()==0) break;

			
			aa.cf_add( (a_width+1) + wl_stru_strf::bstr_en_size( t1=cf_read(&aa), cf_len(), a_probability) );
			t2 = aa.cf_readtop();
			wl_stru_strf::bstr_en(t1, cf_len(), t2, a_probability);

			aa.cf_add(a_width+1); 
			t3 = aa.cf_readtop();
			t3[a_width]=0;

			k = wl_stru_strf::str_len(t2);
			for(j=0;j<k;j+=a_width) {
			   memcpy(t3, t2+j, a_width);
			   a_list->cf_add(t3);
			   i++;
			}
		}while(0);

	   return i;
	}


};

#endif


#ifndef WL_STRU_GMR01_H
#define WL_STRU_GMR01_H


struct wl_s_stru_gmr01_reg { 
	wlint32 rc;
	wlint32 pcx;
	wlint32 pcy;
	wlint32 qa;
	wlint32 q;
	wlint32 lmt;
	wlint32 lmtqa;
	wlint32 bsy;
	wlint32 ci;
	wlint32 cx;
	wlint32 ecd;

	wlint8  * exdata;
	wlpfucb pf;
} ;


struct wl_s_stru_gmr01_trace { 
	wlint32 rc;
	wlint32 id; 
	wlint32 pcy;
	wlint32 qa;
	wlint32 q;
	wlint32 lmt;
	wlint32 lmtqa;
	wlint32 aob;
	wlint32 ci;
	wlint32 cx;
	wlint32 ecd;

	wlint32 aoff;
	wlint32 boff;
} ;


class wl_stru_gmr01 {

private:

	wl_stru_i32que		iv_intstk; 
	wl_stru_i32que		iv_intstk2; 
	wl_stru_i32que		iv_intstk3; 

	struct wl_s_stru_gmr01_reg	iv_reg;

	wl_stru_list	stm_buf; 


	wlint32 iv_vna_iii;		

	wlint32 iv_idt02_iii;	
	wlint8 iv_gen_idt02_buf[33]; 


private:


	int cf_equ(const char *k1, const char *k2){ return !wl_stru_strf::str_cmp((char*)k1,(char*)k2); }


	
	void cf_push(wlint32 i) { iv_intstk.cf_push(i); }
	void cf_pop(wlint32 *p) { iv_intstk.cf_pop (p); }

	
	void cf_push2(wlint32 i) { iv_intstk2.cf_push(i); }
	void cf_pop2(wlint32 *p) { iv_intstk2.cf_pop (p); }

	
	void cf_push3(wlint32 i) { iv_intstk3.cf_push(i); }
	void cf_pop3(wlint32 *p) { iv_intstk3.cf_pop (p); }


	void cf_getstm_init(void)
	{
		wlint32 i,j,k,m;
		k=1;
		j=ivp_rom->cf_rowcount();
		for(i=0;i<j;i++) {
			m=ivp_rom->cf_getrow(i)->cf_maxlen();
			if(k<m)k=m;
		}
		stm_buf.cf_clean();
		k++;
		for(i=0;i<=4;i++){ 
			stm_buf.cf_add(k+sizeof(wlint32));
		}
		
	}


	int cf_getstm(void) 
	{
		
		wlint32 i;
		
		wlint8  *t, *t1, *t2, *tt2;

		
		t = ivp_rom->cf_getele( iv_reg.pcy, iv_reg.pcx ) ;
		if(t==NULL){
			strcpy(stm_buf.cf_read(0), "rtn");
			strcpy(stm_buf.cf_read(1), "");
			strcpy(stm_buf.cf_read(2), "");
			strcpy(stm_buf.cf_read(3), "0");
			return 0;
		}else{
			t1 = strcpy( stm_buf.cf_read(0), t );
		}

		for(t=t2=t1;*t;t++)
			if(*t=='~'){	
				*t=0;
				t++;
				break;
			}
		t2=t;

		

		
		strcpy(stm_buf.cf_read(1), t2);

		if(*t2){
			
			wl_stru_strf::bstr_de(t2, tt2=stm_buf.cf_read(2) );

			
			i=wl_stru_strf::bstr_de_size(t2);
			
			*(wlint32 *)stm_buf.cf_read(3) = i;

			
			*(tt2+i)=0;
		}

		return 1;
	}


	void cf_reg2tr(wl_s_stru_gmr01_trace *p_tr)
	{
		memcpy( p_tr, &iv_reg, sizeof(struct wl_s_stru_gmr01_trace) );

	}


	void a_vnx(void)
	{
		if(iv_reg.ci<0) iv_reg.ci=0;
		
		

		on_vnx();
		if (iv_reg.pf!=NULL)
			(*iv_reg.pf)( (wlint8 *)this, (wlint8 *)cf_getreg() );
	}


	void a_vna(void)
	{
		struct wl_s_stru_gmr01_trace tr;

		--iv_vna_iii;
		if(iv_reg.bsy) return ;

		cf_push3(iv_reg.ci=iv_vna_iii);

		on_vna();
		if (iv_reg.pf!=NULL)
			(*iv_reg.pf)( (wlint8 *)this, (wlint8 *)cf_getreg() );

		
		if(ivp_trace!=NULL&&!iv_reg.bsy){
			cf_reg2tr(&tr);
			tr.id= ivp_trace->cf_howmany();
			tr.aob= 'a';
			tr.qa= tr.q;
			tr.aoff= ivp_trace->cf_howmany();
			ivp_trace->cf_add( (wlint8 *)&tr, sizeof(struct wl_s_stru_gmr01_trace) );
		}
	}


	void a_vnb(void)
	{
		struct wl_s_stru_gmr01_trace tr, *t;
		wlint32 i, j;

		if(iv_reg.bsy) return ;

		cf_pop3( &(iv_reg.ci) );

		on_vnb();
		if (iv_reg.pf!=NULL)
			(*iv_reg.pf)( (wlint8 *)this, (wlint8 *)cf_getreg() );

		if(ivp_trace!=NULL&&!iv_reg.bsy){
			cf_reg2tr(&tr);

			for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
				t = (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(i) );
				if(t->ci==iv_reg.ci){			 
					t->q = tr.q = iv_reg.q - 1;
					t->rc = tr.rc;
					tr.cx = t->cx;
					t->ecd = tr.ecd;
					tr.qa = t->qa;
					tr.aoff= t->aoff;
					tr.boff = t->boff = ivp_trace->cf_howmany();
					break;
				}
			}

			tr.id= ivp_trace->cf_howmany();
			tr.aob= 'b';

			ivp_trace->cf_add( (wlint8 *)&tr, sizeof(struct wl_s_stru_gmr01_trace) );
		}

	}


	void a_tc(void)
	{
		wluint8 c, *cset;
		wlint32 i, len;

		cset = (wluint8 *)stm_buf.cf_read(2);
		
		len = *(wlint32 *)stm_buf.cf_read(3);

		c = ivp_prg->cf_read(iv_reg.q);

		
		if(ivp_prg->cf_eof()) {
			iv_reg.rc=0;
			return;
		}

		if(0!=iv_reg.lmt){
			
			if(iv_reg.q>=iv_reg.lmtqa+iv_reg.lmt){
				iv_reg.rc=0;
				return;
			}
		}

		iv_reg.q++;

		for(i=0;i<len;i++){
			if(cset[i]==c) {
				iv_reg.rc=1;
				return ;
			}
		}

		iv_reg.rc=0;
		return;
	}


	void a_tca(void)
	{
		wluint8 x1,x2, c, *cset;
		wlint32 len;

		cset = (wluint8 *)stm_buf.cf_read(2);
		
		len = *(wlint32 *)stm_buf.cf_read(3);

		x1=x2=0;
		if(len>=1) { x1=cset[0];			 }
		if(len>=2) { x1=cset[0]; x2=cset[1]; }

		c = ivp_prg->cf_read(iv_reg.q);

		
		if(ivp_prg->cf_eof()) {
			iv_reg.rc=0;
			return;
		}

		if(0!=iv_reg.lmt){
			
			if(iv_reg.q>=iv_reg.lmtqa+iv_reg.lmt){
				iv_reg.rc=0;
				return;
			}
		}

		iv_reg.q++;

		if(c>=x1&&c<=x2) { iv_reg.rc=1;	return; }

		iv_reg.rc=0;
		return;
	}


	void a_teof(void)
	{
		iv_reg.rc=0;
		if(iv_reg.q>=ivp_prg->cf_len())
			iv_reg.rc=1;
	}


	void a_teor(void)
	{
		iv_reg.rc=0;
		
		if(0!=iv_reg.lmt&&iv_reg.q>iv_reg.lmtqa+iv_reg.lmt) 	iv_reg.rc=1;
	}


	void a_tbsy(void)
	{
		wlint32 i;
		i = wl_stru_strf::str_atol(stm_buf.cf_read(2));
		iv_reg.rc = (iv_reg.bsy - i)>0;
	}


	void a_ci(void)	{iv_reg.ci = wl_stru_strf::str_atol(stm_buf.cf_read(2));}


	void a_cx(void)
	{
		if(iv_reg.bsy) return ;
		wlint32 i, *preg;
		wl_stru_list  *pl;
		wlint8 *s;

		s = stm_buf.cf_read(2);
		preg = &iv_reg.cx ;
		pl = ivp_cxl;
		i = wl_stru_strf::str_atol(s);
		if(pl==NULL){
			*preg = i;
		}else{
			i = pl->cf_sel(s);
			*preg = (i==-1)?pl->cf_add(s):i;
		}
	}


	void a_ecd(void)
	{
		if(iv_reg.bsy) return ;
		wlint32 i, *preg;
		wl_stru_list  *pl;
		wlint8 *s;

		s = stm_buf.cf_read(2);
		preg = &iv_reg.ecd ;
		pl = ivp_errl;
		i = wl_stru_strf::str_atol(s);
		if(pl==NULL){
			*preg = i;
		}else{
			i = pl->cf_sel(s);
			*preg = (i==-1)?pl->cf_add(s):i;
		}
	}


	void a_let(void)	{iv_reg.rc = wl_stru_strf::str_atol(stm_buf.cf_read(2));	}

	void a_eps(void)	{iv_reg.rc = 1;	}

	void a_not(void)	{iv_reg.rc = !iv_reg.rc;	}


	void a_lmt(void)
	{
		cf_push(iv_reg.lmtqa);
		cf_push(iv_reg.lmt);
		iv_reg.lmtqa = iv_reg.q;
		iv_reg.lmt = wl_stru_strf::str_atol(stm_buf.cf_read(2));
	}


	void a_lmtpop(void)
	{
		cf_pop(&(iv_reg.lmt));
		cf_pop(&(iv_reg.lmtqa));
	}


	void a_jt(void)
	{
		if(iv_reg.rc){
			iv_reg.pcx += wl_stru_strf::str_atol(stm_buf.cf_read(2));
			iv_reg.pcx--;
		}
	}

	void a_jf(void)
	{
		if(!iv_reg.rc) {
			iv_reg.pcx += wl_stru_strf::str_atol(stm_buf.cf_read(2));
			iv_reg.pcx--;
		}
	}

	void a_jmp(void) { iv_reg.pcx += wl_stru_strf::str_atol(stm_buf.cf_read(2));iv_reg.pcx--;}


	void a_bup(void)
	{
		cf_push(iv_reg.lmt);
		cf_push(iv_reg.q);
		cf_push(iv_reg.qa);
		cf_push(iv_reg.cx);
		cf_push(iv_reg.ecd);
		iv_reg.bsy++;
	}


	void a_bdn(void)
	{
		cf_pop(&(iv_reg.ecd));
		cf_pop(&(iv_reg.cx));
		cf_pop(&(iv_reg.qa));
		cf_pop(&(iv_reg.q));
		cf_pop(&(iv_reg.lmt));
		iv_reg.bsy--;
	}


	void a_push(void)
	{
		wlint8 *t;
		t = (wlint8 *)stm_buf.cf_read(2);
		if(0){;}
		else if( cf_equ(t, "rc") )
			cf_push(iv_reg.rc);
		else if( cf_equ(t, "pcx") )
			cf_push(iv_reg.pcx);
		else if( cf_equ(t, "pcy") )
			cf_push(iv_reg.pcy);
		else if( cf_equ(t, "qa") )
			cf_push(iv_reg.qa);
		else if( cf_equ(t, "q") )
			cf_push(iv_reg.q);
		else if( cf_equ(t, "lmt") )
			cf_push(iv_reg.lmt);
		else if( cf_equ(t, "bsy") )
			cf_push(iv_reg.bsy);
		else if( cf_equ(t, "ci") )
			cf_push(iv_reg.ci);
		else if( cf_equ(t, "cx") )
			cf_push(iv_reg.cx);
		else if( cf_equ(t, "ecd") )
			cf_push(iv_reg.ecd);
	}


	void a_pop(void)
	{
		wlint8 *t;
		t = (wlint8 *)stm_buf.cf_read(2);
		if(0){;}
		else if( cf_equ(t, "rc") )
			cf_pop(&(iv_reg.rc));
		else if( cf_equ(t, "pcx") )
			cf_pop(&(iv_reg.pcx));
		else if( cf_equ(t, "pcy") )
			cf_pop(&(iv_reg.pcy));
		else if( cf_equ(t, "qa") )
			cf_pop(&(iv_reg.qa));
		else if( cf_equ(t, "q") )
			cf_pop(&(iv_reg.q));
		else if( cf_equ(t, "lmt") )
			cf_pop(&(iv_reg.lmt));
		else if( cf_equ(t, "bsy") )
			cf_pop(&(iv_reg.bsy));
		else if( cf_equ(t, "ci") )
			cf_pop(&(iv_reg.ci));
		else if( cf_equ(t, "cx") )
			cf_pop(&(iv_reg.cx));
		else if( cf_equ(t, "ecd") )
			cf_pop(&(iv_reg.ecd));
	}


	void a_call(void)
	{
		iv_reg.rc = 100;
		

		cf_push2(iv_reg.pcx);
		cf_push2(iv_reg.pcy);
		cf_push2(iv_reg.ecd);
		iv_reg.pcy = wl_stru_strf::str_atol(stm_buf.cf_read(2));
		iv_reg.pcx=0;
	}


	void a_recf(void)
	{
		if(!iv_reg.bsy&&ivp_err!=NULL&&!iv_reg.rc) {
			ivp_err->cf_add( (wlint8 *)cf_getreg(), sizeof(struct wl_s_stru_gmr01_reg) );
		}
	}


	void a_rtn(void)
	{
		cf_pop2(&(iv_reg.ecd));
		cf_pop2(&(iv_reg.pcy));
		cf_pop2(&(iv_reg.pcx));
	}


	void a_rtnf(void)
	{
		if(!iv_reg.rc) a_rtn();
	}

	void a_bsyrtn(void)
	{
		if(iv_reg.bsy) a_rtn();
	}


protected:


	wlint8 *gen_idt02(void)
	{
		wlint8 *s=iv_gen_idt02_buf;
		
		wl_stru_strf::str_ltoa(++iv_idt02_iii, s+1);
		s[0]='W';
		return s;
	}


	virtual void on_vnx(void) {return ;}
	virtual void on_vna(void) {return ;}
	virtual void on_vnb(void) {return ;}


	void cf_reset(void)
	{
		wlpfucb	 lpf;
		wlint8  *lexdata;

		lpf=iv_reg.pf;
		lexdata=iv_reg.exdata;
		memset( (void *)&iv_reg, 0, sizeof(iv_reg) );
		iv_reg.pf=lpf;
		iv_reg.exdata=lexdata;

		iv_intstk.cf_clean( );
		iv_intstk2.cf_clean();
		iv_intstk3.cf_clean();
	}


public:

	wl_stru_sheet		*ivp_rom;
	wl_stru_vbary_rdr	*ivp_prg;
	wl_stru_list		*ivp_trace;
	wl_stru_list		*ivp_err;
	wl_stru_list		*ivp_errl;
	wl_stru_list		*ivp_cxl; 


public:

	wl_stru_gmr01()
	{
		cf_reset( );
		 ivp_rom=NULL;
		 ivp_prg=NULL;
		 ivp_trace=NULL;
		 ivp_err=NULL;
		 ivp_errl =NULL;
		 ivp_cxl =NULL;

		 iv_idt02_iii=0;
		 iv_vna_iii=0;
	}


	virtual ~wl_stru_gmr01()	{	;	}


	wl_s_stru_gmr01_reg *cf_getreg(void) { return &iv_reg ; }


	int cf_rom( wl_stru_sheet *ap_rom)
	{
		ivp_rom =ap_rom;
		return 1;
	}


	int cf_itfc( wl_stru_list *ap_trace,
				 wl_stru_list *ap_err,
				 wl_stru_list	*ap_errl,
				 wl_stru_list	*ap_cxl,
				 wlpfucb pf,
				 wlint8 *exdata		)
	{
		ivp_trace =ap_trace;
		ivp_err = ap_err;
		ivp_errl = ap_errl;
		ivp_cxl = ap_cxl;
		iv_reg.exdata=exdata;
		iv_reg.pf=pf;

		return 1;
	}


	void cf_debug(int flag)
	{
		if(!flag) return ;
		wlint8 *t;
		wlint8 *t1;
		FILE *fp;
		wl_s_stru_gmr01_reg *pr;
		t = stm_buf.cf_read(0);
		t1= stm_buf.cf_read(1);
		pr = (wl_s_stru_gmr01_reg *)&iv_reg;
		fp=fopen("k:\\dbg.txt", "ab");
		fprintf(fp, "%s %s\t"
					"pcy=%ld\t"
					"pcx=%ld\t"
					"rc=%ld\t"
					"bsy=%ld\t"
					"qa=%ld\t"
					"q=%ld\t"
					"lmt=%ld\t"
					"ecd=%ld\r\n",
						t,t1,
						pr->pcy,
						pr->pcx,
						pr->rc,
						pr->bsy,
						pr->qa,
						pr->q,
						pr->lmt,
						pr->ecd  );
		fclose(fp);
	}


	int cf_app(wl_stru_vbary_rdr *ap_prg)
	{
		ivp_prg =ap_prg;

		
		cf_reset( );

		
		if(ivp_trace!=NULL) ivp_trace->cf_clean();
		if(ivp_err !=NULL)	ivp_err->cf_clean();

		
		if(ivp_errl !=NULL){
			ivp_errl->cf_clean();
			ivp_errl->cf_add("");
		}
		if(ivp_cxl !=NULL){
			ivp_cxl->cf_clean();
			ivp_cxl->cf_add("");
		}

		
		cf_getstm_init();

		wlint8 *t;
		while(1){
			cf_getstm();
			iv_reg.pcx++;
			t = stm_buf.cf_read(0);
			if(0){;} 
			else if( cf_equ( t, "recf") )
				a_recf();
			else if( cf_equ( t, "rtnf") )
				a_rtnf();
			else if( cf_equ( t, "rtn") )
				a_rtn();
			else if( cf_equ( t, "rem") )
				continue;
			else if( cf_equ( t, "call") )
				a_call();
			else if( cf_equ( t, "bup") )
				a_bup();
			else if( cf_equ( t, "bdn") )
				a_bdn();
			else if( cf_equ( t, "vnx") )
				a_vnx();
			else if( cf_equ( t, "vna") )
				a_vna();
			else if( cf_equ( t, "vnb") )
				a_vnb();
			else if( cf_equ( t, "tc") )
				a_tc();
			else if( cf_equ( t, "tca") )
				a_tca();
			else if( cf_equ( t, "jt") )
				a_jt();
			else if( cf_equ( t, "jf") )
				a_jf();
			else if( cf_equ( t, "jmp") )
				a_jmp();
			else if( cf_equ( t, "teof") )
				a_teof();
			else if( cf_equ( t, "teor") )
				a_teor();
			else if( cf_equ( t, "tbsy") )
				a_tbsy();
			else if( cf_equ( t, "cx") )
				a_cx();
			else if( cf_equ( t, "ci") )
				a_ci();
			else if( cf_equ( t, "ecd") )
				a_ecd();
			else if( cf_equ( t, "let") )
				a_let();
			else if( cf_equ( t, "eps") )
				a_eps();
			else if( cf_equ( t, "not") )
				a_not();
			else if( cf_equ( t, "lmt") )
				a_lmt();
			else if( cf_equ( t, "lmtpop") )
				a_lmtpop();
			else if( cf_equ( t, "push") )
				a_push();
			else if( cf_equ( t, "pop") )
				a_pop();
			else if( cf_equ( t, "bsyrtn") )
				a_bsyrtn();
			else if( cf_equ( t, "halt")||cf_equ( t, "hlt") )
				break;

			
		}
		return iv_reg.rc;
	}


	wlint32 cf_gerr_pos(int rct )
	{
		struct wl_s_stru_gmr01_reg *t;
		wl_stru_list *pe;
		wlint32  row, col, total, i;
		wluint8 c;

		pe= ivp_err;
		row=col=total=i=0;

		if(pe==NULL||pe->cf_howmany()==0) return -1;
		t = (wl_s_stru_gmr01_reg *)pe->cf_read(0);
		total = t->q>0?t->q-1:0;

		for(i=total;i>=0;i--){
			c = ivp_prg->cf_read(i);
			
			if(col==0&&(c==0x0d||c==0x0a)) col++;
			if(c==0x0a) break;
			col++;
		}

		for(row++,i=total;i>=0;i--){
			c = ivp_prg->cf_read(i);
			if(c==0x0a) row++;
		}

		if(rct=='r'||rct=='R'||rct==1) return row;
		if(rct=='c'||rct=='C'||rct==2) return col;
		if(rct=='t'||rct=='T'||rct==3) return total;
		return total;
	}




	wlint32 br_hm(void)
	{
		if(ivp_trace==NULL) return 0;
		return  ivp_trace->cf_howmany() ;
	}


	wl_s_stru_gmr01_trace *br_tr(wlint32 h )
	{
		if(ivp_trace==NULL||h<0) return NULL;
		return  (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(h)) ;
	}


	long br_q1(wlint32 h)
	{
		struct wl_s_stru_gmr01_trace  *t;
		t = (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(h)) ;
		if(t==NULL) return -1;
		return t->qa;
	}


	long br_q2(wlint32 h)
	{
		struct wl_s_stru_gmr01_trace  *t;
		t = (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(h)) ;
		if(t==NULL) return -1;
		return t->q;
	}


	wlint8 *br_vt(wlint32 q1, wlint32 q2 )
	{
		return ivp_prg->cf_read( q1, q2 );
	}


	wlint8 *br_vt(wlint32 h)
	{
		struct wl_s_stru_gmr01_trace  *t;

		t = (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(h)) ;
		if(t==NULL) return ivp_prg->cf_read(1, 0);

		return ivp_prg->cf_read(t->qa, t->q); 
	}


	wlint32 br_std(wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='b') h = t->aoff;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='a') return h; else return -1 ;
	}


	wlint32 br_len(wlint32 h)
	{
		struct wl_s_stru_gmr01_trace  *t;
		t = br_tr(h);
		return t==NULL?0:t->q - t->qa + 1;
	}


	wlint32 br_ypr( wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		do{
			if(t->aob=='b') h = t->aoff;
			if(h<0) return -1;

			h--;
			if(h<0) return -1;

			t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
			if(t==NULL) return -1;

		} while(t->aob!='a');

		return h ;
	}


	wlint32 br_yne(wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='b') h = t->aoff;
		if(h<0) return -1;

		h++;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		return t->aob=='a'?h:-1;
	}


	wlint32 br_xpr(wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='b') h = t->aoff;
		if(h<0) return -1;

		h--;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='a') return -1;

		h = t->aoff;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		return h ;
	}


	wlint32 br_xne(wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='a') h = t->boff;
		if(h<0) return -1;

		h++;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='a') return h;

		return -1 ;
	}


	wlint32 br_yfst(wlint32 h)
	{
		wlint32 h1;
		h1=-1;
		for(h=br_std(h); -1!=h; h=br_ypr(h)) h1=h;
		return h1;
	}


	wlint32 br_xfst(wlint32 h)
	{
		wlint32 h1;
		h1=-1;
		for(h=br_std(h); -1!=h; h=br_xpr(h)) h1=h;
		return h1;
	}


	wlint32 br_ylast(wlint32 h)
	{
		wlint32 h1;
		h1=-1;
		for(h=br_std(h); -1!=h; h=br_yne(h)) h1=h;
		return h1;
	}


	wlint32 br_xlast(wlint32 h)
	{
		wlint32 h1;
		h1=-1;
		for(h=br_std(h); -1!=h; h=br_xne(h)) h1=h;
		return h1;
	}


	int br_isycat(wlint32 h1, wlint32 h2)
	{
		wlint32 hh1,hh2;

		if(br_std(h1)<0||br_std(h2)<0) return 0;

		hh1 = br_std(h1);
		hh2 = br_std(h2);
		do {
			if( br_std(hh1)==hh2 ) return 1;
			hh1=br_ypr(hh1);
		}while(hh1!=-1);

		hh1 = br_std(h2);
		hh2 = br_std(h1);
		do {
			if( br_std(hh1)==hh2 ) return 1;
			hh1=br_ypr(hh1);
		}while(hh1!=-1);

		return 0;
	}


	int br_isxcat(wlint32 h1, wlint32 h2)
	{
		h1 = br_xfst(h1);
		h2 = br_std(h2);
		if(h1<0||h2<0) return 0;
		do {
			if(h1==h2) return 1;
			h1=br_xne(h1);
		}while(h1!=-1);

		return 0;
	}


	int br_a(wlint32 h) 
	{
		if(br_std(h)<0) return 0;
		return br_tr(h)->aob=='a';
	}



	wlint32 cxl_l(wlint32 h) 
	{
		if(br_std(h)<0) return -1;
		return br_tr(h)->cx;
	}


	wlint8 *cxl_s(wlint32 h) 
	{
		static char p[]="";
		if(br_std(h)<0||ivp_cxl==NULL) return p;
		return  ivp_cxl->cf_read(cxl_l(h));
	}


	wlint32 cxl_h(wlint32 h, wlint32 l, int forward, int wholelayer)
	
	{
		if(wholelayer) h=forward?br_xfst(h):br_xlast(h);
		else h = br_std(h);
		for(; -1!=h; h=forward?br_xne(h):br_xpr(h) ) {
			if(cxl_l(h)==-1) break;
			if(cxl_l(h)== l) return  h ;
		}
		return -1;
	}


	wlint32 cxl_h(wlint32 h, wlint8 *name, int forward, int wholelayer)
	
	{
		if(wholelayer) h=forward?br_xfst(h):br_xlast(h);
		else h = br_std(h);
		for(; -1!=h; h=forward?br_xne(h):br_xpr(h) )
		{
			if(cxl_l(h)==-1) break;
			if( !strcmp(cxl_s(h),name)) return h;
		}
		return -1;
	}


	wlint32 cxl_hm(wlint32 h, wlint32 l) 
	{
		wlint32 i;
		for(i=0,h=br_xfst(h); -1!=h; h=br_xne(h))
		{
			if(cxl_l(h)==-1) break;
			if(cxl_l(h)==l) i++;
		}
		return i;
	}


	wlint32 cxl_hm(wlint32 h, wlint8 *name) 
	{
		wlint32 i;
		for(i=0,h=br_xfst(h); -1!=h; h=br_xne(h)) {
			if(cxl_l(h)==-1) break;
			if( !strcmp(cxl_s(h),name)) i++;
		}
		return i;
	}


	

	wlint32 erl_l(wlint32 h)
	{
		wl_s_stru_gmr01_reg  *pr;

		if(h<0||h>=ivp_err->cf_howmany()) return -1;

		pr = (wl_s_stru_gmr01_reg *)(ivp_err->cf_read(h));
		return pr->ecd;
	}


	wlint8 *erl_s(wlint32 h)
	{
		static char p[]="";
		if(h<0||h>=ivp_err->cf_howmany()||ivp_errl==NULL) return p;
		return  ivp_errl->cf_read(erl_l(h));
	}




	static void output_trace(wlint8 *pfn, wl_stru_list *aap_tr)
	{
		wlint32  y;
		struct wl_s_stru_gmr01_trace *pt;
		FILE * fp;

		fp=fopen(pfn, "w");

		if(aap_tr==NULL)
			fprintf(fp, "(null)");
		else
			for(y=0;y<aap_tr->cf_howmany();y++) {
				pt = (wl_s_stru_gmr01_trace *)aap_tr->cf_read(y);
				fprintf(fp, "%ld\t"
							"rc=%ld\t"
							"id=%ld\t"
							"pcy=%ld\t"
							"qa=%ld\t"
							"q=%ld\t"
							"lmt=%ld\t"
							"aob=%c\t"
							"ci=%ld\t"
							"cx=%ld\t"
							"ecd=%ld\t"
							"aoff=%ld\t"
							"boff=%ld",
								y,
								pt->rc,
								pt->id,
								pt->pcy,
								pt->qa,
								pt->q,
								pt->lmt,
						(wlint8)pt->aob,
								pt->ci,
								pt->cx,
								pt->ecd,
								pt->aoff,
								pt->boff	);

				fprintf(fp,"\n");
			}
		fclose(fp);
		return ;
	}

	friend  void gmr01_output_trace1(wlint8 *pfn, wl_stru_gmr01 *p)
	{
		wl_stru_list *aap_tr;
		wlint32  y;
		struct wl_s_stru_gmr01_trace *pt;
		FILE * fp;

		aap_tr = p->ivp_trace;

		fp=fopen(pfn, "w");

		if(aap_tr==NULL)
			fprintf(fp, "(null)");
		else
			for(y=0;y<aap_tr->cf_howmany();y++) {
				pt = (wl_s_stru_gmr01_trace *)aap_tr->cf_read(y);
				fprintf(fp, "%ld\t"
							"rc=%ld\t"
							"id=%ld\t"
							"pcy=%ld\t"
							"qa=%ld\t"
							"q=%ld\t"
							"lmt=%ld\t"
							"aob=%c\t"
							"ci=%ld\t"
							"ecd=%ld\t"
							"aoff=%ld\t"
							"boff=%ld\t"
							"cx=%ld(%s)",
								y,
								pt->rc,
								pt->id,
								pt->pcy,
								pt->qa,
								pt->q,
								pt->lmt,
						(wlint8)pt->aob,
								pt->ci,
								pt->ecd,
								pt->aoff,
								pt->boff,
								pt->cx, p->cxl_s(y) );

				fprintf(fp,"\n");
			}
		fclose(fp);
		return ;
	}


	static void output_err(wlint8 *pfn, wl_stru_list *ap_er)
	{
		FILE *fp;
		wlint32  y;
		wl_s_stru_gmr01_reg *pr;

		fp=fopen(pfn, "w");

		if(ap_er==NULL)
			fprintf(fp, "(null)");
		else
			for(y=0;y<ap_er->cf_howmany();y++) {
				pr = (wl_s_stru_gmr01_reg *)ap_er->cf_read(y);
				fprintf(fp, "%ld\t"
							"rc=%ld\t"
							"pcx=%ld\t"
							"pcy=%ld\t"
							"qa=%ld\t"
							"q=%ld\t"
							"lmt=%ld\t"
							"ecd=%ld\n",
								y,
								pr->rc,
								pr->pcx,
								pr->pcy,
								pr->qa,
								pr->q,
								pr->lmt,
								pr->ecd  );
			}
		fclose(fp);
		return ;
	}


}; 

#endif


#ifndef WL_STRU_GMR02_H
#define WL_STRU_GMR02_H


class wl_stru_gmr02 : protected wl_stru_gmr01  {

private:

	void knl_prg(wl_stru_vbary_rdr *a_prg)
	{
		char s[]=
            "rem~S	call~41	recf	rtnf	bup	call~11	bdn	jt~-6	eps	rtn	rem~_版本V2.1	\r\n"
            "rem~一个标识符首字符	tc~ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz	rtn																\r\n"
            "rem~一个标识符中字符	tc~0_123456789ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz	rtn																\r\n"
            "rem~一个任意字符	tc~a	teof	not	rtn														\r\n"
            "rem~或号	tc~|	rtn																\r\n"
            "rem~加号	tc~+	rtn																\r\n"
            "rem~等号	tc~=	rtn																\r\n"
            "rem~分号	tc~;	rtn																\r\n"
            "rem~0D0A	tc~b0d	tc~b0a																\r\n"
            "rem																		\r\n"
            "rem~标识符pkg	vna	call~14	vnb	rtn														\r\n"
            "rem~标识符1	call~2	rtn																\r\n"
            "rem~标识符2	call~3	rtnf	bup	call~3	bdn	jt~-5	eps	rtn										\r\n"
            "rem~标识符	call~12	recf	rtnf	bup	call~13	bdn	jt~2	jf~4	call~13	recf	rtn	eps	rtn					\r\n"
            "rem																		\r\n"
            "rem																		\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem~嵌入G01指令语句pkg	vna	call~26	vnb	rtn								\r\n"
            "rem~[号	tc~[	rtn										\r\n"
            "rem~]号	tc~]	rtn										\r\n"
            "rem~嵌入G01指令pkg	vna	call~25	vnb	rtn								\r\n"
            "rem~嵌入G01指令	bup	call~23	bdn	jt~2	jf~2	rtn	call~4	rtnf	jmp~-8			\r\n"
            "rem~嵌入G01指令语句	call~22	recf	rtnf	call~24	recf	rtnf	call~23	recf	rtnf	rtn		\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem~产生式右部	bup	call~33	bdn	jf~4	call~33	rem~recf	rtn	call~34	rem~recf	rtn	rem~或结构,但要加上recf	\r\n"
            "rem~一个运算元素	bup	call~21	bdn	jf~3	call~21	rtn	call~11	rtn				\r\n"
            "rem~或式	cx~2	call~32	recf	rtnf	call~5	recf	rtnf	call~32	recf	rtnf	call~5	recf	rtnf	call~32	recf	rtnf	rtn	\r\n"
            "rem~加式	cx~3	call~32	recf	rtnf	bup	call~35	bdn	jf~5	call~35	recf	rtnf	rtn	eps	rtn							\r\n"
            "rem~加式2	call~6	recf	rtnf	call~32	recf	rtnf	bup	call~6	bdn	jt~-9	eps	rtn									\r\n"
            "rem																					\r\n"
            "rem																					\r\n"
            "rem																					\r\n"
            "rem																					\r\n"
            "rem																					\r\n"
            "rem~一个完整行pkg	cx~1	vna	call~42	vnb	rtn																\r\n"
            "rem~一个完整行	call~11	recf	rtnf	call~7	recf	rtnf	call~31	recf	rtnf	call~8	recf	rtnf	bup	call~9	bdn	jf~4	call~9	recf	rtnf	eps	rtn\r\n"
		;
		a_prg->cf_opens(s);
		return ;
	}


	int g01_cf_wmk(wl_stru_vbary_rdr *ap_prg, wl_stru_sheet *ap_objrom)
	
	{
		wl_stru_prpt aa;
		int fillz;

		fillz=1;
		ap_objrom->cf_clean();
		aa.cf_let("cmdall", ap_prg->cf_read() );
		aa.cf_repl("cmdall", "\t", " ", 1);
		aa.cf_repl("cmdall", "\r", "", 1);
		ap_objrom->cf_import_str( aa.cf_get("cmdall"), " ", "\n");

		if(fillz){
			wlint32 i;
			wl_stru_list *p;
			char s[33];

			ap_objrom->cf_getsheetknl()->cf_rev();
			ap_objrom->cf_import_str("rem~vna call~1 rem~vnb halt", " ", "\n" );
			ap_objrom->cf_getsheetknl()->cf_rev();

			for(i=0;i<ap_objrom->cf_rowcount();i++) {
				p=ap_objrom->cf_getrow(i);
				p->cf_rev();
				sprintf(s, "rem~auto.%ld", i);
				p->cf_add(s);
				p->cf_rev();
			}
		}
		return 1;
	}


	int yy_chk1(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list l1,l2;
		wlint32 i,j,h;

		for(h=0; -1!=h; h=br_xne(h)) {
			l1.cf_add( br_vt(br_yne(h)) );
		}
		l1.cf_qsort();

		for(i=0,j=l1.cf_howmany();i<j-1;i++){ 
			if(!wl_stru_strf::str_cmp(l1.cf_read(i), l1.cf_read(i+1)))
				l2.cf_add(l1.cf_read(i));
		}
		l2.cf_setuniq();

		j=l2.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("产生式左侧的VN有重复");
			for(i=0;i<l2.cf_howmany();i++) ap_ermsg->cf_add(l2.cf_read(i));
			return 0;
		}
		return 1;
	}


	int yy_chk2(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list vnleft, vnright;
		wlint32 i,j,h;
		wl_s_stru_gmr01_trace  *pt;

		
		for(h=0; -1!=h; h=br_xne(h)) {
			vnleft.cf_add( br_vt(br_yne(h)) );
		}
		vnleft.cf_setuniq();

		
		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->pcy==11 && pt->aob=='a' && pt->cx>=2){
				vnright.cf_add( br_vt(i) );
			}
		}
		vnright.cf_setuniq();
		
		vnright.cf_setcha(&vnleft);

		j=vnright.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("存在未说明的VN");
			for(i=0;i<vnright.cf_howmany();i++) ap_ermsg->cf_add(vnright.cf_read(i));
			return 0;
		}

		return 1;
	}


	int yy_ins1ele(wlint32 ai_idx, wl_stru_list *ap_glist, wl_stru_list *ap_vnlist, wl_stru_list *ap_objrow, wl_stru_list *ap_ermsg)
	{
		wlint8 *t, s[33];
		wlint8 *t1, c;
		wlint32 j;

		t = ap_glist->cf_read(ai_idx);
		if(*t=='['){
			
			if(t[strlen(t)-1]==']'){
				t1 = t+1;
				c = t[strlen(t)-1];
				t[strlen(t)-1]='\0';
				ap_objrow->cf_add(t1);
				t[strlen(t)]=c;
				if( !strncmp(t1, "rem",		3)		||
					!strncmp(t1, "bsyrtn",	6)	||
					!strncmp(t1, "vna",		3)	||
					!strncmp(t1, "vnb",		3)	||
					!strncmp(t1, "eps",		3)	||
					!strncmp(t1, "ecd",		3)	||
					!strncmp(t1, "cx",		2)	||
					!strncmp(t1, "ci",		2)  ||
					!strncmp(t1, "push",	4)
				  )
					return 99; 
			}else{
				ap_objrow->cf_add(t);
			}
		}else{
			j=ap_vnlist->cf_sel(t);
			if(j==-1){
				ap_ermsg->cf_add(15+wl_stru_strf::str_len(t));
				sprintf(ap_ermsg->cf_readtop(), "vnlist内部错误!%s不存在.", t);
				return 0;
			}
			sprintf(s, "call~%ld", j);
			ap_objrow->cf_add(s);
		}
		return 1;
	}


	int yy_lnk(wl_stru_sheet *ap_objrom, wl_stru_list *ap_ermsg	)
	{
		wl_stru_list vnlist, glist, *objrow;
		wlint32 i,j,h;
		wl_s_stru_gmr01_trace *pt;
		wl_stru_prpt aa;

		
		vnlist.cf_add(" ");
		for(h=0; -1!=h; h=br_xne(h)) {
			vnlist.cf_add( br_vt(br_yne(h)) );
		}

		
		ap_objrom->cf_clean();
		for(i=0,j=vnlist.cf_howmany();i<j;i++) ap_objrom->cf_addrow();
		objrow = ap_objrom->cf_getrow(0);
		objrow->cf_add("rem~GMR02");
		
		objrow->cf_add("call~1");
		objrow->cf_add("halt");

		wlint8 c1[33];
		
		for(h=0; -1!=h; h=br_xne(h)) {
			
			glist.cf_clean();
			i = br_xne(br_yne(h));
			pt = (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->cx==2) glist.cf_add("|"); else glist.cf_add("+"); 
			i = br_yne(h);
			glist.cf_add( br_vt(i) );								
			for(i=br_xne(i);-1!=i;i=br_xne(i)){						
				glist.cf_add( br_vt(i) );
			}
			

			j=vnlist.cf_sel(glist.cf_read(1));
			if(j==-1){
				ap_ermsg->cf_add("vnlist列表损坏!");
				return 0;
			}
			objrow = ap_objrom->cf_getrow(j);

			
			aa.cf_let("t", "rem~");
			aa.cf_cat("t", glist.cf_read(1));
			aa.cf_cat("t", "(");
			aa.cf_cat("t", wl_stru_strf::str_ltoa(j,c1));
			aa.cf_cat("t", ")");
			objrow->cf_add(aa.cf_get("t"));

			
			if(*glist.cf_read(0)=='|'){
				objrow->cf_add("bup");

				if(!yy_ins1ele(2, &glist, &vnlist, objrow, ap_ermsg)) return 0;

				objrow->cf_add("bdn");
				objrow->cf_add("jf~4");

				if(!yy_ins1ele(3, &glist, &vnlist, objrow, ap_ermsg)) return 0;

				objrow->cf_add("recf");
				objrow->cf_add("rtn");

				if(!yy_ins1ele(4, &glist, &vnlist, objrow, ap_ermsg)) return 0;

				objrow->cf_add("recf");
				objrow->cf_add("rtn");

			}

			if(*glist.cf_read(0)=='+'){

				int subrc;

				for(i=2;i<glist.cf_howmany();i++){

					subrc = yy_ins1ele(i, &glist, &vnlist, objrow, ap_ermsg);

					if(!subrc) return 0;

					if(subrc==99){
						
						
					}else{
						objrow->cf_add("recf");
						if(i!=glist.cf_howmany()-1) objrow->cf_add("rtnf");
					}

				}
				objrow->cf_add("rtn");
			}

		}

		return 1 ;
	}


protected:

	void cf_emsg(wl_stru_list *ap_ermsg, wlint32 col)
	
	
	{
		char s[99];
		wlint32 y;
		wl_s_stru_gmr01_reg  *pr;

		sprintf(s, "第%ld行，第%ld字节，总第%ld字节.", cf_gerr_pos('r'), cf_gerr_pos('c'), cf_gerr_pos('t') );
		ap_ermsg->cf_add(s);
		for(y=0;y<ivp_err->cf_howmany();y++) {
			pr = (wl_s_stru_gmr01_reg *)(ivp_err->cf_read(y));
			ap_ermsg->cf_add(ivp_rom->cf_getele(pr->pcy, col) );
		}
	}


public:


	int cf_wmk( wl_stru_sheet		*ap_vmrom,
				wl_stru_vbary_rdr	*ap_prg,
				wl_stru_list		*ap_tr,
				wl_stru_sheet		*ap_obj,
				wl_stru_list		*ap_er,
				wl_stru_list		*ap_ermsg	)
	{
		int rc;
		wl_stru_vbary_rdr	prg01;

		
		knl_prg(&prg01);
		rc = g01_cf_wmk(&prg01, ap_vmrom );
		if(!rc) return 0;

		
		cf_rom(ap_vmrom);
		cf_itfc(ap_tr, ap_er, NULL, NULL, NULL, NULL);
		rc = cf_app(ap_prg);
		if(!rc) {
			cf_emsg(ap_ermsg, 1);
			return 0;
		}


		
		rc = yy_chk1(ap_ermsg);
		if(!rc) return 0;

		rc= yy_chk2(ap_ermsg);
		if(!rc) return 0;

		rc= yy_lnk(ap_obj, ap_ermsg);
		if(!rc) return 0;

		return 1;
	}


}; 

#endif


#ifndef WL_STRU_GMR03_H
#define WL_STRU_GMR03_H


class wl_stru_gmr03 : protected wl_stru_gmr02  {

private:

    wl_stru_list gname;
    wl_stru_list glist;
    wl_stru_prpt idt_trans;


	void knl_prg(wl_stru_vbary_rdr *ap_prg)
	{
		char s[]=
             "S=prg+[rem~_版本V1.2];		\r\n"
             "prg=G1|prg1|[eps];		\r\n"
             "prg1=G+prg;		\r\n"
             "G1=idt+SYM_equ;		\r\n"
             "G=[cx~99]+[vna]+idt+[vnb]+SYM_equ+EE+[rem~产生式是标识符=表达句；];		\r\n"
             "EE=Etime|Etime|EE1;		\r\n"
             "EE1=Eadd|Eadd|EE2;		\r\n"
             "EE2=Eif|Eif|EE3;		\r\n"
             "EE3=Enot|Enot|EE4;		\r\n"
             "EE4=Eand|Eand|EE5;		\r\n"
             "EE5=Eor|Eor|Efor;		\r\n"
             "Efor=[cx~7]+E7+SYM_fen+SYM_cr+[rem~for表达句];		\r\n"
             "E7=[tc~fF]+[tc~oO]+[tc~rR]+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b;		\r\n"
             "Eor=[cx~6]+E6+SYM_fen+SYM_cr+[rem~or表达句];		\r\n"
             "E6=[tc~oO]+[tc~rR]+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b;		\r\n"
             "Eand=[cx~5]+E5+SYM_fen+SYM_cr+[rem~and表达句];		\r\n"
             "E5=[tc~aA]+[tc~nN]+[tc~dD]+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b;\r\n"
             "Enot=[cx~4]+E4+SYM_fen+SYM_cr+[rem~not表达句];\r\n"
             "E4=[tc~nN]+[tc~oO]+[tc~tT]+SYM_k1a+ele+SYM_K1b;\r\n"
             "Eif=[cx~3]+E3+SYM_fen+SYM_cr+[rem~if表达句];\r\n"
             "E3=[tc~iI]+[tc~fF]+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b;\r\n"
             "Eadd=[cx~2]+E2+SYM_fen+SYM_cr+[rem~全加表达句];\r\n"
             "E2=ele+E21+[rem~全加表达式];\r\n"
             "E21=SYM_add|E22|[eps];\r\n"
             "E22=SYM_add+ele+E21;\r\n"
             "Etime=[cx~1]+E1+SYM_fen+SYM_cr+[rem~乘法表达句];\r\n"
             "E1=ele+SYM_add+ele+E11+[rem~乘法表达式但首元素为加];\r\n"
             "E11=SYM_or|E12|[eps];\r\n"
             "E12=SYM_or+ele+E11;\r\n"
             "ele=[vna]+ele1+[vnb];\r\n"
             "ele1=ebd|ebd|idt;\r\n"
             "idt=CNidt;\r\n"
             "ebd=SYM_k2a+ebd1+SYM_K2b;\r\n"
             "not_right_kuo=SYM_K2b|[let~0]|[eps];\r\n"
             "ebd1=not_right_kuo|ebd2|[eps];\r\n"
             "ebd2=EBDletter+ebd1;\r\n"
             "EBDletter=CNletter|CNletter|ASC7letter;\r\n"
             "ASC7letter=[tca~b10b7F];\r\n"
             "CNidt=CNletter+Ci1;\r\n"
             "Ci1=CNletter|Ci2|[eps];\r\n"
             "Ci2=CNletter+Ci1;\r\n"
             "CNletter=HZ|HZ|ENletter;\r\n"
             "HZ=[tca~b80bFF]+[tca~b40bFF];\r\n"
             "ENidt=ENletter+Ei1;\r\n"
             "Ei1=ENletter|Ei2|[eps];\r\n"
             "Ei2=ENletter+Ei1;\r\n"
             "ENletter=[tc~0_123456789ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz];\r\n"
             "SYM_add=[tc~+];\r\n"
             "SYM_or=[tc~|];\r\n"
             "SYM_equ=[tc~=];\r\n"
             "SYM_cr=SYM_cr2|SYM_cr2|SYM_cr1;\r\n"
             "SYM_cr1=[tc~b0d]+[tc~b0a];\r\n"
             "SYM_cr2=SYM_cr1+SYM_cr1;\r\n"
             "SYM_fen=[tc~;];\r\n"
             "SYM_k1a=[tc~(];\r\n"
             "SYM_K1b=[tc~)];\r\n"
             "SYM_k2a=[tc~b5b];\r\n"
             "SYM_K2b=[tc~b5d];\r\n"
		 ;
		wl_stru_prpt	pp;

		

		pp.cf_let("prg", s);
		pp.cf_repl("prg", " ", "", 1);
		pp.cf_repl("prg", "\t", "", 1);

		ap_prg->cf_close();
		ap_prg->cf_opens(pp.cf_get("prg"));
		return ;
	}


	int yy_chk1(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list l1,l2;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;

		
		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->cx==99 && pt->aob=='a') l1.cf_add( br_vt(i) );
		}
		l1.cf_qsort();

		for(i=0,j=l1.cf_howmany();i<j-1;i++){ 
			if(!wl_stru_strf::str_cmp(l1.cf_read(i), l1.cf_read(i+1)))
				l2.cf_add(l1.cf_read(i));
		}
		l2.cf_setuniq();

		j=l2.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("产生式左侧的VN有重复");
			for(i=0;i<l2.cf_howmany();i++) ap_ermsg->cf_add(l2.cf_read(i));
			return 0;
		}
		return 1;
	}


	int yy_chk2(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list vnleft, vnright;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;
		wlint8 *s;

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->cx==99 && pt->aob=='a') vnleft.cf_add( br_vt(i) );
			if(pt->cx!=99 && pt->aob=='a'){
				s = br_vt(i);
				if(s[0]!='[') vnright.cf_add(s);
			}
		}
		vnleft.cf_setuniq();
		vnright.cf_setuniq();
		vnright.cf_setcha(&vnleft);

		j=vnright.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("存在未说明的VN");
			for(i=0;i<vnright.cf_howmany();i++) ap_ermsg->cf_add(vnright.cf_read(i));
			return 0;
		}

		return 1;
	}


	int yy_g1( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E,A;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
			A.cf_add( gen_idt02() );
		}

		
		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "+");
		g.cf_cat("a", A.cf_read(0));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		for(i=0;i<(j-1);i++){
			if(i==j-1-1){
				g.cf_let("a", A.cf_read(i));
				g.cf_cat("a", "=");
				g.cf_cat("a", A.cf_read(i+1));
				g.cf_cat("a", ";");
			}else{
				g.cf_let("a", A.cf_read(i));
				g.cf_cat("a", "=");
				g.cf_cat("a", E.cf_read(i+1));
				g.cf_cat("a", "|");
				g.cf_cat("a", E.cf_read(i+1));
				g.cf_cat("a", "|");
				g.cf_cat("a", A.cf_read(i+1));
				g.cf_cat("a", ";");
			}
			ap_prg02_l->cf_add(g.cf_get("a"));
		}
		g.cf_let("a", A.cf_read(i));
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(i));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "~1句型!];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g2( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}

		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");

		for(i=0;i<(j-1);i++){
			g.cf_cat("a", E.cf_read(i));
			g.cf_cat("a", "+");
		}
		g.cf_cat("a", E.cf_read(i));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g3( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}

		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");

		for(i=0;i<(j-1);i++){
			g.cf_cat("a", E.cf_read(i));
			g.cf_cat("a", "|");
		}
		g.cf_cat("a", E.cf_read(i));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g4( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}

		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");

		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "|[let~0]|[eps];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g5( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E,A;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}
		A.cf_add( gen_idt02() );

		
		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "|");
		g.cf_cat("a", A.cf_read(0));
		g.cf_cat("a", "|[let~0];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		g.cf_let("a", A.cf_read(0));
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(1));
		g.cf_cat("a", "|[eps]|[let~0];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g6( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E,A;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}
		A.cf_add( gen_idt02() );

		
		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "|[eps]|");
		g.cf_cat("a", A.cf_read(0));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		g.cf_let("a", A.cf_read(0));
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(1));
		g.cf_cat("a", "|[eps]|[let~0];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g7( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E,A;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}
		A.cf_add( gen_idt02() );

		
		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "|");
		g.cf_cat("a", A.cf_read(0));
		g.cf_cat("a", "|[eps];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		g.cf_let("a", A.cf_read(0));
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(1));
		g.cf_cat("a", "+");
		g.cf_cat("a", idt_trans.cf_get(t) );
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_lnk02(wl_stru_list *ap_prg02_l, wl_stru_list *ap_ermsg)
	{
		int gtype;
		wlint32 i,j;
		wl_s_stru_gmr01_trace *ptr;

		idt_trans.cf_clean();
		idt_trans.cf_getknl()->cf_setsortf(ivp_trace->iv_mycmp);
		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) { 
			ptr= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(ptr->aob=='a') idt_trans.cf_let(br_vt(i), gen_idt02() );
		}

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			ptr= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(ptr->cx==99 && ptr->aob=='a'){
				gname.cf_clean();
				glist.cf_clean();
				gname.cf_add( br_vt(i) );
				ptr= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i+2);
				gtype = ptr->cx;
				for(i+=2;;i+=2){
					if(-1==br_std(i)) break;
					ptr= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
					if(ptr->cx==99) break;
					glist.cf_add( br_vt(i) );
				}
				i--;
				
				
				if(gtype==1&&!yy_g1(ap_prg02_l)) return 0;
				if(gtype==2&&!yy_g2(ap_prg02_l)) return 0;
				if(gtype==3&&!yy_g3(ap_prg02_l)) return 0;
				if(gtype==4&&!yy_g4(ap_prg02_l)) return 0;
				if(gtype==5&&!yy_g5(ap_prg02_l)) return 0;
				if(gtype==6&&!yy_g6(ap_prg02_l)) return 0;
				if(gtype==7&&!yy_g7(ap_prg02_l)) return 0;
			}
		}

		return 1;
	}


public:


	int cf_wmk( wl_stru_sheet		*ap_vmrom,
				wl_stru_vbary_rdr	*ap_prg,
				wl_stru_list		*ap_tr,
				wl_stru_sheet		*ap_obj,
				wl_stru_list		*ap_er,
				wl_stru_list		*ap_ermsg	)
				
	{
		int rc;
		wl_stru_vbary_rdr	prg02;

		wl_stru_sheet	vmrom02;
		wl_stru_list	tr02;
		wl_stru_list	prg02_l;

		
		knl_prg(&prg02);
		rc = wl_stru_gmr02::cf_wmk(&vmrom02, &prg02, &tr02, ap_vmrom, ap_er, ap_ermsg);
		if(!rc) {
			ap_ermsg->cf_rev();
			ap_ermsg->cf_add("G02:");
			ap_ermsg->cf_rev();
			return 0;
		}

		
		cf_rom(ap_vmrom);
		cf_itfc(ap_tr, ap_er, NULL, NULL, NULL, NULL);
		rc = cf_app(ap_prg);
		if(!rc) {
			cf_emsg(ap_ermsg, 0);
			return 0;
		}

		
		rc = yy_chk1(ap_ermsg);
		if(!rc) return 0;

		rc= yy_chk2(ap_ermsg);
		if(!rc) return 0;

		rc= yy_lnk02(&prg02_l, ap_ermsg);
		
		if(!rc) return 0;

		prg02_l.cf_collect("\r\n");
		prg02.cf_close();
		prg02.cf_opens( prg02_l.cf_readtop() );

		
		rc = wl_stru_gmr02::cf_wmk(ap_vmrom, &prg02, ap_tr, ap_obj, ap_er, ap_ermsg);
		
		if(!rc) {
			ap_ermsg->cf_rev();
			ap_ermsg->cf_add("G02-N0.2:");
			ap_ermsg->cf_rev();
			return 0;
		}
		

		return 1;
	}


}; 

#endif


#ifndef WL_STRU_GMR04_H
#define WL_STRU_GMR04_H


class wl_stru_gmr04 : public wl_stru_gmr01  {

private:

	wl_stru_list	iv_bl;	
	wl_stru_list	iv_ul1, iv_ul2;		
	wl_stru_list	iv_bal1, iv_bal2, iv_bal3, iv_bal4;	 

	wl_stru_prpt	idt_trans;	


	void knl_prg(wl_stru_vbary_rdr *ap_prg)
	{
		char s[]=             "S =	for(行头)(一行);\r\n"
          "VER =	[rem~_V1.0];\r\n"
          "行头 =	[vna]+ 标识符+ [vnb] + 等号;\r\n"
          "一行 =	[ecd~一个程序行] + [cx~70] + [vna]+ 行头 + 表达式+ 分号 + [vnb];\r\n"
          "词间空 =	for(词间空一个)(词间空一个);\r\n"
          "词间空一个 =	[rem~nop]+空格|TAB符|回车符|注释;\r\n"
          "空格 =	[tc~b20];\r\n"
          "TAB符 =	[tc~b09];\r\n"
          "回车符 =	[rem~nop]+[tc~b0d]|[tc~b0a];\r\n"
          "注释 =	注括A + 注内容 + 注括B;\r\n"
          "注括A =	[ecd~13] + [tc~/]+[tc~*];\r\n"
          "注括B =	[ecd~14] + [tc~*]+[tc~/];\r\n"
          "注内字节 =	[ecd~15] + [tca~b10bFF] +[rem~nop];\r\n"
          "非注括B =	not(注括B);\r\n"
          "注内容 =	for(非注括B)(注内字节);\r\n"
          "加法号=	词间空+ [cx~91] + [vna]+[tc~+] +[vnb] +词间空;\r\n"
          "乘法号=	词间空+ [cx~92] + [vna]+[tc~*] +[vnb] +词间空;\r\n"
          "等号=	词间空+ [tc~=] +词间空;\r\n"
          "分号=	词间空+ [tc~;] +词间空;\r\n"
          "圆括号A=	词间空+ [tc~(] +词间空;\r\n"
          "圆括号B=	词间空+ [tc~)] +词间空;\r\n"
          "方括号A=	[ecd~方括号A] + [tc~b5b] +[rem~nop];\r\n"
          "方括号B=	[tc~b5d];\r\n"
          "标识符 =	标识符首字符 + 标识符其它字符 +[rem~nop];\r\n"
          "标识符首字符 =	一个标识符字符;\r\n"
          "标识符其它字符 =	for(一个标识符字符)(一个标识符字符);\r\n"
          "一个标识符字符=	[rem~nop]+一个全角字符|一个半角标识符字符;\r\n"
          "一个全角字符=	[tca~b80bFF]+[tca~b40bFF] +[rem~nop];\r\n"
          "一个半角标识符字符=	[tc~0_123456789ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz];\r\n"
          "嵌入指令 =	[ecd~嵌入指令] + 方括号A + 嵌入指令内 + 方括号B;\r\n"
          "非方括号B =	not(方括号B);\r\n"
          "嵌入指令内 =	for(非方括号B)(一个字符);\r\n"
          "一个字符 =	[rem~nop]+一个全角字符|[tca~b10b7F];\r\n"
          "库函数 =	[ecd~库函数] + if型库函数|not型库函数|for型库函数|bsy型库函数;\r\n"
          "if型库函数 =	if([tbsy~1])(if型库函数测试)(if型库函数实际);\r\n"
          "not型库函数 =	if([tbsy~1])(not型库函数测试)(not型库函数实际);\r\n"
          "for型库函数 =	if([tbsy~1])(for型库函数测试)(for型库函数实际);\r\n"
          "bsy型库函数 =	if([tbsy~1])(bsy型库函数测试)(bsy型库函数实际);\r\n"
          "if型库函数测试 =	[tc~iI]+[tc~fF]+ 圆括号A;\r\n"
          "not型库函数测试 =	[tc~nN]+[tc~oO]+[tc~tT]+ 圆括号A;\r\n"
          "for型库函数测试 =	[tc~fF]+[tc~oO]+[tc~rR]+ 圆括号A;\r\n"
          "bsy型库函数测试 =	[tc~bB]+[tc~sS]+[tc~yY]+ 圆括号A;\r\n"
          "if型库函数实际 =	[cx~41] + [vna]+ [ecd~if型库函数] + [tc~iI]+[tc~fF]+ 圆括号A+表达式+圆括号B + 圆括号A+表达式+圆括号B + 圆括号A+表达式+圆括号B;\r\n"
          "not型库函数实际 =	[cx~42] + [vna]+ [ecd~not型库函数] + [tc~nN]+[tc~oO]+[tc~tT]+ 圆括号A+表达式+圆括号B;\r\n"
          "for型库函数实际 =	[cx~43] + [vna]+ [ecd~for型库函数] + [tc~fF]+[tc~oO]+[tc~rR]+ 圆括号A+表达式+圆括号B + 圆括号A+表达式+圆括号B;\r\n"
          "bsy型库函数实际 =	[cx~44] + [vna]+ [ecd~bsy型库函数] + [tc~bB]+[tc~sS]+[tc~yY]+ 圆括号A+表达式+圆括号B + 圆括号A+表达式+圆括号B;\r\n"
          "表达式 =	[ecd~表达式] + [cx~11] + [vna]+ E +[vnb];\r\n"
          "E=	A1+A2+[rem~nop];\r\n"
          "A1=	[rem~nop] + E1|E2;\r\n"
          "A2=	[rem~nop] + E3|[eps];\r\n"
          "E1=	if([tbsy~1])(E1a)(E1b);\r\n"
          "E1a=	圆括号A + E +[rem~nop];\r\n"
          "E1b=	圆括号A + 表达式 + 圆括号B;\r\n"
          "E2=	[cx~12] + [vna]+运算元素+[vnb];\r\n"
          "E3=	[cx~13] + [vna]+op+[vnb] +[bsyrtn]+ 表达式 + A2;\r\n"
          "op=	[rem~nop] + 加法号|乘法号;\r\n"
          "运算元素=	[rem~nop] + 库函数A|嵌入指令A|标识符A;\r\n"
          "库函数A=	库函数 + [vnb] + [rem~nop];\r\n"
          "嵌入指令A=	[cx~51] + [vna]+嵌入指令+[vnb] + [rem~nop];\r\n"
          "标识符A=	[cx~61] + [vna]+标识符+[vnb] + [rem~nop];\r\n"
       ;
		wl_stru_prpt	pp;

		

		pp.cf_let("prg", s);
		pp.cf_repl("prg", " ", "", 1);
		pp.cf_repl("prg", "\t", "", 1);

		ap_prg->cf_close();
		ap_prg->cf_opens(pp.cf_get("prg"));
		return ;
	}


	int yy_chk1(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list l1,l2,l3;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->cx==70 && pt->aob=='a' && -1!=br_ypr(i)) l1.cf_add( br_vt(i) );
		}

		l1.cf_setgroup(&l3);
		for(i=0,j=l3.cf_howmany();i<j;i++) {
			if(*(wlint32 *)l3.cf_read(i)>1) l2.cf_add(l1.cf_read(i));
		}

		j=l2.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("产生式左侧的VN有重复");
			for(i=0;i<l2.cf_howmany();i++) ap_ermsg->cf_add(l2.cf_read(i));
			return 0;
		}
		return 1;
	}


	int yy_chk2(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list l1,l2;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= br_tr(i);
			if(pt->cx==70 && pt->aob=='a' && -1!=br_ypr(i)) l1.cf_add( br_vt(i) );
			if(pt->cx==61 && pt->aob=='a'  )				l2.cf_add( br_vt(i) );
		}

		l1.cf_setuniq();
		l2.cf_setuniq();
		l2.cf_setcha(&l1);
		j=l2.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("存在未说明的VN");
			for(i=0;i<l2.cf_howmany();i++) ap_ermsg->cf_add(l2.cf_read(i));
			return 0;
		}

		
		idt_trans.cf_clean();
		idt_trans.cf_getknl()->cf_setsortf(ivp_trace->iv_mycmp);
		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) { 
			pt= br_tr(i);
			if( (pt->cx==61 && pt->aob=='a'  )||
				(pt->cx==70 && pt->aob=='a' && -1!=br_ypr(i) ) )
				idt_trans.cf_let(br_vt(i), gen_idt02() );
			
		}

		return 1;
	}


	wlint8 *lf_trans(wlint8 *s)
	{
		wlint8 *t;
		t = idt_trans.cf_get( s );
		return *t?t:s;
	}


	int yy_E(wlint32 h , wl_stru_list *ap_lcode, wl_stru_list *ap_lname, wl_stru_list *ap_ermsg)
	
	{
		wlint32 i,j;
		int rc;

		
		for(j=0,i=br_yne(h); -1!=i; i=br_xne(i) ) j++; 

		switch (j)
		{
		case 3:
			
			i=br_yne(h);
			rc = yy_deal(i, ap_lcode, ap_lname, ap_ermsg);
			if(!rc) return rc;
			
			i=br_yne(h); i=br_xne(i); i=br_xne(i);
			rc = yy_deal(i, ap_lcode, ap_lname, ap_ermsg);
			if(!rc) return rc;
			
			i=br_yne(h); i=br_xne(i);
			rc = yy_deal(i, ap_lcode, ap_lname, ap_ermsg);
			if(!rc) return rc;
			break;
		case 1:
			i=br_yne(h);
			rc = yy_deal(i, ap_lcode, ap_lname, ap_ermsg);
			if(!rc) return rc;
			break;
		default:
			ap_ermsg->cf_add(99);
			sprintf(ap_ermsg->cf_readtop(), "表达式处理内部出错,x向个数为:%ld,hnd=%ld", j, h);
			return 0;
		}
		return 1;
	}

	int yy_deal(wlint32 h , wl_stru_list *ap_lcode, wl_stru_list *ap_lname, wl_stru_list *ap_ermsg)
	
	{
		wlint32 cx,i;

		switch (cx=br_tr(h)->cx)
		{
		case 11:
			if(!yy_E(h, ap_lcode, ap_lname, ap_ermsg))return 0;
			break;

		case 13:
			i=br_yne(h);
			ap_lcode->cf_add32(br_tr(i)->cx);
			ap_lname->cf_add(br_vt(i));
			break;

		case 12:
			i=br_yne(h);
			cx=br_tr(i)->cx;
			switch ( cx )
			{
			case 51:
			case 61:
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( br_vt(i) );
				break;
			case 41:
				i=br_yne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				i=br_xne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				i=br_xne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( "if" );
				break;
			case 42:
				i=br_yne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( "not" );
				break;
			case 43:
				i=br_yne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				i=br_xne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( "for" );
				break;
			case 44:
				i=br_yne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				i=br_xne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( "bsy" );
				break;
			default:
				ap_ermsg->cf_add(88);
				sprintf(ap_ermsg->cf_readtop(), "对表达式一个运元进行处理中内部出错,cx=%ld,id=%ld", cx, i);
				return 0;
			}
			break;

		default:
			ap_ermsg->cf_add(88);
			sprintf(ap_ermsg->cf_readtop(), "表达式处理内部出错,cx=%ld,id=%ld", cx, br_tr(h)->id);
			return 0;
		}
		return 1;
	}


	int yy_prg1e(wlint32 Eh , wl_stru_list *ap_prgl, wl_stru_list *ap_ermsg)
		        
	{
		wlint32 i,j,h1,h2,h3; 
		int rc;
		wl_stru_list	lcode, lname;
		wl_stru_list	E;		
		wl_stru_list	I0;		

		rc = yy_E(Eh, &lcode, &lname, ap_ermsg);
		if(!rc) return 0;

		if(1==lcode.cf_howmany()){
			ap_prgl->cf_add( lf_trans(lname.cf_readtop()) );
			
			ap_ermsg->cf_add(33+wl_stru_strf::str_len(lname.cf_readtop()));
			sprintf(ap_ermsg->cf_readtop(),
				"必须至少2个运元相加!%s", lname.cf_readtop());
			return 0;
		}

		for(i=0;i<lcode.cf_howmany();i++){
			I0.cf_clean();
			I0.cf_add( gen_idt02() );
			E.cf_clean();
			E.cf_add( I0.cf_readtop() );
			E.cf_add("=");
			switch ( j=*(wlint32 *)lcode.cf_read(i) )
			{
			case 41:
				h1=i-3;
				h2=i-2;
				h3=i-1; 
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h2)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h3)) );
				E.cf_add(";");
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h2));
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h3));
				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 42:
				h1=i-1; 
				h2=i-0;
				h3=i-0;
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|[let~0]|[eps];");
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h1));
				
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 43:
				h1=i-2;
				h2=i-1; 
				h3=i-0;
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( gen_idt02() );
				E.cf_add( "|[eps];\r\n");
				E.cf_add( E.cf_read(4) );
				E.cf_add( "=" );
				E.cf_add( lf_trans(lname.cf_read(h2)) );
				E.cf_add( "+" );
				E.cf_add( I0.cf_readtop() );
				E.cf_add( ";" );
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h2));
				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 44:
				h1=i-2;
				h2=i-1; 
				h3=i-0;
				E.cf_add( "[tbsy~1]" );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h2)) );
				E.cf_add(";");
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_bl.cf_add(I0.cf_readtop());	
				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 91:
				h1=i-2;
				h2=i-1;
				h3=i-0;  

				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h1));
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h2));
				
				iv_bal1.cf_add(I0.cf_readtop());
				iv_bal2.cf_add(lname.cf_read(h1));
				iv_bal3.cf_add(lname.cf_read(h2));

				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 92:
				h1=i-2;
				h2=i-1;
				h3=i-0; 
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h2)) );
				E.cf_add(";");
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h1));
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h2));
				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			}
		}

		i = lcode.cf_howmany();
		j = lname.cf_howmany();
		if(1!=i||1!=j) {
			ap_ermsg->cf_add(88);
			sprintf(ap_ermsg->cf_readtop(),"逆波兰表达式未能被归并成单一运算元素.lcode=%ld,lname=%ld.",i,j);
			return 0;
		}

		ap_prgl->cf_add(lname.cf_readtop());
		return 1;
	}


	int yy_lnk( wl_stru_list *ap_prgl, wl_stru_list *ap_ermsg)
	{
		int rc=0;
		wlint32 h, h1, i,j;
		wl_stru_list E0, prgl;

		for(h=0;-1!=h; h=br_xne(h) ) {
			E0.cf_clean();
			prgl.cf_clean();

			
			h1 = br_yne(h);
			h1 = br_xne(h1);
			rc = yy_prg1e(h1, &prgl, ap_ermsg);
			if(!rc) return 0;

			h1 = br_yne(h);
			E0.cf_add( lf_trans(br_vt(h1)) );
			E0.cf_add( "=");
			E0.cf_add( prgl.cf_readtop() );
			E0.cf_add( ";");
			E0.cf_collect();
			iv_ul1.cf_add(br_vt(h1)); iv_ul2.cf_add( prgl.cf_readtop() );
			prgl.cf_deltop();
			prgl.cf_add( E0.cf_readtop() );

			
			while(prgl.cf_howmany()>0){
				ap_prgl->cf_add(prgl.cf_readtop());
				prgl.cf_deltop();
			}
		}

		do{
			i = iv_bl.cf_howmany();
			for(j=0;j<iv_ul2.cf_howmany();j++)
				if(-1!= iv_bl.cf_sel( iv_ul2.cf_read(j) ) ) iv_bl.cf_add( iv_ul1.cf_read(j) );
			iv_bl.cf_setuniq();
		}while(i!=iv_bl.cf_howmany());

		for(i=0;i<iv_bal1.cf_howmany();i++){
			E0.cf_clean();
			E0.cf_add( iv_bal1.cf_read(i) );
			E0.cf_add( "=" );
			E0.cf_add( lf_trans(iv_bal2.cf_read(i) ) );
			E0.cf_add( "+" );
			if(-1!= iv_bl.cf_sel( iv_bal2.cf_read(i) ) ) { 
				E0.cf_add("[bsyrtn]+");
			}else{
				E0.cf_add("[rem~nop]+");
			}
			E0.cf_add( lf_trans(iv_bal3.cf_read(i) ) );
			E0.cf_add(";");
			E0.cf_collect();
			ap_prgl->cf_add(E0.cf_readtop());
		}

		return rc;
	}


protected:

	void cf_emsg(wl_stru_list *ap_ermsg)
	
	{
		char s[99], *t;
		wlint32 y;
		wl_s_stru_gmr01_reg  *pr;

		sprintf(s, "第%ld行，第%ld字节，总第%ld字节.", cf_gerr_pos('r'), cf_gerr_pos('c'), cf_gerr_pos('t') );
		ap_ermsg->cf_add(s);
		for(y=0;y<ivp_err->cf_howmany();y++) {
			pr = (wl_s_stru_gmr01_reg *)(ivp_err->cf_read(y));
			t = ivp_errl->cf_read(pr->ecd);
			if(t[0]!=0&&wl_stru_strf::str_cmp(ap_ermsg->cf_readtop(), t) ) ap_ermsg->cf_add( t );
		}
	}


public:


	int cf_wmk( wl_stru_sheet		*ap_vmrom,
				wl_stru_vbary_rdr	*ap_prg,
				wl_stru_list		*ap_tr,
				wl_stru_sheet		*ap_obj,
				wl_stru_list		*ap_er,
				wl_stru_list		*ap_ermsg	)
				
	{
		int rc;
		wl_stru_vbary_rdr	prg03;
		wl_stru_vbary_rdr	prg02;
		wl_stru_gmr03	lg03;
		wl_stru_gmr02	lg02;

		
		knl_prg(&prg03);
		rc = lg03.cf_wmk(ap_vmrom, &prg03, ap_tr, ap_obj, ap_er, ap_ermsg);
		if(!rc) {
			ap_ermsg->cf_rev();
			ap_ermsg->cf_add("G03:");
			ap_ermsg->cf_rev();
			return 0;
		}

		
		
		wl_stru_list errl;
		cf_rom(ap_obj);
		cf_itfc(ap_tr, ap_er, &errl, NULL, NULL, NULL);
		
		rc = cf_app(ap_prg);
		
		if(!rc) {
			cf_emsg(ap_ermsg);
			return 0;
		}

		
		rc = yy_chk1(ap_ermsg);
		if(!rc) return 0;

		rc= yy_chk2(ap_ermsg);
		if(!rc) return 0;

		wl_stru_list   prgl;
		rc = yy_lnk( &prgl, ap_ermsg);
		
		if(!rc) return 0;

		prgl.cf_collect("\r\n");
		prg02.cf_opens( prgl.cf_readtop() );
		
		rc = lg02.cf_wmk(ap_vmrom, &prg02, ap_tr, ap_obj, ap_er, ap_ermsg);
		
		if(!rc) {
			ap_ermsg->cf_rev();
			ap_ermsg->cf_add("G02-B:");
			ap_ermsg->cf_rev();
			return 0;
		}

		return 1;
	}


}; 

#endif


#ifndef WL_STRU_GMR05_H
#define WL_STRU_GMR05_H


class wl_stru_gmr05 : public wl_stru_gmr04  {

private:


	wl_stru_list iv_lcode, iv_lname;


	void knl_prg(wl_stru_vbary_rdr *ap_prg)
	{
		wl_stru_prpt pp;
		char s[]=                   "S	=	[ecd~S]+	词间空+[vna]+		  for(行头)(程序行) + [vnb] + 词间空 + 文件尾	;				\r\n"
          "文件尾	=	[ecd~文件尾] + [teof]				;				\r\n"
          "										\r\n"
          "程序行	=	[ecd~程序行]+			自带ecd的行*传统行	;				\r\n"
          "自带ecd的行	=	[ecd~自带ecd的行]+	[cx~9201]+[vna]+标识符+[vnb]+[cx~9202]+[vna]+双等号+[vnb]+表达式+分号			;				\r\n"
          "传统行	=	[ecd~传统行]+	[cx~9101]+[vna]+标识符+[vnb]+[cx~9102]+[vna]+单等号+[vnb]+表达式+分号			;				\r\n"
          "行头	=	[ecd~行头]+			标识符+ 词间空+ [tc~=]	;				\r\n"
          "										\r\n"
          "词间空	=	[ecd~词间空]+			for(词间空一个)(词间空一个)	;				\r\n"
          "词间空一个	=	[ecd~词间空一个]+			[tc~b20b09b0db0a]*([tc~/]+[tc~*]+for(not([tc~*]+[tc~/]))([tca~b10bFF])+[tc~*]+[tc~/])	;				\r\n"
          "										\r\n"
          "标识符	 =	[ecd~标识符]+			一个标识符字符 + for(一个标识符字符)(一个标识符字符) 	;				\r\n"
          "一个标识符字符	 =	[ecd~一个标识符字符]+			([tca~b80bFF]+[tca~b40bFF])*asc符 	;				\r\n"
          "bs符	 =	[ecd~bs符]+			一个标识符字符 * [tca~b10b7F]	;				\r\n"
          "asc符	 =	[ecd~asc符]+			[tc~0_123456789ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz]+[rem~nop]	;				\r\n"
          "asc串	 =	[ecd~asc串]+			asc符+for(asc符)(asc符) 	;				\r\n"
          "num串	 =	[ecd~num串]+	[cx~961]+[vna]+		[tc~0123456789]+for([tc~0123456789])([tc~0123456789])	+[vnb]	;\r\n"
          "运算元素	 =	[ecd~运算元素]+			库函数* ([cx~921]+[vna]+标识符+[vnb])	;	\r\n"
          "							\r\n"
          "双等号	 =	[ecd~双等号]+			词间空+ [tc~=] +[tc~=] +词间空	;	\r\n"
          "单等号	 =	[ecd~单等号]+			词间空+ [tc~=] +词间空	;	\r\n"
          "加法号	 =	[ecd~加法号]+			词间空+ [cx~971]+[vna]+ [tc~+]  +[vnb] +词间空	;	\r\n"
          "乘法号	 =	[ecd~乘法号]+			词间空+ [cx~972]+[vna]+ [tc~*]  +[vnb] +词间空	;	\r\n"
          "左括	 =	[ecd~左括]+			词间空+ [tc~(] +词间空	;	\r\n"
          "右括	 =	[ecd~右括]+			词间空+ [tc~)] +词间空	;	\r\n"
          "左大括	 =	[ecd~左大括]+			词间空+ [tc~{] +词间空	;	\r\n"
          "右大括	 =	[ecd~右大括]+			词间空+ [tc~}] +词间空	;	\r\n"
          "分号	 =	[ecd~分号]+			词间空+ [tc~;] +词间空	;	\r\n"
          "							\r\n"
          "库函数	 =	[ecd~库函数]+			库1*库2*库3*库4*库5*库6*库7*库8*库9*库10*库11*库12a*库12b*库13*库14*库15*库16	;	\r\n"
          "bs串	 =	[ecd~b型字符串]+	左括 + [cx~962]+[vna]+		(bs符+for(not(右括))(bs符)) +[vnb] + 右括	;	\r\n"
          "bs串2	 =	[ecd~b型字符串]+	[tc~b22] + [cx~962]+[vna]+		(bs符+for(not([tc~b22]))(bs符)) +[vnb] + [tc~b22]	;	\r\n"
          "库1	 =	[ecd~库1(ecd)]+	[cx~10]+	[vna]+	bsy([tc~eE]+[tc~cC]+[tc~dD]+左括)([tc~eE]+[tc~cC]+[tc~dD] + bs串) 	+[vnb]	;\r\n"
          "库2	 =	[ecd~库2(vn)]+			(库2a * 库2b)	+[vnb]	;\r\n"
          "库2a	 =	[ecd~库2a]+	[cx~21]+	[vna]+	bsy([tc~vV]+[tc~nN]+左括)([tc~vV]+[tc~nN]+bs串+左括+表达式+右括)	;	\r\n"
          "库2b	 =	[ecd~库2b]+	[cx~22]+	[vna]+	bsy(左大括)(左大括 + 表达式 + 右大括)	;	\r\n"
          "库3	 =	[ecd~库3(lmt)]+	[cx~30]+	[vna]+	bsy( [tc~lL]+[tc~mM]+[tc~tT]+左括 )( 库3b )	+[vnb]	;\r\n"
          "库3b	 =	[ecd~库3b]+			[tc~lL]+[tc~mM]+[tc~tT]+ 左括 + num串 +右括+ 左括 + 表达式 + 右括	;	\r\n"
          "库4	 =	[ecd~库4(vnx)]+	[cx~40]+	[vna]+	bsy([tc~vV]+[tc~nN]+[tc~xX]+左括)([tc~vV]+[tc~nN]+[tc~xX]+ 左括 + num串 + 右括)	+[vnb]	;\r\n"
          "库5	 =	[ecd~库5(whl)]+	[cx~50]+	[vna]+	bsy([tc~wW]+[tc~hH]+[tc~lL]+左括)([tc~wW]+[tc~hH]+[tc~lL]+左括+表达式+右括+左括+表达式+右括)	+[vnb]	;\r\n"
          "库6	 =	[ecd~库6(for)]+	[cx~60]+	[vna]+	bsy([tc~fF]+[tc~oO]+[tc~rR]+左括)([tc~fF]+[tc~oO]+[tc~rR]+左括+num串+右括+左括+表达式+右括)	+[vnb]	;\r\n"
          "库7	 =	[ecd~库7(if)]+	[cx~70]+	[vna]+	bsy([tc~iI]+[tc~fF]+左括)([tc~iI]+[tc~fF]+左括+表达式+右括+左括+表达式+右括+左括+表达式+右括)	+[vnb]	;\r\n"
          "库8	 =	[ecd~库8(bsy)]+	[cx~80]+	[vna]+	bsy([tc~bB]+[tc~sS]+[tc~yY]+左括)([tc~bB]+[tc~sS]+[tc~yY]+左括+表达式+右括+左括+表达式+右括)	+[vnb]	;\r\n"
          "库9	 =	[ecd~库9(not)]+	[cx~90]+	[vna]+	bsy([tc~nN]+[tc~oO]+[tc~tT]+左括)([tc~nN]+[tc~oO]+[tc~tT]+左括+表达式+右括)	+[vnb]	;\r\n"
          "库10	 =	[ecd~库10(tc)]+	[cx~100]+	[vna]+	bsy([tc~tT]+[tc~cC]+左括)([tc~tT]+[tc~cC] + bs串) 	+[vnb]	;\r\n"
          "库11	 =	[ecd~库11(tca)]+	[cx~110]+	[vna]+	bsy([tc~tT]+[tc~cC]+[tc~aA]+左括)([tc~tT]+[tc~cC]+[tc~aA] + bs串) 	+[vnb]	;\r\n"
          "库12a	 =	[ecd~库12(ts)]+	[cx~121]+	[vna]+	bsy([tc~tT]+[tc~sS]+左括)([tc~tT]+[tc~sS] + bs串) 	+[vnb]	;\r\n"
          "库12b	 =	[ecd~库12(字符串ts)]+	[cx~122]+	[vna]+	bs串2	+[vnb]	;\r\n"
          "库13	 =	[ecd~库13(nop)]+	[cx~130]+	[vna]+	bsy([tc~nN]+[tc~oO]+[tc~pP]+左括)([tc~nN]+[tc~oO]+[tc~pP]+左括+右括) 	+[vnb]	;\r\n"
          "库14	 =	[ecd~库14(eps)]+	[cx~140]+	[vna]+	bsy([tc~eE]+[tc~pP]+[tc~sS]+左括)([tc~eE]+[tc~pP]+[tc~sS]+左括+右括) 	+[vnb]	;\r\n"
          "库15	 =	[ecd~库15(eof)]+	[cx~150]+	[vna]+	bsy([tc~eE]+[tc~oO]+[tc~fF]+左括)([tc~eE]+[tc~oO]+[tc~fF]+左括+右括) 	+[vnb]	;\r\n"
          "库16	 =	[ecd~库16(eor)]+	[cx~160]+	[vna]+	bsy([tc~eE]+[tc~oO]+[tc~rR]+左括)([tc~eE]+[tc~oO]+[tc~rR]+左括+右括) 	+[vnb]	;\r\n"
          "							\r\n"
          "表达式	 =	[ecd~表达式]+			E	;	\r\n"
          "E	 =		[cx~990]+	[vna]+	((左括+E+右括)*运算元素)+(E3*[eps])	+[vnb]	;\r\n"
          "E3	 =				bsy(加法号*乘法号)((加法号*乘法号)+E + (E3*[eps]))	;	\r\n"
		   ;

		

		pp.cf_let("prg", s);
		ap_prg->cf_close();
		ap_prg->cf_opens(pp.cf_get("prg"));
		return ;
	}


	wlint8 *lf_obj5(void){
	static wlint8 s[22575];
	char ss[]=
	"remb7EGMR02b09callb7E1b09haltb0Db0Aremb7EwL8b281b29b09callb7E120b09recfb09rtnb0Db0Aremb7EwSGb282b2"
	"9b09b62upb09callb7E9b09b62dnb09jfb7E4b09callb7E3b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwSHb28"
	"3b29b09callb7E5b09recfb09rtnfb09callb7E2b09recfb09rtnb0Db0Aremb7EwMFb284b29b09callb7E121b09recfb09"
	"rtnb0Db0Aremb7EwMGb285b29b09callb7E122b09recfb09rtnb0Db0Aremb7EwSXb286b29b09b62upb09callb7E7b09b62"
	"dnb09jfb7E4b09callb7E7b09recfb09rtnb09callb7E8b09recfb09rtnb0Db0Aremb7EwMJb287b29b09callb7E132b09r"
	"ecfb09rtnb0Db0Aremb7EwMOb288b29b09callb7E142b09recfb09rtnb0Db0Aremb7EwMTb289b29b09callb7E145b09rec"
	"fb09rtnb0Db0Aremb7EwN8b2810b29b09callb7E146b09recfb09rtnb0Db0Aremb7EwUHb2811b29b09b62upb09callb7E1"
	"3b09b62dnb09jfb7E4b09callb7E12b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwUIb2812b29b09callb7E13b"
	"09recfb09rtnfb09callb7E11b09recfb09rtnb0Db0Aremb7EwMZb2813b29b09callb7E152b09recfb09rtnb0Db0Aremb7"
	"EwU1b2814b29b09b62upb09tcb7Eb6220b6209b620db620ab09b62dnb09jfb7E4b09tcb7Eb6220b6209b620db620ab09re"
	"cfb09rtnb09callb7E151b09recfb09rtnb0Db0Aremb7EwUTb2815b29b09b62upb09callb7E17b09b62dnb09jfb7E4b09c"
	"allb7E16b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwUUb2816b29b09tcab7Eb6210b62FFb09recfb09rtnfb0"
	"9callb7E15b09recfb09rtnb0Db0Aremb7EwURb2817b29b09b62upb09callb7E147b09b62dnb09jfb7E4b09letb7E0b09r"
	"ecfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwNHb2818b29b09callb7E154b09recfb09rtnb0Db0Aremb7EwU7b2819b"
	"29b09b62upb09callb7E21b09b62dnb09jfb7E4b09callb7E20b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwU8"
	"b2820b29b09callb7E21b09recfb09rtnfb09callb7E19b09recfb09rtnb0Db0Aremb7EwM7b2821b29b09callb7E156b09"
	"recfb09rtnb0Db0Aremb7EwVHb2822b29b09b62upb09callb7E155b09b62dnb09jfb7E4b09callb7E155b09recfb09rtnb"
	"09callb7E25b09recfb09rtnb0Db0Aremb7EwO0b2823b29b09callb7E157b09recfb09rtnb0Db0Aremb7EwVMb2824b29b0"
	"9b62upb09callb7E21b09b62dnb09jfb7E4b09callb7E21b09recfb09rtnb09tcab7Eb6210b627Fb09recfb09rtnb0Db0A"
	"remb7EwNDb2825b29b09callb7E159b09recfb09rtnb0Db0Aremb7EwM9b2826b29b09callb7E161b09recfb09rtnb0Db0A"
	"remb7EwVXb2827b29b09b62upb09callb7E25b09b62dnb09jfb7E4b09callb7E28b09recfb09rtnb09epsb09recfb09rtn"
	"b0Db0Aremb7EwVYb2828b29b09callb7E25b09recfb09rtnfb09callb7E27b09recfb09rtnb0Db0Aremb7EwP9b2829b29b"
	"09callb7E166b09recfb09rtnb0Db0Aremb7EwV7b2830b29b09b62upb09tcb7E0123456789b09b62dnb09jfb7E4b09call"
	"b7E31b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwV8b2831b29b09tcb7E0123456789b09recfb09rtnfb09cal"
	"lb7E30b09recfb09rtnb0Db0Aremb7EwR1b2832b29b09callb7E170b09recfb09rtnb0Db0Aremb7EwWPb2833b29b09b62u"
	"pb09callb7E43b09b62dnb09jfb7E4b09callb7E43b09recfb09rtnb09callb7E169b09recfb09rtnb0Db0Aremb7EwNIb2"
	"834b29b09callb7E174b09recfb09rtnb0Db0Aremb7EwNLb2835b29b09callb7E177b09recfb09rtnb0Db0Aremb7EwR6b2"
	"836b29b09callb7E183b09recfb09rtnb0Db0Aremb7EwR7b2837b29b09callb7E189b09recfb09rtnb0Db0Aremb7EwRYb2"
	"838b29b09callb7E192b09recfb09rtnb0Db0Aremb7EwR0b2839b29b09callb7E195b09recfb09rtnb0Db0Aremb7EwPGb2"
	"840b29b09callb7E198b09recfb09rtnb0Db0Aremb7EwPIb2841b29b09callb7E201b09recfb09rtnb0Db0Aremb7EwN6b2"
	"842b29b09callb7E204b09recfb09rtnb0Db0Aremb7EwN9b2843b29b09callb7E205b09recfb09rtnb0Db0Aremb7EwZWb2"
	"844b29b09b62upb09callb7E68b09b62dnb09jfb7E4b09callb7E68b09recfb09rtnb09callb7E45b09recfb09rtnb0Db0"
	"Aremb7EwZVb2845b29b09b62upb09callb7E70b09b62dnb09jfb7E4b09callb7E70b09recfb09rtnb09callb7E46b09rec"
	"fb09rtnb0Db0Aremb7EwZUb2846b29b09b62upb09callb7E76b09b62dnb09jfb7E4b09callb7E76b09recfb09rtnb09cal"
	"lb7E47b09recfb09rtnb0Db0Aremb7EwZTb2847b29b09b62upb09callb7E79b09b62dnb09jfb7E4b09callb7E79b09recf"
	"b09rtnb09callb7E48b09recfb09rtnb0Db0Aremb7EwZSb2848b29b09b62upb09callb7E81b09b62dnb09jfb7E4b09call"
	"b7E81b09recfb09rtnb09callb7E49b09recfb09rtnb0Db0Aremb7EwZRb2849b29b09b62upb09callb7E83b09b62dnb09j"
	"fb7E4b09callb7E83b09recfb09rtnb09callb7E50b09recfb09rtnb0Db0Aremb7EwZQb2850b29b09b62upb09callb7E85"
	"b09b62dnb09jfb7E4b09callb7E85b09recfb09rtnb09callb7E51b09recfb09rtnb0Db0Aremb7EwZPb2851b29b09b62up"
	"b09callb7E87b09b62dnb09jfb7E4b09callb7E87b09recfb09rtnb09callb7E52b09recfb09rtnb0Db0Aremb7EwZOb285"
	"2b29b09b62upb09callb7E89b09b62dnb09jfb7E4b09callb7E89b09recfb09rtnb09callb7E53b09recfb09rtnb0Db0Ar"
	"emb7EwZNb2853b29b09b62upb09callb7E91b09b62dnb09jfb7E4b09callb7E91b09recfb09rtnb09callb7E54b09recfb"
	"09rtnb0Db0Aremb7EwZMb2854b29b09b62upb09callb7E93b09b62dnb09jfb7E4b09callb7E93b09recfb09rtnb09callb"
	"7E55b09recfb09rtnb0Db0Aremb7EwZLb2855b29b09b62upb09callb7E95b09b62dnb09jfb7E4b09callb7E95b09recfb0"
	"9rtnb09callb7E56b09recfb09rtnb0Db0Aremb7EwZKb2856b29b09b62upb09callb7E97b09b62dnb09jfb7E4b09callb7"
	"E97b09recfb09rtnb09callb7E57b09recfb09rtnb0Db0Aremb7EwZJb2857b29b09b62upb09callb7E98b09b62dnb09jfb"
	"7E4b09callb7E98b09recfb09rtnb09callb7E58b09recfb09rtnb0Db0Aremb7EwZIb2858b29b09b62upb09callb7E100b"
	"09b62dnb09jfb7E4b09callb7E100b09recfb09rtnb09callb7E59b09recfb09rtnb0Db0Aremb7EwZHb2859b29b09b62up"
	"b09callb7E102b09b62dnb09jfb7E4b09callb7E102b09recfb09rtnb09callb7E104b09recfb09rtnb0Db0Aremb7EwRCb"
	"2860b29b09callb7E212b09recfb09rtnb0Db0Aremb7EwZ6b2861b29b09b62upb09callb7E63b09b62dnb09jfb7E4b09ca"
	"llb7E62b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwZ7b2862b29b09callb7E23b09recfb09rtnfb09callb7E"
	"61b09recfb09rtnb0Db0Aremb7EwZ4b2863b29b09b62upb09callb7E39b09b62dnb09jfb7E4b09letb7E0b09recfb09rtn"
	"b09epsb09recfb09rtnb0Db0Aremb7EwREb2864b29b09callb7E219b09recfb09rtnb0Db0Aremb7Ew0Qb2865b29b09b62u"
	"pb09callb7E67b09b62dnb09jfb7E4b09callb7E66b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7Ew0Rb2866b29b"
	"09callb7E23b09recfb09rtnfb09callb7E65b09recfb09rtnb0Db0Aremb7Ew0Ob2867b29b09b62upb09tcb7Eb6222b09b"
	"62dnb09jfb7E4b09letb7E0b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwO1b2868b29b09callb7E229b09recf"
	"b09rtnb0Db0Aremb7Ew1Jb2869b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E222b09recfb09rtnb09ca"
	"llb7E225b09recfb09rtnb0Db0Aremb7EwO4b2870b29b09callb7E231b09recfb09rtnb0Db0Aremb7Ew1Sb2871b29b09b6"
	"2upb09callb7E72b09b62dnb09jfb7E4b09callb7E72b09recfb09rtnb09callb7E74b09recfb09rtnb0Db0Aremb7EwO7b"
	"2872b29b09callb7E241b09recfb09rtnb0Db0Aremb7Ew2Gb2873b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09c"
	"allb7E233b09recfb09rtnb09callb7E238b09recfb09rtnb0Db0Aremb7EwPEb2874b29b09callb7E246b09recfb09rtnb"
	"0Db0Aremb7Ew2Tb2875b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E40b09recfb09rtnb09callb7E243"
	"b09recfb09rtnb0Db0Aremb7EwPJb2876b29b09callb7E253b09recfb09rtnb0Db0Aremb7Ew28b2877b29b09b62upb09tb"
	"62syb7E1b09b62dnb09jfb7E4b09callb7E249b09recfb09rtnb09callb7E78b09recfb09rtnb0Db0Aremb7EwPMb2878b2"
	"9b09callb7E262b09recfb09rtnb0Db0Aremb7EwPTb2879b29b09callb7E274b09recfb09rtnb0Db0Aremb7Ew4Kb2880b2"
	"9b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E265b09recfb09rtnb09callb7E270b09recfb09rtnb0Db0Ar"
	"emb7EwPYb2881b29b09callb7E289b09recfb09rtnb0Db0Aremb7Ew5Ib2882b29b09b62upb09tb62syb7E1b09b62dnb09j"
	"fb7E4b09callb7E277b09recfb09rtnb09callb7E285b09recfb09rtnb0Db0Aremb7EwP6b2883b29b09callb7E304b09re"
	"cfb09rtnb0Db0Aremb7Ew6Gb2884b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E292b09recfb09rtnb09"
	"callb7E300b09recfb09rtnb0Db0Aremb7EwQFb2885b29b09callb7E320b09recfb09rtnb0Db0Aremb7Ew7Gb2886b29b09"
	"b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E306b09recfb09rtnb09callb7E316b09recfb09rtnb0Db0Aremb7"
	"EwQQb2887b29b09callb7E335b09recfb09rtnb0Db0Aremb7Ew8Eb2888b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E"
	"4b09callb7E323b09recfb09rtnb09callb7E331b09recfb09rtnb0Db0Aremb7EwQYb2889b29b09callb7E347b09recfb0"
	"9rtnb0Db0Aremb7Ew85b2890b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E338b09recfb09rtnb09call"
	"b7E343b09recfb09rtnb0Db0Aremb7EwQ3b2891b29b09callb7E355b09recfb09rtnb0Db0Aremb7Ew9Pb2892b29b09b62u"
	"pb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E349b09recfb09rtnb09callb7E351b09recfb09rtnb0Db0Aremb7EwQ6"
	"b2893b29b09callb7E365b09recfb09rtnb0Db0Aremb7EwCADb2894b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b0"
	"9callb7E358b09recfb09rtnb09callb7E361b09recfb09rtnb0Db0Aremb7EwQ9b2895b29b09callb7E373b09recfb09rt"
	"nb0Db0Aremb7EwCAWb2896b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E367b09recfb09rtnb09callb7"
	"E369b09recfb09rtnb0Db0Aremb7EwRDb2897b29b09callb7E377b09recfb09rtnb0Db0Aremb7EwRFb2898b29b09callb7"
	"E388b09recfb09rtnb0Db0Aremb7EwCCVb2899b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E380b09rec"
	"fb09rtnb09callb7E384b09recfb09rtnb0Db0Aremb7EwRJb28100b29b09callb7E399b09recfb09rtnb0Db0Aremb7EwCD"
	"Lb28101b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E391b09recfb09rtnb09callb7E395b09recfb09r"
	"tnb0Db0Aremb7EwRNb28102b29b09callb7E410b09recfb09rtnb0Db0Aremb7EwCEAb28103b29b09b62upb09tb62syb7E1"
	"b09b62dnb09jfb7E4b09callb7E402b09recfb09rtnb09callb7E406b09recfb09rtnb0Db0Aremb7EwRRb28104b29b09ca"
	"llb7E421b09recfb09rtnb0Db0Aremb7EwCE0b28105b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E413b"
	"09recfb09rtnb09callb7E417b09recfb09rtnb0Db0Aremb7EwRVb28106b29b09callb7E422b09recfb09rtnb0Db0Aremb"
	"7EwR8b28107b29b09callb7E428b09recfb09rtnb0Db0Aremb7EwCFLb28108b29b09b62upb09callb7E110b09b62dnb09j"
	"fb7E4b09callb7E110b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwCFIb28109b29b09b62upb09callb7E424b0"
	"9b62dnb09jfb7E4b09callb7E424b09recfb09rtnb09callb7E32b09recfb09rtnb0Db0Aremb7EwR9b28110b29b09callb"
	"7E111b09recfb09rtnb0Db0Aremb7EwCF3b28111b29b09b62upb09tb62syb7E1b09b62dnb09jfb7E4b09callb7E114b09r"
	"ecfb09rtnb09callb7E430b09recfb09rtnb0Db0Aremb7EwCF0b28112b29b09b62upb09callb7E110b09b62dnb09jfb7E4"
	"b09callb7E110b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwCFWb28113b29b09b62upb09callb7E36b09b62dn"
	"b09jfb7E4b09callb7E36b09recfb09rtnb09callb7E37b09recfb09rtnb0Db0Aremb7EwCFTb28114b29b09b62upb09cal"
	"lb7E36b09b62dnb09jfb7E4b09callb7E36b09recfb09rtnb09callb7E37b09recfb09rtnb0Db0Aremb7EwSLb28115b29b"
	"09callb7E10b09recfb09rtnfb09remb7Enopb09callb7E4b09recfb09rtnb0Db0Aremb7EwSMb28116b29b09vnb62b09re"
	"mb7Enopb09callb7E115b09recfb09rtnb0Db0Aremb7EwSNb28117b29b09callb7E2b09recfb09rtnfb09b62syrtnb09ca"
	"llb7E116b09recfb09rtnb0Db0Aremb7EwSOb28118b29b09vnab09remb7Enopb09callb7E117b09recfb09rtnb0Db0Arem"
	"b7EwSPb28119b29b09callb7E10b09recfb09rtnfb09remb7Enopb09callb7E118b09recfb09rtnb0Db0Aremb7EwSQb281"
	"20b29b09ecdb7ESb09remb7Enopb09callb7E119b09recfb09rtnb0Db0Aremb7EwSTb28121b29b09ecdb7EbCEbC4bBCbFE"
	"bCEbB2b09remb7Enopb09teofb09recfb09rtnb0Db0Aremb7EwSYb28122b29b09ecdb7EbB3bCCbD0bF2bD0bD0b09remb7E"
	"nopb09callb7E6b09recfb09rtnb0Db0Aremb7EwTAb28123b29b09callb7E106b09recfb09rtnfb09b62syrtnb09callb7"
	"E42b09recfb09rtnb0Db0Aremb7EwTCb28124b29b09vnb62b09remb7Enopb09callb7E123b09recfb09rtnb0Db0Aremb7E"
	"wTDb28125b29b09callb7E34b09recfb09rtnfb09remb7Enopb09callb7E124b09recfb09rtnb0Db0Aremb7EwTEb28126b"
	"29b09vnab09remb7Enopb09callb7E125b09recfb09rtnb0Db0Aremb7EwTFb28127b29b09cxb7E9202b09remb7Enopb09c"
	"allb7E126b09recfb09rtnb0Db0Aremb7EwTGb28128b29b09vnb62b09remb7Enopb09callb7E127b09recfb09rtnb0Db0A"
	"remb7EwTHb28129b29b09callb7E18b09recfb09rtnfb09remb7Enopb09callb7E128b09recfb09rtnb0Db0Aremb7EwTIb"
	"28130b29b09vnab09remb7Enopb09callb7E129b09recfb09rtnb0Db0Aremb7EwTJb28131b29b09cxb7E9201b09remb7En"
	"opb09callb7E130b09recfb09rtnb0Db0Aremb7EwTKb28132b29b09ecdb7EbD7bD4bB4bF8ecdbB5bC4bD0bD0b09remb7En"
	"opb09callb7E131b09recfb09rtnb0Db0Aremb7EwTWb28133b29b09callb7E106b09recfb09rtnfb09b62syrtnb09callb"
	"7E42b09recfb09rtnb0Db0Aremb7EwTXb28134b29b09vnb62b09remb7Enopb09callb7E133b09recfb09rtnb0Db0Aremb7"
	"EwTYb28135b29b09callb7E35b09recfb09rtnfb09remb7Enopb09callb7E134b09recfb09rtnb0Db0Aremb7EwTZb28136"
	"b29b09vnab09remb7Enopb09callb7E135b09recfb09rtnb0Db0Aremb7EwT0b28137b29b09cxb7E9102b09remb7Enopb09"
	"callb7E136b09recfb09rtnb0Db0Aremb7EwT1b28138b29b09vnb62b09remb7Enopb09callb7E137b09recfb09rtnb0Db0"
	"Aremb7EwT2b28139b29b09callb7E18b09recfb09rtnfb09remb7Enopb09callb7E138b09recfb09rtnb0Db0Aremb7EwT3"
	"b28140b29b09vnab09remb7Enopb09callb7E139b09recfb09rtnb0Db0Aremb7EwT4b28141b29b09cxb7E9101b09remb7E"
	"nopb09callb7E140b09recfb09rtnb0Db0Aremb7EwT5b28142b29b09ecdb7EbB4bABbCDbB3bD0bD0b09remb7Enopb09cal"
	"lb7E141b09recfb09rtnb0Db0Aremb7EwUAb28143b29b09callb7E10b09recfb09rtnfb09remb7Enopb09tcb7Eb3Db09re"
	"cfb09rtnb0Db0Aremb7EwUCb28144b29b09callb7E18b09recfb09rtnfb09remb7Enopb09callb7E143b09recfb09rtnb0"
	"Db0Aremb7EwUDb28145b29b09ecdb7EbD0bD0bCDbB7b09remb7Enopb09callb7E144b09recfb09rtnb0Db0Aremb7EwUJb2"
	"8146b29b09ecdb7EbB4bCAbBCbE4bBFbD5b09remb7Enopb09callb7E11b09recfb09rtnb0Db0Aremb7EwUQb28147b29b09"
	"tcb7Eb2Ab09recfb09rtnfb09remb7Enopb09tcb7Eb2Fb09recfb09rtnb0Db0Aremb7EwUXb28148b29b09tcb7Eb2Ab09re"
	"cfb09rtnfb09remb7Enopb09tcb7Eb2Fb09recfb09rtnb0Db0Aremb7EwUYb28149b29b09callb7E15b09recfb09rtnfb09"
	"remb7Enopb09callb7E148b09recfb09rtnb0Db0Aremb7EwUZb28150b29b09tcb7Eb2Ab09recfb09rtnfb09remb7Enopb0"
	"9callb7E149b09recfb09rtnb0Db0Aremb7EwU0b28151b29b09tcb7Eb2Fb09recfb09rtnfb09remb7Enopb09callb7E150"
	"b09recfb09rtnb0Db0Aremb7EwU2b28152b29b09ecdb7EbB4bCAbBCbE4bBFbD5bD2bBBbB8bF6b09remb7Enopb09callb7E"
	"14b09recfb09rtnb0Db0Aremb7EwU9b28153b29b09callb7E21b09recfb09rtnfb09remb7Enopb09callb7E19b09recfb0"
	"9rtnb0Db0Aremb7EwVAb28154b29b09ecdb7EbB1bEAbCAbB6bB7bFBb09remb7Enopb09callb7E153b09recfb09rtnb0Db0"
	"Aremb7EwVFb28155b29b09tcab7Eb6280b62FFb09recfb09rtnfb09remb7Enopb09tcab7Eb6240b62FFb09recfb09rtnb0"
	"Db0Aremb7EwVIb28156b29b09ecdb7EbD2bBBbB8bF6bB1bEAbCAbB6bB7bFBbD7bD6bB7bFBb09remb7Enopb09callb7E22b"
	"09recfb09rtnb0Db0Aremb7EwVNb28157b29b09ecdb7Eb62sbB7bFBb09remb7Enopb09callb7E24b09recfb09rtnb0Db0A"
	"remb7EwVRb28158b29b09tcb7E0b5F123456789ABCDEFGHIJKLMNOPQRSTUVWXYZab6262cdefghijklmnopqrstuvwxyzb09"
	"recfb09rtnfb09remb7Enopb09remb7Enopb09rtnb0Db0Aremb7EwVSb28159b29b09ecdb7EascbB7bFBb09remb7Enopb09"
	"callb7E158b09recfb09rtnb0Db0Aremb7EwVZb28160b29b09callb7E25b09recfb09rtnfb09remb7Enopb09callb7E27b"
	"09recfb09rtnb0Db0Aremb7EwV0b28161b29b09ecdb7EascbB4bAEb09remb7Enopb09callb7E160b09recfb09rtnb0Db0A"
	"remb7EwWAb28162b29b09callb7E30b09recfb09rtnfb09remb7Enopb09vnb62b09rtnb0Db0Aremb7EwWCb28163b29b09t"
	"cb7E0123456789b09recfb09rtnfb09remb7Enopb09callb7E162b09recfb09rtnb0Db0Aremb7EwWDb28164b29b09vnab0"
	"9remb7Enopb09callb7E163b09recfb09rtnb0Db0Aremb7EwWEb28165b29b09cxb7E961b09remb7Enopb09callb7E164b0"
	"9recfb09rtnb0Db0Aremb7EwWFb28166b29b09ecdb7EnumbB4bAEb09remb7Enopb09callb7E165b09recfb09rtnb0Db0Ar"
	"emb7EwWMb28167b29b09callb7E18b09recfb09rtnfb09remb7Enopb09vnb62b09rtnb0Db0Aremb7EwWNb28168b29b09vn"
	"ab09remb7Enopb09callb7E167b09recfb09rtnb0Db0Aremb7EwWOb28169b29b09cxb7E921b09remb7Enopb09callb7E16"
	"8b09recfb09rtnb0Db0Aremb7EwWQb28170b29b09ecdb7EbD4bCBbCBbE3bD4bAAbCBbD8b09remb7Enopb09callb7E33b09"
	"recfb09rtnb0Db0Aremb7EwWWb28171b29b09tcb7Eb3Db09recfb09rtnfb09remb7Enopb09callb7E10b09recfb09rtnb0"
	"Db0Aremb7EwWXb28172b29b09tcb7Eb3Db09recfb09rtnfb09remb7Enopb09callb7E171b09recfb09rtnb0Db0Aremb7Ew"
	"WYb28173b29b09callb7E10b09recfb09rtnfb09remb7Enopb09callb7E172b09recfb09rtnb0Db0Aremb7EwWZb28174b2"
	"9b09ecdb7EbCBbABbB5bC8bBAbC5b09remb7Enopb09callb7E173b09recfb09rtnb0Db0Aremb7EwW4b28175b29b09tcb7E"
	"b3Db09recfb09rtnfb09remb7Enopb09callb7E10b09recfb09rtnb0Db0Aremb7EwW5b28176b29b09callb7E10b09recfb"
	"09rtnfb09remb7Enopb09callb7E175b09recfb09rtnb0Db0Aremb7EwW6b28177b29b09ecdb7EbB5bA5bB5bC8bBAbC5b09"
	"remb7Enopb09callb7E176b09recfb09rtnb0Db0Aremb7EwXFb28178b29b09vnb62b09remb7Enopb09callb7E10b09recf"
	"b09rtnb0Db0Aremb7EwXGb28179b29b09tcb7Eb2Bb09recfb09rtnfb09remb7Enopb09callb7E178b09recfb09rtnb0Db0"
	"Aremb7EwXHb28180b29b09vnab09remb7Enopb09callb7E179b09recfb09rtnb0Db0Aremb7EwXIb28181b29b09cxb7E971"
	"b09remb7Enopb09callb7E180b09recfb09rtnb0Db0Aremb7EwXJb28182b29b09callb7E10b09recfb09rtnfb09remb7En"
	"opb09callb7E181b09recfb09rtnb0Db0Aremb7EwXKb28183b29b09ecdb7EbBCbD3bB7bA8bBAbC5b09remb7Enopb09call"
	"b7E182b09recfb09rtnb0Db0Aremb7EwXSb28184b29b09vnb62b09remb7Enopb09callb7E10b09recfb09rtnb0Db0Aremb"
	"7EwXTb28185b29b09tcb7Eb2Ab09recfb09rtnfb09remb7Enopb09callb7E184b09recfb09rtnb0Db0Aremb7EwXUb28186"
	"b29b09vnab09remb7Enopb09callb7E185b09recfb09rtnb0Db0Aremb7EwXVb28187b29b09cxb7E972b09remb7Enopb09c"
	"allb7E186b09recfb09rtnb0Db0Aremb7EwXWb28188b29b09callb7E10b09recfb09rtnfb09remb7Enopb09callb7E187b"
	"09recfb09rtnb0Db0Aremb7EwXXb28189b29b09ecdb7EbB3bCBbB7bA8bBAbC5b09remb7Enopb09callb7E188b09recfb09"
	"rtnb0Db0Aremb7EwX2b28190b29b09tcb7Eb28b09recfb09rtnfb09remb7Enopb09callb7E10b09recfb09rtnb0Db0Arem"
	"b7EwX3b28191b29b09callb7E10b09recfb09rtnfb09remb7Enopb09callb7E190b09recfb09rtnb0Db0Aremb7EwX4b281"
	"92b29b09ecdb7EbD7bF3bC0bA8b09remb7Enopb09callb7E191b09recfb09rtnb0Db0Aremb7EwX9b28193b29b09tcb7Eb2"
	"9b09recfb09rtnfb09remb7Enopb09callb7E10b09recfb09rtnb0Db0Aremb7EwYAb28194b29b09callb7E10b09recfb09"
	"rtnfb09remb7Enopb09callb7E193b09recfb09rtnb0Db0Aremb7EwYCb28195b29b09ecdb7EbD3bD2bC0bA8b09remb7Eno"
	"pb09callb7E194b09recfb09rtnb0Db0Aremb7EwYHb28196b29b09tcb7Eb7Bb09recfb09rtnfb09remb7Enopb09callb7E"
	"10b09recfb09rtnb0Db0Aremb7EwYIb28197b29b09callb7E10b09recfb09rtnfb09remb7Enopb09callb7E196b09recfb"
	"09rtnb0Db0Aremb7EwYJb28198b29b09ecdb7EbD7bF3bB4bF3bC0bA8b09remb7Enopb09callb7E197b09recfb09rtnb0Db"
	"0Aremb7EwYOb28199b29b09tcb7Eb7Db09recfb09rtnfb09remb7Enopb09callb7E10b09recfb09rtnb0Db0Aremb7EwYPb"
	"28200b29b09callb7E10b09recfb09rtnfb09remb7Enopb09callb7E199b09recfb09rtnb0Db0Aremb7EwYQb28201b29b0"
	"9ecdb7EbD3bD2bB4bF3bC0bA8b09remb7Enopb09callb7E200b09recfb09rtnb0Db0Aremb7EwYVb28202b29b09tcb7Eb3B"
	"b09recfb09rtnfb09remb7Enopb09callb7E10b09recfb09rtnb0Db0Aremb7EwYWb28203b29b09callb7E10b09recfb09r"
	"tnfb09remb7Enopb09callb7E202b09recfb09rtnb0Db0Aremb7EwYXb28204b29b09ecdb7EbB7bD6bBAbC5b09remb7Enop"
	"b09callb7E203b09recfb09rtnb0Db0Aremb7EwZXb28205b29b09ecdb7EbBFbE2bBAbAFbCAbFDb09remb7Enopb09callb7"
	"E44b09recfb09rtnb0Db0Aremb7EwZ8b28206b29b09callb7E23b09recfb09rtnfb09remb7Enopb09callb7E61b09recfb"
	"09rtnb0Db0Aremb7Ew0Cb28207b29b09vnb62b09remb7Enopb09callb7E39b09recfb09rtnb0Db0Aremb7Ew0Db28208b29"
	"b09callb7E206b09recfb09rtnfb09remb7Enopb09callb7E207b09recfb09rtnb0Db0Aremb7Ew0Eb28209b29b09vnab09"
	"remb7Enopb09callb7E208b09recfb09rtnb0Db0Aremb7Ew0Fb28210b29b09cxb7E962b09remb7Enopb09callb7E209b09"
	"recfb09rtnb0Db0Aremb7Ew0Gb28211b29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E210b09recfb09rtn"
	"b0Db0Aremb7Ew0Hb28212b29b09ecdb7Eb62bD0bCDbD7bD6bB7bFBbB4bAEb09remb7Enopb09callb7E211b09recfb09rtn"
	"b0Db0Aremb7Ew0Sb28213b29b09callb7E23b09recfb09rtnfb09remb7Enopb09callb7E65b09recfb09rtnb0Db0Aremb7"
	"Ew0Vb28214b29b09vnb62b09remb7Enopb09tcb7Eb6222b09recfb09rtnb0Db0Aremb7Ew0Wb28215b29b09callb7E213b0"
	"9recfb09rtnfb09remb7Enopb09callb7E214b09recfb09rtnb0Db0Aremb7Ew0Xb28216b29b09vnab09remb7Enopb09cal"
	"lb7E215b09recfb09rtnb0Db0Aremb7Ew0Yb28217b29b09cxb7E962b09remb7Enopb09callb7E216b09recfb09rtnb0Db0"
	"Aremb7Ew0Zb28218b29b09tcb7Eb6222b09recfb09rtnfb09remb7Enopb09callb7E217b09recfb09rtnb0Db0Aremb7Ew0"
	"0b28219b29b09ecdb7Eb62bD0bCDbD7bD6bB7bFBbB4bAEb09remb7Enopb09callb7E218b09recfb09rtnb0Db0Aremb7Ew0"
	"8b28220b29b09tcb7EdDb09recfb09rtnfb09remb7Enopb09callb7E38b09recfb09rtnb0Db0Aremb7Ew09b28221b29b09"
	"tcb7EcCb09recfb09rtnfb09remb7Enopb09callb7E220b09recfb09rtnb0Db0Aremb7Ew1Ab28222b29b09tcb7EeEb09re"
	"cfb09rtnfb09remb7Enopb09callb7E221b09recfb09rtnb0Db0Aremb7Ew1Gb28223b29b09tcb7EdDb09recfb09rtnfb09"
	"remb7Enopb09callb7E60b09recfb09rtnb0Db0Aremb7Ew1Hb28224b29b09tcb7EcCb09recfb09rtnfb09remb7Enopb09c"
	"allb7E223b09recfb09rtnb0Db0Aremb7Ew1Ib28225b29b09tcb7EeEb09recfb09rtnfb09remb7Enopb09callb7E224b09"
	"recfb09rtnb0Db0Aremb7Ew1Lb28226b29b09callb7E69b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7Ew"
	"1Mb28227b29b09vnab09remb7Enopb09callb7E226b09recfb09rtnb0Db0Aremb7Ew1Nb28228b29b09cxb7E10b09remb7E"
	"nopb09callb7E227b09recfb09rtnb0Db0Aremb7Ew1Ob28229b29b09ecdb7EbBFbE21b28ecdb29b09remb7Enopb09callb"
	"7E228b09recfb09rtnb0Db0Aremb7Ew1Ub28230b29b09callb7E71b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0"
	"Aremb7Ew1Vb28231b29b09ecdb7EbBFbE22b28vnb29b09remb7Enopb09callb7E230b09recfb09rtnb0Db0Aremb7Ew12b2"
	"8232b29b09tcb7EnNb09recfb09rtnfb09remb7Enopb09callb7E38b09recfb09rtnb0Db0Aremb7Ew13b28233b29b09tcb"
	"7EvVb09recfb09rtnfb09remb7Enopb09callb7E232b09recfb09rtnb0Db0Aremb7Ew2Ab28234b29b09callb7E106b09re"
	"cfb09rtnfb09b62syrtnb09callb7E39b09recfb09rtnb0Db0Aremb7Ew2Cb28235b29b09callb7E38b09recfb09rtnfb09"
	"remb7Enopb09callb7E234b09recfb09rtnb0Db0Aremb7Ew2Db28236b29b09callb7E60b09recfb09rtnfb09remb7Enopb"
	"09callb7E235b09recfb09rtnb0Db0Aremb7Ew2Eb28237b29b09tcb7EnNb09recfb09rtnfb09remb7Enopb09callb7E236"
	"b09recfb09rtnb0Db0Aremb7Ew2Fb28238b29b09tcb7EvVb09recfb09rtnfb09remb7Enopb09callb7E237b09recfb09rt"
	"nb0Db0Aremb7Ew2Hb28239b29b09vnab09remb7Enopb09callb7E73b09recfb09rtnb0Db0Aremb7Ew2Ib28240b29b09cxb"
	"7E21b09remb7Enopb09callb7E239b09recfb09rtnb0Db0Aremb7Ew2Jb28241b29b09ecdb7EbBFbE22ab09remb7Enopb09"
	"callb7E240b09recfb09rtnb0Db0Aremb7Ew2Rb28242b29b09callb7E106b09recfb09rtnfb09b62syrtnb09callb7E41b"
	"09recfb09rtnb0Db0Aremb7Ew2Sb28243b29b09callb7E40b09recfb09rtnfb09remb7Enopb09callb7E242b09recfb09r"
	"tnb0Db0Aremb7Ew2Ub28244b29b09vnab09remb7Enopb09callb7E75b09recfb09rtnb0Db0Aremb7Ew2Vb28245b29b09cx"
	"b7E22b09remb7Enopb09callb7E244b09recfb09rtnb0Db0Aremb7Ew2Wb28246b29b09ecdb7EbBFbE22b62b09remb7Enop"
	"b09callb7E245b09recfb09rtnb0Db0Aremb7Ew24b28247b29b09tcb7EtTb09recfb09rtnfb09remb7Enopb09callb7E38"
	"b09recfb09rtnb0Db0Aremb7Ew25b28248b29b09tcb7EmMb09recfb09rtnfb09remb7Enopb09callb7E247b09recfb09rt"
	"nb0Db0Aremb7Ew26b28249b29b09tcb7ElLb09recfb09rtnfb09remb7Enopb09callb7E248b09recfb09rtnb0Db0Aremb7"
	"Ew3Ab28250b29b09callb7E77b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7Ew3Cb28251b29b09vnab09r"
	"emb7Enopb09callb7E250b09recfb09rtnb0Db0Aremb7Ew3Db28252b29b09cxb7E30b09remb7Enopb09callb7E251b09re"
	"cfb09rtnb0Db0Aremb7Ew3Eb28253b29b09ecdb7EbBFbE23b28lmtb29b09remb7Enopb09callb7E252b09recfb09rtnb0D"
	"b0Aremb7Ew3Pb28254b29b09callb7E106b09recfb09rtnfb09b62syrtnb09callb7E39b09recfb09rtnb0Db0Aremb7Ew3"
	"Qb28255b29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E254b09recfb09rtnb0Db0Aremb7Ew3Rb28256b29"
	"b09callb7E39b09recfb09rtnfb09remb7Enopb09callb7E255b09recfb09rtnb0Db0Aremb7Ew3Sb28257b29b09callb7E"
	"29b09recfb09rtnfb09remb7Enopb09callb7E256b09recfb09rtnb0Db0Aremb7Ew3Tb28258b29b09callb7E38b09recfb"
	"09rtnfb09remb7Enopb09callb7E257b09recfb09rtnb0Db0Aremb7Ew3Ub28259b29b09tcb7EtTb09recfb09rtnfb09rem"
	"b7Enopb09callb7E258b09recfb09rtnb0Db0Aremb7Ew3Vb28260b29b09tcb7EmMb09recfb09rtnfb09remb7Enopb09cal"
	"lb7E259b09recfb09rtnb0Db0Aremb7Ew3Wb28261b29b09tcb7ElLb09recfb09rtnfb09remb7Enopb09callb7E260b09re"
	"cfb09rtnb0Db0Aremb7Ew3Xb28262b29b09ecdb7EbBFbE23b62b09remb7Enopb09callb7E261b09recfb09rtnb0Db0Arem"
	"b7Ew35b28263b29b09tcb7ExXb09recfb09rtnfb09remb7Enopb09callb7E38b09recfb09rtnb0Db0Aremb7Ew36b28264b"
	"29b09tcb7EnNb09recfb09rtnfb09remb7Enopb09callb7E263b09recfb09rtnb0Db0Aremb7Ew37b28265b29b09tcb7EvV"
	"b09recfb09rtnfb09remb7Enopb09callb7E264b09recfb09rtnb0Db0Aremb7Ew4Fb28266b29b09callb7E29b09recfb09"
	"rtnfb09remb7Enopb09callb7E39b09recfb09rtnb0Db0Aremb7Ew4Gb28267b29b09callb7E38b09recfb09rtnfb09remb"
	"7Enopb09callb7E266b09recfb09rtnb0Db0Aremb7Ew4Hb28268b29b09tcb7ExXb09recfb09rtnfb09remb7Enopb09call"
	"b7E267b09recfb09rtnb0Db0Aremb7Ew4Ib28269b29b09tcb7EnNb09recfb09rtnfb09remb7Enopb09callb7E268b09rec"
	"fb09rtnb0Db0Aremb7Ew4Jb28270b29b09tcb7EvVb09recfb09rtnfb09remb7Enopb09callb7E269b09recfb09rtnb0Db0"
	"Aremb7Ew4Mb28271b29b09callb7E80b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7Ew4Nb28272b29b09v"
	"nab09remb7Enopb09callb7E271b09recfb09rtnb0Db0Aremb7Ew4Ob28273b29b09cxb7E40b09remb7Enopb09callb7E27"
	"2b09recfb09rtnb0Db0Aremb7Ew4Pb28274b29b09ecdb7EbBFbE24b28vnxb29b09remb7Enopb09callb7E273b09recfb09"
	"rtnb0Db0Aremb7Ew4Xb28275b29b09tcb7ElLb09recfb09rtnfb09remb7Enopb09callb7E38b09recfb09rtnb0Db0Aremb"
	"7Ew4Yb28276b29b09tcb7EhHb09recfb09rtnfb09remb7Enopb09callb7E275b09recfb09rtnb0Db0Aremb7Ew4Zb28277b"
	"29b09tcb7EwWb09recfb09rtnfb09remb7Enopb09callb7E276b09recfb09rtnb0Db0Aremb7Ew49b28278b29b09callb7E"
	"106b09recfb09rtnfb09b62syrtnb09callb7E39b09recfb09rtnb0Db0Aremb7Ew5Ab28279b29b09callb7E38b09recfb0"
	"9rtnfb09remb7Enopb09callb7E278b09recfb09rtnb0Db0Aremb7Ew5Cb28280b29b09callb7E39b09recfb09rtnfb09re"
	"mb7Enopb09callb7E279b09recfb09rtnb0Db0Aremb7Ew5Db28281b29b09callb7E106b09recfb09rtnfb09b62syrtnb09"
	"callb7E280b09recfb09rtnb0Db0Aremb7Ew5Eb28282b29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E281"
	"b09recfb09rtnb0Db0Aremb7Ew5Fb28283b29b09tcb7ElLb09recfb09rtnfb09remb7Enopb09callb7E282b09recfb09rt"
	"nb0Db0Aremb7Ew5Gb28284b29b09tcb7EhHb09recfb09rtnfb09remb7Enopb09callb7E283b09recfb09rtnb0Db0Aremb7"
	"Ew5Hb28285b29b09tcb7EwWb09recfb09rtnfb09remb7Enopb09callb7E284b09recfb09rtnb0Db0Aremb7Ew5Kb28286b2"
	"9b09callb7E82b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7Ew5Lb28287b29b09vnab09remb7Enopb09c"
	"allb7E286b09recfb09rtnb0Db0Aremb7Ew5Mb28288b29b09cxb7E50b09remb7Enopb09callb7E287b09recfb09rtnb0Db"
	"0Aremb7Ew5Nb28289b29b09ecdb7EbBFbE25b28whlb29b09remb7Enopb09callb7E288b09recfb09rtnb0Db0Aremb7Ew5V"
	"b28290b29b09tcb7ErRb09recfb09rtnfb09remb7Enopb09callb7E38b09recfb09rtnb0Db0Aremb7Ew5Wb28291b29b09t"
	"cb7EoOb09recfb09rtnfb09remb7Enopb09callb7E290b09recfb09rtnb0Db0Aremb7Ew5Xb28292b29b09tcb7EfFb09rec"
	"fb09rtnfb09remb7Enopb09callb7E291b09recfb09rtnb0Db0Aremb7Ew57b28293b29b09callb7E106b09recfb09rtnfb"
	"09b62syrtnb09callb7E39b09recfb09rtnb0Db0Aremb7Ew58b28294b29b09callb7E38b09recfb09rtnfb09remb7Enopb"
	"09callb7E293b09recfb09rtnb0Db0Aremb7Ew59b28295b29b09callb7E39b09recfb09rtnfb09remb7Enopb09callb7E2"
	"94b09recfb09rtnb0Db0Aremb7Ew6Ab28296b29b09callb7E29b09recfb09rtnfb09remb7Enopb09callb7E295b09recfb"
	"09rtnb0Db0Aremb7Ew6Cb28297b29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E296b09recfb09rtnb0Db0"
	"Aremb7Ew6Db28298b29b09tcb7ErRb09recfb09rtnfb09remb7Enopb09callb7E297b09recfb09rtnb0Db0Aremb7Ew6Eb2"
	"8299b29b09tcb7EoOb09recfb09rtnfb09remb7Enopb09callb7E298b09recfb09rtnb0Db0Aremb7Ew6Fb28300b29b09tc"
	"b7EfFb09recfb09rtnfb09remb7Enopb09callb7E299b09recfb09rtnb0Db0Aremb7Ew6Ib28301b29b09callb7E84b09re"
	"cfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7Ew6Jb28302b29b09vnab09remb7Enopb09callb7E301b09recfb0"
	"9rtnb0Db0Aremb7Ew6Kb28303b29b09cxb7E60b09remb7Enopb09callb7E302b09recfb09rtnb0Db0Aremb7Ew6Lb28304b"
	"29b09ecdb7EbBFbE26b28forb29b09remb7Enopb09callb7E303b09recfb09rtnb0Db0Aremb7Ew6Sb28305b29b09tcb7Ef"
	"Fb09recfb09rtnfb09remb7Enopb09callb7E38b09recfb09rtnb0Db0Aremb7Ew6Tb28306b29b09tcb7EiIb09recfb09rt"
	"nfb09remb7Enopb09callb7E305b09recfb09rtnb0Db0Aremb7Ew65b28307b29b09callb7E106b09recfb09rtnfb09b62s"
	"yrtnb09callb7E39b09recfb09rtnb0Db0Aremb7Ew66b28308b29b09callb7E38b09recfb09rtnfb09remb7Enopb09call"
	"b7E307b09recfb09rtnb0Db0Aremb7Ew67b28309b29b09callb7E39b09recfb09rtnfb09remb7Enopb09callb7E308b09r"
	"ecfb09rtnb0Db0Aremb7Ew68b28310b29b09callb7E106b09recfb09rtnfb09b62syrtnb09callb7E309b09recfb09rtnb"
	"0Db0Aremb7Ew69b28311b29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E310b09recfb09rtnb0Db0Aremb7"
	"Ew7Ab28312b29b09callb7E39b09recfb09rtnfb09remb7Enopb09callb7E311b09recfb09rtnb0Db0Aremb7Ew7Cb28313"
	"b29b09callb7E106b09recfb09rtnfb09b62syrtnb09callb7E312b09recfb09rtnb0Db0Aremb7Ew7Db28314b29b09call"
	"b7E38b09recfb09rtnfb09remb7Enopb09callb7E313b09recfb09rtnb0Db0Aremb7Ew7Eb28315b29b09tcb7EfFb09recf"
	"b09rtnfb09remb7Enopb09callb7E314b09recfb09rtnb0Db0Aremb7Ew7Fb28316b29b09tcb7EiIb09recfb09rtnfb09re"
	"mb7Enopb09callb7E315b09recfb09rtnb0Db0Aremb7Ew7Ib28317b29b09callb7E86b09recfb09rtnfb09b62syrtnb09v"
	"nb62b09rtnb0Db0Aremb7Ew7Jb28318b29b09vnab09remb7Enopb09callb7E317b09recfb09rtnb0Db0Aremb7Ew7Kb2831"
	"9b29b09cxb7E70b09remb7Enopb09callb7E318b09recfb09rtnb0Db0Aremb7Ew7Lb28320b29b09ecdb7EbBFbE27b28ifb"
	"29b09remb7Enopb09callb7E319b09recfb09rtnb0Db0Aremb7Ew7Tb28321b29b09tcb7EyYb09recfb09rtnfb09remb7En"
	"opb09callb7E38b09recfb09rtnb0Db0Aremb7Ew7Ub28322b29b09tcb7EsSb09recfb09rtnfb09remb7Enopb09callb7E3"
	"21b09recfb09rtnb0Db0Aremb7Ew7Vb28323b29b09tcb7Eb62Bb09recfb09rtnfb09remb7Enopb09callb7E322b09recfb"
	"09rtnb0Db0Aremb7Ew75b28324b29b09callb7E106b09recfb09rtnfb09b62syrtnb09callb7E39b09recfb09rtnb0Db0A"
	"remb7Ew76b28325b29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E324b09recfb09rtnb0Db0Aremb7Ew77b"
	"28326b29b09callb7E39b09recfb09rtnfb09remb7Enopb09callb7E325b09recfb09rtnb0Db0Aremb7Ew78b28327b29b0"
	"9callb7E106b09recfb09rtnfb09b62syrtnb09callb7E326b09recfb09rtnb0Db0Aremb7Ew79b28328b29b09callb7E38"
	"b09recfb09rtnfb09remb7Enopb09callb7E327b09recfb09rtnb0Db0Aremb7Ew8Ab28329b29b09tcb7EyYb09recfb09rt"
	"nfb09remb7Enopb09callb7E328b09recfb09rtnb0Db0Aremb7Ew8Cb28330b29b09tcb7EsSb09recfb09rtnfb09remb7En"
	"opb09callb7E329b09recfb09rtnb0Db0Aremb7Ew8Db28331b29b09tcb7Eb62Bb09recfb09rtnfb09remb7Enopb09callb"
	"7E330b09recfb09rtnb0Db0Aremb7Ew8Gb28332b29b09callb7E88b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0"
	"Aremb7Ew8Hb28333b29b09vnab09remb7Enopb09callb7E332b09recfb09rtnb0Db0Aremb7Ew8Ib28334b29b09cxb7E80b"
	"09remb7Enopb09callb7E333b09recfb09rtnb0Db0Aremb7Ew8Jb28335b29b09ecdb7EbBFbE28b28b62syb29b09remb7En"
	"opb09callb7E334b09recfb09rtnb0Db0Aremb7Ew8Rb28336b29b09tcb7EtTb09recfb09rtnfb09remb7Enopb09callb7E"
	"38b09recfb09rtnb0Db0Aremb7Ew8Sb28337b29b09tcb7EoOb09recfb09rtnfb09remb7Enopb09callb7E336b09recfb09"
	"rtnb0Db0Aremb7Ew8Tb28338b29b09tcb7EnNb09recfb09rtnfb09remb7Enopb09callb7E337b09recfb09rtnb0Db0Arem"
	"b7Ew80b28339b29b09callb7E106b09recfb09rtnfb09b62syrtnb09callb7E39b09recfb09rtnb0Db0Aremb7Ew81b2834"
	"0b29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E339b09recfb09rtnb0Db0Aremb7Ew82b28341b29b09tcb"
	"7EtTb09recfb09rtnfb09remb7Enopb09callb7E340b09recfb09rtnb0Db0Aremb7Ew83b28342b29b09tcb7EoOb09recfb"
	"09rtnfb09remb7Enopb09callb7E341b09recfb09rtnb0Db0Aremb7Ew84b28343b29b09tcb7EnNb09recfb09rtnfb09rem"
	"b7Enopb09callb7E342b09recfb09rtnb0Db0Aremb7Ew87b28344b29b09callb7E90b09recfb09rtnfb09b62syrtnb09vn"
	"b62b09rtnb0Db0Aremb7Ew88b28345b29b09vnab09remb7Enopb09callb7E344b09recfb09rtnb0Db0Aremb7Ew89b28346"
	"b29b09cxb7E90b09remb7Enopb09callb7E345b09recfb09rtnb0Db0Aremb7Ew9Ab28347b29b09ecdb7EbBFbE29b28notb"
	"29b09remb7Enopb09callb7E346b09recfb09rtnb0Db0Aremb7Ew9Ib28348b29b09tcb7EcCb09recfb09rtnfb09remb7En"
	"opb09callb7E38b09recfb09rtnb0Db0Aremb7Ew9Jb28349b29b09tcb7EtTb09recfb09rtnfb09remb7Enopb09callb7E3"
	"48b09recfb09rtnb0Db0Aremb7Ew9Nb28350b29b09tcb7EcCb09recfb09rtnfb09remb7Enopb09callb7E60b09recfb09r"
	"tnb0Db0Aremb7Ew9Ob28351b29b09tcb7EtTb09recfb09rtnfb09remb7Enopb09callb7E350b09recfb09rtnb0Db0Aremb"
	"7Ew9Rb28352b29b09callb7E92b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7Ew9Sb28353b29b09vnab09"
	"remb7Enopb09callb7E352b09recfb09rtnb0Db0Aremb7Ew9Tb28354b29b09cxb7E100b09remb7Enopb09callb7E353b09"
	"recfb09rtnb0Db0Aremb7Ew9Ub28355b29b09ecdb7EbBFbE210b28tcb29b09remb7Enopb09callb7E354b09recfb09rtnb"
	"0Db0Aremb7Ew92b28356b29b09tcb7EaAb09recfb09rtnfb09remb7Enopb09callb7E38b09recfb09rtnb0Db0Aremb7Ew9"
	"3b28357b29b09tcb7EcCb09recfb09rtnfb09remb7Enopb09callb7E356b09recfb09rtnb0Db0Aremb7Ew94b28358b29b0"
	"9tcb7EtTb09recfb09rtnfb09remb7Enopb09callb7E357b09recfb09rtnb0Db0Aremb7Ew99b28359b29b09tcb7EaAb09r"
	"ecfb09rtnfb09remb7Enopb09callb7E60b09recfb09rtnb0Db0Aremb7EwCAAb28360b29b09tcb7EcCb09recfb09rtnfb0"
	"9remb7Enopb09callb7E359b09recfb09rtnb0Db0Aremb7EwCACb28361b29b09tcb7EtTb09recfb09rtnfb09remb7Enopb"
	"09callb7E360b09recfb09rtnb0Db0Aremb7EwCAFb28362b29b09callb7E94b09recfb09rtnfb09b62syrtnb09vnb62b09"
	"rtnb0Db0Aremb7EwCAGb28363b29b09vnab09remb7Enopb09callb7E362b09recfb09rtnb0Db0Aremb7EwCAHb28364b29b"
	"09cxb7E110b09remb7Enopb09callb7E363b09recfb09rtnb0Db0Aremb7EwCAIb28365b29b09ecdb7EbBFbE211b28tcab2"
	"9b09remb7Enopb09callb7E364b09recfb09rtnb0Db0Aremb7EwCAPb28366b29b09tcb7EsSb09recfb09rtnfb09remb7En"
	"opb09callb7E38b09recfb09rtnb0Db0Aremb7EwCAQb28367b29b09tcb7EtTb09recfb09rtnfb09remb7Enopb09callb7E"
	"366b09recfb09rtnb0Db0Aremb7EwCAUb28368b29b09tcb7EsSb09recfb09rtnfb09remb7Enopb09callb7E60b09recfb0"
	"9rtnb0Db0Aremb7EwCAVb28369b29b09tcb7EtTb09recfb09rtnfb09remb7Enopb09callb7E368b09recfb09rtnb0Db0Ar"
	"emb7EwCAYb28370b29b09callb7E96b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7EwCAZb28371b29b09v"
	"nab09remb7Enopb09callb7E370b09recfb09rtnb0Db0Aremb7EwCA0b28372b29b09cxb7E121b09remb7Enopb09callb7E"
	"371b09recfb09rtnb0Db0Aremb7EwCA1b28373b29b09ecdb7EbBFbE212b28tsb29b09remb7Enopb09callb7E372b09recf"
	"b09rtnb0Db0Aremb7EwCA7b28374b29b09callb7E64b09recfb09rtnfb09remb7Enopb09vnb62b09rtnb0Db0Aremb7EwCA"
	"8b28375b29b09vnab09remb7Enopb09callb7E374b09recfb09rtnb0Db0Aremb7EwCA9b28376b29b09cxb7E122b09remb7"
	"Enopb09callb7E375b09recfb09rtnb0Db0Aremb7EwCCAb28377b29b09ecdb7EbBFbE212b28bD7bD6bB7bFBbB4bAEtsb29"
	"b09remb7Enopb09callb7E376b09recfb09rtnb0Db0Aremb7EwCCJb28378b29b09tcb7EpPb09recfb09rtnfb09remb7Eno"
	"pb09callb7E38b09recfb09rtnb0Db0Aremb7EwCCKb28379b29b09tcb7EoOb09recfb09rtnfb09remb7Enopb09callb7E3"
	"78b09recfb09rtnb0Db0Aremb7EwCCLb28380b29b09tcb7EnNb09recfb09rtnfb09remb7Enopb09callb7E379b09recfb0"
	"9rtnb0Db0Aremb7EwCCRb28381b29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E39b09recfb09rtnb0Db0A"
	"remb7EwCCSb28382b29b09tcb7EpPb09recfb09rtnfb09remb7Enopb09callb7E381b09recfb09rtnb0Db0Aremb7EwCCTb"
	"28383b29b09tcb7EoOb09recfb09rtnfb09remb7Enopb09callb7E382b09recfb09rtnb0Db0Aremb7EwCCUb28384b29b09"
	"tcb7EnNb09recfb09rtnfb09remb7Enopb09callb7E383b09recfb09rtnb0Db0Aremb7EwCCXb28385b29b09callb7E99b0"
	"9recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7EwCCYb28386b29b09vnab09remb7Enopb09callb7E385b09re"
	"cfb09rtnb0Db0Aremb7EwCCZb28387b29b09cxb7E130b09remb7Enopb09callb7E386b09recfb09rtnb0Db0Aremb7EwCC0"
	"b28388b29b09ecdb7EbBFbE213b28nopb29b09remb7Enopb09callb7E387b09recfb09rtnb0Db0Aremb7EwCC8b28389b29"
	"b09tcb7EsSb09recfb09rtnfb09remb7Enopb09callb7E38b09recfb09rtnb0Db0Aremb7EwCC9b28390b29b09tcb7EpPb0"
	"9recfb09rtnfb09remb7Enopb09callb7E389b09recfb09rtnb0Db0Aremb7EwCDAb28391b29b09tcb7EeEb09recfb09rtn"
	"fb09remb7Enopb09callb7E390b09recfb09rtnb0Db0Aremb7EwCDHb28392b29b09callb7E38b09recfb09rtnfb09remb7"
	"Enopb09callb7E39b09recfb09rtnb0Db0Aremb7EwCDIb28393b29b09tcb7EsSb09recfb09rtnfb09remb7Enopb09callb"
	"7E392b09recfb09rtnb0Db0Aremb7EwCDJb28394b29b09tcb7EpPb09recfb09rtnfb09remb7Enopb09callb7E393b09rec"
	"fb09rtnb0Db0Aremb7EwCDKb28395b29b09tcb7EeEb09recfb09rtnfb09remb7Enopb09callb7E394b09recfb09rtnb0Db"
	"0Aremb7EwCDNb28396b29b09callb7E101b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7EwCDOb28397b29"
	"b09vnab09remb7Enopb09callb7E396b09recfb09rtnb0Db0Aremb7EwCDPb28398b29b09cxb7E140b09remb7Enopb09cal"
	"lb7E397b09recfb09rtnb0Db0Aremb7EwCDQb28399b29b09ecdb7EbBFbE214b28epsb29b09remb7Enopb09callb7E398b0"
	"9recfb09rtnb0Db0Aremb7EwCDYb28400b29b09tcb7EfFb09recfb09rtnfb09remb7Enopb09callb7E38b09recfb09rtnb"
	"0Db0Aremb7EwCDZb28401b29b09tcb7EoOb09recfb09rtnfb09remb7Enopb09callb7E400b09recfb09rtnb0Db0Aremb7E"
	"wCD0b28402b29b09tcb7EeEb09recfb09rtnfb09remb7Enopb09callb7E401b09recfb09rtnb0Db0Aremb7EwCD6b28403b"
	"29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E39b09recfb09rtnb0Db0Aremb7EwCD7b28404b29b09tcb7E"
	"fFb09recfb09rtnfb09remb7Enopb09callb7E403b09recfb09rtnb0Db0Aremb7EwCD8b28405b29b09tcb7EoOb09recfb0"
	"9rtnfb09remb7Enopb09callb7E404b09recfb09rtnb0Db0Aremb7EwCD9b28406b29b09tcb7EeEb09recfb09rtnfb09rem"
	"b7Enopb09callb7E405b09recfb09rtnb0Db0Aremb7EwCEDb28407b29b09callb7E103b09recfb09rtnfb09b62syrtnb09"
	"vnb62b09rtnb0Db0Aremb7EwCEEb28408b29b09vnab09remb7Enopb09callb7E407b09recfb09rtnb0Db0Aremb7EwCEFb2"
	"8409b29b09cxb7E150b09remb7Enopb09callb7E408b09recfb09rtnb0Db0Aremb7EwCEGb28410b29b09ecdb7EbBFbE215"
	"b28eofb29b09remb7Enopb09callb7E409b09recfb09rtnb0Db0Aremb7EwCEOb28411b29b09tcb7ErRb09recfb09rtnfb0"
	"9remb7Enopb09callb7E38b09recfb09rtnb0Db0Aremb7EwCEPb28412b29b09tcb7EoOb09recfb09rtnfb09remb7Enopb0"
	"9callb7E411b09recfb09rtnb0Db0Aremb7EwCEQb28413b29b09tcb7EeEb09recfb09rtnfb09remb7Enopb09callb7E412"
	"b09recfb09rtnb0Db0Aremb7EwCEWb28414b29b09callb7E38b09recfb09rtnfb09remb7Enopb09callb7E39b09recfb09"
	"rtnb0Db0Aremb7EwCEXb28415b29b09tcb7ErRb09recfb09rtnfb09remb7Enopb09callb7E414b09recfb09rtnb0Db0Are"
	"mb7EwCEYb28416b29b09tcb7EoOb09recfb09rtnfb09remb7Enopb09callb7E415b09recfb09rtnb0Db0Aremb7EwCEZb28"
	"417b29b09tcb7EeEb09recfb09rtnfb09remb7Enopb09callb7E416b09recfb09rtnb0Db0Aremb7EwCE2b28418b29b09ca"
	"llb7E105b09recfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7EwCE3b28419b29b09vnab09remb7Enopb09callb"
	"7E418b09recfb09rtnb0Db0Aremb7EwCE4b28420b29b09cxb7E160b09remb7Enopb09callb7E419b09recfb09rtnb0Db0A"
	"remb7EwCE5b28421b29b09ecdb7EbBFbE216b28eorb29b09remb7Enopb09callb7E420b09recfb09rtnb0Db0Aremb7EwCE"
	"8b28422b29b09ecdb7EbB1bEDbB4bEFbCAbBDb09remb7Enopb09callb7E107b09recfb09rtnb0Db0Aremb7EwCFFb28423b"
	"29b09callb7E107b09recfb09rtnfb09b62syrtnb09callb7E39b09recfb09rtnb0Db0Aremb7EwCFGb28424b29b09callb"
	"7E38b09recfb09rtnfb09remb7Enopb09callb7E423b09recfb09rtnb0Db0Aremb7EwCFNb28425b29b09callb7E108b09r"
	"ecfb09rtnfb09b62syrtnb09vnb62b09rtnb0Db0Aremb7EwCFOb28426b29b09callb7E109b09recfb09rtnfb09b62syrtn"
	"b09callb7E425b09recfb09rtnb0Db0Aremb7EwCFPb28427b29b09vnab09remb7Enopb09callb7E426b09recfb09rtnb0D"
	"b0Aremb7EwCFQb28428b29b09cxb7E990b09remb7Enopb09callb7E427b09recfb09rtnb0Db0Aremb7EwCF1b28429b29b0"
	"9callb7E107b09recfb09rtnfb09b62syrtnb09callb7E112b09recfb09rtnb0Db0Aremb7EwCF2b28430b29b09callb7E1"
	"13b09recfb09rtnfb09remb7Enopb09callb7E429b09recfb09rtnb0Db0Ab00"
	; 	return wl_stru_strf::bstr_de(ss,s);}


	int knl_rom05( wl_stru_sheet *ap_rom)
	{
		wl_stru_vbary_rdr romtxt;

		romtxt.cf_opens(lf_obj5());
		return ap_rom->cf_import_str(romtxt.cf_read(), "\t", "\r\n");
	}


	int yy_chk1(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list l1,l2,l3;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= br_tr(i);
			if( (pt->cx==9101||pt->cx==9201) && pt->aob=='a' ) l1.cf_add( br_vt(i) );
		}

		l1.cf_setgroup(&l3);
		for(i=0,j=l3.cf_howmany();i<j;i++) {
			if(*(wlint32 *)l3.cf_read(i)>1) l2.cf_add(l1.cf_read(i));
		}

		j=l2.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("产生式左侧的VN有重复");
			for(i=0;i<l2.cf_howmany();i++) ap_ermsg->cf_add(l2.cf_read(i));
			return 0;
		}
		return 1;
	}


	int yy_chk2(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list vnleft, vnright;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= br_tr(i);
			if( (pt->cx==9101||pt->cx==9201) && pt->aob=='a' ) vnleft.cf_add( br_vt(i) );
			if( pt->cx==921				 && pt->aob=='a' ) vnright.cf_add( br_vt(i) );
		}
		vnleft.cf_setuniq();
		vnright.cf_setuniq();
		vnright.cf_setcha(&vnleft);

		j=vnright.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("存在未说明的VN");
			for(i=0;i<vnright.cf_howmany();i++) ap_ermsg->cf_add(vnright.cf_read(i));
			return 0;
		}

		return 1;
	}


	int yy_deal1ele(wlint32 h , wl_stru_list *ap_ermsg)
	
	{
		wlint32 cx, h1;

		switch (cx=br_tr(h)->cx)
		{
		case 921	:	
		case 961	:	
		case 962	:	
		case 971	:	
		case 972	:	
			iv_lcode.cf_add32(cx);
			iv_lname.cf_add(br_vt(h));
			break;

		case 990	:	
			if(!yy_E(h, ap_ermsg)) return 0;
			break;

		case 10	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "ecd" );
			break;

		case 21	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			h1=br_xne(h1);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "vn" );
			break;

		case 22	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "vn" );
			break;

		case 30	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			h1=br_xne(h1);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "lmt" );
			break;

		case 40	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "vnx" );
			break;

		case 50	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			h1=br_xne(h1);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "whl" );
			break;

		case 60	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			h1=br_xne(h1);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "for" );
			break;

		case 70	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			h1=br_xne(h1);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			h1=br_xne(h1);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;

			
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "if" );
			break;

		case 80	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			h1=br_xne(h1);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;

			
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "bsy" );
			break;

		case 90	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "not" );
			break;

		case 100	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "tc" );
			break;

		case 110	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "tca" );
			break;

		case 121	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "ts" );
			break;

		case 122	:	
			h1=br_yne(h);
			if(!yy_deal1ele(h1, ap_ermsg)) return 0;
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "ts" );
			break;

		case 130	:	
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "nop" );
			break;

		case 140	:	
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "eps" );
			break;

		case 150	:	
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "eof" );
			break;

		case 160	:	
			iv_lcode.cf_add32( cx );
			iv_lname.cf_add( "eor" );
			break;

		default:
			ap_ermsg->cf_add(88);
			sprintf(ap_ermsg->cf_readtop(), "表达式处理内部出错,cx=%ld,id=%ld", cx, br_tr(h)->id);
			return 0;
		}
		return 1;
	}


	int yy_E(wlint32 h , wl_stru_list *ap_ermsg)
	
	{
		wlint32 i,j;
		int rc;

		
		for(j=0,i=br_yne(h); -1!=i; i=br_xne(i) ) j++; 

		switch (j)
		{
		case 3:
			
			i=br_yne(h);
			rc = yy_deal1ele(i, ap_ermsg);
			if(!rc) return rc;
			
			i=br_yne(h); i=br_xne(i); i=br_xne(i);
			rc = yy_deal1ele(i, ap_ermsg);
			if(!rc) return rc;
			
			i=br_yne(h); i=br_xne(i);
			rc = yy_deal1ele(i, ap_ermsg);
			if(!rc) return rc;
			break;
		case 1:
			i=br_yne(h);
			rc = yy_deal1ele(i, ap_ermsg);
			if(!rc) return rc;
			break;
		default:
			ap_ermsg->cf_add(99);
			sprintf(ap_ermsg->cf_readtop(), "表达式处理内部出错,x向个数为:%ld,hnd=%ld", j, h);
			return 0;
		}
		return 1;
	}


	int yy_prg1e(wlint32 h , wl_stru_list *ap_prgl, wl_stru_list *ap_ermsg)
		        
	{
		int rc;
		wlint32 i,c;
		wlint32 h1,h2,h3;
		wl_stru_prpt e;

		rc = yy_E(h, ap_ermsg);
		if(!rc) return 0;

		for(i=0;i<iv_lcode.cf_howmany();i++)
			switch ( c=*(wlint32 *)iv_lcode.cf_read(i) ) {
			case 971	:	
			case 972	:	
				h1=i-2;
				h2=i-1;
				h3=i-0;
				e.cf_let("e", iv_lname.cf_read(h1) );
				e.cf_cat("e", iv_lname.cf_read(h3) );
				e.cf_cat("e", iv_lname.cf_read(h2) );
				if(3!=iv_lcode.cf_howmany()) e.cf_kuo("e", "(", ")");
				
				
				iv_lcode.cf_del(h1);
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 10	:	
				h1=i-1;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", iv_lname.cf_read(h1) );
				e.cf_kuo("e", "[ecd~", "]");
				
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 21	:	
				h1=i-2;
				h2=i-1;
				h3=i-0;
				e.cf_let("e", iv_lname.cf_read(h1) );
				e.cf_kuo("e", "[cx~", "]+[vna]+");
				e.cf_cat("e", iv_lname.cf_read(h2) );
				e.cf_cat("e", "+[vnb]" );
				
				iv_lcode.cf_del(h1);
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 22	:	
				h1=i-1;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", "b00" );
				e.cf_kuo("e", "[cx~", "]+[vna]+");
				e.cf_cat("e", iv_lname.cf_read(h1) );
				e.cf_cat("e", "+[vnb]" );
				
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 30	:	
				h1=i-2;
				h2=i-1;
				h3=i-0;
				e.cf_let("e", "[lmt~" );
				e.cf_cat("e", iv_lname.cf_read(h1) );
				e.cf_cat("e", "]+" );
				e.cf_cat("e", iv_lname.cf_read(h2) );
				e.cf_cat("e", "+[lmtpop]" );
				
				iv_lcode.cf_del(h1);
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 40	:	
				h1=i-1;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", iv_lname.cf_read(h1) );
				e.cf_kuo("e", "[ci~", "]+[vnx]");
				
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 50	:	
				h1=i-2;
				h2=i-1;
				h3=i-0;
				e.cf_let("e", "for(" );
				e.cf_cat("e", iv_lname.cf_read(h1) );
				e.cf_cat("e", ")(");
				e.cf_cat("e", iv_lname.cf_read(h2) );
				e.cf_cat("e", ")" );
				
				iv_lcode.cf_del(h1);
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 60	:	
				h1=i-2;
				h2=i-1;
				h3=i-0;
				e.cf_let("e", "[rem~nop]" );
				for(h3=0;h3<wl_stru_strf::str_atol(iv_lname.cf_read(h1));h3++){
					e.cf_cat("e", "+");
					e.cf_cat("e", iv_lname.cf_read(h2) );
				}
				
				iv_lcode.cf_del(h1);
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 70	:	
				h1=i-3;
				h2=i-2;
				h3=i-1;
				e.cf_let("e", "if(" );
				e.cf_cat("e", iv_lname.cf_read(h1) );
				e.cf_cat("e", ")(");
				e.cf_cat("e", iv_lname.cf_read(h2) );
				e.cf_cat("e", ")([eps]+" );               
				e.cf_cat("e", iv_lname.cf_read(h3) );
				e.cf_cat("e", ")" );
				
				iv_lcode.cf_del(h1);
				iv_lcode.cf_del(h1);
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_del(h1);
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 80	:	
				h1=i-2;
				h2=i-1;
				h3=i-0;
				e.cf_let("e", "bsy(" );
				e.cf_cat("e", iv_lname.cf_read(h1) );
				e.cf_cat("e", ")([eps]+" );               
				e.cf_cat("e", iv_lname.cf_read(h2) );
				e.cf_cat("e", ")" );
				
				iv_lcode.cf_del(h1);
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 90	:	
				h1=i-1;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", "not(" );
				e.cf_cat("e", iv_lname.cf_read(h1) );
				e.cf_cat("e", ")" );
				
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 100	:	
				h1=i-1;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", "[tc~" );
				e.cf_cat("e", iv_lname.cf_read(h1) );
				e.cf_cat("e", "]" );
				
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 110	:	
				h1=i-1;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", "[tca~" );
				e.cf_cat("e", iv_lname.cf_read(h1) );
				e.cf_cat("e", "]" );
				
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 121	:	
			case 122	:	
				h1=i-1;
				h2=i-0;
				h3=i-0;
				{
					wlint8 s[5], *t;
					wlint32 k;
					t = iv_lname.cf_read(h1);
					k = wl_stru_strf::bstr_de_size(t);
					wl_stru_strf::bstr_de(t);
					e.cf_let("e", "[rem~nop]" );
					for(h3=0;h3<k;h3++) {
						s[0]=t[h3];
						s[1]=0;
						wl_stru_strf::bstr_en(s,1);
						e.cf_cat("e", "+[tc~" );
						e.cf_cat("e", s );
						e.cf_cat("e", "]" );
					}
				}
				
				iv_lcode.cf_del(h1);
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_del(h1);
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 130	:	
				h1=i-0;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", "[rem~nop130]" );
				
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 140	:	
				h1=i-0;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", "[eps]" );
				
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 150	:	
				h1=i-0;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", "[teof]" );
				
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;
			case 160	:	
				h1=i-0;
				h2=i-0;
				h3=i-0;
				e.cf_let("e", "[teor]" );
				
				*(wlint32 *)iv_lcode.cf_read(h1) = 921;
				iv_lname.cf_modi(h1, e.cf_get("e") );
				i = h1;
				break;

			}

		ap_prgl->cf_add(iv_lname.cf_readtop());
		return 1;
	}


	int yy_lnk(wl_stru_list *ap_prgl04, wl_stru_list *ap_ermsg)
	{
		int rc;
		wlint32 h;
		wlint32 h1, h2, h3, cx1, cx2, cx3;
		wl_stru_list E0;

		ap_prgl04->cf_clean();
		rc=0;
		h=br_yne(0);
		while(-1!=h) {
			h1 = h;
			h2 = br_xne(h1) ;
			h3 = br_xne(h2) ;
			cx1 = br_tr(h1)->cx;
			cx2 = br_tr(h2)->cx;
			cx3 = br_tr(h3)->cx;

			E0.cf_clean();
			E0.cf_add( br_vt(h1) );

			
			E0.cf_add("=[rem~nop]+");

			if(cx2==9202){
				E0.cf_add("[ecd~");

				E0.cf_add( wl_stru_strf::bstr_en_size(br_vt(h1), wl_stru_strf::str_len(br_vt(h1))) );
				wl_stru_strf::bstr_en(br_vt(h1), wl_stru_strf::str_len(br_vt(h1)), E0.cf_readtop() );

				E0.cf_add( "]+" );
			}

			iv_lcode.cf_clean();
			iv_lname.cf_clean();
			rc = yy_prg1e(h3, &E0, ap_ermsg);
			if(!rc) return 0;


			E0.cf_add(";");
			E0.cf_collect();
			ap_prgl04->cf_add(E0.cf_readtop());

			h = br_xne(h3) ;
		}

		return rc;
	}


protected:

	void cf_emsg(wl_stru_list *ap_ermsg)
	
	{
		char s[99], *t;
		wlint32 y,k;
		wl_s_stru_gmr01_reg  *pr;

		sprintf(s, "第%ld行，第%ld字节，总第%ld字节.", cf_gerr_pos('r'), cf_gerr_pos('c'), cf_gerr_pos('t') );
		ap_ermsg->cf_add(s);
		for(y=k=0;y<ivp_err->cf_howmany();y++) {
			pr = (wl_s_stru_gmr01_reg *)(ivp_err->cf_read(y));
			if(ivp_errl==NULL)
				wl_stru_strf::str_ltoa(pr->ecd, t=s);
			else
				t = erl_s(y);

			if(t[0]!=0&&wl_stru_strf::str_cmp(ap_ermsg->cf_readtop(), t) ){
				if(0==k++){
					ap_ermsg->cf_add(99+wl_stru_strf::str_len(t));
					sprintf(ap_ermsg->cf_readtop(), "程序期待 %s 。导致下列错误", t);
				}else ap_ermsg->cf_add(t);
			}
		}
	}


public:


	int cf_wmk( wl_stru_sheet		*ap_vmrom,
				wl_stru_vbary_rdr	*ap_prg,
				wl_stru_list		*ap_tr,
				wl_stru_sheet		*ap_obj,
				wl_stru_list		*ap_er,
				wl_stru_list		*ap_ermsg	)
				
	{
		int rc;
		wl_stru_vbary_rdr	prg04;
		wl_stru_gmr04	lg04, lg04b;
		wl_stru_list errl;
		wl_stru_list prgl04;

		
		if(!knl_rom05(ap_obj)) {
			knl_prg(&prg04);
			rc = lg04.cf_wmk(ap_vmrom, &prg04, ap_tr, ap_obj, ap_er, ap_ermsg);
			if(!rc) {
				ap_ermsg->cf_add("G04:");
				ap_ermsg->cf_ins(0);
				return 0;
			}
			
		}

		
		cf_rom(ap_obj);
		cf_itfc(ap_tr, ap_er, &errl, NULL, NULL, NULL);
		rc = cf_app(ap_prg);
		if(!rc) {
			cf_emsg(ap_ermsg);
			return 0;
		}

		
		rc = yy_chk1(ap_ermsg);
		if(!rc) return 0;

		rc= yy_chk2(ap_ermsg);
		if(!rc) return 0;


		rc = yy_lnk(&prgl04, ap_ermsg);
		if(!rc) return 0;

		
		prgl04.cf_collect("\r\n");
		prg04.cf_close();
		prg04.cf_opens(prgl04.cf_readtop());
		rc = lg04b.cf_wmk(ap_vmrom, &prg04, ap_tr, ap_obj, ap_er, ap_ermsg);
		if(!rc) {
			ap_ermsg->cf_add("G04-B:");
			ap_ermsg->cf_ins(0);
			return 0;
		}

		return 1;
	}


}; 

#endif


#ifndef WL_STRU_GMR_H
#define WL_STRU_GMR_H

class wl_stru_gmr : public wl_stru_gmr05  {

friend class gmr;

private:

	class gmr *og;
	wl_stru_list		tr ;
	wl_stru_list		er ;
	wl_stru_sheet		vmrom ;
	wl_stru_list	errl, cxl;
	wl_stru_sheet		iv_obj;


	int cf_mk1(	wl_stru_vbary_rdr	*ap_prg,
				wl_stru_sheet		*ap_obj,
				wl_stru_list		*ap_ermsg	)
	{
		wl_stru_gmr05		g05 ;
		ap_ermsg->cf_clean();
		return g05.cf_wmk(&vmrom, ap_prg, &tr, ap_obj, &er, ap_ermsg );
	}


	int cf_mk2(wl_stru_sheet		*ap_obj,
				wl_stru_vbary_rdr	*ap_prg_mess,
				wl_stru_list		*ap_ermsg,
				int have_erl, int have_cxl, wlpfucb pf, wlint8 *exdata )
	{
		ap_ermsg->cf_clean();
		cf_rom(ap_obj);
		cf_itfc(&tr, &er, have_erl?&errl:NULL, have_cxl?&cxl:NULL, pf, exdata);
		if(!cf_app(ap_prg_mess) ) {
			cf_emsg(ap_ermsg);
			return 0;
		}
		return 1;
	}


protected:

	virtual void cf_emsg(wl_stru_list *ap_ermsg)
	{
		wl_stru_gmr05::cf_emsg(ap_ermsg);
	}


public:


	

	int cf_gmk(	wl_stru_vbary_rdr	*ap_prg,
				wl_stru_sheet		*ap_obj,
				wl_stru_vbary_rdr	*ap_prg_mess,
				wl_stru_list		*ap_ermsg,
				int have_erl  = 1,
				int have_cxl  = 1,
				wlpfucb pf    = NULL,
				wlint8 *exdata= NULL )
	{
		int rc;
		wl_stru_sheet	*myobj;

		myobj=(ap_obj==NULL?&iv_obj:ap_obj);
		if(myobj->cf_rowcount()==0){
			rc = cf_mk1(ap_prg, myobj , ap_ermsg);
			if(!rc){
				ap_ermsg->cf_add("源程序语法错：");
				ap_ermsg->cf_ins(0);
				return rc;
			}
		}
		return cf_mk2(myobj, ap_prg_mess, ap_ermsg, have_erl, have_cxl, pf, exdata);
	}


	void cf_output(wlint8 *out1, wlint8 *out2)
	{
		gmr01_output_trace1(out1, this);
		wl_stru_gmr01::output_err(out2,   ivp_err);
	}

}; 

#endif




class gmr {

private:

	gmr & operator = (const gmr & rhs)
	{
		return *this;
	}

	gmr(const gmr & rhs)
	{;}

private:
	 wl_stru_gmr		*m_pg;
	 wl_stru_vbary_rdr	m_txt1;
	 wl_stru_vbary_rdr	m_txt2;
	 wl_stru_sheet		m_objsht;
	 wl_stru_list		m_errmsglst;

public:

	gmr()
	{
		m_pg=NULL;
	}

	virtual ~gmr()
	{
		if(m_pg) delete m_pg;
		m_pg=NULL;
	}

	void init(void)
	{
		if(m_pg) delete m_pg;
		m_pg = new wl_stru_gmr;
		m_pg->og = this;

		m_txt1.cf_close();
		m_txt2.cf_close();
		m_objsht.cf_clean();
		m_errmsglst.cf_clean();
	}


	long errhm( )
	{
		long i;
		i=m_errmsglst.cf_howmany();
		return i;
	}

	char *errln(long i)
	{
		return m_errmsglst.cf_read(i);
	}


	int mka( const char *source, int source_type_is_string=0  )
	{
		return mka( const_cast<char*>(source), source_type_is_string );
	}

	int mka( char *source, int source_type_is_string=0  )
	{
		int rc;

		do
		{
			rc = source_type_is_string==0?m_txt1.cf_openf(source):m_txt1.cf_opens(source);
			if(!rc) break;

			m_objsht.cf_clean();
			m_errmsglst.cf_clean();
			rc = m_pg->cf_mk1( &m_txt1, &m_objsht, &m_errmsglst );

		}while(0);

		return rc;
	}


	int mkb( const char *source, int source_type_is_string=0  )
	{
		return mkb( const_cast<char*>(source), source_type_is_string );
	}

	int mkb( char *source, int source_type_is_string=0  )
	{
		int rc;

		do
		{
			rc = source_type_is_string==0?m_txt2.cf_openf(source):m_txt2.cf_opens(source);
			if(!rc) break;

			m_errmsglst.cf_clean();
			rc = m_pg->cf_mk2( &m_objsht, &m_txt2, &m_errmsglst, 1,1,0,0 );

		}while(0);

		return rc;
	}


	std::string GetErrMsg()
	{
		int i;
		std::string strOut;

		for(i=0;i<errhm();i++)
		{
			strOut += errln(i) ;
			strOut += "\r\n" ;
		}
		return strOut;
	}

public:

	void outtrace	( char *pfn )	{ gmr01_output_trace1(pfn, m_pg); }
	void outerr		( char *pfn )	{ m_pg->output_err( pfn, m_pg->ivp_err); }
	long errposx	(void)			{ return m_pg->cf_gerr_pos('c'); }
	long errposy	(void)			{ return m_pg->cf_gerr_pos('r'); }
	long errpos		(void)			{ return m_pg->cf_gerr_pos('t'); }
	long br_hm		(void)			{ return m_pg->br_hm(); }
	long br_q1		(long h)		{ return m_pg->br_q1( h); } 
	long br_q2		(long h)		{ return m_pg->br_q2( h); }

	char *br_vt		(long q1,long q2){ return m_pg->br_vt(q1,q2); }
	char *br_vt		(long h)		{ return m_pg->br_vt(h); }
	long br_std		(long h)		{ return m_pg->br_std(h); }
	long br_len		(long h)		{ return m_pg->br_len(h); }
	long br_len () { return m_pg->ivp_prg->cf_len() ; }

	long br_ypr		(long h)		{ return m_pg->br_ypr(h); }
	long br_yne		(long h)		{ return m_pg->br_yne(h); }
	long br_xpr		(long h)		{ return m_pg->br_xpr(h); }
	long br_xne		(long h)		{ return m_pg->br_xne(h); }
	long br_yfst	(long h)		{ return m_pg->br_yfst(h); }
	long br_xfst	(long h)		{ return m_pg->br_xfst(h); }
	long br_ylast	(long h)		{ return m_pg->br_ylast(h); }
	long br_xlast	(long h)		{ return m_pg->br_xlast(h); }
	int  br_isycat	(long h1, long h2)	{ return m_pg->br_isycat(h1,h2); }
	int  br_isxcat	(long h1, long h2)	{ return m_pg->br_isxcat(h1,h2); }
	int  br_a		(long h)		{ return m_pg->br_a(h); }
	long cxl_l		(long h)		{ return m_pg->cxl_l(h); }
	char *cxl_s		(long h)		{ return m_pg->cxl_s(h); }
	long cxl_h		(long h, long l, int isforward, int iswholelayer) { return m_pg->cxl_h(h,l,isforward,iswholelayer); }
	long cxl_h		(long h, char *name, int isforward, int iswholelayer) { return m_pg->cxl_h(h,name,isforward,iswholelayer); }
	long cxl_hm		(long h, long l) { return m_pg->cxl_hm(h,l); }
	long cxl_hm		(long h, char *name) { return m_pg->cxl_hm(h,name); }
	long erl_l		(long h)		{ return m_pg->erl_l(h); }
	char *erl_s		(long h)		{ return m_pg->erl_s(h); }
	long erl_hm		(void)			{ return m_pg->ivp_err->cf_howmany(); }


	
	

private:

	long m_RplBaseQ1;
	long m_RplBaseQ2;
	std::vector<long> m_vecRplQ1;
	std::vector<long> m_vecRplQ2;
	std::vector<std::string> m_vecRplNewStr;

public:

	void rpl_base_all()
	{
		rpl_base( 0, br_len()-1 );
	}


	void rpl_base( long h )
	{
		rpl_base( br_q1(h), br_q2(h) );
	}

	void rpl_base( long q1, long q2 )
	{
		m_RplBaseQ1=q1;
		m_RplBaseQ2=q2;
		m_vecRplQ1.clear();
		m_vecRplQ2.clear();
		m_vecRplNewStr.clear();
	}

	void rpl_add( long h , std::string strNewStr )
	{
		long q1;
		long q2;
		q1 = br_q1(h);
		q2 = br_q2(h);
		rpl_add( q1, q2, strNewStr );
	}

	void rpl_add( long q1, long q2, std::string strNewStr )
	{
		
		{
			m_vecRplQ1.push_back(q1) ;
			m_vecRplQ2.push_back(q2) ;
			m_vecRplNewStr.push_back(strNewStr);
		}
	}

	std::string rpl_proc()
	{
		std::string strOut("");

		for( long iQ = m_RplBaseQ1; iQ <= m_RplBaseQ2; iQ++ )
		{
			std::string strTmpEle;

			strTmpEle = br_vt(iQ,iQ);

			for( long i=0; i<(long)m_vecRplQ1.size(); i++ )
			{
				if( m_vecRplQ1[i] == iQ && m_vecRplQ1[i]<=m_vecRplQ2[i] )
				{
					strTmpEle = m_vecRplNewStr[i];
					iQ = m_vecRplQ2[i]; 
					break;
				}

				if( m_vecRplQ1[i] == iQ && m_vecRplQ1[i] > m_vecRplQ2[i] )
				{
					strTmpEle = m_vecRplNewStr[i] + strTmpEle;
					
					break;
				}

			}

			strOut += strTmpEle;

		}

		return strOut;
	}


}; 


}


#endif





#ifndef X011__H_SelfIpPicker_t_h
#define X011__H_SelfIpPicker_t_h


X011_NAMESPACE_BEGIN


class SelfIpPicker_t
{
private:
	wlo::gmr		 m_g;

public:
	SelfIpPicker_t()
	{
		static char p[] =
			"/*pick-up every ip address in a file. V1.0 */"
			"S == whl( not(文件尾) )( ip地址 * tca(b01bff) );"
			"文件尾 == eof();"
			"ip地址 == {IP1 + tc(.) + IP2 + tc(.) + IP3 + tc(.) +IP4};"
			"IP1 = 整数;"
			"IP2 = 整数;"
			"IP3 = 整数;"
			"IP4 = 整数;"
			"整数 == tc(0123456789) + whl( tc(0123456789) )( tc(0123456789) );"
			;
		int rc;

		m_g.init();

		rc = m_g.mka( p, 1 );

		if(!rc)
		{
			
		}
	}

	virtual ~SelfIpPicker_t()
	{}

private:
	
	static std::string Getweb( std::string sHttpUrl, std::string sHost )
	{
		WTcpHttp h;
		SCake ckTmp;
		int i;

		
		h.ConnUrl( sHttpUrl );
		h.AddUrlHeadPara( "Host", sHost );
		h.SendHttpGet( sHttpUrl, "HTTP/1.0", 1 );

		h.killer_up( 33 );

		h.recv_ln( ckTmp, "\r\n\r\n" );
		h.ImportSvrRtnHeadPara( ckTmp );
		i = SStrf::satol( h.GetSvrRtnHeadParaVal( "Content-Length" ).c_str() );
		
		h.recv_all( ckTmp );

		h.killer_dn();

		return ckTmp.mk_sz();
	}

public:
	
	std::string PickIp()
	{
		std::string s1;
		int rc;

		
		s1 = Getweb( "http://www.123cha.com/", "www.123cha.com" );

		rc = m_g.mkb( s1.c_str(), 1 );

		std::vector< std::string > vec1, vec2;
		std::vector< int > veci;

		for( int i = 0; i < m_g.br_hm() ; i++ )
		{
			std::string s2;

			s2 = m_g.br_vt(i);
			if( s2.size() > 7 )
				vec1.push_back( s2 );
		}

		if( vec1.empty() ) return "";
		else
			return vec1[0];
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_WCsrAdoBase_h
#define X011__H_w_WCsrAdoBase_h


X011_NAMESPACE_BEGIN


class WCsrAdoBase : public ICursorDs
{
protected:

	ADODB::_ConnectionPtr	m_Cnn;
	ADODB::_RecordsetPtr	m_Rs1; 

public:
	std::string		m_strUsername;
	std::string		m_strPasswd;
	volatile tbool  m_biExceptionThrowOut;

public:

	WCsrAdoBase()
	{
		m_strUsername = "";
		m_strPasswd = "";
		m_biExceptionThrowOut = 0;
	}

	virtual ~WCsrAdoBase()
	{
		CloseTbl();
		CloseEnv();
	}


public:

	virtual tbool OnOpenEnv( envTYPE & _env )
	{
		HRESULT hr;

		try
		{
			hr = m_Cnn.CreateInstance(__uuidof(ADODB::Connection));
			if( FAILED(hr) )
			{
				m_Cnn=NULL;
				return 0;
			}

			hr = m_Cnn->Open( _bstr_t( _env.c_str() ) ,
							  m_strUsername.c_str() ,
							   m_strPasswd.c_str() ,
							  NULL	);
			if( FAILED(hr) )
			{
				m_Cnn=NULL;
				return 0;
			}

			
			m_Cnn->CommandTimeout = 0;
		}
		catch(...)
		{
			if( m_biExceptionThrowOut )
			{
				m_Cnn=NULL;
				throw;
			}
			else
			{
				m_Cnn=NULL;
				return 0;
			}
		}

		return 1;
	}


	virtual tbool OnOpenTbl( tblTYPE & _tbl )
	{
		HRESULT hr = S_OK;
		tbool rc(0);

		try
		{
			hr = m_Rs1.CreateInstance( __uuidof( ADODB::Recordset ) );
			if( FAILED(hr) )
			{
				m_Rs1 = NULL;
				return rc=0;
			}

			m_Rs1->Open( _bstr_t( _tbl.c_str() ) ,      
						 (IDispatch *)m_Cnn,
						 ADODB::adOpenForwardOnly,
						 ADODB::adLockReadOnly,
						 ADODB::adCmdUnknown );

			
			if( m_Rs1->State == ADODB::adStateOpen )
			{
				
			}
			else
			{
				m_Rs1 = NULL;
				
			}

			rc = 1;
		}
		catch(...)
		{
			if( m_biExceptionThrowOut )
			{
				m_Rs1=NULL;
				throw;
			}
			else
			{
				m_Rs1 = NULL;
				return rc=0;
			}
		}

		return rc;
	}




	virtual void OnCloseTbl()
	{
		if( !GetIsTblOpen() )
		{
			return;
		}

		try
		{
			m_Rs1->Close();
		}
		catch(...)
		{;
		}

		try
		{
			m_Rs1 = NULL;
		}
		catch(...)
		{;}
	}


	virtual void OnCloseEnv()
	{
		if( !GetIsEnvOpen() )
		{
			return;
		}

		try
		{
			m_Cnn->Close();
		}
		catch(...)
		{;
		}

		try
		{
			m_Cnn = NULL;
		}
		catch(...)
		{;}
	}


	
	public:
		long Execute( _bstr_t bstrSql )
		{
			ADODB::_ConnectionPtr	&Cnn(m_Cnn);
			_variant_t  v_nbRecordsaffected;
			long        nbRecordsAffected = -1;

			try
			{
				Cnn->Execute( bstrSql, &v_nbRecordsaffected, ADODB::adExecuteNoRecords);
				nbRecordsAffected = (long)v_nbRecordsaffected;
			}
			catch(...)
			{ ;
			}

			return nbRecordsAffected;
		}

		
		
		
	

	public:


			static SCake ReadDbImageCol( _bstr_t bstrDbConn, _bstr_t bstrSql, _bstr_t bstrColName )
			{
				ADODB::_ConnectionPtr	Cnn;
				ADODB::_RecordsetPtr   RecordSet;

				HRESULT hr;

				int iChunkSize = 222;

				try
				{
					hr = Cnn.CreateInstance(__uuidof(ADODB::Connection));
					hr = Cnn->Open( bstrDbConn , "", "", NULL	);
					hr = RecordSet.CreateInstance(__uuidof(ADODB::Recordset));
					hr = RecordSet->Open( bstrSql ,
										  (IDispatch *)Cnn,
										  ADODB::adOpenDynamic,
										  ADODB::adLockOptimistic,
										  ADODB::adCmdText );

					_variant_t  value1;
					std::vector<unsigned char> vecData;
					unsigned char chData;

					while(1)
					{
						value1 = RecordSet->GetFields()->GetItem( bstrColName )->GetChunk( iChunkSize );

						for( long index = 0; index <= (iChunkSize-1); index++ )
						{
							hr= SafeArrayGetElement( value1.parray, &index, &chData );
							if(SUCCEEDED(hr))
							{
								
								vecData.push_back(chData);
							}
							else
							{
								if( vecData.empty() )
								{
									return SCake();
								}
								return SCake( (char*)&vecData.front(), (long)vecData.size() );
							}
						}
					}

				}
				catch (...)
				{
					return SCake();
				}
			}




			
			

			
			
			
			
			
			
			
			
			

			

			
			


			
			
			
			
			

			
				static void ArrayToVariantUI1( const unsigned char *p, long iLen, _variant_t & varOut )
				{
					SAFEARRAY *psa;
					SAFEARRAYBOUND rgsabound[1];
					rgsabound[0].cElements = iLen;
					rgsabound[0].lLbound = 0;

					psa = SafeArrayCreate( VT_UI1, 1, rgsabound );
					if(psa)
					{
						for ( long index = 0; index < iLen; index++ )
						{
							SafeArrayPutElement( psa, &index, const_cast<unsigned char*>(p+index) );
						}
						VARIANT var;
						var.vt = VT_ARRAY | VT_UI1;
						var.parray = psa;
						varOut=var;

						HRESULT hRes = S_OK;
				 		hRes = SafeArrayDestroy(psa);
					}
				}

			static tbool WriteDbImageCol( _bstr_t bstrDbConn, _bstr_t bstrSql, _bstr_t bstrColName, const SCake & ckData )
			{
				ADODB::_ConnectionPtr	Cnn;
				ADODB::_RecordsetPtr   RecordSet;

				try
				{
					HRESULT hr = Cnn.CreateInstance(__uuidof(ADODB::Connection));
					hr = Cnn->Open( bstrDbConn , "", "", NULL	);
					hr = RecordSet.CreateInstance(__uuidof(ADODB::Recordset));
					hr = RecordSet->Open( bstrSql ,
										  (IDispatch *)Cnn,
										  ADODB::adOpenDynamic,
										  ADODB::adLockOptimistic,
										  ADODB::adCmdText );

					_variant_t  value1;

					ArrayToVariantUI1( (const unsigned char *)ckData.buf_const(), ckData.len(), value1 );

					if( value1.vt != VT_EMPTY && value1.vt !=VT_NULL )
					{
						RecordSet->GetFields()->GetItem( bstrColName )->AppendChunk( value1 );
						RecordSet->Update();
						return 1;
					}
				}
				catch (...)
				{
					;
				}
				return 0;
			}


static std::string GetJOBID()
{
	
	static int i = 1;
	int j;
	void *p=malloc(23);
	free(p);
	memcpy( &j, &p, sizeof(int) );
	SStrf::initrand(++i);
	ULARGE_INTEGER iui8;
	iui8.HighPart = (int)time(0);
	iui8.LowPart = i + i * (int)GetCurrentThreadId() + (int)GetCurrentProcessId() * (int)(j * SStrf::rand1()) * (int)SDte::e_proctime();
	_variant_t vv;
	vv.vt=VT_UI8;
	vv.ullVal = iui8.QuadPart;
	_bstr_t bs = vv;
	return (char*)bs;
}


}; 


X011_NAMESPACE_END

#endif







#ifndef X011__H_w_WCsrAdoTblHead_h
#define X011__H_w_WCsrAdoTblHead_h


X011_NAMESPACE_BEGIN


class WCsrAdoTblHead : public WCsrAdoBase
{
private:

	int m_iTblColNumCur;
	int m_iTblColNumTotal;


	tbool lf_Open( std::string * p_tbl )
	{
		return WCsrAdoBase::OnOpenTbl( * p_tbl );
	}


public:

	virtual ~WCsrAdoTblHead( )
	{ ;
	}


public:

	virtual tbool OnOpenTbl( tblTYPE & _tbl )
	{
		if( !WCsrAdoBase::OnOpenTbl( _tbl )) return 0;

		tbool rc=1;

		try
		{
			m_iTblColNumTotal = m_Rs1->Fields->GetCount();
			m_iTblColNumCur=0;

			rc=1;
		}
		catch(...)
		{
			rc=0;
		}

		return rc;
	}


	virtual tbool OnFetchRow( rowTYPE & _row )
	{
		_variant_t vValue, vValue1;
		_bstr_t str;
		tint32 j;
		tchar *s="";

		try
		{
			_row.clear(); 

			j = m_iTblColNumCur++;
			if(j>=m_iTblColNumTotal)
			{
				return 0;
			}

			s = str = m_Rs1->Fields->Item[(long)j]->Name;
			_row.push_back( s );
		}
		catch(...)
		{
			return 0;
		}

		return 1;
	}


}; 



X011_NAMESPACE_END

#endif






#ifndef X011__H_w_WCsrAdoTbl_h
#define X011__H_w_WCsrAdoTbl_h


X011_NAMESPACE_BEGIN


class  WCsrAdoTbl : public WCsrAdoBase
{

public:

	virtual ~WCsrAdoTbl( )
	{ ;
	}


	virtual tbool OnFetchRow( rowTYPE & _row )
	{
		_variant_t vValue, vValue1;
		_bstr_t str;
		tint32 n,j;

		try
		{
			_row.clear(); 
			n = m_Rs1->Fields->GetCount();
			for (j = 0; j<n; j++)
			{
				vValue = m_Rs1->Fields->Item[(long)j]->Value;
				str="";
				if(VT_NULL!=vValue.vt&&S_OK==VariantChangeType(&vValue1, &vValue, 0, VT_BSTR) )
				{
					str=vValue1.bstrVal;
				}
				_row.push_back( (char*)str );
			}
			m_Rs1->MoveNext();
		}
		catch(...)
		{
			return 0;
		}
		return 1;
	}


}; 


X011_NAMESPACE_END

#endif







#ifndef X011__H_w_WCsrMemTbl_h
#define X011__H_w_WCsrMemTbl_h


X011_NAMESPACE_BEGIN


class WCsrMemTbl : public ICursorDs
{
private:

	envTYPE   m_env;
	tblTYPE   m_tbldata;

	tsize m_i0;
	tsize m_i1;


public:

	std::string  m_strLineSep;


public:

	WCsrMemTbl()
	{
		m_i0 = m_i1 = 0;

		m_strLineSep = "";
	}


	virtual ~WCsrMemTbl()
	{
	}


public:

	void SetLineSep( std::string sLineSep )
	{
		m_strLineSep = sLineSep;
	}


public:

	virtual tbool OnOpenEnv( envTYPE & _env )
	{
		m_env = _env;
		m_i0 = m_i1 = 0;
		return 1;
	}


	virtual tbool OnOpenTbl( tblTYPE & _tbl )
	{
		m_tbldata = _tbl;

		if( m_strLineSep == "" )
			m_i0 = SStrvs::vsa_hm( m_tbldata, m_env, 0 ); 
		else
			m_i0 = SStrvs::vsa_hm( m_tbldata, m_strLineSep, 0 ); 

		m_i1 = 0;
		return m_i0>0 ? 1 : 0;
	}


	virtual tbool OnFetchRow( rowTYPE & _row )
	{
		_row.clear();
		if( m_i1 >= m_i0 ) return 0;

		if( m_strLineSep == "" )
		{
			_row.push_back( SStrvs::vsa_get( m_tbldata, m_env, 0 , m_i1 ) );
			m_i1++;
			return 1;
		}
		else
		{
			
			std::string s1 = SStrvs::vsa_get( m_tbldata, m_strLineSep, 1 , m_i1 );
			std::vector<std::string> vsss;
			SStrvs::vsa_imp( s1, m_env, 0, vsss );
			_row = vsss;
			m_i1++;
			return 1;
		}

	}


}; 



X011_NAMESPACE_END

#endif




X011_NAMESPACE_BEGIN



#ifndef V1_3AAFWEB02_TBL_T_20170622_133852
#define V1_3AAFWEB02_TBL_T_20170622_133852




class AFWEB02_tbl_t_rowtype {

public:

	SDte		m_TimeStamp;			
	int		m_FSA_FuncInt;			
	std::string		m_FSA_Func;			
	std::string		m_strTitle;			
	int		m_BigFontFlag;			
	tuint32		m_StepCount;			
	NaS2S		m_Value;			
	wl::tuint8		m_RES_01;			
	SDte		m_RES_02;			
	long		m_RES_03;			
	tuint64		m_RES_04;			
	uiarr_t<long,3>		m_RES_05;			

public:

	AFWEB02_tbl_t_rowtype()
	{
		m_TimeStamp.MakeNow();
		m_FSA_FuncInt = 0;
		m_FSA_Func = "";
		m_strTitle = "_----_";
		m_BigFontFlag = 0;
		m_StepCount = 0;
		
		m_RES_01 = 0;
		m_RES_02.MakeNow();
		m_RES_03 = 0;
		m_RES_04 = 0;
		
	}

	virtual ~AFWEB02_tbl_t_rowtype(){;}


	bool operator == (const AFWEB02_tbl_t_rowtype & rhs) const
	{
		return this == &rhs;
	}

	
	bool operator > (const AFWEB02_tbl_t_rowtype & rhs) const
	{
		return this > &rhs;
	}

	
	bool operator < (const AFWEB02_tbl_t_rowtype & rhs) const
	{
		return this < &rhs;
	}


protected:

	template< class T > T decode2( void *p )
	 { T x; memcpy( &x, p, sizeof(T) ); return x; }

	
	static void en( const char *src, long len, char *destbuf )
	{
		static char strHexPtr[] = "0123456789ABCDEF";
		char *pdest=destbuf;
		pdest[0]=pdest[1]=0;
		pdest[2]=0;pdest[3]=0;
		for( long i = 0; i<len; i++ )
		{
			
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

	
	std::string & Serialize( std::string & strOut )
	{
		strOut = "";
		const char *buf1;
		long len1;
		char *buf2;
		std::vector< char > v;
		buf1 = (const char *)reinterpret_cast<char *>(&static_cast<wl::SDte_bare&>(m_TimeStamp));
		len1 = sizeof(wl::SDte_bare);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_FSA_FuncInt));
		len1 = sizeof(m_FSA_FuncInt);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_FSA_Func.c_str();
		len1 = (long)(m_FSA_Func.length()*sizeof(char)+sizeof(char));
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_strTitle.c_str();
		len1 = (long)(m_strTitle.length()*sizeof(char)+sizeof(char));
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_BigFontFlag));
		len1 = sizeof(m_BigFontFlag);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_StepCount));
		len1 = sizeof(m_StepCount);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)m_Value.serialize_hold_addr();
		len1 = m_Value.serialize_hold_len();
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES_01));
		len1 = sizeof(m_RES_01);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&static_cast<wl::SDte_bare&>(m_RES_02));
		len1 = sizeof(wl::SDte_bare);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES_03));
		len1 = sizeof(m_RES_03);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES_04));
		len1 = sizeof(m_RES_04);
		if( (int)v.size() < ( len1 * 2 + 4 ) ) v.resize( len1 * 2 + 4 );
		buf2 = (char*)(&(v[0]));
		en( buf1, len1, buf2 );
		strOut += std::string(buf2);
		strOut += std::string("/");
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES_05));
		len1 = sizeof(m_RES_05);
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

	AFWEB02_tbl_t_rowtype & Unserialize( const char * strIn )
	{
		const char *buf1;
		char *buf2;
		buf1 = strIn;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  memcpy(reinterpret_cast<char *>(&static_cast<wl::SDte_bare&>(m_TimeStamp)),buf2,sizeof(wl::SDte_bare)); }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_FSA_FuncInt = *(int*)buf2; }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_FSA_Func = (char*)buf2; }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_strTitle = (char*)buf2; }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_BigFontFlag = *(int*)buf2; }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_StepCount = decode2<tuint32>(buf2); }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_Value.unserialize((char*)buf2); }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_RES_01 = *(wl::tuint8*)buf2; }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  memcpy(reinterpret_cast<char *>(&static_cast<wl::SDte_bare&>(m_RES_02)),buf2,sizeof(wl::SDte_bare)); }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_RES_03 = *(long*)buf2; }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_RES_04 = decode2<tuint64>(buf2); }else return *this;
		buf2 = (char*)buf1;
		 if( *buf2!='}') {buf1 = de( buf2 );
		  m_RES_05 = *(uiarr_t<long,3>*)buf2; }else return *this;
		return *this;
	}


#ifdef X014FASTSERI_

	wl::SCake & Serialize( wl::SCake & ckOut )
	{
		ckOut.redim(0);
		const char *buf1;
		wl::tuint32 len1;
		wl::SCakel ckl;
		buf1 = (const char *)reinterpret_cast<char *>(&static_cast<wl::SDte_bare&>(m_TimeStamp));
		len1 = sizeof(wl::SDte_bare);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_FSA_FuncInt));
		len1 = sizeof(m_FSA_FuncInt);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_FSA_Func.c_str();
		len1 = (long)(m_FSA_Func.length()*sizeof(char)+sizeof(char));
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_strTitle.c_str();
		len1 = (long)(m_strTitle.length()*sizeof(char)+sizeof(char));
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_BigFontFlag));
		len1 = sizeof(m_BigFontFlag);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_StepCount));
		len1 = sizeof(m_StepCount);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)m_Value.serialize_hold_addr();
		len1 = m_Value.serialize_hold_len();
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES_01));
		len1 = sizeof(m_RES_01);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&static_cast<wl::SDte_bare&>(m_RES_02));
		len1 = sizeof(wl::SDte_bare);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES_03));
		len1 = sizeof(m_RES_03);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES_04));
		len1 = sizeof(m_RES_04);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		buf1 = (const char *)reinterpret_cast<char *>(&reinterpret_cast<char&>(m_RES_05));
		len1 = sizeof(m_RES_05);
		ckl.add( wl::SCake( (wl::tchar*)&len1, 4 ) );
		ckl.add( wl::SCake( buf1, len1 ) );
		ckl.collectb();
		return ckOut=*ckl.get0();
	}

	AFWEB02_tbl_t_rowtype & Unserialize( wl::tchar * p_begin, wl::tchar ** pp_end )
	{
		char *buf1 = p_begin;
		char *buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_TimeStamp = memcpy(reinterpret_cast<char *>(&static_cast<wl::SDte_bare&>(buf2COL)),buf2,sizeof(wl::SDte_bare));
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_FSA_FuncInt = *(int*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_FSA_Func = (char*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_strTitle = (char*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_BigFontFlag = *(int*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_StepCount = decode2<tuint32>(buf2);
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_Value = buf2COL.unserialize((char*)buf2);
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES_01 = *(wl::tuint8*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES_02 = memcpy(reinterpret_cast<char *>(&static_cast<wl::SDte_bare&>(buf2COL)),buf2,sizeof(wl::SDte_bare));
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES_03 = *(long*)buf2;
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES_04 = decode2<tuint64>(buf2);
		buf2 = (char*)buf1 + 4;
		buf1 = buf2 + *(wl::tuint32*)buf1;
		m_RES_05 = *(uiarr_t<long,3>*)buf2;
		*pp_end = buf1;
		return *this;
	}


#endif


public:




	SDte & GetCol_TimeStamp(void)
	{
		return m_TimeStamp;
	}




	int & GetCol_FSA_FuncInt(void)
	{
		return m_FSA_FuncInt;
	}




	std::string & GetCol_FSA_Func(void)
	{
		return m_FSA_Func;
	}




	std::string & GetCol_strTitle(void)
	{
		return m_strTitle;
	}




	int & GetCol_BigFontFlag(void)
	{
		return m_BigFontFlag;
	}




	tuint32 & GetCol_StepCount(void)
	{
		return m_StepCount;
	}




	NaS2S & GetCol_Value(void)
	{
		return m_Value;
	}




	wl::tuint8 & GetCol_RES_01(void)
	{
		return m_RES_01;
	}




	SDte & GetCol_RES_02(void)
	{
		return m_RES_02;
	}




	long & GetCol_RES_03(void)
	{
		return m_RES_03;
	}




	tuint64 & GetCol_RES_04(void)
	{
		return m_RES_04;
	}




	uiarr_t<long,3> & GetCol_RES_05(void)
	{
		return m_RES_05;
	}


public:




	int GetColAmount()
	{
		return 12;
	}




	std::string GetColName( int iColNum )
	{
		if( iColNum == 0 )
		{
			return "TimeStamp";
		}
		if( iColNum == 1 )
		{
			return "FSA_FuncInt";
		}
		if( iColNum == 2 )
		{
			return "FSA_Func";
		}
		if( iColNum == 3 )
		{
			return "strTitle";
		}
		if( iColNum == 4 )
		{
			return "BigFontFlag";
		}
		if( iColNum == 5 )
		{
			return "StepCount";
		}
		if( iColNum == 6 )
		{
			return "Value";
		}
		if( iColNum == 7 )
		{
			return "RES_01";
		}
		if( iColNum == 8 )
		{
			return "RES_02";
		}
		if( iColNum == 9 )
		{
			return "RES_03";
		}
		if( iColNum == 10 )
		{
			return "RES_04";
		}
		if( iColNum == 11 )
		{
			return "RES_05";
		}
		return "";
	}




	int GetColNumber( std::string strColName )
	{
		if( strColName == "TimeStamp" )
		{
			return 0;
		}
		if( strColName == "FSA_FuncInt" )
		{
			return 1;
		}
		if( strColName == "FSA_Func" )
		{
			return 2;
		}
		if( strColName == "strTitle" )
		{
			return 3;
		}
		if( strColName == "BigFontFlag" )
		{
			return 4;
		}
		if( strColName == "StepCount" )
		{
			return 5;
		}
		if( strColName == "Value" )
		{
			return 6;
		}
		if( strColName == "RES_01" )
		{
			return 7;
		}
		if( strColName == "RES_02" )
		{
			return 8;
		}
		if( strColName == "RES_03" )
		{
			return 9;
		}
		if( strColName == "RES_04" )
		{
			return 10;
		}
		if( strColName == "RES_05" )
		{
			return 11;
		}
		return -1;
	}




	template<class STRINGT>
	STRINGT GetColStr( int iColNum )
	{
		if( iColNum == 0 )
		{
			return m_TimeStamp.ReadString();
		}
		if( iColNum == 1 )
		{
			return wl::SStrf::sltoa(m_FSA_FuncInt);
		}
		if( iColNum == 2 )
		{
			return m_FSA_Func;
		}
		if( iColNum == 3 )
		{
			return m_strTitle;
		}
		if( iColNum == 4 )
		{
			return wl::SStrf::sltoa(m_BigFontFlag);
		}
		if( iColNum == 5 )
		{
			return wl::SStrf::b2s(m_StepCount);
		}
		if( iColNum == 6 )
		{
			return m_Value.serialize();
		}
		if( iColNum == 7 )
		{
			return wl::SStrf::sltoa(m_RES_01);
		}
		if( iColNum == 8 )
		{
			return m_RES_02.ReadString();
		}
		if( iColNum == 9 )
		{
			return wl::SStrf::sltoa(m_RES_03);
		}
		if( iColNum == 10 )
		{
			return wl::SStrf::b2s(m_RES_04);
		}
		if( iColNum == 11 )
		{
			return wl::SStrf::b2s(m_RES_05);
		}
		return GetColStr<STRINGT>(0);
	}

	template<class STRINGT>
	STRINGT & GetColStr( int iColNum , STRINGT & sBuf ) { return sBuf = GetColStr<STRINGT>(iColNum); }




	template<class STRINGT>
	STRINGT GetColStr( std::string strColName )
	{
		if( strColName == "TimeStamp" )
		{
			return GetColStr<STRINGT>(0);
		}
		if( strColName == "FSA_FuncInt" )
		{
			return GetColStr<STRINGT>(1);
		}
		if( strColName == "FSA_Func" )
		{
			return GetColStr<STRINGT>(2);
		}
		if( strColName == "strTitle" )
		{
			return GetColStr<STRINGT>(3);
		}
		if( strColName == "BigFontFlag" )
		{
			return GetColStr<STRINGT>(4);
		}
		if( strColName == "StepCount" )
		{
			return GetColStr<STRINGT>(5);
		}
		if( strColName == "Value" )
		{
			return GetColStr<STRINGT>(6);
		}
		if( strColName == "RES_01" )
		{
			return GetColStr<STRINGT>(7);
		}
		if( strColName == "RES_02" )
		{
			return GetColStr<STRINGT>(8);
		}
		if( strColName == "RES_03" )
		{
			return GetColStr<STRINGT>(9);
		}
		if( strColName == "RES_04" )
		{
			return GetColStr<STRINGT>(10);
		}
		if( strColName == "RES_05" )
		{
			return GetColStr<STRINGT>(11);
		}
		return GetColStr<STRINGT>(0);
	}

	template<class STRINGT>
	STRINGT& GetColStr( std::string strColName, STRINGT & sBuf ) { return sBuf = GetColStr<STRINGT>(strColName); }




	template<class STRINGT>
	void SetColVal( int iColNum, STRINGT strValPARA )
	{
		if( iColNum == 0 )
		{
			m_TimeStamp.Make(strValPARA);
		}
		if( iColNum == 1 )
		{
			m_FSA_FuncInt=wl::SStrf::satol(strValPARA);
		}
		if( iColNum == 2 )
		{
			m_FSA_Func=strValPARA;
		}
		if( iColNum == 3 )
		{
			m_strTitle=strValPARA;
		}
		if( iColNum == 4 )
		{
			m_BigFontFlag=wl::SStrf::satol(strValPARA);
		}
		if( iColNum == 5 )
		{
			wl::SStrf::s2b(strValPARA,m_StepCount);
		}
		if( iColNum == 6 )
		{
			m_Value.unserialize(strValPARA);
		}
		if( iColNum == 7 )
		{
			m_RES_01=(wl::tuint8)wl::SStrf::satol(strValPARA);
		}
		if( iColNum == 8 )
		{
			m_RES_02.Make(strValPARA);
		}
		if( iColNum == 9 )
		{
			m_RES_03=wl::SStrf::satol(strValPARA);
		}
		if( iColNum == 10 )
		{
			wl::SStrf::s2b(strValPARA,m_RES_04);
		}
		if( iColNum == 11 )
		{
			wl::SStrf::s2b(strValPARA,m_RES_05);
		}
	}




	template<class STRINGT>
	void SetColVal( std::string strColName, STRINGT strValPARA )
	{
		if( strColName == "TimeStamp" )
		{
			SetColVal<STRINGT>(0,strValPARA);
		}
		if( strColName == "FSA_FuncInt" )
		{
			SetColVal<STRINGT>(1,strValPARA);
		}
		if( strColName == "FSA_Func" )
		{
			SetColVal<STRINGT>(2,strValPARA);
		}
		if( strColName == "strTitle" )
		{
			SetColVal<STRINGT>(3,strValPARA);
		}
		if( strColName == "BigFontFlag" )
		{
			SetColVal<STRINGT>(4,strValPARA);
		}
		if( strColName == "StepCount" )
		{
			SetColVal<STRINGT>(5,strValPARA);
		}
		if( strColName == "Value" )
		{
			SetColVal<STRINGT>(6,strValPARA);
		}
		if( strColName == "RES_01" )
		{
			SetColVal<STRINGT>(7,strValPARA);
		}
		if( strColName == "RES_02" )
		{
			SetColVal<STRINGT>(8,strValPARA);
		}
		if( strColName == "RES_03" )
		{
			SetColVal<STRINGT>(9,strValPARA);
		}
		if( strColName == "RES_04" )
		{
			SetColVal<STRINGT>(10,strValPARA);
		}
		if( strColName == "RES_05" )
		{
			SetColVal<STRINGT>(11,strValPARA);
		}
	}

}
;




class AFWEB02_tbl_t {

private:

	AFWEB02_tbl_t_rowtype m_EmptyRow;
	std::vector<AFWEB02_tbl_t_rowtype>  m_DATAcorpora;

public:

	typedef AFWEB02_tbl_t_rowtype 	ROWTYPE;
	typedef std::vector<long> 	RPSTYPE; 
	typedef std::vector<AFWEB02_tbl_t_rowtype>::iterator 	TBLITTYPE;

public:

	AFWEB02_tbl_t()
	{
	}

	virtual ~AFWEB02_tbl_t(){;}


	bool operator == (const AFWEB02_tbl_t & rhs) const
	{
		return this == &rhs;
	}

	
	bool operator > (const AFWEB02_tbl_t & rhs) const
	{
		return this > &rhs;
	}

	
	bool operator < (const AFWEB02_tbl_t & rhs) const
	{
		return this < &rhs;
	}


public:

	
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

	AFWEB02_tbl_t &  Unserialize( const char * strIn , int biAppend = 0 ) 
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

	AFWEB02_tbl_t & Unserialize( wl::SCake & ckIn , int biAppend = 0 )
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




	void Clear(void)
	{
		m_DATAcorpora.clear();
	}




	long GetRowCount( )
	{
		return (long)m_DATAcorpora.size();
	}




	long GetRowCount(const std::vector<long> & vRps)
	{
		return (long)vRps.size();
	}




	AFWEB02_tbl_t_rowtype & GetRow(long lRowNum)
	{
		if(lRowNum>=0&&lRowNum<(long)m_DATAcorpora.size())
		return m_DATAcorpora[lRowNum];
		else
		{
			AFWEB02_tbl_t_rowtype tmpEmptyrow;
			m_EmptyRow = tmpEmptyrow;
			return m_EmptyRow;
		}
	}




	AFWEB02_tbl_t_rowtype & GetRow(const std::vector<long> & vRps, long lRowNum)
	{
		long ltmp;
		do{
		{
			AFWEB02_tbl_t_rowtype tmpEmptyrow;
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




	void Add(const AFWEB02_tbl_t_rowtype & varRow)
	{
		m_DATAcorpora.push_back( varRow);
	}




	void AddDefaultRow()
	{
		Add( AFWEB02_tbl_t_rowtype());
	}




	void ReIdx()
	{
	}




	void DelInternal( long lRowNum )
	{
		if(!(lRowNum>=0&&lRowNum<(long)m_DATAcorpora.size())) return;
		m_DATAcorpora.erase( m_DATAcorpora.begin()+lRowNum);
	}




	void Del( long lRowNum )
	{
		AFWEB02_tbl_t * p = new AFWEB02_tbl_t;
		*p = *this;
		p->DelInternal(lRowNum);
		Clear();
		for( long i = 0; i < p->GetRowCount(); i++ ) Add( p->GetRow(i) );
		delete p;
	}




	void SelE_TimeStamp(SDte strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_TimeStamp==strVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_TimeStamp(SDte strVal)
	{
		std::vector<long> vRps ;
		SelE_TimeStamp( strVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_TimeStamp(SDte strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_TimeStamp(strVal, vRps, pRefRps);
	}




	void SelE_FSA_FuncInt(int iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_FSA_FuncInt==iVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_FSA_FuncInt(int iVal)
	{
		std::vector<long> vRps ;
		SelE_FSA_FuncInt( iVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_FSA_FuncInt(int iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_FSA_FuncInt(iVal, vRps, pRefRps);
	}




	void SelE_FSA_Func(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_FSA_Func==strVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_FSA_Func(std::string strVal)
	{
		std::vector<long> vRps ;
		SelE_FSA_Func( strVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_FSA_Func(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_FSA_Func(strVal, vRps, pRefRps);
	}




	void SelE_strTitle(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_strTitle==strVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_strTitle(std::string strVal)
	{
		std::vector<long> vRps ;
		SelE_strTitle( strVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_strTitle(std::string strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_strTitle(strVal, vRps, pRefRps);
	}




	void SelE_BigFontFlag(int iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_BigFontFlag==iVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_BigFontFlag(int iVal)
	{
		std::vector<long> vRps ;
		SelE_BigFontFlag( iVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_BigFontFlag(int iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_BigFontFlag(iVal, vRps, pRefRps);
	}




	void SelE_StepCount(tuint32 iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_StepCount==iVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_StepCount(tuint32 iVal)
	{
		std::vector<long> vRps ;
		SelE_StepCount( iVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_StepCount(tuint32 iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_StepCount(iVal, vRps, pRefRps);
	}




	void SelE_Value(NaS2S aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_Value==aVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_Value(NaS2S aVal)
	{
		std::vector<long> vRps ;
		SelE_Value( aVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_Value(NaS2S aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_Value(aVal, vRps, pRefRps);
	}




	void SelE_RES_01(wl::tuint8 iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES_01==iVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_RES_01(wl::tuint8 iVal)
	{
		std::vector<long> vRps ;
		SelE_RES_01( iVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_RES_01(wl::tuint8 iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_RES_01(iVal, vRps, pRefRps);
	}




	void SelE_RES_02(SDte strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES_02==strVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_RES_02(SDte strVal)
	{
		std::vector<long> vRps ;
		SelE_RES_02( strVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_RES_02(SDte strVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_RES_02(strVal, vRps, pRefRps);
	}




	void SelE_RES_03(long iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES_03==iVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_RES_03(long iVal)
	{
		std::vector<long> vRps ;
		SelE_RES_03( iVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_RES_03(long iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_RES_03(iVal, vRps, pRefRps);
	}




	void SelE_RES_04(tuint64 iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES_04==iVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_RES_04(tuint64 iVal)
	{
		std::vector<long> vRps ;
		SelE_RES_04( iVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_RES_04(tuint64 iVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_RES_04(iVal, vRps, pRefRps);
	}




	void SelE_RES_05(uiarr_t<long,3> aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		for(long ltmp=0;ltmp<(long)m_DATAcorpora.size();ltmp++)
		if(m_DATAcorpora[ltmp].m_RES_05==aVal)
		if( !pRefRps || ( !pRefRps->empty() && std::binary_search( pRefRps->begin(), pRefRps->end(), ltmp ) ) ) vRps.push_back( ltmp );
	}




	AFWEB02_tbl_t_rowtype & SelE1_RES_05(uiarr_t<long,3> aVal)
	{
		std::vector<long> vRps ;
		SelE_RES_05( aVal, vRps );
		return GetRow( vRps, 0 );
	}




	void SelEc_RES_05(uiarr_t<long,3> aVal, std::vector<long> & vRps, std::vector<long> * pRefRps=NULL) 
	{
		vRps.clear();
		SelE_RES_05(aVal, vRps, pRefRps);
	}




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




	RPSTYPE & RpsAnd( RPSTYPE & varRpsSource1, RPSTYPE & varRpsSource2, RPSTYPE & vRps3, int sort_flag = 0 )
	{
		if( (sort_flag & 2 ) == 0 ) std::sort( varRpsSource1.begin(), varRpsSource1.end() );
		if( (sort_flag & 1 ) == 0 ) std::sort( varRpsSource2.begin(), varRpsSource2.end() );
		vRps3.clear();
		std::set_intersection(
		 varRpsSource1.begin(), varRpsSource1.end(), varRpsSource2.begin(), varRpsSource2.end(), std::insert_iterator<RPSTYPE>(vRps3,vRps3.begin()) );
		return vRps3;
	}




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


#endif


#ifndef K1__AFWEB02_t_H
#define K1__AFWEB02_t_H


#define AFWEB02_NAMESPACE_BEGIN namespace AFWEB02	{
#define AFWEB02_NAMESPACE_END						}


AFWEB02_NAMESPACE_BEGIN





class AFlowData_t
{
public:
	AFWEB02_tbl_t_rowtype	 	m_env0;

public:
	AFlowData_t()
	{
		m_env0.m_BigFontFlag = 0; 
	}

	virtual ~AFlowData_t()
	{}

public:

};




class AFlowFolder_t
{
public:
	WCrsc	  m_AFLck;
	std::map< std::string, AFlowData_t* > m_datapool;
	int  m_iPurgeConfSec;

public:
	AFlowFolder_t()
	{
		m_iPurgeConfSec = 1234;
	}

	virtual ~AFlowFolder_t()
	{
	}

public:
	
	AFlowData_t * folder_takeout( std::string strSessionId )
	{
		WCrsc aLock( &m_AFLck );
		std::map< std::string, AFlowData_t* >::iterator it;

		it = m_datapool.find( strSessionId );

		if( strSessionId == "" || it == m_datapool.end() ) 
		{
			return NULL;
		}

		AFlowData_t * pdata = it->second;

		
		m_datapool.erase(it);

		return pdata;
	}

	
	tbool folder_put( std::string strSessionId, AFlowData_t * pdata )
	{
		if( strSessionId == "" ) return 0;
		if( pdata == NULL ) return 0;

		WCrsc aLock( &m_AFLck );

		AFlowData_t *p = pdata;
		m_datapool[strSessionId] = p;

		return 1;
	}

	
	tbool folder_del( std::string strSessionId )
	{
		WCrsc aLock( &m_AFLck );
		std::map< std::string, AFlowData_t* >::iterator it;

		it = m_datapool.find( strSessionId );

		if( it == m_datapool.end() ) 
		{
			return 0;
		}

		delete it->second;
		m_datapool.erase(it);

		return 1;
	}

	
	tbool folder_purge()
	{
		WCrsc aLock( &m_AFLck );
		std::map< std::string, AFlowData_t* >::iterator it;
		SDte dt;
		tbool rc(0);

		dt.MakeNow();

		for( it = m_datapool.begin(); it != m_datapool.end() ; )
		{
			if( dt.DiffSecInt( it->second->m_env0.m_TimeStamp ) > m_iPurgeConfSec )
			{
				delete it->second;

				
				m_datapool.erase(it);
				it = m_datapool.begin();

				rc = 1;
			}
			else
			{
				++it;
			}
		}

		return rc;
	}

};





class AFlowEle_t : public WThrd
{
public:
	tbool			m_tSvrGoodFlag;
	tbool			m_WebFormBeginDoneFlag;

	WTcpCells		m_tSvr;

public:
	AFlowFolder_t	*m_pFolder;
	AFlowData_t		*m_pafdata;

	WNava			m_nvHTTPGET;		
	std::string		m_SessionId;

	std::string  m_strHttpHead;
	std::string  m_strCmdLine1, m_strCmdVerb, m_strProtocolName, m_strAddr;
	std::string		m_strUPfn;	
	std::string  m_strUCmdLine; 

	SDte		m_dtnow;

public:
	AFlowEle_t()
	{
		m_tSvrGoodFlag = 1;
		m_WebFormBeginDoneFlag = 0;
	}

	virtual ~AFlowEle_t()
	{
		tr_destruct();
	}

public:

	
	void WebSendString( std::string strValue )
	{
		WebFormBegin();

		if( strValue.empty() ) return;

		if( m_tSvrGoodFlag )
		{
			m_tSvrGoodFlag = m_tSvr.send_str( strValue );
		}
	}


	void WebSendBlock( std::string content_type, const SCake &ck )
	{
		if( ck.len() == 0 ) return;

		std::string strOut;

		strOut = "HTTP/1.0 200 OK\r\n";
		strOut += "Server: NotApache/" + wl::SDte::GetNow().ReadStringPack() + "\r\n";
		strOut += "Cache-Control: no-cache\r\n";
		strOut += "Pragma: no-cache\r\n";

		
		strOut += content_type + "\r\n";

		strOut += "Content-Length: " + SStrf::sltoa( (int)ck.len() ) + "\r\n";
		strOut += "Connection: close\r\n";
		strOut += "\r\n";

		if( m_tSvrGoodFlag )
			m_tSvrGoodFlag = m_tSvr.send_str( strOut );

		if( m_tSvrGoodFlag )
			m_tSvrGoodFlag = m_tSvr.send_bin( ck );
	}

	
	void WebSendBlock( std::string content_type, SFile fl )
	{
		SCake ck;

		if( fl.exists() )
		{
			fl.read( ck );
			this->WebSendBlock( content_type, ck );
		}
	}

	
	void WebSendBlock( std::string content_type, std::string fn )
	{
		SFile fl;

		fl.bind( fn );

		this->WebSendBlock( content_type, fl );
	}


	static tchar bs_esc2(void)
	{  return '%'; }

	static std::string DeValue( std::string strValue )
	{
		SStrf::sreplstr( strValue, "+",  " " );
		return SStrf::bs_de( strValue, bs_esc2 );
	}

	static std::string Chg2XmlCode( std::string s )
	{
		if( s.empty() ) return "&nbsp;";
		return SStrf::Chg2XmlCode( s );
	}

	void AFMyDebug()
	{
		int i;
		i = 0;
	}

	
	std::string & STRVAR( const std::string & s )
	{
		return (m_pafdata->m_env0).m_Value[s];
	}

	
	std::string GETWEBINPUT( const std::string & sName )
	{
		return m_nvHTTPGET.get(sName);
	}

	
	std::string GETWEBINPUT_DE( const std::string & sName )
	{
		return DeValue(m_nvHTTPGET.get(sName));
	}

	
	std::string GETWEBINPUT_PrefixName( const std::string & sNameprefix )
	{
		for( std::map< std::string , std::string >::const_iterator it = m_nvHTTPGET.m_mapKnl.begin(); it != m_nvHTTPGET.m_mapKnl.end(); ++it )
		{
			if( it->first.find(sNameprefix) == 0 )
			{
				return it->first;
			}
		}
		return "";
	}

	
	std::string GETWEBINPUT_PrefixName_DE( const std::string & sNameprefix )
	{
		 return GETWEBINPUT_DE(GETWEBINPUT_PrefixName(sNameprefix));
	}


	virtual void tr_on_pre_thrd()
	{
		
	}

	virtual void tr_on_post_thrd()
	{
		
	}


	virtual void on_reset_fsa()
	{
		
		
	}

	virtual void on_restore_fsa()
	{
		
		
	}

	virtual void on_store_fsa()
	{
	}

	virtual tbool On_StaticFlow()
	{
		return 0;
	}


	virtual void On_flow()
	{
		std::vector< std::string > v1;
		std::vector< std::string > v2;

		v1.push_back( "m_tSvr.m_strRemoteIPAddress" );   v2.push_back( m_tSvr.m_strRemoteIPAddress );
		v1.push_back( "m_strHttpHead" );   		v2.push_back( m_strHttpHead );
		v1.push_back( "m_strCmdLine1" );   		v2.push_back( m_strCmdLine1 );
		v1.push_back( "m_strCmdVerb" );   		v2.push_back( m_strCmdVerb );
		v1.push_back( "m_strProtocolName" );   	v2.push_back( m_strProtocolName );
		v1.push_back( "m_strAddr" );   			v2.push_back( m_strAddr );
		v1.push_back( "m_strUPfn" );   			v2.push_back( m_strUPfn );
		v1.push_back( "m_dtnow.ReadString" );   v2.push_back( m_dtnow.ReadString() );
		v1.push_back( "m_strUCmdLine" );   		v2.push_back( m_strUCmdLine );

		WTcpHttp h;

		h.ImportSvrRtnHeadPara( m_strHttpHead );
		v1.push_back( "User-Agent" );  	v2.push_back( h.GetSvrRtnHeadParaVal( "User-Agent" ) );


		WebFormBegin( "Welcome to use AFWEB02 - " + m_dtnow.ReadString() );

		WebSendString( "built-in variable: " );

		
		WebSendString( "<table border=1 cellspacing=0 cellpadding=0 bordercolor=\"yellow\">\r\n" );

		for( int j = 0; j < (int)v1.size(); j++ )
		{
			WebSendString( "<tr>\r\n" );
			WebSendString( "<td>" );
			WebSendString( Chg2XmlCode(v1[j]) );
			WebSendString( "</td>" );
			WebSendString( "\r\n" );
			WebSendString( "<td>" );
			WebSendString( Chg2XmlCode(v2[j]) );
			WebSendString( "</td>" );
			WebSendString( "\r\n" );
			WebSendString( "</tr>\r\n" );
		}
		WebSendString( "</table>\r\n" );

		WebAddTextBox( "name1", "value1" );
		WebAddButt( "name2", "value2" );
	}


	virtual int tr_on_user_run()
	{
		SCake ckTmp;

		m_dtnow.MakeNow();

		
		m_tSvr.recv_ln( ckTmp, "\r\n\r\n" );
		ckTmp.mk_str(m_strHttpHead);
		WTcpHttp::GetLine1ParaFromHead( m_strHttpHead, m_strCmdLine1, m_strCmdVerb, m_strProtocolName, m_strAddr, m_strUPfn ); 

		m_strUCmdLine = SStrvs::vsa_get( m_strUPfn, std::string("?"), 1, 1 );
		m_nvHTTPGET.impconf( m_strUCmdLine, "&", "=", "" );


		if( On_StaticFlow() ) 
		{
			m_tSvr.DisConn();
			return 0;
		}

		m_SessionId = m_nvHTTPGET.get("sessionid");
		m_pFolder->folder_purge();

		m_pafdata = m_pFolder->folder_takeout( m_SessionId ); 	

		if( NULL == m_pafdata ) 
		{
			wl::SStrf::newobjptr( m_pafdata );

			m_SessionId = WFile::MkRUStr() + WFile::MkRUStr() + WFile::MkRUStr();
			m_pafdata->m_env0.m_TimeStamp = m_dtnow;
			on_reset_fsa();
		}
		else
		{
			m_pafdata->m_env0.m_TimeStamp = m_dtnow;
			on_restore_fsa();
		}

		

		m_pafdata->m_env0.m_StepCount ++;

		On_flow();

		on_store_fsa();	

		m_pFolder->folder_put( m_SessionId, m_pafdata );	

		WebFormEnd();
		m_tSvr.DisConn();

		return 0;
	}


	void WebFormBegin()
	{
		if( m_WebFormBeginDoneFlag == 0 )
		{
			m_WebFormBeginDoneFlag = 1;

			std::string str1;

			str1 = "HTTP/1.0 200 OK\r\n\r\n";
			str1 += "<html><head>\r\n";
			
			str1 += "<meta http-equiv=\"Content-Type\" content=\"application/xhtml+xml; charset=gb2312\"/>\r\n";
			str1 += "<meta  http-equiv=\"Expires\"   content=\"0\"/>\r\n";
			str1 += "<meta  http-equiv=\"Cache-Control\"   content=\"no-cache\"/>\r\n";
			str1 += "<meta  http-equiv=\"Pragma\"   content=\"no-cache\"/>\r\n";

			
			if( m_pafdata->m_env0.m_BigFontFlag )
			{
				str1 += "<style type=\"text/css\">*{font-size:41pt;}</style>";
			}
			else
			{
				
				
			}

			str1 += "<title>"+ m_pafdata->m_env0.m_strTitle +"</title>\r\n";

			str1 += "</head>\r\n";
			str1 += "<body>\r\n";

			str1 += "<form method=\"GET\">\r\n";
			str1 += "<p>\r\n";

			str1 += "<input type=\"hidden\" name=\"sessionid\" size=\"60\" value=\""+ m_SessionId +"\">\r\n";
			str1 += "<p>\r\n";

			WebSendString( str1 );
		}
	}


	void WebFormBegin( std::string strTitle )
	{
		m_pafdata->m_env0.m_strTitle = strTitle;
		WebFormBegin();
	}

	
	void WebFormEnd()
	{
		std::string str1;

		str1 += "</form>\r\n";
		str1 += "</body>\r\n";
		str1 += "</html>\r\n";

		WebSendString( str1 );
	}

	void WebAddBr() 
	{
		std::string sOut = "<br>\r\n";
		WebSendString( sOut );
	}

	void WebAddCr() 
	{
		std::string sOut = "<p></p>\r\n";
		WebSendString( sOut );
	}

	void WebAddHr() 
	{
		std::string sOut = "<hr/>\r\n";
		WebSendString( sOut );
	}

	void WebAddSpace( int i = 2 )
	{
		std::string sOut = "&nbsp;";
		for( int j = 0; j < i; j++ )
		{
			WebSendString( sOut );
		}
		WebSendString( "\r\n" );
	}

	void WebAddButt( std::string strName, std::string strValue )
	{
		std::string sOut = "<input class=\"btns\" type=\"submit\" value=\""+ strValue +"\" name=\""+ strName +"\">\r\n";
		WebSendString( sOut );
	}

	void WebAddTextBox( std::string strName, std::string strValue, int iSize = 20 )
	{
		std::string str1;
		std::string strSize20;

		strSize20 = SStrf::sltoa(iSize);

		if( strValue == "" )
		{
			str1 = "<input type=\"text\" name=\""+ strName +"\" size=\"" + strSize20 + "\">\r\n";
		}
		else
		{
			str1 = "<input type=\"text\" name=\""+ strName +"\" size=\""+ strSize20 +"\" value=\""+ strValue +"\">\r\n";
		}

		WebSendString( str1 );
	}

	void WebAddTextarea( std::string strName, std::string strValue, int rows = 3, int cols = 20 )
	{
		
		std::string str1;

		str1 = "<textarea rows=\"" + SStrf::sltoa(rows) + "\" name=\"" + strName + "\" cols=\"" + SStrf::sltoa(cols) + "\">" + strValue + "</textarea>\r\n";
		WebSendString( str1 );
	}

	void WebAddTable( NaS2S & content, int width, int height , tbool isHaveHeader = 0 ) 
	{
		std::string sS2SName;

		
		WebSendString( "<table border=1 cellspacing=0 cellpadding=0 bordercolor=\"yellow\">\r\n" );

		for( int y = 0; y < height; y++ )
		{
			WebSendString( "<tr>\r\n" );

			for( int x = 0; x < width; x++ )
			{
				sS2SName = SStrf::sltoa(x) + "-" + SStrf::sltoa(y);

				if( isHaveHeader && y== 0 )
				{
					
					WebSendString( "<td align=\"center\" ><b>" );
					WebSendString( Chg2XmlCode(content[sS2SName]) );
					WebSendString( "</b></td>" );
				}
				else
				{
					WebSendString( "<td>" );
					WebSendString( Chg2XmlCode(content[sS2SName]) );
					WebSendString( "</td>" );
				}
				WebSendString( "\r\n" );
			}

			WebSendString( "</tr>\r\n" );
		}

		WebSendString( "</table>\r\n" );
	}

	void WebAddTable2Begin()
	{
		WebSendString( "<table border=1 cellspacing=0 cellpadding=0 bordercolor=\"yellow\">\r\n" );
	}

	void WebAddTable2End()
	{
		WebSendString( "</table>\r\n" );
	}

	void WebAddTable2Row( std::vector< std::string > &r , tbool isHeader = 0 )
	{
		WebSendString( "<tr>\r\n" );

		for( std::vector< std::string >::iterator it = r.begin(); it != r.end(); ++it )
		{
			if( isHeader )
			{
				
				WebSendString( "<td align=\"center\" ><b>" );
				WebSendString( Chg2XmlCode(*it) );
				WebSendString( "</b></td>" );
			}
			else
			{
				WebSendString( "<td>" );
				WebSendString( Chg2XmlCode(*it) );
				WebSendString( "</td>" );
			}
			WebSendString( "\r\n" );
		}

		WebSendString( "</tr>\r\n" );
	}


	void WebAddTable2( std::vector< std::string > &v1 , std::vector< std::string > &v2 )
	{
		WebSendString( "<table border=1 cellspacing=0 cellpadding=0 bordercolor=\"yellow\">\r\n" );

		for( int j = 0; j < (int)v1.size(); j++ )
		{
			WebSendString( "<tr>\r\n" );

			WebSendString( "<td>" );
			WebSendString( Chg2XmlCode(v1[j]) );
			WebSendString( "</td>" );

			WebSendString( "\r\n" );

			WebSendString( "<td>" );
			WebSendString( Chg2XmlCode(v2[j]) );
			WebSendString( "</td>" );
			WebSendString( "\r\n" );

			WebSendString( "</tr>\r\n" );
		}
		WebSendString( "</table>\r\n" );
	}


};




template< class _T = AFlowEle_t >
class AFlowMgr_t : public WThrdMgr< _T, WThrd >
{
public:
	WTcpListener  m_Lsn;
	AFlowFolder_t  m_aFolder;

public:
	AFlowMgr_t()
	{
	}

	virtual ~AFlowMgr_t()
	{
		WThrd::tr_destruct();
	}

public:
	virtual tbool OnMgrPrepare( _T & t )
	{
		if( !t.m_tSvr.Conn( m_Lsn ) )
			return 0;

		t.m_pFolder = &m_aFolder;
		return 1;
	}

	static tbool NewFlow( int iPort = 3456, int iPurgeConfSec = 3456 )
	{
		AFlowMgr_t *p;
		p = new AFlowMgr_t;

		p->m_aFolder.m_iPurgeConfSec = iPurgeConfSec;

		if( p->m_Lsn.Listen((u_short)iPort) )
		{
			p->tr_openx();
			return 1;
		}

		return 0;
	}
};




class AWeb_t : public AFlowEle_t
{
public:

	
	
	
	

	virtual void On_flow()
	{
		On_flow2( &((m_pafdata->m_env0).m_FSA_FuncInt) );
	}

	virtual void On_flow2( int *pstate )
	{
		AFlowEle_t::On_flow();
	}




	
	
	
	
	

};





AFWEB02_NAMESPACE_END


#endif




X011_NAMESPACE_END



#pragma warning(pop)

#endif

#ifdef LINUENV_



#ifndef X011__H_w_sbase_h
#define X011__H_w_sbase_h


#define X011_NAMESPACE_BEGIN namespace wl {
#define X011_NAMESPACE_END                }


#include <iterator>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <vector>
#include <map>
#include <set>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include <sys/dir.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>  
#include <pthread.h>

#include <netdb.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <termios.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>

#include "iconv.h"

X011_NAMESPACE_BEGIN


typedef		double					tdouble; 
typedef		char					tint8;
typedef		unsigned char			tuint8;
typedef		short					tint16;
typedef		unsigned short			tuint16;
typedef		long					tint32;
typedef		unsigned long			tuint32;

typedef     long long               tint64;
typedef     unsigned long long      tuint64; 


typedef		tint8				tchar;
typedef		int					tbool;


typedef		tuint32			tsize;
typedef		tint32			toffset;


typedef unsigned long       DWORD;


X011_NAMESPACE_END


#define		SOCKET                int
#define		INVALID_SOCKET                (-1)
#define		closesocket                close
#define		SOCKET_ERROR            (-1)



#endif





#ifndef X011__H_w_SClib_h
#define X011__H_w_SClib_h




X011_NAMESPACE_BEGIN


class SClib
{

public:

	SClib(){;}

	~SClib(){;}

	typedef int (* PT_sscanf)( const char *buffer, const char *format , ... );
	static PT_sscanf p_sscanf() { return sscanf; }

	typedef int (* PT_sprintf)( char *, const char *, ... );
	static PT_sprintf p_sprintf() { return sprintf; }

	typedef int (* PT_vsprintf)( char *, const char *, va_list aaa );
	static PT_vsprintf p_vsprintf() { return vsprintf; }

	typedef char * (* PT_strcpy)( char *strDestination, const char *strSource );
	static PT_strcpy p_strcpy() { return strcpy; }


	typedef tm * (* PT_localtime)( const time_t * );
	static PT_localtime p_localtime() { return localtime; }

	typedef FILE * (* PT_fopen)( const char *filename, const char *mode );
	static PT_fopen p_fopen(){ return fopen; }


	static char * ltoaB( long _Val, char * _DstBuf, int _Radix)
	{
		if(_Radix==16)
			sprintf(_DstBuf, "%x",  (unsigned int)_Val);
		else
			sprintf(_DstBuf, "%ld", _Val);

		return _DstBuf;
	}

	typedef char * (* PT_ltoa)( long value, char *str, int radix );
	static PT_ltoa p_ltoa() { return ltoaB; }


}; 




X011_NAMESPACE_END


#endif






#ifndef X011__H_w_sstrf_h
#define X011__H_w_sstrf_h


X011_NAMESPACE_BEGIN


class SStrf
{

public:

	
	
	 ~SStrf(){;}

	
	template < class T >
	static T * AddressOf( T & obj )
	{
		return reinterpret_cast<T *>(&reinterpret_cast<char&>(obj));
	}

	
	template< class T >
	static T * newobjptr( T * & p )
	{
		try
		{
			p = new T;
		}
		catch(...)
		{
			p = NULL;
		}

		return p;
	}

	
	template< class T >
	static T * newobjptr()  
	{
		T *  p;
		return newobjptr(p);
	}

	
	static void * smalloc( tsize i )
	{
		return malloc( i );
	}

	
	static void sfree(void *s)
	{
		free(s);
	}


	static tuint16 smkU16( tuint8 c1, tuint8 c2) 
	{
	   tuint16 ilow,ihigh;
	   ilow =  (tuint16)c1;
	   ihigh = (tuint16)c2;
	   ihigh <<= 8;
	   return ihigh + ilow;
	}


	template< class INTData_T >
	static INTData_T MkBlock2INTDataMem( const void *pBlock , tbool Ischgendian = 0 )
	{
		 INTData_T x;
		 memcpy( &x, pBlock, sizeof(INTData_T) );
		if( Ischgendian ) chgendian( x );
		 return x;
	}

	
	template< class INTData_T >
	static INTData_T & MkBlock2INTDataRef( const void *pBlock, INTData_T & x , tbool Ischgendian = 0 )
	{
		 memcpy( &x, pBlock, sizeof(INTData_T) );
		if( Ischgendian ) chgendian( x );
		 return x;
	}

	
	template< class INTData_T >
	static char * MkINTData2BlockMem( const void *pINTData, char *pBlockOut , tbool Ischgendian = 0 )
	{
		if( !Ischgendian ) 
		{
			 memcpy( pBlockOut, pINTData, sizeof(INTData_T) );
			 return pBlockOut;
		}

		
		INTData_T x;
		memcpy( &x, pINTData, sizeof(INTData_T) );
		chgendian( x );
		return MkINTData2BlockMem<INTData_T>( &x, pBlockOut, 0 );
	}

	
	template< class INTData_T >
	static char * MkINTData2BlockRef( const INTData_T &a, char *pBlockOut , tbool Ischgendian = 0 )
	{
		const void *pINTData = &a;
		return MkINTData2BlockMem<INTData_T>( pINTData, pBlockOut, Ischgendian );
	}


	static tbool is_little_endian()
	{
		tuint32 i = 1;
		char *p = (char*)(&i);
		return *p ? 1 : 0;
	}


	template< class T >
	static T & chgendian( T & val )
	{
		if( sizeof(T) != 1 ) srev( (tchar *)&(val), sizeof(T) );
		return val;
	}

	
	template< class T >
	static T chgendian2( T val )
	{
		return chgendian(val);
	}


	
	
	
	
	static tbool readbit_s( void * pbin, int iBytesLen, int sufx )
	{
		if( sufx < 0 || iBytesLen <= 0 || (sufx / 8) >= iBytesLen )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		
		iOffset =  (sufx % 8);

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}


	static tbool readbit_r_s( void * pbin, int iBytesLen, int sufx )
	{
		if( sufx < 0 || iBytesLen <= 0 || (sufx / 8) >= iBytesLen )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		iOffset = 7 - (sufx % 8); 
		

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}


	static tbool readbit_p( void * pbin, int sufx )
	{
		if( sufx < 0 )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		
		iOffset =  (sufx % 8);

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}


	static tbool readbit_r_p( void * pbin, int sufx )
	{
		if( sufx < 0 )
		{
			return 0;
		}

		tuint8 * pbin2 = (tuint8 *)pbin;
		tuint8 cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		iOffset = 7 - (sufx % 8); 
		

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;
		return cSrc;
	}


	template<class T>
	static tbool readbit( T bindata , int sufx )  
	{
		return readbit_s( &bindata, (int)sizeof(T), sufx );
	}


	template<class T>
	static tbool readbit_r( T bindata , int sufx )  
	{
		return readbit_r_s( &bindata, (int)sizeof(T), sufx );
	}


	
	static void writebit( void * pbin , int sufx , tbool val )
	{
		if( sufx < 0 )
		{
			return ;
		}

		val = val?1:0;

		tuint8 * pbin2 = (tuint8 *)pbin;
		int cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		
		iOffset = (sufx % 8);

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;

		if( cSrc == val ) return ;

		int i = 1;
		i <<= iOffset;

		pbin2[sufx / 8] ^= i;
	}


	static void writebit_r( void * pbin , int sufx , tbool val )
	{
		if( sufx < 0 )
		{
			return ;
		}

		val = val?1:0;

		tuint8 * pbin2 = (tuint8 *)pbin;
		int cSrc;
		int iOffset ;

		cSrc = pbin2[sufx / 8];

		iOffset = 7 - (sufx % 8);
		

		if(iOffset) cSrc >>= iOffset;
		cSrc &= 1;

		if( cSrc == val ) return ;

		int i = 1;
		i <<= iOffset;

		pbin2[sufx / 8] ^= i;
	}


	static void writebit_s( void * pbin, int iBytesLen, int sufx , tbool val )
	{
		if( sufx < 0 || iBytesLen <= 0 || (sufx / 8) >= iBytesLen )
		{
			return;
		}
		writebit( pbin, sufx , val );
	}


	
	template<class T> 
	static std::string & byte2binstr( T c, std::string & strrtn )
	{
		strrtn = "01234567";
		for( int i = 0; i < 8; i++ ) strrtn[i] = readbit( c, i ) ? '1' : '0' ;
		return strrtn;
	}

	
	template<class T> 
	static std::string byte2binstr( T c )
	{
		std::string str;
		return byte2binstr( c, str );
	}

	
	template<class T> 
	static T & binstr2byte( std::string str, T & c )
	{
		
		str += "00000000";
		for( int i = 0; i < 8; i++ ) writebit( &c, i , str[i]=='0' ? 0 : 1 );
		return c;
	}

	
	static tuint8 binstr2byte( std::string str )
	{
		tuint8 c;
		return binstr2byte( str, c );
	}


	static void initrand( int seed = 0 ) 
	{
		tint32 j=(tint16)(0x0555&(time(0)*seed));
		for(tint32 i=0;i<j;++i) rand();
	}

	
	static tdouble rand1( int iShouldInitSeed = 0 )
	{
		if( iShouldInitSeed ) initrand( iShouldInitSeed );
		return (tdouble)rand()/(tdouble)RAND_MAX;
	}

	
	static void * randfill( void *dest, tsize count )
	{
		unsigned char *p = (unsigned char *)dest;
		for( tsize j = 0; j < count; j++ )
		{
			p[j] = (unsigned char)(rand() & 0xFF );
		}
		return dest;
	}

	
	template< class T >
	static void * randfill( T & dest )
	{
		return randfill( &dest, sizeof(T) );
	}


	static void *smemcpy( void *dest, const void *src, tsize count )
	{
		return memcpy(dest,src,count);
	}

	
	static void * smemset( void *dest, tuint8 c, tsize count )
	{
		return memset( dest, (int)c, (size_t)count );
	}

	
	template< class T >
	static void * smemset( T & dest, tuint8 c = 0 )
	{
		return memset( &dest, (int)c, sizeof(T) );
	}


	static tchar * scpy( tchar *strDestination, const tchar *strSource )
	{
		return (*SClib::p_strcpy())( strDestination, strSource );
	}

	
	static tsize slen( const tchar * s ) 
	{
		if(s==NULL) return (tsize)0;
		return (tsize)strlen(s);
	}

	
	static tbool sishex(tchar c)
	{
		return  (c>='0'&&c<='9')||(c>='A'&&c<='F')||(c>='a'&&c<='f');
	}

	
	static tbool sishex(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sishex(*s)) return 0;
		return 1;
	}

	
	static tbool sisdec(tchar c) 
	{
		return  (c>='0'&&c<='9');
	}

	
	static tbool sisdec(const tchar *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!sisdec(*s)) return 0;
		return 1;
	}

	
	static tbool sisalpha(char c) 
	{
		return sisdec(c) || (c>='A'&&c<='Z')|| (c>='a'&&c<='z');
	}


	static tchar *sltoa( tint32 i, tchar *buf, int radix = 10 )
	{
		return (*SClib::p_ltoa())(i, buf, radix);
	}

	
	static std::string sltoa( tint32 i, int radix = 10 )
	{
		tchar c[55];
		std::string buf;
		buf = sltoa( i, c, radix );
		return buf;
	}

	
	static tint32 satol( const tchar *s ) { return(s==NULL)?0:(tint32)atol(s); }

	
	static tint32 satol( const std::string & s ) { return satol(s.c_str()); }

	
	static tint32 satol_16( std::string s )
	{
		tint32 ii;
		(SClib::p_sscanf())( s.c_str(), "%x", &ii );
		return ii;
	}


	static std::string sultoa( tuint32 i )
	{
		std::stringstream stream;
		stream << i;
		return stream.str();
	}


	static std::string sultoa_h( std::string s1 )
	{
		if( s1.size() <= 3 ) 
		{
			return s1.c_str();
		}

		if( s1.size() <= 6 ) 
		{
			s1.insert( s1.begin() + ( s1.size() - 3 ), '.' );
			s1[ ( s1.size() - 3 ) + 1 ] = 'K';
			s1[ ( s1.size() - 3 ) + 2 ] = 0;
			return s1.c_str();
		}

		
		{
			s1.insert( s1.begin() + ( s1.size() - 6 ), '.' );
			s1[ ( s1.size() - 6 ) + 1 ] = 'M';
			s1[ ( s1.size() - 6 ) + 2 ] = 0;
			return s1.c_str();
		}
	}

	
	static std::string sultoa_h( tuint32 i )
	{
		return sultoa_h( sultoa(i) );
	}


	
	static tuint32 satoul( std::string s )
	{
		return strtoul( s.c_str(), NULL, 10 );
	}

	
	static tuint32 satoul_16( std::string s )
	{
		return strtoul( s.c_str(), NULL, 16 );
	}

	
	static tuint32 satoul_x( std::string s )
	{
		return strtoul( s.c_str(), NULL, 0 );
	}


	static std::string GetBcdStr( tuint8 c1 )
	{
		char s[11];
		(*SClib::p_sprintf())( s, "%02X", (unsigned int)c1 );
		return s;
	}

	
	static std::string GetBcdStr2Str( std::string s1 )
	{
		return GetBcdStr( (tuint8)satol(s1) );
	}

	
	
	
	
	


	static tuint8 GetBcdInt( tuint8 c1 ) 
	{
		return (tuint8)satol(GetBcdStr(c1));
	}

	
	static tuint8 Num2Bcd( tuint8 c1 )
	{
		tint32 ii;
		char s[11];
		(*SClib::p_sprintf())( s, "%d", (unsigned int)c1 );
		(SClib::p_sscanf())( s, "%x", &ii );
		return (tuint8)ii;
	}


	static tchar * sftoa( tdouble f , tchar * buf , int decimal_digits = -1 )
	
	{
		std::string s1;

		if( decimal_digits < 0 )
		{
			s1 = "%f";
		}
		else
		{
			s1 = "%." + sltoa(decimal_digits) + "f";
		}

		(*SClib::p_sprintf())( buf, s1.c_str(), f );

		return buf;
	}

	
	static std::string sftoa( tdouble f , int decimal_digits = -1 )
	{
		if( decimal_digits < -1 ) decimal_digits = -1;

		std::vector<char> v( 66 + decimal_digits );
		tchar * c;

		c = &(v[0]);
		return  sftoa( f, c , decimal_digits );
	}

	
	static tdouble satof( const tchar *s )
	{
		if(s==NULL) return 0.0;
		return (tdouble)atof(s);
	}

	
	static tdouble satof( const std::string & s )
	{
		return satof(s.c_str());
	}

	
	static int scmpi( const tchar *a, const tchar *b )	
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		toffset i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i];i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z') c1+=('A'-'a');
			if(c2>='a'&&c2<='z') c2+=('A'-'a');
			if(c1!=c2) return c1-c2;
		}
		return t1[i]-t2[i];
	}

	
	static int scmpin( const tchar *a, const tchar *b, tsize count ) 
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		const tchar *t1;
		const tchar *t2;
		tchar c1, c2;
		tsize i;
		t1 = a;
		t2 = b;
		for( i=0;t1[i]&&t2[i]&&i<count;i++ )
		{
			c1=t1[i]; c2=t2[i];
			if(c1>='a'&&c1<='z')c1+=('A'-'a');
			if(c2>='a'&&c2<='z')c2+=('A'-'a');
			if(c1!=c2)return c1-c2;
		}
		if(i>0) i--;
		return t1[i]-t2[i];
	}


	static int scmpin( const tchar *a, const tchar *b ) 
	{
		return scmpin(a,b,slen(b));
	}



	static int scmpn( const tchar *a, const tchar *b, tsize count )
	{
		if(!count) return 0; 
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1; 
		if(a!=NULL&&b==NULL) return 1;  
		return strncmp(a,b,count);
	}


	static int scmpn( const tchar *a, const tchar *b ) 
	{
		return scmpn(a,b,slen(b));
	}



	static int scmp( const tchar *a, const tchar *b )
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		return strcmp(a,b);
	}


	static tchar * sucase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='a'&&s[i]<='z')s[i] = s[i] -'a' + 'A' ;
		}
		return s;
	}


	static std::string & sucase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		sucase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}


	static tchar * slcase( tchar *s )
	{
		toffset i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='A'&&s[i]<='Z')s[i] = s[i] -'A' + 'a' ;
		}
		return s;
	}


	static std::string & slcase( std::string & str )
	{
		tchar * szstr;
		szstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( szstr, str.c_str() );
		slcase( szstr );
		str = szstr;
		sfree( szstr );
		return str;
	}


	
	
	template< class Pchar_CPchar_T >	
	static Pchar_CPchar_T splast( Pchar_CPchar_T s, toffset offset2left = 0  )
	{
		Pchar_CPchar_T t = s;
		if(!s||!*s) return t; 
		toffset i,j ;
		j = (toffset)slen(s);
		i = j - 1 - offset2left ;
		t=s+(i<0?0:i);
		return t;
	}

	
	template< class Pchar_CPchar_T >
	static Pchar_CPchar_T splast( Pchar_CPchar_T s, tsize uiLen, toffset offset2left  )
	{
		Pchar_CPchar_T t = s;
		if(!s||!*s) return t; 
		toffset i,j ;
		j = (toffset)uiLen;
		i = j - 1 - offset2left ;
		t=s+(i<0?0:i);
		return t;
	}


	static const tchar * sstr( const tchar * s, const tchar *substr )
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (const tchar *)strstr(s,substr);
	}

	
	static tchar * sstr( tchar * s, const tchar *substr )
	{
		if(!s||!substr||!(*s)||!(*substr)) return NULL;
		return (tchar *)strstr(s,substr);
	}

	
	template< class Pchar_CPchar_T >
	static Pchar_CPchar_T sstr( Pchar_CPchar_T s, tchar subc )
	{
		tchar t[2];
		t[0]=subc;
		t[1]=0;
		return sstr(s,t) ;
	}




	static tchar * srev( tchar * s, tsize len )
	{
		tsize u;
		toffset  x, y, i, a, b;
		u = len;
		u >>= 1;
		x = u;
		y = (toffset)len - 1;
		for(i=0;i<x;i++) {
			a = i;
			b = y - i;
			s[a] ^= s[b];
			s[b] ^= s[a];
			s[a] ^= s[b];
		}
		return s;
	}

	
	static tchar *srev( tchar * s )
	{
		return srev(s,slen(s));
	}

	
	static tchar * sreplch( tchar * source, tsize len, tchar c1, tchar c2 )	
	{
		tsize i;
		for(i=0;source&&i<len;i++) {
			if(source[i]==c1) source[i]=c2;
		}
		return source;
	}


	static tchar * sreplch( tchar * source, tchar c1, tchar c2 )	
	{
		return sreplch(source, slen(source), c1, c2);
	}


	static std::string & sreplstr( std::string & str, const tchar *string_to_replace, const tchar *new_string )
	{
		if( string_to_replace && new_string )
		{
			
			std::string::size_type   index   =   str.find(string_to_replace);
			
			while(index   !=   std::string::npos)
			{
				
				str.replace(index,   strlen(string_to_replace),   new_string);
				
				index   =   str.find(string_to_replace,   index   +   strlen(new_string));
			}
		}
		return   str;
	}


	static std::string & sreplstr( std::string & str, const std::string & string_to_replace, const std::string & new_string )
	{
		return sreplstr( str, string_to_replace.c_str(), new_string.c_str() ) ;
	}

	
	
	
	

	
	

	
	static std::string Chg2XmlCode( std::string s )
	{
		sreplstr( s, "&",  "&amp;"  );
		sreplstr( s, "<",  "&lt;"   );
		sreplstr( s, ">",  "&gt;"   );
		sreplstr( s, " ",  "&nbsp;"  );
		sreplstr( s, "\"", "&quot;"  );
		return s;
	}


	

	static std::string & str_trim_base( tchar *(*f)( tchar *, const tchar * ), std::string & str, const tchar *str_space="\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = (*f)( pstr, str_space );
		sfree( pstr );
		return str;
	}



	static tchar * strimr( tchar * s, tchar a_space ) 
	{
		toffset i;
		for(i=slen(s)-1;i>=0;i--)
			if(s[i]==a_space)
				s[i]=0;
			else
				break;
		return s;
	}

	static tchar * strimr( tchar * s, const tchar *str_space="\r\n \t" ) 
	{
		toffset i;
		for( i=slen(s)-1; i >= 0; i-- )
			if( sstr(str_space,s[i]) != NULL )
				s[i]=0;
			else
				break;
		return s;
	}

	static std::string & strimr( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strimr, str, str_space );
	}



	static tchar * striml( tchar * s, tchar a_space )	
	{
		return srev( strimr(srev(s), a_space) ) ;
	}

	static tchar * striml( tchar * s, const tchar * str_space = "\r\n \t" )		
	{
		return srev( strimr(srev(s), str_space) ) ;
	}

	static std::string & striml( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		tchar * pstr;
		pstr = (tchar *)smalloc( (tsize)str.size() + 1 );
		scpy( pstr, str.c_str() );
		str = striml( pstr, str_space );
		sfree( pstr );
		return str;
	}



	static tchar * strim( tchar * s, tchar a_space  ) 
	{
		return  striml( strimr(s,a_space), a_space) ;
	}

	static tchar * strim( tchar * s, const tchar * str_space = "\r\n \t" ) 
	{
		return  striml( strimr(s,str_space), str_space) ;
	}

	static std::string & strim( std::string & str, const tchar * str_space = "\r\n \t" )
	{
		return str_trim_base( strim , str, str_space );
	}

	


	static tchar * sleft( tchar * s, tsize n ) 
	{
		if(n>slen(s)) return s;
		s[n]=0;
		return s;
	}


	static tchar * sright( tchar * s, tsize n )
	{
		return srev(sleft(srev(s), n));
	}


	static tchar * smid( tchar * s, tsize a_pos, tsize a_len )
	{
		sright(s, slen(s) - a_pos );
		sleft(s, a_len);
		return s;
	}


	static const tchar * seq_dirno()
	{
		return "0123456789ACEFHKLMPQSTUWXYZ"; 
	}


	static std::string seq( std::string strCurNum, tbool isFixLen = 1, const tchar * s_symbset = NULL )
	{
		static tchar c[1];
		tchar * s_num;
		tint16 *lia ;
		tint16 ulia;
		tint32 i,j,k;

		c[0]=0;
		if(slen(s_symbset)<2) s_symbset = seq_dirno();
		s_num = (tchar*)smalloc( (tsize)strCurNum.size() + 2 );
		if(!s_num) return "";

		scpy( s_num, strCurNum.c_str() );

		lia = (tint16 *)smalloc( (slen(s_num) + 1)*sizeof(tint16) );
		if(!lia)
		{
			sfree(s_num);
			return "";
		}

		if(!(*s_num)) {
			s_num[0]=s_symbset[0];
			s_num[1]=0;
		}

		j = slen(s_num) ;
		for(i=0;i<j;i++)
		{
			const char *t = sstr( s_symbset, s_num[i] );
			if(!t)
				lia[i] = 0;
			else
				lia[i] = (tint16)( t - s_symbset );
		}

		lia[j-1] ++;
		k = slen(s_symbset) ;
		ulia = 0;
		for(i=j-1;i>=0;i--)
		{
			if(lia[i] >= k)
			{
				lia[i] -= (tint16)k;
				if(i>0)
					lia[i-1]++;
				else
					ulia++;
			}
		}

		for( i=0;i<j;i++ )
		{
			s_num[i] = s_symbset[ lia[i] ];
		}

		if( (!isFixLen) && ulia )	
		{
			srev(s_num);
			s_num[j] = s_symbset[ulia];
			s_num[j+1] = 0;
			srev(s_num);
		}

		strCurNum = s_num;
		sfree(s_num);
		sfree(lia);
		return strCurNum;
	}



	static tchar bs_esc() { return 'b'; }


	static tbool bs_inset( tchar c ) 
	{
		if(c==bs_esc()) return 0; 
		if(c>='a'&&c<='z') return 1;
		if(c>='0'&&c<='9') return 1;
		if(c>='A'&&c<='Z') return 1;
		return 0;
	}


	static tsize bs_ensize( const tchar *s, tsize len )
	{
		tsize i;
		tchar *t1, *t2, *t3;
		if(s==NULL) return 0;
		i=0;
		t1=(tchar*)s;
		t3=t1+len;
		for( t2=t1; t2<t3; t2++ )
			i += bs_inset(*t2)?(1*sizeof(tchar)):(3*sizeof(tchar));

		return i+(sizeof(tchar)); 
	}


	static tsize bs_ensize( const tchar *s )
	{
		return bs_ensize( s, slen(s) + 1 );
	}


	static tchar * bs_en( const tchar *s, tsize len, tchar *destbuf )
	{
		tchar *ss1, *ss2, *ss3, *sd1;
		tbool rc;
		int l;
		if(s==NULL||destbuf==NULL) return NULL;
		ss1 = (tchar*)s;
		ss3 = ss1 + len;
		sd1 = destbuf;

		for( ss2=ss1; ss2<ss3; ss2++)
		{
			rc = 0;

			do 
			{
				if( !bs_inset(*ss2) ) 
				{
					rc = 1;
					break;
				}

				*sd1 = *ss2;         
				sd1++;

			}while(0);

			if(rc) {    
				l = (tuint8)(*ss2);
				(*SClib::p_sprintf())( sd1, "%c%02X", bs_esc(), l );
				sd1 += (3*sizeof(tchar));
			}
		}
		*sd1=0;
		return destbuf;
	}


	static tchar * bs_en( const tchar *s, tchar *destbuf )
	{
		return bs_en( s, slen(s) + 1, destbuf );
	}

	static std::string  & bs_en( std::string & strData ) 
	{
		std::string s1( 3 + bs_ensize( strData.c_str(), (tsize)strData.length() ) , 'a' );

		bs_en( strData.c_str(), &(s1[0]) );

		return strData = s1.c_str();
	}

	
	static std::string  & bs_de( std::string & strData , tchar(*apf1)()=bs_esc )
	{
		std::string s1( strData );

		s1 += (*apf1)( ); 
		s1 += "00123";

		strData += (*apf1)( ); 
		strData += "00123";

		bs_de( strData.c_str(), &(s1[0]) , apf1 );

		return strData = s1.c_str();
	}

	
	static tsize bs_desize( const tchar *s , tchar(*apf1)()=bs_esc )
	{
		toffset j,i;
		tsize  k;
		if(s==NULL) return 0;

		for( i=0,j=(toffset)slen(s),k=0;i<j; )
			if(	(i+2<j)				&&
				s[i]==(*apf1)( )	&&
				sishex(s[i+1])		&&
				sishex(s[i+2])  )
			{
				k++;
				i+=3;
			}
			else
			{
				i++;
				k++;
			}
		return k;
	}

	
	static tchar * bs_de( const tchar *s, tchar *dest , tchar(*apf1)()=bs_esc ) 
	{
		if(s==NULL||dest==NULL) return dest;
		toffset i,j,k;
		toffset a1,a2;
		tchar ss[2];
		ss[1]=0;

		for(i=0,j=(toffset)slen(s),k=0;i<j; ) {
			if(	(i+2<j)			&&
				s[i]==(*apf1)( )&&
				sishex(s[i+1])	&&
				sishex(s[i+2])	 )
			{
				ss[0]=s[i+1];
				sucase(ss);
				a1 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) * 16 ;

				ss[0]=s[i+2];
				sucase(ss);
				a2 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) ;

				*(tchar *)(dest+k) = (tuint8)(a1+a2);
				k++;
				i+=3;
			}else{
				dest[k] = s[i];
				k++;
				i++;
			}
		}

		return dest;
	}


	static tchar * bs_de( tchar *source_dest , tchar(*apf1)()=bs_esc ) 
	{
		return bs_de(source_dest,source_dest,apf1);
	}


	static std::string b2s( void *p, long len )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( len * 3 + 12 );
		bs_en( (const char *)p, len, szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
	}

	
	template< class T >
	static std::string b2s(  T & sourcedata )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( sizeof(T) * 3 + 12 );
		bs_en( (const char *)reinterpret_cast<const char *>(&reinterpret_cast< const char& >(sourcedata)), sizeof(T), szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
	}

	
	template< class T >
	static std::string b2s_i( T sourcedata )
	{
		return b2s(sourcedata);
	}

	
	template< class T >
	static std::string b2s_const( const T & sourcedata )
	{
		return b2s_i(sourcedata);
	}

	
	template< class T >
	static T & s2b( std::string strSource, T & destdata )
	{
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}


	template< class T >
	static T s2b( std::string strSource )
	{
		T destdata;
		bs_de( strSource.c_str(), reinterpret_cast<tchar *>(&reinterpret_cast<char& >(destdata))  );
		return destdata;
	}


	#if 1
	

	template < class T >
	static T & mkint( T & _out, tuint8 *p1, int len, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		if( biIsIntel )
		{
			tuint8 *p2 = (tuint8 *)&_out;
			int i,j,k,x,signflag;
			j = (int)(sizeof(T)<=len?sizeof(T):len);
			k = (int)sizeof(T);
			signflag = biHaveSign && (p1[len-1] & (tuint8)0x80);
			
			for( i = 0 ; i < j; i++ )
			{
				if( signflag && i == j - 1 && j != k )
					p2[i] = p1[i]; 
				else
					p2[i] = p1[i];
			}
			
			for( x=i; x < k; x++ ) 
			{
				if( signflag )
					p2[x] = (tuint8)0xff;
				else
					p2[x] = (tuint8)0;
			}
		} 
		else
		{
			srev( (tchar *)p1, len );
			mkint( _out, p1, len, 1, biHaveSign );
			srev( (tchar *)p1, len ); 
			chgendian(_out);
		} 

		return _out;
	}

	
	template<class T> static T & mkint( T & _out, tuint8 c1, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		tuint8 c[4];
		c[0] = (tuint8)c1;
		return mkint( _out, c, 1, biIsIntel, biHaveSign );
	}
	
	template<class T> static T & mkint( T & _out, tuint8 c1, tuint8 c2, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		tuint8 c[4];
		c[0] = (tuint8)c1; c[1] = (tuint8)c2;
		return mkint( _out, c, 2, biIsIntel, biHaveSign );
	}
	
	template<class T> static T & mkint( T & _out, tuint8 c1, tuint8 c2, tuint8 c3, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		tuint8 c[4];
		c[0] = (tuint8)c1; c[1] = (tuint8)c2; c[2] = (tuint8)c3;
		return mkint( _out, c, 3, biIsIntel, biHaveSign );
	}
	
	template<class T> static T & mkint( T & _out, tuint8 c1, tuint8 c2, tuint8 c3, tuint8 c4, tbool biIsIntel = 1, tbool biHaveSign = 1 )
	{
		tuint8 c[4];
		c[0] = (tuint8)c1; c[1] = (tuint8)c2; c[2] = (tuint8)c3; c[3] = (tuint8)c4;
		return mkint( _out, c, 4, biIsIntel, biHaveSign );
	}

	
	#endif


	#if 0
	static unsigned char mk_chksumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += sz1[j];

		sz1[iLen-1] = c1;

		return 1;
	}

	static unsigned char chk_chksumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += sz1[j];

		if( sz1[iLen-1] == c1 )
			return 1;
		else
			return 0;
	}
	#endif


	
	#if 0
	static void mk_busycode( unsigned char src, unsigned char *pDest )
	{
		unsigned char mask;
		unsigned char i;

		mask = 0x80;
		pDest[0] = 0;
		pDest[1] = 0;

		for( i = 0; i < 8; i++ )
		{
			if( src & mask ) 
			{
				
				pDest[i/4] <<= 1;
				pDest[i/4] ++;
				if( i != 3 && i != 7 )
					pDest[i/4] <<= 1;
			}
			else
			{
				pDest[i/4] ++;
				pDest[i/4] <<= 1;
				
				if( i != 3 && i != 7 )
					pDest[i/4] <<= 1;
			}
			mask >>= 1;
		}
	}
	#endif

	
	#if 1
	static void mk_busycode( unsigned char src, unsigned char *pDest )
	{
		unsigned char mask;
		unsigned char i;

		

		mask = 0x80;
		for( i = 0; i < 8; i++ )
		{
			if( src & mask ) 
			{
				pDest[i/4] <<= 1;
				pDest[i/4] &= 0xfe;

				pDest[i/4] <<= 1;
				pDest[i/4] |= 1;
			}
			else
			{
				pDest[i/4] <<= 1;
				pDest[i/4] |= 1;

				pDest[i/4] <<= 1;
				pDest[i/4] &= 0xfe;
			}
			mask >>= 1;
		}
	}
	#endif


	
	#if 0
	static unsigned char chk_busycode( unsigned char *p )
	{
		unsigned char mask;
		unsigned char i;
		unsigned char c;

		mask = 0x80;
		c = 0;

		for( i = 0; i < 8; i++ )
		{
			if( !(p[i/4] & mask) ) c++;
			if( i != 7 ) c <<= 1;
			p[i/4] <<= 1;
			p[i/4] <<= 1;
		}
		return c;
	}
	#endif

	
	#if 1
	static unsigned char chk_busycode( unsigned char *p )
	{
		unsigned char i;
		unsigned char c;

		
		for( i = 0; i < 8; i++ )
		{
			if( p[i/4] & 0x80 )
			{
				c <<= 1;
				c &= 0xfe;
			}
			else
			{
				c <<= 1;
				c |= 1;
			}

			p[i/4] <<= 1;
			p[i/4] <<= 1;
		}
		return c;
	}
	#endif


	
	static std::string chg_jian2big( std::string s1, const char * jian, const char *fan, long jf_len )
	{
		char p[] = {0,0,0};
		const char * p1 ;
		long j,k;

		for( j = 0; j < (int)s1.size(); j++ )
		{
			p[0] = s1[j];
			int c = static_cast<int>(p[0]);

			if( c > 0 && c <= 127 )
			{
				continue;
			}
			j++;
			if( j == s1.size() ) break;
			p[1] = s1[j];

			
			k = 0;
			for( p1 = jian; p1 < jian + jf_len + 1; p1++ )
			{
				if( p1[0] == p[0] && p1[1] == p[1] )
				{
					k = 1;
					break;
				}

				int c = static_cast<int>(*p1);

				if( c > 0 && c <= 127 )
				{
				}
				else p1++;
			}
			if( k == 0 ) continue; 

			k = (long)(p1 - jian);

			s1[j-1] = fan[k];
			s1[j] = fan[k+1];
		}

		return s1;
	}


}; 




template < class INT_T, int LEN_T >
class uiarr_t
{
public:
	INT_T a[LEN_T];

	template < class _T >
	bool operator == (const _T & rhs) const
	{
		size_t i1, i2, i3 , i;
		i1 = sizeof(a);
		i2 = sizeof(rhs);
		if( i1 != i2 ) return false;
		if( i1 < i2 ) i3 = i1; else i3 = i2;
		for( i = 0; i < i3; i++ )
		{
			if( a[i] != rhs.a[i] ) return false;
		}
		return true;
	}

	template < class _T >
	bool operator != (const _T & rhs) const
	{
		return !this->operator==(rhs);
	}

	template < class _T >
	bool operator > (const _T & rhs) const
	{
		size_t i1, i2, i3 , i;
		i1 = sizeof(a);
		i2 = sizeof(rhs);
		if( i1 < i2 ) i3 = i1; else i3 = i2;
		for( i = 0; i < i3; i++ )
		{
			if( a[i] > rhs.a[i] ) return true;
			else if( a[i] < rhs.a[i] ) return false;
		}
		if( i1 > i2 ) return true;
		return false;
	}

	template < class _T >
	bool operator >= (const _T & rhs) const
	{
		return (*this > rhs) || (*this == rhs);
	}

	template < class _T >
	bool operator < (const _T & rhs) const
	{
		size_t i1, i2, i3 , i;
		i1 = sizeof(a);
		i2 = sizeof(rhs);
		if( i1 < i2 ) i3 = i1; else i3 = i2;
		for( i = 0; i < i3; i++ )
		{
			if( a[i] < rhs.a[i] ) return true;
			else if( a[i] > rhs.a[i] ) return false;
		}
		if( i1 < i2 ) return true;
		return false;
	}

	template < class _T >
	bool operator <= (const _T & rhs) const
	{
		return (*this < rhs) || (*this == rhs);
	}

	uiarr_t()
	{
		SStrf::smemset(a);
	}

	~uiarr_t()
	{ 	}
};



template < int LEN_T >
class ui8arr_t :public uiarr_t< tuint8 , LEN_T >
{
public:
};


template < int LEN_T >
class ui16arr_t :public uiarr_t< tuint16 , LEN_T >
{
public:
};





X011_NAMESPACE_END




#define MOONLOGSTR  \
	( "**" +  std::string(__FILE__) + "|" + std::string(__FUNCTION__) + "|" + wl::SStrf::sltoa(__LINE__) )






#endif





#ifndef X011__H_w_SCalc_h
#define X011__H_w_SCalc_h


X011_NAMESPACE_BEGIN


class SCalc
{

public:

	
	virtual ~SCalc(){;}


	static tint32 max_divisor( tint32 a, tint32 b) 
	{
		tint32 temp;
		while(b!=0) 
		{
		temp=a%b; 
		a=b;      
		b=temp;   
		}
		return a;
	}

	
	static tbool quadratic_equation_root( tdouble a, tdouble b, tdouble c, tdouble *x1, tdouble *x2) 
	{
		if(b*b<4*a*c) return 0;
		*x1=(sqrt(b*b-4*a*c)-b)/(2*a);
		*x2=(-sqrt(b*b-4*a*c)-b)/(2*a);
		return 1;
	}


	static tuint32 chksum( const tchar *s, tsize len)
	{
		tuint32 j=0;
		if(SStrf::slen(s)==0) return 0;
		while(len--)
		{
			j += (tuint8)s[len]+(len+1);
			j &= 0x7FffFFff;
		}
		return j;
	}


	static tuint32 chksum2( const tchar *s, tsize len)
	{
		tuint32 j=0;
		
		while(len--)
		{
			j += (tuint8)(s[len])+(len+2);
			j &= 0x7FffFFff;
		}
		return j;
	}


	static std::string dseal( const std::string & strData , tsize out_len , const tchar *szMethod = ""  )
	{
		return dseal( strData.c_str(), SStrf::slen( strData.c_str() ) , out_len , szMethod );
	}


	static std::string dseal( const tchar *s, tsize len, tsize out_len, const tchar *szMethod = "" )
	{
		
		tuint32 i, j;
		tchar *t, *t0;
		std::string strOut("");
		if(!s||!out_len||!szMethod) return "";
		for(j=len+out_len,i=0;;i++)
		{
			j = ++j + chksum(s, len) + chksum(szMethod,SStrf::slen(szMethod));
			j = ++j * chksum(strOut.c_str(),(tsize)strOut.size()) * (len^10) * out_len ;
			j = 0x7FffFFff & (j ^ (~j * ~i + (len ^ out_len)) * (~j+~j*~i+~i));
			strOut += SStrf::sltoa(j);
			if( out_len+11 < strOut.size() ) break ;
		}
		t0 = t = (tchar*)SStrf::smalloc( (tsize)strOut.size()+1 );
		if(!t) return "";
		SStrf::scpy( t, strOut.c_str() );
		SStrf::srev(t);
		if(*t=='0') t++;
		t[out_len] = 0;
		strOut=t;
		SStrf::sfree(t0);
		return strOut;
	}


	static std::string dseal2( const tchar *s, tsize len, tsize out_len )
	{
		
		tuint32 i, j;
		tchar *t, *t0;
		std::string strOut("");
		if(!s||!len||!out_len) return "";
		for(j=len+out_len,i=0;;i++)
		{
			j = ++j + chksum2(s, len);	j = ++j * chksum2(strOut.c_str(),(tsize)strOut.size()) * (len^10) * out_len ;
			j = 0x7FffFFff & (j ^ (~j * ~i + (len ^ out_len)) * (~j+~j*~i+~i));			strOut += SStrf::sltoa(j);
			if( out_len+11 < strOut.size() ) break ;
		}
		t0 = t = (tchar*)SStrf::smalloc( (tsize)strOut.size()+1 );
		if(!t) return "";
		SStrf::scpy( t, strOut.c_str() );		SStrf::srev(t);
		if(*t=='0') t++;
		t[out_len] = 0;		strOut=t;		SStrf::sfree(t0);
		return strOut;
	}


	static std::string dseal3( const tchar *s, tsize len, tsize out_len = 33 )
	{
		std::string strOut("");
		const unsigned char *a = (const unsigned char *)s;
		tsize l;
		tuint32 l1 = 0;
		for( l = 0; l < len; l++ )  l1 += (l * a[l]) ^ a[l];
		for( l = 0; l < len; l++ )  l1 += (l | a[l]) * a[l] + a[l];
		strOut = dseal2( s, len, out_len + 22 );
		(*SClib::p_sprintf())( &(strOut[0]), "a%d", (int)l1 );
		return dseal2( strOut.c_str(), (tsize)strOut.size(), out_len );
	}


	static std::string dseal3( const std::string &s, tsize out_len = 33 )
	{
		return dseal3( s.c_str(), (tsize)s.size(), out_len );
	}


	static tchar * xorB( tchar * Src, tsize len, tuint8 x )
	{
		tsize i;
		tuint8 *s=(tuint8 *)Src;
		if( !s || !len ) return (tchar*)s;
		for(i=0;i<len;i++) s[i] ^= x;
		return (tchar*)s;
	}


	static unsigned int CRC_16(const unsigned char *str,unsigned int usDataLen)
	{
		static const unsigned char  auchCRCHi[256] = {
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
			0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40
		} ;

		static const unsigned char  auchCRCLo[256] = {
			0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7, 0x05, 0xC5, 0xC4,0x04,
			0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E, 0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8,
			0xD8, 0x18, 0x19, 0xD9, 0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
			0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3, 0x11, 0xD1, 0xD0, 0x10,
			0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32, 0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4,
			0x3C, 0xFC, 0xFD, 0x3D, 0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
			0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF, 0x2D, 0xED, 0xEC, 0x2C,
			0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26, 0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0,
			0xA0, 0x60, 0x61, 0xA1, 0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
			0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB, 0x69, 0xA9, 0xA8, 0x68,
			0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA, 0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C,
			0xB4, 0x74, 0x75, 0xB5, 0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
			0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97, 0x55, 0x95, 0x94, 0x54,
			0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E, 0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98,
			0x88, 0x48, 0x49, 0x89, 0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
			0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83, 0x41, 0x81, 0x80,0x40
		} ;

		unsigned char uchCRCHi = 0xFF ; 
		unsigned char uchCRCLo = 0xFF ; 
		unsigned int uIndex ; 
		while (usDataLen--)
		{
			uIndex = uchCRCHi ^ *str++ ; 
			uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
			uchCRCLo = auchCRCLo[uIndex] ;
		}
		return ( ((int)uchCRCHi) << 8 | uchCRCLo) ;
	}


	
	static tuint16 CRC_16_2(const unsigned char *str,unsigned int usDataLen)	
	{
		static const unsigned short vCrcList[256] =
		{
			0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
			0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef,
			0x1231, 0x0210, 0x3273, 0x2252, 0x52b5, 0x4294, 0x72f7, 0x62d6,
			0x9339, 0x8318, 0xb37b, 0xa35a, 0xd3bd, 0xc39c, 0xf3ff, 0xe3de,
			0x2462, 0x3443, 0x0420, 0x1401, 0x64e6, 0x74c7, 0x44a4, 0x5485,
			0xa56a, 0xb54b, 0x8528, 0x9509, 0xe5ee, 0xf5cf, 0xc5ac, 0xd58d,
			0x3653, 0x2672, 0x1611, 0x0630, 0x76d7, 0x66f6, 0x5695, 0x46b4,
			0xb75b, 0xa77a, 0x9719, 0x8738, 0xf7df, 0xe7fe, 0xd79d, 0xc7bc,
			0x48c4, 0x58e5, 0x6886, 0x78a7, 0x0840, 0x1861, 0x2802, 0x3823,
			0xc9cc, 0xd9ed, 0xe98e, 0xf9af, 0x8948, 0x9969, 0xa90a, 0xb92b,
			0x5af5, 0x4ad4, 0x7ab7, 0x6a96, 0x1a71, 0x0a50, 0x3a33, 0x2a12,
			0xdbfd, 0xcbdc, 0xfbbf, 0xeb9e, 0x9b79, 0x8b58, 0xbb3b, 0xab1a,
			0x6ca6, 0x7c87, 0x4ce4, 0x5cc5, 0x2c22, 0x3c03, 0x0c60, 0x1c41,
			0xedae, 0xfd8f, 0xcdec, 0xddcd, 0xad2a, 0xbd0b, 0x8d68, 0x9d49,
			0x7e97, 0x6eb6, 0x5ed5, 0x4ef4, 0x3e13, 0x2e32, 0x1e51, 0x0e70,
			0xff9f, 0xefbe, 0xdfdd, 0xcffc, 0xbf1b, 0xaf3a, 0x9f59, 0x8f78,
			0x9188, 0x81a9, 0xb1ca, 0xa1eb, 0xd10c, 0xc12d, 0xf14e, 0xe16f,
			0x1080, 0x00a1, 0x30c2, 0x20e3, 0x5004, 0x4025, 0x7046, 0x6067,
			0x83b9, 0x9398, 0xa3fb, 0xb3da, 0xc33d, 0xd31c, 0xe37f, 0xf35e,
			0x02b1, 0x1290, 0x22f3, 0x32d2, 0x4235, 0x5214, 0x6277, 0x7256,
			0xb5ea, 0xa5cb, 0x95a8, 0x8589, 0xf56e, 0xe54f, 0xd52c, 0xc50d,
			0x34e2, 0x24c3, 0x14a0, 0x0481, 0x7466, 0x6447, 0x5424, 0x4405,
			0xa7db, 0xb7fa, 0x8799, 0x97b8, 0xe75f, 0xf77e, 0xc71d, 0xd73c,
			0x26d3, 0x36f2, 0x0691, 0x16b0, 0x6657, 0x7676, 0x4615, 0x5634,
			0xd94c, 0xc96d, 0xf90e, 0xe92f, 0x99c8, 0x89e9, 0xb98a, 0xa9ab,
			0x5844, 0x4865, 0x7806, 0x6827, 0x18c0, 0x08e1, 0x3882, 0x28a3,
			0xcb7d, 0xdb5c, 0xeb3f, 0xfb1e, 0x8bf9, 0x9bd8, 0xabbb, 0xbb9a,
			0x4a75, 0x5a54, 0x6a37, 0x7a16, 0x0af1, 0x1ad0, 0x2ab3, 0x3a92,
			0xfd2e, 0xed0f, 0xdd6c, 0xcd4d, 0xbdaa, 0xad8b, 0x9de8, 0x8dc9,
			0x7c26, 0x6c07, 0x5c64, 0x4c45, 0x3ca2, 0x2c83, 0x1ce0, 0x0cc1,
			0xef1f, 0xff3e, 0xcf5d, 0xdf7c, 0xaf9b, 0xbfba, 0x8fd9, 0x9ff8,
			0x6e17, 0x7e36, 0x4e55, 0x5e74, 0x2e93, 0x3eb2, 0x0ed1, 0x1ef0
		};

		tuint32 i ,j ;
		tuint32 k;
		tuint16 crc ;
		crc = 0;
		j = usDataLen;
		for( i = 0 ; i < j; i++ )
		{
			k = (crc & 0xFF00) / 256;
			crc = (crc % 256) * 256;
			crc = crc ^ vCrcList[k ^ str[i] ];
		}

		return crc;
	}


	#if 1
	static tbool mk_chksumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += sz1[j];

		sz1[iLen-1] = c1;

		return 1;
	}
	#endif

	#if 1
	static tbool chk_chksumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += sz1[j];

		if( sz1[iLen-1] == c1 )
			return 1;
		else
			return 0;
	}
	#endif


	
	#if 1
	static unsigned char mk_chk2sumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += ( sz1[j] ^ (unsigned char)j );

		if( c1 == 0 || c1 == 255 ) c1 = 1;

		sz1[iLen-1] = c1;

		return 1;
	}
	#endif

	#if 1
	static unsigned char chk_chk2sumU8( unsigned char * sz1, unsigned int iLen )
	{
		unsigned char c1 = 0;
		unsigned int j;

		
		for( j = 0 ; j < iLen - 1; j ++ )
			c1 += ( sz1[j] ^ (unsigned char)j );

		if( c1 == 0 || c1 == 255 ) c1 = 1;

		if( sz1[iLen-1] == c1 )
			return 1;
		else
			return 0;
	}
	#endif



}; 




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_sstrvs_h
#define X011__H_w_sstrvs_h


X011_NAMESPACE_BEGIN


class SStrvs
{
public:

	
	virtual ~SStrvs(){;}


	template < class StrT > 
	static tsize vsa_impbylen( const StrT & strsource, typename StrT::size_type ilen, std::vector<StrT> & vecrtn )
	{
		StrT s1(strsource);
		typedef typename StrT::size_type sizetypeB;

		while( !s1.empty() )
		{
			sizetypeB i = ilen <= s1.size() ? ilen : s1.size();
			StrT s2 = s1.substr( 0, i );
			vecrtn.push_back(s2);
			s1.erase( 0, i );	
		}
		return (tsize)vecrtn.size();
	}



	
	template < class StrT > 
	static tsize vsa_imp( const StrT & ssource, const StrT & ssep, tbool istoken, std::vector<StrT> & rtnlst )
	
	{
		std::vector<tint32> vAbuf, vBbuf;
		tint32  ltmpn,ltmpm,ltmpi,ltmpj,ltmpk, ltmpb1, ltmpb2;
		typedef typename StrT::size_type sizetypeB;
		sizetypeB ssti;

		ltmpm = ltmpi = ltmpj = 0;
		ltmpn = (tint32)ssource.size();
		ltmpk = (tint32)ssep.size();

		do 
		{
			if(ltmpk==0)
			{
				rtnlst.push_back(ssource);
				break;
			}

			do
			{
				if(ltmpm>=ltmpn) break;
				ssti = ssource.find( ssep, ltmpm ); 
				if(ssti==StrT::npos) break;
				ltmpi = (tint32)ssti;
				ltmpm = ltmpi;

				vAbuf.push_back(ltmpi);
				ltmpj ++;
				ltmpm += ltmpk;

			} while(1);

			ltmpb1 = 0 ; 
			ltmpb2 = ltmpj - 1 ; 

			ltmpj = 0;
			vBbuf.push_back(ltmpj);
			for(ltmpi=ltmpb1;ltmpi<=ltmpb2;ltmpi++){
				ltmpj = vAbuf[ltmpi];
				vBbuf.push_back(ltmpj);
				vBbuf.push_back(ltmpj+ltmpk);
			}
			vBbuf.push_back( ltmpn );

			ltmpj = (tint32)vBbuf.size();
			for(ltmpi=0;ltmpi<ltmpj;ltmpi+=2)
			{
				ltmpm = vBbuf[ltmpi];
				ltmpn = vBbuf[ltmpi+1];
				ltmpk = ltmpn - ltmpm;

				if(istoken&&ltmpk==0){
					;
				}else
					rtnlst.push_back( ssource.substr( ltmpm, ltmpk ) ); 

			}

		}while(0);

		return (tsize)rtnlst.size();
	}


	template < class StrT > 
	static std::vector<StrT>  vsa_imp( const StrT & ssource, const StrT & ssep, tbool istoken )
	{
		std::vector<StrT>  r;
		vsa_imp( ssource, ssep, istoken, r );
		return r;
	}


	template < class StrT > 
	static tsize vsa_hm( const StrT & ssource, const StrT & ssep, tbool istoken )
	{
		std::vector<StrT> a;
		return vsa_imp( ssource, ssep, istoken, a );
	}


	template < class StrT > 
	static StrT vsa_get( const StrT & ssource, const StrT & ssep, tbool istoken, tsize iwhich )
	
	{
		std::vector<StrT> tmplst;
		if( iwhich<vsa_imp( ssource, ssep, istoken, tmplst ) )
			return tmplst[iwhich];
		else
			return StrT();
	}

	template < class StrT >
	static StrT vsa_get( const StrT & ssource, const typename StrT::value_type *ssep, tbool istoken, tsize iwhich )
	{
			return vsa_get( ssource,  StrT(ssep),  istoken,  iwhich );
	}


	
	template < class StrT >
	static StrT vsa2v_get( const StrT & ssource,

						  const StrT & ssepTR,
						  tbool		istokenTR,
						  const StrT & ssepTD,
						  tbool		istokenTD,

						  tsize iwhichTR,  tsize iwhichTD		)

	{
		std::vector<StrT> tmplst1, tmplst2;
		if( iwhichTR<vsa_imp( ssource, ssepTR, istokenTR, tmplst1 ) )
		{
			if( iwhichTD<vsa_imp( tmplst1[iwhichTR], ssepTD, istokenTD, tmplst2 ) )
				return tmplst2[iwhichTD];
		}
		return StrT();
	}


	
	template < class StrT >
	static std::map<StrT,StrT> & vsa2v_prpt( const StrT & ssource,
											 const StrT & ssepTR,
											 const StrT & ssepTD,
											 std::map<StrT,StrT> & mapRtn	)
	{
		std::vector<StrT> vecTmpTR, vecTmpTD;
		typedef typename std::vector<StrT>::iterator iteratortypeB;
		iteratortypeB itTR;
		vsa_imp( ssource, ssepTR, 1, vecTmpTR );
		for( itTR = vecTmpTR.begin(); itTR!=vecTmpTR.end(); ++itTR)
		{
			vsa_imp( *itTR, ssepTD, 1, vecTmpTD );
			vecTmpTD.push_back( StrT() );
			vecTmpTD.push_back( StrT() );
			mapRtn.insert( std::pair<StrT,StrT>( vecTmpTD[0], vecTmpTD[1] ) );
			vecTmpTD.clear();
		}
		return mapRtn;
	}


};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_SSetu_h
#define X011__H_w_SSetu_h


X011_NAMESPACE_BEGIN


class SSetu
{

public:

	
	virtual ~SSetu(){;}


	template < class CntnrT, class ELET >
	static tsize vs_setch( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 == vset2.end() ) 
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	template < class CntnrT, class ELET >
	static tsize vs_setj( CntnrT &vset1, CntnrT &vset2, std::vector<ELET> &rtnlst )
	{
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB it1, it2;
		tsize i;
		i=0;
		for( it1=vset1.begin(); it1!=vset1.end(); it1++)
		{
			it2 = std::find( vset2.begin(), vset2.end(), *it1 );
			if( it2 != vset2.end() ) 
			{
				rtnlst.push_back( *it1 );
				i++;
			}
		}
		return i;
	}


	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent, std::vector<int> & rtnsubsum )
	{
		CntnrT v2, v3; 
		typedef typename CntnrT::iterator iteratortypeB;
		iteratortypeB  it1,  itNewEnd2;
		int i;

		v2 = vsource;
		std::sort( v2.begin(), v2.end() );
		v3 = v2;

		itNewEnd2 = std::unique( v2.begin(), v2.end() );

		for( it1=v2.begin(); it1!=itNewEnd2; it1++)
		{
			rtncontent.push_back( *it1 );
			i = (int)std::count( v3.begin(), v3.end(), *it1 );
			rtnsubsum.push_back(i);
		}
		return (tsize)v2.size();
	}


	template < class CntnrT, class ELET >
	static tsize vs_setgroup( const CntnrT & vsource, std::vector<ELET> & rtncontent )
	{
		std::vector<int> v;
		return vs_setgroup( vsource, rtncontent, v );
	}


	template < class ELET >
	static tsize vs_setgroup( std::vector<ELET> & _a_content )  
	{
		std::vector<ELET> _a_aa1;
		tsize i = vs_setgroup( _a_content, _a_aa1 );
		_a_content = _a_aa1;
		return i;
	}




	template < class ELET >
	static ELET vs_groupbig( const std::vector<ELET> & memo, const std::vector<int> & subsum )
	{
		typedef typename std::vector<ELET>::const_iterator iteratortypeB;
		iteratortypeB it1;
		std::vector<int>::const_iterator it2, it3;
		int i;

		if( memo.size() != subsum.size() || memo.size() == 0 ) return ELET();

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2>i )
			{
				i = *it2;  
				it3 = it2; 
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	template < class ELET >
	static ELET vs_groupsmall( const std::vector<ELET> & memo, const std::vector<int> & subsum )
	{
		typename std::vector<ELET>::const_iterator it1;
		std::vector<int>::const_iterator it2, it3;
		int i;

		if( memo.size() != subsum.size() || memo.size() == 0 ) return ELET();

		i=0;
		for( it3=it2=subsum.begin(); it2!=subsum.end(); ++it2)
		{
			if( *it2<i || i==0 )
			{
				i = *it2;  
				it3 = it2; 
			}
		}

		it1 = memo.begin() + ( it3 - subsum.begin() );
		return *it1;
	}


	template < class ELET >
	static void StableDelOld( std::vector<ELET> & v )
	{
		for( typename std::vector<ELET>::iterator it = v.begin(); it != v.end(); )
		{
			typename std::vector<ELET>::iterator it2;

			it2 = it + 1;

			if( std::find( it2, v.end(), *it ) != v.end() )
			{
				
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}


	template < class CNTNRT, class ELET >
	
	static void StableDel( CNTNRT & v , ELET val )
	{
		for( typename CNTNRT::iterator it = v.begin(); it != v.end(); )
		{
			if( *it == val )
			{
				
				v.erase( it );
				it = v.begin();
			}
			else
				++it;
		}
	}

};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_scake_h
#define X011__H_w_scake_h



X011_NAMESPACE_BEGIN


template < class CT >
class SCake_base
{
public:
	typedef  CT CkEle_t;

private:

	CT		*m_pbuf;
	tsize	m_mysize; 

	mutable std::vector<CT>  m_FastAppendBuf;

private:

	void init(void) { 	m_pbuf=NULL; 	m_mysize=0; }

	void freeall(void)
	{
		if(m_pbuf) delete [] m_pbuf;
		m_mysize=0;
		init();
	}

public:

	SCake_base() {  init(); }

	SCake_base( const SCake_base<CT> & cakesource )
	{
		init();
		let(cakesource);
	}

	SCake_base( CT c ) { init(); let(&c,1); }

	SCake_base( const CT *psource, tsize isize ) { init(); let(psource,isize); }

	SCake_base( const tchar *psource ) { init(); lets(psource); } 

	SCake_base( const std::string & s) { init(); lets(s); } 


	virtual ~SCake_base( )
	{
		freeall();
	}


	
	
	
	

	
	
	

	void copybuf( const CT *psource, CT *pdest, tsize isize, toffset iDestOffsetWhere = 0 )
	{
		if( psource == pdest && iDestOffsetWhere == 0 ) return;

		if( psource && pdest && isize )
		{
			for( tsize jtmp=iDestOffsetWhere; jtmp<isize+iDestOffsetWhere; jtmp++ )
				pdest[jtmp] = psource[jtmp-iDestOffsetWhere];
		}
	}


	void redim( tsize iNewSize, tbool reserve=0 )
	{
		if( iNewSize <= len() && iNewSize > len()/2 )
		{
			m_mysize = iNewSize;
		}
		else
		{
			CT *lbuf;
			if(iNewSize==0)
			{
				freeall();
				return;
			}
			lbuf = new CT[iNewSize] ;
			if(reserve) copybuf( m_pbuf, lbuf, iNewSize<m_mysize?iNewSize:m_mysize );
			freeall();
			m_pbuf = lbuf;
			m_mysize = iNewSize;
		}
	}

	const CT * buf_const() const
	{
		

		return m_pbuf;
	}


	CT * buf()
	{
		FastAppendEnd();

		return m_pbuf;
	}

	tsize len() const
	{
		return m_mysize;
	}

	void let( const CT *psource, tsize isize ) 
	{
		FastAppendEnd();

		if( (void*)psource==(void*)m_pbuf ) return;

		redim(isize);
		copybuf( psource, m_pbuf, isize );
	}


	void let( const SCake_base<CT> & cakesource )
	{
		let( cakesource.buf_const(), cakesource.len() );
	}


	void lets( const CT *psource, CT c00 )
	{
		tsize i;
		const CT *p2;
		for(i=1,p2=psource;*p2!=c00;p2++)
			i++; 
		let( psource, i );
	}


 	void lets( const tchar *psource ) 
	{
		if( (void*)psource==(void*)m_pbuf ) return;

		if(psource)
		{
			redim( SStrf::slen(psource) + 1 );
			tsize jtmp;
			for( jtmp=0; psource[jtmp]; jtmp++ )
			{
				m_pbuf[jtmp] = psource[jtmp];
			}
			m_pbuf[jtmp] = 0;
		}
	}


	void lets( const std::string & s) { lets(s.c_str()); }

	void lets( tint32 i)  { lets( SStrf::sltoa(i) ); }

	void lets( tdouble d) { lets( SStrf::sftoa(d) ); }

	SCake_base<CT> & dump( SCake_base<CT> & cake2 ) 
	{
		tsize iGoneSize;
		cake2.let( buf(), iGoneSize = ( len() < cake2.len() ? len() : cake2.len() ) ); 
		SCake_base<CT> * ptmpcake = new SCake_base<CT>(*this);
		let( ptmpcake->buf() + iGoneSize, len() - iGoneSize );
		delete ptmpcake;
		return cake2;
	}


	SCake_base<CT> & cut( tsize howmany ) 
	{
		if( howmany<=m_mysize) m_mysize -= howmany;
		else m_mysize = 0;
		return *this;
	}


	SCake_base<CT> & FastAppend( const SCake_base<CT> & cake2 ) 
	{
		if( !this->m_pbuf ) return this->append(cake2);

		if(cake2.len()==0)
		{
			return *this;
		}

		this->m_mysize += cake2.len();
		std::copy( cake2.buf_const(), cake2.buf_const() + cake2.len(), std::back_inserter(m_FastAppendBuf) );

		return *this;
	}

	void FastAppendEnd()
	{
		if( m_FastAppendBuf.empty() ) return;

		std::vector<CT>  FastBuf2(m_FastAppendBuf);

		m_FastAppendBuf.clear(); 
		this->m_mysize -= (tsize)FastBuf2.size();
		this->append( &(FastBuf2[0]), (tsize)FastBuf2.size() );
	}


	SCake_base<CT> & append( const SCake_base<CT> & cake2 ) 
	{
		if(cake2.len()==0)
		{
			
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = cake2.buf_const();
			len1 = len();
			len2 = cake2.len();
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	
	SCake_base<CT> & append( const CT *psource, tsize isize )
	{
		if( isize==0 || !psource )
		{
			
		}
		else
		{
			CT *lbuf1;
			const CT *lbuf2;
			tsize len1,len2;
			lbuf1 = buf();
			lbuf2 = psource;
			len1 = len();
			len2 = isize;
			redim( len1+len2, 1 );
			copybuf( lbuf2, buf(), len2, len1 );
		}
		return *this;
	}

	
	SCake_base<CT> & append( CT val )
	{
		return append( &val, 1 );
	}

	
	std::string ds2( tsize out_len = 33 ) const
	{
		std::string s( out_len, '0' );
		if( this->len() == 0 ) return s;
		return SCalc::dseal2( (const char*)this->buf_const(), this->m_mysize, out_len );
	}

	
	std::string ds3( tsize out_len = 33 ) const
	{
		std::string s( out_len, '0' );
		if( this->len() == 0 ) return s;
		return SCalc::dseal3( (const char*)this->buf_const(), this->m_mysize, out_len );
	}


public:	

	

	SCake_base<CT> & operator = ( const SCake_base<CT> & cake2 )
	{
		let(cake2);
		return *this;
	}


	operator CT * ( )
	{
		return buf();
	}


	operator const CT * ( ) const
	{
		return buf_const();
	}

	int operator < ( const SCake_base<CT> & cake2 ) const
	{
		return ( (int)buf_const() < (int)cake2.buf_const() );
	}


}; 





class SCake : public SCake_base<tchar>
{

public:

	SCake():SCake_base<tchar>( ) { }

	SCake(const SCake & ckSrc):SCake_base<tchar>( ckSrc ) {  }


	SCake(const SCake_base<tchar> & ckSrc):SCake_base<tchar>( ckSrc ) {  }

	SCake( tchar c ):SCake_base<tchar>( c ) {  }
	
	

	SCake(const tchar * psrc, tsize isize):SCake_base<tchar>( psrc, isize ) {  }

	SCake(const tchar *psrc):SCake_base<tchar>( psrc ) {  }

	SCake(const std::string & s):SCake_base<tchar>( s) { }


	SCake & bs_en()
	{
		SCake *pck = new SCake;
		pck->redim( SStrf::bs_ensize( buf(), len() ) );
		SStrf::bs_en( buf(), len(), pck->buf() );
		*this = *pck;
		delete pck;
		return *this;
	}

	SCake & bs_en( std::string & strOut )
	{
		SCake *pck = new SCake;
		*pck = *this;
		pck->bs_en();
		strOut = pck->buf();
		delete pck;
		return *this;
	}

	std::string bs_en( std::string *pstrOut )
	{
		std::string strBuf;
		if( pstrOut == NULL ) pstrOut = &strBuf;
		bs_en( *pstrOut );
		return ( *pstrOut );
	}


	SCake & bs_de() 
	{
		if( buf() == NULL )
		{
			redim(0);
			return *this;
		}
		tsize iDatalen = SStrf::bs_desize( buf() );
		SStrf::bs_de( buf() );
		redim( iDatalen, 1 );
		return *this;
	}

	SCake & bs_de( const std::string & str ) 
	{
		if( str.empty() )
		{
			redim(0);
			return *this;
		}
		redim( (tsize)str.size() + 1 );
		(*SClib::p_strcpy())( buf(), str.c_str() );
		return bs_de();
	}


	tchar * mk_sz()
	{
		append( SCake("") );
		return buf();
	}

	std::string & mk_str( std::string & strOut ) const
	{
		if( this->len() )
		{
			return strOut = std::string( this->buf_const(), this->len() ).c_str(); 
		}
		return strOut = "";
	}

	
	std::string mk_str() const
	{
		std::string s1;
		return mk_str(s1);
	}


	std::string GetReadable_2v( int iLineLen , std::string strTd, std::string strTr ) const
	{
		std::string strOut;

		for( tsize i = 0; i < this->len(); i++ )
		{
			if( i != 0 && ( i % iLineLen ) == 0 )
				strOut += strTr;

			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];

			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;

			(*SClib::p_sprintf())( sz1, "%02X", (int)(*p2) );
			strOut += sz1;

			strOut += strTd;
		}

		return strOut;
	}


	std::string GetReadable() const
	{
		std::string strOut;

		for( tsize i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];

			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;
			(*SClib::p_sprintf())( sz1, "%02X", (int)(*p2) );
			strOut += sz1;
		}

		return strOut;
	}


	std::string GetReadableWithLen() const
	{
		std::string strOut = "L" + SStrf::sltoa( (int)this->len() ) + "-";

		for( tsize i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];

			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;
			(*SClib::p_sprintf())( sz1, "%02X", (int)(*p2) );
			strOut += sz1;
		}

		return strOut;
	}


	
	long ConvStr2Bin( std::string strData, void * pData ) const
	{
		std::vector<std::string> vec1;

		SStrvs::vsa_imp( strData, std::string(" "), 1, vec1 );

		for( std::vector<std::string>::size_type i = 0; pData && i < vec1.size(); i++ )
		{
			int ii;
			(SClib::p_sscanf())( vec1[i].c_str(), "%x", &ii );
			*((tuint8*)pData+i) = (tuint8)ii;
		}

		return (long)vec1.size();
	}

	
	long ConvStr2Bin( std::string strData ) 
	{
		redim( ConvStr2Bin( strData, NULL ) );
		return ConvStr2Bin( strData, buf() );
	}

	
	long ConvPackStr2Bin( std::string s1 ) 
	{
		std::vector<std::string> vec1;

		SStrvs::vsa_impbylen( s1, 2, vec1 );

		s1="";
		for( std::vector<std::string>::size_type i = 0; i < vec1.size(); i++ )
		{
			s1 += vec1[i] + " ";
		}

		return ConvStr2Bin( s1 );
	}


	std::string Seri() const  
	{
		return GetReadable();
	}

	
	long UnSeri( const std::string & s1 ) 
	{
		return ConvPackStr2Bin( s1 ); 
	}

	
	std::string Seri_S() const  
	{
		std::string strOut;
		for( tsize i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];
			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;
			(*SClib::p_sprintf())( sz1, "%02X ", (int)(*p2) );
			strOut += sz1;
		}
		return strOut;
	}

	
	long UnSeri_S( const std::string & s1 ) 
	{
		return ConvStr2Bin( s1 ); 
	}


	long UnSeri2( const std::string & s1 ) 
	{
		for( std::string::const_iterator it = s1.begin(); it != s1.end() ; ++it )
		{
			if( *it == ' ' ) return UnSeri_S( s1 );
		}
		return UnSeri( s1 );
	}

	
	long UnSeri3( const std::string & s1 ) 
	{
		std::string s2;
		for( std::string::size_type i = 0; i < s1.size(); i++ )
		{
			if( wl::SStrf::sishex( s1[i] ) ) s2 += *( s1.c_str() + i );
		}
		return UnSeri( s2 );
	}

	
	long UnSeri10D( const std::string &strData, void * pData ) const
	{
		std::vector<std::string> vec1;

		SStrvs::vsa_imp( strData, std::string(","), 1, vec1 );

		for( std::vector<std::string>::size_type i = 0; pData && i < vec1.size(); i++ )
		{
			int ii;
			(SClib::p_sscanf())( vec1[i].c_str(), "%d", &ii );
			*((tuint8*)pData+i) = (tuint8)ii;
		}

		return (long)vec1.size();
	}

	
	long UnSeri10D( const std::string &strData ) 
	{
		redim( UnSeri10D( strData, NULL ) );
		return UnSeri10D( strData, buf() );
	}

	
	std::string Seri10D() const  
	{
		tsize i;
		std::string strOut;
		for( i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;
			char sz1[9];
			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;
			(*SClib::p_sprintf())( sz1, "%d,", (int)(*p2) );
			strOut += sz1;
		}
		if( !strOut.empty() ) strOut.erase( strOut.end() - 1 );
		return strOut;
	}

public:	

	SCake & operator = ( const SCake & cake2 )
	{
		let(cake2);
		return *this;
	}


}; 





template < class cakeT, class CT >
class SCakel_base2 {

private:

	std::vector<cakeT *> m_vknl;

	
	void collect( tbool szstyle = 1, cakeT  * pscbuff = NULL )
	{
		
		tsize wholesize,copypoint;
		typename std::vector<cakeT *>::iterator it;
		for( wholesize=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			wholesize += (*it)->len( );
			if(szstyle&&(*it)->len( )) wholesize--;
		}
		if(szstyle) wholesize++;

		cakeT  * psc = pscbuff;

		if( pscbuff == NULL ) psc = new cakeT ;
		psc->redim(wholesize);
		for( copypoint=0,it=m_vknl.begin(); it!=m_vknl.end(); ++it )
		{
			psc->copybuf( (*it)->buf(), psc->buf(),	(*it)->len(), copypoint );
			copypoint += (*it)->len();
			if(szstyle) copypoint--;
		}
		clean();

		if( pscbuff == NULL ) m_vknl.push_back( psc );
	}


private:

	SCakel_base2( const SCakel_base2 & ckl )
	{
		;
	}

public:

	SCakel_base2() { ; }

	virtual ~SCakel_base2()
	{
		for( typename std::vector<cakeT *>::iterator it=m_vknl.begin();it!=m_vknl.end();++it)
			delete *it;
	} 


	tsize hm(void) const
	{
		return (tsize)m_vknl.size();
	}


	std::vector<cakeT *> & knl( ) {
		return m_vknl;
	}


	cakeT  * get( tsize iwhere ) const
	{
		return ( hm( )==0 || iwhere>=hm( ) )?NULL:m_vknl[iwhere];
		
		
	}


	cakeT  * get( ) const
	{
		return get( hm( )-1 );
	}


	cakeT  * get0( )
	{
		return get(0);
	}


	void add( const cakeT  & cakesource, tsize iwhere )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );
		if(iwhere>hm()) iwhere=hm();
		m_vknl.insert( m_vknl.begin()+iwhere, psc );
	}


	void add( const cakeT  & cakesource )
	{
		cakeT  * psc;
		psc = new cakeT ( cakesource );	
		m_vknl.push_back( psc );
	}


	void add0( cakeT  & cakesource ) { add(cakesource,0); }


	void del( tsize iwhere )
	{
		typename std::vector<cakeT *>::iterator it;
		if( !( hm( )==0 || iwhere>=hm( ) ) )
		{
			it = m_vknl.begin( ) + iwhere;
			delete *it;
			m_vknl.erase( it );
		}
	}

	void del()  { del(hm()-1); }

	void del0() { del(0); }


	void clean()
	{
		tsize iremain = 0;
		while( hm() > iremain )
			del();
	}

	void clean( tsize iremain )
	{
		while( hm() > iremain )
			del();
	}


	void clean0( tsize iremain = 0 )
	{
		while( hm() > iremain )
			del0();
	}

	void collectb( cakeT  * pscbuff = NULL ) { collect(0,pscbuff); }

	void collects( cakeT  * pscbuff = NULL ) { collect(1,pscbuff); }


	void scatter( const cakeT  & ckSrc , CT cSepC )
	{
		tsize p1,p2;
		cakeT  ckTmp;
		for(p1=p2=0;p2<ckSrc.len();p2++)
		{
			if( *(ckSrc+p2)==cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				add( ckTmp );
				p1=p2+1;
			}
		}

		
		if(p2) 
		{
			p2--;
			if( *(ckSrc+p2)!=cSepC )
			{
				ckTmp.let( ckSrc+p1, p2-p1+1 );
				ckTmp.append( cakeT ( &cSepC,1 ) );
				add( ckTmp );
			}
		}
	}


	void scatter( CT cSepC=0 )
	{
		do 
		{
			if(hm()>1)
				collectb();

			if(hm()==0)
				break;

			scatter( *get0() , cSepC );

			del0();

		}while(0);
	}


	SCakel_base2<cakeT,CT> & append( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}


public: 


	operator std::vector<cakeT *> & ( )
	{
		return knl( );
	}


	SCakel_base2<cakeT,CT> & operator = ( const SCakel_base2<cakeT,CT> & cakel2 )
	{
		clean();
		return append(cakel2);
	}


};






template < class CT >
class SCakel_base : public SCakel_base2<  SCake_base<CT>, CT >
{
private:

	SCakel_base( const SCakel_base & ckl )
	{
		;
	}

public:

	SCakel_base() { ; }

	virtual ~SCakel_base() { ; }

public: 

	SCakel_base<CT> & operator = ( const SCakel_base<CT> & cakel2 )
	{
		SCakel_base2<  SCake_base<CT>, CT >::clean();
		return append(cakel2);
	}

};






class SCakel : public SCakel_base2< SCake, tchar >
{
private:

	SCakel( const SCakel & ckl )
	{
		;
	}

public:

	SCakel() { ;	}
	virtual ~SCakel() { ; }

public:

	SCakel & append( const SCakel & cakel2 )
	{
		tsize len2,lcount;
		len2 = cakel2.hm();
		for(lcount=0;lcount<len2;lcount++)
		{
			add( *(cakel2.get(lcount)) );
		}
		return *this;
	}

	static tsize MkVecCake( const SCake &ckInput, tsize iLen, std::vector< SCake > & vckOut, tbool biLastFull = 1, tuint8 *pFill = NULL )
	{
		tsize i1, i2;
		i1 = 0;
		i2 = iLen;
		vckOut.clear();
		if( ckInput.len() == 0 || iLen == 0 ) return 0;
		for( ; ; i1 += iLen, i2 += iLen )
		{
			SCake ck;
			tbool biLastFlag = 0;

			if( i2 >= ckInput.len() )
			{
				i2 = ckInput.len();
				biLastFlag = 1;
			}

			ck.redim( iLen );
			SStrf::smemset( ck.buf(), pFill ? *pFill : 0, ck.len() );
			SStrf::smemcpy( ck.buf(), ckInput.buf_const() + i1, i2 - i1 );

			if( biLastFlag == 1 && biLastFull == 0 && i2 - i1 != ck.len() )
			{
				ck.redim( i2 - i1, 1 );
			}

			vckOut.push_back( ck );

			if( biLastFlag == 1 )
				return i2 - i1;
		}
	}


public: 

	SCakel & operator = ( const SCakel & cakel2 )
	{
		clean();
		return append(cakel2);
	}

};





#ifdef VC6_COMPATIBLE_X011_
	

#else

class S_dataeater_t
{
private:
	SCake	m_ckBufData;
	int     m_iBufOffset;

public:
	
	S_dataeater_t()
	{
		m_iBufOffset = 0;
	}

	
	S_dataeater_t( const S_dataeater_t & aa )
	{
		m_ckBufData = aa.m_ckBufData;
		m_iBufOffset = aa.m_iBufOffset;
	}

	S_dataeater_t(SCake ckData)
	{
		reset( ckData );
	}

	
	S_dataeater_t(void *p, int iLen )
	{
		reset( p, iLen );
	}

	
	virtual ~S_dataeater_t(){;}

public:

	
	void reset()
	{
	  m_iBufOffset  = 0;
	}

	
	void reset( void *p, int iLen )
	{
		SCake c( (char*)p, iLen);
		reset(c);
	}

	
	void reset( SCake ckData )
	{
		m_ckBufData = ckData;
		m_iBufOffset = 0;
	}

	
	tbool HaveMoreData()
	{
		if( m_ckBufData.len() == 0 ) return 0;
		return ( (tsize)m_iBufOffset >= m_ckBufData.len() ) ? 0 : 1 ;
	}

	
	template<class T>
	T eat_data( tbool biTurnEndian = 1 , tbool biMoveOn = 1 )
	{
		if( !HaveMoreData() )
		{
			
			
			return 0;
		}

		T i;

		
		SStrf::MkBlock2INTDataRef( m_ckBufData.buf() + m_iBufOffset, i , 0 ); 

		if(biMoveOn) m_iBufOffset += sizeof(T);
		if(biTurnEndian)
			if( sizeof(T) > 1 ) SStrf::chgendian( i );
		return i;
	}

	
	std::string eat_str( int iLen )
	{
		std::string s1 = "";
		for( int i = 0; iLen > 0 && i < iLen; i++ )
		{
			if( !HaveMoreData() ) break;
			s1 += this->eat_data<char>();
		}
		return s1.c_str();
	}

	
	tuint32 eat_big3( tbool biTurnEndian = 1 , tbool biMoveOn = 1 )
	{
		tuint32 ul1(0);
		tuint8 *p1 = (tuint8*)&ul1;
		p1[0] = 0;
		p1[1] = eat_data<tuint8>(biTurnEndian,biMoveOn);
		p1[2] = eat_data<tuint8>(biTurnEndian,biMoveOn);
		p1[3] = eat_data<tuint8>(biTurnEndian,biMoveOn);
		if(biTurnEndian)
			SStrf::chgendian( ul1 );
		return ul1;
	}

	
	template<class T>
	T & eat_bin( T & aa , tbool biMoveOn = 1 )
	{
		if( HaveMoreData() && m_ckBufData.len() >= m_iBufOffset + sizeof(T) )
		{
			SStrf::MkBlock2INTDataRef( m_ckBufData.buf() + m_iBufOffset, aa , 0 );
		}
		else
			SStrf::smemset(aa);

		if(biMoveOn) m_iBufOffset += sizeof(T);

		return aa;
	}

	
	void * eat_BinBlock( void *pDest, tsize i, tbool biMoveOn = 1 )
	{
		if( HaveMoreData() && m_ckBufData.len() >= m_iBufOffset + i )
		{
			SStrf::smemcpy( pDest, m_ckBufData.buf() + m_iBufOffset, i );
			return pDest;
		}
		return NULL;
	}


	template<class T>
	void eat_skip()
	{ m_iBufOffset += sizeof(T); }

	
	void eat_skip( int i )
	{ m_iBufOffset += i; }

};

#endif	





class SStrTbl
{
public:

	
	
	static void encodebase64( const char *p1, int ilen, std::string &rtn_str )
	{
		static char basis_64[] =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/???????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????????";
		const unsigned char *in = (const unsigned char *)p1;
		unsigned char   oval;
		unsigned        olen;
		SCake ck;
		unsigned long inlen = ilen;

		olen = (inlen + 2) / 3 * 4;
		ck.redim(olen+1);

		unsigned char  *out = (unsigned char *)ck.buf();

	 
		while (inlen >= 3)
		{
	 
			*out++ = basis_64[in[0] >> 2];
			*out++ = basis_64[((in[0] << 4) & 0x30) | (in[1] >> 4)];
			*out++ = basis_64[((in[1] << 2) & 0x3c) | (in[2] >> 6)];
			*out++ = basis_64[in[2] & 0x3f];
			in += 3;
			inlen -= 3;
		}
		if (inlen > 0)
		{
	 
			*out++ = basis_64[in[0] >> 2];
			oval = (in[0] << 4) & 0x30;
			if (inlen > 1)
				oval |= in[1] >> 4;
			*out++ = basis_64[oval];
			*out++ = (inlen < 2) ? '=' : basis_64[(in[1] << 2) & 0x3c];
			*out++ = '=';
		}

		*out = '\0';

		rtn_str = ck.buf();
	}

	
	static std::string encodebase64( const SCake &ckin )
	{
		std::string s;
		encodebase64( ckin.buf_const(), (int)ckin.len(), s );
		return s;
	}

	
	static std::string encodebase64str( const std::string & str_in ) 
	{
		SCake ck;
		ck.lets(str_in);
		ck.cut( 1 );
		return encodebase64(ck);
	}


	static char CHAR64(int c)
	{
		static char  index_64[128] = {
			
			
			
			
			
			
(char)-1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char)
-1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char)
-1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) 62,(char) -1,(char) -1,(char) -1,(char) 63,(char)
52,(char) 53,(char) 54,(char) 55,(char) 56,(char) 57,(char) 58,(char) 59,(char) 60,(char) 61,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char)
-1,(char) 0,(char) 1,(char) 2,(char) 3,(char) 4,(char) 5,(char) 6,(char) 7,(char) 8,(char) 9,(char) 10,(char) 11,(char) 12,(char) 13,(char) 14,(char)
15,(char) 16,(char) 17,(char) 18,(char) 19,(char) 20,(char) 21,(char) 22,(char) 23,(char) 24,(char) 25,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1,(char)
-1,(char) 26,(char) 27,(char) 28,(char) 29,(char) 30,(char) 31,(char) 32,(char) 33,(char) 34,(char) 35,(char) 36,(char) 37,(char) 38,(char) 39,(char) 40,(char)
41,(char) 42,(char) 43,(char) 44,(char) 45,(char) 46,(char) 47,(char) 48,(char) 49,(char) 50,(char) 51,(char) -1,(char) -1,(char) -1,(char) -1,(char) -1

		};
		return (((c) < 0 || (c) > 127) ? -1 : index_64[(c)]);
	}


	static tbool decode64(const char *in, unsigned long inlen, char *out, unsigned long *outlen)
	{
		unsigned int   len = 0;
		unsigned int lup;
		int   c1,	 c2,	 c3,	 c4;

		
		if (in[0] == '+' && in[1] == ' ')
			in += 2;

		if (*in == '\0')
			return 0;

		for (lup = 0; lup < inlen / 4; lup++)
		{
			c1 = in[0];
			if (CHAR64(c1) == (char)-1)
				return 0;
			c2 = in[1];
			if (CHAR64(c2) == (char)-1)
				return 0;
			c3 = in[2];
			if (c3 != '=' && CHAR64(c3) == (char)-1)
				return 0;
			c4 = in[3];
			if (c4 != '=' && CHAR64(c4) == (char)-1)
				return 0;
			in += 4;
			*out++ = (CHAR64(c1) << 2) | (CHAR64(c2) >> 4);
			++len;
			if (c3 != '=')
			{
				*out++ = ((CHAR64(c2) << 4) & 0xf0) | (CHAR64(c3) >> 2);
				++len;
				if (c4 != '=')
				{
					*out++ = ((CHAR64(c3) << 6) & 0xc0) | CHAR64(c4);
					++len;
				}
			}
		}

		*out = 0;                   
		*outlen = len;

		return 1;
	}


	static bool decode64( const std::string & strin, SCake & rtn_ck )
	{
		unsigned long i;

		rtn_ck.redim( (int)strin.size() );
		if( decode64( strin.c_str(), (int)strin.size(), rtn_ck.buf(), &i ) )
		{
			rtn_ck.redim( i, 1 );
			return 1;
		}

		return 0;
	}


	static std::string decode64str( const std::string & str_in ) 
	{
		SCake ck;
		if( !decode64( str_in, ck ) ) return "";
		return std::string( ck.buf(), ck.buf() + ck.len() );
	}


	
	static void seri( const std::vector< std::string > & v_in, std::string & rtn_str )
	{
		std::vector< std::string >::const_iterator it;

		rtn_str = "";
		for( it = v_in.begin(); it != v_in.end(); ++it )
		{
			rtn_str += encodebase64str(*it);
			rtn_str += "}";
		}
	}

	
	static void unseri( const std::string & str_in , std::vector< std::string > & v_rtn )
	{
		v_rtn.clear();
		SStrvs::vsa_imp( str_in, std::string("}"), 0, v_rtn );

		std::vector< std::string >::iterator it;

		for( it = v_rtn.begin(); it != v_rtn.end(); ++it )
		{
			*it = decode64str( *it );
		}

		if( !v_rtn.empty() ) v_rtn.pop_back();
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_sdte_h
#define X011__H_w_sdte_h



X011_NAMESPACE_BEGIN


class SDte_bare
{
public:
	int m_year;
	int m_mon;
	int m_day;
	int m_hour;
	int m_min;
	int m_sec;
	
};


class SDte : public SDte_bare
{


public:

private:

	static tbool d_is_leap_year(int y)
	{
		
		

		return ( y % 400 == 0 ) ||
				( ( y % 4 == 0 ) && ( y % 100 != 0 ) );
	}


	static int d_day_of_year(int y)
	{
		return d_is_leap_year(y)?366:365;
	}


	static int d_day_of_month(int y, int m)
	{
		tint8 Array[]={0, 31, 28, 31,30,31,30,31,31,30,31,30,31};
		if(m<1||m>12) m=1;
		return (int)(m==2 ? Array[m] + (d_is_leap_year(y)?1:0) : Array[m]);
	}


	static tchar * d_odget( SCakel_base<tchar> & abuf, tint32 od )
	{
		abuf.add( SCake_base<tchar>("000000000") );
		if(od<0) od *= -1;
		abuf.add( SCake_base<tchar>( SStrf::sltoa(od) ) );
		abuf.collects( );
		return abuf.get( )->buf( );
	}


	static time_t dt_mk(void)
	{
		struct tm tmm, *tp;
		time_t timer;
		time(&timer);
		tp = (*SClib::p_localtime())(&timer);
		memcpy(&tmm, tp, sizeof(struct tm));
		return mktime(&tmm);
	}


	static int dt_mk( struct tm *ptm , time_t tmr)
	{
		struct tm *tp;
		tp = (*SClib::p_localtime())(&tmr);
		if(ptm!=NULL&&tp!=NULL) memcpy(ptm, tp, sizeof(struct tm));
		return tp!=NULL;
	}


	static void dt_mknow( int& y, int&m, int& d, int& hh, int& mi, int& ss ) 
	{
		struct tm tmm;
		struct tm *tp;
		memset(tp=&tmm, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		y = tp->tm_year+1900;
		m = tp->tm_mon+1;
		d = tp->tm_mday;
		hh = tp->tm_hour;
		mi = tp->tm_min;
		ss = tp->tm_sec;
	}

	

	static struct tm & RegulateTmYear4( struct tm & t )
	{
		if( t.tm_year <= 999 )
		{
			t.tm_year += 1900;
		}
		return t;
	}

	static struct tm & RegulateTmYear2( struct tm & t )
	{
		if( t.tm_year > 1900 )
		{
			t.tm_year -= 1900;
		}
		return t;
	}


	static struct tm & Now( struct tm & t )
	{
		struct tm *tp;
		memset(tp=&t, 0, sizeof(struct tm));
		dt_mk(tp, dt_mk());
		tp->tm_year+=1900;
		return t;
	}


	
	static time_t tm2l( struct tm t )
	{
		RegulateTmYear2(t);

		return mktime(&t);	
	}


	static struct tm l2tm( time_t tmr )
	{
		struct tm *tp;
		struct tm tm2;

		SStrf::smemset(tm2);

		
		tp = (*SClib::p_localtime())(&tmr);

		if(tp!=NULL) memcpy(&tm2, tp, sizeof(struct tm));

		return tm2;
	}


	static tint32 idmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int y, m, d;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d", &y, &m, &d );
		return idmk(y,m,d);
	}


	static tint32 idmk(int y, int m, int d, tint32 offset=0)
	{
		tint32 i,j;
		for(j=0,i=0;i<=(y-1);i++) j += d_day_of_year(i);
		for(i=1;i<=(m-1);i++) j += d_day_of_month(y,i);
		return j = j + d + offset;
	}


	static int odgety( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,3);
		*t=0;
		return (int)SStrf::satol(t-4);
	}


	static int odgetm( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,1);
		*t=0;
		return (int)SStrf::satol(t-2);
	}


	static int odgetd( tint32 od )
	{
		tchar *t;
		SCakel_base<tchar> abuf;
		t = d_odget( abuf, od );
		t = SStrf::splast(t,0);
		return (int)SStrf::satol(t-1);
	}


	static tint32 id2o( tint32 id )
	{
		tint32 i1, i2, i3, i4;
		if(id<=0) 	 id=1;
		for(i1=0;id>d_day_of_year(i1);) {
			id -= d_day_of_year(i1);
			i1++;
		}
		for(i2=1;id>d_day_of_month(i1,i2);) {
			id -= d_day_of_month(i1,i2);
			i2++;
		}
		i3 = id;
		return i4 = 10000*i1 + 100*i2 + i3;
	}


	static tint32 od2i( tint32 od )
	{
		return idmk( odgety(od), odgetm(od), odgetd(od) );
	}


	static int idgety( tint32 id ) { return odgety( id2o(id) ); }

	static int idgetm( tint32 id ) { return odgetm( id2o(id) ); }

	static int idgetd( tint32 id ) { return odgetd( id2o(id) ); }

	static tint32 idnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return idmk(y,m,d); }

	static tint32 odnow( ) { return id2o(idnow()); }



	static tint32 itmk( const tchar * sDateTime )
	{
		if(!sDateTime) return 0;
		int h, m, s, i;
		(*SClib::p_sscanf())( sDateTime, "%d-%d-%d %d:%d:%d", &i, &i, &i, &h, &m, &s );
		return itmk(h, m, s);
	}


	static tint32 itmk(int h, int m, int s)
	{
		return h*60*60+m*60+s;
	}

	static tint32 itgeth(tint32 it)		{	return it/3600; 	}

	static tint32 itgetm(tint32 it)		{	return it%3600/60; 	}

	static tint32 itgets(tint32 it)		{	return it%60;	}


	static tint32 it2o(tint32 it)
	{
		tchar s[7];
		(*SClib::p_sprintf())( s, "%02d%02d%02d", itgeth(it), itgetm(it), itgets(it) );
		return SStrf::satol(s);
	}


	static tint32 ot2i(tint32 ot)
	{
		SCake_base<tchar> ca("000000", 6);
		ca.append( SCake_base<tchar>(SStrf::sltoa(ot)) );
		int h,m,s;
		(*SClib::p_sscanf())( SStrf::splast(ca.buf(), 5), "%2d%2d%2d", &h,&m,&s);
		return itmk(h,m,s);
	}


	static tint32 itnow( ) { int y,m,d,hh,mi,ss; dt_mknow(y,m,d,hh,mi,ss); return itmk(hh,mi,ss); }

	static tint32 otnow( ) { return it2o(itnow()); }

	static tdouble iemk( tint32 id, tint32 it) { return  id + (tdouble)it/(tdouble)86400; }


	static tdouble ie2o( tint32 id, tint32 it)
	{
		tint8 s[16];
		(*SClib::p_sprintf())(s, "%ld.%06ld", id2o(id), it2o(it) );
		return SStrf::satof(s);
	}

	static tdouble ie2o(tdouble ie)
	{
		tdouble d1, d2;
		d1 = floor(ie);
		d2 = 0.5 + ( (ie - floor(ie)) * 86400 ) ;
		return ie2o((tint32)d1, (tint32)d2);
	}


	static tdouble oe2i(double oe)
	{
		tdouble od, ot;
		od = floor(oe);
		ot = 0.5 + ( (oe - floor(oe)) * 1e6 ) ;
		return iemk( od2i((tint32)od), ot2i((tint32)ot) );
	}


	static tdouble ienow()
	{
		return iemk( idnow(), itnow() );
	}


	static tdouble oenow()
	{
		return ie2o( ienow() );
	}


	static std::string Db_oe( tint32 idNow=0, tint32 itNow=-1 ) 
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 idgety(idNow), idgetm(idNow), idgetd(idNow),
					 itgeth(itNow), itgetm(itNow), itgets(itNow)	);
		return sBuf;
	}


	static std::string Pack_oe( tint32 idNow=0, tint32 itNow=-1 ) 
	{
		if(idNow==0 ) idNow=idnow();
		if(itNow==-1) itNow=itnow();
		return  SStrf::sftoa( ie2o( iemk( idNow, itNow ) ) );
	}


public:

	SDte()
	{
		m_year= 0;
		m_mon= 0;
		m_day= 0;
		m_hour= 0;
		m_min= 0;
		m_sec= 0;
		
	}

	SDte( std::string str_dte )
	{
		if(str_dte=="") this->MakeNow();
		else
			Make( str_dte );
	}

	SDte( int iHour, int iMin, int iSec )
	{
		this->MakeNow();
		this->m_hour= iHour;
		this->m_min= iMin;
		this->m_sec= iSec;
	}

	virtual ~SDte() { ; }


	static double e_proctime()  
	{
		return (double)clock()/(double)CLOCKS_PER_SEC;
	}

	static int Get_msec() 
	{
		struct timeval t_start;
		gettimeofday(&t_start, NULL);
		return (int)(t_start.tv_usec/1000);
	}

	static std::string Get_now_mtime( int wei = 2 ) 
	{
		int i = Get_msec();
		char ss[33];
		sprintf( ss, "%s.%03d", (SDte::GetNow().ReadStringPack().c_str() + 9),i );
		if( wei == 2 ) ss[9] = 0;
		return ss;
	}


	SDte & Make( std::string str_dte )
	{
		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) != std::string::npos ) 
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d %d:%d:%d", &m_year, &m_mon, &m_day, &m_hour, &m_min, &m_sec );
			return *this;
		}

		if( str_dte.find( "-" ) != std::string::npos && str_dte.find( ":" ) == std::string::npos ) 
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d-%d-%d", &m_year, &m_mon, &m_day );
			m_hour = 	m_min = m_sec = 0;
			return *this;
		}

		if( str_dte.find( "-" ) == std::string::npos && str_dte.find( ":" ) != std::string::npos ) 
		{
			(*SClib::p_sscanf())( str_dte.c_str(), "%d:%d:%d", &m_hour, &m_min, &m_sec );
			m_year = m_mon = m_day = 0;
			return *this;
		}

		tint32 oiid, oiit;

		if( str_dte.find( " " ) != std::string::npos ) 
		{
			oiid = (tint32)SStrf::satol( SStrvs::vsa_get( str_dte, std::string(" "), 1, 0 ) );
			oiit = (tint32)SStrf::satol( SStrvs::vsa_get( str_dte, std::string(" "), 1, 1 ) );
		}
		else
		{
			oiid = (tint32)SStrf::satol( str_dte );
			oiit = 0;
		}

		oiid = this->od2i( oiid );
		oiit = this->ot2i( oiit );

		m_year = idgety( oiid );
		m_mon  = idgetm( oiid );
		m_day  = idgetd( oiid );

		m_hour = itgeth( oiit );
		m_min = itgetm(  oiit );
		m_sec = itgets(  oiit );



		tint32 i;

		i = itmk( m_hour, m_min, m_sec );
		m_day += i / 86400;
		i %= 86400;
		m_hour = itgeth( i );
		m_min = itgetm( i );
		m_sec = itgets( i );

		i = idmk( m_year, m_mon, m_day );
		m_year = idgety( i );
		m_mon  = idgetm( i );
		m_day  = idgetd( i );


		return *this;
	}


	static tbool IsValidDate( std::string strVal ) 
	{
		if( strVal.length() != 8 ) return 0;
		std::string s1,s2;
		SDte d1;
		s1 = strVal + " 001122";
		d1.Make( s1 );
		s2 = d1.ReadStringPack();
		SStrf::sreplstr( s1, " ", "." );
		if( s1 != s2 ) return 0;
		return 1;
	}


	static tbool IsValidTime( std::string strVal ) 
	{
		if( strVal.length() != 6 ) return 0;

		std::string s1 ;

		s1 = strVal.substr( 0, 2 );
		int i1 = SStrf::satol( s1 );
		if( i1 >= 24 ) return 0;

		s1 = strVal.substr( 2, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		s1 = strVal.substr( 4, 2 );
		i1 = SStrf::satol( s1 );
		if( i1 >= 60 ) return 0;

		return 1;
	}



	static tbool IsValidDateTime( std::string strVal ) 
	{
		if( strVal.length() != 14 ) return 0;

		std::string s1,s2;
		SDte d1;
		s2 = strVal;
		s2.insert( 8, " " );
		d1.Make( s2 );
		s1 = d1.ReadStringPack();
		SStrf::sreplstr( s2, " ", "." );
		if( s1 != s2 ) return 0;
		return 1;
	}




	SDte & MakeNow()
	{
		struct tm  tnow;
		this->Now(tnow);
		m_year= tnow.tm_year;
		m_mon = tnow.tm_mon+1;
		m_day = tnow.tm_mday;
		m_hour= tnow.tm_hour;
		m_min = tnow.tm_min;
		m_sec = tnow.tm_sec;
		return *this;
	}


	static SDte GetNow()  
	{
		SDte s;
		return s.MakeNow();
	}


	tint32 DiffDay( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = this->idmk( m_year, m_mon, m_day ) ;
		d2 = dte2.idmk( dte2.m_year, dte2.m_mon, dte2.m_day ) ;

		return d1 - d2;
	}


	tdouble DiffSec( const SDte & dte2 ) const
	{
		tdouble d1, d2;

		d1 = (double)this->itmk( m_hour, m_min, m_sec );
		d2 = (double)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400.0;
	}


	tint32 DiffSecInt( const SDte & dte2 ) const
	{
		tint32 d1, d2;

		d1 = (tint32)this->itmk( m_hour, m_min, m_sec );
		d2 = (tint32)dte2.itmk( dte2.m_hour, dte2.m_min, dte2.m_sec );

		return d1 - d2 + DiffDay(dte2) * 86400;
		
	}


	static tint32 DiffSecToday()
	{
		SDte a;
		return a.itnow();
	}

	
	static tint32 DiffSecOf1day(SDte dt) 
	{
		SDte a=dt;
		SDte b=a;
		b.m_hour=b.m_min=b.m_sec=0;
		return a.DiffSecInt(b);
	}

	
	static tint32 DiffSecOf1day( std::string strTime ) 
	{
		SDte a;
		if( strTime.find( ":" ) != std::string::npos ) 
		{
			(*SClib::p_sscanf())( strTime.c_str(), "%d:%d:%d", &a.m_hour, &a.m_min, &a.m_sec );
			a.m_year = a.m_mon = a.m_day = 0;
			return a.m_hour * 60 * 60 + a.m_min * 60 + a.m_sec;
		}
		return 0;
	}


	int WeekDay() const
	{
		int i2 = this->DiffDay( wl::SDte() );
		return (i2 - 2 ) % 7;
	}


	SDte & Relative_internal( const SDte & dte2 )
	{
		m_year += dte2.m_year;
		m_mon  += dte2.m_mon;
		m_day  += dte2.m_day;
		m_hour += dte2.m_hour;
		m_min  += dte2.m_min;
		m_sec  += dte2.m_sec;

		tint32 i;

		i = itmk( m_hour, m_min, m_sec );
		m_day += i / (int)86400;
		i %= (int)86400;
		m_hour = itgeth( i );
		m_min = itgetm( i );
		m_sec = itgets( i );

		i = idmk( m_year, m_mon, m_day );
		m_year = idgety( i );
		m_mon  = idgetm( i );
		m_day  = idgetd( i );

		return *this;
	}

	SDte & Relative( const SDte & dte2 )
	{
		Relative_internal(dte2);

		if( this->m_hour < 0 || this->m_min < 0 || this->m_sec < 0 )
		{
			SDte dte2;
			dte2.m_year = dte2.m_mon = dte2.m_day = dte2.m_hour = dte2.m_min = 0;
			dte2.m_sec = (int)-86400;
			this->Relative_internal( dte2 );
			dte2.m_sec = (int)86400;
			this->Relative_internal( dte2 );
		}

		return *this;
	}


	SDte & RelativeDay( toffset day2 )
	{
		SDte dte2;
		dte2.m_year = dte2.m_mon = dte2.m_day = dte2.m_hour = dte2.m_min = 0;
		dte2.m_day = (int)day2;
		return Relative(dte2);
	}


	SDte & RelativeSec( toffset sec2 )
	{
		SDte dte2;
		dte2.m_year = dte2.m_mon = dte2.m_day = dte2.m_hour = dte2.m_min = 0;
		dte2.m_sec = (int)sec2;
		return Relative(dte2);
	}

	
	SDte & RelativeSecFF( tuint32 sec2 ) 
	{
		this->RelativeSec( sec2 / 3 );
		this->RelativeSec( sec2 / 3 );
		this->RelativeSec( sec2 / 3 );
		return this->RelativeSec( sec2 -  sec2 / 3 * 3 );
	}


	std::string ReadString() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 m_year, m_mon, m_day,
					 m_hour, m_min, m_sec	);
		return sBuf;
	}


	std::string ReadStringTw( tbool IsShortFmt = 1 ) const 
	{
		tchar sBuf[33];
		if( IsShortFmt )
		{
			(*SClib::p_sprintf())(sBuf,"%d/%02d/%02d %02d:%02d",
						 m_year, m_mon, m_day,
						 m_hour, m_min	);
		}
		else
		{
			(*SClib::p_sprintf())(sBuf,"%d/%02d/%02d %02d:%02d:%02d",
						 m_year, m_mon, m_day,
						 m_hour, m_min	, m_sec	);
		}
		return sBuf;
	}


	std::string ReadStrDate() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d",
					 m_year, m_mon, m_day );
		return sBuf;
	}

	
	std::string ReadStrTime() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d:%02d:%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	
	std::string ReadStringPack( char c = '.' ) const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d%c%02d%02d%02d",
					 m_year, m_mon, m_day,  c ,
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	
	std::string ReadStringPack14() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d%02d%02d%02d",
					 m_year, m_mon, m_day ,
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	
	std::string ReadStrPackDate() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d%02d%02d",
					 m_year, m_mon, m_day 	);
		return sBuf;
	}

	
	std::string ReadStrPackTime() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%02d%02d%02d",
					 m_hour, m_min, m_sec	);
		return sBuf;
	}

	
	std::string Read_dt1() const 
	{
		tchar sBuf[33];
		const tchar *s2[] = {"aa","Jan", "Feb","Mar","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
		(*SClib::p_sprintf())(sBuf,"%d-%s-%d",
								m_day, s2[m_mon], m_year );
		return sBuf;
	}

	
	void GetBcdArr( SCake & ck ) const 
	{
		std::string s1 = ReadStringPack14();
		std::vector<std::string> vec1;

		SStrvs::vsa_impbylen( s1, 2, vec1 );

		s1="";
		for( std::vector<std::string>::size_type i = 0; i < vec1.size(); i++ )
		{
			s1 += vec1[i] + " ";
		}
		ck.ConvStr2Bin(s1);
	}

	
	void GetBcdArr( std::vector<tuint8> & v ) const 
	{
		SCake ck;
		GetBcdArr(ck);
		v.resize(7);
		std::copy( (tuint8*)(ck.buf()), (tuint8*)(ck.buf() + ck.len()), v.begin() );
	}

	
	operator std::string () const
	{
		return ReadStringPack() ;
	}

	
	bool operator != (const SDte & rhs) const { return this->ReadStringPack() != rhs.ReadStringPack(); }
	bool operator == (const SDte & rhs) const { return this->ReadStringPack() == rhs.ReadStringPack(); }
	bool operator >= (const SDte & rhs) const { return this->ReadStringPack() >= rhs.ReadStringPack(); }
	bool operator <= (const SDte & rhs) const { return this->ReadStringPack() <= rhs.ReadStringPack(); }
	bool operator > (const SDte & rhs) const  { return this->ReadStringPack() >  rhs.ReadStringPack(); }
	bool operator < (const SDte & rhs) const  { return this->ReadStringPack() <  rhs.ReadStringPack(); }

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_sfile_h
#define X011__H_w_sfile_h



X011_NAMESPACE_BEGIN


class SFile
{

private:

	std::string m_strFilename;

public:

	SFile()
	{
		bind("");
	}


	SFile( std::string fn )
	{
		bind(fn);
	}


	virtual ~SFile()
	{ ;
	}


	static std::string GetPathSep()
	{
		return "/";
	}


	static std::string MkDir2Path( std::string strPathOrDir )
	{
		if( strPathOrDir.length() )
		{
			const tchar * t;
			t = SStrf::splast( strPathOrDir.c_str() );
			if( *t == GetPathSep()[0] )
			{
				return strPathOrDir;
			}
		}

		return strPathOrDir + GetPathSep();
	}



	static void Dir2Path( std::string & strPathOrDir )
	{
		strPathOrDir = MkDir2Path(strPathOrDir);
	}

	
	static std::string GetOnlyname( std::string strPfn )
	{
		std::string strChar=GetPathSep();
		std::string::size_type nPos;
		nPos = strPfn.find_last_of( strChar[0] );
		if( nPos != std::string::npos )
		{
			return &(strPfn[nPos+1] );
		}
		return strPfn.c_str();
	}
	
	std::string GetOnlyname() const
	{
		return GetOnlyname(filename());
	}

	
	static std::string GetPath( std::string strPfn )
	{
		std::string strChar=GetPathSep();
		std::string::size_type nPos;
		nPos = strPfn.find_last_of( strChar[0] );
		if( nPos != std::string::npos )
		{
			strPfn[nPos+1] = 0;
		}
		return strPfn.c_str();
	}
	
	std::string GetPath() const
	{
		return GetPath(filename());
	}

	
	static std::string GetDir( std::string strPfn )
	{
		std::string strChar=GetPathSep();
		std::string::size_type nPos;
		nPos = strPfn.find_last_of( strChar[0] );
		if( nPos != std::string::npos )
		{
			strPfn[nPos+0] = 0;
		}
		return strPfn.c_str();
	}
	
	std::string GetDir() const
	{
		return GetDir(filename());
	}


	void bind( std::string fn )
	{
		m_strFilename = fn;
	}


	tbool bind_nofile( std::string strPath, const tchar * pszExt = NULL , int iThreadId = 0 ) 
	{
		static int iName1 = 0;
		tdouble dName2;
		int k=0;
		std::string strNameExt(pszExt?pszExt:".tmp");
		std::string strGoodPathfilename;

		
		strPath = MkDir2Path( strPath );

		if( pszExt && *pszExt!='.' ) strNameExt = std::string(".") + pszExt;

		do
		{
			iName1--;
			dName2 = SStrf::rand1();
			strGoodPathfilename = strPath + "h" + SStrf::sltoa(iName1) + "_" + SStrf::sltoa(iThreadId) + SStrf::sftoa(dName2) + strNameExt;
			bind(strGoodPathfilename);
			if(canoutput()) return 1;
			if( k ++ > 9 )
			{
				if(!erase())
				{
					bind("");
					return 0;
				}
			}
		}while(1);
	}


	std::string filename() const
	{
		return m_strFilename;
	}


	
	


	operator std::string () const
	{
		return m_strFilename;
	}

	
	operator const tchar * () const
	{
		return m_strFilename.c_str();
	}


	static tbool erase(std::string strfilename)
	{
		return 0==remove( strfilename.c_str() )?1:0;
	}

	
	tbool erase()
	{
		return 0==remove( m_strFilename.c_str() )?1:0;
	}


	tbool exists()
	{
		FILE *fp;
		tbool rc;
		if( m_strFilename=="" )
		{
			return 0;
		}
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if(fp==NULL) rc=0;
		if(fp!=NULL)
		{
			rc=1; fclose(fp);
		}
		return rc;
	}

	
	static tbool exists(std::string strfilename)
	{
		SFile fInFile;
		fInFile.bind( strfilename );
		return fInFile.exists();
	}


	tbool caninput()
	{
		return exists();
	}


	tbool canoutputabs()
	{
		FILE *fp;
		fp = (*SClib::p_fopen())(m_strFilename.c_str(),"wb");
		if(fp==NULL) return 0;
		fclose(fp);
		return erase();
	}


	tbool canoutput()
	{	
		if(exists()) return 0;
		return canoutputabs();
	}


	
	tsize len()
	{
		if( !exists() ) return 0;
		tsize flen;
		FILE *fp;
		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fclose(fp);
		return flen;
	}


	static tsize len( std::string strfilename )
	{
		SFile fInFile;
		fInFile.bind( strfilename );
		return fInFile.len();
	}


	
	tbool read( SCake & ckbuf, long iBeginOff, tsize iLenBytes )
	{
		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if( fp == NULL )
		{
			return 0;
		}

		fseek( fp, iBeginOff, SEEK_SET );

		ckbuf.redim( iLenBytes );
		SStrf::smemset( ckbuf.buf(), 0, iLenBytes );

		tsize a = (tsize)fread( ckbuf.buf(), 1, iLenBytes, fp );

		if( a == iLenBytes )
		{}
		else
		if( a == 0 )
		{
			ckbuf.redim(0);
		}
		else
		{
			ckbuf.cut( iLenBytes - a );
		}

		fclose(fp);

		return ckbuf.len() ? 1 : 0;
	}


	
	tbool read( SCake_base<tchar> & buf, tsize a_extra_bytes = 0 ) 
	{
		if(!this->exists()) return 0;

		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if( fp == NULL )
		{
			return 0;
		}

		tsize flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );


		
		
		

		buf.redim( flen + a_extra_bytes );

		if(a_extra_bytes)
		{
			SStrf::smemset( buf.buf(), 0, flen + a_extra_bytes ); 
			
		}

		if(flen) fread( buf.buf(), flen, 1, fp );

		fclose(fp);

		return 1;
	}


	tbool read( std::vector<char> & buf )
	{
		buf.clear();

		if(!this->exists()) return 0;

		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );

		if( fp == NULL )
		{
			return 0;
		}

		tsize flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );

		buf.resize( flen, 0 );

		if(flen)
			fread( &(buf[0]), flen, 1, fp );

		fclose(fp);

		return 1;
	}


	tbool read_str( SCake_base<tchar> & buf ) 
	{
		return this->read( buf, 1 );
	}


	tbool read_str( std::string & strRtnBuf )
	{
		
		
		
		
		
		

		
		strRtnBuf = "";

		if( !this->exists() ) return 0;
		FILE *fp;

		fp = (*SClib::p_fopen())( m_strFilename.c_str(), "rb" );
		if( fp == NULL )
		{
			return 0;
		}

		tsize flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );

		if( flen == 0)
		{
			fclose(fp);
			return 0 ;
		}

		strRtnBuf.resize( flen , 0 );

		if(flen) fread( &(strRtnBuf[0]), flen, 1, fp );

		fclose(fp);

		return 1;
	}


	tbool read_bs( std::string & strRtnBs )
	{
		SCake ck;

		if( !this->read( ck ) ) return 0;
		strRtnBs = ck.len() ? ck.bs_en().buf() : "";

		return 1;
	}


	tbool read_vecstr( std::vector<std::string> & vecLines, std::string strSep, tbool istoken = 1 )
	{
		wl::SCake ckData;
		if( !read_str( ckData ) ) return 0;
		if( !ckData.len() ) return 0;
		SStrvs::vsa_imp( std::string(ckData.buf()), strSep, istoken, vecLines );
		return 1;
	}


	
	std::string read_dseal( int outlen )
	{
		SCake ck;
		read(ck);
		if( ck.len() == 0 ) return "";
		return SCalc::dseal( ck.buf(), ck.len(), outlen );
	}

	
	std::string read_dseal2( int outlen )
	{
		SCake ck;
		read(ck);
		if( ck.len() == 0 ) return "";
		return SCalc::dseal2( ck.buf(), ck.len(), outlen );
	}

	
	std::string read_dseal3( int outlen )
	{
		SCake ck;
		read(ck);
		if( ck.len() == 0 ) return "";
		return SCalc::dseal3( ck.buf(), ck.len(), outlen );
	}


	tbool write( const void * pbuf, tsize len, tbool bIsAppend = 0 ) 
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( len == 0 ) break;
			if( !pbuf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( pbuf, len, 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}


	tbool write( const SCake_base<tchar> & buf, tbool bIsAppend = 0 ) 
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( buf.len()==0 ) break;
			if( !buf.buf_const() ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			rc = fwrite( buf.buf_const(), buf.len(), 1, fp )?1:0 ;
			fclose(fp);
		}while(0);

		return rc?1:0 ;
	}


	tbool write() 
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			fp = (*SClib::p_fopen())( m_strFilename.c_str( ), "wb" );
			if(fp==NULL) break;
			fclose(fp);
			rc = 1;
		}while(0);

		return rc?1:0 ;
	}


	
	tbool write_bs( const std::string & strBs )
	{
		SCake ck;

		ck.lets( strBs );
		ck.bs_de();

		return write(ck);
	}


	tbool write_str( const tchar * buf, tbool bIsAppend = 0 )
	{
		FILE *fp;
		tbool rc;

		rc=0;

		do
		{
			if( NULL == buf ) break;
			fp = (*SClib::p_fopen())( m_strFilename.c_str(), bIsAppend?"ab":"wb" );
			if(fp==NULL) break;
			if( fwrite( buf, SStrf::slen(buf), 1, fp ) )
			{
				rc = 1;
			}
			else
			{
				rc = 0;
			}
			fclose(fp);

		}while(0);

		return rc?1:0 ;
	}


	tbool write_str( const std::string & buf, tbool bIsAppend = 0 )
	{
		return write_str( buf.c_str(), bIsAppend );
	}


	tbool write_vecstr( const std::vector<std::string> & vecLines, std::string strSep, tbool bIsAppend = 0 )
	{
		std::string strOut;

		for( std::vector<std::string>::const_iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			if( it == (vecLines.end() - 1) && it->empty() )
			{
			}
			else
				strOut += *it + strSep;
		}

		return write_str(strOut, bIsAppend);
	}


	
	tbool cp( std::string strFnSource, std::string strFnDest )
	{
		SCake buf;
		this->bind(strFnSource);
		this->read( buf );
		this->bind(strFnDest);
		return write(buf);
	}


	void cp( std::string strFnSource, std::string strFnDest1, std::string strFnDest2 )
	{
		SCake buf;
		this->bind(strFnSource);
		this->read( buf );
		this->bind(strFnDest1);
		write(buf);
		this->bind(strFnDest2);
		write(buf);
	}


	
	static tbool cp2( std::string strFnSource, std::string strFnDest )
	{
		FILE *fp1;
		FILE *fp2;
		SCake ckbuf;
		int iLenBytes = 128;

		fp1 = (*SClib::p_fopen())( strFnSource.c_str(), "rb" );
		if( fp1 == NULL )
			return 0;

		fp2 = (*SClib::p_fopen())( strFnDest.c_str(), "ab" );
		if( fp2 == NULL )
		{
			fclose(fp1);
			return 0;
		}

		ckbuf.redim( iLenBytes );
		SStrf::smemset( ckbuf.buf(), 0, iLenBytes );

		while(1)
		{
			tsize a = (tsize)fread( ckbuf.buf(), 1, iLenBytes, fp1 );

			if( a == iLenBytes )
			{
				fwrite( ckbuf.buf(), iLenBytes, 1, fp2 );
			}
			else if( a == 0 )
			{
				break;
			}
			else
			{
				fwrite( ckbuf.buf(), a, 1, fp2 );
				break;
			}
		}

		fclose(fp1);
		fclose(fp2);

		return 1;
	}


	
	tbool IsHeadOf( SFile & me2 )
	{
		if( !SStrf::scmpi( this->filename().c_str(), me2.filename().c_str() ) ) return 0; 
		if( !this->exists() ) return 0;
		if( !me2.exists()   ) return 0;

		tsize i1, i2;

		if( (i1 = this->len()) == 0 ) return 0;
		if( (i2 = me2.len()) == 0   ) return 0;

		if( i1 > i2 ) return 0;

		SCake ck1, ck2;

		this->read( ck1 );
		me2.read( ck2 );

		if( !memcmp( ck1.buf(), ck2.buf(), i1 ) ) return 1;

		return 0;
	}


	tbool IsHeadOf( std::string strme2 )
	{
		SFile sf2;
		sf2.bind(strme2);
		return IsHeadOf(sf2);
	}


	static std::string ReadFileStr( const std::string & Fn )
	{
		SFile fInFile;
		std::string	 strFileContent;
		fInFile.bind( Fn );
		fInFile.read_str( strFileContent );
		return strFileContent;
	}

};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_w_SBmp_h
#define X011__H_w_w_SBmp_h


X011_NAMESPACE_BEGIN


class SBmp
{
public:
	struct RGB_t
	{
		tuint8 R;
		tuint8 G;
		tuint8 B;
		tuint8 _reserved;
	};

private:
	char  m_ASC_ZK16_NOZK[66];
	char  m_HZ_ZK16_NOZK[66];

protected:
	char *	m_pASC_ZK16;
	char *	m_pHZ_ZK16;
	SCake * m_pckBuf;		
	int     m_iBufWidth;	

public:
	RGB_t   m_DefaultColor;
	int     m_iCHARGAP;

public:
	
	static RGB_t MKRGB( tuint8 R, tuint8 G, tuint8 B )
	{
		RGB_t t;
		t.R = R;  t.G = G; 	t.B = B;
		return t;
	}

	
	static int bitn(int c, int i) {c>>=i;c&=1;return c;}


	void InitZK( char *pASC, char *pHz, SCake * pckbuf=NULL, int iwidth = 0 ) 
	{
		m_pASC_ZK16 = pASC;
		m_pHZ_ZK16 = pHz;
		m_pckBuf = pckbuf;
		if(m_pckBuf)
			SStrf::smemset( m_pckBuf->buf(), 0xff, m_pckBuf->len() );
		m_iBufWidth = iwidth;
		
		
	}

	
	void SaveBufBmpOut( std::string strFn , SCake *pck = NULL, int iDepth = 3, int iBufWidth = 0 )
	{
		if( m_pckBuf || pck )
		{
			SFile fl;
			int width = iBufWidth != 0 ? iBufWidth : m_iBufWidth;

			if( pck == NULL )  pck =m_pckBuf;

			fl.bind( strFn );
			Conv2Bmp( *pck, width, iDepth ); 
			fl.write(*pck);
		}
	}

public:
	
	SBmp()
	{
		m_iCHARGAP = 1;

		m_pASC_ZK16 =
		m_pHZ_ZK16 = NULL;
		m_pckBuf = NULL;
		m_iBufWidth = 0;

		m_DefaultColor = MKRGB( 0x00, 0x0, 0x0 );


		SStrf::smemset( m_ASC_ZK16_NOZK, 0, 66 );
		SStrf::smemset( m_HZ_ZK16_NOZK, 0, 66 );
		m_ASC_ZK16_NOZK[7] = 0x40;
		m_HZ_ZK16_NOZK[7] = 0x40;
	}

	
	virtual ~SBmp()
	{ ;
	}


	
	static tbool Conv2Bmp( SCake & ckPicInOut, tsize iWidth, int iDepth , tbool turnUpDn = 1 )
	{
		int iBMHeaderSize = 0x36;
		if( ckPicInOut.len() == 0 ) return 0;
		if( !( iDepth == 1 || iDepth == 2 || iDepth == 3 || iDepth == 4 ) ) return 0;

		tsize i1, i2;
		tsize iWidthNew;
		tsize iHeight;
		std::vector < tuint8 > v1;
		std::vector < std::vector < tuint8 >::size_type > vIdx1; 
		std::vector < std::vector < tuint8 >::size_type > vIdx2;

		for( iWidthNew = iWidth; ; iWidthNew++ )
		{
			if( iWidthNew % 4 == 0 ) break;
		}

		i1 = 0;
		iHeight = 0;
		v1.resize( iBMHeaderSize, 0 );

		for( ; ; )
		{
			vIdx1.push_back( v1.size() );

			for( i2 = 0; i2 < iWidth; i2++ )
			{
				tuint8 ui1;

				if( iDepth == 1 )
				{
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					v1.push_back(0);
					v1.push_back(0);
				}

				if( iDepth == 2 )
				{
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					v1.push_back(0);
				}

				if( iDepth == 3 )
				{
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
				}

				if( iDepth == 4 )
				{
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					v1.push_back( ui1 );
					if( i1 < ckPicInOut.len() ) ui1 = *(tuint8*)(ckPicInOut.buf_const() + i1); else ui1 = 0;
					i1++;
					
				}
			}

			
			
			
			
			
			
			for( ;;)
			{
				std::vector < tuint8 >::size_type ioccupy = v1.size() - *vIdx1.rbegin();
				if( ioccupy % 4 == 0 ) break;
				v1.push_back(0);
			}

			iHeight++;

			if( i1 >= ckPicInOut.len() ) break;
		}

		
		if( turnUpDn )
		if( vIdx1.size() >= 2 )
		{
			long ilinelen = (long)(vIdx1[1] - vIdx1[0]);
			std::vector < tuint8 > vlinebuf;
			vlinebuf.resize(ilinelen);
			vIdx2 = vIdx1;
			std::reverse(vIdx2.begin(), vIdx2.end());

			for( i2 = 0; i2 < vIdx1.size() / 2 ; i2++ )
			{
				SStrf::smemcpy( &(vlinebuf[0]),  &(v1[vIdx1[i2]]), ilinelen );
				SStrf::smemcpy( &(v1[vIdx1[i2]]),  &(v1[vIdx2[i2]]), ilinelen );
				SStrf::smemcpy( &(v1[vIdx2[i2]]),  &(vlinebuf[0]), ilinelen );
			}
		}

		*(char*)(&(v1[0])) = 'B';
		*(char*)(&(v1[1])) = 'M';
		*(tuint32*)(&(v1[2])) = (tuint32)v1.size();
		
		

		*(tuint16*)(&(v1[6])) = 0;
		

		*(tuint16*)(&(v1[8])) = 0;
		

		*(tuint32*)(&(v1[0xA])) = 0x36;
		
		

		*(tuint32*)(&(v1[0xE])) = 0x28;
		
		

		*(tuint32*)(&(v1[0x12])) = (tuint32)iWidth;
		
		

		*(tuint32*)(&(v1[0x16])) = (tuint32)iHeight;
		
		

		*(tuint16*)(&(v1[0x1A])) = 1;
		

		*(tuint16*)(&(v1[0x1c])) = 24;
		

		*(tuint32*)(&(v1[0x1E])) = 0;
		
		

		*(tuint32*)(&(v1[0x22])) = (tuint32)v1.size() - 0x36;
		
		

		*(tuint32*)(&(v1[0x26])) = 0;
		
		

		*(tuint32*)(&(v1[0x2a])) = 0;
		
		

		*(tuint32*)(&(v1[0x2e])) = 0;
		
		

		*(tuint32*)(&(v1[0x32])) = 0;
		
		

		ckPicInOut.let( (tchar*)(&(v1[0])), (tuint32)v1.size() );

		return 1;
	}


	virtual tuint8 OnConv2Bmp32( long X, long Y )
	{
		return (tuint8)255;
	}

	
	tbool Conv2Bmp32( const SCake & ckIn, SCake & ckBmpOut, tsize iWidth, tbool turnUpDn = 1 )
	{
		int iBMHeaderSize = 0x36;
		if( ckIn.len() == 0 ) return 0;
		if( iWidth == 0 ) return 0;

		tsize i1, i2;
		tsize iHeight;
		std::vector < tuint8 > v1;
		std::vector < std::vector < tuint8 >::size_type > vIdx1; 
		std::vector < std::vector < tuint8 >::size_type > vIdx2;

		i1 = 0;
		iHeight = 0;
		v1.resize( iBMHeaderSize, 0 );

		for( ; ; )
		{
			vIdx1.push_back( v1.size() );

			for( i2 = 0; i2 < iWidth; i2++ )
			{
				tuint8 ui1;
				long X,Y,H;

				X = i1 / 3;
				Y = X / iWidth;
				H = ckIn.len() / 3 / iWidth;
				Y = H - Y - 1;

				

				
				if( i1 < ckIn.len() ) ui1 = *(tuint8*)(ckIn.buf_const() + i1); else ui1 = 0;
				i1++;
				v1.push_back( ui1 );

				if( i1 < ckIn.len() ) ui1 = *(tuint8*)(ckIn.buf_const() + i1); else ui1 = 0;
				i1++;
				v1.push_back( ui1 );

				if( i1 < ckIn.len() ) ui1 = *(tuint8*)(ckIn.buf_const() + i1); else ui1 = 0;
				i1++;
				v1.push_back( ui1 );

				
				ui1 = OnConv2Bmp32( X, Y );
				v1.push_back( ui1 );

			}

			
			for( ;;)
			{
				std::vector < tuint8 >::size_type ioccupy = v1.size() - *vIdx1.rbegin();
				if( ioccupy % 4 == 0 ) break;
				v1.push_back(0);
			}

			iHeight++;

			if( i1 >= ckIn.len() ) break;
		}

		
		if( turnUpDn )
		if( vIdx1.size() >= 2 )
		{
			long ilinelen = (long)(vIdx1[1] - vIdx1[0]);
			std::vector < tuint8 > vlinebuf;
			vlinebuf.resize(ilinelen);
			vIdx2 = vIdx1;
			std::reverse(vIdx2.begin(), vIdx2.end());

			for( i2 = 0; i2 < vIdx1.size() / 2 ; i2++ )
			{
				SStrf::smemcpy( &(vlinebuf[0]),  &(v1[vIdx1[i2]]), ilinelen );
				SStrf::smemcpy( &(v1[vIdx1[i2]]),  &(v1[vIdx2[i2]]), ilinelen );
				SStrf::smemcpy( &(v1[vIdx2[i2]]),  &(vlinebuf[0]), ilinelen );
			}
		}

		*(char*)(&(v1[0])) = 'B';
		*(char*)(&(v1[1])) = 'M';
		*(tuint32*)(&(v1[2])) = (tuint32)v1.size();
		
		

		*(tuint16*)(&(v1[6])) = 0;
		

		*(tuint16*)(&(v1[8])) = 0;
		

		*(tuint32*)(&(v1[0xA])) = 0x36;
		
		

		*(tuint32*)(&(v1[0xE])) = 0x28;
		
		

		*(tuint32*)(&(v1[0x12])) = (tuint32)iWidth;
		
		

		*(tuint32*)(&(v1[0x16])) = (tuint32)iHeight;
		
		

		*(tuint16*)(&(v1[0x1A])) = 1;
		

		*(tuint16*)(&(v1[0x1c])) = 32;
		

		*(tuint32*)(&(v1[0x1E])) = 0;
		
		

		*(tuint32*)(&(v1[0x22])) = (tuint32)v1.size() - 0x36;
		
		

		*(tuint32*)(&(v1[0x26])) = 0;
		
		

		*(tuint32*)(&(v1[0x2a])) = 0;
		
		

		*(tuint32*)(&(v1[0x2e])) = 0;
		
		

		*(tuint32*)(&(v1[0x32])) = 0;
		
		

		ckBmpOut.let( (tchar*)(&(v1[0])), (tuint32)v1.size() );

		return 1;
	}


	static tbool Conv2Ck( const SCake & ckBmpIn, SCake &ckOut, int & rtn_iWidth, int & rtn_iHeight, int & rtn_iDepth )
	{
		if( ckBmpIn.len() < 0x32 ) return 0;
		if( *ckBmpIn.buf_const() != 'B' ) return 0;
		if( *(ckBmpIn.buf_const()+1) != 'M' ) return 0;

		rtn_iWidth = *(tuint32*)(ckBmpIn.buf_const()+0x12);
		rtn_iHeight = *(tuint32*)(ckBmpIn.buf_const()+0x16);
		rtn_iDepth = *(tuint16*)(ckBmpIn.buf_const()+0x1c);

		if( rtn_iDepth == 24 )
		{
			rtn_iDepth = 3;
		}
		else if( rtn_iDepth == 32 )
		{
			rtn_iDepth = 4;
		}
		else return 0;

		tsize iWidthNew;

		for( iWidthNew = rtn_iWidth; ; iWidthNew++ )
		{
			if( iWidthNew % 4 == 0 ) break;
		}

		if( rtn_iDepth == 3 || rtn_iDepth == 4 ) 
		{
			if( ckBmpIn.len() < iWidthNew * rtn_iHeight * rtn_iDepth )
				return 0;

			ckOut.redim( rtn_iWidth * rtn_iHeight * rtn_iDepth );

			const char *p;
			char *p1;

			p = ckBmpIn.buf_const() + ckBmpIn.len();
			p -= iWidthNew * rtn_iDepth;
			p1 = ckOut.buf();

			for( int j = 0; j < rtn_iHeight; j++ )
			{
				SStrf::smemcpy( p1, p, rtn_iWidth * rtn_iDepth );
				p -= iWidthNew * rtn_iDepth;
				p1 += rtn_iWidth * rtn_iDepth;
			}

			return 1;
		}

		if( rtn_iDepth == 4 )
		{
			return 0;
		}

		return 0;
	}


	static tbool Ck4Ck3( const SCake & ckIn, int iWidthIn, SCake & ckOut )
	{
		int x2,y2;
		const tchar *p1;
		tchar *p2;
		int iHeightIn;

		if( (ckIn.len() % (iWidthIn*4)) != 0 )
			return 0;

		iHeightIn = ckIn.len() / (iWidthIn*4);

		ckOut.redim( ckIn.len() / 4 * 3 );

		for( x2 = 0; x2 < iWidthIn; x2++ )
		{
			for( y2 = 0; y2 < iHeightIn; y2++ )
			{
				p1 = ckIn.buf_const() + ( iWidthIn * y2 + x2 ) * 4;

				p2 = ckOut.buf() + ( iWidthIn * y2 + x2 ) * 3;

				*p2 = *p1;  p1++; p2++;
				*p2 = *p1;  p1++; p2++;
				*p2 = *p1; 
			}
		}

		return 1;
	}


	static tbool Turn_180( const SCake & ckIn, SCake & ckOut )
	{
		const tchar *p1;
		tchar *p2;
		tsize i;

		ckOut.redim( ckIn.len() );

		if( (ckIn.len() % 3) != 0 )
		{
			p1 = ckIn.buf_const();
			p2 = ckOut.buf() + ckOut.len() - 1;

			for( i = 0; i < ckIn.len(); i++ )
			{
				*p2 = *p1;
				p1++;
				p2--;
			}
		}
		else
		{
			p1 = ckIn.buf_const();
			p2 = ckOut.buf() + ckOut.len() - 3;

			for( i = 0; i < ckIn.len(); i+=3 )
			{
				*p2 = *p1;
				p1++; p2++;
				*p2 = *p1;
				p1++; p2++;
				*p2 = *p1;
				p1++; p2++;
				p2 -= 3;
				p2 -= 3;
			}
		}

		return 1;
	}


	static tbool Turn_p90( const SCake & ckIn, int iWidthIn, SCake & ckOut, int & rtn_iWidthOut )
	{
		const tchar *p1;
		tchar *p2;
		int iHeightIn;
		int iHeightOut;
		int x,y;
		int x2,y2;

		if( (ckIn.len() % (iWidthIn*3)) != 0 )
			return 0;

		iHeightIn = ckIn.len() / (iWidthIn*3);
		rtn_iWidthOut = iHeightIn;
		iHeightOut = iWidthIn;

		ckOut.redim( ckIn.len() );
		for( y = 0; y < iHeightIn; y++ )
		{
			for( x = 0; x < iWidthIn; x++ )
			{
				p1 = ckIn.buf_const() + ( iWidthIn * y + x ) * 3;
				x2 = iHeightIn - 1 - y;
				y2 = x;
				p2 = ckOut.buf() + ( rtn_iWidthOut * y2 + x2 ) * 3;

				*p2 = *p1;  p1++; p2++;
				*p2 = *p1;  p1++; p2++;
				*p2 = *p1; 
			}
		}

		return 1;
	}


	virtual void On_Add_pic_func( int x, int y, tuint8 *pcMain, const tuint8 *pcSub )
	{
		*pcMain = *pcSub;  pcMain++; pcSub++;
		*pcMain = *pcSub;  pcMain++; pcSub++;
		*pcMain = *pcSub;
	}

	
	tbool Add_pic( SCake & ckMain, int iWidthMain, int x, int y, const SCake & ckSub, int iWidthSub )
	{
		int x3,y3; 
		int x2,y2; 
		tchar *p1;
		const tchar *p2;

		if( (ckMain.len() % (iWidthMain*3)) != 0 )
			return 0;

		if( (ckSub.len() % (iWidthSub*3)) != 0 )
			return 0;

		int HeightMain = ckMain.len() / (iWidthMain*3);
		int HeightSub = ckSub.len() / (iWidthSub*3);

		y3 = HeightSub + y;
		if( y3 > HeightMain ) y3 = HeightMain;

		x3 = iWidthSub + x;
		if( x3 > iWidthMain ) x3 = iWidthMain;

		for( x2 = x; x2 < x3; x2 ++ )
		{
			for( y2 = y; y2 < y3; y2 ++ )
			{
				p1 = ckMain.buf() + ( iWidthMain * y2 + x2 ) * 3;

				p2 = ckSub.buf_const() + ( iWidthSub * (y2-y) + (x2-x) ) * 3;

				On_Add_pic_func( x2, y2, (tuint8 *)p1, (const tuint8 *)p2 );
			}
		}

		return 1;
	}

	
	tbool Cut_pic( const SCake & ckIn, int iWidthIn, int x, int y, int iCutWidth, int iCutHeight, SCake & ckOut, int & iWidthOut )
	{
		int x3,y3;
		int x2,y2;
		const tchar *p1;
		tchar *p2;
		int iHeightIn;

		if( (ckIn.len() % (iWidthIn*3)) != 0 )
			return 0;

		iHeightIn = ckIn.len() / (iWidthIn*3);

		y3 = iCutHeight + y;
		if( y3 > iHeightIn ) y3 = iHeightIn;

		x3 = iCutWidth + x;
		if( x3 > iWidthIn ) x3 = iWidthIn;

		ckOut.redim( (x3-x) * (y3-y) * 3 );
		iWidthOut = x3-x;

		for( x2 = x; x2 < x3; x2 ++ )
		{
			for( y2 = y; y2 < y3; y2 ++ )
			{
				p1 = ckIn.buf_const() + ( iWidthIn * y2 + x2 ) * 3;

				p2 = ckOut.buf() + ( iWidthOut * (y2-y) + (x2-x) ) * 3;

				*p2 = *p1;  p1++; p2++;
				*p2 = *p1;  p1++; p2++;
				*p2 = *p1; 
			}
		}

		return 1;
	}


	int out1hz( const char *phz, int x=0, int y=0 )
	{
		unsigned char *p = (unsigned char *)phz;
		int n=0, i=0;
		unsigned ch=0,we=0,xoff=0,yoff=0;
		unsigned char *c;
		long aa = 0;

		c = (unsigned char *)m_HZ_ZK16_NOZK;

		if( p[0] == 0xa1 && p[1] == 0xa3 )
		{
			p[0]=0xaa,p[1]=0xae;
		}

		if( (x+xoff) > 79 )
		{
			xoff=0;
			yoff++;
		}

		if( (*p) > 0xa1 )
		{
			ch = ( *p++ - 0xa1) & 0x7f;
			we = ( *p++ - 0xa1) & 0x7f;
			aa = ( ch * 94 + we ) * 32l;
			c = (unsigned char *)m_pHZ_ZK16 + aa;
		}

		if( !m_pHZ_ZK16 ) c = (unsigned char *)m_HZ_ZK16_NOZK;

		for( n = 0; n < 32; n++ )
		{
			for( i = 7; i >= 0; i-- )
			{
				if(bitn(c[n],i))
					OnPoint(x,y);
				else
					OnPoint_bg(x,y);
				x++;
			}
			n++;
			for( i = 7; i >= 0; i--)
			{
				if(bitn(c[n],i))
					OnPoint(x,y);
				else
					OnPoint_bg(x,y);
				x++;
			}
			y++;OnYpp(y);
			x -= 16;
		}
		return x;
	}

	
	int out1hz_scale( const char *phz, int x=0, int y=0, double dRateX = 1.0 , double dRateY = 1.0 )
	{
		int x_ori = x;
		double i = 0;
		double n = 0;
		unsigned char *p = (unsigned char *)phz;
		unsigned ch=0,we=0,xoff=0,yoff=0;
		unsigned char *c;
		long aa = 0;
		double dStep_x = 1.0 / dRateX ;
		double dStep_y = 1.0 / dRateY ;

		if( p[0] == 0xa1 && p[1] == 0xa3 )
		{
			p[0]=0xaa,p[1]=0xae;
		}
		if( (x+xoff) > 79 )
		{
			xoff=0;
			yoff++;
		}

		if( (*p) > 0xa1 )
		{
			ch = ( *p++ - 0xa1) & 0x7f;
			we = ( *p++ - 0xa1) & 0x7f;
			aa = ( ch * 94 + we ) * 32l;
			c = (unsigned char *)m_pHZ_ZK16 + aa;
		}

		if( !m_pHZ_ZK16 ) c = (unsigned char *)m_HZ_ZK16_NOZK;

		for( n = 0; n < 16; n += dStep_y )
		{
			for( i = 0; i < 16; i += dStep_x )
			{
				if( SStrf::readbit_r_p( c + ( ((int)n)*2) , (int)i ) )
					OnPoint( x,y );
				else
					OnPoint_bg(x,y);
				x++;
			}
			y ++; OnYpp(y);
			x = x_ori;
		}
		return x;
	}

	
	int out1asc( const char *pasc, int x=0, int y=0 )
	{
		unsigned char *p = (unsigned char *)pasc;
		int n=0,i=0;
		unsigned char *c;

		c = (unsigned char *)m_pASC_ZK16 + *p*16L;
		
		
		if( !m_pASC_ZK16 ) c = (unsigned char *)m_ASC_ZK16_NOZK;

		for(n=0;n<16;n++) {
		 for(i=7;i>=0;i--) {
				if(bitn(c[n],i)) OnPoint(x,y);
				else OnPoint_bg(x,y);
				x++;
		 }
		 x-=8;
		 y++;OnYpp(y);
		}
		return x;
	}


	int out1asc_scale( const char *pasc, int x=0, int y=0, double dRateX = 1.0 , double dRateY = 1.0 )
	{
		int x_ori = x;
		double i = 0.0;
		double n = 0.0;
		unsigned char *p = (unsigned char *)pasc;
		unsigned char *c;
		double dStep_x = 1.0 / dRateX ;
		double dStep_y = 1.0 / dRateY ;

		c = (unsigned char *)m_pASC_ZK16 + *p*16L;
		if( !m_pASC_ZK16 ) c = (unsigned char *)m_ASC_ZK16_NOZK;

		for( n = 0.0 ; n < 16.0 ; n += dStep_y )
		{
			for( i = 7.0 ; i >= 0.0 ; i -= dStep_x  )
			{
				if( bitn( c[(int)n], (int)i ) )
					OnPoint(x,y);
				else
					OnPoint_bg(x,y);

				x ++;
			}
			x = x_ori;
			y ++; OnYpp(y);
		}
		return x;
	}


	int OutText( const char *pstr, int x=0, int y=0, int RealDraw = 1 )
	{
		int CHARGAP = m_iCHARGAP;
		unsigned char *p = (unsigned char *)pstr;
		int pos;
		unsigned char c[2];
		for(pos=0;p[pos]!=0;pos++)if(iscntrl(p[pos]))p[pos]=' ';
		for(pos=0;p[pos]!=0;) {
			if(p[pos]>0xa0) {
					c[0]=p[pos];c[1]=p[pos+1];
					pos+=2;
					if(RealDraw) { out1hz((char*)c,x,y); OnZipp(x,y); }
					x+=16+ CHARGAP;
			}else{
					c[0]=p[pos++];
					c[1]=0;
					if(RealDraw) { out1asc((char*)c,x,y);OnZipp(x,y); }
					x+=8+ CHARGAP;
			}
		}
		return x;
	}

	
	int OutText_scale( const char *pstr, int x=0, int y=0, double dRateX = 1.0 , double dRateY = 1.0, int RealDraw = 1 )
	{
		int CHARGAP = m_iCHARGAP;
		unsigned char *p = (unsigned char *)pstr;
		int pos;
		unsigned char c[2];
		for(pos=0;p[pos]!=0;pos++)if(iscntrl(p[pos]))p[pos]=' ';
		for(pos=0;p[pos]!=0;) {
			if(p[pos]>0xa0) {
					c[0]=p[pos];c[1]=p[pos+1];
					pos+=2;
					if(RealDraw) { out1hz_scale((char*)c,x,y,dRateX,dRateY); OnZipp(x,y); }
					x += (16*(int)dRateX) + CHARGAP;
			}else{
					c[0]=p[pos++];
					c[1]=0;
					if(RealDraw) { out1asc_scale((char*)c,x,y,dRateX,dRateY); OnZipp(x,y); }
					x += (8*(int)dRateX) + CHARGAP;
			}
		}
		return x;
	}


	int OutTextWidth_scale( const char *pstr, int x2, int y2, int iWidth, double dRateX = 1.0 , double dRateY = 1.0, int RealDraw = 1 , int * ppos = NULL )
	{
		int CHARGAP = m_iCHARGAP;
		int x = x2;
		int y = y2;
		unsigned char *p = (unsigned char *)pstr;
		int pos;
		unsigned char c[3];
		c[2]=0;

		if( ppos ) { *ppos=0; }

		for(pos=0;p[pos]!=0;pos++)
		{
			if( iscntrl(p[pos]) && p[pos] != '\n' ) p[pos]=' ';
		}

		for(pos=0;p[pos]!=0;)
		{
			if( p[pos] == '\n' )
			{
				x = x2;
				y += (int)(16.0 * dRateY) + CHARGAP;

				pos++;

				if( ppos ) { *ppos=pos; return y; } 

				continue;
			}

			if( x - x2 > iWidth )
			{
				x = x2;
				y += (int)(16.0 * dRateY) + CHARGAP;

				if( ppos ) { *ppos=pos; return y; } 
			}
			else 
			{
				int x3 = x;

				if(p[pos]>0xa0)
					x3 += (int)( 16.0 * dRateX ) + CHARGAP;
				else
					x3 += (int)( 8.0 * dRateX ) + CHARGAP;

				if( x3 - x2 > iWidth )
				{
					if( ppos ) { *ppos=pos; return y; } 
				}
			}

			if(p[pos]>0xa0)
			{
				c[0]=p[pos]; c[1]=p[pos+1];
				pos+=2;
				if(RealDraw) { out1hz_scale((char*)c,x,y,dRateX,dRateY); OnZipp(x,y); }
				x += (16*(int)dRateX) + CHARGAP;
			}else
			{
				c[0]=p[pos++]; c[1]=0;
				if(RealDraw) { out1asc_scale((char*)c,x,y,dRateX,dRateY);OnZipp(x,y); }
				x += (8*(int)dRateX) + CHARGAP;
			}
		}
		return y;
	}

	
	int OutTextWidth( const char *pstr, int x2, int y2, int iWidth, int RealDraw = 1, int * ppos = NULL )
	{
		int CHARGAP = m_iCHARGAP;
		int x = x2;
		int y = y2;
		unsigned char *p = (unsigned char *)pstr;
		int pos;
		unsigned char c[3];
		c[2]=0;

		if( ppos ) { *ppos=0; }

		for(pos=0;p[pos]!=0;pos++)
		{
			if( iscntrl(p[pos]) && p[pos] != '\n' ) p[pos]=' ';
		}

		for(pos=0;p[pos]!=0;)
		{
			if( p[pos] == '\n' )
			{
				x = x2;
				y += 16+ CHARGAP;

				pos++;

				if( ppos ) { *ppos=pos; return y; } 

				continue;
			}

			if( x - x2 > iWidth )
			{
				x = x2;
				y += 16+ CHARGAP;

				if( ppos ) { *ppos=pos; return y; } 
			}
			else 
			{
				int x3 = x;

				if(p[pos]>0xa0)
					x3 += 16+ CHARGAP;
				else
					x3 += 8+ CHARGAP;

				if( x3 - x2 > iWidth )
				{
					if( ppos ) { *ppos=pos; return y; } 
				}
			}

			if(p[pos]>0xa0)
			{
				c[0]=p[pos]; c[1]=p[pos+1];
				pos+=2;
				if(RealDraw) { out1hz((char*)c,x,y); OnZipp(x,y); }
				x += 16+ CHARGAP;
			}else
			{
				c[0]=p[pos++]; c[1]=0;
				if(RealDraw) { out1asc((char*)c,x,y);OnZipp(x,y); }
				x += 8+ CHARGAP;
			}
		}
		return y;
	}


	virtual void OnPoint( int x, int y )
	{
		if( m_pckBuf )
		{
			char *buf = m_pckBuf->buf();
			int width = m_iBufWidth;
			int o = y * width + x;
			char *p;

			p = buf + o * 3;
			*p = (char)m_DefaultColor.B;
			p++;
			*p = (char)m_DefaultColor.G;
			p++;
			*p = (char)m_DefaultColor.R;
		}
	}


	virtual void OnPoint_bg( int x, int y ) { ;	}

	virtual void OnYpp( int y ) { ;	}				

	virtual void OnZipp( int x, int y ) { ;	}		

};




class SimpPaper : public SBmp
{
public:
	SCake   m_ckBuf;	
	int     m_width;	
	int     m_height;	
	RGB_t   m_foreColor;
	RGB_t   m_backColor;

public:
	
	SimpPaper()
	{
		m_ckBuf.redim(0);
		m_width = 0;
		m_height = 0;

		m_foreColor = MKRGB( 0x00, 0x00, 0x00 );	
		m_backColor = MKRGB( 0xff, 0xff, 0xff );	

		m_pckBuf = NULL;
		m_iBufWidth = 0;
		m_DefaultColor = m_foreColor;
	}

	
	virtual ~SimpPaper(){}


	tbool Init( int width ) 
	{
		m_width = width;
		m_height = m_ckBuf.len() / m_width / 3;

		return 1;
	}

	
	tbool Init( int width, int height )
	{
		m_width = width;
		m_height = height;
		m_ckBuf.redim( 3 * m_width * m_height );
		m_pckBuf = &m_ckBuf;

		for( int y = 0; y < m_height; y++ )
		{
			for( int x = 0; x < m_width; x++ )
			{
				PaperPutPixel( x, y, m_backColor );
			}
		}

		return 1;
	}

	
	tbool InitFn( std::string strFn )
	{
		SFile fl;
		fl.bind( strFn );
		return Init( fl );
	}

	
	tbool Init( SFile fl )
	{
		m_pckBuf = &m_ckBuf;

		SCake ck;

		fl.read( ck );

		return Init(ck);
	}

	
	tbool Init( const SCake &ckBmp24 )
	{
		tbool rc;
		const SCake &ck(ckBmp24);
		int depth;

		rc = SBmp::Conv2Ck( ck, m_ckBuf, m_width, m_height, depth );

		if( rc == 0 && depth == 3 ) 
		{
			tint32 &L( *(tint32*)(ck.buf_const()+0x16) );
			if( L < 0 )
			{
				L = L * (-1);
				SBmp::Conv2Ck( ck, m_ckBuf, m_width, m_height, depth );
				TurnUpDn();
				return 1;
			}
			return 0;
		}

		return 1;
	}

	
	tbool Init( std::string str, int CrPixelWidth, tbool RealDraw = 1 )
	{
		int y;
		tbool rc;

		y = this->PrintText( str.c_str(), 0, 0, 0, CrPixelWidth );
		if( y == 0 ) return 0;
		rc = Init( CrPixelWidth, y );

		if( !rc ) return rc;
		if( !RealDraw ) return rc;

		rc = Init( CrPixelWidth, y );
		y = this->PrintText( str.c_str(), 0, 0, 1, CrPixelWidth );

		return rc;
	}


	tbool Init_str_scale( std::string str, int CrPixelWidth, double ratex, double ratey )
	{
		int y;
		tbool rc;

		y = this->PrintText( str.c_str(), 0, 0, 0, CrPixelWidth , 1, ratex, ratey );
		if( y == 0 ) return 0;
		rc = Init( CrPixelWidth, y );

		if( !rc ) return rc;

		rc = Init( CrPixelWidth, y );
		y = this->PrintText( str.c_str(), 0, 0, 1, CrPixelWidth , 1, ratex, ratey );

		return rc;
	}


	void AttachHZK( char *pASC, char *pHz )
	{
		InitZK( pASC, pHz, &m_ckBuf , m_width );
	}


	tbool SaveBmp( std::string strFn )
	{
		SFile fl;
		SCake ck;

		ck = m_ckBuf;
		fl.bind( strFn );
		if( !Conv2Bmp( ck, m_width, 3 , 1 ) ) return 0;
		return fl.write(ck);
	}

	
	tbool SaveBmp( SCake &ckBmp )
	{
		ckBmp = m_ckBuf;
		if( !Conv2Bmp( ckBmp, m_width, 3 , 1 ) ) return 0;
		return 1;
	}


	tbool ConvBmp( SCake &ckOut )
	{
		if( !Conv2Bmp( ckOut, m_width, 3 , 1 ) ) return 0;
		return 1;
	}


	void PaperPutPixel( int x, int y, RGB_t color )
	{
		if( x >= m_width ) return;
		if( y >= m_height) return;

		char *buf = m_ckBuf.buf();
		int o = y * m_width + x;
		char *p;

		p = buf + o * 3;
		*p = (char)(color.B);
		p++;
		*p = (char)(color.G);
		p++;
		*p = (char)(color.R);
	}

	
	tbool PaperGetPixel( int x, int y, RGB_t &color )
	{
		if( x >= m_width ) return 0;
		if( y >= m_height) return 0;

		char *buf = m_ckBuf.buf();
		int o = y * m_width + x;
		char *p;

		p = buf + o * 3;
		color.B = (tuint8)(*p);
		p++;
		color.G = (tuint8)(*p);
		p++;
		color.R = (tuint8)(*p);

		return 1;
	}

	
	RGB_t PaperGetPixel( int x, int y )
	{
		if( x >= m_width ) return m_backColor;
		if( y >= m_height) return m_backColor;

		RGB_t color;
		char *buf = m_ckBuf.buf();
		int o = y * m_width + x;
		char *p;

		p = buf + o * 3;
		color.B = (tuint8)(*p);
		p++;
		color.G = (tuint8)(*p);
		p++;
		color.R = (tuint8)(*p);

		return color;
	}


	
	
	virtual void OnPoint( int x, int y )
	{
		PaperPutPixel( x, y, m_foreColor );
	}

	
	
	
	



	tbool TurnUpDn()
	{
		tbool rc;
		SCake ck;
		int width, height, depth;

		ck = m_ckBuf;
		rc = Conv2Bmp( ck, m_width, 3 , 0 );
		if( !rc ) return 0;
		SBmp::Conv2Ck( ck, m_ckBuf, width, height, depth );
		return 1;
	}

	
	tbool TurnP90()
	{
		int iWidth;
		SCake ck;
		tbool rc;

		ck = m_ckBuf;
		rc = Turn_p90( ck, m_width, m_ckBuf, iWidth );
		m_height = m_width;
		m_width= iWidth;
		return rc;
	}

	
	tbool Turn180()
	{
		SCake ck;
		tbool rc;

		ck = m_ckBuf;
		rc = Turn_180( ck , m_ckBuf );
		return rc;
	}

	
	tbool Add( int x, int y, SimpPaper & sp2 )
	{
		return Add_pic( m_ckBuf, m_width, x, y, sp2.m_ckBuf, sp2.m_width );
	}

	
	tbool AddUseTrans( int x, int y, SimpPaper & sp2 , int CopyXor = 0 ) 
	{
		int x3,y3; 
		int x2,y2; 
		int x9,y9; 

		y3 = sp2.m_height + y;
		if( y3 > m_height ) y3 = m_height;

		x3 = sp2.m_width + x;
		if( x3 > m_width ) x3 = m_width;

		for( x2 = x; x2 < x3; x2 ++ )
		{
			x9 = (x2-x);

			for( y2 = y; y2 < y3; y2 ++ )
			{
				y9 = (y2-y);

				RGB_t ColorSub;

				sp2.PaperGetPixel( x9, y9, ColorSub );

				if( m_backColor.R == ColorSub.R && m_backColor.G == ColorSub.G && m_backColor.B == ColorSub.B )
				{
				}
				else
				{
					if( CopyXor == 0 )
					{
						PaperPutPixel( x2,y2, ColorSub );
					}
					else
					{
						RGB_t ColorMain;

						PaperGetPixel( x2,y2, ColorMain );
						ColorMain.R ^= ColorSub.R;
						ColorMain.G ^= ColorSub.G;
						ColorMain.B ^= ColorSub.B;

						PaperPutPixel( x2,y2, ColorMain );
					}
				}
			}
		}

		return 1;
	}

	
	tbool Cut( int x, int y, int iCutWidth, int iCutHeight, SimpPaper & sp2 )
	{
		SCake ck;
		tbool rc;

		rc = Cut_pic( m_ckBuf, m_width, x, y, iCutWidth, iCutHeight, sp2.m_ckBuf, sp2.m_width );
		sp2.Init( sp2.m_width );
		return rc;
	}

	
	tbool Cut2( int x, int y, int x2, int y2, SimpPaper & sp2 )
	{
		return Cut( x, y, x2 - x, y2 - y , sp2 );
	}


	int PrintText( std::string s1, int x, int y, int RealDraw = 1, int CrPixelWidth = 0 , tbool HaveScale = 0 , double dRateX = 1.0 , double dRateY = 1.0 )
	{
		const char *p = s1.c_str();

		m_pckBuf = &m_ckBuf;
		m_DefaultColor = m_foreColor;

		int pos = 0;

		if( p && *p )
		for( ; ; )
		{
			if( HaveScale == 0 )
			{
				OutTextWidth( p, x, y, CrPixelWidth <= 0 ? m_width : CrPixelWidth , RealDraw, &pos );

				p += pos;
				y += 16+ m_iCHARGAP;
				if( pos == 0 ) break;
			}
			else
			{
				
				OutTextWidth_scale( p, x, y, CrPixelWidth <= 0 ? m_width : CrPixelWidth , dRateX , dRateY, RealDraw, &pos );

				p += pos;
				y += (int)( 16.0 * dRateY ) + m_iCHARGAP;
				if( pos == 0 ) break;
			}
		}

		return y;
	}

	
	void Line( int x1, int y1, int x2, int y2 )
	{
		 int dx = x2 - x1;
		 int dy = y2 - y1;
		 int ux = ((dx > 0) << 1) - 1;
		 int uy = ((dy > 0) << 1) - 1;
		 int x = x1, y = y1, eps;

		 eps = 0;dx = abs(dx); dy = abs(dy);
		 if (dx > dy)
		 {
			 for (x = x1; x != x2+ux; x += ux)
			 {
				  PaperPutPixel( x, y, m_foreColor );
				  eps += dy;
				  if ((eps << 1) >= dx)
				  {
					   y += uy; eps -= dx;
				  }
			 }
		 }
		 else
		 {
			 for (y = y1; y != y2+uy; y += uy)
			 {
				  PaperPutPixel( x, y, m_foreColor );
				  eps += dx;
				  if ((eps << 1) >= dy)
				  {
					   x += ux; eps -= dy;
				  }
			 }
		 }
	}

	
	void Rect( int x1, int y1, int x2, int y2 )
	{
		Line( x1, y1, x2, y1 );
		Line( x1, y1, x1, y2 );
		Line( x2, y2, x2, y1 );
		Line( x2, y2, x1, y2 );
	}

	
	void Rect()
	{
		Rect( 0, 0, m_width-1, m_height-1 );
	}

	
	void Circle( int x, int y, int r )
	{
		int tx = 0;
		int ty = r;
		int d = 1 - r;

		RGB_t &color(m_foreColor);

		while(tx <= ty){
			
			PaperPutPixel(x + tx, y + ty, color);
			PaperPutPixel(x + tx, y - ty, color);
			PaperPutPixel(x - tx, y + ty, color);
			PaperPutPixel(x - tx, y - ty, color);
			PaperPutPixel(x + ty, y + tx, color);
			PaperPutPixel(x + ty, y - tx, color);
			PaperPutPixel(x - ty, y + tx, color);
			PaperPutPixel(x - ty, y - tx, color);
			if(d < 0){
				d += 2 * tx + 3;
			}else{
				d += 2 * (tx - ty) + 5;
				ty--;
			}
			tx++;
		}
	}

};






X011_NAMESPACE_END


#endif






#ifndef X011__H_w_SNava_h
#define X011__H_w_SNava_h


X011_NAMESPACE_BEGIN


template< class nameT, class valueT >
class SNava_base
{
public:
	typedef typename std::map< nameT, valueT >::iterator		 MAP_MAPKNL_IT;
	typedef typename std::map< nameT, valueT >::const_iterator   MAP_MAPKNL_CONSTIT;

public:
	std::map< nameT, valueT >  m_mapKnl;

public:

	virtual ~SNava_base() {;}


	void clear()
	{
		m_mapKnl.clear();
	}


	tbool IsEmpty()
	{
		if( m_mapKnl.empty() ) return 1;
		return 0;
	}


	tbool let( const nameT & name, const valueT & val )
	{
		
		m_mapKnl[name] = val; 
		return 1;
	}


	tbool get( const nameT & name, valueT & val )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			val = it->second;
			return 1;
		}
		return 0;
		
	}


	valueT & get( const nameT & name )
	{
		return m_mapKnl[name];
	}


	tbool del( const nameT & name )
	{
		MAP_MAPKNL_IT it;
		it = m_mapKnl.find( name );
		if( it != m_mapKnl.end() )
		{
			m_mapKnl.erase(it);
			return 1;
		}
		return 0;
	}


	tbool GetFirstName( nameT & Name, MAP_MAPKNL_IT & it4name )
	{
		it4name = it4name.begin();
		if( it4name != m_mapKnl.end() )
		{
			Name = it4name->first;
			return 1;
		}
		return 0;
	}


	tbool GetNextName( nameT & Name, MAP_MAPKNL_IT & it4name )
	{
		it4name ++;
		if( it4name != m_mapKnl.end() )
		{
			Name = it4name->first;
			return 1;
		}
		return 0;
	}


	bool operator < ( const SNava_base & rhs) const
	{
		return  m_mapKnl < rhs.m_mapKnl ;
	}

	bool operator <= ( const SNava_base & rhs) const
	{
		return  m_mapKnl <= rhs.m_mapKnl ;
	}

	bool operator > ( const SNava_base & rhs) const
	{
		return  m_mapKnl > rhs.m_mapKnl ;
	}

	bool operator >= ( const SNava_base & rhs) const
	{
		return m_mapKnl >= rhs.m_mapKnl ;
	}

	bool operator == ( const SNava_base & rhs) const
	{
		return  m_mapKnl == rhs.m_mapKnl ;
	}
};



class SNavass : public SNava_base< std::string, std::string >
{
private:

	static void seri_element_en( SCake & ck )
	{
		if( ck.len() == 0 ) return;
		ck.bs_en();
	}

	static void seri_element_de( SCake & ck )
	{
		if( ck.len() == 0 || !ck.buf() )
		{
			ck.lets("");
			return;
		}

		ck.bs_de();

		if( ck.len() == 0 || !ck.buf() )
		{
			ck.lets("");
			return;
		}

		
	}

public:
	virtual ~SNavass() {;}


	void imp( const std::string & ssource, std::string ssepTR, std::string ssepTD )
	{
		SStrvs::vsa2v_prpt( ssource, ssepTR, ssepTD , m_mapKnl );
	}


	void trimall()
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			SStrf::strim( s1 );
			SStrf::strim( s2 );

			this->let( s1, s2 );
		}
	}


	tbool let( const std::string & name, const std::string & val )
	{
		m_mapKnl[name] = val;
		return 1;
	}


	tbool let( const std::string & name, int val )
	{
		m_mapKnl[name] = SStrf::sltoa(val);
		return 1;
	}


	std::string GetReadable() const
	{
		std::string strOut = "";

		for( MAP_MAPKNL_CONSTIT it = m_mapKnl.begin(); it != m_mapKnl.end(); ++it )
		{
			strOut += it->first;
			strOut += "=";
			strOut +=  it->second;
			strOut += "\r\n";
		}

		return strOut;
	}


	tbool serialize( std::string & strOut ) const
	{
		strOut = "";

		SCake ckTmp;

		for( MAP_MAPKNL_CONSTIT it = m_mapKnl.begin(); it != m_mapKnl.end(); ++it )
		{
			ckTmp.lets( it->first );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += "(";

			ckTmp.lets( it->second );
			seri_element_en( ckTmp );
			strOut += ckTmp.buf();

			strOut += ")";
		}

		return 1;
	}


	std::string serialize() const
	{
		std::string strOut;
		serialize(strOut);
		return strOut;
	}


	tbool unserialize( const std::string & strData )
	{
		std::map< std::string, std::string > mapTmp;

		SStrvs::vsa2v_prpt( strData, std::string(")"), std::string("(") , mapTmp );

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			SCake ckTmp1,ckTmp2;

			ckTmp1.lets( it->first );
			seri_element_de( ckTmp1 );

			ckTmp2.lets( it->second );
			seri_element_de( ckTmp2 );

			
			this->let( ckTmp1.mk_str(), ckTmp2.mk_str() );
		}

		return 1;
	}

};



class NaStrarr__bak
{
	SNavass m_navaknl;

public:
	std::string  m_serialize_hold;

	
	void clear()
	{
		m_navaknl.clear();
	}

	
	tbool let( long name, const std::string & val )
	{
		m_navaknl.let( SStrf::sltoa(name) , val );
		return 1;
	}

	
	std::string & get( long name )
	{
		return m_navaknl.get(SStrf::sltoa(name));
	}

	std::string & operator[] (long name )
	{
		return get(name);
	}

	
	tbool del( long name )
	{
		return m_navaknl.del(SStrf::sltoa(name));
	}

	
	const char * serialize_hold()
	{
		m_serialize_hold = m_navaknl.serialize();
		return m_serialize_hold.c_str();
	}

	
	std::string serialize() const
	{
		return m_navaknl.serialize();
	}

	
	tbool unserialize( const std::string & strData )
	{
		return m_navaknl.unserialize(strData);
	}

	
	
	
	

	
	
	
	
};


template< class KeyType_T >		
class NaStrarr_base
{
protected:
	SNavass m_navaknl;
	std::string  m_serialize_hold;

public:
	virtual ~NaStrarr_base() {;}

	
	void clear()
	{
		m_navaknl.clear();
	}

	
	tbool let( KeyType_T name, const std::string & val )
	{
		std::stringstream stream1;
		stream1<<name;
		m_navaknl.let( stream1.str() , val );
		return 1;
	}

	
	std::string & get( KeyType_T name )
	{
		std::stringstream stream1;
		stream1 << name;
		return m_navaknl.get(stream1.str());
	}

	
	std::string & operator[] ( KeyType_T name )
	{
		return get(name);
	}

	
	tbool del( KeyType_T name )
	{
		std::stringstream stream1;
		stream1 << name;
		return m_navaknl.del(stream1.str());
	}

	
	const char * serialize_hold_addr()
	{
		m_serialize_hold = m_navaknl.serialize();
		return m_serialize_hold.c_str();
	}
	
	long serialize_hold_len()
	{
		return (long)m_serialize_hold.size() + 1;
	}

	
	std::string serialize() const
	{
		return m_navaknl.serialize();
	}

	
	tbool unserialize( const std::string & strData )
	{
		return m_navaknl.unserialize(strData);
	}

	
	
	
	

	bool operator <  ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl <  rhs.m_navaknl; 	}
	bool operator <= ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl <= rhs.m_navaknl; 	}
	bool operator >  ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl >  rhs.m_navaknl; 	}
	bool operator >= ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl >= rhs.m_navaknl; 	}
	bool operator == ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return m_navaknl == rhs.m_navaknl; 	}
	bool operator != ( const NaStrarr_base< KeyType_T > & rhs) const 	{ 	return !(m_navaknl == rhs.m_navaknl);  	}
};



class NaStrarr : public NaStrarr_base< long >
{
public:
	virtual ~NaStrarr() {;}
};



template< class INT_NAME_T, class INT_VAL_T >
class NaIntarr_base : public NaStrarr_base< INT_NAME_T >
{
public:
	virtual ~NaIntarr_base()
	{;}

	
	tbool let( INT_NAME_T name, INT_VAL_T val )
	{
		std::stringstream stream1;
		std::stringstream stream_val;
		stream1 << name;
		stream_val << val;
		NaStrarr_base< INT_NAME_T >::m_navaknl.let( stream1.str() , stream_val.str() );
		return 1;
	}

	
	INT_VAL_T get( INT_NAME_T name )
	{
		std::stringstream stream1;
		std::stringstream stream2;
		INT_VAL_T n;
		stream1 << name;
		if( NaStrarr_base< INT_NAME_T >::m_navaknl.get(stream1.str()).empty() )
		{
			stream2 << "0";
		}
		else
			stream2 << NaStrarr_base< INT_NAME_T >::m_navaknl.get(stream1.str());
		stream2 >> n;
		return n;
	}

	
	INT_VAL_T operator[] ( INT_NAME_T name )
	{
		return get(name);
	}
};



class NaLngarr : public NaIntarr_base< long, long >
{
public:
	virtual ~NaLngarr() {;}

	long addvalue( long name, long val )
	{
		long j = get( name );
		j += val;
		let( name, j );
		return j;
	}
};



	
	

class NaS2S : public NaStrarr_base< std::string >	
{
public:
	virtual ~NaS2S() {;}
};


class NaL2S : public NaStrarr	 	
{
public:
	virtual ~NaL2S() {;}
};


class NaL2L : public NaLngarr	 	
{
public:
	virtual ~NaL2L() {;}
};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_SAbys_h
#define X011__H_w_SAbys_h



X011_NAMESPACE_BEGIN


class SAbys
{

private:

	SCake		m_knowledge_cake;
	tsize		m_knowledge_cur_pos;
	tdouble		m_data_knowledge_ratio;

	
	

public:

	SAbys()
	{
		init( 23.6 );
	}

	SAbys( tdouble ratio )
	{
		init( ratio );
	}

	SAbys( const SCake & cakeKnow )
	{
		init(cakeKnow);
	}

	virtual ~SAbys( )
	{ ; }


	void init( tdouble data_knowledge_ratio = 1.0 )
	{
		SStrf::initrand();
		SCake ckTmp( SStrf::sftoa( SStrf::rand1() ) + SStrf::sftoa( SStrf::rand1() ) );
		ckTmp.cut(1);
		init( ckTmp , data_knowledge_ratio );
	}


	void init( const SCake & knowledge_cake , tdouble data_knowledge_ratio = 1.0 )
	{
		if(knowledge_cake.len()>0)
			m_knowledge_cake = knowledge_cake;
		else
			init(data_knowledge_ratio);
		m_knowledge_cur_pos = (tsize)(m_knowledge_cake.len() * SStrf::rand1());
		m_data_knowledge_ratio = data_knowledge_ratio>0?data_knowledge_ratio:1;
	}


	void mix( const SCake & ck_Data  ,
			  SCake & ck_Mixeddata  ,
			  tchar chSep = '('		)
	{
		SCake ck_dubious_data = ck_Data;
		ck_dubious_data.bs_en();

		SStrf::srev( ck_dubious_data );
		tsize iKnowLen = (tsize)(ck_Data.len()/m_data_knowledge_ratio);
		ck_Mixeddata.redim( ck_dubious_data.len() + iKnowLen + 1 );
		SStrf::scpy( ck_Mixeddata, ck_dubious_data );
		ck_dubious_data.cut(1);
		tsize iPnt = ck_dubious_data.len();
		*(ck_Mixeddata.buf()+iPnt) = chSep;
		iPnt++;
		for(ck_Mixeddata.cut(1);iPnt!=ck_Mixeddata.len();iPnt++)
		{
			m_knowledge_cur_pos++;
			if(m_knowledge_cur_pos>=m_knowledge_cake.len()) m_knowledge_cur_pos=0;
			*(ck_Mixeddata.buf()+iPnt) = *(m_knowledge_cake.buf()+m_knowledge_cur_pos);
		}
		*(ck_Mixeddata.buf()+iPnt) = 0;
	}

	std::string mix( const SNavass & nv )
	{
		std::string str;
		nv.serialize(str);
		SCake ck1( str );
		SCake ck2;
		mix( ck1, ck2 );
		return ck2.buf();
	}

	std::string & mix( const std::string & str , std::string & strOut )
	{
		SCake ck1( str );
		SCake ck2;
		mix( ck1, ck2 );
		strOut = ck2.buf();
		return strOut;
	}


	void unmix(  const SCake & ck_Mixeddata,		 
				 SCake	 & ck_Data						,
				 tchar chSep = '('		)
	{
		SCake ck0("");
		SCake ckMixDataWriteable( ck_Mixeddata );

		ckMixDataWriteable.append( ck0 );

		tchar strSep[2];

		strSep[0] = chSep;
		strSep[1] = 0;

		ck_Data.lets( SStrvs::vsa_get( std::string(ckMixDataWriteable), std::string(strSep), 1, 0 ) );
		SStrf::srev( ck_Data );
		tsize iDatalen = SStrf::bs_desize( ck_Data );
		
		ck_Data.bs_de();
		ck_Data.redim( iDatalen, 1 );
	}

	void unmix( const std::string & strSource, SNavass & nv )
	{
		SCake ck1( strSource );
		SCake ck2;
		unmix( ck1, ck2 );
		ck2.mk_sz();
		nv.unserialize( std::string(ck2) );
	}

	std::string & unmix( const std::string & strSource, std::string & strOut )
	{
		SCake ck1( strSource );
		SCake ck2;
		unmix( ck1, ck2 );
		ck2.mk_sz();
		strOut = ck2.buf();
		return strOut;
	}


	void envelop( 	const SCake & ckKeyWord,
					const SCake & ckHead, const SCake & ckTail, const SCake & ck_src, SCake & ck_destbuf )
	{
		
	}

	tbool unenvelop( const SCake & ckKeyWord,
					 const SCake & ck_src, SCake & ck_destbuf	)
	{
		return 1;
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_IRice_h
#define X011__H_w_IRice_h



X011_NAMESPACE_BEGIN


class IRice
{
public:
	tbool m_biRecv0Flag;

protected:
	SCake m_ckDataL2CacheBuf;

protected:

	tsize sys_recv( SCake & ckDataBuf )
	{
		on_send_recv_kick();

		int i = on_sys_recv(ckDataBuf); 
		if(i)
		{
			return i;
		}
		else
		{
			ckDataBuf.redim(0);
			m_biRecv0Flag = 1;
			return 0;
		}
	}


	tsize sys_send( const SCake & ckDataBuf )
	{
		on_send_recv_kick();

		return on_sys_send(ckDataBuf);
	}


public:

	IRice( )
	{
		m_biRecv0Flag = 0;
	}


	virtual ~IRice( )
	{ ; }


	void ClearL2Cache()
	{
		m_ckDataL2CacheBuf.redim(0);
	}


	tbool send_str( std::string s ) 
	{
		return send_str(s.c_str());
	}


	tbool send_str( const tchar *s ) 
	{
		SCake ckTmp(s);
		ckTmp.cut(1);
		return send_bin( ckTmp );
	}


	template<class T>
	tbool send_bin_internal( T adata )
	{
		SCake ck;
		ck.let( (SCake::CkEle_t*)&adata, sizeof(T) );
		return send_bin(ck);
	}

	tbool send_bin( tuint8  a ) { return send_bin_internal(a); }
	tbool send_bin( tuint16 a ) { return send_bin_internal(a); }
	tbool send_bin( tuint32 a ) { return send_bin_internal(a); }
	tbool send_bin( tint8  a ) { return send_bin_internal(a); }
	tbool send_bin( tint16 a ) { return send_bin_internal(a); }
	tbool send_bin( tint32 a ) { return send_bin_internal(a); }

	
	tbool send_bin( const SCake & ckData )
	{
		tsize rc, k;
		if(ckData.len()==0) return 0;
		for(k=0;;)
		{
			SCake ckTmp(ckData.buf_const()+k, ckData.len()-k);
			rc = sys_send( ckTmp );
			if(rc==0) return 0;
			k += rc;
			if(k>=ckData.len()) break;
		}
		return 1;
	}

	tbool send_bin_shortdata( const SCake & ckData )
	{
		tsize rc, k;
		if(ckData.len()==0) return 0;
		for(k=0;;)
		{
			rc = sys_send( ckData );
			if(rc==0) return 0;
			break;
		}
		return 1;
	}


	
	
	



	tbool recv_bin( SCake & ckData ) 
	{
		SCake ckTmp;

		if( m_ckDataL2CacheBuf.len() == 0 )
		{
			sys_recv( ckTmp ); 
			m_ckDataL2CacheBuf.append(ckTmp);
		}
		else
		{
			
		}

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_all( SCake & ckData ) 
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; 

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_all_f( SCake & ckData ) 
	{
		SCake ckTmp;
		do
		{
			if( !sys_recv( ckTmp ) ) break;
			
			m_ckDataL2CacheBuf.FastAppend(ckTmp);

			
		}while(ckTmp.len()>0);

		m_ckDataL2CacheBuf.FastAppendEnd();

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_len( SCake & ckData , tsize iWantDataLen ) 
	{
		SCake ckTmp;

		while( m_ckDataL2CacheBuf.len()< iWantDataLen )
		{
			if( !sys_recv( ckTmp ) ) break;

			
			m_ckDataL2CacheBuf.FastAppend(ckTmp);
		}

		m_ckDataL2CacheBuf.FastAppendEnd();

		ckData.redim(iWantDataLen);
		m_ckDataL2CacheBuf.dump( ckData );
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


	tbool recv_ln( SCake & ckData , const std::vector<std::string> & vecstrSeperate, std::string * pstrRealSep=NULL ) 
	{
		SCake ckTmp;
		tchar * pSep;
		SCake ckSepDumpTmp;

		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();

			pSep = NULL;

			if(pstrRealSep) *pstrRealSep = "";

			
			for( std::vector<std::string>::const_iterator it = vecstrSeperate.begin();
				 it != vecstrSeperate.end();
				 ++it )
			{
				pSep = SStrf::sstr( ckTmpL2Cache2, it->c_str() );
				if( pSep )
				{
					if(pstrRealSep) *pstrRealSep = *it;

					ckSepDumpTmp.lets(*it);
					ckSepDumpTmp.cut(1); 
					break;
				}
			}


			if( pSep )
			{
				
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );

				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); 
				return 1;
			}

			if( !sys_recv( ckTmp ) ) break;
			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; 

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_ln( SCake & ckData , const tchar * strSeperate = "\n" ) 
	{
		if( strSeperate && std::string(strSeperate) == "\r\n\r\n\r\n" )
			return recv_ln2( ckData , strSeperate );

		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);

		ckSepDumpTmp.cut(1); 

		do
		{
			SCake ckTmpL2Cache2;
			ckTmpL2Cache2 = m_ckDataL2CacheBuf;
			ckTmpL2Cache2.mk_sz();

			
			pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );

			if( pSep )
			{
				
				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );

				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp ); 
				return 1;
			}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

			if( !on_chk_L2CacheLen( m_ckDataL2CacheBuf ) ) break; 

		}while(ckTmp.len()>0);

		ckData = m_ckDataL2CacheBuf;	
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


	tbool recv_ln( SCake & ckData , tchar cSeperate ) 
	{
		tchar t[2];
		t[0]=cSeperate;
		t[1]=0;
		return recv_ln(ckData,t) ;
	}


	tbool recv_ln2( SCake & ckData , const tchar * strSeperate )  
	{
		SCake ckTmp;
		tchar *pSep;
		SCake ckSepDumpTmp(strSeperate);

		ckSepDumpTmp.cut(1);


		std::vector<tchar>  vec_m_ckTmpL2CacheBuf;
		std::copy( m_ckDataL2CacheBuf.buf(), m_ckDataL2CacheBuf.buf() + m_ckDataL2CacheBuf.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) );

		long lLastChkOffset(0);

		do
		{
			vec_m_ckTmpL2CacheBuf.push_back(0);

			pSep = SStrf::sstr( &(vec_m_ckTmpL2CacheBuf[lLastChkOffset]), strSeperate );

			vec_m_ckTmpL2CacheBuf.pop_back();


			if( pSep )
			{
				
				
				if( vec_m_ckTmpL2CacheBuf.empty() )
					m_ckDataL2CacheBuf.redim(0);
				else
					m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

				vec_m_ckTmpL2CacheBuf.clear();
				

				SCake ckTmpL2Cache2;
				ckTmpL2Cache2 = m_ckDataL2CacheBuf;
				ckTmpL2Cache2.mk_sz();

				pSep = SStrf::sstr( ckTmpL2Cache2, strSeperate );

				ckData.redim( (tsize)(pSep - ckTmpL2Cache2.buf() ) );

				m_ckDataL2CacheBuf.dump( ckData );
				m_ckDataL2CacheBuf.dump( ckSepDumpTmp );
				return 1;
			}
			else
			{
				
				lLastChkOffset = (long)vec_m_ckTmpL2CacheBuf.size() - (long)ckSepDumpTmp.len();
				if( lLastChkOffset < 0 ) lLastChkOffset = 0;
			}


			if( !sys_recv( ckTmp ) ) break;

			std::copy( ckTmp.buf(), ckTmp.buf() + ckTmp.len(), std::back_inserter(vec_m_ckTmpL2CacheBuf) );
			

			
		}while(ckTmp.len()>0);


		
		if( vec_m_ckTmpL2CacheBuf.empty() )
			m_ckDataL2CacheBuf.redim(0);
		else
			m_ckDataL2CacheBuf.let( &(vec_m_ckTmpL2CacheBuf[0]), (tsize)vec_m_ckTmpL2CacheBuf.size() );

		vec_m_ckTmpL2CacheBuf.clear();
		

		ckData = m_ckDataL2CacheBuf;
		m_ckDataL2CacheBuf.redim(0);
		return ckData.len()==0?0:1;
	}


public:

	virtual void on_send_recv_kick()
	{
		return;
	}

	virtual tbool on_chk_L2CacheLen( const SCake & ckCurrentL2Cache )
	{
		return 1;
	}


	virtual int on_sys_recv( SCake & ckDataBuf ) 
	{
		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		return 0;
	}


};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_ICursor_h
#define X011__H_w_ICursor_h


X011_NAMESPACE_BEGIN


template < class envT, class tblT, class rowT >
class ICursor
{
private:

	tbool		 m_bIsEnvOpen;
	tbool		 m_bIsTblOpen;

public:

	ICursor( )
	{
		m_bIsEnvOpen = m_bIsTblOpen = 0;
	}


	virtual ~ICursor( )
	{
		
	}

public:
	typedef envT envTYPE;
	typedef tblT tblTYPE;
	typedef rowT rowTYPE;

public:
	tbool GetIsEnvOpen()
	{
		return m_bIsEnvOpen;
	}

	tbool GetIsTblOpen()
	{
		return m_bIsTblOpen;
	}

public:
	tbool OpenEnv( envTYPE & _env )
	{
		CloseEnv();
		return m_bIsEnvOpen = OnOpenEnv(_env);
	}

	tbool OpenTbl( tblTYPE & _tbl )
	{
		CloseTbl();
		return m_bIsTblOpen = OnOpenTbl(_tbl);
	}

	tbool FetchRow( rowTYPE & _row )
	{
		return OnFetchRow( _row );
	}

	void CloseTbl()
	{
		if( GetIsTblOpen() ) OnCloseTbl();
		m_bIsTblOpen=0;
	}

	void CloseEnv()
	{
		if( GetIsEnvOpen() ) OnCloseEnv();
		m_bIsEnvOpen=0;
	}

public:
	virtual tbool OnOpenEnv( envTYPE & _env )
	{
		return 0;
	}

	virtual tbool OnOpenTbl( tblTYPE & _tbl )
	{
		return 0;
	}

	virtual tbool OnFetchRow( rowTYPE & _row )
	{
		return 0;
	}

	virtual void OnCloseTbl()
	{
		return;
	}

	virtual void OnCloseEnv()
	{
		return;
	}

};








template < class IDS_ELE_TYPE_T >
class ICursorDsColNames
{
public:
	typedef typename std::map<std::string,int> ColNamesMapTYPE;
	typedef  IDS_ELE_TYPE_T IDS_Ele_TYPE;

public:
	ColNamesMapTYPE  m_mapColNames;
	std::vector<IDS_Ele_TYPE>  m_row;
	IDS_Ele_TYPE m_emptyrow;

public:
	int SetColNames( std::string strColNames )
	{
		std::vector<std::string> rtnlst;
		SStrvs::vsa_imp( strColNames, std::string(","), 0, rtnlst );
		m_mapColNames.clear();
		for( int i = 0; i < (int)rtnlst.size(); i++ )
		{
			m_mapColNames[SStrf::strim(rtnlst[i])] = i;
		}
		return (int)m_mapColNames.size();
	}

	void SetRow( const std::vector<IDS_Ele_TYPE> & r )
	{
		m_row = r;
	}

	ICursorDsColNames & operator = ( const char * szColNames )
	{
		SetColNames(szColNames);
		return *this;
	}

	ICursorDsColNames & operator = ( const std::vector<IDS_Ele_TYPE> & r )
	{
		SetRow(r);
		return *this;
	}

	IDS_Ele_TYPE GetEle( const std::vector<IDS_Ele_TYPE> & row, int iCol )
	{
		if( iCol < 0 || iCol >= (int)row.size() ) return IDS_Ele_TYPE();
		return row[iCol];
	}

	IDS_Ele_TYPE GetEle( int iCol )
	{
		return GetEle( m_row, iCol );
	}

	IDS_Ele_TYPE & operator [] ( int iCol )
	{
		if( iCol < 0 || iCol >= (int)m_row.size() ) return m_emptyrow = IDS_Ele_TYPE();
		return m_row[iCol];
	}

	IDS_Ele_TYPE GetEle( const std::vector<IDS_Ele_TYPE> & row, const std::string & strName )
	{
		ColNamesMapTYPE::const_iterator it = m_mapColNames.find(strName);
		if( it != m_mapColNames.end() )
			return GetEle(row, it->second);
		else
			return IDS_Ele_TYPE();
	}

	IDS_Ele_TYPE GetEle( const std::string & strName )
	{
		return GetEle( m_row, strName );
	}

	IDS_Ele_TYPE & operator [] (const std::string & strName)
	{
		ColNamesMapTYPE::const_iterator it = m_mapColNames.find(strName);
		if( it != m_mapColNames.end() )
		{
			return (*this)[it->second];
		}
		else
			return m_emptyrow = IDS_Ele_TYPE();
	}
};




template < class IDS_ELE_TYPE_T >
class ICursorDs_base : public ICursor < std::string,				 
										std::string,				 
										std::vector<IDS_ELE_TYPE_T>  > 
{
public:
	typedef  IDS_ELE_TYPE_T IDS_Ele_TYPE;

	typedef  ICursorDsColNames<IDS_ELE_TYPE_T> ColNamesTYPE;

public:
	virtual ~ICursorDs_base( )
	{ ;
	}

};




class ICursorDs	: public ICursorDs_base < std::string >
{
public:
	virtual ~ICursorDs( )
	{ ;
	}


};




X011_NAMESPACE_END

#endif








#ifndef X011__H_w_wcrsc_h
#define X011__H_w_wcrsc_h


X011_NAMESPACE_BEGIN


class WCrsc
{
private:
	pthread_mutex_t  * m_pcsFather;
	WCrsc            * m_pCrsc_father;
	int              m_biIsBusy;

private:
	

	

	void LockCrsc( WCrsc & Crsc_father )
	{
		if(Crsc_father.m_pcsSelf)
		{
			pthread_mutex_lock( m_pcsFather = Crsc_father.m_pcsSelf );
			m_pCrsc_father = &Crsc_father;
			m_pCrsc_father->SetBusy();
		}
	}

	void InitVars()
	{
		m_pcsFather = NULL;
		m_pCrsc_father=NULL;
		m_pcsSelf = NULL;
		m_biIsBusy = 0;
	}

	
	void SetBusy()
	{
		m_biIsBusy++;
	}

	
	void SetIdle()
	{
		m_biIsBusy--;
	}

public:
	pthread_mutex_t  * m_pcsSelf;

public:

	WCrsc()
	{
		InitVars();

		m_pcsSelf = new pthread_mutex_t;
		pthread_mutexattr_t attr;
		pthread_mutexattr_init(&attr);

#ifdef OS_MACOSX_
		pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE);
#else
		pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE_NP);
#endif

		pthread_mutex_init(m_pcsSelf,&attr);
		pthread_mutexattr_destroy(&attr);
	}


private:
	
	
	
	
	WCrsc( WCrsc & Crsc_father)
	{
		InitVars();

		LockCrsc( Crsc_father );
	}


public:
	WCrsc( WCrsc * pCrsc_father)
	{
		InitVars();

		if( pCrsc_father ) LockCrsc( *pCrsc_father );
	}


	virtual ~WCrsc()
	{
		if( m_pcsFather != NULL )
		{
			m_pCrsc_father->SetIdle();
			pthread_mutex_unlock (m_pcsFather);
			return;
		}

		if( m_pcsFather == NULL )
		{
			if( m_pcsSelf != NULL )
			{
				pthread_mutex_destroy( m_pcsSelf );
				delete m_pcsSelf;
				return;
			}
		}
	}


	WCrsc & operator = (const WCrsc & rhs)
	{
		
		return *this;
	}


	tbool IsIdle() const
	{
		return m_biIsBusy?0:1;
	}

}; 




X011_NAMESPACE_END

#endif








#ifndef X011__W_WUNITBLCH_H
#define X011__W_WUNITBLCH_H



X011_NAMESPACE_BEGIN



class unitbl_base_t
{
protected:
	

public:
	WCrsc		m_ut_tbl_lck;

public:
	unitbl_base_t() { ;}
	virtual ~unitbl_base_t() {;	}

public:
	virtual void ut_ClearTbl() = 0;

	virtual int ut_GetColAmount() = 0;
	virtual std::string ut_GetColName( int iColNum ) = 0;

	virtual long ut_GetRowAmount() = 0;

	virtual std::string ut_GetRowSeriStr( long lRowNum ) = 0;

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName ) = 0;
	virtual std::string ut_GetItemStr( long lRowNum, int iColNum ) = 0;

	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA  ) = 0;
	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA  ) = 0;


	virtual void _save_readable( std::string strFn ) = 0;
	virtual std::string _get_readable_row( long iRow )  = 0;


	virtual std::string & ut_SeriTblStr( std::string & strOut ) = 0;
	virtual tbool ut_SeriTblFile( SFile & fl ) = 0;
	virtual tbool ut_SeriTblFile( SFile & fl, long lbegin, long lend ) = 0;
	virtual unitbl_base_t & ut_UnseriTblStr( const std::string & strIn, int biAppend ) = 0;

	virtual tbool ut_SeriTblFile( std::string strFn ) = 0;
	virtual unitbl_base_t & ut_UnseriTblFile( std::string strFn ) = 0;


	virtual long ut_AddRow() = 0;	
	virtual long ut_AddRow( std::string strRowSeriStr) = 0;
	virtual void ut_ReIdx() = 0;
	virtual void ut_DelRowf( long lRowNum ) = 0;
	virtual void ut_DelRow( long lRowNum ) = 0;

	virtual void * ut_GetRowAddr( long lRowNum ) = 0;
	virtual std::string ut_GetRowAddrStr( long lRowNum )=0;

	virtual unitbl_base_t * ut_GetDup() = 0;
	virtual void ut_DestroyDup(unitbl_base_t *p) { 	if( p ) delete p; }

	
	void SdbAttachFile( std::string strTblName, std::string strWorkPath ) {	OnSdbAttachFile( strTblName, strWorkPath); }
	tbool SdbLoadFile() { return OnSdbLoadFile(); }
	tbool SdbSaveFile() { return OnSdbSaveFile(); }
	virtual void OnSdbAttachFile( std::string strTblName, std::string strWorkPath ) {return;}
	virtual tbool OnSdbLoadFile() { return 0; }
	virtual tbool OnSdbSaveFile() { return 0; }

};




template<class T>
class unitbl_t : public unitbl_base_t , public T
{
public:
	virtual ~unitbl_t() {;}

public:
	virtual void ut_ClearTbl()
	{
		T::Clear();
	}

	virtual int ut_GetColAmount()
	{
		return T::GetRow(-1).GetColAmount() ;
	}

	virtual std::string ut_GetColName( int iColNum )
	{
		return T::GetRow(-1).GetColName( iColNum );
	}

	virtual long ut_GetRowAmount()
	{
		return T::GetRowCount();
	}

	virtual std::string ut_GetRowSeriStr( long lRowNum )
	{
		return T::GetRow(lRowNum).Serialize();
	}

	virtual std::string ut_GetItemStr( long lRowNum, std::string strColName )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( strColName, s1 );
		return s1;
	}

	virtual std::string ut_GetItemStr( long lRowNum, int iColNum )
	{
		std::string s1;
		T::GetRow(lRowNum).GetColStr( iColNum, s1 );
		return s1;
	}

	virtual void ut_SetItemByStr( long lRowNum, std::string strColName, std::string strValPARA )
	{
		T::GetRow(lRowNum).SetColVal( strColName, strValPARA );
	}

	virtual void ut_SetItemByStr( long lRowNum, int iColNum ,           std::string strValPARA )
	{
		T::GetRow(lRowNum).SetColVal( iColNum, strValPARA );
	}

	
	long _ut_imp( std::string strtblFn, std::string strTD, std::string strTR,  int SrcBeginRownum = 0, int SrcBeginColnum = 0, int TblBeginColnum = 0, tbool WithTrim = 1 , const tchar *str_space="\r\n \t" )
	{
		std::string strtbl;
		SFile fl;
		long lAddedRowNum = 0;

		fl.bind( strtblFn );
		fl.read_str( strtbl );

		tsize x, y,z;
		tsize a, b;

		a = SStrvs::vsa_hm( strtbl, strTR, 1 );

		for( y = 0; y < a; y++ )
		{
			if( (int)y < SrcBeginRownum )
				continue;
			else
			{
				std::string str1 = SStrvs::vsa_get( strtbl, strTR, 1, y );

				if(WithTrim)
					SStrf::strim( str1,str_space );

				b = SStrvs::vsa_hm( str1, strTD, 0 );

				long lNowRowNum = this->ut_AddRow();

				lAddedRowNum++;

				z = TblBeginColnum;

				std::vector< std::string > vecs2;

				SStrvs::vsa_imp( str1, strTD, 0, vecs2 );

				for( x = 0; x < b; x++ )
				{
					if( (int)x < SrcBeginColnum )
						continue;
					else
					{
						std::string str2;

						
						if( x >= (int)vecs2.size() )
						{
							str2 = "";
						}
						else
						{
							str2 = vecs2[x];
						}

						if(WithTrim)
							SStrf::strim( str2 ); 

						
						T::GetRow(lNowRowNum).SetColVal( (int)z, str2 );

						z ++;
					}
				}
			}
		}
		return lAddedRowNum;
	}

	
	void _save_readable( std::string strFn )
	{
		SFile fl;

		fl.bind( strFn );
		fl.erase();
		for( int y = 0; y < this->ut_GetRowAmount(); y++ )
		{
			std::string s2;

			for( int x = 0; x < this->ut_GetColAmount(); x++ )
			{
				s2 += this->ut_GetColName(x) + "=" + this->ut_GetItemStr(y,x);
				if( x != this->ut_GetColAmount() - 1 ) s2 += ", ";
			}
			fl.write_str( s2 + "\r\n", 1 );
		}
	}

	
	std::string _get_readable_row( long iRow )
	{
		int y = iRow;
		std::string s2;

		for( int x = 0; x < this->ut_GetColAmount(); x++ )
		{
			s2 += this->ut_GetColName(x) + "=" + this->ut_GetItemStr(y,x);
			if( x != this->ut_GetColAmount() - 1 ) s2 += ", ";
		}
		return s2;
	}

	virtual std::string & ut_SeriTblStr( std::string & strOut )
	{
		return T::Serialize( strOut );
	}

	virtual tbool ut_SeriTblFile( SFile & fl )
	{
		tbool rc = 0;
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "wb" );
		if(fp==NULL) return rc;
		for(long i=0;i<(long)T::GetRowCount();i++)
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		rc = 1;
		fclose(fp);
		return rc;
	}


	virtual tbool ut_SeriTblFile( SFile & fl, long lbegin, long lend )
	{
		tbool rc = 0;
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "ab" );
		if(fp == NULL) return rc;
		for( long i = lbegin;i<(long)lend + 1; i++ )
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		rc = 1;
		fclose(fp);
		return rc;
	}

	virtual unitbl_base_t & ut_UnseriTblStr( const std::string & strIn, int biAppend )
	{
		T::Unserialize( strIn.c_str() , biAppend )	;
		return *this;
	}


	virtual tbool ut_SeriTblFile( std::string strFn )
	{
		SFile fl;
		fl.bind(strFn);
		return this->ut_SeriTblFile(fl);
	}

	virtual unitbl_base_t & ut_UnseriTblFile( std::string strFn )
	{
		std::string strContent;
		SFile fl;
		tbool rc;

		fl.bind( strFn );
		this->ut_ClearTbl();
		rc = fl.read_str( strContent );
		return this->ut_UnseriTblStr( strContent, 0 );
	}


	virtual long ut_AddRow()
	{
		T::Add(T::GetRow(-1));
		return T::GetRowCount() - 1 ;
	}

	virtual long ut_AddRow( std::string strRowSeriStr )
	{
		typename T::ROWTYPE row1;
		row1.Unserialize( strRowSeriStr.c_str() );
		T::Add(row1);
		return T::GetRowCount() - 1 ;
	}

	virtual void ut_ReIdx()
	{
		T::ReIdx();
		return;
	}

	virtual void ut_DelRowf( long lRowNum )
	{
		T::DelInternal( lRowNum );
	}

	virtual void ut_DelRow( long lRowNum )
	{
		T::Del( lRowNum );
	}

	virtual void * ut_GetRowAddr( long lRowNum )
	{
		return (void*)(&(T::GetRow(lRowNum)));
	}

	
	virtual std::string ut_GetRowAddrStr( long lRowNum )
	{
		void *p= (void*)(&(T::GetRow(lRowNum)));
		return SStrf::b2s(p);
	}

	virtual unitbl_base_t * ut_GetDup()
	{
		
		try
		{
			unitbl_t<T> *p;
			p = new unitbl_t<T>();
			*p = *this;
			return p;
		}
		catch(...)
		{
			return NULL;
		}
	}

};


template<class T>
class SDB_t : public unitbl_t< T >
{
private:
	std::string  m_strTblChkSum1;
	std::string  m_strTblChkSum2;

public:
	std::string  m_strTblName;
	std::string  m_strWorkPath;
	tbool        m_FastSaveFlag;

public:
	tbool        m_Dirty1; 
	tbool        m_Dirty2;

public:
	
	SDB_t()
	{
		m_FastSaveFlag = 0;
		m_Dirty1 = 1;
		m_Dirty2 = 1;
	}

	
	virtual ~SDB_t() {;}

public:

	
	virtual void OnSdbAttachFile( std::string strTblName, std::string strWorkPath )
	{
		InitSDB( strTblName, strWorkPath );
	}
	virtual tbool OnSdbLoadFile() { return Load(); }
	virtual tbool OnSdbSaveFile() { return SaveF(); }

	
	void InitSDB( std::string strTblName, std::string strWorkPath, tbool FastSaveFlag = 0, tbool Dirty1 = 1, tbool Dirty2 = 1 )
	{
		m_strTblName = strTblName;
		m_strWorkPath = SFile::MkDir2Path(strWorkPath);
		m_FastSaveFlag = FastSaveFlag;
		m_Dirty1 = Dirty1;
		m_Dirty2 = Dirty2;
	}

	
	tbool DetectDirty()	
	{
		std::string s1;

		if( this->ut_GetRowAmount() == 0 )
			s1 = "";
		else
		{
			s1 = this->ut_GetRowSeriStr(0);
			s1 += SStrf::sltoa(this->ut_GetRowAmount());
			s1 += this->ut_GetRowSeriStr(this->ut_GetRowAmount()-1);
			s1 += this->ut_GetRowAddrStr(this->ut_GetRowAmount()-1);
		}

		if( m_Dirty1 == 1 || s1 != m_strTblChkSum1 )
		{
			m_strTblChkSum1 = s1;
			m_Dirty1 = 1;
		}

		if( m_Dirty2 == 1 || s1 != m_strTblChkSum2 )
		{
			m_strTblChkSum2 = s1;
			m_Dirty2 = 1;
		}

		if( m_Dirty1 == 0 &&
			m_Dirty2 == 0	)
			return 0;

		return 1;
	}


	tbool Load()
	{
		std::string strPFn1;
		std::string strPFn2;
		std::string strLight1;
		std::string strLight2;
		std::string strContent;
		SFile fl;
		tbool rc;

		strPFn1 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".1.txt";
		strPFn2 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".2.txt";
		strLight1 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".light1.txt";
		strLight2 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".light2.txt";

		fl.bind( strLight1 );
		if( fl.exists() )
		{
			fl.bind( strPFn1 );
			m_Dirty1 = 0;
			m_Dirty2 = 1;
		}
		else
		{
			fl.bind( strPFn2 );
			m_Dirty1 = 1;
			m_Dirty2 = 0;
		}

		this->ut_ClearTbl();
		rc = fl.read_str( strContent );
		this->ut_UnseriTblStr( strContent, 0 );

		
		return rc;
	}

	
	virtual void OnLightFileSync()
	{
		
		
	}

	
	virtual void OnBeforeDataFileDel( SFile & fl )
	{
		
	}

	
	tbool Save( int iWhich = 0 , tbool WithDetectDirty = 1 ) 
	{
		if( iWhich == 0 )
		{
			return this->Save(1,WithDetectDirty) && this->Save(2,WithDetectDirty);
		}

		std::string strPFn1;
		std::string strPFn2;
		std::string strLight1;
		std::string strLight2;
		std::string strContent;
		SFile fl;
		tbool		rcDiskOk1(1);
		tbool		rcDiskOk2(1);

		strPFn1 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".1.txt";
		strPFn2 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".2.txt";
		strLight1 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".light1.txt";
		strLight2 = SFile::MkDir2Path(m_strWorkPath) + m_strTblName + ".light2.txt";

		if( WithDetectDirty ) DetectDirty();

		if( iWhich == 1 && m_Dirty1 )
		{
			unitbl_base_t * p = NULL;  
			unitbl_base_t * pp = NULL;

			
			fl.bind( strLight1 );
			fl.erase();
			OnLightFileSync();

			if( m_FastSaveFlag == 1 )  
			{
				
				p = pp = this->ut_GetDup();
			}

			if( pp == NULL )
				pp = this;

			fl.bind( strPFn1 );
			OnBeforeDataFileDel(fl);
			fl.erase();
			rcDiskOk1 = pp->ut_SeriTblFile(fl);
			if(p)
				this->ut_DestroyDup(p);
			if( rcDiskOk1 )
				m_Dirty1 = 0;

			
			fl.bind( strLight1 );
			fl.write_str( SDte::GetNow().ReadString() );
			OnLightFileSync();
		}

		if( iWhich == 2 && m_Dirty2 )
		{
			unitbl_base_t * p = NULL;  
			unitbl_base_t * pp = NULL;

			
			fl.bind( strLight2 );
			fl.erase();
			OnLightFileSync();

			if( m_FastSaveFlag == 1 )
				p = pp = this->ut_GetDup();

			if( pp == NULL )
				pp = this;

			fl.bind( strPFn2 );
			OnBeforeDataFileDel(fl);
			fl.erase();
			rcDiskOk2 = pp->ut_SeriTblFile(fl);
			if(p)
				this->ut_DestroyDup(p);
			if( rcDiskOk2 )
				m_Dirty2 = 0;

			
			fl.bind( strLight2 );
			fl.write_str( SDte::GetNow().ReadString() );
			OnLightFileSync();
		}

		if( iWhich == 1  )
			return rcDiskOk1;

		
			return rcDiskOk2;
	}

	
	tbool SaveF() 
	{
		SDB_t< T > * p=NULL;

		if(1)
		{
			WCrsc aaLock( &(this->m_ut_tbl_lck) );

			
			DetectDirty();

			if( m_Dirty1 || m_Dirty2 )
			{
				
				p = new SDB_t< T >;
				*p = *this;

				p->m_Dirty1 = m_Dirty1;
				p->m_Dirty2 = m_Dirty2;

				
				m_Dirty1 = 0;
				m_Dirty2 = 0;
			}
		}

		if( p )
		p->Save( 0, 0 );

		if( p )
		delete p;

		return 1;
	}

};



	
template< class T >
class SED_t
{
private:
	std::string  m_strSedFn;

public:
	typedef typename T::ROWTYPE 	R;
	typename T::ROWTYPE   m_rowBig;

public:
	SED_t()
	{
		m_strSedFn = "";
	}

	virtual ~SED_t()
	{
		m_strSedFn = "";
	}

public:

	
	tbool InitSed( std::string strFn, tbool biResetFile = 0 )
	{
		SFile fl;
		fl.bind( m_strSedFn = strFn );
		if( biResetFile ) return fl.canoutputabs();
		if( fl.exists() ) return 1;
		if( fl.canoutputabs() ) return 1;
		return 0;
	}

	
	int row_cp( typename T::ROWTYPE & rowSource ) 
	{
		int iMinColNum;
		std::string strVal;

		iMinColNum = rowSource.GetColAmount();
		if( m_rowBig.GetColAmount() < iMinColNum ) iMinColNum = m_rowBig.GetColAmount();

		for( int i = 0; i < iMinColNum; i++ )
		{
			rowSource.GetColStr( i, strVal );
			m_rowBig.SetColVal( i, strVal );
		}

		return iMinColNum;
	}

	
	tbool row_save( tuint32 & rtnOrSet_iBeginOff , tbool biFakeSave = 0 , tbool biOverwriteRowFlag = 0, tuint32 * p_rtn_row_data_len = NULL )
	{
		tbool rc = 0;
		std::string strTmp;
		std::string::size_type ilen;
		FILE *fp;

		fp = (*SClib::p_fopen())( m_strSedFn.c_str(), biOverwriteRowFlag ? "rb+" : "ab" );
		if(fp==NULL) goto L_ROW_SAVE_END;

		if( biOverwriteRowFlag )
		{
			if( 0 != fseek( fp, (long)rtnOrSet_iBeginOff, SEEK_SET ) ) goto L_ROW_SAVE_END;
		}
		else
		{
			if( 0 != fseek( fp, 0,SEEK_END ) ) goto L_ROW_SAVE_END;
			rtnOrSet_iBeginOff = (tuint32)ftell(fp);
		}

		rc = 1;
		if( biFakeSave && p_rtn_row_data_len == NULL ) goto L_ROW_SAVE_END;

		m_rowBig.Serialize(strTmp);

		strTmp += "}a";
		ilen = strTmp.size();
		strTmp[ilen-1] = 0;

		if( p_rtn_row_data_len )
			*p_rtn_row_data_len = (tuint32)(size_t)ilen;

		if( biFakeSave ) goto L_ROW_SAVE_END;

		if( fwrite( strTmp.c_str(), (size_t)ilen, 1, fp ) )
			rc = 1;
		else
			rc = 0;

L_ROW_SAVE_END:
		if(fp) fclose(fp);
		return rc;
	}

	
	tbool row_save_add( tuint32 * p_rtn_Cur_tail_pos = NULL )
	{
		tuint32 rtnOff;
		tuint32 row_data_len;
		tbool rc;
		rc = this->row_save( rtnOff, 0, 0, &row_data_len );
		if( p_rtn_Cur_tail_pos ) *p_rtn_Cur_tail_pos = rtnOff+row_data_len;
		return rc;
	}

	
	tbool row_save_over(tuint32 offs)
	{
		return this->row_save( offs, 0, 1 );
	}


	tbool row_load( tuint32 iBeginOff, tuint32 * p_rtn_NextOff = NULL )
	{
		std::vector<char> v1;
		SCake ckbuf;
		FILE *fp = NULL;
		tbool rc = 0;
		tsize a;
		tbool biLeadZeroFlag = 0;

		if( m_strSedFn.empty() )  goto L_ROW_LOAD_END;

		fp = (*SClib::p_fopen())( m_strSedFn.c_str(), "rb" );
		if(fp==NULL) goto L_ROW_LOAD_END;

		ckbuf.redim( 128 );

		if( 0 != fseek( fp, iBeginOff, SEEK_SET ) ) goto L_ROW_LOAD_END;

		while(1)
		{
			SStrf::smemset( ckbuf.buf(), 0, ckbuf.len() );
			a = (tsize)fread( ckbuf.buf(), 1, ckbuf.len(), fp );

			if( a == ckbuf.len() )
			{
				tsize i;
				std::copy( ckbuf.buf(), ckbuf.buf() + ckbuf.len(), std::back_inserter(v1) );
				for( i = 0; i < a; i++ )
				{
					if( *(ckbuf.buf()+i) != 0 )
					{
						biLeadZeroFlag = 1;
					}

					if( *(ckbuf.buf()+i) == 0 && biLeadZeroFlag == 1 )
						break;
				}

				if( i < a )
				{
					break;
				}
			}
			else
			if( a == 0 )
			{
				break;
			}
			else
			{
				ckbuf.cut( ckbuf.len() - a );
				std::copy( ckbuf.buf(), ckbuf.buf() + ckbuf.len(), std::back_inserter(v1) );
				break;
			}

		} 

		if( v1.empty() )
			goto L_ROW_LOAD_END;

		
		while( !v1.empty() && v1[0] == 0 ) v1.erase(v1.begin());

		v1.push_back(0);
		a = (tsize)SStrf::slen(&v1[0]);

		if( p_rtn_NextOff ) *p_rtn_NextOff = iBeginOff + 1 + (tuint32)a;

		if( a == 0 )
			goto L_ROW_LOAD_END;
		else rc = 1;

		m_rowBig.Unserialize( &v1[0] );

L_ROW_LOAD_END:
		if(fp) fclose(fp);
		return rc;
	}


	tbool row_load( tuint32 * p_begin_n_next )
	{
		tuint32 iNext;
		tbool rc;
		rc = row_load( *p_begin_n_next, &iNext );
		if(rc) *p_begin_n_next=iNext ;
		return rc;
	}


	
	tbool del_middle( tuint32 iDelRow , tuint32 * p_rtn_rest_rows = NULL )
	{
		std::string SedFn1 = m_strSedFn;
		std::string SedFn2 = m_strSedFn + "_2";
		SFile fl;
		tbool rc;
		tuint32 off1;
		tuint32 iCount;
		SED_t< T > *p2 = new SED_t< T >;

		
		rc = p2->InitSed( SedFn2, 1 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		rc = fl.cp2( m_strSedFn, SedFn2 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		off1 = 0;
		for( iCount = 0; iCount <= iDelRow; iCount++ ) 
		{
			rc = p2->row_load( &off1 );
			if( !rc )
			{
				break;
			}
		}

		
		rc = this->InitSed( SedFn1, 1 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		for( iCount = 0; ; iCount++ )
		{
			rc = p2->row_load( &off1 );
			if( !rc )
			{
				break;
			}

			this->m_rowBig = p2->m_rowBig;
			rc = this->row_save_add();
			if( !rc )
			{
				goto L_DEL_HEAD_END;
			}
		}

		if( p_rtn_rest_rows ) *p_rtn_rest_rows = iCount;

		rc = 1;

L_DEL_HEAD_END:
		fl.bind(SedFn2);
		fl.erase();
		delete p2;
		return rc;
	}


	virtual tbool on_should_del_middle( tuint32 iCount )
	{
		return 0;
	}

	
	tbool del_middle( tuint32 * p_rtn_rest_rows = NULL )
	{
		std::string SedFn1 = m_strSedFn;
		std::string SedFn2 = m_strSedFn + "_2";
		SFile fl;
		tbool rc;
		tuint32 off1;
		tuint32 iCount;
		SED_t< T > *p2 = new SED_t< T >;

		
		rc = p2->InitSed( SedFn2, 1 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		rc = fl.cp2( m_strSedFn, SedFn2 );
		if( !rc ) goto L_DEL_HEAD_END;

		
		rc = this->InitSed( SedFn1, 1 );
		if( !rc ) goto L_DEL_HEAD_END;

		off1 = 0;

		
		for( iCount = 0; ; iCount++ )
		{
			rc = p2->row_load( &off1 );
			if( !rc )
			{
				break;
			}

			if( !on_should_del_middle( iCount ) )
				continue;

			this->m_rowBig = p2->m_rowBig;
			rc = this->row_save_add();
			if( !rc )
			{
				goto L_DEL_HEAD_END;
			}
		}

		if( p_rtn_rest_rows ) *p_rtn_rest_rows = iCount;

		rc = 1;

L_DEL_HEAD_END:
		fl.bind(SedFn2);
		fl.erase();
		delete p2;
		return rc;
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_WFile_h
#define X011__H_w_WFile_h



X011_NAMESPACE_BEGIN


class WFile : public SFile
{

private:


public:

	WFile( )
	{
		;
	}


	virtual ~WFile( )
	{ ;
	}

	
	static int run_exe( std::string strCmd )
	{
		int i;
		return i = (int)system(strCmd.c_str());
	}

	
	void rename( std::string strNewNameCanBeWithNewDir )
	{
		std::string strCmd;

		strCmd = "mv \"";
		strCmd += this->filename();
		strCmd += "\" ";
		strCmd += "\"" + strNewNameCanBeWithNewDir + "\"";

		system( strCmd.c_str() );
	}


	static void makedir( std::string str )
	{
		SStrf::sreplstr( str, "\\", "|" );
		SStrf::sreplstr( str, "/", "|" );
		SStrf::sreplstr( str, "|", GetPathSep() );

		mkdir( str.c_str() , 0777);
	}

	
	static tbool FileAttriIsDir( std::string strFullPathName )
	{
        struct   stat   stbuf;

        if(   lstat( strFullPathName.c_str(),   &stbuf )   <   0)
		{
                return   0;
        }
        else
		{
			return   (S_ISDIR(stbuf.st_mode))?   1   :   0   ;
		}
	}



	static void ListFile(	std::string strRootPathOrDir,	
							std::string strPattern,			
							std::vector<std::string> & vecstrRtnBuf1 ,
							tbool bIncludeDirName,
							tbool bIncludeFileName,
							tbool bRetFullName	)
	{
		

		std::vector<std::string>  vecstrRtnBuf;

		DIR *pdir;
		struct dirent *pdirent;
		pdir = opendir( strRootPathOrDir.c_str() );

		if( !pdir )
		{
			return;
		}

		while( ( pdirent = readdir(pdir) ) ) 
		{
			std::string strFn( pdirent->d_name );
			std::string strFullFn( MkDir2Path( strRootPathOrDir ) + strFn );
			std::string strOut;

			if( bRetFullName )
			{
				strOut = strFullFn;
			}
			else
			{
				strOut = strFn;
			}

			if( strFn == "." || strFn == ".." )  continue;

			if( bIncludeDirName && FileAttriIsDir( strFullFn ) )
			{
				vecstrRtnBuf.push_back( strOut );
			}

			if( bIncludeFileName && !FileAttriIsDir( strFullFn ) )
			{
				vecstrRtnBuf.push_back( strOut );
			}

		} 

		closedir(pdir);

		
		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end();  )
		{
			std::string s2( strPattern );

			if( s2.size() < 3 ) break;
			if( s2[0] != '*' ) break;
			if( s2[1] != '.' ) break;
			if( s2[2] == '*' ) break;

			std::string s1( *it1 );

			std::reverse( s1.begin(), s1.end() );

			s2.erase( s2.begin() );
			std::reverse( s2.begin(), s2.end() );

			if( s1.find(s2) != 0 ) 
			{
				it1 = vecstrRtnBuf.erase( it1 );
			}
			else
				it1++;
		}

		
		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end();  )
		{
			std::string s2( strPattern ); 

			std::reverse( s2.begin(), s2.end() ); 

			if( s2.size() < 3 ) break;
			if( s2[0] != '*' ) break;
			if( s2[1] != '.' ) break;
			if( s2[2] == '*' ) break;

			
			s2.erase( s2.begin() );
			std::reverse( s2.begin(), s2.end() ); 

			std::string s1( *it1 );

			if( s1.find(s2) != 0 ) 
			{
				it1 = vecstrRtnBuf.erase( it1 );
			}
			else
				it1++;
		}


		for( std::vector<std::string>::iterator it2 = vecstrRtnBuf.begin(); it2 != vecstrRtnBuf.end(); it2++ )
		{
			vecstrRtnBuf1.push_back(*it2);
		}
	}


	static void ListAllFile(	std::string strRootPathOrDir,		
								std::string strPattern,				
								std::vector<std::string> & vecstrRtnBuf	,
								tbool bIncludeDirName  = 0 ,
								tbool bIncludeFileName = 1 ,
								tbool bRetFullName     = 0 ,
								tbool bRecursive       = 0	)
	{
		

		if( bRecursive )
		{
			std::vector<std::string>  vecBuf1;
			std::vector<std::string>::iterator itBuf1;
			std::vector<std::string>  vecBuf2;
			std::vector<std::string>  vecBuf_FullName;

			vecBuf1.push_back( strRootPathOrDir );

			do{
				vecBuf2.clear();

				itBuf1 = vecBuf1.begin();

				if( itBuf1 == vecBuf1.end() )
				{
					break;
				}

				ListFile( *itBuf1, "*", vecBuf2, 1, 0, 1 ); 
				vecBuf_FullName.insert( vecBuf_FullName.end(), vecBuf2.begin(), vecBuf2.end() );

				vecBuf1.erase( itBuf1 ); 

				vecBuf1.insert( vecBuf1.end(), vecBuf2.begin(), vecBuf2.end() ); 

			}while(1);

			if( 1 )
			{
				for( std::vector<std::string>::iterator it = vecBuf_FullName.begin();
					 it != vecBuf_FullName.end();
					 ++it )
				{
					ListFile( *it, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName ); 
				}
				ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
			}
		}
		else
		{
			ListFile( strRootPathOrDir, strPattern, vecstrRtnBuf, bIncludeDirName, bIncludeFileName, bRetFullName );
		}
	}


	
	static void DelHalf( std::string strRootDir, std::string strPattern )			
	{
		std::vector<std::string>  vecstrRtnBuf;

		ListFile( strRootDir, strPattern, vecstrRtnBuf, 0, 1, 1 );

		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end(); ++it1 )
		{
			for( std::vector<std::string>::iterator it2 = vecstrRtnBuf.begin(); it2 != vecstrRtnBuf.end(); ++it2 )
			{
				SFile f1, f2;
				f1.bind( *it1 );
				f2.bind( *it2 );
				if( f1.IsHeadOf(f2) ) f1.erase();
			} 
		} 
	}


		struct FileStat_t
		{
			std::string strFullFn;
			std::string strFileDSeal;
			tsize iFileLen;
			tbool tbExists;
		} ;
		
	static void DelHalf_fast( std::string strRootDir, std::string strPattern, tsize iMinLen )			
	{
		std::vector<std::string>  vecstrRtnBuf;
		std::vector<FileStat_t>  vecFileStat;

		ListFile( strRootDir, strPattern, vecstrRtnBuf, 0, 1, 1 );

		for( std::vector<std::string>::iterator it1 = vecstrRtnBuf.begin(); it1 != vecstrRtnBuf.end(); ++it1 )
		{
			SFile fl ;
			SCake ck;
			FileStat_t fs;

			fl.bind( *it1 );
			fs.strFullFn = *it1;
			fs.iFileLen = fl.len();
			fs.tbExists = fs.iFileLen < iMinLen ? 0 : 1 ;
			if( !fs.tbExists )
			{
				fl.erase();
				continue;
			}
			fl.read( ck );
			fs.strFileDSeal = SCalc::dseal( ck.buf(), iMinLen, 123 );

			vecFileStat.push_back( fs );
		} 


		for( std::vector<FileStat_t>::iterator it2 = vecFileStat.begin(); it2 != vecFileStat.end(); ++it2 )
		{
			for( std::vector<FileStat_t>::iterator it3 = vecFileStat.begin(); it3 != vecFileStat.end(); ++it3 )
			{
				if( !(it2->tbExists && it3->tbExists) ) continue;
				if( it2->strFileDSeal != it3->strFileDSeal ) continue;
				if( it2->strFullFn == it3->strFullFn ) continue;

				std::vector<FileStat_t>::iterator it4 = it3;
				if( it2->iFileLen < it3->iFileLen ) it4 = it2;

				SFile::erase( it4->strFullFn );
				it4->tbExists = 0;

				printf( "%s\n", it4->strFullFn.c_str() );
			} 
		} 

	}


	tbool bind_tmpfile( const tchar * pszExt = NULL , int iThreadId = 0 ) 
	{
		std::string  strEnvTmpPath;
		strEnvTmpPath = "/tmp/";
		if( strEnvTmpPath == "" ) return 0;
		return bind_nofile( strEnvTmpPath, pszExt, iThreadId );
	}


	
	static void PackFolder( std::string strWorkPathOrDir, SCake & ckOut )
	{
		
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;
		std::string strSeal;
		int iSealLen = 33;

		
		std::string strTD = "\t";
		std::string strTR = "\n";


		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;



		ListAllFile( strWorkPath, "*.*", vDirFullNameLst, 1, 0, 1, 1 );

		for( it = vDirFullNameLst.begin(); it != vDirFullNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vDirNameLst.push_back(p);
		}

		
		SSetu::vs_setgroup( vDirNameLst );



		ListAllFile( strWorkPath, "*.*", vFileFullPathNameLst, 0, 1, 1, 1 );

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			const char *p;
			p = it->c_str() + strWorkPath.size();
			vFileRelaPathNameLst.push_back(p);
		}



		tint32 iLenAmount=0;

		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it )
		{
			SFile sf;
			tint32 i;

			sf.bind( *it );
			i = sf.len();
			iLenAmount += i;
			vFileLenLst.push_back( SStrf::sltoa( i ) );
		}



		strInfoHeader = "";

		strSeal = SCalc::dseal( " ", iSealLen ); 
		strInfoHeader = strSeal + strTD;
		strInfoHeader += strTR;

		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;
		}
		strInfoHeader += strTR;

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;
		}
		strInfoHeader += strTR;

		for( it = vFileLenLst.begin(); it != vFileLenLst.end(); ++it )
		{
			strInfoHeader += *it;
			strInfoHeader += strTD;
		}
		strInfoHeader += strTR;


		

		ckOut.redim( iLenAmount + (tsize)strInfoHeader.size() + 1 );

		tchar *p1;

		p1 = ckOut.buf();

		
		SStrf::smemcpy( p1, strInfoHeader.c_str(), (tsize)strInfoHeader.size() );
		p1 += (tsize)strInfoHeader.size();

		*p1 = 0;
		p1 ++; 

		std::vector<std::string>::iterator it2;

		it2 = vFileLenLst.begin();
		for( it = vFileFullPathNameLst.begin(); it != vFileFullPathNameLst.end(); ++it, ++it2 )
		{
			SCake ck;
			SFile sf;

			sf.bind( *it );
			sf.read( ck );

			if( ck.len() )
			{
				SStrf::smemcpy( p1, ck.buf(), (tint32)ck.len() <  SStrf::satol( *it2 ) ? (tint32)ck.len() :  SStrf::satol( *it2 ) );
			}

			
			p1 += SStrf::satol( *it2 );
		}

		
		strSeal = SCalc::dseal( ckOut.buf() + iSealLen, ckOut.len() - iSealLen, iSealLen );
		SStrf::smemcpy( ckOut.buf(), strSeal.c_str(), (tint32)strSeal.size() );
	}


	static tbool UnPackFolder(      std::string strWorkPathOrDir,
									const SCake & ckIn , tbool biCheckSeal = 1 ,
									tbool biWriteDiskReal = 1 ,
									const char * pWhitePfn = NULL	,
									std::vector<std::string> *pvWhiteLst = NULL ,
									std::vector<std::string> *pvDirFullNameLst = NULL ,
									std::vector<std::string> *pvFileFullPathNameLst = NULL
								)
	{
		if( ckIn.len() == 0 ) return 0;

		
		
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;
		std::string strSeal;
		std::string strSeal2;
		int iSealLen = 33;


		std::string strTD = "\t";
		std::string strTR = "\n";

		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;

		tsize iii3;
		const char * ppp3 = (const char*)ckIn.buf_const();
		for( iii3 = 0; iii3 < ckIn.len(); iii3++ ) if( *(ppp3 + iii3) == 0 ) break;
		strInfoHeader.assign( (const char*)ckIn.buf_const(), (const char*)ckIn.buf_const() + iii3 ); 

		if( biCheckSeal )
		{
			strSeal = SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 );
			strSeal = SStrvs::vsa_get( strSeal, strTD, 0, 0 );

			if( (int)ckIn.len() <= (int)iSealLen ) return 0;
			strSeal2 = SCalc::dseal( ckIn.buf_const() + iSealLen, ckIn.len() - iSealLen, iSealLen );

			if( strSeal != strSeal2 ) return 0;
		}

		
		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 + 1 ), strTD, 1, vDirNameLst );

		std::sort( vDirNameLst.begin(), vDirNameLst.end() ); 

			
		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vDirFullNameLst.push_back( s1 );

			
			if( biWriteDiskReal )
			{
			
			
				mkdir(s1.c_str(), 0777);
			}
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 1 + 1 ), strTD, 1, vFileRelaPathNameLst );

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vFileFullPathNameLst.push_back( s1 );
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 2 + 1 ), strTD, 1, vFileLenLst );


		if( pvDirFullNameLst != NULL ) *pvDirFullNameLst = vDirFullNameLst;
		if( pvFileFullPathNameLst != NULL ) *pvFileFullPathNameLst = vFileFullPathNameLst;



		const tchar *p1;

		p1 = ckIn.buf_const() + strInfoHeader.size() + 1;

		

		for( ; !vFileFullPathNameLst.empty(); )
		{
			std::string s1;
			tint32 i1;

			s1 = vFileFullPathNameLst.front();
			i1 = SStrf::satol( vFileLenLst.front() );

			if( p1 > ckIn.buf_const() + ckIn.len() ) break;

			SFile sf;

			sf.bind( s1 );

			if( biWriteDiskReal )
			{
				if( pvWhiteLst == NULL && pWhitePfn == NULL )
				{
					sf.write( p1, (tsize)i1 );
				}

				if( pvWhiteLst != NULL )
				{
					for( std::vector<std::string>::iterator itwhite = pvWhiteLst->begin(); itwhite != pvWhiteLst->end(); ++itwhite )
					{
						if( MkDir2Path( strWorkPathOrDir ) + *itwhite == s1 )
						{
							sf.write( p1, (tsize)i1 );
							break;
						}
					}
				}

				if( pWhitePfn != NULL )
				{
					std::string sA, sB;
					sA = MkDir2Path( strWorkPathOrDir ) + pWhitePfn;
					sB = s1;
					SStrf::sucase( sA );
					SStrf::sucase( sB );
					if( sA == sB )
					{
						sf.write( p1, (tsize)i1 );
					}
				}
			}

			vFileFullPathNameLst.erase( vFileFullPathNameLst.begin() );
			vFileLenLst.erase( vFileLenLst.begin() );

			p1 += i1;
		}

		return 1;
	}


	

	static void lf_conv_code( std::string & s , const char *tocode, const char *fromcode )
	{
		iconv_t cd = iconv_open( tocode, fromcode );
		unsigned int inlen  = strlen(s.c_str());
		char *outbuf = (char *)malloc( inlen * 4 );
		memset( outbuf, (int)0, inlen * 4);
		char *in2 = (char*)s.c_str();
		char *out2 = outbuf;
		size_t outlen = inlen *4;
		iconv(cd, &in2, (size_t *)&inlen, &out2, &outlen);
		outlen = strlen(outbuf);
		
		s = outbuf;
		free(outbuf);
		iconv_close(cd);
	}


	static std::string & ChtoUtf8( std::string & s ) 
	{
		lf_conv_code( s, "UTF-8", "GBK" );
		return s;
	}


	static std::string & Utf8toCh( std::string & s )
	{
		lf_conv_code( s, "GBK", "UTF-8" );
		
		return s;
	}


	static std::string & GB_BIG5( std::string & s )
	{
		lf_conv_code( s, "UTF-8", "GBK" );
		lf_conv_code( s, "BIG5", "UTF-8" );
		return s;
	}


	
	static std::string MkRUStr()
	{
		static tint32 i = 1;

#ifdef OS_MACOSX_
		std::string ss = SStrf::b2s_i( pthread_self() ) + "12341234";
		int i2 = (int)time(0) * ( *(int*)( &(ss[0]) ) );
#else
		int i2 = (int)time(0) * (int)pthread_self();
#endif

		int j;
		void *p = SStrf::smalloc(3);
		memcpy( &j, &p, sizeof(int) );
		SStrf::sfree(p);

		double dd = SStrf::rand1() * i * i2 * j * SDte::e_proctime();
		std::string s2 = SStrf::sftoa(dd);
		std::string s3 = SStrf::sftoa(dd);

		std::reverse( (char*)(&dd), (char*)(&dd) + sizeof(double) );
		std::reverse( s2.begin(), s2.end() );

		tchar szBuf[33];
		tchar *pp=szBuf;
		SClib::p_sprintf()( szBuf, "%p%x", *(int*)(&dd) + j + i + SStrf::satol(s2) + SStrf::satol(s3) + (int)time(0) + i2 , 0xfff & i );
		i++;

		if( szBuf[0] == '0' && szBuf[1] == 'x' ) pp++;
		return SStrf::slcase(pp);
	}


};




X011_NAMESPACE_END


#endif






#ifndef X011__H_W_WNAVA_H
#define X011__H_W_WNAVA_H


X011_NAMESPACE_BEGIN


class WNava : public SNavass
{
public:

	WNava()
	{
	}

	WNava( const WNava & aa2 )
	{
		m_mapKnl = aa2.m_mapKnl;
	}

	WNava( const SNavass & aa2 )
	{
		m_mapKnl = aa2.m_mapKnl;
	}


public:

	virtual ~WNava() {;}


	
	
	

	
	void impconf( const std::string & ssource, std::string ssepTR = "\n", std::string ssepTD = "=", std::string strMemoLineHead = "#" )
	{
		

		std::vector<std::string>  vecLines;
		SStrvs::vsa_imp( ssource, ssepTR, 1, vecLines );
		for( std::vector<std::string>::iterator it = vecLines.begin(); it != vecLines.end(); ++it )
		{
			std::string::size_type i;

			i = it->find(ssepTD);
			if( i == std::string::npos ) continue;

			SStrf::strim( *it );
			if( strMemoLineHead != "" && it->find(strMemoLineHead) == 0 ) continue;

			(*it)[i] = 0;
			this->let( it->c_str(), it->c_str() + i + ssepTD.size() );
		}

		this->trimall();
	}

	
	static WNava ReadFileNa( const std::string & Fn )
	{
		SFile fInFile;
		std::string	 strFileContent;
		fInFile.bind( Fn );
		fInFile.read_str( strFileContent );
		WNava nvA;
		nvA.impconf( strFileContent );
		return nvA;
	}


	
	
	
	WNava & InterpCmdLine( int argc, char* argv[] )
	{
		for( int i = 1; i < argc; i += 2 )
		{
			std::string n;
			std::string v = " ";	
			if( i   < argc ) n = argv[i  ];
			if( i+1 < argc ) v = argv[i+1];
			this->let( n, v );
		}
		return *this;
	}



	typedef std::string & (* P_t) ( std::string & );


	void AtoB( P_t pf )
	{
		std::map< std::string, std::string > mapTmp = m_mapKnl;

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			std::string s1 = it->first;
			std::string s2 = it->second;

			(*pf)( s1 );
			(*pf)( s2 );

			let( s1, s2 );
		}
	}


#ifdef VC6_COMPATIBLE_X011_

#else

	void ChtoUtf8()
	{
		AtoB( WFile::ChtoUtf8 );
	}

	void Utf8toCh()
	{
		AtoB( WFile::Utf8toCh );
	}

#endif


	WNava & operator = ( const WNava & aa2 )
	{
		m_mapKnl = aa2.m_mapKnl;
		return *this;
	}

	WNava & operator = ( const SNavass & aa2 )
	{
		m_mapKnl = aa2.m_mapKnl;
		return *this;
	}

};



X011_NAMESPACE_END

#endif






#ifndef X011__H_w_wthrd_h
#define X011__H_w_wthrd_h



X011_NAMESPACE_BEGIN


class WThrd
{

private:

	pthread_t   m_hThread;	
	volatile int m_iAutoDel;
	volatile int m_iShouldBreak;
	volatile int m_iLive;
	volatile int m_iShouldDetach;
	volatile int m_iCreationDone;

	volatile int m_iOpened;

	pthread_attr_t  m_stacksize;
	volatile int m_join_count;

private:


	static void * ThreadProc(void * lpParam)
	{
		WThrd *pThis=reinterpret_cast<WThrd*>(lpParam);
		int iAutoDel = pThis->m_iAutoDel; 
		int iAutoDelrc = 0;

		
		pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);

		try
		{
			pThis->tr_init_rand();
			pThis->tr_on_pre_thrd();
			pThis->tr_on_knl_run();
			pThis->tr_on_post_thrd();

			pThis->tr_shouldbrk();

			pThis->m_iLive = 0;

			if(iAutoDel)
			{
				if( !pThis->m_iCreationDone )
				{
					while( !pThis->m_iCreationDone )
						tr_sleep( 1 );

					tr_sleep( 1 );
				}

				tr_sleep( 1 ); 

				
				iAutoDelrc = 1;
			}
		}
		catch(...)
		{ ;	}

		if( iAutoDelrc ) delete pThis;
		return((void *)0);
	}


private:

	WThrd & operator = (const WThrd & rhs)
	{
		return *this;
	}


	WThrd(const WThrd & rhs)
	{;}


protected:
	volatile int m_idestructed; 

protected:
	void tr_destruct()
	{
		if( !m_idestructed )
		{
			m_idestructed = 1;

			
			pthread_attr_destroy(&m_stacksize);


			if( !m_iOpened ) return;

			
			{
				tr_shouldbrk();

				if( !m_iAutoDel )
				{
					if( m_join_count != 1 )
					{
						pthread_join( m_hThread , NULL );
						m_join_count++;
					}
				}

				
			}
			
			
			if( m_iAutoDel )
				if( m_iShouldDetach ) pthread_detach(m_hThread); 
			
		}
	}

public:

	WThrd()
	{
		
		m_iAutoDel = 0;
		m_iShouldBreak = 0;
		m_iLive = 0;
		m_iShouldDetach = 1;
		m_iCreationDone = 0;
		m_iOpened = 0;

		pthread_attr_init(&m_stacksize);

		size_t val;

		
		val = 2 * 1024 * 1024;
		pthread_attr_setstacksize(&m_stacksize, val);

		m_idestructed = 0;
		m_join_count = 0;
	}


	virtual ~WThrd()
	{
		tr_destruct();
	}


public:

	static std::string tr_GetCurrentThreadId()
	{
		char sz1[22];
		SClib::p_sprintf()( sz1, "%p", pthread_self() );
		return sz1;
	}


	pthread_t tr_GetHnd() const
	{
		return m_hThread;
	}

	
	void tr_init_rand()
	{
		int j, j2;
		pthread_t h;
		void *p;

		h = tr_GetHnd();
		memcpy( &j,  &h, sizeof(int) < sizeof(h) ? sizeof(int) : sizeof(h) );
		p = (void*)tr_GetCurrentThreadId().c_str();
		memcpy( &j2, &p, sizeof(int) < sizeof(p) ? sizeof(int) : sizeof(p) );

		SStrf::initrand( j + j2 );
	}

	
	static void tr_sleep( int iSec , double dSec = 0.0 )	
	{
		if( iSec > 0 )
			sleep( iSec );

		if( dSec > 0.0 )
		{
			usleep( static_cast<int>(dSec * 1000 * 1000) );
		}
	}

	
	static void tr_sleepu( double dSec ) 
	{
		if( dSec > 0 )
		{
			tr_sleep( (int)dSec, dSec - (int)dSec );
		}
	}

	
	tbool tr_open()
	{
		m_iCreationDone = 0;

		on_before_tr_open();

		
		m_iLive = 1;

		
		int err;

		

		err = pthread_create( &m_hThread, &m_stacksize,  
										ThreadProc, reinterpret_cast<void*>(this) );

		tbool rc = 1;

		if(err != 0)
		{
			m_iLive = 0;
			rc = 0;
		}

		if(rc) on_after_tr_open(); 


		if( tr_isRunning() )
		{
			m_iOpened = 1;
		}

		m_iCreationDone = 1;

		return rc;
	}


	tbool tr_openx() 
	{
		m_iAutoDel = 1;
		return tr_open();
	}


	void tr_shouldbrk()
	{
		m_iShouldBreak = 1;
	}


	int tr_isShouldBrk() const
	{
		return m_iShouldBreak;
	}


	int tr_isRunning()
	{
		 return m_iLive;
	}


	void tr_Terminate()
	{
		if( !m_iOpened ) return;

		try
		{
			if( tr_isRunning() )
			{
				
				
				pthread_cancel(m_hThread); 
			}
		}
		catch (...)
		{	;
		}
	}


	void tr_closehandl()
	{
		tr_shouldbrk();
	}


	
	
	int tr_wait(  )
	{
		if( !m_iOpened ) return 0;

		if( m_join_count++ != 1 ) pthread_join( m_hThread , NULL );

		m_iAutoDel = 0;
		m_iShouldDetach = 0;

		return 0;
	}



	
	virtual void on_before_tr_open()
	{
	}

	
	virtual void on_after_tr_open()
	{
	}


	virtual void tr_on_knl_run()
	{
		while(1)
		{
			if( !tr_on_user_run() ) break;

			if( m_iShouldBreak ) break;

			
		}
	}

	
	virtual void tr_on_pre_thrd()
	{
	}

	
	virtual void tr_on_post_thrd()
	{
	}

	
	virtual int tr_on_user_run() 
	{
		return 0;
	}

	
	virtual tbool tr_OnMgrPrepare() 
	{
		return 1;
	}

}; 




X011_NAMESPACE_END

#endif








#ifndef X011__H_W_WTHRDMGR_H
#define X011__H_W_WTHRDMGR_H


X011_NAMESPACE_BEGIN






template < class ThreadEle_T , class THREADBASE_T = WThrd >
class WThrdMgr : public THREADBASE_T
{
private:

public:
	typedef	 ThreadEle_T   ThrEle_t;
	volatile tbool         m_biMgrShouldBreak;
	double                 m_FailWaitTimesec; 
	tbool                  m_biIsMultiEleType;

public:
	
	WThrdMgr()
	{
		m_biMgrShouldBreak = 0;
		m_FailWaitTimesec = 0.2;
		m_biIsMultiEleType = 1;
	}

	
	virtual ~WThrdMgr()
	{ THREADBASE_T::tr_destruct();	}

	
	virtual tbool OnMgrPrepare( ThrEle_t & t ) 
	{
		return 1;
	}

	
	virtual int tr_on_user_run()
	{
		BirthEle();

		return 1;
	}

	
	virtual ThrEle_t * MgrPrepare()   
	{
		ThrEle_t * p;

		try{
			p = new ThrEle_t;
		}
		catch(...)
		{p=NULL;}

		if( p==NULL ) return NULL;

		if( !OnMgrPrepare(*p) ) 
		{
			delete p;
			return NULL;
		}

		if( ! p->tr_OnMgrPrepare() ) 
		{
			delete p;
			return NULL;
		}

		return p;
	}



	tbool BirthEle()
	{
		if( m_biMgrShouldBreak ) return 0;

		if( THREADBASE_T::tr_isShouldBrk() ) return 0;

		ThrEle_t * p = MgrPrepare();

		if( p != NULL )
		{
			if( m_biIsMultiEleType )
			{
				p->tr_openx();
			}
			else
			{
				p->tr_open();
				p->tr_wait(); 
				delete p;
			}

			return 1;
		}
		else
		{
			if( m_FailWaitTimesec <= 0 ) return 0;

			WThrd::tr_sleepu( m_FailWaitTimesec );

			return 0;
		}
	}

};




















































class WThrdCity
{
public:

		class WThrd2 : public WThrd
		{

		friend class WThrdCity;

		private:
			WThrdCity * m_pWThrdCity;

			int tr_on_user_run() 
			{
				return OnRun() ;
			}

		public:

			WThrd2()
			{
				m_pWThrdCity = NULL;
			}

			virtual ~WThrd2()
			{
				if( m_pWThrdCity ) m_pWThrdCity->RemoveEle(*this);

				tr_destruct();
			}

			virtual int OnRun()
			{
				return 0;
			}

		};


	typedef  WThrd2  WThrdEle;

	
	friend class WThrd2;


private:

	std::vector< WThrdEle * >  m_vecThrdLst;

	WCrsc m_crscThrdLst;

	WCrsc m_crscThrdOpenFunc;

	
	int AddEle( WThrdEle & t )
	{
		WCrsc aLock( &(this->m_crscThrdLst) );
		WThrdEle * p = SStrf::AddressOf( t );

		m_vecThrdLst.push_back( p );
		return GetThrdAmount();
	}

	
	int RemoveEle( WThrdEle & t )
	{
		WCrsc aLock( &(this->m_crscThrdLst) );
		WThrdEle * p = SStrf::AddressOf( t );

		std::vector< WThrdEle * >::iterator it = std::find( m_vecThrdLst.begin(), m_vecThrdLst.end(), p );
		if( it != m_vecThrdLst.end() )
		{
			m_vecThrdLst.erase( it );
		}
		return GetThrdAmount();
	}

public:
	int m_iLimit;

	tbool m_bWithOpenFailRetry;

public:
	
	WThrdCity( int iLimit = 123 )
	{
		m_iLimit = iLimit;
		m_bWithOpenFailRetry = 0;
	}

	
	virtual ~WThrdCity()
	{;	}

public:
	
	int GetThrdAmount() const
	{
		return (int)m_vecThrdLst.size();
	}

	
	void CleanStoppedThrd()
	{
		WCrsc aLock ( &m_crscThrdOpenFunc );
		WCrsc a2Lock( &m_crscThrdLst );

		std::vector< WThrdEle * >::iterator it;

		for( it = m_vecThrdLst.begin();
			 it != m_vecThrdLst.end();
			 ++it	)
		{
			if( (*it)->tr_isRunning() )
			{
				
			}
			else
			{
				(*it)->m_pWThrdCity = NULL; 
				delete *it;
				it = m_vecThrdLst.erase( it );
			}
		}

	}

	
	tbool OpenThrd( WThrdEle & t )
	{
		WCrsc aLock( &m_crscThrdOpenFunc );

		if( GetThrdAmount() >= m_iLimit )
		{
			
			return 0;
		}

		AddEle( t );

		t.m_pWThrdCity = this;
		t.tr_open();

		return 1;
	}

	
	tbool OpenThrdHp( WThrdEle * t1 ) 
	{
		WCrsc aLock( &m_crscThrdOpenFunc );

		if( !t1 ) return 0;

		if( GetThrdAmount() >= m_iLimit )
		{
			
			return 0;
		}



		AddEle( *t1 ); 

		( *t1 ).m_pWThrdCity = this;
		( *t1 ).tr_openx();

		return 1;
	}

	
	template< class ThrdEle_T >
	tbool OpenThrdHp()
	{
		

		WThrdEle * p = new ThrdEle_T ;

		return OpenThrdHp(p); 
	}


	
	
};


typedef  WThrdCity::WThrd2  WThrdEle;


#ifdef VC6_COMPATIBLE_X011_

#else




template < class TASK_T , class TH_T = WThrd >
class WIdleThrd
{
public:
	typedef  TASK_T  TASK_t;

private:
	std::vector<TASK_T>   m_vecTasks;
	WCrsc                 m_crTasksReadLck;

	WCrsc                 m_crTasksRunLck;

	volatile int          m_iWorkThrdObjRef; 
	WCrsc                 m_crWorkThrdObjRefLck;

	volatile int          m_iWorkThrdWaitingRunfuncRef; 
	WCrsc                 m_crWorkThrdWaitingRunfuncRefLck;

	volatile int          m_iWorkThrdRunRef; 
	WCrsc                 m_crWorkThrdRunRefLck;

	friend class WIdleThrdEle;

	volatile int          m_isLive; 

public:
		
		class WIdleThrdEle : public TH_T
		{
		private:
			WIdleThrd < TASK_T , TH_T >  * m_pWIdleThrd;

			
			int tr_on_user_run()
			{
				if(1)
				{
					WCrsc aaa2 ( &(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck) );
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef++;
				}

				TASK_T t;
				WCrsc aaa ( &(m_pWIdleThrd->m_crTasksRunLck) ); 

				if(1)
				{
					WCrsc aaa2 ( &(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck) );
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef--;
				}

				for( ; m_pWIdleThrd->TakeTask(t); )  
				{
					m_pWIdleThrd->OnRunTask(t);
				}

				return 0;
			}

			
			virtual void tr_on_pre_thrd()
			{
				WCrsc aaa ( &(m_pWIdleThrd->m_crWorkThrdRunRefLck) );
				m_pWIdleThrd->m_iWorkThrdRunRef++;
			}

			
			virtual void tr_on_post_thrd()
			{
				WCrsc aaa ( &(m_pWIdleThrd->m_crWorkThrdRunRefLck) );
				m_pWIdleThrd->m_iWorkThrdRunRef--;
			}

		public: 
			
			WIdleThrdEle( WIdleThrd < TASK_T , TH_T > *p )
			{
				m_pWIdleThrd = p;

				WCrsc aaa ( &(m_pWIdleThrd->m_crWorkThrdObjRefLck) );

				m_pWIdleThrd->m_iWorkThrdObjRef++;
			}

			
			virtual ~WIdleThrdEle()
			{
				if(1)
				{
					WCrsc aaa ( &(m_pWIdleThrd->m_crWorkThrdObjRefLck) );

					m_pWIdleThrd->m_iWorkThrdObjRef--;
				}

				TH_T::tr_destruct();
			}
		};

public:
	
	WIdleThrd()
	{
		m_iWorkThrdObjRef = 0;
		m_iWorkThrdWaitingRunfuncRef = 0;
		m_iWorkThrdRunRef = 0;

		m_isLive = 1;
	}

	
	virtual ~WIdleThrd()
	{
		m_isLive = 0;

		while( GetTasksSize() )
		{
			WThrd::tr_sleep(1);
		}
		while( m_iWorkThrdObjRef > 0 )
		{
			WThrd::tr_sleep(1);
		}
	}

public:
	
	void PostTask( const TASK_T & t, tbool biWithWait = 1, tbool biContribute = 1 )
	{
		if( !m_isLive ) return;

		
		if( biWithWait )
		{
			if   ( m_iWorkThrdObjRef              > 9 ) WThrd::tr_sleep( 0, 0.51 );
			while( m_iWorkThrdWaitingRunfuncRef   > 4 ) WThrd::tr_sleep( 0, 0.51 );
			while( m_iWorkThrdRunRef              > 7 ) WThrd::tr_sleep( 0, 0.51 );
		}
		else
		{
			if   ( m_iWorkThrdObjRef              > 800 )
				WThrd::tr_sleep( 0, 0.51 );

			while( m_iWorkThrdWaitingRunfuncRef   > 300 )
				WThrd::tr_sleep( 0, 0.51 );

			while( m_iWorkThrdRunRef              > 600 )
				WThrd::tr_sleep( 0, 0.51 );
		}

		if(1)
		{
			WCrsc aaa(&m_crTasksReadLck);

			if( OnBeforePushTask(t) )
			{
				m_vecTasks.push_back(t);
				
			}

			if( !m_vecTasks.empty() )
			{
				OnAfterPushTask( *m_vecTasks.rbegin() ) ;
			}

			
			if( biContribute )
			{
				if( m_iWorkThrdWaitingRunfuncRef < 2 ) 
				{
					WIdleThrdEle *p = new WIdleThrdEle(this);
					p->tr_openx();
				}
			}
		}

		return ;
	}

	
	void ContributeTask()
	{
		WCrsc aaa(m_crTasksReadLck);

		if( m_iWorkThrdWaitingRunfuncRef < 2 ) 
		{
			WIdleThrdEle *p = new WIdleThrdEle(this);
			p->tr_openx();
		}
	}


	tbool TakeTask( TASK_T & t )
	{
		WCrsc aaa(&m_crTasksReadLck);
		if( m_vecTasks.empty() ) return 0;
		t = m_vecTasks[0];
		m_vecTasks.erase( m_vecTasks.begin() );
		return 1;
	}

	
	tuint32 GetTasksSize()
	{
		WCrsc aaa(&m_crTasksReadLck);
		return  (tuint32)m_vecTasks.size();
	}

	
	void ClearTask()
	{
		WCrsc aaa(&m_crTasksReadLck);
		m_vecTasks.clear();
	}


	void WaitAllTaskDone()
	{
		while( m_iWorkThrdRunRef > 0 )
		{
			WThrd::tr_sleep(1);
		}
	}


	
	virtual tbool OnBeforePushTask( const TASK_T & t )
	{
		return 1;
	}

	
	virtual void OnAfterPushTask( TASK_T & t )
	{
		return;
	}


	virtual void OnRunTask( TASK_T t ) 
	=0;
	
	
};

#endif	








template < int INT_SEC_T >
class WCrsc2
{
public:
	enum base_son_type1_t    { BASE, SON };
	enum read_write_type2_t  { READ, WRITE };

private:
	WCrsc	   * m_p_base_csc_read;
	WCrsc	   * m_p_base_csc_write;
	WCrsc	   * m_pwrite;
	int          m_reader_ref;
	base_son_type1_t       m_type1;
	read_write_type2_t     m_type2;
	WCrsc2            * m_p_father;

	void InitVars()
	{
		m_p_base_csc_read = NULL;
		m_p_base_csc_write = NULL;
		m_pwrite = NULL;
		m_reader_ref = 0;
		m_type1 = BASE;
		m_type2 = READ;
		m_p_father = NULL;
	}

private:
	
	
	
	
	WCrsc2( WCrsc2 & aa )
	{
	}

public:
	WCrsc2()
	{
		InitVars();

		m_p_base_csc_read = new WCrsc;
		m_p_base_csc_write = new WCrsc;
		m_type1 = BASE;
	}

	WCrsc2( WCrsc2 * pfather, read_write_type2_t type2 = READ , double dSec = 0.10 )
	{
		InitVars();

		m_type1 = SON;
		m_type2 = type2;
		m_p_father = pfather;

		if( m_type2 == READ )
		{
			WCrsc big_csc( m_p_father->m_p_base_csc_write );
			WCrsc small_csc( m_p_father->m_p_base_csc_read );
			m_p_father->m_reader_ref ++;
		}

		if( m_type2 == WRITE )
		{
			m_pwrite = new WCrsc( m_p_father->m_p_base_csc_write );

			while( m_p_father->m_reader_ref != 0 )
			{
				WThrd::tr_sleep( INT_SEC_T , dSec );
			}
		}
	}


	virtual ~WCrsc2()
	{
		if( m_type1 == BASE )
		{
			delete m_p_base_csc_read;
			delete m_p_base_csc_write;
		}

		if( m_type1 == SON && m_type2 == READ )
		{
			WCrsc small_csc( m_p_father->m_p_base_csc_read );
			m_p_father->m_reader_ref --;
		}

		if( m_type1 == SON && m_type2 == WRITE )
		{
			delete m_pwrite;
			m_pwrite = NULL;
		}
	}

	
	WCrsc & operator = (const WCrsc & rhs)
	{
		
		return *this;
	}

};














X011_NAMESPACE_END

#endif







#ifndef X011__w_WSnd_H
#define X011__w_WSnd_H




#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>


#ifdef OS_MACOSX_

#else
#include <linux/soundcard.h>
#endif


X011_NAMESPACE_BEGIN





class WSndConv
{
public:
	
	enum WavStyle_t { R44100D16C2 };
public:
	virtual ~WSndConv() {;}

public:

	
	static tbool Conv( SCake & ckBufInOut, WavStyle_t eStyle = R44100D16C2 )
	{
		if( eStyle == R44100D16C2 && ckBufInOut.len() )
		{
			std::vector<tuint8> v1;

			v1.resize( 0x2c, 0 ); 


			
			
			
			
			v1.insert(v1.end(),   (tuint8*)ckBufInOut.buf(),   (tuint8*)ckBufInOut.buf() + ckBufInOut.len()   );


			*(char*)(&(v1[0])) = 'R';
			*(char*)(&(v1[1])) = 'I';
			*(char*)(&(v1[2])) = 'F';
			*(char*)(&(v1[3])) = 'F';
			*(tuint32*)(&(v1[4])) = (tuint32)v1.size() - 8; 
			
			

			*(char*)(&(v1[8])) = 'W';
			*(char*)(&(v1[9])) = 'A';
			*(char*)(&(v1[0x0a])) = 'V';
			*(char*)(&(v1[0x0b])) = 'E';
			*(char*)(&(v1[0x0c])) =  'f';
			*(char*)(&(v1[0x0d])) =  'm';
			*(char*)(&(v1[0x0e])) =  't';
			*(char*)(&(v1[0x0f])) = 0x20; 
			*(tuint32*)(&(v1[0x10])) = (tuint32)0x00000010; 
			
			

			*(tuint16*)(&(v1[0x14])) = (tuint16)0x0001; 
			

			*(tuint16*)(&(v1[0x16])) = (tuint16)0x0002; 
			

			*(tuint32*)(&(v1[0x18])) = (tuint32)0x0000ac44; 
			
			

			*(tuint32*)(&(v1[0x1c])) = (tuint32)0x0002b110; 
			
			

			*(tuint16*)(&(v1[0x20])) = (tuint16)0x04; 
			

			*(tuint16*)(&(v1[0x22])) = (tuint16)0x10; 
			

			*(char*)(&(v1[0x24])) = 'd';
			*(char*)(&(v1[0x25])) = 'a';
			*(char*)(&(v1[0x26])) = 't';
			*(char*)(&(v1[0x27])) = 'a';
			*(tuint32*)(&(v1[0x28])) = (tuint32)ckBufInOut.len();
			
			

			ckBufInOut.let( (tchar*)(&(v1[0])), (tuint32)v1.size() );

			return 1;
		}

		return 0;
	}
};




#ifdef OS_MACOSX_


#else


class WSnd : public WSndConv
{
public:

	struct RIFF_Header{
		char RIFF_ID[4];
		uint32_t RIFF_Size;
		char RIFF_Format[4];
	};

	struct Chunk_Header{
		char Chunk_ID[4];
		uint32_t Chunk_Size;
	};

	struct Wave_Format{
		uint16_t AudioFormat;
		uint16_t NumChannels;
		uint32_t SampleRate;
		uint32_t AvgBytesPerSec;
		uint16_t BlockAlign;
		uint16_t BitsPerSample;
	};

public:
	virtual ~WSnd() {;}

public:

	static void PlayWav( std::string strFile, tbool *pStop = NULL )
	{
		struct RIFF_Header riff_header;
		struct Chunk_Header fmt_chunk, data_chunk;
		struct Wave_Format wavfmt;

		char buf[512];

		FILE * fwave;
		int fwave_opened=0;
		int sndfd;
		int sndfd_opened=0;

		int status;
		int arg;
		int readbytes;
		int writebytes;
		int writed;

		fwave = fopen( strFile.c_str(), "r");
		if( fwave == NULL )
		{
			goto L_END;
		}
		fwave_opened = 1;

		fread(&riff_header, 1, sizeof(struct RIFF_Header), fwave);
		if( strncmp(riff_header.RIFF_ID, "RIFF", 4) || strncmp(riff_header.RIFF_Format, "WAVE",4))
		{
			goto L_END;
		}

		sndfd = open("/dev/dsp", O_RDWR);
		
		if (sndfd < 0)
		{
			goto L_END;
		}
		sndfd_opened = 1;

		fread(&fmt_chunk, 1, sizeof(struct Chunk_Header), fwave);
		if( !strncmp(fmt_chunk.Chunk_ID, "fmt ", 4) )
		{
			
			fread(&wavfmt, 1, sizeof(struct Wave_Format), fwave);

			arg = wavfmt.BitsPerSample;
			status = ioctl(sndfd, SOUND_PCM_WRITE_BITS, &arg);
			if (status == -1)
				perror("SOUND_PCM_WRITE_BITS ioctl failed");
			if (arg != wavfmt.BitsPerSample)
				perror("unable to set sample size");

			arg = wavfmt.NumChannels;
			status = ioctl(sndfd, SOUND_PCM_WRITE_CHANNELS, &arg);
			if (status == -1)
				perror("SOUND_PCM_WRITE_CHANNELS ioctl failed");
			if (arg != wavfmt.NumChannels)
				perror("unable to set number of channels");

			arg = wavfmt.SampleRate;
			status = ioctl(sndfd, SOUND_PCM_WRITE_RATE, &arg);
			if (status == -1)
				perror("SOUND_PCM_WRITE_WRITE ioctl failed");

			
			fseek(fwave, fmt_chunk.Chunk_Size - 16 + fmt_chunk.Chunk_Size%2, SEEK_CUR);
		}
		else
		{
			goto L_END;
		}

		while( fread(&data_chunk, 1, sizeof(struct Chunk_Header), fwave) != 0 )
		{
			if( pStop && *pStop )
			{
				goto L_END;
			}

			if( !strncmp(data_chunk.Chunk_ID, "data", 4) )
			{
				
				
				writed = 0;
				while(writed < data_chunk.Chunk_Size)
				{
					if( pStop && *pStop )
					{
						goto L_END;
					}

					readbytes = fread(buf, 1, 512, fwave);
					writebytes = write(sndfd, buf, readbytes);

					
					writed += readbytes;
				}
			}
			else
			{
				
				fseek(fwave, data_chunk.Chunk_Size + fmt_chunk.Chunk_Size%2, SEEK_CUR);
			}
		}

L_END:
		if(fwave_opened) fclose(fwave);
		if(sndfd_opened) close(sndfd);

		return;
	}

};




class WSndQue : public WSnd , public WIdleThrd < std::string >
{
public:
	WCrsc  m_WavLck;
	tbool  m_IsStopFlag;

public:
	WSndQue() { m_IsStopFlag = 0; }
	virtual ~WSndQue() {;}

public:
	
	void Play( std::string strFile )
	{
		StopPlay();
		m_IsStopFlag = 0;
		this->PostTask( strFile, 0, 1 );
	}

	
	void StopPlay()
	{
		m_IsStopFlag = 1;	
		WCrsc aa(&m_WavLck); 
	}

	
	virtual void OnRunTask( std::string t )
	{
		WCrsc aa(&m_WavLck);

		this->PlayWav( t, &m_IsStopFlag );
	}


};


#endif






X011_NAMESPACE_END

#endif







#ifndef X011__H_w_WMoonLog_h
#define X011__H_w_WMoonLog_h


X011_NAMESPACE_BEGIN


class WMoonLog
{
private:
	WCrsc       m_LogLck;

	std::string  m_strFnOld;	
	std::string  m_strFnNow;  

	std::string  m_strWorkPath;
	int          m_iRelativeDay;
	int          m_iLogCounter;

public:
	WMoonLog()
	{
		m_strWorkPath = "";
		m_iRelativeDay = 0;
		m_iLogCounter = 0;
	}

	virtual ~WMoonLog(){;}

private:

	
	void WashLogFile()  
	{
		SDte dtold;
		SDte dtnow;
		char szold[22];
		char sznow[22];

		if( m_iRelativeDay >= 0 ) return;

		dtold.MakeNow();
		dtold.RelativeDay( m_iRelativeDay ); 
		dtnow.MakeNow();

		(SClib::p_strcpy())( szold, dtold.ReadStringPack().c_str() );
		(SClib::p_strcpy())( sznow, dtnow.ReadStringPack().c_str() );

		szold[8] = 0;
		sznow[8] = 0;

		m_strFnOld = m_strWorkPath + "log" + std::string( szold + 3 ) + std::string(".txt");
		m_strFnNow = m_strWorkPath + "log" + std::string( sznow + 3 ) + std::string(".txt");

		SFile fl;

		fl.bind(m_strFnOld);
		fl.erase();
	}

	
	static std::string RefineStrVal( const std::string & s )
	{
		if( s.size() < 9 && wl::SStrf::sisdec( s.c_str() ) )
		{
			char ss[22];
			unsigned long ul;

			ul = wl::SStrf::satoul(s);
			(*wl::SClib::p_sprintf())( ss, "(0x%02X)", ul );
			return s + ss;
		}
		else
			return s;
	}

	
	void WriteStr( const std::string & s1 )
	{
		WCrsc aLock(&m_LogLck);

		if( m_iRelativeDay >= 0 ) return;

		if( m_iLogCounter++ >= 10000 ) 
		{
			m_iLogCounter=0;
			WashLogFile();
		}

		SFile fl;

		fl.bind(m_strFnNow);
		fl.write_str( s1 + "\r\n", 1 );
	}

	
	void GetTimeStr( std::string & s )
	{
		s = "." + wl::SStrf::sltoa(wl::SDte::Get_msec());
		s = wl::SDte::GetNow().ReadStringPack() + s;
	}

public:

	
	void InitLog( std::string strWorkPath, int iRelativeDay )
	{
		m_strWorkPath = SFile::MkDir2Path(strWorkPath);
		m_iRelativeDay = iRelativeDay;
		m_iLogCounter = 0;

		WashLogFile();

		std::string s1(88,'-');
		WriteStr( s1 );
	}

	
	template<class T>
	void WriteLog( T val1 )
	{	
		std::stringstream stream1;
		std::string strOut;
		stream1 << val1;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str());
		WriteStr(strOut);
	}

	template<class T1, class T2>
	void WriteLog( T1 val1, T2 val2 )
	{
		std::stringstream stream1, stream2;
		std::string strOut;
		stream1 << val1;
		stream2 << val2;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str()) + "\t" + RefineStrVal(stream2.str());
		WriteStr(strOut);
	}

	template<class T1, class T2, class T3>
	void WriteLog( T1 val1, T2 val2, T3 val3 )
	{
		std::stringstream stream1, stream2, stream3;
		std::string strOut;
		stream1 << val1;
		stream2 << val2;
		stream3 << val3;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str()) + "\t" + RefineStrVal(stream2.str()) + "\t" + RefineStrVal(stream3.str());
		WriteStr(strOut);
	}
};














class WDaydayLog
{
public:

	WCrsc		 m_LogLck;

	std::string  m_strWorkPath;
	std::string  m_strPrefix;  
	int          m_iLogNum;

	int          m_iRelativeDay;
	tbool		 m_biLogEnabled;

	std::string  m_strFnNow;  
	SDte	    m_dtBegin;


public:
	WDaydayLog()
	{
		m_iRelativeDay = -19;
		m_biLogEnabled = 1;
		m_iLogNum = 0;		
	}

	virtual ~WDaydayLog() {}


public:
	void WashLogFile() 		
	{
		SDte dtnow;
		char sznow[22];

		dtnow.MakeNow();

		
		if( dtnow.ReadStrPackDate() == m_dtBegin.ReadStrPackDate() )
		{}
		else
		{
			
			(*SClib::p_strcpy())( sznow, dtnow.ReadStringPack().c_str() );

			sznow[8] = 0;

			m_strFnNow = m_strWorkPath + "log" + m_strPrefix + std::string( sznow + 2 ) + std::string(".txt");

			SDte dtold;
			char szold[22];
			SFile fl;
			std::string  strFnOld;	

			dtold.MakeNow();
			dtold.RelativeDay( m_iRelativeDay );
			for( int i = 0; i < 22; i++ )
			{
				dtold.RelativeDay( -1 );
				(*SClib::p_strcpy())( szold, dtold.ReadStringPack().c_str() );
				szold[8] = 0;
				strFnOld = m_strWorkPath + "log" + m_strPrefix + std::string( szold + 2 ) + std::string(".txt"); 
				fl.bind(strFnOld);
				fl.erase();
			}

			m_dtBegin = dtnow;
		}
	}


	std::string RefineStrVal( const std::string & s )
	{
		if( s.size() < 9 && wl::SStrf::sisdec( s.c_str() ) )
		{
			char ss[22];
			unsigned long ul;

			ul = wl::SStrf::satoul(s);
			(*SClib::p_sprintf())( ss, "(0x%02X)", ul );
			return s + ss;
		}
		else
			return s;
	}


	void GetTimeStr( std::string & s )
	{
		char ss[22];
		(*SClib::p_sprintf())( ss, "%s.%03d", (SDte::GetNow().ReadStringPack().c_str() + 9), SDte::Get_msec() );
		ss[9] = 0;
		s = ss;
	}


	void WriteStr( std::string & s1 )
	{
		WashLogFile();

		SFile fl;

		fl.bind(m_strFnNow);
		fl.write_str( s1 + "\n", 1 );
	}


public:

	void InitLog( std::string strWorkPath, std::string strPrefix, int iLogNum )
	{
		if( strWorkPath.empty() )
			m_strWorkPath = "";
		else
			m_strWorkPath = SFile::MkDir2Path(strWorkPath);

		m_strPrefix = strPrefix;
		m_iLogNum = iLogNum;

		m_dtBegin = SDte("1970-1-1 00:00:00");
		WashLogFile();

		std::string s1(66,'-');

		s1 = SDte::GetNow().ReadStringPack() + s1;

		WriteStr( s1 );
	}


	virtual tbool OnBeforeWriteLog( std::string & strLogstr )
	{
		return 1;
	}


	template<class T>
	void WriteLog( T val1 )
	{
		if( !m_biLogEnabled ) return;

		std::stringstream stream1;
		std::string strOut;
		stream1 << val1;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str());

		if( !OnBeforeWriteLog(strOut) )
		{
			return;
		}

		WriteStr(strOut);
	}


	template<class T1, class T2>
	void WriteLog( T1 val1, T2 val2 )
	{
		if( !m_biLogEnabled ) return;

		std::stringstream stream1, stream2;
		std::string strOut;
		stream1 << val1;
		stream2 << val2;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str()) + "\t" + RefineStrVal(stream2.str());

		if( !OnBeforeWriteLog(strOut) )
		{
			return;
		}

		WriteStr(strOut);
	}


	template<class T1, class T2, class T3>
	void WriteLog( T1 val1, T2 val2, T3 val3 )
	{
		if( !m_biLogEnabled ) return;

		std::stringstream stream1, stream2, stream3;
		std::string strOut;
		stream1 << val1;
		stream2 << val2;
		stream3 << val3;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str()) + "\t" + RefineStrVal(stream2.str()) + "\t" + RefineStrVal(stream3.str());

		if( !OnBeforeWriteLog(strOut) )
		{
			return;
		}

		WriteStr(strOut);
	}

};









	
	

	

	




class WBoxLog_t
{
public:
	WCrsc		 m_LogLck;
	tbool		 m_biLogEnabled;

public:
	WBoxLog_t()
	{
		m_biLogEnabled = 1;
	}

	virtual ~WBoxLog_t() {}

public:
	void LogPrintf( int iSize, const char *szstring, ... )
	{
		va_list			args;
		std::string     StringBuffer;
		int				StringLength;

		if( szstring == NULL || *szstring == 0 ) return;
		if( !m_biLogEnabled ) return;
		if( iSize <= 0 ) return;

		StringBuffer.resize( iSize );

		va_start(args, szstring);
		StringLength = (*SClib::p_vsprintf())( &StringBuffer[0], szstring, args);
		va_end(args);

		WCrsc aLock( &m_LogLck );
		OnLogWrite( &StringBuffer[0] );
	}

	
	void LogPrintf( const char *szstring, ... )
	{
		va_list			args;
		std::string     StringBuffer;
		int				StringLength;
		int			iSize = 0;

		if( szstring == NULL || *szstring == 0 ) return;
		if( !m_biLogEnabled ) return;

		for( int i = 0; szstring[i]; i++ )
		{
			char c(szstring[i]);
			iSize++;
			if( c == '%' ) iSize += 9;
			if( c == 's' ) iSize += 90;
			if( c == ' ' ) iSize += 40;
		}

		if( iSize <= 0 ) return;

		StringBuffer.resize( iSize );

		va_start(args, szstring);
		StringLength = (*SClib::p_vsprintf())( &StringBuffer[0], szstring, args);
		va_end(args);

		WCrsc aLock( &m_LogLck );
		OnLogWrite( &StringBuffer[0] );
	}

	
	void LogPrintStr( const char *sz )
	{
		WCrsc aLock( &m_LogLck );
		OnLogWrite( sz );
	}

public:
	virtual void OnLogWrite( const char *sz )
	{
		printf( "%s\n", sz );
	}
};



class WFileBoxLog_t : public WBoxLog_t
{
private:

public:
	FILE * m_fp;

	std::string  m_strWorkPath;
	std::string  m_strPrefix;
	int          m_iDays;

public:
	WFileBoxLog_t()
	{
		m_fp = NULL;

		m_strWorkPath = "." + SFile::GetPathSep();
		m_strPrefix = "LOG";
		m_iDays = 9;
	}

	virtual ~WFileBoxLog_t()
	{
		if( m_fp != NULL )
		{
			fclose(m_fp); 
			m_fp = NULL;
		}
	}

public:
	tbool Open()
	{
		WCrsc aLock( &m_LogLck );
		std::string strFn;
		SDte	dtLast;
		SDte	dtNow;

		dtNow.MakeNow();
		dtLast.Make( "1970-1-1 0:0:0" );

		strFn.resize( 255 );
		(*SClib::p_sprintf())( &strFn[0], "%s%s%d.TXT", m_strWorkPath.c_str(), m_strPrefix.c_str(), dtNow.DiffDay(dtLast) % m_iDays );

		m_fp = (*SClib::p_fopen())("log.txt","ab");

		if( m_fp == NULL ) return 0;

		return 1;
	}

public:
	virtual void OnLogWrite( const char *sz )
	{
		printf( "%s\n", sz );
	}
};






template < int SEQLEN_T = 7 >		
class LOG4_t
{
private:
	int FILENUMBER_i ;
	int CAPACITY_KB_i;		

	WCrsc		 m_LogLck;
	std::string  m_strWorkPath;
	std::vector< std::pair< std::string, std::string  > > m_vProfile;

	
	void load_profile()
	{
		std::vector<std::string> vecSrcFileList;
		WFile wf;
		std::string s1,s2;

		m_vProfile.clear();
		wf.ListAllFile( m_strWorkPath, "*.*", vecSrcFileList, 0, 1, 0, 0 );
		if( vecSrcFileList.empty() ) return;
		for( int i = 0; i < (int)vecSrcFileList.size(); i++ )
		{
			s1 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 0 );
			s2 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 1 );
			s2 = SStrvs::vsa_get( s2, ".", 1, 0 );
			m_vProfile.push_back( std::pair< std::string, std::string  >(s1,s2) );
		}
		std::sort(m_vProfile.begin(), m_vProfile.end());
	}

	
	tbool numberX_reach()  
	{
		long k=0;

		if( (int)m_vProfile.size() > FILENUMBER_i )
		{
			
			return 1;
		}

		if( CAPACITY_KB_i > 0 )
		{
			for( int i = 0; i < (int)m_vProfile.size(); i++ )
			{
				std::string s1,s2;
				WFile wf;

				s1 = m_vProfile[i].first;
				s2 = m_vProfile[i].second;
				wf.bind( m_strWorkPath + s1 + "_" + s2 + ".txt" );
				k += (long)wf.len();
			}
			k /= 1000;

			if( k > CAPACITY_KB_i )
				return 1;
		}

		return 0;
	}

	
	std::string pack_date_str()
	{
		return on_get_pack_date_str();
	}

	
	virtual std::string on_get_pack_date_str()
	{
		return SDte::GetNow().ReadStrPackDate();
		
	}


	tbool day_change()
	{
		if( m_vProfile.empty() )
			return 1;

		if( m_vProfile.rbegin()->second != pack_date_str() )
			return 1;

		return 0;
	}

	
	void add_file()
	{
		std::string s1, s2;

		if( m_vProfile.empty() )
		{
			int i = SEQLEN_T;
			s1 = std::string(i,' ');
		}
		else
		{
			s1 = m_vProfile.rbegin()->first;
		}

		s1 = SStrf::seq( s1.c_str() );

		s2 = pack_date_str();

		m_vProfile.push_back( std::pair< std::string, std::string  >(s1,s2) );

		std::vector< std::pair< std::string, std::string  > > vPF2;

		vPF2 = m_vProfile;
		std::sort(vPF2.begin(), vPF2.end());

		if( m_vProfile.rbegin()->first < vPF2.rbegin()->first )
		{
			for( int i = 0; i < FILENUMBER_i; i++ )
			{
				Purge();
			}
		}
	}

	
	tbool get_small_probability()
	{
		if ( SStrf::rand1() < 0.003 ) return 1;
		return 0;
	}

	
	void Purge()
	{
		WFile wf;
		std::string s1, s2;

		if( m_vProfile.size() ==0 ) return;

		s1 = m_vProfile[0].first;
		s2 = m_vProfile[0].second;
		wf.bind( m_strWorkPath + s1 + "_" + s2 + ".txt" );
		if( !wf.erase() )
		{
			wf.bind( m_strWorkPath + s1 );
			wf.erase();
		}

		load_profile();
	}

public:

	
	tbool Init( std::string strBeginWorkPath , std::string strPrefixName , int filenumber_i = 9 , int capacity_kb_i = 0 )
	{
		FILENUMBER_i = filenumber_i;
		CAPACITY_KB_i = capacity_kb_i;

		WFile wf;

		m_strWorkPath = WFile::MkDir2Path( WFile::MkDir2Path( strBeginWorkPath ) + strPrefixName );
		wf.makedir(m_strWorkPath);
		load_profile();

		for( int i = 0; i < 5 && numberX_reach(); i++ )
		{

			Purge();
		}

		tbool rc;

		rc = day_change();

		if( rc )
			add_file();

		return 1;
	}

	
	void WriteStr( std::string s1 )
	{
		WFile fl;
		WCrsc aLock( &m_LogLck );

		if( m_vProfile.empty() )
			add_file();

		fl.bind( m_strWorkPath + m_vProfile.rbegin()->first + "_" + m_vProfile.rbegin()->second + ".txt" );
		fl.write_str( s1 + "\r\n", 1 );

		if( get_small_probability() && numberX_reach() )
				Purge();

		if( day_change() ||
			( get_small_probability() && get_small_probability() && numberX_reach() )	)
		{
			add_file();
		}
	}

};






template < int SEQLEN_T = 7 >	
class LOG5_t
{
private:
	int FILENUMBER_i ;
	int CAPACITY_KB_i;	

	WCrsc		 m_LogLck;
	std::string  m_strWorkPath;
	std::string  m_strDeviceName;
	std::vector< std::pair< std::string, std::string  > > m_vProfile;

	
	void load_profile()
	{
		std::vector<std::string> vecSrcFileList;
		WFile wf;
		std::string s1,s2,s3;

		m_vProfile.clear();
		wf.ListAllFile( m_strWorkPath, "*.*", vecSrcFileList, 0, 1, 0, 0 );
		if( vecSrcFileList.empty() ) return;
		for( int i = 0; i < (int)vecSrcFileList.size(); i++ )
		{
			s1 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 0 );
			s2 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 1 );
			s3 = SStrvs::vsa_get( vecSrcFileList[i], "_", 1, 2 );
			s2 = SStrvs::vsa_get( s3, ".", 1, 0 );
			m_vProfile.push_back( std::pair< std::string, std::string  >(s1,s2) );
		}
		std::sort(m_vProfile.begin(), m_vProfile.end());
	}

	
	tbool numberX_reach() 
	{
		long k=0;

		if( (int)m_vProfile.size() > FILENUMBER_i )
		{
			
			return 1;
		}

		if( CAPACITY_KB_i > 0 )
		{
			for( int i = 0; i < (int)m_vProfile.size(); i++ )
			{
				std::string s1,s2;
				WFile wf;

				s1 = m_vProfile[i].first;
				s2 = m_vProfile[i].second;
				
				wf.bind( get_PFn( s1, s2 ) );
				k += (long)wf.len();

				
			}
			k /= 1000;

			if( k > CAPACITY_KB_i )
				return 1;
		}

		return 0;
	}


	std::string pack_date_str()
	{
		return on_get_pack_date_str();
	}

	
	virtual std::string on_get_pack_date_str()
	{
		return SDte::GetNow().ReadStrPackDate();
		
	}


	tbool day_change()
	{
		if( m_vProfile.empty() )
			return 1;

		if( m_vProfile.rbegin()->second != pack_date_str() )
			return 1;

		return 0;
	}


	std::string get_PFn( std::string s1Num, std::string s2Dte )
	{
		return m_strWorkPath + s1Num + "_" + s2Dte + "_" + m_strDeviceName + ".txt";
	}




	
	void add_file()
	{

		std::string s1, s2;


		if( m_vProfile.empty() )
		{

			int i = SEQLEN_T;
			s1 = std::string(i,' ');
		}
		else
		{

			s1 = m_vProfile.rbegin()->first;
		}


		s1 = SStrf::seq( s1.c_str() );
	

		s2 = pack_date_str();

		m_vProfile.push_back( std::pair< std::string, std::string  >(s1,s2) );

		std::vector< std::pair< std::string, std::string  > > vPF2;


		vPF2 = m_vProfile;
		std::sort(vPF2.begin(), vPF2.end());


		if( m_vProfile.rbegin()->first < vPF2.rbegin()->first )
		{

			for( int i = 0; i < FILENUMBER_i; i++ )
			{

				Purge();
			}

		}

	}

	
	tbool get_small_probability()
	{
		if ( SStrf::rand1() < 0.003 ) return 1;
		return 0;
	}

	
	void Purge()
	{
		WFile wf;
		std::string s1, s2;

		if( m_vProfile.size() ==0 ) return;

		s1 = m_vProfile[0].first;
		s2 = m_vProfile[0].second;
		
		wf.bind( get_PFn( s1, s2 ) );

		if( !wf.erase() )
		{
			wf.bind( m_strWorkPath + s1 );
			wf.erase();
		}

		load_profile();
	}

public:
	
	virtual ~LOG5_t()
	{
	}

	
	tbool Init( std::string strBeginWorkPath , std::string strPrefixName , int filenumber_i = 9 , int capacity_kb_i = 0 )
	{
		FILENUMBER_i = filenumber_i;
		CAPACITY_KB_i = capacity_kb_i;

	
		WFile wf;

		m_strWorkPath = WFile::MkDir2Path( strBeginWorkPath );
		m_strWorkPath = WFile::MkDir2Path( m_strWorkPath + strPrefixName );
		m_strDeviceName = strPrefixName;
		wf.makedir(m_strWorkPath);
		load_profile();

	
	

		for( int i = 0; i < 5 && numberX_reach(); i++ )
		{

			Purge();
		}


		tbool rc;

		rc = day_change();
	

		if( rc )
			add_file();


		return 1;
	}


	void WriteStr( std::string s1 )
	{
		WFile fl;
		WCrsc aLock( &m_LogLck );

		if( m_vProfile.empty() )
			add_file();

		
		fl.bind( get_PFn( m_vProfile.rbegin()->first,  m_vProfile.rbegin()->second ) );

		fl.write_str( s1 + "\r\n", 1 );

		if( get_small_probability() && numberX_reach() )
				Purge();

		if( day_change() ||
			( get_small_probability() && get_small_probability() && numberX_reach() )	)
		{
			add_file();
		}
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_WTcpDisConnable_h
#define X011__H_w_WTcpDisConnable_h


X011_NAMESPACE_BEGIN


class WTcpDisConnable : public IRice
{

private:

	WTcpDisConnable & operator = (const WTcpDisConnable & rhs)
	{
		return *this;
	}

	WTcpDisConnable(const WTcpDisConnable & rhs)
	{;}


public:
	class MyTimeKiller : public WThrd
	{
	public:
		WTcpDisConnable * m_ph;
		volatile int  m_iSec100Limit;
		volatile int  m_iSec100;

		MyTimeKiller( WTcpDisConnable * ph, int iSec100Limit )
		{
			m_ph = ph;
			m_iSec100Limit = iSec100Limit;
			m_iSec100 = 0;
		}

		virtual ~MyTimeKiller()
		{
			m_iSec100 = 0;
			tr_shouldbrk();

			
			
			tr_wait();	
		}


		virtual int tr_on_user_run()
		{
			double dIStep = 0.1;

			if( m_iSec100 < m_iSec100Limit )
			{
				WThrd::tr_sleep( 0, dIStep );
				m_iSec100 ++;
				if( this->tr_isShouldBrk() ) return 0;
				return 1;
			}

			if( this->tr_isShouldBrk() ) return 0;

			if(m_ph)
			{
				m_ph->m_biKillFlag = 1;
				m_ph->DisConnNOclear();
			}

			return 0;
		}
	};

public:
	MyTimeKiller *  m_pkiller;
	tbool			m_biKillFlag;
	WTcpDisConnable * m_pBrother;
	WCrsc           m_killerLock;

public:

	void killer_up( double iMaxSec )
	{
		killer_dn() ;

		if(1)
		{
			WCrsc  aaa( &m_killerLock );

			m_pkiller = new MyTimeKiller( this, (int)(iMaxSec * 10) );
			m_pkiller->tr_open();
		}
	}


	void killer_setbegin()
	{
		WCrsc  aaa( &m_killerLock );

		if( m_pkiller != NULL )
		{
			m_pkiller->m_iSec100 = 0;
		}
	}


	void killer_dn()
	{
		if(1)
		{
			WCrsc  aaa( &m_killerLock );

			if( m_pkiller != NULL )
				m_pkiller->tr_shouldbrk();
		}

		while(1)
		{
			int isLive=0;
			if(1)
			{
				WCrsc  aaa( &m_killerLock );

				if( m_pkiller != NULL )
					isLive = m_pkiller->tr_isRunning();
			}
			if(isLive) WThrd::tr_sleep( 0, 0.5 );
			else break;
		}

		if(1)
		{
			WCrsc  aaa( &m_killerLock );

			if( m_pkiller != NULL )
			{
				delete m_pkiller;  
				m_pkiller = NULL;
			}
		}
	}

public:

	WTcpDisConnable()
	{
		m_pkiller = NULL;
		m_biKillFlag = 0;
		m_pBrother = NULL;
	}

	virtual ~WTcpDisConnable()
	{
		killer_dn() ;
	}


	virtual void DisConn()  
	{
			ClearL2Cache();

		OnDisConn();
	}

	
	virtual void DisConnNOclear()
	{
		OnDisConn();
	}


public:

	virtual void OnDisConn() { ; } 

	virtual void on_send_recv_kick()
	{
		killer_setbegin();
		if( m_pBrother ) m_pBrother->killer_setbegin();
	}

}; 



X011_NAMESPACE_END

#endif







#ifndef X011__H_w_wtcp_cell_h
#define X011__H_w_wtcp_cell_h


X011_NAMESPACE_BEGIN


class WTcpCell : public WTcpDisConnable
{

protected:

	SOCKET			m_socRemote;


private:

	WTcpCell & operator = (const WTcpCell & rhs)
	{
		return *this;
	}

	WTcpCell(const WTcpCell & rhs)
	{;}


public:

	WTcpCell()
	{
		m_socRemote = INVALID_SOCKET;

	}

	virtual ~WTcpCell()
	{
		DisConn();
	}


public:

	SOCKET GetRemoteSoc() const
	{
		return m_socRemote;
	}

	void AttachSoc(SOCKET ss)
	{
		m_socRemote = ss;
	}


	static std::string getselfname()
	{
		tchar ss[1024] = {0};
		gethostname(ss,1024);  
		return ss;
	}


	static std::string getipbyname( std::string name )
	{
		hostent * host;
		std::vector<std::string> vecNameParts;

		wl::SStrvs::vsa_imp( name, std::string("."), 1, vecNameParts );
		if( vecNameParts.size()==4 &&
			SStrf::sisdec(vecNameParts[0].c_str()) &&
			SStrf::sisdec(vecNameParts[1].c_str()) &&
			SStrf::sisdec(vecNameParts[2].c_str()) &&
			SStrf::sisdec(vecNameParts[3].c_str())		)
			return name;

		if( name.size() == 0 )
			name = getselfname();

		host = gethostbyname(name.c_str());

		if(host==NULL)
			return "";

		if( host->h_addr_list[0] )
		{
			struct in_addr addr;
			memmove( &addr, host->h_addr_list[0], 4 );
			return inet_ntoa(addr);
		}

		return "";
	}


	static std::string getnamebyip( std::string strIP )
	{
		DWORD dwIPAddr;
		dwIPAddr = inet_addr(strIP.c_str());
		if(dwIPAddr == INADDR_NONE)
		{
			return "";
		}
		else
		{
			hostent * p=gethostbyaddr( (const char *)&dwIPAddr, 4, PF_INET ); 
			if(!p)
			{
				return "";
			}
			else
			{
				return p->h_name;
			}
		}
	}

	
	static std::string get_machineIP()
	{
		return getipbyname( getselfname() );
	}

	
	static unsigned char * Ipstr2Ipbyte( std::string strIp, unsigned char *pOut )
	{
		std::vector<std::string> v1;

		SStrvs::vsa_imp( strIp, std::string("."), 1, v1 );

		for( int i = 0; i < (int)v1.size(); i ++ )
		{
			std::string str1 = v1[i];

			pOut[i] =  (tuint8)SStrf::satol(str1);
		}

		return pOut;
	}

	
	static std::string Ipbyte2Ipstr( unsigned char *pIn )
	{
		std::string str1;

		for( int i = 0; i < 4; i ++ )
		{
			str1 += SStrf::sltoa(pIn[i]);
			str1 += ".";
		}
		str1.erase( str1.end() - 1 );

		return str1;
	}

public:

	virtual void OnDisConn()
	{
		if( m_socRemote == INVALID_SOCKET ) return;

		try
		{
			shutdown( m_socRemote, 2 );
			closesocket(m_socRemote);
			m_socRemote = INVALID_SOCKET ;
		}
		catch(...)
		{
			m_socRemote = INVALID_SOCKET;
		}
	}


public:

	virtual int on_get_defaultrecv_buf_len() 
	{
		return 256;
	}

	virtual int on_sys_recv( SCake & ckDataBuf ) 
	{
		int iDefaultBufLen = on_get_defaultrecv_buf_len();
		ckDataBuf.redim( iDefaultBufLen );

		int i;
		SOCKET s = m_socRemote;

		if(s==INVALID_SOCKET)
		{
			return 0;
		}

		i = (int)::recv(s, ckDataBuf.buf(), (int)ckDataBuf.len(), 0);
		if(i==SOCKET_ERROR||i==0)
		{
			return i = 0;
		}

		ckDataBuf.cut( iDefaultBufLen-i );

		return i;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		int i;
		SOCKET s = m_socRemote;
		if(s==INVALID_SOCKET) return 0; 

		if( ckDataBuf.len() == 0 || !ckDataBuf.buf_const() ) return 0;

		i = (int)::send(s, ckDataBuf, (int)ckDataBuf.len(), 0);
		

		if(i==SOCKET_ERROR)
			i = 0;

		return i;
	}


}; 



X011_NAMESPACE_END

#endif







#ifndef X011__H_w_wtcp_cellc_h
#define X011__H_w_wtcp_cellc_h


X011_NAMESPACE_BEGIN


class WTcpCellc : public WTcpCell
{

private:

	WTcpCellc & operator = (const WTcpCellc & rhs)
	{
		return *this;
	}

	WTcpCellc(const WTcpCellc & rhs)
	{;}


public:


	WTcpCellc()
	{
	}


	virtual ~WTcpCellc()
	{
	}


	tbool Conn_udp( std::string name, u_short port )
	{
		struct	sockaddr_in		saddr ;

		m_socRemote = socket(AF_INET, SOCK_DGRAM, 0);

		if( m_socRemote == INVALID_SOCKET)
		{
			return 0;
		}

		
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET;
		saddr.sin_port = htons( (u_short)port );
		
		saddr.sin_addr.s_addr = inet_addr( getipbyname(name).c_str() );

		if( 0 != ::connect( m_socRemote, (struct sockaddr *)&saddr, sizeof(saddr) )  )
		{
			return 0;
		}

		return 1;
	}

	
	int send_udp( void *pdata, int ilen )
	{
		return send( m_socRemote, (const char *)pdata, ilen, 0 );
	}

	
	int send_udp( const SCake & ck )
	{
		if( ck.len() == 0 ) return 0;
		return send_udp( (void*)ck.buf_const(), (int)ck.len() );
	}

	
	int recv_udp( char *buf, int ilen )
	{
        return recv( m_socRemote, buf, ilen, 0 );
	}

	
	int recv_udp( SCake & ck )
	{
		if( ck.len() == 0 ) return 0;
		return recv_udp( ck.buf(), (int)ck.len() );
	}



	tbool Conn( std::string name, u_short port )
	{
		struct	sockaddr_in		saddr ;

		DisConn();

		m_socRemote = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socRemote == INVALID_SOCKET )
		{
			return 0;
		}

		
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET;
			
			saddr.sin_addr.s_addr = inet_addr( getipbyname(name).c_str() );
		saddr.sin_port = htons( (u_short)port );

		if(SOCKET_ERROR == ::connect( m_socRemote, (struct sockaddr *)&saddr, sizeof(saddr) )  )
		{
			return 0;
		}

		return 1;
	}



	tbool Conn( std::string name, std::string port )
	{
		return this->Conn( name, static_cast<u_short>(SStrf::satol(port.c_str()) ) );
	}



	tbool Conn( std::string strAddrLst ) 
	{
		std::vector<std::string> vecAddr1;

		SStrvs::vsa_imp( strAddrLst, std::string("|"), 1, vecAddr1 );

		for( int i = 0; i < (int)vecAddr1.size(); i ++ )
		{
			std::string strAddr = vecAddr1[i];

			try
			{
				std::vector<std::string> vecNameParts;
				SStrvs::vsa_imp( strAddr, std::string(":"), 1, vecNameParts );
				vecNameParts.push_back( std::string("") );
				vecNameParts.push_back( std::string("") );
				if( this->Conn( vecNameParts[0], vecNameParts[1] ) ) return 1;
			}
			catch(...)
			{
				
				return 0;
			}
		}

		return 0;
	}


}; 








class WTcpFtp : public WTcpCellc
{
private:

	WTcpFtp & operator = (const WTcpFtp & rhs)
	{
		return *this;
	}

	WTcpFtp(const WTcpFtp & rhs)
	{;}

public:

	WTcpFtp()
	{
	}

	virtual ~WTcpFtp()
	{
	}

public:

	
	std::string read_welcome_msg()
	{
		std::string str1;
		SCake ck;

		do{
			this->recv_ln( ck, "\n" );
			if( ck.len() == 0 ) return "";
			str1 = ck.mk_str();
			if( str1.size() < 3 ) return "";
			if( str1.size() == 3 ) return str1;
			if( str1.size() > 3 && str1[3] != '-' ) return str1;
		}while( str1.size() >= 4 && str1[3] == '-' );

		return "";
	}

	
	tbool FtpLogin( std::string strUser, std::string strPass )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;

		
		
		
		
		
		str1 = read_welcome_msg();


		iRc = this->send_str( "user " + strUser + "\r\n" );
		if( !iRc ) return 0;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 331 ) return 0;

		
		iRc = this->send_str( "pass " + strPass + "\r\n" );
		if( !iRc ) return 0;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 230 ) return 0;

		
		iRc = this->send_str( "type i\r\n" );
		if( !iRc ) return 0;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		return 1;
	}

	
	std::string FtpPwd() 
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;

		
		iRc = this->send_str( "pwd\r\n" );
		if( !iRc ) return "";
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 257 ) return "";
		return str1;
	}

	
	tbool FtpCwd( std::string t ) 
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;

		
		iRc = this->send_str( "cwd " + t + "\r\n" );
		if( !iRc ) return 0;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;
		return 1;
	}

	
	std::string FtpPasv() 
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		std::vector<std::string> vec1;
		long lport;

		
		iRc = this->send_str( "pasv\r\n" );
		if( !iRc ) return "";
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 227 ) return "";

		SStrvs::vsa_imp( str1, std::string("("), 1, vec1 );
		if( vec1.size() < 2 ) return "";

		str1 = vec1[1];
		vec1.clear();

		SStrvs::vsa_imp( str1, std::string(","), 1, vec1 );
		if( vec1.size() < 6 ) return "";
		lport = SStrf::satol(vec1[4]) * 256 + SStrf::satol(vec1[5]);
		str1 = vec1[0] + "." + vec1[1] + "." + vec1[2] + "." + vec1[3] + ":" + SStrf::sltoa(lport);

		return str1;
	}

	
	std::string FtpList()
	{
		std::string str1;
		std::string strRtn;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc c;

		
		str1 = this->FtpPasv();
		if( str1.empty() ) return "";
		if( !c.Conn(str1) ) return "";

		iRc = this->send_str( "list\r\n" );
		if( !iRc ) return "";

		c.recv_all( ck );
		if( ck.len() == 0 ) return "";
		strRtn = ck.mk_str();

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return "";

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return "";

		return strRtn;
	}


	tbool FtpStor( std::string strFn, const SCake & ckData, WTcpCellc *pc = NULL )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc cc;

		if( ckData.len() == 0 ) return 0;

		if( pc == NULL ) pc = &cc;

		
		str1 = this->FtpPasv();
		if( str1.empty() ) return 0;

		if( !pc->Conn(str1) ) return 0;

		iRc = this->send_str( "stor " + strFn + "\r\n" );
		if( !iRc )
		{
			pc->DisConn();
			return 0;
		}

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 )
		{
			pc->DisConn();
			return 0;
		}

		pc->send_bin( ckData );

		pc->DisConn();

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		return 1;
	}


	
	tbool FtpStor_begin( std::string strFn, WTcpCellc &cc )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc *pc;

		pc = &cc;

		
		str1 = this->FtpPasv();
		if( str1.empty() ) return 0;

		if( !pc->Conn(str1) ) return 0;

		iRc = this->send_str( "stor " + strFn + "\r\n" );
		if( !iRc )
		{
			pc->DisConn();
			return 0;
		}

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 )
		{
			pc->DisConn();
			return 0;
		}

		return 1;
	}

	
	tbool FtpStor_mid( const SCake & ckData, WTcpCellc &cc )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc *pc;

		if( ckData.len() == 0 ) return 0;

		pc = &cc;

		pc->send_bin( ckData );

		return 1;
	}


	tbool FtpStor_end( WTcpCellc &cc )
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc *pc;

		pc = &cc;

		pc->DisConn();

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		return 1;
	}



	
	tbool FtpRetr( std::string strFn, SCake & ckData, WTcpCellc *pc = NULL )
	{
		std::string str1;
		std::string strRtn;
		SCake ck;
		tbool iRc = 0;
		WTcpCellc cc;

		if( pc == NULL ) pc = &cc;

		
		str1 = this->FtpPasv();
		if( str1.empty() ) return 0;

		if( !pc->Conn(str1) ) return 0;

		iRc = this->send_str( "retr " + strFn + "\r\n" );
		if( !iRc )
		{
			pc->DisConn();
			return 0;
		}

		pc->recv_all_f( ckData );
		if( ckData.len() == 0 )
		{
			pc->DisConn();
			return 0;
		}

		pc->DisConn();

		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) == 0 ) return 0;

		return 1;
	}


	tbool FtpBye()
	{
		std::string str1;
		SCake ck;
		tbool iRc = 0;

		
		iRc = this->send_str( "quit\r\n" );
		if( !iRc ) return 1;
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 221 ) return 1; 
		return 1;
	}
};





class WDte : public SDte
{
private:

	typedef struct
	{
		tint32 L1;
		tint32 Version;
		tint32 mode;
		char stratum;
		char poll;
		char precision;
		tuint32 root_delay;
		tuint32 root_dispersion;
		tuint32 reference_identifier;
		tint64 reference_timestamp;
		tint64 originate_timestamp;
		tint64 receive_timestamp;
		tint64 transmit_timestamp;
	}	ntp;

	tuint32  TIMEDIFF; 
	tuint32  NTP_HEAD_LEN ; 

	void pack_ntp_data(char *buf, ntp const *ntp_packet)
	{
		memset(buf, 0x00, NTP_HEAD_LEN);

		buf[0] = (char) ( (ntp_packet->L1<<6) | (ntp_packet->Version<<3) | (ntp_packet->mode) );
		buf[1] = ntp_packet->stratum;
		buf[2] = ntp_packet->poll;
		buf[3] = ntp_packet->precision;
		memcpy(buf + 4, &ntp_packet->root_delay, 2);
		
		memcpy(buf + 40, &ntp_packet->transmit_timestamp, 4);
	}

	void unpack_ntp_data(char *data)
	{
		tint64 transmit_time;

		memcpy(&transmit_time, data + 32, 4);
		transmit_time = ntohl((tsize)transmit_time) - TIMEDIFF;
		
		
		
		
		
		
		
		this->Make("1970-1-1 0:0:0");
		this->RelativeSec( (int)transmit_time );
		this->RelativeSec( 8 * 60 * 60 );
	}

public:

public:

	WDte()
	{
		TIMEDIFF = 0x83aa7e80;
		NTP_HEAD_LEN = 48;
	}

	virtual ~WDte() { ; }

	tbool NtpMakeCnTimeNow( std::string strServer , int iPort = 123, int iTimeOutSec = 15 ) 
	{
		WTcpCellc  cc;
		tbool iRc = 0;
		int iRtn;
		ntp ntp_packet;
		char *buf;
		SCake buf2;

		buf2.redim(NTP_HEAD_LEN);
		buf = buf2.buf();

		iRc = cc.Conn_udp( strServer, (u_short)iPort );
		if( !iRc ) return 0;

		ntp_packet.L1 = 0;
		ntp_packet.Version = 3;
		ntp_packet.mode = 3;
		ntp_packet.stratum = 0;
		ntp_packet.poll = 5;
		ntp_packet.root_delay = 0;
		ntp_packet.precision = (char)(-6);
		ntp_packet.transmit_timestamp = 0;

		pack_ntp_data(buf, &ntp_packet);

		if( iTimeOutSec > 0 ) cc.killer_up( iTimeOutSec );
		

		iRtn = cc.send_udp( buf, NTP_HEAD_LEN );
		if ( iRtn != NTP_HEAD_LEN ) return 0;

		iRtn = cc.recv_udp( buf, NTP_HEAD_LEN );

		if( iTimeOutSec > 0 ) cc.killer_dn();

		if( iRtn == NTP_HEAD_LEN )
		{
			unpack_ntp_data(buf);
			return 1;
		}

		return 0;
	}

	tbool NtpMakeCnTimeNow()
	{
		if( NtpMakeCnTimeNow("0.cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("0.tw.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("1.cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("1.tw.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("2.cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("2.tw.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("3.cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("3.tw.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("cn.pool.ntp.org") ) return 1;
		if( NtpMakeCnTimeNow("tw.pool.ntp.org") ) return 1;
		return 0;
	}

};




class WTftp
{
public:

	WTftp()
	{
	}

	virtual ~WTftp() { ; }

public:

	
	tbool TFtpGet2( std::string strServerIp, int iPort, std::string strFn, SCake & ckData )
	{
		WTcpCellc  cc;
		tbool iRc;
		int iRtn;
		char *buf;
		SCake buf2;
		int buflen;


		buf2.redim(555);
		buf = buf2.buf();

		iRc = cc.Conn_udp( strServerIp, (u_short)iPort );
		if( !iRc ) return 0;

		buflen = (*SClib::p_sprintf())( buf, "%c%c%s%c%s%c", 0, 1, strFn.c_str(), 0, "octet", 0 );
		iRtn = cc.send_udp( buf, buflen );
		if ( iRtn != buflen ) return 0;


		char command;
		char serial = 0;

		ckData.redim(0);

		do{
			buflen = cc.recv_udp( buf,516 ); 	

			if(buflen == -1)
			{
				break;
			}

			command = buf[1];
			if(command == 3)
			{
				if(serial < buf[3])
				{
					serial = buf[3];
					ckData.append(buf+4,buflen-4);
				}
				buf[1] = 4;
				cc.send_udp( buf, 4 ); 
			}
			else if(command == 5)
			{
				break;
			}

		}while(buflen == 516);

		return 1;
	}


	tbool TFtpGet( std::string strServerIp, int iPort, std::string strFn, SCake & ckData, int iTimeOutSec = 15 )
	{
		WTcpCellc  cc;
		FILE * fp = NULL;
		unsigned short p_num = 0;
		char buf[516] = "";
		volatile unsigned char cmd = 0;
		volatile unsigned int len = 0;
		struct sockaddr_in addr;
		struct sockaddr_in cliaddr;
		int addrlen = sizeof(addr);
		SOCKET udpfd;

		len = (*SClib::p_sprintf())(buf,"%c%c%s%c%s%c", 0, 1, strFn.c_str(), 0, "octet", 0);    

		addr.sin_family = AF_INET;
		addr.sin_port = htons( (u_short)iPort );
		addr.sin_addr.s_addr = inet_addr( WTcpCell::getipbyname(strServerIp).c_str() );


		if( (udpfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 )
		{
			return 0;
		}

		cc.AttachSoc(udpfd);

		sendto(udpfd, buf, len, 0, (struct sockaddr *)&addr, sizeof(addr));

		if( iTimeOutSec > 0 ) cc.killer_up( iTimeOutSec );

		do{
			if( iTimeOutSec > 0 ) cc.killer_setbegin();

			
			len = recvfrom(udpfd, buf, sizeof(buf), 0, (struct sockaddr*)&cliaddr, (socklen_t*)&addrlen);
			cmd = buf[1];
			

			if( cmd == 3 )    
			{
				
				if( p_num < ntohs(*(unsigned short*)(buf+2) ))
				{
					ckData.append(buf+4,len-4);	
					p_num = ntohs(*(unsigned short*)(buf+2));
					
				}
				buf[1] = 4;
				sendto(udpfd, buf, 4, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
			}
			else if( cmd == 6 ) 
			{
				 buf[0] = 0; buf[1] = 4; buf[2] = 0; buf[3] = 0;
				 sendto(udpfd, buf, 4, 0, (struct sockaddr*)&cliaddr, sizeof(cliaddr));
				 continue;
			}
			else if( cmd==5 ) 
			{
				
				closesocket(udpfd);
				return 0;
			}
		}while((len == 516)||(cmd == 6)); 

		if( iTimeOutSec > 0 ) cc.killer_dn();

		closesocket(udpfd);

		if( ckData.len() == 0 ) return 0;

		return 1;
	}

};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_WTcpListener_h
#define X011__H_w_WTcpListener_h


X011_NAMESPACE_BEGIN


class WTcpListener
{

private:

	SOCKET	m_socLocalListener;
	

private:

	WTcpListener & operator = (const WTcpListener & rhs)
	{
		return *this;
	}

	WTcpListener(const WTcpListener & rhs)
	{;}


public:

	u_short		m_port;

	u_long		m_u_in_addr;


	WTcpListener( )
	{
		m_socLocalListener = INVALID_SOCKET;
		
		m_port = 0;
	}

	virtual ~WTcpListener( )
	{
		this->StopListen();
	}


	
	


	tbool Listen( u_short port,  u_long a_in_addrip = INADDR_ANY, int listener_num = 4 )
	{
		struct	sockaddr_in	 saddr;

		m_port = port;
		m_u_in_addr = a_in_addrip;

		if ( 0 == port )
		{
			
		}

		m_socLocalListener = socket( AF_INET, SOCK_STREAM, IPPROTO_TCP );

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		
		int on;
		on = 1;
		setsockopt( m_socLocalListener, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on) );

		
		SStrf::smemset( (void*)&saddr, 0, sizeof(saddr) );

		saddr.sin_family = AF_INET;
		saddr.sin_port = htons( (u_short)port );
		
		saddr.sin_addr.s_addr = a_in_addrip;

		if( SOCKET_ERROR == bind( m_socLocalListener, (struct sockaddr *)&saddr, sizeof(saddr) ))
		{
			this->StopListen();
			
			return 0;
		}

		if( 0 == ::listen( m_socLocalListener, listener_num ) )
		{
			return 1;
		}
		else
		{
			
			return 0;
		}
	}


	tbool Listen( u_short uport, const tchar * sz_addrip ) 
	{
		if( sz_addrip && *sz_addrip )
		{
			return this->Listen( uport, inet_addr( sz_addrip ) ) ;
		}

		return this->Listen( uport );
	}


	tbool Listen( std::string strport, const tchar * sz_addrip )
	{
		return this->Listen( (u_short)SStrf::satol(strport) , sz_addrip );
	}


	tbool Listen( std::string straddr ) 
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( straddr, std::string(":"), 1, vecNameParts );
			if( vecNameParts.size() == 1 )
			{
				vecNameParts.insert( vecNameParts.begin(), std::string("") );
			}

			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return Listen( vecNameParts[1], vecNameParts[0].c_str() );
		}
		catch(...)
		{
			return 0;
		}
	}


	void StopListen(void)
	{
		if( m_socLocalListener != INVALID_SOCKET )
		{
			closesocket( m_socLocalListener );
			m_socLocalListener = INVALID_SOCKET;
		}
	}


	tbool AcceptNewSvr( SOCKET & socNewSvr, std::string & strRtnRemoteIP )
	{
		struct	sockaddr_in	 from;
		socklen_t  nSize;

		if( m_socLocalListener == INVALID_SOCKET )
		{
			return 0;
		}

		nSize= sizeof(from);
		socNewSvr = ::accept( m_socLocalListener, (struct sockaddr *)&from, &nSize ); 
		if( socNewSvr == INVALID_SOCKET )
		{
			strRtnRemoteIP = "";
			return 0;
		}
		else
		{
			strRtnRemoteIP = inet_ntoa( from.sin_addr ) ; 
			return 1;
		}
	}


}; 



X011_NAMESPACE_END

#endif






#ifndef X011__H_w_wtcp_cells_h
#define X011__H_w_wtcp_cells_h


X011_NAMESPACE_BEGIN


class WTcpCells : public WTcpCell
{

public:

	std::string m_strRemoteIPAddress;


private:

	WTcpCells & operator = (const WTcpCells & rhs)
	{
		return *this;
	}

	WTcpCells(const WTcpCells & rhs)
	{;}


public:

	WTcpCells()
	{
		m_strRemoteIPAddress="";
	}


	virtual ~WTcpCells()
	{	m_strRemoteIPAddress="";
	}


	operator const std::string & () const
	{
		return m_strRemoteIPAddress;
	}


	std::string GetRemoteIPAddress() const
	{
		return m_strRemoteIPAddress;
	}


	tbool Conn( WTcpListener & aListener)
	{
		int iRc;

		iRc = aListener.AcceptNewSvr( m_socRemote , m_strRemoteIPAddress );

		if(!iRc) return 0;

		
		return 1;
	}


	tbool Conn( WTcpListener * pListener)
	{
		if(!pListener)
			return 0;

		return this->Conn(*pListener);
	}


}; 




X011_NAMESPACE_END


#endif






#ifndef X011__H_w_WTcpHttp_h
#define X011__H_w_WTcpHttp_h


X011_NAMESPACE_BEGIN


class WTcpHttp : public WTcpCellc
{
public:

	typedef std::map< std::string, std::string >	MAP_HTTPHEADPARA;
	typedef MAP_HTTPHEADPARA::iterator				MAP_HTTPHEADPARA_IT;
	typedef MAP_HTTPHEADPARA::value_type			MAP_HTTPHEADPARA_VT;


private:

	MAP_HTTPHEADPARA m_mapUrlHeadPara;

	MAP_HTTPHEADPARA m_mapSvrRtnHeadPara;


private:

	WTcpHttp & operator = (const WTcpHttp & rhs)
	{
		return *this;
	}

	WTcpHttp(const WTcpHttp & rhs)
	{;}


public:

	std::string m_strProxyAddr;


public:

	WTcpHttp()
	{
		m_strProxyAddr = "";
		ClearUrlHeadPara();
	}


	WTcpHttp( int iMaxSec ) 
	{
		killer_up( iMaxSec );

		m_strProxyAddr = "";
		ClearUrlHeadPara();
	}


	virtual ~WTcpHttp()
	{
		m_strProxyAddr = "";
	}





	const std::string & SetProxyAddr( std::string strPxyAddr )
	{
		return m_strProxyAddr = strPxyAddr;
	}


	
	


	void ClearUrlHeadPara()
	{
		m_mapUrlHeadPara.clear();
	}


	void AddUrlHeadPara( std::string strName, std::string strValue )
	{
		m_mapUrlHeadPara.insert( MAP_HTTPHEADPARA_VT( strName, strValue ) );
	}


	void ClearSvrRtnHeadPara()
	{
		m_mapSvrRtnHeadPara.clear();
	}


	static void MakeHeadParaMap( const std::string & strHeadPart , MAP_HTTPHEADPARA & hm )
	{
		hm.clear();

		std::vector<std::string> vecTmpTR, vecTmpTD;
		std::vector<std::string>::iterator itTR;
		SStrvs::vsa_imp( strHeadPart, std::string("\r\n"), 1, vecTmpTR );
		for( itTR = vecTmpTR.begin(); itTR!=vecTmpTR.end(); ++itTR )
		{
			SCake ck;
			ck.lets( itTR->c_str() );
			tchar *p = SStrf::sstr( ck.buf(), ":" );
			if( p )
			{
				*p = 0;
				p++;
				SStrf::strim( p );
			}
			else
			{
				
				p=NULL;
			}

			SStrf::strim( ck.buf() );
			vecTmpTD.push_back( ck.buf() );
			vecTmpTD.push_back( p ? p : "" );

			hm.insert( MAP_HTTPHEADPARA_VT( vecTmpTD[0], vecTmpTD[1] ) );
			vecTmpTD.clear();
		}

	}


	void ImportSvrRtnHeadPara( const std::string & strHeadPart )
	{
		


		MakeHeadParaMap( strHeadPart, m_mapSvrRtnHeadPara );
	}


	void ImportSvrRtnHeadPara( SCake ckHeadPart )
	{
		ImportSvrRtnHeadPara( std::string(ckHeadPart.mk_sz() ) );
	}

	MAP_HTTPHEADPARA GetSvrRtnHeadPara() const
	{
		return m_mapSvrRtnHeadPara;
	}

	std::string GetSvrRtnHeadParaVal( const std::string & strParaName )
	{
		return m_mapSvrRtnHeadPara[strParaName];
	}


	static void GetLine1ParaFromHead( const std::string & strHttpHead ,
										std::string & rstrCmdLine1 ,
										std::string & rstrCmdVerb ,
										std::string & rstrProtocolName ,
										std::string & rstrAddr ,
										std::string & rstrUPfn				)
	{
		SCake ck;
		std::string strSep;
		std::string strAddrTmp;

		std::string strCmdLine1, strCmdVerb, strProtocolName, strAddr;

		ck.lets( strHttpHead );

		strCmdLine1 = SStrvs::vsa_get( strHttpHead, std::string("\n"), 1, 0 );
		SStrf::strim( strCmdLine1 );

		strCmdVerb = SStrvs::vsa_get( strCmdLine1, std::string(" "), 1, 0 );

		
		ck.lets( strCmdLine1 );
		for( char *p = SStrf::splast( ck.buf() ); p != ck.buf(); p-- )
		{
			if( *p == ' ' )
			{
				*p = 0;
				break;
			}
		}

		strAddrTmp = ck.buf();

		
		if( strAddrTmp.find( "/" ) != std::string::npos && strAddrTmp.find( "://" ) == std::string::npos )
		{
			if( strAddrTmp.find( " /" ) != std::string::npos )
			{
				MAP_HTTPHEADPARA m;
				std::string s2(strHttpHead);
				SStrf::slcase( s2 );
				MakeHeadParaMap( s2, m );
				SStrf::sreplstr( strAddrTmp, " ", " http://" + m["host"] );
			}
			else
			{
				SStrf::sreplstr( strAddrTmp, " ", " http://" );
			}
		}


		strProtocolName = SStrvs::vsa_get( strAddrTmp, std::string("://"), 1, 0 );
		ck.lets( strProtocolName );
		SStrf::srev( ck.buf() );
		SStrf::sreplch( ck.buf(), ' ', 0 );
		strProtocolName = SStrf::srev( ck.buf() );


		

		if( strAddrTmp.find( "/" ) != std::string::npos )
		{
			strSep = "/";
		}
		else
		{
			strSep = " ";
		}
		strAddr = SStrvs::vsa_get( strAddrTmp, strSep, 1, 1 );


		if(1)
		{
			std::string str80("80");
			std::string s1(strProtocolName);

			SStrf::slcase( s1 );
			

			if( strAddr.find( ":" ) == std::string::npos ) strAddr += ":" + str80;

			if( *SStrf::splast( strAddr.c_str() ) == ':' ) strAddr += str80;
		}

		
		rstrCmdLine1 = strCmdLine1;
		rstrCmdVerb = strCmdVerb;
		rstrProtocolName = strProtocolName;
		rstrAddr = strAddr;

		rstrUPfn = SStrvs::vsa_get( strCmdLine1, std::string(" "), 1, 1 );
		rstrUPfn = SStrvs::vsa_get( rstrUPfn, std::string(" "), 1, 0 );
	}


	static std::string GetHostAddrFromUrl( std::string  strUrl )
	{
		std::string strConnWho;

		
		

		SStrf::strim( strUrl );
		strUrl = "a " + strUrl + " a"; 

		std::string s1;

		GetLine1ParaFromHead( strUrl, s1, s1, s1, strConnWho, s1 );

		return strConnWho;
	}



	static std::string GetResPathnameFromUrl( std::string  strUrl )
	{
		std::string::size_type ssti;
		std::string s;

		
		s = GetHostAddrFromUrl( strUrl );
		s = SStrvs::vsa_get( std::string(s), std::string(":"), 1, 0 );


		ssti = strUrl.find( s );
		if(ssti==std::string::npos) return "";
		ssti += s.size() /2;


		ssti = strUrl.find( '/', ssti );
		if(ssti==std::string::npos) return "/";	 


		return strUrl.c_str() + ssti;
	}



	tbool ConnUrl( std::string strUrl )
	{
		tbool iRc;
		std::string strConnWho;

		do 
		{
			iRc = 0;

			strConnWho = GetHostAddrFromUrl( strUrl );

			if( m_strProxyAddr.length() ) strConnWho = m_strProxyAddr;

			if( !Conn( strConnWho ) ) break;

			iRc = 1;

		}while(0);

		return iRc;
	}


	tbool SendHttpGet( std::string strUrl, std::string strHttpVer = "HTTP/1.0" , tbool bSmartSendResPathname = 1 , tbool bCleanUrlPara = 1 )
	{
		std::string strSnd;
		tbool iRc;
		std::string strConnWho;

		if(bSmartSendResPathname) 
		{
			

			if( this->m_strProxyAddr != "" ) 
			{
				
			}
			else
			{
				
				strUrl = GetResPathnameFromUrl( strUrl );
			}
		}

		strSnd =  "GET " + strUrl + " " + strHttpVer + "\r\n";

		AddUrlHeadPara( "Accept-language", "zh-cn" );
		
		AddUrlHeadPara( "User-Agent", "Mozilla/4.0 (compatible; MSIE 6.0; Windows NT 5.1; SV1; .NET CLR 1.1.4322)" );
		
		AddUrlHeadPara( "Pragma", "no-cache" );
		AddUrlHeadPara( "cache_control", "no-cache" );
		AddUrlHeadPara( "Cache-Control", "no-cache" );
		
		
		
		


		for( MAP_HTTPHEADPARA_IT it = m_mapUrlHeadPara.begin(); it != m_mapUrlHeadPara.end(); ++it )
		{
			strSnd += it->first;
			strSnd += ": ";
			strSnd += it->second;
			strSnd += "\r\n";
		}

		if(bCleanUrlPara)
		{
			ClearUrlHeadPara();
		}

		strSnd += "\r\n";


		do
		{
			iRc = 0;

			iRc = send_str( strSnd );

		}while(0);

		return iRc;
	}


	SCake SimpleHttpGetFile( std::string strUrl, int iMaxTimeoutSec = 11 )
	{
		WTcpHttp & h(*this);
		std::string & s(strUrl);
		SCake ckTmp;

		

		
		if( h.ConnUrl( s ) )
		{
			h.killer_up( iMaxTimeoutSec );

			AddUrlHeadPara( "Connection", "close" );
			h.SendHttpGet( s, "HTTP/1.0" );

			h.recv_ln( ckTmp, "\r\n\r\n" );

			h.ImportSvrRtnHeadPara( ckTmp );
			int i;
			i = atol( h.GetSvrRtnHeadParaVal( "Content-Length" ).c_str() );

			if( i <= 0 ) return SCake();

			h.recv_len( ckTmp , i );
			h.DisConn();
		}

		return ckTmp;
	}


}; 




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_WTcpEmailc_h
#define X011__H_w_WTcpEmailc_h


X011_NAMESPACE_BEGIN


class WTcpEmailc
{
private:

	WTcpEmailc & operator = (const WTcpEmailc & rhs)
	{
		return *this;
	}

	WTcpEmailc(const WTcpEmailc & rhs)
	{;}

protected:
	
	IRice	* m_pCellc;

public:

	WTcpEmailc()
	{
		m_pCellc = NULL;
	}

	virtual ~WTcpEmailc()
	{	;
	}

public:
	
	void LinkCellc( IRice * p )
	{
		m_pCellc = p;
	}
	
	void LinkCellc( IRice & r )
	{
		m_pCellc = &r;
	}

	
	std::string read_ack_msg()
	{
		std::string str1;
		SCake ck;

		do{
			m_pCellc->recv_ln( ck, "\n" );
			if( ck.len() == 0 ) return "";
			str1 = ck.mk_str();
			if( str1.empty() ) return "";
			if( str1[0] == '-' ) return str1;
			if( str1[0] == '+' ) return str1;
		}while(1);

		return "";
	}

	
	std::string read_welcome_msg()
	{
		std::string str1;
		SCake ck;

		do{
			m_pCellc->recv_ln( ck, "\n" );
			if( ck.len() == 0 ) return "";
			str1 = ck.mk_str();
			if( str1.size() < 3 ) return "";
			if( str1.size() == 3 ) return str1;
			if( str1.size() > 3 && str1[3] != '-' ) return str1;
		}while( str1.size() >= 4 && str1[3] == '-' );

		return "";
	}

	
	std::string get_t1( std::string strUser, std::string strPass )  
	{
		SCake ck;
		tbool rc;
		std::string str1;
		int statmax;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		rc = m_pCellc->send_str( "user " + strUser + "\r\n" ); 
		if( !rc ) return "";

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		rc = m_pCellc->send_str( "pass " + strPass + "\r\n" ); 
		if( !rc ) return "";

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		rc = m_pCellc->send_str( "stat\r\n" ); 
		if( !rc ) return "";

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		statmax = SStrf::satol( str1.c_str() + 3 );

		rc = m_pCellc->send_str( "top " + SStrf::sltoa(statmax) + " 1\r\n" ); 
		if( !rc ) return "";

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return ""; 

		std::vector<std::string> vecstrSeperate;

		vecstrSeperate.push_back("\n.\n");
		vecstrSeperate.push_back("\r\n.\r\n");

		m_pCellc->recv_ln( ck, vecstrSeperate );
		str1 = ck.mk_str();

		std::string strUpper = str1;

		SStrf::sucase(strUpper);

		std::string::size_type i = strUpper.find("SUBJECT: ");
		std::string::size_type i2 = i + SStrf::slen("SUBJECT: ");

		
		if(1)
		{
			rc = m_pCellc->send_str( "quit\r\n" ); 
			

			read_ack_msg();
			

		}

		for( ; i != std::string::npos && i < str1.size() ; i++ )
		{
			if( str1[i] == 0x0d || str1[i] == 0x0a )
			{
				str1[i] = 0;
				return &(str1[i2]);
			}
		}

		return str1;
	}

	
	virtual tbool on_before_get_t2_del( std::string strNowTitle, std::string strNowSender )
	{
		return 0;
	}


	tbool get_t2( std::string strUser, std::string strPass, std::vector< std::string > *pvSubject, std::vector< std::string > *pvFrom )
	{
		SCake ck;
		tbool rc;
		std::string str1;
		int statnum;
		int statnum1;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return 0; 

		rc = m_pCellc->send_str( "user " + strUser + "\r\n" ); 
		if( !rc ) return 0;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return 0; 

		rc = m_pCellc->send_str( "pass " + strPass + "\r\n" ); 
		if( !rc ) return 0;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return 0; 

		rc = m_pCellc->send_str( "stat\r\n" ); 
		if( !rc ) return 0;

		str1 = read_ack_msg();
		if( str1.empty() || str1[0] != '+' ) return 0; 
		statnum = SStrf::satol( str1.c_str() + 3 );

		if(pvSubject) pvSubject->clear();
		if(pvFrom) pvFrom->clear();
		for( statnum1 = 1 ; statnum1 <= statnum; statnum1 ++ )
		{
			rc = m_pCellc->send_str( "top " + SStrf::sltoa(statnum1) + " 1\r\n" ); 
			if( !rc ) return 0;

			str1 = read_ack_msg();
			if( str1.empty() || str1[0] != '+' ) return 0; 

			std::vector<std::string> vecstrSeperate;

			vecstrSeperate.push_back("\n.\n");
			vecstrSeperate.push_back("\r\n.\r\n");

			m_pCellc->recv_ln( ck, vecstrSeperate );
			str1 = ck.mk_str();


			std::string strNowTitle, strNowSender;
			std::string *ps=NULL;

			if(pvSubject) pvSubject->push_back("");
			if(pvFrom) pvFrom->push_back("");

			if(pvSubject) ps = &(*(pvSubject->rbegin()));
			if(1) 
			{
				std::string strKey = "aSUBJECT: ";
				std::string str2 = str1;
				std::string strUpper = str2;

				strKey[0] = 0x0a;
				SStrf::sucase(strUpper);

				std::string::size_type i1 = strUpper.find(strKey);
				std::string::size_type i2 = i1 + SStrf::slen(strKey.c_str());

				if( i1 != std::string::npos ) i1++;

				for( ; i1 != std::string::npos && i1 < str2.size() ; i1++ )
				{
					if( str2[i1] == 0x0d || str2[i1] == 0x0a )
					{
						str2[i1] = 0;
						strNowTitle = &(str2[i2]);
						if(pvSubject) { *ps = &(str2[i2]); break; }
					}
				}
			}

			if(pvFrom) ps = &(*(pvFrom->rbegin()));
			if(1) 
			{
				std::string strKey = "aFROM: ";
				std::string str2 = str1;
				std::string strUpper = str2;

				strKey[0] = 0x0a;
				SStrf::sucase(strUpper);

				std::string::size_type i1 = strUpper.find(strKey);
				std::string::size_type i2 = i1 + SStrf::slen(strKey.c_str());

				if( i1 != std::string::npos ) i1++;

				for( ; i1 != std::string::npos && i1 < str2.size() ; i1++ )
				{
					if( str2[i1] == 0x0d || str2[i1] == 0x0a )
					{
						str2[i1] = 0;

						strNowSender = &(str2[i2]);	

						if( strNowSender.find("<") != std::string::npos )
						{
							str2 = SStrvs::vsa_get( strNowSender, "<", 0, 1 );
							strNowSender = SStrvs::vsa_get( str2, ">", 0, 0 );
						}

						if(pvFrom)
						{
							*ps = strNowSender;
							break;
						}
					}
				}
			}

			tbool biWithDel = 1;

			biWithDel = on_before_get_t2_del( strNowTitle, strNowSender );

			if( biWithDel )
			{
				rc = m_pCellc->send_str( "DELE " + SStrf::sltoa(statnum1) + "\r\n" );   
				if( !rc ) return 0;

				std::string ss = read_ack_msg();
				if( ss.empty() || ss[0] != '+' ) return 0; 
			}

		}

		rc = m_pCellc->send_str( "quit\r\n" ); 
		read_ack_msg();

		return 1;
	}


	tbool send_t1( std::string strEHLO, std::string strUser, std::string strPass, std::string strFromEmailAddr, std::string strToEmailAddr, std::string strSubj, std::string strBody )
	{
		SCake ck;
		tbool rc;
		std::string str1;

		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 220 ) return 0;

		
		
		
		
		
		rc = m_pCellc->send_str( "ehlo " + strEHLO + "\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;

		
		rc = m_pCellc->send_str( "auth login\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 334 ) return 0;

		
		rc = m_pCellc->send_str( SStrTbl::encodebase64str(strUser) + "\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 334 ) return 0;

		
		rc = m_pCellc->send_str( SStrTbl::encodebase64str(strPass) + "\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 235 ) return 0;

		
		rc = m_pCellc->send_str( "mail from: <" +  strFromEmailAddr + ">\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;

		
		rc = m_pCellc->send_str( "rcpt to: <" +  strToEmailAddr + ">\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;

		
		rc = m_pCellc->send_str( "data\r\n" );
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 354 ) return 0;

		rc = m_pCellc->send_str(__FUNCTION__);
		rc = m_pCellc->send_str( "\r\n" );
		rc = m_pCellc->send_str(SStrf::sltoa(__LINE__));
		rc = m_pCellc->send_str( "\r\n" );
		rc = m_pCellc->send_str( "Subject: " + strSubj + "\r\n" );

		rc = m_pCellc->send_str( "\r\n" );
		rc = m_pCellc->send_str( strBody );
		rc = m_pCellc->send_str( "\r\n.\r\n" );

		
		
		
		str1 = read_welcome_msg();
		if( SStrf::satol(str1) != 250 ) return 0;

		rc = m_pCellc->send_str( "quit\r\n" );
		str1 = read_welcome_msg();
		

		return 1;
	}

};




X011_NAMESPACE_END

#endif






#ifndef X011__H_w_WComeliProtocol_h
#define X011__H_w_WComeliProtocol_h


X011_NAMESPACE_BEGIN


class WComeliProtocol : public WTcpDisConnable
{

public:

	volatile tbool  m_biComportOpened;
	volatile tbool  m_biShouldDisConn;
	volatile tbool  m_biRecvHaveComTimeoutTrait;


private:

	WComeliProtocol & operator = (const WComeliProtocol & rhs) 	{ 	return *this; }
	WComeliProtocol(const WComeliProtocol & rhs) {;}


public:

	WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
		m_biRecvHaveComTimeoutTrait = 1;

	}

	virtual ~WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;
	}


public:

	
	typedef tuint8 (* PfChkSum_t) ( tuint8 a, tuint8 b );

	static tuint8 comesc_xor ( tuint8 a, tuint8 b ) { return a ^ b; };
	static tuint8 comesc_add ( tuint8 a, tuint8 b ) { return a + b; };


	static SCake & comesc_en( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = comesc_add, SCake * pdata2 = NULL ) 
	{
		

		tuint8  ucChkSum(0);
		std::vector<tuint8> v1;
		tuint8 c;

		
		v1.push_back(a1);


		for( tsize i2 = 0; pdata2 && i2 < pdata2->len(); i2++ )
		{
			c = *(tuint8*)(pdata2->buf()+i2);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back( c );
		}


		c = static_cast<tuint8>( ckDataInOut.len() );
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back( c );


		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			c = *(tuint8*)(ckDataInOut.buf()+i);
			if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
			v1.push_back(c);
		}


		
		for( tsize i3 = 0; i3 < ckDataInOut.len(); i3++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i3) );
		}
		
		for( tsize i4 = 0; pdata2 && i4 < pdata2->len(); i4++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)((*pdata2).buf()+i4) );
		}
		 
		c = (*pf)( ucChkSum, static_cast<tuint8>( ckDataInOut.len() ) );
		
		if( c == a1 || c == a2 || c == a3 ) v1.push_back(a2);
		v1.push_back(c);


		
		v1.push_back(a3);


		ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

		return ckDataInOut;
	}


	
	static SCake & comesc_en( SCake ckDataIn, SCake & ckDataOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = comesc_add, SCake * pdata2 = NULL ) 
	{
		return ckDataOut = comesc_en( ckDataIn, a1, a2, a3 , pf, pdata2 );
	}


	
	static int comesc_de( SCake & ckDataInOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = NULL , SCake * pdata2 = NULL ) 
	{
		if( ckDataInOut.len() != 0 )
		{
			std::vector<tuint8> v1;
			int flag = 1;

			

			for( tsize i = 0; i < ckDataInOut.len(); i++ )
			{
				tuint8 c = *(tuint8*)(ckDataInOut.buf()+i);
				tuint8 c2;


				if( flag == 1 )
				{
					if( c == a1 && i == 0 )
					{
						flag = 2;
						continue;
					}

					if( c == a1 && i != 0 )
					{
						tuint8 c0 = *(tuint8*)(ckDataInOut.buf()+i-1); 
						if( c == a1 && c0 != a2 ) 
						{
							flag = 2;
							continue;
						}
					}

					continue;
				}


				
				if( i+1 < ckDataInOut.len() )
				{
					
					c2 = *(tuint8*)(ckDataInOut.buf()+i+1);

					if( c == a2 )
					{
						v1.push_back( c2 );
						i++;
					}
					else
					{
						v1.push_back( c );
					}
				}
				else
				{
					
					if( c != a2 && c != a3 ) v1.push_back( c );
				}
			}

			
			if(v1.size()<2)
			{
				ckDataInOut.redim(0);
				return 0;
			}

			if( pdata2 != NULL && pdata2->len() != 0 )
			{
				if( v1.size() - pdata2->len() < 2 )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				for( tsize i2 = 0; i2 < pdata2->len(); i2++ )
				{
					tuint8 c = v1[0];
					*(tuint8*)(pdata2->buf()+i2) = c;
					v1.erase( v1.begin() );
				}
			}

			
			if( v1.size() == 2 )
			{
				ckDataInOut.redim(0);
				return v1[0];
			}

			
			{
				tuint8 ilen = v1[0];
				tuint8 iChkSum = v1[v1.size()-1];
				v1.erase( v1.begin() );
				v1.erase( v1.end() - 1 );

				ckDataInOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

				
				if( pf )
				{
					tuint8  ucChkSum(0);

					for( tsize i = 0; i < ckDataInOut.len(); i++ )
					{
						ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
					}
					if( iChkSum != ucChkSum )
					{
						ckDataInOut.redim(0);
						return 0;
					}
				}

				if( ilen != ckDataInOut.len() )
				{
					ckDataInOut.redim(0);
					return 0;
				}

				return ilen;
			}
		}

		return 0;
	}


	
	static int comesc_de(  SCake ckDataIn, SCake & ckDataOut, tuint8 a1, tuint8 a2, tuint8 a3 , PfChkSum_t pf = NULL , SCake * pdata2 = NULL )
	{
		int i = comesc_de( ckDataIn, a1, a2, a3 , pf, pdata2 );
		ckDataOut = ckDataIn;
		return i;
	}


	

	static SCake & com_hzo_de( const void * p, tsize iLen, SCake & ckOut )
	{
		tuint8 a1 = 0x06; 
		tuint8 a2 = 0x10;
		tuint8 a3 = 0x03;
		std::vector<tuint8> v1;
		int flag = 1;

		

		for( tsize i = 0; i < iLen; i++ )
		{
			tuint8 c = *((tuint8*)p+i);
			tuint8 c2;

			if( flag == 1 )
			{
				if( c == a1 && i == 0 )
				{
					flag = 2;
					continue;
				}

				if( c == a1 && i != 0 )
				{
					tuint8 c0 = *((tuint8*)p+i-1); 
					if( c == a1 && c0 != a2 ) 
					{
						flag = 2;
						continue;
					}
				}

				continue;
			}

			
			if( i+1 < iLen )
			{
				
				c2 = *((tuint8*)p+i+1);

				if( c == a2 )
				{
					v1.push_back( c2 );
					i++;
				}
				else
				{
					v1.push_back( c );
				}
			}
			else
			{
				
				if( c != a2 && c != a3 ) v1.push_back( c );
			}
		}

		
		if(v1.size()<1)
		{
			ckOut.redim(0);
		}
		else
			ckOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

		return ckOut;
	}


	static SCake & com_hzo_en( const void * p, tsize iLen, SCake & ckOut )
	{
		std::vector<tuint8> v1;
		tuint8 c;
		const tuint8 *p1 = (const tuint8 *)p;

		v1.push_back(0x02);

		for( tsize i2 = 0; i2 < iLen; i2++ )
		{
			c = p1[i2];
			if( c == 0x02	||
				c == 0x03	||
				c == 0x10	||
				c == 0x06	)
			{
				v1.push_back(0x10);
			}
			v1.push_back( c );
		}

		v1.push_back(0x03);

		ckOut.let( (tchar*)&(v1[0]), (tsize)v1.size() );

		return ckOut;
	}






	tbool recv_comesc_wrong( SCake & ckData , tuint8 a2, tuint8 a3 )
	{
		SCake ckTmp;
		tsize i = 1;

		do
		{
			if( m_ckDataL2CacheBuf.len() >= 2 )
				for( ; i < m_ckDataL2CacheBuf.len(); i++ )
				{
					tchar c = *(m_ckDataL2CacheBuf.buf()+i);
					tchar c1 = *(m_ckDataL2CacheBuf.buf()+i-1);

					if( c1 != a2 && c == a3 )
					{
						goto L_RECV_ESC; 
					}
				}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

		}while(ckTmp.len()>0);

L_RECV_ESC:
		ckData.redim(i+1);
		m_ckDataL2CacheBuf.dump( ckData );
		
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


	tbool recv_comesc_wrong2( SCake & ckData , tuint8 a2, tuint8 a3 )
	{
		SCake ckTmp;
		tsize i = 1;
		int iState = 0x02;

		do
		{
			if( m_ckDataL2CacheBuf.len() < 2 )
			{
			}
			else
			{
				for( ; i < m_ckDataL2CacheBuf.len(); i++ )
				{
					tuint8 *p1;

					p1 = (tuint8 *)(m_ckDataL2CacheBuf.buf() + i);

					if( iState == 0x02 && *p1 == a2 )
					{
						iState = 0x10;
						continue;
					}

					if( iState == 0x10 )
					{
						iState = 0x02;
						continue;
					}

					if( iState == 0x02 && *p1 == a3 )
					{
						
						goto L_RECV_ESC; 
					}
				}
			}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

		}while(ckTmp.len()>0);

L_RECV_ESC:
		ckData.redim(i+1);
		m_ckDataL2CacheBuf.dump( ckData );
		
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


	
	tbool recv_comesc( SCake & ckData , tuint8 a2, tuint8 a3 )
	{
		SCake ckTmp;
		tsize i = 1;
		unsigned int iCount;

		do
		{
			if( m_ckDataL2CacheBuf.len() < 2 )
			{
			}
			else
			{
				for( ; i < m_ckDataL2CacheBuf.len(); i++ )
				{
					tuint8 *p1;
					tuint8 *p2;

					p1 = (tuint8 *)(m_ckDataL2CacheBuf.buf() + i);

					if( *p1 == a3 )
					{
						iCount = 0;

						for( int ii2 = i - 1; ii2 >= 1; ii2-- )
						{
							p2 = (tuint8 *)(m_ckDataL2CacheBuf.buf() + ii2);
							if( *p2 == a2 )
								iCount++;
							else
								break;
						}

						iCount &= 1;

						if( iCount == 0x00 )
						{
							goto L_RECV_ESC; 
						}
					}
				}
			}

			if( !sys_recv( ckTmp ) ) break;

			m_ckDataL2CacheBuf.append(ckTmp);

		}while(ckTmp.len()>0);

L_RECV_ESC:
		ckData.redim(i+1);
		m_ckDataL2CacheBuf.dump( ckData );
		
		return ckData.len()+m_ckDataL2CacheBuf.len()==0?0:1;
	}


public:

	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;
	}


	virtual int on_get_defaultrecv_buf_len() 
	{
		return 1;
	}


}; 



X011_NAMESPACE_END

#endif







#ifndef X011__H_w_WComeliCell_h
#define X011__H_w_WComeliCell_h


X011_NAMESPACE_BEGIN


class WComeliCell : public WComeliProtocol
{

protected:

	int   m_hComport;


private:

	WComeliCell & operator = (const WComeliCell & rhs) 	{ 	return *this; }
	WComeliCell(const WComeliCell & rhs) {;}

	
	int  m_itimeoutsec;
	int  m_itimeoutusec;

public:

	
	WComeliCell()
	{

	}

	
	virtual ~WComeliCell()
	{
		if( m_biComportOpened )
		{
			close(m_hComport); 
			m_biComportOpened = 0;
		}
	}


public:

	
	tbool Conn( std::string strname )
	{
		DisConn();

		WNava nv;
		char ss[55];
		std::string strComName;

		nv.impconf( strname, ";", "=" );

		strComName = nv.get("com");
		SStrf::strim(strComName);
		if( strComName.empty() )
			return 0;

		if( SStrf::sisdec(strComName[0]) )
			(*SClib::p_sprintf())( ss, "/dev/ttyS%d", (int)SStrf::satol( nv.get("com") ) - 1 );  
		else
			(*SClib::p_sprintf())( ss, "/dev/%s", strComName.c_str() );        

		m_hComport = open( ss, O_RDWR | O_NOCTTY | O_NDELAY );

		if ( m_hComport < 0 )
		{
			
			return 0;
		}

		m_biComportOpened = 1;


		if(1)
		{
			int speed_arr[] = { B50, B75, B110, B134, B150, B200, B300, B600, B1200, B1800, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400 };
			int name_arr[] =  {  50,  75,  110,  134,  150,  200,  300,  600,  1200,  1800,  2400,  4800,  9600,  19200,  38400,  57600,  115200,  230400 };
			int i;
			int status;
			struct termios Opt;
			tcgetattr(m_hComport, &Opt);
			for ( i= 0; i < sizeof(speed_arr) / sizeof(int); i++)
			{
				if ( (int)SStrf::satol( nv.get("speed") ) == name_arr[i] )
				{
					tcflush(m_hComport, TCIOFLUSH);
					cfsetispeed(&Opt, speed_arr[i]);
					cfsetospeed(&Opt, speed_arr[i]);
					status = tcsetattr(m_hComport, TCSANOW, &Opt);
					if (status != 0)
					{
						close(m_hComport); 
						m_biComportOpened = 0;
						return 0;
					}
					tcflush(m_hComport,TCIOFLUSH);
					break;
				}
			} 

			if( i >= sizeof(speed_arr) / sizeof(int) )
			{
				close(m_hComport); 
				m_biComportOpened = 0;
				return 0;
			}
		}


		if(1)
		{
			struct termios options;
			if ( tcgetattr( m_hComport,&options) != 0 )
			{
				close(m_hComport); 
				m_biComportOpened = 0;
				return 0;
			}
			options.c_cflag &= ~CSIZE;
			switch ( (tuint8)SStrf::satol( nv.get("datalen") ) )
			{
			case 7:
				options.c_cflag |= CS7;
				break;
			case 8:
				options.c_cflag |= CS8;
				break;
			default:
				close(m_hComport); 
				m_biComportOpened = 0;
				return 0;
			}
			switch ( nv.get("parity")[0] )
			{
			case 'n':
			case 'N':
				options.c_cflag &= ~PARENB;
				options.c_iflag &= ~INPCK;
				break;
			case 'o':
			case 'O':
				options.c_cflag |= (PARODD | PARENB);
				options.c_iflag |= INPCK;
				break;
			case 'e':
			case 'E':
				options.c_cflag |= PARENB;
				options.c_cflag &= ~PARODD;
				options.c_iflag |= INPCK;
				break;
			case 'S':
			case 's':
				options.c_cflag &= ~PARENB;
				options.c_cflag &= ~CSTOPB;
				break;
			default:
				close(m_hComport); 
				m_biComportOpened = 0;
				return 0;
			}
			switch ( (int)SStrf::satol( nv.get("stop") ) )
			{
			case 1:
				options.c_cflag &= ~CSTOPB;
				break;
			case 2: options.c_cflag |= CSTOPB;
				break;
			default:
				close(m_hComport); 
				m_biComportOpened = 0;
				return 0;
			}
			if ( nv.get("parity")[0] != 'n' && nv.get("parity")[0] != 'N' )
				options.c_iflag |= INPCK;
			tcflush(m_hComport,TCIFLUSH);
			options.c_cc[VTIME] = 0;
			options.c_cc[VMIN] = 1;

			options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG); options.c_oflag &= ~OPOST;


			options.c_iflag = 0;
			options.c_oflag = 0;
			options.c_lflag = 0;


			if (tcsetattr(m_hComport,TCSANOW,&options) != 0)
			{
				close(m_hComport); 
				m_biComportOpened = 0;
				return 0;
			}

		}



		m_itimeoutsec = SStrf::satol( nv.get("timeoutsec") );
		m_itimeoutusec = (int) ( 1000 * 1000 * SStrf::satof( "0." + SStrvs::vsa_get( nv.get("timeoutsec"), ".", 1, 1 ) ) );

		m_biShouldDisConn = 0;

		return 1;
	}


	virtual void OnDisConn()
	{
		m_biShouldDisConn = 1;

		if( m_biComportOpened )
		{
			close(m_hComport); 
			m_biComportOpened = 0;
		}
	}


public:

	
	virtual int on_sys_recv( SCake & ckDataBuf ) 
	{
		while(1)
		{
			if(m_biShouldDisConn)
			{
				return 0;
			}

			if( !m_biComportOpened )
				return 0;

			ckDataBuf.redim( on_get_defaultrecv_buf_len() ); 

			int retval;
			fd_set rfds;
			struct timeval tv;
			int ret;
			tv.tv_sec = m_itimeoutsec;
			tv.tv_usec = m_itimeoutusec;

			if(m_biComportOpened)
			{
				FD_ZERO(&rfds);
				FD_SET(m_hComport,&rfds);
				retval = select(m_hComport+1,&rfds,NULL,NULL,&tv);
				if( retval < 0 )
				{
					return 0;
				}

				if( retval == 0 )
				{
					return 0;
				}

				if( retval > 0 )
				{
					
					ret= read( m_hComport, ckDataBuf.buf(), ckDataBuf.len() );
					return (int)ckDataBuf.len();
				}
			}

			if( m_biRecvHaveComTimeoutTrait )
				return 0;
			else
				WThrd::tr_sleep( 0, 0.002 );
		}
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		if( !m_biComportOpened )
			return 0;


		int len   =   0;

		
		len = (int)ckDataBuf.len();
		len   = write( m_hComport, ckDataBuf.buf_const(), len );

		if ( len > 0 )
		{
			
			if( ckDataBuf.len() % 13 == 3 || SStrf::rand1() > 0.88 )
			{
				
			}
		}

		return (int)len > 0 ? len : 0;
	}


}; 



X011_NAMESPACE_END

#endif







#ifndef X011__H_w_WHWPoorCellc_h
#define X011__H_w_WHWPoorCellc_h



X011_NAMESPACE_BEGIN





class HWPoorCellc : public WTcpDisConnable
{
private:

	WComeliCell  m_Comport;

	
	tbool ComportSendAndEcho( std::string str1 ) 
	{
		tbool rc;
		SCake ck;

		rc = m_Comport.send_str( str1 + "\r\n" ); 
		if( !rc ) return 0;

		return ExpectingEcho( str1, 6 );
	}

	
	tbool ExpectingEcho( std::string str1, int ii = 3 , std::string *pstrRtnBuf = NULL )
	{
		tbool rc;
		SCake ck;
		std::string str9;

		
		for( int i = 0; i < ii; i++ )
		{
			rc = m_Comport.recv_ln( ck, "\n" ); 
			str9 = ck.mk_str();
			SStrf::strim(str9);
			
			if( !rc ) return 0;

			if( pstrRtnBuf ) *pstrRtnBuf += str9 + "\r\n";

			if( str1 == str9 ) return 1;

			if( str1.find("|") != std::string::npos )
				if( str1.find(str9) != std::string::npos ) return 1;

			if( !str1.empty() && str1[0] == '*' ) 
			{
				std::string s1 = str1.c_str()+1;
				std::string s9 = str9;
				SStrf::sucase(s1);
				SStrf::sucase(s9);
				if( s9.find(s1) != std::string::npos ) return 1;
			}
		}

		return 0;
	}

private:

	HWPoorCellc & operator = (const HWPoorCellc & rhs) 	{ 	return *this; }
	HWPoorCellc(const HWPoorCellc & rhs) {;}

public:
	int  m_iRecvTimeoutTimes;

public:

	HWPoorCellc()
	{
		m_iRecvTimeoutTimes = 3;
	}

	virtual ~HWPoorCellc()
	{
		CloseEnv1();
	}

public:

	
	tbool OpenEnv1( std::string strname = "com=6;start=1;stop=1;speed=9600;parity=N;datalen=8;timeoutsec=7.890;" )
	{
		tbool rc;
		SCake ck;
		std::string str1;

		WThrd::tr_sleep( 0, 0.5 );

		rc = m_Comport.Conn(strname);
		if( !rc ) return 0;

		
		WThrd::tr_sleep( 1, 0.5 );

		rc = ComportSendAndEcho( "AT+CGDCONT=1,\"IP\",\"CMNET\"" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK", 3 );
		if( !rc ) return 0;

		WThrd::tr_sleep( 1, 0.5 );

		rc = ComportSendAndEcho( "AT%ETCPIP" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK", 3 );
		if( !rc ) return 0;

		return 1;
	}


	std::string AtDns( std::string strDomain ) 
	{
		tbool rc;
		SCake ck;
		std::string str1;

		rc = ComportSendAndEcho( "AT%DNSR=\"" + strDomain + "\"" ); 
		if( !rc ) return "";

		rc = m_Comport.recv_ln( ck, "\n" ); 
		str1 = ck.mk_str();
		SStrf::strim(str1);
		if( !rc ) return "";

		if( str1.find("%DNSR:") == 0 )
		{
			rc = m_Comport.recv_ln( ck, "\n" ); 

			std::string str2 = str1.c_str() + SStrf::slen("%DNSR:");
			return SStrf::strim(str2);
		}

		return "";
	}

	
	std::string getipbyname( std::string name )
	{	return AtDns( name );	}


	tbool AtRst()
	{
		tbool rc;
		SCake ck;
		std::string str1;

		rc = m_Comport.send_str( "AT%RST\r\n" );
		if( !rc ) return 0;

		WThrd::tr_sleep( 1, 0.5 );

		rc = ExpectingEcho( "*Command Interpreter ready", 7 );
		if( !rc ) return 0;

		return 1;
	}

	
	std::string At( std::string strAt, std::string strLastEcho )
	{
		tbool rc;
		std::string str1;

		rc = ComportSendAndEcho( strAt ); 
		if( !rc ) return "";

		rc = ExpectingEcho( "OK|ERROR", 3, &str1 );
		if( !rc ) return "";

		return str1;
	}

	
	tbool LogoutGprs()
	{
		tbool rc;

		rc = ComportSendAndEcho( "AT%IPCLOSE=5" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK|ERROR", 3 );
		if( !rc ) return 0;

		return 1;
	}

	
	tbool CloseEnv1() 
	{
		tbool rc;

		rc = ComportSendAndEcho( "AT%IPCLOSE=5" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK|ERROR", 3 );
		if( !rc ) return 0;

		m_Comport.DisConn();

		return 1;
	}

	
	tbool CloseSingleTcpConn() 
	{
		tbool rc;
		SCake ck;
		std::string str1;

		rc = ComportSendAndEcho( "AT%IPCLOSE" );
		if( !rc ) return 0;

		rc = ExpectingEcho( "OK|ERROR", 3 );
		if( !rc ) return 0;

		return 1;
	}

	
	tbool Conn( std::string strIp, int iPort )
	{
		tbool rc;
		SCake ck;
		std::string str1;

		rc = ComportSendAndEcho( "AT%IPOPEN=\"TCP\",\"" + strIp + "\"," + SStrf::sltoa(iPort) );
		if( !rc ) return 0;

		rc = ExpectingEcho( "CONNECT", 3 );
		if( !rc ) return 0;

		return 1;
	}

	tbool Conn( std::string strAddrLst ) 
	{
		std::vector<std::string> vecAddr1;

		SStrvs::vsa_imp( strAddrLst, std::string("|"), 1, vecAddr1 );

		for( int i = 0; i < (int)vecAddr1.size(); i ++ )
		{
			std::string strAddr = vecAddr1[i];

			try
			{
				std::vector<std::string> vecNameParts;
				SStrvs::vsa_imp( strAddr, std::string(":"), 1, vecNameParts );
				vecNameParts.push_back( std::string("") );
				vecNameParts.push_back( std::string("") );
				if( this->Conn( vecNameParts[0], static_cast<u_short>(SStrf::satol(vecNameParts[1].c_str()) ) ) ) return 1;
			}
			catch(...)
			{
				return 0;
			}
		}

		return 0;
	}

public:

	
	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		int iPerLen = 22;
		tbool rc;
		SCake ck;
		std::string str1;

		if( !m_Comport.m_biComportOpened ) return 0;
		if( m_Comport.m_biShouldDisConn ) return 0;

		if( ckDataBuf.len() == 0 ) return 0;

		if( (int)ckDataBuf.len() > iPerLen )
		{
			ck.let( ckDataBuf.buf_const(), iPerLen );
		}
		else
		{
			iPerLen = ckDataBuf.len();
			ck.let( ckDataBuf.buf_const(), iPerLen );
		}

		str1 = "AT%IPSEND=\"" + ck.GetReadable() + "\"";

		rc = ComportSendAndEcho( str1 );
		if( !rc ) return 0;

		rc = m_Comport.recv_ln( ck, "\n" );
		str1 = ck.mk_str();
		SStrf::strim(str1);
		if( !rc ) return 0;
		

		rc = ExpectingEcho( "OK", 3 );
		if( !rc ) return 0;

		return iPerLen;
	}

	
	virtual int on_sys_recv( SCake & ckDataBuf ) 
	{
		tbool rc;
		SCake ck;
		std::string str1;
		std::string str2;

		if( !m_Comport.m_biComportOpened ) return 0;
		if( m_Comport.m_biShouldDisConn ) return 0;

		for( int i = 0; i < m_iRecvTimeoutTimes ; i++ )
		{
			rc = m_Comport.recv_ln( ck, "\n" ); 
			str1 = ck.mk_str();
			SStrf::strim(str1);
			if( !rc ) return 0;

			if( str1.find("%IPDATA:") == 0 ) break;

			if( !str1.empty() && str1.find("%IPDATA:") != 0 ) return 0; 

			WThrd::tr_sleep( 0, 0.5 );


			if( !m_Comport.m_biComportOpened ) break;
			if( m_Comport.m_biShouldDisConn ) break;
		}

		str2 = SStrvs::vsa_get( str1, "\"", 0, 1 );

		if( str2.empty() ) return 0;

		ck.ConvPackStr2Bin(str2);

		ckDataBuf = ck;

		return (int)ck.len();
	}


	virtual void OnDisConn()
	{
		CloseSingleTcpConn();
	}

};




X011_NAMESPACE_END

#endif







#ifndef X011__H_w_MOON_MAN_h
#define X011__H_w_MOON_MAN_h


X011_NAMESPACE_BEGIN


template < class CONN_AGENT_T >
class WMoonMan : public WTcpDisConnable
{

private:

	std::string		m_strMManId;
	std::string		m_strMManIdRemote;

	tbool m_iIsConnected;


	int on_sys_recv( SCake & ckDataBuf ) 
	{
		if( !m_iIsConnected ) return 0;
		return OnRecv( ckDataBuf ) ;
	}

	int on_sys_send( const SCake & ckDataBuf ) 
	{
		if( !m_iIsConnected ) return 0;
		return OnSend( ckDataBuf );
	}


protected:

	static std::string MkId()
	{
		return WFile::MkRUStr();
	}


public:

	WMoonMan() :
	  m_iIsConnected(0)
	{
	}

	virtual ~WMoonMan()
	{
	}


public:

	typedef CONN_AGENT_T  CONN_AGENT_TYPET;


public:

	tbool Conn( CONN_AGENT_TYPET  rd ) 
	{
		SetMManId();
		SetMManIdRemote();
		m_iIsConnected = OnConn( rd )?1:0;
		return m_iIsConnected;
	}

	void DisConn()
	{
		m_iIsConnected = 0;

		
		WTcpDisConnable::DisConn();
	}

	tbool IsConnected() const
	{
		return m_iIsConnected;
	}


	void SetMManId( std::string strId = "" )
	{
		if( strId == "" )
			m_strMManId = MkId();
		else
			m_strMManId = strId;
	}


	void SetMManIdRemote( std::string strId = "" )
	{
		if( strId == "" )
			m_strMManIdRemote = MkId();
		else
			m_strMManIdRemote = strId;
	}


	std::string GetMManId() const
	{
		return m_strMManId;
	}


	std::string GetMManIdRemote() const
	{
		return m_strMManIdRemote;
	}


public:

	virtual tbool OnConn( CONN_AGENT_TYPET  rd ) = 0;
	

	virtual void OnDisConn() = 0;
	

	virtual int OnRecv( SCake & ckDataBuf ) = 0;
	

	virtual int OnSend( const SCake & ckDataBuf ) = 0;
	

}; 



X011_NAMESPACE_END


#endif







#ifndef X011__H_w_MOON_box_H
#define X011__H_w_MOON_box_H


X011_NAMESPACE_BEGIN


template < class MoonMan_Ta, class MoonMan_Tb >
class WMoonBox : public WThrd
{

private:

	class WMoonBoxThread : public WThrd
	{
	public:
		WMoonBox * m_Mbox;
		int m_iMManType;

		WMoonBoxThread()
		{;}
		virtual ~WMoonBoxThread()
		{ tr_destruct(); }

		virtual int tr_on_user_run()
		{
			if( m_iMManType == 'a' )
			{
				return m_Mbox->RunMMa();
			}
			else
			{
				return m_Mbox->RunMMb();
			}
		}
	};


private:

	MoonMan_Ta * m_pMMa;
	MoonMan_Tb * m_pMMb;

	WMoonBoxThread m_thrdMMa;
	WMoonBoxThread m_thrdMMb;


	virtual int tr_on_user_run()
	{
		return RunMM3();
	}


	int DeliverAb( WTcpDisConnable * p1, WTcpDisConnable * p2 )
	{
		SCake ckTmp;
		if( p1->recv_bin( ckTmp ) )
		{
			OnDeliverAb( ckTmp );
			p2->send_bin( ckTmp );
			return 1;
		}
		p2->DisConn();
		return 0;
	}


	int DeliverBa( WTcpDisConnable * p1, WTcpDisConnable * p2 )
	{
		SCake ckTmp;
		if( p1->recv_bin( ckTmp ) )
		{
			OnDeliverBa( ckTmp );
			p2->send_bin( ckTmp );
			return 1;
		}
		p2->DisConn();
		return 0;
	}


	int RunMMa()
	{
		return DeliverAb( m_pMMa, m_pMMb ); 
	}


	int RunMMb()
	{
		return DeliverBa( m_pMMb, m_pMMa );
	}


	int RunMM3()
	{
		return OnMoonBoxThrdRun( m_thrdMMa, m_thrdMMb );
	}


public:

	WMoonBox()
	{
		m_pMMa = new MoonMan_Ta();
		m_pMMb = new MoonMan_Tb();
	}


	virtual ~WMoonBox()
	{
		m_thrdMMa.tr_shouldbrk();
		m_thrdMMb.tr_shouldbrk();
		m_pMMa->DisConn();
		m_pMMb->DisConn();
		m_thrdMMa.tr_wait();
		m_thrdMMb.tr_wait();

		if(m_pMMa)
		{
			delete m_pMMa;
		}

		if(m_pMMb)
		{
			delete m_pMMb;
		}

		tr_destruct();
	}


public:

	void Init()
	{
		
		
	}


	MoonMan_Ta & GetMMa()
	{
		return * m_pMMa;
	}


	MoonMan_Tb & GetMMb()
	{
		return * m_pMMb;
	}


	void Launch()
	{
		m_thrdMMa.m_Mbox = this;
		m_thrdMMa.m_iMManType = 'a';
		m_thrdMMb.m_Mbox = this;
		m_thrdMMb.m_iMManType = 'b';

		m_thrdMMa.tr_open();
		m_thrdMMb.tr_open();

		
	}


public:

	virtual int OnMoonBoxThrdRun( WThrd & thrd_a, WThrd & thrd_b )
	{
		thrd_a.tr_wait();
		thrd_b.tr_wait();
		return 0; 
	}


	virtual void OnDeliverAb( SCake & ckTmp )
	{
		
		
		

		return;
	}


	virtual void OnDeliverBa( SCake & ckTmp )
	{
		return;
	}

}; 




X011_NAMESPACE_END


#endif






#ifndef X011__H_w_WMManSimpCellc_h
#define X011__H_w_WMManSimpCellc_h


X011_NAMESPACE_BEGIN


template< class Cellc_T = WTcpCellc >
class WMManSimpCellc : public WMoonMan< std::string >
{
public:
	Cellc_T  m_tcpc;

public:

	virtual tbool OnConn( CONN_AGENT_TYPET strAddr )
	{
		return m_tcpc.Conn( strAddr );
	}

	virtual void OnDisConn()
	{
		m_tcpc.DisConn();
		return;
	}

	virtual int OnRecv( SCake & ckDataBuf )
	{
		m_tcpc.recv_bin(ckDataBuf);
		return ckDataBuf.len();
	}

	virtual int OnSend( const SCake & ckDataBuf )
	{
		if( m_tcpc.send_bin( ckDataBuf ) )
		{
			return ckDataBuf.len();
		}
		return 0;
	}

}; 



X011_NAMESPACE_END


#endif






#ifndef X011__H_w_WMManSimpCells_h
#define X011__H_w_WMManSimpCells_h


X011_NAMESPACE_BEGIN




template< class Cells_T = WTcpCells >
class WMManSimpCells : public WMoonMan< WTcpListener & >
{
public:
	Cells_T m_tcps;

public:

	virtual tbool OnConn( CONN_AGENT_TYPET L )
	{
		return m_tcps.Conn(L);
	}

	virtual void OnDisConn()
	{
		m_tcps.DisConn();
		return;
	}

	virtual int OnRecv( SCake & ckDataBuf )
	{
		m_tcps.recv_bin(ckDataBuf);
		return ckDataBuf.len();
	}

	virtual int OnSend( const SCake & ckDataBuf )
	{
		if( m_tcps.send_bin( ckDataBuf ) )
		{
			return ckDataBuf.len();
		}
		return 0;
	}

}; 



X011_NAMESPACE_END


#endif






#ifndef X011__H_W_WTCPBACKOFFI2_H
#define X011__H_W_WTCPBACKOFFI2_H


X011_NAMESPACE_BEGIN


#ifdef VC6_COMPATIBLE_X011_

#else





class bu_backoffi2_protocol_t
{
public:
	bu_backoffi2_protocol_t(){};
	virtual ~bu_backoffi2_protocol_t(){;}

public:

	tbool Proc2( SCake & ckin, std::string & sout )
	{
		SNavass nvin;
		SNavass nvout;
		std::string s1, s2, s3, s4;

		if( ckin.len() == 0 )
		{
			return 0;
		}

		nvin.unserialize( ckin.mk_str() );
		nvout.clear();

		
		if( OnPreProc(nvin,nvout) )
		{
			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		if( s1 == "hello" )
		{
			nvout.let( "rc", "1" );
			nvout.let( "dt", SDte::GetNow().ReadString() );
			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("data");
		s3 = nvin.get("file");
		if( s1 == "write" && !s2.empty() && !s3.empty() )
		{
			SFile wf;
			SCake ck;

			ck.lets( s2 );
			ck.bs_de();

			if( !OnBeforeWriteBindFile( s3 ) ) goto L_ANS;

			wf.bind( s3 );

			nvout.let( "rc", (int)wf.write(ck,1) );

			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("file");
		s3 = nvin.get("offset");
		s4 = nvin.get("len");
		if( s1 == "read" && !s2.empty() && !s3.empty() && !s4.empty() )
		{
			SCake ck;
			SFile fl;
			std::string strFnData;

			if( !OnBeforeReadBindFile( s2 ) ) goto L_ANS;

			fl.bind( s2 );

			if( !fl.exists() || fl.len() <= (tsize)SStrf::satol(s3) )
			{
				nvout.let( "rc", "0" );
				goto L_ANS;
			}

			nvout.let( "rc", "1" );
			fl.read( ck, (tsize)SStrf::satol(s3) , SStrf::satol(s4) );
			strFnData = ck.len() ? ck.bs_en().buf() : "";
			nvout.let( "data", strFnData );

			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("file");
		if( s1 == "del" && !s2.empty() )
		{
			SCake ck;
			SFile fl;

			if( !OnBeforeDelBindFile( s2 ) ) goto L_ANS;

			fl.bind( s2 );
			if( fl.exists() )  fl.erase();
			nvout.let( "rc", "1" );

			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("file");
		s3 = nvin.get("len");
		if( s1 == "ds2" && !s2.empty() && !s3.empty() )
		{
			SCake ck;
			SFile fl;

			if( !OnBeforeDs2BindFile( s2 ) ) goto L_ANS;

			fl.bind( s2 );

			if( !fl.exists() )
			{
				nvout.let( "rc", "0" );
				goto L_ANS;
			}

			nvout.let( "rc", "1" );
			fl.read( ck );

			std::string s = ck.ds2( SStrf::satol(s3) );

			nvout.let( "data", s );

			goto L_ANS;
		}

		
		s1 = nvin.get("cmd");
		s2 = nvin.get("file");
		if( s1 == "run" && !s2.empty() )
		{
			int i = WFile::run_exe( s2.c_str() );
			nvout.let( "rc", "1" );
			nvout.let( "code", i );

			goto L_ANS;
		}

		
		nvout.let( "rc", "0" );
		nvout.let( "dt", SDte::GetNow().ReadString() );

L_ANS:
		nvout.serialize( sout );
		return 1;
	}

	
	virtual tbool OnPreProc( SNavass & nvin, SNavass & nvout )
	{
		return 0;
	}

	
	virtual tbool OnBeforeWriteBindFile( std::string & strfn ) 	{		return 1;	}
	virtual tbool OnBeforeReadBindFile( std::string & strfn ) 	{		return 1;	}
	virtual tbool OnBeforeDelBindFile( std::string & strfn ) 	{		return 1;	}
	virtual tbool OnBeforeDs2BindFile( std::string & strfn ) 	{		return 1;	}
};



template <
			class THRD_ELE_T = WThrd ,
			class BACKOFFI2_PROTOCOL_T = bu_backoffi2_protocol_t ,
			class TCPSERVER_TRAIT_T = WTcpCells
		>
class bu_backoffi2_ele_t : public THRD_ELE_T , public BACKOFFI2_PROTOCOL_T
{
public:
	TCPSERVER_TRAIT_T  m_tSvr;

public:
	bu_backoffi2_ele_t(){};
	virtual ~bu_backoffi2_ele_t(){ THRD_ELE_T::tr_destruct();}

public:
	virtual int tr_on_user_run()
	{
		WTcpDisConnable &tSvr(m_tSvr);
		SCake ckin;
		SNavass nvin;
		SNavass nvout;
		std::string sout;

		tSvr.recv_ln2( ckin, "\n" );

		if( this->Proc2( ckin, sout ) )
		{
			tbool rc;

			rc = tSvr.send_str( sout + "\n" );
			

			return 1;
		}
		else
		{
			WThrd::tr_sleep(1);
			return 0;
		}
	}
	
	
	
	
};



template	<
				class THRD_MGR_T = WThrd ,
				class THRD_ELE_T = WThrd ,
				class BACKOFFI2_PROTOCOL_T = bu_backoffi2_protocol_t ,
				class TCPSERVER_TRAIT_T = WTcpCells ,
				class TCPLSN_TRAIT_T = WTcpListener
			>
class bu_backoffi2_mgr_t : public WThrdMgr< bu_backoffi2_ele_t< THRD_ELE_T, BACKOFFI2_PROTOCOL_T >, THRD_MGR_T >
{
protected:
	typedef	 bu_backoffi2_ele_t< THRD_ELE_T, BACKOFFI2_PROTOCOL_T, TCPSERVER_TRAIT_T >   ThrEle_t;
public:
	TCPLSN_TRAIT_T  m_tLsn;
	

public:
	bu_backoffi2_mgr_t(){}

	virtual ~bu_backoffi2_mgr_t()
	{
		
		
		THRD_MGR_T::tr_destruct();
	}

public:
	
	
	

	virtual tbool OnMgrPrepare( ThrEle_t & t )	
	{
		if( !t.m_tSvr.Conn( m_tLsn ) )
			return 0;

		return 1;
	}

	static tbool Def( tuint16 port = 9900 ) 
	{
		bu_backoffi2_mgr_t< > *p;
		if( SStrf::newobjptr(p) && p->m_tLsn.Listen( (tuint16)port ) )
		{
			p->tr_openx();
			return 1;
		}
		return 0;
	}
};



class bu_backoffi2_client_base_t
{
public:
	WTcpDisConnable  * m_pCellc;

public:
	bu_backoffi2_client_base_t()
	{
		m_pCellc = NULL;
	}

	virtual ~bu_backoffi2_client_base_t()
	{
	}

public:

	
	tbool ReConn()
	{
		return OnReConn();
	}

	
	virtual tbool OnReConn()
	{
		m_pCellc = NULL;

		return 0;
	}

	
	virtual int OnGetReadBufLen()
	{
		return 64;
	}

	
	virtual int OnGetWriteBufLen()
	{
		return 64;
	}


	tbool Read( std::string strRemotefn, SCake & ckRtn, int iRetry = 9 ) 
	{
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		SCake ck;
		std::string strout;
		long iOffset;
		long iLen;

		ckRtn.redim(0);
		iLen = OnGetReadBufLen();

		if( m_pCellc == NULL )
		{
			if( !ReConn() )
			{
				
				m_pCellc = NULL;

				return 0;
			}
		}

		for( iOffset = 0; ; )
		{
			if( iRetry <= 0 )
			{
				return 0;
			}

			if( m_pCellc == NULL )
			{
				if( !ReConn() )
				{
					WThrd::tr_sleep(2);
					m_pCellc = NULL;

					iRetry--;
					continue;
				}
			}

			nvout.let( "cmd", "read" );
			nvout.let( "file", strRemotefn );
			nvout.let( "offset", SStrf::sltoa(iOffset) );
			nvout.let( "len", SStrf::sltoa(iLen) );

			nvout.serialize( strout );

			if( !m_pCellc->send_str( strout + "\n" ) )
			{
				m_pCellc->DisConn();
				m_pCellc = NULL;

				iRetry--;
				continue;
			}

			m_pCellc->recv_ln( ckin );

			if( ckin.len() == 0 )
			{
				m_pCellc->DisConn();
				m_pCellc = NULL;

				iRetry--;
				continue;
			}

			nvin.unserialize( ckin.mk_str() );

			if( nvin.get("rc") == "1" )
			{
				ck.lets( nvin.get("data") );
				ck.bs_de();
				ckRtn.FastAppend(ck);
				iOffset += (int)ck.len();

				continue;
			}

			if( nvin.get("rc") != "1" )
			{
				break;
			}

			
		} 

		if( iRetry <= 0 )
		{
			return 0;
		}

		if( m_pCellc != NULL )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
		}

		ckRtn.FastAppendEnd();

		return 1;
	}


	tbool Write( std::string strRemotefn, const SCake & ck )
	{
		std::vector< SCake > vck;
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		std::string strout;

		if( ck.len() == 0 ) return 0;

		SCakel::MkVecCake( ck, OnGetWriteBufLen(), vck, 0 );

		if( m_pCellc == NULL )
			if( !ReConn() )
			{
				
				m_pCellc = NULL;
				return 0;
			}


		nvout.let( "cmd", "del" );
		nvout.let( "file", strRemotefn );

		nvout.serialize( strout );

		if( !m_pCellc->send_str( strout + "\n" ) )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
		}
		else
			m_pCellc->recv_ln( ckin );

		for( int i = 0; i < (int)vck.size(); )
		{
			printf( "%d/%d\t", (int)i, (int)vck.size() );

			if( m_pCellc == NULL )
			{
				if( !ReConn() )
				{
					WThrd::tr_sleep(2);
					m_pCellc = NULL;

					continue;
				}
			}

			nvout.let( "cmd", "write" );
			nvout.let( "file", strRemotefn );
			nvout.let( "data", vck[i].bs_en().buf() );

			nvout.serialize( strout );

			if( !m_pCellc->send_str( strout + "\n" ) )
			{
				m_pCellc->DisConn();
				m_pCellc = NULL;

				continue;
			}

			m_pCellc->recv_ln( ckin );

			if( ckin.len() == 0 )
			{
				m_pCellc->DisConn();
				m_pCellc = NULL;

				continue;
			}

			nvin.unserialize( ckin.mk_str() );

			if( nvin.get("rc") == "1" )
			{
				i++;
				continue;
			}

			if( nvin.get("rc") != "1" )
			{
				break;
			}

			
		} 

		printf( "\n" );

		if( m_pCellc != NULL )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
		}

		return 1;
	}


	tbool Ds2( std::string strRemotefn , std::string & strrefRtnDs2_33 )
	{
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		std::string strout;

		if( m_pCellc == NULL )
			if( !ReConn() )
			{
				
				m_pCellc = NULL;
				return 0;
			}


		nvout.let( "cmd", "ds2" );
		nvout.let( "file", strRemotefn );
		nvout.let( "len", "33" );

		nvout.serialize( strout );

		if( !m_pCellc->send_str( strout + "\n" ) )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->recv_ln( ckin );

		if( ckin.len() == 0 )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->DisConn();
		m_pCellc = NULL;

		nvin.unserialize( ckin.mk_str() );

		if( nvin.get("rc") == "1" )
		{
			strrefRtnDs2_33 = nvin.get("data") ;
			return 1;
		}

		return 0;
	}


	tbool RunCmd( std::string strRemotefn, int *piRtn = NULL )
	{
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		std::string strout;

		if( m_pCellc == NULL )
			if( !ReConn() )
			{
				
				m_pCellc = NULL;
				return 0;
			}


		nvout.let( "cmd", "run" );
		nvout.let( "file", strRemotefn );

		nvout.serialize( strout );

		if( !m_pCellc->send_str( strout + "\n" ) )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->recv_ln( ckin );

		if( ckin.len() == 0 )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->DisConn();
		m_pCellc = NULL;

		nvin.unserialize( ckin.mk_str() );

		if( nvin.get("rc") == "1" )
		{
			if(piRtn)
				*piRtn = (int)SStrf::satol( nvin.get("code") );
			return 1;
		}

		return 0;
	}

	
	tbool Del( std::string strRemotefn )
	{
		SNavass nvin;
		SNavass nvout;
		SCake ckin;
		std::string strout;

		if( m_pCellc == NULL )
			if( !ReConn() )
			{
				
				m_pCellc = NULL;
				return 0;
			}

		nvout.let( "cmd", "del" );
		nvout.let( "file", strRemotefn );

		nvout.serialize( strout );

		if( !m_pCellc->send_str( strout + "\n" ) )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->recv_ln( ckin );

		if( ckin.len() == 0 )
		{
			m_pCellc->DisConn();
			m_pCellc = NULL;
			return 0;
		}

		m_pCellc->DisConn(); 
		m_pCellc = NULL;

		nvin.unserialize( ckin.mk_str() );

		if( nvin.get("rc") == "1" )
		{
			return 1;
		}

		return 0;
	}

};




template< class T >
class bu_backoffi2_client_cellc_t : public bu_backoffi2_client_base_t
{
public:
	
	T		   * m_ptc;
	std::string  m_strAddr;

public:
	bu_backoffi2_client_cellc_t()
	{
		m_ptc = NULL;
	}

	virtual ~bu_backoffi2_client_cellc_t()
	{
	}

public:
	virtual tbool OnReConn()
	{
		if( m_ptc->Conn(m_strAddr) )
		{
			m_pCellc = m_ptc;
			return 1;
		}
		else
		{
			m_pCellc = NULL;
			return 0;
		}
	}
};


class bu_backoffi2_client_t : public bu_backoffi2_client_cellc_t<WTcpCellc>
{
public:
	virtual ~bu_backoffi2_client_t(){}

	
	virtual int OnGetReadBufLen()
	{
		return 2048;
	}

	
	virtual int OnGetWriteBufLen()
	{
		return 1024;
	}
};



class bu_backoffi2_HWclient_t : public bu_backoffi2_client_cellc_t<HWPoorCellc>
{
public:
	virtual ~bu_backoffi2_HWclient_t(){}

	
	virtual int OnGetReadBufLen()
	{
		return 40;
	}

	
	virtual int OnGetWriteBufLen()
	{
		return 40;
	}
};


#endif


X011_NAMESPACE_END


#endif



#ifndef X011__H_w_w_WKeyinput_t_h
#define X011__H_w_w_WKeyinput_t_h


X011_NAMESPACE_BEGIN


#ifdef VC6_COMPATIBLE_X011_

#else


template < class THREADBASE_T = WThrd, class THREADBASE_T_toutman = WThrd >
class WKeyinput : public WIdleThrd< std::string > , public THREADBASE_T
{
public:

private:
	class TimeoutMan : public THREADBASE_T_toutman
	{
	public:
		WKeyinput * m_pFather;

		TimeoutMan(){ m_pFather = NULL; }

		virtual ~TimeoutMan(){ THREADBASE_T_toutman::tr_destruct(); }

		virtual int tr_on_user_run()
		{
			if( m_pFather == NULL || m_pFather->m_timeout_dSec <= 0.001 )
			{
				WThrd::tr_sleepu( 1.2 );
				return 1;
			}
			WThrd::tr_sleepu( m_pFather->m_timeout_dSec );
			if( m_pFather) m_pFather->PostTask( "<timeout>" );
			return 1;
		}
	};

	std::string  m_strkeyaddress;

	WTcpListener  m_tLsn;
	WTcpCells     m_ts;
	WTcpCellc     m_tc;
	WCrsc					  m_KeyBufLck;
	std::list< std::string >  m_KeyBuf;
	volatile WCrsc			* m_pKeyBufTempLock;

	volatile double m_timeout_dSec;

	TimeoutMan	*m_pto;

public:
	WKeyinput()
	{
		m_pto = new TimeoutMan;

		m_pKeyBufTempLock = NULL;
		m_timeout_dSec = 0.0;
	}

	virtual ~WKeyinput()
	{
		m_pto->tr_shouldbrk();
		m_pto->m_pFather = NULL;
		delete m_pto;

		THREADBASE_T::tr_destruct();
	}

public:
	
	tbool KeyiInit( int iPort , int *pPortOut = NULL ) 
	{
		WCrsc aLock( &m_KeyBufLck );
		int iPortOut;

		m_KeyBuf.clear();

		for( int i = 0; i < 9999; i++ )
		{
			m_strkeyaddress = "127.0.0.1:" + SStrf::sltoa( iPortOut = (i + iPort) );

			if( m_tLsn.Listen( m_strkeyaddress ) )
			{
				this->tr_open();

				this->PostTask( "<connect>" );
				WThrd::tr_sleepu(0.61);

				m_pto->m_pFather = this;
				m_pto->tr_open();
				

				if( pPortOut ) *pPortOut = iPortOut;
				return 1;
			}
		}

		return 0;
	}

	
	void SetTimeout( double dSec = 0.0 )
	{
		m_timeout_dSec = dSec;
	}

	
	void Clear()
	{
		WCrsc aLock( &m_KeyBufLck );
		m_KeyBuf.clear();
	}

	
	
	


	std::string GetKey( tbool biWithWait = 1 )
	{
		std::string s;

		do
		{
			if(1)
			{
				volatile WCrsc aLock( &m_KeyBufLck );

				if( m_KeyBuf.empty() )
				{
					if( biWithWait )
						this->PostTask( "<lock>", 0, 1 );
					else
						return "";
				}
				else
				{
					s = *(m_KeyBuf.begin());
					m_KeyBuf.pop_front();
					break;
				}
			}

			WThrd::tr_sleep( 0, 0.25 );
			continue;

		}while(1);

		return s;
	}

	virtual void OnRunTask( std::string t )
	{
		if( t.empty() )
		{
			return;
		}

		if( t == "<connect>" )
		{
			this->m_tc.Conn( m_strkeyaddress );
			return;
		}

		
		this->m_tc.send_str( t + "\n" );
	}

	
	virtual int tr_on_user_run()
	{
		if( !this->m_ts.Conn( this->m_tLsn ) )
		{
			WThrd::tr_sleep(1);
			return 1;
		}

		while(1)
		{
			SCake ck;
			std::string s1;

			if( this->tr_isShouldBrk() )
				break;

			m_ts.recv_ln( ck );
			ck.mk_str(s1);

			if( s1.empty() )
			{
				this->m_ts.DisConn();
				this->PostTask( "<connect>", 1, 1 );

				return 1;
			}

			if( s1 == "<timeout>" )
			{
				if( m_pKeyBufTempLock == NULL )
				{
					m_pKeyBufTempLock = new WCrsc( &m_KeyBufLck );

					m_KeyBuf.push_back( "" );

					delete m_pKeyBufTempLock;
					m_pKeyBufTempLock = NULL;

					continue;
				}

				if( m_pKeyBufTempLock != NULL )
				{
					m_KeyBuf.push_back( "" );

					delete m_pKeyBufTempLock;
					m_pKeyBufTempLock = NULL;

					continue;
				}
			}

			if( s1 == "<lock>" )
			{
				if( m_pKeyBufTempLock == NULL )
				{
					m_pKeyBufTempLock = new WCrsc( &m_KeyBufLck );
					continue;
				}

				if( m_pKeyBufTempLock != NULL )
				{
					continue;
				}
			}

			
			if( m_pKeyBufTempLock == NULL )
			{
				m_pKeyBufTempLock = new WCrsc( &m_KeyBufLck );

				m_KeyBuf.push_back( s1 );

				delete m_pKeyBufTempLock;
				m_pKeyBufTempLock = NULL;

				continue;
			}

			
			if( m_pKeyBufTempLock != NULL )
			{
				m_KeyBuf.push_back( s1 );

				delete m_pKeyBufTempLock;
				m_pKeyBufTempLock = NULL;

				continue;
			}

			
			continue;
		}

		WThrd::tr_sleep(1);
		return 1;
	}

};

#endif	




X011_NAMESPACE_END

#endif




#ifndef WLoUTIL__X013__H
#define WLoUTIL__X013__H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>


namespace wlo {


class gmr;
class wl_stru_gmr;
typedef gmr Gmr;





typedef		 char				   wlint8;
typedef		 unsigned char		   wluint8;
typedef		 short				   wlint16;
typedef		 unsigned short		   wluint16;
typedef		 long				   wlint32;
typedef		 unsigned long		   wluint32;
typedef		 int (*wlpfucb) (wlint8 *, wlint8 *);


#ifndef WL_STRU_STRF_H
#define WL_STRU_STRF_H


class wl_stru_strf {


public:

	 wl_stru_strf(){;}

	~wl_stru_strf(){;}


	static wluint16 mk_U16(wluint8 c1, wluint8 c2) 
	{
	   wluint16 ilow,ihigh;
	   ilow =  (wluint16)c1;
	   ihigh = (wluint16)c2;
	   ihigh <<= 8;
	   return ihigh + ilow;
	}

	static wluint32 mk_U32(wluint8 c1, wluint8 c2, wluint8 c3, wluint8 c4)
	{
	   return mk_U32( mk_U16(c1,c2), mk_U16(c3,c4) );
	}

	static wluint32 mk_U32(wluint16 i1 , wluint16 i2 )
	{
	   wluint32 ilow,ihigh;
	   ilow =(wluint32)i1;
	   ihigh=(wluint32)i2;
	   ihigh <<= 16;
	   return ihigh + ilow;
	}


	static wlint8 *mk_xor(wlint8 *s, wlint32 a_len, wlint8 x)
	{
		wlint32 i;
		if(s==NULL) return s;
		if(a_len==0) return s;
		for(i=0;i<a_len;i++) s[i] ^= x;
		return s;
	}


	static wlint32 str_chksum(wlint8 *s)
	{
		return str_chksum( s, str_len(s) );
	}


	static wlint32 str_chksum(wlint8 *s, wlint32 a_len)
	{
		wlint32 i,j;
		if(s==NULL) return 0;
		if(strlen(s)==0) return 0;
		for(i=0,j=0;i<a_len;i++){
			j=j+(wluint8)s[i]+(i+1);
			j &= 0x7FFFffff;
		}
		return (wlint32)j;
	}


	static int str_ishex(wlint8 c)
	{
		return  (c>='0'&&c<='9')||(c>='A'&&c<='F')||(c>='a'&&c<='f');
	}

	static int str_ishex(wlint8 *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!str_ishex(*s)) return 0;
		return 1;
	}


	static int str_isdec(wlint8 c)
	{
		return  (c>='0'&&c<='9') ;
	}

	static int str_isdec(wlint8 *s)
	{
		if(s==NULL) return 0;
		for(;*s;s++) if(!str_isdec(*s)) return 0;
		return 1;
	}


	static wlint32 str_len(wlint8 *s)
	{
		if(s==NULL) return 0;
		return (wlint32)strlen(s);
	}




	static wlint8 *str_ltoa(wlint32 i, wlint8 *buf)	{ return str_ltoa(i,10, buf) ;}


	static wlint8 *str_ltoa(wlint32 i, int radix, wlint8 *buf)
	{
		static wlint8 c[33];
		
		return (*wl::SClib::p_ltoa()) (i, buf==NULL?c:buf, radix);
	}


	static wlint32 str_atol(wlint8 *s)
	{
		if(s==NULL) return 0;
		return (wlint32)::atol(s);
	}


	static double str_atof(wlint8 *s)
	{
		if(s==NULL) return 0.0;
		return (double)::atof(s);
	}


    static int str_cmpi(wlint8 *a,wlint8 *b)
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		wlint8 *t1,*t2, c1,c2;
		wlint32 i;
		t1 = a;
		t2 = b;
		for(i=0;t1[i]&&t2[i];i++){
			c1=t1[i];
			c2=t2[i];
			if(c1>='a'&&c1<='z')c1+=('A'-'a');
			if(c2>='a'&&c2<='z')c2+=('A'-'a');
			if(c1!=c2)return c1-c2;
		}
		return t1[i]-t2[i];
	}


	static int str_cmpn(wlint8 *a,wlint8 *b, wlint32 count )
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		return ::strncmp(a,b,(size_t)count);
	}


	static int str_cmp(wlint8 *a,wlint8 *b)
	{
		if(a==NULL&&b==NULL) return 0;
		if(a==NULL&&b!=NULL) return -1;
		if(a!=NULL&&b==NULL) return 1;
		return ::strcmp(a,b);
	}


	static wlint8 *str_ucase(wlint8 *s)
	{
		wlint32 i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='a'&&s[i]<='z')s[i] = s[i] -'a' + 'A' ;
		}
		return s;
	}

	static wlint8 *str_lcase(wlint8 *s)
	{
		wlint32 i;
		if(s==NULL) return NULL;
		for(i=0;s[i]!=0;i++){
			if(s[i]>='A'&&s[i]<='Z')s[i] = s[i] -'A' + 'a' ;
		}
		return s;
	}


	static wlint8 *str_poslast(wlint8 *s, wlint32 offset2left=0) 
	{
		if(!s||!*s) return s;
		wlint32 i,j ;
		j=str_len(s);
		i = j - 1 - offset2left ;
		return s+(i<0?0:i);
	}


	static wlint32 str_instr(wlint8 *s, wlint8 *substr)
	{													
		wlint8 *t;
		if(!s||!substr||!(*s)||!(*substr)) return -1;
		t = strstr(s,substr);
		if(t==NULL) return -1;
		return (wlint32)(t - s) ;
	}

	static wlint32 str_instr(wlint8 *s, wlint8 subc)
	{
		wlint8 t[2];
		t[0]=subc;
		t[1]=0;
		return str_instr(s,t) ;
	}


	static wlint32 str_instri(wlint8 *s, wlint8 *substr)
	{
		wlint8 *t1,*t2;
		wlint32 i;

		if(s==NULL) return -1;
		if(substr==NULL) return -1;
		t1 = (wlint8 *)malloc( str_len(s)		+ 1 );
		t2 = (wlint8 *)malloc( str_len(substr)	+ 1 );
		if(t1==NULL) return -1;
		if(t2==NULL) { free(t1); return -1; }
		strcpy(t1,s);
		strcpy(t2,substr);
		str_ucase(t1);
		str_ucase(t2);
		i=str_instr(t1,t2);
		free(t1);
		free(t2);
		return i ;
	}


	static wlint8 *str_replchar(wlint8 *s, wlint8 c1, wlint8 c2)
	{
		return str_replchar(s, str_len(s), c1, c2);
	}


	static wlint8 *str_replchar(wlint8 *s, wlint32 len, wlint8 c1, wlint8 c2)
	{
		wlint32 i;
		for(i=0;s&&i<len;i++) {
			if(s[i]==c1) s[i]=c2;
		}
		return s;
	}


	static wlint8 *str_rev(wlint8 *s)
    {
		wluint32 u;
		wlint32  x, y, i;
		wlint32  a, b;
		u = (wluint32)str_len(s);
		u >>= 1;
		x = u;
		y = str_len(s) - 1;
        for(i=0;i<x;i++) {
			a = i;
			b = y - i;
			
			s[a] ^= s[b];
			s[b] ^= s[a];
			s[a] ^= s[b];
		}
		return s;
    }


	static wlint8 *str_rtrim(wlint8 *s, wlint8 c_my_space='\0')
	{
		wlint32 i,j ;
		j=str_len(s);
		for(i=j-1;i>=0;i--) {
			if(s[i]==0x09||s[i]==' '||s[i]==c_my_space)
				s[i]=0;
			else
				break;
		}
		return s;
	}


	static wlint8 *str_ltrim(wlint8 *s, wlint8 c_my_space='\0')
	{
		return  str_rev(str_rtrim(str_rev(s), c_my_space) ) ;
	}


	static wlint8 *str_trim(wlint8 *s, wlint8 c_my_space='\0')
	{
		return  str_ltrim(str_rtrim(s,c_my_space), c_my_space) ;
	}


	static wlint8 *str_left(wlint8 *s, wlint32 n)
	{
		if(n>(wlint32)str_len(s)||n<0) return s;
		s[n]=0;
		return s;
	}


	static wlint8 *str_right(wlint8 *s, wlint32 n)
	{
		return str_rev(str_left(str_rev(s), n));
	}


	static wlint8 *str_mid(wlint8 *s, wlint32 n, wlint32 n2)
	{
		str_right(s, str_len(s) - n );
		str_left(s, n2);
		return s;
	}


	static int str_seq_sort( const void *arg1, const void *arg2 )
	{   
		wlint8 *t1,*t2 ;
		wlint32 i;
		t1 = * ( char ** ) arg1;
		t2 = * ( char ** ) arg2;
		i=str_len(t1)-str_len(t2);

		if(i) return i;
		return str_cmp(t1,t2);
	}


	static wlint8 *str_seq_dirno(void)
	{
		static char t[]=
		 "0123456789ACEFHKLMPQSTUWXYZ"; 
		return t;
	}


	
	
	
	
	
	
	
	
	
	
	
	

	static wlint8 *str_seq(wlint8 *buf=NULL)
	{
		static wlint8 s[34]={0,0,0,0,0,0,0};
		return str_seq(buf==NULL?s:buf, "", 0);
	}

	static wlint8 *str_seq(wlint8 *s_num, const wlint8 *s_symbset1, int isfix=0)
	{
		char *s_symbset=(char*)s_symbset1;
		
		static wlint8 c[1];
		c[0]=0;
		if(s_num==NULL) return c;
		
		if(str_len(s_symbset)<2) s_symbset = str_seq_dirno();

		wlint16 *lia , ulia;
		wlint32 i,j,k;

		lia = (wlint16 *)malloc( (str_len(s_num) + 1)*sizeof(wlint16) );

		if(!(*s_num)) {
			s_num[0]=s_symbset[0];
			s_num[1]=0;
		}

		j = str_len(s_num) ;
		for(i=0;i<j;i++)
		{
			lia[i]=(wlint16)str_instr(s_symbset, s_num[i]);
			if(lia[i]==-1) lia[i]=0;
		}

		lia[j-1] ++;
		k = str_len(s_symbset) ;
		ulia=0;
		for(i=j-1;i>=0;i--)
		{
			if(lia[i]>=k){
				lia[i]-=(wlint16)k;
				if(i>0) lia[i-1]++; else ulia++;
			}
		}

		for(i=0;i<j;i++)
		{
			s_num[i]=s_symbset[lia[i]];
		}

		if((!isfix)&&ulia){
			str_rev(s_num);
			s_num[j]=s_symbset[ulia];
			s_num[j+1]=0;
			str_rev(s_num);
		}

		free(lia);
		return s_num;
	}


	static wlint8 bstr_esc(wlint8 cc)
	{
		if(cc!=0) return cc;
		return 'b';
	}

	static int bstr_in_set(wlint8 c, wlint8 ac_bstresc)
	{
		if(c==bstr_esc(ac_bstresc)) return 0; 
		if(c>='a'&&c<='z') return 1;
		if(c>='0'&&c<='9') return 1;
		if(c>='A'&&c<='Z') return 1;
		return 0;
	}


	static int bstr_iswhole(wlint8 *s, wlint8 ac_bstresc=0)
	{
		wlint32 i;
		switch (i=str_len(s))
			{
			case 0:
				return 1;
			case 1:
				return s[0]!=bstr_esc(ac_bstresc);
			case 2:
				if(s[0]==bstr_esc(ac_bstresc)&&str_ishex(s[1])) return 0;
				return bstr_iswhole(&s[1]);
			default:
				s=s+i-3;
				if(s[0]==bstr_esc(ac_bstresc)&&str_ishex(s[1])&&str_ishex(s[2])) return 1;
				return bstr_iswhole(&s[1]);
			}
	}


	
	static wlint32 bstr_en_size(wlint8 *s,
								wlint32 len,
								wluint8 probability=0 ,
								wlint8 ac_bstresc=0 ,
								int(*apf1)(wlint8,wlint8)=bstr_in_set
								)
	{
		if(s==NULL) return 0;
		if(probability) return len*3+1;

		wlint32 i,j,k;
		for(i=0,j=len,k=0;i<j;i++)
			k += (*apf1)(s[i],ac_bstresc)?1:3;
		return k+1; 
	}
	


	static wlint8 *bstr_en( wlint8 *s  ,
							wlint32 len,
							wluint8 probability=0 ,
							wlint8 ac_bstresc=0 ,
							int(*apf1)(wlint8,wlint8)=bstr_in_set
							)
	{
		static wlint8 c[1];
		c[0]=0;
		wlint8 *t1;
		if(s==NULL) return c;
		t1 = (wlint8 *)malloc( len );
		memcpy(t1,s,len);
		bstr_en(t1,len,s,probability,ac_bstresc,apf1);
		free(t1);
		return s ;
	}

	static wlint8 *bstr_en( wlint8 *s  ,
							wlint32 len,
							wlint8 *dest,
							wluint8 probability=0 ,
							wlint8 ac_bstresc=0 ,
							int(*apf1)(wlint8,wlint8)=bstr_in_set
							)
	{
		static wlint8 c[1];
		c[0]=0;
		if(s==NULL||dest==NULL) return c;
		wlint32 i,j,k,l;
		int rc;

		for(i=0,j=len,k=0;i<j;i++){

			rc = 0;

			do {
				if( !(*apf1)(s[i],ac_bstresc) ) { 
					rc = 1;
					break;
				}

				if( probability	&& ((rand()&0xFF)<probability) ){ 
					rc = 1;
					break;
				}

				dest[k]=s[i];         
				k++;

			}while(0);

			if(rc) {    
				l=(wluint8)s[i];
				sprintf(dest+k, "%c%02X", bstr_esc(ac_bstresc), (unsigned int)l);
				k+=3;
			}
		}
		dest[k]=0;
		return dest;
	}


	static wlint32 bstr_de_size( wlint8 *s ,
								 wlint8 ac_bstresc=0
								)
	{
		if(s==NULL) return 0;
		wlint32 i,j,k;
		for(i=0,j=str_len(s),k=0;i<j; )
			if(	(i+2<j)					    &&
				s[i]==bstr_esc(ac_bstresc)	&&
				str_ishex(s[i+1])			&&
				str_ishex(s[i+2])      ) {
				k++;
				i+=3;
			}else{
				i++;
				k++;
			}
		return k;
	}


	static wlint8 *bstr_de(wlint8 *s, wlint8 ac_bstresc=0)
	{
		return bstr_de(s,s,ac_bstresc);
	}


	static wlint8 *bstr_de(wlint8 *s, wlint8 *dest, wlint8 ac_bstresc=0)
	{
		static wlint8 c[1];
		c[0]=0;
		if(s==NULL||dest==NULL) return c;
		wlint32 i,j,k;
		wlint32 a1,a2;

		wlint8 ss[2];
		ss[1]=0;

		for(i=0,j=str_len(s),k=0;i<j; ) {
			if(	(i+2<j)		&&
				s[i]==bstr_esc(ac_bstresc)	&&
				str_ishex(s[i+1])	&&
				str_ishex(s[i+2])	 ) {

				ss[0]=s[i+1];
				str_ucase(ss);
				a1 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) * 16 ;

				ss[0]=s[i+2];
				str_ucase(ss);
				a2 = (ss[0] <= '9' ? ss[0] - '0' : ss[0] - 'A' + 10) ;

				*(wluint8 *)(dest+k) = (wluint8)(a1+a2);
				k++;
				i+=3;
			}else{
				dest[k] = s[i];
				k++;
				i++;
			}
		}

		
		dest[k]='\0';

		return dest;
	}


	static wlint8 *bstr_b2u(wlint8 *s, wlint8 ac_bstresc=0)
	
	
	{
		wlint8 *t;
		for(t=s;t&&*t;t++){
			if(*t==bstr_esc(ac_bstresc)) *t='%';
			if(*t==' ') *t='+';
		}
		return s;
	}

	static wlint8 *bstr_u2b(wlint8 *s , wlint8 ac_bstresc=0)
	{
		wlint8 *t;
		for(t=s;t&&*t;t++){
			if(*t=='%') *t=bstr_esc(ac_bstresc);
			if(*t=='+') *t=' ';
			if(*t=='?') *t=' ';
		}
		return s;
	}


}; 

#endif


#ifndef WL_STRU_LIST_H
#define WL_STRU_LIST_H

class wl_stru_list {

private:
	wlint8 *lv_lang_wl_stru_list_tp;
	wlint8 *lv_cf_add_t;
	wlint8 *lv_cf_add2_t ;
	wlint32 lv_cf_add2_i;
	wlint8 *lv_cf_add3_t ;
		wlint8 *lv_cf_import_strarr_t, lv_cf_import_strarr_c, lv_cf_import_strarr_c2, *lv_cf_import_strarr_lastt;
		wlint32 lv_cf_import_strarr_i, lv_cf_import_strarr_ti, lv_cf_import_strarr_datalen, lv_cf_import_strarr_seplen;
		wlint32 lv_cf_modi_i;
		int lv_cf_modi_rc;
		wlint8 *lv_cf_modi_t ;
        wlint8 *lv_cf_swap_tp;
		wlint32 lv_cf_swap_j;
		int lv_cf_del_rc;
		wlint32 lv_cf_del_i;
		wlint8 *lv_cf_deltop_tp;
        wlint32 lv_cf_rev_a,lv_cf_rev_b;
		wlint32 lv_cf_rev_x,lv_cf_rev_y,lv_cf_rev_i;
		wluint32 lv_cf_rev_u;
        wlint8 *lv_cf_rev_tp;
        wlint32 lv_cf_sel_low,lv_cf_sel_high,lv_cf_sel_mid,lv_cf_sel_x;
		class wl_stru_list *lv_cf_output_lp;
        wlint32 lv_cf_output_i;
        FILE *lv_cf_output_fp;
		class wl_stru_list *lv_cf_output2_lp;
        wlint32 lv_cf_output2_i;
        FILE *lv_cf_output2_fp;

        wlint8 *lv_init_tp;
        wlint8 *lv_push_tp;
        wlint8 **lv_push_tt;
        wlint32 lv_push_tl,lv_push_ttl;
		wlint32 lv_count_i,lv_count_c;
		wlint8 *lv_chg_tp;
        wlint8 *lv_lcf_free_tp;
        wlint32 lv_cf_qsel_low,lv_cf_qsel_high,lv_cf_qsel_mid,lv_cf_qsel_x;


protected:

    struct  {
        wlint32 depth;
        wlint32 sp;
        wlint8 **stk;
    } str_stack;

	int initdepth ;

	struct {
		int (*cmpf)(const void *,const void *);
		int issorted;							
	} sortstatus;


public:

	int (*iv_mycmp)(const void *,const void *);	

	int iv_fast_del;


public:

    static int cf_sortA_ss( const void *arg1, const void *arg2 )
	{   
		
		return wl_stru_strf::str_cmp( * ( char ** ) arg1, * ( char ** ) arg2 );
	}

	static int cf_sortA_ssi( const void *arg1, const void *arg2 )
	{   
		return wl_stru_strf::str_cmpi( * ( char ** ) arg1, * ( char ** ) arg2 );
	}

	static int cf_sortA_si( const void *arg1, const void *arg2 )
	{   
		return wl_stru_strf::str_atol( *(wlint8 **)arg1) - wl_stru_strf::str_atol( *(wlint8 **)arg2);
	}


	static int cf_sortA_ii( const void *arg1, const void *arg2 )
	{   
		return **(wlint32 **)arg1 - **(wlint32 **)arg2;
	}


public:

	wl_stru_list()	{			wl_stru_list_init_depth(13);	  }
	wl_stru_list(int depth)	{	wl_stru_list_init_depth(depth);    }

    void wl_stru_list_init_depth(int depth)
    {
		initdepth= depth;
        str_stack.stk=NULL;
        str_stack.sp=0;
        init(initdepth);

		cf_setsortf(cf_sortA_ss);
		iv_fast_del = 0;

		sortstatus.cmpf=iv_mycmp;
		sortstatus.issorted=0;
    }

    ~wl_stru_list()
    {
        if(str_stack.stk==NULL) return;
        for(;!isempty();){
            if(isempty()) return ;
            str_stack.sp--;
            lv_lang_wl_stru_list_tp=str_stack.stk[str_stack.sp];
            free(lv_lang_wl_stru_list_tp);
        }
        if(str_stack.stk!=NULL) {
            free(str_stack.stk);
            str_stack.stk=NULL;
        }
    }


	void cf_setsortf(int (*cmpf)(const void *,const void *))
	{
		iv_mycmp = cmpf;
	}


	int cf_copy_str(wl_stru_list *dest, wlint8 *ss_head=NULL, wlint8 *ss_tail=NULL)
	{
		wlint8 *t;
		wlint32 i;
		if(!dest) return 0;
		for(i=0;i<cf_howmany();i++) {
			
			if(-1==dest->cf_add( wl_stru_strf::str_len(cf_read(i))+wl_stru_strf::str_len(ss_head)+wl_stru_strf::str_len(ss_tail)+1 ))
				return 0;
			t = dest->cf_readtop();
			t[0]=0;
			if(ss_head&&*ss_head) ::strcpy(t, ss_head);
			::strcat(t, cf_read(i));
			if(ss_tail&&*ss_tail) ::strcat(t, ss_tail);
		}
		return 1;
	}


	int cf_copy_bstr(wl_stru_list *dest, int want_sz=1, wluint8 probability=0)
	{
		wlint32 i,j,len,sourcelen;
		j=cf_howmany();
		for(i=0;i<j;i++) {
			sourcelen = wl_stru_strf::str_len(cf_read(i));
			len = wl_stru_strf::bstr_en_size(cf_read(i), (want_sz?1:0)+sourcelen, probability);
			if(-1==dest->cf_add(len)) return 0;
			wl_stru_strf::bstr_en(cf_read(i), (want_sz?1:0)+sourcelen, dest->cf_readtop(), probability);
		}
		return 1;
	}


	int cf_plot(wlint32 a_idx) 
	{
		wlint32 i;
		if(a_idx<=cf_howmany()-1) return 1;
		for(i=cf_howmany();i<=a_idx;i++) if(-1==cf_add("")) return 0;
		return 1;
	}


	int cf_collect(void) { return cf_collect(""); }

	int cf_collect(const wlint8 *a_sep1) 
	{
		char*a_sep=(char*)a_sep1;
		wlint32 i,j,k;
		wlint32 a;
		wlint8 *t;

		a = wl_stru_strf::str_len( a_sep );
		j = howmany_AA();
		for(k=i=0;i<j;i++) {
			k += wl_stru_strf::str_len( cf_read(i) );
			k += a;
		}
		k++;
		if(-1==cf_add(k)) return 0;
		t = cf_readtop();
		for(i=0;i<j;i++) {
			strcpy(t, cf_read(i) );
			t += wl_stru_strf::str_len( cf_read(i) );
			strcpy(t, a_sep==NULL?"":a_sep );
			t += a;
		}
		*t='\0';

		if(j!=0) {
			i=cf_swap(0,j);
			if(!i) return 0;
		}
		while(howmany_AA()>1){
			cf_deltop();
		}
		return 1;
	}


	wlint32 cf_add(wlint8 c1, wlint8 c2)
	{
		wlint8 s[3];
		s[0]=c1;
		s[1]=c2;
		s[2]=0;
		return cf_add(s);
	}


	wlint32 cf_add(const wlint8 *s1)
	{
		wlint8 *s=(char*)s1;

			sortstatus.issorted=0;

		lv_cf_add_t = push(s, wl_stru_strf::str_len(s) + 1, 1 );

		if(lv_cf_add_t==NULL) return -1;
		return str_stack.sp - 1;
	}


	wlint32 cf_add(wlint8 *s, wlint32 a_size)
	{
			sortstatus.issorted=0;

		lv_cf_add2_t = push(s, a_size, 0 );

		if(lv_cf_add2_t==NULL) return -1;

		for(lv_cf_add2_i=0;lv_cf_add2_i<a_size;lv_cf_add2_i++) {
		    lv_cf_add2_t[lv_cf_add2_i] = s[lv_cf_add2_i];
		}
		return str_stack.sp - 1;
	}


	wlint32 cf_add(wlint32 a_size)
	{
			sortstatus.issorted=0;

		lv_cf_add3_t = push("", a_size, 0 );

		if(lv_cf_add3_t==NULL) return -1;
		return str_stack.sp - 1;
	}


	wlint32 cf_adda(wlint32 i) 
	{
		wlint8 c[33];
		return cf_add(wl_stru_strf::str_ltoa(i,c) );
	}

	wlint32 cf_addf(double e) 
	{
		wlint8 c[44];
		sprintf(c, "%f", e);
		return cf_add(c);
	}


	wlint32 cf_add32(wlint32 l) 
	{
		return cf_add( (wlint8 *)(&l), sizeof(wlint32) );
		
	}


	wlint8 *cf_read(wlint32 idx) 
	{
        if(idx<0) return NULL;
        if(idx>=howmany_AA()) return NULL;
        if(isempty()) return NULL;
        return  str_stack.stk[idx];
    }


	wlint8 *cf_readtop(void)
	{
		return cf_read( cf_howmany() - 1 );
	}


	wlint32 cf_maxlen(void)
	{
		wlint32 i,j,k,m;
		k=0;
		j=howmany_AA();
		for(i=0;i<j;i++) {
			m=wl_stru_strf::str_len( cf_read(i));
			if(k<m)k=m;
		}
		return k;
	}


	wlint32 cf_sumlen(void)
	{
		wlint32 i,j,k,m;
		k=0;
		j=howmany_AA();
		for(i=0;i<j;i++) {
			m=wl_stru_strf::str_len( cf_read(i));
			k += m;
		}
		return k;
	}


	int cf_import_strarr(wlint8 *as_data, wlint8 ac_sep, int opt_is_token)
	{
		wlint8 t[2];
		t[0]=ac_sep;
		t[1]=0;
		return cf_import_strarr(as_data,t,opt_is_token) ;
	}


	int cf_import_strarr(wlint8 *as_data, wlint8 *as_sep, int opt_is_token)
	{

		if(wl_stru_strf::str_len(as_sep)==1)
			return cf_import_strarr_v1(as_data,as_sep,opt_is_token);

		class wl_stru_list *pA;
		class wl_stru_list *pB;
		wlint32  n,m,i,j,k, b1, b2;
		wlint8 c1 , *t;

		m = i = j = 0;
		n = wl_stru_strf::str_len(as_data);
		k = wl_stru_strf::str_len(as_sep);
		pA = new class wl_stru_list;
		pB = new class wl_stru_list;

		t = (wlint8 *)malloc(n+1);
		if(!t) return 0;
		if(as_data) as_data = ::strcpy(t,as_data);

		do {
			if(m>=n) break;
			i = wl_stru_strf::str_instr(as_data + m, as_sep);
			if(i<0)  break;
			i += m;
			m = i;

			pA->cf_add32(i);
			j ++;
			m += k;

		} while(1);

		b1 = 0 ; 
		b2 = j - 1 ; 

		j = 0;
		pB->cf_add32(j);
		for(i=b1;i<=b2;i++){
			j = *(wlint32 *)pA->cf_read(i);
			pB->cf_add32(j);
			pB->cf_add32(j+k);
		}
		pB->cf_add32(n );

		

		for(i=0;i<pB->cf_howmany();i+=2) {
			m = *(wlint32 *)pB->cf_read(i);
			n = *(wlint32 *)pB->cf_read(i+1);
			k = n - m;
			t = as_data + m;
			c1 = t[k];
			t[k]=0;

			
			if(opt_is_token&&k==0){
				;
			}else
				this->cf_add(t);

			t[k]=c1;
		}

		free(as_data);
		delete pA;
		delete pB;

		return 1;
	}


	int cf_import_strarr_v1(wlint8 *as_data, wlint8 *as_sep, int opt_is_token)
    {
		if(as_data==NULL) return 0;
		if(as_sep==NULL) return 0;
		if(as_data[0]==0&&!opt_is_token) return 1;

			sortstatus.issorted=0;

		lv_cf_import_strarr_datalen = wl_stru_strf::str_len(as_data);
		lv_cf_import_strarr_seplen =  wl_stru_strf::str_len(as_sep);
		lv_cf_import_strarr_t = (char *)malloc( lv_cf_import_strarr_datalen + lv_cf_import_strarr_seplen * 2 + 3 );
		if(lv_cf_import_strarr_t==NULL) return 0;
		strcpy(lv_cf_import_strarr_t, as_data);
		strcat(lv_cf_import_strarr_t, as_sep);

		if(as_sep[0]==0) {
			cf_add(lv_cf_import_strarr_t);
			free(lv_cf_import_strarr_t);
			return 1;
		}

		for(lv_cf_import_strarr_lastt=lv_cf_import_strarr_t,lv_cf_import_strarr_i=0;lv_cf_import_strarr_i<lv_cf_import_strarr_datalen+lv_cf_import_strarr_seplen;){
			lv_cf_import_strarr_ti = lv_cf_import_strarr_i+lv_cf_import_strarr_seplen;
			lv_cf_import_strarr_c = lv_cf_import_strarr_t[lv_cf_import_strarr_ti];
			lv_cf_import_strarr_t[lv_cf_import_strarr_ti] = 0;
			if(!strcmp(lv_cf_import_strarr_t+lv_cf_import_strarr_i,as_sep)){ 
				lv_cf_import_strarr_c2= lv_cf_import_strarr_t[lv_cf_import_strarr_i];
				lv_cf_import_strarr_t[lv_cf_import_strarr_i]=0;
				if(opt_is_token==0){ 
					cf_add(lv_cf_import_strarr_lastt);
				}else{
					if(lv_cf_import_strarr_lastt[0]!=0)cf_add(lv_cf_import_strarr_lastt);
				}
				lv_cf_import_strarr_t[lv_cf_import_strarr_i]=lv_cf_import_strarr_c2;
				lv_cf_import_strarr_i += lv_cf_import_strarr_seplen;
				lv_cf_import_strarr_lastt = lv_cf_import_strarr_t+lv_cf_import_strarr_i;
			}else{
				lv_cf_import_strarr_i ++;
			}
			lv_cf_import_strarr_t[lv_cf_import_strarr_ti]= lv_cf_import_strarr_c;
		}
		free(lv_cf_import_strarr_t);
		return 1;
	}


	wlint32 cf_howmany(void)
	{
		return howmany_AA();
	}


	int cf_modi(wlint32 idx, const wlint8 *s1)
    {
		char *s = (char*)s1;
		
			sortstatus.issorted=0;

        return chg(idx, s, wl_stru_strf::str_len(s) + 1, 1 );
    }


	int cf_modi(wlint32 idx, wlint8 *s, wlint32 a_size)
    {
			sortstatus.issorted=0;

		lv_cf_modi_rc= chg(idx, s, a_size, 0);
		lv_cf_modi_t = cf_read(idx);
		for(lv_cf_modi_i=0;lv_cf_modi_i<a_size;lv_cf_modi_i++)
			lv_cf_modi_t[lv_cf_modi_i] = s[lv_cf_modi_i];
        return lv_cf_modi_rc;
    }


	int cf_modi(wlint32 idx, wlint32 a_size)
    {
			sortstatus.issorted=0;

		lv_cf_modi_rc= chg(idx, "", a_size, 0);
		lv_cf_modi_t = cf_read(idx);
		
			
        return lv_cf_modi_rc;
    }


	int cf_swap(wlint32 idx1, wlint32 idx2)
	{
			sortstatus.issorted=0;

		lv_cf_swap_j= idx1;
        if(lv_cf_swap_j<0) return 0;
        if(lv_cf_swap_j>=cf_howmany()) return 0;
        if(isempty()) return 0;

		lv_cf_swap_j= idx2;
        if(lv_cf_swap_j<0) return 0;
        if(lv_cf_swap_j>=cf_howmany()) return 0;
        if(isempty()) return 0;

		if(idx1==idx2) return 1;

        lv_cf_swap_tp = str_stack.stk[idx1];
		str_stack.stk[idx1] = str_stack.stk[idx2];
		str_stack.stk[idx2] = lv_cf_swap_tp;
        return 1;
    }


	int cf_del(wlint32 idx)
    {

		lv_cf_del_rc = lcf_free(idx);
        if(lv_cf_del_rc==0) return 0;

		if(iv_fast_del){

				sortstatus.issorted=0;

			cf_swap(idx, (howmany_AA() - 1) );
		}else{
			for(lv_cf_del_i=idx;lv_cf_del_i < (howmany_AA() - 1);lv_cf_del_i++)
				cf_swap(lv_cf_del_i, lv_cf_del_i+1);
		}

		str_stack.sp--;
		return 1;
	}


	int cf_ins(wlint32 idx_to)
    {

		wlint32 i;
		if(idx_to<0||idx_to>=cf_howmany()) return 0;

			sortstatus.issorted=0;


		for(i=cf_howmany()-1;i>idx_to;i--){
			cf_swap(i, i-1);
		}

		return 1;
	}


	int cf_deltop(void) 
    {
        if(str_stack.stk==NULL) return 0;
        if(isempty()) return 0;
        str_stack.sp--;
        lv_cf_deltop_tp=str_stack.stk[str_stack.sp];
        free(lv_cf_deltop_tp);
        return 1;
    }


	int cf_clean(void)
	{
		while( cf_howmany()!= 0) { cf_deltop(); }
		return 1;
	}


	int cf_clean(wlint32 remain)
    {
        if(remain<0) remain=0;
		while( cf_howmany()>remain)	{
			cf_del(0);
		}
		return 1;
	}


	int cf_rev(void)
    {
			sortstatus.issorted=0;

		lv_cf_rev_u = (wluint32)cf_howmany();
		lv_cf_rev_u >>= 1;
		lv_cf_rev_x = lv_cf_rev_u;
		lv_cf_rev_y = cf_howmany() - 1;

        for(lv_cf_rev_i=0;lv_cf_rev_i<lv_cf_rev_x;lv_cf_rev_i++) {
			lv_cf_rev_a = lv_cf_rev_i;
			lv_cf_rev_b = lv_cf_rev_y - lv_cf_rev_i;
			lv_cf_rev_tp=str_stack.stk[lv_cf_rev_a];
			str_stack.stk[lv_cf_rev_a]= str_stack.stk[lv_cf_rev_b];
			str_stack.stk[lv_cf_rev_b]= lv_cf_rev_tp;
		}
		return 1;
    }


	void cf_qsort( void )
    { 
        cf_qsort(iv_mycmp);
    }


	void cf_qsort( int (*mycmpf)(const void *,const void *) )
    { 
        iv_mycmp=mycmpf;

			sortstatus.cmpf=iv_mycmp; sortstatus.issorted=1;

        ::qsort((void *)str_stack.stk, (size_t)howmany_AA(), sizeof(char *), iv_mycmp);
    }


	wlint32 cf_sel(void *pvalue )
    {
		return cf_sel(iv_mycmp, pvalue);
	}


	wlint32 cf_sel( int (*mycmpf)(const void *,const void *) , void *pvalue )
    {
	 
     

		if(sortstatus.cmpf==mycmpf&&sortstatus.issorted)
			return cf_qsel(sortstatus.cmpf, pvalue);


		iv_mycmp=mycmpf;

		if(iv_mycmp==NULL) return -1;
        if(str_stack.stk==NULL) return -1;
        lv_cf_sel_low=0;
        lv_cf_sel_high=str_stack.sp - 1;
        while(lv_cf_sel_low<=lv_cf_sel_high) {
            if(1||lv_cf_sel_high-lv_cf_sel_low<=3) {
                for(;lv_cf_sel_low<=lv_cf_sel_high;lv_cf_sel_low++) {
                    lv_cf_sel_mid=lv_cf_sel_low;
                    
					lv_cf_sel_x = (*iv_mycmp) ( (const void *)(&pvalue), (const void *)(&str_stack.stk[lv_cf_sel_mid])  ) ;
					
					
                    if(lv_cf_sel_x==0) return lv_cf_sel_mid;
                }
                return -1;
            }
            lv_cf_sel_mid=(lv_cf_sel_low+lv_cf_sel_high)/2;
            
            if(lv_cf_sel_x<0) lv_cf_sel_high=lv_cf_sel_mid-1;
            else if(lv_cf_sel_x>0) lv_cf_sel_low=lv_cf_sel_mid+1;
            else return 1; 
        }
        return -1;
    }


	wlint32 cf_output(char *pfn)
	{
        return cf_output(pfn, "\r\n");
    }


	wlint32 cf_outputa(char *pfn)
	{
        return cf_output(pfn, "\r\n", "ab");
    }

	wlint32 cf_output(wlint8 *pfn, const wlint8 *ln_sep)
    {
        return cf_output(pfn, (char*)ln_sep, "wb");
    }


	wlint32 cf_output(const wlint8 *pfn1, const wlint8 *ln_sep1, const wlint8 *openMethd1)
    {
		char *pfn=(char*)pfn1;
		char *ln_sep=(char*)ln_sep1;
		char *openMethd=(char*)openMethd1;
		
		lv_cf_output_lp = this;
        lv_cf_output_fp=fopen(pfn,openMethd);
        if(lv_cf_output_fp==NULL) return 0;
        for(lv_cf_output_i=0;lv_cf_output_i<lv_cf_output_lp->cf_howmany();lv_cf_output_i++) {
            fprintf(lv_cf_output_fp,"%s%s",lv_cf_output_lp->cf_read(lv_cf_output_i), ln_sep);
        }
        fclose(lv_cf_output_fp);
        return lv_cf_output_i;
    }


	wlint32 cf_output(char *pfn , wlint32 rec_size)
    {
		lv_cf_output2_lp = this;

        lv_cf_output2_fp=fopen(pfn,"wb");
        if(lv_cf_output2_fp==NULL) return 0;
        for(lv_cf_output2_i=0;lv_cf_output2_i<lv_cf_output2_lp->cf_howmany();lv_cf_output2_i++) {
			fwrite(lv_cf_output2_lp->cf_read(lv_cf_output2_i), rec_size, 1, lv_cf_output2_fp);
        }
        fclose(lv_cf_output2_fp);
        return lv_cf_output2_i;
    }


	

	wlint32 cf_setjiao(class wl_stru_list *pl)
    {
		wlint32 i;
		pl->cf_qsort( iv_mycmp );
		for(i=cf_howmany()-1;i>=0;i--) if(-1==pl->cf_sel(cf_read(i)) )cf_del(i);
		return cf_howmany();
	}


	wlint32 cf_setcha(class wl_stru_list *pl)
    {
		wlint32 i;
		pl->cf_qsort( iv_mycmp );
		for(i=cf_howmany()-1;i>=0;i--) if(!(-1==pl->cf_sel(cf_read(i)) ))cf_del(i);
		return cf_howmany();
	}


	wlint32 cf_setuniq(void)
	{
		return cf_setgroup(NULL);
	}


	wlint32 cf_setgroup(class wl_stru_list *pl)
    {
		wlint32 i,j;
		wlint8 *t1, *t2;
		cf_qsort( ); 
		j=1;
		for(i=cf_howmany()-1;i>=1;i--) {
			t1 = cf_read(i);
			t2 = cf_read(i-1);
			if(!((*iv_mycmp) ( (const void *)(&t1), (const void *)(&t2) ))) {
				cf_del(i);
				j++;
			}else{
				
				
				if(NULL!=pl) {
					
					pl->cf_add32(j);
				}
				j=1;
			}
		}
		if(cf_howmany()>0){
			
			
			if(NULL!=pl) {
				
				pl->cf_add32(j);
			}
		}
		if(NULL!=pl) { pl->cf_rev(); }
		return cf_howmany();
	}


	wlint8 *cf_set_luosuo(void) 
    {
		wlint32 i,j,k1,k2;
		class wl_stru_list *p;

		p = new class wl_stru_list;
		cf_setgroup(p);
		for(j=k1=i=0;i<cf_howmany();i++) {
			k2 = *(wlint32 *)p->cf_read(i);
			if(k2>k1) {
				k1=k2; 
				j=i;   
			}
		}

		if(cf_howmany()&&j>0) {
			cf_swap(0,j);
		}

		while(cf_howmany()>1)
			cf_deltop();

		delete p;
		return cf_read(0);
	}


private:

    int init(long depth)
    {

        if(str_stack.stk!=NULL) {
            for(;!isempty();){
                if(isempty()) break;
                str_stack.sp--;
                lv_init_tp=str_stack.stk[str_stack.sp];
                free(lv_init_tp);
            }
            free(str_stack.stk);
            str_stack.stk=NULL;
        }
        str_stack.stk=(char **)malloc(sizeof(char *)*(depth+2));
        if(str_stack.stk==NULL) return 0;
        str_stack.sp=0;
        str_stack.depth=depth;
        return 1;
    }


    int isempty(void)
    {
        if(str_stack.stk==NULL) return 1;
    	return str_stack.sp-1<0?1:0;
    }


    int isfull(void)
    {
        if(str_stack.sp>str_stack.depth) return 1;
        return 0;
    }


    char *push(const char *s1, wlint32 a_size, wlint8 ifstrcpy)
    {
		char *s=(char*)s1;

        if(str_stack.stk==NULL) { return NULL; }
        if(s==NULL) return NULL;
        if(isfull()) {
            lv_push_tl = 2 + (long)(1.18 * (float)str_stack.depth) + initdepth;
            lv_push_tt = (char **)malloc(sizeof(char *)*lv_push_tl);
            if(lv_push_tt==NULL) return NULL;
            for(lv_push_ttl=0;lv_push_ttl<=str_stack.depth;lv_push_ttl++)
				lv_push_tt[lv_push_ttl]=str_stack.stk[lv_push_ttl];
            free(str_stack.stk);
            str_stack.stk=lv_push_tt;
            str_stack.depth=lv_push_tl-2;
			
        }
        lv_push_tp=(char *)malloc(a_size);
        if(lv_push_tp==NULL) return NULL;
        str_stack.stk[str_stack.sp]=lv_push_tp;
        if(ifstrcpy) strcpy(str_stack.stk[str_stack.sp],s);
        str_stack.sp++;
        return lv_push_tp;
    }


    wlint32 howmany_AA()
    {
        return str_stack.sp;
    }


	long count(char *s) 
	{

		lv_count_c=0;
		for(lv_count_i=0;lv_count_i<howmany_AA();lv_count_i++) {
			if (!strcmp(s, cf_read(lv_count_i))) lv_count_c++;
		}
		return lv_count_c;
	}


	int chg(wlint32 idx, const wlint8 *newvalue1, wlint32 a_size, wlint8 ifstrcpy)
    {
		char *newvalue=(char*)newvalue1;
        if(idx<0) return 0;
        if(idx>=howmany_AA()) return 0;
        if(isempty()) return 0;
        lv_chg_tp=str_stack.stk[idx];
		free(lv_chg_tp);
		lv_chg_tp=(char *)malloc( a_size );
		if(lv_chg_tp==NULL) return 0;
		if(ifstrcpy) strcpy(lv_chg_tp,newvalue);
		str_stack.stk[idx]=lv_chg_tp;
        return 1;
    }


	int lcf_free(wlint32 idx)
    {

        if(idx<0) return 0;
        if(idx>=howmany_AA()) return 0;
        if(isempty()) return 0;
        lv_lcf_free_tp=str_stack.stk[idx];
		free(lv_lcf_free_tp);
		return 1;
	}


	wlint32 cf_qsel( void *pvalue )
	{
		return cf_qsel(iv_mycmp, pvalue);
	}


	wlint32 cf_qsel( int (*mycmpf)(const void *,const void *) , void *pvalue)
    {
		iv_mycmp=mycmpf;

		if(iv_mycmp==NULL) return -1;
        if(str_stack.stk==NULL) return -1;

        lv_cf_qsel_low = 0;
        lv_cf_qsel_high = str_stack.sp - 1 ;
        while(lv_cf_qsel_low<=lv_cf_qsel_high) {
            lv_cf_qsel_mid = (lv_cf_qsel_low+lv_cf_qsel_high)/2;
            lv_cf_qsel_x = (*iv_mycmp) ( (const void *)(&pvalue), (const void *)(&str_stack.stk[lv_cf_qsel_mid])  ) ;
            if(lv_cf_qsel_x<0) lv_cf_qsel_high = lv_cf_qsel_mid - 1;
            else if(lv_cf_qsel_x>0) lv_cf_qsel_low = lv_cf_qsel_mid + 1;
            else return lv_cf_qsel_mid; 
        }
        return  -1;
    }


}; 


#endif


#ifndef WL_STRU_I32QUE_H
#define WL_STRU_I32QUE_H


class wl_stru_i32que {

private:

	wl_stru_list	iv_knl;
	wlint32		iv_width, iv_x , *ivp_base;
	wlint32		iv_init_width;

	int lf_alloc(void)
	{
		int rc;
		rc = -1!=iv_knl.cf_add(iv_width*sizeof(wlint32));
		ivp_base = (wlint32 *)iv_knl.cf_readtop();
		return rc;
	}

	int lf_resize(void)
	{
		wlint32		i;
		i= iv_width;
		iv_width = (wlint32)((double)iv_width*1.18+3.10+iv_init_width);
		if(!lf_alloc())return 0;
		memcpy(iv_knl.cf_read(1), iv_knl.cf_read(0), i*sizeof(wlint32));
		return iv_knl.cf_del(0);
	}

	int wl_stru_i32que_init(wlint32 width)
    {
		iv_init_width = iv_width= (width<=0?2:width);
		iv_x= 0;
		iv_knl.cf_setsortf(iv_knl.cf_sortA_ii);
		return lf_alloc();
    }

public:

	wl_stru_i32que()	{	wl_stru_i32que_init(33);	}


	wl_stru_i32que(wlint32 width)	{	wl_stru_i32que_init(width);    }


	class wl_stru_list *cf_getknl(void)
	{
		return &iv_knl;
	}


	int cf_clean(void)
	{
		iv_x = 0;
		return 1;
	}


	int cf_push(wlint32 i)
	{
		if(iv_x>=iv_width)
			if(!lf_resize()) return 0;
		ivp_base[iv_x++] = i;
		return 1;
	}


	int cf_pop(wlint32 *p)
	{
		iv_x--;
		if(iv_x<0) return 0;
		*p = ivp_base[iv_x];
		return 1;
	}


	int cf_deltop(void)
	{
		iv_x--;
		if(iv_x<0) return 0;
		return 1;
	}


	wlint32 cf_hm(void)
	{
		return (iv_x);
	}


	int cf_read(wlint32 idx, wlint32 *p)
	{
		if(idx<0||idx>=cf_hm()) return *p=0;
		*p=ivp_base[idx];
		return 1;
	}


	wlint32 * cf_read(wlint32 idx)
	{
		if(idx<0||idx>=cf_hm()) return NULL;
		return  ivp_base+idx;
	}


}; 


#endif


#ifndef WL_STRU_SHEET_H
#define WL_STRU_SHEET_H




class wl_stru_sheet {

private:
    class wl_stru_list  iv_aa;
	class wl_stru_list *iv_tp;

		wlint32 lv_wl_stru_sheet_i;
		class wl_stru_sheet *lv_cf_output_lp;
        wlint32 lv_cf_output_x,lv_cf_output_y;
        FILE *lv_cf_output_fp;
		class wl_stru_list *lv_cf_output_tp;

public:

    static int cf_sortA_ss( const void *arg1, const void *arg2 )
	{   
		return ::strcmp( (**( class wl_stru_list ***)arg1)->cf_read(0), (**( class wl_stru_list ***)arg2)->cf_read(0) );
	}


	static int cf_sortA_ii( const void *arg1, const void *arg2 )
	{   
		wlint32 i,j;
		class wl_stru_list *p1, *p2 ;

		p1 = **( class wl_stru_list ***)arg1;
		p2 = **( class wl_stru_list ***)arg2;

		i = *((wlint32 *)(p1->cf_read(0)));
		j = *((wlint32 *)(p2->cf_read(0)));

		return i-j;
	}


public:

    wl_stru_sheet()
    {
		iv_aa.iv_fast_del=0;
		cf_getsheetknl()->cf_setsortf(cf_sortA_ss);
    }

    ~wl_stru_sheet()
    {

		iv_aa.iv_fast_del=0;
		for(lv_wl_stru_sheet_i=iv_aa.cf_howmany()-1;lv_wl_stru_sheet_i>=0;lv_wl_stru_sheet_i--)  cf_delrow(lv_wl_stru_sheet_i);
    }


	int cf_plot(wlint32 a_row, wlint32 a_col) 
	{
		wlint32 i;
		if(a_row<=cf_rowcount()-1) return 1;
		for(i=cf_rowcount();i<=a_row;i++) if(-1==cf_addrow()) return 0;
		for(i=0;i<=a_row;i++) if(!cf_getrow(i)->cf_plot(a_col)) return 0;
		return 1;
		
	}


	wlint32 cf_addrow(void)
	{
		iv_tp =  new class wl_stru_list;
		return iv_aa.cf_add( (wlint8 *)(&iv_tp), sizeof(wl_stru_list *) );
	}


	int cf_delrow(wlint32 idx)
    {
		iv_tp = cf_getrow(idx);
		delete iv_tp;
		return iv_aa.cf_del(idx);
	}


	int cf_dellastrow(void)
    {
		return cf_delrow(cf_rowcount()-1);
	}


	int cf_clean(void)
	{
		while( cf_rowcount()!= 0)
		{
			cf_delrow(cf_rowcount()-1);
		}
		return 1;
	}


	wlint32 cf_rowcount(void)
	{
		return iv_aa.cf_howmany();
	}


	wlint8 *cf_getele(wlint32 row, wlint32 col)
	{
		if(row>=cf_rowcount()) return NULL;
		return (wlint8 *)(cf_getrow(row)->cf_read(col));
	}


	class wl_stru_list *cf_getrow(wlint32 idx)
	{
		class wl_stru_list **t;
		t=(class wl_stru_list **)iv_aa.cf_read(idx);
		return t==NULL?NULL:*t;
	}


	class wl_stru_list *cf_getlastrow(void)
	{
		return cf_getrow(cf_rowcount()-1);
	}


	class wl_stru_list *cf_getsheetknl(void)
	{
		return (&iv_aa) ;
	}


	wlint32 cf_output(wlint8 *pfn)
	{
		return cf_output(pfn, "", "", "\t", "\n");
	}


	wlint32 cf_output(const wlint8 *pfn_1, const wlint8 *quo1_1, const wlint8 *quo2_1, const wlint8 *s_td_1, const wlint8 *s_tr_1)
    {
		char *pfn=(char*)pfn_1;
		char *quo1=(char*)quo1_1;
		char *quo2=(char*)quo2_1;
		char *s_td=(char*)s_td_1;
		char *s_tr=(char*)s_tr_1;
		

		lv_cf_output_lp = this;
        lv_cf_output_fp=fopen(pfn,"w");
        if(lv_cf_output_fp==NULL) return 0;
        for(lv_cf_output_y=0;lv_cf_output_y<(lv_cf_output_lp->cf_getsheetknl())->cf_howmany();lv_cf_output_y++) {
			lv_cf_output_tp = lv_cf_output_lp->cf_getrow(lv_cf_output_y);
			for(lv_cf_output_x=0;lv_cf_output_x<lv_cf_output_tp->cf_howmany();lv_cf_output_x++) {
				fprintf(lv_cf_output_fp,"%s%s%s", quo1, lv_cf_output_tp->cf_read(lv_cf_output_x), quo2);
				if(lv_cf_output_x!=(lv_cf_output_tp->cf_howmany() - 1))fprintf(lv_cf_output_fp,"%s", s_td);
			}
			
			fprintf(lv_cf_output_fp,"%s", s_tr);
        }
        fclose(lv_cf_output_fp);
        return lv_cf_output_y;
    }


	int cf_import_str(const wlint8 *s_data, const wlint8 *s_td, const wlint8 *s_tr)
    {
		return cf_import_str((char*)s_data, (char*)s_td, 0 , (char*)s_tr, 1 );
	}


	int cf_import_str(wlint8 *s_data, wlint8 *s_td, int td_mthd, wlint8 *s_tr, int tr_mthd)
    {
		class wl_stru_list a, b;
		wlint32 i;

		a.cf_import_strarr(s_data, s_tr, tr_mthd);
		for(i=0;i<a.cf_howmany();i++){
			cf_addrow();
			cf_getlastrow()->cf_import_strarr(a.cf_read(i), s_td, td_mthd);
		}
		return 1;
	}


}; 

#endif


#ifndef WL_STRU_PRPT01_H
#define WL_STRU_PRPT01_H


class wl_stru_prpt01  : public wl_stru_list {

public:

    wl_stru_prpt01()
    {
		iv_fast_del = 0;
		cf_setsortf(cf_sortA_ssi);
		sortstatus.cmpf=iv_mycmp;
		sortstatus.issorted=0;
    }


	int cf_clean(void)
	{
		
		return wl_stru_list::cf_clean();
	}


	wlint8 *cf_prpt_new(wlint8 *s_var, wlint8 *s_val) 
	{
		wlint32 i;
		wlint8 *t;

		i = cf_add( wl_stru_strf::str_len(s_var) + wl_stru_strf::str_len(s_val) + 2 );

		::strcpy(cf_read(i), s_var);
		t = ::strcpy(cf_read(i)+wl_stru_strf::str_len(s_var)+1, s_val);

		
		return t;
	}


	wlint8 *cf_prpt_get(const wlint8 *s_var1) 
	{
		wlint8 *s_var=(char*)s_var1;
		wlint32 i;
		static wlint8 c[1];

		c[0]=0;

		
		i = cf_sel(s_var);

		
		if(i==-1) return c;

		return cf_read(i) + wl_stru_strf::str_len(s_var) + 1 ;
	}


	wlint8 *cf_prpt_get(wlint32 i, int i_want_val) 
	{
		static wlint8 c[1];
		c[0]=0;

		if(i<0||i>=cf_howmany()) return c; 

		if(i_want_val) return cf_read(i) + 1+ wl_stru_strf::str_len(cf_read(i)) ;
		else return cf_read(i) ;
	}


	wlint8 *cf_prpt_let(const wlint8 *s_var1, const wlint8 *s_newval1) 
	{
		char *s_var=(char*)s_var1;
		char *s_newval=(char*)s_newval1;
		wlint32 i;

		
		i = cf_sel(s_var);

		if(i==-1) {
			
			return cf_prpt_new(s_var, s_newval);
		}

		class wl_stru_list a;
		a.cf_add(s_var);
		a.cf_add(s_newval);
		s_var = a.cf_read(0);
		s_newval= a.cf_read(1);

		cf_modi(i,  wl_stru_strf::str_len(s_var) + wl_stru_strf::str_len(s_newval) + 2 );
		::strcpy(cf_read(i), s_var);
		return ::strcpy(cf_read(i)+ wl_stru_strf::str_len(s_var)+1, s_newval);
	}


	wlint8 *cf_prpt_let(wlint8 *s_var, wlint32  i_newval) 
	{
		wlint8 c[33];
		wl_stru_strf::str_ltoa(i_newval,c);
		return cf_prpt_let(s_var, c);
	}


	int cf_prpt_del(wlint8 *s_var) 
    {
		wlint32 i;

		
		i = cf_sel(s_var);

		if(i==-1) return 0;
        return cf_del(i);
	}


	wlint8 *cf_prpt_cat(const wlint8 *s_var1, const wlint8 *s_cat_val1) 
	{
		char * s_var=(char*)s_var1;
		char *s_cat_val=(char*)s_cat_val1;
		wl_stru_list a;
		wlint8 *t;

		t = cf_prpt_get(s_var);

		a.cf_add( wl_stru_strf::str_len(t) + wl_stru_strf::str_len(s_cat_val) + 1 ); 

		sprintf(a.cf_readtop(), "%s%s", t, s_cat_val);

		t = cf_prpt_let(s_var, a.cf_readtop());

		return t;
	}


	wlint8 *cf_prpt_add(wlint8 *s_var, wlint8 *s_val1,  wlint8 *s_val2) 
	{
		class wl_stru_list aa;
		aa.cf_add(s_val1);
		aa.cf_add(s_val2);

		cf_prpt_let(s_var, aa.cf_read(0));
		return cf_prpt_cat(s_var, aa.cf_read(1));
	}


	wlint8 *cf_prpt_kuo(wlint8 *s_var, wlint8 *s_kuoval1,  wlint8 *s_kuoval2) 
	{
		cf_prpt_cat(s_var, s_kuoval2);
		return cf_prpt_add(s_var, s_kuoval1, cf_prpt_get(s_var));
	}


	wlint8 *cf_pstr_replace(wlint8 *s_var, wlint8 *s1, wlint8 *s2, int opt)
	{
		class wl_stru_list b;
		class wl_stru_prpt01 a;
		
		a.cf_prpt_let("t", "");
		a.cf_prpt_let("t2", "");
		
		wlint32 i1, i2;

		if(s_var==NULL||s1==NULL||*s_var==0||*s1==0||s2==NULL) return s_var;
		

		
		a.cf_prpt_let("tmp", cf_prpt_get(s_var));
		if(!wl_stru_strf::str_cmp(s1,wl_stru_strf::str_right(a.cf_prpt_get("tmp"), wl_stru_strf::str_len(s1)))){
			a.cf_prpt_let("t2", s2);
		}else{
			a.cf_prpt_let("t2", "");
		}

		
		b.cf_import_strarr(cf_prpt_get(s_var), s1, opt);
		i2 = b.cf_howmany();

		
		

		for(i1=0;i1<i2-1;i1++){
			a.cf_prpt_cat("t", b.cf_read(i1));
			a.cf_prpt_cat("t", s2 );
		}

		
		a.cf_prpt_let("out", a.cf_prpt_get("t") );
		if(i2>0) a.cf_prpt_cat("out", b.cf_read(i2-1) );

		
		
		if(opt&&!wl_stru_strf::str_cmp(s1,wl_stru_strf::str_right(cf_prpt_get(s_var), wl_stru_strf::str_len(s1)))){
			
			a.cf_prpt_cat("out", a.cf_prpt_get("t2") );
		}
		return cf_prpt_let(s_var, a.cf_prpt_get("out") );
	}


	void cf_prpt_sort( void )
    {
        cf_qsort( );
    }


	int cf_import_prpt(char *as_data, char *as_sepTD, char *as_sepTR)
	{
		class wl_stru_list a, b;
		wlint32 i;

		a.cf_import_strarr(as_data, as_sepTR, 0);

		for(i=0;i<a.cf_howmany();i++){
			b.cf_clean();
			b.cf_import_strarr(a.cf_read(i), as_sepTD, 0);
			if(b.cf_howmany()>=2){
				cf_prpt_let(b.cf_read(0), b.cf_read(1));
			}
		}
		cf_prpt_sort();
		return 1;
	}


	int cf_import_prpt(char **p_data, char *as_sepTD )
	{
		class wl_stru_list  b;
		wlint32 i;

		for(i=0;;i++){
            if(p_data[i]==NULL)break;
			b.cf_clean();
			b.cf_import_strarr(p_data[i], as_sepTD, 0);
			if(b.cf_howmany()>=2){
				cf_prpt_let(b.cf_read(0), b.cf_read(1));
			}
		}
		cf_prpt_sort();
		return 1;
	}


	int cf_impfast_prpt(char *as_data, char *as_sepTD, char *as_sepTR)
	{
		class wl_stru_list a, b;
		wlint32 i;

		a.cf_import_strarr(as_data, as_sepTR, 0);

		for(i=0;i<a.cf_howmany();i++){
			b.cf_clean();
			b.cf_import_strarr(a.cf_read(i), as_sepTD, 0);
			if(b.cf_howmany()>=2){
				cf_prpt_new(b.cf_read(0), b.cf_read(1));
			}
		}
		cf_setuniq();
		return 1;
	}


	int cf_impfast_prpt(char **p_data, char *as_sepTD )
	{
		class wl_stru_list  b;
		wlint32 i;

		for(i=0;;i++){
            if(p_data[i]==NULL)break;
			b.cf_clean();
			b.cf_import_strarr(p_data[i], as_sepTD, 0);
			if(b.cf_howmany()>=2){
				cf_prpt_new(b.cf_read(0), b.cf_read(1));
			}
		}
		cf_setuniq();
		return 1;
	}


	wlint32 cf_prpt_output(wlint8 *pfn)
    {
		FILE *fp;
		wlint32 i;
		fp=fopen(pfn,"w");
        if(fp==NULL) return 0;
        for(i=0;i<cf_howmany();i++) {
            fprintf(fp,"%s=%s\n",cf_read(i), cf_prpt_get(cf_read(i)) );
        }
        fclose(fp);
        return i;
    }


	wlint32 cf_prpt_output(wlint8 *pfn, wlint8 *as_var)
    {
		wl_stru_list ll;
		ll.cf_clean();
		ll.cf_add(cf_prpt_get(as_var));
		return ll.cf_output(pfn, "");
    }


}; 


#endif


#ifndef WL_STRU_PRPT_H
#define WL_STRU_PRPT_H


class wl_stru_prpt  {

private:

	class wl_stru_prpt01	 iv_knl;

public:

    wl_stru_prpt()   {  }


	wl_stru_prpt01 *cf_getknl(void)
	{
		return &iv_knl;
	}


	int cf_clean(void)
	{
		return iv_knl.cf_clean();
	}


	wlint32 cf_hm(void)
	{
		return iv_knl.cf_howmany() ;
	}


	wlint8 *cf_new(wlint8 *s_var, wlint8 *s_val) 
	{
		return iv_knl.cf_prpt_new(s_var, s_val);
	}


	int cf_equal(wlint8 *s_var, wlint8 *val) 
	{
		return !wl_stru_strf::str_cmp( cf_get(s_var), val) ;
	}


	wlint8 *cf_get(const wlint8 *s_var1) 
	{
		wlint8 *s_var=(char*)s_var1;
		return iv_knl.cf_prpt_get(s_var) ;
	}


	wlint8 *cf_get(wlint32 i, int i_want_val=1) 
	{
		return iv_knl.cf_prpt_get(i, i_want_val) ;
	}


	int cf_get(wlint8 *s_objname, void *p, wlint32 len) 
	{
		wlint8 *t;
		t = cf_get(s_objname);
		if(!(*t))  return 0;
		memcpy(p, t+1, len );
		return 1;
	}


	wlint8 *cf_let(const wlint8 *s_var1, const wlint8 *s_newval1) 
	{
		wlint8 *s_var=(char*)s_var1;
		wlint8 *s_newval=(char*)s_newval1;
		return iv_knl.cf_prpt_let( s_var, s_newval) ;
	}


	wlint8 *cf_let(wlint8 *s_var, wlint32  i_newval) 
	{
		return iv_knl.cf_prpt_let( s_var, i_newval);
	}


	int cf_let(wlint8 *s_objname, void *p, wlint32 len) 
	{
		wl_stru_list aa;
		wlint8 *t;
		wlint32 i;
		if(len<=0)  return 0;
		len += 2;
		if(aa.cf_add(len)<0)  return 0;
		t = aa.cf_readtop();
		for(i=0;i<len-1;i++) { 
			t[i]='a';
		}
		t[i]=0;
		t = cf_let( s_objname, t );
		memcpy( t+1, p, len-2);
		return 1;
	}


	int cf_del(wlint8 *s_var) 
    {
		return iv_knl.cf_prpt_del(s_var);
	}


	wlint8 *cf_cat(const wlint8 *s_var1, const wlint8 *s_cat_val1) 
	{
		char *s_var=(char*)s_var1;
		char *s_cat_val=(char*)s_cat_val1;
		return iv_knl.cf_prpt_cat( s_var, s_cat_val);
	}

	wlint8 *cf_cat(wlint8 *s_var, wlint32 i) 
	{
		wlint8 c[33];
		return cf_cat(s_var, wl_stru_strf::str_ltoa(i,c) );
	}


	wlint8 *cf_add(wlint8 *s_var, wlint8 *s_val1,  wlint8 *s_val2) 
	{
		return iv_knl.cf_prpt_add( s_var,  s_val1,  s_val2) ;
	}


	wlint8 *cf_kuo(const wlint8 *s_var,const  wlint8 *s_kuoval1, const  wlint8 *s_kuoval2) 
	{
		return iv_knl.cf_prpt_kuo( (char*)s_var,  (char*)s_kuoval1,  (char*)s_kuoval2);
	}


	wlint8 *cf_repl(const wlint8 *s_var, const wlint8 *s1, const wlint8 *s2, int opt)
	{
		return iv_knl.cf_pstr_replace( (char*)s_var,  (char*)s1,  (char*)s2,  opt);
	}


	void cf_sort( void )
    {
        iv_knl.cf_prpt_sort();
    }


	int cf_impt(char *as_data, char *as_sepTD, char *as_sepTR)
	{
		return iv_knl.cf_import_prpt(as_data, as_sepTD, as_sepTR);
	}


	int cf_impt(char **p_data, char *as_sepTD )
	{
		return iv_knl.cf_import_prpt(p_data, as_sepTD);
	}


	int cf_impt(wl_stru_list *pl, char *as_sepTD ) 
	{
		wlint8 *t1, *t2;
		wlint32 i,j;

		for(i=0;i<pl->cf_howmany();i++){
            t1 = pl->cf_read(i);
			if(t1==NULL) continue;
			j = wl_stru_strf::str_instr(t1, as_sepTD);
			if(j<=0) continue; 
			t1[j] = 0;
			t2 = t1 + j + 1;
			cf_new(t1, t2);
		}
		iv_knl.cf_setuniq();
		return 1;
	}


	int cf_impt(wl_stru_sheet *ps)
	{
		static char p[]="";
		wlint8 *t1, *t2;
		wlint32 i;

		for(i=0;i<ps->cf_rowcount();i++){
            t1 = ps->cf_getele(i, 0);
			t2 = ps->cf_getele(i, 1);
			if(t1==NULL) t1=p;
			if(t2==NULL) t2=p;
			cf_new(t1, t2);
		}
		iv_knl.cf_setuniq();
		return 1;
	}


	int cf_imptf(char *as_data, char *as_sepTD, char *as_sepTR)
	{
		return iv_knl.cf_impfast_prpt(as_data, as_sepTD, as_sepTR);
	}


	int cf_imptf(char **p_data, char *as_sepTD )
	{
		return iv_knl.cf_impfast_prpt(p_data, as_sepTD);
	}


	wlint32 cf_output(wlint8 *pfn)
    {
		return iv_knl.cf_prpt_output(pfn);
    }


	wlint32 cf_output(wlint8 *pfn, wlint8 *as_var)
    {
		return iv_knl.cf_prpt_output(pfn, as_var);
    }


}; 


#endif


#ifndef WL_STRU_VBARY_FILE_H
#define WL_STRU_VBARY_FILE_H


class wl_stru_vbary_file{

          
public:
   struct wl_vbary_file_a4352357i647{
   	   int opening; 
       int vbaryOK;
       int vbaryERROR;
       int state;  
       class wl_stru_list  filename ;
       FILE *fp;
       wlint32 filelength;    
       wluint8 *buf ;
       wlint32 buf_size;
       wlint32 buf_ptr1,buf_ptr2;
       wlint32 read_disk_count;   
       wlint32 read_count;        
   }  varray ;

private:
	class wl_stru_list  iv_aa;

public:

   wl_stru_vbary_file(void)
       {
   	      varray.opening=0;
   	      varray.vbaryOK= 1;
          varray.vbaryERROR= 0;
          varray.buf_ptr1=0;
          varray.buf_ptr2=0;
          varray.read_disk_count=0;
          varray.read_count=0;

		  varray.buf_size=1333;
		  iv_aa.cf_add(varray.buf_size);
		  varray.buf = (wluint8 *)iv_aa.cf_read(0);
   	   }

   ~wl_stru_vbary_file(void)
        {
        	if(varray.opening) cf_close();
   	    }


   double cf_getreadv(void) 
       {
          double d;
          if(varray.read_disk_count==0) d=0;
          else if(varray.read_count==0) d=0;
          else d=(double)varray.read_disk_count/(double)(varray.read_count);
          return d;
       }


   wlint32 cf_len(void) { return varray.opening==0?0L:varray.filelength; }


   int cf_open(char *f)
       {
          if(varray.opening) cf_close();

          varray.buf_ptr1=0;
          varray.buf_ptr2=0;     
          varray.read_disk_count=0;
          varray.read_count=0;

          
		  varray.filename.cf_clean() ;
		  varray.filename.cf_add(f);

          varray.fp=fopen((char *)varray.filename.cf_read(0), "rb");
          if(varray.fp==NULL) {
             varray.state=varray.vbaryERROR;
             return varray.vbaryERROR ;
          }
          fseek(varray.fp,0,SEEK_END);
          varray.filelength=ftell(varray.fp);
          fclose(varray.fp);
          varray.fp=fopen((char *)varray.filename.cf_read(0), "rb");
          varray.opening=1;
          cf_read(1);     
		  
		  if(varray.filelength<=1) fread(varray.buf,1,1,varray.fp);
          varray.state=varray.vbaryOK;
          return varray.vbaryOK;
       }


   int cf_close(void)
       {
	      if(varray.opening) {
			  varray.opening=0;
			  fclose(varray.fp);
		  }
		  varray.state=varray.vbaryOK;
		  return varray.vbaryOK;
       }

   wluint8 cf_read(wlint32 Q)
       {
          wluint8 c;
          if(!varray.opening){
              varray.state=varray.vbaryERROR;
              return 0;
          }
          varray.state=varray.vbaryOK;
          varray.read_count++;
          if(Q>=varray.buf_ptr1&&Q<=varray.buf_ptr2) {
             return varray.buf[Q - varray.buf_ptr1];
          }
          if(Q<0||Q>=varray.filelength) {
             varray.state=varray.vbaryERROR;
             return 0;
          }
          fseek(varray.fp,Q,SEEK_SET);

          fread(varray.buf,varray.buf_size,1,varray.fp);
          varray.read_disk_count++;
          varray.buf_ptr1=Q;
          varray.buf_ptr2=Q+varray.buf_size - 1;
          if(varray.buf_ptr2>=varray.filelength) varray.buf_ptr2 = varray.filelength - 1;
          c=varray.buf[0];
          return c;
       }


};

#endif


#ifndef WL_STRU_VBARY_RDR_H
#define WL_STRU_VBARY_RDR_H



class wl_stru_vbary_rdr {


private:
	class wl_stru_vbary_file  iv_v_file;

	class wl_stru_list   iv_v_string;
	wlint32             iv_mem_len;

	wlint8 iv_type;

	class wl_stru_list  iv_aa2;

	int  iv_state;

public:

	wl_stru_vbary_rdr(void)
	{
	   iv_type='n'; 
	   iv_state=0;
	}

	virtual ~wl_stru_vbary_rdr(void) { ;  }


	double cf_getreadv(void) 
	{
	   switch( iv_type )
	   {
	   case 'f' :
		   return iv_v_file.cf_getreadv();
	   case 's' :
		   return 1;
	   default :
		   break;
	   }

	   return iv_state = 1 ;
	}


	wlint32 cf_len(void)
	{
	   switch( iv_type )
	   {
	   case 'f' :
		   return iv_v_file.cf_len();
	   case 's' :
		   return  iv_mem_len ;
	   default :
		   break;
	   }

	   return 0;
	}


	int cf_openf(char *f)
	{
	   cf_close();
	   int i;
	   i = iv_v_file.cf_open(f);
	   iv_state = iv_v_file.varray.state;
	   iv_type = 'f';
	   return i;
	}


	int cf_opens(char *s)
	{
	   cf_close();
	   iv_v_string.cf_clean();
	   iv_state = iv_v_string.cf_add(s)<0? 0:1;
	   iv_mem_len = wl_stru_strf::str_len(s);
	   iv_type = 's';
	   return iv_state;
	}


	int cf_opens(char *mem, wlint32 mem_len)
	{
	   cf_close();
	   iv_v_string.cf_clean();
	   iv_state = iv_v_string.cf_add(mem, mem_len)<0? 0:1;
	   iv_mem_len = mem_len;
	   iv_type = 's';
	   return iv_state;
	}


	int cf_opencol(wl_stru_list *a_list)
	{
		wl_stru_list aa;
		wlint8 *t;
		wlint32 i;
		int rc ;

		rc=0;
		do {
			if(!a_list) break;

			a_list->cf_copy_str(&aa);
			aa.cf_collect();
			t = aa.cf_readtop();
			i = wl_stru_strf::bstr_de_size(t);
			wl_stru_strf::bstr_de(t);
			rc = cf_opens(t,i);

		}while(0);
		return rc ;
	}


	int cf_close(void)
	{
	   switch( iv_type )
	   {
	   case 'f' :
		   return iv_v_file.cf_close();
	   case 's' :
		   return iv_v_string.cf_clean();

	   default :
		   break;
	   }

	   return 0;
	}


	int cf_eof(void)
	{
	   return !iv_state;
	}


	wluint8 cf_read(wlint32 Q)
	{
	   wluint8 u;
	   switch( iv_type )
	   {
	   case 'f' :
		   u = iv_v_file.cf_read(Q);
		   iv_state = iv_v_file.varray.state;
		   return u;
	   case 's' :
		   iv_state = Q<iv_mem_len?1:0;
		   if(iv_state) u = (wluint8)(*(iv_v_string.cf_read(0) + Q)); else u=0;
		   return u;
	   default :
		   break;
	   }

	   return 0;
	}


	wlint8 *cf_read(wl_stru_list *destbuf=NULL)
	{
	   return cf_read(0, cf_len() - 1 , destbuf);
	}


	wlint8 *cf_read(wlint32 Q1, wlint32 Q2, wl_stru_list *destbuf=NULL)
	{
	   wlint8 *tp;

	   if(!destbuf) destbuf= &iv_aa2;
	   destbuf->cf_clean() ;
	   destbuf->cf_add(Q2 - Q1 + 1 + 1); 
	   tp = destbuf->cf_read(0);
	   return cf_read(Q1,Q2,tp);
	}


	wlint8 *cf_read(wlint32 Q1, wlint32 Q2, wlint8 *buf)
	{
	
	   wluint8 *tp;
	   wlint32 i ;

	   tp = (wluint8 *)buf;
	   for(i=Q1;i<=Q2;i++){
		   tp[i - Q1]=cf_read(i);
	   }
	   tp[i-Q1] = 0;
	   return (wlint8 *)tp;
	}


	wlint32 cf_in(wlint8 *s_seek, wlint32 i_from=0)
	{
		wlint8 *t;
		wlint32 i,j ;
		class wl_stru_prpt aa;

		j=wl_stru_strf::str_len(s_seek);
		aa.cf_let("s", s_seek);
		t = aa.cf_get("s");

		for(i=i_from;i<=cf_len()-j;i++){
			if(cf_read(i)!=*(wluint8 *)s_seek) continue;
			cf_read(i, i+j-1, t);
			if(!strcmp(t, s_seek)) return i;
		}
		return -1;
	}


	int cf_write(wlint8 *a_pfn) 
	{
	    FILE *fp;
		wl_stru_list aa(2);
		wlint8 *t;
		int rc ;

		rc=0;
		do {
			if(cf_len()==0) break;

			fp = fopen(a_pfn,"wb");
			if(fp==NULL) break;

			t = cf_read(&aa);
			rc = fwrite(t, cf_len(), 1, fp)?1:0 ;
			fclose(fp);
			

        }while(0);

		return rc?1:0 ;
	}


	wlint32 cf_mkcol(wlint32 a_width, wl_stru_list *a_list, wluint8 a_probability=0) 
	{
		wl_stru_list aa(3);
		wlint8 *t1, *t2, *t3;
		wlint32 i,j,k;

		i=0;
		do{
			if(!a_list) break;

			if(a_width<=0) break;

			if(cf_len()==0) break;

			
			aa.cf_add( (a_width+1) + wl_stru_strf::bstr_en_size( t1=cf_read(&aa), cf_len(), a_probability) );
			t2 = aa.cf_readtop();
			wl_stru_strf::bstr_en(t1, cf_len(), t2, a_probability);

			aa.cf_add(a_width+1); 
			t3 = aa.cf_readtop();
			t3[a_width]=0;

			k = wl_stru_strf::str_len(t2);
			for(j=0;j<k;j+=a_width) {
			   memcpy(t3, t2+j, a_width);
			   a_list->cf_add(t3);
			   i++;
			}
		}while(0);

	   return i;
	}


};

#endif


#ifndef WL_STRU_GMR01_H
#define WL_STRU_GMR01_H


struct wl_s_stru_gmr01_reg { 
	wlint32 rc;
	wlint32 pcx;
	wlint32 pcy;
	wlint32 qa;
	wlint32 q;
	wlint32 lmt;
	wlint32 lmtqa;
	wlint32 bsy;
	wlint32 ci;
	wlint32 cx;
	wlint32 ecd;

	wlint8  * exdata;
	wlpfucb pf;
} ;


struct wl_s_stru_gmr01_trace { 
	wlint32 rc;
	wlint32 id; 
	wlint32 pcy;
	wlint32 qa;
	wlint32 q;
	wlint32 lmt;
	wlint32 lmtqa;
	wlint32 aob;
	wlint32 ci;
	wlint32 cx;
	wlint32 ecd;

	wlint32 aoff;
	wlint32 boff;
} ;


class wl_stru_gmr01 {

private:

	wl_stru_i32que		iv_intstk; 
	wl_stru_i32que		iv_intstk2; 
	wl_stru_i32que		iv_intstk3; 

	struct wl_s_stru_gmr01_reg	iv_reg;

	wl_stru_list	stm_buf; 


	wlint32 iv_vna_iii;		

	wlint32 iv_idt02_iii;	
	wlint8 iv_gen_idt02_buf[33]; 


private:


	int cf_equ(const char *k1, const char *k2){ return !wl_stru_strf::str_cmp((char*)k1,(char*)k2); }


	
	void cf_push(wlint32 i) { iv_intstk.cf_push(i); }
	void cf_pop(wlint32 *p) { iv_intstk.cf_pop (p); }

	
	void cf_push2(wlint32 i) { iv_intstk2.cf_push(i); }
	void cf_pop2(wlint32 *p) { iv_intstk2.cf_pop (p); }

	
	void cf_push3(wlint32 i) { iv_intstk3.cf_push(i); }
	void cf_pop3(wlint32 *p) { iv_intstk3.cf_pop (p); }


	void cf_getstm_init(void)
	{
		wlint32 i,j,k,m;
		k=1;
		j=ivp_rom->cf_rowcount();
		for(i=0;i<j;i++) {
			m=ivp_rom->cf_getrow(i)->cf_maxlen();
			if(k<m)k=m;
		}
		stm_buf.cf_clean();
		k++;
		for(i=0;i<=4;i++){ 
			stm_buf.cf_add(k+sizeof(wlint32));
		}
		
	}


	int cf_getstm(void) 
	{
		
		wlint32 i;
		
		wlint8  *t, *t1, *t2, *tt2;

		
		t = ivp_rom->cf_getele( iv_reg.pcy, iv_reg.pcx ) ;
		if(t==NULL){
			strcpy(stm_buf.cf_read(0), "rtn");
			strcpy(stm_buf.cf_read(1), "");
			strcpy(stm_buf.cf_read(2), "");
			strcpy(stm_buf.cf_read(3), "0");
			return 0;
		}else{
			t1 = strcpy( stm_buf.cf_read(0), t );
		}

		for(t=t2=t1;*t;t++)
			if(*t=='~'){	
				*t=0;
				t++;
				break;
			}
		t2=t;

		

		
		strcpy(stm_buf.cf_read(1), t2);

		if(*t2){
			
			wl_stru_strf::bstr_de(t2, tt2=stm_buf.cf_read(2) );

			
			i=wl_stru_strf::bstr_de_size(t2);
			
			*(wlint32 *)stm_buf.cf_read(3) = i;

			
			*(tt2+i)=0;
		}

		return 1;
	}


	void cf_reg2tr(wl_s_stru_gmr01_trace *p_tr)
	{
		memcpy( p_tr, &iv_reg, sizeof(struct wl_s_stru_gmr01_trace) );

	}


	void a_vnx(void)
	{
		if(iv_reg.ci<0) iv_reg.ci=0;
		
		

		on_vnx();
		if (iv_reg.pf!=NULL)
			(*iv_reg.pf)( (wlint8 *)this, (wlint8 *)cf_getreg() );
	}


	void a_vna(void)
	{
		struct wl_s_stru_gmr01_trace tr;

		--iv_vna_iii;
		if(iv_reg.bsy) return ;

		cf_push3(iv_reg.ci=iv_vna_iii);

		on_vna();
		if (iv_reg.pf!=NULL)
			(*iv_reg.pf)( (wlint8 *)this, (wlint8 *)cf_getreg() );

		
		if(ivp_trace!=NULL&&!iv_reg.bsy){
			cf_reg2tr(&tr);
			tr.id= ivp_trace->cf_howmany();
			tr.aob= 'a';
			tr.qa= tr.q;
			tr.aoff= ivp_trace->cf_howmany();
			ivp_trace->cf_add( (wlint8 *)&tr, sizeof(struct wl_s_stru_gmr01_trace) );
		}
	}


	void a_vnb(void)
	{
		struct wl_s_stru_gmr01_trace tr, *t;
		wlint32 i, j;

		if(iv_reg.bsy) return ;

		cf_pop3( &(iv_reg.ci) );

		on_vnb();
		if (iv_reg.pf!=NULL)
			(*iv_reg.pf)( (wlint8 *)this, (wlint8 *)cf_getreg() );

		if(ivp_trace!=NULL&&!iv_reg.bsy){
			cf_reg2tr(&tr);

			for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
				t = (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(i) );
				if(t->ci==iv_reg.ci){			 
					t->q = tr.q = iv_reg.q - 1;
					t->rc = tr.rc;
					tr.cx = t->cx;
					t->ecd = tr.ecd;
					tr.qa = t->qa;
					tr.aoff= t->aoff;
					tr.boff = t->boff = ivp_trace->cf_howmany();
					break;
				}
			}

			tr.id= ivp_trace->cf_howmany();
			tr.aob= 'b';

			ivp_trace->cf_add( (wlint8 *)&tr, sizeof(struct wl_s_stru_gmr01_trace) );
		}

	}


	void a_tc(void)
	{
		wluint8 c, *cset;
		wlint32 i, len;

		cset = (wluint8 *)stm_buf.cf_read(2);
		
		len = *(wlint32 *)stm_buf.cf_read(3);

		c = ivp_prg->cf_read(iv_reg.q);

		
		if(ivp_prg->cf_eof()) {
			iv_reg.rc=0;
			return;
		}

		if(0!=iv_reg.lmt){
			
			if(iv_reg.q>=iv_reg.lmtqa+iv_reg.lmt){
				iv_reg.rc=0;
				return;
			}
		}

		iv_reg.q++;

		for(i=0;i<len;i++){
			if(cset[i]==c) {
				iv_reg.rc=1;
				return ;
			}
		}

		iv_reg.rc=0;
		return;
	}


	void a_tca(void)
	{
		wluint8 x1,x2, c, *cset;
		wlint32 len;

		cset = (wluint8 *)stm_buf.cf_read(2);
		
		len = *(wlint32 *)stm_buf.cf_read(3);

		x1=x2=0;
		if(len>=1) { x1=cset[0];			 }
		if(len>=2) { x1=cset[0]; x2=cset[1]; }

		c = ivp_prg->cf_read(iv_reg.q);

		
		if(ivp_prg->cf_eof()) {
			iv_reg.rc=0;
			return;
		}

		if(0!=iv_reg.lmt){
			
			if(iv_reg.q>=iv_reg.lmtqa+iv_reg.lmt){
				iv_reg.rc=0;
				return;
			}
		}

		iv_reg.q++;

		if(c>=x1&&c<=x2) { iv_reg.rc=1;	return; }

		iv_reg.rc=0;
		return;
	}


	void a_teof(void)
	{
		iv_reg.rc=0;
		if(iv_reg.q>=ivp_prg->cf_len())
			iv_reg.rc=1;
	}


	void a_teor(void)
	{
		iv_reg.rc=0;
		
		if(0!=iv_reg.lmt&&iv_reg.q>iv_reg.lmtqa+iv_reg.lmt) 	iv_reg.rc=1;
	}


	void a_tbsy(void)
	{
		wlint32 i;
		i = wl_stru_strf::str_atol(stm_buf.cf_read(2));
		iv_reg.rc = (iv_reg.bsy - i)>0;
	}


	void a_ci(void)	{iv_reg.ci = wl_stru_strf::str_atol(stm_buf.cf_read(2));}


	void a_cx(void)
	{
		if(iv_reg.bsy) return ;
		wlint32 i, *preg;
		wl_stru_list  *pl;
		wlint8 *s;

		s = stm_buf.cf_read(2);
		preg = &iv_reg.cx ;
		pl = ivp_cxl;
		i = wl_stru_strf::str_atol(s);
		if(pl==NULL){
			*preg = i;
		}else{
			i = pl->cf_sel(s);
			*preg = (i==-1)?pl->cf_add(s):i;
		}
	}


	void a_ecd(void)
	{
		if(iv_reg.bsy) return ;
		wlint32 i, *preg;
		wl_stru_list  *pl;
		wlint8 *s;

		s = stm_buf.cf_read(2);
		preg = &iv_reg.ecd ;
		pl = ivp_errl;
		i = wl_stru_strf::str_atol(s);
		if(pl==NULL){
			*preg = i;
		}else{
			i = pl->cf_sel(s);
			*preg = (i==-1)?pl->cf_add(s):i;
		}
	}


	void a_let(void)	{iv_reg.rc = wl_stru_strf::str_atol(stm_buf.cf_read(2));	}

	void a_eps(void)	{iv_reg.rc = 1;	}

	void a_not(void)	{iv_reg.rc = !iv_reg.rc;	}


	void a_lmt(void)
	{
		cf_push(iv_reg.lmtqa);
		cf_push(iv_reg.lmt);
		iv_reg.lmtqa = iv_reg.q;
		iv_reg.lmt = wl_stru_strf::str_atol(stm_buf.cf_read(2));
	}


	void a_lmtpop(void)
	{
		cf_pop(&(iv_reg.lmt));
		cf_pop(&(iv_reg.lmtqa));
	}


	void a_jt(void)
	{
		if(iv_reg.rc){
			iv_reg.pcx += wl_stru_strf::str_atol(stm_buf.cf_read(2));
			iv_reg.pcx--;
		}
	}

	void a_jf(void)
	{
		if(!iv_reg.rc) {
			iv_reg.pcx += wl_stru_strf::str_atol(stm_buf.cf_read(2));
			iv_reg.pcx--;
		}
	}

	void a_jmp(void) { iv_reg.pcx += wl_stru_strf::str_atol(stm_buf.cf_read(2));iv_reg.pcx--;}


	void a_bup(void)
	{
		cf_push(iv_reg.lmt);
		cf_push(iv_reg.q);
		cf_push(iv_reg.qa);
		cf_push(iv_reg.cx);
		cf_push(iv_reg.ecd);
		iv_reg.bsy++;
	}


	void a_bdn(void)
	{
		cf_pop(&(iv_reg.ecd));
		cf_pop(&(iv_reg.cx));
		cf_pop(&(iv_reg.qa));
		cf_pop(&(iv_reg.q));
		cf_pop(&(iv_reg.lmt));
		iv_reg.bsy--;
	}


	void a_push(void)
	{
		wlint8 *t;
		t = (wlint8 *)stm_buf.cf_read(2);
		if(0){;}
		else if( cf_equ(t, "rc") )
			cf_push(iv_reg.rc);
		else if( cf_equ(t, "pcx") )
			cf_push(iv_reg.pcx);
		else if( cf_equ(t, "pcy") )
			cf_push(iv_reg.pcy);
		else if( cf_equ(t, "qa") )
			cf_push(iv_reg.qa);
		else if( cf_equ(t, "q") )
			cf_push(iv_reg.q);
		else if( cf_equ(t, "lmt") )
			cf_push(iv_reg.lmt);
		else if( cf_equ(t, "bsy") )
			cf_push(iv_reg.bsy);
		else if( cf_equ(t, "ci") )
			cf_push(iv_reg.ci);
		else if( cf_equ(t, "cx") )
			cf_push(iv_reg.cx);
		else if( cf_equ(t, "ecd") )
			cf_push(iv_reg.ecd);
	}


	void a_pop(void)
	{
		wlint8 *t;
		t = (wlint8 *)stm_buf.cf_read(2);
		if(0){;}
		else if( cf_equ(t, "rc") )
			cf_pop(&(iv_reg.rc));
		else if( cf_equ(t, "pcx") )
			cf_pop(&(iv_reg.pcx));
		else if( cf_equ(t, "pcy") )
			cf_pop(&(iv_reg.pcy));
		else if( cf_equ(t, "qa") )
			cf_pop(&(iv_reg.qa));
		else if( cf_equ(t, "q") )
			cf_pop(&(iv_reg.q));
		else if( cf_equ(t, "lmt") )
			cf_pop(&(iv_reg.lmt));
		else if( cf_equ(t, "bsy") )
			cf_pop(&(iv_reg.bsy));
		else if( cf_equ(t, "ci") )
			cf_pop(&(iv_reg.ci));
		else if( cf_equ(t, "cx") )
			cf_pop(&(iv_reg.cx));
		else if( cf_equ(t, "ecd") )
			cf_pop(&(iv_reg.ecd));
	}


	void a_call(void)
	{
		iv_reg.rc = 100;
		

		cf_push2(iv_reg.pcx);
		cf_push2(iv_reg.pcy);
		cf_push2(iv_reg.ecd);
		iv_reg.pcy = wl_stru_strf::str_atol(stm_buf.cf_read(2));
		iv_reg.pcx=0;
	}


	void a_recf(void)
	{
		if(!iv_reg.bsy&&ivp_err!=NULL&&!iv_reg.rc) {
			ivp_err->cf_add( (wlint8 *)cf_getreg(), sizeof(struct wl_s_stru_gmr01_reg) );
		}
	}


	void a_rtn(void)
	{
		cf_pop2(&(iv_reg.ecd));
		cf_pop2(&(iv_reg.pcy));
		cf_pop2(&(iv_reg.pcx));
	}


	void a_rtnf(void)
	{
		if(!iv_reg.rc) a_rtn();
	}

	void a_bsyrtn(void)
	{
		if(iv_reg.bsy) a_rtn();
	}


protected:


	wlint8 *gen_idt02(void)
	{
		wlint8 *s=iv_gen_idt02_buf;
		
		wl_stru_strf::str_ltoa(++iv_idt02_iii, s+1);
		s[0]='W';
		return s;
	}


	virtual void on_vnx(void) {return ;}
	virtual void on_vna(void) {return ;}
	virtual void on_vnb(void) {return ;}


	void cf_reset(void)
	{
		wlpfucb	 lpf;
		wlint8  *lexdata;

		lpf=iv_reg.pf;
		lexdata=iv_reg.exdata;
		memset( (void *)&iv_reg, 0, sizeof(iv_reg) );
		iv_reg.pf=lpf;
		iv_reg.exdata=lexdata;

		iv_intstk.cf_clean( );
		iv_intstk2.cf_clean();
		iv_intstk3.cf_clean();
	}


public:

	wl_stru_sheet		*ivp_rom;
	wl_stru_vbary_rdr	*ivp_prg;
	wl_stru_list		*ivp_trace;
	wl_stru_list		*ivp_err;
	wl_stru_list		*ivp_errl;
	wl_stru_list		*ivp_cxl; 


public:

	wl_stru_gmr01()
	{
		cf_reset( );
		 ivp_rom=NULL;
		 ivp_prg=NULL;
		 ivp_trace=NULL;
		 ivp_err=NULL;
		 ivp_errl =NULL;
		 ivp_cxl =NULL;

		 iv_idt02_iii=0;
		 iv_vna_iii=0;
	}


	virtual ~wl_stru_gmr01()	{	;	}


	wl_s_stru_gmr01_reg *cf_getreg(void) { return &iv_reg ; }


	int cf_rom( wl_stru_sheet *ap_rom)
	{
		ivp_rom =ap_rom;
		return 1;
	}


	int cf_itfc( wl_stru_list *ap_trace,
				 wl_stru_list *ap_err,
				 wl_stru_list	*ap_errl,
				 wl_stru_list	*ap_cxl,
				 wlpfucb pf,
				 wlint8 *exdata		)
	{
		ivp_trace =ap_trace;
		ivp_err = ap_err;
		ivp_errl = ap_errl;
		ivp_cxl = ap_cxl;
		iv_reg.exdata=exdata;
		iv_reg.pf=pf;

		return 1;
	}


	void cf_debug(int flag)
	{
		if(!flag) return ;
		wlint8 *t;
		wlint8 *t1;
		FILE *fp;
		wl_s_stru_gmr01_reg *pr;
		t = stm_buf.cf_read(0);
		t1= stm_buf.cf_read(1);
		pr = (wl_s_stru_gmr01_reg *)&iv_reg;
		fp=fopen("k:\\dbg.txt", "ab");
		fprintf(fp, "%s %s\t"
					"pcy=%ld\t"
					"pcx=%ld\t"
					"rc=%ld\t"
					"bsy=%ld\t"
					"qa=%ld\t"
					"q=%ld\t"
					"lmt=%ld\t"
					"ecd=%ld\r\n",
						t,t1,
						pr->pcy,
						pr->pcx,
						pr->rc,
						pr->bsy,
						pr->qa,
						pr->q,
						pr->lmt,
						pr->ecd  );
		fclose(fp);
	}


	int cf_app(wl_stru_vbary_rdr *ap_prg)
	{
		ivp_prg =ap_prg;

		
		cf_reset( );

		
		if(ivp_trace!=NULL) ivp_trace->cf_clean();
		if(ivp_err !=NULL)	ivp_err->cf_clean();

		
		if(ivp_errl !=NULL){
			ivp_errl->cf_clean();
			ivp_errl->cf_add("");
		}
		if(ivp_cxl !=NULL){
			ivp_cxl->cf_clean();
			ivp_cxl->cf_add("");
		}

		
		cf_getstm_init();

		wlint8 *t;
		while(1){
			cf_getstm();
			iv_reg.pcx++;
			t = stm_buf.cf_read(0);
			if(0){;} 
			else if( cf_equ( t, "recf") )
				a_recf();
			else if( cf_equ( t, "rtnf") )
				a_rtnf();
			else if( cf_equ( t, "rtn") )
				a_rtn();
			else if( cf_equ( t, "rem") )
				continue;
			else if( cf_equ( t, "call") )
				a_call();
			else if( cf_equ( t, "bup") )
				a_bup();
			else if( cf_equ( t, "bdn") )
				a_bdn();
			else if( cf_equ( t, "vnx") )
				a_vnx();
			else if( cf_equ( t, "vna") )
				a_vna();
			else if( cf_equ( t, "vnb") )
				a_vnb();
			else if( cf_equ( t, "tc") )
				a_tc();
			else if( cf_equ( t, "tca") )
				a_tca();
			else if( cf_equ( t, "jt") )
				a_jt();
			else if( cf_equ( t, "jf") )
				a_jf();
			else if( cf_equ( t, "jmp") )
				a_jmp();
			else if( cf_equ( t, "teof") )
				a_teof();
			else if( cf_equ( t, "teor") )
				a_teor();
			else if( cf_equ( t, "tbsy") )
				a_tbsy();
			else if( cf_equ( t, "cx") )
				a_cx();
			else if( cf_equ( t, "ci") )
				a_ci();
			else if( cf_equ( t, "ecd") )
				a_ecd();
			else if( cf_equ( t, "let") )
				a_let();
			else if( cf_equ( t, "eps") )
				a_eps();
			else if( cf_equ( t, "not") )
				a_not();
			else if( cf_equ( t, "lmt") )
				a_lmt();
			else if( cf_equ( t, "lmtpop") )
				a_lmtpop();
			else if( cf_equ( t, "push") )
				a_push();
			else if( cf_equ( t, "pop") )
				a_pop();
			else if( cf_equ( t, "bsyrtn") )
				a_bsyrtn();
			else if( cf_equ( t, "halt")||cf_equ( t, "hlt") )
				break;

			
		}
		return iv_reg.rc;
	}


	wlint32 cf_gerr_pos(int rct )
	{
		struct wl_s_stru_gmr01_reg *t;
		wl_stru_list *pe;
		wlint32  row, col, total, i;
		wluint8 c;

		pe= ivp_err;
		row=col=total=i=0;

		if(pe==NULL||pe->cf_howmany()==0) return -1;
		t = (wl_s_stru_gmr01_reg *)pe->cf_read(0);
		total = t->q>0?t->q-1:0;

		for(i=total;i>=0;i--){
			c = ivp_prg->cf_read(i);
			
			if(col==0&&(c==0x0d||c==0x0a)) col++;
			if(c==0x0a) break;
			col++;
		}

		for(row++,i=total;i>=0;i--){
			c = ivp_prg->cf_read(i);
			if(c==0x0a) row++;
		}

		if(rct=='r'||rct=='R'||rct==1) return row;
		if(rct=='c'||rct=='C'||rct==2) return col;
		if(rct=='t'||rct=='T'||rct==3) return total;
		return total;
	}




	wlint32 br_hm(void)
	{
		if(ivp_trace==NULL) return 0;
		return  ivp_trace->cf_howmany() ;
	}


	wl_s_stru_gmr01_trace *br_tr(wlint32 h )
	{
		if(ivp_trace==NULL||h<0) return NULL;
		return  (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(h)) ;
	}


	long br_q1(wlint32 h)
	{
		struct wl_s_stru_gmr01_trace  *t;
		t = (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(h)) ;
		if(t==NULL) return -1;
		return t->qa;
	}


	long br_q2(wlint32 h)
	{
		struct wl_s_stru_gmr01_trace  *t;
		t = (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(h)) ;
		if(t==NULL) return -1;
		return t->q;
	}


	wlint8 *br_vt(wlint32 q1, wlint32 q2 )
	{
		return ivp_prg->cf_read( q1, q2 );
	}


	wlint8 *br_vt(wlint32 h)
	{
		struct wl_s_stru_gmr01_trace  *t;

		t = (wl_s_stru_gmr01_trace *)(ivp_trace->cf_read(h)) ;
		if(t==NULL) return ivp_prg->cf_read(1, 0);

		return ivp_prg->cf_read(t->qa, t->q); 
	}


	wlint32 br_std(wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='b') h = t->aoff;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='a') return h; else return -1 ;
	}


	wlint32 br_len(wlint32 h)
	{
		struct wl_s_stru_gmr01_trace  *t;
		t = br_tr(h);
		return t==NULL?0:t->q - t->qa + 1;
	}


	wlint32 br_ypr( wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		do{
			if(t->aob=='b') h = t->aoff;
			if(h<0) return -1;

			h--;
			if(h<0) return -1;

			t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
			if(t==NULL) return -1;

		} while(t->aob!='a');

		return h ;
	}


	wlint32 br_yne(wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='b') h = t->aoff;
		if(h<0) return -1;

		h++;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		return t->aob=='a'?h:-1;
	}


	wlint32 br_xpr(wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='b') h = t->aoff;
		if(h<0) return -1;

		h--;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='a') return -1;

		h = t->aoff;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		return h ;
	}


	wlint32 br_xne(wlint32 h )
	{
		struct wl_s_stru_gmr01_trace  *t;
		wl_stru_list *ptrace;

		ptrace= ivp_trace;

		if(ptrace==NULL) return -1;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='a') h = t->boff;
		if(h<0) return -1;

		h++;
		if(h<0) return -1;

		t = (wl_s_stru_gmr01_trace *)(ptrace->cf_read(h)) ;
		if(t==NULL) return -1;

		if(t->aob=='a') return h;

		return -1 ;
	}


	wlint32 br_yfst(wlint32 h)
	{
		wlint32 h1;
		h1=-1;
		for(h=br_std(h); -1!=h; h=br_ypr(h)) h1=h;
		return h1;
	}


	wlint32 br_xfst(wlint32 h)
	{
		wlint32 h1;
		h1=-1;
		for(h=br_std(h); -1!=h; h=br_xpr(h)) h1=h;
		return h1;
	}


	wlint32 br_ylast(wlint32 h)
	{
		wlint32 h1;
		h1=-1;
		for(h=br_std(h); -1!=h; h=br_yne(h)) h1=h;
		return h1;
	}


	wlint32 br_xlast(wlint32 h)
	{
		wlint32 h1;
		h1=-1;
		for(h=br_std(h); -1!=h; h=br_xne(h)) h1=h;
		return h1;
	}


	int br_isycat(wlint32 h1, wlint32 h2)
	{
		wlint32 hh1,hh2;

		if(br_std(h1)<0||br_std(h2)<0) return 0;

		hh1 = br_std(h1);
		hh2 = br_std(h2);
		do {
			if( br_std(hh1)==hh2 ) return 1;
			hh1=br_ypr(hh1);
		}while(hh1!=-1);

		hh1 = br_std(h2);
		hh2 = br_std(h1);
		do {
			if( br_std(hh1)==hh2 ) return 1;
			hh1=br_ypr(hh1);
		}while(hh1!=-1);

		return 0;
	}


	int br_isxcat(wlint32 h1, wlint32 h2)
	{
		h1 = br_xfst(h1);
		h2 = br_std(h2);
		if(h1<0||h2<0) return 0;
		do {
			if(h1==h2) return 1;
			h1=br_xne(h1);
		}while(h1!=-1);

		return 0;
	}


	int br_a(wlint32 h) 
	{
		if(br_std(h)<0) return 0;
		return br_tr(h)->aob=='a';
	}



	wlint32 cxl_l(wlint32 h) 
	{
		if(br_std(h)<0) return -1;
		return br_tr(h)->cx;
	}


	wlint8 *cxl_s(wlint32 h) 
	{
		static char p[]="";
		if(br_std(h)<0||ivp_cxl==NULL) return p;
		return  ivp_cxl->cf_read(cxl_l(h));
	}


	wlint32 cxl_h(wlint32 h, wlint32 l, int forward, int wholelayer)
	
	{
		if(wholelayer) h=forward?br_xfst(h):br_xlast(h);
		else h = br_std(h);
		for(; -1!=h; h=forward?br_xne(h):br_xpr(h) ) {
			if(cxl_l(h)==-1) break;
			if(cxl_l(h)== l) return  h ;
		}
		return -1;
	}


	wlint32 cxl_h(wlint32 h, wlint8 *name, int forward, int wholelayer)
	
	{
		if(wholelayer) h=forward?br_xfst(h):br_xlast(h);
		else h = br_std(h);
		for(; -1!=h; h=forward?br_xne(h):br_xpr(h) )
		{
			if(cxl_l(h)==-1) break;
			if( !strcmp(cxl_s(h),name)) return h;
		}
		return -1;
	}


	wlint32 cxl_hm(wlint32 h, wlint32 l) 
	{
		wlint32 i;
		for(i=0,h=br_xfst(h); -1!=h; h=br_xne(h))
		{
			if(cxl_l(h)==-1) break;
			if(cxl_l(h)==l) i++;
		}
		return i;
	}


	wlint32 cxl_hm(wlint32 h, wlint8 *name) 
	{
		wlint32 i;
		for(i=0,h=br_xfst(h); -1!=h; h=br_xne(h)) {
			if(cxl_l(h)==-1) break;
			if( !strcmp(cxl_s(h),name)) i++;
		}
		return i;
	}


	

	wlint32 erl_l(wlint32 h)
	{
		wl_s_stru_gmr01_reg  *pr;

		if(h<0||h>=ivp_err->cf_howmany()) return -1;

		pr = (wl_s_stru_gmr01_reg *)(ivp_err->cf_read(h));
		return pr->ecd;
	}


	wlint8 *erl_s(wlint32 h)
	{
		static char p[]="";
		if(h<0||h>=ivp_err->cf_howmany()||ivp_errl==NULL) return p;
		return  ivp_errl->cf_read(erl_l(h));
	}




	static void output_trace(wlint8 *pfn, wl_stru_list *aap_tr)
	{
		wlint32  y;
		struct wl_s_stru_gmr01_trace *pt;
		FILE * fp;

		fp=fopen(pfn, "w");

		if(aap_tr==NULL)
			fprintf(fp, "(null)");
		else
			for(y=0;y<aap_tr->cf_howmany();y++) {
				pt = (wl_s_stru_gmr01_trace *)aap_tr->cf_read(y);
				fprintf(fp, "%ld\t"
							"rc=%ld\t"
							"id=%ld\t"
							"pcy=%ld\t"
							"qa=%ld\t"
							"q=%ld\t"
							"lmt=%ld\t"
							"aob=%c\t"
							"ci=%ld\t"
							"cx=%ld\t"
							"ecd=%ld\t"
							"aoff=%ld\t"
							"boff=%ld",
								y,
								pt->rc,
								pt->id,
								pt->pcy,
								pt->qa,
								pt->q,
								pt->lmt,
						(wlint8)pt->aob,
								pt->ci,
								pt->cx,
								pt->ecd,
								pt->aoff,
								pt->boff	);

				fprintf(fp,"\n");
			}
		fclose(fp);
		return ;
	}

	friend  void gmr01_output_trace1(wlint8 *pfn, wl_stru_gmr01 *p)
	{
		wl_stru_list *aap_tr;
		wlint32  y;
		struct wl_s_stru_gmr01_trace *pt;
		FILE * fp;

		aap_tr = p->ivp_trace;

		fp=fopen(pfn, "w");

		if(aap_tr==NULL)
			fprintf(fp, "(null)");
		else
			for(y=0;y<aap_tr->cf_howmany();y++) {
				pt = (wl_s_stru_gmr01_trace *)aap_tr->cf_read(y);
				fprintf(fp, "%ld\t"
							"rc=%ld\t"
							"id=%ld\t"
							"pcy=%ld\t"
							"qa=%ld\t"
							"q=%ld\t"
							"lmt=%ld\t"
							"aob=%c\t"
							"ci=%ld\t"
							"ecd=%ld\t"
							"aoff=%ld\t"
							"boff=%ld\t"
							"cx=%ld(%s)",
								y,
								pt->rc,
								pt->id,
								pt->pcy,
								pt->qa,
								pt->q,
								pt->lmt,
						(wlint8)pt->aob,
								pt->ci,
								pt->ecd,
								pt->aoff,
								pt->boff,
								pt->cx, p->cxl_s(y) );

				fprintf(fp,"\n");
			}
		fclose(fp);
		return ;
	}


	static void output_err(wlint8 *pfn, wl_stru_list *ap_er)
	{
		FILE *fp;
		wlint32  y;
		wl_s_stru_gmr01_reg *pr;

		fp=fopen(pfn, "w");

		if(ap_er==NULL)
			fprintf(fp, "(null)");
		else
			for(y=0;y<ap_er->cf_howmany();y++) {
				pr = (wl_s_stru_gmr01_reg *)ap_er->cf_read(y);
				fprintf(fp, "%ld\t"
							"rc=%ld\t"
							"pcx=%ld\t"
							"pcy=%ld\t"
							"qa=%ld\t"
							"q=%ld\t"
							"lmt=%ld\t"
							"ecd=%ld\n",
								y,
								pr->rc,
								pr->pcx,
								pr->pcy,
								pr->qa,
								pr->q,
								pr->lmt,
								pr->ecd  );
			}
		fclose(fp);
		return ;
	}


}; 

#endif


#ifndef WL_STRU_GMR02_H
#define WL_STRU_GMR02_H


class wl_stru_gmr02 : protected wl_stru_gmr01  {

private:

	void knl_prg(wl_stru_vbary_rdr *a_prg)
	{
		char s[]=
            "rem~S	call~41	recf	rtnf	bup	call~11	bdn	jt~-6	eps	rtn	rem~_版本V2.1	\r\n"
            "rem~一个标识符首字符	tc~ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz	rtn																\r\n"
            "rem~一个标识符中字符	tc~0_123456789ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz	rtn																\r\n"
            "rem~一个任意字符	tc~a	teof	not	rtn														\r\n"
            "rem~或号	tc~|	rtn																\r\n"
            "rem~加号	tc~+	rtn																\r\n"
            "rem~等号	tc~=	rtn																\r\n"
            "rem~分号	tc~;	rtn																\r\n"
            "rem~0D0A	tc~b0d	tc~b0a																\r\n"
            "rem																		\r\n"
            "rem~标识符pkg	vna	call~14	vnb	rtn														\r\n"
            "rem~标识符1	call~2	rtn																\r\n"
            "rem~标识符2	call~3	rtnf	bup	call~3	bdn	jt~-5	eps	rtn										\r\n"
            "rem~标识符	call~12	recf	rtnf	bup	call~13	bdn	jt~2	jf~4	call~13	recf	rtn	eps	rtn					\r\n"
            "rem																		\r\n"
            "rem																		\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem~嵌入G01指令语句pkg	vna	call~26	vnb	rtn								\r\n"
            "rem~[号	tc~[	rtn										\r\n"
            "rem~]号	tc~]	rtn										\r\n"
            "rem~嵌入G01指令pkg	vna	call~25	vnb	rtn								\r\n"
            "rem~嵌入G01指令	bup	call~23	bdn	jt~2	jf~2	rtn	call~4	rtnf	jmp~-8			\r\n"
            "rem~嵌入G01指令语句	call~22	recf	rtnf	call~24	recf	rtnf	call~23	recf	rtnf	rtn		\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem												\r\n"
            "rem~产生式右部	bup	call~33	bdn	jf~4	call~33	rem~recf	rtn	call~34	rem~recf	rtn	rem~或结构,但要加上recf	\r\n"
            "rem~一个运算元素	bup	call~21	bdn	jf~3	call~21	rtn	call~11	rtn				\r\n"
            "rem~或式	cx~2	call~32	recf	rtnf	call~5	recf	rtnf	call~32	recf	rtnf	call~5	recf	rtnf	call~32	recf	rtnf	rtn	\r\n"
            "rem~加式	cx~3	call~32	recf	rtnf	bup	call~35	bdn	jf~5	call~35	recf	rtnf	rtn	eps	rtn							\r\n"
            "rem~加式2	call~6	recf	rtnf	call~32	recf	rtnf	bup	call~6	bdn	jt~-9	eps	rtn									\r\n"
            "rem																					\r\n"
            "rem																					\r\n"
            "rem																					\r\n"
            "rem																					\r\n"
            "rem																					\r\n"
            "rem~一个完整行pkg	cx~1	vna	call~42	vnb	rtn																\r\n"
            "rem~一个完整行	call~11	recf	rtnf	call~7	recf	rtnf	call~31	recf	rtnf	call~8	recf	rtnf	bup	call~9	bdn	jf~4	call~9	recf	rtnf	eps	rtn\r\n"
		;
		a_prg->cf_opens(s);
		return ;
	}


	int g01_cf_wmk(wl_stru_vbary_rdr *ap_prg, wl_stru_sheet *ap_objrom)
	
	{
		wl_stru_prpt aa;
		int fillz;

		fillz=1;
		ap_objrom->cf_clean();
		aa.cf_let("cmdall", ap_prg->cf_read() );
		aa.cf_repl("cmdall", "\t", " ", 1);
		aa.cf_repl("cmdall", "\r", "", 1);
		ap_objrom->cf_import_str( aa.cf_get("cmdall"), " ", "\n");

		if(fillz){
			wlint32 i;
			wl_stru_list *p;
			char s[33];

			ap_objrom->cf_getsheetknl()->cf_rev();
			ap_objrom->cf_import_str("rem~vna call~1 rem~vnb halt", " ", "\n" );
			ap_objrom->cf_getsheetknl()->cf_rev();

			for(i=0;i<ap_objrom->cf_rowcount();i++) {
				p=ap_objrom->cf_getrow(i);
				p->cf_rev();
				sprintf(s, "rem~auto.%ld", i);
				p->cf_add(s);
				p->cf_rev();
			}
		}
		return 1;
	}


	int yy_chk1(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list l1,l2;
		wlint32 i,j,h;

		for(h=0; -1!=h; h=br_xne(h)) {
			l1.cf_add( br_vt(br_yne(h)) );
		}
		l1.cf_qsort();

		for(i=0,j=l1.cf_howmany();i<j-1;i++){ 
			if(!wl_stru_strf::str_cmp(l1.cf_read(i), l1.cf_read(i+1)))
				l2.cf_add(l1.cf_read(i));
		}
		l2.cf_setuniq();

		j=l2.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("产生式左侧的VN有重复");
			for(i=0;i<l2.cf_howmany();i++) ap_ermsg->cf_add(l2.cf_read(i));
			return 0;
		}
		return 1;
	}


	int yy_chk2(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list vnleft, vnright;
		wlint32 i,j,h;
		wl_s_stru_gmr01_trace  *pt;

		
		for(h=0; -1!=h; h=br_xne(h)) {
			vnleft.cf_add( br_vt(br_yne(h)) );
		}
		vnleft.cf_setuniq();

		
		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->pcy==11 && pt->aob=='a' && pt->cx>=2){
				vnright.cf_add( br_vt(i) );
			}
		}
		vnright.cf_setuniq();
		
		vnright.cf_setcha(&vnleft);

		j=vnright.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("存在未说明的VN");
			for(i=0;i<vnright.cf_howmany();i++) ap_ermsg->cf_add(vnright.cf_read(i));
			return 0;
		}

		return 1;
	}


	int yy_ins1ele(wlint32 ai_idx, wl_stru_list *ap_glist, wl_stru_list *ap_vnlist, wl_stru_list *ap_objrow, wl_stru_list *ap_ermsg)
	{
		wlint8 *t, s[33];
		wlint8 *t1, c;
		wlint32 j;

		t = ap_glist->cf_read(ai_idx);
		if(*t=='['){
			
			if(t[strlen(t)-1]==']'){
				t1 = t+1;
				c = t[strlen(t)-1];
				t[strlen(t)-1]='\0';
				ap_objrow->cf_add(t1);
				t[strlen(t)]=c;
				if( !strncmp(t1, "rem",		3)		||
					!strncmp(t1, "bsyrtn",	6)	||
					!strncmp(t1, "vna",		3)	||
					!strncmp(t1, "vnb",		3)	||
					!strncmp(t1, "eps",		3)	||
					!strncmp(t1, "ecd",		3)	||
					!strncmp(t1, "cx",		2)	||
					!strncmp(t1, "ci",		2)  ||
					!strncmp(t1, "push",	4)
				  )
					return 99; 
			}else{
				ap_objrow->cf_add(t);
			}
		}else{
			j=ap_vnlist->cf_sel(t);
			if(j==-1){
				ap_ermsg->cf_add(15+wl_stru_strf::str_len(t));
				sprintf(ap_ermsg->cf_readtop(), "vnlist内部错误!%s不存在.", t);
				return 0;
			}
			sprintf(s, "call~%ld", j);
			ap_objrow->cf_add(s);
		}
		return 1;
	}


	int yy_lnk(wl_stru_sheet *ap_objrom, wl_stru_list *ap_ermsg	)
	{
		wl_stru_list vnlist, glist, *objrow;
		wlint32 i,j,h;
		wl_s_stru_gmr01_trace *pt;
		wl_stru_prpt aa;

		
		vnlist.cf_add(" ");
		for(h=0; -1!=h; h=br_xne(h)) {
			vnlist.cf_add( br_vt(br_yne(h)) );
		}

		
		ap_objrom->cf_clean();
		for(i=0,j=vnlist.cf_howmany();i<j;i++) ap_objrom->cf_addrow();
		objrow = ap_objrom->cf_getrow(0);
		objrow->cf_add("rem~GMR02");
		
		objrow->cf_add("call~1");
		objrow->cf_add("halt");

		wlint8 c1[33];
		
		for(h=0; -1!=h; h=br_xne(h)) {
			
			glist.cf_clean();
			i = br_xne(br_yne(h));
			pt = (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->cx==2) glist.cf_add("|"); else glist.cf_add("+"); 
			i = br_yne(h);
			glist.cf_add( br_vt(i) );								
			for(i=br_xne(i);-1!=i;i=br_xne(i)){						
				glist.cf_add( br_vt(i) );
			}
			

			j=vnlist.cf_sel(glist.cf_read(1));
			if(j==-1){
				ap_ermsg->cf_add("vnlist列表损坏!");
				return 0;
			}
			objrow = ap_objrom->cf_getrow(j);

			
			aa.cf_let("t", "rem~");
			aa.cf_cat("t", glist.cf_read(1));
			aa.cf_cat("t", "(");
			aa.cf_cat("t", wl_stru_strf::str_ltoa(j,c1));
			aa.cf_cat("t", ")");
			objrow->cf_add(aa.cf_get("t"));

			
			if(*glist.cf_read(0)=='|'){
				objrow->cf_add("bup");

				if(!yy_ins1ele(2, &glist, &vnlist, objrow, ap_ermsg)) return 0;

				objrow->cf_add("bdn");
				objrow->cf_add("jf~4");

				if(!yy_ins1ele(3, &glist, &vnlist, objrow, ap_ermsg)) return 0;

				objrow->cf_add("recf");
				objrow->cf_add("rtn");

				if(!yy_ins1ele(4, &glist, &vnlist, objrow, ap_ermsg)) return 0;

				objrow->cf_add("recf");
				objrow->cf_add("rtn");

			}

			if(*glist.cf_read(0)=='+'){

				int subrc;

				for(i=2;i<glist.cf_howmany();i++){

					subrc = yy_ins1ele(i, &glist, &vnlist, objrow, ap_ermsg);

					if(!subrc) return 0;

					if(subrc==99){
						
						
					}else{
						objrow->cf_add("recf");
						if(i!=glist.cf_howmany()-1) objrow->cf_add("rtnf");
					}

				}
				objrow->cf_add("rtn");
			}

		}

		return 1 ;
	}


protected:

	void cf_emsg(wl_stru_list *ap_ermsg, wlint32 col)
	
	
	{
		char s[99];
		wlint32 y;
		wl_s_stru_gmr01_reg  *pr;

		sprintf(s, "第%ld行，第%ld字节，总第%ld字节.", cf_gerr_pos('r'), cf_gerr_pos('c'), cf_gerr_pos('t') );
		ap_ermsg->cf_add(s);
		for(y=0;y<ivp_err->cf_howmany();y++) {
			pr = (wl_s_stru_gmr01_reg *)(ivp_err->cf_read(y));
			ap_ermsg->cf_add(ivp_rom->cf_getele(pr->pcy, col) );
		}
	}


public:


	int cf_wmk( wl_stru_sheet		*ap_vmrom,
				wl_stru_vbary_rdr	*ap_prg,
				wl_stru_list		*ap_tr,
				wl_stru_sheet		*ap_obj,
				wl_stru_list		*ap_er,
				wl_stru_list		*ap_ermsg	)
	{
		int rc;
		wl_stru_vbary_rdr	prg01;

		
		knl_prg(&prg01);
		rc = g01_cf_wmk(&prg01, ap_vmrom );
		if(!rc) return 0;

		
		cf_rom(ap_vmrom);
		cf_itfc(ap_tr, ap_er, NULL, NULL, NULL, NULL);
		rc = cf_app(ap_prg);
		if(!rc) {
			cf_emsg(ap_ermsg, 1);
			return 0;
		}


		
		rc = yy_chk1(ap_ermsg);
		if(!rc) return 0;

		rc= yy_chk2(ap_ermsg);
		if(!rc) return 0;

		rc= yy_lnk(ap_obj, ap_ermsg);
		if(!rc) return 0;

		return 1;
	}


}; 

#endif


#ifndef WL_STRU_GMR03_H
#define WL_STRU_GMR03_H


class wl_stru_gmr03 : protected wl_stru_gmr02  {

private:

    wl_stru_list gname;
    wl_stru_list glist;
    wl_stru_prpt idt_trans;


	void knl_prg(wl_stru_vbary_rdr *ap_prg)
	{
		char s[]=
             "S=prg+[rem~_版本V1.2];		\r\n"
             "prg=G1|prg1|[eps];		\r\n"
             "prg1=G+prg;		\r\n"
             "G1=idt+SYM_equ;		\r\n"
             "G=[cx~99]+[vna]+idt+[vnb]+SYM_equ+EE+[rem~产生式是标识符=表达句；];		\r\n"
             "EE=Etime|Etime|EE1;		\r\n"
             "EE1=Eadd|Eadd|EE2;		\r\n"
             "EE2=Eif|Eif|EE3;		\r\n"
             "EE3=Enot|Enot|EE4;		\r\n"
             "EE4=Eand|Eand|EE5;		\r\n"
             "EE5=Eor|Eor|Efor;		\r\n"
             "Efor=[cx~7]+E7+SYM_fen+SYM_cr+[rem~for表达句];		\r\n"
             "E7=[tc~fF]+[tc~oO]+[tc~rR]+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b;		\r\n"
             "Eor=[cx~6]+E6+SYM_fen+SYM_cr+[rem~or表达句];		\r\n"
             "E6=[tc~oO]+[tc~rR]+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b;		\r\n"
             "Eand=[cx~5]+E5+SYM_fen+SYM_cr+[rem~and表达句];		\r\n"
             "E5=[tc~aA]+[tc~nN]+[tc~dD]+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b;\r\n"
             "Enot=[cx~4]+E4+SYM_fen+SYM_cr+[rem~not表达句];\r\n"
             "E4=[tc~nN]+[tc~oO]+[tc~tT]+SYM_k1a+ele+SYM_K1b;\r\n"
             "Eif=[cx~3]+E3+SYM_fen+SYM_cr+[rem~if表达句];\r\n"
             "E3=[tc~iI]+[tc~fF]+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b+SYM_k1a+ele+SYM_K1b;\r\n"
             "Eadd=[cx~2]+E2+SYM_fen+SYM_cr+[rem~全加表达句];\r\n"
             "E2=ele+E21+[rem~全加表达式];\r\n"
             "E21=SYM_add|E22|[eps];\r\n"
             "E22=SYM_add+ele+E21;\r\n"
             "Etime=[cx~1]+E1+SYM_fen+SYM_cr+[rem~乘法表达句];\r\n"
             "E1=ele+SYM_add+ele+E11+[rem~乘法表达式但首元素为加];\r\n"
             "E11=SYM_or|E12|[eps];\r\n"
             "E12=SYM_or+ele+E11;\r\n"
             "ele=[vna]+ele1+[vnb];\r\n"
             "ele1=ebd|ebd|idt;\r\n"
             "idt=CNidt;\r\n"
             "ebd=SYM_k2a+ebd1+SYM_K2b;\r\n"
             "not_right_kuo=SYM_K2b|[let~0]|[eps];\r\n"
             "ebd1=not_right_kuo|ebd2|[eps];\r\n"
             "ebd2=EBDletter+ebd1;\r\n"
             "EBDletter=CNletter|CNletter|ASC7letter;\r\n"
             "ASC7letter=[tca~b10b7F];\r\n"
             "CNidt=CNletter+Ci1;\r\n"
             "Ci1=CNletter|Ci2|[eps];\r\n"
             "Ci2=CNletter+Ci1;\r\n"
             "CNletter=HZ|HZ|ENletter;\r\n"
             "HZ=[tca~b80bFF]+[tca~b40bFF];\r\n"
             "ENidt=ENletter+Ei1;\r\n"
             "Ei1=ENletter|Ei2|[eps];\r\n"
             "Ei2=ENletter+Ei1;\r\n"
             "ENletter=[tc~0_123456789ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz];\r\n"
             "SYM_add=[tc~+];\r\n"
             "SYM_or=[tc~|];\r\n"
             "SYM_equ=[tc~=];\r\n"
             "SYM_cr=SYM_cr2|SYM_cr2|SYM_cr1;\r\n"
             "SYM_cr1=[tc~b0d]+[tc~b0a];\r\n"
             "SYM_cr2=SYM_cr1+SYM_cr1;\r\n"
             "SYM_fen=[tc~;];\r\n"
             "SYM_k1a=[tc~(];\r\n"
             "SYM_K1b=[tc~)];\r\n"
             "SYM_k2a=[tc~b5b];\r\n"
             "SYM_K2b=[tc~b5d];\r\n"
		 ;
		wl_stru_prpt	pp;

		

		pp.cf_let("prg", s);
		pp.cf_repl("prg", " ", "", 1);
		pp.cf_repl("prg", "\t", "", 1);

		ap_prg->cf_close();
		ap_prg->cf_opens(pp.cf_get("prg"));
		return ;
	}


	int yy_chk1(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list l1,l2;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;

		
		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->cx==99 && pt->aob=='a') l1.cf_add( br_vt(i) );
		}
		l1.cf_qsort();

		for(i=0,j=l1.cf_howmany();i<j-1;i++){ 
			if(!wl_stru_strf::str_cmp(l1.cf_read(i), l1.cf_read(i+1)))
				l2.cf_add(l1.cf_read(i));
		}
		l2.cf_setuniq();

		j=l2.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("产生式左侧的VN有重复");
			for(i=0;i<l2.cf_howmany();i++) ap_ermsg->cf_add(l2.cf_read(i));
			return 0;
		}
		return 1;
	}


	int yy_chk2(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list vnleft, vnright;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;
		wlint8 *s;

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->cx==99 && pt->aob=='a') vnleft.cf_add( br_vt(i) );
			if(pt->cx!=99 && pt->aob=='a'){
				s = br_vt(i);
				if(s[0]!='[') vnright.cf_add(s);
			}
		}
		vnleft.cf_setuniq();
		vnright.cf_setuniq();
		vnright.cf_setcha(&vnleft);

		j=vnright.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("存在未说明的VN");
			for(i=0;i<vnright.cf_howmany();i++) ap_ermsg->cf_add(vnright.cf_read(i));
			return 0;
		}

		return 1;
	}


	int yy_g1( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E,A;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
			A.cf_add( gen_idt02() );
		}

		
		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "+");
		g.cf_cat("a", A.cf_read(0));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		for(i=0;i<(j-1);i++){
			if(i==j-1-1){
				g.cf_let("a", A.cf_read(i));
				g.cf_cat("a", "=");
				g.cf_cat("a", A.cf_read(i+1));
				g.cf_cat("a", ";");
			}else{
				g.cf_let("a", A.cf_read(i));
				g.cf_cat("a", "=");
				g.cf_cat("a", E.cf_read(i+1));
				g.cf_cat("a", "|");
				g.cf_cat("a", E.cf_read(i+1));
				g.cf_cat("a", "|");
				g.cf_cat("a", A.cf_read(i+1));
				g.cf_cat("a", ";");
			}
			ap_prg02_l->cf_add(g.cf_get("a"));
		}
		g.cf_let("a", A.cf_read(i));
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(i));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "~1句型!];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g2( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}

		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");

		for(i=0;i<(j-1);i++){
			g.cf_cat("a", E.cf_read(i));
			g.cf_cat("a", "+");
		}
		g.cf_cat("a", E.cf_read(i));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g3( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}

		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");

		for(i=0;i<(j-1);i++){
			g.cf_cat("a", E.cf_read(i));
			g.cf_cat("a", "|");
		}
		g.cf_cat("a", E.cf_read(i));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g4( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}

		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");

		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "|[let~0]|[eps];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g5( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E,A;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}
		A.cf_add( gen_idt02() );

		
		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "|");
		g.cf_cat("a", A.cf_read(0));
		g.cf_cat("a", "|[let~0];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		g.cf_let("a", A.cf_read(0));
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(1));
		g.cf_cat("a", "|[eps]|[let~0];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g6( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E,A;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}
		A.cf_add( gen_idt02() );

		
		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "|[eps]|");
		g.cf_cat("a", A.cf_read(0));
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		g.cf_let("a", A.cf_read(0));
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(1));
		g.cf_cat("a", "|[eps]|[let~0];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_g7( wl_stru_list *ap_prg02_l)
	{
		wl_stru_prpt g;
		wl_stru_list E,A;
		wlint32 i,j;
		wlint8 *t;

		for(i=0,j=glist.cf_howmany();i<j;i++){
			t = glist.cf_read(i);
			E.cf_add( t[0]=='['?t:idt_trans.cf_get(t) );
		}
		A.cf_add( gen_idt02() );

		
		t = gname.cf_readtop();
		g.cf_let("a", idt_trans.cf_get(t) );
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(0));
		g.cf_cat("a", "|");
		g.cf_cat("a", A.cf_read(0));
		g.cf_cat("a", "|[eps];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		g.cf_let("a", A.cf_read(0));
		g.cf_cat("a", "=");
		g.cf_cat("a", E.cf_read(1));
		g.cf_cat("a", "+");
		g.cf_cat("a", idt_trans.cf_get(t) );
		g.cf_cat("a", ";");
		ap_prg02_l->cf_add(g.cf_get("a"));

		
		g.cf_let("a", gen_idt02());
		g.cf_cat("a", "=[rem~");
		g.cf_cat("a", gname.cf_readtop());
		g.cf_cat("a", "];");
		ap_prg02_l->cf_add(g.cf_get("a"));

		return 1;
	}


	int yy_lnk02(wl_stru_list *ap_prg02_l, wl_stru_list *ap_ermsg)
	{
		int gtype;
		wlint32 i,j;
		wl_s_stru_gmr01_trace *ptr;

		idt_trans.cf_clean();
		idt_trans.cf_getknl()->cf_setsortf(ivp_trace->iv_mycmp);
		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) { 
			ptr= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(ptr->aob=='a') idt_trans.cf_let(br_vt(i), gen_idt02() );
		}

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			ptr= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(ptr->cx==99 && ptr->aob=='a'){
				gname.cf_clean();
				glist.cf_clean();
				gname.cf_add( br_vt(i) );
				ptr= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i+2);
				gtype = ptr->cx;
				for(i+=2;;i+=2){
					if(-1==br_std(i)) break;
					ptr= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
					if(ptr->cx==99) break;
					glist.cf_add( br_vt(i) );
				}
				i--;
				
				
				if(gtype==1&&!yy_g1(ap_prg02_l)) return 0;
				if(gtype==2&&!yy_g2(ap_prg02_l)) return 0;
				if(gtype==3&&!yy_g3(ap_prg02_l)) return 0;
				if(gtype==4&&!yy_g4(ap_prg02_l)) return 0;
				if(gtype==5&&!yy_g5(ap_prg02_l)) return 0;
				if(gtype==6&&!yy_g6(ap_prg02_l)) return 0;
				if(gtype==7&&!yy_g7(ap_prg02_l)) return 0;
			}
		}

		return 1;
	}


public:


	int cf_wmk( wl_stru_sheet		*ap_vmrom,
				wl_stru_vbary_rdr	*ap_prg,
				wl_stru_list		*ap_tr,
				wl_stru_sheet		*ap_obj,
				wl_stru_list		*ap_er,
				wl_stru_list		*ap_ermsg	)
				
	{
		int rc;
		wl_stru_vbary_rdr	prg02;

		wl_stru_sheet	vmrom02;
		wl_stru_list	tr02;
		wl_stru_list	prg02_l;

		
		knl_prg(&prg02);
		rc = wl_stru_gmr02::cf_wmk(&vmrom02, &prg02, &tr02, ap_vmrom, ap_er, ap_ermsg);
		if(!rc) {
			ap_ermsg->cf_rev();
			ap_ermsg->cf_add("G02:");
			ap_ermsg->cf_rev();
			return 0;
		}

		
		cf_rom(ap_vmrom);
		cf_itfc(ap_tr, ap_er, NULL, NULL, NULL, NULL);
		rc = cf_app(ap_prg);
		if(!rc) {
			cf_emsg(ap_ermsg, 0);
			return 0;
		}

		
		rc = yy_chk1(ap_ermsg);
		if(!rc) return 0;

		rc= yy_chk2(ap_ermsg);
		if(!rc) return 0;

		rc= yy_lnk02(&prg02_l, ap_ermsg);
		
		if(!rc) return 0;

		prg02_l.cf_collect("\r\n");
		prg02.cf_close();
		prg02.cf_opens( prg02_l.cf_readtop() );

		
		rc = wl_stru_gmr02::cf_wmk(ap_vmrom, &prg02, ap_tr, ap_obj, ap_er, ap_ermsg);
		
		if(!rc) {
			ap_ermsg->cf_rev();
			ap_ermsg->cf_add("G02-N0.2:");
			ap_ermsg->cf_rev();
			return 0;
		}
		

		return 1;
	}


}; 

#endif


#ifndef WL_STRU_GMR04_H
#define WL_STRU_GMR04_H


class wl_stru_gmr04 : public wl_stru_gmr01  {

private:

	wl_stru_list	iv_bl;	
	wl_stru_list	iv_ul1, iv_ul2;		
	wl_stru_list	iv_bal1, iv_bal2, iv_bal3, iv_bal4;	 

	wl_stru_prpt	idt_trans;	


	void knl_prg(wl_stru_vbary_rdr *ap_prg)
	{
		char s[]=             "S =	for(行头)(一行);\r\n"
          "VER =	[rem~_V1.0];\r\n"
          "行头 =	[vna]+ 标识符+ [vnb] + 等号;\r\n"
          "一行 =	[ecd~一个程序行] + [cx~70] + [vna]+ 行头 + 表达式+ 分号 + [vnb];\r\n"
          "词间空 =	for(词间空一个)(词间空一个);\r\n"
          "词间空一个 =	[rem~nop]+空格|TAB符|回车符|注释;\r\n"
          "空格 =	[tc~b20];\r\n"
          "TAB符 =	[tc~b09];\r\n"
          "回车符 =	[rem~nop]+[tc~b0d]|[tc~b0a];\r\n"
          "注释 =	注括A + 注内容 + 注括B;\r\n"
          "注括A =	[ecd~13] + [tc~/]+[tc~*];\r\n"
          "注括B =	[ecd~14] + [tc~*]+[tc~/];\r\n"
          "注内字节 =	[ecd~15] + [tca~b10bFF] +[rem~nop];\r\n"
          "非注括B =	not(注括B);\r\n"
          "注内容 =	for(非注括B)(注内字节);\r\n"
          "加法号=	词间空+ [cx~91] + [vna]+[tc~+] +[vnb] +词间空;\r\n"
          "乘法号=	词间空+ [cx~92] + [vna]+[tc~*] +[vnb] +词间空;\r\n"
          "等号=	词间空+ [tc~=] +词间空;\r\n"
          "分号=	词间空+ [tc~;] +词间空;\r\n"
          "圆括号A=	词间空+ [tc~(] +词间空;\r\n"
          "圆括号B=	词间空+ [tc~)] +词间空;\r\n"
          "方括号A=	[ecd~方括号A] + [tc~b5b] +[rem~nop];\r\n"
          "方括号B=	[tc~b5d];\r\n"
          "标识符 =	标识符首字符 + 标识符其它字符 +[rem~nop];\r\n"
          "标识符首字符 =	一个标识符字符;\r\n"
          "标识符其它字符 =	for(一个标识符字符)(一个标识符字符);\r\n"
          "一个标识符字符=	[rem~nop]+一个全角字符|一个半角标识符字符;\r\n"
          "一个全角字符=	[tca~b80bFF]+[tca~b40bFF] +[rem~nop];\r\n"
          "一个半角标识符字符=	[tc~0_123456789ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz];\r\n"
          "嵌入指令 =	[ecd~嵌入指令] + 方括号A + 嵌入指令内 + 方括号B;\r\n"
          "非方括号B =	not(方括号B);\r\n"
          "嵌入指令内 =	for(非方括号B)(一个字符);\r\n"
          "一个字符 =	[rem~nop]+一个全角字符|[tca~b10b7F];\r\n"
          "库函数 =	[ecd~库函数] + if型库函数|not型库函数|for型库函数|bsy型库函数;\r\n"
          "if型库函数 =	if([tbsy~1])(if型库函数测试)(if型库函数实际);\r\n"
          "not型库函数 =	if([tbsy~1])(not型库函数测试)(not型库函数实际);\r\n"
          "for型库函数 =	if([tbsy~1])(for型库函数测试)(for型库函数实际);\r\n"
          "bsy型库函数 =	if([tbsy~1])(bsy型库函数测试)(bsy型库函数实际);\r\n"
          "if型库函数测试 =	[tc~iI]+[tc~fF]+ 圆括号A;\r\n"
          "not型库函数测试 =	[tc~nN]+[tc~oO]+[tc~tT]+ 圆括号A;\r\n"
          "for型库函数测试 =	[tc~fF]+[tc~oO]+[tc~rR]+ 圆括号A;\r\n"
          "bsy型库函数测试 =	[tc~bB]+[tc~sS]+[tc~yY]+ 圆括号A;\r\n"
          "if型库函数实际 =	[cx~41] + [vna]+ [ecd~if型库函数] + [tc~iI]+[tc~fF]+ 圆括号A+表达式+圆括号B + 圆括号A+表达式+圆括号B + 圆括号A+表达式+圆括号B;\r\n"
          "not型库函数实际 =	[cx~42] + [vna]+ [ecd~not型库函数] + [tc~nN]+[tc~oO]+[tc~tT]+ 圆括号A+表达式+圆括号B;\r\n"
          "for型库函数实际 =	[cx~43] + [vna]+ [ecd~for型库函数] + [tc~fF]+[tc~oO]+[tc~rR]+ 圆括号A+表达式+圆括号B + 圆括号A+表达式+圆括号B;\r\n"
          "bsy型库函数实际 =	[cx~44] + [vna]+ [ecd~bsy型库函数] + [tc~bB]+[tc~sS]+[tc~yY]+ 圆括号A+表达式+圆括号B + 圆括号A+表达式+圆括号B;\r\n"
          "表达式 =	[ecd~表达式] + [cx~11] + [vna]+ E +[vnb];\r\n"
          "E=	A1+A2+[rem~nop];\r\n"
          "A1=	[rem~nop] + E1|E2;\r\n"
          "A2=	[rem~nop] + E3|[eps];\r\n"
          "E1=	if([tbsy~1])(E1a)(E1b);\r\n"
          "E1a=	圆括号A + E +[rem~nop];\r\n"
          "E1b=	圆括号A + 表达式 + 圆括号B;\r\n"
          "E2=	[cx~12] + [vna]+运算元素+[vnb];\r\n"
          "E3=	[cx~13] + [vna]+op+[vnb] +[bsyrtn]+ 表达式 + A2;\r\n"
          "op=	[rem~nop] + 加法号|乘法号;\r\n"
          "运算元素=	[rem~nop] + 库函数A|嵌入指令A|标识符A;\r\n"
          "库函数A=	库函数 + [vnb] + [rem~nop];\r\n"
          "嵌入指令A=	[cx~51] + [vna]+嵌入指令+[vnb] + [rem~nop];\r\n"
          "标识符A=	[cx~61] + [vna]+标识符+[vnb] + [rem~nop];\r\n"
       ;
		wl_stru_prpt	pp;

		

		pp.cf_let("prg", s);
		pp.cf_repl("prg", " ", "", 1);
		pp.cf_repl("prg", "\t", "", 1);

		ap_prg->cf_close();
		ap_prg->cf_opens(pp.cf_get("prg"));
		return ;
	}


	int yy_chk1(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list l1,l2,l3;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= (wl_s_stru_gmr01_trace *)ivp_trace->cf_read(i);
			if(pt->cx==70 && pt->aob=='a' && -1!=br_ypr(i)) l1.cf_add( br_vt(i) );
		}

		l1.cf_setgroup(&l3);
		for(i=0,j=l3.cf_howmany();i<j;i++) {
			if(*(wlint32 *)l3.cf_read(i)>1) l2.cf_add(l1.cf_read(i));
		}

		j=l2.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("产生式左侧的VN有重复");
			for(i=0;i<l2.cf_howmany();i++) ap_ermsg->cf_add(l2.cf_read(i));
			return 0;
		}
		return 1;
	}


	int yy_chk2(wl_stru_list *ap_ermsg) 
	{
		wl_stru_list l1,l2;
		wlint32 i,j;
		wl_s_stru_gmr01_trace  *pt;

		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) {
			pt= br_tr(i);
			if(pt->cx==70 && pt->aob=='a' && -1!=br_ypr(i)) l1.cf_add( br_vt(i) );
			if(pt->cx==61 && pt->aob=='a'  )				l2.cf_add( br_vt(i) );
		}

		l1.cf_setuniq();
		l2.cf_setuniq();
		l2.cf_setcha(&l1);
		j=l2.cf_howmany();
		if(j!=0){
			ap_ermsg->cf_add("存在未说明的VN");
			for(i=0;i<l2.cf_howmany();i++) ap_ermsg->cf_add(l2.cf_read(i));
			return 0;
		}

		
		idt_trans.cf_clean();
		idt_trans.cf_getknl()->cf_setsortf(ivp_trace->iv_mycmp);
		for(i=0,j=ivp_trace->cf_howmany();i<j;i++) { 
			pt= br_tr(i);
			if( (pt->cx==61 && pt->aob=='a'  )||
				(pt->cx==70 && pt->aob=='a' && -1!=br_ypr(i) ) )
				idt_trans.cf_let(br_vt(i), gen_idt02() );
			
		}

		return 1;
	}


	wlint8 *lf_trans(wlint8 *s)
	{
		wlint8 *t;
		t = idt_trans.cf_get( s );
		return *t?t:s;
	}


	int yy_E(wlint32 h , wl_stru_list *ap_lcode, wl_stru_list *ap_lname, wl_stru_list *ap_ermsg)
	
	{
		wlint32 i,j;
		int rc;

		
		for(j=0,i=br_yne(h); -1!=i; i=br_xne(i) ) j++; 

		switch (j)
		{
		case 3:
			
			i=br_yne(h);
			rc = yy_deal(i, ap_lcode, ap_lname, ap_ermsg);
			if(!rc) return rc;
			
			i=br_yne(h); i=br_xne(i); i=br_xne(i);
			rc = yy_deal(i, ap_lcode, ap_lname, ap_ermsg);
			if(!rc) return rc;
			
			i=br_yne(h); i=br_xne(i);
			rc = yy_deal(i, ap_lcode, ap_lname, ap_ermsg);
			if(!rc) return rc;
			break;
		case 1:
			i=br_yne(h);
			rc = yy_deal(i, ap_lcode, ap_lname, ap_ermsg);
			if(!rc) return rc;
			break;
		default:
			ap_ermsg->cf_add(99);
			sprintf(ap_ermsg->cf_readtop(), "表达式处理内部出错,x向个数为:%ld,hnd=%ld", j, h);
			return 0;
		}
		return 1;
	}

	int yy_deal(wlint32 h , wl_stru_list *ap_lcode, wl_stru_list *ap_lname, wl_stru_list *ap_ermsg)
	
	{
		wlint32 cx,i;

		switch (cx=br_tr(h)->cx)
		{
		case 11:
			if(!yy_E(h, ap_lcode, ap_lname, ap_ermsg))return 0;
			break;

		case 13:
			i=br_yne(h);
			ap_lcode->cf_add32(br_tr(i)->cx);
			ap_lname->cf_add(br_vt(i));
			break;

		case 12:
			i=br_yne(h);
			cx=br_tr(i)->cx;
			switch ( cx )
			{
			case 51:
			case 61:
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( br_vt(i) );
				break;
			case 41:
				i=br_yne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				i=br_xne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				i=br_xne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( "if" );
				break;
			case 42:
				i=br_yne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( "not" );
				break;
			case 43:
				i=br_yne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				i=br_xne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( "for" );
				break;
			case 44:
				i=br_yne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				i=br_xne(i);
				if(!yy_E(i, ap_lcode, ap_lname, ap_ermsg))return 0;
				ap_lcode->cf_add32( cx );
				ap_lname->cf_add( "bsy" );
				break;
			default:
				ap_ermsg->cf_add(88);
				sprintf(ap_ermsg->cf_readtop(), "对表达式一个运元进行处理中内部出错,cx=%ld,id=%ld", cx, i);
				return 0;
			}
			break;

		default:
			ap_ermsg->cf_add(88);
			sprintf(ap_ermsg->cf_readtop(), "表达式处理内部出错,cx=%ld,id=%ld", cx, br_tr(h)->id);
			return 0;
		}
		return 1;
	}


	int yy_prg1e(wlint32 Eh , wl_stru_list *ap_prgl, wl_stru_list *ap_ermsg)
		        
	{
		wlint32 i,j,h1,h2,h3; 
		int rc;
		wl_stru_list	lcode, lname;
		wl_stru_list	E;		
		wl_stru_list	I0;		

		rc = yy_E(Eh, &lcode, &lname, ap_ermsg);
		if(!rc) return 0;

		if(1==lcode.cf_howmany()){
			ap_prgl->cf_add( lf_trans(lname.cf_readtop()) );
			
			ap_ermsg->cf_add(33+wl_stru_strf::str_len(lname.cf_readtop()));
			sprintf(ap_ermsg->cf_readtop(),
				"必须至少2个运元相加!%s", lname.cf_readtop());
			return 0;
		}

		for(i=0;i<lcode.cf_howmany();i++){
			I0.cf_clean();
			I0.cf_add( gen_idt02() );
			E.cf_clean();
			E.cf_add( I0.cf_readtop() );
			E.cf_add("=");
			switch ( j=*(wlint32 *)lcode.cf_read(i) )
			{
			case 41:
				h1=i-3;
				h2=i-2;
				h3=i-1; 
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h2)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h3)) );
				E.cf_add(";");
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h2));
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h3));
				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 42:
				h1=i-1; 
				h2=i-0;
				h3=i-0;
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|[let~0]|[eps];");
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h1));
				
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 43:
				h1=i-2;
				h2=i-1; 
				h3=i-0;
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( gen_idt02() );
				E.cf_add( "|[eps];\r\n");
				E.cf_add( E.cf_read(4) );
				E.cf_add( "=" );
				E.cf_add( lf_trans(lname.cf_read(h2)) );
				E.cf_add( "+" );
				E.cf_add( I0.cf_readtop() );
				E.cf_add( ";" );
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h2));
				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 44:
				h1=i-2;
				h2=i-1; 
				h3=i-0;
				E.cf_add( "[tbsy~1]" );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h2)) );
				E.cf_add(";");
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_bl.cf_add(I0.cf_readtop());	
				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 91:
				h1=i-2;
				h2=i-1;
				h3=i-0;  

				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h1));
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h2));
				
				iv_bal1.cf_add(I0.cf_readtop());
				iv_bal2.cf_add(lname.cf_read(h1));
				iv_bal3.cf_add(lname.cf_read(h2));

				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			case 92:
				h1=i-2;
				h2=i-1;
				h3=i-0; 
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h1)) );
				E.cf_add("|");
				E.cf_add( lf_trans(lname.cf_read(h2)) );
				E.cf_add(";");
				E.cf_collect();
				ap_prgl->cf_add(E.cf_readtop());
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h1));
				iv_ul1.cf_add(I0.cf_readtop()); iv_ul2.cf_add(lname.cf_read(h2));
				
				lcode.cf_del(h1);
				lcode.cf_del(h1);
				*(wlint32 *)lcode.cf_read(h1) = 61;
				lname.cf_del(h1);
				lname.cf_del(h1);
				lname.cf_modi(h1, I0.cf_readtop() );
				i = h1;
				break;
			}
		}

		i = lcode.cf_howmany();
		j = lname.cf_howmany();
		if(1!=i||1!=j) {
			ap_ermsg->cf_add(88);
			sprintf(ap_ermsg->cf_readtop(),"逆波兰表达式未能被归并成单一运算元素.lcode=%ld,lname=%ld.",i,j);
			return 0;
		}

		ap_prgl->cf_add(lname.cf_readtop());
		return 1;
	}


	int yy_lnk( wl_stru_list *ap_prgl, wl_stru_list *ap_ermsg)
	{
		int rc=0;
		wlint32 h, h1, i,j;
		wl_stru_list E0, prgl;

		for(h=0;-1!=h; h=br_xne(h) ) {
			E0.cf_clean();
			prgl.cf_clean();

			
			h1 = br_yne(h);
			h1 = br_xne(h1);
			rc = yy_prg1e(h1, &prgl, ap_ermsg);
			if(!rc) return 0;

			h1 = br_yne(h);
			E0.cf_add( lf_trans(br_vt(h1)) );
			E0.cf_add( "=");
			E0.cf_add( prgl.cf_readtop() );
			E0.cf_add( ";");
			E0.cf_collect();
			iv_ul1.cf_add(br_vt(h1)); iv_ul2.cf_add( prgl.cf_readtop() );
			prgl.cf_deltop();
			prgl.cf_add( E0.cf_readtop() );

			
			while(prgl.cf_howmany()>0){
				ap_prgl->cf_add(prgl.cf_readtop());
				prgl.cf_deltop();
			}
		}

		do{
			i = iv_bl.cf_howmany();
			for(j=0;j<iv_ul2.cf_howmany();j++)
				if(-1!= iv_bl.cf_sel( iv_ul2.cf_read(j) ) ) iv_bl.cf_add( iv_ul1.cf_read(j) );
			iv_bl.cf_setuniq();
		}while(i!=iv_bl.cf_howmany());

		for(i=0;i<iv_bal1.cf_howmany();i++){
			E0.cf_clean();
			E0.cf_add( iv_bal1.cf_read(i) );
			E0.cf_add( "=" );
			E0.cf_add( lf_trans(iv_bal2.cf_read(i) ) );
			E0.cf_add( "+" );
			if(-1!= iv_bl.cf_sel( iv_bal2.cf_read(i) ) ) { 
				E0.cf_add("[bsyrtn]+");
			}else{
				E0.cf_add("[rem~nop]+");
			}
			E0.cf_add( lf_trans(iv_bal3.cf_read(i) ) );
			E0.cf_add(";");
			E0.cf_collect();
			ap_prgl->cf_add(E0.cf_readtop());
		}

		return rc;
	}


protected:

	void cf_emsg(wl_stru_list *ap_ermsg)
	
	{
		char s[99], *t;
		wlint32 y;
		wl_s_stru_gmr01_reg  *pr;

		sprintf(s, "第%ld行，第%ld字节，总第%ld字节.", cf_gerr_pos('r'), cf_gerr_pos('c'), cf_gerr_pos('t') );
		ap_ermsg->cf_add(s);
		for(y=0;y<ivp_err->cf_howmany();y++) {
			pr = (wl_s_stru_gmr01_reg *)(ivp_err->cf_read(y));
			t = ivp_errl->cf_read(pr->ecd);
			if(t[0]!=0&&wl_stru_strf::str_cmp(ap_ermsg->cf_readtop(), t) ) ap_ermsg->cf_add( t );
		}
	}


public:


	int cf_wmk( wl_stru_sheet		*ap_vmrom,
				wl_stru_vbary_rdr	*ap_prg,
				wl_stru_list		*ap_tr,
				wl_stru_sheet		*ap_obj,
				wl_stru_list		*ap_er,
				wl_stru_list		*ap_ermsg	)
				
	{
		int rc;
		wl_stru_vbary_rdr	prg03;
		wl_stru_vbary_rdr	prg02;
		wl_stru_gmr03	lg03;
		wl_stru_gmr02	lg02;

		
		knl_prg(&prg03);
		rc = lg03.cf_wmk(ap_vmrom, &prg03, ap_tr, ap_obj, ap_er, ap_ermsg);
		if(!rc) {
			ap_ermsg->cf_rev();
			ap_ermsg->cf_add("G03:");
			ap_ermsg->cf_rev();
			return 0;
		}

		
		
		wl_stru_list errl;
		cf_rom(ap_obj);
		cf_itfc(ap_tr, ap_er, &errl, NULL, NULL, NULL);
		
		rc = cf_app(ap_prg);
		
		if(!rc) {
			cf_emsg(ap_ermsg);
			return 0;
		}

		
		rc = yy_chk1(ap_ermsg);
		if(!rc) return 0;

		rc= yy_chk2(ap_ermsg);
		if(!rc) return 0;

		wl_stru_list   prgl;
		rc = yy_lnk( &prgl, ap_ermsg);
		
		if(!rc) return 0;

		prgl.cf_collect("\r\n");
		prg02.cf_opens( prgl.cf_readtop() );
		
		rc = lg02.cf_wmk(ap_vmrom, &prg02, ap_tr, ap_obj, ap_er, ap_ermsg);
		
		if(!rc) {
			ap_ermsg->cf_rev();
			ap_ermsg->cf_add("G02-B:");
			ap_ermsg->cf_rev();
			return 0;
		}

		return 1;
	}


}; 

#endif


#ifndef WL_STRU_GMR05_H
#define WL_STRU_GMR05_H


class wl_stru_gmr05 : public wl_stru_gmr04  {

private:


	wl_stru_list iv_lcode, iv_lname;


	void knl_prg(wl_stru_vbary_rdr *ap_prg)
	{
		wl_stru_prpt pp;
		char s[]=                   "S	=	[ecd~S]+	词间空+[vna]+		  for(行头)(程序行) + [vnb] + 词间空 + 文件尾	;				\r\n"
          "文件尾	=	[ecd~文件尾] + [teof]				;				\r\n"
          "										\r\n"
          "程序行	=	[ecd~程序行]+			自带ecd的行*传统行	;				\r\n"
          "自带ecd的行	=	[ecd~自带ecd的行]+	[cx~9201]+[vna]+标识符+[vnb]+[cx~9202]+[vna]+双等号+[vnb]+表达式+分号			;				\r\n"
          "传统行	=	[ecd~传统行]+	[cx~9101]+[vna]+标识符+[vnb]+[cx~9102]+[vna]+单等号+[vnb]+表达式+分号			;				\r\n"
          "行头	=	[ecd~行头]+			标识符+ 词间空+ [tc~=]	;				\r\n"
          "										\r\n"
          "词间空	=	[ecd~词间空]+			for(词间空一个)(词间空一个)	;				\r\n"
          "词间空一个	=	[ecd~词间空一个]+			[tc~b20b09b0db0a]*([tc~/]+[tc~*]+for(not([tc~*]+[tc~/]))([tca~b10bFF])+[tc~*]+[tc~/])	;				\r\n"
          "										\r\n"
          "标识符	 =	[ecd~标识符]+			一个标识符字符 + for(一个标识符字符)(一个标识符字符) 	;				\r\n"
          "一个标识符字符	 =	[ecd~一个标识符字符]+			([tca~b80bFF]+[tca~b40bFF])*asc符 	;				\r\n"
          "bs符	 =	[ecd~bs符]+			一个标识符字符 * [tca~b10b7F]	;				\r\n"
          "asc符	 =	[ecd~asc符]+			[tc~0_123456789ABCDEFGHIJKLMNOPQRSTUVWXYZab62cdefghijklmnopqrstuvwxyz]+[rem~nop]	;				\r\n"
          "asc串	 =	[ecd~asc串]+			asc符+for(asc符)(asc符) 	;				\r\n"
          "num串	 =	[ecd~num串]+	[cx~961]+[vna]+		[tc~0123456789]+for([tc~0123456789])([tc~0123456789])	+[vnb]	;\r\n"
          "运算元素	 =	[ecd~运算元素]+			库函数* ([cx~921]+[vna]+标识符+[vnb])	;	\r\n"
          "							\r\n"
          "双等号	 =	[ecd~双等号]+			词间空+ [tc~=] +[tc~=] +词间空	;	\r\n"
          "单等号	 =	[ecd~单等号]+			词间空+ [tc~=] +词间空	;	\r\n"
          "加法号	 =	[ecd~加法号]+			词间空+ [cx~971]+[vna]+ [tc~+]  +[vnb] +词间空	;	\r\n"
          "乘法号	 =	[ecd~乘法号]+			词间空+ [cx~972]+[vna]+ [tc~*]  +[vnb] +词间空	;	\r\n"
          "左括	 =	[ecd~左括]+			词间空+ [tc~(] +词间空	;	\r\n"
          "右括	 =	[ecd~右括]+			词间空+ [tc~)] +词间空	;	\r\n"
          "左大括	 =	[ecd~左大括]+			词间空+ [tc~{] +词间空	;	\r\n"
          "右大括	 =	[ecd~右大括]+			词间空+ [tc~}] +词间空	;	\r\n"
          "分号	 =	[ecd~分号]+			词间空+ [tc~;] +词间空	;	\r\n"
          "							\r\n"
          "库函数	 =	[ecd~库函数]+			库1*库2*库3*库4*库5*库6*库7*库8*库9*库10*库11*库12a*库12b*库13*库14*库15*库16	;	\r\n"
          "bs串	 =	[ecd~b型字符串]+	左括 + [cx~962]+[vna]+		(bs符+for(not(右括))(bs符)) +[vnb] + 右括	;	\r\n"
          "bs串2	 =	[ecd~b型字符串]+	[tc~b22] + [cx~962]+[vna]+		(bs符+for(not([tc~b22]))(bs符)) +[vnb] + [tc~b22]	;	\r\n"
          "库1	 =	[ecd~库1(ecd)]+	[cx~10]+	[vna]+	bsy([tc~eE]+[tc~cC]+[tc~dD]+左括)([tc~eE]+[tc~cC]+[tc~dD] + bs串) 	+[vnb]	;\r\n"
          "库2	 =	[ecd~库2(vn)]+			(库2a * 库2b)	+[vnb]	;\r\n"
          "库2a	 =	[ecd~库2a]+	[cx~21]+	[vna]+	bsy([tc~vV]+[tc~nN]+左括)([tc~vV]+[tc~nN]+bs串+左括+表达式+右括)	;	\r\n"
          "库2b	 =	[ecd~库2b]+	[cx~22]+	[vna]+	bsy(左大括)(左大括 + 表达式 + 右大括)	;	\r\n"
          "库3	 =	[ecd~库3(lmt)]+	[cx~30]+	[vna]+	bsy( [tc~lL]+[tc~mM]+[tc~tT]+左括 )( 库3b )	+[vnb]	;\r\n"
          "库3b	 =	[ecd~库3b]+			[tc~lL]+[tc~mM]+[tc~tT]+ 左括 + num串 +右括+ 左括 + 表达式 + 右括	;	\r\n"
          "库4	 =	[ecd~库4(vnx)]+	[cx~40]+	[vna]+	bsy([tc~vV]+[tc~nN]+[tc~xX]+左括)([tc~vV]+[tc~nN]+[tc~xX]+ 左括 + num串 + 右括)	+[vnb]	;\r\n"
          "库5	 =	[ecd~库5(whl)]+	[cx~50]+	[vna]+	bsy([tc~wW]+[tc~hH]+[tc~lL]+左括)([tc~wW]+[tc~hH]+[tc~lL]+左括+表达式+右括+左括+表达式+右括)	+[vnb]	;\r\n"
          "库6	 =	[ecd~库6(for)]+	[cx~60]+	[vna]+	bsy([tc~fF]+[tc~oO]+[tc~rR]+左括)([tc~fF]+[tc~oO]+[tc~rR]+左括+num串+右括+左括+表达式+右括)	+[vnb]	;\r\n"
          "库7	 =	[ecd~库7(if)]+	[cx~70]+	[vna]+	bsy([tc~iI]+[tc~fF]+左括)([tc~iI]+[tc~fF]+左括+表达式+右括+左括+表达式+右括+左括+表达式+右括)	+[vnb]	;\r\n"
          "库8	 =	[ecd~库8(bsy)]+	[cx~80]+	[vna]+	bsy([tc~bB]+[tc~sS]+[tc~yY]+左括)([tc~bB]+[tc~sS]+[tc~yY]+左括+表达式+右括+左括+表达式+右括)	+[vnb]	;\r\n"
          "库9	 =	[ecd~库9(not)]+	[cx~90]+	[vna]+	bsy([tc~nN]+[tc~oO]+[tc~tT]+左括)([tc~nN]+[tc~oO]+[tc~tT]+左括+表达式+右括)	+[vnb]	;\r\n"
          "库10	 =	[ecd~库10(tc)]+	[cx~100]+	[vna]+	bsy([tc~tT]+[tc~cC]+左括)([tc~tT]+[tc~cC] + bs串) 	+[vnb]	;\r\n"
          "库11	 =	[ecd~库11(tca)]+	[cx~110]+	[vna]+	bsy([tc~tT]+[tc~cC]+[tc~aA]+左括)([tc~tT]+[tc~cC]+[tc~aA] + bs串) 	+[vnb]	;\r\n"
          "库12a	 =	[ecd~库12(ts)]+	[cx~121]+	[vna]+	bsy([tc~tT]+[tc~sS]+左括)([tc~tT]+[tc~sS] + bs串) 	+[vnb]	;\r\n"
          "库12b	 =	[ecd~库12(字符串ts)]+	[cx~122]+	[vna]+	bs串2	+[vnb]	;\r\n"
          "库13	 =	[ecd~库13(nop)]+	[cx~130]+	[vna]+	bsy([tc~nN]+[tc~oO]+[tc~pP]+左括)([tc~nN]+[tc~oO]+[tc~pP]+左括+右括) 	+[vnb]	;\r\n"
          "库14	 =	[ecd~库14(eps)]+	[cx~140]+	[vna]+	bsy([tc~eE]+[tc~pP]+[tc~sS]+左括)([tc~eE]+[tc~pP]+[tc~sS]+左括+右括) 	+[vnb]	;\r\n"
          "库15	 =	[ecd~库15(eof)]+	[cx~150]+	[vna]+	bsy([tc~eE]+[tc~oO]+[tc~fF]+左括)([tc~eE]+[tc~oO]+[tc~fF]+左括+右括) 	+[vnb]	;\r\n"
          "库16	 =	[ecd~库16(eor)]+	[cx~160]+	[vna]+	bsy([tc~eE]+[tc~oO]+[tc~rR]+左括)([tc~eE]+[tc~oO]+[tc~rR]+左括+右括) 	+[vnb]	;\r\n"
          "							\r\n"
          "表达式	 =	[ecd~表达式]+			E	;	\r\n"
          "E	 =		[cx~990]+	[vna]+	((左括+E+右括)*运算元素)+(E3*[eps])	+[vnb]	;\r\n"
          "E3	 =				bsy(加法号*乘法号)((加法号*乘法号)+E + (E3*[eps]))	;	\r\n"
		   ;

		

		pp.cf_let("prg", s);
		ap_prg->cf_close();
		ap_prg->cf_opens(pp.cf_get("prg"));
		return ;
	}


	wlint8 *lf_obj5(void){
	static wlint8 s[22575];
	char ss[]=
	"remb7EGMR02b09callb7E1b09haltb0Db0Aremb7EwL8b281b29b09callb7E120b09recfb09rtnb0Db0Aremb7EwSGb282b2"
	"9b09b62upb09callb7E9b09b62dnb09jfb7E4b09callb7E3b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwSHb28"
	"3b29b09callb7E5b09recfb09rtnfb09callb7E2b09recfb09rtnb0Db0Aremb7EwMFb284b29b09callb7E121b09recfb09"
	"rtnb0Db0Aremb7EwMGb285b29b09callb7E122b09recfb09rtnb0Db0Aremb7EwSXb286b29b09b62upb09callb7E7b09b62"
	"dnb09jfb7E4b09callb7E7b09recfb09rtnb09callb7E8b09recfb09rtnb0Db0Aremb7EwMJb287b29b09callb7E132b09r"
	"ecfb09rtnb0Db0Aremb7EwMOb288b29b09callb7E142b09recfb09rtnb0Db0Aremb7EwMTb289b29b09callb7E145b09rec"
	"fb09rtnb0Db0Aremb7EwN8b2810b29b09callb7E146b09recfb09rtnb0Db0Aremb7EwUHb2811b29b09b62upb09callb7E1"
	"3b09b62dnb09jfb7E4b09callb7E12b09recfb09rtnb09epsb09recfb09rtnb0Db0Aremb7EwUIb2812b29b09callb7E13b"
	"09recfb09rtnfb09callb7E11b09recfb09rtnb0Db0Aremb7EwMZb2813b29b09callb7E152b09recfb09rtnb0Db0Aremb7"
	"EwU1b2814b29b09b62upb09tcb7Eb6220b6209b620db620ab09b62dnb09jfb7E4b09tcb7Eb6220b6209b620db620ab09re"
	"cfb09rtnb09callb7E151b09recfb09rtnb0Db0Aremb7EwUTb2815b29b09b62upb09callb7E17b09b62dnb09jfb7E4b09c"
	"13b09recfb09rtnfb09remb7Enopb09callb7E429b09recfb09rtnb0Db0Ab00"

