#include "gocqhttp_API.h"
#include <WS2tcpip.h>
#include <process.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

/* socket */
static SOCKADDR_IN server_addr; //服务端
static SOCKET server;           //新建套接字

/*send_private_msg 发送私密消息*/
send_private_msg_data *New_send_private_msg(unsigned long user_id,
                                            unsigned long group_id,
                                            char message[1500],
                                            int auto_escape) {
  send_private_msg_data *data =
      (send_private_msg_data *)malloc(sizeof(send_private_msg_data));
  if (!data)
    return NULL;
  data->send_msg.user_id = user_id;
  data->send_msg.group_id = group_id;
  strcpy(data->send_msg.message, message);
  data->send_msg.auto_escape = auto_escape;
  return data;
}

cqhttp_err send_private_msg(send_private_msg_data *data) {
  char func[70] = "send_private_msg";

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return set_cqhttp_err(SocketInitError, func, 0, NULL);
  if (connect(server, (SOCKADDR *)&server_addr, sizeof(server_addr)) < 0)
    return set_cqhttp_err(ConnectionError, func, 0, NULL);

  char rmsg[1024] = {'\0'}; //收包
  char smsg[1024] = {'\0'}; //发包
  memset(smsg, 0, 1024);

  //构建发包（字符串）
  sprintf(smsg, API_SEND_PRIVATE_MSG_FORM, data->send_msg.user_id,
          data->send_msg.group_id, data->send_msg.message,
          data->send_msg.auto_escape);
  int isend = send(server, smsg, strlen(smsg), 0); //发送
  if (isend < 0) {
    closesocket(server);
    return set_cqhttp_err(NetworkIOError, func, 1, "发包发送失败");
  }

  memset(data, 0, sizeof(send_private_msg_data));
  while (recv(server, rmsg, sizeof(rmsg), 0) < 0)
    ; //接收
  if (sscanf(rmsg, API_SEND_PRIVATE_MSG_RECV, &data->recv_msg.data.message_id,
             &data->recv_msg.retcode, data->recv_msg.status) == -1)
    cqhttp_err_out(set_cqhttp_err(StringError, func, 1, "sscanf"));

  closesocket(server);
  return set_cqhttp_err(None, func, 0, NULL);
}

/*send_group_msg 发送群消息*/
send_group_msg_data *New_send_group_msg(unsigned long group_id,
                                        char message[1500], int auto_escape) {
  send_group_msg_data *data =
      (send_group_msg_data *)malloc(sizeof(send_group_msg_data));
  if (!data)
    return NULL;
  data->send_msg.group_id = group_id;
  strcpy(data->send_msg.message, message);
  data->send_msg.auto_escape = auto_escape;
  return data;
}

cqhttp_err send_group_msg(send_group_msg_data *data) {
  char func[70] = "send_group_msg";

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return set_cqhttp_err(SocketInitError, func, 0, NULL);
  if (connect(server, (SOCKADDR *)&server_addr, sizeof(server_addr)) < 0)
    return set_cqhttp_err(ConnectionError, func, 0, NULL);

  char rmsg[1024] = {'\0'}; //收包
  char smsg[1024] = {'\0'}; //发包
  memset(smsg, 0, 1024);

  //构建发包
  sprintf(smsg, API_SEND_GROUP_MSG_FORM, data->send_msg.group_id,
          data->send_msg.message, data->send_msg.auto_escape);
  int isend = send(server, smsg, strlen(smsg), 0); //发送
  if (isend < 0) {
    closesocket(server);
    return set_cqhttp_err(NetworkIOError, func, 1, "发包发送失败");
  }

  memset(data, 0, sizeof(send_group_msg_data));
  while (recv(server, rmsg, sizeof(rmsg), 0) < 0)
    ; //接收
  if (sscanf(rmsg, API_SEND_GROUP_MSG_RECV, &data->recv_msg.data.message_id,
             &data->recv_msg.retcode, data->recv_msg.status) == -1)
    cqhttp_err_out(set_cqhttp_err(StringError, func, 1, "sscanf"));

  closesocket(server);
  return set_cqhttp_err(None, func, 0, NULL);
}

/*get_msg 获取消息*/
get_msg_data *New_get_msg(int message_id) {
  get_msg_data *data = (get_msg_data *)malloc(sizeof(get_msg_data));
  if (!data)
    return NULL;
  data->send_msg.message_id = message_id;
  return data;
}

cqhttp_err get_msg(get_msg_data *data) {
  char func[70] = "get_msg";

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return set_cqhttp_err(SocketInitError, func, 0, NULL);
  if (connect(server, (SOCKADDR *)&server_addr, sizeof(server_addr)) < 0)
    return set_cqhttp_err(ConnectionError, func, 0, NULL);

  char rmsg[1024] = {'\0'}; //收包
  char smsg[1024] = {'\0'}; //发包
  memset(smsg, 0, 1024);

  //构建发包
  sprintf(smsg, API_GET_MSG_FORM, data->send_msg.message_id);
  int isend = send(server, smsg, strlen(smsg), 0); //发送
  if (isend < 0) {
    closesocket(server);
    return set_cqhttp_err(NetworkIOError, func, 1, "发包发送失败");
  }

  memset(data, 0, sizeof(delete_msg_data));
  while (recv(server, rmsg, sizeof(rmsg), 0) < 0)
    ; //接收
  if (sscanf(rmsg, API_GET_MSG_RECV, data->recv_msg.data.group,
             &data->recv_msg.data.group_id, data->recv_msg.data.message,
             &data->recv_msg.data.message_id, &data->recv_msg.data.message_seq,
             data->recv_msg.data.message_type, data->recv_msg.data.raw_message,
             &data->recv_msg.data.real_id, data->recv_msg.data.sender.nickname,
             &data->recv_msg.data.sender.user_id, &data->recv_msg.data.time,
             &data->recv_msg.retcode, data->recv_msg.status) == -1)
    cqhttp_err_out(set_cqhttp_err(StringError, func, 1, "sscanf"));

  closesocket(server);
  return set_cqhttp_err(None, func, 0, NULL);
}

/*delete_msg 撤回消息*/
delete_msg_data *New_delete_msg(int message_id) {
  delete_msg_data *data = (delete_msg_data *)malloc(sizeof(delete_msg_data));
  if (!data)
    return NULL;
  data->send_msg.message_id = message_id;
  return data;
}

cqhttp_err delete_msg(delete_msg_data *data) {
  char func[70] = "delete_msg";

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    return set_cqhttp_err(SocketInitError, func, 0, NULL);
  if (connect(server, (SOCKADDR *)&server_addr, sizeof(server_addr)) < 0)
    return set_cqhttp_err(ConnectionError, func, 0, NULL);

  char rmsg[1024] = {'\0'}; //收包
  char smsg[1024] = {'\0'}; //发包
  memset(smsg, 0, 1024);

  //构建发包
  sprintf(smsg, API_DELETE_MSG_FORM, data->send_msg.message_id);
  int isend = send(server, smsg, strlen(smsg), 0); //发送
  if (isend < 0) {
    closesocket(server);
    return set_cqhttp_err(NetworkIOError, func, 1, "发包发送失败");
  }

  memset(data, 0, sizeof(data));
  while (recv(server, rmsg, sizeof(rmsg), 0) < 0)
    ; //接收
  if (sscanf(rmsg, API_DELETE_MSG_RECV, data->recv_msg.data,
             &data->recv_msg.retcode, data->recv_msg.status) == -1)
    cqhttp_err_out(set_cqhttp_err(StringError, func, 1, "sscanf"));

  closesocket(server);
  return set_cqhttp_err(None, func, 0, NULL);
}

/*初始化*/
cqhttp_err init_gocqhttpAPI(const char *ip, const int port) {
  const char func[70] = "init_gocqhttpAPI";

  memset((void *)&server_addr, 0, sizeof(SOCKADDR_IN));

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(port);
  inet_pton(AF_INET, ip, (void *)&server_addr.sin_addr);

  WSADATA wsaData;
  int e = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (e)
    return set_cqhttp_err(WSAStartupError, func, 1, "初始化动态库失败");

  return set_cqhttp_err(None, func, 0, NULL);
}

/*退出*/
void exit_gocqhttpAPI(void) {
  closesocket(server);
  memset((void *)&server_addr, 0, sizeof(server_addr));
}
