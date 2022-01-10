#include <stdio.h>
#include <stdlib.h>

typedef struct QNode
{
    struct QNode* prev;
    struct QNode* next;
    unsigned pageNumber;
} QNode;

typedef struct Queue
{
    unsigned count;             // ť�� ���� ��� ��
    unsigned numberOfFrames;    // ť�� ���� �� �ִ� �ִ� ��� ��
    QNode* front;
    QNode* rear;
} Queue;

typedef struct Hash
{
    int capacity;
    QNode** arr;    // �ؽ� ���̺�(�迭)
} Hash;

/// <summary>
/// ���ο� ��带 �����ϴ� �Լ�
/// </summary>
/// <param name="pageNumber">������ �ѹ�</param>
/// <returns></returns>
QNode* NewQNode(unsigned pageNumber)
{
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    if (temp)
    {
        // ���ο� ��带 �ʱ�ȭ
        temp->pageNumber = pageNumber;
        temp->prev = temp->next = NULL;
    }
    return temp;
}

/// <summary>
/// ����ִ� ť�� �����ϴ� �Լ�
/// </summary>
/// <param name="numberOfFrames">ť�� �ִ� ��� ��</param>
/// <returns>������ ť</returns>
Queue* CreateQueue(int numberOfFrames)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue)
    {
        // ���� ���� ť�� �ʱ�ȭ
        queue->front = queue->rear = nullptr;
        queue->count = 0;
        queue->numberOfFrames = numberOfFrames;
    }
    return queue;
}

/// <summary>
/// ����ִ� �ؽ� ���̺��� �����ϴ� �Լ�
/// �ؽ� ���̺�: Key�������� �� ���� ��ȸ�� �� �ִ� �ڷᱸ��
/// </summary>
/// <param name="capacity">�ؽ� ���̺�(�迭)�� �뷮</param>
/// <returns>������ �ؽ�</returns>
Hash* CreateHash(int capacity)
{
    Hash* hash = (Hash*)malloc(sizeof(hash));
    if (hash)
    {
        // ���� ���� �ؽø� �ʱ�ȭ
        hash->capacity = capacity;
        // capacity��ŭ�� QNode*�� �����ϴ� �迭 ����
        hash->arr = (QNode**)malloc(sizeof(QNode*) * hash->capacity);
        for (int i = 0; i < hash->capacity; i++)
            hash->arr[i] = nullptr;
    }
    return hash;
}

/// <summary>
/// ť�� �� ������ �ִ��� Ȯ���ϴ� �Լ�
/// </summary>
/// <param name="queue">��� ť</param>
/// <returns>�� ������ ������ true, �� �ܴ� false</returns>
bool AreAllFramesFull(Queue* queue)
{
    return queue->count == queue->numberOfFrames;
}

/// <summary>
/// ť�� ����ִ��� Ȯ���ϴ� �Լ�
/// </summary>
/// <param name="queue">��� ť</param>
/// <returns></returns>
bool IsQueueEmpty(Queue* queue)
{
    return queue->rear == nullptr;
}

// ť�� �������� �����ϴ� �Լ�
void DeQueue(Queue* queue)
{
    // ť�� ����ִ� ���
    if (IsQueueEmpty(queue)) return;
    // ť�� ��尡 �ϳ��� �ִ� ���(rear�� �������� ó��)
    if (queue->front == queue->rear) queue->front = nullptr;
    
    // ť�� rear(���� ��)
    QNode* temp = queue->rear;
    // ť�� rear�� �� ��带 ť�� rear�� �缳��
    queue->rear = queue->rear->prev;

    // ���Ӱ� ������ rear�� null�� �ƴ� ���(��尡 1���� ���� null�� ��)
    if (queue->rear)
    {
        // ���Ӱ� ������ rear�� next�� null�� ����
        queue->rear->next = nullptr;
    }

    // rear(���� ��)�� �޸� ����
    free(temp);
    // ť�� ���� ��� ���� �ϳ� ����
    queue->count--;
}

/// <summary>
/// ������(������ �ѹ�)�� ť�� �ؽÿ� �߰��ϴ� �Լ�
/// </summary>
/// <param name="queue">�ش� ť</param>
/// <param name="hash">�ش� �ؽ�</param>
/// <param name="pageNumber">������ �ѹ�</param>
void EnQueue(Queue* queue, Hash* hash, unsigned pageNumber)
{
    // ť�� �� ������ ���� ���
    // ť�� rear�� �ش��ϴ� �����͸� ť�� �ؽÿ��� ������
    if (AreAllFramesFull(queue))
    {
        hash->arr[queue->rear->pageNumber] = nullptr;
        DeQueue(queue);
    }

    // ť�� front�� ���ο� ��带 ����
    QNode* temp = NewQNode(pageNumber);
    temp->next = queue->front;

    // ť�� ����־��ٸ� �߰��� ��带 ť�� front�� rear�� ����
    if (IsQueueEmpty(queue))
    {
        queue->rear = temp;
        queue->front = temp;
    }
    // �� ���� ���� ť�� front�� temp�� ����
    else
    {
        queue->front->prev = temp;
        queue->front = temp;
    }

    // ť�� ���� ��� ���� +1��
    queue->count++;

    // �ؽÿ� ������ �ѹ��� �߰���
    hash->arr[pageNumber] = temp;
}

/// <summary>
/// �޸𸮿� �ִ� ������ �������� �����ϴ� �Լ�
/// 1. Frame�� �޸𸮿� ������, �޸𸮿��� �������� ť�� front�� �߰�
/// 2. Frame�� �޸𸮿� ������, �ش� Frame�� ť�� front�� �ű�
/// </summary>
/// <param name="queue"></param>
/// <param name="hash"></param>
/// <param name="pageNumber"></param>
void ReferencePage(Queue* queue, Hash* hash, int pageNumber)
{
    QNode* reqPage = hash->arr[pageNumber];

    // ť�� �ش� �������� ������ �������� �߰���
    if (reqPage == nullptr)
    {
        EnQueue(queue, hash, pageNumber);
    }
    // ť�� �ش� �������� �ִµ� front�� �ƴ϶�� ť�� �������Ѵ�
    else if (reqPage != queue->front)
    {
        // A <=> reqPage <=> B ===> A <=> B�� ����
        reqPage->prev->next = reqPage->next;
        if (reqPage->next)
        {
            // reqPage�� ť�� rear�� �ƴ� ���
            reqPage->next->prev = reqPage->prev;
        }
        //// reqPage�� ť�� rear�� ���
        //// �ҽ� �ڵ尡 �˱� ��ư� �ǹǷ� ���� if������ �и�
        //else
        //{
        //    queue->rear = reqPage->prev;
        //    queue->rear->next = nullptr;
        //}
        
        // reqPage�� ť�� rear���ٸ� rear�� �缳���Ѵ�
        if (reqPage == queue->rear)
        {
            queue->rear = reqPage->prev;
            queue->rear->next = nullptr;
        }

        // reqPage�� ť�� front�� �����Ѵ�
        // null <=> reqPage <=> front(���� ��)
        reqPage->prev = nullptr;        // reqPage ����� prev�� null�� ����
        reqPage->next = queue->front;   // reqPage ����� next�� ť�� front(���� ��)���� ����
        reqPage->next->prev = reqPage;  // reqPage ���� ����� prev�� reqPage�� ����
        queue->front = reqPage;         // ť�� front�� reqPage�� ����
    }
    // reqPage�� front��� �ƹ��� ó���� ���� ����
    else
    {
        // ó�� ����
    }
}

int main()
{
    // ť�� ����: �ֱٿ� ������ ��带 �׻� ����Ʈ�� ����
    Queue* q = CreateQueue(4);
    Hash* hash = CreateHash(10);

    // Let us refer pages 1, 2, 3, 1, 4, 5
    ReferencePage(q, hash, 1);
    ReferencePage(q, hash, 2);
    ReferencePage(q, hash, 3);
    ReferencePage(q, hash, 1);
    ReferencePage(q, hash, 4);
    ReferencePage(q, hash, 5);

    // Let us print cache frames after the above referenced pages
    printf("%d ", q->front->pageNumber);
    printf("%d ", q->front->next->pageNumber);
    printf("%d ", q->front->next->next->pageNumber);
    printf("%d ", q->front->next->next->next->pageNumber);

    system("pause");
    return 0;
}