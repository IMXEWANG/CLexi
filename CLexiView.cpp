
// CLexiView.cpp : CCLexiView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "CLexi.h"
#endif

#include "CLexiDoc.h"
#include "CLexiView.h"

#include <imm.h>
#pragma comment(lib,"imm32.lib")

#include "LxSrcFontFactory.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCLexiView

IMPLEMENT_DYNCREATE(CCLexiView, CView)

BEGIN_MESSAGE_MAP(CCLexiView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_MESSAGE(LEXI_INIT, &CCLexiView::OnLexiInit)
	ON_WM_CHAR()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SIZE()
	ON_WM_ERASEBKGND()
	ON_WM_KEYDOWN()
	ON_WM_SETCURSOR()
END_MESSAGE_MAP()

// CCLexiView ����/����

CCLexiView::CCLexiView()
{
	// TODO: �ڴ˴���ӹ������
	bInitialized = FALSE;
	IMECharLeft = 0;
	IMECharSize = 0;
}

CCLexiView::~CCLexiView()
{
}

BOOL CCLexiView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CCLexiView ����

void CCLexiView::create_caret(int height, int width)
{
	CreateSolidCaret(width, height);
}
void CCLexiView::hide_caret()
{
	HideCaret();
}
void CCLexiView::show_caret(int x, int y)
{
	POINT point;
	point.x = x;
	point.y = y;
	SetCaretPos(point);
	ShowCaret();
}
void CCLexiView::move_caret(unsigned int direction)
{
	CDC* pDC = GetDC();
	doc_view_controler.usr_move_cursor(pDC, direction);
	ReleaseDC(pDC);
}

void CCLexiView::OnDraw(CDC* pDC)
{
	CCLexiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	/*CreateSolidCaret(2, 16);
	SetCaretPos(CPoint(100, 100));
	ShowCaret();*/

	//CRect rect;
	//GetClientRect(&rect);
	//CDC dcMem;
	//CBitmap bmp;

	//dcMem.CreateCompatibleDC(pDC);
	//bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	//dcMem.SelectObject(&bmp);
	//dcMem.FillSolidRect(rect, pDC->GetBkColor());
	//dcMem.TextOut(100, 100, "hello world!!!");

	//CString screen_size;
	//int cx = GetSystemMetrics(SM_CXSCREEN);
	//int cy = GetSystemMetrics(SM_CYSCREEN);
	//
	//int nScreenWidth, nScreenHeight;
	//HDC hdcScreen = ::GetDC(NULL);			//��ȡ��Ļ��HDC
	//nScreenWidth = GetDeviceCaps(hdcScreen, HORZSIZE);
	//nScreenHeight = GetDeviceCaps(hdcScreen, VERTSIZE);
	//screen_size.Format("�ֱ���:%d,%d   �ߴ�:%d,%d", cx, cy, nScreenWidth, nScreenHeight);
	//dcMem.TextOut(100, 200, screen_size);

	//pDC->BitBlt(0, 0, rect.Width(), rect.Height(),
	//	&dcMem, 0, 0, SRCCOPY);

	//dcMem.DeleteDC();
	//bmp.DeleteObject();
}


// CCLexiView ��ӡ

BOOL CCLexiView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CCLexiView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CCLexiView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}


// CCLexiView ���

#ifdef _DEBUG
void CCLexiView::AssertValid() const
{
	CView::AssertValid();
}

void CCLexiView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CCLexiDoc* CCLexiView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CCLexiDoc)));
	return (CCLexiDoc*)m_pDocument;
}
#endif //_DEBUG


// CCLexiView ��Ϣ�������


BOOL CCLexiView::PreTranslateMessage(MSG* pMsg)
{
	// TODO:  �ڴ����ר�ô����/����û���
	if (pMsg->message == WM_IME_ENDCOMPOSITION)
	{
		HIMC himc = ImmGetContext(this->m_hWnd);
		IMECharSize = IMECharLeft = ImmGetCompositionString(himc, GCS_RESULTSTR, 0, 0);
		ImmReleaseContext(this->m_hWnd, himc);
	}
	return CView::PreTranslateMessage(pMsg);
}

BOOL CCLexiView::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	return CView::OnSetCursor(pWnd, nHitTest, message);
}

LRESULT CCLexiView::OnLexiInit(WPARAM wParam, LPARAM lParam)
{
	CDC* pDC = GetDC();
	doc_view_controler.init(pDC);
	doc_view_controler.draw_complete(pDC);
	ReleaseDC(pDC);
	bInitialized = TRUE;
	//::SetFocus(m_hWnd);
	SetClassLong(GetSafeHwnd(), GCL_HCURSOR, (long)::LoadCursor(NULL, IDC_IBEAM));
	return 0;
}

BOOL CCLexiView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

void CCLexiView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	switch (nChar)
	{
	case VK_UP:
	case VK_DOWN:
	case VK_LEFT:
	case VK_RIGHT:
		move_caret(nChar);
		break;
	default:
		break;
	}
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}

void CCLexiView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (IMECharLeft == 0)
	{
		switch (nChar)
		{
		case '\t':
			//table תΪ����ո���
		{
			TCHAR cs[4] = { ' ', ' ', ' ', ' ' };
			this->insert(cs, 4);
		}
			break;
		case '\r':
			//���»س��������������
			wrap();
			break;
		case '\n':
			break;
		case 8:
			//ɾ��
			backspace();
			break;
		default:
			//�ַ�����
		{
			TCHAR character = nChar;
			this->insert(&character, 1);
		}
			break;
		}
	}
	else
	{
		IMECharLeft -= 2;
		if (IMECharLeft == 0)
		{
			HIMC himc = ImmGetContext(this->m_hWnd);
			TCHAR* result_str = new TCHAR[IMECharSize/2];
			ImmGetCompositionString(himc, GCS_RESULTSTR, (BYTE*)result_str, IMECharSize);
			ImmReleaseContext(this->m_hWnd, himc);
			this->insert(result_str, IMECharSize/2);
			delete[] result_str;
		}
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CCLexiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC* pDC = GetDC();
	doc_view_controler.usr_mouse_lbutton_down(pDC, point.x, point.y);
	ReleaseDC(pDC);

	/*CString info;
	info.Format(L"down (%d,%d)\n", point.x, point.y);
	OutputDebugString(info);*/
	//::SetFocus(m_hWnd);
	CView::OnLButtonDown(nFlags, point);
}


void CCLexiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC* pDC = GetDC();
	doc_view_controler.usr_mouse_lbutton_up(pDC, point.x, point.y);
	ReleaseDC(pDC);

	/*CString info;
	info.Format(L"up (%d,%d)\n", point.x, point.y);
	OutputDebugString(info);*/
	CView::OnLButtonUp(nFlags, point);
}


void CCLexiView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CDC* pDC = GetDC();
	doc_view_controler.usr_mouse_move(pDC, point.x, point.y);
	ReleaseDC(pDC);

	/*CString info;
	info.Format(L"move (%d,%d)\n", point.x, point.y);
	OutputDebugString(info);*/
	CView::OnMouseMove(nFlags, point);
}


void CCLexiView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);
	CRect rect;
	GetClientRect(&rect);
	AdjustViewWindow(rect.Width(), rect.Height());
	//size�ı���ĵ���offset_y���ֲ��䣬�����ͻ�����ĸ߶ȴ��ڵ����ĵ��ܸ߶�ʱ����offset_y��Ϊ0
	//ͬ��offset_xҲ���ֲ��䣬���ͻ�����Ŀ�ȴ��ڵ����ĵ�ҳ����ʱ����offset_x��Ϊ0
	if (!bInitialized)
		return;
	CDC* take_place = NULL;
	Task<CDC>* task = NewRunnableMethod(&doc_view_controler, take_place, &LxDcViCtl::draw_complete);
	ExecuteNormalTask(task);
	delete task;
}

// CCLexiView mydoc��������

void CCLexiView::ExecuteNormalTask(Task<CDC>* task)
{
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	CBitmap bmp;
	CDC* pDC = GetDC();
	dcMem.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	dcMem.SelectObject(&bmp);
	dcMem.FillSolidRect(rect, pDC->GetBkColor());

	task->run(&dcMem);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(),
		&dcMem, 0, 0, SRCCOPY);

	dcMem.DeleteDC();
	bmp.DeleteObject();
	ReleaseDC(pDC);
}

void CCLexiView::insert(TCHAR* cs, int len)
{
	CDC* take_place = NULL;
	Task<CDC>* task = NewRunnableMethod(&doc_view_controler, take_place, &LxDcViCtl::usr_insert, cs, len);
	ExecuteNormalTask(task);
	delete task;
}

void CCLexiView::wrap()
{
	CDC* take_place = NULL;
	Task<CDC>* task = NewRunnableMethod(&doc_view_controler, take_place, &LxDcViCtl::usr_wrap);
	ExecuteNormalTask(task);
	delete task;
}

void CCLexiView::backspace()
{
	CDC* take_place = NULL;
	Task<CDC>* task = NewRunnableMethod(&doc_view_controler, take_place, &LxDcViCtl::usr_backspace);
	ExecuteNormalTask(task);
	delete task;
}
