#include <Windows.h>
#include "res.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>
bool isGameOn = false;  //czy gra została zaczęta
bool isFirstPlayerTurn = true;  //czyj ruch
bool isDraw = false;  //czy remis
int lRuch;  //liczba wykonanych ruchów
int pole;   //oznaczenie pustego pola na planszy
int lRuchPC = 0;    //liczba wykonanych ruchów w grze z komputerem

int tab[9] = { 234, 45, 124, 547, 67, 34, 678, 768, 435 };
//
//Funkcja określająca warunki wygrania rozgrywki 1 na 1
//
bool CheckWinningCondition(HWND hwndDlg, HWND lParam, int znak)
{
  lRuchPC++;
  HWND hwndButton1 = GetDlgItem(hwndDlg, IDC_BUTTON1);
  HWND hwndButton2 = GetDlgItem(hwndDlg, IDC_BUTTON2);
  HWND hwndButton3 = GetDlgItem(hwndDlg, IDC_BUTTON3);
  HWND hwndButton4 = GetDlgItem(hwndDlg, IDC_BUTTON4);
  HWND hwndButton5 = GetDlgItem(hwndDlg, IDC_BUTTON5);
  HWND hwndButton6 = GetDlgItem(hwndDlg, IDC_BUTTON6);
  HWND hwndButton7 = GetDlgItem(hwndDlg, IDC_BUTTON7);
  HWND hwndButton8 = GetDlgItem(hwndDlg, IDC_BUTTON8);
  HWND hwndButton9 = GetDlgItem(hwndDlg, IDC_BUTTON9);
  if (znak == 0) {
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
  else if (znak == 1) {
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
    return true;
  else
  {
    lRuch++;
    if (lRuch == 9) isDraw = true;
    return false;
  }
  //return false;
}
//
//sprawdzenie wygranej w grze z komputerem
//
bool CheckWinningConditionWithPC()
{
  lRuchPC++;
  if (tab[0] == tab[1] && tab[1] == tab[2] && tab[2] == 1 || tab[3] == tab[4] && tab[4] == tab[5] && tab[5] == 1 ||
    tab[6] == tab[7] && tab[7] == tab[8] && tab[8] == 1 || tab[0] == tab[3] && tab[3] == tab[6] && tab[6] == 1 ||
    tab[1] == tab[4] && tab[4] == tab[7] && tab[7] == 1 || tab[2] == tab[5] && tab[5] == tab[8] && tab[8] == 1 ||
    tab[0] == tab[4] && tab[4] == tab[8] && tab[8] == 1 || tab[2] == tab[4] && tab[4] == tab[6] && tab[6] == 1)
    return true;
  else
  {
    lRuch++;
    if (lRuch == 9) isDraw = true;
    return false;
  }
}
//#include <Windows.h>
#include "res.h"
#include <ctime>
#include <cstdlib>
#include <cstdio>
bool isGameOn = false;  //czy gra została zaczęta
bool isFirstPlayerTurn = true;  //czyj ruch
bool isDraw = false;  //czy remis
int lRuch;  //liczba wykonanych ruchów
int pole;   //oznaczenie pustego pola na planszy
int lRuchPC = 0;    //liczba wykonanych ruchów w grze z komputerem

int tab[9] = { 234, 45, 124, 547, 67, 34, 678, 768, 435 };
//
//Funkcja określająca warunki wygrania rozgrywki 1 na 1
//
bool CheckWinningCondition(HWND hwndDlg, HWND lParam, int znak)
{
  lRuchPC++;
  HWND hwndButton1 = GetDlgItem(hwndDlg, IDC_BUTTON1);
  HWND hwndButton2 = GetDlgItem(hwndDlg, IDC_BUTTON2);
  HWND hwndButton3 = GetDlgItem(hwndDlg, IDC_BUTTON3);
  HWND hwndButton4 = GetDlgItem(hwndDlg, IDC_BUTTON4);
  HWND hwndButton5 = GetDlgItem(hwndDlg, IDC_BUTTON5);
  HWND hwndButton6 = GetDlgItem(hwndDlg, IDC_BUTTON6);
  HWND hwndButton7 = GetDlgItem(hwndDlg, IDC_BUTTON7);
  HWND hwndButton8 = GetDlgItem(hwndDlg, IDC_BUTTON8);
  HWND hwndButton9 = GetDlgItem(hwndDlg, IDC_BUTTON9);
  if (znak == 0) {
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
  else if (znak == 1) {
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
    return true;
  else
  {
    lRuch++;
    if (lRuch == 9) isDraw = true;
    return false;
  }
  //return false;
}
//
//sprawdzenie wygranej w grze z komputerem
//
bool CheckWinningConditionWithPC()
{
  lRuchPC++;
  if (tab[0] == tab[1] && tab[1] == tab[2] && tab[2] == 1 || tab[3] == tab[4] && tab[4] == tab[5] && tab[5] == 1 ||
    tab[6] == tab[7] && tab[7] == tab[8] && tab[8] == 1 || tab[0] == tab[3] && tab[3] == tab[6] && tab[6] == 1 ||
    tab[1] == tab[4] && tab[4] == tab[7] && tab[7] == 1 || tab[2] == tab[5] && tab[5] == tab[8] && tab[8] == 1 ||
    tab[0] == tab[4] && tab[4] == tab[8] && tab[8] == 1 || tab[2] == tab[4] && tab[4] == tab[6] && tab[6] == 1)
    return true;
  else
  {
    lRuch++;
    if (lRuch == 9) isDraw = true;
    return false;
  }
}
//
//funkcja do ruchu komputera
//
void MovePC(HWND hwndDlg)
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

  for (int i = 0; i < 3; i++)
  {
    //sprawdzenie w poziomie
    if (tab[i * 3] == 0 && tab[i * 3 + 1] == 0 && tab[i * 3 + 2] != 0 && tab[i * 3 + 2] != 1 ||
      tab[i * 3] == 1 && tab[i * 3 + 1] == 1 && tab[i * 3 + 2] != 0 && tab[i * 3 + 2] != 1)   //0 i 3 takie samo
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton3) == 0)  //jeśli pole 2 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton3, szText);
          tab[2] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton6) == 0)  //jeśli pole 5 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton6, szText);
          tab[5] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton9) == 0)  //jeśli pole 8 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton9, szText);
          tab[8] = 1;
        }
      }
      return;
    }

    if (tab[i * 3] == 0 && tab[i * 3 + 2] == 0 && tab[i * 3 + 1] != 0 && tab[i * 3 + 1] != 1 ||
      tab[i * 3] == 1 && tab[i * 3 + 2] == 1 && tab[i * 3 + 1] != 0 && tab[i * 3 + 1] != 1)  //0 i 6 takie samo
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton2) == 0)  //jeśli pole 1 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton2, szText);
          tab[1] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton5) == 0)  //jeśli pole 4 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton5, szText);
          tab[4] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton8) == 0)  //jeśli pole 7 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton8, szText);
          tab[7] = 1;
        }
      }
      return;
    }

    if (tab[i * 3 + 1] == 0 && tab[i * 3 + 2] == 0 && tab[i * 3] != 0 && tab[i * 3] != 1 ||
      tab[i * 3 + 1] == 1 && tab[i * 3 + 2] == 1 && tab[i * 3] != 0 && tab[i * 3] != 1)  //3 i 6 takie samo
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton1) == 0)  //jeśli pole 0 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton1, szText);
          tab[0] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton4) == 0)  //jeśli pole 3 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton4, szText);
          tab[3] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton7) == 0)  //jeśli pole 6 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton7, szText);
          tab[6] = 1;
        }
      }
      return;
    }

    //sprawdzenie w pionie
    if (tab[i] == 0 && tab[i + 3] == 0 && tab[i + 6] != 0 && tab[i + 6] != 1 ||
      tab[i] == 1 && tab[i + 3] == 1 && tab[i + 6] != 0 && tab[i + 6] != 1)  //jeśli pole 0 i 3 takie same
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton7) == 0)  //jeśli pole 6 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton7, szText);
          tab[6] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton8) == 0)  //jeśli pole 7 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton8, szText);
          tab[7] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton9) == 0)  //jeśli pole 8 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton9, szText);
          tab[8] = 1;
        }
      }
      return;
    }

    if (tab[i] == 0 && tab[i + 6] == 0 && tab[i + 3] != 0 && tab[i + 3] != 1 ||
      tab[i] == 1 && tab[i + 6] == 1 && tab[i + 3] != 0 && tab[i + 3] != 1)  //jeśli pole 0 i 6 takie same
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton4) == 0)  //jeśli pole 3 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton4, szText);
          tab[3] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton5) == 0)  //jeśli pole 4 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton5, szText);
          tab[4] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton6) == 0)  //jeśli pole 5 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton6, szText);
          tab[5] = 1;
        }
      }
      return;
    }

    if (tab[i + 3] == 0 && tab[i + 6] == 0 && tab[i] != 0 && tab[i] != 1 ||
      tab[i + 3] == 1 && tab[i + 6] == 1 && tab[i] != 0 && tab[i] != 1)  //jeśli pole 3 i 6 takie same
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton1) == 0)  //jeśli pole 0 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton1, szText);
          tab[0] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton2) == 0)  //jeśli pole 1 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton2, szText);
          tab[1] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton3) == 0)  //jeśli pole 2 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton3, szText);
          tab[2] = 1;
        }
      }
      return;
    }
  }

  //główna przekątna
  if (tab[0] == 0 && tab[4] == 0 && tab[8] != 0 && tab[8] != 1 ||
    tab[0] == 1 && tab[4] == 1 && tab[8] != 0 && tab[8] != 1)    //jeśli pola 0 i 4 takie same
  {
    if (GetWindowTextLength(hwndButton9) == 0)  //jeśli pole 8 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton9, szText);
      tab[8] = 1;
    }
    return;
  }

  if (tab[0] == 0 && tab[8] == 0 && tab[4] != 0 & tab[4] != 1 ||
    tab[0] == 1 && tab[8] == 1 && tab[4] != 0 & tab[4] != 1)   //jeśli pola 0 i 8 takie same
  {
    if (GetWindowTextLength(hwndButton5) == 0)  //jeśli pole 4 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton5, szText);
      tab[4] = 1;
    }
    return;
  }

  if (tab[4] == 0 && tab[8] == 0 && tab[0] != 0 && tab[0] != 1 ||
    tab[4] == 1 && tab[8] == 1 && tab[0] != 0 && tab[0] != 1)   //jeśli pola 4 i 8 takie same
  {
    if (GetWindowTextLength(hwndButton1) == 0)  //jeśli pole 0 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton1, szText);
      tab[0] = 1;
    }
    return;
  }
  //druga przekątna
  if (tab[2] == 0 && tab[4] == 0 && tab[6] != 0 && tab[6] != 1 ||
    tab[2] == 1 && tab[4] == 1 && tab[6] != 0 && tab[6] != 1)    //jeśli pola 2 i 4 takie same
  {
    if (GetWindowTextLength(hwndButton7) == 0)  //jeśli pole 6 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton7, szText);
      tab[6] = 1;
    }return;
  }

  if (tab[2] == 0 && tab[6] == 0 && tab[4] != 0 && tab[4] != 1 ||
    tab[2] == 1 && tab[6] == 1 && tab[4] != 0 && tab[4] != 1)    //jeśli pola 2 i 6 takie same
  {
    if (GetWindowTextLength(hwndButton5) == 0)  //jeśli pole 4 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton5, szText);
      tab[4] = 1;
    }return;
  }

  if (tab[4] == 0 && tab[6] == 0 && tab[2] != 0 && tab[2] != 1 ||
    tab[4] == 1 && tab[6] == 1 && tab[2] != 0 && tab[2] != 1)    //jeśli pola 4 i 6 takie same
  {
    if (GetWindowTextLength(hwndButton3) == 0)  //jeśli pole 2 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton3, szText);
      tab[2] = 1;
    }return;
  }

  bool isempty = true;   //czy plansza jest pusta
  while (isempty && lRuchPC != 9)
  {
    pole = (rand() % 9);

    switch (pole)
    {
    case 0:
      if (GetWindowTextLength(hwndButton1) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton1, szText);
        isempty = false;
      }
      break;
    case 1:
      if (GetWindowTextLength(hwndButton2) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton2, szText);
        isempty = false;
      }
      break;
    case 2:
      if (GetWindowTextLength(hwndButton3) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton3, szText);
        isempty = false;
      }
      break;
    case 3:
      if (GetWindowTextLength(hwndButton4) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton4, szText);
        isempty = false;
      }
      break;
    case 4:
      if (GetWindowTextLength(hwndButton5) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton5, szText);
        isempty = false;
      }
      break;
    case 5:
      if (GetWindowTextLength(hwndButton6) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton6, szText);
        isempty = false;
      }
      break;
    case 6:
      if (GetWindowTextLength(hwndButton7) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton7, szText);
        isempty = false;
      }
      break;
    case 7:
      if (GetWindowTextLength(hwndButton8) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton8, szText);
        isempty = false;
      }
      break;
    case 8:
      if (GetWindowTextLength(hwndButton9) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton9, szText);
        isempty = false;
      }
      break;
    }
  }
}
//Funkcja czyszcząca planszę po zakończeniu rozgrywki
void Clean_field(HWND hwndDlg) {
  for (int i = 0; i < 9; i++) {
    HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i);
    CHAR szText[500];
    wsprintf(szText, "");
    SetWindowText(hwndButton, szText);
    for (int i = 0; i < 9; i++) { tab[i] = 100 + i; }
  }
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if (IsDlgButtonChecked(hwndDlg, IDC_RADIO_1na1))
  {
    //Gra 1 na 1
    switch (uMsg)
    {
    case WM_COMMAND:
      switch (HIWORD(wParam))
      {
      case BN_CLICKED:    //zdarzenie klikniêcia
        switch (LOWORD(wParam))
        {
          /*case IDC_BUTTON1:  case IDC_BUTTON2:  case IDC_BUTTON3:  case IDC_BUTTON4:
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
          }
          }
          SetWindowText(hwndButton, szText);
          isFirstPlayerTurn = !isFirstPlayerTurn;
          }
          return TRUE;
          }
          return TRUE;*/
        case IDC_BUTTON_START:
          if (isGameOn == false)
          {
            isGameOn = true;
            isDraw = false;
            lRuch = 0;
            HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
            CHAR szText[500];
            wsprintf(szText, "gra się toczy");
            SetWindowText(hwndStatic, szText);
            Clean_field(hwndDlg);
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
          }
          return TRUE;
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

  else if (IsDlgButtonChecked(hwndDlg, IDC_RADIO_PC))
  {
    //gra z komputerem
    switch (uMsg)
    {
    case WM_COMMAND:
      switch (HIWORD(wParam))
      {
      case BN_CLICKED:    //zdarzenie klikniêcia
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:  case IDC_BUTTON2:  case IDC_BUTTON3:  case IDC_BUTTON4:
        case IDC_BUTTON5:  case IDC_BUTTON6:  case IDC_BUTTON7:  case IDC_BUTTON8:
        case IDC_BUTTON9:
          if (isGameOn == true)
          {
            HWND hwndButton = (HWND)lParam;
            CHAR szText[500];
            if (GetWindowTextLength(hwndButton) == 0)
            {
              //Zaczyna gracz X
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
              wsprintf(szText, "X");
              SetWindowText(hwndButton, szText);
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
              }
              MovePC(hwndDlg);
              //czy nastapiła wygrana gracza O
              if (CheckWinningConditionWithPC())
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                CHAR szText[500];
                wsprintf(szText, "Wygrana O, aby zacząć od nowa, wciśnij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
              else if (isDraw)
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                CHAR szText[500];
                wsprintf(szText, "Remis, aby zacząć od nowa, wciśnij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
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
            lRuchPC = 0;
            HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
            CHAR szText[500];
            wsprintf(szText, "gra się toczy");
            SetWindowText(hwndStatic, szText);
            Clean_field(hwndDlg);
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
          }
          return TRUE;
        }
      }
      return FALSE;
    case WM_CLOSE:    //komunikat zamknięcia okienka
      DestroyWindow(hwndDlg);
      PostQuitMessage(0);
      return TRUE;
    }
    return FALSE;
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  srand(time(NULL));
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}
//funkcja do ruchu komputera
//
void MovePC(HWND hwndDlg)
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

  for (int i = 0; i < 3; i++)
  {
    //sprawdzenie w poziomie
    if (tab[i * 3] == 0 && tab[i * 3 + 1] == 0 && tab[i * 3 + 2] != 0 && tab[i * 3 + 2] != 1 ||
      tab[i * 3] == 1 && tab[i * 3 + 1] == 1 && tab[i * 3 + 2] != 0 && tab[i * 3 + 2] != 1)   //0 i 3 takie samo
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton3) == 0)  //jeśli pole 2 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton3, szText);
          tab[2] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton6) == 0)  //jeśli pole 5 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton6, szText);
          tab[5] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton9) == 0)  //jeśli pole 8 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton9, szText);
          tab[8] = 1;
        }
      }
      return;
    }

    if (tab[i * 3] == 0 && tab[i * 3 + 2] == 0 && tab[i * 3 + 1] != 0 && tab[i * 3 + 1] != 1 ||
      tab[i * 3] == 1 && tab[i * 3 + 2] == 1 && tab[i * 3 + 1] != 0 && tab[i * 3 + 1] != 1)  //0 i 6 takie samo
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton2) == 0)  //jeśli pole 1 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton2, szText);
          tab[1] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton5) == 0)  //jeśli pole 4 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton5, szText);
          tab[4] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton8) == 0)  //jeśli pole 7 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton8, szText);
          tab[7] = 1;
        }
      }
      return;
    }

    if (tab[i * 3 + 1] == 0 && tab[i * 3 + 2] == 0 && tab[i * 3] != 0 && tab[i * 3] != 1 ||
      tab[i * 3 + 1] == 1 && tab[i * 3 + 2] == 1 && tab[i * 3] != 0 && tab[i * 3] != 1)  //3 i 6 takie samo
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton1) == 0)  //jeśli pole 0 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton1, szText);
          tab[0] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton5) == 0)  //jeśli pole 3 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton4, szText);
          tab[3] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton7) == 0)  //jeśli pole 6 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton8, szText);
          tab[6] = 1;
        }
      }
      return;
    }

    //sprawdzenie w pionie
    if (tab[i] == 0 && tab[i + 3] == 0 && tab[i + 6] != 0 && tab[i + 6] != 1 ||
      tab[i] == 1 && tab[i + 3] == 1 && tab[i + 6] != 0 && tab[i + 6] != 1)  //jeśli pole 0 i 3 takie same
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton7) == 0)  //jeśli pole 6 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton7, szText);
          tab[6] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton8) == 0)  //jeśli pole 7 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton8, szText);
          tab[7] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton9) == 0)  //jeśli pole 8 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton9, szText);
          tab[8] = 1;
        }
      }
      return;
    }

    if (tab[i] == 0 && tab[i + 6] == 0 && tab[i + 3] != 0 && tab[i + 3] != 1 ||
      tab[i] == 1 && tab[i + 6] == 1 && tab[i + 3] != 0 && tab[i + 3] != 1)  //jeśli pole 0 i 6 takie same
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton4) == 0)  //jeśli pole 3 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton4, szText);
          tab[3] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton5) == 0)  //jeśli pole 4 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton5, szText);
          tab[4] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton6) == 0)  //jeśli pole 5 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton6, szText);
          tab[5] = 1;
        }
      }
      return;
    }

    if (tab[i + 3] == 0 && tab[i + 6] == 0 && tab[i] != 0 && tab[i] != 1 ||
      tab[i + 3] == 1 && tab[i + 6] == 1 && tab[i] != 0 && tab[i] != 1)  //jeśli pole 3 i 6 takie same
    {
      if (i == 0)
      {
        if (GetWindowTextLength(hwndButton1) == 0)  //jeśli pole 0 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton1, szText);
          tab[0] = 1;
        }
      }
      if (i == 1)
      {
        if (GetWindowTextLength(hwndButton2) == 0)  //jeśli pole 1 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton2, szText);
          tab[1] = 1;
        }
      }
      if (i == 2)
      {
        if (GetWindowTextLength(hwndButton3) == 0)  //jeśli pole 2 puste
        {
          CHAR szText[500];
          wsprintf(szText, "O");
          SetWindowText(hwndButton3, szText);
          tab[2] = 1;
        }
      }
      return;
    }
  }

  //główna przekątna
  if (tab[0] == 0 && tab[4] == 0 && tab[8] != 0 && tab[8] != 1 ||
    tab[0] == 1 && tab[4] == 1 && tab[8] != 0 && tab[8] != 1)    //jeśli pola 0 i 4 takie same
  {
    if (GetWindowTextLength(hwndButton9) == 0)  //jeśli pole 8 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton9, szText);
      tab[8] = 1;
    }
    return;
  }

  if (tab[0] == 0 && tab[8] == 0 && tab[4] != 0 & tab[4] != 1 ||
    tab[0] == 1 && tab[8] == 1 && tab[4] != 0 & tab[4] != 1)   //jeśli pola 0 i 8 takie same
  {
    if (GetWindowTextLength(hwndButton5) == 0)  //jeśli pole 4 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton5, szText);
      tab[4] = 1;
    }
    return;
  }

  if (tab[4] == 0 && tab[8] == 0 && tab[0] != 0 && tab[0] != 1 ||
    tab[4] == 1 && tab[8] == 1 && tab[0] != 0 && tab[0] != 1)   //jeśli pola 4 i 8 takie same
  {
    if (GetWindowTextLength(hwndButton1) == 0)  //jeśli pole 0 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton1, szText);
      tab[0] = 1;
    }
    return;
  }
  //druga przekątna
  if (tab[2] == 0 && tab[4] == 0 && tab[6] != 0 && tab[6] != 1 ||
    tab[2] == 1 && tab[4] == 1 && tab[6] != 0 && tab[6] != 1)    //jeśli pola 2 i 4 takie same
  {
    if (GetWindowTextLength(hwndButton7) == 0)  //jeśli pole 6 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton7, szText);
      tab[6] = 1;
    }return;
  }

  if (tab[2] == 0 && tab[6] == 0 && tab[4] != 0 && tab[4] != 1 ||
    tab[2] == 1 && tab[6] == 1 && tab[4] != 0 && tab[4] != 1)    //jeśli pola 2 i 6 takie same
  {
    if (GetWindowTextLength(hwndButton5) == 0)  //jeśli pole 4 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton5, szText);
      tab[4] = 1;
    }return;
  }

  if (tab[4] == 0 && tab[6] == 0 && tab[2] != 0 && tab[2] != 1 ||
    tab[4] == 1 && tab[6] == 1 && tab[2] != 0 && tab[2] != 1)    //jeśli pola 4 i 6 takie same
  {
    if (GetWindowTextLength(hwndButton3) == 0)  //jeśli pole 2 puste
    {
      CHAR szText[500];
      wsprintf(szText, "O");
      SetWindowText(hwndButton3, szText);
      tab[2] = 1;
    }return;
  }

  bool isempty = true;   //czy plansza jest pusta
  while (isempty && lRuchPC != 9)
  {
    pole = (rand() % 9);

    switch (pole)
    {
    case 0:
      if (GetWindowTextLength(hwndButton1) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton1, szText);
        isempty = false;
      }
      break;
    case 1:
      if (GetWindowTextLength(hwndButton2) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton2, szText);
        isempty = false;
      }
      break;
    case 2:
      if (GetWindowTextLength(hwndButton3) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton3, szText);
        isempty = false;
      }
      break;
    case 3:
      if (GetWindowTextLength(hwndButton4) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton4, szText);
        isempty = false;
      }
      break;
    case 4:
      if (GetWindowTextLength(hwndButton5) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton5, szText);
        isempty = false;
      }
      break;
    case 5:
      if (GetWindowTextLength(hwndButton6) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton6, szText);
        isempty = false;
      }
      break;
    case 6:
      if (GetWindowTextLength(hwndButton7) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton7, szText);
        isempty = false;
      }
      break;
    case 7:
      if (GetWindowTextLength(hwndButton8) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton8, szText);
        isempty = false;
      }
      break;
    case 8:
      if (GetWindowTextLength(hwndButton9) == 0)
      {
        CHAR szText[500];
        wsprintf(szText, "O");
        tab[pole] = 1;
        SetWindowText(hwndButton9, szText);
        isempty = false;
      }
      break;
    }
  }
}
//Funkcja czyszcząca planszę po zakończeniu rozgrywki
void Clean_field(HWND hwndDlg) {
  for (int i = 0; i < 9; i++) {
    HWND hwndButton = GetDlgItem(hwndDlg, IDC_BUTTON1 + i);
    CHAR szText[500];
    wsprintf(szText, "");
    SetWindowText(hwndButton, szText);
    for (int i = 0; i < 9; i++) { tab[i] = 100 + i; }
  }
}

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  if (IsDlgButtonChecked(hwndDlg, IDC_RADIO_1na1))
  {
    //Gra 1 na 1
    switch (uMsg)
    {
    case WM_COMMAND:
      switch (HIWORD(wParam))
      {
      case BN_CLICKED:    //zdarzenie klikniêcia
        switch (LOWORD(wParam))
        {
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
            CHAR szText[500];
            wsprintf(szText, "gra się toczy");
            SetWindowText(hwndStatic, szText);
            Clean_field(hwndDlg);
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
          }
          return TRUE;
        }
      }
      return FALSE;
    case WM_CLOSE:    //komunikat zamknięcia okienka
      DestroyWindow(hwndDlg);
      PostQuitMessage(0);
      return TRUE;
    }
    return FALSE;
  }

  else if (IsDlgButtonChecked(hwndDlg, IDC_RADIO_PC))
  {
    //gra z komputerem
    switch (uMsg)
    {
    case WM_COMMAND:
      switch (HIWORD(wParam))
      {
      case BN_CLICKED:    //zdarzenie klikniêcia
        switch (LOWORD(wParam))
        {
        case IDC_BUTTON1:  case IDC_BUTTON2:  case IDC_BUTTON3:  case IDC_BUTTON4:
        case IDC_BUTTON5:  case IDC_BUTTON6:  case IDC_BUTTON7:  case IDC_BUTTON8:
        case IDC_BUTTON9:
          if (isGameOn == true)
          {
            HWND hwndButton = (HWND)lParam;
            CHAR szText[500];
            if (GetWindowTextLength(hwndButton) == 0)
            {
              //Zaczyna gracz X
              CheckRadioButton(hwndDlg, IDC_RADIO1, IDC_RADIO2, IDC_RADIO1);
              wsprintf(szText, "X");
              SetWindowText(hwndButton, szText);
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
              }
              MovePC(hwndDlg);
              //czy nastapiła wygrana gracza O
              if (CheckWinningConditionWithPC())
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                CHAR szText[500];
                wsprintf(szText, "Wygrana O, aby zacząć od nowa, wciśnij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
              else if (isDraw)
              {
                HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
                CHAR szText[500];
                wsprintf(szText, "Remis, aby zacząć od nowa, wciśnij start");
                SetWindowText(hwndStatic, szText);
                isGameOn = false;
                HWND hwndButton_start = GetDlgItem(hwndDlg, IDC_BUTTON_START);
                wsprintf(szText, "Start");
                SetWindowText(hwndButton_start, szText);
              }
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
            lRuchPC = 0;
            HWND hwndStatic = GetDlgItem(hwndDlg, IDC_STATIC1);
            CHAR szText[500];
            wsprintf(szText, "gra się toczy");
            SetWindowText(hwndStatic, szText);
            Clean_field(hwndDlg);
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
          }
          return TRUE;
        }
      }
      return FALSE;
    case WM_CLOSE:    //komunikat zamknięcia okienka
      DestroyWindow(hwndDlg);
      PostQuitMessage(0);
      return TRUE;
    }
    return FALSE;
  }
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  srand(time(NULL));
  MSG msg = {};
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return 0;
}