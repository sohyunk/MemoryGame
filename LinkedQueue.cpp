#include "LinkedQueue.h"

#pragma warning (disable:4996)

void LQ_CreateQueue(LinkedQueue** Queue)
{
	(*Queue) = (LinkedQueue*)malloc(sizeof(LinkedQueue));
	(*Queue)->Front = NULL;
	(*Queue)->Rear = NULL;
	(*Queue)->Count = 0;
}

void LQ_DestroyQueue(LinkedQueue* Queue)
{
	while (!LQ_IsEmpty(Queue))
	{
		NodeLQ* Popped = LQ_Dequeue(Queue);
		LQ_DestroyNode(Popped);
	}

	free(Queue);
}

NodeLQ* LQ_CrateNode(int NewData)
{
	NodeLQ* NewNode = (NodeLQ*)malloc(sizeof(NodeLQ));
	NewNode->Data = NewData;
	NewNode->NextNode = NULL;

	return NewNode;
}

void LQ_DestroyNode(NodeLQ* _Node)
{
	free(_Node);
}

void LQ_Enqueue(LinkedQueue* Queue, NodeLQ* NewNode)
{
	if (Queue->Front == NULL)
	{
		Queue->Front = NewNode;
		Queue->Rear = NewNode;
		Queue->Count++;
	}
	else
	{
		Queue->Rear->NextNode = NewNode;
		Queue->Rear = NewNode;
		Queue->Count++;
	}
}

NodeLQ* LQ_Dequeue(LinkedQueue* Queue)
{
	NodeLQ* Front = Queue->Front;

	if (Queue->Front->NextNode == NULL)
	{
		Queue->Front = NULL;
		Queue->Rear = NULL;
	}
	else
	{
		Queue->Front = Queue->Front->NextNode;
	}

	Queue->Count--;

	return Front;
}

int LQ_IsEmpty(LinkedQueue* Queue)
{
	return (Queue->Front == NULL);
}