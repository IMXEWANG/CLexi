/**
���е�command��Executeʵ�����ڶ������ڵ�ǰcursor��λ�ã����Ҫʵ��undo��redoӦ���޸�Ϊ�뵱ǰ���λ���޹�
Documentʵ��add_paragraph��paragraph��
ComposeDocʵ�� LxParagraphInDocIter add_paragraph(Paragraph* pgh, LxParagraphInDocIter pos, int before_after)
{
  add
  1.�ȼ��������Ķε� index, global_index, top_pos
  2.���ɶ�,����
  3.modify_index(pgh->size());
  4.�Զν����Ű�
  5.�Ű���������������ǰҳ,��ҳ֮��Ķ�������һҳ
  6.�Ű���ɷ���
 }
 splitcmd exec
 1.modify_index(calc);
 2.modify(LxParagraphInDocIter);
 3.add_paragraph();
*/