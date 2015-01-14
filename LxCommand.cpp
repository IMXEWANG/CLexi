#include "stdafx.h"
#include "LxCommand.h"

LxInsertCmd::LxInsertCmd(size_t ins_pos, size_t src_font, COLORREF src_color)
	: ins_pos(ins_pos), src_font(src_font), src_color(src_color)
{
}
LxInsertCmd::LxInsertCmd(char* cs, size_t len) : cs_(cs), len_(len) {}
void LxInsertCmd::Excute(CDC* pDC)
{
	//1.先修改物理文档
	//2.根据修改的物理文档的位置调用相应的排版函数
	//3.依次计算剩余文档的段、页关系
	doc_view_ctrl_->insert(cs_, len_);
	doc_view_ctrl_->modify_layout(pDC, len_);
	doc_view_ctrl_->draw_complete(pDC);
}
void LxInsertCmd::Undo()
{

}

LxDeleteCmd::~LxDeleteCmd()
{

}
void LxDeleteCmd::Excute(CDC* pDC)
{

}
void LxDeleteCmd::Undo()
{

}

void LxModifyViewCmd::Excute(CDC* pDC)
{

}

LxMergeCmd::LxMergeCmd(ComposeParagraph* paragraph1, ComposeParagraph* paragraph2)
	: paragraph1_(paragraph1), paragraph2_(paragraph2)
{
}
LxMergeCmd::~LxMergeCmd()
{

}
void LxMergeCmd::Excute(CDC* pDC)
{

}
void LxMergeCmd::Undo()
{

}

LxSplitCmd::LxSplitCmd(ComposeParagraph* paragraph)
	: paragraph(paragraph)
{
}
LxSplitCmd::~LxSplitCmd()
{

}
void LxSplitCmd::Excute(CDC* pDC)
{

}
void LxSplitCmd::Undo()
{

}

LxCommand::~LxCommand()
{
	for (LxCommandBase* it : command)
		delete it;
}
void LxCommand::add_child_cmd(LxCommandBase* child_cmd)
{
	command.push_back(child_cmd);
}
void LxCommand::Excute(CDC* pDC)
{
	for (LxCommandBase* it : command)
		it->Excute(pDC);
}
bool LxCommand::CanUndo()
{
	for (LxCommandBase* it : command)
		if (!it->CanUndo()) return false;
	return true;
}
void LxCommand::Undo()
{
	if (CanUndo())
	{
		auto rit = command.rbegin();
		auto rite = command.rend();
		for (; rit != rite; rit++)
		{
			(*(rit))->Undo();
		}
	}
}
void LxCommand::set_dvctl(LxDcViCtl* doc_view_ctrl)
{
	for (LxCommandBase* it : command)
		it->set_dvctl(doc_view_ctrl);
}

LxCommandMgr::LxCommandMgr()
{
	LxCommand* empty_cmd = new LxCommand();
	empty_cmd->add_child_cmd(new LxEmptyCmd());
	command_list.push_back(empty_cmd);
	curr_ = command_list.begin();
}
LxCommandMgr::~LxCommandMgr()
{
	for (LxCommand* it : command_list)
		delete it;
}
void LxCommandMgr::insert_cmd(LxCommand* lx_cmd)
{
	if (!lx_cmd->CanUndo())
	{
		delete lx_cmd;
		return;
	}
	if (curr_ == command_list.begin())
	{
		command_list.push_back(lx_cmd);
		curr_++;
		return;
	}
	auto it = curr_;
	it++;
	for (; it != command_list.end();)
	{
		delete *it;
		it = command_list.erase(it);
	}
	command_list.push_back(lx_cmd);
	curr_++;
}
LxCommand* LxCommandMgr::get_redo_cmd()
{
	if (curr_ == --command_list.end()) return nullptr;
	curr_++;
	return *curr_;
}
LxCommand* LxCommandMgr::get_undo_cmd()
{
	if (curr_ == command_list.begin()) return nullptr;
	LxCommand* cmd = *curr_;
	curr_--;
	return cmd;
}