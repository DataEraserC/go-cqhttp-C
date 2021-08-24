#pragma once

typedef enum
{
	None,					//û�д���
	WSAStartupError,		//WSAStartup�����쳣
	SocketInitError,		//socket��ʼ���쳣
	BindError,				//�󶨶˿�ʧ��
	ListenError,			//�����˿�ʧ��
	AcceptFailed,			//��������ʧ��
	ConnectionError,		//���Ӵ���
	NetworkIOError,			//����IO����
	NULLError				//��ָ���쳣
}cqhttp_err_list;	//��������

typedef struct
{
	cqhttp_err_list error;	//��������
	char function[20];		//������
} cqhttp_err;		//�����װ

//����cqhttp_err
cqhttp_err set_cqhttp_err(
	cqhttp_err_list list,	//��������
	char function[20]		//������
);

//�������
cqhttp_err_list cqhttp_err_out(
	cqhttp_err err		//������Ϣ
);