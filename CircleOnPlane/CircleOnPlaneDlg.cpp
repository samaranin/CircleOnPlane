
// CircleOnPlaneDlg.cpp : ���� ����������
//

#include "stdafx.h"
#include "CircleOnPlane.h"
#include "CircleOnPlaneDlg.h"
#include "afxdialogex.h"
#include "cmath"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���������� ���� CCircleOnPlaneDlg



CCircleOnPlaneDlg::CCircleOnPlaneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CCircleOnPlaneDlg::IDD, pParent)
	, x_angle(30)
	, v0(830)
	, vr(850)
	, vc(670)
	, phi_n(15)
	, x1(5)
	, x2(5)
	, x3(0)
	, x4(0)
	, y1(5)
	, y3(0)
	, y4(5)
	, z1(2)
	, z2(7)
	, y2(0)
	, z3(1)
	, z4(5)
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
	DDX_Text(pDX, IDC_EDIT_x1, x1);
	DDX_Text(pDX, IDC_EDIT_x2, x2);
	DDX_Text(pDX, IDC_EDIT_x3, x3);
	DDX_Text(pDX, IDC_EDIT_x4, x4);
	DDX_Text(pDX, IDC_EDIT_y1, y1);
	DDX_Text(pDX, IDC_EDIT_y2, y2);
	DDX_Text(pDX, IDC_EDIT_y3, y3);
	DDX_Text(pDX, IDC_EDIT_y4, y4);
	DDX_Text(pDX, IDC_EDIT_z1, z1);
	DDX_Text(pDX, IDC_EDIT_z2, z2);
	DDX_Text(pDX, IDC_EDIT_y2, y2);
	DDX_Text(pDX, IDC_EDIT_z3, z3);
	DDX_Text(pDX, IDC_EDIT_z4, z4);
}

BEGIN_MESSAGE_MAP(CCircleOnPlaneDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CCircleOnPlaneDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// ����������� ��������� CCircleOnPlaneDlg

BOOL CCircleOnPlaneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ������ ������ ��� ����� ����������� ����. ����� ������ ��� �������������,
	//  ���� ������� ���� ���������� �� �������� ����������
	SetIcon(m_hIcon, TRUE);			// ������� ������
	SetIcon(m_hIcon, FALSE);		// ������ ������

	// TODO: �������� �������������� �������������

	return TRUE;  // ������� �������� TRUE, ���� ����� �� ������� �������� ����������
}

// ��� ���������� ������ ����������� � ���������� ���� ����� ��������������� ����������� ���� �����,
//  ����� ���������� ������. ��� ���������� MFC, ������������ ������ ���������� ��� �������������,
//  ��� ������������� ����������� ������� ��������.

void CCircleOnPlaneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �������� ���������� ��� ���������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ������������ ������ �� ������ ����������� ��������������
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ��������� ������
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ������� �������� ��� ������� ��� ��������� ����������� ������� ��� �����������
//  ���������� ����.
HCURSOR CCircleOnPlaneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

//����� ��� ����������� ���� double � ������
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

//������� ���������, ����������� ��� ������� ������
double Phi_n = 0;
double Vc = 0;
double Vr = 0;
double V0 = 0;
double x = 0;
double p1 = 0, p2 = 0;
double eps = 0;

//����� ����������� ������
double point_T1[3] = {0, 0, 0};
double point_T2[3] = {0, 0, 0};

CString s = CString("");
char sz[32] = "";


void Block9(CDC* pDC)
{
	eps = atan((Vc*sin(x))/(Vc*cos(x) + Vr));  //������� ���� ����������
	double A2 = (sin(eps)*sin(eps) - sin(Phi_n)*sin(Phi_n));

	double V_rel = sqrt(Vr*Vr + Vc*Vc + 2*Vr*Vc*cos(x)); //������������� �������� ������
	double f0 = V_rel/V0;
	double B2 = (cos(Phi_n) + f0*cos(eps))*(cos(Phi_n) + f0*cos(eps));

	double C2 = pow((f0 + cos(Phi_n)*cos(eps)),2) - pow(sin(Phi_n), 2)*pow(sin(eps), 2);

	double D = B2*B2 - A2*C2; //������������
	
	if (D >= 0)
	{
		p1 = (-B2 + sqrt(D))/A2;
		p2 = (-B2 - sqrt(D))/A2;

		//����� �1
		dtoa(p1,sz);
		s.Format(_T("%S"), "p1 = ");
		pDC->TextOutW(80, 350, s);
		s.Format(_T("%S"), sz);
		pDC->TextOutW(115, 350, s);
		
		//����� �2
		dtoa(p2,sz);
		s.Format(_T("%S"), "p2 = ");
		pDC->TextOutW(220, 350, s);
		s.Format(_T("%S"), sz);
		pDC->TextOutW(255, 350, s);
		dtoa(p1,sz);
	}
	else
	{
		s.Format(_T("%S"), "��� ������� ���������!");
		pDC->TextOutW(100, 350, s);
	}

}

void GetTCoordinates(CDC* pDC, double points[4][3])
{
	//��������������� �������
	s.Format(_T("%S"), "T1: ");
	pDC->TextOutW(80, 380, s);

	s.Format(_T("%S"), "T2: ");
	pDC->TextOutW(80, 410, s);

	int mark = 0; //������ ��� ������� 11 � ������������ �������

	for (int j = 0; j < 3; j++) //�������� ������ 10 �� ������� ��� ���� ����� 4-1
	{
		double l = sqrt(pow((points[3][j] - points[0][j]), 2) 
							+ pow((points[3][j] - points[0][j]), 2)
							+ pow((points[3][j] - points[0][j]), 2)); //����� ������� - ������� 9
	
		point_T1[j] = points[3][0] + ( (points[3][j] - points[0][j]) / l)*p1; //������� 10
		point_T2[j] = points[3][0] + ( (points[3][j] - points[0][j]) / l)*p2;

		if ( (min(points[3][j], points[0][j]) <= point_T2[j])  && (max(points[3][j], points[0][j]) >= point_T2[j]) )
			 mark += 1; //������� 11
		else {mark = 0;}
	}

	//���� ����� ������� 11
	if (mark == 3)
	{
		//������� �1
		for (int x = 0, i = 0; i < 3 ; i++, x += 100)
		{
			dtoa(point_T1[i],sz);
			s.Format(_T("%S"), sz);
			pDC->TextOutW((120 + x), 380, s);
		}	

		//������� �2
		for (int x = 0, i = 0; i < 3 ; i++, x += 100)
		{
			dtoa(point_T2[i],sz);
			s.Format(_T("%S"), sz);
			pDC->TextOutW((120 + x), 410, s);
		}	

		return;
	}

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++) //�������� ������ 10 �� ������� ��� ��� ����� 1-2, 2-3, 3-4
		{
			double l = sqrt(pow((points[i][0] - points[i + 1][0]), 2) 
							+ pow((points[i][1] - points[i + 1][1]), 2)
							+ pow((points[i][2] - points[i + 1][2]), 2));//����� ������� - ������� 9

			point_T1[j] = points[i][j] + ( (points[i+1][j] - points[i][j]) / l)*p1;//������� 10
			point_T2[j] = points[i][j] + ( (points[i+1][j] - points[i][j]) / l)*p2;

			if ( (min(points[i][j], points[i+1][j]) <= point_T2[j])  && (max(points[i][j], points[i+1][j]) >= point_T2[j]) )
				mark += 1; //������� 11
			else {mark = 0;}

			//���� ����� ������� 11
			if (mark == 3)
			{
				 //������� �1
				 for (int x = 0, i = 0; i < 3 ; i++, x += 100)
				{
					dtoa(point_T1[i],sz);
					s.Format(_T("%S"), sz);
					pDC->TextOutW((120 + x), 380, s);
				}	

				//������� �2
				for (int x = 0, i = 0; i < 3 ; i++, x += 100)
				{
					dtoa(point_T2[i],sz);
					s.Format(_T("%S"), sz);
					pDC->TextOutW((120 + x), 410, s);
				}	

				return;
			}
		}
	}
}

void Block10(CDC* pDC, double points[4][3]) //���� 10
{
	double mid_point_T[3] = {0.5*(point_T1[0] + point_T2[0]), 0.5*(point_T1[1] + point_T2[1]), 0.5*(point_T1[2] + point_T2[2])}; //���������� ������� ����� �����
	double Dr = sqrt(mid_point_T[0]*mid_point_T[0] + mid_point_T[1]*mid_point_T[1] + mid_point_T[2]*mid_point_T[2]); //���������� �� ����� ������ �� ������ �����
	
	//���� ������� ������������� Dr
	double phi_r = acos(mid_point_T[0]/Dr);
	double eta_r = atan(mid_point_T[1]/mid_point_T[0]);

	double cos_phi_r = (mid_point_T[0] * cos(x - eps) - mid_point_T[0] * sin(x - eps)) / Dr;
	double sin_sqr_phi_r = 1 - cos_phi_r * cos_phi_r;
	double V01 = sqrt(V0*V0 + Vr*Vr + 2*V0*Vr*cos(Phi_n));//��������� �������� ������� �������
	double Vv = Vc*cos_phi_r + sqrt(V01*V01 - Vc*Vc*sin_sqr_phi_r);//�������� �������

	double Tr = Dr/Vv; //����� ������ ����������� ������
	double R = V0 * sin(Phi_n) * Tr; //������ ����������� ������

	//��������� �������� Vv
	double lv = cos(phi_r);
	double mv = sin(phi_r) * sin(eta_r);
	double rv = sin(phi_r) * cos(eta_r);

	double A = (points[1][1] - points[0][1])*(points[2][2] - points[0][2]) - 
				(points[2][1] - points[0][1])*(points[1][2] - points[0][2]);
	double B = (points[2][0] - points[0][0])*(points[1][2] - points[0][2]) - 
				(points[1][0] - points[0][0])*(points[2][2] - points[0][2]);
	double C = (points[1][0] - points[0][0])*(points[2][1] - points[0][1]) - 
				(points[2][0] - points[0][0])*(points[1][1] - points[0][1]);
	double l = sqrt(A*A + B*B + C*C);

	//��������� �������� N � �����
	double lN = A/l;
	double mN = B/l;
	double rN = C/l;

	double alpha = asin(lv*lN + mv*mN + rv*rN); //���� ������� Vv � alpha

	double ka = 0; //���������� ������� ����� �� ������� ���������
	if ((alpha > (10 * 3.14159265)/180) && (alpha <= (90 * 3.14159265)/180)) 
		ka = sin(alpha - (10 * 3.14159265)/180) / sin((80 * 3.14159265)/180);

	double Lvn = 0.00673 * ka * Vv; //������� ��������� ������

	//��������������� �������
	s.Format(_T("%S"), "Lvn: ");
	pDC->TextOutW(80, 440, s);

	dtoa(Lvn,sz);
	s.Format(_T("%S"), sz);
	pDC->TextOutW(120, 440, s);
}

void PaintPlane(CDC* pDC, double points[4][3])
{
	int x0 = 80; int y0 = 480;
	int scale = 20;
	pDC->MoveTo((int) x0 + scale*points[3][0], (int)  y0 + scale*points[3][1]);
	for (int i = 0; i < 4; i++)
	{
		pDC->LineTo((int)  x0 + scale*points[i][0], (int)  y0 + scale*points[i][1]);
		pDC->MoveTo((int)  x0 + scale*points[i][0], (int)  y0 + scale*points[i][1]);
	}
}

void CCircleOnPlaneDlg::OnBnClickedButton1()
{
	UpdateData(TRUE);
	CDC *pDC = GetDC(); //����� ��� ��������� �� �����
	Phi_n = phi_n; Vc = vc; Vr = vr; V0 = v0; x = x_angle; //�������� �������� � ����� �����

	//���������� ������
	double points[4][3] = {{x1, y1, z1},   //���������� ����� �� ������������
						   {x2, y2, z2},
						   {x3, y3, z3},
						   {x4, y4, z4}};

	Block9(pDC); //���������� ����� 9 � ������������� �������
	GetTCoordinates(pDC, points); //���������� ��������� ����� ����������� ������ � �����
	Block10(pDC, points); //���������� ����� 10
	PaintPlane(pDC, points); //������� ��������

	ReleaseDC(pDC);
}