#define k 5

#include<stdio.h>
#include<stdlib.h>
//简单循环队列的定义
typedef struct{
    int * base;
    int  font,rear;
    int length;
}Queue;

void QueueInit(Queue &q){
    q.base = (int *)malloc(sizeof(int)*k);
    q.font = q.rear = 0;
    q.length = 0;
}

bool EnQueue(Queue &q,int e){
    if(q.font == (q.rear+1)%k) return false;
    else{
        q.base[q.rear] = e;
        if(q.rear == k - 1)
            q.rear = 0;
        else
            q.rear++;
        q.length++;
    }
    return true;
}

int DeQueue(Queue &q){
    if(q.font == q.rear) return -1;

    else{
        int e = q.base[q.font];
        q.length --;
        if(q.font == k-1)
            q.font = 0;
        else
            q.font++;
        return e;
    }
}

bool DestroyQueue(Queue &q){
    free(q.base);
    q.base = NULL;
    q.font = 0;
    q.rear = 0;
    q.length = 0;
    return true;
}

//k阶斐波那契数列的函数
#define max 10000

void finibocci_queue(int n,int kk){
    //kk为k阶斐波那契数列，比队列的k少一
    int i = 0;
    Queue q;
    int sum = 0;//存储队列的总和
    int pop;

    QueueInit(q);

    for(;i<kk;i++){
        if(i<=kk-2)
            EnQueue(q,0);
        else{

            EnQueue(q,1);
            sum = 1;
        }
    }//队列0～k-1位的赋值

    while(i<=n){
        //通过队列特性，将第m-k位从队列移除，将m位插入队列，实现队列在k阶斐波那契数列的动态平移
        if(i == kk){
            DeQueue(q);
            EnQueue(q,sum);
            sum +=1;
        }

        else{
            pop = DeQueue(q);
            if(sum>max){
                break;
            }
            EnQueue(q,sum);
            sum *= 2;
            sum -= pop;
        }
        i++;
    }
    while(q.font != q.rear){
        pop = DeQueue(q);
    }

    printf("N : %d",i-1);
    printf("K : %d", pop);

    DestroyQueue(q);

}



int main(){
    finibocci_queue(22,k-1);
    return 0;
}



