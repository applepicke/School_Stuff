/*Finally, real windows programming*/
#include <windows.h>

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
     MessageBox(NULL, TEXT("Hello, Windows 7!"), TEXT("I, Title"), 0) ;

     return 0 ;
}
