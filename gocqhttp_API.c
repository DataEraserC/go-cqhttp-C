#include"gocqhttp_API.h"
#include<process.h>
#include<winsock2.h>
#include<windows.h>
#include<WS2tcpip.h>
#include<stdio.h>
#include<string.h>
#pragma comment(lib, "ws2_32.lib")

/* socket */
static SOCKADDR_IN	server_addr;//�����
static SOCKET		server;		//�½��׽���

/*��*/
static int len_max = 130;

/*send_private_msg ����˽����Ϣ*/
send_private_msg_data* New_send_private_msg(unsigned long user_id, unsigned long group_id, char message[300], int auto_escape)
{
	send_private_msg_data* data = (send_private_msg_data*)malloc(sizeof(send_private_msg_data));
	if (!data)
		return NULL;
	data->send_msg.user_id = user_id;
	data->send_msg.group_id = group_id;
	strcpy(data->send_msg.message, message);
	data->send_msg.auto_escape = auto_escape;
	return data;
}

cqhttp_err send_private_msg(send_private_msg_data* data)
{
	char func[70] = "send_private_msg";

	char rmsg[500] = { '\0' };							//�հ�
	const int len = strlen(data->send_msg.message) + 1;	//��Ϣ����
	char* smsg = (char*)malloc(len + len_max);			//����
	if (!smsg)
		return set_cqhttp_err(NULLError, func, 1, "�����ڴ�����ʧ��");
	memset(smsg, 0, len + len_max);

	//�����������ַ�����
	sprintf(smsg, API_SEND_PRIVATE_MSG_FORM,
			data->send_msg.user_id,
			data->send_msg.group_id,
			data->send_msg.message,
			data->send_msg.auto_escape);
	int isend = send(server, smsg, strlen(smsg), 0);	//����
	if (isend < 0)
		return set_cqhttp_err(NetworkIOError, func, 1, "��������ʧ��");

	memset(data, 0, sizeof(data));
	while (recv(server, rmsg, sizeof(rmsg), 0) < 0);	//����
	if(sscanf(rmsg, API_SEND_PRIVATE_MSG_RECV,
				&data->recv_msg.data.message_id,
				&data->recv_msg.retcode,
				data->recv_msg.status) == -1)
		cqhttp_err_out(set_cqhttp_err(StringError, func, 1, "sscanf"));

	free(smsg);
	return set_cqhttp_err(None, func, 0, NULL);
}

/*send_group_msg ����Ⱥ��Ϣ*/
send_group_msg_data* New_send_group_msg(unsigned long group_id, char message[300], int auto_escape)
{
	send_group_msg_data* data = (send_group_msg_data*)malloc(sizeof(send_group_msg_data));
	if (!data)
		return NULL;
	data->send_msg.group_id = group_id;
	strcpy(data->send_msg.message, message);
	data->send_msg.auto_escape = auto_escape;
	return data;
}

cqhttp_err send_group_msg(send_group_msg_data* data)
{
	char func[70] = "send_group_msg";

	char rmsg[500] = { '\0' };							//�հ�
	const int len = strlen(data->send_msg.message) + 1;	//��Ϣ����
	char* smsg = (char*)malloc(len + len_max);			//����
	if (!smsg)
		return set_cqhttp_err(NULLError, func, 1, "�����ڴ�����ʧ��");
	memset(smsg, 0, len + len_max);

	//��������
	sprintf(smsg, API_SEND_GROUP_MSG_FORM,
			data->send_msg.group_id,
			data->send_msg.message,
			data->send_msg.auto_escape);
	int isend = send(server, smsg, strlen(smsg), 0);	//����
	if (isend < 0)
		return set_cqhttp_err(NetworkIOError, func, 1, "��������ʧ��");

	memset(data, 0, sizeof(data));
	while (recv(server, rmsg, sizeof(rmsg), 0) < 0);	//����
	if (sscanf(rmsg, API_SEND_GROUP_MSG_RECV,
		&data->recv_msg.data.message_id,
		&data->recv_msg.retcode,
		data->recv_msg.status) == -1)
		cqhttp_err_out(set_cqhttp_err(StringError, func, 1, "sscanf"));

	free(smsg);
	return set_cqhttp_err(None, func, 0, NULL);
}

/*delete_msg ������Ϣ*/
delete_msg_data* New_delete_msg(int message_id)
{
	delete_msg_data* data = (delete_msg_data*)malloc(sizeof(delete_msg_data));
	if (!data)
		return NULL;
	data->send_msg.message_id = message_id;
	return data;
}

cqhttp_err delete_msg(delete_msg_data* data)
{
	char func[70] = "delete_msg";

	char rmsg[500] = { '\0' };							//�հ�
	char* smsg = (char*)malloc(len_max);				//����
	if (!smsg)
		return set_cqhttp_err(NULLError, func, 1, "�����ڴ�����ʧ��");
	memset(smsg, 0, len_max);

	//��������
	sprintf_s(smsg, len_max, API_DELETE_MSG_FORM,
		data->send_msg.message_id);
	int isend = send(server, smsg, strlen(smsg), 0);	//����
	if (isend < 0)
		return set_cqhttp_err(NetworkIOError, func, 1, "��������ʧ��");

	memset(data, 0, sizeof(data));
	while (recv(server, rmsg, sizeof(rmsg), 0) < 0);	//����
	if (sscanf(rmsg, API_SEND_GROUP_MSG_RECV,
		data->recv_msg.data,
		&data->recv_msg.retcode,
		data->recv_msg.status) == -1)
		cqhttp_err_out(set_cqhttp_err(StringError, func, 1, "sscanf"));

	free(smsg);
	return set_cqhttp_err(None, func, 0, NULL);
}

/*��ʼ��*/
cqhttp_err init_gocqhttpAPI(const char* ip, const int port)
{
	const char func[70] = "init_gocqhttpAPI";

	memset((void*)&server_addr, 0, sizeof(SOCKADDR_IN));
	
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	inet_pton(AF_INET, ip, (void*)&server_addr.sin_addr);

	WSADATA wsaData;
	int e = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (e)
		return set_cqhttp_err(WSAStartupError, func, 1, "��ʼ����̬��ʧ��");
	
	if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		return set_cqhttp_err(SocketInitError, func, 0, NULL);
	
	if (connect(server, (SOCKADDR*)&server_addr, sizeof(server_addr)) < 0)
		return set_cqhttp_err(ConnectionError, func, 0, NULL);
	else
		return set_cqhttp_err(None, func, 0, NULL);
}

/*�˳�*/
void exit_gocqhttpAPI(void)
{
	closesocket(server);  
	memset((void*)&server_addr, 0, sizeof(server_addr));
}