#pragma once

/// <summary>
/// Object Pool�� �迭�� ����� Ŭ����
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T, int SIZE = 64>
class TOjbectArrayPool
{
public:
    using OBJCET_PTR = T*;

    TOjbectArrayPool()
    {
        // �Ҵ�� �ʱ�ȭ
        objectArray = new OBJCET_PTR[SIZE];

        for (int i = 0; i < SIZE; i++)
        {
            *(objectArray + i) = new T();
        }
    }
    ~TOjbectArrayPool()
    {
        // ����
        for (int i = 0; i < SIZE; i++)
        {
            delete *(objectArray + i);
        }
        delete[] objectArray;
    }

    // ������Ʈ Ǯ�� �ּ� �Ҵ��� ��û�޾��� ���
    OBJCET_PTR Alloc()
    {
        OBJCET_PTR temp = nullptr;
        // ������Ʈ Ǯ Ž��
        for (int i = 0; i < SIZE; i++)
        {
            // ������Ʈ Ǯ���� null�� �ƴ� �ε����� ã�Ƽ� return����
            // (OBJCET_PTR�� �ᱹ T*�̱� ������ �ּҸ� ������ ���� �ȴ�)
            if (*(objectArray + i) != nullptr)
            {
                temp = *(objectArray + i);
                // return�� ���� null�� �ٲ�
                *(objectArray + i) = nullptr;
                break;
            }
        }
        return temp;
    }
    // ������Ʈ Ǯ�� �ּҸ� �ݳ��� ���
    void Free(OBJCET_PTR pObj)
    {
        // ������Ʈ Ǯ Ž��
        for (int i = 0; i < SIZE; i++)
        {
            // ������Ʈ Ǯ���� null�� ���� ã�Ƽ� �־���
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
/// Object Pool�� ��ũ�� ����Ʈ�� ����� Ŭ����
/// </summary>
/// <typeparam name="T"></typeparam>
template <typename T, int SIZE = 64>
class TOjbectListPool
{
public:
    using OBJCET_PTR = T*;

    TOjbectListPool()
    {
        // �Ҵ�� �ʱ�ȭ
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
        // ����
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