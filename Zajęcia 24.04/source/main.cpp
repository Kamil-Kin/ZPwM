#include <Windows.h>
#include "res.h"
#include <gl/gl.h>
#include <gl/glu.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
HDC hDC = NULL;
HGLRC hRC = NULL;

bool isGameOn = false;  //czy gra zosta³a zaczêta
bool isFirstPlayerTurn = true;  //czyj ruch
bool isFieldOccupiedByFirstPlayer[3][3];
bool isFieldOccupiedBySecondPlayer[3][3];
bool isDraw = false;  //czy remis
int lRuch;  //liczba wykonanych ruchów
            //int tab[9] = { 234, 45, 124, 547, 67, 34, 678, 768, 435 };

INT_PTR CALLBACK DialogProc(HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
  switch (uMsg)
  {
  case WM_INITDIALOG:
  {
    //zmieniæ styl okienka
    SetWindowLong(hwndDlg, GWL_STYLE, CS_HREDRAW | CS_VREDRAW | CS_OWNDC | WS_OVERLAPPEDWINDOW);
    SetClassLong(hwndDlg, GWL_STYLE, CS_HREDRAW | CS_VREDRAW | CS_OWNDC);
    //STWORZYÆ MASZYNÊ STANU
    static PIXELFORMATDESCRIPTOR pfd = {
      sizeof(PIXELFORMATDESCRIPTOR), //rozmiar struktury
      1,
      PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
      PFD_TYPE_RGBA,
      16,
      0,0,0,0,0,0,
      0,
      0,  //PRZESUNIÊCIE
      0,  //AKUMULATOR
      0,0,0,0,  //PRZESUNIÊCIE AKKUMULATORA
      16,
      0,
      0,
      PFD_MAIN_PLANE,
      0,
      0,0,0
    };

    GLuint PixelFormat;    //uchwyt kontekstu graficznego

    hDC = GetDC(hwndDlg);
    PixelFormat = ChoosePixelFormat(hDC, &pfd);
    SetPixelFormat(hDC, PixelFormat, &pfd);

    hRC = wglCreateContext(hDC);
    wglMakeCurrent(hDC, hRC);
  }

  case WM_SIZE:
  {
    GLint iWidth = LOWORD(lParam);
    GLint iHeight = HIWORD(lParam);
    if (iHeight == 0) iHeight = 1;

    glViewport(0, 0, iWidth, iHeight);

    glMatrixMode(GL_PROJECTION);

    glLoadIdentity();

    //glLoadMatrix();
    gluPerspective(45.0f, iWidth / iHeight, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
  }

  case WM_COMMAND:
  {
    /*
    switch (HIWORD(wParam))
    {
    case BN_CLICKED:    //zdarzenie klikniêcia
    switch (LOWORD(wParam))
    {
    case IDC_BUTTON_START:
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
    HWND hwndButtonStart = GetDlgItem(hwndDlg, IDC_BUTTON_START);
    wsprintf(szText, "Stop");
    SetWindowText(hwndButtonStart, szText);

    //Rysowanie siatki gry
    HDC hdc = GetDC(hwndDlg);
    //LineTo
    //MovetoEx
    //Rectangle
    //TextOut
    //GetPixel
    //SetPixel
    HPEN hMyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
    SelectObject(hdc, hMyPen);

    MoveToEx(hdc, 100, 30, NULL);
    LineTo(hdc, 100, 230);
    MoveToEx(hdc, 180, 30, NULL);
    LineTo(hdc, 180, 230);
    MoveToEx(hdc, 40, 100, NULL);
    LineTo(hdc, 240, 100);
    MoveToEx(hdc, 40, 180, NULL);
    LineTo(hdc, 240, 180);
    //DeleteObject(hMyPen);
    TextOut(hdc, 0, 0, szText, strlen(szText));
    ReleaseDC(hwndDlg, hdc);

    for (int i = 0; i < 3; i++)
    {
    for (int j = 0; j < 3; j++)
    {
    isFieldOccupiedByFirstPlayer[i][j] = false;
    isFieldOccupiedBySecondPlayer[i][j] = false;
    }
    }
    }
    else
    {
    isGameOn = false;
    HWND hwndButtonStart = GetDlgItem(hwndDlg, IDC_BUTTON_START);
    CHAR szText[500];
    wsprintf(szText, "Start");
    SetWindowText(hwndButtonStart, szText);
    }
    }
    return TRUE;
    }*/
  }
  return FALSE;

  case WM_LBUTTONDOWN:
  {
    /*CHAR szText[200];
    if (isGameOn == true)
    {
    int x = LOWORD(lParam); int y = HIWORD(lParam);
    if ((x > 30 && x < 240) && (y > 30 && y < 240))
    {
    int fieldX = (x - 10) / 80;
    int fieldY = (y - 10) / 80;
    if ((isFieldOccupiedByFirstPlayer[fieldX][fieldY] == false) &&
    (isFieldOccupiedBySecondPlayer[fieldX][fieldY] == false))
    {
    x = fieldX * 80 + 60;
    y = fieldY * 80 + 60;
    HDC hdc = GetDC(hwndDlg);
    if (isFirstPlayerTurn == true)
    {
    MoveToEx(hdc, x - 30, y - 30, NULL);
    LineTo(hdc, x + 30, y + 30);
    MoveToEx(hdc, x - 30, y + 30, NULL);
    LineTo(hdc, x + 30, y - 30);
    isFieldOccupiedByFirstPlayer[fieldX][fieldY] = true;
    }
    else
    {
    MoveToEx(hdc, x - 30, y - 30, NULL);
    LineTo(hdc, x - 30, y + 30);
    LineTo(hdc, x - 30, y - 30);
    LineTo(hdc, x + 30, y - 30);
    LineTo(hdc, x + 30, y + 30);
    isFieldOccupiedBySecondPlayer[fieldX][fieldY] = true;
    }
    ReleaseDC(hwndDlg, hdc);
    isFirstPlayerTurn = !isFirstPlayerTurn; //prze³¹czanie graczy
    }
    }
    }*/
  }
  return TRUE;

  /*case WM_PAINT:
  {
  HDC hdc = GetDC(hwndDlg);
  //DrawBoard(hdc);
  //HPEN hMyPen = CreatePen(PS_SOLID, 5, RGB(255, 255, 0));
  //SelectObject(hdc, hMyPen);

  MoveToEx(hdc, 100, 30, NULL);
  LineTo(hdc, 100, 230);
  MoveToEx(hdc, 180, 30, NULL);
  LineTo(hdc, 180, 230);
  MoveToEx(hdc, 40, 100, NULL);
  LineTo(hdc, 240, 100);
  MoveToEx(hdc, 40, 180, NULL);
  LineTo(hdc, 240, 180);

  //DrawAllBoards(hdc);
  for (int iFieldX = 0; iFieldX < 3; iFieldX++)
  {
  for (int iFieldY = 0; iFieldY < 3; iFieldY++)
  {
  if (isFieldOccupiedByFirstPlayer[iFieldX][iFieldY] == true)
  {
  //DrawX(hdc, iFieldX, iFieldY);
  }
  if (isFieldOccupiedBySecondPlayer[iFieldX][iFieldY] == true)
  {
  //DrawO(hdc, iFieldX, iFieldY);
  }
  }
  }
  ReleaseDC(hwndDlg, hdc);
  }
  return TRUE;
  */

  case WM_CLOSE:    //komunikat zamkniêcia okienka
  {
    DestroyWindow(hwndDlg);
    PostQuitMessage(0);
  }
  return TRUE;
  }
  return FALSE;
}
//
//rysowanie uk³adu wspó³rzêdnych
//
void DrawGLAxis()
{
  glBegin(GL_LINES);
  glColor3d(1, 0, 0);   //oœ X czerwona
  glVertex3d(3, 0, 0);
  glVertex3d(-1, 0, 0);

  glColor3d(0, 1, 0);   //oœ Y zielona
  glVertex3d(0, 3, 0);
  glVertex3d(0, -1, 0);

  glColor3d(0, 0, 1);   //oœ Z niebieska
  glVertex3d(0, 0, 3);
  glVertex3d(0, 0, -1);
  glEnd();
}
//
//rysowanie kostki szeœciennej
//
void DrawGLCube(int a, int b, int c)
{
  glBegin(GL_QUADS);

  glColor3d(1, 0, 0);   //red bottom
  glNormal3d(0, -1, 0);
  glVertex3d(0, 0, 0);
  glVertex3d(0, 0, c);
  glVertex3d(a, 0, c);
  glVertex3d(a, 0, 0);

  glColor3d(0, 1, 0);   //green
  glNormal3d(1, 0, 0);
  glVertex3d(a, 0, 0);
  glVertex3d(a, 0, c);
  glVertex3d(a, b, c);
  glVertex3d(a, b, 0);

  glColor3d(1, 0, 0);   //red top
  glNormal3d(0, 1, 0);
  glVertex3d(a, b, 0);
  glVertex3d(a, b, c);
  glVertex3d(0, b, c);
  glVertex3d(0, b, 0);

  glColor3d(0, 1, 1);   //cyan 
  glNormal3d(-1, 0, 0);
  glVertex3d(0, b, 0);
  glVertex3d(0, b, c);
  glVertex3d(0, 0, c);
  glVertex3d(0, 0, 0);

  glColor3d(1, 0, 1);   //magenta
  glNormal3d(0, 0, 1);
  glVertex3d(0, 0, c);
  glVertex3d(0, b, c);
  glVertex3d(a, b, c);
  glVertex3d(a, 0, c);

  glColor3d(1, 1, 0);   //yellow
  glNormal3d(0, 0, -1);
  glVertex3d(0, 0, 0);
  glVertex3d(a, 0, 0);
  glVertex3d(a, b, 0);
  glVertex3d(0, b, 0);

  glEnd();
}
//
//rysowanie kó³ka
//
void DrawGLBall()
{
  glBegin(GL_TRIANGLE_STRIP);

  glColor3d(1, 0, 0);   //red bottom
  glNormal3d(0, -1, 0);

  glVertex3d(0, 0, -0.2);
  glVertex3d(0, 0, 0.2);
  glVertex3d(0.1, 0.1, -0.2);
  glVertex3d(0.2, 0.2, 0.2);
  glVertex3d(0.3, 0.3, -0.2);
  glVertex3d(0.4, 0.4, 0.2);
  glVertex3d(0.5, 0.5, -0.2);
  glVertex3d(0.5, 0.5, 0.2);
  glVertex3d(0.4, 0.6, -0.2);
  glVertex3d(0.3, 0.7, 0.2);
  glVertex3d(0.2, 0.8, -0.2);
  glVertex3d(0.1, 0.9, 0.2);
  glVertex3d(0, 1, -0.2);
  glVertex3d(0, 1, 0.2);

  glVertex3d(-0.1, 0.9, -0.2);
  glVertex3d(-0.2, 0.8, 0.2);
  glVertex3d(-0.3, 0.7, -0.2);
  glVertex3d(-0.4, 0.6, 0.2);
  glVertex3d(-0.5, 0.5, -0.2);
  glVertex3d(-0.5, 0.5, 0.2);
  glVertex3d(-0.4, 0.4, -0.2);
  glVertex3d(-0.3, 0.3, 0.2);
  glVertex3d(-0.2, 0.2, -0.2);
  glVertex3d(-0.1, 0.1, 0.2);
  glVertex3d(0, 0, -0.2);
  glVertex3d(0, 0, 0.2);

  glColor3d(0, 1, 0);

  glVertex3d(-0.2, 0, 0);
  glVertex3d(0.2, 0, 0);
  glVertex3d(-0.2, 0.1, 0.1);
  glVertex3d(0.2, 0.2, 0.2);
  glVertex3d(-0.2, 0.3, 0.3);
  glVertex3d(0.2, 0.4, 0.4);
  glVertex3d(-0.2, 0.5, 0.5);
  glVertex3d(0.2, 0.6, 0.4);
  glVertex3d(-0.2, 0.7, 0.3);
  glVertex3d(0.2, 0.8, 0.2);
  glVertex3d(-0.2, 0.9, 0.1);
  glVertex3d(0.2, 1, 0);

  glVertex3d(-0.2, 1, 0);
  glVertex3d(0.2, 0.9, -0.1);
  glVertex3d(-0.2, 0.8, -0.2);
  glVertex3d(0.2, 0.7, -0.3);
  glVertex3d(-0.2, 0.6, -0.4);
  glVertex3d(0.2, 0.5, -0.5);
  glVertex3d(-0.2, 0.4, -0.4);
  glVertex3d(0.2, 0.3, -0.3);
  glVertex3d(-0.2, 0.2, -0.2);
  glVertex3d(0.2, 0.1, -0.1);
  glVertex3d(-0.2, 0, 0);
  glVertex3d(0.2, 0, 0);
  glEnd();
}
//
//rysowanie krzy¿yka
//
void DrawGLCross()
{
  glBegin(GL_TRIANGLE_STRIP);
  glColor3d(0, 0, 1);
  glNormal3d(0, -1, 0);

  glVertex3d(0, -0.5, 0);
  glVertex3d(0, -0.5, 0.5);
  glVertex3d(0.25, -0.75, 0);
  glVertex3d(0.5, -1, 0.5);
  glVertex3d(0.5, -1, 0);

  glVertex3d(0.75, -0.7, 0.5);
  glVertex3d(1, -0.5, 0);
  glVertex3d(1, -0.5, 0.5);

  glVertex3d(0.75, -0.25, 0);
  glVertex3d(0.5, -0, 0.5);
  glVertex3d(0.5, -0, 0);

  glVertex3d(0.75, 0.25, 0.5);
  glVertex3d(1, 0.5, 0);
  glVertex3d(1, 0.5, 0.5);

  glVertex3d(0.75, 0.75, 0);
  glVertex3d(0.5, 1, 0.5);
  glVertex3d(0.5, 1, 0);

  glVertex3d(0.25, 0.75, 0.5);
  glVertex3d(0, 0.5, 0);
  glVertex3d(0, 0.5, 0.5);

  glVertex3d(-0.25, 0.75, 0);
  glVertex3d(-0.5, 1, 0.5);
  glVertex3d(-0.5, 1, 0);

  glVertex3d(-0.75, 0.75, 0.5);
  glVertex3d(-1, 0.5, 0);
  glVertex3d(-1, 0.5, 0.5);

  glVertex3d(-0.75, 0.25, 0);
  glVertex3d(-0.5, 0, 0.5);
  glVertex3d(-0.5, 0, 0);

  glVertex3d(-0.75, -0.25, 0.5);
  glVertex3d(-1, -0.5, 0);
  glVertex3d(-1, -0.5, 0.5);

  glVertex3d(-0.75, -0.75, 0);
  glVertex3d(-0.5, -1, 0.5);
  glVertex3d(-0.5, -1, 0);

  glVertex3d(-0.25, -0.75, 0.5);
  glVertex3d(0, -0.5, 0);
  glVertex3d(0, -0.5, 0.5);

  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  glColor3d(1, 1, 0);
  glNormal3d(0, 0, -1);

  glVertex3d(0.5, -1, 0.5);
  glVertex3d(1, -0.5, 0.5);
  glVertex3d(0, -0.5, 0.5);
  glVertex3d(0, 0.5, 0.5);
  glVertex3d(-1, 0.5, 0.5);
  glVertex3d(-0.5, 1, 0.5);
  glVertex3d(0, 0.5, 0.5);

  glVertex3d(-0.5, 0, 0.5);
  glVertex3d(-1, -0.5, 0.5);
  glVertex3d(-0.5, -1, 0.5);
  glVertex3d(-0.5, 0, 0.5);
  glVertex3d(0.5, 0, 0.5);
  glVertex3d(0.5, 1, 0.5);
  glVertex3d(1, 0.5, 0.5);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  glColor3d(1, 0, 1);
  glNormal3d(0, 0, 1);

  glVertex3d(0.5, -1, 0);
  glVertex3d(1, -0.5, 0);
  glVertex3d(0, -0.5, 0);
  glVertex3d(0, 0.5, 0);
  glVertex3d(-1, 0.5, 0);
  glVertex3d(-0.5, 1, 0);
  glVertex3d(0, 0.5, 0);

  glVertex3d(-0.5, 0, 0);
  glVertex3d(-1, -0.5, 0);
  glVertex3d(-0.5, -1, 0);
  glVertex3d(-0.5, 0, 0);
  glVertex3d(0.5, 0, 0);
  glVertex3d(0.5, 1, 0);
  glVertex3d(1, 0.5, 0);

  glEnd();
}
//
//rysowanie planszy
//
void DrawBoard()
{
  int iLineLength = 1;
  int iLineWidth = 1;
  int iLineDepth = 1;

  glTranslatef(-3, 3, 0);
  DrawGLAxis();
  DrawGLCube(iLineLength, iLineWidth + 4, iLineDepth);
  DrawGLCube(iLineLength, iLineWidth - 12, iLineDepth);
  DrawGLCube(iLineLength - 4, iLineWidth, iLineDepth);
  DrawGLCube(iLineLength + 8, iLineWidth, iLineDepth);

  glTranslatef(5, -7, 0);
  DrawGLAxis();
  DrawGLCube(iLineLength, iLineWidth - 5, iLineDepth);
  DrawGLCube(iLineLength, iLineWidth + 11, iLineDepth);
  DrawGLCube(iLineLength + 3, iLineWidth, iLineDepth);
  DrawGLCube(iLineLength - 9, iLineWidth, iLineDepth);
}

GLint DrawGLScene()
{
  glEnable(GL_DEPTH_TEST);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glLoadIdentity();

  static GLfloat fAngle = 0.0;
  fAngle += 0.2f;
  glTranslatef(0, 0, -5);
  //glRotatef(fAngle, 0, 1, 0);
  glScalef(0.5, 0.5, 0.5);

  DrawGLAxis();
  //DrawGLCross();

  DrawGLBall();
  glTranslatef(0, 0, -15);
  //glScalef(0.5, 0.5, 1);
  DrawBoard();

  return 1;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow);
  MSG msg = {};
  /* while (GetMessage(&msg, NULL, 0, 0))
  {
  TranslateMessage(&msg);
  DispatchMessage(&msg);
  }*/
  bool bDone = false;
  while (!bDone)
  {
    if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))     //pobiera wiadomoœæ z kolejki wiadomoœci do obs³u¿enia
    {
      if (msg.message == WM_QUIT) bDone = true;
      TranslateMessage(&msg);
      DispatchMessage(&msg);
    }
    else
    {
      DrawGLScene();
      //DrawGLCube(1,1,1);
      SwapBuffers(hDC);
    }
  }
  return 0;
}