
sdcopyman

copy sd card 

sudo dd if=/dev/mmcblk0 of=/dev/sda bs=15123123

raspberry pi3，SD拷贝器，读卡器直接插入即可开始把本机SD拷到USB读卡器，最小16G，事后还可能需要调整大小
if output is 32G, use 
sudo raspi-config afterward.


ifconfig wlan0 |grep "inet addr"| cut -f 2 -d ":"|cut -f 1 -d " ">1.txt




