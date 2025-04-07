
// GlimWorkDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "GlimWork.h"
#include "GlimWorkDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CGlimWorkDlg 대화 상자



CGlimWorkDlg::CGlimWorkDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_GLIMWORK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CGlimWorkDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CGlimWorkDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONUP()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()


// CGlimWorkDlg 메시지 처리기

BOOL CGlimWorkDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	CRect rect;
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	m_Image.Create(rect.Width(), rect.Height(), 8);

	static RGBQUAD rgb[256];
	for (int i = 0; i < 256; i++)
		rgb[i].rgbRed = rgb[i].rgbGreen = rgb[i].rgbBlue = i;
	m_Image.SetColorTable(0, 256, rgb);

	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	// '(전체 줄 - 1) * 한줄의 바이트수'를 빼서 시작 줄의 주소로 변경한다.
	fm -= m_Image.GetWidth() * (m_Image.GetHeight() - 1) * (8 / 8);

	memset(fm, 0xFF, m_Image.GetWidth() * m_Image.GetHeight());

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CGlimWorkDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CGlimWorkDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rect;
		GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);
		ScreenToClient(&rect);

		CClientDC DC(this);
		m_Image.Draw(DC, rect);		

		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CGlimWorkDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CGlimWorkDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	// UI 반응 범주
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	if (!rect.PtInRect(point))
	{
		return;
	}
	
	// 클릭 오브젝트 찾기
	for (int i = 0; i < CircleMaxCount; i++)
	{
		if (m_Circle[i]._Create && m_Circle[i].PtInRect(point))
		{
			m_Circle[i]._Moving = true;
			return;
		}
	}

	// 생성
	if (CircleMaxCount <= m_dCircleCnt)
	{
		return;
	}

	m_Circle[m_dCircleCnt++].Create(rect, point);

	CirclePrc();

	CDialogEx::OnLButtonDown(nFlags, point);
}

// 오브젝트들에게 마우스 다운 노티

void CGlimWorkDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	
	// UI 반응 범주
	CRect rect;
	GetDlgItem(IDC_STATIC)->GetWindowRect(&rect);
	ScreenToClient(&rect);

	if (!rect.PtInRect(point))
	{
		return;
	}

	// 클릭 오브젝트 찾기
	for (int i = 0; i < CircleMaxCount; i++)
	{
		if (m_Circle[i]._Moving)
		{
			m_Circle[i]._Moving = false;
		}
	}
	
	CDialogEx::OnLButtonUp(nFlags, point);
}

// 오브젝트들에게 마우스 업 노티

void CGlimWorkDlg::CirclePrc(void)
{
	// TODO: 여기에 구현 코드 추가.
	
	unsigned char* fm = (unsigned char*)m_Image.GetBits();

	// '(전체 줄 - 1) * 한줄의 바이트수'를 빼서 시작 줄의 주소로 변경한다.
	fm -= m_Image.GetWidth() * (m_Image.GetHeight() - 1) * (8 / 8);
	memset(fm, 0xFF, m_Image.GetWidth() * m_Image.GetHeight());

	for (int i = 0; i < m_dCircleCnt; i++)
	{
		if (m_Circle[i]._Create)
			m_Circle[i]._Drwa((unsigned char *)m_Image.GetBits(), m_Image.GetPitch());
	}

	// 세점의 외접원
	if (CircleMaxCount <= m_dCircleCnt)
	{
		unsigned char* fm2 = (unsigned char*)m_Image.GetBits();

		CPoint _Center = GetCenter(m_Circle[0]._ClickPoint, m_Circle[1]._ClickPoint, m_Circle[2]._ClickPoint);

		// 중심점에서 반지름
		int distance = sqrt(pow(_Center.x - m_Circle[0]._ClickPoint.x, 2) + pow(_Center.y - m_Circle[0]._ClickPoint.y, 2));

		int nStartX = _Center.x - distance;
		int nStartY = _Center.y - distance;
		int nCenterX = _Center.x;
		int nCenterY = _Center.y;

		for (int i = nStartX; i < nStartX + (distance * 2); i++)
		{
			for (int j = nStartY; j < nStartY + (distance * 2); j++)
			{
				// 픽셀단위로 원에 해당 여부를 판정
				if (isInCircle(i, j, nCenterX, nCenterY, distance))
					fm2[(j * m_Image.GetPitch()) + i] = 0x00;
			}
		}
	}

	OnPaint();
}

bool CGlimWorkDlg::isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
{
	bool bRet = false;

	double dX = i - nCenterX;
	double dY = j - nCenterY;
	double dDist = dX * dX + dY * dY;

	if (dDist < nRadius * nRadius) {
		bRet = true;
	}

	return bRet;
}

// 외접원 계산식 'https://m.blog.naver.com/hileejaeho/221751241141'
CPoint CGlimWorkDlg::GetCenter(CPoint pt1, CPoint pt2, CPoint pt3)
{
	double A = pt2.x - pt1.x;
	double B = pt2.y - pt1.y;
	double C = pt3.x - pt1.x;
	double D = pt3.y - pt1.y;
	double E = A * (pt1.x + pt2.x) + B * (pt1.y + pt2.y);
	double F = C * (pt1.x + pt3.x) + D * (pt1.y + pt3.y);
	double G = 2.0 * (A * (pt3.y - pt2.y) - B * (pt3.x - pt2.x));
	if (G == 0)
		return pt1;

	CPoint ptCenter;
	ptCenter.x = (D * E - B * F) / G;
	ptCenter.y = (A * F - C * E) / G;

	return ptCenter;
}

void CGlimWorkDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	for (int i = 0; i < CircleMaxCount; i++)
	{
		if (m_Circle[i]._Moving)
		{
			m_Circle[i].Hold(point);
		}
	}

	CirclePrc();

	CDialogEx::OnMouseMove(nFlags, point);
}
