#include <iostream>
#include "Queue.h"

using namespace std;

int main() 
{
    cout << "=== Simple TQueue Demo ===" << endl;
    
  
    TQueue<int> q(4);
    
    
    cout << "Pushing 10, 20, 30..." << endl;
    q.Push(10);
    q.Push(20);
    q.Push(30);
    
    
    while (!q.IsEmpty()) 
    {
        cout << "Pop: " << q.Pop() << endl;
    }
    
    cout << "=== Demo completed ===" << endl;
    return 0;
}
