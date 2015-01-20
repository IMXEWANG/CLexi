
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
END_MESSAGE_MAP()

// CCLexiView ����/����

CCLexiView::CCLexiView()
{
	// TODO: �ڴ˴���ӹ������
	bInitialized = FALSE;
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
	//dcMem.TextOutA(100, 200, screen_size);

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

LRESULT CCLexiView::OnLexiInit(WPARAM wParam, LPARAM lParam)
{
	CDC* pDC = GetDC();
	doc_view_controler.init(pDC);
	doc_view_controler.draw_complete(pDC);
	ReleaseDC(pDC);
	bInitialized = TRUE;
	return 0;
}

BOOL CCLexiView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

void CCLexiView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	static TCHAR character = 0;
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
		if (nChar & 0x80 != 1)
		{
			character = nChar;
			this->insert(&character, 1);
			character = 0;
		}
		else
		{
			character <<= 8;
			character |= nChar;
			if (character & 0xff00)
			{
				this->insert(&character, 1);
				character = 0;
			}
		}
	}
		break;
	}
	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CCLexiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	LxCommand* locate_cmd = new LxCommand();
	locate_cmd->add_child_cmd(new LxLocateCmd(point.x, point.y));
	locate_cmd->set_dvctl(&doc_view_controler);
	//ExecuteNormalCmd(locate_cmd);
	CDC* pDC = GetDC();
	locate_cmd->Excute(pDC);
	ReleaseDC(pDC);
	lx_command_mgr.insert_cmd(locate_cmd);

	CView::OnLButtonDown(nFlags, point);
}


void CCLexiView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnLButtonUp(nFlags, point);
}


void CCLexiView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	CDC* pDC = GetDC();
	doc_view_controler.draw_complete(pDC);
	ReleaseDC(pDC);
}

// CCLexiView mydoc��������

void CCLexiView::ExecuteNormalCmd(LxCommand* cmd)
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

	cmd->Excute(&dcMem);

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(),
		&dcMem, 0, 0, SRCCOPY);

	dcMem.DeleteDC();
	bmp.DeleteObject();
	ReleaseDC(pDC);
}

void CCLexiView::insert(TCHAR* cs, int len)
{
	LxCommand* insert_cmd = new LxCommand();
	insert_cmd->add_child_cmd(new LxInsertCmd(cs, len));
	insert_cmd->set_dvctl(&doc_view_controler);
	/*CDC* pDC = GetDC();
	insert_cmd->Excute(pDC);
	ReleaseDC(pDC);*/
	ExecuteNormalCmd(insert_cmd);
	lx_command_mgr.insert_cmd(insert_cmd);
}

void CCLexiView::backspace()
{
	LxCommand* backspace_cmd = new LxCommand();
	backspace_cmd->add_child_cmd(new LxSingleRemoveCmd());
	backspace_cmd->set_dvctl(&doc_view_controler);
	/*CDC* pDC = GetDC();
	insert_cmd->Excute(pDC);
	ReleaseDC(pDC);*/
	ExecuteNormalCmd(backspace_cmd);
	lx_command_mgr.insert_cmd(backspace_cmd);
}