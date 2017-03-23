#include <Windows.h>
#include "res.h"
#include <cstdlib>
#include <ctime>

int numer;
int licznik;
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
  switch (uMsg) 
  {
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:    //zdarzenie klikniÍcia
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:   //konkretny button
          HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);
          HWND hwndStatic1 = GetDlgItem(hwndDlg, IDC_STATIC1);
          HWND hwndStatic2 = GetDlgItem(hwndDlg, IDC_STATIC2);
          int iTextLength = GetWindowTextLength(hwndEditBox);
          CHAR szText[500];
          CHAR lText[100];
          GetWindowText(hwndEditBox, szText, iTextLength + 1);
          SetWindowText(hwndStatic1, szText);
          int rzut = atoi(szText);
          if ((rzut >= 1) && (rzut <= 40)) 
          {
            if (rzut < numer) 
            {
              licznik++;
              wsprintf(lText, "Liczba prÛb: %d", licznik);
              SetWindowText(hwndStatic2, lText);
              SetWindowText(hwndStatic1, "Za ma≥o");
            }
            else if (rzut > numer) 
            {
              licznik++;
              wsprintf(lText, "Liczba prÛb: %d", licznik);
              SetWindowText(hwndStatic2, lText);
              SetWindowText(hwndStatic1, "Za duøo");
            }
            else
            {
            licznik++;
            wsprintf(lText, "Liczba prÛb: %d", licznik);
            SetWindowText(hwndStatic2, lText);
            SetWindowText(hwndStatic1, "Brawo!");
            wsprintf(szText, "Wygra≥eú!");
            MessageBox(hwndDlg, szText, TEXT("Koniec"), MB_OK);
            DestroyWindow(hwndDlg);
            PostQuitMessage(0);
            }
          }
          else
          {
            licznik++;
            wsprintf(lText, "Liczba prÛb: %d", licznik);
            SetWindowText(hwndStatic2, lText);
            SetWindowText(hwndStatic1, "Tylko od 1 do 40");
            wsprintf(szText, "Tak byÊ nie moøe");
            MessageBox(hwndDlg, szText, "èle", MB_OK);
          }
          return TRUE;
        }
    }
    return FALSE;
  case WM_CLOSE:    //komunikat zamkniÍcia okienka
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
    return TRUE;
  }
  return FALSE;
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) 
{
  srand(time(NULL));
  int liczba = (std::rand() % 40) + 1;
  numer = liczba;
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow); 
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0)) 
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}