#include <gtest/gtest.h>
#include "priorityqueue.h"
#include <iostream>
#include <stdlib.h>

bool testSize()
{
    priorityqueue<int> pq;
    for (int i = 1; i < 10; i++)
    {
        pq.enqueue(i, rand() % 10);
        if (pq.Size() != i)
        {
            cout << "testSize error: size should be " << i << endl;
            return false;
        }
    }
    cout << "testSize: all passed!" << endl;
    return true;
}

bool constructorTest()
{
    priorityqueue<int> pq;
    if (pq.Size() != 0)
    {
        cout << "constructorTest error: size should be 0" << endl;
        return false;
    }
    if (pq.getRoot() != NULL)
    {
        cout << "constructorTest error: root should be null" << endl;
        return false;
    }
    cout << "constructorTest: all passed!" << endl;
    return true;
}

bool assignmentOperatorTest()
{
    priorityqueue<int> pq;
    priorityqueue<int> pq2;
    pq = pq2;
    if (pq.Size() != pq2.Size())
    {
        cout << "assignmentOperatorTest: initial sizes not equal" << endl;
        return false;
    }
    for (int i = 1; i <= 10; i++)
    {
        pq.enqueue(i, rand() % 10);
        pq = pq2;
    }
    pq = pq2;
    if (pq.Size() != pq2.Size())
    {
        cout << "assignmentOperatorTest: sizes not equal after enqueue" << endl;
        return false;
    }
    cout << "assignmentOperatorTest: all passed!" << endl;
    return true;
}

bool testClear()
{
    priorityqueue<int> pq;
    for (int i = 1; i < 10; i++)
    {
        pq.enqueue(i, rand() % 10);
    }
    pq.clear();
    if (pq.Size() != 0)
    {
        cout << "testClear: size is not 0" << endl;
        return false;
    }
    if (pq.getRoot() != NULL)
    {
        cout << "testClear: root is not null" << endl;
        return false;
    }
    cout << "testClear: all passed!" << endl;
    return true;
}

bool testDequeue()
{
    priorityqueue<int> pq;
    for (int i = 1; i < 10; i++)
    {
        pq.enqueue(i, rand() % 10);
    }
    for (int i = 0; i < 10; i++)
    {
        pq.dequeue();
    }
    if (pq.Size() != -1)
    {
        cout << "testDequeue failed" << endl;
        return false;
    }
    cout << "testDequeue: all passed!" << endl;
    return true;
}

bool testToString()
{
    map<int, int> map;
    priorityqueue<int> pq;
    for (int i = 1; i < 10; i++)
    {
        pq.enqueue(i, rand() % 10);
    }
    stringstream ss;
    for (auto e : map)
    {
        int priority = e.first;
        int values = e.second;
        for (size_t j = 0; j < map.size(); j++)
        {
            ss << priority << " value: " << values << endl;
        }
    }
    if (pq.toString() != ss.str())
    {
        cout << "toString failure" << endl;
        return false;
    }
    cout << "toString passed!" << endl;
    return true;
}

bool testNext()
{
    map<int, int> map;
    priorityqueue<int> pq;
    for (int i = 1; i < 10; i++)
    {
        int random = rand() % 10;
        pq.enqueue(i, random);
        map[i] = random;
    }
    pq.begin();
    int value;
    int priority;
    stringstream ss;
    while (pq.next(value, priority))
    {
        ss << priority << " value: " << value << endl;
    }
    ss << priority << " value: " << value << endl;
    if (pq.toString() != ss.str())
    {
        cout << "testNext failed" << endl;
        return false;
    }
    cout << "testNext passed" << endl;
    return true;
}

bool testPeek()
{
    priorityqueue<string> pq;
    int n = 8;
    string vals[] = {"Dolores", "Bernard", "Arnold", "Ford", "Jasmine", "Carlos", "william", "teddy"};
    int prs[] = {5, 4, 8, 2, 6, 11, 8, 8};
    for (int i = 0; i < n; i++)
    {
        pq.enqueue(vals[i], prs[i]);
    }
    if (pq.peek() != vals[0])
    {
        cout << "testPeek failed" << endl;
        return false;
    }
    cout << "testPeek passed!" << endl;
    return true;
}

bool testEqualityOperator()
{
    map<int, int> map;
    priorityqueue<int> pq;
    priorityqueue<int> pq2;
    for (int i = 1; i < 10; i++)
    {
        pq.enqueue(i, rand() % 10);
    }
    pq = pq2;
    if (pq == pq2)
    {
        cout << "testEqualityOperator passed!" << endl;
        return true;
    }
    return false;
}

int main()
{
    testSize();
    constructorTest();
    assignmentOperatorTest();
    testClear();
    testDequeue();
    testToString();
    testNext();
    testPeek();
    testEqualityOperator();
}