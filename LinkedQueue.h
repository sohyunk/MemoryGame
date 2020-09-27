#ifndef LINKED_QUEUE_H
#define LINKED_QUEUE_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tagNodeLQ
{
	int Data;
	struct tagNodeLQ* NextNode;
} NodeLQ;

typedef struct tagLinkedQueue
{
	NodeLQ* Front;
	NodeLQ* Rear;
	int Count;
} LinkedQueue;

void LQ_CreateQueue(LinkedQueue** Queue);
void LQ_DestroyQueue(LinkedQueue* Queue);

NodeLQ* LQ_CrateNode(int NewData);
void LQ_DestroyNode(NodeLQ* _Node);

void LQ_Enqueue(LinkedQueue* Queue, NodeLQ* NewNode);
NodeLQ* LQ_Dequeue(LinkedQueue* Queue);

int LQ_IsEmpty(LinkedQueue* Queue);

#endif