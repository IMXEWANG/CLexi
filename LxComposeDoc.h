#include "stdafx.h"
#include <list>
using std::list;

#ifndef __LEXI_COMPOSE_DOC_H
#define __LEXI_COMPOSE_DOC_H

#include "LxDocument.h"
#include "LxTreeBase.h"
#include "LxPaper.h"

/*
������ʾ�Ű�ṹ�������ֲ�������Ҫ���¼����Ű�ı�������ı仯�˵Ľṹ��Ϣ�������С��Ρ�ҳ���Եı仯��

*/
class ComposeBase;
class ComposeParagraph;
class ComposePage;
class ComposeDoc;
class ComposeRow;

typedef list<ComposeRow*> RowList;

typedef list<ComposePage*>::iterator page_iter;
typedef list<ComposeParagraph*>::iterator paragraph_iter;
typedef list<ComposeRow*>::iterator row_iter;

class LxRowInPageIter;
class LxRowInDocIter;
class LxParagraphInDocIter;

class LxCursor;

class ComposeBase
{
public:
	virtual void modify() = 0;
};

class ComposeRow
{
public:
	friend class ComposeDoc;
	ComposeRow();
	~ComposeRow() {}
	void init();
	void set_area(size_t index_begin, size_t index_end)
	{
		this->index_begin = index_begin;
		this->index_end = index_end;
	}
	size_t get_area_begin() { return index_begin; }
	size_t get_area_end() { return index_end; }
	size_t size() { return index_end - index_begin + 1; }
	bool empty() { return size() == 0; }
public:
	int get_line_space() { return last_line_space; }
	void set_line_space(int space) { last_line_space = space; }
	int get_height() { return max_height; }
	void set_height(int height) { max_height = height; }
	int get_base_line() { return baseline_offset_inner; }
	void set_base_line(int base_line) { baseline_offset_inner = base_line; }
	int get_bottom_pos() { return top_offset_session + max_height; }
	int get_next_allowed_pos() { return top_offset_session + max_height + ri_external_leading; }
	int get_top_pos() { return top_offset_session; }
	void set_top_pos(int offset) { top_offset_session = offset; }
	int get_external_leading() { return ri_external_leading; }
	void set_external_leading(int leading) { ri_external_leading = leading; }
	void set_words_space(int words_space_) { words_space = words_space_; }
	int get_words_space() { return words_space; }
public:
	void modify_pos(int offset_y) { top_offset_session += offset_y; }
	void FlushOwnArea(CDC* pDC);
	void Draw(CDC* pDC, TreeBase* font_tree, TreeBase* color_tree, Paragraph* pagraph, size_t base_index, bool bParaFlag = false);
private:
	size_t index_begin;
	size_t index_end;
private:
	int words_space;						//�ּ��
	int top_offset_session;
	int max_height;							//�еĸ߶�
	int baseline_offset_inner;		//����
	int ri_external_leading;			//���彨����о�
	int last_line_space;					//��ĩʣ��Ŀհ׿ռ�(�������κ��ַ�)���
};

class ComposeParagraph
{
public:
	friend class ComposeDoc;
	ComposeParagraph() {}
	~ComposeParagraph();
public:
	bool empty() { return rows.empty(); }
	void add_row(ComposeRow* row);
	void add_row(ComposeRow* row,int index);
	void remove_row(row_iter row_it) { rows.erase(row_it); }
	void set_phy_paragraph(Paragraph* paragraph) { this->paragraph = paragraph; }
	Paragraph* get_phy_paragraph() { return paragraph; }
	void set_parent_page(ComposePage* parent) { parent_page = parent; }
	ComposePage* get_parent_page() { return parent_page; }
	void set_area(size_t index_begin, size_t index_end)
	{
		this->index_begin = index_begin;
		this->index_end = index_end;
	}
	size_t get_area_begin() { return index_begin; }
	size_t get_area_end() { return index_end; }
	int get_height() { return bottom_offset_session - top_offset_session; }
	void set_pos(int top_offset, int bottom_offset)
	{
		this->top_offset_session = top_offset;
		this->bottom_offset_session = bottom_offset;
	}
	int get_top_pos() { return top_offset_session; }
	int get_bottom_pos() { return bottom_offset_session; }
	int get_next_allowed_pos() { return (*(--rows.end()))->get_next_allowed_pos(); }
	void set_offset_inner(size_t offset_inner) { this->offset_inner = offset_inner; }
	size_t get_offset_inner() { return offset_inner; }
	size_t size() { return index_end - index_begin + 1; }
	size_t row_size() { return rows.size(); }
public:
	row_iter begin() { return rows.begin(); }
	row_iter end() { return rows.end(); }
public:
	//����ҳ�ĶεĴ��������ڲ�����
	void modify_pos(int offset_y);
	void FlushOwnArea(CDC* pDC);
	void Draw(CDC* pDC, TreeBase* font_tree, TreeBase* color_tree);
private:
	// offset_inner -> �߼�����ʼλ��������ε�ƫ�ƣ�ƫ��Ϊ0�����Ӧ�ĵ�һ���߼���
	size_t offset_inner;
	size_t index_begin;
	size_t index_end;
private:
	int top_offset_session;
	int bottom_offset_session;
private:
	Paragraph* paragraph;
	ComposePage* parent_page;
	list<ComposeRow*> rows;
};

class ComposePage
{
public:
	friend class ComposeDoc;
	ComposePage() {}
	~ComposePage();
	bool empty() { return paragraphs.empty(); }
	void add_paragraph(ComposeParagraph* paragraph);
	void add_paragraph(ComposeParagraph* paragraph,int index);
	void remove_paragraph(paragraph_iter it) { paragraphs.erase(it); }
	void set_area(size_t index_begin, size_t index_end)
	{
		this->index_begin = index_begin;
		this->index_end = index_end;
	}
	void set_top_pos(int top_pos) { top_pos_global = top_pos; }
	int get_area_begin() { return index_begin; }
	int get_area_end() { return index_end; }
	int get_top_pos() { return top_pos_global; }
	int get_bottom_pos() { return top_pos_global + LxPaper::pixel_height; }
	int get_last_space() { return last_space; }
	size_t size() { return index_end - index_begin + 1; }
	size_t pgh_size() { return paragraphs.size(); }
public:
	ComposeParagraph* get_last_pgh();
	paragraph_iter begin() { return paragraphs.begin(); }
	paragraph_iter end() { return paragraphs.end(); }
	typedef LxRowInPageIter inner_row_iter;
	inner_row_iter rowiter_begin();
	inner_row_iter rowiter_end();
public:
	//����ҳ�ĶεĴ��������ڲ�����
	void modify_pos(int offset_y);
	void FlushOwnArea(CDC* pDC);
	void Draw(CDC* pDC, TreeBase* font_tree, TreeBase* color_tree);
private:
	//����λ��
	size_t index_begin;
	size_t index_end;
private:
	int top_pos_global;		//ҳֽ�Ŷ��������꣬ҳ����ʼ��Чλ�û�Ӧ�ü��� LxPaper::top_margin
	int last_space;			//ҳ���ʣ�µĿռ�߶�
	list<ComposeParagraph*> paragraphs;
};

class ComposeDoc
{
public:
	ComposeDoc() = default;
	~ComposeDoc();
	bool empty() { return pages.empty(); }
	void add_page(ComposePage* page);
	void add_page(ComposePage* page, int index);
	void remove_page(page_iter it) { pages.erase(it); }
public:
	void clear();
	void remove_group_paragraph(LxParagraphInDocIter group_first);
	//��ĳһ������ν����Ű�
	LxParagraphInDocIter compose_phy_pagph(Paragraph* pagph, int index, ComposePage* &page, size_t& index_global, int& y_offset, CDC* pDC);
	LxParagraphInDocIter compose_phy_pagph(Paragraph* pagph, int page_index, int pagh_index, CDC* pDC);
	// ��֮ǰ direction = 0 , ��֮�� direction = 1
	LxParagraphInDocIter compose_phy_pagph(Paragraph* pagph, ComposePage* page, ComposeParagraph* cpgh, int direction, CDC* pDC);
	//ȫ�������Ű�
	void compose_complete(CDC* pDC);
	//�����ɾ���ı�ʱ�޸ĺ��ز���
	LxParagraphInDocIter modify(LxParagraphInDocIter pagraph_iter, row_iter pos, CDC* pDC);
	//�����ɾ���ı�ʱ�޸���Ӧ�ṹ��index
	void modify_index(LxParagraphInDocIter pagraph_iter, int count);
	//relayout����Ϊ��ʣ�µ������������ƶ�������ÿ�е��Ű�����Ķ�
	void relayout(LxParagraphInDocIter pagraph_iter);
	paragraph_iter do_logic_combine(ComposePage* page, paragraph_iter paragraph_it);
public:
	void Draw(CDC* pDC);
	void locate(page_iter& page_it, paragraph_iter& pgh_it, row_iter& row_it, size_t phy_pgh_index, size_t offset_inner);
	void locate(ComposePage*& page, ComposeParagraph*& cpgh, int index, int direction);
	void locate(LxCursor& cursor, CDC* pDC, int doc_x, int doc_y);
	void calc_cursor(LxCursor& cursor, size_t cur_gbl_index, Paragraph* phy_pgh, CDC* pDC);
	void AttachFontInfo(TreeBase* font_tree) { this->font_tree = font_tree; }
	void AttachColorInfo(TreeBase* color_tree) { this->color_tree = color_tree; }
	void AttachPhyDoc(Document* phy_document) { this->phy_document = phy_document; }
public:
	page_iter begin() { return pages.begin(); }
	page_iter end() { return pages.end(); }
	LxParagraphInDocIter pargraph_begin();
	LxParagraphInDocIter pargraph_end();
	LxRowInDocIter row_begin();
	LxRowInDocIter row_end();
	bool first_phy_paragraph(LxCursor& cursor);
	int current_phypgh_index(LxCursor& cursor);
	int total_width();
	int total_height();
// only for test and debugger
public:
	bool self_check();
private:
	list<ComposePage*> pages;
	TreeBase* font_tree;
	TreeBase* color_tree;
	Document* phy_document;
};

/*
ʵ��Iteratorģʽ���������е�ÿһ���С��Ρ�ҳ��
list��iterator���Ա�����Ч��
*/

//do not need again
bool is_crossed_paragraph(ComposeParagraph* paragraph);
void FlushRect(CDC* pDC, CRect* rect, COLORREF back_color);

class LxRowInPageIter
{
public:
	LxRowInPageIter() = delete;
	LxRowInPageIter(ComposePage* page, paragraph_iter pagraph, row_iter irow) :
		this_page(page), paragraph(pagraph), row(irow)
	{
	}
	LxRowInPageIter(const LxRowInPageIter& other)
	{
		this->this_page = other.this_page;
		this->row = other.row;
		this->paragraph = other.paragraph;
	}
	bool operator==(const LxRowInPageIter& other) const
	{
		if (this_page != other.this_page)
			return false;
		if (paragraph != other.paragraph)
			return false;
		return row == other.row;
	}
	bool operator!=(const LxRowInPageIter& other) const
	{
		if (this_page != other.this_page)
			return true;
		if (paragraph != other.paragraph)
			return true;
		return row == other.row;
	}
	LxRowInPageIter& operator=(LxRowInPageIter& other)
	{
		this_page = other.this_page;
		paragraph = other.paragraph;
		row = other.row;
		return *this;
	}
	ComposeRow* operator*()
	{
		return *row;
	}
	LxRowInPageIter& operator++()
	{
		row++;
		if (row == (*paragraph)->end())
		{
			paragraph++;
			if (paragraph != this_page->end())
				row = (*paragraph)->begin();
		}
		return *this;
	}
	LxRowInPageIter operator++(int)
	{
		LxRowInPageIter tmp = *this;
		row++;
		if (row == (*paragraph)->end())
		{
			paragraph++;
			if (paragraph != this_page->end())
				row = (*paragraph)->begin();
		}
		return tmp;
	}
private:
	ComposePage* this_page;
	paragraph_iter paragraph;
	row_iter row;
};

class LxRowInDocIter
{
public:
	LxRowInDocIter() = delete;
	LxRowInDocIter(ComposeDoc* the_doc, page_iter page_it, paragraph_iter pagraph_it, row_iter row_it) :
		doc(the_doc), page(page_it), paragraph(pagraph_it), row(row_it)
	{
	}
	LxRowInDocIter(const LxRowInDocIter& other)
	{
		this->doc = other.doc;
		this->row = other.row;
		this->page = other.page;
		this->paragraph = other.paragraph;
	}
	~LxRowInDocIter() = default;
	ComposeRow* operator*()
	{
		return *row;
	}
	bool operator==(const LxRowInDocIter& other) const
	{
		if (page != other.page)
			return false;
		if (paragraph != other.paragraph)
			return false;
		if (row != other.row)
			return false;
		return true;
	}
	bool operator!=(const LxRowInDocIter& other) const
	{
		if (page != other.page)
			return true;
		if (paragraph != other.paragraph)
			return true;
		if (row != other.row)
			return true;
		return false;
	}
	LxRowInDocIter& operator=(LxRowInDocIter& other)
	{
		paragraph = other.paragraph;
		page = other.page;
		row = other.row;
		doc = other.doc;
		return *this;
	}

	LxRowInDocIter& operator++()
	{
		row++;
		if (row == (*paragraph)->end())
		{
			paragraph++;
			if (paragraph == (*page)->end())
			{
				page++;
				if (page != doc->end())
				{
					paragraph = (*page)->begin();
					row = (*paragraph)->begin();
				}
			}
			else
			{
				row = (*paragraph)->begin();
			}
		}
		return *this;
	}
	LxRowInDocIter& operator--()
	{
		if (row == (*paragraph)->begin())
		{
			if (paragraph == (*page)->begin())
			{
				page--;
				paragraph = --(*page)->end();
				row = --(*paragraph)->end();
			}
			else
			{
				paragraph--;
				row = --(*paragraph)->end();
			}
		}
		else
			row--;
		return *this;
	}
	LxRowInDocIter operator++(int)
	{
		LxRowInDocIter tmp = *this;
		row++;
		if (row == (*paragraph)->end())
		{
			paragraph++;
			if (paragraph == (*page)->end())
			{
				page++;
				if (page != doc->end())
				{
					paragraph = (*page)->begin();
					row = (*paragraph)->begin();
				}
			}
			else
			{
				row = (*paragraph)->begin();
			}
		}
		return tmp;
	}
	LxRowInDocIter operator--(int)
	{
		LxRowInDocIter tmp = *this;
		if (row == (*paragraph)->begin())
		{
			if (paragraph == (*page)->begin())
			{
				page--;
				paragraph = --(*page)->end();
				row = --(*paragraph)->end();
			}
			else
			{
				paragraph--;
				row = --(*paragraph)->end();
			}
		}
		else
			row--;
		return tmp;
	}
private:
	ComposeDoc* doc;
	paragraph_iter paragraph;
	page_iter page;
	row_iter row;
};

class LxParagraphInDocIter
{
public:
	LxParagraphInDocIter() = delete;
	LxParagraphInDocIter(ComposeDoc* the_doc, page_iter page_it, paragraph_iter pagraph_it) :
		doc(the_doc), page(page_it), paragraph(pagraph_it)
	{
	}
	LxParagraphInDocIter(const LxParagraphInDocIter& other)
	{
		this->doc = other.doc;
		this->page = other.page;
		this->paragraph = other.paragraph;
	}
	~LxParagraphInDocIter() = default;
	inline page_iter get_page() { return page; }
	inline paragraph_iter get_paragraph() { return paragraph; }
	bool operator==(const LxParagraphInDocIter& other) const
	{
		//��ͬlist֮��ĵ������ǲ��ɱȽϵ�
		//return paragraph == other.paragraph;
		//�����ڳ�ʼ��ʱ�������Ϊend������ȡ����
		if (page != other.page)
			return false;
		if (paragraph != other.paragraph)
			return false;
		return true;
		//return (*paragraph)->get_area_begin() == (*(other.paragraph))->get_area_begin();
	}
	bool operator!=(const LxParagraphInDocIter& other) const
	{
		if (page != other.page)
			return true;
		if (paragraph != other.paragraph)
			return true;
		return false;
		//return (*paragraph)->get_area_begin() != (*(other.paragraph))->get_area_begin();
	}
	LxParagraphInDocIter& operator=(LxParagraphInDocIter& other)
	{
		paragraph = other.paragraph;
		page = other.page;
		doc = other.doc;
		return *this;
	}
	LxParagraphInDocIter& operator++()
	{
		paragraph++;
		if (paragraph == (*page)->end())
		{
			page++;
			if (page != doc->end())
				paragraph = (*page)->begin();
		}
		return *this;
	}
	LxParagraphInDocIter& operator--()
	{
		if (paragraph == (*page)->begin())
		{
			page--;
			paragraph = --(*page)->end();
		}
		else
			paragraph--;
		return *this;
	}
	LxParagraphInDocIter operator++(int)
	{
		LxParagraphInDocIter tmp = *this;
		paragraph++;
		if (paragraph == (*page)->end())
		{
			page++;
			if (page != doc->end())
				paragraph = (*page)->begin();
		}
		return tmp;
	}
	LxParagraphInDocIter operator--(int)
	{
		LxParagraphInDocIter tmp = *this;
		if (paragraph == (*page)->begin())
		{
			page--;
			paragraph = --(*page)->end();
		}
		else
			paragraph--;
		return tmp;
	}
	ComposeParagraph* operator*()
	{
		return *paragraph;
	}
private:
	ComposeDoc* doc;
	paragraph_iter paragraph;
	page_iter page;
};

#endif