#include <Windows.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) 
{
  int iRetKey = MessageBox(0, "Podoba siê?", "app", MB_YESNO);
  if (iRetKey == IDYES) 
  {
    MessageBox(0, "To dobrze", "App", MB_OK);
  }
  else 
  {
    MessageBox(0, "To Ÿle", "App2", MB_OK|MB_ICONQUESTION);
  }

  MessageBox(0, "Hello World", "Okno", MB_OK);
  return 0;
}