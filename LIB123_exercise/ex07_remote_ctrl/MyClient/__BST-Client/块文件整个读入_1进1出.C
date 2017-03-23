
2个参数
##PARA0#：文件全名，const char*类型 
##PARA1#：返回BUFF，预先有内存

###
if(##PARA0#)
{
	FILE *fp;
	fp = fopen( ##PARA0# , "rb" );
	if(fp==NULL){}
	else
	{
		long flen;
		fseek( fp,0,SEEK_END );
		flen=ftell(fp);
		fseek( fp,0,SEEK_SET );
		fread( (##PARA1#), flen, 1, fp );
		fclose(fp);
	}
}
