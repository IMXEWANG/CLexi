/**
Attention!! ע����������������ı��Ű��ĵ�������ı� font_tree �� color_tree.
next to do:
	1.��ѡ�����������µ�ɾ������						 done
		1.1ɾ��ĳһ�������                                     done
		1.2��ĳ�����������֮ǰ������κϲ�       done
	2.��ɱ���ʹ򿪹���                                        done
	3.��ӹ�����														 done
	4.δѡ�������µ��������ɫ����						 done
	5.ѡ���������ʾ(����仯��ʵ��)					 done
	6.ѡ�������µ���ɫ����									 done
	7.ѡ�������µ���������									 done
	8.ѡ�������µ�ɾ�������롢�س�						 done
	9.�ع����п�����Ҫ�ع��������ʵ��				 done
	10.ctrl+z,ctrl+y undo��redo							 now to do, but how? some operations are so complex like section_remove or ctr+c ctrl+v
																				 to do this, i need to add some other command like 
																				 insert_structured_context(ctrl+v) and section_remove(ctrl+c)
																				 section_wrap and section_replace is composited command
																				 //!!!!    so I need only a new command which is insert_structured_context
																				 //!!!!    and adjust some command
	11.ctrl+c,ctrl+x,ctrl+v ���ơ����С�ճ��		 next to do
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
