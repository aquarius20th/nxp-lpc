
//��Դ�ļ�
#ifndef STR_TAB_H
#define STR_TAB_H
#define ID_STRING_NONE                                  	0   	//��

#define ID_STRING_LOGO                                  	1   	//UITC2000բ�Ų��װ��

#define ID_STRING_MAIN_MENU                             	2   	//���˵�

#define ID_STRING_VALUE_TAB                             	3   	//ʵʱ��ֵ

#define ID_STRING_GATE_CTRL                             	4   	//բ�Ų���

#define ID_STRING_DEVICE_CFG                            	5   	//װ������

#define ID_STRING_RUN_STAT                              	6   	//����ͳ��

#define ID_STRING_DEVICE_ADDR                           	7   	//װ�õ�ַ

#define ID_STRING_TIME                                  	8   	//ʱ��

#define ID_STRING_GATAGE                                	9   	//բ�ſ���

#define ID_STRING_M                                     	10  	//��

#define ID_STRING_ENCODER_VAL                           	11  	//����������

#define ID_STRING_UP_LEVEL                              	12  	//����ˮλ

#define ID_STRING_DN_LEVEL                              	13  	//����ˮλ

#define ID_STRING_CUR_FLUX                              	14  	//��ǰ��բ����

#define ID_STRING_STATE                                 	15  	//״̬

#define ID_STRING_GATE_STATE                            	16  	//բ��״̬

#define ID_STRING_RAISE                                 	17  	//����

#define ID_STRING_DROP                                  	18  	//�½�

#define ID_STRING_STOP                                  	19  	//ֹͣ

#define ID_STRING_DEST_GATAGE                           	20  	//�趨Ŀ�꿪��

#define ID_STRING_START                                 	21  	//����

#define ID_STRING_RAW_OP                                	22  	//ֱ�Ӳ���

#define ID_STRING_CUR_GATE_STATE                        	23  	//��ǰբ��״̬

#define ID_STRING_COMM_CFG                              	24  	//ͨ�Ų�������

#define ID_STRING_COMM_STATE                            	25  	//ͨ��״̬��Ϣ

#define ID_STRING_VER_INFO                              	26  	//�汾��Ϣ

#define ID_STRING_DIAG                                  	27  	//װ���Լ����

#define ID_STRING_BAUD                                  	28  	//������

#define ID_STRING_DATA_BIT                              	29  	//����λ

#define ID_STRING_STOP_BIT                              	30  	//ֹͣλ

#define ID_STRING_PARITY_BIT                            	31  	//У��λ

#define ID_STRING_RCV_CNT                               	32  	//���ձ��İ�����

#define ID_STRING_SND_CNT                               	33  	//���ͱ��İ�����

#define ID_STRING_RCV_LEN                               	34  	//���ձ����ֽڳ���

#define ID_STRING_SND_LEN                               	35  	//���ͱ����ֽڳ���

#define ID_STRING_FM_VER                                	36  	//�̼��汾

#define ID_STRING_FM_TIME                               	37  	//�̼���¼ʱ��

#define ID_STRING_FILE_VER                              	38  	//�����ļ��汾

#define ID_STRING_FILE_TIME                             	39  	//�����ļ�����ʱ��


//�ַ�����Դ
typedef struct STR_RES
{
/**����**/
	const INT16U * cn;
	INT16U cnlen;
/**Ӣ��**/
	const char * en;
	INT16U enlen;
}STR_RES;

extern const STR_RES StringRes[];

extern const INT16U NUM_STRINGRESOURCE ;
 
#endif	//_RESOURCE_H
