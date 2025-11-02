#include <iostream>
#include <sstream>
#include <string>
#include "Queue.h"


using namespace std;

int main()
{
    cout << "=== Simple TQueue Test ===" << endl;

    // Создаем очередь емкостью 5
    TQueue<int> q(5);

    // Добавляем элементы
    cout << "Pushing elements: 10, 20, 30, 40" << endl;
    q.Push(10);
    q.Push(20);
    q.Push(30);
    q.Push(40);

    cout << "Current queue: " << q << endl;
    cout << "Count: " << q.GetCount() << "/" << q.GetLen() << endl;
    cout << "Start: " << q.GetStart() << ", End: " << q.GetEnd() << endl;
    cout << "Is full: " << q.IsFull() << endl;

    // Извлекаем элементы
    cout << "\nPopping elements:" << endl;
    cout << "Pop: " << q.Pop() << endl;
    cout << "Pop: " << q.Pop() << endl;
    cout << "After pops: " << q << endl;

    // Поиск минимума
    cout << "Min element: " << q.FindMin() << endl;

    // Тест копирования
    TQueue<int> qCopy(q);
    cout << "\nCopied queue: " << qCopy << endl;

    // Тест файловых операций
    cout << "\nTesting file operations..." << endl;
    q.SaveToFile("test_queue.txt");

    TQueue<int> loadedQ;
    loadedQ.LoadFromFile("test_queue.txt");
    cout << "Loaded from file: " << loadedQ << endl;

    cout << "\n=== Test finished ===" << endl;

    return 0;
}