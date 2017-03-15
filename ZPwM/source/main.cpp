#include <Windows.h>
#include <stdio.h>

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) 
{
  int i = MessageBox(0, "Wybierz liczbê od 1 do 40", "Start", MB_OK);
  int max = 40;
  int min = 1;
  int mid = (max + min) / 2;

  char tab[100];

  while (max > min) 
  {
    sprintf_s(tab, "Czy Twoja liczba jest wiêksza od %d", mid);
    i = MessageBox(0, tab, "Zgadywanka", MB_YESNO);
    if (i == IDYES) 
    {
      min = mid + 1;
    }
    else 
    {
      max = mid;
    }
    mid = (max + min) / 2;
  }
  sprintf_s(tab, "Czy Twoja liczba to %d", min);
  MessageBox(0,tab,"Koniec", MB_OK);
  return 0;
}