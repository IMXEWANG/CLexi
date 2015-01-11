#include "stdafx.h"
#include "LxComposeDoc.h"
#include "LxCursor.h"

#ifndef __LX_RENDER_H
#define __LX_RENDER_H

/*
��render�л����ĵ���ҳ���Ρ���
����ҳ����
��ҳ�Ļ��ƺͲ��ֻ����ڲ�ͬ������ʵ�֣�ͬ�����Ű�Ͳ����Ű�һ��
*/

class LxRender
{
public:
	LxRender() {}
	virtual ~LxRender() {}
	void ShowCousor(CDC* pDC, LxCursor* cursor);
public:
	virtual void DrawDocument(CDC* pDC) = 0;
};

class LxContexRender : public LxRender
{
public:
	LxContexRender(ComposeDoc* compose_doc);
	virtual ~LxContexRender();
public:
	virtual void DrawDocument(CDC* pDC) override;
private:
	ComposeDoc* compose_doc_;
};

class LxBorderRender : public LxRender
{
public:
	LxBorderRender(LxRender* base_render);
	virtual ~LxBorderRender();
public:
	virtual void DrawDocument(CDC* pDC) override;
private:
	void DrawBorder(CDC* pDC);
	void DrawPageSpace(CDC* pDC, int bottom_pos, int pages_space);
private:
	LxRender* base_render_;
};

#endif