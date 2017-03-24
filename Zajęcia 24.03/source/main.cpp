#include <Windows.h>
#include "res.h"

bool isGameOn = false;
bool isFirstPlayerTurn = true;

/*bool CheckWinningCondition() 
{

}*/
INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{ 
  switch (uMsg)
  {
  case WM_COMMAND:
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:    //zdarzenie klikniêcia
      switch (LOWORD(wParam))
      {
      case IDC_BUTTON1:   //konkretny button
      case IDC_BUTTON2:
      case IDC_BUTTON3:
      case IDC_BUTTON4:
      case IDC_BUTTON5:
      case IDC_BUTTON6:
      case IDC_BUTTON7:
      case IDC_BUTTON8:
      case IDC_BUTTON9:
        if (isGameOn == true) 
        {
        //isFirstPlayerTurn
          HWND hwndButton = (HWND)lParam;
          if (GetWindowTextLength(hwndButton) == 0) 
          {
            CHAR szText[500];
 
            if (isFirstPlayerTurn == true) 
            {
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
              wsprintf(szText, "X");
            }
            else
            {
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
              wsprintf(szText, "O");
            }
            SetWindowText(hwndButton, szText);
            isFirstPlayerTurn = !isFirstPlayerTurn;
          }
          return TRUE;
        }
        return TRUE;

      case IDC_BUTTON10:
        if (isGameOn == false)
        {
          isGameOn = true;
          HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
          CHAR szText[500];
          wsprintf(szText, "Start");
          SetWindowText(hwndStatic, szText);
          for (int i = 0; i < 9; i++)
          {
            HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i);
            CHAR szText[500];
            wsprintf(szText, "");
            SetWindowText(hwndButton, szText);
          }
          HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
          //char szText[500];
          wsprintf(szText, "Stop");
          SetWindowText(hwndButton10, szText);
        }
        else 
        {
          isGameOn = false;
          HWND hwndButton10 = GetDlgItem(hwndDlg, IDC_BUTTON10);
          CHAR szText[500];
          wsprintf(szText, "Start");
          SetWindowText(hwndButton10, szText);
        }
       
      }
      return TRUE;
    }
    return FALSE;
  case WM_CLOSE:    //komunikat zamkniêcia okienka
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
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