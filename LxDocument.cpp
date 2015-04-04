#include "stdafx.h"
#include "LxDocument.h"
#include <iostream>
using namespace std;

Document::Document() {}
Document::~Document()
{
	for(auto it=paragraph_list.begin();it != paragraph_list.end();it++)
		delete *it;
	paragraph_list.clear();
}

void Document::store_stream(FILE* file)
{
	for(auto it=paragraph_list.begin();it != paragraph_list.end();it++)
		(*it)->store_stream(file);
}

void Document::add_paragraph(Paragraph* paragraph)
{
	paragraph_list.push_back(paragraph);
}

void Document::insert_paragraph(Paragraph* paragraph,int index)
{
	auto it = paragraph_list.begin();
	advance(it, index);
	paragraph_list.insert(it, paragraph);
}

Paragraph* Document::get_pgh(int index)
{
	auto it = paragraph_list.begin();
	advance(it, index);
	return *it;
}

void Document::insert_paragraph(Paragraph* paragraph, contex_pgh_iter pos)
{
	paragraph_list.insert(pos, paragraph);
}

void Document::remove_paragraph(int index)
{
	contex_pgh_iter it = paragraph_list.begin();
	advance(it, index);
	paragraph_list.erase(it);
}

void Document::remove_paragraph(contex_pgh_iter pgh_it)
{
	paragraph_list.erase(pgh_it);
}

void Document::insert(size_t pos, TCHAR* cs, size_t len)
{
	size_t index = 0;
	for (Paragraph* paragraph : paragraph_list)
	{
		index += paragraph->size() - 1;
		if (pos <= index)
		{
			return;
		}
	}
}