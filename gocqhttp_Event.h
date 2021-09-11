#pragma once
#include"gocqhttp_err.h"

#define ACCEPT_COUNT_MAX	20
#define Event_Response		"HTTP/1.1 204 OK\r\n\r\n"

/*�¼���Ϣ*/
typedef enum
{
	message_event,			//��Ϣ
	notice_event,			//֪ͨ
	meta_event,				//����
	unknow_event			//δ֪
}event_type;		//�¼�����

typedef enum
{
	private_message,	//˽���¼�
	group_message,		//Ⱥ��Ϣ�¼�
	unknow_message		//δ֪��Ϣ�¼�
}message_type;		//��Ϣ�¼�����

typedef struct Event_List_Node
{
	char* msg;						//�¼���Ϣ
	struct Event_List_Node* next;	//��һ�ڵ�
}event_list_node;	//��Ϣ�¼��ڵ㣨����

typedef struct
{
	int read;				//�Ƿ�����evebt_get������ȡ
	event_list_node* head;	//�¼�
}event_list_head;					//��Ϣ�¼��ڵ�ͷ������
event_list_head head;

////////////
/*˽���¼�*/
////////////
typedef struct
{
	unsigned long time;			//�¼�������ʱ���
	unsigned long self_id;		//�յ��¼��Ļ����� QQ ��
	char post_type[20];			//�ϱ�����
	char message_type[20];		//��Ϣ����
	char sub_type[20];			//��Ϣ������
	unsigned long target_id;	//��Ҳ��֪���Ǹ�ɶ�ģ��ĵ�Ҳûд�����˿�������Ҳ��֪������ֵӦ�ú�self_id�ֶ�һ��
	int temp_source;			//��ʱ�Ի���Դ
	int message_id;				//��ϢID
	unsigned long user_id;		//������QQ��
	char message[1024];			//��Ϣ����
	char raw_message[1024];		//ԭʼ��Ϣ����
	int font;					//����
	struct
	{
		unsigned long user_id;	//������QQ��
		unsigned long group_id;	//Ⱥ��
		char nickname[50];		//�ǳ�
		char sex[10];			//�Ա�
		int age;				//����
	}sender;		//��������Ϣ
}private_message_event_data;

#define PRIVATE_MESSAGE_EVENT_FORM_1	"%*[^{]{\"font\":%d,\"message\":\"%[^\"]\",\"message_id\":%d,\"message_type\":\"%[^\"]\",\"post_type\":\"%[^\"]\",\"raw_message\":\"%[^\"]\",\"self_id\":%lu,\"sender\":{\"age\":%d,\"nickname\":\"%[^\"]\",\"sex\":\"%[^\"]\",\"user_id\":%lu},\"sub_type\":\"%[^\"]\",\"target_id\":%ld,\"time\":%lu,\"user_id\":%lu}"
#define PRIVATE_MESSAGE_EVENT_FORM_2	"%*[^{]{\"font\":%d,\"message\":\"%[^\"]\",\"message_id\":%d,\"message_type\":\"%[^\"]\",\"post_type\":\"%[^\"]\",\"raw_message\":\"%[^\"]\",\"self_id\":%lu,\"sender\":{\"age\":%d,\"group_id\":%lu,\"nickname\":\"%[^\"]\",\"sex\":\"%[^\"]\",\"user_id\":%lu},\"sub_type\":\"%[^\"]\",\"temp_sourc\":%d\"time\":%lu,\"user_id\":%lu}"

private_message_event_data private_message_event_analysis(char* data);		//�����¼�

//////////////
/*Ⱥ��Ϣ�¼�*/
//////////////
typedef struct
{
	unsigned long time;			//�¼�����ʱ���
	unsigned long self_id;		//�յ��¼��Ļ�����QQ��
	char post_type[20];			//�ϱ�����
	char message_type[20];		//��Ϣ����
	int message_seq;			//����Ϊʲô����ĵ���û�У������˿����ߣ���Ҳ����
	char sub_type[20];			//��Ϣ������
	int message_id;				//��ϢID
	unsigned long group_id;		//Ⱥ��
	unsigned long user_id;		//������QQ��
	struct
	{
		unsigned long id;		//�����û�ID
		char name[40];			//�����û��ǳ�
		char flag[100];			//�����û�flag�����ý���APIʱ�贫��
	}anonymous;	//������Ϣ(������Ϊnull)
	char message[1024];			//��Ϣ����
	char raw_message[1024];		//ԭʼ��Ϣ����
	int font;					//����
	struct
	{
		unsigned long user_id;	//������QQ��
		char nickname[50];		//�ǳ�
		char card[50];			//Ⱥ��Ƭ/��ע
		char sex[10];			//�Ա�
		int age;				//����
		char area[100];			//����
		char level[10];			//��Ա�ȼ�
		char role[20];			//��ɫ
		char title[20];			//ר��ͷ��
	}sender;		//��������Ϣ
}group_message_event_data;

#define GROUP_MESSAGE_EVENT_FORM		"%*[^{]{\"anonymous\":%[^,],\"font\":%d,\"group_id\":%lu,\"message\":\"%[^\"]\",\"message_id\":%d,\"message_seq\":%d,\"message_type\":\"%[^\"]\",\"post_type\":\"%[^\"]\",\"raw_message\":\"%[^\"]\",\"self_id\":%lu,\"sender\":{%[^}]},\"sub_type\":\"%[^\"]\",\"time\":%lu,\"user_id\":%lu}"
#define GROUP_MESSAGE_EVENT_FORM_ANOYMOUS	"{\"flag\":\"%[^\"]\",\"id\":%ld,\"name\":\"%[^\"]\"}"

group_message_event_data group_message_event_analysis(char* data);			//�����¼�

////////////
/*δ֪�¼�*/
////////////
typedef struct
{
	char* data;					//�¼�����
}unknow_event_data;

/*����Event�����*/
cqhttp_err init_gocqhttpEvent(
	const char* ip,
	const int port,
	void(*response)(void* data)				//��Ϣ�¼���Ӧ����
);

/*�����¼�*/
typedef union
{
	private_message_event_data private_message;
	group_message_event_data group_message;
}event_data;

/*����Event*/
cqhttp_err recv_event(void);

////////////////
/*�¼���Ϣ����*/
////////////////

//�ϱ����ͼ���
#define EVENT_TYPE_FORM		"\"post_type\":\"%[^\"]\""
event_type event_type_switch(const char* data);

//��Ϣ���ͼ���
#define	MESSAGE_TYPE_FORM	"\"message_type\":\"%[^\"]\""
message_type message_type_switch(const char* data);

//֪ͨ���ͼ���
// #define NOTICE_TYPE_FORM	""
//notice_type notice_type_switch(char* data);