#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 基础常量与结构定义
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAX_TABLE_SIZE 11 // 哈希表容量（质数）
typedef int Status;
typedef int ElemType;

// 开放定址法（线性探测）哈希表结构
typedef struct
{
  ElemType elem[MAX_TABLE_SIZE]; // 存储元素
  int state[MAX_TABLE_SIZE];     // 状态：0-空，1-占用，2-已删除
  int tablesize;                 // 容量
} HashTable_L;

// 全局标志：标记哈希表是否已初始化（管控操作顺序）
int isInited = FALSE;

/*****************************************
 * 核心功能函数（开放定址法）
 *****************************************/
// 哈希函数（取模法）
int HashFunc(ElemType e)
{
  return e % MAX_TABLE_SIZE;
}

// 1. 初始化哈希表
Status InitHashTable_L(HashTable_L *HT)
{
  if (isInited == TRUE)
  {
    printf("哈希表已初始化，无需重复操作！\n");
    return ERROR;
  }
  HT->tablesize = MAX_TABLE_SIZE;
  for (int i = 0; i < HT->tablesize; i++)
  {
    HT->state[i] = 0; // 初始为空
    HT->elem[i] = 0;  // 占位值
  }
  isInited = TRUE;
  printf("哈希表初始化成功！容量：%d\n", MAX_TABLE_SIZE);
  return OK;
}

// 2. 插入元素（用户输入元素值）
Status InsertHash_L(HashTable_L *HT, ElemType e)
{
  if (isInited == FALSE)
  {
    printf("请先初始化哈希表！\n");
    return ERROR;
  }
  if (e < 0)
  {
    printf("插入的值不合法!请重新输入");
    return ERROR;
  }
  // 先检查是否重复
  int addr = HashFunc(e);
  int i = 0;
  while (i < HT->tablesize && HT->state[addr] != 0)
  {
    if (HT->state[addr] == 1 && HT->elem[addr] == e)
    {
      printf("元素 %d 已存在，不允许重复插入！\n", e);
      return ERROR;
    }
    addr = (HashFunc(e) + i) % HT->tablesize;
    i++;
  }
  // 检查是否表满
  if (i >= HT->tablesize)
  {
    printf("哈希表已满，无法插入元素 %d！\n", e);
    return ERROR;
  }
  // 插入元素
  HT->elem[addr] = e;
  HT->state[addr] = 1;
  printf("元素 %d 插入成功！存储地址：%d\n", e, addr);
  return OK;
}

// 3. 删除元素（用户输入元素值）
Status DeleteHash_L(HashTable_L *HT, ElemType e)
{
  if (isInited == FALSE)
  {
    printf("请先初始化哈希表！\n");
    return ERROR;
  }
  // 查找元素
  int addr = HashFunc(e);
  int i = 0;
  while (i < HT->tablesize && HT->state[addr] != 0)
  {
    if (HT->state[addr] == 1 && HT->elem[addr] == e)
    {
      // 标记为已删除
      HT->state[addr] = 2;
      printf("元素 %d 删除成功！原地址：%d\n", e, addr);
      return OK;
    }
    addr = (HashFunc(e) + i) % HT->tablesize;
    i++;
  }
  printf("元素 %d 不存在，删除失败！\n", e);
  return ERROR;
}

// 4. 查找元素（用户输入元素值）
int SearchHash_L(HashTable_L HT, ElemType e)
{
  if (isInited == FALSE)
  {
    printf("请先初始化哈希表！\n");
    return -2; // 用-2表示未初始化（区别于-1的不存在）
  }
  int addr = HashFunc(e);
  int i = 0;
  while (i < HT.tablesize && HT.state[addr] != 0)
  {
    if (HT.state[addr] == 1 && HT.elem[addr] == e)
    {
      printf("元素 %d 查找成功！存储地址：%d\n", e, addr);
      return addr;
    }
    addr = (HashFunc(e) + i) % HT.tablesize;
    i++;
  }
  printf("元素 %d 不存在！\n", e);
  return -1;
}

// 5. 查看表长（有效元素个数）
int HashLength_L(HashTable_L HT)
{
  if (isInited == FALSE)
  {
    printf("请先初始化哈希表！\n");
    return -1;
  }
  int len = 0;
  for (int i = 0; i < HT.tablesize; i++)
  {
    if (HT.state[i] == 1)
      len++;
  }
  printf("哈希表当前有效元素个数：%d\n", len);
  return len;
}

// 6. 查看哈希表状态（可视化每个位置的元素+状态，增强互动感知）
void ShowHashTable_L(HashTable_L HT)
{
  if (isInited == FALSE)
  {
    printf("请先初始化哈希表！\n");
    return;
  }
  printf("\n=========================================\n");
  printf("哈希表当前状态（容量：%d）\n", HT.tablesize);
  printf("地址 | 元素值 | 状态（0=空，1=占用，2=已删除）\n");
  printf("-----------------------------------------\n");
  for (int i = 0; i < HT.tablesize; i++)
  {
    printf("%3d | %5d | %d\n", i, HT.elem[i], HT.state[i]);
  }
  printf("=========================================\n\n");
}

// 7. 清空哈希表
Status ClearHashTable_L(HashTable_L *HT)
{
  if (isInited == FALSE)
  {
    printf("请先初始化哈希表！\n");
    return ERROR;
  }
  for (int i = 0; i < HT->tablesize; i++)
  {
    HT->state[i] = 0;
    HT->elem[i] = 0;
  }
  printf("哈希表清空成功！所有位置恢复为“空”状态\n");
  return OK;
}

// 8. 销毁哈希表
Status DestroyHashTable_L(HashTable_L *HT)
{
  if (isInited == FALSE)
  {
    printf("哈希表未初始化，无需销毁！\n");
    return ERROR;
  }
  ClearHashTable_L(HT);
  HT->tablesize = 0;
  isInited = FALSE; // 销毁后需重新初始化才能操作
  printf("哈希表销毁成功！后续操作需重新初始化\n");
  return OK;
}

/*****************************************
 * 辅助函数：输入合法性校验（确保用户输入整数）
 *****************************************/
// 读取用户输入的整数，若输入非数字则提示重新输入
int ReadIntInput(const char *prompt)
{
  int num;
  char buf[50]; // 临时存储输入字符串
  while (1)
  {
    printf("%s", prompt);
    fgets(buf, sizeof(buf), stdin);
    // 检查是否为有效整数（忽略前后空格）
    if (sscanf(buf, "%d", &num) == 1)
    {
      return num;
    }
    printf("输入无效！请输入整数（如10、25）\n");
  }
}

/*****************************************
 * 主函数：菜单驱动的互动流程
 *****************************************/
int main()
{
  HashTable_L htL;
  int choice; // 用户选择的操作序号

  // 欢迎界面
  printf("=========================================\n");
  printf("   开放定址法哈希表互动测试系统\n");
  printf("   学生姓名：林勇佳\n");
  printf("   学号：3124004327\n");
  printf("   专业班级：计算机科学与技术11班\n");
  printf("   指导教师：林志毅\n");
  printf("=========================================\n");

  // 循环菜单：直至用户选择退出
  while (1)
  {
    // 打印操作菜单
    printf("\n【请选择操作（输入序号）】\n");
    printf("1. 初始化哈希表\n");
    printf("2. 插入元素（需输入元素值）\n");
    printf("3. 删除元素（需输入元素值）\n");
    printf("4. 查找元素（需输入元素值）\n");
    printf("5. 查看有效元素个数\n");
    printf("6. 查看哈希表完整状态\n");
    printf("7. 清空哈希表\n");
    printf("8. 销毁哈希表\n");
    printf("0. 退出系统\n");

    // 读取用户选择（校验是否为0-8的整数）
    choice = ReadIntInput("请输入操作序号：");
    if (choice < 0 || choice > 8)
    {
      printf("操作序号无效！请输入0-8之间的整数\n");
      continue;
    }

    // 根据选择执行对应操作
    switch (choice)
    {
    case 1:
      InitHashTable_L(&htL);
      break;
    case 2:
    {
      ElemType e = ReadIntInput("请输入要插入的元素值：");
      InsertHash_L(&htL, e);
      break;
    }
    case 3:
    {
      ElemType e = ReadIntInput("请输入要删除的元素值：");
      DeleteHash_L(&htL, e);
      break;
    }
    case 4:
    {
      ElemType e = ReadIntInput("请输入要查找的元素值：");
      SearchHash_L(htL, e);
      break;
    }
    case 5:
      HashLength_L(htL);
      break;
    case 6:
      ShowHashTable_L(htL);
      break;
    case 7:
      ClearHashTable_L(&htL);
      break;
    case 8:
      DestroyHashTable_L(&htL);
      break;
    case 0:
      printf("\n感谢使用！系统退出中...\n");
      return 0; // 退出程序
    }
  }
}