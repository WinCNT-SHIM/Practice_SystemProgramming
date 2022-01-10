#include <stdio.h>
#include <Windows.h>
#include <forward_list>
#include <random>
#include "ExObjectPool.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define new new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#endif

struct Dummy
{
    int seq;    // �߰��� ����
    int number; // ���� ��ȣ
};

class MinAndAvg
{
public:
    ~MinAndAvg()
    {
        for (auto iter = m_list.begin(); iter != m_list.end(); iter++)
        {
            m_arrayPool.Free(*iter);
        }
    }
    void AddNumber(int number)
    {
        Dummy* dummyPtr =  m_arrayPool.Alloc();
        dummyPtr->seq = index++;
        //if (index > 9) index = 0;
        dummyPtr->number = number;

        // �ּҰ� ��
        if (number <= minNum)
        {
            minNum = number;
        }
        // forward_list�� ���� ���� 10���� �Ѿ�� �� ó���� ��Ҹ� �����
        if (listSize >= 10)
        {
            Dummy* freeDummy = nullptr;
            auto literEndBefore = m_list.begin();
            for (int i = 0; i < listSize - 2; i++)
            {
                literEndBefore = ++literEndBefore;
            }
            auto literEnd = literEndBefore;
            literEnd++;
            freeDummy = *(literEnd);
            
            sumNum -= freeDummy->number;
            m_arrayPool.Free(freeDummy);
            m_list.erase_after(literEndBefore);
            listSize--;
        }
        sumNum += number;
        m_list.push_front(dummyPtr);
        listSize++;
    }
    void Print()
    {
        /*�ֱ� 10���� ���� ��հ� �ּҰ� ��� */
        printf("�ֱ� 10���� ������ ��հ�: %f\n", (float)sumNum / (float)(listSize));
        printf("�ֱ� 10���� ������ �ּҰ�: %d\n", minNum);
    }

private:
    std::forward_list<Dummy*> m_list;
    TOjbectArrayPool<Dummy> m_arrayPool;

    //�ʿ��� ��� �߰�
    int index = 0;
    int listSize = 0;
    int minNum = 99999; // �ּҰ��� �ʱⰪ
    int sumNum = 0;
    int avgNum;
};

class MaxAndAvg
{
public:

    void AddNumber(int number) {}
    void Print() { /*�ֱ� 10���� ���� ��հ� �ִ밪 ��� */ }

private:
    std::forward_list<Dummy*> m_list;
    TOjbectListPool<Dummy> m_listPool;

    //�ʿ��� ��� �߰�
    /*
    * ���������� �������
    * m_list�� ���� new�� �������
    * ������ �̹� ������ new�� �ƴ϶� pool�� �ϴ� ��
    * 
    */
};

void main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    MinAndAvg minAvg;
    //MaxAndAvg maxAvg;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    int cnt = 0;
    bool bRun = true;
    while (bRun)
    {
        cnt++;
        //1. �� 2�ʸ��� ������ ���� n�� ����
        //Sleep(2000);
        int n = dist(gen);
        printf("������ ����: %d\n", n);
        //2. minAvg.AddNumber(n); minAvg.Print()
        minAvg.AddNumber(n);
        minAvg.Print();
        //3. maxAvg.AddNumber(n); maxAvg.Print()

        // 100�� �̻��̸� �ߴ�
        if (cnt >= 100) bRun = false;
    }

    system("pause");
}