
�����趨 orange pi zero������ļ�
��pppͨ��ttyS2����������

�������д���ʵ�֡����á��ṹ

���������ذ�:
apt-get install iptables
apt-get install ppp
apt-get install g++

ppp server�ˣ�����������qq.com ��reboot


stty -F /dev/ttyS0 -a
stty -F /dev/ttyS2 -a


echo -n -e "\xc1\xc1\xc1">/dev/ttyS2
echo -n -e "\xc3\xc3\xc3">/dev/ttyS2
 
echo -n -e "\xc1\xc1\xc1\xc3\xc3\xc3">/dev/ttyS2 ###�����á�
 
./multibox -c hex -f /dev/ttyS2&
echo -n -e "\xc0\x45\x67\x18\x00\xc0">/dev/ttyS2
echo -n -e "\xc0\x45\x67\x38\x00\xc0">/dev/ttyS2




