#include "stdafx.h"

#ifndef __LEXI_COMPOSE_ALGOM_H
#define __LEXI_COMPOSE_ALGOM_H

#include "LxTreeBase.h"
#include "LxComposeDoc.h"
#include "LxCursor.h"
#include "LxCommon.h"

//��Ϊ���������������ܻᲿ���Ű��ȫ���Ű棬�����Ҫ�����Ű��ȫ���Ű�
//  <--������     ���ǵ��Ű��㷨�Ķ����ԣ���ôһ��ͨ�õ��Ű��㷨��Ҫ�����Ľӿڣ�      ������ -->

//asw: ���룺��ǰPage&pos_session
//       ���أ��Ű���ɵ�paragraph��List<Page>(��ʾ������Խ��ҳ)��

/*
	���ε��Ű�Ͳ����Ű�
*/

class LxComposeAlgom
{
public:
	LxComposeAlgom() = default;
	virtual ~LxComposeAlgom() = default;
	
	//�����������������Ű��㷨�У���Ӧ�����������Ű�ʵ����
	virtual void compose() = 0;
	virtual void layout() = 0;
	//���ε��Ű�
	virtual ComposeParagraph* compose(int offset_y, size_t pagra_index_begin, Paragraph* pagraph, TreeBase* font_tree, CDC* pDC) = 0;
	//����Ĳ����Ű�,ִ�в����������Ű��㷨
	virtual void compose(LxCursor cursor) = 0;
	virtual void compose(ComposeRow* row_to_compose, Paragraph* pagraph, size_t& index_begin, size_t& index_inner, TreeBase* font_tree, CDC* pDC) = 0;
};

class LxSimpleComposeAlgo : public LxComposeAlgom
{
public:
	LxSimpleComposeAlgo();
	virtual ~LxSimpleComposeAlgo();
	virtual void compose() override;
	virtual void layout() override;
	virtual ComposeParagraph* compose(int offset_y, size_t pagra_index_begin, Paragraph* pagraph, TreeBase* font_tree, CDC* pDC) override;
	virtual void compose(LxCursor cursor) override;
	virtual void compose(ComposeRow* row_to_compose, Paragraph* pagraph, size_t& index_begin, size_t& index_inner, TreeBase* font_tree, CDC* pDC) override;
};

class ComposeAlgoFactory
{
public:
	~ComposeAlgoFactory()
	{
		for (auto algo : algoms)
			delete algo;
	}
	LxComposeAlgom* get_compose_algom(ComposeAlgoType type)
	{
		return algoms[type];
	}
public:
	static ComposeAlgoFactory* GetComposeAlgoFactInstance()
	{
		if (lpComposeAlgoFactoryInstance == nullptr)
			lpComposeAlgoFactoryInstance = new ComposeAlgoFactory();
		return lpComposeAlgoFactoryInstance;
	}
private:
	static ComposeAlgoFactory* lpComposeAlgoFactoryInstance;
	LxComposeAlgom* algoms[1];
private:
	ComposeAlgoFactory()
	{
		algoms[0] = new LxSimpleComposeAlgo();
	}
	ComposeAlgoFactory(const ComposeAlgoFactory&) = delete;
	ComposeAlgoFactory& operator=(const ComposeAlgoFactory&) = delete;
};

#endif