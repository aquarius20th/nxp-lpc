///////////////////////////////////////////////////////////////
//	�� �� �� : Resource.c
//	�ļ����� : ��Դ�ļ�
//	��    �� : ��ΰ
//	����ʱ�� : 2008-03-06 14:50:04
//	��Ŀ���� : 
//	����ϵͳ : 
//	��    ע :
//	��ʷ��¼ : 
///////////////////////////////////////////////////////////////
#include "includes.h"
#include "StringTable.h"
//�ַ�����Դ

#define _ZILIB

#ifdef _ZILIB
	#define _PER_SIZE sizeof(INT16U)
#else
	#define _PER_SIZE sizeof(char)
#endif


//------ ID_STRING_NONE --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_NONE[]={10169};
#else
const char str_cn_ID_STRING_NONE[]="��";
#endif
//None
const char str_en_ID_STRING_NONE[]="None";

//------ ID_STRING_SETVAL_EXIT --------
//�˳�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SETVAL_EXIT[]={10119,10225};
#else
const char str_cn_ID_STRING_SETVAL_EXIT[]="�˳�";
#endif
//Exit
const char str_en_ID_STRING_SETVAL_EXIT[]="Exit";

//------ ID_STRING_LOCAL --------
//����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_LOCAL[]={10083,10155};
#else
const char str_cn_ID_STRING_LOCAL[]="����";
#endif
//Local
const char str_en_ID_STRING_LOCAL[]="Local";

//------ ID_STRING_REMOTE --------
//Զ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_REMOTE[]={10063,10121};
#else
const char str_cn_ID_STRING_REMOTE[]="Զ��";
#endif
//Remote
const char str_en_ID_STRING_REMOTE[]="Remote";

//------ ID_STRING_DI_LOCALREMOTE --------
//����/Զ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_LOCALREMOTE[]={10083,10155,47,10063,10121};
#else
const char str_cn_ID_STRING_DI_LOCALREMOTE[]="����/Զ��";
#endif
//Local/Remote
const char str_en_ID_STRING_DI_LOCALREMOTE[]="Local/Remote";

//------ ID_STRING_HAVE --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_HAVE[]={10134};
#else
const char str_cn_ID_STRING_HAVE[]="��";
#endif
//Have
const char str_en_ID_STRING_HAVE[]="Have";

//------ ID_STRING_HAVENOT --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_HAVENOT[]={10169};
#else
const char str_cn_ID_STRING_HAVENOT[]="��";
#endif
//None
const char str_en_ID_STRING_HAVENOT[]="None";

//------ ID_STRING_ENABLE --------
//����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ENABLE[]={10116,10210};
#else
const char str_cn_ID_STRING_ENABLE[]="����";
#endif
//Enable
const char str_en_ID_STRING_ENABLE[]="Enable";

//------ ID_STRING_DISABLE --------
//��ֹ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DISABLE[]={10242,10071};
#else
const char str_cn_ID_STRING_DISABLE[]="��ֹ";
#endif
//Disable
const char str_en_ID_STRING_DISABLE[]="Disable";

//------ ID_STRING_PASSWORD --------
//�û�����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PASSWORD[]={10096,10019,10166,10202};
#else
const char str_cn_ID_STRING_PASSWORD[]="�û�����";
#endif
//Password
const char str_en_ID_STRING_PASSWORD[]="Password";

//------ ID_STRING_SC_COMM_485 --------
//485
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COMM_485[]={52,56,53};
#else
const char str_cn_ID_STRING_SC_COMM_485[]="485";
#endif
// 485
const char str_en_ID_STRING_SC_COMM_485[]=" 485";

//------ ID_STRING_SC_COMM_ETH --------
//ETH
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COMM_ETH[]={69,84,72};
#else
const char str_cn_ID_STRING_SC_COMM_ETH[]="ETH";
#endif
//ETH
const char str_en_ID_STRING_SC_COMM_ETH[]="ETH";

//------ ID_STRING_SC_COMM_ADDRESS --------
//ͨѶ��ַ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COMM_ADDRESS[]={10026,10062,10155,10067};
#else
const char str_cn_ID_STRING_SC_COMM_ADDRESS[]="ͨѶ��ַ";
#endif
//Port Address
const char str_en_ID_STRING_SC_COMM_ADDRESS[]="Port Address";

//------ ID_STRING_SC_ETH_IP1 --------
//IP��ַ��1��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_ETH_IP1[]={73,80,10155,10067,10161,49,10126};
#else
const char str_cn_ID_STRING_SC_ETH_IP1[]="IP��ַ��1��";
#endif
//ETH-IP1
const char str_en_ID_STRING_SC_ETH_IP1[]="ETH-IP1";

//------ ID_STRING_SC_ETH_IP2 --------
//IP��ַ��2��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_ETH_IP2[]={73,80,10155,10067,10161,50,10126};
#else
const char str_cn_ID_STRING_SC_ETH_IP2[]="IP��ַ��2��";
#endif
//ETH-IP2
const char str_en_ID_STRING_SC_ETH_IP2[]="ETH-IP2";

//------ ID_STRING_SC_ETH_IP3 --------
//IP��ַ��3��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_ETH_IP3[]={73,80,10155,10067,10161,51,10126};
#else
const char str_cn_ID_STRING_SC_ETH_IP3[]="IP��ַ��3��";
#endif
//ETH-IP3
const char str_en_ID_STRING_SC_ETH_IP3[]="ETH-IP3";

//------ ID_STRING_SC_ETH_IP4 --------
//IP��ַ��4��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_ETH_IP4[]={73,80,10155,10067,10161,52,10126};
#else
const char str_cn_ID_STRING_SC_ETH_IP4[]="IP��ַ��4��";
#endif
//ETH-IP4
const char str_en_ID_STRING_SC_ETH_IP4[]="ETH-IP4";

//------ ID_STRING_SC_ETH_MASK1 --------
//Mask��ַ��1��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_ETH_MASK1[]={77,97,115,107,10155,10067,10161,49,10126};
#else
const char str_cn_ID_STRING_SC_ETH_MASK1[]="Mask��ַ��1��";
#endif
//ETH-MASK1
const char str_en_ID_STRING_SC_ETH_MASK1[]="ETH-MASK1";

//------ ID_STRING_SC_ETH_MASK2 --------
//Mask��ַ��2��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_ETH_MASK2[]={77,97,115,107,10155,10067,10161,50,10126};
#else
const char str_cn_ID_STRING_SC_ETH_MASK2[]="Mask��ַ��2��";
#endif
//ETH-MASK2
const char str_en_ID_STRING_SC_ETH_MASK2[]="ETH-MASK2";

//------ ID_STRING_SC_ETH_MASK3 --------
//Mask��ַ��3��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_ETH_MASK3[]={77,97,115,107,10155,10067,10161,51,10126};
#else
const char str_cn_ID_STRING_SC_ETH_MASK3[]="Mask��ַ��3��";
#endif
//ETH-MASK3
const char str_en_ID_STRING_SC_ETH_MASK3[]="ETH-MASK3";

//------ ID_STRING_SC_ETH_MASK4 --------
//Mask��ַ��4��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_ETH_MASK4[]={77,97,115,107,10155,10067,10161,52,10126};
#else
const char str_cn_ID_STRING_SC_ETH_MASK4[]="Mask��ַ��4��";
#endif
//ETH-MASK4
const char str_en_ID_STRING_SC_ETH_MASK4[]="ETH-MASK4";

//------ ID_STRING_SC_COM_BAUDRATE --------
//������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COM_BAUDRATE[]={10023,10157,10115};
#else
const char str_cn_ID_STRING_SC_COM_BAUDRATE[]="������";
#endif
//Baudrate
const char str_en_ID_STRING_SC_COM_BAUDRATE[]="Baudrate";

//------ ID_STRING_SC_LANGUAGE --------
//����ѡ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_LANGUAGE[]={10214,10145,10003,10217};
#else
const char str_cn_ID_STRING_SC_LANGUAGE[]="����ѡ��";
#endif
//Language
const char str_en_ID_STRING_SC_LANGUAGE[]="Language";

//------ ID_STRING_SC_LANGUAGE_CN --------
//����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_LANGUAGE_CN[]={10135,10100};
#else
const char str_cn_ID_STRING_SC_LANGUAGE_CN[]="����";
#endif
//Chinese
const char str_en_ID_STRING_SC_LANGUAGE_CN[]="Chinese";

//------ ID_STRING_SC_LANGUAGE_EN --------
//English
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_LANGUAGE_EN[]={69,110,103,108,105,115,104};
#else
const char str_cn_ID_STRING_SC_LANGUAGE_EN[]="English";
#endif
//English
const char str_en_ID_STRING_SC_LANGUAGE_EN[]="English";

//------ ID_STRING_SC_SCREENSAVE --------
//����ʱ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_SCREENSAVE[]={10091,10007,10045,10183};
#else
const char str_cn_ID_STRING_SC_SCREENSAVE[]="����ʱ��";
#endif
//Screen Save
const char str_en_ID_STRING_SC_SCREENSAVE[]="Screen Save";

//------ ID_STRING_SC_COMM_BAUDRATE_4800 --------
//485~4800
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COMM_BAUDRATE_4800[]={52,56,53,126,52,56,48,48};
#else
const char str_cn_ID_STRING_SC_COMM_BAUDRATE_4800[]="485~4800";
#endif
//485 - 4800
const char str_en_ID_STRING_SC_COMM_BAUDRATE_4800[]="485 - 4800";

//------ ID_STRING_SC_COMM_BAUDRATE_9600 --------
//485~9600
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COMM_BAUDRATE_9600[]={52,56,53,126,57,54,48,48};
#else
const char str_cn_ID_STRING_SC_COMM_BAUDRATE_9600[]="485~9600";
#endif
//485 - 9600
const char str_en_ID_STRING_SC_COMM_BAUDRATE_9600[]="485 - 9600";

//------ ID_STRING_SC_COMM_BAUDRATE_19200 --------
//485~19200
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COMM_BAUDRATE_19200[]={52,56,53,126,49,57,50,48,48};
#else
const char str_cn_ID_STRING_SC_COMM_BAUDRATE_19200[]="485~19200";
#endif
//485 - 19200
const char str_en_ID_STRING_SC_COMM_BAUDRATE_19200[]="485 - 19200";

//------ ID_STRING_SC_COMM_BAUDRATE_38400 --------
//485~38400
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COMM_BAUDRATE_38400[]={52,56,53,126,51,56,52,48,48};
#else
const char str_cn_ID_STRING_SC_COMM_BAUDRATE_38400[]="485~38400";
#endif
//485 - 38400
const char str_en_ID_STRING_SC_COMM_BAUDRATE_38400[]="485 - 38400";

//------ ID_STRING_SC_COMM_BAUDRATE_57600 --------
//485~57600
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COMM_BAUDRATE_57600[]={52,56,53,126,53,55,54,48,48};
#else
const char str_cn_ID_STRING_SC_COMM_BAUDRATE_57600[]="485~57600";
#endif
//485 - 57600
const char str_en_ID_STRING_SC_COMM_BAUDRATE_57600[]="485 - 57600";

//------ ID_STRING_SC_COMM_BAUDRATE_115200 --------
//485~115200
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COMM_BAUDRATE_115200[]={52,56,53,126,49,49,53,50,48,48};
#else
const char str_cn_ID_STRING_SC_COMM_BAUDRATE_115200[]="485~115200";
#endif
//485 - 115200
const char str_en_ID_STRING_SC_COMM_BAUDRATE_115200[]="485 - 115200";

//------ ID_STRING_SC_COM_DATAB --------
//����λ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COM_DATAB[]={10249,10168,10075};
#else
const char str_cn_ID_STRING_SC_COM_DATAB[]="����λ";
#endif
//Data Bit
const char str_en_ID_STRING_SC_COM_DATAB[]="Data Bit";

//------ ID_STRING_SC_COM_STOPB --------
//ֹͣλ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COM_STOPB[]={10010,10071,10075};
#else
const char str_cn_ID_STRING_SC_COM_STOPB[]="ֹͣλ";
#endif
//Stop Bit
const char str_en_ID_STRING_SC_COM_STOPB[]="Stop Bit";

//------ ID_STRING_SC_COM_PARITYB --------
//У��λ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SC_COM_PARITYB[]={10011,10198,10075};
#else
const char str_cn_ID_STRING_SC_COM_PARITYB[]="У��λ";
#endif
//Parity Bit
const char str_en_ID_STRING_SC_COM_PARITYB[]="Parity Bit";

//------ ID_STRING_PRJ_RANGE --------
//��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJ_RANGE[]={10027,10110,10087,10121};
#else
const char str_cn_ID_STRING_PRJ_RANGE[]="��������";
#endif
//Range
const char str_en_ID_STRING_PRJ_RANGE[]="Range";

//------ ID_STRING_PRJ_HIGHEST --------
//բ����󿪶�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJ_HIGHEST[]={10006,10102,10213,10220,10027,10110};
#else
const char str_cn_ID_STRING_PRJ_HIGHEST[]="բ����󿪶�";
#endif
//Highest
const char str_en_ID_STRING_PRJ_HIGHEST[]="Highest";

//------ ID_STRING_PRJ_ZEROCODE --------
//�����ֵ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJ_ZEROCODE[]={10181,10180,10202,10059};
#else
const char str_cn_ID_STRING_PRJ_ZEROCODE[]="�����ֵ";
#endif
//Zero Code
const char str_en_ID_STRING_PRJ_ZEROCODE[]="Zero Code";

//------ ID_STRING_PRJ_HIGHCODE --------
//��ߵ���ֵ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJ_HIGHCODE[]={10213,10172,10180,10202,10059};
#else
const char str_cn_ID_STRING_PRJ_HIGHCODE[]="��ߵ���ֵ";
#endif
//High Code
const char str_en_ID_STRING_PRJ_HIGHCODE[]="High Code";

//------ ID_STRING_PRJ_PRESET --------
//Ԥ�迪��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJ_PRESET[]={10014,10195,10027,10110};
#else
const char str_cn_ID_STRING_PRJ_PRESET[]="Ԥ�迪��";
#endif
//Preset
const char str_en_ID_STRING_PRJ_PRESET[]="Preset";

//------ ID_STRING_PRJ_ARCNUM --------
//���ֶ���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJ_ARCNUM[]={10001,10149,10126,10249};
#else
const char str_cn_ID_STRING_PRJ_ARCNUM[]="���ֶ���";
#endif
//Arc Num
const char str_en_ID_STRING_PRJ_ARCNUM[]="Arc Num";

//------ ID_STRING_PRJ_GATAGE --------
//�� �㿪��ֵ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJ_GATAGE[]={10161,32,10180,10027,10110,10059};
#else
const char str_cn_ID_STRING_PRJ_GATAGE[]="�� �㿪��ֵ";
#endif
//No Gatage
const char str_en_ID_STRING_PRJ_GATAGE[]="No Gatage";

//------ ID_STRING_PRJ_CODERDATA --------
//�� �����ֵ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJ_CODERDATA[]={10161,32,10180,10174,10202,10059};
#else
const char str_cn_ID_STRING_PRJ_CODERDATA[]="�� �����ֵ";
#endif
//No CoderData
const char str_en_ID_STRING_PRJ_CODERDATA[]="No CoderData";

//------ ID_STRING_PRJ_SLOPE --------
//�� ��б��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJ_SLOPE[]={10161,32,10126,10046,10115};
#else
const char str_cn_ID_STRING_PRJ_SLOPE[]="�� ��б��";
#endif
//No Slope
const char str_en_ID_STRING_PRJ_SLOPE[]="No Slope";

//------ ID_STRING_DEV_DIRECTION --------
//բ��ת��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_DIRECTION[]={10006,10102,10029,10218};
#else
const char str_cn_ID_STRING_DEV_DIRECTION[]="բ��ת��";
#endif
//Gate Type
const char str_en_ID_STRING_DEV_DIRECTION[]="Gate Type";

//------ ID_STRING_DEV_CALCMETHOD --------
//���㷽ʽ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_CALCMETHOD[]={10105,10182,10079,10081};
#else
const char str_cn_ID_STRING_DEV_CALCMETHOD[]="���㷽ʽ";
#endif
//Calc Method
const char str_en_ID_STRING_DEV_CALCMETHOD[]="Calc Method";

//------ ID_STRING_DEV_DATASOURSE --------
//������Դ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_DATASOURSE[]={10249,10168,10051,10053};
#else
const char str_cn_ID_STRING_DEV_DATASOURSE[]="������Դ";
#endif
//Data Sourse
const char str_en_ID_STRING_DEV_DATASOURSE[]="Data Sourse";

//------ ID_STRING_DEV_ENCODERTYPE --------
//�������ӿ�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_ENCODERTYPE[]={10174,10202,10232,10138,10162};
#else
const char str_cn_ID_STRING_DEV_ENCODERTYPE[]="�������ӿ�";
#endif
//Encoder Type
const char str_en_ID_STRING_DEV_ENCODERTYPE[]="Encoder Type";

//------ ID_STRING_DEV_CODETYPE --------
//��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_CODETYPE[]={10202,10153,10176,10125};
#else
const char str_cn_ID_STRING_DEV_CODETYPE[]="��������";
#endif
//Code Type
const char str_en_ID_STRING_DEV_CODETYPE[]="Code Type";

//------ ID_STRING_DEV_METHOD_LINE --------
//�����㷨
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_METHOD_LINE[]={10173,10144,10182,10025};
#else
const char str_cn_ID_STRING_DEV_METHOD_LINE[]="�����㷨";
#endif
//Line Method
const char str_en_ID_STRING_DEV_METHOD_LINE[]="Line Method";

//------ ID_STRING_DEV_METHOD_TABLE --------
//����㷨
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_METHOD_TABLE[]={10196,10208,10182,10025};
#else
const char str_cn_ID_STRING_DEV_METHOD_TABLE[]="����㷨";
#endif
//Table Search
const char str_en_ID_STRING_DEV_METHOD_TABLE[]="Table Search";

//------ ID_STRING_DEV_DATA_ENCODER --------
//���Ա���ֵ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_DATA_ENCODER[]={10051,10147,10174,10202,10059};
#else
const char str_cn_ID_STRING_DEV_DATA_ENCODER[]="���Ա���ֵ";
#endif
//From Encoder
const char str_en_ID_STRING_DEV_DATA_ENCODER[]="From Encoder";

//------ ID_STRING_DEV_DATA_AD --------
//����ģ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_DATA_AD[]={10051,10147,10009,10204};
#else
const char str_cn_ID_STRING_DEV_DATA_AD[]="����ģ��";
#endif
//From AI
const char str_en_ID_STRING_DEV_DATA_AD[]="From AI";

//------ ID_STRING_DEV_GATE_COROTATION --------
//��ת
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_GATE_COROTATION[]={10250,10029};
#else
const char str_cn_ID_STRING_DEV_GATE_COROTATION[]="��ת";
#endif
//Corotation
const char str_en_ID_STRING_DEV_GATE_COROTATION[]="Corotation";

//------ ID_STRING_DEV_GATE_ROLLBACK --------
//��ת
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_GATE_ROLLBACK[]={10049,10029};
#else
const char str_cn_ID_STRING_DEV_GATE_ROLLBACK[]="��ת";
#endif
//Rollback
const char str_en_ID_STRING_DEV_GATE_ROLLBACK[]="Rollback";

//------ ID_STRING_DEV_ENCODE_NONE --------
//�ޱ�����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_ENCODE_NONE[]={10169,10174,10202,10232};
#else
const char str_cn_ID_STRING_DEV_ENCODE_NONE[]="�ޱ�����";
#endif
//None Encoder
const char str_en_ID_STRING_DEV_ENCODE_NONE[]="None Encoder";

//------ ID_STRING_DEV_ENCODE_PARALLEL --------
//�����Ͳ���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_ENCODE_PARALLEL[]={10237,10141,10125,10004,10162};
#else
const char str_cn_ID_STRING_DEV_ENCODE_PARALLEL[]="�����Ͳ���";
#endif
//Abs Parallel
const char str_en_ID_STRING_DEV_ENCODE_PARALLEL[]="Abs Parallel";

//------ ID_STRING_DEV_ENCODE_SSI --------
//������SSI
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_ENCODE_SSI[]={10237,10141,10125,83,83,73};
#else
const char str_cn_ID_STRING_DEV_ENCODE_SSI[]="������SSI";
#endif
//Abs SSI
const char str_en_ID_STRING_DEV_ENCODE_SSI[]="Abs SSI";

//------ ID_STRING_DEV_ENCODE_INCREMENTAL --------
//����������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_ENCODE_INCREMENTAL[]={10228,10087,10125,10227,10188};
#else
const char str_cn_ID_STRING_DEV_ENCODE_INCREMENTAL[]="����������";
#endif
//Incremental
const char str_en_ID_STRING_DEV_ENCODE_INCREMENTAL[]="Incremental";

//------ ID_STRING_DEV_CODE_GRAY --------
//������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_CODE_GRAY[]={10216,10154,10202};
#else
const char str_cn_ID_STRING_DEV_CODE_GRAY[]="������";
#endif
//Gray
const char str_en_ID_STRING_DEV_CODE_GRAY[]="Gray";

//------ ID_STRING_DEV_CODE_BCD --------
//BCD��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_CODE_BCD[]={66,67,68,10202};
#else
const char str_cn_ID_STRING_DEV_CODE_BCD[]="BCD��";
#endif
//BCD
const char str_en_ID_STRING_DEV_CODE_BCD[]="BCD";

//------ ID_STRING_DEV_CODE_BINARY --------
//��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_CODE_BINARY[]={10251,10236,10107,10202};
#else
const char str_cn_ID_STRING_DEV_CODE_BINARY[]="��������";
#endif
//Binary
const char str_en_ID_STRING_DEV_CODE_BINARY[]="Binary";

//------ ID_STRING_DEV_ADDACHOICE --------
//AIAOͨ��ѡ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_ADDACHOICE[]={65,73,65,79,10026,10089,10003,10217};
#else
const char str_cn_ID_STRING_DEV_ADDACHOICE[]="AIAOͨ��ѡ��";
#endif
//AIAO Channel
const char str_en_ID_STRING_DEV_ADDACHOICE[]="AIAO Channel";

//------ ID_STRING_DEV_NONE_ADDA --------
//��ģ��ģ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_NONE_ADDA[]={10169,10009,10204,10009,10225};
#else
const char str_cn_ID_STRING_DEV_NONE_ADDA[]="��ģ��ģ��";
#endif
//None AIAO
const char str_en_ID_STRING_DEV_NONE_ADDA[]="None AIAO";

//------ ID_STRING_DEV_ADDA --------
//1·AI1·AO
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_ADDA[]={49,10065,65,73,49,10065,65,79};
#else
const char str_cn_ID_STRING_DEV_ADDA[]="1·AI1·AO";
#endif
//1AI 1AO
const char str_en_ID_STRING_DEV_ADDA[]="1AI 1AO";

//------ ID_STRING_DEV_TWOAD --------
//2·AI
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_TWOAD[]={50,10065,65,73};
#else
const char str_cn_ID_STRING_DEV_TWOAD[]="2·AI";
#endif
//2 AI
const char str_en_ID_STRING_DEV_TWOAD[]="2 AI";

//------ ID_STRING_DEV_ONEDA --------
//1·AO
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_ONEDA[]={49,10065,65,79};
#else
const char str_cn_ID_STRING_DEV_ONEDA[]="1·AO";
#endif
//1 AO
const char str_en_ID_STRING_DEV_ONEDA[]="1 AO";

//------ ID_STRING_DEV_DIDOCONFIG --------
//���뿪������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_DIDOCONFIG[]={10027,10204,10027,10225,10024,10189};
#else
const char str_cn_ID_STRING_DEV_DIDOCONFIG[]="���뿪������";
#endif
//DIDO Mode
const char str_en_ID_STRING_DEV_DIDOCONFIG[]="DIDO Mode";

//------ ID_STRING_DEV_DIGITALTIME --------
//ȥ��ʱ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEV_DIGITALTIME[]={10016,10060,10045,10183};
#else
const char str_cn_ID_STRING_DEV_DIGITALTIME[]="ȥ��ʱ��";
#endif
//Digial Time
const char str_en_ID_STRING_DEV_DIGITALTIME[]="Digial Time";

//------ ID_STRING_DC_DIDOCONFIG_DEFAULT --------
//Ĭ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DC_DIDOCONFIG_DEFAULT[]={10033,10129};
#else
const char str_cn_ID_STRING_DC_DIDOCONFIG_DEFAULT[]="Ĭ��";
#endif
//DIDO_Def
const char str_en_ID_STRING_DC_DIDOCONFIG_DEFAULT[]="DIDO_Def";

//------ ID_STRING_DC_DIDOCONFIG_PREDEFINE --------
//Ԥ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DC_DIDOCONFIG_PREDEFINE[]={10014,10024,10189};
#else
const char str_cn_ID_STRING_DC_DIDOCONFIG_PREDEFINE[]="Ԥ����";
#endif
//DIDO_PreDef
const char str_en_ID_STRING_DC_DIDOCONFIG_PREDEFINE[]="DIDO_PreDef";

//------ ID_STRING_DC_DIDOCONFIG_CUSTOM --------
//�Զ���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DC_DIDOCONFIG_CUSTOM[]={10147,10024,10189};
#else
const char str_cn_ID_STRING_DC_DIDOCONFIG_CUSTOM[]="�Զ���";
#endif
//DIDO_Custom
const char str_en_ID_STRING_DC_DIDOCONFIG_CUSTOM[]="DIDO_Custom";

//------ ID_STRING_K_IN --------
//4~20mA Kin
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_K_IN[]={52,126,50,48,109,65,32,75,105,110};
#else
const char str_cn_ID_STRING_K_IN[]="4~20mA Kin";
#endif
//4~20mA Kin
const char str_en_ID_STRING_K_IN[]="4~20mA Kin";

//------ ID_STRING_K_OUT --------
//4~20mA K
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_K_OUT[]={52,126,50,48,109,65,32,75};
#else
const char str_cn_ID_STRING_K_OUT[]="4~20mA K";
#endif
// 4-20mA K
const char str_en_ID_STRING_K_OUT[]=" 4-20mA K";

//------ ID_STRING_B_OUT --------
//4~20mA B
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_B_OUT[]={52,126,50,48,109,65,32,66};
#else
const char str_cn_ID_STRING_B_OUT[]="4~20mA B";
#endif
// 4-20mA B
const char str_en_ID_STRING_B_OUT[]=" 4-20mA B";

//------ ID_STRING_ABNORMAL_FRAM --------
//FRAM
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_FRAM[]={70,82,65,77};
#else
const char str_cn_ID_STRING_ABNORMAL_FRAM[]="FRAM";
#endif
//FRAM
const char str_en_ID_STRING_ABNORMAL_FRAM[]="FRAM";

//------ ID_STRING_ABNORMAL_RAM --------
//RAM
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_RAM[]={82,65,77};
#else
const char str_cn_ID_STRING_ABNORMAL_RAM[]="RAM";
#endif
// RAM
const char str_en_ID_STRING_ABNORMAL_RAM[]=" RAM";

//------ ID_STRING_ABNORMAL_CLOCK --------
//ʱ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_CLOCK[]={10045,10140};
#else
const char str_cn_ID_STRING_ABNORMAL_CLOCK[]="ʱ��";
#endif
// Clock
const char str_en_ID_STRING_ABNORMAL_CLOCK[]=" Clock";

//------ ID_STRING_ABNORMAL_MEAS_PRECISION --------
//��������ϵ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_MEAS_PRECISION[]={10178,10087,10030,10110,10058,10249};
#else
const char str_cn_ID_STRING_ABNORMAL_MEAS_PRECISION[]="��������ϵ��";
#endif
//Meas. Gains
const char str_en_ID_STRING_ABNORMAL_MEAS_PRECISION[]="Meas. Gains";

//------ ID_STRING_ABNORMAL_SYSCFG --------
//ϵͳ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_SYSCFG[]={10058,10048,10195,10097};
#else
const char str_cn_ID_STRING_ABNORMAL_SYSCFG[]="ϵͳ����";
#endif
//System Cfg.
const char str_en_ID_STRING_ABNORMAL_SYSCFG[]="System Cfg.";

//------ ID_STRING_ABNORMAL_DBGCFG --------
//��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_DBGCFG[]={10012,10121,10185,10097};
#else
const char str_cn_ID_STRING_ABNORMAL_DBGCFG[]="��������";
#endif
//Field Cfg.
const char str_en_ID_STRING_ABNORMAL_DBGCFG[]="Field Cfg.";

//------ ID_STRING_ABNORMAL_DIDOCONFIG --------
//���뿪������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_DIDOCONFIG[]={10027,10204,10027,10225,10185,10097};
#else
const char str_cn_ID_STRING_ABNORMAL_DIDOCONFIG[]="���뿪������";
#endif
//DI/DO Cfg.
const char str_en_ID_STRING_ABNORMAL_DIDOCONFIG[]="DI/DO Cfg.";

//------ ID_STRING_ABNORMAL_DO_POWER --------
//����24V��Դ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_DO_POWER[]={10027,10225,50,52,86,10193,10053};
#else
const char str_cn_ID_STRING_ABNORMAL_DO_POWER[]="����24V��Դ";
#endif
//24V Monitor
const char str_en_ID_STRING_ABNORMAL_DO_POWER[]="24V Monitor";

//------ ID_STRING_ABNORMAL_CONNECTION --------
//�ⲿ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_CONNECTION[]={10179,10086,10138,10173};
#else
const char str_cn_ID_STRING_ABNORMAL_CONNECTION[]="�ⲿ����";
#endif
//CTRL Circuit \nBroken
const char str_en_ID_STRING_ABNORMAL_CONNECTION[]="CTRL Circuit \nBroken";

//------ ID_STRING_ABNORMAL_EXECODE --------
//��ִ�д���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ABNORMAL_EXECODE[]={10113,10054,10133,10241,10202};
#else
const char str_cn_ID_STRING_ABNORMAL_EXECODE[]="��ִ�д���";
#endif
//Exe. Code
const char str_en_ID_STRING_ABNORMAL_EXECODE[]="Exe. Code";

//------ ID_STRING_RUN_COOL_STARTUP --------
//������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RUN_COOL_STARTUP[]={10184,10222,10039};
#else
const char str_cn_ID_STRING_RUN_COOL_STARTUP[]="������";
#endif
//Cool Startup
const char str_en_ID_STRING_RUN_COOL_STARTUP[]="Cool Startup";

//------ ID_STRING_RUN_SETTING --------
//�޸Ķ�ֵ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RUN_SETTING[]={10171,10099,10024,10059};
#else
const char str_cn_ID_STRING_RUN_SETTING[]="�޸Ķ�ֵ";
#endif
//Modify Setting
const char str_en_ID_STRING_RUN_SETTING[]="Modify Setting";

//------ ID_STRING_RUN_FRAM_INIT --------
//FRAM��ʼ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RUN_FRAM_INIT[]={70,82,65,77,10223,10077,10040};
#else
const char str_cn_ID_STRING_RUN_FRAM_INIT[]="FRAM��ʼ��";
#endif
//Init. FRAM 
const char str_en_ID_STRING_RUN_FRAM_INIT[]="Init. FRAM ";

//------ ID_STRING_RUN_INTO_DEBUGING --------
//�������̬��..
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RUN_INTO_DEBUGING[]={10236,10204,10229,10142,10034,10135,46,46};
#else
const char str_cn_ID_STRING_RUN_INTO_DEBUGING[]="�������̬��..";
#endif
//In Debug \nEntering..
const char str_en_ID_STRING_RUN_INTO_DEBUGING[]="In Debug \nEntering..";

//------ ID_STRING_RUN_OUTOF_DEBUGING --------
//�˳�����̬��..
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RUN_OUTOF_DEBUGING[]={10119,10225,10229,10142,10034,10135,46,46};
#else
const char str_cn_ID_STRING_RUN_OUTOF_DEBUGING[]="�˳�����̬��..";
#endif
//In Debug \nExiting...
const char str_en_ID_STRING_RUN_OUTOF_DEBUGING[]="In Debug \nExiting...";

//------ ID_STRING_RUN_INTO_DEBUG --------
//�������̬
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RUN_INTO_DEBUG[]={10236,10204,10229,10142,10034};
#else
const char str_cn_ID_STRING_RUN_INTO_DEBUG[]="�������̬";
#endif
//Enter Debug
const char str_en_ID_STRING_RUN_INTO_DEBUG[]="Enter Debug";

//------ ID_STRING_RUN_OUTOF_DEBUG --------
//�˳�����̬
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RUN_OUTOF_DEBUG[]={10119,10225,10229,10142,10034};
#else
const char str_cn_ID_STRING_RUN_OUTOF_DEBUG[]="�˳�����̬";
#endif
//Exit Debug
const char str_en_ID_STRING_RUN_OUTOF_DEBUG[]="Exit Debug";

//------ ID_STRING_MEASTYPE_ALL --------
//��ʾ������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEASTYPE_ALL[]={10143,10084,10239,10134,10087};
#else
const char str_cn_ID_STRING_MEASTYPE_ALL[]="��ʾ������";
#endif
//All Data
const char str_en_ID_STRING_MEASTYPE_ALL[]="All Data";

//------ ID_STRING_MEASTYPE_SIGNAL --------
//��ʾ�ź���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEASTYPE_SIGNAL[]={10143,10084,10103,10101,10087};
#else
const char str_cn_ID_STRING_MEASTYPE_SIGNAL[]="��ʾ�ź���";
#endif
//Signal Data
const char str_en_ID_STRING_MEASTYPE_SIGNAL[]="Signal Data";

//------ ID_STRING_MEASTYPE_STATUS --------
//��ʾ״̬��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEASTYPE_STATUS[]={10143,10084,10055,10034,10087};
#else
const char str_cn_ID_STRING_MEASTYPE_STATUS[]="��ʾ״̬��";
#endif
//Status
const char str_en_ID_STRING_MEASTYPE_STATUS[]="Status";

//------ ID_STRING_MEASTYPE_MEAS --------
//��ʾ����ֵ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEASTYPE_MEAS[]={10143,10084,10178,10087,10059};
#else
const char str_cn_ID_STRING_MEASTYPE_MEAS[]="��ʾ����ֵ";
#endif
//Meas Data
const char str_en_ID_STRING_MEASTYPE_MEAS[]="Meas Data";

//------ ID_STRING_MEAS_GATAGE --------
//բ�ſ���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_GATAGE[]={10006,10102,10027,10110};
#else
const char str_cn_ID_STRING_MEAS_GATAGE[]="բ�ſ���";
#endif
//Gatage
const char str_en_ID_STRING_MEAS_GATAGE[]="Gatage";

//------ ID_STRING_MEASTYPE_CODEDATA --------
//����ֵ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEASTYPE_CODEDATA[]={10174,10202,10059};
#else
const char str_cn_ID_STRING_MEASTYPE_CODEDATA[]="����ֵ";
#endif
//Enc Data
const char str_en_ID_STRING_MEASTYPE_CODEDATA[]="Enc Data";

//------ ID_STRING_MEAS_CODEDATA_L --------
//����ֵ��λ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_CODEDATA_L[]={10174,10202,10059,10122,10075};
#else
const char str_cn_ID_STRING_MEAS_CODEDATA_L[]="����ֵ��λ";
#endif
//Enc Data_H
const char str_en_ID_STRING_MEAS_CODEDATA_L[]="Enc Data_H";

//------ ID_STRING_MEAS_CODEDATA_H --------
//����ֵ��λ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_CODEDATA_H[]={10174,10202,10059,10172,10075};
#else
const char str_cn_ID_STRING_MEAS_CODEDATA_H[]="����ֵ��λ";
#endif
//Enc Data_H
const char str_en_ID_STRING_MEAS_CODEDATA_H[]="Enc Data_H";

//------ ID_STRING_MEAS_AI1 --------
//�������1
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_AI1[]={10187,10204,10193,10231,49};
#else
const char str_cn_ID_STRING_MEAS_AI1[]="�������1";
#endif
//AIn No1
const char str_en_ID_STRING_MEAS_AI1[]="AIn No1";

//------ ID_STRING_MEAS_AI2 --------
//�������2
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_AI2[]={10187,10204,10193,10231,50};
#else
const char str_cn_ID_STRING_MEAS_AI2[]="�������2";
#endif
//AIn No2
const char str_en_ID_STRING_MEAS_AI2[]="AIn No2";

//------ ID_STRING_MEAS_AO --------
//�������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_AO[]={10187,10225,10193,10231};
#else
const char str_cn_ID_STRING_MEAS_AO[]="�������";
#endif
//AOut
const char str_en_ID_STRING_MEAS_AO[]="AOut";

//------ ID_STRING_MEAS_ADCODE --------
//AD��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_ADCODE[]={65,68,10202};
#else
const char str_cn_ID_STRING_MEAS_ADCODE[]="AD��";
#endif
//AD Code
const char str_en_ID_STRING_MEAS_ADCODE[]="AD Code";

//------ ID_STRING_MEAS_LED --------
//�� ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_LED[]={10103,32,10104};
#else
const char str_cn_ID_STRING_MEAS_LED[]="�� ��";
#endif
//LED
const char str_en_ID_STRING_MEAS_LED[]="LED";

//------ ID_STRING_MEAS_GATESTATUS --------
//բ��״̬
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_GATESTATUS[]={10006,10102,10055,10034};
#else
const char str_cn_ID_STRING_MEAS_GATESTATUS[]="բ��״̬";
#endif
//Gate Status
const char str_en_ID_STRING_MEAS_GATESTATUS[]="Gate Status";

//------ ID_STRING_MEAS_SIG_DI --------
//����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_SIG_DI[]={10027,10204};
#else
const char str_cn_ID_STRING_MEAS_SIG_DI[]="����";
#endif
//DI
const char str_en_ID_STRING_MEAS_SIG_DI[]="DI";

//------ ID_STRING_MEAS_SIG_DO --------
//����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_SIG_DO[]={10027,10225};
#else
const char str_cn_ID_STRING_MEAS_SIG_DO[]="����";
#endif
//DO
const char str_en_ID_STRING_MEAS_SIG_DO[]="DO";

//------ ID_STRING_MEAS_SIG_SELFCHK --------
//�� �Լ�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_SIG_SELFCHK[]={10103,32,10147,10206};
#else
const char str_cn_ID_STRING_MEAS_SIG_SELFCHK[]="�� �Լ�";
#endif
//Self-check
const char str_en_ID_STRING_MEAS_SIG_SELFCHK[]="Self-check";

//------ ID_STRING_MEAS_SIG_SELFCHKEX --------
//�� �Լ� 
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_SIG_SELFCHKEX[]={10103,32,10147,10206,32};
#else
const char str_cn_ID_STRING_MEAS_SIG_SELFCHKEX[]="�� �Լ� ";
#endif
//Self-checkEx
const char str_en_ID_STRING_MEAS_SIG_SELFCHKEX[]="Self-checkEx";

//------ ID_STRING_MEAS_SIG_TOTAL --------
//�� ���ź�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MEAS_SIG_TOTAL[]={10103,32,10167,10103,10101};
#else
const char str_cn_ID_STRING_MEAS_SIG_TOTAL[]="�� ���ź�";
#endif
//Total Signal
const char str_en_ID_STRING_MEAS_SIG_TOTAL[]="Total Signal";

//------ ID_STRING_CONTROL --------
//Ĭ�ϻ���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CONTROL[]={10033,10129,10035,10192};
#else
const char str_cn_ID_STRING_CONTROL[]="Ĭ�ϻ���";
#endif
//Default Screen
const char str_en_ID_STRING_CONTROL[]="Default Screen";

//------ ID_STRING_STATUS --------
//������ʾ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_STATUS[]={10178,10087,10143,10084};
#else
const char str_cn_ID_STRING_STATUS[]="������ʾ";
#endif
//Meas. 
const char str_en_ID_STRING_STATUS[]="Meas. ";

//------ ID_STRING_SYSINFO --------
//ϵͳ��Ϣ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SYSINFO[]={10058,10048,10103,10005};
#else
const char str_cn_ID_STRING_SYSINFO[]="ϵͳ��Ϣ";
#endif
//System Info.
const char str_en_ID_STRING_SYSINFO[]="System Info.";

//------ ID_STRING_SYSSET --------
//ϵͳ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SYSSET[]={10058,10048,10195,10097};
#else
const char str_cn_ID_STRING_SYSSET[]="ϵͳ����";
#endif
//System Cfg.
const char str_en_ID_STRING_SYSSET[]="System Cfg.";

//------ ID_STRING_PRJSET --------
//��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJSET[]={10012,10121,10195,10097};
#else
const char str_cn_ID_STRING_PRJSET[]="��������";
#endif
//Project Cfg.
const char str_en_ID_STRING_PRJSET[]="Project Cfg.";

//------ ID_STRING_DEVICEMODEL --------
//װ������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEVICEMODEL[]={10043,10097,10185,10097};
#else
const char str_cn_ID_STRING_DEVICEMODEL[]="װ������";
#endif
//Field Cfg.
const char str_en_ID_STRING_DEVICEMODEL[]="Field Cfg.";

//------ ID_STRING_DEBUG --------
//װ�õ���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEBUG[]={10043,10097,10229,10142};
#else
const char str_cn_ID_STRING_DEBUG[]="װ�õ���";
#endif
//Device Debug
const char str_en_ID_STRING_DEBUG[]="Device Debug";

//------ ID_STRING_OTHER --------
//��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_OTHER[]={10186,10243,10195,10097};
#else
const char str_cn_ID_STRING_OTHER[]="��������";
#endif
//Other Settings
const char str_en_ID_STRING_OTHER[]="Other Settings";

//------ ID_STRING_STA_MEAS --------
//��������ʾ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_STA_MEAS[]={10178,10087,10087,10143,10084};
#else
const char str_cn_ID_STRING_STA_MEAS[]="��������ʾ";
#endif
//Meas. Value
const char str_en_ID_STRING_STA_MEAS[]="Meas. Value";

//------ ID_STRING_STA_LOOP --------
//ѭ����ʾ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_STA_LOOP[]={10036,10064,10143,10084};
#else
const char str_cn_ID_STRING_STA_LOOP[]="ѭ����ʾ";
#endif
//Disp Loop
const char str_en_ID_STRING_STA_LOOP[]="Disp Loop";

//------ ID_STRING_STA_PROT --------
//��������ʾ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_STA_PROT[]={10007,10013,10087,10143,10084};
#else
const char str_cn_ID_STRING_STA_PROT[]="��������ʾ";
#endif
//Prot. Value
const char str_en_ID_STRING_STA_PROT[]="Prot. Value";

//------ ID_STRING_STA_STAS --------
//״̬����ʾ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_STA_STAS[]={10055,10034,10087,10143,10084};
#else
const char str_cn_ID_STRING_STA_STAS[]="״̬����ʾ";
#endif
//Status
const char str_en_ID_STRING_STA_STAS[]="Status";

//------ ID_STRING_SYSSET_PWVALUE --------
//�û�����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SYSSET_PWVALUE[]={10096,10019,10166,10202};
#else
const char str_cn_ID_STRING_SYSSET_PWVALUE[]="�û�����";
#endif
//User Password
const char str_en_ID_STRING_SYSSET_PWVALUE[]="User Password";

//------ ID_STRING_SYSSET_ETH --------
//��̫��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SYSSET_ETH[]={10146,10032,10238,10162,10195,10097};
#else
const char str_cn_ID_STRING_SYSSET_ETH[]="��̫��������";
#endif
//ETH Settings
const char str_en_ID_STRING_SYSSET_ETH[]="ETH Settings";

//------ ID_STRING_SYSSET_COM --------
//485�˿�����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SYSSET_COM[]={52,56,53,10118,10162,10195,10097};
#else
const char str_cn_ID_STRING_SYSSET_COM[]="485�˿�����";
#endif
//COM Settings
const char str_en_ID_STRING_SYSSET_COM[]="COM Settings";

//------ ID_STRING_SYSSET_AO --------
//4~20mA���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SYSSET_AO[]={52,126,50,48,109,65,10187,10225};
#else
const char str_cn_ID_STRING_SYSSET_AO[]="4~20mA���";
#endif
//4-20mA Output
const char str_en_ID_STRING_SYSSET_AO[]="4-20mA Output";

//------ ID_STRING_PRJSET_RANGE --------
//��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJSET_RANGE[]={10087,10121,10195,10097};
#else
const char str_cn_ID_STRING_PRJSET_RANGE[]="��������";
#endif
//Range Settings
const char str_en_ID_STRING_PRJSET_RANGE[]="Range Settings";

//------ ID_STRING_PRJSET_PRESET --------
//Ԥ�迪������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJSET_PRESET[]={10014,10195,10027,10110,10195,10097};
#else
const char str_cn_ID_STRING_PRJSET_PRESET[]="Ԥ�迪������";
#endif
//Preset Setting
const char str_en_ID_STRING_PRJSET_PRESET[]="Preset Setting";

//------ ID_STRING_PRJSET_ARCSET --------
//���ֶ�����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJSET_ARCSET[]={10001,10149,10126,10195,10097};
#else
const char str_cn_ID_STRING_PRJSET_ARCSET[]="���ֶ�����";
#endif
//Arc Settings
const char str_en_ID_STRING_PRJSET_ARCSET[]="Arc Settings";

//------ ID_STRING_PRJSET_SLOPESET --------
//����б������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_PRJSET_SLOPESET[]={10230,10126,10046,10115,10195,10097};
#else
const char str_cn_ID_STRING_PRJSET_SLOPESET[]="����б������";
#endif
//Slope Setting
const char str_en_ID_STRING_PRJSET_SLOPESET[]="Slope Setting";

//------ ID_STRING_CLOCK --------
//ʱ������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CLOCK[]={10045,10140,10195,10097};
#else
const char str_cn_ID_STRING_CLOCK[]="ʱ������";
#endif
//Clock
const char str_en_ID_STRING_CLOCK[]="Clock";

//------ ID_STRING_SYSSET_LANG --------
//����ѡ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SYSSET_LANG[]={10214,10145,10003,10217};
#else
const char str_cn_ID_STRING_SYSSET_LANG[]="����ѡ��";
#endif
//Language
const char str_en_ID_STRING_SYSSET_LANG[]="Language";

//------ ID_STRING_DEVICEMODEL_MEASPRECIS --------
//���������ֶ�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEVICEMODEL_MEASPRECIS[]={10178,10087,10030,10110,10151,10039};
#else
const char str_cn_ID_STRING_DEVICEMODEL_MEASPRECIS[]="���������ֶ�";
#endif
//Prot. Gains 
const char str_en_ID_STRING_DEVICEMODEL_MEASPRECIS[]="Prot. Gains ";

//------ ID_STRING_DEVICEMODEL_MODEL --------
//װ��ѡ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEVICEMODEL_MODEL[]={10043,10097,10003,10185};
#else
const char str_cn_ID_STRING_DEVICEMODEL_MODEL[]="װ��ѡ��";
#endif
//Field Cfg.
const char str_en_ID_STRING_DEVICEMODEL_MODEL[]="Field Cfg.";

//------ ID_STRING_DEVICEMODEL_DI --------
//DIԤ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEVICEMODEL_DI[]={68,73,10014,10024,10189};
#else
const char str_cn_ID_STRING_DEVICEMODEL_DI[]="DIԤ����";
#endif
//DI Predefine
const char str_en_ID_STRING_DEVICEMODEL_DI[]="DI Predefine";

//------ ID_STRING_DEVICEMODEL_DO --------
//DOԤ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEVICEMODEL_DO[]={68,79,10014,10024,10189};
#else
const char str_cn_ID_STRING_DEVICEMODEL_DO[]="DOԤ����";
#endif
//DO Predefine
const char str_en_ID_STRING_DEVICEMODEL_DO[]="DO Predefine";

//------ ID_STRING_INIT_DEFAULT --------
//�ָ���������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_INIT_DEFAULT[]={10150,10050,10225,10018,10195,10097};
#else
const char str_cn_ID_STRING_INIT_DEFAULT[]="�ָ���������";
#endif
//Restore Default\nSettings
const char str_en_ID_STRING_INIT_DEFAULT[]="Restore Default\nSettings";

//------ ID_STRING_SCREEN --------
//��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SCREEN[]={10194,10192,10195,10097};
#else
const char str_cn_ID_STRING_SCREEN[]="��������";
#endif
//Screen Cfg.
const char str_en_ID_STRING_SCREEN[]="Screen Cfg.";

//------ ID_STRING_VERTTYPE --------
//��ֱ������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_VERTTYPE[]={10069,10047,10226,10039,10224};
#else
const char str_cn_ID_STRING_VERTTYPE[]="��ֱ������";
#endif
//Vert. Bar Mode
const char str_en_ID_STRING_VERTTYPE[]="Vert. Bar Mode";

//------ ID_STRING_VERTTYPE_NUM --------
//��ʾ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_VERTTYPE_NUM[]={10143,10084,10249,10153};
#else
const char str_cn_ID_STRING_VERTTYPE_NUM[]="��ʾ����";
#endif
//Num.
const char str_en_ID_STRING_VERTTYPE_NUM[]="Num.";

//------ ID_STRING_VERTTYPE_GRAP1 --------
//��ʾͼ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_VERTTYPE_GRAP1[]={10143,10084,10078,10199};
#else
const char str_cn_ID_STRING_VERTTYPE_GRAP1[]="��ʾͼ��";
#endif
//Icon
const char str_en_ID_STRING_VERTTYPE_GRAP1[]="Icon";

//------ ID_STRING_VERTTYPE_GRAP2 --------
//��ʾ������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_VERTTYPE_GRAP2[]={10143,10084,10226,10039,10224};
#else
const char str_cn_ID_STRING_VERTTYPE_GRAP2[]="��ʾ������";
#endif
//Scroll Bar
const char str_en_ID_STRING_VERTTYPE_GRAP2[]="Scroll Bar";

//------ ID_STRING_MENU_LEFTRIGHT --------
//�˵�ˮƽ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MENU_LEFTRIGHT[]={10117,10015,10038,10080,10226,10039};
#else
const char str_cn_ID_STRING_MENU_LEFTRIGHT[]="�˵�ˮƽ����";
#endif
//Hori. Bar Mode
const char str_en_ID_STRING_MENU_LEFTRIGHT[]="Hori. Bar Mode";

//------ ID_STRING_DEFAULT_SCREEN --------
//Ĭ����ʾ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DEFAULT_SCREEN[]={10033,10129,10143,10084,10194,10192};
#else
const char str_cn_ID_STRING_DEFAULT_SCREEN[]="Ĭ����ʾ����";
#endif
//Default Screen
const char str_en_ID_STRING_DEFAULT_SCREEN[]="Default Screen";

//------ ID_STRING_MAIN_MENU_STYLE --------
//���˵���ʽ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MAIN_MENU_STYLE[]={10234,10117,10015,10240,10081};
#else
const char str_cn_ID_STRING_MAIN_MENU_STYLE[]="���˵���ʽ";
#endif
//Main Menu Style
const char str_en_ID_STRING_MAIN_MENU_STYLE[]="Main Menu Style";

//------ ID_STRING_MAIN_MENU_STYLE_NORMAL --------
//�˵���ʽ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MAIN_MENU_STYLE_NORMAL[]={10117,10015,10240,10081};
#else
const char str_cn_ID_STRING_MAIN_MENU_STYLE_NORMAL[]="�˵���ʽ";
#endif
//Menu Style
const char str_en_ID_STRING_MAIN_MENU_STYLE_NORMAL[]="Menu Style";

//------ ID_STRING_MAIN_MENU_STYLE_ICON --------
//ͼ����ʽ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MAIN_MENU_STYLE_ICON[]={10078,10199,10240,10081};
#else
const char str_cn_ID_STRING_MAIN_MENU_STYLE_ICON[]="ͼ����ʽ";
#endif
//Icon Style
const char str_en_ID_STRING_MAIN_MENU_STYLE_ICON[]="Icon Style";

//------ ID_STRING_DO_CHECK --------
//�������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_CHECK[]={10027,10225,10206,10196};
#else
const char str_cn_ID_STRING_DO_CHECK[]="�������";
#endif
//Do Check
const char str_en_ID_STRING_DO_CHECK[]="Do Check";

//------ ID_STRING_DI_CHECK --------
//������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_CHECK[]={10027,10204,10206,10196};
#else
const char str_cn_ID_STRING_DI_CHECK[]="������";
#endif
//Di Check
const char str_en_ID_STRING_DI_CHECK[]="Di Check";

//------ ID_STRING_AO_CHECK --------
//4~20mA���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_AO_CHECK[]={52,126,50,48,109,65,10187,10225};
#else
const char str_cn_ID_STRING_AO_CHECK[]="4~20mA���";
#endif
//4-20mA Output
const char str_en_ID_STRING_AO_CHECK[]="4-20mA Output";

//------ ID_STRING_CLEAR_CODE --------
//����ֵ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CLEAR_CODE[]={10174,10202,10059,10197,10181};
#else
const char str_cn_ID_STRING_CLEAR_CODE[]="����ֵ����";
#endif
//Claer EnCoder
const char str_en_ID_STRING_CLEAR_CODE[]="Claer EnCoder";

//------ ID_STRING_COMM_MONITOR --------
//���ļ���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_COMM_MONITOR[]={10022,10100,10175,10139};
#else
const char str_cn_ID_STRING_COMM_MONITOR[]="���ļ���";
#endif
//Comm Monitor
const char str_en_ID_STRING_COMM_MONITOR[]="Comm Monitor";

//------ ID_STRING_MAIN_VERSION --------
//װ�ð汾
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MAIN_VERSION[]={10043,10097,10190,10083};
#else
const char str_cn_ID_STRING_MAIN_VERSION[]="װ�ð汾";
#endif
//Device Ver.
const char str_en_ID_STRING_MAIN_VERSION[]="Device Ver.";

//------ ID_STRING_YEAR --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_YEAR[]={10200};
#else
const char str_cn_ID_STRING_YEAR[]="��";
#endif
//Year
const char str_en_ID_STRING_YEAR[]="Year";

//------ ID_STRING_MONTH --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MONTH[]={10094};
#else
const char str_cn_ID_STRING_MONTH[]="��";
#endif
//Month
const char str_en_ID_STRING_MONTH[]="Month";

//------ ID_STRING_DAY --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DAY[]={10148};
#else
const char str_cn_ID_STRING_DAY[]="��";
#endif
//Day
const char str_en_ID_STRING_DAY[]="Day";

//------ ID_STRING_HOUR --------
//ʱ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_HOUR[]={10045};
#else
const char str_cn_ID_STRING_HOUR[]="ʱ";
#endif
//Hour
const char str_en_ID_STRING_HOUR[]="Hour";

//------ ID_STRING_MIN --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_MIN[]={10149};
#else
const char str_cn_ID_STRING_MIN[]="��";
#endif
//Minute
const char str_en_ID_STRING_MIN[]="Minute";

//------ ID_STRING_SEC --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SEC[]={10203};
#else
const char str_cn_ID_STRING_SEC[]="��";
#endif
//Second
const char str_en_ID_STRING_SEC[]="Second";

//------ ID_STRING_COMMFLT --------
//ͨѶ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_COMMFLT[]={10026,10062,10114,10131};
#else
const char str_cn_ID_STRING_COMMFLT[]="ͨѶ����";
#endif
//Com. Failure
const char str_en_ID_STRING_COMMFLT[]="Com. Failure";

//------ ID_STRING_STATUS_STOP --------
//ֹͣ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_STATUS_STOP[]={10010,10071};
#else
const char str_cn_ID_STRING_STATUS_STOP[]="ֹͣ";
#endif
//Stop
const char str_en_ID_STRING_STATUS_STOP[]="Stop";

//------ ID_STRING_STATUS_RUN --------
//�˶�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_STATUS_RUN[]={10120,10039};
#else
const char str_cn_ID_STRING_STATUS_RUN[]="�˶�";
#endif
//Running
const char str_en_ID_STRING_STATUS_RUN[]="Running";

//------ ID_STRING_BRANDING --------
//�Ƽ�����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_BRANDING[]={10106,10076,10169,10170};
#else
const char str_cn_ID_STRING_BRANDING[]="�Ƽ�����";
#endif
//CopyRight2007
const char str_en_ID_STRING_BRANDING[]="CopyRight2007";

//------ ID_STRING_WISCOM --------
//��ɫ�ǻ�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_WISCOM[]={10215,10031,10109,10164};
#else
const char str_cn_ID_STRING_WISCOM[]="��ɫ�ǻ�";
#endif
//Wiscom System
const char str_en_ID_STRING_WISCOM[]="Wiscom System";

//------ ID_STRING_NOMEAS --------
//�޲�����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_NOMEAS[]={10169,10178,10087,10087};
#else
const char str_cn_ID_STRING_NOMEAS[]="�޲�����";
#endif
//No Meas.
const char str_en_ID_STRING_NOMEAS[]="No Meas.";

//------ ID_STRING_ACT_RESULT_WARNING --------
//�澯
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ACT_RESULT_WARNING[]={10191,10041};
#else
const char str_cn_ID_STRING_ACT_RESULT_WARNING[]="�澯";
#endif
//Warning
const char str_en_ID_STRING_ACT_RESULT_WARNING[]="Warning";

//------ ID_STRING_ERR_UNKNOWN --------
//ͨѶ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_UNKNOWN[]={10026,10062,10225,10209};
#else
const char str_cn_ID_STRING_ERR_UNKNOWN[]="ͨѶ����";
#endif
//ERR Com.
const char str_en_ID_STRING_ERR_UNKNOWN[]="ERR Com.";

//------ ID_STRING_ERR_CHECKSUM --------
//У���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_CHECKSUM[]={10011,10198,10123};
#else
const char str_cn_ID_STRING_ERR_CHECKSUM[]="У���";
#endif
//ERR CheckSum
const char str_en_ID_STRING_ERR_CHECKSUM[]="ERR CheckSum";

//------ ID_STRING_ERR_SETRANGE --------
//��ֵ��Χ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_SETRANGE[]={10024,10059,10061,10021,10209};
#else
const char str_cn_ID_STRING_ERR_SETRANGE[]="��ֵ��Χ��";
#endif
//ERR OverRange
const char str_en_ID_STRING_ERR_SETRANGE[]="ERR OverRange";

//------ ID_STRING_ERR_TIME_ILLEGAL --------
//ʱ�䲻�Ϸ�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_TIME_ILLEGAL[]={10045,10183,10073,10128,10025};
#else
const char str_cn_ID_STRING_ERR_TIME_ILLEGAL[]="ʱ�䲻�Ϸ�";
#endif
//ERR Illegal
const char str_en_ID_STRING_ERR_TIME_ILLEGAL[]="ERR Illegal";

//------ ID_STRING_ERR_UNREMOTE --------
//װ�ò���Զ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_UNREMOTE[]={10043,10097,10073,10163,10063,10079};
#else
const char str_cn_ID_STRING_ERR_UNREMOTE[]="װ�ò���Զ��";
#endif
//ERR UnRemote
const char str_en_ID_STRING_ERR_UNREMOTE[]="ERR UnRemote";

//------ ID_STRING_ERR_MODIFYSET_CANCEL --------
//�޸Ķ�ֵ\n������ȡ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_MODIFYSET_CANCEL[]={10171,10099,10024,10059,13,10,10108,10250,10008,10002,10244};
#else
const char str_cn_ID_STRING_ERR_MODIFYSET_CANCEL[]="�޸Ķ�ֵ\n������ȡ��";
#endif
//ERR Abnormal\nCancel On Set.
const char str_en_ID_STRING_ERR_MODIFYSET_CANCEL[]="ERR Abnormal\nCancel On Set.";

//------ ID_STRING_ERR_UNKNOW_CODE --------
//δָ֪��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_UNKNOW_CODE[]={10052,10028,10068,10211};
#else
const char str_cn_ID_STRING_ERR_UNKNOW_CODE[]="δָ֪��";
#endif
//Unknow Code
const char str_en_ID_STRING_ERR_UNKNOW_CODE[]="Unknow Code";

//------ ID_STRING_ERR_RECHECK --------
//��У����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_RECHECK[]={10056,10011,10209,10221};
#else
const char str_cn_ID_STRING_ERR_RECHECK[]="��У����";
#endif
//ERR CheckSum
const char str_en_ID_STRING_ERR_RECHECK[]="ERR CheckSum";

//------ ID_STRING_ERR_UNDEBUG --------
//װ�ò���\n����λ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_UNDEBUG[]={10043,10097,10073,10163,13,10,10229,10142,10075,10097};
#else
const char str_cn_ID_STRING_ERR_UNDEBUG[]="װ�ò���\n����λ��";
#endif
//ERR UnDebug \nMode
const char str_en_ID_STRING_ERR_UNDEBUG[]="ERR UnDebug \nMode";

//------ ID_STRING_ERR_SEQUENCE --------
//�������д���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_SEQUENCE[]={10022,10100,10219,10132,10209,10221};
#else
const char str_cn_ID_STRING_ERR_SEQUENCE[]="�������д���";
#endif
//ERR Message\nSequence
const char str_en_ID_STRING_ERR_SEQUENCE[]="ERR Message\nSequence";

//------ ID_STRING_ERR_UNLOCAL --------
// װ�ò���\n�͵�λ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_UNLOCAL[]={32,10043,10097,10073,10163,13,10,10124,10155,10075,10097};
#else
const char str_cn_ID_STRING_ERR_UNLOCAL[]=" װ�ò���\n�͵�λ��";
#endif
//ERR UnLocal
const char str_en_ID_STRING_ERR_UNLOCAL[]="ERR UnLocal";

//------ ID_STRING_ERR_UNKNOW_SETID --------
//δ֪���������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_UNKNOW_SETID[]={10052,10028,10098,10195,10097,10219,10101};
#else
const char str_cn_ID_STRING_ERR_UNKNOW_SETID[]="δ֪���������";
#endif
//UnKnown \nSetting ID
const char str_en_ID_STRING_ERR_UNKNOW_SETID[]="UnKnown \nSetting ID";

//------ ID_STRING_ERR_MESSAGE_CRASH --------
//���Ľṹ������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_MESSAGE_CRASH[]={10022,10100,10177,10070,10073,10201,10245};
#else
const char str_cn_ID_STRING_ERR_MESSAGE_CRASH[]="���Ľṹ������";
#endif
//ERR Message\nCrash
const char str_en_ID_STRING_ERR_MESSAGE_CRASH[]="ERR Message\nCrash";

//------ ID_STRING_ERR_CONTROL_ILLEGAL --------
//���ƷǷ�\n������ִ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_CONTROL_ILLEGAL[]={10156,10107,10108,10025,13,10,10073,10116,10210,10054,10133};
#else
const char str_cn_ID_STRING_ERR_CONTROL_ILLEGAL[]="���ƷǷ�\n������ִ��";
#endif
//ERR Control\nIllegal
const char str_en_ID_STRING_ERR_CONTROL_ILLEGAL[]="ERR Control\nIllegal";

//------ ID_STRING_ERR_DISABLE_CODE --------
//ָ�����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_DISABLE_CODE[]={10068,10211,10073,10116,10210};
#else
const char str_cn_ID_STRING_ERR_DISABLE_CODE[]="ָ�����";
#endif
//Prohibited \ninstruction
const char str_en_ID_STRING_ERR_DISABLE_CODE[]="Prohibited \ninstruction";

//------ ID_STRING_ERR_OPERATE --------
//����ʧ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_OPERATE[]={10160,10235,10020,10165};
#else
const char str_cn_ID_STRING_ERR_OPERATE[]="����ʧ��";
#endif
//Operate Failure
const char str_en_ID_STRING_ERR_OPERATE[]="Operate Failure";

//------ ID_STRING_OPERATING --------
//����ִ����...
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_OPERATING[]={10160,10235,10054,10133,10135,46,46,46};
#else
const char str_cn_ID_STRING_OPERATING[]="����ִ����...";
#endif
//Operating...
const char str_en_ID_STRING_OPERATING[]="Operating...";

//------ ID_STRING_ERR_OVER_RANGE --------
//��ΧԽ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_OVER_RANGE[]={10061,10021,10082,10194};
#else
const char str_cn_ID_STRING_ERR_OVER_RANGE[]="��ΧԽ��";
#endif
//Over Range
const char str_en_ID_STRING_ERR_OVER_RANGE[]="Over Range";

//------ ID_STRING_ERR_CTRLCMD_CHECK_CONTROLMODE --------
//�������\n��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_CTRLCMD_CHECK_CONTROLMODE[]={10073,10116,10210,10095,13,10,10156,10107,10246,10211};
#else
const char str_cn_ID_STRING_ERR_CTRLCMD_CHECK_CONTROLMODE[]="�������\n��������";
#endif
//Error Control\nMode
const char str_en_ID_STRING_ERR_CTRLCMD_CHECK_CONTROLMODE[]="Error Control\nMode";

//------ ID_STRING_CTRLCMD_CHECK_HAVEOPERA --------
//��ǰ����\nִ��ָ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CTRLCMD_CHECK_HAVEOPERA[]={10044,10042,10250,10163,13,10,10054,10133,10068,10211};
#else
const char str_cn_ID_STRING_CTRLCMD_CHECK_HAVEOPERA[]="��ǰ����\nִ��ָ��";
#endif
//Instruction\nExecuting!
const char str_en_ID_STRING_CTRLCMD_CHECK_HAVEOPERA[]="Instruction\nExecuting!";

//------ ID_STRING_SEARCHING --------
//������...
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_SEARCHING[]={10136,10233,10135,46,46,46};
#else
const char str_cn_ID_STRING_SEARCHING[]="������...";
#endif
//Searching....
const char str_en_ID_STRING_SEARCHING[]="Searching....";

//------ ID_STRING_STARTING_TIME --------
//������ʱ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_STARTING_TIME[]={10222,10039,10096,10045};
#else
const char str_cn_ID_STRING_STARTING_TIME[]="������ʱ";
#endif
//Startup time
const char str_en_ID_STRING_STARTING_TIME[]="Startup time";

//------ ID_STRING_OP_CONFIRM --------
//����ִ�У�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_OP_CONFIRM[]={10160,10235,10054,10133,10085};
#else
const char str_cn_ID_STRING_OP_CONFIRM[]="����ִ�У�";
#endif
//Operation\nConfirm?
const char str_en_ID_STRING_OP_CONFIRM[]="Operation\nConfirm?";

//------ ID_STRING_ERROR_PASWORD --------
//�������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERROR_PASWORD[]={10166,10202,10209,10221,10000};
#else
const char str_cn_ID_STRING_ERROR_PASWORD[]="�������";
#endif
//PassWord\nError!
const char str_en_ID_STRING_ERROR_PASWORD[]="PassWord\nError!";

//------ ID_STRING_DI_DI1 --------
//����1
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI1[]={10027,10204,49};
#else
const char str_cn_ID_STRING_DI_DI1[]="����1";
#endif
//DI1
const char str_en_ID_STRING_DI_DI1[]="DI1";

//------ ID_STRING_DI_DI2 --------
//����2
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI2[]={10027,10204,50};
#else
const char str_cn_ID_STRING_DI_DI2[]="����2";
#endif
//DI2
const char str_en_ID_STRING_DI_DI2[]="DI2";

//------ ID_STRING_DI_DI3 --------
//����3
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI3[]={10027,10204,51};
#else
const char str_cn_ID_STRING_DI_DI3[]="����3";
#endif
//DI3
const char str_en_ID_STRING_DI_DI3[]="DI3";

//------ ID_STRING_DI_DI4 --------
//����4
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI4[]={10027,10204,52};
#else
const char str_cn_ID_STRING_DI_DI4[]="����4";
#endif
//DI4
const char str_en_ID_STRING_DI_DI4[]="DI4";

//------ ID_STRING_DI_DI5 --------
//����5
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI5[]={10027,10204,53};
#else
const char str_cn_ID_STRING_DI_DI5[]="����5";
#endif
//DI5
const char str_en_ID_STRING_DI_DI5[]="DI5";

//------ ID_STRING_DI_DI6 --------
//����6
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI6[]={10027,10204,54};
#else
const char str_cn_ID_STRING_DI_DI6[]="����6";
#endif
//DI6
const char str_en_ID_STRING_DI_DI6[]="DI6";

//------ ID_STRING_DI_DI7 --------
//����7
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI7[]={10027,10204,55};
#else
const char str_cn_ID_STRING_DI_DI7[]="����7";
#endif
//DI7
const char str_en_ID_STRING_DI_DI7[]="DI7";

//------ ID_STRING_DI_DI8 --------
//����8
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI8[]={10027,10204,56};
#else
const char str_cn_ID_STRING_DI_DI8[]="����8";
#endif
//DI8
const char str_en_ID_STRING_DI_DI8[]="DI8";

//------ ID_STRING_DI_DI9 --------
//����9
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI9[]={10027,10204,57};
#else
const char str_cn_ID_STRING_DI_DI9[]="����9";
#endif
//DI9
const char str_en_ID_STRING_DI_DI9[]="DI9";

//------ ID_STRING_DI_DI10 --------
//����10
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI10[]={10027,10204,49,48};
#else
const char str_cn_ID_STRING_DI_DI10[]="����10";
#endif
//DI10
const char str_en_ID_STRING_DI_DI10[]="DI10";

//------ ID_STRING_DI_DI11 --------
//����11
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI11[]={10027,10204,49,49};
#else
const char str_cn_ID_STRING_DI_DI11[]="����11";
#endif
//DI11
const char str_en_ID_STRING_DI_DI11[]="DI11";

//------ ID_STRING_DI_DI12 --------
//����12
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_DI12[]={10027,10204,49,50};
#else
const char str_cn_ID_STRING_DI_DI12[]="����12";
#endif
//DI12
const char str_en_ID_STRING_DI_DI12[]="DI12";

//------ ID_STRING_DI_UPPER_LIMIT --------
//բλ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_UPPER_LIMIT[]={10006,10075,10130,10170};
#else
const char str_cn_ID_STRING_DI_UPPER_LIMIT[]="բλ����";
#endif
//Upper Limit
const char str_en_ID_STRING_DI_UPPER_LIMIT[]="Upper Limit";

//------ ID_STRING_DI_LOWER_LIMIT --------
//բλ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_LOWER_LIMIT[]={10006,10075,10092,10170};
#else
const char str_cn_ID_STRING_DI_LOWER_LIMIT[]="բλ����";
#endif
//Lower Limit
const char str_en_ID_STRING_DI_LOWER_LIMIT[]="Lower Limit";

//------ ID_STRING_DI_OVER_UPPER --------
//բλ������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_OVER_UPPER[]={10006,10075,10130,10130,10170};
#else
const char str_cn_ID_STRING_DI_OVER_UPPER[]="բλ������";
#endif
//Over Upper
const char str_en_ID_STRING_DI_OVER_UPPER[]="Over Upper";

//------ ID_STRING_DI_BELOW_LOWER --------
//բλ������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_BELOW_LOWER[]={10006,10075,10092,10092,10170};
#else
const char str_cn_ID_STRING_DI_BELOW_LOWER[]="բλ������";
#endif
//Below Lower
const char str_en_ID_STRING_DI_BELOW_LOWER[]="Below Lower";

//------ ID_STRING_DI_GATE_RISE --------
//բ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_GATE_RISE[]={10006,10102,10248};
#else
const char str_cn_ID_STRING_DI_GATE_RISE[]="բ����";
#endif
//Gate Rise
const char str_en_ID_STRING_DI_GATE_RISE[]="Gate Rise";

//------ ID_STRING_DI_GATE_FALL --------
//բ�Ž�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_GATE_FALL[]={10006,10102,10057};
#else
const char str_cn_ID_STRING_DI_GATE_FALL[]="բ�Ž�";
#endif
//Gate Fall
const char str_en_ID_STRING_DI_GATE_FALL[]="Gate Fall";

//------ ID_STRING_DI_BREAK_STATE --------
//��·��״̬
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_BREAK_STATE[]={10127,10065,10232,10055,10034};
#else
const char str_cn_ID_STRING_DI_BREAK_STATE[]="��·��״̬";
#endif
//Break State
const char str_en_ID_STRING_DI_BREAK_STATE[]="Break State";

//------ ID_STRING_DI_OVER_LOAD1 --------
//�������ź�1
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_OVER_LOAD1[]={10247,10072,10112,10103,10101,49};
#else
const char str_cn_ID_STRING_DI_OVER_LOAD1[]="�������ź�1";
#endif
//Over Load 1
const char str_en_ID_STRING_DI_OVER_LOAD1[]="Over Load 1";

//------ ID_STRING_DI_OVER_LOAD2 --------
//�������ź�2
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_OVER_LOAD2[]={10247,10072,10112,10103,10101,50};
#else
const char str_cn_ID_STRING_DI_OVER_LOAD2[]="�������ź�2";
#endif
//Over Load 2
const char str_en_ID_STRING_DI_OVER_LOAD2[]="Over Load 2";

//------ ID_STRING_DI_OVER_LOAD3 --------
//�������ź�3
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_OVER_LOAD3[]={10247,10072,10112,10103,10101,51};
#else
const char str_cn_ID_STRING_DI_OVER_LOAD3[]="�������ź�3";
#endif
//Over Load 3
const char str_en_ID_STRING_DI_OVER_LOAD3[]="Over Load 3";

//------ ID_STRING_DI_OVER_LOAD4 --------
//�������ź�4
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_OVER_LOAD4[]={10247,10072,10112,10103,10101,52};
#else
const char str_cn_ID_STRING_DI_OVER_LOAD4[]="�������ź�4";
#endif
//Over Load 4
const char str_en_ID_STRING_DI_OVER_LOAD4[]="Over Load 4";

//------ ID_STRING_DI_REMOTE_LOCAL --------
//Զ��/�ֵ�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_REMOTE_LOCAL[]={10063,10079,47,10152,10155};
#else
const char str_cn_ID_STRING_DI_REMOTE_LOCAL[]="Զ��/�ֵ�";
#endif
//Remote/Local
const char str_en_ID_STRING_DI_REMOTE_LOCAL[]="Remote/Local";

//------ ID_STRING_DO_DO1 --------
//����1
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_DO1[]={10027,10225,49};
#else
const char str_cn_ID_STRING_DO_DO1[]="����1";
#endif
//DO1
const char str_en_ID_STRING_DO_DO1[]="DO1";

//------ ID_STRING_DO_DO2 --------
//����2
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_DO2[]={10027,10225,50};
#else
const char str_cn_ID_STRING_DO_DO2[]="����2";
#endif
//DO2
const char str_en_ID_STRING_DO_DO2[]="DO2";

//------ ID_STRING_DO_DO3 --------
//����3
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_DO3[]={10027,10225,51};
#else
const char str_cn_ID_STRING_DO_DO3[]="����3";
#endif
//DO3
const char str_en_ID_STRING_DO_DO3[]="DO3";

//------ ID_STRING_DO_DO4 --------
//����4
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_DO4[]={10027,10225,52};
#else
const char str_cn_ID_STRING_DO_DO4[]="����4";
#endif
//DO4
const char str_en_ID_STRING_DO_DO4[]="DO4";

//------ ID_STRING_DO_DO5 --------
//����5
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_DO5[]={10027,10225,53};
#else
const char str_cn_ID_STRING_DO_DO5[]="����5";
#endif
//DO5
const char str_en_ID_STRING_DO_DO5[]="DO5";

//------ ID_STRING_DO_DO6 --------
//����6
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_DO6[]={10027,10225,54};
#else
const char str_cn_ID_STRING_DO_DO6[]="����6";
#endif
//DO6
const char str_en_ID_STRING_DO_DO6[]="DO6";

//------ ID_STRING_DO_RISE_GATE --------
//��բ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_RISE_GATE[]={10248,10006,10102};
#else
const char str_cn_ID_STRING_DO_RISE_GATE[]="��բ��";
#endif
//Rise Gate
const char str_en_ID_STRING_DO_RISE_GATE[]="Rise Gate";

//------ ID_STRING_DO_FALL_GATE --------
//��բ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_FALL_GATE[]={10057,10006,10102};
#else
const char str_cn_ID_STRING_DO_FALL_GATE[]="��բ��";
#endif
//Fall Gate
const char str_en_ID_STRING_DO_FALL_GATE[]="Fall Gate";

//------ ID_STRING_DO_STOP_GATE --------
//ͣբ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_STOP_GATE[]={10010,10006,10102};
#else
const char str_cn_ID_STRING_DO_STOP_GATE[]="ͣբ��";
#endif
//Stop Gate
const char str_en_ID_STRING_DO_STOP_GATE[]="Stop Gate";

//------ ID_STRING_DO_CLOSE_BREAK --------
//��բ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_CLOSE_BREAK[]={10128,10006};
#else
const char str_cn_ID_STRING_DO_CLOSE_BREAK[]="��բ";
#endif
//Close Break
const char str_en_ID_STRING_DO_CLOSE_BREAK[]="Close Break";

//------ ID_STRING_DO_TRIP_BREAK --------
//��բ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_TRIP_BREAK[]={10149,10006};
#else
const char str_cn_ID_STRING_DO_TRIP_BREAK[]="��բ";
#endif
//Trip Break
const char str_en_ID_STRING_DO_TRIP_BREAK[]="Trip Break";

//------ ID_STRING_OPEN --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_OPEN[]={10149};
#else
const char str_cn_ID_STRING_OPEN[]="��";
#endif
//Trip
const char str_en_ID_STRING_OPEN[]="Trip";

//------ ID_STRING_CLOSE --------
//��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CLOSE[]={10128};
#else
const char str_cn_ID_STRING_CLOSE[]="��";
#endif
//Close
const char str_en_ID_STRING_CLOSE[]="Close";

//------ ID_STRING_NOMENUITEM --------
//�޲˵���Ŀ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_NOMENUITEM[]={10169,10117,10015,10212,10088};
#else
const char str_cn_ID_STRING_NOMENUITEM[]="�޲˵���Ŀ";
#endif
//No Menu Item
const char str_en_ID_STRING_NOMENUITEM[]="No Menu Item";

//------ ID_STRING_COMPILETIME --------
//����ʱ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_COMPILETIME[]={10174,10205,10045,10183};
#else
const char str_cn_ID_STRING_COMPILETIME[]="����ʱ��";
#endif
//Compile Time
const char str_en_ID_STRING_COMPILETIME[]="Compile Time";

//------ ID_STRING_CFGLOADTIME --------
//���ü���ʱ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CFGLOADTIME[]={10185,10097,10137,10158,10045,10183};
#else
const char str_cn_ID_STRING_CFGLOADTIME[]="���ü���ʱ��";
#endif
//File LoadTime
const char str_en_ID_STRING_CFGLOADTIME[]="File LoadTime";

//------ ID_STRING_LOADTIME --------
//ϵͳ����ʱ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_LOADTIME[]={10058,10048,10137,10158,10045,10183};
#else
const char str_cn_ID_STRING_LOADTIME[]="ϵͳ����ʱ��";
#endif
//OS LoadTime
const char str_en_ID_STRING_LOADTIME[]="OS LoadTime";

//------ ID_STRING_OLD_PW --------
//ԭ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_OLD_PW[]={10037,10166,10202};
#else
const char str_cn_ID_STRING_OLD_PW[]="ԭ����";
#endif
//Old Password
const char str_en_ID_STRING_OLD_PW[]="Old Password";

//------ ID_STRING_NEW_PW2 --------
//ȷ��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_NEW_PW2[]={10066,10129,10093,10166,10202};
#else
const char str_cn_ID_STRING_NEW_PW2[]="ȷ��������";
#endif
//Confirm Password
const char str_en_ID_STRING_NEW_PW2[]="Confirm Password";

//------ ID_STRING_NEW_PW --------
//����������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_NEW_PW[]={10187,10204,10093,10166,10202};
#else
const char str_cn_ID_STRING_NEW_PW[]="����������";
#endif
//New Password
const char str_en_ID_STRING_NEW_PW[]="New Password";

//------ ID_STRING_DO1_PULSEWIDTH --------
//DO1ʱ�䶨��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO1_PULSEWIDTH[]={68,79,49,10045,10183,10024,10189};
#else
const char str_cn_ID_STRING_DO1_PULSEWIDTH[]="DO1ʱ�䶨��";
#endif
//DO1 Pulse Width
const char str_en_ID_STRING_DO1_PULSEWIDTH[]="DO1 Pulse Width";

//------ ID_STRING_DO2_PULSEWIDTH --------
//DO2ʱ�䶨��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO2_PULSEWIDTH[]={68,79,50,10045,10183,10024,10189};
#else
const char str_cn_ID_STRING_DO2_PULSEWIDTH[]="DO2ʱ�䶨��";
#endif
//DO2 Pulse Width
const char str_en_ID_STRING_DO2_PULSEWIDTH[]="DO2 Pulse Width";

//------ ID_STRING_DO3_PULSEWIDTH --------
//DO3ʱ�䶨��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO3_PULSEWIDTH[]={68,79,51,10045,10183,10024,10189};
#else
const char str_cn_ID_STRING_DO3_PULSEWIDTH[]="DO3ʱ�䶨��";
#endif
//DO3 Pulse Width
const char str_en_ID_STRING_DO3_PULSEWIDTH[]="DO3 Pulse Width";

//------ ID_STRING_DO4_PULSEWIDTH --------
//DO4ʱ�䶨��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO4_PULSEWIDTH[]={68,79,52,10045,10183,10024,10189};
#else
const char str_cn_ID_STRING_DO4_PULSEWIDTH[]="DO4ʱ�䶨��";
#endif
//DO4 Pulse Width
const char str_en_ID_STRING_DO4_PULSEWIDTH[]="DO4 Pulse Width";

//------ ID_STRING_DI_SWITCHOFF --------
//��բ״̬
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_SWITCHOFF[]={10149,10006,10055,10034};
#else
const char str_cn_ID_STRING_DI_SWITCHOFF[]="��բ״̬";
#endif
//Breaker Triped
const char str_en_ID_STRING_DI_SWITCHOFF[]="Breaker Triped";

//------ ID_STRING_DI_SWITCHON --------
//��բ״̬
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_SWITCHON[]={10128,10006,10055,10034};
#else
const char str_cn_ID_STRING_DI_SWITCHON[]="��բ״̬";
#endif
//Breaker Closed
const char str_en_ID_STRING_DI_SWITCHON[]="Breaker Closed";

//------ ID_STRING_DI_CMDSWITCHOFF --------
//��բ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_CMDSWITCHOFF[]={10149,10006,10246,10211};
#else
const char str_cn_ID_STRING_DI_CMDSWITCHOFF[]="��բ����";
#endif
//Trip Command
const char str_en_ID_STRING_DI_CMDSWITCHOFF[]="Trip Command";

//------ ID_STRING_DI_CMDSWITCHON --------
//��բ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DI_CMDSWITCHON[]={10128,10006,10246,10211};
#else
const char str_cn_ID_STRING_DI_CMDSWITCHON[]="��բ����";
#endif
//Close Command
const char str_en_ID_STRING_DI_CMDSWITCHON[]="Close Command";

//------ ID_STRING_CONTROL_SWITCHOFF_COMM --------
//ͨ�ŷ�բ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CONTROL_SWITCHOFF_COMM[]={10026,10103,10149,10006};
#else
const char str_cn_ID_STRING_CONTROL_SWITCHOFF_COMM[]="ͨ�ŷ�բ";
#endif
//Communication\nTrip
const char str_en_ID_STRING_CONTROL_SWITCHOFF_COMM[]="Communication\nTrip";

//------ ID_STRING_CONTROL_SWITCHON_COMM --------
//ͨ�ź�բ
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CONTROL_SWITCHON_COMM[]={10026,10103,10128,10006};
#else
const char str_cn_ID_STRING_CONTROL_SWITCHON_COMM[]="ͨ�ź�բ";
#endif
//Communication\nClose
const char str_en_ID_STRING_CONTROL_SWITCHON_COMM[]="Communication\nClose";

//------ ID_STRING_READING_SYSINIT_INFO --------
//����ʼ����Ϣ..
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_READING_SYSINIT_INFO[]={10090,10223,10077,10040,10103,10005,46,46};
#else
const char str_cn_ID_STRING_READING_SYSINIT_INFO[]="����ʼ����Ϣ..";
#endif
//Reading\nSystem Info...
const char str_en_ID_STRING_READING_SYSINIT_INFO[]="Reading\nSystem Info...";

//------ ID_STRING_ERR_PASSWORD --------
//�������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_PASSWORD[]={10166,10202,10209,10221,10000};
#else
const char str_cn_ID_STRING_ERR_PASSWORD[]="�������";
#endif
//Password ERR!
const char str_en_ID_STRING_ERR_PASSWORD[]="Password ERR!";

//------ ID_STRING_ERR_OVERRANGE --------
//��ֵԽ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_OVERRANGE[]={10249,10059,10082,10194};
#else
const char str_cn_ID_STRING_ERR_OVERRANGE[]="��ֵԽ��";
#endif
//Over Range
const char str_en_ID_STRING_ERR_OVERRANGE[]="Over Range";

//------ ID_STRING_CONFIRM --------
//ȷ���޸� 
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CONFIRM[]={10066,10129,10171,10099,32};
#else
const char str_cn_ID_STRING_CONFIRM[]="ȷ���޸� ";
#endif
//Confirm Modify
const char str_en_ID_STRING_CONFIRM[]="Confirm Modify";

//------ ID_STRING_ERR_TIME --------
//ʱ����Ϣ����
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_ERR_TIME[]={10045,10140,10103,10005,10209,10221};
#else
const char str_cn_ID_STRING_ERR_TIME[]="ʱ����Ϣ����";
#endif
//Clock Time ERR
const char str_en_ID_STRING_ERR_TIME[]="Clock Time ERR";

//------ ID_STRING_NO_ABNORMAL --------
//û���쳣
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_NO_ABNORMAL[]={10074,10134,10207,10008};
#else
const char str_cn_ID_STRING_NO_ABNORMAL[]="û���쳣";
#endif
//No Abnormal
const char str_en_ID_STRING_NO_ABNORMAL[]="No Abnormal";

//------ ID_STRING_OPERATION_SUCCESS --------
//�����ɹ�
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_OPERATION_SUCCESS[]={10160,10235,10111,10017};
#else
const char str_cn_ID_STRING_OPERATION_SUCCESS[]="�����ɹ�";
#endif
//Operate Success
const char str_en_ID_STRING_OPERATION_SUCCESS[]="Operate Success";

//------ ID_STRING_DO_OFF2ON --------
//��->��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_OFF2ON[]={10149,45,62,10128};
#else
const char str_cn_ID_STRING_DO_OFF2ON[]="��->��";
#endif
//0->1
const char str_en_ID_STRING_DO_OFF2ON[]="0->1";

//------ ID_STRING_DO_ON2OFF --------
//��->��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DO_ON2OFF[]={10128,45,62,10149};
#else
const char str_cn_ID_STRING_DO_ON2OFF[]="��->��";
#endif
//1->0
const char str_en_ID_STRING_DO_ON2OFF[]="1->0";

//------ ID_STRING_RESET_CONFIRM --------
//ȷ�ϸ��飿
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RESET_CONFIRM[]={10066,10129,10050,10197,10085};
#else
const char str_cn_ID_STRING_RESET_CONFIRM[]="ȷ�ϸ��飿";
#endif
//Confirm Revert?
const char str_en_ID_STRING_RESET_CONFIRM[]="Confirm Revert?";

//------ ID_STRING_RESET --------
//װ�ø���
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RESET[]={10043,10097,10050,10197};
#else
const char str_cn_ID_STRING_RESET[]="װ�ø���";
#endif
//Reset
const char str_en_ID_STRING_RESET[]="Reset";

//------ ID_STRING_RESTART --------
//װ������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RESTART[]={10043,10097,10159,10222};
#else
const char str_cn_ID_STRING_RESTART[]="װ������";
#endif
//Restart
const char str_en_ID_STRING_RESTART[]="Restart";

//------ ID_STRING_RESTART_CONFIRM --------
//ȷ��������
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_RESTART_CONFIRM[]={10066,10129,10159,10222,10085};
#else
const char str_cn_ID_STRING_RESTART_CONFIRM[]="ȷ��������";
#endif
//Confirm Restart?
const char str_en_ID_STRING_RESTART_CONFIRM[]="Confirm Restart?";

//------ ID_STRING_CONFIG_VERSION --------
//�����ļ��汾
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_CONFIG_VERSION[]={10185,10097,10100,10252,10190,10083};
#else
const char str_cn_ID_STRING_CONFIG_VERSION[]="�����ļ��汾";
#endif
//CfgFlie Ver.
const char str_en_ID_STRING_CONFIG_VERSION[]="CfgFlie Ver.";

//------ ID_STRING_NOW_TIME --------
//��ǰʱ��
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_NOW_TIME[]={10044,10042,10045,10183};
#else
const char str_cn_ID_STRING_NOW_TIME[]="��ǰʱ��";
#endif
//Current Time
const char str_en_ID_STRING_NOW_TIME[]="Current Time";

//------ ID_STRING_DOWNLOAD --------
//�ļ�������...
#ifdef _ZILIB
const INT16U str_cn_ID_STRING_DOWNLOAD[]={10100,10252,10092,10158,10135,46,46,46};
#else
const char str_cn_ID_STRING_DOWNLOAD[]="�ļ�������...";
#endif
//Downloading...
const char str_en_ID_STRING_DOWNLOAD[]="Downloading...";


const STR_RES StringRes[]=
{
	{str_cn_ID_STRING_NONE,sizeof(str_cn_ID_STRING_NONE)/_PER_SIZE,str_en_ID_STRING_NONE,sizeof(str_en_ID_STRING_NONE)},
	{str_cn_ID_STRING_SETVAL_EXIT,sizeof(str_cn_ID_STRING_SETVAL_EXIT)/_PER_SIZE,str_en_ID_STRING_SETVAL_EXIT,sizeof(str_en_ID_STRING_SETVAL_EXIT)},
	{str_cn_ID_STRING_LOCAL,sizeof(str_cn_ID_STRING_LOCAL)/_PER_SIZE,str_en_ID_STRING_LOCAL,sizeof(str_en_ID_STRING_LOCAL)},
	{str_cn_ID_STRING_REMOTE,sizeof(str_cn_ID_STRING_REMOTE)/_PER_SIZE,str_en_ID_STRING_REMOTE,sizeof(str_en_ID_STRING_REMOTE)},
	{str_cn_ID_STRING_DI_LOCALREMOTE,sizeof(str_cn_ID_STRING_DI_LOCALREMOTE)/_PER_SIZE,str_en_ID_STRING_DI_LOCALREMOTE,sizeof(str_en_ID_STRING_DI_LOCALREMOTE)},
	{str_cn_ID_STRING_HAVE,sizeof(str_cn_ID_STRING_HAVE)/_PER_SIZE,str_en_ID_STRING_HAVE,sizeof(str_en_ID_STRING_HAVE)},
	{str_cn_ID_STRING_HAVENOT,sizeof(str_cn_ID_STRING_HAVENOT)/_PER_SIZE,str_en_ID_STRING_HAVENOT,sizeof(str_en_ID_STRING_HAVENOT)},
	{str_cn_ID_STRING_ENABLE,sizeof(str_cn_ID_STRING_ENABLE)/_PER_SIZE,str_en_ID_STRING_ENABLE,sizeof(str_en_ID_STRING_ENABLE)},
	{str_cn_ID_STRING_DISABLE,sizeof(str_cn_ID_STRING_DISABLE)/_PER_SIZE,str_en_ID_STRING_DISABLE,sizeof(str_en_ID_STRING_DISABLE)},
	{str_cn_ID_STRING_PASSWORD,sizeof(str_cn_ID_STRING_PASSWORD)/_PER_SIZE,str_en_ID_STRING_PASSWORD,sizeof(str_en_ID_STRING_PASSWORD)},
	{str_cn_ID_STRING_SC_COMM_485,sizeof(str_cn_ID_STRING_SC_COMM_485)/_PER_SIZE,str_en_ID_STRING_SC_COMM_485,sizeof(str_en_ID_STRING_SC_COMM_485)},
	{str_cn_ID_STRING_SC_COMM_ETH,sizeof(str_cn_ID_STRING_SC_COMM_ETH)/_PER_SIZE,str_en_ID_STRING_SC_COMM_ETH,sizeof(str_en_ID_STRING_SC_COMM_ETH)},
	{str_cn_ID_STRING_SC_COMM_ADDRESS,sizeof(str_cn_ID_STRING_SC_COMM_ADDRESS)/_PER_SIZE,str_en_ID_STRING_SC_COMM_ADDRESS,sizeof(str_en_ID_STRING_SC_COMM_ADDRESS)},
	{str_cn_ID_STRING_SC_ETH_IP1,sizeof(str_cn_ID_STRING_SC_ETH_IP1)/_PER_SIZE,str_en_ID_STRING_SC_ETH_IP1,sizeof(str_en_ID_STRING_SC_ETH_IP1)},
	{str_cn_ID_STRING_SC_ETH_IP2,sizeof(str_cn_ID_STRING_SC_ETH_IP2)/_PER_SIZE,str_en_ID_STRING_SC_ETH_IP2,sizeof(str_en_ID_STRING_SC_ETH_IP2)},
	{str_cn_ID_STRING_SC_ETH_IP3,sizeof(str_cn_ID_STRING_SC_ETH_IP3)/_PER_SIZE,str_en_ID_STRING_SC_ETH_IP3,sizeof(str_en_ID_STRING_SC_ETH_IP3)},
	{str_cn_ID_STRING_SC_ETH_IP4,sizeof(str_cn_ID_STRING_SC_ETH_IP4)/_PER_SIZE,str_en_ID_STRING_SC_ETH_IP4,sizeof(str_en_ID_STRING_SC_ETH_IP4)},
	{str_cn_ID_STRING_SC_ETH_MASK1,sizeof(str_cn_ID_STRING_SC_ETH_MASK1)/_PER_SIZE,str_en_ID_STRING_SC_ETH_MASK1,sizeof(str_en_ID_STRING_SC_ETH_MASK1)},
	{str_cn_ID_STRING_SC_ETH_MASK2,sizeof(str_cn_ID_STRING_SC_ETH_MASK2)/_PER_SIZE,str_en_ID_STRING_SC_ETH_MASK2,sizeof(str_en_ID_STRING_SC_ETH_MASK2)},
	{str_cn_ID_STRING_SC_ETH_MASK3,sizeof(str_cn_ID_STRING_SC_ETH_MASK3)/_PER_SIZE,str_en_ID_STRING_SC_ETH_MASK3,sizeof(str_en_ID_STRING_SC_ETH_MASK3)},
	{str_cn_ID_STRING_SC_ETH_MASK4,sizeof(str_cn_ID_STRING_SC_ETH_MASK4)/_PER_SIZE,str_en_ID_STRING_SC_ETH_MASK4,sizeof(str_en_ID_STRING_SC_ETH_MASK4)},
	{str_cn_ID_STRING_SC_COM_BAUDRATE,sizeof(str_cn_ID_STRING_SC_COM_BAUDRATE)/_PER_SIZE,str_en_ID_STRING_SC_COM_BAUDRATE,sizeof(str_en_ID_STRING_SC_COM_BAUDRATE)},
	{str_cn_ID_STRING_SC_LANGUAGE,sizeof(str_cn_ID_STRING_SC_LANGUAGE)/_PER_SIZE,str_en_ID_STRING_SC_LANGUAGE,sizeof(str_en_ID_STRING_SC_LANGUAGE)},
	{str_cn_ID_STRING_SC_LANGUAGE_CN,sizeof(str_cn_ID_STRING_SC_LANGUAGE_CN)/_PER_SIZE,str_en_ID_STRING_SC_LANGUAGE_CN,sizeof(str_en_ID_STRING_SC_LANGUAGE_CN)},
	{str_cn_ID_STRING_SC_LANGUAGE_EN,sizeof(str_cn_ID_STRING_SC_LANGUAGE_EN)/_PER_SIZE,str_en_ID_STRING_SC_LANGUAGE_EN,sizeof(str_en_ID_STRING_SC_LANGUAGE_EN)},
	{str_cn_ID_STRING_SC_SCREENSAVE,sizeof(str_cn_ID_STRING_SC_SCREENSAVE)/_PER_SIZE,str_en_ID_STRING_SC_SCREENSAVE,sizeof(str_en_ID_STRING_SC_SCREENSAVE)},
	{str_cn_ID_STRING_SC_COMM_BAUDRATE_4800,sizeof(str_cn_ID_STRING_SC_COMM_BAUDRATE_4800)/_PER_SIZE,str_en_ID_STRING_SC_COMM_BAUDRATE_4800,sizeof(str_en_ID_STRING_SC_COMM_BAUDRATE_4800)},
	{str_cn_ID_STRING_SC_COMM_BAUDRATE_9600,sizeof(str_cn_ID_STRING_SC_COMM_BAUDRATE_9600)/_PER_SIZE,str_en_ID_STRING_SC_COMM_BAUDRATE_9600,sizeof(str_en_ID_STRING_SC_COMM_BAUDRATE_9600)},
	{str_cn_ID_STRING_SC_COMM_BAUDRATE_19200,sizeof(str_cn_ID_STRING_SC_COMM_BAUDRATE_19200)/_PER_SIZE,str_en_ID_STRING_SC_COMM_BAUDRATE_19200,sizeof(str_en_ID_STRING_SC_COMM_BAUDRATE_19200)},
	{str_cn_ID_STRING_SC_COMM_BAUDRATE_38400,sizeof(str_cn_ID_STRING_SC_COMM_BAUDRATE_38400)/_PER_SIZE,str_en_ID_STRING_SC_COMM_BAUDRATE_38400,sizeof(str_en_ID_STRING_SC_COMM_BAUDRATE_38400)},
	{str_cn_ID_STRING_SC_COMM_BAUDRATE_57600,sizeof(str_cn_ID_STRING_SC_COMM_BAUDRATE_57600)/_PER_SIZE,str_en_ID_STRING_SC_COMM_BAUDRATE_57600,sizeof(str_en_ID_STRING_SC_COMM_BAUDRATE_57600)},
	{str_cn_ID_STRING_SC_COMM_BAUDRATE_115200,sizeof(str_cn_ID_STRING_SC_COMM_BAUDRATE_115200)/_PER_SIZE,str_en_ID_STRING_SC_COMM_BAUDRATE_115200,sizeof(str_en_ID_STRING_SC_COMM_BAUDRATE_115200)},
	{str_cn_ID_STRING_SC_COM_DATAB,sizeof(str_cn_ID_STRING_SC_COM_DATAB)/_PER_SIZE,str_en_ID_STRING_SC_COM_DATAB,sizeof(str_en_ID_STRING_SC_COM_DATAB)},
	{str_cn_ID_STRING_SC_COM_STOPB,sizeof(str_cn_ID_STRING_SC_COM_STOPB)/_PER_SIZE,str_en_ID_STRING_SC_COM_STOPB,sizeof(str_en_ID_STRING_SC_COM_STOPB)},
	{str_cn_ID_STRING_SC_COM_PARITYB,sizeof(str_cn_ID_STRING_SC_COM_PARITYB)/_PER_SIZE,str_en_ID_STRING_SC_COM_PARITYB,sizeof(str_en_ID_STRING_SC_COM_PARITYB)},
	{str_cn_ID_STRING_PRJ_RANGE,sizeof(str_cn_ID_STRING_PRJ_RANGE)/_PER_SIZE,str_en_ID_STRING_PRJ_RANGE,sizeof(str_en_ID_STRING_PRJ_RANGE)},
	{str_cn_ID_STRING_PRJ_HIGHEST,sizeof(str_cn_ID_STRING_PRJ_HIGHEST)/_PER_SIZE,str_en_ID_STRING_PRJ_HIGHEST,sizeof(str_en_ID_STRING_PRJ_HIGHEST)},
	{str_cn_ID_STRING_PRJ_ZEROCODE,sizeof(str_cn_ID_STRING_PRJ_ZEROCODE)/_PER_SIZE,str_en_ID_STRING_PRJ_ZEROCODE,sizeof(str_en_ID_STRING_PRJ_ZEROCODE)},
	{str_cn_ID_STRING_PRJ_HIGHCODE,sizeof(str_cn_ID_STRING_PRJ_HIGHCODE)/_PER_SIZE,str_en_ID_STRING_PRJ_HIGHCODE,sizeof(str_en_ID_STRING_PRJ_HIGHCODE)},
	{str_cn_ID_STRING_PRJ_PRESET,sizeof(str_cn_ID_STRING_PRJ_PRESET)/_PER_SIZE,str_en_ID_STRING_PRJ_PRESET,sizeof(str_en_ID_STRING_PRJ_PRESET)},
	{str_cn_ID_STRING_PRJ_ARCNUM,sizeof(str_cn_ID_STRING_PRJ_ARCNUM)/_PER_SIZE,str_en_ID_STRING_PRJ_ARCNUM,sizeof(str_en_ID_STRING_PRJ_ARCNUM)},
	{str_cn_ID_STRING_PRJ_GATAGE,sizeof(str_cn_ID_STRING_PRJ_GATAGE)/_PER_SIZE,str_en_ID_STRING_PRJ_GATAGE,sizeof(str_en_ID_STRING_PRJ_GATAGE)},
	{str_cn_ID_STRING_PRJ_CODERDATA,sizeof(str_cn_ID_STRING_PRJ_CODERDATA)/_PER_SIZE,str_en_ID_STRING_PRJ_CODERDATA,sizeof(str_en_ID_STRING_PRJ_CODERDATA)},
	{str_cn_ID_STRING_PRJ_SLOPE,sizeof(str_cn_ID_STRING_PRJ_SLOPE)/_PER_SIZE,str_en_ID_STRING_PRJ_SLOPE,sizeof(str_en_ID_STRING_PRJ_SLOPE)},
	{str_cn_ID_STRING_DEV_DIRECTION,sizeof(str_cn_ID_STRING_DEV_DIRECTION)/_PER_SIZE,str_en_ID_STRING_DEV_DIRECTION,sizeof(str_en_ID_STRING_DEV_DIRECTION)},
	{str_cn_ID_STRING_DEV_CALCMETHOD,sizeof(str_cn_ID_STRING_DEV_CALCMETHOD)/_PER_SIZE,str_en_ID_STRING_DEV_CALCMETHOD,sizeof(str_en_ID_STRING_DEV_CALCMETHOD)},
	{str_cn_ID_STRING_DEV_DATASOURSE,sizeof(str_cn_ID_STRING_DEV_DATASOURSE)/_PER_SIZE,str_en_ID_STRING_DEV_DATASOURSE,sizeof(str_en_ID_STRING_DEV_DATASOURSE)},
	{str_cn_ID_STRING_DEV_ENCODERTYPE,sizeof(str_cn_ID_STRING_DEV_ENCODERTYPE)/_PER_SIZE,str_en_ID_STRING_DEV_ENCODERTYPE,sizeof(str_en_ID_STRING_DEV_ENCODERTYPE)},
	{str_cn_ID_STRING_DEV_CODETYPE,sizeof(str_cn_ID_STRING_DEV_CODETYPE)/_PER_SIZE,str_en_ID_STRING_DEV_CODETYPE,sizeof(str_en_ID_STRING_DEV_CODETYPE)},
	{str_cn_ID_STRING_DEV_METHOD_LINE,sizeof(str_cn_ID_STRING_DEV_METHOD_LINE)/_PER_SIZE,str_en_ID_STRING_DEV_METHOD_LINE,sizeof(str_en_ID_STRING_DEV_METHOD_LINE)},
	{str_cn_ID_STRING_DEV_METHOD_TABLE,sizeof(str_cn_ID_STRING_DEV_METHOD_TABLE)/_PER_SIZE,str_en_ID_STRING_DEV_METHOD_TABLE,sizeof(str_en_ID_STRING_DEV_METHOD_TABLE)},
	{str_cn_ID_STRING_DEV_DATA_ENCODER,sizeof(str_cn_ID_STRING_DEV_DATA_ENCODER)/_PER_SIZE,str_en_ID_STRING_DEV_DATA_ENCODER,sizeof(str_en_ID_STRING_DEV_DATA_ENCODER)},
	{str_cn_ID_STRING_DEV_DATA_AD,sizeof(str_cn_ID_STRING_DEV_DATA_AD)/_PER_SIZE,str_en_ID_STRING_DEV_DATA_AD,sizeof(str_en_ID_STRING_DEV_DATA_AD)},
	{str_cn_ID_STRING_DEV_GATE_COROTATION,sizeof(str_cn_ID_STRING_DEV_GATE_COROTATION)/_PER_SIZE,str_en_ID_STRING_DEV_GATE_COROTATION,sizeof(str_en_ID_STRING_DEV_GATE_COROTATION)},
	{str_cn_ID_STRING_DEV_GATE_ROLLBACK,sizeof(str_cn_ID_STRING_DEV_GATE_ROLLBACK)/_PER_SIZE,str_en_ID_STRING_DEV_GATE_ROLLBACK,sizeof(str_en_ID_STRING_DEV_GATE_ROLLBACK)},
	{str_cn_ID_STRING_DEV_ENCODE_NONE,sizeof(str_cn_ID_STRING_DEV_ENCODE_NONE)/_PER_SIZE,str_en_ID_STRING_DEV_ENCODE_NONE,sizeof(str_en_ID_STRING_DEV_ENCODE_NONE)},
	{str_cn_ID_STRING_DEV_ENCODE_PARALLEL,sizeof(str_cn_ID_STRING_DEV_ENCODE_PARALLEL)/_PER_SIZE,str_en_ID_STRING_DEV_ENCODE_PARALLEL,sizeof(str_en_ID_STRING_DEV_ENCODE_PARALLEL)},
	{str_cn_ID_STRING_DEV_ENCODE_SSI,sizeof(str_cn_ID_STRING_DEV_ENCODE_SSI)/_PER_SIZE,str_en_ID_STRING_DEV_ENCODE_SSI,sizeof(str_en_ID_STRING_DEV_ENCODE_SSI)},
	{str_cn_ID_STRING_DEV_ENCODE_INCREMENTAL,sizeof(str_cn_ID_STRING_DEV_ENCODE_INCREMENTAL)/_PER_SIZE,str_en_ID_STRING_DEV_ENCODE_INCREMENTAL,sizeof(str_en_ID_STRING_DEV_ENCODE_INCREMENTAL)},
	{str_cn_ID_STRING_DEV_CODE_GRAY,sizeof(str_cn_ID_STRING_DEV_CODE_GRAY)/_PER_SIZE,str_en_ID_STRING_DEV_CODE_GRAY,sizeof(str_en_ID_STRING_DEV_CODE_GRAY)},
	{str_cn_ID_STRING_DEV_CODE_BCD,sizeof(str_cn_ID_STRING_DEV_CODE_BCD)/_PER_SIZE,str_en_ID_STRING_DEV_CODE_BCD,sizeof(str_en_ID_STRING_DEV_CODE_BCD)},
	{str_cn_ID_STRING_DEV_CODE_BINARY,sizeof(str_cn_ID_STRING_DEV_CODE_BINARY)/_PER_SIZE,str_en_ID_STRING_DEV_CODE_BINARY,sizeof(str_en_ID_STRING_DEV_CODE_BINARY)},
	{str_cn_ID_STRING_DEV_ADDACHOICE,sizeof(str_cn_ID_STRING_DEV_ADDACHOICE)/_PER_SIZE,str_en_ID_STRING_DEV_ADDACHOICE,sizeof(str_en_ID_STRING_DEV_ADDACHOICE)},
	{str_cn_ID_STRING_DEV_NONE_ADDA,sizeof(str_cn_ID_STRING_DEV_NONE_ADDA)/_PER_SIZE,str_en_ID_STRING_DEV_NONE_ADDA,sizeof(str_en_ID_STRING_DEV_NONE_ADDA)},
	{str_cn_ID_STRING_DEV_ADDA,sizeof(str_cn_ID_STRING_DEV_ADDA)/_PER_SIZE,str_en_ID_STRING_DEV_ADDA,sizeof(str_en_ID_STRING_DEV_ADDA)},
	{str_cn_ID_STRING_DEV_TWOAD,sizeof(str_cn_ID_STRING_DEV_TWOAD)/_PER_SIZE,str_en_ID_STRING_DEV_TWOAD,sizeof(str_en_ID_STRING_DEV_TWOAD)},
	{str_cn_ID_STRING_DEV_ONEDA,sizeof(str_cn_ID_STRING_DEV_ONEDA)/_PER_SIZE,str_en_ID_STRING_DEV_ONEDA,sizeof(str_en_ID_STRING_DEV_ONEDA)},
	{str_cn_ID_STRING_DEV_DIDOCONFIG,sizeof(str_cn_ID_STRING_DEV_DIDOCONFIG)/_PER_SIZE,str_en_ID_STRING_DEV_DIDOCONFIG,sizeof(str_en_ID_STRING_DEV_DIDOCONFIG)},
	{str_cn_ID_STRING_DEV_DIGITALTIME,sizeof(str_cn_ID_STRING_DEV_DIGITALTIME)/_PER_SIZE,str_en_ID_STRING_DEV_DIGITALTIME,sizeof(str_en_ID_STRING_DEV_DIGITALTIME)},
	{str_cn_ID_STRING_DC_DIDOCONFIG_DEFAULT,sizeof(str_cn_ID_STRING_DC_DIDOCONFIG_DEFAULT)/_PER_SIZE,str_en_ID_STRING_DC_DIDOCONFIG_DEFAULT,sizeof(str_en_ID_STRING_DC_DIDOCONFIG_DEFAULT)},
	{str_cn_ID_STRING_DC_DIDOCONFIG_PREDEFINE,sizeof(str_cn_ID_STRING_DC_DIDOCONFIG_PREDEFINE)/_PER_SIZE,str_en_ID_STRING_DC_DIDOCONFIG_PREDEFINE,sizeof(str_en_ID_STRING_DC_DIDOCONFIG_PREDEFINE)},
	{str_cn_ID_STRING_DC_DIDOCONFIG_CUSTOM,sizeof(str_cn_ID_STRING_DC_DIDOCONFIG_CUSTOM)/_PER_SIZE,str_en_ID_STRING_DC_DIDOCONFIG_CUSTOM,sizeof(str_en_ID_STRING_DC_DIDOCONFIG_CUSTOM)},
	{str_cn_ID_STRING_K_IN,sizeof(str_cn_ID_STRING_K_IN)/_PER_SIZE,str_en_ID_STRING_K_IN,sizeof(str_en_ID_STRING_K_IN)},
	{str_cn_ID_STRING_K_OUT,sizeof(str_cn_ID_STRING_K_OUT)/_PER_SIZE,str_en_ID_STRING_K_OUT,sizeof(str_en_ID_STRING_K_OUT)},
	{str_cn_ID_STRING_B_OUT,sizeof(str_cn_ID_STRING_B_OUT)/_PER_SIZE,str_en_ID_STRING_B_OUT,sizeof(str_en_ID_STRING_B_OUT)},
	{str_cn_ID_STRING_ABNORMAL_FRAM,sizeof(str_cn_ID_STRING_ABNORMAL_FRAM)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_FRAM,sizeof(str_en_ID_STRING_ABNORMAL_FRAM)},
	{str_cn_ID_STRING_ABNORMAL_RAM,sizeof(str_cn_ID_STRING_ABNORMAL_RAM)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_RAM,sizeof(str_en_ID_STRING_ABNORMAL_RAM)},
	{str_cn_ID_STRING_ABNORMAL_CLOCK,sizeof(str_cn_ID_STRING_ABNORMAL_CLOCK)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_CLOCK,sizeof(str_en_ID_STRING_ABNORMAL_CLOCK)},
	{str_cn_ID_STRING_ABNORMAL_MEAS_PRECISION,sizeof(str_cn_ID_STRING_ABNORMAL_MEAS_PRECISION)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_MEAS_PRECISION,sizeof(str_en_ID_STRING_ABNORMAL_MEAS_PRECISION)},
	{str_cn_ID_STRING_ABNORMAL_SYSCFG,sizeof(str_cn_ID_STRING_ABNORMAL_SYSCFG)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_SYSCFG,sizeof(str_en_ID_STRING_ABNORMAL_SYSCFG)},
	{str_cn_ID_STRING_ABNORMAL_DBGCFG,sizeof(str_cn_ID_STRING_ABNORMAL_DBGCFG)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_DBGCFG,sizeof(str_en_ID_STRING_ABNORMAL_DBGCFG)},
	{str_cn_ID_STRING_ABNORMAL_DIDOCONFIG,sizeof(str_cn_ID_STRING_ABNORMAL_DIDOCONFIG)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_DIDOCONFIG,sizeof(str_en_ID_STRING_ABNORMAL_DIDOCONFIG)},
	{str_cn_ID_STRING_ABNORMAL_DO_POWER,sizeof(str_cn_ID_STRING_ABNORMAL_DO_POWER)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_DO_POWER,sizeof(str_en_ID_STRING_ABNORMAL_DO_POWER)},
	{str_cn_ID_STRING_ABNORMAL_CONNECTION,sizeof(str_cn_ID_STRING_ABNORMAL_CONNECTION)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_CONNECTION,sizeof(str_en_ID_STRING_ABNORMAL_CONNECTION)},
	{str_cn_ID_STRING_ABNORMAL_EXECODE,sizeof(str_cn_ID_STRING_ABNORMAL_EXECODE)/_PER_SIZE,str_en_ID_STRING_ABNORMAL_EXECODE,sizeof(str_en_ID_STRING_ABNORMAL_EXECODE)},
	{str_cn_ID_STRING_RUN_COOL_STARTUP,sizeof(str_cn_ID_STRING_RUN_COOL_STARTUP)/_PER_SIZE,str_en_ID_STRING_RUN_COOL_STARTUP,sizeof(str_en_ID_STRING_RUN_COOL_STARTUP)},
	{str_cn_ID_STRING_RUN_SETTING,sizeof(str_cn_ID_STRING_RUN_SETTING)/_PER_SIZE,str_en_ID_STRING_RUN_SETTING,sizeof(str_en_ID_STRING_RUN_SETTING)},
	{str_cn_ID_STRING_RUN_FRAM_INIT,sizeof(str_cn_ID_STRING_RUN_FRAM_INIT)/_PER_SIZE,str_en_ID_STRING_RUN_FRAM_INIT,sizeof(str_en_ID_STRING_RUN_FRAM_INIT)},
	{str_cn_ID_STRING_RUN_INTO_DEBUGING,sizeof(str_cn_ID_STRING_RUN_INTO_DEBUGING)/_PER_SIZE,str_en_ID_STRING_RUN_INTO_DEBUGING,sizeof(str_en_ID_STRING_RUN_INTO_DEBUGING)},
	{str_cn_ID_STRING_RUN_OUTOF_DEBUGING,sizeof(str_cn_ID_STRING_RUN_OUTOF_DEBUGING)/_PER_SIZE,str_en_ID_STRING_RUN_OUTOF_DEBUGING,sizeof(str_en_ID_STRING_RUN_OUTOF_DEBUGING)},
	{str_cn_ID_STRING_RUN_INTO_DEBUG,sizeof(str_cn_ID_STRING_RUN_INTO_DEBUG)/_PER_SIZE,str_en_ID_STRING_RUN_INTO_DEBUG,sizeof(str_en_ID_STRING_RUN_INTO_DEBUG)},
	{str_cn_ID_STRING_RUN_OUTOF_DEBUG,sizeof(str_cn_ID_STRING_RUN_OUTOF_DEBUG)/_PER_SIZE,str_en_ID_STRING_RUN_OUTOF_DEBUG,sizeof(str_en_ID_STRING_RUN_OUTOF_DEBUG)},
	{str_cn_ID_STRING_MEASTYPE_ALL,sizeof(str_cn_ID_STRING_MEASTYPE_ALL)/_PER_SIZE,str_en_ID_STRING_MEASTYPE_ALL,sizeof(str_en_ID_STRING_MEASTYPE_ALL)},
	{str_cn_ID_STRING_MEASTYPE_SIGNAL,sizeof(str_cn_ID_STRING_MEASTYPE_SIGNAL)/_PER_SIZE,str_en_ID_STRING_MEASTYPE_SIGNAL,sizeof(str_en_ID_STRING_MEASTYPE_SIGNAL)},
	{str_cn_ID_STRING_MEASTYPE_STATUS,sizeof(str_cn_ID_STRING_MEASTYPE_STATUS)/_PER_SIZE,str_en_ID_STRING_MEASTYPE_STATUS,sizeof(str_en_ID_STRING_MEASTYPE_STATUS)},
	{str_cn_ID_STRING_MEASTYPE_MEAS,sizeof(str_cn_ID_STRING_MEASTYPE_MEAS)/_PER_SIZE,str_en_ID_STRING_MEASTYPE_MEAS,sizeof(str_en_ID_STRING_MEASTYPE_MEAS)},
	{str_cn_ID_STRING_MEAS_GATAGE,sizeof(str_cn_ID_STRING_MEAS_GATAGE)/_PER_SIZE,str_en_ID_STRING_MEAS_GATAGE,sizeof(str_en_ID_STRING_MEAS_GATAGE)},
	{str_cn_ID_STRING_MEASTYPE_CODEDATA,sizeof(str_cn_ID_STRING_MEASTYPE_CODEDATA)/_PER_SIZE,str_en_ID_STRING_MEASTYPE_CODEDATA,sizeof(str_en_ID_STRING_MEASTYPE_CODEDATA)},
	{str_cn_ID_STRING_MEAS_CODEDATA_L,sizeof(str_cn_ID_STRING_MEAS_CODEDATA_L)/_PER_SIZE,str_en_ID_STRING_MEAS_CODEDATA_L,sizeof(str_en_ID_STRING_MEAS_CODEDATA_L)},
	{str_cn_ID_STRING_MEAS_CODEDATA_H,sizeof(str_cn_ID_STRING_MEAS_CODEDATA_H)/_PER_SIZE,str_en_ID_STRING_MEAS_CODEDATA_H,sizeof(str_en_ID_STRING_MEAS_CODEDATA_H)},
	{str_cn_ID_STRING_MEAS_AI1,sizeof(str_cn_ID_STRING_MEAS_AI1)/_PER_SIZE,str_en_ID_STRING_MEAS_AI1,sizeof(str_en_ID_STRING_MEAS_AI1)},
	{str_cn_ID_STRING_MEAS_AI2,sizeof(str_cn_ID_STRING_MEAS_AI2)/_PER_SIZE,str_en_ID_STRING_MEAS_AI2,sizeof(str_en_ID_STRING_MEAS_AI2)},
	{str_cn_ID_STRING_MEAS_AO,sizeof(str_cn_ID_STRING_MEAS_AO)/_PER_SIZE,str_en_ID_STRING_MEAS_AO,sizeof(str_en_ID_STRING_MEAS_AO)},
	{str_cn_ID_STRING_MEAS_ADCODE,sizeof(str_cn_ID_STRING_MEAS_ADCODE)/_PER_SIZE,str_en_ID_STRING_MEAS_ADCODE,sizeof(str_en_ID_STRING_MEAS_ADCODE)},
	{str_cn_ID_STRING_MEAS_LED,sizeof(str_cn_ID_STRING_MEAS_LED)/_PER_SIZE,str_en_ID_STRING_MEAS_LED,sizeof(str_en_ID_STRING_MEAS_LED)},
	{str_cn_ID_STRING_MEAS_GATESTATUS,sizeof(str_cn_ID_STRING_MEAS_GATESTATUS)/_PER_SIZE,str_en_ID_STRING_MEAS_GATESTATUS,sizeof(str_en_ID_STRING_MEAS_GATESTATUS)},
	{str_cn_ID_STRING_MEAS_SIG_DI,sizeof(str_cn_ID_STRING_MEAS_SIG_DI)/_PER_SIZE,str_en_ID_STRING_MEAS_SIG_DI,sizeof(str_en_ID_STRING_MEAS_SIG_DI)},
	{str_cn_ID_STRING_MEAS_SIG_DO,sizeof(str_cn_ID_STRING_MEAS_SIG_DO)/_PER_SIZE,str_en_ID_STRING_MEAS_SIG_DO,sizeof(str_en_ID_STRING_MEAS_SIG_DO)},
	{str_cn_ID_STRING_MEAS_SIG_SELFCHK,sizeof(str_cn_ID_STRING_MEAS_SIG_SELFCHK)/_PER_SIZE,str_en_ID_STRING_MEAS_SIG_SELFCHK,sizeof(str_en_ID_STRING_MEAS_SIG_SELFCHK)},
	{str_cn_ID_STRING_MEAS_SIG_SELFCHKEX,sizeof(str_cn_ID_STRING_MEAS_SIG_SELFCHKEX)/_PER_SIZE,str_en_ID_STRING_MEAS_SIG_SELFCHKEX,sizeof(str_en_ID_STRING_MEAS_SIG_SELFCHKEX)},
	{str_cn_ID_STRING_MEAS_SIG_TOTAL,sizeof(str_cn_ID_STRING_MEAS_SIG_TOTAL)/_PER_SIZE,str_en_ID_STRING_MEAS_SIG_TOTAL,sizeof(str_en_ID_STRING_MEAS_SIG_TOTAL)},
	{str_cn_ID_STRING_CONTROL,sizeof(str_cn_ID_STRING_CONTROL)/_PER_SIZE,str_en_ID_STRING_CONTROL,sizeof(str_en_ID_STRING_CONTROL)},
	{str_cn_ID_STRING_STATUS,sizeof(str_cn_ID_STRING_STATUS)/_PER_SIZE,str_en_ID_STRING_STATUS,sizeof(str_en_ID_STRING_STATUS)},
	{str_cn_ID_STRING_SYSINFO,sizeof(str_cn_ID_STRING_SYSINFO)/_PER_SIZE,str_en_ID_STRING_SYSINFO,sizeof(str_en_ID_STRING_SYSINFO)},
	{str_cn_ID_STRING_SYSSET,sizeof(str_cn_ID_STRING_SYSSET)/_PER_SIZE,str_en_ID_STRING_SYSSET,sizeof(str_en_ID_STRING_SYSSET)},
	{str_cn_ID_STRING_PRJSET,sizeof(str_cn_ID_STRING_PRJSET)/_PER_SIZE,str_en_ID_STRING_PRJSET,sizeof(str_en_ID_STRING_PRJSET)},
	{str_cn_ID_STRING_DEVICEMODEL,sizeof(str_cn_ID_STRING_DEVICEMODEL)/_PER_SIZE,str_en_ID_STRING_DEVICEMODEL,sizeof(str_en_ID_STRING_DEVICEMODEL)},
	{str_cn_ID_STRING_DEBUG,sizeof(str_cn_ID_STRING_DEBUG)/_PER_SIZE,str_en_ID_STRING_DEBUG,sizeof(str_en_ID_STRING_DEBUG)},
	{str_cn_ID_STRING_OTHER,sizeof(str_cn_ID_STRING_OTHER)/_PER_SIZE,str_en_ID_STRING_OTHER,sizeof(str_en_ID_STRING_OTHER)},
	{str_cn_ID_STRING_STA_MEAS,sizeof(str_cn_ID_STRING_STA_MEAS)/_PER_SIZE,str_en_ID_STRING_STA_MEAS,sizeof(str_en_ID_STRING_STA_MEAS)},
	{str_cn_ID_STRING_STA_LOOP,sizeof(str_cn_ID_STRING_STA_LOOP)/_PER_SIZE,str_en_ID_STRING_STA_LOOP,sizeof(str_en_ID_STRING_STA_LOOP)},
	{str_cn_ID_STRING_STA_PROT,sizeof(str_cn_ID_STRING_STA_PROT)/_PER_SIZE,str_en_ID_STRING_STA_PROT,sizeof(str_en_ID_STRING_STA_PROT)},
	{str_cn_ID_STRING_STA_STAS,sizeof(str_cn_ID_STRING_STA_STAS)/_PER_SIZE,str_en_ID_STRING_STA_STAS,sizeof(str_en_ID_STRING_STA_STAS)},
	{str_cn_ID_STRING_SYSSET_PWVALUE,sizeof(str_cn_ID_STRING_SYSSET_PWVALUE)/_PER_SIZE,str_en_ID_STRING_SYSSET_PWVALUE,sizeof(str_en_ID_STRING_SYSSET_PWVALUE)},
	{str_cn_ID_STRING_SYSSET_ETH,sizeof(str_cn_ID_STRING_SYSSET_ETH)/_PER_SIZE,str_en_ID_STRING_SYSSET_ETH,sizeof(str_en_ID_STRING_SYSSET_ETH)},
	{str_cn_ID_STRING_SYSSET_COM,sizeof(str_cn_ID_STRING_SYSSET_COM)/_PER_SIZE,str_en_ID_STRING_SYSSET_COM,sizeof(str_en_ID_STRING_SYSSET_COM)},
	{str_cn_ID_STRING_SYSSET_AO,sizeof(str_cn_ID_STRING_SYSSET_AO)/_PER_SIZE,str_en_ID_STRING_SYSSET_AO,sizeof(str_en_ID_STRING_SYSSET_AO)},
	{str_cn_ID_STRING_PRJSET_RANGE,sizeof(str_cn_ID_STRING_PRJSET_RANGE)/_PER_SIZE,str_en_ID_STRING_PRJSET_RANGE,sizeof(str_en_ID_STRING_PRJSET_RANGE)},
	{str_cn_ID_STRING_PRJSET_PRESET,sizeof(str_cn_ID_STRING_PRJSET_PRESET)/_PER_SIZE,str_en_ID_STRING_PRJSET_PRESET,sizeof(str_en_ID_STRING_PRJSET_PRESET)},
	{str_cn_ID_STRING_PRJSET_ARCSET,sizeof(str_cn_ID_STRING_PRJSET_ARCSET)/_PER_SIZE,str_en_ID_STRING_PRJSET_ARCSET,sizeof(str_en_ID_STRING_PRJSET_ARCSET)},
	{str_cn_ID_STRING_PRJSET_SLOPESET,sizeof(str_cn_ID_STRING_PRJSET_SLOPESET)/_PER_SIZE,str_en_ID_STRING_PRJSET_SLOPESET,sizeof(str_en_ID_STRING_PRJSET_SLOPESET)},
	{str_cn_ID_STRING_CLOCK,sizeof(str_cn_ID_STRING_CLOCK)/_PER_SIZE,str_en_ID_STRING_CLOCK,sizeof(str_en_ID_STRING_CLOCK)},
	{str_cn_ID_STRING_SYSSET_LANG,sizeof(str_cn_ID_STRING_SYSSET_LANG)/_PER_SIZE,str_en_ID_STRING_SYSSET_LANG,sizeof(str_en_ID_STRING_SYSSET_LANG)},
	{str_cn_ID_STRING_DEVICEMODEL_MEASPRECIS,sizeof(str_cn_ID_STRING_DEVICEMODEL_MEASPRECIS)/_PER_SIZE,str_en_ID_STRING_DEVICEMODEL_MEASPRECIS,sizeof(str_en_ID_STRING_DEVICEMODEL_MEASPRECIS)},
	{str_cn_ID_STRING_DEVICEMODEL_MODEL,sizeof(str_cn_ID_STRING_DEVICEMODEL_MODEL)/_PER_SIZE,str_en_ID_STRING_DEVICEMODEL_MODEL,sizeof(str_en_ID_STRING_DEVICEMODEL_MODEL)},
	{str_cn_ID_STRING_DEVICEMODEL_DI,sizeof(str_cn_ID_STRING_DEVICEMODEL_DI)/_PER_SIZE,str_en_ID_STRING_DEVICEMODEL_DI,sizeof(str_en_ID_STRING_DEVICEMODEL_DI)},
	{str_cn_ID_STRING_DEVICEMODEL_DO,sizeof(str_cn_ID_STRING_DEVICEMODEL_DO)/_PER_SIZE,str_en_ID_STRING_DEVICEMODEL_DO,sizeof(str_en_ID_STRING_DEVICEMODEL_DO)},
	{str_cn_ID_STRING_INIT_DEFAULT,sizeof(str_cn_ID_STRING_INIT_DEFAULT)/_PER_SIZE,str_en_ID_STRING_INIT_DEFAULT,sizeof(str_en_ID_STRING_INIT_DEFAULT)},
	{str_cn_ID_STRING_SCREEN,sizeof(str_cn_ID_STRING_SCREEN)/_PER_SIZE,str_en_ID_STRING_SCREEN,sizeof(str_en_ID_STRING_SCREEN)},
	{str_cn_ID_STRING_VERTTYPE,sizeof(str_cn_ID_STRING_VERTTYPE)/_PER_SIZE,str_en_ID_STRING_VERTTYPE,sizeof(str_en_ID_STRING_VERTTYPE)},
	{str_cn_ID_STRING_VERTTYPE_NUM,sizeof(str_cn_ID_STRING_VERTTYPE_NUM)/_PER_SIZE,str_en_ID_STRING_VERTTYPE_NUM,sizeof(str_en_ID_STRING_VERTTYPE_NUM)},
	{str_cn_ID_STRING_VERTTYPE_GRAP1,sizeof(str_cn_ID_STRING_VERTTYPE_GRAP1)/_PER_SIZE,str_en_ID_STRING_VERTTYPE_GRAP1,sizeof(str_en_ID_STRING_VERTTYPE_GRAP1)},
	{str_cn_ID_STRING_VERTTYPE_GRAP2,sizeof(str_cn_ID_STRING_VERTTYPE_GRAP2)/_PER_SIZE,str_en_ID_STRING_VERTTYPE_GRAP2,sizeof(str_en_ID_STRING_VERTTYPE_GRAP2)},
	{str_cn_ID_STRING_MENU_LEFTRIGHT,sizeof(str_cn_ID_STRING_MENU_LEFTRIGHT)/_PER_SIZE,str_en_ID_STRING_MENU_LEFTRIGHT,sizeof(str_en_ID_STRING_MENU_LEFTRIGHT)},
	{str_cn_ID_STRING_DEFAULT_SCREEN,sizeof(str_cn_ID_STRING_DEFAULT_SCREEN)/_PER_SIZE,str_en_ID_STRING_DEFAULT_SCREEN,sizeof(str_en_ID_STRING_DEFAULT_SCREEN)},
	{str_cn_ID_STRING_MAIN_MENU_STYLE,sizeof(str_cn_ID_STRING_MAIN_MENU_STYLE)/_PER_SIZE,str_en_ID_STRING_MAIN_MENU_STYLE,sizeof(str_en_ID_STRING_MAIN_MENU_STYLE)},
	{str_cn_ID_STRING_MAIN_MENU_STYLE_NORMAL,sizeof(str_cn_ID_STRING_MAIN_MENU_STYLE_NORMAL)/_PER_SIZE,str_en_ID_STRING_MAIN_MENU_STYLE_NORMAL,sizeof(str_en_ID_STRING_MAIN_MENU_STYLE_NORMAL)},
	{str_cn_ID_STRING_MAIN_MENU_STYLE_ICON,sizeof(str_cn_ID_STRING_MAIN_MENU_STYLE_ICON)/_PER_SIZE,str_en_ID_STRING_MAIN_MENU_STYLE_ICON,sizeof(str_en_ID_STRING_MAIN_MENU_STYLE_ICON)},
	{str_cn_ID_STRING_DO_CHECK,sizeof(str_cn_ID_STRING_DO_CHECK)/_PER_SIZE,str_en_ID_STRING_DO_CHECK,sizeof(str_en_ID_STRING_DO_CHECK)},
	{str_cn_ID_STRING_DI_CHECK,sizeof(str_cn_ID_STRING_DI_CHECK)/_PER_SIZE,str_en_ID_STRING_DI_CHECK,sizeof(str_en_ID_STRING_DI_CHECK)},
	{str_cn_ID_STRING_AO_CHECK,sizeof(str_cn_ID_STRING_AO_CHECK)/_PER_SIZE,str_en_ID_STRING_AO_CHECK,sizeof(str_en_ID_STRING_AO_CHECK)},
	{str_cn_ID_STRING_CLEAR_CODE,sizeof(str_cn_ID_STRING_CLEAR_CODE)/_PER_SIZE,str_en_ID_STRING_CLEAR_CODE,sizeof(str_en_ID_STRING_CLEAR_CODE)},
	{str_cn_ID_STRING_COMM_MONITOR,sizeof(str_cn_ID_STRING_COMM_MONITOR)/_PER_SIZE,str_en_ID_STRING_COMM_MONITOR,sizeof(str_en_ID_STRING_COMM_MONITOR)},
	{str_cn_ID_STRING_MAIN_VERSION,sizeof(str_cn_ID_STRING_MAIN_VERSION)/_PER_SIZE,str_en_ID_STRING_MAIN_VERSION,sizeof(str_en_ID_STRING_MAIN_VERSION)},
	{str_cn_ID_STRING_YEAR,sizeof(str_cn_ID_STRING_YEAR)/_PER_SIZE,str_en_ID_STRING_YEAR,sizeof(str_en_ID_STRING_YEAR)},
	{str_cn_ID_STRING_MONTH,sizeof(str_cn_ID_STRING_MONTH)/_PER_SIZE,str_en_ID_STRING_MONTH,sizeof(str_en_ID_STRING_MONTH)},
	{str_cn_ID_STRING_DAY,sizeof(str_cn_ID_STRING_DAY)/_PER_SIZE,str_en_ID_STRING_DAY,sizeof(str_en_ID_STRING_DAY)},
	{str_cn_ID_STRING_HOUR,sizeof(str_cn_ID_STRING_HOUR)/_PER_SIZE,str_en_ID_STRING_HOUR,sizeof(str_en_ID_STRING_HOUR)},
	{str_cn_ID_STRING_MIN,sizeof(str_cn_ID_STRING_MIN)/_PER_SIZE,str_en_ID_STRING_MIN,sizeof(str_en_ID_STRING_MIN)},
	{str_cn_ID_STRING_SEC,sizeof(str_cn_ID_STRING_SEC)/_PER_SIZE,str_en_ID_STRING_SEC,sizeof(str_en_ID_STRING_SEC)},
	{str_cn_ID_STRING_COMMFLT,sizeof(str_cn_ID_STRING_COMMFLT)/_PER_SIZE,str_en_ID_STRING_COMMFLT,sizeof(str_en_ID_STRING_COMMFLT)},
	{str_cn_ID_STRING_STATUS_STOP,sizeof(str_cn_ID_STRING_STATUS_STOP)/_PER_SIZE,str_en_ID_STRING_STATUS_STOP,sizeof(str_en_ID_STRING_STATUS_STOP)},
	{str_cn_ID_STRING_STATUS_RUN,sizeof(str_cn_ID_STRING_STATUS_RUN)/_PER_SIZE,str_en_ID_STRING_STATUS_RUN,sizeof(str_en_ID_STRING_STATUS_RUN)},
	{str_cn_ID_STRING_BRANDING,sizeof(str_cn_ID_STRING_BRANDING)/_PER_SIZE,str_en_ID_STRING_BRANDING,sizeof(str_en_ID_STRING_BRANDING)},
	{str_cn_ID_STRING_WISCOM,sizeof(str_cn_ID_STRING_WISCOM)/_PER_SIZE,str_en_ID_STRING_WISCOM,sizeof(str_en_ID_STRING_WISCOM)},
	{str_cn_ID_STRING_NOMEAS,sizeof(str_cn_ID_STRING_NOMEAS)/_PER_SIZE,str_en_ID_STRING_NOMEAS,sizeof(str_en_ID_STRING_NOMEAS)},
	{str_cn_ID_STRING_ACT_RESULT_WARNING,sizeof(str_cn_ID_STRING_ACT_RESULT_WARNING)/_PER_SIZE,str_en_ID_STRING_ACT_RESULT_WARNING,sizeof(str_en_ID_STRING_ACT_RESULT_WARNING)},
	{str_cn_ID_STRING_ERR_UNKNOWN,sizeof(str_cn_ID_STRING_ERR_UNKNOWN)/_PER_SIZE,str_en_ID_STRING_ERR_UNKNOWN,sizeof(str_en_ID_STRING_ERR_UNKNOWN)},
	{str_cn_ID_STRING_ERR_CHECKSUM,sizeof(str_cn_ID_STRING_ERR_CHECKSUM)/_PER_SIZE,str_en_ID_STRING_ERR_CHECKSUM,sizeof(str_en_ID_STRING_ERR_CHECKSUM)},
	{str_cn_ID_STRING_ERR_SETRANGE,sizeof(str_cn_ID_STRING_ERR_SETRANGE)/_PER_SIZE,str_en_ID_STRING_ERR_SETRANGE,sizeof(str_en_ID_STRING_ERR_SETRANGE)},
	{str_cn_ID_STRING_ERR_TIME_ILLEGAL,sizeof(str_cn_ID_STRING_ERR_TIME_ILLEGAL)/_PER_SIZE,str_en_ID_STRING_ERR_TIME_ILLEGAL,sizeof(str_en_ID_STRING_ERR_TIME_ILLEGAL)},
	{str_cn_ID_STRING_ERR_UNREMOTE,sizeof(str_cn_ID_STRING_ERR_UNREMOTE)/_PER_SIZE,str_en_ID_STRING_ERR_UNREMOTE,sizeof(str_en_ID_STRING_ERR_UNREMOTE)},
	{str_cn_ID_STRING_ERR_MODIFYSET_CANCEL,sizeof(str_cn_ID_STRING_ERR_MODIFYSET_CANCEL)/_PER_SIZE,str_en_ID_STRING_ERR_MODIFYSET_CANCEL,sizeof(str_en_ID_STRING_ERR_MODIFYSET_CANCEL)},
	{str_cn_ID_STRING_ERR_UNKNOW_CODE,sizeof(str_cn_ID_STRING_ERR_UNKNOW_CODE)/_PER_SIZE,str_en_ID_STRING_ERR_UNKNOW_CODE,sizeof(str_en_ID_STRING_ERR_UNKNOW_CODE)},
	{str_cn_ID_STRING_ERR_RECHECK,sizeof(str_cn_ID_STRING_ERR_RECHECK)/_PER_SIZE,str_en_ID_STRING_ERR_RECHECK,sizeof(str_en_ID_STRING_ERR_RECHECK)},
	{str_cn_ID_STRING_ERR_UNDEBUG,sizeof(str_cn_ID_STRING_ERR_UNDEBUG)/_PER_SIZE,str_en_ID_STRING_ERR_UNDEBUG,sizeof(str_en_ID_STRING_ERR_UNDEBUG)},
	{str_cn_ID_STRING_ERR_SEQUENCE,sizeof(str_cn_ID_STRING_ERR_SEQUENCE)/_PER_SIZE,str_en_ID_STRING_ERR_SEQUENCE,sizeof(str_en_ID_STRING_ERR_SEQUENCE)},
	{str_cn_ID_STRING_ERR_UNLOCAL,sizeof(str_cn_ID_STRING_ERR_UNLOCAL)/_PER_SIZE,str_en_ID_STRING_ERR_UNLOCAL,sizeof(str_en_ID_STRING_ERR_UNLOCAL)},
	{str_cn_ID_STRING_ERR_UNKNOW_SETID,sizeof(str_cn_ID_STRING_ERR_UNKNOW_SETID)/_PER_SIZE,str_en_ID_STRING_ERR_UNKNOW_SETID,sizeof(str_en_ID_STRING_ERR_UNKNOW_SETID)},
	{str_cn_ID_STRING_ERR_MESSAGE_CRASH,sizeof(str_cn_ID_STRING_ERR_MESSAGE_CRASH)/_PER_SIZE,str_en_ID_STRING_ERR_MESSAGE_CRASH,sizeof(str_en_ID_STRING_ERR_MESSAGE_CRASH)},
	{str_cn_ID_STRING_ERR_CONTROL_ILLEGAL,sizeof(str_cn_ID_STRING_ERR_CONTROL_ILLEGAL)/_PER_SIZE,str_en_ID_STRING_ERR_CONTROL_ILLEGAL,sizeof(str_en_ID_STRING_ERR_CONTROL_ILLEGAL)},
	{str_cn_ID_STRING_ERR_DISABLE_CODE,sizeof(str_cn_ID_STRING_ERR_DISABLE_CODE)/_PER_SIZE,str_en_ID_STRING_ERR_DISABLE_CODE,sizeof(str_en_ID_STRING_ERR_DISABLE_CODE)},
	{str_cn_ID_STRING_ERR_OPERATE,sizeof(str_cn_ID_STRING_ERR_OPERATE)/_PER_SIZE,str_en_ID_STRING_ERR_OPERATE,sizeof(str_en_ID_STRING_ERR_OPERATE)},
	{str_cn_ID_STRING_OPERATING,sizeof(str_cn_ID_STRING_OPERATING)/_PER_SIZE,str_en_ID_STRING_OPERATING,sizeof(str_en_ID_STRING_OPERATING)},
	{str_cn_ID_STRING_ERR_OVER_RANGE,sizeof(str_cn_ID_STRING_ERR_OVER_RANGE)/_PER_SIZE,str_en_ID_STRING_ERR_OVER_RANGE,sizeof(str_en_ID_STRING_ERR_OVER_RANGE)},
	{str_cn_ID_STRING_ERR_CTRLCMD_CHECK_CONTROLMODE,sizeof(str_cn_ID_STRING_ERR_CTRLCMD_CHECK_CONTROLMODE)/_PER_SIZE,str_en_ID_STRING_ERR_CTRLCMD_CHECK_CONTROLMODE,sizeof(str_en_ID_STRING_ERR_CTRLCMD_CHECK_CONTROLMODE)},
	{str_cn_ID_STRING_CTRLCMD_CHECK_HAVEOPERA,sizeof(str_cn_ID_STRING_CTRLCMD_CHECK_HAVEOPERA)/_PER_SIZE,str_en_ID_STRING_CTRLCMD_CHECK_HAVEOPERA,sizeof(str_en_ID_STRING_CTRLCMD_CHECK_HAVEOPERA)},
	{str_cn_ID_STRING_SEARCHING,sizeof(str_cn_ID_STRING_SEARCHING)/_PER_SIZE,str_en_ID_STRING_SEARCHING,sizeof(str_en_ID_STRING_SEARCHING)},
	{str_cn_ID_STRING_STARTING_TIME,sizeof(str_cn_ID_STRING_STARTING_TIME)/_PER_SIZE,str_en_ID_STRING_STARTING_TIME,sizeof(str_en_ID_STRING_STARTING_TIME)},
	{str_cn_ID_STRING_OP_CONFIRM,sizeof(str_cn_ID_STRING_OP_CONFIRM)/_PER_SIZE,str_en_ID_STRING_OP_CONFIRM,sizeof(str_en_ID_STRING_OP_CONFIRM)},
	{str_cn_ID_STRING_ERROR_PASWORD,sizeof(str_cn_ID_STRING_ERROR_PASWORD)/_PER_SIZE,str_en_ID_STRING_ERROR_PASWORD,sizeof(str_en_ID_STRING_ERROR_PASWORD)},
	{str_cn_ID_STRING_DI_DI1,sizeof(str_cn_ID_STRING_DI_DI1)/_PER_SIZE,str_en_ID_STRING_DI_DI1,sizeof(str_en_ID_STRING_DI_DI1)},
	{str_cn_ID_STRING_DI_DI2,sizeof(str_cn_ID_STRING_DI_DI2)/_PER_SIZE,str_en_ID_STRING_DI_DI2,sizeof(str_en_ID_STRING_DI_DI2)},
	{str_cn_ID_STRING_DI_DI3,sizeof(str_cn_ID_STRING_DI_DI3)/_PER_SIZE,str_en_ID_STRING_DI_DI3,sizeof(str_en_ID_STRING_DI_DI3)},
	{str_cn_ID_STRING_DI_DI4,sizeof(str_cn_ID_STRING_DI_DI4)/_PER_SIZE,str_en_ID_STRING_DI_DI4,sizeof(str_en_ID_STRING_DI_DI4)},
	{str_cn_ID_STRING_DI_DI5,sizeof(str_cn_ID_STRING_DI_DI5)/_PER_SIZE,str_en_ID_STRING_DI_DI5,sizeof(str_en_ID_STRING_DI_DI5)},
	{str_cn_ID_STRING_DI_DI6,sizeof(str_cn_ID_STRING_DI_DI6)/_PER_SIZE,str_en_ID_STRING_DI_DI6,sizeof(str_en_ID_STRING_DI_DI6)},
	{str_cn_ID_STRING_DI_DI7,sizeof(str_cn_ID_STRING_DI_DI7)/_PER_SIZE,str_en_ID_STRING_DI_DI7,sizeof(str_en_ID_STRING_DI_DI7)},
	{str_cn_ID_STRING_DI_DI8,sizeof(str_cn_ID_STRING_DI_DI8)/_PER_SIZE,str_en_ID_STRING_DI_DI8,sizeof(str_en_ID_STRING_DI_DI8)},
	{str_cn_ID_STRING_DI_DI9,sizeof(str_cn_ID_STRING_DI_DI9)/_PER_SIZE,str_en_ID_STRING_DI_DI9,sizeof(str_en_ID_STRING_DI_DI9)},
	{str_cn_ID_STRING_DI_DI10,sizeof(str_cn_ID_STRING_DI_DI10)/_PER_SIZE,str_en_ID_STRING_DI_DI10,sizeof(str_en_ID_STRING_DI_DI10)},
	{str_cn_ID_STRING_DI_DI11,sizeof(str_cn_ID_STRING_DI_DI11)/_PER_SIZE,str_en_ID_STRING_DI_DI11,sizeof(str_en_ID_STRING_DI_DI11)},
	{str_cn_ID_STRING_DI_DI12,sizeof(str_cn_ID_STRING_DI_DI12)/_PER_SIZE,str_en_ID_STRING_DI_DI12,sizeof(str_en_ID_STRING_DI_DI12)},
	{str_cn_ID_STRING_DI_UPPER_LIMIT,sizeof(str_cn_ID_STRING_DI_UPPER_LIMIT)/_PER_SIZE,str_en_ID_STRING_DI_UPPER_LIMIT,sizeof(str_en_ID_STRING_DI_UPPER_LIMIT)},
	{str_cn_ID_STRING_DI_LOWER_LIMIT,sizeof(str_cn_ID_STRING_DI_LOWER_LIMIT)/_PER_SIZE,str_en_ID_STRING_DI_LOWER_LIMIT,sizeof(str_en_ID_STRING_DI_LOWER_LIMIT)},
	{str_cn_ID_STRING_DI_OVER_UPPER,sizeof(str_cn_ID_STRING_DI_OVER_UPPER)/_PER_SIZE,str_en_ID_STRING_DI_OVER_UPPER,sizeof(str_en_ID_STRING_DI_OVER_UPPER)},
	{str_cn_ID_STRING_DI_BELOW_LOWER,sizeof(str_cn_ID_STRING_DI_BELOW_LOWER)/_PER_SIZE,str_en_ID_STRING_DI_BELOW_LOWER,sizeof(str_en_ID_STRING_DI_BELOW_LOWER)},
	{str_cn_ID_STRING_DI_GATE_RISE,sizeof(str_cn_ID_STRING_DI_GATE_RISE)/_PER_SIZE,str_en_ID_STRING_DI_GATE_RISE,sizeof(str_en_ID_STRING_DI_GATE_RISE)},
	{str_cn_ID_STRING_DI_GATE_FALL,sizeof(str_cn_ID_STRING_DI_GATE_FALL)/_PER_SIZE,str_en_ID_STRING_DI_GATE_FALL,sizeof(str_en_ID_STRING_DI_GATE_FALL)},
	{str_cn_ID_STRING_DI_BREAK_STATE,sizeof(str_cn_ID_STRING_DI_BREAK_STATE)/_PER_SIZE,str_en_ID_STRING_DI_BREAK_STATE,sizeof(str_en_ID_STRING_DI_BREAK_STATE)},
	{str_cn_ID_STRING_DI_OVER_LOAD1,sizeof(str_cn_ID_STRING_DI_OVER_LOAD1)/_PER_SIZE,str_en_ID_STRING_DI_OVER_LOAD1,sizeof(str_en_ID_STRING_DI_OVER_LOAD1)},
	{str_cn_ID_STRING_DI_OVER_LOAD2,sizeof(str_cn_ID_STRING_DI_OVER_LOAD2)/_PER_SIZE,str_en_ID_STRING_DI_OVER_LOAD2,sizeof(str_en_ID_STRING_DI_OVER_LOAD2)},
	{str_cn_ID_STRING_DI_OVER_LOAD3,sizeof(str_cn_ID_STRING_DI_OVER_LOAD3)/_PER_SIZE,str_en_ID_STRING_DI_OVER_LOAD3,sizeof(str_en_ID_STRING_DI_OVER_LOAD3)},
	{str_cn_ID_STRING_DI_OVER_LOAD4,sizeof(str_cn_ID_STRING_DI_OVER_LOAD4)/_PER_SIZE,str_en_ID_STRING_DI_OVER_LOAD4,sizeof(str_en_ID_STRING_DI_OVER_LOAD4)},
	{str_cn_ID_STRING_DI_REMOTE_LOCAL,sizeof(str_cn_ID_STRING_DI_REMOTE_LOCAL)/_PER_SIZE,str_en_ID_STRING_DI_REMOTE_LOCAL,sizeof(str_en_ID_STRING_DI_REMOTE_LOCAL)},
	{str_cn_ID_STRING_DO_DO1,sizeof(str_cn_ID_STRING_DO_DO1)/_PER_SIZE,str_en_ID_STRING_DO_DO1,sizeof(str_en_ID_STRING_DO_DO1)},
	{str_cn_ID_STRING_DO_DO2,sizeof(str_cn_ID_STRING_DO_DO2)/_PER_SIZE,str_en_ID_STRING_DO_DO2,sizeof(str_en_ID_STRING_DO_DO2)},
	{str_cn_ID_STRING_DO_DO3,sizeof(str_cn_ID_STRING_DO_DO3)/_PER_SIZE,str_en_ID_STRING_DO_DO3,sizeof(str_en_ID_STRING_DO_DO3)},
	{str_cn_ID_STRING_DO_DO4,sizeof(str_cn_ID_STRING_DO_DO4)/_PER_SIZE,str_en_ID_STRING_DO_DO4,sizeof(str_en_ID_STRING_DO_DO4)},
	{str_cn_ID_STRING_DO_DO5,sizeof(str_cn_ID_STRING_DO_DO5)/_PER_SIZE,str_en_ID_STRING_DO_DO5,sizeof(str_en_ID_STRING_DO_DO5)},
	{str_cn_ID_STRING_DO_DO6,sizeof(str_cn_ID_STRING_DO_DO6)/_PER_SIZE,str_en_ID_STRING_DO_DO6,sizeof(str_en_ID_STRING_DO_DO6)},
	{str_cn_ID_STRING_DO_RISE_GATE,sizeof(str_cn_ID_STRING_DO_RISE_GATE)/_PER_SIZE,str_en_ID_STRING_DO_RISE_GATE,sizeof(str_en_ID_STRING_DO_RISE_GATE)},
	{str_cn_ID_STRING_DO_FALL_GATE,sizeof(str_cn_ID_STRING_DO_FALL_GATE)/_PER_SIZE,str_en_ID_STRING_DO_FALL_GATE,sizeof(str_en_ID_STRING_DO_FALL_GATE)},
	{str_cn_ID_STRING_DO_STOP_GATE,sizeof(str_cn_ID_STRING_DO_STOP_GATE)/_PER_SIZE,str_en_ID_STRING_DO_STOP_GATE,sizeof(str_en_ID_STRING_DO_STOP_GATE)},
	{str_cn_ID_STRING_DO_CLOSE_BREAK,sizeof(str_cn_ID_STRING_DO_CLOSE_BREAK)/_PER_SIZE,str_en_ID_STRING_DO_CLOSE_BREAK,sizeof(str_en_ID_STRING_DO_CLOSE_BREAK)},
	{str_cn_ID_STRING_DO_TRIP_BREAK,sizeof(str_cn_ID_STRING_DO_TRIP_BREAK)/_PER_SIZE,str_en_ID_STRING_DO_TRIP_BREAK,sizeof(str_en_ID_STRING_DO_TRIP_BREAK)},
	{str_cn_ID_STRING_OPEN,sizeof(str_cn_ID_STRING_OPEN)/_PER_SIZE,str_en_ID_STRING_OPEN,sizeof(str_en_ID_STRING_OPEN)},
	{str_cn_ID_STRING_CLOSE,sizeof(str_cn_ID_STRING_CLOSE)/_PER_SIZE,str_en_ID_STRING_CLOSE,sizeof(str_en_ID_STRING_CLOSE)},
	{str_cn_ID_STRING_NOMENUITEM,sizeof(str_cn_ID_STRING_NOMENUITEM)/_PER_SIZE,str_en_ID_STRING_NOMENUITEM,sizeof(str_en_ID_STRING_NOMENUITEM)},
	{str_cn_ID_STRING_COMPILETIME,sizeof(str_cn_ID_STRING_COMPILETIME)/_PER_SIZE,str_en_ID_STRING_COMPILETIME,sizeof(str_en_ID_STRING_COMPILETIME)},
	{str_cn_ID_STRING_CFGLOADTIME,sizeof(str_cn_ID_STRING_CFGLOADTIME)/_PER_SIZE,str_en_ID_STRING_CFGLOADTIME,sizeof(str_en_ID_STRING_CFGLOADTIME)},
	{str_cn_ID_STRING_LOADTIME,sizeof(str_cn_ID_STRING_LOADTIME)/_PER_SIZE,str_en_ID_STRING_LOADTIME,sizeof(str_en_ID_STRING_LOADTIME)},
	{str_cn_ID_STRING_OLD_PW,sizeof(str_cn_ID_STRING_OLD_PW)/_PER_SIZE,str_en_ID_STRING_OLD_PW,sizeof(str_en_ID_STRING_OLD_PW)},
	{str_cn_ID_STRING_NEW_PW2,sizeof(str_cn_ID_STRING_NEW_PW2)/_PER_SIZE,str_en_ID_STRING_NEW_PW2,sizeof(str_en_ID_STRING_NEW_PW2)},
	{str_cn_ID_STRING_NEW_PW,sizeof(str_cn_ID_STRING_NEW_PW)/_PER_SIZE,str_en_ID_STRING_NEW_PW,sizeof(str_en_ID_STRING_NEW_PW)},
	{str_cn_ID_STRING_DO1_PULSEWIDTH,sizeof(str_cn_ID_STRING_DO1_PULSEWIDTH)/_PER_SIZE,str_en_ID_STRING_DO1_PULSEWIDTH,sizeof(str_en_ID_STRING_DO1_PULSEWIDTH)},
	{str_cn_ID_STRING_DO2_PULSEWIDTH,sizeof(str_cn_ID_STRING_DO2_PULSEWIDTH)/_PER_SIZE,str_en_ID_STRING_DO2_PULSEWIDTH,sizeof(str_en_ID_STRING_DO2_PULSEWIDTH)},
	{str_cn_ID_STRING_DO3_PULSEWIDTH,sizeof(str_cn_ID_STRING_DO3_PULSEWIDTH)/_PER_SIZE,str_en_ID_STRING_DO3_PULSEWIDTH,sizeof(str_en_ID_STRING_DO3_PULSEWIDTH)},
	{str_cn_ID_STRING_DO4_PULSEWIDTH,sizeof(str_cn_ID_STRING_DO4_PULSEWIDTH)/_PER_SIZE,str_en_ID_STRING_DO4_PULSEWIDTH,sizeof(str_en_ID_STRING_DO4_PULSEWIDTH)},
	{str_cn_ID_STRING_DI_SWITCHOFF,sizeof(str_cn_ID_STRING_DI_SWITCHOFF)/_PER_SIZE,str_en_ID_STRING_DI_SWITCHOFF,sizeof(str_en_ID_STRING_DI_SWITCHOFF)},
	{str_cn_ID_STRING_DI_SWITCHON,sizeof(str_cn_ID_STRING_DI_SWITCHON)/_PER_SIZE,str_en_ID_STRING_DI_SWITCHON,sizeof(str_en_ID_STRING_DI_SWITCHON)},
	{str_cn_ID_STRING_DI_CMDSWITCHOFF,sizeof(str_cn_ID_STRING_DI_CMDSWITCHOFF)/_PER_SIZE,str_en_ID_STRING_DI_CMDSWITCHOFF,sizeof(str_en_ID_STRING_DI_CMDSWITCHOFF)},
	{str_cn_ID_STRING_DI_CMDSWITCHON,sizeof(str_cn_ID_STRING_DI_CMDSWITCHON)/_PER_SIZE,str_en_ID_STRING_DI_CMDSWITCHON,sizeof(str_en_ID_STRING_DI_CMDSWITCHON)},
	{str_cn_ID_STRING_CONTROL_SWITCHOFF_COMM,sizeof(str_cn_ID_STRING_CONTROL_SWITCHOFF_COMM)/_PER_SIZE,str_en_ID_STRING_CONTROL_SWITCHOFF_COMM,sizeof(str_en_ID_STRING_CONTROL_SWITCHOFF_COMM)},
	{str_cn_ID_STRING_CONTROL_SWITCHON_COMM,sizeof(str_cn_ID_STRING_CONTROL_SWITCHON_COMM)/_PER_SIZE,str_en_ID_STRING_CONTROL_SWITCHON_COMM,sizeof(str_en_ID_STRING_CONTROL_SWITCHON_COMM)},
	{str_cn_ID_STRING_READING_SYSINIT_INFO,sizeof(str_cn_ID_STRING_READING_SYSINIT_INFO)/_PER_SIZE,str_en_ID_STRING_READING_SYSINIT_INFO,sizeof(str_en_ID_STRING_READING_SYSINIT_INFO)},
	{str_cn_ID_STRING_ERR_PASSWORD,sizeof(str_cn_ID_STRING_ERR_PASSWORD)/_PER_SIZE,str_en_ID_STRING_ERR_PASSWORD,sizeof(str_en_ID_STRING_ERR_PASSWORD)},
	{str_cn_ID_STRING_ERR_OVERRANGE,sizeof(str_cn_ID_STRING_ERR_OVERRANGE)/_PER_SIZE,str_en_ID_STRING_ERR_OVERRANGE,sizeof(str_en_ID_STRING_ERR_OVERRANGE)},
	{str_cn_ID_STRING_CONFIRM,sizeof(str_cn_ID_STRING_CONFIRM)/_PER_SIZE,str_en_ID_STRING_CONFIRM,sizeof(str_en_ID_STRING_CONFIRM)},
	{str_cn_ID_STRING_ERR_TIME,sizeof(str_cn_ID_STRING_ERR_TIME)/_PER_SIZE,str_en_ID_STRING_ERR_TIME,sizeof(str_en_ID_STRING_ERR_TIME)},
	{str_cn_ID_STRING_NO_ABNORMAL,sizeof(str_cn_ID_STRING_NO_ABNORMAL)/_PER_SIZE,str_en_ID_STRING_NO_ABNORMAL,sizeof(str_en_ID_STRING_NO_ABNORMAL)},
	{str_cn_ID_STRING_OPERATION_SUCCESS,sizeof(str_cn_ID_STRING_OPERATION_SUCCESS)/_PER_SIZE,str_en_ID_STRING_OPERATION_SUCCESS,sizeof(str_en_ID_STRING_OPERATION_SUCCESS)},
	{str_cn_ID_STRING_DO_OFF2ON,sizeof(str_cn_ID_STRING_DO_OFF2ON)/_PER_SIZE,str_en_ID_STRING_DO_OFF2ON,sizeof(str_en_ID_STRING_DO_OFF2ON)},
	{str_cn_ID_STRING_DO_ON2OFF,sizeof(str_cn_ID_STRING_DO_ON2OFF)/_PER_SIZE,str_en_ID_STRING_DO_ON2OFF,sizeof(str_en_ID_STRING_DO_ON2OFF)},
	{str_cn_ID_STRING_RESET_CONFIRM,sizeof(str_cn_ID_STRING_RESET_CONFIRM)/_PER_SIZE,str_en_ID_STRING_RESET_CONFIRM,sizeof(str_en_ID_STRING_RESET_CONFIRM)},
	{str_cn_ID_STRING_RESET,sizeof(str_cn_ID_STRING_RESET)/_PER_SIZE,str_en_ID_STRING_RESET,sizeof(str_en_ID_STRING_RESET)},
	{str_cn_ID_STRING_RESTART,sizeof(str_cn_ID_STRING_RESTART)/_PER_SIZE,str_en_ID_STRING_RESTART,sizeof(str_en_ID_STRING_RESTART)},
	{str_cn_ID_STRING_RESTART_CONFIRM,sizeof(str_cn_ID_STRING_RESTART_CONFIRM)/_PER_SIZE,str_en_ID_STRING_RESTART_CONFIRM,sizeof(str_en_ID_STRING_RESTART_CONFIRM)},
	{str_cn_ID_STRING_CONFIG_VERSION,sizeof(str_cn_ID_STRING_CONFIG_VERSION)/_PER_SIZE,str_en_ID_STRING_CONFIG_VERSION,sizeof(str_en_ID_STRING_CONFIG_VERSION)},
	{str_cn_ID_STRING_NOW_TIME,sizeof(str_cn_ID_STRING_NOW_TIME)/_PER_SIZE,str_en_ID_STRING_NOW_TIME,sizeof(str_en_ID_STRING_NOW_TIME)},
	{str_cn_ID_STRING_DOWNLOAD,sizeof(str_cn_ID_STRING_DOWNLOAD)/_PER_SIZE,str_en_ID_STRING_DOWNLOAD,sizeof(str_en_ID_STRING_DOWNLOAD)},

};

const INT16U NUM_STRINGRESOURCE = sizeof(StringRes)/sizeof(STR_RES);
