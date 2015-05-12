
// CircleOnPlaneDlg.cpp : файл реализации
//

#include "stdafx.h"
#include "CircleOnPlane.h"
#include "CircleOnPlaneDlg.h"
#include "afxdialogex.h"
#include "cmath"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// диалоговое окно CCircleOnPlaneDlg



CCircleOnPlaneDlg::CCircleOnPlaneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCircleOnPlaneDlg::IDD, pParent)
	, x_angle(0)
	, v0(0)
	, vr(0)
	, vc(0)
	, phi_n(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCircleOnPlaneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_x, x_angle);
	DDX_Text(pDX, IDC_EDIT_V0, v0);
	DDX_Text(pDX, IDC_EDIT_Vr, vr);
	DDX_Text(pDX, IDC_EDIT_Vc, vc);
	DDX_Text(pDX, IDC_EDIT_Phi_n, phi_n);
}

BEGIN_MESSAGE_MAP(CCircleOnPlaneDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCircleOnPlaneDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// обработчики сообщений CCircleOnPlaneDlg

BOOL CCircleOnPlaneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна. Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок. Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CCircleOnPlaneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CCircleOnPlaneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//метод для конвертации типа double в строку
void dtoa(double d, char* str)
{    
    sprintf(str,"%f",d);
    
    if(strstr(str,".") != NULL)
    {
        int i = strlen(str)-1;

        while(str[i] != '.')
        {
            if(str[i] == '0')
                str[i]=NULL;
            else
                break;
            i--;
            if(i<0) break;
        }

        if(str[i] == '.')
            str[i]=NULL;
    }
}

//создаем пременные, необходимые для решения задачи
double Phi_n = 0;
double Vc = 0;
double Vr = 0;
double V0 = 0;
double x = 0;
double p1 = 0, p2 = 0;

void CCircleOnPlaneDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	Phi_n = phi_n; Vc = vc; Vr = vr; V0 = v0; x = x_angle; //получаем значения с полей формы

	double eps = atan((Vc*sin(x))/(Vc*cos(x) + Vr));  //считаем угол упреждения
	double A2 = (sin(eps)*sin(eps) - sin(Phi_n)*sin(Phi_n));

	double V_rel = sqrt(Vr*Vr + Vc*Vc + 2*Vr*Vc*cos(x)); //относительная скорость ракеты
	double f0 = V_rel/V0;
	double B2 = (cos(Phi_n) + f0*cos(eps))*(cos(Phi_n) + f0*cos(eps));

	double C2 = pow((f0 + cos(Phi_n)*cos(eps)),2) - pow(sin(Phi_n), 2)*pow(sin(eps), 2);

	double D = B2*B2 - A2*C2; //дискриминант
	
	if (D >= 0)
	{
		p1 = (-B2 + sqrt(D))/A2;
		p2 = (-B2 - sqrt(D))/A2;
		char sztemp[32]={0};
		dtoa(p1,sztemp);     
		MessageBoxA(NULL,sztemp,"P1",MB_ICONINFORMATION);
		dtoa(p2,sztemp);     
		MessageBoxA(NULL,sztemp,"P2",MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(L"No solution");
	}

}