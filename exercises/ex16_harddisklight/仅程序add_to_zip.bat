
pushd "%~dp0" 
rem set path="C:\Program Files\WinRAR"
set path="C:\Program Files (x86)\WinRAR\"

set toolname=1.zip

set foldername=.\

start /wait winrar a %toolname% %foldername%*.h %foldername%*.c %foldername%*.cpp %foldername%*.xpp %foldername%*.txt %foldername%*.sh %foldername%*.py %foldername%*.gif %foldername%*.bmp

\_mytools\multibox -c fup -n %toolname%  
erase %toolname%

:pause

