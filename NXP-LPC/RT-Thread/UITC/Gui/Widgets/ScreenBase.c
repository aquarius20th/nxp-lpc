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
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


#include "ScreenBase.h"


void SetScreenInfo(CScreenBase *pScreen,INT8U ParentID,INT8U CurrentID,INT16U nScreenName )
{
	if (pScreen)
	{
		pScreen->ParentID = ParentID;
		pScreen->CurrentID = CurrentID;
		pScreen->ScreenName = nScreenName;
	}
}


//��̬����һ����Ļ
CScreenBase * CreateScreen( INT32U nSize,scr_ctor ctor,scr_dtor dtor )
{
	CScreenBase *pObj;

	if (nSize <= 0 || nSize > MAX_SCR_SIZE)
		return RT_NULL;

	pObj = rt_malloc(nSize);
	if (pObj == RT_NULL)
		return RT_NULL;

	pObj->Ctor = ctor;
	pObj->Dtor = dtor;
	pObj->Size = nSize;

	if(ctor)
	{
		ctor(pObj);
	}
	return pObj;
}
