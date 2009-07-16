/****************************************Copyright (c)**************************************************
**                                      
**               ��ͼ����                       
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
#include "includes.h" 
#include "GuiConst.h" 
#include "global.h"
#include "DC.h"
#include "Func.h"
#include "Icon.h"
#include "asc8_8.h"
#include "ascil_8_16.h"
#include "WordStock.h"
#include "StringTable.h"

//������ʾ������ LCD_WIDTH/8, LCD_HEIGHT ÿλ��ʾһ�����״̬
static LcdBuffer g_LcdBuff;
//Һ����״̬
static INT8U g_nLcdLed;

static 	void _LcdWriteData(LcdPos col, LcdPos row)
{
	hd_LCD_WriteData(col, row, g_LcdBuff[col][row]);
}

//�õ�ĳһ�����ɫ
static COLOR GetPixel(LcdPos x, LcdPos y)
{
//	L_ASSERT(x>=0 && x<GetLCDWidth() && y>=0 && y<GetLCDHeight());

	//��Χ���
	if(x>=GetLCDWidth() || y>=GetLCDHeight() || x<0 || y <0)
	{
		return COLOR_BK;
	}

 	if(g_LcdBuff[GetXIndex(x)][GetYIndex(y)] & GetYBitMask(y))
	{
		return COLOR_FR;
	}
	else
	{
		return COLOR_BK;
	}
}

//����
static void DrawPixel(LcdPos x, LcdPos y, COLOR cr/*=COLOR_FR*/)
{
	INT8U b = 0 ; 
//	L_ASSERT(x>=0 && x<GetLCDWidth() && y>=0 && y<GetLCDHeight());

	//��Χ���
	if(x>=GetLCDWidth() || y>=GetLCDHeight() || x<0 || y <0)
	{
		return;
	}
 
	b=g_LcdBuff[GetXIndex(x)][GetYIndex(y)];
	if(cr==COLOR_FR)
	{
		b |= GetYBitMask(y);
	}
	else
	{
		b &= ~ GetYBitMask(y);
	}

	//д��Һ��
	hd_LCD_WriteData(GetXIndex(x), GetYIndex(y), b);
}

static void DrawPixelEx(LcdPos x, LcdPos y,COLOR cr, PEN pen/*=PEN_COPY*/)
{
//	L_ASSERT(x>=0 && x<GetLCDWidth() && y>=0 && y<GetLCDHeight());

	//��Χ���
	if(x>=GetLCDWidth() || y>=GetLCDHeight() || x<0 || y <0)
	{
		return;
	}

	switch(pen)
	{
	case PEN_COPY:
		{
			DrawPixel(x,y,cr);
		}
		break;
	case PEN_NOT:
		{
			//ȡҺ������Ӧ�㵱ǰ��ɫ�ķ�ɫ
			DrawPixel(x,y,!GetPixel(x,y));
		}
		break;
	case PEN_OR:
		{
			//�����1�ͻ���������㣬�ͺ͵�ǰ״̬һ�£�����
			if(cr==COLOR_FR)
				DrawPixel(x,y,cr);
		}
		break;
	case PEN_XOR:
		{
			cr ^= GetPixel(x,y);
			DrawPixel(x,y,cr);
		}
		break;
	case PEN_AND:
		{
			cr &= GetPixel(x,y);
			DrawPixel(x,y,cr);
		}
		break;
	}
}

//��һ���ֽ�(�ߣ�����)
static void DrawByte(LcdPos x, LcdPos y, INT8U byteValue, PEN pen/*=PEN_COPY*/)
{
	LcdPos i; 
	COLOR cr;	

	for(i=0; i<8; i++)
	{
		cr = (byteValue & (0x01<<(7-i)))>>(7-i);
		DrawPixelEx(x+i, y, cr, pen);
	}
}

static void Redraw(void)
{ 
	INT32U col = 0, row = 0;
	for ( col=0;col<GetLCDBufferWidth();col++) 
	{
		for( row=0;row<GetLCDBufferHeight();row++)
		{
			_LcdWriteData(col, row);
		} 
	}
}

//����
extern void DrawLine(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr)
{
	INT16U i;
	LcdPos  dx,dy,e;
	LcdPos x,y;

	//��ֱ��
	if(x0==x1)
	{
		if(y0>y1)
		{
			i=y0;
			y0=y1;
			y1=i;
		}
		//		for (i=y0;i<y1;i++) {
		//			DrawPixel(x0, i, cr);
		//		}
		//���԰��ֽڽ����Ż�
		for (i=GetYIndex(y0); i<=GetYIndex(y1); i++) 
		{
			LcdPos j;
			//����Ƿ�������һ���ֽ�
			for (j=max(i*8, y0);j<=min((i+1)*8-1, y1);j++) 
			{
				if(GetXIndex(x0)<GetLCDBufferWidth() && i<GetLCDBufferHeight()
					&& GetXIndex(x0)>=0 && i>=0)
				{
					if(cr==COLOR_FR)
					{
						g_LcdBuff[GetXIndex(x0)][i] |= GetYBitMask(j);
					}
					else
					{
						g_LcdBuff[GetXIndex(x0)][i] &= ~ GetYBitMask(j);
					}
				}

			}

			_LcdWriteData(x0, i);
		}
	}
	else if (y0==y1) // ˮƽ��
	{
		if(x0>x1)
		{
			i=x0;
			x0=x1;
			x1=i;
		}

		for (i=x0;i<=x1;i++)
		{
			DrawPixel(i, y0, cr);
		}
	}
	else	//����б��
	{
		//����ֱ�ߵ���ʼ��
		if(x0>x1)
		{
			i=x0;
			x0=x1;
			x1=i;
			i=y0;
			y0=y1;
			y1=i;
		}

		dx=x1-x0;
		dy=y1-y0;
		e=-dx; x=x0; y=y0;    

		if(aabs(dy)<dx)                  //0<б�ʵľ���ֵ <1
		{
			if(dy>0)                    //0<б��<=1
			{
				for(i=0; i<=dx; i++)    
				{
					DrawPixel(x, y, cr);
					x+=1;
					e=e+dy+dy;
					if(e>=0)
					{
						y+=1;
						e=e-dx-dx;
					}
				}//end for

				return;
			}//end if

			if(dy<0)
			{			
				for(i=0; i<=dx; i++)    
				{
					DrawPixel(x, y, cr);
					x+=1;
					e=e-dy-dy;
					if(e>=0)
					{
						y-=1;
						e=e-dx-dx;
					}
				}//end for

				return;
			}//end if 

		}//end if
		else
		{
			if(dy>=0)                               // ����>б��>1
			{
				e=-dy;
				for(i=0; i<=dy; i++)
				{
					DrawPixel(x, y, cr);
					y+=1;
					e=e+dx+dx;
					if(e>=0)
					{
						x+=1;
						e=e-dy-dy;
					}
				}//end for

				return;
			}//end if 

			if(dy<=0)
			{
				e=dy;
				for(i=0; i<=-dy; i++)
				{
					DrawPixel(x, y, cr);
					y-=1;
					e=e+dx+dx;
					if(e>=0)
					{
						x+=1;
						e=e+dy+dy;
					}
				}//end for
				return;
			}//endif		
		}//end else	
	}
}
extern void DrawLineEx(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr/*=COLOR_FR*/, PEN pen/*=PEN_COPY*/)
{
//	L_ASSERT(x0<GetLCDWidth() && x1<GetLCDWidth() && y0<GetLCDHeight() && y1<GetLCDHeight());

	switch(pen)
	{
	case PEN_COPY:
		{
			DrawLine(x0,y0,x1,y1,cr);
		}
		break;
	case PEN_OR:
		{
			if(cr==COLOR_FR)
				DrawLine(x0,y0,x1,y1,cr);
		}
		break;
	case PEN_XOR:
	case PEN_NOT:
	case PEN_AND:
		{
			//��Һ������ǰ����ɫ�йأ���Ҫ��һ������
			INT16U i;
			LcdPos  dx,dy,e;
			LcdPos x,y;

			//��ֱ��
			if(x0==x1)
			{
				if(y0>y1)
				{
					i=y0;
					y0=y1;
					y1=i;
				}

				for (i=y0;i<=y1;i++) 
				{
					DrawPixelEx(x0, i, cr, pen);
				}
			}
			else if (y0==y1) // ˮƽ��
			{
				if(x0>x1)
				{
					i=x0;
					x0=x1;
					x1=i;
				}

				for (i=x0;i<=x1;i++) 
				{
					DrawPixelEx(i, y0, cr, pen);
				}
			}
			else	//����б��
			{
				//����ֱ�ߵ���ʼ��
				if(x0>x1)
				{
					i=x0;
					x0=x1;
					x1=i;
					i=y0;
					y0=y1;
					y1=i;
				}

				dx=x1-x0;
				dy=y1-y0;
				e=-dx; x=x0; y=y0;    

				if(aabs(dy)<dx)                  //0<б�ʵľ���ֵ <1
				{
					if(dy>0)                    //0<б��<=1
					{
						for(i=0; i<=dx; i++)    
						{
							DrawPixelEx(x, y, cr,pen);
							x+=1;
							e=e+dy+dy;
							if(e>=0)
							{
								y+=1;
								e=e-dx-dx;
							}
						}//end for

						return;
					}//end if

					if(dy<0)
					{			
						for(i=0; i<=dx; i++)    
						{
							DrawPixelEx(x, y, cr,pen);
							x+=1;
							e=e-dy-dy;
							if(e>=0)
							{
								y-=1;
								e=e-dx-dx;
							}
						}//end for

						return;
					}//end if 

				}//end if
				else
				{
					if(dy>=0)                               // ����>б��>1
					{
						e=-dy;
						for(i=0; i<=dy; i++)
						{
							DrawPixelEx(x, y, cr,pen);
							y+=1;
							e=e+dx+dx;
							if(e>=0)
							{
								x+=1;
								e=e-dy-dy;
							}
						}//end for

						return;
					}//end if 

					if(dy<=0)
					{
						e=dy;
						for(i=0; i<=-dy; i++)
						{
							DrawPixelEx(x, y, cr,pen);
							y-=1;
							e=e+dx+dx;
							if(e>=0)
							{
								x+=1;
								e=e+dy+dy;
							}
						}//end for
						return;
					}//endif		
				}//end else	
			}
		}
		break;
	}
}

extern void DrawBlock(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr/*=COLOR_FR*/)
{
//	L_ASSERT(x0<GetLCDWidth() && x1<GetLCDWidth() && y0<GetLCDHeight() && y1<GetLCDHeight());
	INT32U x = 0;

	for ( x=x0;x<=x1;x++)
	{
		DrawLine(x, y0, x, y1, cr);
	}
}

extern void DrawBlockRect( LCDRECT *pRect, COLOR cr)
{
	if (pRect)
	{
		DrawBlock(pRect->left, pRect->top, pRect->right, pRect->bottom, cr);
	}
}


extern void DrawBlockEx(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr/*=COLOR_FR*/, PEN pen/*=PEN_COPY*/)
{
//	L_ASSERT(x0<GetLCDWidth() && x1<GetLCDWidth() &&  y0<GetLCDHeight() && y1<GetLCDHeight());

	INT32U x = 0;
	for ( x=x0;x<=x1;x++)
	{
		DrawLineEx(x, y0, x, y1, cr, pen);
	}
}

extern void DrawRect(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr/*=COLOR_FR*/)
{
//	L_ASSERT(x0<GetLCDWidth() && x1<GetLCDWidth() && y0<GetLCDHeight() && y1<GetLCDHeight());

	if(x0==x1)
	{
		DrawLine(x0,y0,x0,y1,cr);
	}
	else if(y0==y1)
	{
		DrawLine(x0,y1,x1,y0,cr);
	}
	else
	{
		DrawLine(x0, y0, x1,y0,cr);
		DrawLine(x1, y0, x1,y1,cr);
		DrawLine(x1, y1, x0,y1,cr);
		DrawLine(x0, y1, x0,y0,cr);
	}
}

extern void DrawRectEx(LcdPos x0, LcdPos y0, LcdPos x1, LcdPos y1, COLOR cr/*=COLOR_FR*/, PEN pen/*=PEN_COPY*/)
{
	//	L_ASSERT(x0<GetLCDWidth() && x1<GetLCDWidth() && y0<GetLCDHeight() && y1<GetLCDHeight());

	LCDRECT rect;
	if(x0==x1)
	{
		DrawLineEx(x0,y0,x0,y1, cr, pen);
	}
	else if(y0==y1)
	{
		DrawLineEx(x0,y1,x1,y0, cr, pen);
	}
	else
	{
		rect.left = x0;
		rect.top = y0; 
		rect.right =x1;
		rect.bottom = y1;
		NormalizeRect(&rect);
		DrawLineEx(rect.left, rect.top, rect.right, rect.top, cr, pen);
		DrawLineEx(rect.right, rect.top+1, rect.right, rect.bottom,cr, pen);
		DrawLineEx(rect.right-1, rect.bottom, rect.left, rect.bottom,cr, pen);
		DrawLineEx(rect.left, rect.bottom-1, rect.left, rect.top+1,cr, pen);
	}
}


static const INT8U mask1[]={0x00, 0x01, 0x03, 0x07, 0x0F, 0x1F, 0x3F, 0x7F, 0xFF};


static void _DrawByteArray(LcdPos x, LcdPos y, INT8U nH, INT8U nV, const INT8U * pBuff)
{
	INT8U col = 0, row = 0;
	INT32U X = 0,Y = 0;
	INT8U b = 0;
	INT32U index = 0;
	INT32U Y1 = 0 , Y2 = 0;

	if (pBuff == NULL)
		return;

	if( (y&0x07) ==0 )
	{
		//�������8����Ŀ��Զ�������Ż�
		for ( col=0;col<nH;col++)
		{
			for ( row=0;row<nV;row++)
			{
				X=GetXIndex(x)+col;
				Y=GetYIndex(y)+row;
				if(X<GetLCDBufferWidth() && Y<GetLCDBufferHeight() && X>=0 && Y>=0)
				{
					g_LcdBuff[X][Y]=pBuff[col*nV+row];
					_LcdWriteData(X,Y);
				}
			}
		}
	}
	else
	{
		//���Ƕ���ģ������Ż�����ȼ۸���
		for (col=0;col<nH;col++)
		{
			for (row=0;row<nV;row++) 
			{
				index=col*nV+row;
				//��Ӧ��ĳ�����ֽڵ�Һ��������ȥ
				X=GetXIndex(x)+col;

				Y1=GetYIndex(y)+row;
				Y2=GetYIndex(y)+row+1;

				b=pBuff[index];

				//ǰһ���ֽڵĴ���
				if(X<GetLCDBufferWidth() && Y1<GetLCDBufferHeight() && X>=0 && Y1>=0)
				{
					g_LcdBuff[X][Y1] = (g_LcdBuff[X][Y1] & (mask1[GetYBitPos(y)]) ) | ((b & (mask1[8-GetYBitPos(y)])) << GetYBitPos(y));
					_LcdWriteData(X,Y1);
				}
				//��һ���ֽڵĴ���
				if(X<GetLCDBufferWidth() && Y2<GetLCDBufferHeight() && X>=0 && Y2>=0)
				{
					g_LcdBuff[X][Y2] = (g_LcdBuff[X][Y2] & (~mask1[GetYBitPos(y)]) ) | ((b & (~mask1[8-GetYBitPos(y)])) >> (8-GetYBitPos(y)));
					_LcdWriteData(X,Y2);
				}
			}
		}		
	}
}

static void _DrawByteArrayEx(LcdPos x, LcdPos y, INT8U nH, INT8U nV, const INT8U * pBuff, PEN pen)
{
	INT32U col = 0, row = 0;
	INT32U X = 0,Y = 0;
	INT8U b = 0;
	INT32U index = 0;
	INT32U Y1 = 0 , Y2 = 0;

	if( (y&0x07) ==0 )
	{
		//�������8����Ŀ��Զ�������Ż�
		for (col=0;col<nH;col++) 
		{
			for (row=0;row<nV;row++)
			{
				X=GetXIndex(x)+col;
				Y=GetYIndex(y)+row;
				if(X<GetLCDBufferWidth() && Y<GetLCDBufferHeight() && X>=0 && Y>=0)
				{
					switch(pen) 
					{
					case PEN_COPY:
						g_LcdBuff[X][Y]=pBuff[col*nV+row];
						break;
					case PEN_NOT:
						g_LcdBuff[X][Y]=~pBuff[col*nV+row];
						break;
					case PEN_OR:
						g_LcdBuff[X][Y] |= pBuff[col*nV+row];
						break;
					case PEN_XOR:
						g_LcdBuff[X][Y] ^= pBuff[col*nV+row];
						break;
					case PEN_AND:
						g_LcdBuff[X][Y] &= pBuff[col*nV+row];
						break;
					}
					_LcdWriteData(X,Y);
				}
			}
		}
	}
	else
	{
		//���Ƕ���ģ������Ż�����ȼ۸���
		for (col=0;col<nH;col++) 
		{
			for (row=0;row<nV;row++) 
			{
				index=col*nV+row;
				//��Ӧ��ĳ�����ֽڵ�Һ��������ȥ
				X=GetXIndex(x)+col;

				Y1=GetYIndex(y)+row;
				Y2=GetYIndex(y)+row+1;

				b=pBuff[index];

				//ǰһ���ֽڵĴ���
				if(X<GetLCDBufferWidth() && Y1<GetLCDBufferHeight() && X>=0 && Y1>=0)
				{
					switch(pen)
					{
					case PEN_COPY:
						g_LcdBuff[X][Y1] = (g_LcdBuff[X][Y1] & (mask1[GetYBitPos(y)]) ) | ((b & (mask1[8-GetYBitPos(y)])) << GetYBitPos(y));
						break;
					case PEN_NOT:
						g_LcdBuff[X][Y1] = (g_LcdBuff[X][Y1] & (mask1[GetYBitPos(y)]) ) | (((~b) & (mask1[8-GetYBitPos(y)])) << GetYBitPos(y));
						break;
					case PEN_OR:
						g_LcdBuff[X][Y1] |= ((b & (mask1[8-GetYBitPos(y)])) << GetYBitPos(y));
						break;
					case PEN_XOR:
						g_LcdBuff[X][Y1] = (g_LcdBuff[X][Y1] & (mask1[GetYBitPos(y)]) ) | (( (g_LcdBuff[X][Y1]) ^ ((b & (mask1[8-GetYBitPos(y)])) << GetYBitPos(y)) ) & (~mask1[GetYBitPos(y)]));
						break;
					case PEN_AND:
						g_LcdBuff[X][Y1] &= ((b & (mask1[8-GetYBitPos(y)])) << GetYBitPos(y)) | mask1[GetYBitPos(y)];
						break;
					}

					_LcdWriteData(X,Y1);
				}
				//��һ���ֽڵĴ���
				if(X<GetLCDBufferWidth() && Y2<GetLCDBufferHeight() && X>=0 && Y2>=0)
				{
					switch(pen) 
					{
					case PEN_COPY:
						g_LcdBuff[X][Y2] = (g_LcdBuff[X][Y2] & (~mask1[GetYBitPos(y)]) ) | ((b & (~mask1[8-GetYBitPos(y)])) >> (8-GetYBitPos(y)));
						break;
					case PEN_NOT:
						g_LcdBuff[X][Y2] = (g_LcdBuff[X][Y2] & (~mask1[GetYBitPos(y)]) ) | (((~b) & (~mask1[8-GetYBitPos(y)])) >> (8-GetYBitPos(y)));
						break;
					case PEN_OR:
						g_LcdBuff[X][Y2] |=  ((b & (~mask1[8-GetYBitPos(y)])) >> (8-GetYBitPos(y)));
						break;
					case PEN_XOR:
						g_LcdBuff[X][Y2] = (g_LcdBuff[X][Y2] & (~mask1[GetYBitPos(y)]) ) | (( (g_LcdBuff[X][Y2]) ^ ((b & (~mask1[8-GetYBitPos(y)])) >> (8-GetYBitPos(y))) ) & (mask1[GetYBitPos(y)]));
						break;
					case PEN_AND:
						g_LcdBuff[X][Y2] &=  ((b & (~mask1[8-GetYBitPos(y)])) >> (8-GetYBitPos(y))) | (~mask1[GetYBitPos(y)]);
						break;
					}
					_LcdWriteData(X,Y2);
				}
			}
		}		
	}
}

extern void DrawIcon(LcdPos x, LcdPos y, INT16U iIconID, PEN pen/*=PEN_COPY*/)
{
//	L_ASSERT(iIconID< NUM_ICON);

	const ICON_RES * pIcon=&IconRes[iIconID];

	int nH=pIcon->nWidth;
	int nV=pIcon->nHeight / 8+(pIcon->nHeight%8==0?0:1);

	if(pen==PEN_COPY)
		_DrawByteArray(x,y,nH,nV,pIcon->pBmp);
	else
		_DrawByteArrayEx(x,y,nH,nV,pIcon->pBmp, pen);
}

//��һ��Ӣ�����ֺ���
extern void DrawEnChar(LcdPos x, LcdPos y, char ch, PEN pen/*=PEN_COPY*/,INT8U nEnFontType /*= LCD_EN_FONT_8_8*/)
{
	INT8U i = 0;
	if(ch<0x20 || (ch-0x20)>=NUM_ENCHAR || ch=='\t')
	{
		ch=' ';
	}
	if(nEnFontType == LCD_EN_FONT_8_8)
	{
		if(pen==PEN_COPY)
			_DrawByteArray(x,y,8,1,asclib8_8[ch-0x20]);
		else
			_DrawByteArrayEx(x,y,8,1,asclib8_8[ch-0x20], pen);
	}
	else if(nEnFontType == LCD_EN_FONT_8_16)
	{
		for( i=0;i<16;i++)
			DrawByte(x, y++, asclib8_16[ch-0x20][i], pen);
	}
}

extern void DrawCnChar(LcdPos x, LcdPos y, INT16U iID, PEN pen/*=PEN_COPY*/)
{
//	L_ASSERT(iID <ZIKUNUM);
	if(pen==PEN_COPY)
		_DrawByteArray(x,y,16,2,g_WordStock[iID].m);
	else
		_DrawByteArrayEx(x,y,16,2,g_WordStock[iID].m, pen);
}

extern void DrawChar(LcdPos x, LcdPos y, INT16U index, PEN pen/*=PEN_COPY*/,INT8U nEnFontType /*= LCD_EN_FONT_8_8*/)
{
	if( index< CNZI_FIRST_INDEX)
	{
		DrawEnChar(x,y,index,pen,nEnFontType);
	}
	else
	{
		DrawCnChar(x,y,index-CNZI_FIRST_INDEX,pen);
	}
}

extern void  DrawCnCharCode(LcdPos x, LcdPos y, INT16U code, PEN pen/*=PEN_COPY*/)
{
	int nID=FindCnCharIndex(code);
	if(nID != NOFIND)
		DrawCnChar(x,y,nID,pen);
}

extern void  DrawCharCode(LcdPos x, LcdPos y, INT16U code, PEN pen/*=PEN_COPY*/,INT8U nEnFontType /*= LCD_EN_FONT_8_8*/)
{
	if(code>=256)
	{
		//�����ַ�
		DrawCnCharCode(x,y,code,pen);
	}
	else
	{
		//Ӣ���ַ�
		DrawEnChar(x,y,code,pen,nEnFontType);
	}
}


//�ж��ַ�����ʽ
typedef enum TEXT_FORMAT
{
	TEXT_ALL_EN,		// ȫӢ��
	TEXT_ALL_CN,		// ȫ����
	TEXT_EN_CN,			// ��Ӧ�Ļ��
	TEXT_UNKNOW         // δ֪
}TEXT_FORMAT;

static INT8U JudgeStringText(const INT16U * pStr, INT16U nLen)
{
	INT8U flagEN=FALSE;
	INT8U flagCN=FALSE;
	INT16U i = 0;
	INT16U zi = 0;

	for ( i=0;i<nLen;i++)
	{
		zi=pStr[i];
		if(zi>=CNZI_FIRST_INDEX)
		{
			flagCN=TRUE;
		}
		else if(zi!='\n' && zi!='\r' && zi!=' ' && zi!='\t')
		{
			flagEN=TRUE;
		}
	}

	// ȫ��Ӣ���ַ�
	if((flagCN==FALSE) && (flagEN==TRUE))
		return TEXT_ALL_EN;

	// ȫ������
	if( (flagCN==TRUE) && (flagEN==FALSE))
		return TEXT_ALL_CN;

	// ������ַ���
	if((flagCN==TRUE) && (flagEN==TRUE))
		return TEXT_EN_CN;

	return TEXT_ALL_EN;
}


//��򵥵Ļ����ַ����ĺ���������Ҫ���д������ر���ռ�ÿռ䷶Χ
static LCDRECT _DrawString(LcdPos x, LcdPos y, const INT16U * pCode, INT16U nLen, PEN pen/*=PEN_COPY*/,INT8U nEnFontType)
{
	INT16U i = 0;
	INT8U nTextStyle= 0;
	INT16U zi = 0;

	LCDRECT rect;

	rect.right=rect.left=x;
	rect.top=rect.bottom=y;

	if(x>=GetLCDWidth() || y>= GetLCDHeight())
	{
		return rect;
	}

	nTextStyle=JudgeStringText(pCode, nLen);

	switch(nTextStyle) 
	{
	case TEXT_ALL_EN:
		{
			if(nEnFontType == LCD_EN_FONT_8_8)
				rect.bottom+=8;
			else if(nEnFontType == LCD_EN_FONT_8_16)
				rect.bottom+=16;			
		}
		break;
	case TEXT_ALL_CN:
	case TEXT_EN_CN:
		rect.bottom+=16;
		break;
	default :
		break;
	}

	for ( i=0;i<nLen;i++) 
	{
		zi=pCode[i];
		if(zi>=CNZI_FIRST_INDEX)
		{
			//����
			DrawCnChar(rect.right, rect.top, zi-CNZI_FIRST_INDEX, pen);
			rect.right+=16;	//����16����
		}
		else //Ӣ��
		{
			switch(nTextStyle) 
			{
			case TEXT_ALL_EN:
				DrawEnChar(rect.right, rect.top,zi,pen,nEnFontType);
				rect.right+=8;
				break;
			case TEXT_EN_CN:
				if(nEnFontType == LCD_EN_FONT_8_8)
				{
					//�ϰ벿���ո�
					DrawEnChar(rect.right, rect.top,' ',pen, LCD_EN_FONT_8_8);
					//�°벿дӢ���ַ�
					DrawEnChar(rect.right, rect.top+8,zi,pen,LCD_EN_FONT_8_8);
					rect.right+=8;				
				}
				else if(nEnFontType == LCD_EN_FONT_8_16)
				{
					DrawEnChar(rect.right, rect.top+16,zi,pen,LCD_EN_FONT_8_16);
					rect.right+=8;									
				}
				break;
			default:
//				L_ASSERT(FALSE);	//�����ܳ����������
				break;
			}
		}
	}
	return rect;
}
///////////////////////////////////////////////////////////////
//	�� �� �� : FindStringFirstLine
//	�������� : �����ַ��������һ�У�����һ�г��ȷ��أ����������д����pNext��
//	������� : 
//	��    ע : 
//	��    �� : ��ΰ
//	ʱ    �� : 2006��2��8��
//	�� �� ֵ : INT16U  ���ص�һ���ַ�����
//	����˵�� : INT16U * pString,
//				 INT16U nLen
///////////////////////////////////////////////////////////////
INT16U FindStringFirstLine(const INT16U * pString, INT16U nLen, const INT16U ** pNext)
{
	int count=nLen;
	INT16U zi = 0;
	INT16U i;

	*pNext=NULL;

	for (i=0;i<nLen;i++)
	{
		zi=pString[i];
		if(zi=='\r' || zi=='\n')
		{
			count=i;
			break;
		}
	}

	//������һ���ַ�
	for (;i<nLen;i++)
	{
		zi=pString[i];
		if(zi!='\r' && zi!='\n')
		{
			*pNext=&pString[i];
			break;
		}
	}

	return count;
}

//���������п�
INT16U GetStringLineWidth(const INT16U * pString, INT16U nLen)
{
	INT16U nWidth=0;
	INT16U i = 0;
	for ( i=0;i<nLen;i++) 
	{
		if(pString[i]>=CNZI_FIRST_INDEX)
		{
			nWidth+=16;
		}
		else
		{
			nWidth+=8;
		}
	}

	return nWidth;
}
///////////////////////////////////////////////////////////////
//	�� �� �� : String2Resource
//	�������� : 
//	�������� : ���ַ���ת��Ϊ��Դ�������ʽ
//	������� : 
//	��    ע : 
//	��    �� : ��ΰ
//	ʱ    �� : 2006��2��8��
//	�� �� ֵ : INT16U				ʵ�����鳤��
//	����˵�� : INT16U * pBuff,		��Դ����
//				 char * pString,	�ַ���
//				 INT16U nBuffLen	��Դ���鳤��
///////////////////////////////////////////////////////////////
INT16U String2Resource(INT16U * pBuff, const char * pString, INT16U nBuffLen)
{
	INT32U count=0;
	INT32U i=0;
	INT8U c1=0,c2 = 0;
	INT16U index = 0;
	INT16U code = 0;

	while (i<strlen(pString)) 
	{
		c1=pString[i];
		c2=pString[i+1];
		index=NOFIND;
		if( (c1 & 0x80) && ( c2&0x80 ))
		{
			//�����ַ�
			code= ((INT16U)c1) | (((INT16U)c2)<<8);
			index=FindCnCharIndex(code);
			if(index!=NOFIND)
			{
				index+=CNZI_FIRST_INDEX;
			}
			i+=2;
		}
		else	//Ӣ���ַ�
		{
			index=c1;
			i++;
		}

		if(index!=NOFIND)
		{
			if(count < nBuffLen)
			{
				pBuff[count++]=index;
			}
			else
			{
				break;	//�˳�
			}
		}
	}

	return count;
}
//����Դ�������ʽ
static void  DrawStringA(LcdPos x, LcdPos y, const INT16U * pCode, INT16U nLen, PEN pen/*=PEN_COPY*/, ALIGN nAlign/*=ALIGN_LEFT*/,INT8U nEnFontType)
{
	LCDRECT rect;
	const INT16U * pTemp;
	const INT16U * pNext=pCode;
	INT16U n = 0;
	INT16U nWidth = 0;

	while(pNext!=NULL)
	{
		n=FindStringFirstLine(pNext, nLen-(pNext-pCode), &pTemp);
		switch(nAlign)
		{
		case ALIGN_LEFT:
			{
				rect=_DrawString(x,y,pNext, n, pen,nEnFontType);
				y=rect.bottom+1;
			}
			break;
		case ALIGN_RIGHT:
			{
				nWidth=GetStringLineWidth(pNext, n);
				rect=_DrawString(x-nWidth,y,pNext, n, pen,nEnFontType);
				y=rect.bottom+1;				
			}
			break;
		case ALIGN_CENTER:
			{
				nWidth=GetStringLineWidth(pNext, n);
				rect=_DrawString(x-nWidth/2,y,pNext, n, pen,nEnFontType);
				y=rect.bottom+1;
			}
			break;
		}
		pNext=pTemp;
	}
}
//�����ַ��� char *
extern void DrawStringByStr(LcdPos x, LcdPos y, const char * pString, PEN pen/*=PEN_COPY*/, ALIGN nAlign/*=ALIGN_LEFT*/,INT8U nEnFontType)
{
	//���ַ���ת��Ϊ��Դ�������ʽ
	INT16U str[STRING_MAXLEN];
	INT16U nLen=String2Resource(str, pString, STRING_MAXLEN);
	DrawStringA(x, y, str, nLen, pen, nAlign,nEnFontType);
}
/*********************************************************************************************************
** ��������: DrawStringById
** ��������: DrawStringById
**
** ���������� �����ַ�����Դ
**
** �䡡��:  LcdPos x
** �䡡��:  LcdPos y
** �䡡��:  INT16U uStringResID
** �䡡��:  PEN pen
** �䡡��:  ALIGN nAlign
** �䡡��:  INT8U nEnFontType
**          
** �䡡��:  extern void
**         
** ȫ�ֱ���:  
** ����ģ��: ��
**
** ������:  LiJin
** �ա���:  2008��10��19��
** ��  ע: 
**-------------------------------------------------------------------------------------------------------
** �޸���:
** �ա���:
** ��  ע: 
**------------------------------------------------------------------------------------------------------
********************************************************************************************************/
extern void DrawStringById(LcdPos x, LcdPos y, INT16U uStringResID, PEN pen/*=PEN_COPY*/, ALIGN nAlign/*=ALIGN_LEFT*/,INT8U nEnFontType)
{
//	L_ASSERT(uStringResID<NUM_STRINGRESOURCE);
	const STR_RES * pStrRes=&StringRes[uStringResID];
// 	if(GetSysCfgValue(ID_SYS_LANGUAGE)==LANGUAGE_CN)
// 	{
// 		DrawStringA(x,y,pStrRes->cn, pStrRes->cnlen, pen, nAlign,nEnFontType);
// 	}
// 	else if(GetSysCfgValue(ID_SYS_LANGUAGE)==LANGUAGE_EN)
// 	{
// 		//���Ӣ���ַ�
// 		DrawStringByStr(x,y,pStrRes->en, pen, nAlign,nEnFontType);
// 	}
	//��������ַ�
	DrawStringA(x,y,pStrRes->cn, pStrRes->cnlen, pen, nAlign,nEnFontType);
}
//Һ���ػ�
extern void ClearScreen(void)
{
	//�建��
	memset(g_LcdBuff, 0, sizeof(g_LcdBuff));

	//��Һ��
	hd_LCD_ClearScreen();
}
//����Һ����
extern void TurnOnLed(void)
{
	hd_LightLCD(TRUE);
	g_nLcdLed=TRUE;
}

extern void TurnOffLed(void)
{
	hd_LightLCD(FALSE);
	g_nLcdLed=FALSE;
}	//Ϩ��Һ����
