/*
 * @Author: your name
 * @Date: 2021-08-19 11:35:52
 * @LastEditTime: 2021-08-20 11:18:49
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \c\str.c
 */
#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct A
{
	int a;
	short d;
	int c;
	char b;
};
int main()
{
  char *str;
  char str2[] = "hello word2";
  str = "hello word";
  printf("%x\r\n",*str);
  printf("%s\r\n",str);
  printf("%s\r\n",str2);
  // printf("%d\n",sizeof(str));
  // printf("%d\n",sizeof(str2) );
  //int a = 1;
  //printf("%d",sizeof(char));
  //printf(sizeof(str2));
  int b = sizeof(str);
  printf("%d\n",b);

  int c = sizeof(str2);
  printf("%d\n",c);

  char str3 = 'a';
  int d = sizeof(str3);
  printf("%d\n",d);

  char pwd[128];
  char *res = getcwd(pwd,128);
  printf("%s\n", res);
}
