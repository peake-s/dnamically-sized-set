#include "intSet.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

int main(void){
  intSet set1=createSet();
  printf("%d\n",card(set1));
  printf("%s\n",toString(set1));
  bool test=isEmpty(set1);
  if(test==true)
    printf("yes\n");
  for(int i=0;i<6;i++){
    if(i%2==0)
      add(set1,i);
    else add(set1,i+6);
  }
  intSet set2=createSet();
  printf("%d\n",card(set1));
  printf("set1 %s\n",toString(set1));
  int *arr=toArray(set1);
  printf("to array test \n");
  for(int i=0;i<6;i++)
    printf("%d ",arr[i]);
  printf("\n%d\n",card(set2));
  return 0;
}
