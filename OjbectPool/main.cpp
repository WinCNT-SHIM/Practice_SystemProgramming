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
    int seq;    // 추가된 순서
    int number; // 랜덤 번호
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

        // 최소값 비교
        if (number <= minNum)
        {
            minNum = number;
        }
        // forward_list의 원소 수가 10개가 넘어가면 맨 처음의 요소를 지운다
        if (listSize >= 10)
        {
            Dummy* freeDummy = nullptr;
            auto literEndBefore = m_list.begin();
            for (int i = 0; i < listSize - 2; i++)
            {
                // forward_list의 마지막의 바로 앞 요소를 획득
                literEndBefore = ++literEndBefore;
            }
            // forward_list의 마지막 요소를 획득
            auto literEnd = literEndBefore;
            literEnd++;
            freeDummy = *literEnd;
            // forward_list의 마지막 요소의 메모리를 반환한다
            sumNum -= freeDummy->number;
            m_arrayPool.Free(freeDummy);
            
            // forward_list의 마지막의 바로 앞 요소의 뒷부분(즉 마지막 요소)를 삭제
            m_list.erase_after(literEndBefore);
            listSize--;
        }
        sumNum += number;
        m_list.push_front(dummyPtr);
        listSize++;
    }
    void Print()
    {
        /*최근 10개의 숫자 평균과 최소값 출력 */
        printf("최근 10개의 숫자의 평균값: %f\n", (float)sumNum / (float)(listSize));
        printf("최근 10개의 숫자의 최소값: %d\n", minNum);
    }

private:
    std::forward_list<Dummy*> m_list;
    TOjbectArrayPool<Dummy> m_arrayPool;

    //필요한 멤버 추가
    int index = 0;
    int listSize = 0;
    int minNum = 99999; // 최소값의 초기값
    int sumNum = 0;
    int avgNum;
};

class MaxAndAvg
{
public:
    ~MaxAndAvg()
    {
        for (auto iter = m_list.begin(); iter != m_list.end(); iter++)
        {
            m_listPool.Free(*iter);
        }
    }
    void AddNumber(int number)
    {
        Dummy* dummyPtr = m_listPool.Alloc();
        dummyPtr->seq = index++;
        dummyPtr->number = number;
        
        // 최대값 비교
        if (number >= maxNum)
        {
            maxNum = number;
        }
        // forward_list의 원소 수가 10개가 넘어가면 맨 처음의 요소를 지운다
        if (listSize >= 10)
        {
            Dummy* freeDummy = nullptr;
            auto literEndBefore = m_list.begin();
            for (int i = 0; i < listSize - 2; i++)
            {
                // forward_list의 마지막의 바로 앞 요소를 획득
                literEndBefore = ++literEndBefore;
            }
            // forward_list의 마지막 요소를 획득
            auto literEnd = literEndBefore;
            literEnd++;
            freeDummy = *literEnd;
            // forward_list의 마지막 요소의 메모리를 반환한다
            sumNum -= freeDummy->number;
            m_listPool.Free(freeDummy);

            // forward_list의 마지막의 바로 앞 요소의 뒷부분(즉 마지막 요소)를 삭제
            m_list.erase_after(literEndBefore);
            listSize--;
        }
        sumNum += number;
        m_list.push_front(dummyPtr);
        listSize++;
    }
    void Print()
    {
        /*최근 10개의 숫자 평균과 최대값 출력 */
        printf("최근 10개의 숫자의 평균값: %f\n", (float)sumNum / (float)(listSize));
        printf("최근 10개의 숫자의 최대값: %d\n", maxNum);
    }

private:
    std::forward_list<Dummy*> m_list;
    TOjbectListPool<Dummy> m_listPool;

    //필요한 멤버 추가
    int index = 0;
    int listSize = 0;
    int maxNum = -99999; // 최소값의 초기값
    int sumNum = 0;
    int avgNum;
};

void main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    MinAndAvg minAvg;
    MaxAndAvg maxAvg;

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 10);

    int cnt = 0;
    bool bRun = true;
    while (bRun)
    {
        cnt++;
        //1. 매 2초마다 랜덤한 숫자 n을 생성
        //Sleep(2000);
        int n = dist(gen);
        printf("랜덤한 숫자: %d\n", n);
        //2. minAvg.AddNumber(n); minAvg.Print()
        printf("==========minAvg==========\n");
        minAvg.AddNumber(n);
        minAvg.Print();
        3. maxAvg.AddNumber(n); maxAvg.Print()
        printf("==========maxAvg==========\n");
        maxAvg.AddNumber(n);
        maxAvg.Print();
        printf("\n");

        // 100개 이상이면 중단
        if (cnt >= 100) bRun = false;
    }

    system("pause");
}