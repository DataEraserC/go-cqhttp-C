/* 本文件代码来自于
 * https://blog.csdn.net/langeldep/article/details/6264058
 * https://blog.csdn.net/bladeandmaster88/article/details/54800287
 * 并稍加修改，并非本作者编写，仅仅是为了初学者能更快地进行机器人的编写，
 * 并非抄袭之意，如有侵权请联系我
 */
#include "URLcode.h"
#include "Tool.h"
#include <locale.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

static int hex2dec(char c);
static char dec2hex(short c);

int hex2dec(char c) {
  if ('0' <= c && c <= '9')
    return c - '0';
  else if ('a' <= c && c <= 'f')
    return c - 'a' + 10;
  else if ('A' <= c && c <= 'F')
    return c - 'A' + 10;
  else
    return -1;
}

char dec2hex(short c) {
  if (0 <= c && c <= 9)
    return c + '0';
  else if (10 <= c && c <= 15)
    return c + 'A' - 10;
  else
    return -1;
}

/*URL编码 */
char *urlencode(char url[]) {
  int i;
  int len = strlen(url);
  int res_len = 0;
  char *res = (char *)malloc(CODESIZE_MAX + 1);
  if (!res)
    return NULL;
  memset(res, 0, 1025);
  for (i = 0; i < len; ++i) {
    char c = url[i];
    if (('0' <= c && c <= '9') || ('a' <= c && c <= 'z') ||
        ('A' <= c && c <= 'Z') || c == '/' || c == '.')
      res[res_len++] = c;
    else {
      int j = (short)c;
      if (j < 0)
        j += 256;
      int i1, i0;
      i1 = j / 16;
      i0 = j - i1 * 16;
      res[res_len++] = '%';
      res[res_len++] = dec2hex(i1);
      res[res_len++] = dec2hex(i0);
    }
  }
  res[res_len] = '\0';
  return res;
}

/* GBK to UTF-8 */
char *GBKtoUTF8(char *strGbk) {
  setlocale(LC_ALL, "zh_CN.GBK");

  int len = mbstowcs(NULL, strGbk, 0);
  if (len == -1)
    return NULL;

  wchar_t *strUnicode = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
  if (!strUnicode)
    return NULL;

  mbstowcs(strUnicode, strGbk, len + 1);

  len = wcstombs(NULL, strUnicode, 0);
  if (len == -1) {
    free(strUnicode);
    return NULL;
  }

  char *strUtf8 = (char *)malloc(sizeof(char) * (len + 1));
  if (!strUtf8) {
    free(strUnicode);
    return NULL;
  }

  wcstombs(strUtf8, strUnicode, len + 1);

  free(strUnicode);
  return strUtf8;
}

/* UTF-8 to GBK */
char *UTF8toGBK(char *strUtf8) {
  setlocale(LC_ALL, "zh_CN.UTF-8");

  int len = mbstowcs(NULL, strUtf8, 0);
  if (len == -1)
    return NULL;

  wchar_t *strUnicode = (wchar_t *)malloc(sizeof(wchar_t) * (len + 1));
  if (!strUnicode)
    return NULL;

  mbstowcs(strUnicode, strUtf8, len + 1);

  len = wcstombs(NULL, strUnicode, 0);
  if (len == -1) {
    free(strUnicode);
    return NULL;
  }

  char *strGbk = (char *)malloc(sizeof(char) * (len + 1));
  if (!strGbk) {
    free(strUnicode);
    return NULL;
  }

  wcstombs(strGbk, strUnicode, len + 1);

  free(strUnicode);
  return strGbk;
}