
```
harddisklight

用vmstat
找出硬盘读写行为
然后用画图法显示出硬盘是否忙

这个程序分为服务端和客户端两部分

服务端运行于ubuntu，并形成web server
客户端读取硬盘读写次数，显示为有颜色的线段


server:

vmstat | harddisklight



client:

harddisklight -c client -width 1800 -addr 192.168.41.129:12000



