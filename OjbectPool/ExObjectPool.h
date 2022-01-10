#pragma once

/// <summary>
/// Object Pool을 배열로 만드는 클래스
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T, int SIZE = 64>
class TOjbectArrayPool
{
public:
    using OBJCET_PTR = T*;

    TOjbectArrayPool()
    {
        // 할당과 초기화
        objectArray = new OBJCET_PTR[SIZE];

        for (int i = 0; i < SIZE; i++)
        {
            *(objectArray + i) = new T();
        }
    }
    ~TOjbectArrayPool()
    {
        // 해제
        for (int i = 0; i < SIZE; i++)
        {
            delete *(objectArray + i);
        }
        delete[] objectArray;
    }

    // 오브젝트 풀이 주소 할당을 요청받았을 경우
    OBJCET_PTR Alloc()
    {
        OBJCET_PTR temp = nullptr;
        // 오브젝트 풀 탐색
        for (int i = 0; i < SIZE; i++)
        {
            // 오브젝트 풀에서 null이 아닌 인덱스를 찾아서 return해줌
            // (OBJCET_PTR란 결국 T*이기 때문에 주소를 리턴한 것이 된다)
            if (*(objectArray + i) != nullptr)
            {
                temp = *(objectArray + i);
                // return한 곳은 null로 바꿈
                *(objectArray + i) = nullptr;
                break;
            }
        }
        return temp;
    }
    // 오브젝트 풀에 주소를 반납할 경우
    void Free(OBJCET_PTR pObj)
    {
        // 오브젝트 풀 탐색
        for (int i = 0; i < SIZE; i++)
        {
            // 오브젝트 풀에서 null인 곳을 찾아서 넣어줌
            if (*(objectArray + i) == nullptr)
            {
                *(objectArray + i) = pObj;
                break;
            }
        }
    }

private:
    OBJCET_PTR* objectArray;
};

/// <summary>
/// Object Pool을 링크드 리스트로 만드는 클래스
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T, int SIZE = 64>
class TOjbectListPool
{
public:
    using OBJCET_PTR = T*;

    TOjbectListPool()
    {
        // 할당과 초기화
        pHead, pTail = nullptr;
        for (int i = 0; i < SIZE; i++)
        {
            Node* temp = new Node();
            temp->obj = 0;
            temp->pNext = nullptr;

            if (pHead == nullptr)
            {
                pHead = temp;
                pTail = temp;
                continue;
            }

            temp->pNext = pHead;
            pHead = temp;
        }
    }

    ~TOjbectListPool()
    {
        // 해제
        Node* temp = pHead;
        for (int i = 0; i < SIZE; i++)
        {

        }
        delete pHead;
        delete pTail;
    }

    OBJCET_PTR Alloc() { return nullptr; }
    void Free(OBJCET_PTR pObj) {}

private:
    struct Node
    {
        T obj;
        Node* pNext;
    };

    Node* pHead;
    Node* pTail;

    //Node* GetTail()
    //{
    //    if (GetTail()->pNext == nullptr) temp;
    //    else return GetTail();
    //}
};