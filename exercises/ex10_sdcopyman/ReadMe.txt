
sdcopyman

copy sd card 

sudo dd if=/dev/mmcblk0 of=/dev/sda bs=15123123

raspberry pi3��SD��������������ֱ�Ӳ��뼴�ɿ�ʼ�ѱ���SD����USB����������С16G���º󻹿�����Ҫ������С
if output is 32G, use 
sudo raspi-config afterward.


ifconfig wlan0 |grep "inet addr"| cut -f 2 -d ":"|cut -f 1 -d " ">1.txt




