 /****************************************Copyright (c)**************************************************
**						��ʾӲ������������ֻ֧��1����ʾ�ӿ�	     
**                                      
**                                      
**
**                           
**
**--------------�ļ���Ϣ--------------------------------------------------------------------------------
**��   ��   ��:   LcdDriver.h
**��   ��   ��:   Author: admin
**����޸�����: Created on: 2009-11-15
**��        ��:   
**��        ע :    
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

#include "applib.h" 
#include "GuiDef.h" 


typedef struct GUI_RECT_NODE CGuiRectNode;

struct GUI_RECT_NODE
{
	CGuiRect Rect;

	CGuiRectNode *pPrev;
	CGuiRectNode *pNext; 
};

struct GUI_BLOCK_HEAP;
struct GUI_REGION
{
	/**
    * Type of the region, can be one of the following:
    *   - NULLREGION\n
    *     A null region.
    *   - SIMPLEREGION\n
    *     A simple region.
    *   - COMPLEXREGION
    *     A complex region.
    *
    * \note Only defined for _USE_NEWGAL.
    */
    INT8U      Type;
   /**
    * Reserved for alignment.
    *
    * \note Only defined for _USE_NEWGAL.
    */
    INT8U      Reserved[3];
	CGuiRect RectBound; // The bounding rect of the region.
	CGuiRectNode *pHead;
	CGuiRectNode *pTail;

	struct GUI_BLOCK_HEAP *pHeap;
};
typedef struct GUI_REGION CGuiRegion;
typedef struct GUI_REGION CGuiClipRgn;


#define GUI_REGION_NULL      0x00
#define GUI_REGION_SIMPLE    0x01
#define GUI_REGION_COMPLEX   0x02
