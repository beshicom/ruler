


all :	ruler.exe

ruler.exe : ruler.obj ruler.res
	cl ruler.obj ruler.res user32.lib kernel32.lib gdi32.lib /link /out:ruler.exe

ruler.obj : ruler.cpp
	cl /c /std:c++17 ruler.cpp

ruler.res : ruler.rc ruler.ico
	rc ruler.rc



