#include "stdafx.h"
#include "LxDcViCtl.h"
#include "LxSrcFontFactory.h"

LxDcViCtl::LxDcViCtl() {}
LxDcViCtl::~LxDcViCtl() {}

void LxDcViCtl::init(CDC* pDC)
{
	CFont* font = new CFont;
	font->CreateFont(-16, 0, 0, 0, 100, FALSE, FALSE, 0, ANSI_CHARSET, OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FF_SWISS, "Arial");
	LOGFONT logfont;
	font->GetLogFont(&logfont);
	size_t font_index = SrcFontFactory::GetFontFactInstance()->insert_src_font(logfont);
	font_tree.insert(0, 0, font_index);

	pDC->SelectObject(font);
	TEXTMETRIC trx;
	pDC->GetTextMetrics(&trx);
	cursor.height = trx.tmHeight;

	delete font;
	color_tree.insert(0, 0, RGB(0, 0, 0));

	Paragraph* paragraph = new Paragraph();
	//设置默认的排版算法，对象应从排版算法管理结构中获取
	paragraph->SetComposeAlgom(new LxSimpleComposeAlgo());
	document.add_paragraph(paragraph);
	compose_doc.AttachColorInfo(&color_tree);
	compose_doc.AttachFontInfo(&font_tree);
	compose_doc.AttachPhyDoc(&document);

	compose_doc.compose_complete(pDC);

	cursor.point_x = LxPaper::left_margin;
	cursor.point_y = ViewWindow::GetViewWindowInstance()->border_height + LxPaper::top_margin;
	cursor.page = compose_doc.begin();
	cursor.paragraph = (*cursor.page)->begin();
	cursor.row = (*cursor.paragraph)->begin();
	cursor.index_inner = 0;
	cursor.width_used = 0;

	gd_proxy.init();
	render = new LxBorderRender(new LxContexRender(&compose_doc, &gd_proxy));
}

void LxDcViCtl::insert(char* src, size_t  count)
{
	//在cursor处执行插入操作
	Paragraph* pgh = (*(cursor.paragraph))->get_phy_paragraph();
	pgh->Insert(cursor.get_index_inner_paragraph(), src, count);

	font_tree.insert(cursor.get_index_global(), count);
	color_tree.insert(cursor.get_index_global(), count);
}
void LxDcViCtl::insert(char* src, size_t  count, size_t src_index)
{
}
void LxDcViCtl::remove(size_t position)
{
	if( position != 0 )
		remove(position-1, position);
}
void LxDcViCtl::remove(size_t position_begin, size_t position_end)
{
	font_tree.remove(position_begin, position_end);
	color_tree.remove(position_begin, position_end);
}
void LxDcViCtl::modify_font(size_t position_begin, size_t position_end, size_t font_src_index)
{
	font_tree.modify(position_begin,position_end,font_src_index);
}
void LxDcViCtl::modify_color(size_t position_begin, size_t position_end, size_t color_src_index)
{
	color_tree.modify(position_begin,position_end,color_src_index);
}

//partial
void LxDcViCtl::modify_layout(CDC* pDC, int count)
{
	LxParagraphInDocIter pgh_doc_it(&compose_doc, cursor.page, cursor.paragraph);
	size_t cur_gbl_index_old = cursor.get_index_global();
	Paragraph* phy_pgh = cursor.get_phy_paragraph();

	compose_doc.modify_index(pgh_doc_it, count);
	pgh_doc_it = compose_doc.modify(pgh_doc_it, cursor.row, pDC);
	compose_doc.relayout(pgh_doc_it);

	//计算新的cursor
	cur_gbl_index_old += count;
	compose_doc.calc_cursor(cursor, cur_gbl_index_old, phy_pgh, pDC);
}

//full text
void LxDcViCtl::compose_complete(CDC* pDC)
{
	compose_doc.compose_complete(pDC);
}
void LxDcViCtl::draw_complete(CDC* pDC)
{
	pDC->SetBkMode(TRANSPARENT);
	render->DrawDocument(pDC);
	render->hide_caret();
	render->create_caret(cursor.height, cursor.height/8);
	render->show_caret(&cursor);
}