/*************************************************************************
	> File Name: KMP.c
	> Author: 
	> Mail: 
	> Created Time: 日  5/ 8 16:32:52 2016
 ************************************************************************/

/**
 * name:KMP 
 * time:2012-11-22
 * 字符串快速匹配 
 */ 
#include<stdio.h>
#include<string.h>
typedef struct seqstring{
    char string[100];
    int length;
}seqstring;

void getnext(seqstring p,int next[]){
    int i,j;
    next[0]=-1;//next[0]放上-1 
    i=0;//指向字符串每个字符的指针 
    j=-1;
    while(i<p.length){//没有到达结尾的话 
        if(j==-1||p.string[i]==p.string[j]){//如果是第一个字符或遇到相同的字符 
            i++;j++;next[i]=j;
        } 
        else
            j=next[j];
    }
    for(i=0;i<p.length;i++){//输出next[]值 
        printf("%d",next[i]);
    }
} 

int kmp(seqstring t,seqstring p,int next[]){
    int i,j;
    i=j=0;
    while(i<t.length&&j<p.length){
        if(j==-1||t.string[i]==p.string[j]){
            i++;j++;
        }
        else
            j=next[j];
    }
    if(j==p.length) return i-p.length;
    else return -1;
} 
int main(){
    seqstring t,p;
    int next[50];
    printf("please input string t:");
    scanf("%s",t.string);
    
    t.length=strlen(t.string);
    printf("please input string p:");
    scanf("%s",p.string);
    p.length=strlen(p.string);
    
    getnext(p,next);
    printf("\n%d\n",kmp(t,p,next));
}
