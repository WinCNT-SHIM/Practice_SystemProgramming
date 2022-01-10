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
    unsigned count;             // 큐의 현재 노드 수
    unsigned numberOfFrames;    // 큐가 가질 수 있는 최대 노드 수
    QNode* front;
    QNode* rear;
} Queue;

typedef struct Hash
{
    int capacity;
    QNode** arr;    // 해시 테이블(배열)
} Hash;

/// <summary>
/// 새로운 노드를 생성하는 함수
/// </summary>
/// <param name="pageNumber">페이지 넘버</param>
/// <returns></returns>
QNode* NewQNode(unsigned pageNumber)
{
    QNode* temp = (QNode*)malloc(sizeof(QNode));
    if (temp)
    {
        // 새로운 노드를 초기화
        temp->pageNumber = pageNumber;
        temp->prev = temp->next = NULL;
    }
    return temp;
}

/// <summary>
/// 비어있는 큐를 생성하는 함수
/// </summary>
/// <param name="numberOfFrames">큐의 최대 노드 수</param>
/// <returns>생성한 큐</returns>
Queue* CreateQueue(int numberOfFrames)
{
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    if (queue)
    {
        // 새로 만든 큐를 초기화
        queue->front = queue->rear = nullptr;
        queue->count = 0;
        queue->numberOfFrames = numberOfFrames;
    }
    return queue;
}

/// <summary>
/// 비어있는 해시 테이블을 생성하는 함수
/// 해시 테이블: Key값만으로 한 번에 조회할 수 있는 자료구조
/// </summary>
/// <param name="capacity">해시 테이블(배열)의 용량</param>
/// <returns>생성한 해시</returns>
Hash* CreateHash(int capacity)
{
    Hash* hash = (Hash*)malloc(sizeof(hash));
    if (hash)
    {
        // 새로 만든 해시를 초기화
        hash->capacity = capacity;
        // capacity만큼의 QNode*를 보관하는 배열 생성
        hash->arr = (QNode**)malloc(sizeof(QNode*) * hash->capacity);
        for (int i = 0; i < hash->capacity; i++)
            hash->arr[i] = nullptr;
    }
    return hash;
}

/// <summary>
/// 큐에 빈 공간이 있는지 확인하는 함수
/// </summary>
/// <param name="queue">대상 큐</param>
/// <returns>빈 공간이 없으면 true, 그 외는 false</returns>
bool AreAllFramesFull(Queue* queue)
{
    return queue->count == queue->numberOfFrames;
}

/// <summary>
/// 큐가 비어있는지 확인하는 함수
/// </summary>
/// <param name="queue">대상 큐</param>
/// <returns></returns>
bool IsQueueEmpty(Queue* queue)
{
    return queue->rear == nullptr;
}

// 큐의 프레임을 제거하는 함수
void DeQueue(Queue* queue)
{
    // 큐가 비어있는 경우
    if (IsQueueEmpty(queue)) return;
    // 큐에 노드가 하나만 있는 경우(rear는 공통으로 처리)
    if (queue->front == queue->rear) queue->front = nullptr;
    
    // 큐의 rear(였던 것)
    QNode* temp = queue->rear;
    // 큐의 rear의 앞 노드를 큐의 rear로 재설정
    queue->rear = queue->rear->prev;

    // 새롭게 설정된 rear가 null이 아닌 경우(노드가 1개인 경우는 null이 됨)
    if (queue->rear)
    {
        // 새롭게 설정된 rear의 next를 null로 설정
        queue->rear->next = nullptr;
    }

    // rear(였던 것)의 메모리 해제
    free(temp);
    // 큐의 현재 노드 수를 하나 감소
    queue->count--;
}

/// <summary>
/// 페이지(페이지 넘버)를 큐와 해시에 추가하는 함수
/// </summary>
/// <param name="queue">해당 큐</param>
/// <param name="hash">해당 해시</param>
/// <param name="pageNumber">페이지 넘버</param>
void EnQueue(Queue* queue, Hash* hash, unsigned pageNumber)
{
    // 큐에 빈 공간이 없는 경우
    // 큐의 rear에 해당하는 데이터를 큐와 해시에서 제거함
    if (AreAllFramesFull(queue))
    {
        hash->arr[queue->rear->pageNumber] = nullptr;
        DeQueue(queue);
    }

    // 큐의 front에 새로운 노드를 설정
    QNode* temp = NewQNode(pageNumber);
    temp->next = queue->front;

    // 큐가 비어있었다면 추가한 노드를 큐의 front와 rear로 설정
    if (IsQueueEmpty(queue))
    {
        queue->rear = temp;
        queue->front = temp;
    }
    // 그 외의 경우는 큐의 front를 temp로 설정
    else
    {
        queue->front->prev = temp;
        queue->front = temp;
    }

    // 큐의 현재 노드 수를 +1함
    queue->count++;

    // 해시에 페이지 넘버를 추가함
    hash->arr[pageNumber] = temp;
}

/// <summary>
/// 메모리에 있는 페이지 프레임을 참조하는 함수
/// 1. Frame이 메모리에 없으면, 메모리에서 가져오고 큐의 front에 추가
/// 2. Frame이 메모리에 있으면, 해당 Frame을 큐의 front로 옮김
/// </summary>
/// <param name="queue"></param>
/// <param name="hash"></param>
/// <param name="pageNumber"></param>
void ReferencePage(Queue* queue, Hash* hash, int pageNumber)
{
    QNode* reqPage = hash->arr[pageNumber];

    // 큐에 해당 페이지가 없으면 페이지를 추가함
    if (reqPage == nullptr)
    {
        EnQueue(queue, hash, pageNumber);
    }
    // 큐에 해당 페이지가 있는데 front가 아니라면 큐를 재정렬한다
    else if (reqPage != queue->front)
    {
        // A <=> reqPage <=> B ===> A <=> B로 변경
        reqPage->prev->next = reqPage->next;
        if (reqPage->next)
        {
            // reqPage가 큐의 rear이 아닐 경우
            reqPage->next->prev = reqPage->prev;
        }
        //// reqPage가 큐의 rear일 경우
        //// 소스 코드가 알기 어렵게 되므로 따로 if문으로 분리
        //else
        //{
        //    queue->rear = reqPage->prev;
        //    queue->rear->next = nullptr;
        //}
        
        // reqPage가 큐의 rear였다면 rear를 재설정한다
        if (reqPage == queue->rear)
        {
            queue->rear = reqPage->prev;
            queue->rear->next = nullptr;
        }

        // reqPage를 큐의 front로 설정한다
        // null <=> reqPage <=> front(였던 것)
        reqPage->prev = nullptr;        // reqPage 노드의 prev를 null로 설정
        reqPage->next = queue->front;   // reqPage 노드의 next를 큐의 front(였던 것)으로 설정
        reqPage->next->prev = reqPage;  // reqPage 다음 노드의 prev를 reqPage로 설정
        queue->front = reqPage;         // 큐의 front를 reqPage로 설정
    }
    // reqPage가 front라면 아무런 처리도 하지 않음
    else
    {
        // 처리 없음
    }
}

int main()
{
    // 큐의 역할: 최근에 참조한 노드를 항상 프론트로 유지
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