 
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

#ifdef WINENV_
#pragma warning(push)
#pragma warning(disable: 4996)
#pragma warning(disable: 4786)

#include <shellapi.h>
#pragma comment( lib, "ws2_32.lib" )
#include <winsock.h>
#include "atlstr.h"



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


	template< class T >
	static T & chgendian( T & val )
	{
		if( sizeof(T) != 1 ) srev( (tchar *)&val, sizeof(T) );
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


	template<class T>
	static tbool readbit( T bindata , int sufx )
	{
		return readbit_s( &bindata, (int)sizeof(T), sufx );
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


	static void writebit_s( void * pbin, int iBytesLen, int sufx , tbool val )
	{
		if( sufx < 0 || iBytesLen <= 0 || (sufx / 8) >= iBytesLen )
		{
			return;
		}
		writebit( pbin, sufx , val );
	}



	
	template<class T> 
	static std::string & byte2str( T c, std::string & strrtn )
	{
		strrtn = "01234567";
		for( int i = 0; i < 8; i++ ) strrtn[i] = readbit( c, i ) ? '1' : '0' ;
		return strrtn;
	}

	
	template<class T> 
	static std::string byte2str( T c )
	{
		std::string str;
		return byte2str( c, str );
	}

	
	template<class T> 
	static T & str2byte( std::string str, T & c )
	{
		
		str += "00000000";
		for( int i = 0; i < 8; i++ ) writebit( &c, i , str[i]=='0' ? 0 : 1 );
		return c;
	}

	
	static tuint8 str2byte( std::string str )
	{
		tuint8 c;
		return str2byte( str, c );
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

	
	static void *smemcpy( void *dest, const void *src, tsize count )
	{
		return memcpy(dest,src,count);
	}

	
	static void * smemset( void *dest, tchar c, tsize count )
	{
		return memset( dest, (int)c, (size_t)count );
	}

	
	template< class T >
	static void * smemset( T & dest, tchar c = 0 )
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

	
	static std::string sultoa( tuint32 i )
	{
		std::stringstream stream;
		stream << i;
		return stream.str();
	}

	
	static tuint32 satoul( std::string  s )
	{
		return strtoul(s.c_str(),NULL,10);
	}


	static std::string GetBcdStr( tuint8 c1 )
	{
		char s[11];
		(*SClib::p_sprintf())( s, "%X", (unsigned int)c1 );
		return s;
	}

	
	static std::string GetBcdStr( std::string s1 )
	{
		tuint8 c1;
		c1 = (tuint8)satol(s1);
		char s[11];
		(*SClib::p_sprintf())( s, "%X", (unsigned int)c1 );
		return s;
	}

	
	static int GetBcdInt( tuint8 c1 )
	{
		return (int)satol(GetBcdStr(c1));
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
		std::vector<tchar> v( 22 + decimal_digits );
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
		lia = (tint16 *)smalloc( (slen(s_num) + 1)*sizeof(tint16) );
		if(!lia)
		{
			sfree(s_num);
			return "";
		}

		scpy( s_num, strCurNum.c_str() );

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

	static std::string  & bs_de( std::string & strData )
	{
		std::string s1( strData + "123" );

		bs_de( strData.c_str(), &(s1[0]) );

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


	
	template< class T >
	static std::string b2s(  T & sourcedata )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( sizeof(T) * 3 + 12 );
		bs_en( (const char *)reinterpret_cast<const char *>(&reinterpret_cast< char& >(sourcedata)), sizeof(T), szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
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
					p2[i] = p1[i] & (tuint8)0x7f;
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


	static tuint32 chksum( const tchar *s, tsize len)
	{
		tuint32 j=0;
		if(SStrf::slen(s)==0)
			return 0;
		while(len--)
		{
			j += (tuint8)s[len]+(len+1);
			j &= 0x7FffFFff;
		}
		return j;
	}


	static tchar * xor( tchar * Src, tsize len, tuint8 x )
	{
		tsize i;
		tuint8 *s=(tuint8 *)Src;
		if( !s || !len ) return (tchar*)s;
		for(i=0;i<len;i++) s[i] ^= x;
		return (tchar*)s;
	}


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
	static ELET & vs_groupbig( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typedef typename std::vector<ELET>::iterator iteratortypeB;
		iteratortypeB it1;
		std::vector<int>::iterator it2, it3;
		int i;

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
	static ELET & vs_groupsmall( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typename std::vector<ELET>::iterator it1;
		std::vector<int>::iterator it2, it3;
		int i;

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


	virtual ~SCake_base( ) { freeall(); }


	
	
	
	

	
	
	

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


	SCake & bs_de() 
	{
		tsize iDatalen = SStrf::bs_desize( buf() );
		SStrf::bs_de( buf() );
		redim( iDatalen, 1 );
		return *this;
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
			return strOut = std::string( this->buf_const(), this->len() );
		}
		return strOut = "";
	}

	
	std::string mk_str() const
	{
		std::string s1;
		return mk_str(s1);
	}


	std::string GetReadable() const
	{
		std::string strOut = "L" + SStrf::sltoa( (int)this->len() ) + "-";

		
		
		
		for( tsize i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;

			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;

			

			char sz1[22];
			(*SClib::p_sprintf())( sz1, "%02X", (int)(*p2) );
			strOut += sz1;
		}

		return strOut;
	}


	long ConvStr2Bin( std::string strData, void * pData ) const
	{
		std::vector<std::string> vec1;

		wl::SStrvs::vsa_imp( strData, std::string(" "), 1, vec1 );

		for( std::vector<std::string>::size_type i = 0; pData && i < vec1.size(); i++ )
		{
			int ii;
			(SClib::p_sscanf())( vec1[i].c_str(), "%x", &ii );
			*((wl::tuint8*)pData+i) = (wl::tuint8)ii;
		}

		return (long)vec1.size();
	}

	
	long ConvStr2Bin( std::string strData )
	{
		redim( ConvStr2Bin( strData, NULL ) );
		return ConvStr2Bin( strData, buf() );
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

public: 

	SCakel & operator = ( const SCakel & cakel2 )
	{
		clean();
		return append(cakel2);
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_sdte_h
#define X011__H_w_sdte_h



X011_NAMESPACE_BEGIN


class SDte
{


public:

	int m_year;
	int m_mon;
	int m_day;
	int m_hour;
	int m_min;
	int m_sec;
	

private:

	static tbool d_is_leap_year(int y)
	{
		return y%400==0||y%4==0&&y%100!=0;
		
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
		int i = (int)( e_proctime() * 1000 );
		return i % 1000;
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

	
	static tint32 DiffSecToday(SDte dt)
	{
		SDte a=dt;
		SDte b=a;
		b.m_hour=b.m_min=b.m_sec=0;
		return a.DiffSecInt(b);
	}


	int WeekDay() const
	{
		int i2 = this->DiffDay( wl::SDte() );
		return (i2 - 2 ) % 7;
	}


	SDte & Relative( const SDte & dte2 )
	{
		m_year += dte2.m_year;
		m_mon  += dte2.m_mon;
		m_day  += dte2.m_day;
		m_hour += dte2.m_hour;
		m_min  += dte2.m_min;
		m_sec  += dte2.m_sec;

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


	std::string ReadString() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 m_year, m_mon, m_day,
					 m_hour, m_min, m_sec	);
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
								m_day,s2[m_mon], m_year );
		return sBuf;
	}

	
	void GetBcdArr( SCake & ck ) const 
	{
		std::string s1 = ReadStringPack14();
		std::vector<std::string> vec1;

		wl::SStrvs::vsa_impbylen( s1, 2, vec1 );

		s1.clear();
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


	tbool erase()
	{
		return 0==remove( m_strFilename.c_str() )?1:0;
	}

	static tbool erase(std::string strfilename)
	{
		return 0==remove( strfilename.c_str() )?1:0;
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


	tbool read_str( SCake_base<tchar> & buf ) 
	{
		return this->read( buf, 1 );
	}


	tbool read_bs( std::string & strRtnBs )
	{
		SCake ck;

		if( !this->read( ck ) ) return 0;
		strRtnBs = ck.len() ? ck.bs_en().buf() : "";

		return 1;
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


	tbool read_vecstr( std::vector<std::string> & vecLines, std::string strSep, tbool istoken = 1 )
	{
		wl::SCake ckData;
		if( !read_str( ckData ) ) return 0;
		if( !ckData.len() ) return 0;
		SStrvs::vsa_imp( std::string(ckData.buf()), strSep, istoken, vecLines );
		return 1;
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

	typedef typename std::map< nameT, valueT >::iterator	MAP_MAPKNL_IT;
	typedef typename std::map< nameT, valueT >::const_iterator  MAP_MAPKNL_CONSTIT;

	MAP_MAPKNL_IT m_it4name;

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


	tbool GetFirstName( nameT & Name )
	{
		m_it4name = m_mapKnl.begin();
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool GetNextName( nameT & Name )
	{
		m_it4name ++;
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool operator < ( const SNava_base & rhs) const
	{
		return ( m_mapKnl < rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator <= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl <= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator > ( const SNava_base & rhs) const
	{
		return ( m_mapKnl > rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator >= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl >= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator == ( const SNava_base & rhs) const
	{
		return ( m_mapKnl == rhs.m_mapKnl ? 1 : 0 );
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
		if( ck.len() == 0 ) return;
		ck.bs_de();
		if( !ck.buf() ) ck.lets(""); 
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
		SCake ckTmp1,ckTmp2;

		SStrvs::vsa2v_prpt( strData, std::string(")"), std::string("(") , mapTmp );

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			ckTmp1.lets( it->first );
			seri_element_de( ckTmp1 );
			ckTmp2.lets( it->second );
			seri_element_de( ckTmp2 );

			let( std::string(ckTmp1.buf()), std::string(ckTmp2.buf()) );
		}

		return 1;
	}

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

	typedef typename std::vector< itT > RTNVEC_T;
	typedef typename std::vector< itT >::iterator RTNVEC_IT;

private:

	std::vector< itT >  m_begin;
	std::vector< itT >  m_end;

	std::vector< itT >  m_beginBak;
	std::vector< itT >  m_endBak;

	tbool m_canfetchflag;

	std::set< RTNVEC_T > m_comb_buf;

public:

	SPeco(){ GotoBegin();}

	virtual ~SPeco(){;}

public:

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
		tbool plusflag(1);

		if( m_canfetchflag == 0 ) return m_canfetchflag;

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

protected:

	SCake m_ckDataL2CacheBuf;


protected:

	tsize sys_recv( SCake & ckDataBuf )
	{
		int i = on_sys_recv(ckDataBuf); 
		if(i)
		{
			return i;
		}
		else
		{
			ckDataBuf.redim(0);
			return 0;
		}
	}


	tsize sys_send( const SCake & ckDataBuf )
	{
		return on_sys_send(ckDataBuf);
	}


public:

	IRice( )
	{
		
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


	template<class T>
	tbool send_bin( T adata )
	{
		SCake ck;
		ck.let( (SCake::CkEle_t*)&adata, sizeof(T) );
		return send_bin(ck);
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
		if( it != m_mapColNames.end() ) return GetEle(row, it->second);
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


	WCrsc( WCrsc & Crsc_father)
	{
		InitVars();

		LockCrsc( Crsc_father );
	}

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
	wl::WCrsc		m_ut_tbl_lck;

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

	virtual std::string & ut_SeriTbl( std::string & strOut )=0;
	virtual void ut_SeriTbl( SFile & fl ) = 0;
	virtual void ut_SeriTbl( SFile & fl, long lbegin, long lend ) = 0;
	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend ) = 0;

	virtual long ut_AddRow() = 0;
	virtual long ut_AddRow( std::string strRowSeriStr) = 0;
	virtual void ut_ReIdx() = 0;
	virtual void ut_DelRowf( long lRowNum ) = 0;
	virtual void ut_DelRow( long lRowNum ) = 0;

	virtual void * ut_GetRowAddr( long lRowNum ) = 0;

	virtual unitbl_base_t * ut_GetDup() = 0;
	virtual void ut_DestroyDup(unitbl_base_t *p) { 	if( p ) delete p; }
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

	virtual std::string & ut_SeriTbl( std::string & strOut )
	{
		return T::Serialize( strOut );
	}

	virtual void ut_SeriTbl( SFile & fl )
	{
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "wb" );
		if(fp==NULL) return;
		for(long i=0;i<(long)T::GetRowCount();i++)
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		fclose(fp);
	}

	virtual void ut_SeriTbl( SFile & fl, long lbegin, long lend )
	{
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "ab" );
		if(fp == NULL) return;
		for( long i = lbegin;i<(long)lend + 1; i++ )
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		fclose(fp);
	}

	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend )
	{
		T::Unserialize( strIn.c_str() , biAppend )	;
		return *this;
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


	
	static std::string MkUId()
	{
		static tint32 i = 1;
		int i2 = (int)time(0) * (int)GetCurrentThreadId() * (int)GetCurrentProcessId();
		int j;
		void *p = SStrf::smalloc(3);
		memcpy( &j, &p, sizeof(int) );
		SStrf::sfree(p);

		double dd = SStrf::rand1() * i * i2 * j * SDte::e_proctime();

		std::reverse( (char*)(&dd), (char*)(&dd) + sizeof(double) );

		tchar szBuf[33];
		SClib::p_sprintf()( szBuf, "%x%u", *(int*)(&dd) + j + i , i++ );

		return szBuf;
	}


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
			printf( "ok in i\n" );
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
			printf( "ok in un\n" );
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


	void rename( std::string strNewNameNoDir )
	{
		std::string strCmd;

		strCmd = "ren \"";
		strCmd += this->filename();
		strCmd += "\" ";
		strCmd += "\"" + strNewNameNoDir + "\"";

		system( strCmd.c_str() );
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

	}


	static void UnPackFolder( std::string strWorkPathOrDir, const SCake & ckIn , std::vector<std::string> *pvDirFullNameLst = NULL, std::vector<std::string> *pvFileFullPathNameLst = NULL )
	{
		if( ckIn.len() == 0 ) return;

		
		
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;


		std::string strTD = "\t";
		std::string strTR = "\n";

		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;

		strInfoHeader = (const char*)ckIn.buf_const();



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 ), strTD, 1, vDirNameLst );

		std::sort( vDirNameLst.begin(), vDirNameLst.end() ); 

		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vDirFullNameLst.push_back( s1 );

			CString cs1;
			cs1 = s1.c_str();
			::CreateDirectory( cs1, NULL );
			
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 1 ), strTD, 1, vFileRelaPathNameLst );

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vFileFullPathNameLst.push_back( s1 );
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 2 ), strTD, 1, vFileLenLst );


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

			sf.write( p1, (tsize)i1 );

			vFileFullPathNameLst.erase( vFileFullPathNameLst.begin() );
			vFileLenLst.erase( vFileLenLst.begin() );

			p1 += i1;
		}

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
			if( it->find(strMemoLineHead) == 0 ) continue;

			(*it)[i] = 0;
			this->let( it->c_str(), it->c_str() + i + ssepTD.size() );
		}

		this->trimall();
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


	void ChtoUtf8()
	{
		AtoB( WFile::ChtoUtf8 );
	}

	void Utf8toCh()
	{
		AtoB( WFile::Utf8toCh );
	}


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




#ifndef _MT
#ifndef X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
#define X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
#endif
#endif


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

		try
		{
			

			pThis->tr_on_pre_thrd();
			pThis->tr_on_knl_run();
			pThis->tr_on_post_thrd();

			
			pThis->tr_shouldbrk();

			pThis->m_iLive = 0;

			if(pThis->m_iAutoDel)
			{
				if( !pThis->m_iCreationDone )
				{
					while( !pThis->m_iCreationDone ) tr_sleep( 1 );
					tr_sleep( 1 );
				}

				tr_sleep( 2 ); 

				delete pThis;
			}
		}
		catch(...)
		{ ;	}

		return (DWORD)0;
	}


private:

	WThrd & operator = (const WThrd & rhs)
	{
		return *this;
	}


	WThrd(const WThrd & rhs)
	{;}


public:

	WThrd()
	{
		m_hThread = INVALID_HANDLE_VALUE;
		m_iAutoDel = 0;
		m_iShouldBreak = 0;
		m_iLive = 0;
		m_iCreationDone = 0;
		m_iOpened = 0;
	}


	virtual ~WThrd()
	{
		if( !m_iOpened ) return;

		try
		{
			tr_shouldbrk();

			
			
			
			
			

			if( !m_iAutoDel )
				tr_wait();

			tr_closehandl();
		}
		catch(...)
		{; }
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


	static void tr_sleep( int iSec , double dSec = 0.0 )	
	{
		if( iSec > 0 )
			Sleep( iSec * 1000 );

		if( dSec > 0.0 )
		{
			Sleep( static_cast<int>(dSec * 1000 * 1) );
		}
	}


	tbool tr_open()
	{
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


	virtual void tr_on_knl_run()
	{
		
		SStrf::initrand( (int)((int)time(0) * (int)GetCurrentThreadId()) );

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
	int                    m_iFailWaitTimesec; 
	tbool                  m_biIsMultiEleType;

public:
	
	WThrdMgr()
	{
		m_biMgrShouldBreak = 0;
		m_iFailWaitTimesec = 2;
		m_biIsMultiEleType = 1;
	}

	
	virtual ~WThrdMgr()
	{;	}

	
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
		ThrEle_t * p = new ThrEle_t;

		if( !p ) return NULL;

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
			WThrd::tr_sleep( m_iFailWaitTimesec > 0 ? m_iFailWaitTimesec : 2 );

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
		WCrsc aLock( this->m_crscThrdLst );
		WThrdEle * p = SStrf::AddressOf( t );

		m_vecThrdLst.push_back( p );
		return GetThrdAmount();
	}

	
	int RemoveEle( WThrdEle & t )
	{
		WCrsc aLock( this->m_crscThrdLst );
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
		WCrsc aLock ( m_crscThrdOpenFunc );
		WCrsc a2Lock( m_crscThrdLst );

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
		WCrsc aLock( m_crscThrdOpenFunc );

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
		WCrsc aLock( m_crscThrdOpenFunc );

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






template < class TASK_T >
class WIdleThrd
{
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

public:
		
		class WIdleThrdEle : public WThrd
		{
		private:
			WIdleThrd<TASK_T>  * m_pWIdleThrd;

			
			int tr_on_user_run()
			{
				if(1)
				{
					WCrsc aaa2(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck);
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef++;
				}

				TASK_T t;
				WCrsc aaa(m_pWIdleThrd->m_crTasksRunLck); 

				if(1)
				{
					WCrsc aaa2(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck);
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef--;
				}

				for( ; m_pWIdleThrd->GetTask(t); )  
				{
					m_pWIdleThrd->OnRun(t);
				}

				return 0;
			}

			
			virtual void tr_on_pre_thrd()
			{
				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdRunRefLck);
				m_pWIdleThrd->m_iWorkThrdRunRef++;
			}

			
			virtual void tr_on_post_thrd()
			{
				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdRunRefLck);
				m_pWIdleThrd->m_iWorkThrdRunRef--;
			}

		public:
			
			WIdleThrdEle( WIdleThrd<TASK_T> *p )
			{
				m_pWIdleThrd = p;

				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdObjRefLck);

				m_pWIdleThrd->m_iWorkThrdObjRef++;
			}

			virtual ~WIdleThrdEle()
			{
				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdObjRefLck);

				m_pWIdleThrd->m_iWorkThrdObjRef--;
			}
		};

public:
	
	WIdleThrd()
	{
		m_iWorkThrdObjRef = 0;
		m_iWorkThrdWaitingRunfuncRef = 0;
		m_iWorkThrdRunRef = 0;
	}

	
	virtual ~WIdleThrd()
	{
		while( m_iWorkThrdObjRef > 0 ) WThrd::tr_sleep(1);
	}

public:
	
	void PostTask( const TASK_T & t, tbool biWithWait = 1 )
	{
		if( biWithWait )
		{
			if   ( m_iWorkThrdObjRef              > 9 ) WThrd::tr_sleep(1);
			while( m_iWorkThrdWaitingRunfuncRef   > 4 ) WThrd::tr_sleep(1);
			while( m_iWorkThrdRunRef              > 7 ) WThrd::tr_sleep(1);
		}

		if(1)
		{
			WCrsc aaa(m_crTasksReadLck);

			m_vecTasks.push_back(t);

			if( m_iWorkThrdWaitingRunfuncRef < 2 ) 
			{
				WIdleThrdEle *p = new WIdleThrdEle(this);
				p->tr_openx();
			}

		}

	}


	tbool GetTask( TASK_T & t )
	{
		WCrsc aaa(m_crTasksReadLck);
		if( m_vecTasks.empty() ) return 0;
		t = m_vecTasks[0];
		m_vecTasks.erase( m_vecTasks.begin() );
		return 1;
	}


	void ClearTask()
	{
		WCrsc aaa(m_crTasksReadLck);
		m_vecTasks.clear();
	}


	void WaitAllTaskDone()
	{
		while( m_iWorkThrdRunRef > 0 ) WThrd::tr_sleep(1);
	}


	virtual void OnRun( TASK_T t ) 
	{
		return;
	}
};




X011_NAMESPACE_END

#endif








#ifndef X011__w_WSnd_H
#define X011__w_WSnd_H


#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")


X011_NAMESPACE_BEGIN


class WSnd
{
public:

public:
	virtual ~WSnd() {;}

public:

	static void PlayWav( std::string strFile )
	{
		PlaySoundA( strFile.c_str(), NULL, SND_FILENAME | SND_SYNC );
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

		WFile fl;

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
		WCrsc aLock(m_LogLck);

		if( m_iRelativeDay >= 0 ) return;

		if( m_iLogCounter++ >= 10000 ) 
		{
			m_iLogCounter=0;
			WashLogFile();
		}

		WFile fl;

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
	void WriteLog(T val1)
	{	
		std::stringstream stream1;
		std::string strOut;
		stream1 << val1;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str());
		WriteStr(strOut);
	}

	template<class T1, class T2>
	void WriteLog(T1 val1, T2 val2 )
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
	void WriteLog(T1 val1, T2 val2, T3 val3)
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
		int  m_i;
		int  m_iMaxSec;
		double  m_d;
		double  m_dMaxSec2;

		MyTimeKiller( WTcpDisConnable * ph, int iMaxSec, double dMaxSec2 = 0.0 )
		{
			m_ph = ph;
			m_i = 0;
			m_iMaxSec = iMaxSec;
			m_d = 0.0;
			m_dMaxSec2 = dMaxSec2;
		}

		virtual ~MyTimeKiller()
		{
			m_i = 0;
			tr_shouldbrk();

			
			
		}


		virtual int tr_on_user_run()
		{
			if( m_i <= m_iMaxSec )
			{
				m_i++;
				if( m_i > m_iMaxSec )
				{
					
					
				}
				else
				{
					WThrd::tr_sleep(1);
					return 1;
				}
			}

			if( m_d < m_dMaxSec2 ) 
			{
				m_d += m_dMaxSec2;
				WThrd::tr_sleep( 0 , m_dMaxSec2 );
				return 1;
			}

			if( this->tr_isShouldBrk() ) return 0;

			if(m_ph) m_ph->DisConn();
			return 0;
		}
	};


	MyTimeKiller * m_pkiller;


	void killer_up( int iMaxSec ) 
	{
		killer_dn() ;
		m_pkiller = new MyTimeKiller( this, iMaxSec );
		m_pkiller->tr_open();
	}


	void killer_dn()
	{
		if( m_pkiller != NULL )
		{
			delete m_pkiller;
			m_pkiller = NULL;
		}
	}

public:

	WTcpDisConnable()
	{
		m_pkiller = NULL;
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


public:

	virtual void OnDisConn() { ; } 


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

	SOCKET GetRemoteSoc () const
	{
		return m_socRemote;
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
		return 255;
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



	tbool Conn( std::string nameOraddr ) 
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( nameOraddr, std::string(":"), 1, vecNameParts );
			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return this->Conn( vecNameParts[0], vecNameParts[1] );
		}
		catch(...)
		{
			
			return 0;
		}
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
		saddr.sin_addr.s_addr = htonl(a_in_addrip);	

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


	static void GetLine1ParaFromHead( const std::string & strHttpHead,
										std::string & rstrCmdLine1,
										std::string & rstrCmdVerb,
										std::string & rstrProtocolName,
										std::string & rstrAddr		)
	{
		wl::SCake ck;
		std::string strSep;
		std::string strAddrTmp;

		std::string strCmdLine1, strCmdVerb,strProtocolName, strAddr;

		ck.lets( strHttpHead );

		strCmdLine1 = SStrvs::vsa_get( strHttpHead, std::string("\n"), 1, 0 );
		wl::SStrf::strim( strCmdLine1 );

		strCmdVerb = SStrvs::vsa_get( strCmdLine1, std::string(" "), 1, 0 );

		
		ck.lets( strCmdLine1 );
		for( char *p = wl::SStrf::splast( ck.buf() ); p != ck.buf(); p-- )
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
		strAddr = wl::SStrvs::vsa_get( strAddrTmp, strSep, 1, 1 );


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
	}


	static std::string GetHostAddrFromUrl( std::string  strUrl )
	{
		std::string strConnWho;

		
		

		SStrf::strim( strUrl );
		strUrl = "a " + strUrl + " a"; 

		std::string s1;

		GetLine1ParaFromHead( strUrl, s1, s1, s1, strConnWho );

		return strConnWho;
	}



	static std::string GetResPathnameFromUrl( std::string  strUrl )
	{
		std::string::size_type ssti;
		std::string s;

		
		s = GetHostAddrFromUrl( strUrl );
		s = wl::SStrvs::vsa_get( std::string(s), std::string(":"), 1, 0 );


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


	SCake SimpleHttpGetFile( std::string strUrl )
	{
		WTcpHttp & h(*this);
		std::string & s(strUrl);
		SCake ckTmp;

		

		
		h.ConnUrl( s );
		AddUrlHeadPara( "Connection", "close" );
		h.SendHttpGet( s, "HTTP/1.0" );

		h.recv_ln( ckTmp, "\r\n\r\n" );

		h.ImportSvrRtnHeadPara( ckTmp );
		int i;
		i = atol( h.GetSvrRtnHeadParaVal( "Content-Length" ).c_str() );

		if( i <= 0 ) return SCake();

		h.recv_len( ckTmp , i );
		h.DisConn();

		return ckTmp;
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

	tbool  m_biComportOpened;
	tbool  m_biShouldDisConn;


private:

	WComeliProtocol & operator = (const WComeliProtocol & rhs) 	{ 	return *this; }
	WComeliProtocol(const WComeliProtocol & rhs) {;}


public:

	WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;

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


		
		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
		}
		
		for( tsize i2 = 0; pdata2 && i2 < pdata2->len(); i2++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)((*pdata2).buf()+i2) );
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
			strComName = "COM"+nv.get("com");

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
		if(m_biShouldDisConn)
		{
			return 0;
		}

		ckDataBuf.redim( on_get_defaultrecv_buf_len() );

		DWORD dwBytes;

		ReadFile(m_hComport, ckDataBuf.buf(), ckDataBuf.len(), &dwBytes, 0);

		if(dwBytes == ckDataBuf.len()) return (int)ckDataBuf.len();

		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		DWORD ret;

		WriteFile( m_hComport, ckDataBuf.buf_const(), 1 ,&ret, NULL ); 

		if( ckDataBuf.len() % 13 == 3 || SStrf::rand1() > 0.88 )
			WThrd::tr_sleep( 0, 0.001 );

		return (int)ret;
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
		return WMsg::MkUId();
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






#ifndef X011__H_a01env_csr_envinit_h
#define X011__H_a01env_csr_envinit_h



X011_NAMESPACE_BEGIN




class wl_y_csr_com_envinit {
private:
	int com_opened_byme;

	static int wl_y_csr_comopen(void)
	{
		int rc=1;
		try
		{
			::CoInitialize(NULL);
		}
		catch (...)
		{
			rc=0;
		}
		return rc ;
	}

	static int wl_y_csr_comclose(void)
	{
		int rc=1;
		try
		{
			::CoUninitialize();
		}
		catch (...)
		{
			rc=0;
		}
		return rc ;
	}

public:

	wl_y_csr_com_envinit()
	{
		ADODB::_ConnectionPtr 	iv_Cnn;
		HRESULT hr= E_FAIL;

		

		if(!(SUCCEEDED(hr))){
			wl_y_csr_comopen();
			com_opened_byme=1;
		}else
			com_opened_byme=0;
	 }

	~wl_y_csr_com_envinit()
	{
		if(com_opened_byme)
			wl_y_csr_comclose();
	}
};


static volatile  wl_y_csr_com_envinit   wl_y_csr_com_env_init___234tb463_obj;


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

	WCsrAdoBase()
	{
		;
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
				throw 0;
			}

			hr = m_Cnn->Open( _bstr_t( _env.c_str() ),
							  "",
							  "",
							  NULL	);
			if( FAILED(hr) )
			{
				throw 0;
			}

			
			m_Cnn->CommandTimeout = 0;
		}
		catch(...)
		{
			m_Cnn=NULL;
			return 0;
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
				throw 0;
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
			m_Rs1 = NULL;
			return rc=0;
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

		m_Rs1 = NULL;
	}


	virtual void OnCloseEnv()
	{
		if( GetIsEnvOpen() )
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

		m_Cnn = NULL;
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




#pragma warning(pop)

#endif

#ifdef LINUENV_



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

	typedef char * (* PT_strcpy)( char *strDestination, const char *strSource );
	static PT_strcpy p_strcpy() { return strcpy; }


	typedef tm * (* PT_localtime)( const time_t * );
	static PT_localtime p_localtime() { return localtime; }

	typedef FILE * (* PT_fopen)( const char *filename, const char *mode );
	static PT_fopen p_fopen(){ return fopen; }


	static char * ltoaB( long _Val, char * _DstBuf, int _Radix)
	{
		if(_Radix==16)
			sprintf(_DstBuf, "%x",  _Val);
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


	template< class T >
	static T & chgendian( T & val )
	{
		if( sizeof(T) != 1 ) srev( (tchar *)&val, sizeof(T) );
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


	template<class T>
	static tbool readbit( T bindata , int sufx )
	{
		return readbit_s( &bindata, (int)sizeof(T), sufx );
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


	static void writebit_s( void * pbin, int iBytesLen, int sufx , tbool val )
	{
		if( sufx < 0 || iBytesLen <= 0 || (sufx / 8) >= iBytesLen )
		{
			return;
		}
		writebit( pbin, sufx , val );
	}



	
	template<class T> 
	static std::string & byte2str( T c, std::string & strrtn )
	{
		strrtn = "01234567";
		for( int i = 0; i < 8; i++ ) strrtn[i] = readbit( c, i ) ? '1' : '0' ;
		return strrtn;
	}

	
	template<class T> 
	static std::string byte2str( T c )
	{
		std::string str;
		return byte2str( c, str );
	}

	
	template<class T> 
	static T & str2byte( std::string str, T & c )
	{
		
		str += "00000000";
		for( int i = 0; i < 8; i++ ) writebit( &c, i , str[i]=='0' ? 0 : 1 );
		return c;
	}

	
	static tuint8 str2byte( std::string str )
	{
		tuint8 c;
		return str2byte( str, c );
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

	
	static void *smemcpy( void *dest, const void *src, tsize count )
	{
		return memcpy(dest,src,count);
	}

	
	static void * smemset( void *dest, tchar c, tsize count )
	{
		return memset( dest, (int)c, (size_t)count );
	}

	
	template< class T >
	static void * smemset( T & dest, tchar c = 0 )
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

	
	static std::string sultoa( tuint32 i )
	{
		std::stringstream stream;
		stream << i;
		return stream.str();
	}

	
	static tuint32 satoul( std::string  s )
	{
		return strtoul(s.c_str(),NULL,10);
	}


	static std::string GetBcdStr( tuint8 c1 )
	{
		char s[11];
		(*SClib::p_sprintf())( s, "%X", (unsigned int)c1 );
		return s;
	}

	
	static std::string GetBcdStr( std::string s1 )
	{
		tuint8 c1;
		c1 = (tuint8)satol(s1);
		char s[11];
		(*SClib::p_sprintf())( s, "%X", (unsigned int)c1 );
		return s;
	}

	
	static int GetBcdInt( tuint8 c1 )
	{
		return (int)satol(GetBcdStr(c1));
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
		std::vector<tchar> v( 22 + decimal_digits );
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
		lia = (tint16 *)smalloc( (slen(s_num) + 1)*sizeof(tint16) );
		if(!lia)
		{
			sfree(s_num);
			return "";
		}

		scpy( s_num, strCurNum.c_str() );

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

	static std::string  & bs_de( std::string & strData )
	{
		std::string s1( strData + "123" );

		bs_de( strData.c_str(), &(s1[0]) );

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


	
	template< class T >
	static std::string b2s(  T & sourcedata )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( sizeof(T) * 3 + 12 );
		bs_en( (const char *)reinterpret_cast<const char *>(&reinterpret_cast< char& >(sourcedata)), sizeof(T), szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
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
					p2[i] = p1[i] & (tuint8)0x7f;
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


	static tuint32 chksum( const tchar *s, tsize len)
	{
		tuint32 j=0;
		if(SStrf::slen(s)==0)
			return 0;
		while(len--)
		{
			j += (tuint8)s[len]+(len+1);
			j &= 0x7FffFFff;
		}
		return j;
	}


	static tchar * xorB( tchar * Src, tsize len, tuint8 x )
	{
		tsize i;
		tuint8 *s=(tuint8 *)Src;
		if( !s || !len ) return (tchar*)s;
		for(i=0;i<len;i++) s[i] ^= x;
		return (tchar*)s;
	}


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
	static ELET & vs_groupbig( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typedef typename std::vector<ELET>::iterator iteratortypeB;
		iteratortypeB it1;
		std::vector<int>::iterator it2, it3;
		int i;

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
	static ELET & vs_groupsmall( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typename std::vector<ELET>::iterator it1;
		std::vector<int>::iterator it2, it3;
		int i;

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


	virtual ~SCake_base( ) { freeall(); }


	
	
	
	

	
	
	

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


	SCake & bs_de() 
	{
		tsize iDatalen = SStrf::bs_desize( buf() );
		SStrf::bs_de( buf() );
		redim( iDatalen, 1 );
		return *this;
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
			return strOut = std::string( this->buf_const(), this->len() );
		}
		return strOut = "";
	}

	
	std::string mk_str() const
	{
		std::string s1;
		return mk_str(s1);
	}


	std::string GetReadable() const
	{
		std::string strOut = "L" + SStrf::sltoa( (int)this->len() ) + "-";

		
		
		
		for( tsize i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;

			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;

			

			char sz1[22];
			(*SClib::p_sprintf())( sz1, "%02X", (int)(*p2) );
			strOut += sz1;
		}

		return strOut;
	}


	long ConvStr2Bin( std::string strData, void * pData ) const
	{
		std::vector<std::string> vec1;

		wl::SStrvs::vsa_imp( strData, std::string(" "), 1, vec1 );

		for( std::vector<std::string>::size_type i = 0; pData && i < vec1.size(); i++ )
		{
			int ii;
			(SClib::p_sscanf())( vec1[i].c_str(), "%x", &ii );
			*((wl::tuint8*)pData+i) = (wl::tuint8)ii;
		}

		return (long)vec1.size();
	}

	
	long ConvStr2Bin( std::string strData )
	{
		redim( ConvStr2Bin( strData, NULL ) );
		return ConvStr2Bin( strData, buf() );
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

public: 

	SCakel & operator = ( const SCakel & cakel2 )
	{
		clean();
		return append(cakel2);
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_sdte_h
#define X011__H_w_sdte_h



X011_NAMESPACE_BEGIN


class SDte
{


public:

	int m_year;
	int m_mon;
	int m_day;
	int m_hour;
	int m_min;
	int m_sec;
	

private:

	static tbool d_is_leap_year(int y)
	{
		return y%400==0||y%4==0&&y%100!=0;
		
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

	
	static tint32 DiffSecToday(SDte dt)
	{
		SDte a=dt;
		SDte b=a;
		b.m_hour=b.m_min=b.m_sec=0;
		return a.DiffSecInt(b);
	}


	int WeekDay() const
	{
		int i2 = this->DiffDay( wl::SDte() );
		return (i2 - 2 ) % 7;
	}


	SDte & Relative( const SDte & dte2 )
	{
		m_year += dte2.m_year;
		m_mon  += dte2.m_mon;
		m_day  += dte2.m_day;
		m_hour += dte2.m_hour;
		m_min  += dte2.m_min;
		m_sec  += dte2.m_sec;

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


	std::string ReadString() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 m_year, m_mon, m_day,
					 m_hour, m_min, m_sec	);
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
								m_day,s2[m_mon], m_year );
		return sBuf;
	}

	
	void GetBcdArr( SCake & ck ) const 
	{
		std::string s1 = ReadStringPack14();
		std::vector<std::string> vec1;

		wl::SStrvs::vsa_impbylen( s1, 2, vec1 );

		s1.clear();
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


	tbool erase()
	{
		return 0==remove( m_strFilename.c_str() )?1:0;
	}

	static tbool erase(std::string strfilename)
	{
		return 0==remove( strfilename.c_str() )?1:0;
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


	tbool read_str( SCake_base<tchar> & buf ) 
	{
		return this->read( buf, 1 );
	}


	tbool read_bs( std::string & strRtnBs )
	{
		SCake ck;

		if( !this->read( ck ) ) return 0;
		strRtnBs = ck.len() ? ck.bs_en().buf() : "";

		return 1;
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


	tbool read_vecstr( std::vector<std::string> & vecLines, std::string strSep, tbool istoken = 1 )
	{
		wl::SCake ckData;
		if( !read_str( ckData ) ) return 0;
		if( !ckData.len() ) return 0;
		SStrvs::vsa_imp( std::string(ckData.buf()), strSep, istoken, vecLines );
		return 1;
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

	typedef typename std::map< nameT, valueT >::iterator	MAP_MAPKNL_IT;
	typedef typename std::map< nameT, valueT >::const_iterator  MAP_MAPKNL_CONSTIT;

	MAP_MAPKNL_IT m_it4name;

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


	tbool GetFirstName( nameT & Name )
	{
		m_it4name = m_mapKnl.begin();
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool GetNextName( nameT & Name )
	{
		m_it4name ++;
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool operator < ( const SNava_base & rhs) const
	{
		return ( m_mapKnl < rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator <= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl <= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator > ( const SNava_base & rhs) const
	{
		return ( m_mapKnl > rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator >= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl >= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator == ( const SNava_base & rhs) const
	{
		return ( m_mapKnl == rhs.m_mapKnl ? 1 : 0 );
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
		if( ck.len() == 0 ) return;
		ck.bs_de();
		if( !ck.buf() ) ck.lets(""); 
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
		SCake ckTmp1,ckTmp2;

		SStrvs::vsa2v_prpt( strData, std::string(")"), std::string("(") , mapTmp );

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			ckTmp1.lets( it->first );
			seri_element_de( ckTmp1 );
			ckTmp2.lets( it->second );
			seri_element_de( ckTmp2 );

			let( std::string(ckTmp1.buf()), std::string(ckTmp2.buf()) );
		}

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

protected:

	SCake m_ckDataL2CacheBuf;


protected:

	tsize sys_recv( SCake & ckDataBuf )
	{
		int i = on_sys_recv(ckDataBuf); 
		if(i)
		{
			return i;
		}
		else
		{
			ckDataBuf.redim(0);
			return 0;
		}
	}


	tsize sys_send( const SCake & ckDataBuf )
	{
		return on_sys_send(ckDataBuf);
	}


public:

	IRice( )
	{
		
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


	template<class T>
	tbool send_bin( T adata )
	{
		SCake ck;
		ck.let( (SCake::CkEle_t*)&adata, sizeof(T) );
		return send_bin(ck);
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
		if( it != m_mapColNames.end() ) return GetEle(row, it->second);
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
		pthread_mutexattr_settype(&attr,PTHREAD_MUTEX_RECURSIVE_NP);
		pthread_mutex_init(m_pcsSelf,&attr);
		pthread_mutexattr_destroy(&attr);
	}


	WCrsc( WCrsc & Crsc_father)
	{
		InitVars();

		LockCrsc( Crsc_father );
	}

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
	wl::WCrsc		m_ut_tbl_lck;

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

	virtual std::string & ut_SeriTbl( std::string & strOut )=0;
	virtual void ut_SeriTbl( SFile & fl ) = 0;
	virtual void ut_SeriTbl( SFile & fl, long lbegin, long lend ) = 0;
	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend ) = 0;

	virtual long ut_AddRow() = 0;
	virtual long ut_AddRow( std::string strRowSeriStr) = 0;
	virtual void ut_ReIdx() = 0;
	virtual void ut_DelRowf( long lRowNum ) = 0;
	virtual void ut_DelRow( long lRowNum ) = 0;

	virtual void * ut_GetRowAddr( long lRowNum ) = 0;

	virtual unitbl_base_t * ut_GetDup() = 0;
	virtual void ut_DestroyDup(unitbl_base_t *p) { 	if( p ) delete p; }
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

	virtual std::string & ut_SeriTbl( std::string & strOut )
	{
		return T::Serialize( strOut );
	}

	virtual void ut_SeriTbl( SFile & fl )
	{
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "wb" );
		if(fp==NULL) return;
		for(long i=0;i<(long)T::GetRowCount();i++)
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		fclose(fp);
	}

	virtual void ut_SeriTbl( SFile & fl, long lbegin, long lend )
	{
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "ab" );
		if(fp == NULL) return;
		for( long i = lbegin;i<(long)lend + 1; i++ )
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		fclose(fp);
	}

	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend )
	{
		T::Unserialize( strIn.c_str() , biAppend )	;
		return *this;
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


	void rename( std::string strNewNameCanBeWithNewDir )
	{
		std::string strCmd;

		strCmd = "mv \"";
		strCmd += this->filename();
		strCmd += "\" ";
		strCmd += "\"" + strNewNameCanBeWithNewDir + "\"";

		system( strCmd.c_str() );
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

		while( pdirent = readdir(pdir) )
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

	}


	static void UnPackFolder( std::string strWorkPathOrDir, const SCake & ckIn , std::vector<std::string> *pvDirFullNameLst = NULL, std::vector<std::string> *pvFileFullPathNameLst = NULL )
	{
		if( ckIn.len() == 0 ) return;

		
		
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;


		std::string strTD = "\t";
		std::string strTR = "\n";

		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;

		strInfoHeader = (const char*)ckIn.buf_const();



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 ), strTD, 1, vDirNameLst );

		std::sort( vDirNameLst.begin(), vDirNameLst.end() ); 

		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vDirFullNameLst.push_back( s1 );

			
			
			
			mkdir(s1.c_str(), 0777);
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 1 ), strTD, 1, vFileRelaPathNameLst );

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vFileFullPathNameLst.push_back( s1 );
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 2 ), strTD, 1, vFileLenLst );


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

			sf.write( p1, (tsize)i1 );

			vFileFullPathNameLst.erase( vFileFullPathNameLst.begin() );
			vFileLenLst.erase( vFileLenLst.begin() );

			p1 += i1;
		}

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
			if( it->find(strMemoLineHead) == 0 ) continue;

			(*it)[i] = 0;
			this->let( it->c_str(), it->c_str() + i + ssepTD.size() );
		}

		this->trimall();
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


	void ChtoUtf8()
	{
		AtoB( WFile::ChtoUtf8 );
	}

	void Utf8toCh()
	{
		AtoB( WFile::Utf8toCh );
	}


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


private:


	static void * ThreadProc(void * lpParam)
	{
		WThrd *pThis=reinterpret_cast<WThrd*>(lpParam);

		pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL); 

		try
		{
			pThis->tr_on_pre_thrd();
			pThis->tr_on_knl_run();
			pThis->tr_on_post_thrd();

			pThis->tr_shouldbrk();

			pThis->m_iLive = 0;

			if(pThis->m_iAutoDel)
			{
				if( !pThis->m_iCreationDone )
				{
					while( !pThis->m_iCreationDone ) tr_sleep( 1 );
					tr_sleep( 1 );
				}

				tr_sleep( 2 ); 

				delete pThis;
			}
		}
		catch(...)
		{ ;		}

		return((void *)0);
	}


private:

	WThrd & operator = (const WThrd & rhs)
	{
		return *this;
	}


	WThrd(const WThrd & rhs)
	{;}


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
	}


	virtual ~WThrd()
	{
		pthread_attr_destroy(&m_stacksize);


		if( !m_iOpened ) return;

		try
		{
			tr_shouldbrk();

			if( !m_iAutoDel )
				pthread_join( m_hThread , NULL );

			
		}
		catch(...)
		{; }

		if( m_iAutoDel )
			if( m_iShouldDetach ) pthread_detach(m_hThread); 
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


	static void tr_sleep( int iSec , double dSec = 0.0 )	
	{
		if( iSec > 0 )
			sleep( iSec );

		if( dSec > 0.0 )
		{
			usleep( static_cast<int>(dSec * 1000 * 1000) );
		}
	}


	tbool tr_open()
	{
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

		pthread_join( m_hThread , NULL );

		m_iAutoDel = 0;
		m_iShouldDetach = 0;

		return 0;
	}



	
	virtual void on_before_tr_open()
	{
	}

	
	virtual void tr_on_knl_run()
	{
		while(1)
		{
			if( !tr_on_user_run() ) break;

			if( m_iShouldBreak ) break;

			pthread_testcancel();
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
	int                    m_iFailWaitTimesec; 
	tbool                  m_biIsMultiEleType;

public:
	
	WThrdMgr()
	{
		m_biMgrShouldBreak = 0;
		m_iFailWaitTimesec = 2;
		m_biIsMultiEleType = 1;
	}

	
	virtual ~WThrdMgr()
	{;	}

	
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
		ThrEle_t * p = new ThrEle_t;

		if( !p ) return NULL;

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
			WThrd::tr_sleep( m_iFailWaitTimesec > 0 ? m_iFailWaitTimesec : 2 );

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
		WCrsc aLock( this->m_crscThrdLst );
		WThrdEle * p = SStrf::AddressOf( t );

		m_vecThrdLst.push_back( p );
		return GetThrdAmount();
	}

	
	int RemoveEle( WThrdEle & t )
	{
		WCrsc aLock( this->m_crscThrdLst );
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
		WCrsc aLock ( m_crscThrdOpenFunc );
		WCrsc a2Lock( m_crscThrdLst );

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
		WCrsc aLock( m_crscThrdOpenFunc );

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
		WCrsc aLock( m_crscThrdOpenFunc );

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






template < class TASK_T >
class WIdleThrd
{
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

public:
		
		class WIdleThrdEle : public WThrd
		{
		private:
			WIdleThrd<TASK_T>  * m_pWIdleThrd;

			
			int tr_on_user_run()
			{
				if(1)
				{
					WCrsc aaa2(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck);
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef++;
				}

				TASK_T t;
				WCrsc aaa(m_pWIdleThrd->m_crTasksRunLck); 

				if(1)
				{
					WCrsc aaa2(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck);
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef--;
				}

				for( ; m_pWIdleThrd->GetTask(t); )  
				{
					m_pWIdleThrd->OnRun(t);
				}

				return 0;
			}

			
			virtual void tr_on_pre_thrd()
			{
				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdRunRefLck);
				m_pWIdleThrd->m_iWorkThrdRunRef++;
			}

			
			virtual void tr_on_post_thrd()
			{
				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdRunRefLck);
				m_pWIdleThrd->m_iWorkThrdRunRef--;
			}

		public:
			
			WIdleThrdEle( WIdleThrd<TASK_T> *p )
			{
				m_pWIdleThrd = p;

				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdObjRefLck);

				m_pWIdleThrd->m_iWorkThrdObjRef++;
			}

			virtual ~WIdleThrdEle()
			{
				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdObjRefLck);

				m_pWIdleThrd->m_iWorkThrdObjRef--;
			}
		};

public:
	
	WIdleThrd()
	{
		m_iWorkThrdObjRef = 0;
		m_iWorkThrdWaitingRunfuncRef = 0;
		m_iWorkThrdRunRef = 0;
	}

	
	virtual ~WIdleThrd()
	{
		while( m_iWorkThrdObjRef > 0 ) WThrd::tr_sleep(1);
	}

public:
	
	void PostTask( const TASK_T & t, tbool biWithWait = 1 )
	{
		if( biWithWait )
		{
			if   ( m_iWorkThrdObjRef              > 9 ) WThrd::tr_sleep(1);
			while( m_iWorkThrdWaitingRunfuncRef   > 4 ) WThrd::tr_sleep(1);
			while( m_iWorkThrdRunRef              > 7 ) WThrd::tr_sleep(1);
		}

		if(1)
		{
			WCrsc aaa(m_crTasksReadLck);

			m_vecTasks.push_back(t);

			if( m_iWorkThrdWaitingRunfuncRef < 2 ) 
			{
				WIdleThrdEle *p = new WIdleThrdEle(this);
				p->tr_openx();
			}

		}

	}


	tbool GetTask( TASK_T & t )
	{
		WCrsc aaa(m_crTasksReadLck);
		if( m_vecTasks.empty() ) return 0;
		t = m_vecTasks[0];
		m_vecTasks.erase( m_vecTasks.begin() );
		return 1;
	}


	void ClearTask()
	{
		WCrsc aaa(m_crTasksReadLck);
		m_vecTasks.clear();
	}


	void WaitAllTaskDone()
	{
		while( m_iWorkThrdRunRef > 0 ) WThrd::tr_sleep(1);
	}


	virtual void OnRun( TASK_T t ) 
	{
		return;
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
#include <linux/soundcard.h>


X011_NAMESPACE_BEGIN


class WSnd
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

	static void PlayWav( std::string strFile )
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
			if( !strncmp(data_chunk.Chunk_ID, "data", 4) )
			{
				
				
				writed = 0;
				while(writed < data_chunk.Chunk_Size)
				{
					readbytes = fread(buf, 1, 512, fwave);
					writebytes = write(sndfd, buf, readbytes);
					if( writebytes != readbytes )
						perror("wrote wrong number of bytes");
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

		WFile fl;

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
		WCrsc aLock(m_LogLck);

		if( m_iRelativeDay >= 0 ) return;

		if( m_iLogCounter++ >= 10000 ) 
		{
			m_iLogCounter=0;
			WashLogFile();
		}

		WFile fl;

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
	void WriteLog(T val1)
	{	
		std::stringstream stream1;
		std::string strOut;
		stream1 << val1;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str());
		WriteStr(strOut);
	}

	template<class T1, class T2>
	void WriteLog(T1 val1, T2 val2 )
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
	void WriteLog(T1 val1, T2 val2, T3 val3)
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
		int  m_i;
		int  m_iMaxSec;
		double  m_d;
		double  m_dMaxSec2;

		MyTimeKiller( WTcpDisConnable * ph, int iMaxSec, double dMaxSec2 = 0.0 )
		{
			m_ph = ph;
			m_i = 0;
			m_iMaxSec = iMaxSec;
			m_d = 0.0;
			m_dMaxSec2 = dMaxSec2;
		}

		virtual ~MyTimeKiller()
		{
			m_i = 0;
			tr_shouldbrk();

			
			
		}


		virtual int tr_on_user_run()
		{
			if( m_i <= m_iMaxSec )
			{
				m_i++;
				if( m_i > m_iMaxSec )
				{
					
					
				}
				else
				{
					WThrd::tr_sleep(1);
					return 1;
				}
			}

			if( m_d < m_dMaxSec2 ) 
			{
				m_d += m_dMaxSec2;
				WThrd::tr_sleep( 0 , m_dMaxSec2 );
				return 1;
			}

			if( this->tr_isShouldBrk() ) return 0;

			if(m_ph) m_ph->DisConn();
			return 0;
		}
	};


	MyTimeKiller * m_pkiller;


	void killer_up( int iMaxSec ) 
	{
		killer_dn() ;
		m_pkiller = new MyTimeKiller( this, iMaxSec );
		m_pkiller->tr_open();
	}


	void killer_dn()
	{
		if( m_pkiller != NULL )
		{
			delete m_pkiller;
			m_pkiller = NULL;
		}
	}

public:

	WTcpDisConnable()
	{
		m_pkiller = NULL;
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


public:

	virtual void OnDisConn() { ; } 


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

	SOCKET GetRemoteSoc () const
	{
		return m_socRemote;
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
		return 255;
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



	tbool Conn( std::string nameOraddr ) 
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( nameOraddr, std::string(":"), 1, vecNameParts );
			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return this->Conn( vecNameParts[0], vecNameParts[1] );
		}
		catch(...)
		{
			
			return 0;
		}
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
		saddr.sin_addr.s_addr = htonl(a_in_addrip);	

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







#ifndef X011__H_w_WComeliProtocol_h
#define X011__H_w_WComeliProtocol_h


X011_NAMESPACE_BEGIN


class WComeliProtocol : public WTcpDisConnable
{

public:

	tbool  m_biComportOpened;
	tbool  m_biShouldDisConn;


private:

	WComeliProtocol & operator = (const WComeliProtocol & rhs) 	{ 	return *this; }
	WComeliProtocol(const WComeliProtocol & rhs) {;}


public:

	WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;

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


		
		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
		}
		
		for( tsize i2 = 0; pdata2 && i2 < pdata2->len(); i2++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)((*pdata2).buf()+i2) );
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
		if(m_biShouldDisConn)
		{
			return 0;
		}

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

		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		int len   =   0;

		len   = write( m_hComport, ckDataBuf.buf_const(), 1 );

		if (len   >   0)
		{
			
			if( ckDataBuf.len() % 13 == 3 || SStrf::rand1() > 0.88 )
				WThrd::tr_sleep( 0, 0.001 );
		}

		return (int)len;
	}


}; 



X011_NAMESPACE_END

#endif




#endif

#ifdef WCEENV_



#ifndef X011__H_w_sbase_h
#define X011__H_w_sbase_h


#define X011_NAMESPACE_BEGIN namespace wl {
#define X011_NAMESPACE_END                }


#include <iterator>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

	typedef char * (* PT_strcpy)( char *strDestination, const char *strSource );
	static PT_strcpy p_strcpy() { return strcpy; }


	typedef tm * (* PT_localtime)( const time_t * );
	static PT_localtime p_localtime() { return localtime; }

	typedef FILE * (* PT_fopen)( const char *filename, const char *mode );
	static PT_fopen p_fopen(){ return fopen; }


	static char * ltoaB( long _Val, char * _DstBuf, int _Radix)
	{
		if(_Radix==16)
			sprintf(_DstBuf, "%x",  _Val);
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


	template< class T >
	static T & chgendian( T & val )
	{
		if( sizeof(T) != 1 ) srev( (tchar *)&val, sizeof(T) );
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


	template<class T>
	static tbool readbit( T bindata , int sufx )
	{
		return readbit_s( &bindata, (int)sizeof(T), sufx );
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


	static void writebit_s( void * pbin, int iBytesLen, int sufx , tbool val )
	{
		if( sufx < 0 || iBytesLen <= 0 || (sufx / 8) >= iBytesLen )
		{
			return;
		}
		writebit( pbin, sufx , val );
	}



	
	template<class T> 
	static std::string & byte2str( T c, std::string & strrtn )
	{
		strrtn = "01234567";
		for( int i = 0; i < 8; i++ ) strrtn[i] = readbit( c, i ) ? '1' : '0' ;
		return strrtn;
	}

	
	template<class T> 
	static std::string byte2str( T c )
	{
		std::string str;
		return byte2str( c, str );
	}

	
	template<class T> 
	static T & str2byte( std::string str, T & c )
	{
		
		str += "00000000";
		for( int i = 0; i < 8; i++ ) writebit( &c, i , str[i]=='0' ? 0 : 1 );
		return c;
	}

	
	static tuint8 str2byte( std::string str )
	{
		tuint8 c;
		return str2byte( str, c );
	}

	
	static void initrand( int seed = 0 ) 
	{
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);
		int i = (int)( sysTime.wSecond + sysTime.wMilliseconds + GetTickCount() );
		tint32 j=(tint16)(0x0555&(i*seed));
		for(tint32 i=0;i<j;++i) rand();
	}

	
	static tdouble rand1( int iShouldInitSeed = 0 )
	{
		if( iShouldInitSeed ) initrand( iShouldInitSeed );
		return (tdouble)rand()/(tdouble)RAND_MAX;
	}

	
	static void *smemcpy( void *dest, const void *src, tsize count )
	{
		return memcpy(dest,src,count);
	}

	
	static void * smemset( void *dest, tchar c, tsize count )
	{
		return memset( dest, (int)c, (size_t)count );
	}

	
	template< class T >
	static void * smemset( T & dest, tchar c = 0 )
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

	
	static std::string sultoa( tuint32 i )
	{
		std::stringstream stream;
		stream << i;
		return stream.str();
	}

	
	static tuint32 satoul( std::string  s )
	{
		return strtoul(s.c_str(),NULL,10);
	}


	static std::string GetBcdStr( tuint8 c1 )
	{
		char s[11];
		(*SClib::p_sprintf())( s, "%X", (unsigned int)c1 );
		return s;
	}

	
	static std::string GetBcdStr( std::string s1 )
	{
		tuint8 c1;
		c1 = (tuint8)satol(s1);
		char s[11];
		(*SClib::p_sprintf())( s, "%X", (unsigned int)c1 );
		return s;
	}

	
	static int GetBcdInt( tuint8 c1 )
	{
		return (int)satol(GetBcdStr(c1));
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
		std::vector<tchar> v( 22 + decimal_digits );
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
		lia = (tint16 *)smalloc( (slen(s_num) + 1)*sizeof(tint16) );
		if(!lia)
		{
			sfree(s_num);
			return "";
		}

		scpy( s_num, strCurNum.c_str() );

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

	static std::string  & bs_de( std::string & strData )
	{
		std::string s1( strData + "123" );

		bs_de( strData.c_str(), &(s1[0]) );

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


	
	template< class T >
	static std::string b2s(  T & sourcedata )
	{
		std::string str1;
		tchar * szstr;
		szstr = (tchar *)smalloc( sizeof(T) * 3 + 12 );
		bs_en( (const char *)reinterpret_cast<const char *>(&reinterpret_cast< char& >(sourcedata)), sizeof(T), szstr );
		str1 = szstr;
		sfree( szstr );
		return str1;
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
					p2[i] = p1[i] & (tuint8)0x7f;
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


	static tuint32 chksum( const tchar *s, tsize len)
	{
		tuint32 j=0;
		if(SStrf::slen(s)==0)
			return 0;
		while(len--)
		{
			j += (tuint8)s[len]+(len+1);
			j &= 0x7FffFFff;
		}
		return j;
	}


	static tchar * xor( tchar * Src, tsize len, tuint8 x )
	{
		tsize i;
		tuint8 *s=(tuint8 *)Src;
		if( !s || !len ) return (tchar*)s;
		for(i=0;i<len;i++) s[i] ^= x;
		return (tchar*)s;
	}


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
	static ELET & vs_groupbig( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typedef typename std::vector<ELET>::iterator iteratortypeB;
		iteratortypeB it1;
		std::vector<int>::iterator it2, it3;
		int i;

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
	static ELET & vs_groupsmall( std::vector<ELET> & memo, std::vector<int> & subsum )
	{
		typename std::vector<ELET>::iterator it1;
		std::vector<int>::iterator it2, it3;
		int i;

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


	virtual ~SCake_base( ) { freeall(); }


	
	
	
	

	
	
	

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


	SCake & bs_de() 
	{
		tsize iDatalen = SStrf::bs_desize( buf() );
		SStrf::bs_de( buf() );
		redim( iDatalen, 1 );
		return *this;
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
			return strOut = std::string( this->buf_const(), this->len() );
		}
		return strOut = "";
	}

	
	std::string mk_str() const
	{
		std::string s1;
		return mk_str(s1);
	}


	std::string GetReadable() const
	{
		std::string strOut = "L" + SStrf::sltoa( (int)this->len() ) + "-";

		
		
		
		for( tsize i = 0; i < this->len(); i++ )
		{
			const CkEle_t *p1;
			const tuint8 *p2;

			p1 = this->buf_const() + i;
			p2 = (const tuint8*)p1;

			

			char sz1[22];
			(*SClib::p_sprintf())( sz1, "%02X", (int)(*p2) );
			strOut += sz1;
		}

		return strOut;
	}


	long ConvStr2Bin( std::string strData, void * pData ) const
	{
		std::vector<std::string> vec1;

		wl::SStrvs::vsa_imp( strData, std::string(" "), 1, vec1 );

		for( std::vector<std::string>::size_type i = 0; pData && i < vec1.size(); i++ )
		{
			int ii;
			(SClib::p_sscanf())( vec1[i].c_str(), "%x", &ii );
			*((wl::tuint8*)pData+i) = (wl::tuint8)ii;
		}

		return (long)vec1.size();
	}

	
	long ConvStr2Bin( std::string strData )
	{
		redim( ConvStr2Bin( strData, NULL ) );
		return ConvStr2Bin( strData, buf() );
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

public: 

	SCakel & operator = ( const SCakel & cakel2 )
	{
		clean();
		return append(cakel2);
	}

};




X011_NAMESPACE_END

#endif





#ifndef X011__H_w_sdte_h
#define X011__H_w_sdte_h



X011_NAMESPACE_BEGIN


class SDte
{


public:

	int m_year;
	int m_mon;
	int m_day;
	int m_hour;
	int m_min;
	int m_sec;
	

private:

	static tbool d_is_leap_year(int y)
	{
		return y%400==0||y%4==0&&y%100!=0;
		
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
		int i = (int)( e_proctime() * 1000 );
		return i % 1000;
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

		m_year = 0;
		m_mon  = 0;
		m_day  = 0;

		m_hour = 0;
		m_min = 0;
		m_sec = 0;

		return *this;
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


	SDte & MakeNow()
	{
		SYSTEMTIME sysTime;
		GetLocalTime(&sysTime);

		m_year= sysTime.wYear;
		m_mon = sysTime.wMonth;
		m_day = sysTime.wDay;
		m_hour= sysTime.wHour;
		m_min = sysTime.wMinute;
		m_sec = sysTime.wSecond;
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

	
	static tint32 DiffSecToday(SDte dt)
	{
		SDte a=dt;
		SDte b=a;
		b.m_hour=b.m_min=b.m_sec=0;
		return a.DiffSecInt(b);
	}


	int WeekDay() const
	{
		int i2 = this->DiffDay( wl::SDte() );
		return (i2 - 2 ) % 7;
	}


	SDte & Relative( const SDte & dte2 )
	{
		m_year += dte2.m_year;
		m_mon  += dte2.m_mon;
		m_day  += dte2.m_day;
		m_hour += dte2.m_hour;
		m_min  += dte2.m_min;
		m_sec  += dte2.m_sec;

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


	std::string ReadString() const 
	{
		tchar sBuf[33];
		(*SClib::p_sprintf())(sBuf,"%d-%02d-%02d %02d:%02d:%02d",
					 m_year, m_mon, m_day,
					 m_hour, m_min, m_sec	);
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
								m_day,s2[m_mon], m_year );
		return sBuf;
	}

	
	void GetBcdArr( SCake & ck ) const 
	{
		std::string s1 = ReadStringPack14();
		std::vector<std::string> vec1;

		wl::SStrvs::vsa_impbylen( s1, 2, vec1 );

		s1.clear();
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
		std::wstring ws1( 2+strfilename.size(), L'-' );
		swprintf( &(ws1[0]), L"%S", strfilename.c_str() );
		return   DeleteFile(&(ws1[0])) ? 1 : 0;
	}

	tbool erase()
	{
		return erase(m_strFilename);
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


	tbool read_str( SCake_base<tchar> & buf ) 
	{
		return this->read( buf, 1 );
	}


	tbool read_bs( std::string & strRtnBs )
	{
		SCake ck;

		if( !this->read( ck ) ) return 0;
		strRtnBs = ck.len() ? ck.bs_en().buf() : "";

		return 1;
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


	tbool read_vecstr( std::vector<std::string> & vecLines, std::string strSep, tbool istoken = 1 )
	{
		wl::SCake ckData;
		if( !read_str( ckData ) ) return 0;
		if( !ckData.len() ) return 0;
		SStrvs::vsa_imp( std::string(ckData.buf()), strSep, istoken, vecLines );
		return 1;
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

	typedef typename std::map< nameT, valueT >::iterator	MAP_MAPKNL_IT;
	typedef typename std::map< nameT, valueT >::const_iterator  MAP_MAPKNL_CONSTIT;

	MAP_MAPKNL_IT m_it4name;

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


	tbool GetFirstName( nameT & Name )
	{
		m_it4name = m_mapKnl.begin();
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool GetNextName( nameT & Name )
	{
		m_it4name ++;
		if( m_it4name != m_mapKnl.end() )
		{
			Name = m_it4name->first;
			return 1;
		}
		return 0;
	}


	tbool operator < ( const SNava_base & rhs) const
	{
		return ( m_mapKnl < rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator <= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl <= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator > ( const SNava_base & rhs) const
	{
		return ( m_mapKnl > rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator >= ( const SNava_base & rhs) const
	{
		return ( m_mapKnl >= rhs.m_mapKnl ? 1 : 0 );
	}

	tbool operator == ( const SNava_base & rhs) const
	{
		return ( m_mapKnl == rhs.m_mapKnl ? 1 : 0 );
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
		if( ck.len() == 0 ) return;
		ck.bs_de();
		if( !ck.buf() ) ck.lets(""); 
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
		SCake ckTmp1,ckTmp2;

		SStrvs::vsa2v_prpt( strData, std::string(")"), std::string("(") , mapTmp );

		this->clear();

		for( MAP_MAPKNL_IT it = mapTmp.begin(); it != mapTmp.end(); ++it )
		{
			ckTmp1.lets( it->first );
			seri_element_de( ckTmp1 );
			ckTmp2.lets( it->second );
			seri_element_de( ckTmp2 );

			let( std::string(ckTmp1.buf()), std::string(ckTmp2.buf()) );
		}

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

protected:

	SCake m_ckDataL2CacheBuf;


protected:

	tsize sys_recv( SCake & ckDataBuf )
	{
		int i = on_sys_recv(ckDataBuf); 
		if(i)
		{
			return i;
		}
		else
		{
			ckDataBuf.redim(0);
			return 0;
		}
	}


	tsize sys_send( const SCake & ckDataBuf )
	{
		return on_sys_send(ckDataBuf);
	}


public:

	IRice( )
	{
		
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


	template<class T>
	tbool send_bin( T adata )
	{
		SCake ck;
		ck.let( (SCake::CkEle_t*)&adata, sizeof(T) );
		return send_bin(ck);
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
	typedef std::map<std::string,int> ColNamesMapTYPE;
	typedef typename IDS_ELE_TYPE_T IDS_Ele_TYPE;

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
		if( it != m_mapColNames.end() ) return GetEle(row, it->second);
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
	typedef typename IDS_ELE_TYPE_T IDS_Ele_TYPE;

	typedef typename ICursorDsColNames<IDS_ELE_TYPE_T> ColNamesTYPE;

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






#ifndef X011__H_w_IQar_h
#define X011__H_w_IQar_h


X011_NAMESPACE_BEGIN


template < class QuestionT, class AnswerT >
class IQar
{

private:


public:

	IQar( )
	{
		
	}

	virtual ~IQar( ) { ; }


public:

	tbool IsMyQuestion( const QuestionT & a_Question )
	{
		return OnIsMyQuestion(a_Question);
	}


	tbool Question( const QuestionT & a_Question , AnswerT & a_Answer )
	{
		
		{
			return OnQuestion( a_Question, a_Answer );
		}
		
		
		
	}


public:

	virtual tbool OnIsMyQuestion( const QuestionT & a_Question )
	{
		return 1;
	}


	virtual tbool OnQuestion( const QuestionT & a_Question , AnswerT & a_Answer )
	{
		return 0;
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


	WCrsc( WCrsc & Crsc_father)
	{
		InitVars();

		LockCrsc( Crsc_father );
	}

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
	wl::WCrsc		m_ut_tbl_lck;

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

	virtual std::string & ut_SeriTbl( std::string & strOut )=0;
	virtual void ut_SeriTbl( SFile & fl ) = 0;
	virtual void ut_SeriTbl( SFile & fl, long lbegin, long lend ) = 0;
	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend ) = 0;

	virtual long ut_AddRow() = 0;
	virtual long ut_AddRow( std::string strRowSeriStr) = 0;
	virtual void ut_ReIdx() = 0;
	virtual void ut_DelRowf( long lRowNum ) = 0;
	virtual void ut_DelRow( long lRowNum ) = 0;

	virtual void * ut_GetRowAddr( long lRowNum ) = 0;

	virtual unitbl_base_t * ut_GetDup() = 0;
	virtual void ut_DestroyDup(unitbl_base_t *p) { 	if( p ) delete p; }
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

	virtual std::string & ut_SeriTbl( std::string & strOut )
	{
		return T::Serialize( strOut );
	}

	virtual void ut_SeriTbl( SFile & fl )
	{
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "wb" );
		if(fp==NULL) return;
		for(long i=0;i<(long)T::GetRowCount();i++)
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		fclose(fp);
	}

	virtual void ut_SeriTbl( SFile & fl, long lbegin, long lend )
	{
		FILE *fp = (*wl::SClib::p_fopen())( fl.filename().c_str(), "ab" );
		if(fp == NULL) return;
		for( long i = lbegin;i<(long)lend + 1; i++ )
		{
			std::string strTmp;
			T::GetRow(i).Serialize(strTmp);
			strTmp += "}";
			fwrite( strTmp.c_str(), (size_t)strTmp.size(), 1, fp );
		}
		fclose(fp);
	}

	virtual unitbl_base_t & ut_UnseriTbl( const std::string & strIn, int biAppend )
	{
		T::Unserialize( strIn.c_str() , biAppend )	;
		return *this;
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



X011_NAMESPACE_END

#endif






#ifndef X011__H_w_WClp_h
#define X011__H_w_WClp_h


X011_NAMESPACE_BEGIN


class WClp
{

public:

	WClp()
	{
	}

	 ~WClp()
	{
	}

	static tbool txt_put( std::string txtdata )
	{
		tchar *buffer;
		if(OpenClipboard(0)) {
			HGLOBAL clipbuffer;
			EmptyClipboard();
			clipbuffer = GlobalAlloc(GMEM_MOVEABLE, SStrf::slen(txtdata.c_str())+1);
			buffer = (tchar *)GlobalLock(clipbuffer);
			SStrf::scpy( buffer, txtdata.c_str() );
			GlobalUnlock( clipbuffer );
			SetClipboardData( CF_TEXT, clipbuffer );
			CloseClipboard();
			GlobalFree(clipbuffer);
			return 1;
		}else{
			return 0;
		}
	}

	static tbool txt_put( tchar * txtdata )
	{
		return txt_put( std::string(txtdata?txtdata:"") );
	}


	static std::string txt_get()
	{
		char *buffer;
		std::string strtmp("");

		if ( OpenClipboard(0) )
		{
			HANDLE hData = GetClipboardData(CF_TEXT);
			buffer = (char *)GlobalLock(hData);

			if(buffer)
				strtmp = buffer;

			GlobalUnlock(hData);
			CloseClipboard();
		}
		return strtmp;
	}

	
	static CString txt_getTS()
	{
		CStringW strtmp(L"");

		if ( OpenClipboard(0) )
		{
			HANDLE hData = GetClipboardData(CF_UNICODETEXT);
			wchar_t * buffer = (wchar_t *)GlobalLock(hData);

			if(buffer)
				strtmp = buffer;

			GlobalUnlock(hData);
			CloseClipboard();
		}
		return CString(strtmp);
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



	static std::string MkUId()
	{
		static tint32 i = 1;
		int i2 = (int)time(0) * (int)GetCurrentThreadId() * (int)GetCurrentProcessId();
		int j;
		void *p = SStrf::smalloc(3);
		memcpy( &j, &p, sizeof(int) );
		SStrf::sfree(p);

		double dd = SStrf::rand1() * i * i2 * j * SDte::e_proctime();

		std::reverse( (char*)(&dd), (char*)(&dd) + sizeof(double) );

		tchar szBuf[33];
		SClib::p_sprintf()( szBuf, "%x%u", *(int*)(&dd) + j + i , i++ );

		return szBuf;
	}


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
			printf( "ok in i\n" );
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
			printf( "ok in un\n" );
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






#ifndef X011__H_w_WLog_h
#define X011__H_w_WLog_h


X011_NAMESPACE_BEGIN


class WLog
{

public:

	tbool isEnabled;

	WLog()
	{
		EnableLog();
	}

	virtual ~WLog()	{ 	}


	void EnableLog()
	{
		isEnabled = 1;
	}


	void DisableLog()
	{
		isEnabled = 0;
	}


#ifndef VC6_COMPATIBLE_X011_
	void LogWritef( int iFilter, LPCSTR Text, ... )
	{
		if( !isEnabled ) return;

		if ( Text == NULL )
		{
			return;
		}

		CStringA sTraceMsgA("");

		
		va_list args;
		va_start( args, Text );
		sTraceMsgA.AppendFormatV( Text, args );
		va_end(args);

		std::string s( sTraceMsgA.GetString() );
		OnLogWrite(iFilter,s);
	}
 #endif




#ifndef VC6_COMPATIBLE_X011_
	void LogWritef( LPCSTR Text, ... )
	{
		if( !isEnabled ) return;

		if ( Text == NULL )
		{
			return;
		}

		CStringA sTraceMsgA("");

		
		va_list args;
		va_start( args, Text );
		sTraceMsgA.FormatV( Text, args );
		va_end(args);

		std::string s( sTraceMsgA.GetString() );
		OnLogWrite(0,s);
	}
#endif




public:

	virtual void OnLogWrite( int iFilter, const std::string & s )
	{
		printf( "%d\t%s\n", iFilter, s.c_str() );
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


	
	

	
	
	
	
	

	static tbool FileAttriIsDir( std::string strFullPathName )
	{
		DWORD i = GetFileAttributes( CString(strFullPathName.c_str()) );
		
		
		
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

	}



	static void UnPackFolder( std::string strWorkPathOrDir, const SCake & ckIn , std::vector<std::string> *pvDirFullNameLst = NULL, std::vector<std::string> *pvFileFullPathNameLst = NULL )
	{
		if( ckIn.len() == 0 ) return;

		
		
		std::string strWorkPath;
		std::vector<std::string>::iterator it;
		std::vector<std::string> vDirFullNameLst;
		std::vector<std::string> vDirNameLst;
		std::vector<std::string> vFileFullPathNameLst;
		std::vector<std::string> vFileRelaPathNameLst;
		std::vector<std::string> vFileLenLst;
		std::string strInfoHeader;


		std::string strTD = "\t";
		std::string strTR = "\n";

		strWorkPath = MkDir2Path( strWorkPathOrDir ) ;

		strInfoHeader = (const char*)ckIn.buf_const();



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 0 ), strTD, 1, vDirNameLst );

		std::sort( vDirNameLst.begin(), vDirNameLst.end() ); 

		for( it = vDirNameLst.begin(); it != vDirNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vDirFullNameLst.push_back( s1 );

			CString cs1;
			cs1 = s1.c_str();
			::CreateDirectory( cs1, NULL );
			
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 1 ), strTD, 1, vFileRelaPathNameLst );

		for( it = vFileRelaPathNameLst.begin(); it != vFileRelaPathNameLst.end(); ++it )
		{
			std::string s1;
			s1 = MkDir2Path( strWorkPathOrDir ) + *it ;
			vFileFullPathNameLst.push_back( s1 );
		}



		SStrvs::vsa_imp( SStrvs::vsa_get( strInfoHeader, strTR, 0, 2 ), strTD, 1, vFileLenLst );


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

			sf.write( p1, (tsize)i1 );

			vFileFullPathNameLst.erase( vFileFullPathNameLst.begin() );
			vFileLenLst.erase( vFileLenLst.begin() );

			p1 += i1;
		}

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
			if( it->find(strMemoLineHead) == 0 ) continue;

			(*it)[i] = 0;
			this->let( it->c_str(), it->c_str() + i + ssepTD.size() );
		}

		this->trimall();
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


	void ChtoUtf8()
	{
		AtoB( WFile::ChtoUtf8 );
	}

	void Utf8toCh()
	{
		AtoB( WFile::Utf8toCh );
	}


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




#ifndef _MT
#ifndef X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
#define X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED
#endif
#endif


#define X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED


#ifdef  X011__WL_WIN_THRD_H_WIN_VER_SHOULD_BE_USED

#else

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

		try
		{
			

			pThis->tr_on_pre_thrd();
			pThis->tr_on_knl_run();
			pThis->tr_on_post_thrd();

			
			pThis->tr_shouldbrk();

			pThis->m_iLive = 0;

			if(pThis->m_iAutoDel)
			{
				if( !pThis->m_iCreationDone )
				{
					while( !pThis->m_iCreationDone ) tr_sleep( 1 );
					tr_sleep( 1 );
				}

				tr_sleep( 4 ); 

				delete pThis;
			}
		}
		catch(...)
		{ ;	}

		return (DWORD)0;
	}


private:

	WThrd & operator = (const WThrd & rhs)
	{
		return *this;
	}


	WThrd(const WThrd & rhs)
	{;}


public:

	WThrd()
	{
		m_hThread = INVALID_HANDLE_VALUE;
		m_iAutoDel = 0;
		m_iShouldBreak = 0;
		m_iLive = 0;
		m_iCreationDone = 0;
		m_iOpened = 0;
	}


	virtual ~WThrd()
	{
		if( !m_iOpened ) return;

		try
		{
			tr_shouldbrk();

			
			
			
			
			

			if( !m_iAutoDel )
				tr_wait();

			tr_closehandl();
		}
		catch(...)
		{; }
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


	static void tr_sleep( int iSec , double dSec = 0.0 )	
	{
		if( iSec > 0 )
			Sleep( iSec * 1000 );

		if( dSec > 0.0 )
		{
			Sleep( static_cast<int>(dSec * 1000 * 1) );
		}
	}


	tbool tr_open()
	{
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


	virtual void tr_on_knl_run()
	{
		SStrf::initrand( (int)GetCurrentThreadId() );

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
	int                    m_iFailWaitTimesec; 
	tbool                  m_biIsMultiEleType;

public:
	
	WThrdMgr()
	{
		m_biMgrShouldBreak = 0;
		m_iFailWaitTimesec = 2;
		m_biIsMultiEleType = 1;
	}

	
	virtual ~WThrdMgr()
	{;	}

	
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
		ThrEle_t * p = new ThrEle_t;

		if( !p ) return NULL;

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
			WThrd::tr_sleep( m_iFailWaitTimesec > 0 ? m_iFailWaitTimesec : 2 );

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
		WCrsc aLock( this->m_crscThrdLst );
		WThrdEle * p = SStrf::AddressOf( t );

		m_vecThrdLst.push_back( p );
		return GetThrdAmount();
	}

	
	int RemoveEle( WThrdEle & t )
	{
		WCrsc aLock( this->m_crscThrdLst );
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
		WCrsc aLock ( m_crscThrdOpenFunc );
		WCrsc a2Lock( m_crscThrdLst );

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
		WCrsc aLock( m_crscThrdOpenFunc );

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
		WCrsc aLock( m_crscThrdOpenFunc );

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






template < class TASK_T >
class WIdleThrd
{
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

public:
		
		class WIdleThrdEle : public WThrd
		{
		private:
			WIdleThrd<TASK_T>  * m_pWIdleThrd;

			
			int tr_on_user_run()
			{
				if(1)
				{
					WCrsc aaa2(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck);
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef++;
				}

				TASK_T t;
				WCrsc aaa(m_pWIdleThrd->m_crTasksRunLck); 

				if(1)
				{
					WCrsc aaa2(m_pWIdleThrd->m_crWorkThrdWaitingRunfuncRefLck);
					m_pWIdleThrd->m_iWorkThrdWaitingRunfuncRef--;
				}

				for( ; m_pWIdleThrd->GetTask(t); )  
				{
					m_pWIdleThrd->OnRun(t);
				}

				return 0;
			}

			
			virtual void tr_on_pre_thrd()
			{
				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdRunRefLck);
				m_pWIdleThrd->m_iWorkThrdRunRef++;
			}

			
			virtual void tr_on_post_thrd()
			{
				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdRunRefLck);
				m_pWIdleThrd->m_iWorkThrdRunRef--;
			}

		public:
			
			WIdleThrdEle( WIdleThrd<TASK_T> *p )
			{
				m_pWIdleThrd = p;

				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdObjRefLck);

				m_pWIdleThrd->m_iWorkThrdObjRef++;
			}

			virtual ~WIdleThrdEle()
			{
				WCrsc aaa(m_pWIdleThrd->m_crWorkThrdObjRefLck);

				m_pWIdleThrd->m_iWorkThrdObjRef--;
			}
		};

public:
	
	WIdleThrd()
	{
		m_iWorkThrdObjRef = 0;
		m_iWorkThrdWaitingRunfuncRef = 0;
		m_iWorkThrdRunRef = 0;
	}

	
	virtual ~WIdleThrd()
	{
		while( m_iWorkThrdObjRef > 0 ) WThrd::tr_sleep(1);
	}

public:
	
	void PostTask( const TASK_T & t, tbool biWithWait = 1 )
	{
		if( biWithWait )
		{
			if   ( m_iWorkThrdObjRef              > 9 ) WThrd::tr_sleep(1);
			while( m_iWorkThrdWaitingRunfuncRef   > 4 ) WThrd::tr_sleep(1);
			while( m_iWorkThrdRunRef              > 7 ) WThrd::tr_sleep(1);
		}

		if(1)
		{
			WCrsc aaa(m_crTasksReadLck);

			m_vecTasks.push_back(t);

			if( m_iWorkThrdWaitingRunfuncRef < 2 ) 
			{
				WIdleThrdEle *p = new WIdleThrdEle(this);
				p->tr_openx();
			}

		}

	}


	tbool GetTask( TASK_T & t )
	{
		WCrsc aaa(m_crTasksReadLck);
		if( m_vecTasks.empty() ) return 0;
		t = m_vecTasks[0];
		m_vecTasks.erase( m_vecTasks.begin() );
		return 1;
	}


	void ClearTask()
	{
		WCrsc aaa(m_crTasksReadLck);
		m_vecTasks.clear();
	}


	void WaitAllTaskDone()
	{
		while( m_iWorkThrdRunRef > 0 ) WThrd::tr_sleep(1);
	}


	virtual void OnRun( TASK_T t ) 
	{
		return;
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

		WFile fl;

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
		WCrsc aLock(m_LogLck);

		if( m_iRelativeDay >= 0 ) return;

		if( m_iLogCounter++ >= 10000 ) 
		{
			m_iLogCounter=0;
			WashLogFile();
		}

		WFile fl;

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
	void WriteLog(T val1)
	{	
		std::stringstream stream1;
		std::string strOut;
		stream1 << val1;
		GetTimeStr(strOut);
		strOut += "|" + RefineStrVal(stream1.str());
		WriteStr(strOut);
	}

	template<class T1, class T2>
	void WriteLog(T1 val1, T2 val2 )
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
	void WriteLog(T1 val1, T2 val2, T3 val3)
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


X011_NAMESPACE_END

#endif













#ifndef X011__H_w_wtcp_a01env_netheaderlib_h
#define X011__H_w_wtcp_a01env_netheaderlib_h


#pragma comment( lib, "ws2.lib" )

#include <winsock.h>





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
		return ZEROIFSUCCESSFUL == WSAStartup( 0x0202, &Wa );
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
		int  m_i;
		int  m_iMaxSec;
		double  m_d;
		double  m_dMaxSec2;

		MyTimeKiller( WTcpDisConnable * ph, int iMaxSec, double dMaxSec2 = 0.0 )
		{
			m_ph = ph;
			m_i = 0;
			m_iMaxSec = iMaxSec;
			m_d = 0.0;
			m_dMaxSec2 = dMaxSec2;
		}

		virtual ~MyTimeKiller()
		{
			m_i = 0;
			tr_shouldbrk();

			
			
		}


		virtual int tr_on_user_run()
		{
			if( m_i <= m_iMaxSec )
			{
				m_i++;
				if( m_i > m_iMaxSec )
				{
					
					
				}
				else
				{
					WThrd::tr_sleep(1);
					return 1;
				}
			}

			if( m_d < m_dMaxSec2 ) 
			{
				m_d += m_dMaxSec2;
				WThrd::tr_sleep( 0 , m_dMaxSec2 );
				return 1;
			}

			if( this->tr_isShouldBrk() ) return 0;

			if(m_ph) m_ph->DisConn();
			return 0;
		}
	};


	MyTimeKiller * m_pkiller;


	void killer_up( int iMaxSec ) 
	{
		killer_dn() ;
		m_pkiller = new MyTimeKiller( this, iMaxSec );
		m_pkiller->tr_open();
	}


	void killer_dn()
	{
		if( m_pkiller != NULL )
		{
			delete m_pkiller;
			m_pkiller = NULL;
		}
	}

public:

	WTcpDisConnable()
	{
		m_pkiller = NULL;
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


public:

	virtual void OnDisConn() { ; } 


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

	SOCKET GetRemoteSoc () const
	{
		return m_socRemote;
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
		return 255;
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



	tbool Conn( std::string nameOraddr ) 
	{
		try
		{
			std::vector<std::string> vecNameParts;
			SStrvs::vsa_imp( nameOraddr, std::string(":"), 1, vecNameParts );
			vecNameParts.push_back( std::string("") );
			vecNameParts.push_back( std::string("") );
			return this->Conn( vecNameParts[0], vecNameParts[1] );
		}
		catch(...)
		{
			
			return 0;
		}
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
		saddr.sin_addr.s_addr = htonl(a_in_addrip);	

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







#ifndef X011__H_w_WComeliProtocol_h
#define X011__H_w_WComeliProtocol_h


X011_NAMESPACE_BEGIN


class WComeliProtocol : public WTcpDisConnable
{

public:

	tbool  m_biComportOpened;
	tbool  m_biShouldDisConn;


private:

	WComeliProtocol & operator = (const WComeliProtocol & rhs) 	{ 	return *this; }
	WComeliProtocol(const WComeliProtocol & rhs) {;}


public:

	WComeliProtocol()
	{
		m_biComportOpened = 0;
		m_biShouldDisConn = 0;

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


		
		for( tsize i = 0; i < ckDataInOut.len(); i++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)(ckDataInOut.buf()+i) );
		}
		
		for( tsize i2 = 0; pdata2 && i2 < pdata2->len(); i2++ )
		{
			ucChkSum = (*pf)( ucChkSum, *(tuint8*)((*pdata2).buf()+i2) );
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
			strComName = "COM" + nv.get("com") + std::string(":");

		m_hComport = CreateFile( CString(strComName.c_str()) ,
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
		if(m_biShouldDisConn)
		{
			return 0;
		}

		ckDataBuf.redim( on_get_defaultrecv_buf_len() );

		DWORD dwBytes;

		ReadFile(m_hComport, ckDataBuf.buf(), ckDataBuf.len(), &dwBytes, 0);

		if(dwBytes == ckDataBuf.len()) return (int)ckDataBuf.len();

		return 0;
	}


	virtual int on_sys_send( const SCake & ckDataBuf ) 
	{
		if(m_biShouldDisConn)
		{
			return 0;
		}

		DWORD ret;

		WriteFile( m_hComport, ckDataBuf.buf_const(), 1 ,&ret, NULL ); 

		
		if( ckDataBuf.len() % 13 == 3 || SStrf::rand1() > 0.56 )
			WThrd::tr_sleep( 0, 0.001 );

		return (int)ret;
	}


}; 



X011_NAMESPACE_END

#endif




#endif

