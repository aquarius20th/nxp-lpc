/****************************************Copyright (c)**************************************************
**
**
**
**
**
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:
**��   ��   ��:
**����޸�����:
**��        ��:
**
**--------------��ʷ�汾��Ϣ----------------------------------------------------------------------------
** ������:
** ��  ��:
** �ա���:
** �衡��:
**
**--------------��ǰ�汾�޶�------------------------------------------------------------------------------
** �޸���:
** �ա���:
** �衡��:
**
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
#pragma once
#ifndef GUI_LIST_H
#define GUI_LIST_H

struct GuiListNode
{
	struct GuiListNode* pNext;
};
typedef struct GuiListNode gui_list_t;

__inline void GuiListInit(gui_list_t *l)
{
	l->pNext = (struct GuiListNode *)0;
}

__inline void GuiListAppend(gui_list_t *l, gui_list_t *n)
{
	struct GuiListNode* node = l;

	while (node->pNext) node = node->pNext;

	/* append the node to the tail */
	node->pNext = n;
	n->pNext = (gui_list_t*) 0;
}

__inline void GuiListInsert(gui_list_t *l, gui_list_t *n)
{
	n->pNext = l->pNext;
	l->pNext = n;
}

__inline gui_list_t* GuiListRemove(gui_list_t *l, gui_list_t *n)
{
	/* remove slist head */
	struct GuiListNode* node = l;
	while (node->pNext && node->pNext != n) node = node->pNext;

	/* remove node */
	if (node->pNext != (gui_list_t *)0)
		node->pNext = node->pNext->pNext;

	return l;
}
__inline int GuiListIsEmpty(const gui_list_t *l)
{
	return l->pNext == l;
}

#define CONTAINING_RECORD(node, type, member)	\
	((type *)((char*)(node)-(unsigned long)(&((type *)0)->member)))

#define GuiListForEach(node, list)	\
	for ((node) = (list)->pNext; (node) != RT_NULL; (node) = (node)->pNext)
#endif
