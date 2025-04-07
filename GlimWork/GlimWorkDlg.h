
// GlimWorkDlg.h: 헤더 파일
//

#pragma once


// CGlimWorkDlg 대화 상자
class CGlimWorkDlg : public CDialogEx
{
// 생성입니다.
public:
	CGlimWorkDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GLIMWORK_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
private:
	void CirclePrc(void);
	bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius);
	CPoint GetCenter(CPoint pt1, CPoint pt2, CPoint pt3);
	int m_dCircleCnt;
	CImage m_Image;
	
	static const int CircleMaxCount = 3;

	struct _Circle
	{
		CPoint _ClickPoint;
		CRect _CirclePos;
		int _nRadius;
		bool _Moving;
		bool _Create;

		// 계산하기 힘들고 일단 함수를 다 까먹어서 오프셋으로 한다.
		int _Xoffset;
		int _Yoffset;

		_Circle()
		{
			_nRadius = 20;
			_Moving = false;
			_Create = false; // 이게 뭐여 ㅋㅋㅋ
		}

		void Create(CRect& rect/*offset*/, CPoint point)
		{
			_Xoffset = -rect.left;
			_Yoffset = -rect.top;

			_Create = true;

			point.x += _Xoffset;
			point.y += _Yoffset;

			_ClickPoint.x = point.x;
			_ClickPoint.y = point.y;

			_CirclePos.left = point.x - _nRadius;
			_CirclePos.right = _CirclePos.left + _nRadius;
			_CirclePos.top = point.y - _nRadius;
			_CirclePos.bottom = _CirclePos.top + _nRadius;
		}

		void Hold(CPoint& point)
		{
			point.x += _Xoffset;
			point.y += _Yoffset;

			_ClickPoint.x = point.x;
			_ClickPoint.y = point.y;

			_CirclePos.left = point.x - _nRadius;
			_CirclePos.right = _CirclePos.left + _nRadius;
			_CirclePos.top = point.y - _nRadius;
			_CirclePos.bottom = _CirclePos.top + _nRadius;
		}

		bool PtInRect(CPoint point)
		{
			point.x += _Xoffset;
			point.y += _Yoffset;

			CRect rect(_ClickPoint.x - _nRadius, _ClickPoint.y - _nRadius, _ClickPoint.x + _nRadius, _ClickPoint.y + _nRadius);

			return rect.PtInRect(point);
		}

		void _Drwa(unsigned char *p, int nPitch)
		{
			int nStartX = _ClickPoint.x - _nRadius;
			int nStartY = _ClickPoint.y - _nRadius;
			int nCenterX = _ClickPoint.x;
			int nCenterY = _ClickPoint.y;

			for (int i = nStartX; i < nStartX + (_nRadius * 2); i++)
			{
				for (int j = nStartY; j < nStartY + (_nRadius * 2); j++)
				{
					// 픽셀단위로 원에 해당 여부를 판정
					if (isInCircle(i, j, nCenterX, nCenterY, _nRadius))
						p[(j * nPitch) + i] = 0x00;
				}
			}
		}

		bool isInCircle(int i, int j, int nCenterX, int nCenterY, int nRadius)
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
	};

	// 리스트로 바꿔야 하는데 다 까먹었네, 비교 연산자 오버로딩 펑터 뭐더라;;;
	_Circle m_Circle[CircleMaxCount];
	_Circle *ActiveCircle = NULL;
public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};

// ToDo
/*
-아래 그림의 순서대로 조작하여 요구사항들을 모두 만족하는 프로그램을 작성합니다.
- 세 번째 클릭 이후에 클릭 지점 3개를 모두 지나가는 정원 1개를 그립니다.
- 클릭 지점 원을 그릴 때의 반지름 크기는 사용자로부터 입력 받습니다.
- 각 클릭 지점 원의 중심 좌표를 UI에 표시합니다.
- 네 번째 클릭부터는 클릭 지점 원을 그리지 않습니다.
- 세 클릭 지점을 지나가는 정원의 내부는 채워지지 않아야 하며, 가장자리 두께는 사용자로부터 입력 받습니다.
- 클릭 지점 3개 중 하나를 클릭하고 드래그 했을 때 정원을 다시 그립니다.
- 이 때, 마우스 커서 좌표가 바뀌는 동안 즉, 마우스 드래그 상태가 끝날 때 까지 정원이 계속해서 이동하며 그려져야 합니다.
- [초기화] 버튼을 누르면 그려졌던 모든 내용들을 삭제하고 처음부터 입력 받을 수 있는 상태가 되어야 합니다.
- 정원이 그려진 상태에서[랜덤 이동] 버튼을 누르면 3개의 클릭 지점 원 모두를 랜덤한 위치로 이동시킵니다.
- 이 때, 정원 또한 마찬가지로 다시 그려져야 합니다.
- 랜덤한 위치로 이동 및 정원 그리기 동작을 초당 2회, 총 10번 자동으로 반복하되 메인UI가 프리징 상태가 되지 않도록 별도 쓰레드로 구현해야 합니다.
- MFC Dialog 기반 프로젝트로 작성해야 합니다.
- 클릭 지점 원과 정원을 그릴 때 CDC 클래스를 사용하면 안됩니다. (안내한 유튜브 영상 참고)
*/