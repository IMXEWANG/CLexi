#include "LxComposeDoc.h"

#ifndef __LEXI_CURSOR_H
#define __LEXI_CURSOR_H

class LxCursor
{
public:
	LxCursor() :point_x(0), point_y(0), index_inner(0) {}
	~LxCursor() {}
	LxCursor& operator++();
	LxCursor operator++(int);
	size_t get_index_global()
	{
		return (*row)->get_area_begin() + index_inner;
	}
public:
	int point_x;			//carset��λ�������ҳ�淶Χ
	int point_y;
	int height;				//���ĸ߶���������ı�
	int index_inner;		//�ڵ�ǰ�еĵڼ����ַ��� //need
	int width_used;		//��ǰ���ڴ˴��ﵽ�Ŀ�� //don't need
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
};

//

#endif