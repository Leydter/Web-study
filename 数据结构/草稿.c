#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct SList
{
  int *data;
  int length;
  int size;
} SList;
int start(SList *L);
int change(SList *L);
int main()
{
  SList *L = (SList *)malloc(sizeof(SList));
  if (L == NULL)
  {
    printf("内存分配失败!\n");
    return -1;
  }
  if (start(L) != 0)
  {
    free(L);
    return -1;
  }

  if (change(L) != 0)
  {
    free(L->data);
    free(L);
    return -1;
  }
  free(L->data);
  L->data = NULL;
  free(L);
  L = NULL;
  return 0;
}
// 初始化顺序表
int start(SList *L)
{
  L->length = 0;
  printf("请输入要建立的顺序表的数据数量\n");
  scanf("%d", &L->size);
  if (L->size <= 0)
  {
    printf("请规范输入!");
    return -1;
  }

  L->data = malloc(L->size * sizeof(int));
  if (L->data == NULL)
  {
    printf("内存分配失败!\n");
    return -1;
  }
  for (int i = 0; i < L->size; i++)
  {
    L->data[i] = i + 1;
    L->length++;
  }
  printf("初始顺序表内容:\n");
  for (int i = 0; i < L->length; i++)
  {
    printf("%d\n", L->data[i]);
  }
  return 0;
}
// 修改顺序表容量
int change(SList *L)
{
  int oldSize = L->size;
  printf("请输入修改之后顺序表的数据数量\n");
  scanf("%d", &L->size);
  if (L->size <= 0)
  {
    printf("请规范输入!");
    return -1;
  }
  int *temp = realloc(L->data, L->size * sizeof(int));
  if (temp == NULL)
  {
    printf("内存分配失败!");
    L->size = oldSize;
    return -1;
  }
  else
  {
    L->data = temp;
    temp = NULL;
    // 缩减
    if (L->size < oldSize)
    {
      L->length = L->size;
    }
    // 扩充
    if (L->size > oldSize)
    {
      for (int i = oldSize; i < L->size; i++)
      {
        L->data[i] = i + 1;
        L->length++;
      }
    }
    printf("顺序表修改之后的内容为\n");
  }
  for (int i = 0; i < L->length; i++)
  {
    printf("%d\n", L->data[i]);
  }
  return 0;
}