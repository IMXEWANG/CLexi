/**
Attention!! ע����������������ı��Ű��ĵ�������ı� font_trrr �� color_tree.
next to do:
	1.��ѡ�����������µ�ɾ������						done
		1.1ɾ��ĳһ�������                                     done
		1.2��ĳ�����������֮ǰ������κϲ�       done
	2.��ɱ���ʹ򿪹���                                        have the solution
	3.��ӹ�����														 done
	4.δѡ�������µ��������ɫ����						 done
	5.ѡ���������ʾ(����仯��ʵ��)					 next to do
	6.ѡ�������µ��������ɫ����						 refactoring with 4
*/



/**
���е�command��Executeʵ�����ڶ������ڵ�ǰcursor��λ�ã����Ҫʵ��undo��redoӦ���޸�Ϊ�뵱ǰ���λ���޹�
Documentʵ��add_paragraph��paragraph��
ComposeDocʵ�� LxParagraphInDocIter add_paragraph(Paragraph* pgh, LxParagraphInDocIter pos, int before_after)
{
  add
  1.�ȼ��������Ķε� index, global_index, top_pos
  2.���ɶ�,����
  3.�Զν����Ű�
  4.�Ű���������������ǰҳ,��ҳ֮��Ķ�������һҳ
  5.�Ű����
  6.modify_index(pgh->size());����
 }
 splitcmd exec
 1.modify_index(calc);
 2.modify(LxParagraphInDocIter);
 3.add_paragraph();
*/
