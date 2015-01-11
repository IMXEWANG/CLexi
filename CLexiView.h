
// CLexiView.h : CCLexiView ��Ľӿ�
//

#pragma once

#include "LxCommand.h"

class CCLexiView : public CView
{
private:
	LxCommandMgr lx_command_mgr;		//�������
	LxDcViCtl doc_view_controler;				//�ĵ����Ű����

protected: // �������л�����
	CCLexiView();
	DECLARE_DYNCREATE(CCLexiView)

// ����
public:
	CCLexiDoc* GetDocument() const;

// ����
public:
//��ȡ��Ϣ
public:
	int GetTextTrueWidth(char* text, size_t src_font);
	int GetTextTrueHeight(char text, size_t src_font);


// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
private:

public:
	virtual ~CCLexiView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // CLexiView.cpp �еĵ��԰汾
inline CCLexiDoc* CCLexiView::GetDocument() const
   { return reinterpret_cast<CCLexiDoc*>(m_pDocument); }
#endif

