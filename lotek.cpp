#define _WIN32_IE 0x0600        //musi byc tu przed zeby common controls dzialaly
#include "lotek_dodatek.h"
#include <iostream>
#include <ctime>
#include <time.h>
#include <cstdlib>
#include <stdio.h>
#include <windows.h>
#include <commctrl.h>
using namespace std;


#define ID_PRZYCISK(K) (500+K)           //dyrektywa
#define ID_RADIO1  601
#define ID_RADIO2  602
#define ID_RADIO3  603


LPSTR NazwaKlasy = "Klasa Okienka";
MSG Komunikat;

HWND g_hPrzyciskL;                //deklaracja globalnego uchwytu
HWND g_hPrzyciskW;
HWND g_hPrzyciskO;
HWND g_hPrzyciskR;
HWND g_hPrzyciskS;
HWND g_hPrzyciskILE;
HWND g_hPrzyciskLICZBY;
HWND g_hPrzyciskLICZNIK2;
HWND hOknoLK;
HWND hOknoLK2;
HWND hOknoLK3;
HWND hOknoLK4;
HWND hOknoLK5;
HWND hText;
HWND hRadio1, hRadio2, hRadio3;
HWND hOknoWYBRANE;
HWND hOknoWYBRANEP;
HWND hOknoSTOPER;
HWND OknoRadio;
HWND g_hPrzyciskLICZNIK;
HWND g_hPrzyciskAUTOR;
HWND g_hPrzyciskSZANS;
HWND g_hPrzyciskTRAF;
HWND hOkno1, hOkno2, hOkno3, hOkno4, hOkno5, hOkno6, hOkno7, hOkno8, hOkno9, hOkno10;         //okna liczb
HWND hOknoL1, hOknoL2, hOknoL3, hOknoL4, hOknoL5, hOknoL6;            //okna wynikow
HWND hOknoW;
HWND hOknoT1, hOknoT2, hOknoT3, hOknoT4, hOknoT5, hOknoT6, hOknoT7, hOknoT8, hOknoT9, hOknoT10, hOknoT11;            //okna trafien
HWND hOknoP1, hOknoP2, hOknoP3, hOknoP4, hOknoP5;            //okna trafien +4
HWND hOknoS1, hOknoS2, hOknoS3, hOknoS4, hOknoS5, hOknoS6;            //okna szans
HWND hStatic1, hStatic2, hStatic3, hStatic4, hStatic5, hStatic6, hStatic7, hStatic8, hStatic9, hStatic10, hStatic11;
HWND hStoper1;
HWND hOknoWYNIK, hOknoWYNIK2;
HWND hOkno[6];                     //tablica okien typow
HWND hOknoP;                     //okno typow P
HWND g_hPrzycisk[49];              //deklaracja tablicy globalnych uchwytow
HWND g_hPrzyciskP[4];              //deklaracja tablicy globalnych uchwytow dla plusa
HBRUSH hBrush,hBrush2;        //do koloru tla
HWND hLsb;
//HDC kon;
//PAINTSTRUCT ps;

HHOOK    g_hHook;            //
HWND     g_hWndMsgBox;
WNDPROC  g_MsgBoxProc;
HBRUSH   g_hBrush;
HBITMAP  g_hBitmap;

int typy[6]= {0,0,0,0,0,0};
int typy2= 0;
int czy_wolne_typy[6]= {0,0,0,0,0,0};
int czy_wolne_typy2= 0;
int losowe[6];
int losowa;
int trafienia[6]= {0,0,0,0,0,0};
int trafieniaP[5]= {0,0,0,0,0};
int ile_losowan=1;
char ile_losowan_bufor[10];
int licznik=0;
char text[50];
int licznik_losowan=0;
int licznik_wygranej=0;
int licznik_kosztow=0;
int gra = 35;
int liczby = 5;
int gra2 = 4;
int liczby2 = 1;
float procent[100];
int p = 0;

int ret;

int wylosuj();
int wylosuj2();
char StoperStart();
void resetuj();
LRESULT CALLBACK HookProc (int nCode, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK CoolMsgBoxProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
int CoolMsgBox (HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType);

HBITMAP hbmObraz, hbmOld, hbmMaska;
HICON hbmIkona;

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam );
HBITMAP CreateBitmapMask (HBITMAP hbmColour, COLORREF crTransparent);
BOOL CALLBACK DlgProc (HWND, UINT, WPARAM, LPARAM);

//HFONT hNormalFont = (HFONT)GetStockObject(DEFAULT_GUI_FONT);      //funkcja wczytuj¹ca czcionkê zapisana do zmiennej
WNDCLASSEX wc;           //wypelnienie struktury

HWND hwnd,hwnd2,hProgressBar,hButton;
HINSTANCE hInstance;
//HWND hProgressBar;

int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    WNDCLASSEX wc;           //wypelnienie struktury

    hBrush = CreateSolidBrush(RGB (211, 211, 200));    //tworzy pedzel jednolitego koloru
    hBrush2 = CreateSolidBrush (RGB (211, 211, 200));

    wc.cbSize = sizeof( WNDCLASSEX );
    wc.style = 0;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon( NULL, IDI_APPLICATION );
    wc.hCursor = LoadCursor( hInstance, MAKEINTRESOURCE(KURSOR) );     //laduje kursor
    wc.hbrBackground =( HBRUSH )( hBrush + 0 );       //kolor tla
    wc.lpszMenuName = NULL;
    wc.lpszClassName = NazwaKlasy;
    wc.hIconSm = LoadIcon( hInstance, MAKEINTRESOURCE(IKONA) );        //zmieniam ikone okna
    srand( time( NULL ) );

    INITCOMMONCONTROLSEX cc;//struktura inicjacyjcna
    cc.dwSize=sizeof(INITCOMMONCONTROLSEX);
    cc.dwICC=ICC_BAR_CLASSES;
    InitCommonControlsEx(&cc);//funkcja inicjujaca

    for(int y=1; y<101; y++)
    {
        procent[y-1]=(y*0.01);
    }

    if( !RegisterClassEx( & wc ) )        //rejestrowanie klasy okna
    {
        MessageBox( NULL, "Blad rejestracji okna!", "Koniec",
                    MB_ICONEXCLAMATION | MB_OK );
        return 1;
    }

//   HWND hwnd;        // TWORZENIE OKNA      (skopiowalem do globalnych)

    hwnd = CreateWindowEx( WS_EX_WINDOWEDGE, NazwaKlasy, "Easy Lotek", WS_BORDER  ,
                           CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, NULL, NULL, hInstance, NULL );

    if( hwnd == NULL )
    {
        MessageBox( NULL, "Blad otwarcia okna", "Do zobaczenia..", MB_ICONEXCLAMATION );
        return 1;
    }

    //hProgressBar = CreateWindowEx (0,PROGRESS_CLASS,NULL,WS_CHILD | WS_VISIBLE, 10, 100, 300, 10, hwnd, (HMENU)200, hInstance, NULL);  //progress bar

    OknoRadio = CreateWindowEx( 0, "BUTTON", "GRA", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                     10, 0, 120, 100, hwnd, NULL, hInstance, NULL );
    hRadio1 = CreateWindowEx(0, "BUTTON", "Ekstra Pensja", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE | BS_AUTORADIOBUTTON,            //przyciski radio
                             20, 18, 100, 20, hwnd, (HMENU)ID_RADIO1, hInstance, NULL);
    hRadio2 = CreateWindowEx(0, "BUTTON", "Mini Lotto", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE | BS_AUTORADIOBUTTON,
                             20, 46, 100, 20, hwnd, (HMENU)ID_RADIO2, hInstance, NULL);
    hRadio3 = CreateWindowEx(0, "BUTTON", "Lotto", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE | BS_AUTORADIOBUTTON,
                             20, 74, 100, 20, hwnd, (HMENU)ID_RADIO3, hInstance, NULL);
    CheckRadioButton (hwnd, ID_RADIO1, ID_RADIO2, ID_RADIO1);                   //zaznaczam od razu 1 przycisk

    g_hPrzyciskLICZBY = CreateWindowEx( 0, "BUTTON", "LICZBY", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                        10, 100, 230, 150, hwnd, NULL, hInstance, NULL );

    g_hPrzycisk[0] = CreateWindowEx( 0, "BUTTON", "1", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     20, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(1), hInstance, NULL );
    g_hPrzycisk[1] = CreateWindowEx( 0, "BUTTON", "2", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     40, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(2), hInstance, NULL );
    g_hPrzycisk[2] = CreateWindowEx( 0, "BUTTON", "3", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     60, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(3), hInstance, NULL );
    g_hPrzycisk[3] = CreateWindowEx( 0, "BUTTON", "4", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     80, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(4), hInstance, NULL );
    g_hPrzycisk[4] = CreateWindowEx( 0, "BUTTON", "5", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     100, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(5), hInstance, NULL );
    g_hPrzycisk[5] = CreateWindowEx( 0, "BUTTON", "6", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     120, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(6), hInstance, NULL );
    g_hPrzycisk[6] = CreateWindowEx( 0, "BUTTON", "7", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     140, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(7), hInstance, NULL );
    g_hPrzycisk[7] = CreateWindowEx( 0, "BUTTON", "8", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     160, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(8), hInstance, NULL );
    g_hPrzycisk[8] = CreateWindowEx( 0, "BUTTON", "9", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     180, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(9), hInstance, NULL );
    g_hPrzycisk[9] = CreateWindowEx( 0, "BUTTON", "10", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                     200, 130, 20, 20, hwnd, (HMENU)ID_PRZYCISK(10), hInstance, NULL );
    g_hPrzycisk[10] = CreateWindowEx( 0, "BUTTON", "11", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      20, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(11), hInstance, NULL );
    g_hPrzycisk[11] = CreateWindowEx( 0, "BUTTON", "12", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      40, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(12), hInstance, NULL );
    g_hPrzycisk[12] = CreateWindowEx( 0, "BUTTON", "13", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      60, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(13), hInstance, NULL );
    g_hPrzycisk[13] = CreateWindowEx( 0, "BUTTON", "14", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      80, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(14), hInstance, NULL );
    g_hPrzycisk[14] = CreateWindowEx( 0, "BUTTON", "15", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      100, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(15), hInstance, NULL );
    g_hPrzycisk[15] = CreateWindowEx( 0, "BUTTON", "16", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      120, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(16), hInstance, NULL );
    g_hPrzycisk[16] = CreateWindowEx( 0, "BUTTON", "17", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      140, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(17), hInstance, NULL );
    g_hPrzycisk[17] = CreateWindowEx( 0, "BUTTON", "18", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      160, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(18), hInstance, NULL );
    g_hPrzycisk[18] = CreateWindowEx( 0, "BUTTON", "19", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      180, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(19), hInstance, NULL );
    g_hPrzycisk[19] = CreateWindowEx( 0, "BUTTON", "20", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      200, 150, 20, 20, hwnd, (HMENU)ID_PRZYCISK(20), hInstance, NULL );
    g_hPrzycisk[20] = CreateWindowEx( 0, "BUTTON", "21", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      20, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(21), hInstance, NULL );
    g_hPrzycisk[21] = CreateWindowEx( 0, "BUTTON", "22", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      40, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(22), hInstance, NULL );
    g_hPrzycisk[22] = CreateWindowEx( 0, "BUTTON", "23", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      60, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(23), hInstance, NULL );
    g_hPrzycisk[23] = CreateWindowEx( 0, "BUTTON", "24", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      80, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(24), hInstance, NULL );
    g_hPrzycisk[24] = CreateWindowEx( 0, "BUTTON", "25", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      100, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(25), hInstance, NULL );
    g_hPrzycisk[25] = CreateWindowEx( 0, "BUTTON", "26", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      120, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(26), hInstance, NULL );
    g_hPrzycisk[26] = CreateWindowEx( 0, "BUTTON", "27", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      140, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(27), hInstance, NULL );
    g_hPrzycisk[27] = CreateWindowEx( 0, "BUTTON", "28", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      160, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(28), hInstance, NULL );
    g_hPrzycisk[28] = CreateWindowEx( 0, "BUTTON", "29", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      180, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(29), hInstance, NULL );
    g_hPrzycisk[29] = CreateWindowEx( 0, "BUTTON", "30", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      200, 170, 20, 20, hwnd, (HMENU)ID_PRZYCISK(30), hInstance, NULL );
    g_hPrzycisk[30] = CreateWindowEx( 0, "BUTTON", "31", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      20, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(31), hInstance, NULL );
    g_hPrzycisk[31] = CreateWindowEx( 0, "BUTTON", "32", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      40, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(32), hInstance, NULL );
    g_hPrzycisk[32] = CreateWindowEx( 0, "BUTTON", "33", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      60, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(33), hInstance, NULL );
    g_hPrzycisk[33] = CreateWindowEx( 0, "BUTTON", "34", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      80, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(34), hInstance, NULL );
    g_hPrzycisk[34] = CreateWindowEx( 0, "BUTTON", "35", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      100, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(35), hInstance, NULL );

    g_hPrzyciskP[0] = CreateWindowEx( 0, "BUTTON", "1", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      20, 220, 20, 20, hwnd, (HMENU)ID_PRZYCISK(50), hInstance, NULL );
    g_hPrzyciskP[1] = CreateWindowEx( 0, "BUTTON", "2", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      40, 220, 20, 20, hwnd, (HMENU)ID_PRZYCISK(51), hInstance, NULL );
    g_hPrzyciskP[2] = CreateWindowEx( 0, "BUTTON", "3", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      60, 220, 20, 20, hwnd, (HMENU)ID_PRZYCISK(52), hInstance, NULL );
    g_hPrzyciskP[3] = CreateWindowEx( 0, "BUTTON", "4", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      80, 220, 20, 20, hwnd, (HMENU)ID_PRZYCISK(53), hInstance, NULL );

    hOknoWYBRANE = CreateWindowEx( 0, "BUTTON", "", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                        250, 100, 40, 150, hwnd, NULL, hInstance, NULL );
    hOknoWYBRANEP = CreateWindowEx( 0, "BUTTON", "", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                        300, 100, 40, 150, hwnd, NULL, hInstance, NULL );

    hOknoSTOPER = CreateWindowEx( 0, "BUTTON", "STOPER", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                        350, 100, 160, 150, hwnd, NULL, hInstance, NULL );

    hStoper1 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |                 //okna do wyswietlenia typow
                              SS_LEFT, 360, 120, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStoper1, "0" );

    hOkno[0] = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |                 //okna do wyswietlenia typow
                              SS_LEFT, 260, 120, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOkno[0] , "0");
    hOkno[1] = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 260, 140, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOkno[1] , "0");
    hOkno[2] = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 260, 160, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOkno[2] , "0");
    hOkno[3] = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 260, 180, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOkno[3] , "0");
    hOkno[4] = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 260, 200, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOkno[4] , "0");
    hOkno[5] = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 260, 220, 20, 20, hwnd, NULL, hInstance, NULL);

    hOknoP = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |                 //okno do wyswietlenia typow P
                              SS_LEFT, 310, 120, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoP , "0");

    hOknoWYNIK = CreateWindowEx( 0, "BUTTON", "?", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                      520, 100, 40, 150, hwnd, NULL, hInstance, NULL );
    hOknoL1 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |                 //okna do wyswietlenia wynikow
                             SS_LEFT, 530, 120, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoL1 , "0");
    hOknoL2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 530, 140, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoL2 , "0");
    hOknoL3 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 530, 160, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoL3 , "0");
    hOknoL4 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 530, 180, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoL4 , "0");
    hOknoL5 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 530, 200, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoL5 , "0");
    hOknoL6 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 530, 220, 20, 20, hwnd, NULL, hInstance, NULL);

    hOknoWYNIK2 = CreateWindowEx( 0, "BUTTON", "?", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                     570, 100, 40, 150, hwnd, NULL, hInstance, NULL );
    hOknoW = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |                 //okna do wyswietlenia wynikow P
                             SS_LEFT, 580, 120, 20, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoW , "0");

    g_hPrzyciskTRAF = CreateWindowEx( 0, "BUTTON", "TRAFIENIA", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                           110, 290, 200, 150, hwnd, NULL, hInstance, NULL );
    hStatic1 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                                   SS_LEFT, 120, 310, 160, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic1, "1: ");
    hStatic2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                                   SS_LEFT, 120, 330, 180, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic2, "2: ");
    hStatic3 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                                   SS_LEFT, 120, 350, 180, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic3, "3: ");
    hStatic4 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                                   SS_LEFT, 120, 370, 180, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic4, "4: ");
    hStatic5 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                                   SS_LEFT, 120, 390, 180, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic5, "5: ");
    hStatic6 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 120, 410, 180, 20, hwnd, NULL, hInstance, NULL);
    hStatic7 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 220, 310, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic7, "1+1: ");
    hStatic8 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 220, 330, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic8, "2+1: ");
    hStatic9 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 220, 350, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic9, "3+1: ");
    hStatic10 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 220, 370, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic10, "4+1: ");
    hStatic11 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                              SS_LEFT, 220, 390, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hStatic11, "5+1: ");

    hOknoT1 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |                 //okna do wyswietlenia trafien
                             SS_LEFT, 150, 310, 60, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT1,"0");
    hOknoT2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 150, 330, 60, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT2,"0");
    hOknoT3 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 150, 350, 60, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT3,"0");
    hOknoT4 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 150, 370, 60, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT4,"0");
    hOknoT5 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 150, 390, 60, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT5,"0");
    hOknoT6 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 150, 410, 60, 20, hwnd, NULL, hInstance, NULL);

    hOknoT7 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |                 //okna do wyswietlenia trafien+4
                             SS_LEFT, 260, 310, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT7,"0");
    hOknoT8 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 260, 330, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT8,"0");
    hOknoT9 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 260, 350, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT9,"0");
    hOknoT10 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 260, 370, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT10,"0");
    hOknoT11 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 260, 390, 40, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoT11,"0");

    g_hPrzyciskSZANS = CreateWindowEx( 0, "BUTTON", "SZANSE", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                            320, 290, 210, 150, hwnd, NULL, hInstance, NULL );
    hOknoS1 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |                 //okna do wyswietlenia szans
                             SS_LEFT, 330, 310, 180, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoS1 , "1 : 2.5             1 : 7.5");
    hOknoS2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 330, 330, 180, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoS2 , "1 : 11              1 : 32");
    hOknoS3 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 330, 350, 180, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoS3 , "1 : 100            1 : 299");
    hOknoS4 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 330, 370, 180, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoS4 , "1 : 2 886         1 : 8 657");
    hOknoS5 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 330, 390, 180, 20, hwnd, NULL, hInstance, NULL);
    SetWindowText (hOknoS5 , "1 : 432 843     1 : 1 298 528");
    hOknoS6 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 330, 410, 100, 20, hwnd, NULL, hInstance, NULL);

    g_hPrzyciskR = CreateWindowEx( WS_EX_WINDOWEDGE, "BUTTON", "Reset", WS_CHILD | WS_VISIBLE | WS_BORDER |BS_PUSHLIKE,
                                   10, 400, 80, 40, hwnd, NULL, hInstance, NULL );
    g_hPrzyciskL = CreateWindowEx( WS_EX_WINDOWEDGE, "BUTTON", "Losuj", WS_CHILD | WS_VISIBLE | WS_BORDER |BS_PUSHLIKE,
                                   10, 350, 80, 40, hwnd, NULL, hInstance, NULL );
    g_hPrzyciskO = CreateWindowEx( WS_EX_WINDOWEDGE, "BUTTON", "... ? ...", WS_CHILD | WS_VISIBLE | WS_BORDER | BS_PUSHLIKE,
                                   550, 350, 80, 40, hwnd, NULL, hInstance, NULL );
    g_hPrzyciskW = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "Wyjdz", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE,
                                   550, 400, 80, 40, hwnd, NULL, hInstance, NULL );
    g_hPrzyciskS = CreateWindowEx( WS_EX_CLIENTEDGE, "BUTTON", "start-stop", WS_CHILD | WS_VISIBLE | BS_PUSHLIKE,
                                   360, 150, 80, 40, hwnd, NULL, hInstance, NULL );

    g_hPrzyciskILE = CreateWindowEx( 0, "BUTTON", "ILE LOSOWAN", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                                     160, 0, 170, 90, hwnd, NULL, hInstance, NULL );
    hText = CreateWindowEx (WS_EX_CLIENTEDGE, "EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 170, 40, 75, 27,       //okno textowe
                            hwnd, NULL, hInstance, NULL);
    SendMessage (hText, EM_LIMITTEXT, 7, 0);                               //ograniczenie do x znakow w polu
    SetWindowText (hText, "1");
    //HWND hCombo = CreateWindowEx(WS_EX_CLIENTEDGE, "COMBOBOX", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWNLIST,   //lista rozwijalna
    // 230, 40, 100, 100, hwnd, NULL, hInstance, NULL);
    // SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"10");
    //  SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"100");
    // SendMessage(hCombo, CB_ADDSTRING, 0, (LPARAM)"1000");

   // g_hPrzyciskAUTOR = CreateWindowEx( 0, "BUTTON", "AUTOR", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
    //                                        500, 10, 60, 80, hwnd, NULL, hInstance, NULL );

    g_hPrzyciskLICZNIK = CreateWindowEx( 0, "BUTTON", "LICZNIK", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                              350, 0, 110, 90, hwnd, NULL, hInstance, NULL );
    hOknoLK = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 360, 30, 90, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoLK,"0");

    g_hPrzyciskLICZNIK2 = CreateWindowEx( 0, "BUTTON", "$", WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
                              470, 0, 105, 90, hwnd, NULL, hInstance, NULL );
    hOknoLK2 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 480, 68, 90, 20, hwnd, NULL, hInstance, NULL);
    hOknoLK3 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 480, 33, 90, 20, hwnd, NULL, hInstance, NULL);
    hOknoLK4 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 480, 15, 90, 20, hwnd, NULL, hInstance, NULL);
    hOknoLK5 = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |
                             SS_LEFT, 480, 50, 90, 20, hwnd, NULL, hInstance, NULL);
    SetWindowTextA(hOknoLK2,"0");
    SetWindowTextA(hOknoLK3,"0");
    SetWindowTextA(hOknoLK4,"koszt");
    SetWindowTextA(hOknoLK5,"wygrana");


    hbmObraz = (HBITMAP) LoadBitmap (hInstance, MAKEINTRESOURCE(LOGO));

    // HWND hStatic = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |                 //napis statyczny
    // SS_LEFT, 20, 170, 200, 20, hwnd, NULL, hInstance, NULL);
    // SetWindowText (hStatic, "Wpisz lub wybierz z listy..");

    // HWND hStaticIcon = CreateWindowEx(0, "STATIC", NULL, WS_CHILD | WS_VISIBLE |         //ikona lub bitmapa statyczna
    //  SS_ICON, 50, 50, 48, 48, hwnd, NULL, hInstance, NULL);
    // SendMessage(hStaticIcon, STM_SETICON, (WPARAM)LoadIcon(NULL, IDI_APPLICATION), 0);

    ShowWindow( hwnd, nCmdShow ); // Pokaz okienko...
    UpdateWindow( hwnd );

    while( GetMessage( & Komunikat, NULL, 0, 0 ) )       // Petla komunikatów
    {
        TranslateMessage( & Komunikat );
        DispatchMessage( & Komunikat );
    }
    return Komunikat.wParam;
}

LRESULT CALLBACK WndProc( HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam )      //obsluga zdarzen
{
    COLORREF clr,clr1;
    switch( msg )
    {
    case WM_CLOSE:
        DestroyWindow( hwnd );
        break;

    case WM_DESTROY:
        PostQuitMessage( 0 );
        break;

    default:
        return DefWindowProc( hwnd, msg, wParam, lParam );

       case WM_CTLCOLOREDIT:
       case WM_CTLCOLORSTATIC:
        {
         HWND hCtl = (HWND) lParam;
         HDC hDC = (HDC) wParam;

         if (hCtl == hOknoLK)
        {
         SetBkMode (hDC, TRANSPARENT);
         //SetTextColor (hDC, RGB (0, 0, 0));
         return (LRESULT) hBrush2;
        }

        if (hCtl == hOknoL1){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoL2){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoL3){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoL4){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoL5){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoL6){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}

        if (hCtl == hOknoW){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}

        if (hCtl == hOknoS1){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoS2){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoS3){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoS4){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoS5){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoS6){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}

        if (hCtl == hOknoP1){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoP2){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoP3){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoP4){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoP5){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}

        if (hCtl == hOkno[0]){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOkno[1]){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOkno[2]){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOkno[3]){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOkno[4]){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOkno[5]){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}

        if (hCtl == hOknoP){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}

        if (hCtl == hOknoT1){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT2){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT3){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT4){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT5){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT6){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT7){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT8){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT9){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT10){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hOknoT11){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}

        if (hCtl == hStatic1){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic2){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic3){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic4){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic5){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic6){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic7){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic8){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic9){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic10){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}
        if (hCtl == hStatic11){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}

        if (hCtl == g_hPrzyciskLICZBY){SetBkMode (hDC, TRANSPARENT);return (LRESULT) hBrush2;}

        if (hCtl == g_hPrzyciskILE)
        {
          SetBkMode (hDC, TRANSPARENT);
         if (IsWindowEnabled (hCtl))
             SetTextColor (hDC, RGB (0, 0, 0));
         else
             SetTextColor (hDC, RGB (128, 128, 128)); // szary
         return (LRESULT) hBrush2;
       }

       if (hCtl == OknoRadio)
       {
         SetBkMode (hDC, TRANSPARENT);
         if (IsWindowEnabled (hCtl))
             SetTextColor (hDC, RGB (0, 0, 0));
         else
             SetTextColor (hDC, RGB (128, 128, 128)); // szary
         return (LRESULT) hBrush2;
       }

       if (hCtl == g_hPrzyciskLICZNIK)
       {
         SetBkMode (hDC, TRANSPARENT);
         if (IsWindowEnabled (hCtl))
             SetTextColor (hDC, RGB (0, 0, 0));
         else
             SetTextColor (hDC, RGB (128, 128, 128)); // szary
         return (LRESULT) hBrush2;
       }

       if (hCtl == g_hPrzyciskLICZNIK2)
       {
         SetBkMode (hDC, TRANSPARENT);
         if (IsWindowEnabled (hCtl))
             SetTextColor (hDC, RGB (0, 0, 0));
         else
             SetTextColor (hDC, RGB (128, 128, 128)); // szary
         return (LRESULT) hBrush2;
       }

       if (hCtl == g_hPrzyciskAUTOR)
       {
         SetBkMode (hDC, TRANSPARENT);
         if (IsWindowEnabled (hCtl))
             SetTextColor (hDC, RGB (0, 0, 0));
         else
             SetTextColor (hDC, RGB (128, 128, 128)); // szary
         return (LRESULT) hBrush2;
       }

      if (hCtl == g_hPrzyciskSZANS)
       {
         SetBkMode (hDC, TRANSPARENT);
         if (IsWindowEnabled (hCtl))
             SetTextColor (hDC, RGB (0, 0, 0));
         else
             SetTextColor (hDC, RGB (128, 128, 128)); // szary
         return (LRESULT) hBrush2;
       }

      if (hCtl == g_hPrzyciskTRAF)
       {
         SetBkMode (hDC, TRANSPARENT);
         if (IsWindowEnabled (hCtl))
             SetTextColor (hDC, RGB (0, 0, 0));
         else
             SetTextColor (hDC, RGB (128, 128, 128)); // szary
         return (LRESULT) hBrush2;
       }

        }
       break;


    case WM_CREATE:
      hProgressBar = CreateWindowEx (0,PROGRESS_CLASS,NULL,WS_CHILD | WS_VISIBLE,10, 265, 550, 10, hwnd, (HMENU)200, hInstance, NULL);
      SendMessage(hProgressBar, PBM_SETRANGE, 0, (LPARAM)MAKELONG(0,100));
      SendMessage(hProgressBar, PBM_SETPOS, (WPARAM)0, 0); // ustawia wartosc na 17
      SendMessage(hProgressBar, PBM_SETSTEP, (WPARAM)1, 0);
      clr=RGB(0,0,0);                                 //kolor paska
      SendMessage(hProgressBar,PBM_SETBARCOLOR,0,(LPARAM)clr);
      clr1=RGB(200,200,200);                              //kolor tla
      SendMessage(hProgressBar,PBM_SETBKCOLOR,0,(LPARAM)clr1);
     // hButton=CreateWindowEx(0,WC_BUTTON,"Krok",WS_VISIBLE|WS_CHILD,20,50,300,30,hwnd,(HMENU)1,hInstance,0);
      break;

    case WM_COMMAND:                           //komunikat do konkretnego przycisku

    {
        if ( (HWND) lParam == hRadio1 )
        {
            BOOL bChecked1 = (IsDlgButtonChecked (hwnd, ID_RADIO1) == BST_CHECKED);       //sprawdzam stan przycisku
            resetuj();
            if(bChecked1)
            {
                gra = 35;
                liczby = 5;
                DestroyWindow(g_hPrzycisk[35]);
                DestroyWindow(g_hPrzycisk[36]);
                DestroyWindow(g_hPrzycisk[37]);
                DestroyWindow(g_hPrzycisk[38]);
                DestroyWindow(g_hPrzycisk[39]);
                DestroyWindow(g_hPrzycisk[40]);
                DestroyWindow(g_hPrzycisk[41]);
                DestroyWindow(g_hPrzycisk[42]);
                DestroyWindow(g_hPrzycisk[43]);
                DestroyWindow(g_hPrzycisk[44]);
                DestroyWindow(g_hPrzycisk[45]);
                DestroyWindow(g_hPrzycisk[46]);
                DestroyWindow(g_hPrzycisk[47]);
                DestroyWindow(g_hPrzycisk[48]);

                g_hPrzyciskP[0] = CreateWindowEx( 0, "BUTTON", "1", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      20, 220, 20, 20, hwnd, (HMENU)ID_PRZYCISK(50), hInstance, NULL );
                g_hPrzyciskP[1] = CreateWindowEx( 0, "BUTTON", "2", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      40, 220, 20, 20, hwnd, (HMENU)ID_PRZYCISK(51), hInstance, NULL );
                g_hPrzyciskP[2] = CreateWindowEx( 0, "BUTTON", "3", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      60, 220, 20, 20, hwnd, (HMENU)ID_PRZYCISK(52), hInstance, NULL );
                g_hPrzyciskP[3] = CreateWindowEx( 0, "BUTTON", "4", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                      80, 220, 20, 20, hwnd, (HMENU)ID_PRZYCISK(53), hInstance, NULL );

                SetWindowTextA(hOknoS1,"1 : 2.5             1 : 7.5");
                SetWindowTextA(hOknoS2,"1 : 11              1 : 32");
                SetWindowTextA(hOknoS3,"1 : 100            1 : 299");
                SetWindowTextA(hOknoS4,"1 : 2 886         1 : 8 657");
                SetWindowTextA(hOknoS5,"1 : 432 843     1 : 1 298 528");
                SetWindowText (hStatic7, "1+1: ");
                SetWindowText (hStatic8, "2+1: ");
                SetWindowText (hStatic9, "3+1: ");
                SetWindowText (hStatic10, "4+1: ");
                SetWindowText (hStatic11, "5+1: ");
                SetWindowTextA(hOknoS6,"");
                SetWindowText (hStatic6, "");
                SetWindowTextA(hOknoL6,"");
                SetWindowTextA(hOkno[5],"");
                SetWindowTextA(hOknoP,"0");
                SetWindowTextA(hOknoT7,"0");
                SetWindowTextA(hOknoT8,"0");
                SetWindowTextA(hOknoT9,"0");
                SetWindowTextA(hOknoT10,"0");
                SetWindowTextA(hOknoT11,"0");
            }

        }

        if ( (HWND) lParam == hRadio2 )
        {
            BOOL bChecked2 = (IsDlgButtonChecked (hwnd, ID_RADIO2) == BST_CHECKED);         //sprawdzam stan przycisku
            resetuj();
            if(bChecked2)
            {
                gra = 42;
                liczby = 5;
                DestroyWindow(g_hPrzycisk[35]);
                DestroyWindow(g_hPrzycisk[36]);
                DestroyWindow(g_hPrzycisk[37]);
                DestroyWindow(g_hPrzycisk[38]);
                DestroyWindow(g_hPrzycisk[39]);
                DestroyWindow(g_hPrzycisk[40]);
                DestroyWindow(g_hPrzycisk[41]);
                DestroyWindow(g_hPrzycisk[42]);
                DestroyWindow(g_hPrzycisk[43]);
                DestroyWindow(g_hPrzycisk[44]);
                DestroyWindow(g_hPrzycisk[45]);
                DestroyWindow(g_hPrzycisk[46]);
                DestroyWindow(g_hPrzycisk[47]);
                DestroyWindow(g_hPrzycisk[48]);

                DestroyWindow(g_hPrzyciskP[0]);
                DestroyWindow(g_hPrzyciskP[1]);
                DestroyWindow(g_hPrzyciskP[2]);
                DestroyWindow(g_hPrzyciskP[3]);

                g_hPrzycisk[35] = CreateWindowEx( 0, "BUTTON", "36", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  120, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(36), wc.hInstance, NULL );
                g_hPrzycisk[36] = CreateWindowEx( 0, "BUTTON", "37", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  140, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(37), wc.hInstance, NULL );
                g_hPrzycisk[37] = CreateWindowEx( 0, "BUTTON", "38", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  160, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(38), wc.hInstance, NULL );
                g_hPrzycisk[38] = CreateWindowEx( 0, "BUTTON", "39", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  180, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(39), wc.hInstance, NULL );
                g_hPrzycisk[39] = CreateWindowEx( 0, "BUTTON", "40", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  200, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(40), wc.hInstance, NULL );
                g_hPrzycisk[40] = CreateWindowEx( 0, "BUTTON", "41", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  20, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(41), wc.hInstance, NULL );
                g_hPrzycisk[41] = CreateWindowEx( 0, "BUTTON", "42", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  40, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(42), wc.hInstance, NULL );
                SetWindowTextA(hOknoS1,"1 : 2.5");
                SetWindowTextA(hOknoS2,"1 : 11");
                SetWindowTextA(hOknoS3,"1 : 127");
                SetWindowTextA(hOknoS4,"1 : 4 598");
                SetWindowTextA(hOknoS5,"1 : 850 668");
                SetWindowText (hStatic7, "");
                SetWindowText (hStatic8, "");
                SetWindowText (hStatic9, "");
                SetWindowText (hStatic10, "");
                SetWindowText (hStatic11, "");
                SetWindowTextA(hOknoS6,"");
                SetWindowText (hStatic6, "");
                SetWindowTextA(hOknoL6,"");
                SetWindowTextA(hOkno[5],"");
                SetWindowTextA(hOknoP,"");
                SetWindowTextA(hOknoT7,"");
                SetWindowTextA(hOknoT8,"");
                SetWindowTextA(hOknoT9,"");
                SetWindowTextA(hOknoT10,"");
                SetWindowTextA(hOknoT11,"");
            }
        }

         if ( (HWND) lParam == hRadio3 )
        {
            BOOL bChecked3 = (IsDlgButtonChecked (hwnd, ID_RADIO3) == BST_CHECKED);       //sprawdzam stan przycisku
            resetuj();
            if(bChecked3)
            {
                gra = 49;
                liczby = 6;
                DestroyWindow(g_hPrzycisk[35]);
                DestroyWindow(g_hPrzycisk[36]);
                DestroyWindow(g_hPrzycisk[37]);
                DestroyWindow(g_hPrzycisk[38]);
                DestroyWindow(g_hPrzycisk[39]);
                DestroyWindow(g_hPrzycisk[40]);
                DestroyWindow(g_hPrzycisk[41]);

                DestroyWindow(g_hPrzyciskP[0]);
                DestroyWindow(g_hPrzyciskP[1]);
                DestroyWindow(g_hPrzyciskP[2]);
                DestroyWindow(g_hPrzyciskP[3]);

                g_hPrzycisk[35] = CreateWindowEx( 0, "BUTTON", "36", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  120, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(36), wc.hInstance, NULL );
                g_hPrzycisk[36] = CreateWindowEx( 0, "BUTTON", "37", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  140, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(37), wc.hInstance, NULL );
                g_hPrzycisk[37] = CreateWindowEx( 0, "BUTTON", "38", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  160, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(38), wc.hInstance, NULL );
                g_hPrzycisk[38] = CreateWindowEx( 0, "BUTTON", "39", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  180, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(39), wc.hInstance, NULL );
                g_hPrzycisk[39] = CreateWindowEx( 0, "BUTTON", "40", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  200, 190, 20, 20, hwnd, (HMENU)ID_PRZYCISK(40), wc.hInstance, NULL );
                g_hPrzycisk[40] = CreateWindowEx( 0, "BUTTON", "41", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  20, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(41), wc.hInstance, NULL );
                g_hPrzycisk[41] = CreateWindowEx( 0, "BUTTON", "42", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  40, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(42), wc.hInstance, NULL );
                g_hPrzycisk[42] = CreateWindowEx( 0, "BUTTON", "43", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  60, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(43), wc.hInstance, NULL );
                g_hPrzycisk[43] = CreateWindowEx( 0, "BUTTON", "44", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  80, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(44), wc.hInstance, NULL );
                g_hPrzycisk[44] = CreateWindowEx( 0, "BUTTON", "45", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  100, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(45), wc.hInstance, NULL );
                g_hPrzycisk[45] = CreateWindowEx( 0, "BUTTON", "46", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  120, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(46), wc.hInstance, NULL );
                g_hPrzycisk[46] = CreateWindowEx( 0, "BUTTON", "47", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  140, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(47), wc.hInstance, NULL );
                g_hPrzycisk[47] = CreateWindowEx( 0, "BUTTON", "48", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  160, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(48), wc.hInstance, NULL );
                g_hPrzycisk[48] = CreateWindowEx( 0, "BUTTON", "49", WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_PUSHLIKE,
                                                  180, 210, 20, 20, hwnd, (HMENU)ID_PRZYCISK(49), wc.hInstance, NULL );
                SetWindowTextA(hOknoS1,"1 : 2.4");
                SetWindowTextA(hOknoS2,"1 : 7.5");
                SetWindowTextA(hOknoS3,"1 : 57");
                SetWindowTextA(hOknoS4,"1 : 1 032");
                SetWindowTextA(hOknoS5,"1 : 54 201");
                SetWindowTextA(hOknoS6,"1 : 13 983 816");
                SetWindowText (hStatic7, "");
                SetWindowText (hStatic8, "");
                SetWindowText (hStatic9, "");
                SetWindowText (hStatic10, "");
                SetWindowText (hStatic11, "");
                SetWindowText (hStatic6, "6: ");
                SetWindowTextA(hOknoL6,"0");
                SetWindowTextA(hOkno[5],"0");
                SetWindowTextA(hOknoP,"");
                SetWindowTextA(hOknoT6,"0");
                SetWindowTextA(hOknoT7,"");
                SetWindowTextA(hOknoT8,"");
                SetWindowTextA(hOknoT9,"");
                SetWindowTextA(hOknoT10,"");
                SetWindowTextA(hOknoT11,"");
            }
        }

        for(int a=0; a<gra; a++)          //ilosc przyciskow
        {
            int suma=0;
            if( (HWND) lParam == g_hPrzycisk[a] )
            {

                for (int y=0; y<liczby; y++)     //sprawdzam czy jest wolne miejsce w tabeli czy_wolne_typy
                {
                    BOOL bChecked = (IsDlgButtonChecked (hwnd, ID_PRZYCISK(a+1)) == BST_CHECKED);       //sprawdzam stan przycisku
                    if(bChecked)                   //jesli wciskam
                    {
                        if(czy_wolne_typy[y] == 0)
                        {
                            typy[y]=a+1;
                            czy_wolne_typy[y]=1;            //zajmuje miejsce
                            sprintf(text,"%i",typy[y]);
                            SetWindowTextA(hOkno[y],text);
                            break;                    //zatrzymanie petli for
                        }
                        suma += czy_wolne_typy[y];            //sprawdzenie czy mozna wcisnac wiecej przyciskow
                        if(suma>=liczby)
                        {
                            CheckDlgButton(hwnd, ID_PRZYCISK(a+1), BST_UNCHECKED);
                        }
                    }
                    else                                //jesli wyciskam
                    {
                        for(int z=0; z<liczby; z++)
                        {
                            if(typy[z]==(a+1))
                            {
                                typy[z]=0;
                                czy_wolne_typy[z]=0;            //zwalniam miejsce
                                sprintf(text,"%i",typy[z]);
                                SetWindowTextA(hOkno[z],text);
                                break;                    //zatrzymanie petli for
                            }
                        }
                    }
                }
            }
        }

        for(int a=0; a<gra2; a++)          //ilosc przyciskow
        {
           // int suma=0;
            if( (HWND) lParam == g_hPrzyciskP[a] )
            {

                for (int y=0; y<liczby2; y++)     //sprawdzam czy jest wolne miejsce w tabeli czy_wolne_typy
                {
                    BOOL bChecked = (IsDlgButtonChecked (hwnd, ID_PRZYCISK(a+50)) == BST_CHECKED);       //sprawdzam stan przycisku
                    if(bChecked)                   //jesli wciskam
                    {
                        if(czy_wolne_typy2 == 0)
                        {
                            typy2=a+1;
                            czy_wolne_typy2=1;            //zajmuje miejsce
                            sprintf(text,"%i",typy2);
                            SetWindowTextA(hOknoP,text);
                            break;                    //zatrzymanie petli for
                        }
                      //  suma += czy_wolne_typy2;            //sprawdzenie czy mozna wcisnac wiecej przyciskow
                        if(czy_wolne_typy2>=liczby2)
                        {
                            CheckDlgButton(hwnd, ID_PRZYCISK(a+50), BST_UNCHECKED);
                        }
                    }
                    else                                //jesli wyciskam
                    {
                        for(int z=0; z<liczby2; z++)
                        {
                            if(typy2==(a+1))
                            {
                                typy2=0;
                                czy_wolne_typy2=0;            //zwalniam miejsce
                                sprintf(text,"%i",typy2);
                                SetWindowTextA(hOknoP,text);
                                break;                    //zatrzymanie petli for
                            }
                        }
                    }
                }
            }
        }

        if ( (HWND) lParam == g_hPrzyciskL )         //przycisk LOSUJ
        {
            SendMessage(hProgressBar, PBM_SETPOS, (WPARAM)0, 0); // ustawia wartosc na 0, cofam scrollbar
            p = 0;
            GetWindowText (hText, ile_losowan_bufor, 8);
            //SetWindowTextA(hOkno5,ile_losowan_bufor);
            ile_losowan = atoi(ile_losowan_bufor);
            licznik_losowan = licznik_losowan+ile_losowan;
            for(int z=0; z<ile_losowan; z++)
            {
                licznik=0;
                for(int i=0; i<liczby; i++)
                {
                    losowe[i] = wylosuj();
                    losowa = wylosuj2();
                    if(i>0)
                        for(int j=1; j<(i+1); j++)           //sprawdzam zeby nie bylo powtorzen
                        {
                            while (losowe[i] == losowe[i-j])
                            {
                                losowe[i]=wylosuj();
                            }
                        }
                    cout << losowe[i] << " ";
                }

                if (ile_losowan<=100)
                {
                 SendMessage(hProgressBar, PBM_DELTAPOS, (WPARAM)100, 0); // zwieksza wartosc o 100
                }
               else
               {
                if ((z+1) >= (ile_losowan*procent[p]))             //warunek do przesuniecia scrollbara
                {
                 SendMessage(hProgressBar,PBM_STEPIT,0,0);
                 p++;
                }
               }

                cout << endl;
                for(int x=0; x<liczby; x++)              //sprawdzam trafienia
                {
                    for(int y=0; y<liczby; y++)
                    {
                        if(losowe[x] == typy[y])
                            licznik++;
                    }
                }
                for(int z=0; z<liczby; z++)                 //wpisuje ewentualne trafienia do tablicy trafien
                {
                    if(licznik == (z+1))
                       {
                        if (losowa == typy2)
                              trafieniaP[z]++;
                        else
                           trafienia[z]++;
                       }
                }


            }

            if (gra == 35)
                        {
                         licznik_wygranej = (trafienia[1]*5);       //a tu wpsiuje wygrane
                         licznik_wygranej += (trafienia[2]*25);
                         licznik_wygranej += (trafienia[3]*200);
                         licznik_wygranej += (trafienia[4]*25000);
                              licznik_wygranej += (trafieniaP[1]*10);       //a tu wpsiuje wygrane z P
                              licznik_wygranej += (trafieniaP[2]*80);
                              licznik_wygranej += (trafieniaP[3]*1000);
                              licznik_wygranej += (trafieniaP[4]*1200000);
                              licznik_kosztow = licznik_losowan * 5;
                        }
             if (gra == 42)
                        {
                         licznik_wygranej = (trafienia[2]*24);       //a tu wpsiuje wygrane
                         licznik_wygranej += (trafienia[3]*591);
                         licznik_wygranej += (trafienia[4]*197443);
                         licznik_kosztow = licznik_losowan * 1.25;
                        }
             if (gra == 49)
                        {
                         licznik_wygranej = (trafienia[2]*24);       //a tu wpsiuje wygrane
                         licznik_wygranej += (trafienia[3]*174);
                         licznik_wygranej += (trafienia[4]*5382);
                         licznik_wygranej += (trafienia[5]*4589500);
                         licznik_kosztow = licznik_losowan * 3;
                        }


            sprintf(text,"%i",losowe[0]);           //wyswietlanie wyniku do okien
            SetWindowTextA(hOknoL1,text);
            sprintf(text,"%i",losowe[1]);
            SetWindowTextA(hOknoL2,text);
            sprintf(text,"%i",losowe[2]);
            SetWindowTextA(hOknoL3,text);
            sprintf(text,"%i",losowe[3]);
            SetWindowTextA(hOknoL4,text);
            sprintf(text,"%i",losowe[4]);
            SetWindowTextA(hOknoL5,text);
            sprintf(text,"%i",losowa);           //wyswietlanie wyniku P do okien
            SetWindowTextA(hOknoW,text);
            BOOL bChecked = (IsDlgButtonChecked (hwnd, ID_RADIO3) == BST_CHECKED);       //sprawdzam stan przycisku
            if(bChecked)
            {
                sprintf(text,"%i",losowe[5]);
                SetWindowTextA(hOknoL6,text);
            }

            sprintf(text,"%i",trafienia[0]);           //wyswietlanie trafien do okien
            SetWindowTextA(hOknoT1,text);
            sprintf(text,"%i",trafienia[1]);
            SetWindowTextA(hOknoT2,text);
            sprintf(text,"%i",trafienia[2]);
            SetWindowTextA(hOknoT3,text);
            sprintf(text,"%i",trafienia[3]);
            SetWindowTextA(hOknoT4,text);
            sprintf(text,"%i",trafienia[4]);
            SetWindowTextA(hOknoT5,text);
            if (gra == 35)
           {
            sprintf(text,"%i",trafieniaP[0]);          //wyswietlanie trafien P do okien
            SetWindowTextA(hOknoT7,text);
            sprintf(text,"%i",trafieniaP[1]);
            SetWindowTextA(hOknoT8,text);
            sprintf(text,"%i",trafieniaP[2]);
            SetWindowTextA(hOknoT9,text);
            sprintf(text,"%i",trafieniaP[3]);
            SetWindowTextA(hOknoT10,text);
            sprintf(text,"%i",trafieniaP[4]);
            SetWindowTextA(hOknoT11,text);
           }
            BOOL bChecked2 = (IsDlgButtonChecked (hwnd, ID_RADIO3) == BST_CHECKED);       //sprawdzam stan przycisku
            if(bChecked2)
            {
                sprintf(text,"%i",trafienia[5]);
                SetWindowTextA(hOknoT6,text);
            }
            sprintf(text,"%i",licznik_losowan);                  //licznik losowan
            SetWindowTextA(hOknoLK,text);
            sprintf(text,"%i",licznik_wygranej);                  //licznik wygranej
            SetWindowTextA(hOknoLK2,text);
            sprintf(text,"%i",licznik_kosztow);                  //licznik wygranej
            SetWindowTextA(hOknoLK3,text);
        }

        if ( (HWND) lParam == g_hPrzyciskS )            //przycisk start-stop
        {
           do
            //StoperStart();
           // for(int i=0; i < 100000; i++)
            {
             sprintf(text,"%i",(clock())/100 );
             SetWindowTextA(hStoper1,text);
            }while ( (HWND) lParam != g_hPrzyciskS );
        }

        if ( (HWND) lParam == g_hPrzyciskR )            //przycisk RESET
        {
            int b=0;
            for(int a=0; a<6; a++)
            {
                b=typy[a];
                CheckDlgButton(hwnd, ID_PRZYCISK(b), BST_UNCHECKED);        //zmieniam stan przycisku
                typy[a]=0;
                czy_wolne_typy[a]=0;
            }

          //  b=typy[a];
            CheckDlgButton(hwnd, ID_PRZYCISK(typy2+49), BST_UNCHECKED);        //zmieniam stan przycisku P
            typy2=0;
            czy_wolne_typy2=0;

            licznik_losowan = 0;
            licznik_wygranej = 0;
            for(int i=0; i<6; i++)
            {
                trafienia[i]=0;
            }
             for(int i=0; i<5; i++)
            {
                trafieniaP[i]=0;
            }
            for(int j=0; j<6; j++)
            {
                losowe[j]=0;
            }
            losowa = 0;

            sprintf(text,"%i",typy[0]);
            SetWindowTextA(hOkno[0],text);
            sprintf(text,"%i",typy[1]);
            SetWindowTextA(hOkno[1],text);
            sprintf(text,"%i",typy[2]);
            SetWindowTextA(hOkno[2],text);
            sprintf(text,"%i",typy[3]);
            SetWindowTextA(hOkno[3],text);
            sprintf(text,"%i",typy[4]);
            SetWindowTextA(hOkno[4],text);
            sprintf(text,"%i",typy2);
            SetWindowTextA(hOknoP,text);
            BOOL bChecked3 = (IsDlgButtonChecked (hwnd, ID_RADIO3) == BST_CHECKED);       //sprawdzam stan przycisku
            if(bChecked3)
            {
                sprintf(text,"%i",typy[5]);
                SetWindowTextA(hOkno[5],text);
            }
            sprintf(text,"%i",losowe[0]);           //wyswietlanie wyniku do okien
            SetWindowTextA(hOknoL1,text);
            sprintf(text,"%i",losowe[1]);
            SetWindowTextA(hOknoL2,text);
            sprintf(text,"%i",losowe[2]);
            SetWindowTextA(hOknoL3,text);
            sprintf(text,"%i",losowe[3]);
            SetWindowTextA(hOknoL4,text);
            sprintf(text,"%i",losowe[4]);
            SetWindowTextA(hOknoL5,text);
            sprintf(text,"%i",losowa);           //wyswietlanie wyniku P do okien
            SetWindowTextA(hOknoW,text);
            BOOL bChecked = (IsDlgButtonChecked (hwnd, ID_RADIO3) == BST_CHECKED);       //sprawdzam stan przycisku
            if(bChecked)
            {
                sprintf(text,"%i",losowe[5]);
                SetWindowTextA(hOknoL6,text);
            }
            sprintf(text,"%i",trafienia[0]);           //wyswietlanie trafien do okien
            SetWindowTextA(hOknoT1,text);
            sprintf(text,"%i",trafienia[1]);
            SetWindowTextA(hOknoT2,text);
            sprintf(text,"%i",trafienia[2]);
            SetWindowTextA(hOknoT3,text);
            sprintf(text,"%i",trafienia[3]);
            SetWindowTextA(hOknoT4,text);
            sprintf(text,"%i",trafienia[4]);
            SetWindowTextA(hOknoT5,text);
            sprintf(text,"%i",trafieniaP[0]);
            SetWindowTextA(hOknoT7,text);
            sprintf(text,"%i",trafieniaP[1]);
            SetWindowTextA(hOknoT8,text);
            sprintf(text,"%i",trafieniaP[2]);
            SetWindowTextA(hOknoT9,text);
            sprintf(text,"%i",trafieniaP[3]);
            SetWindowTextA(hOknoT10,text);
            sprintf(text,"%i",trafieniaP[4]);
            SetWindowTextA(hOknoT11,text);
            BOOL bChecked2 = (IsDlgButtonChecked (hwnd, ID_RADIO3) == BST_CHECKED);       //sprawdzam stan przycisku
            if(bChecked2)
            {
                sprintf(text,"%i",trafienia[5]);
                SetWindowTextA(hOknoT6,text);
            }

            sprintf(text,"%i",licznik_losowan);                  //licznik
            SetWindowTextA(hOknoLK,text);
            SetWindowText (hText, "1");

            sprintf(text,"%i",licznik_wygranej);                  //licznik
            SetWindowTextA(hOknoLK2,text);
            SetWindowText (hText, "1");

            sprintf(text,"%i",licznik_wygranej);                  //licznik
            SetWindowTextA(hOknoLK3,text);
            SetWindowText (hText, "1");

            SendMessage(hProgressBar, PBM_SETPOS, (WPARAM)0, 0); // ustawia wartosc na 0, cofam scrollbar

        }

        if ( (HWND) lParam == g_hPrzyciskW )           //przycisk WYJSCIE
            DestroyWindow( hwnd );

      if ( (HWND) lParam == g_hPrzyciskO )         //przycisk 'O..'
        {
          ret = DialogBox (GetModuleHandle(NULL), MAKEINTRESOURCE(MOJDIALOG), hwnd, DlgProc);

          //CoolMsgBox (hwnd, "Wersja: 1.0                                  Autor ", "O..", MB_ICONINFORMATION);

        }
    }
        break;

  /*  case WM_LBUTTONDOWN:              //reakcja na przysick myszki - postawienie kropki
    {
        HDC hdc = GetDC (hwnd);
        Ellipse (hdc, LOWORD (lParam) - 3, HIWORD (lParam) - 3, LOWORD (lParam) + 3, HIWORD (lParam) + 3);
        ReleaseDC (hwnd, hdc);
    }
    break;
    */

  /*  case WM_PAINT:                 //odswiezanie zawartosci okna
    {
        PAINTSTRUCT ps; // deklaracja struktury
        HDC hdc = BeginPaint (hwnd, &ps);

      //  hbmObraz = (HBITMAP) LoadImage (NULL, "marcin2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);   //poczatek wczytywania bitmapy z pliku
        hbmMaska = CreateBitmapMask (hbmObraz, RGB(0, 255, 0));
        //hbmMaska2 = CreateBitmapMask (hbmObraz2, RGB(0, 0, 255));                                 //wywolanie funkcji tworzenia maski

        hdc = GetDC (hwnd);
        HDC hdcNowy = CreateCompatibleDC (hdc);
        BITMAP bmInfo;
       // HDC hdcNowy2 = CreateCompatibleDC (hdc);
     //   BITMAP bmInfo2;

        GetObject (hbmObraz, sizeof(bmInfo), &bmInfo);
        hbmOld = (HBITMAP) SelectObject (hdcNowy, hbmMaska);
       // GetObject (hbmObraz2, sizeof(bmInfo2), &bmInfo2);
    //    hbmOld2 = (HBITMAP) SelectObject (hdcNowy2, hbmMaska2);

       // BitBlt (hdc, 510, 230, bmInfo.bmWidth, bmInfo.bmHeight, hdcNowy, 0, 0, SRCAND);
       // SelectObject (hdcNowy, hbmObraz);
       // BitBlt (hdc, 510, 230, bmInfo.bmWidth, bmInfo.bmHeight, hdcNowy, 0, 0, SRCPAINT);
        BitBlt (hdc, 421, 2, bmInfo.bmWidth, bmInfo.bmHeight, hdcNowy, 0, 0, SRCAND);
        SelectObject (hdcNowy, hbmObraz);
        BitBlt (hdc, 421, 2, bmInfo.bmWidth, bmInfo.bmHeight, hdcNowy, 0, 0, SRCPAINT);
        //sprintf(text,"%i",typy[0]);
        //TextOut(hdc, 450, 350, text, 2);

        ReleaseDC (hwnd, hdc);
        SelectObject (hdcNowy, hbmOld);
        DeleteDC (hdcNowy);
        DeleteObject (hbmMaska);
        DeleteObject (hbmObraz);

     //   SelectObject (hdcNowy2, hbmOld2);
      //  DeleteDC (hdcNowy2);
      //  DeleteObject (hbmMaska2);
      //  DeleteObject (hbmObraz2);
        EndPaint (hwnd, &ps); // zwalniamy hdc
    }*/
    break;
    }

    return 0;
}

HBITMAP CreateBitmapMask (HBITMAP hbmColour, COLORREF crTransparent)
{
    HDC hdcMem, hdcMem2;
    HBITMAP hbmMask, hbmOld, hbmOld2;
    BITMAP bm;

    GetObject (hbmColour, sizeof(BITMAP), &bm);
    hbmMask = CreateBitmap (bm.bmWidth, bm.bmHeight, 1, 1, NULL);

    hdcMem = CreateCompatibleDC (NULL);
    hdcMem2 = CreateCompatibleDC (NULL);

    hbmOld = (HBITMAP) SelectObject (hdcMem, hbmColour);
    hbmOld2 = (HBITMAP) SelectObject (hdcMem2, hbmMask);

    SetBkColor (hdcMem, crTransparent);

    BitBlt (hdcMem2, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem, 0, 0, SRCCOPY);
    BitBlt (hdcMem, 0, 0, bm.bmWidth, bm.bmHeight, hdcMem2, 0, 0, SRCINVERT);

    SelectObject (hdcMem, hbmOld);
    SelectObject (hdcMem2, hbmOld2);
    DeleteDC (hdcMem);
    DeleteDC (hdcMem2);

    return hbmMask;
}

int wylosuj()
{
    return (( rand() % gra) + 1);
}

int wylosuj2()
{
    return (( rand() % 4) + 1);
}

char StoperStart ()
{
   char pokaz = clock();
   return pokaz;
}

void resetuj()
{
    licznik_losowan = 0;
    sprintf(text,"%i",licznik_losowan);                  //reset licznik losowan
    SetWindowTextA(hOknoLK,text);
    SetWindowText (hText, "1");

    licznik_wygranej = 0;
    sprintf(text,"%i",licznik_wygranej);                  //reset licznik wygranej
    SetWindowTextA(hOknoLK2,text);
    SetWindowText (hText, "1");

    licznik_kosztow = 0;
    sprintf(text,"%i",licznik_kosztow);                  //reset licznik kosztow
    SetWindowTextA(hOknoLK3,text);
    SetWindowText (hText, "1");

    int b=0;
    for(int a=0; a<6; a++)
    {
        b=typy[a];
        CheckDlgButton(hwnd, ID_PRZYCISK(b), BST_UNCHECKED);        //zmieniam stan przycisku
        typy[a]=0;
        czy_wolne_typy[a]=0;
    }


        CheckDlgButton(hwnd, ID_PRZYCISK(typy2), BST_UNCHECKED);        //zmieniam stan przycisku
        typy2=0;
        czy_wolne_typy2=0;

    for(int i=0; i<6; i++)
    {
        trafienia[i]=0;
    }
    for(int j=0; j<6; j++)
    {
        losowe[j]=0;
    }
    sprintf(text,"%i",typy[0]);
    SetWindowTextA(hOkno[0],text);
    sprintf(text,"%i",typy[1]);
    SetWindowTextA(hOkno[1],text);
    sprintf(text,"%i",typy[2]);
    SetWindowTextA(hOkno[2],text);
    sprintf(text,"%i",typy[3]);
    SetWindowTextA(hOkno[3],text);
    sprintf(text,"%i",typy[4]);
    SetWindowTextA(hOkno[4],text);
    BOOL bChecked3 = (IsDlgButtonChecked (hwnd, ID_RADIO3) == BST_CHECKED);       //sprawdzam stan przycisku
    if(bChecked3)
    {
        sprintf(text,"%i",typy[5]);
        SetWindowTextA(hOkno[5],text);
    }
    sprintf(text,"%i",losowe[0]);           //wyswietlanie wyniku do okien
    SetWindowTextA(hOknoL1,text);
    sprintf(text,"%i",losowe[1]);
    SetWindowTextA(hOknoL2,text);
    sprintf(text,"%i",losowe[2]);
    SetWindowTextA(hOknoL3,text);
    sprintf(text,"%i",losowe[3]);
    SetWindowTextA(hOknoL4,text);
    sprintf(text,"%i",losowe[4]);
    SetWindowTextA(hOknoL5,text);
    BOOL bChecked = (IsDlgButtonChecked (hwnd, ID_RADIO3) == BST_CHECKED);       //sprawdzam stan przycisku
    if(bChecked)
    {
        sprintf(text,"%i",losowe[5]);
        SetWindowTextA(hOknoL6,text);
    }
    sprintf(text,"%i",trafienia[0]);           //wyswietlanie trafien do okien
    SetWindowTextA(hOknoT1,text);
    sprintf(text,"%i",trafienia[1]);
    SetWindowTextA(hOknoT2,text);
    sprintf(text,"%i",trafienia[2]);
    SetWindowTextA(hOknoT3,text);
    sprintf(text,"%i",trafienia[3]);
    SetWindowTextA(hOknoT4,text);
    sprintf(text,"%i",trafienia[4]);
    SetWindowTextA(hOknoT5,text);
    BOOL bChecked2 = (IsDlgButtonChecked (hwnd, ID_RADIO3) == BST_CHECKED);       //sprawdzam stan przycisku
    if(bChecked2)
    {
        sprintf(text,"%i",trafienia[5]);
        SetWindowTextA(hOknoT6,text);
    }

    SendMessage(hProgressBar, PBM_SETPOS, (WPARAM)0, 0); // ustawia wartosc na 0, cofam scrollbar
}

int CoolMsgBox (HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, UINT uType)
{
   g_hHook = NULL;
   g_hWndMsgBox = NULL;
   g_MsgBoxProc = NULL;

   HINSTANCE hInstance = GetModuleHandle (NULL);

   g_hHook = SetWindowsHookEx (WH_CBT, HookProc, hInstance, GetCurrentThreadId());

   int nRet = MessageBox (hWnd, lpText, lpCaption, uType);

   UnhookWindowsHookEx (g_hHook);

   return nRet;
}

LRESULT CALLBACK HookProc (int nCode, WPARAM wParam, LPARAM lParam)
{
   if (nCode < 0)
       return CallNextHookEx (g_hHook, nCode, wParam, lParam);

   switch (nCode)
   {
   case HCBT_CREATEWND:
   {
      LPCBT_CREATEWND lpCbtCreate = (LPCBT_CREATEWND) lParam;
      if (lpCbtCreate->lpcs->lpszClass == WC_DIALOG)
      {
          g_hWndMsgBox = (HWND) wParam;
      }
      else
      {
          if (g_MsgBoxProc == NULL)
              g_MsgBoxProc = (WNDPROC) SetWindowLongPtrA (g_hWndMsgBox, GWLP_WNDPROC, (LONG_PTR) CoolMsgBoxProc);
      }
   }
   break;
   case HCBT_DESTROYWND:
   {
       if ((HWND) wParam == g_hWndMsgBox)
           SetWindowLongPtr (g_hWndMsgBox, GWLP_WNDPROC, (LONG_PTR) g_MsgBoxProc);
   }
   }

   return 0;
}

LRESULT CALLBACK CoolMsgBoxProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
   switch (uMsg)
   {
   case WM_INITDIALOG:
      {
          HINSTANCE hInstance = GetModuleHandle (NULL);
          //HBITMAP hBitmap = (HBITMAP) LoadImage (hInstance, "logo2.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
          HBITMAP hBitmap = (HBITMAP) LoadBitmap (hInstance, MAKEINTRESOURCE(LOGO));
          g_hBrush = CreatePatternBrush (hBitmap);
          DeleteObject (hBitmap);
      }
      break;
   case WM_CTLCOLORDLG:
   case WM_CTLCOLORSTATIC:
      {
          HDC hDC = (HDC) wParam;
          SetBkMode (hDC, TRANSPARENT);
          SetTextColor (hDC, RGB (0, 128, 0));
          return (LRESULT) g_hBrush;
      }
      break;
   case WM_COMMAND:
      {
          DeleteObject (g_hBrush);
      }
      break;
   }

   return CallWindowProc (g_MsgBoxProc, hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK DlgProc (HWND hwnd, UINT Msg, WPARAM wParam, LPARAM lParam)           // Procedura dialogowa
{
 switch (Msg)
 {
  case WM_COMMAND:
  {
   switch (LOWORD(wParam))              // reakcja na przyciski
   {
    case IDOK: EndDialog (hwnd, IDOK); break;
    case IDCANCEL: EndDialog (hwnd, IDCANCEL); break;
   }
  }
  break;

  default: return FALSE;
 }

 return TRUE;
}

