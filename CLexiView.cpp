
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

void CCLexiView::OnDraw(CDC* pDC)
{
	CCLexiDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
	CreateSolidCaret(2, 16);
	SetCaretPos(CPoint(100, 100));
	ShowCaret();

	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	CBitmap bmp;

	dcMem.CreateCompatibleDC(pDC);
	bmp.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());
	dcMem.SelectObject(&bmp);
	dcMem.FillSolidRect(rect, pDC->GetBkColor());
	dcMem.TextOut(100, 100, "hello world!!!");
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(),
		&dcMem, 0, 0, SRCCOPY);

	dcMem.DeleteDC();
	bmp.DeleteObject();
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

BOOL CCLexiView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	//return CView::OnEraseBkgnd(pDC);
}

void CCLexiView::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

	CView::OnChar(nChar, nRepCnt, nFlags);
}


void CCLexiView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ

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
	// TODO:  �ڴ˴������Ϣ����������
}