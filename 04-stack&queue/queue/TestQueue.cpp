#include "Queue.hpp"
#include <iostream>
using namespace std;

int main() {
    Queue<int> q;
    q.enqueue(3);
    q.enqueue(5);
    q.enqueue(8);
    q.dequeue();
    cout << q.front() << endl;
    cout << q.rear() << endl;
    system("pause");
    return 0;
}