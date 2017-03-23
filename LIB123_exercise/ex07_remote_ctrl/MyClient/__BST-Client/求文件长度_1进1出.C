
2个参数
##PARA0#：文件全名，const char*类型 
##PARA1#：返回long，长度
如果文件不存在，返回长度为0。

###
if(##PARA0#)
{
	FILE *fp;
	fp = fopen( ##PARA0# , "rb" );
	if(fp==NULL) ##PARA1# = 0;
	else
	{
		fseek( fp,0,SEEK_END );
		##PARA1# =ftell(fp);
		fclose(fp);
	}
}
