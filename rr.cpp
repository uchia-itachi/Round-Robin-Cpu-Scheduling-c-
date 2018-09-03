/*
 * rboin.cpp
 *
 *  Created on: 09-Aug-2018
 *      Author: sunil
 */

#include<iostream>
#include<stdlib.h>
#include<time.h>
#include<iomanip>
using namespace std;


struct node
{
    int time;
    char c[4];
    node *next;
    node *prev;
};


node *insertion(node *start)
{
    static int i=1;
    node *n=new node;
    n->next=NULL;
    n->prev=NULL;

    n->time=rand()%20+1;
    n->c[0]='P';
    int rev=0,j=i;
    while(j)
    {
        rev=rev*10+j%10;
        j=j/10;
    }
    if(rev/10==0)
    {
        rev=rev*10;
    }
    j=1;
    while(rev)
    {
        n->c[j]=(rev%10+'0');
        rev=rev/10;
        j++;
    }
    n->c[j]='\0';
    i++;
    if(start==NULL)
    {
        start=n;
        n->next=start;
        n->prev=start;
    }
    else
    {
        node *t=start;
        while(t->next!=start)
        {
            t=t->next;
        }
        t->next=n;
        n->prev=t;
        n->next=start;
        start->prev=n;
    }


    return start;
}

int delTime(node *start,int time,char **arr,int *val)
{
    int operationtime=rand()%100;
    cout<<"optime="<<operationtime<<endl;
    int i=0;
    int ttime=0;
    //the down while loop will run until there in only one process in linked list and its value should also be less than 0 to stop;
    while(operationtime>0 && (start->next!=start || start->time>0))
    {
        int ctime=0;
        start=insertion(start);
        if(start->time-time>0)
        {
            start->time=start->time-time;
            ctime=time;
            ttime+=time;
            char *p=start->c;
            arr[i]=p;
            val[i]=ttime;
            i++;
            /*char cn[2];//char node which stores node process number;
            			int nc=0; //char node node count used to copy  node process no;
            			while(start->c[nc]!='\0'){
            				cn[nc]=start->c[nc];
            				nc++;
            			}
            			cn[nc]='\0';
            			char *p=cn;
            			arr[i]=p;
            			i++;*/
            start=start->next;
        }
        else if(start->time-time<=0)
        {
            ttime+=start->time;
            ctime=start->time;
            start->time=start->time-time;
            node *t=start;
            start=start->next;
            t->prev->next=t->next;;
            start->prev=t->prev;
            char *p=t->c;
            arr[i]=p;
            val[i]=ttime;
            i++;
            /*char cn[2];//char node which stores node process number;
            int nc=0; //char node node count used to copy  node process no;
            while(t->c[nc]!='\0'){
            	cn[nc]=t->c[nc];
            	nc++;
            }
            cn[nc]='\0';
            char *p=cn;
            arr[i]=p;
            i++;*/
            //free(t);
        }
        operationtime-=ctime;

    }
    return i;
}


void display(node *start)
{
    node *t=start;
    do
    {
        cout<<t->c<<" "<<t->time<<" ";
        t=t->next;
    }
    while(t!=start);
    cout<<endl;
}

void printGang(char ** arr,int i,int *val)
{

    cout<<"----------------------"<<endl;
    cout<<"|  Process  |  Time  |"<<endl;
    cout<<"----------------------"<<endl;
    for(int j=0; j<i; j++)
    {
        cout<<"|    "<<arr[j]<<"    |   "<<setw(2) << std::setfill('0')<<val[j]<<"   |"<<endl;
    }
    cout<<"----------------------"<<endl;
}

int main()
{
    srand(time(0));
    node *start=NULL;
    start=insertion(start);
    int delt;
    cout<<"enter quantam time = ";
    cin>>delt;
    char **arr=(char **)malloc(100*sizeof(int*));
    int *val=(int *)malloc(100*sizeof(int));
    int i=delTime(start,delt,arr,val);
    //display(start);
    cout<<"i = "<<i<<endl;
    printGang(arr,i,val);

}
