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
int processcount=0;//counts total no of process created.
int finishcount=0;//counts total no of process finished.

struct node
{
    int time;
    char c[5];
    node *next;
    node *prev;
};


node *insertion(node *start)
{
    static int i=1;
    processcount++;
    node *n=new node;
    n->next=NULL;
    n->prev=NULL;

    n->time=rand()%20+1;
    n->c[0]='P';
    int rev=0,j=i;
    int fc=0;
    //below two loops are used to reverse the ll time so we can easily enter in char array;
    while(j)//1st loop
    {
        rev=rev*10+j%10;
        if(j%10==0)
            fc++;
        j=j/10;
    }
    if(rev<10 && fc==0)
    {
        rev=rev*10;
    }
    j=1;
    while(rev)//2nd loop
    {
        n->c[j]=(rev%10+'0');
        rev=rev/10;
        j++;
    }
    while(fc--)
    {
        n->c[j]='0';
        j++;
    }
    n->c[j]='\0';
    i++;
    // cout<<n->c<<" "<<n->time<<endl;
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
    while(operationtime<20)
    {
        operationtime=rand()%100;
    }
    cout<<"Total Scheduling Time="<<operationtime<<endl;
    int i=0;
    int ttime=0;
    //the down while loop will run until there in only one process in linked list and its value should also be less than 0 to stop;
    while(operationtime>0 && (start->next!=start || start->time>0))

    {
        int generation=rand()%10;
        if(generation<5)
        {
            start=insertion(start);//used to insert process at random time
        }
        int ctime=0;//ctime will store the time for which the process gets executed  and and subtract it from total operation time;
        if(start->time-time>0)//is process time is greater then quantam time
        {
            if(operationtime<time)//if oeration time < than quantime time, do not run exit the loop;;
            {
                ctime=operationtime;
            }
            else
            {
                start->time=start->time-time;
                ctime=time;
                ttime+=time;
                char *p=new char[10];
                p=start->c;
                arr[i]=p;
                val[i]=ttime;
                i++;

                start=start->next;
            }

        }
        else if(start->time-time<=0)//if process time is equal to or less than quantam time
        {

            if(operationtime<start->time)// if operation time is < than process time exit the loop
            {
                ctime=start->time;
            }
            else
            {
                ttime+=start->time;
                ctime=start->time;
                start->time=start->time-time;
                node *t=start;
                start=start->next;
                t->prev->next=t->next;;
                start->prev=t->prev;
                char *p=new char[10];
                p=t->c;
                arr[i]=p;
                val[i]=ttime;
                i++;
                finishcount++;
            }

        }
        operationtime-=ctime;

    }
    return i;
}

void printGang(char ** arr,int i,int *val)
{
    cout<<endl<<"Gang Chart Of Process Which Gets Executed"<<endl;
    cout<<"----------------------"<<endl;
    cout<<"|  Process  |  Time  |"<<endl;
    cout<<"----------------------"<<endl;
    for(int j=0; j<i; j++)
    {
        cout<<"|    "<<arr[j]<<"    |   ";
        cout<<setw(3) << std::setfill(' ')<<val[j]<<"  |"<<endl;
    }
    cout<<"----------------------"<<endl;
}

int main()
{
    srand(time(0));
    node *start=NULL;
    for(int i=0; i<3; i++)
        start=insertion(start);
    int delt=0;
    while(delt<5)
    {

        delt=rand()%10+1;
    }
    cout<<"Quantam Time = "<<delt<<endl;
    char **arr=(char **)malloc(100*sizeof(int*));
    int *val=(int *)malloc(100*sizeof(int));
    int i=delTime(start,delt,arr,val);
    cout<<"Total Process In The Queue = "<<processcount<<endl;
    printGang(arr,i,val);
    cout<<"Total Process Completed = "<<finishcount<<endl;

}
