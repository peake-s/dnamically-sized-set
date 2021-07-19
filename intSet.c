//Samuel Peake EGRE 246 Project 3
#include "intSet.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
//#include <limits.h>
#include <string.h>


struct intsetType{
  int *data, numItems,size;
};

intSet createSet(){
  intSet set=malloc(sizeof(struct intsetType));
  set->numItems=0;//initialize number of sets in the list to be empty
  set->size=0;
  set->data=NULL;
  //printf("Success\n");
  return set;
}

void destroySet(intSet set){
  set->numItems=0;// reset size
  free(set->data); 
  free(set);//free data elements and then the struct
}

void clear(intSet set){
  for(int i=0;i<set->numItems;i++)
    remove_(set,set->data[i]);//remove all the items
  set->numItems=0;//sets the size of the set to 0
}

int card(const intSet set){
  return set->numItems;
}

static void sortToAscend(intSet s){
  int temp=0;
  for(int i=0;i<s->numItems;i++){//loop to run thru the array
    for(int j=i+1;j<s->numItems;j++){//loop to check ahead in the array
      if(s->data[i]>s->data[j]){//checks to see if the element ahead is less than the current element
        //if it is swap the elements by setting
        temp=s->data[i];//set value to temp value as to not lose current element
        s->data[i]=s->data[j];
        s->data[j]=temp;//swap complete
      }
    }
  }

}

static intSet createCopy(const intSet s){//static function to create copies of the set
  intSet new = createSet();
  for(int i=0;i<s->numItems;i++)
    add(new,s->data[i]);
  return new;
}

bool equals(const intSet x,const intSet y){
  if(x->numItems!=y->numItems)//automatically not equal if of different size
    return false;

  intSet xc= createSet();
  intSet yc=createSet();
  xc=createCopy(x); yc=createCopy(y);
  sortToAscend(xc); sortToAscend(yc); //sort lists to easily compare
  for(int i=0;i<x->numItems;i++){
    if(xc->data[i]!=yc->data[i])
      return false;//return false if the sets are different
  }
  return true;//return true if they are equal
}

bool contains(const intSet set, int x){
  for(int i=0;i<set->numItems;i++){//checks if item is in set
    if(set->data[i]==x)
      return true;//true if the item is in the set
  }
  return false;//false otherwise
}

static int where(const intSet s, int thing){//find position of a desired item
  if(!contains(s,thing))
    return -1;
  for(int i=0;i<s->numItems;i++){
    if(s->data[i]==thing)
      return i;
  }
}

int largest(const intSet s){
  int large=-2000000;
  if(isEmpty(s)){
    printf("error, set is empty");
    exit(EXIT_FAILURE); }
  for(int i=0; i<s->numItems;i++){//loop to check for largest item
    if(s->data[i]>=large)
      large=s->data[i];
  }
  return large;
}

int smallest(const intSet s){
  int small=999999;
  if(isEmpty(s)){
    printf("error, set is empty");
    exit(EXIT_FAILURE); }

  for(int i=0; i<s->numItems;i++){//loop to check for smallest item
    if(s->data[i]<=small)
      small=s->data[i];
  }
  return small;
}

void add(intSet s, int item){
  if(contains(s,item))//checks if the item is in the set and ends if it is
    return;


  if(s->size == s->numItems){//if the list is full, increase the size and add new item
    s->size+=10;//increasing the size of the list by chunk
    int *temp=(int*)malloc((s->size)*(sizeof(int)));//dynamically allocating the temp array
    int *old = s->data;//storing the data from data into the array old to free it up
    for(int i=0;i<s->numItems;i++)//loop to store data data into the temp array
      temp[i]=s->data[i];
    s->data=temp;

    free(old);
  }

  s->data[s->numItems]=item;//add item into the list
  s->numItems++;//increment the current number of items in the set
}

void remove_(intSet s, int item){
  if(!contains(s,item))//if item not in the set end function
    return;

  int pos=where(s,item);//determine position of the item
  for(int i=pos;i<s->numItems;i++)//start the loop at one space before the position
    s->data[i]=s->data[i+1];//shift the position to the right until the item to remove is at the end
  s->numItems-=1;//decrease the size
}

intSet intersect(const intSet x, const intSet y){
  int i=0;
  int j=0;
  intSet inter=createSet();
  intSet xc= createSet(); intSet yc=createSet();
  xc=createCopy(x); yc=createCopy(y);
  sortToAscend(xc); sortToAscend(yc);//sorts arrays to easily sort
  while(i<x->numItems&&j<y->numItems){//loop body makes sure loop does not search out of bounds
    if(xc->data[i]<yc->data[j])//if the data in x < y move x count once
      i++;
    else if(xc->data[i]>yc->data[j])//if the data in y < x move y count once
      j++;
    else{//if shared item add the common element and advance both x and y
      add(inter,yc->data[j]);
      i++; j++;
    }
  }
  return inter;
}


intSet union_(const intSet x, const intSet y){
  intSet u=createSet();
  intSet z=createSet();
  if(isEmpty(x)||isEmpty(y))
    return z;
  z=createCopy(y);
  //u=createCopy(x);
  //sortToAscend(u); sortToAscend(z);
  for(int i=0;i<x->numItems;i++)
    add(u,x->data[i]);
  for(int i=0;i<y->numItems;i++)
    add(u,z->data[i]);
  sortToAscend(u);
  return u;
}

intSet diff(const intSet s1,const intSet s2){
  intSet z=createSet();
  if(isEmpty(s1)||isEmpty(s2))
    return z;

  intSet d=createSet();
  d=createCopy(s1); sortToAscend(d);
  intSet c=createSet();
  c=createCopy(s2); sortToAscend(c);
  intSet inters=createSet();
  inters=intersect(d,c);
  for(int i=0;i<inters->numItems;i++)
    remove_(d,inters->data[i]);

  return d;
}

bool isEmpty(const intSet s){//checks if empty
  if(s->numItems==0)
    return true;
  return false;
}

int *toArray(const intSet s){
  intSet sc=createSet();
  sc=createCopy(s);
  sortToAscend(sc);
  int *ret=sc->data;
  return ret;
}

char *toString(const intSet s){
  char *strNum;

  if(isEmpty(s)){
    strNum =(char*)malloc(3*sizeof(char));
    strcpy(strNum,"{}");
  }

  else{
  intSet sc=createSet();
  sc=createCopy(s);
  sortToAscend(sc);
  int size=(s->numItems*15)+3;//size big enough to hold {}, data, and ,
  strNum =(char*)malloc((size)*sizeof(char));//creating the num to return
  char *temp=malloc(40*sizeof(char));
  for(int i=0;i<s->numItems+3;i++){
    if(i==0)
      strcpy(strNum,"{");
    if(i>0&&i<s->numItems+1){
      if(i==s->numItems)
        sprintf(temp,"%d",sc->data[i-1]);//dont print , at the end
      else
        sprintf(temp,"%d,",sc->data[i-1]);//put in correct piece of data in the list
      strcat(strNum,temp);
    }
    if(i==s->numItems+1)//add } at the end
      strcat(strNum,"}");
    }
    free(temp);
  }

  return strNum;
}

/*

void dbg(stack newStack) {
  itemType holdingArray[500] = {0};
  int i = 0;
  int stackSize = 0;
  int length = 0;
  stack stackHolder = createStack();
  while(!isEmpty(newStack)) {
    push(stackHolder,top(newStack));
    pop(newStack);
  }
  stackSize = size(newStack);
  length = stackSize - 1;
  //printf("This is stackSize: %d This is length: %d\n",stackSize, length);
  printf("DEBUG:[");
  for(i = 0; !isEmpty(stackHolder); ++i) {
    printf("%d", top(stackHolder));
    /*holdingArray[i] = top(newStack);
    if(i != length) {
      printf("%d,", holdingArray[i]);
    }
    else {
      printf("%d", holdingArray[i]);
    }
    push(newStack, top(stackHolder));
    pop(stackHolder);
    if(!isEmpty(stackHolder)) {
      printf(",");
    }
  }
  /*for(int j = i - 1; j >= 0; j--) {
    //push(newStack, holdingArray[j]);
  //}
  printf("](top)\n");
}
*/
