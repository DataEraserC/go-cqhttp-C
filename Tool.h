#pragma once
#include<malloc.h>
#include<stdio.h>

//��ȡ�ļ���С
int getFileSize(FILE* fp);

//��ȫ�����ڴ棨ʹ��malloc���룬�������NULL�����˳�����
void* malloc_s(size_t size);

//ȥ��http��Ϣͷ
char* removeHeaders(char* httpMessage);