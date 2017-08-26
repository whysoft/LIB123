
内置设定 orange pi zero所需各文件
用ppp通过ttyS2互连，组网

对命令行处理实现“领用”结构

事先需下载包:
apt-get install iptables
apt-get install ppp
apt-get install g++

ppp server端，两次连不上qq.com 即reboot


stty -F /dev/ttyS0 -a
stty -F /dev/ttyS2 -a


echo -n -e "\xc1\xc1\xc1">/dev/ttyS2
echo -n -e "\xc3\xc3\xc3">/dev/ttyS2
 
echo -n -e "\xc1\xc1\xc1\xc3\xc3\xc3">/dev/ttyS2 ###不好用。
 
./multibox -c hex -f /dev/ttyS2&
echo -n -e "\xc0\x45\x67\x18\x00\xc0">/dev/ttyS2
echo -n -e "\xc0\x45\x67\x38\x00\xc0">/dev/ttyS2


sudo vim /etc/ppp/options.ttyS2
/usr/sbin/pppd /dev/ttyS2 nodetach&


-c server
-c cli







 