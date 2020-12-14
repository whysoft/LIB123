
pushd "%~dp0" 
rem set path=%path%;"C:\Program Files\WinRAR"
rem set path="C:\Program Files (x86)\WinRAR\"

set toolname=1.zip

set foldername=.\

start /wait winrar a %toolname% %foldername%*.h %foldername%*.c %foldername%*.cpp %foldername%*.xpp %foldername%*.txt %foldername%*.sh %foldername%*.py %foldername%*.wav %foldername%*.db
ping -n 2 127.0.0.1 


\_mytools\multibox -c fup -n %toolname%  
erase %toolname%

:pause

