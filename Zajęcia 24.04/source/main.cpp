#include <Windows.h>
#include <mmsystem.h>
#include "res.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdio.h>
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
HDC hDC = NULL;
HGLRC hRC = NULL;
HINSTANCE hInst;
GLuint idTexture;
float fStep = 1.0;
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
  glBindTexture(GL_TEXTURE_2D, idTexture);
  glBegin(GL_QUADS);

  glColor3d(1, 0, 0);   //red bottom
  glNormal3d(0, -1, 0);

  glTexCoord2f(0.0, 0.0);   glVertex3d(0, 0, 0);
  glTexCoord2f(0.0, 1.0);   glVertex3d(0, 0, c);
  glTexCoord2f(0.5, 1.0);   glVertex3d(a, 0, c);
  glTexCoord2f(0.5, 0.0);   glVertex3d(a, 0, 0);

  glColor3d(0, 1, 0);   //green
  glNormal3d(1, 0, 0);

  glTexCoord2f(0.0, 0.0);   glVertex3d(a, 0, 0);
  glTexCoord2f(0.0, 1.0);   glVertex3d(a, 0, c);
  glTexCoord2f(0.25, 1.0);   glVertex3d(a, b, c);
  glTexCoord2f(0.25, 0.0);   glVertex3d(a, b, 0);

  glColor3d(1, 0, 0);   //red top
  glNormal3d(0, 1, 0);

  glTexCoord2f(0.0, 0.0);  glVertex3d(a, b, 0);
  glTexCoord2f(0.0, 1.0);  glVertex3d(a, b, c);
  glTexCoord2f(1.0, 1.0);  glVertex3d(0, b, c);
  glTexCoord2f(1.0, 0.0);  glVertex3d(0, b, 0);

  glColor3d(0, 1, 1);   //cyan 
  glNormal3d(-1, 0, 0);

  glTexCoord2f(0.0, 0.0);  glVertex3d(0, b, 0);
  glTexCoord2f(0.0, 1.0);  glVertex3d(0, b, c);
  glTexCoord2f(1.0, 1.0);  glVertex3d(0, 0, c);
  glTexCoord2f(1.0, 0.0);  glVertex3d(0, 0, 0);

  glColor3d(1, 0, 1);   //magenta
  glNormal3d(0, 0, 1);

  glTexCoord2f(0.0, 0.0);  glVertex3d(0, 0, c);
  glTexCoord2f(0.0, 1.0);  glVertex3d(0, b, c);
  glTexCoord2f(1.0, 1.0);  glVertex3d(a, b, c);
  glTexCoord2f(1.0, 0.0);  glVertex3d(a, 0, c);

  glColor3d(1, 1, 0);   //yellow
  glNormal3d(0, 0, -1);

  glTexCoord2f(0.0, 0.0);  glVertex3d(0, 0, 0);
  glTexCoord2f(0.0, 1.0);  glVertex3d(a, 0, 0);
  glTexCoord2f(1.0, 1.0);  glVertex3d(a, b, 0);
  glTexCoord2f(1.0, 0.0);  glVertex3d(0, b, 0);

  glEnd();
}
//
//rysowanie kó³ka
//
void DrawGLBall(int x, int y, int z)
{
  glBegin(GL_TRIANGLE_STRIP);
  glColor3d(1, 0, 0);   //red bottom
  glNormal3d(-1, -1, 0);

  glVertex3d(x, y, z - 0.2);
  glVertex3d(x, y, z + 0.2);
  glVertex3d(x + 0.1, y + 0.1, z - 0.2);
  glVertex3d(x + 0.2, y + 0.2, z + 0.2);
  glVertex3d(x + 0.3, y + 0.3, z - 0.2);
  glVertex3d(x + 0.4, y + 0.4, z + 0.2);
  glVertex3d(x + 0.5, y + 0.5, z - 0.2);

  glNormal3d(1, 1, 0);

  glVertex3d(x + 0.5, y + 0.5, z + 0.2);
  glVertex3d(x + 0.4, y + 0.6, z - 0.2);
  glVertex3d(x + 0.3, y + 0.7, z + 0.2);
  glVertex3d(x + 0.2, y + 0.8, z - 0.2);
  glVertex3d(x + 0.1, y + 0.9, z + 0.2);
  glVertex3d(x, y, z - 0.2);
  glVertex3d(x, y, z + 0.2);

  glNormal3d(-1, 1, 0);

  glVertex3d(x - 0.1, y + 0.9, z - 0.2);
  glVertex3d(x - 0.2, y + 0.8, z + 0.2);
  glVertex3d(x - 0.3, y + 0.7, z - 0.2);
  glVertex3d(x - 0.4, y + 0.6, z + 0.2);
  glVertex3d(x - 0.5, y + 0.5, z - 0.2);

  glNormal3d(-1, -1, 0);

  glVertex3d(x - 0.5, y + 0.5, z + 0.2);
  glVertex3d(x - 0.4, y + 0.4, z - 0.2);
  glVertex3d(x - 0.3, y + 0.3, z + 0.2);
  glVertex3d(x - 0.2, y + 0.2, z - 0.2);
  glVertex3d(x - 0.1, y + 0.1, z + 0.2);
  glVertex3d(x, y, z - 0.2);
  glVertex3d(x, y, z + 0.2);

  glColor3d(0, -1, 1);

  glNormal3d(0, -1, 1);

  glVertex3d(x - 0.2, y, z);
  glVertex3d(x + 0.2, y, z);
  glVertex3d(x - 0.2, y + 0.1, z + 0.1);
  glVertex3d(x + 0.2, y + 0.2, z + 0.2);
  glVertex3d(x - 0.2, y + 0.3, z + 0.3);
  glVertex3d(x + 0.2, y + 0.4, z + 0.4);
  glVertex3d(x - 0.2, y + 0.5, z + 0.5);

  glColor3d(0, -1, 1);
  glNormal3d(0, 1, 1);

  glVertex3d(x + 0.2, y + 0.6, z + 0.4);
  glVertex3d(x - 0.2, y + 0.7, z + 0.3);
  glVertex3d(x + 0.2, y + 0.8, z + 0.2);
  glVertex3d(x - 0.2, y + 0.9, z + 0.1);
  glVertex3d(x + 0.2, y + 1, z);

  glNormal3d(0, 1, -1);

  glVertex3d(x - 0.2, y + 1, z);
  glVertex3d(x + 0.2, y + 0.9, z - 0.1);
  glVertex3d(x - 0.2, y + 0.8, z - 0.2);
  glVertex3d(x + 0.2, y + 0.7, z - 0.3);
  glVertex3d(x - 0.2, y + 0.6, z - 0.4);
  glVertex3d(x + 0.2, y + 0.5, z - 0.5);

  glNormal3d(0, -1, -1);

  glVertex3d(x - 0.2, y + 0.4, z - 0.4);
  glVertex3d(x + 0.2, y + 0.3, z - 0.3);
  glVertex3d(x - 0.2, y + 0.2, z - 0.2);
  glVertex3d(x + 0.2, y + 0.1, z - 0.1);
  glVertex3d(x - 0.2, y, z);
  glVertex3d(x + 0.2, y, z);
  glEnd();
}
//
//rysowanie krzy¿yka
//
void DrawGLCross(int x, int y, int z)
{
  glBegin(GL_TRIANGLE_STRIP);
  glColor3d(0, 0, 1);
  glNormal3d(0, -1, 0);

  glVertex3d(x, y - 0.5, z);
  glVertex3d(x, y - 0.5, z + 0.5);
  glVertex3d(x + 0.25, y - 0.75, z);
  glVertex3d(x + 0.5, y - 1, z + 0.5);
  glVertex3d(x + 0.5, y - 1, z);

  glVertex3d(x + 0.75, y - 0.7, z + 0.5);
  glVertex3d(x + 1, y - 0.5, z);
  glVertex3d(x + 1, y - 0.5, z + 0.5);

  glVertex3d(x + 0.75, y - 0.25, z);
  glVertex3d(x + 0.5, y, z + 0.5);
  glVertex3d(x + 0.5, y, z);

  glVertex3d(x + 0.75, x + 0.25, x + 0.5);
  glVertex3d(x + 1, y + 0.5, z);
  glVertex3d(x + 1, y + 0.5, z + 0.5);

  glVertex3d(x + 0.75, y + 0.75, z);
  glVertex3d(x + 0.5, y + 1, z + 0.5);
  glVertex3d(x + 0.5, y + 1, z);

  glVertex3d(x + 0.25, y + 0.75, z + 0.5);
  glVertex3d(x, y + 0.5, z);
  glVertex3d(x, y + 0.5, z + 0.5);

  glVertex3d(x - 0.25, y + 0.75, z);
  glVertex3d(x - 0.5, y, z + 0.5);
  glVertex3d(x - 0.5, y, z);

  glVertex3d(x - 0.75, y + 0.75, z + 0.5);
  glVertex3d(x - 1, y + 0.5, z);
  glVertex3d(x - 1, y + 0.5, z + 0.5);

  glVertex3d(x - 0.75, y + 0.25, z);
  glVertex3d(x - 0.5, y, z + 0.5);
  glVertex3d(x - 0.5, y, z);

  glVertex3d(x-0.75, y-0.25, z+0.5);
  glVertex3d(x-1, y-0.5, z);
  glVertex3d(x-1, y-0.5, z+0.5);

  glVertex3d(x - 0.75, y - 0.75, z);
  glVertex3d(x - 0.5, y - 1, z + 0.5);
  glVertex3d(x - 0.5, y - 1, z);

  glVertex3d(x - 0.25, y - 0.75, z + 0.5);
  glVertex3d(x, y - 0.5, z);
  glVertex3d(x, y - 0.5, z + 0.5);;

  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  glColor3d(1, 1, 0);
  glNormal3d(0, 0, 1);

  glVertex3d(x + 0.5, y - 1, z + 0.5);
  glVertex3d(x + 1, y - 0.5, z + 0.5);
  glVertex3d(x, y - 0.5, z + 0.5);
  glVertex3d(x, y + 0.5, z + 0.5);
  glVertex3d(x - 1, y + 0.5, z + 0.5);
  glVertex3d(x - 0.5, y + 1, z + 0.5);
  glVertex3d(x, y + 0.5, z + 0.5);

  glVertex3d(x - 0.5, y, z + 0.5);
  glVertex3d(x - 1, y - 0.5, z + 0.5);
  glVertex3d(x - 0.5, y - 1, 0.5);
  glVertex3d(x - 0.5, y, z + 0.5);
  glVertex3d(x + 0.5, y, z + 0.5);
  glVertex3d(x + 0.5, y + 1, z + 0.5);
  glVertex3d(x + 1, y + 0.5, z + 0.5);
  glEnd();

  glBegin(GL_TRIANGLE_STRIP);
  glColor3d(1, 0, 1);
  glNormal3d(0, 0, -1);

  glVertex3d(x + 0.5, y - 1, z);
  glVertex3d(x + 1, y - 0.5, z);
  glVertex3d(x, y - 0.5, z);
  glVertex3d(x, y + 0.5, z);
  glVertex3d(x - 1, y + 0.5, z);
  glVertex3d(x - 0.5, y + 1, z);
  glVertex3d(x, y + 0.5, z);

  glVertex3d(x - 0.5, y, z);
  glVertex3d(x - 1, y - 0.5, z);
  glVertex3d(x - 0.5, y - 1, z);
  glVertex3d(x - 0.5, y, z);
  glVertex3d(x + 0.5, y, z);
  glVertex3d(x + 0.5, y + 1, z);
  glVertex3d(x + 1, y + 0.5, z);

  glEnd();
}
//
//rysowanie planszy
//
void DrawBoard(int iLineLength, int iLineWidth, int iLineDepth)
{
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
  glClearColor(0.0f, 0.6f, 0.9f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_TEXTURE_2D);
  glLoadIdentity();

  static GLfloat fAngle = 0.0;
  fAngle += fStep;
  //
  //
  //
  glPushMatrix();

  glTranslatef(3, 0, -20);
  glRotatef(fAngle, 1, 0, 0);
  //glScalef(0.8, 0.8, 0.8);
  DrawGLCross(0.5, 0.5, 0.5);
  //DrawGLAxis();

  glPopMatrix();
  //
  //
  //
  glPushMatrix();

  glTranslatef(0, 0, -10); 
  //DrawGLAxis();
  //glScalef(0.01, 0.01, 0.01);
  glRotatef(fAngle, 1, 0, 0);
  DrawGLBall(0.5, 0.5, 0.5);

  glPopMatrix();
  //
  //
  //
  glPushMatrix();

  glTranslatef(0, 0, -3); 
  //DrawGLAxis();
  glRotatef(fAngle, 1, 0, 0);
  glScalef(0.1, 0.1, 0.1);
  DrawBoard(1, 1, 1);

  glPopMatrix();

  return 1;
}

unsigned char* ReadBmpFromFile(char* szFileName, int &riWidth, int &riHeight)
{
  BITMAPFILEHEADER     bfh;
  BITMAPINFOHEADER     bih;

  int                i, j, h, v, lev, l, ls;
  unsigned char*     buff = NULL;

  unsigned char* p_palette = NULL;
  unsigned short n_colors = 0;

  unsigned char* pRGBBuffer = NULL;

  FILE* hfile;    // = fopen_s(szFileName, "rb");
  fopen_s(&hfile, szFileName, "rb");
  if (hfile != NULL)
  {
    fread(&bfh, sizeof(bfh), 1, hfile);
    if (!(bfh.bfType != 0x4d42 || (bfh.bfOffBits < (sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER)))))
    {
      fread(&bih, sizeof(bih), 1, hfile);
      v = bih.biWidth;
      h = bih.biHeight;
      lev = bih.biBitCount;

      riWidth = v;
      riHeight = h;
      pRGBBuffer = new unsigned char[riWidth*riHeight * 3]; //Zaalokowanie odpowiedniego buffora obrazu

                                                            //Za³aduj Palete barw jesli jest
      if ((lev == 1) || (lev == 4) || (lev == 8))
      {
        n_colors = 1 << lev;
        p_palette = new unsigned char[4 * n_colors];
        fread(p_palette, 4 * n_colors, 1, hfile);
      }

      fseek(hfile, bfh.bfOffBits, SEEK_SET);

      buff = new unsigned char[v * 4];

      switch (lev)
      {
      case 1:
        //Nie obs³ugiwane
        break;
      case 4:
        //nie Obs³ugiwane
        break;
      case 8: //Skala szaroœci
        ls = (v + 3) & 0xFFFFFFFC;
        for (j = (h - 1); j >= 0; j--)
        {
          fread(buff, ls, 1, hfile);
          for (i = 0, l = 0; i<v; i++)
          {
            pRGBBuffer[((j*riWidth) + i) * 3 + 2] = p_palette[(buff[i] << 2) + 2];//R
            pRGBBuffer[((j*riWidth) + i) * 3 + 1] = p_palette[(buff[i] << 2) + 1];//G
            pRGBBuffer[((j*riWidth) + i) * 3 + 0] = p_palette[(buff[i] << 2) + 0];//B
          }
        };
        break;
      case 24:
        //bitmapa RGB
        ls = (v * 3 + 3) & 0xFFFFFFFC;
        for (j = (h - 1); j >= 0; j--)
        {
          //x_fread(hfile,buff,ls);
          fread(buff, ls, 1, hfile);
          for (i = 0, l = 0; i<v; i++, l += 3)
          {
            pRGBBuffer[((j*riWidth) + i) * 3 + 0] = buff[l + 0];
            pRGBBuffer[((j*riWidth) + i) * 3 + 1] = buff[l + 1];
            pRGBBuffer[((j*riWidth) + i) * 3 + 2] = buff[l + 2];
          };
        };
        break;
      case 32:
        // RGBA bitmap 
        for (j = (h - 1); j >= 0; j--)
        {
          fread(buff, v * 4, 1, hfile);
          for (i = 0, l = 0; i<v; i++, l += 4)
          {
            pRGBBuffer[((j*riWidth) + i) * 3 + 0] = buff[l + 0];
            pRGBBuffer[((j*riWidth) + i) * 3 + 1] = buff[l + 1];
            pRGBBuffer[((j*riWidth) + i) * 3 + 2] = buff[l + 2];
          }
        };
        break;
      };
      delete buff;
      if (p_palette) delete p_palette;

    }
  }
  return pRGBBuffer;
}

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
      //
      //³adowanie obrazka
      //
      int iWidth, iHeight;
      unsigned char* pMyImage = ReadBmpFromFile("..\\res\\sheep.bmp",iWidth, iHeight);

      glGenTextures(1, &idTexture);

      glBindTexture(GL_TEXTURE_2D, idTexture);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, iWidth, iHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, pMyImage);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      delete [] pMyImage;
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
      gluPerspective(45.0f, iWidth / (float) iHeight, 0.1f, 100.0f);

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
      PlaySound(MAKEINTRESOURCE(IDW_DICE), hInst, SND_RESOURCE);
      SetTimer(hwndDlg, 1, 500, NULL); KillTimer(hwndDlg, 1);
    }
    return TRUE;

    case WM_TIMER:
    {
      if (wParam == 1)
      {
        fStep = 0.0; 
        KillTimer(hwndDlg, 1);
      }
      if (wParam == 2) 
      {
        DrawGLScene();
        SwapBuffers(hDC);
      }
    }
    return TRUE;

    case WM_CLOSE:    //komunikat zamkniêcia okienka
    {
      DestroyWindow(hwndDlg);
      PostQuitMessage(0);
    }
    return TRUE;
  }
  return FALSE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow) 
{
  HWND hwndMainWindow = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_MAINVIEW), NULL, DialogProc);
  ShowWindow(hwndMainWindow, iCmdShow); 
  MSG msg = {};

  SetTimer(hwndMainWindow, 2, 50, NULL);
  while (GetMessage(&msg, NULL, 0, 0)) 
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  /*bool bDone = false;
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
  }*/
  return 0;
}

//lodepng
//picojpeg