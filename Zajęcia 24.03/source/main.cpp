#include <Windows.h>
#include "res.h"

bool isGameOn = false;  //czy gra została zaczęta
bool isFirstPlayerTurn = true;  //czyj ruch
bool isDraw = false;  //czy remis
int lRuch;  //liczba wykonanych ruchów
bool isWithPC = false;  //czy gra z komputerem

int tab[9] = { 234, 45, 124, 547, 67, 34, 678, 768, 435 };
//Funkcja określająca warunki wygrania rozgrywki
bool CheckWinningCondition(HWND hwndDlg, HWND lParam, int znak)
{
  HWND hwndButton1 = GetDlgItem(hwndDlg, IDC_BUTTON1);
  HWND hwndButton2 = GetDlgItem(hwndDlg, IDC_BUTTON2);
  HWND hwndButton3 = GetDlgItem(hwndDlg, IDC_BUTTON3);
  HWND hwndButton4 = GetDlgItem(hwndDlg, IDC_BUTTON4);
  HWND hwndButton5 = GetDlgItem(hwndDlg, IDC_BUTTON5);
  HWND hwndButton6 = GetDlgItem(hwndDlg, IDC_BUTTON6);
  HWND hwndButton7 = GetDlgItem(hwndDlg, IDC_BUTTON7);
  HWND hwndButton8 = GetDlgItem(hwndDlg, IDC_BUTTON8);
  HWND hwndButton9 = GetDlgItem(hwndDlg, IDC_BUTTON9);
  if (znak == 0) 
  {
    if (hwndButton1 == lParam) tab[0] = 0;
    if (hwndButton2 == lParam) tab[1] = 0;
    if (hwndButton3 == lParam) tab[2] = 0;
    if (hwndButton4 == lParam) tab[3] = 0;
    if (hwndButton5 == lParam) tab[4] = 0;
    if (hwndButton6 == lParam) tab[5] = 0;
    if (hwndButton7 == lParam) tab[6] = 0;
    if (hwndButton8 == lParam) tab[7] = 0;
    if (hwndButton9 == lParam) tab[8] = 0;
  }
  else if (znak == 1) 
  {
    if (hwndButton1 == lParam) tab[0] = 1;
    if (hwndButton2 == lParam) tab[1] = 1;
    if (hwndButton3 == lParam) tab[2] = 1;
    if (hwndButton4 == lParam) tab[3] = 1;
    if (hwndButton5 == lParam) tab[4] = 1;
    if (hwndButton6 == lParam) tab[5] = 1;
    if (hwndButton7 == lParam) tab[6] = 1;
    if (hwndButton8 == lParam) tab[7] = 1;
    if (hwndButton9 == lParam) tab[8] = 1;
  }

  if (tab[0] == tab[1] && tab[1] == tab[2] 
      || tab[3] == tab[4] && tab[4] == tab[5]
      || tab[6] == tab[7] && tab[7] == tab[8] 
      || tab[0] == tab[3] && tab[3] == tab[6] 
      || tab[1] == tab[4] && tab[4] == tab[7] 
      || tab[2] == tab[5] && tab[5] == tab[8] 
      || tab[0] == tab[4] && tab[4] == tab[8] 
      || tab[2] == tab[4] && tab[4] == tab[6])
      /*if (((tab[3 * i] == tab[3 * i + 1]) && (tab[3 * i + 1] == tab[3 * i + 2])) ||
        ((tab[i] == tab[i + 3]) && (tab[i + 3] == tab[i + 6])) ||
        ((tab[0] == tab[4] && tab[0] == tab[8])) || ((tab[2] == tab[4] && tab[2] == tab[6])))*/
      return true;
  else
    {
      lRuch++;
      if (lRuch == 9) isDraw = true;
      return false;
    }
  return false;
}
//Funkcja czyszcząca planszę po zakończeniu rozgrywki
/*void Clean_field(HWND hwndDlg) 
{
  for (int i = 0; i < 9; i++)
  {
    HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i);
    CHAR szText[500];
    wsprintf(szText, "");
    SetWindowText(hwndButton, szText);
  }
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
        //konkretny button
      case IDC_BUTTON1:  case IDC_BUTTON2:  case IDC_BUTTON3:  case IDC_BUTTON4:
      case IDC_BUTTON5:  case IDC_BUTTON6:  case IDC_BUTTON7:  case IDC_BUTTON8:

      case IDC_BUTTON9:
        if (isGameOn == true)
        {
          //isFirstPlayerTurn
          HWND hwndButton = (HWND)lParam;

          if (GetWindowTextLength(hwndButton) == 0)
          {
            CHAR szText[500];
            //Zaczyna gracz X
            if (isFirstPlayerTurn == true)
            {
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
              wsprintf(szText, "X");
              //czy nastąpiła wygrana gracza X
              if (CheckWinningCondition(hwndDlg, hwndButton, 0)) 
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                CHAR szText[500];
                wsprintf(szText, "Wygrana X,aby zacząć od nowa, wciśnij start");
                SetWindowText(hwndStatic, szText);

                isGameOn = false;

                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
                for (int i = 0; i < 9; i++) { tab[i] = 10 + i; }
              }
              else if (isDraw) 
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                CHAR szText[500];
                wsprintf(szText, "Remis,aby zacząć od nowa, wciśnij start");
                SetWindowText(hwndStatic, szText);

                isGameOn = false;

                for (int i = 0; i < 9; i++) { tab[i] = 10 + i; }
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
            }
            //Ruch gracza O
            else
            {
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO2);
              wsprintf(szText, "O");
              //czy nastapiła wygrana gracza O
              if (CheckWinningCondition(hwndDlg, hwndButton, 1))
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                CHAR szText[500];
                wsprintf(szText, "Wygrana O, aby zacząć od nowa, wciśnij start");
                SetWindowText(hwndStatic, szText);

                isGameOn = false;

                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
                for (int i = 0; i < 9; i++) { tab[i] = 10 + i; }
              }
              else if (isDraw) 
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                CHAR szText[500];
                wsprintf(szText, "Remis,aby zacząć od nowa, wciśnij start");
                SetWindowText(hwndStatic, szText);

                isGameOn = false;

                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
                for (int i = 0; i < 9; i++) { tab[i] = 10 + i; }
              }
            }
            SetWindowText(hwndButton, szText);
            isFirstPlayerTurn = !isFirstPlayerTurn;
          }
          return TRUE;
        }
        return TRUE;

      case IDC_BUTTON_START:
        if (isGameOn == false)
        {
          isGameOn = true;
          isDraw = false;
          lRuch = 0;
          HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
          //HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
          CHAR szText[500];
          wsprintf(szText, "gra się toczy");
          SetWindowText(hwndStatic, szText);
          for (int i = 0; i < 9; i++)
          {
            HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i);
            CHAR szText[500];
            wsprintf(szText, "");
            SetWindowText(hwndButton, szText);
          }
          HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
          wsprintf(szText, "Stop");
          SetWindowText(hwndButton_start, szText);
        }
        else
        {
          isGameOn = false;
          HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
          HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);          
          CHAR szText[500];
          wsprintf(szText, "gra wstrzymana");
          SetWindowText(hwndStatic, szText);   
          wsprintf(szText, "Start");
          SetWindowText(hwndButton_start, szText);
          for (int i = 0; i < 9; i++) { tab[i] = 10 + i;}
        }
      }
      return TRUE;
    }
    return FALSE;

  case WM_CLOSE:    //komunikat zamknięcia okienka
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