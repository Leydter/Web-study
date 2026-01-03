#include <stdio.h>
int main()
{
  FILE *file = fopen("C:\\Users\\林\\Desktop\\code\\API\\例题\\02--焦点图案例.html", "r");
  int c;
  while ((c = fgetc(file)) != -1)
  {
    printf("%c", c);
  }

  fclose(file);
}