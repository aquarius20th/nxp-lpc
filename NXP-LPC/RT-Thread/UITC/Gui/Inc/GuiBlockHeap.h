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

#define BDS_FREE        0x0000
#define BDS_SPECIAL     0x0001
#define BDS_USED        0x0002

 /**
 * GUI's private block data heap.
 *
 * \sa InitBlockDataHeap, DestroyBlockDataHeap
 */
struct	GUI_BLOCK_HEAP
{
    /**
     * Size of one block element.
     */
    INT32U          bd_size;
    /**
     * Size of the heap in blocks.
     */
    INT32U          heap_size;
    /**
     * The first free element in the heap.
     */
    INT32U             free;
    /**
     * Pointer to the pre-allocated heap.
     */
    void*           heap;
} ;

typedef struct GUI_BLOCK_HEAP CGuiBlockHeap;

void* BlockDataAlloc (CGuiBlockHeap * heap);
void BlockDataFree (CGuiBlockHeap* heap, void* data);
