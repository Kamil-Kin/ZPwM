#include <Windows.h>
#include "res.h"

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
  switch (uMsg) 
  {
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case EN_CHANGE:
      switch (LOWORD(wParam))
      {
      case IDC_EDIT1:
        //MessageBox(hwndDlg, TEXT("TEST"), TEXT("Klikniêcie"), MB_OK);
        HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);
        HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1);
        int iTextLength = GetWindowTextLength(hwndEditBox);
        CHAR szText[500];
        GetWindowText(hwndEditBox, szText, iTextLength + 1);
        SetWindowText(hwndButton, szText);
        return TRUE;
      }
      return FALSE;
    case BN_CLICKED:
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:
          MessageBox(hwndDlg, TEXT("TEST"), TEXT("Klikniêcie"), MB_OK);
          HWND hwndEditBox = GetDlgItem(hwndDlg, IDC_EDIT1);
          int iTextLength = GetWindowTextLength(hwndEditBox);
          CHAR szText[500];
          GetWindowText(hwndEditBox, szText, iTextLength + 1);
          SetWindowText((HWND)lParam, szText);
          return TRUE;
        }
    }
    return FALSE;
  case WM_CLOSE:
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
    return TRUE;
  case WM_LBUTTONDOWN:
    CHAR szText[200];
    wsprintf(szText, "Klikn¹³eœ myszk¹ x=%d, y = %d", LOWORD(lParam), HIWORD(lParam));
    MessageBox(hwndDlg, szText, TEXT("Klikniêcie"), MB_OK);
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) 
{

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


