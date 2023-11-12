#include "Log.h"
#include "Tool.h"
#include <malloc.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h> // For mkdir
#include <time.h>
#include <unistd.h> // For access

struct _logTypeInfoBase {
  LogType baseType; //预设类型的基本类型（信息，警告，错误）
  char *info;
};
typedef struct _logTypeInfoBase LogTypeInfoBase;
static LogTypeInfoBase setBaseType(LogType type, char *info);

/*获取日志类型基本信息*/
static LogTypeInfoBase getLogTypeInfo(LogType type);

//生成当前格式化时间
static void getNowFormatTime(char *formatTime);

//判断是否初始化
void isLogInit();

//日志输出（根据预设）
void logPreset(LogType type) {
  LogTypeInfoBase baseType;
  baseType = getLogTypeInfo(type);
  switch (baseType.baseType) {
  case Information:
    logInfo(baseType.info);
    break;
  case Warning:
    logWarn(baseType.info);
    break;
  case Error:
    logErr(baseType.info);
    break;
  }
}
void logPresetDetailed(char *functionName, char *filePath, int line,
                       LogType type) {
  LogTypeInfoBase baseType;
  baseType = getLogTypeInfo(type);
  switch (baseType.baseType) {
  case Information:
    logInfoDetailed(functionName, filePath, line, baseType.info);
    break;
  case Warning:
    logWarnDetailed(functionName, filePath, line, baseType.info);
    break;
  case Error:
    logErrDetailed(functionName, filePath, line, baseType.info);
    break;
  }
}

//信息输出
void logInfo(char *message, ...) {
  va_list args;
  va_start(args, message);
  FILE *tempFile;
  char tempFilePath[40] = {'\0'};
  char fileName[11] = {'\0'};
  char *completeMessage;
  int messageSize;

  isLogInit();

  char nowFormatTime[30];
  getNowFormatTime(nowFormatTime);

  // 把格式化字符串暂存到一个文件
  strncpy(fileName, nowFormatTime,
          sizeof(fileName) - 1); // 截取 YYYY-MM-DD 的部分
  fileName[sizeof(fileName) - 1] = '\0';
  sprintf(tempFilePath, "temp/%s", fileName);

  tempFile = fopen(tempFilePath, "wb+");
  if (tempFile == NULL) {
    fclose(tempFile);
    return;
  }
  vfprintf(tempFile, message, args);

  messageSize = getFileSize(tempFile) + 1; // +1 补空字符的位置
  completeMessage = (char *)malloc(messageSize);
  fseek(tempFile, 0L, SEEK_SET);
  fread(completeMessage, messageSize, 1, tempFile);
  completeMessage[messageSize - 1] = '\0'; // 在最后补空字符

  color(INFO_COLOR);
  printf("%s <INFO> %s\n", nowFormatTime, completeMessage);
  color(DEFAULT_COLOR);
  fprintf(logFile, "%s <INFO> %s\n", nowFormatTime, completeMessage);

  fclose(tempFile);
  free(completeMessage);
  // remove(tempFilePath);
}
// 详细信息输出
void logInfoDetailed(char *functionName, char *filePath, int line,
                     char *message, ...) {
  va_list args;
  va_start(args, message);
  FILE *tempFile;
  char tempFilePath[40] = {'\0'};
  char fileName[11] = {'\0'};
  char *completeMessage;
  int messageSize;

  isLogInit();

  char nowFormatTime[30];
  getNowFormatTime(nowFormatTime);

  // 把格式化字符串暂存到一个文件
  strncpy(fileName, nowFormatTime,
          sizeof(fileName) - 1); // 截取 YYYY-MM-DD 的部分
  fileName[sizeof(fileName) - 1] = '\0';
  sprintf(tempFilePath, "temp/%s", fileName);

  tempFile = fopen(tempFilePath, "wb+");
  if (tempFile == NULL) {
    fclose(tempFile);
    return;
  }
  vfprintf(tempFile, message, args);

  messageSize = getFileSize(tempFile) + 1; // +1 补空字符的位置
  completeMessage = (char *)malloc(messageSize);
  fseek(tempFile, 0L, SEEK_SET);
  fread(completeMessage, messageSize, 1, tempFile);
  completeMessage[messageSize - 1] = '\0'; // 在最后补空字符

  color(INFO_COLOR);
  printf("%s <INFO> %s\nfunction: %s\npath: %s\nline: %d\n\n", nowFormatTime,
         completeMessage, functionName, filePath, line);
  color(DEFAULT_COLOR);
  fprintf(logFile, "%s <INFO> %s\nfunction: %s\npath: %s\nline: %d\n\n",
          nowFormatTime, completeMessage, functionName, filePath, line);

  fclose(tempFile);
  free(completeMessage);
  // remove(tempFilePath);
}

void logWarn(char *message, ...) {
  va_list args;
  va_start(args, message);
  FILE *tempFile;
  char tempFilePath[40] = {'\0'};
  char fileName[11] = {'\0'};
  char *completeMessage;
  int messageSize;

  isLogInit();

  char nowFormatTime[30];
  getNowFormatTime(nowFormatTime);

  // 把格式化字符串暂存到一个文件
  strncpy(fileName, nowFormatTime,
          sizeof(fileName) - 1); // 截取 YYYY-MM-DD 的部分
  fileName[sizeof(fileName) - 1] = '\0';
  sprintf(tempFilePath, "temp/%s", fileName);

  tempFile = fopen(tempFilePath, "wb+");
  if (tempFile == NULL) {
    fclose(tempFile);
    return;
  }
  vfprintf(tempFile, message, args);

  messageSize = getFileSize(tempFile) + 1; // +1 补空字符的位置
  completeMessage = (char *)malloc(messageSize);
  fseek(tempFile, 0L, SEEK_SET);
  fread(completeMessage, messageSize, 1, tempFile);
  completeMessage[messageSize - 1] = '\0'; // 在最后补空字符

  color(WARNING_COLOR);
  printf("%s <WARNING> %s\n", nowFormatTime, completeMessage);
  color(DEFAULT_COLOR);
  fprintf(logFile, "%s <WARNING> %s\n", nowFormatTime, completeMessage);

  fclose(tempFile);
  free(completeMessage);
  // remove(tempFilePath);
}
void logWarnDetailed(char *functionName, char *filePath, int line,
                     char *message, ...) {
  va_list args;
  va_start(args, message);
  FILE *tempFile;
  char tempFilePath[40] = {'\0'};
  char fileName[11] = {'\0'};
  char *completeMessage;
  int messageSize;

  isLogInit();

  char nowFormatTime[30];
  getNowFormatTime(nowFormatTime);

  // 把格式化字符串暂存到一个文件
  strncpy(fileName, nowFormatTime,
          sizeof(fileName) - 1); // 截取 YYYY-MM-DD 的部分
  fileName[sizeof(fileName) - 1] = '\0';
  sprintf(tempFilePath, "temp/%s", fileName);

  tempFile = fopen(tempFilePath, "wb+");
  if (tempFile == NULL) {
    fclose(tempFile);
    return;
  }
  vfprintf(tempFile, message, args);

  messageSize = getFileSize(tempFile) + 1; // +1 补空字符的位置
  completeMessage = (char *)malloc(messageSize);
  fseek(tempFile, 0L, SEEK_SET);
  fread(completeMessage, messageSize, 1, tempFile);
  completeMessage[messageSize - 1] = '\0'; // 在最后补空字符

  color(WARNING_COLOR);
  printf("%s <WARNING> %s\nfunction: %s\npath: %s\nline: %d\n\n", nowFormatTime,
         completeMessage, functionName, filePath, line);
  color(DEFAULT_COLOR);
  fprintf(logFile, "%s <WARNING> %s\nfunction: %s\npath: %s\nline: %d\n\n",
          nowFormatTime, completeMessage, functionName, filePath, line);

  fclose(tempFile);
  free(completeMessage);
  // remove(tempFilePath);
}

//错误输出
void logErr(char *message, ...) {
  va_list args;
  va_start(args, message);
  FILE *tempFile;
  char tempFilePath[40] = {'\0'};
  char fileName[11] = {'\0'};
  char *completeMessage;
  int messageSize;

  isLogInit();

  char nowFormatTime[30];
  getNowFormatTime(nowFormatTime);

  // 把格式化字符串暂存到一个文件
  strncpy(fileName, nowFormatTime,
          sizeof(fileName) - 1); // 截取 YYYY-MM-DD 的部分
  fileName[sizeof(fileName) - 1] = '\0';
  sprintf(tempFilePath, "temp/%s", fileName);

  tempFile = fopen(tempFilePath, "wb+");
  if (tempFile == NULL) {
    fclose(tempFile);
    return;
  }
  vfprintf(tempFile, message, args);

  messageSize = getFileSize(tempFile) + 1; // +1 补空字符的位置
  completeMessage = (char *)malloc(messageSize);
  fseek(tempFile, 0L, SEEK_SET);
  fread(completeMessage, messageSize, 1, tempFile);
  completeMessage[messageSize - 1] = '\0'; // 在最后补空字符

  color(4);
  printf("%s <ERROR> %s\n", nowFormatTime, completeMessage);
  color(7);
  fprintf(logFile, "%s <ERROR> %s\n", nowFormatTime, completeMessage);

  fclose(tempFile);
  free(completeMessage);
  // remove(tempFilePath);
}

void logErrDetailed(char *functionName, char *filePath, int line, char *message,
                    ...) {
  va_list args;
  va_start(args, message);
  FILE *tempFile;
  char tempFilePath[40] = {'\0'};
  char fileName[11] = {'\0'};
  char *completeMessage;
  int messageSize;

  isLogInit();

  char nowFormatTime[30];
  getNowFormatTime(nowFormatTime);

  // 把格式化字符串暂存到一个文件
  strncpy(fileName, nowFormatTime,
          sizeof(fileName) - 1); // 只截取 YYYY-MM-DD 的部分
  fileName[sizeof(fileName) - 1] = '\0';
  sprintf(tempFilePath, "temp/%s", fileName);

  tempFile = fopen(tempFilePath, "wb+");
  if (tempFile == NULL) {
    fclose(tempFile);
    return;
  }
  vfprintf(tempFile, message, args);

  messageSize = getFileSize(tempFile) + 1; // +1 补空字符的位置
  completeMessage = (char *)malloc(messageSize);
  fseek(tempFile, 0L, SEEK_SET);
  fread(completeMessage, messageSize, 1, tempFile);
  completeMessage[messageSize - 1] = '\0'; // 在最后补空字符

  color(ERROR_COLOR);
  printf("%s <ERROR> %s\nfunction: %s\npath: %s\nline: %d\n\n", nowFormatTime,
         completeMessage, functionName, filePath, line);
  color(DEFAULT_COLOR);
  fprintf(logFile, "%s <ERROR> %s\nfunction: %s\npath: %s\nline: %d\n\n",
          nowFormatTime, completeMessage, functionName, filePath, line);

  fclose(tempFile);
  free(completeMessage);
  remove(tempFilePath);
}

// 生成当前格式化时间
static void getNowFormatTime(char *formatTime) {
  if (!formatTime)
    return;

  time_t now;
  struct tm *timeinfo;

  time(&now);
  timeinfo = localtime(&now);

  sprintf(formatTime, "%d-%02d-%02d %02d:%02d:%02d", timeinfo->tm_year + 1900,
          timeinfo->tm_mon + 1, timeinfo->tm_mday, timeinfo->tm_hour,
          timeinfo->tm_min, timeinfo->tm_sec);
}

static LogTypeInfoBase getLogTypeInfo(LogType type) {
  switch (type) {
  case Information:
    return setBaseType(Information, "Information");
  case Warning:
    return setBaseType(Warning, "Warning");
  case Error:
    return setBaseType(Error, "Error");
  case WSAStartupError:
    return setBaseType(Error, "Failed to open socket service");
  case SocketInitError:
    return setBaseType(Error, "Initialization scoket error");
  case BindError:
    return setBaseType(Error, "Binding port failed");
  case ListenError:
    return setBaseType(Error, "Listening port failed");
  case AcceptFailed:
    return setBaseType(Warning, "Failed to accept connection");
  case ConnectionError:
    return setBaseType(Error, "Connection server error");
  case NetworkIOException:
    return setBaseType(Warning, "Failed to send or recv");
  case NULLException:
    return setBaseType(Warning, "The pointer is null");
  case NotFound:
    return setBaseType(Warning, "Not found the file");
  case StringException:
    return setBaseType(Warning, "String operation error");
  case AllocNULLEXception:
    return setBaseType(Error, "Memory request failed");
  default:
    return setBaseType(Warning, "No such error type");
  }
}

static LogTypeInfoBase setBaseType(LogType type, char *info) {
  LogTypeInfoBase base;
  base.baseType = type;
  base.info = info;
  return base;
}

//初始化日志模块
void init_Log() {
  char logFileName[30] = {'\0'};
  time_t now;
  struct tm timeinfo;

  if (access("log", F_OK) == -1) // 如果文件夹不存在
  {
    int temp = mkdir("log", 0777);
    if (temp != 0) // 对返回值进行处理
    {
      printf("不能创建log文件夹");
    }
  }

  if (access("temp", F_OK) == -1) // 如果文件夹不存在
  {
    int temp = mkdir("temp", 0777);
    if (temp != 0) // 对返回值进行处理
    {
      printf("不能创建temp文件夹");
    }
  }

  time(&now);
  localtime_r(&now, &timeinfo);
  sprintf(logFileName, "log/%d-%d-%d.log", timeinfo.tm_year + 1900,
          timeinfo.tm_mon + 1, timeinfo.tm_mday);

  FILE *logFile = fopen(logFileName, "a");
  if (logFile == NULL) {
    printf("不能打开日志文件");
  }
}

void isLogInit() {
  if (!logFile) //是否初始化日志模块
  {
    color(DEFAULT_COLOR);
    puts("未初始化日志模块！");
    exit(1);
  }
}

int color(int a) {
  switch (a) {
  case 1:
    printf("\033[31m"); // 红色
    break;
  case 2:
    printf("\033[32m"); // 绿色
    break;
  case 3:
    printf("\033[33m"); // 黄色
    break;
  case 4:
    printf("\033[34m"); // 蓝色
    break;
  case 5:
    printf("\033[35m"); // 紫色
    break;
  case 6:
    printf("\033[36m"); // 青色
    break;
  case 7:
    printf("\033[37m"); // 白色
    break;
  default:
    printf("\033[0m"); // 默认颜色
    break;
  }
  return 0;
}
