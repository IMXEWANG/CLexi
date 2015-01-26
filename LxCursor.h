#include "LxComposeDoc.h"

#ifndef __LEXI_CURSOR_H
#define __LEXI_CURSOR_H

class LxCursor
{
public:
	LxCursor() :point_x(0), point_y(0), index_inner(0) {}
	LxCursor(const LxCursor& other)
	{
		this->point_x = other.point_x;
		this->point_y = other.point_y;
		this->height = other.height;
		this->index_inner = other.index_inner;
		this->page = other.page;
		this->paragraph = other.paragraph;
		this->row = other.row;
	}
	~LxCursor() {}
	LxCursor& operator=(const LxCursor& other)
	{
		this->point_x = other.point_x;
		this->point_y = other.point_y;
		this->height = other.height;
		this->index_inner = other.index_inner;
		this->page = other.page;
		this->paragraph = other.paragraph;
		this->row = other.row;
		return *this;
	}
	bool operator==(const LxCursor& other)
	{
		return point_x == other.point_x && point_y == other.point_y;
	}
	bool operator!=(const LxCursor& other)
	{
		return point_x != other.point_x || point_y != other.point_y;
	}
	/*LxCursor& operator++();
	LxCursor operator++(int);*/
	size_t get_index_global()
	{
		return (*row)->get_area_begin() + index_inner;
	}
	size_t get_index_inner_paragraph()
	{
		return get_index_global() - (*paragraph)->get_area_begin() + (*paragraph)->get_offset_inner();
	}
	Paragraph* get_phy_paragraph()
	{
		return (*paragraph)->get_phy_paragraph();
	}
public:
	int point_x;			//carset��λ�������ҳ�淶Χ
	int point_y;
	int height;				//���ĸ߶���������ı�
	int index_inner;		//�ڵ�ǰ�еĵڼ����ַ���,����˴�û���ַ�����Ϊ0 //need
	//int width_used;		//��ǰ���ڴ˴��ﵽ�Ŀ�� //don't need
	page_iter page;
	paragraph_iter paragraph;
	row_iter row;
};

/*
ѡ�����򣺱�ʾ��ѡ�е�������Ϣ��
�ڳ��˹�����copy������һ�в����󣬽����١�
����ʱ�������ػ棬ѡ�е��ı���ӻ�ɫ����
*/
struct Section
{
	LxCursor cursor_begin;
	LxCursor cursor_end;
	bool active()
	{
		return cursor_begin != cursor_end;
	}
};

//

#endif