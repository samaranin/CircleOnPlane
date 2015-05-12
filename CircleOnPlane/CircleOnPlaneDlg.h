
// CircleOnPlaneDlg.h : файл заголовка
//

#pragma once


// диалоговое окно CCircleOnPlaneDlg
class CCircleOnPlaneDlg : public CDialogEx
{
// Создание
public:
	CCircleOnPlaneDlg(CWnd* pParent = NULL);	// стандартный конструктор

// Данные диалогового окна
	enum { IDD = IDD_CIRCLEONPLANE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	double x_angle;
	double v0;
	double vr;
	double vc;
	double phi_n;
};
