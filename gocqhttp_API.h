#pragma once
#include"gocqhttp_err.h"

/*��ʼ��*/
cqhttp_err init_gocqhttpAPI(const char* ip, const int port);

/*�˳�*/
void exit_gocqhttpAPI(void);

/////////////////////////////////
/*send_private_msg ����˽����Ϣ*/
/////////////////////////////////

#define API_SEND_PRIVATE_MSG_FORM	"GET /send_private_msg?user_id=%u&group_id=%u&message=%s&auto_escape=%d HTTP/1.1\r\nHost: 127.0.0.1:5700\r\nConnection: keep-alive\r\n\r\n"
#define API_SEND_PRIVATE_MSG_RECV	"%*[^{]{\"data\":{\"message\":%d},\"retcode\":%d,\"status\":\"%[^\"]\""

typedef struct
{
	unsigned long user_id;	//�Է� QQ ��
	unsigned long group_id;	//����������ʱ�ỰȺ��(�����˱�������ǹ���Ա/Ⱥ��)
	char message[300];		//Ҫ���͵�����
	int auto_escape;		//��Ϣ�����Ƿ���Ϊ���ı����ͣ�ֻ�� message �ֶ����ַ���ʱ��Ч(Ĭ��ֵ false��
}send_private_msg_s;	//������Ϣ��

typedef struct
{
	struct
	{
		int message_id;		//��ϢID
	}data;	//��������
	int retcode;			//������
	char status[10];		//״̬
}send_private_msg_r;	//������Ϣ��

typedef union
{
	send_private_msg_s send_msg;	//����
	send_private_msg_r recv_msg;	//�հ�
}send_private_msg_data;//��ϰ�

//API
cqhttp_err send_private_msg(
	send_private_msg_data* data				//����
);

//��ȡ����
send_private_msg_data* New_send_private_msg(
	unsigned long user_id,					//�û�ID
	unsigned long group_id,					//Ⱥ��
	char message[300],						//��Ϣ
	int auto_escape							//�Ƿ��ı�
);

/////////////////////////////
/*send_group_msg ����Ⱥ��Ϣ*/
/////////////////////////////

#define API_SEND_GROUP_MSG_FORM		"GET /send_group_msg?group_id=%ld&message=%s&auto_escape=%d HTTP/1.1\r\nHost: 127.0.0.1:5700\r\nConnection: keep-alive\r\n\r\n"
#define API_SEND_GROUP_MSG_RECV		"%*[^{]{\"data\":{\"message\":%d},\"retcode\":%d,\"status\":\"%[^\"]\""

typedef struct
{
	unsigned long group_id;	//Ⱥ��
	char message[300];		//Ҫ���͵�����
	int auto_escape;		//��Ϣ�����Ƿ���Ϊ���ı����ͣ�ֻ�� message �ֶ����ַ���ʱ��Ч(Ĭ��ֵ false��
}send_group_msg_s;  //������Ϣ��

typedef struct
{
	struct
	{
		int message_id;		//��ϢID
	}data;	//��������
	int retcode;			//������
	char status[10];		//״̬
}send_group_msg_r;  //������Ϣ��

typedef union
{
	send_group_msg_s send_msg;		//����
	send_group_msg_r recv_msg;		//�հ�
}send_group_msg_data;//��ϰ�

//API
cqhttp_err send_group_msg(
	send_group_msg_data* data				//����
);

//��ȡ����
send_group_msg_data* New_send_group_msg(
	unsigned long group_id,					//Ⱥ��
	char message[300],						//��Ϣ
	int auto_escape							//�Ƿ��ı�
);

///////////////////////
/*delete_msg ������Ϣ*/
///////////////////////

#define API_DELETE_MSG_FORM			"GET /delete_msg?message_id=%d HTTP/1.1\r\nHost: 127.0.0.1:5700\r\nConnection: keep-alive\r\n\r\n"
#define API_DELETE_MSG_RECV			"%*[^{]{\"data\":%[^,],\"retcode\":%d,\"status\":\"%[^\"]\""

typedef struct
{
	int message_id;	//��Ϣ ID
}delete_msg_s;		//������Ϣ��

typedef struct
{
	char* data[10];			//��������
	int retcode;			//������
	char status[10];		//״̬
}delete_msg_r;		//������Ϣ��

typedef union
{
	delete_msg_s send_msg;			//����
	delete_msg_r recv_msg;			//�հ�
}delete_msg_data;		//��ϰ�

//API
cqhttp_err delete_msg(
	delete_msg_data* data					//����
);

//��ȡ����
delete_msg_data* New_delete_msg(
	int message_id							//��ϢID
);