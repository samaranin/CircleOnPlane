
// CircleOnPlane.h : ������� ���� ��������� ��� ���������� PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�������� stdafx.h �� ��������� ����� ����� � PCH"
#endif

#include "resource.h"		// �������� �������


// CCircleOnPlaneApp:
// � ���������� ������� ������ ��. CircleOnPlane.cpp
//

class CCircleOnPlaneApp : public CWinApp
{
public:
	CCircleOnPlaneApp();

// ���������������
public:
	virtual BOOL InitInstance();

// ����������

	DECLARE_MESSAGE_MAP()
};

extern CCircleOnPlaneApp theApp;