#include "Queue.h"

#include <gtest.h>
#include <fstream>
#include <sstream>

using namespace std;

TEST(TQueueTest, DefaultConstructor) 
{
    TQueue<int> q;
    EXPECT_EQ(q.GetLen(), 0);
    EXPECT_EQ(q.GetStart(), 0);
    EXPECT_EQ(q.GetEnd(), 0);
    EXPECT_EQ(q.GetCount(), 0);
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueueTest, SizeConstructor) 
{
    TQueue<int> q(5);
    EXPECT_EQ(q.GetLen(), 5);
    EXPECT_EQ(q.GetCount(), 0);
    EXPECT_TRUE(q.IsEmpty());
    EXPECT_FALSE(q.IsFull());
}

TEST(TQueueTest, SizeConstructorNegative) 
{
    EXPECT_THROW(TQueue<int> q(-1), invalid_argument);
}

TEST(TQueueTest, CopyConstructor) 
{
    TQueue<int> q1(3);
    q1.Push(1);
    q1.Push(2);

    TQueue<int> q2(q1);
    EXPECT_EQ(q2.GetLen(), 3);
    EXPECT_EQ(q2.GetCount(), 2);
    EXPECT_EQ(q2.Pop(), 1);
    EXPECT_EQ(q2.Pop(), 2);
}

TEST(TQueueTest, MoveConstructor) 
{
    TQueue<int> q1(3);
    q1.Push(1);
    q1.Push(2);

    TQueue<int> q2(move(q1));
    EXPECT_EQ(q2.GetLen(), 3);
    EXPECT_EQ(q2.GetCount(), 2);
    EXPECT_EQ(q1.GetLen(), 0); 
}


TEST(TQueueTest, PushAndPop) 
{
    TQueue<int> q(4);

    q.Push(10);
    EXPECT_EQ(q.GetCount(), 1);
    EXPECT_FALSE(q.IsEmpty());

    q.Push(20);
    q.Push(30);
    EXPECT_EQ(q.GetCount(), 3);
    EXPECT_TRUE(q.IsFull());

    EXPECT_EQ(q.Pop(), 10);
    EXPECT_EQ(q.Pop(), 20);
    EXPECT_EQ(q.Pop(), 30);
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueueTest, PushFullQueue) 
{
    TQueue<int> q(2); 
    q.Push(1);

    EXPECT_THROW(q.Push(2), logic_error);
}

TEST(TQueueTest, PopEmptyQueue) 
{
    TQueue<int> q(3);

    EXPECT_THROW(q.Pop(), logic_error);
}

TEST(TQueueTest, CircularBehavior) 
{
    TQueue<int> q(4); 

    q.Push(1);
    q.Push(2);
    q.Push(3);
    EXPECT_TRUE(q.IsFull());

    EXPECT_EQ(q.Pop(), 1);
    EXPECT_EQ(q.Pop(), 2);

    q.Push(4);
    q.Push(5);

    EXPECT_EQ(q.Pop(), 3);
    EXPECT_EQ(q.Pop(), 4);
    EXPECT_EQ(q.Pop(), 5);
    EXPECT_TRUE(q.IsEmpty());
}


TEST(TQueueTest, CopyAssignment) 
{
    TQueue<int> q1(3);
    q1.Push(1);
    q1.Push(2);

    TQueue<int> q2;
    q2 = q1;

    EXPECT_EQ(q2.GetLen(), 3);
    EXPECT_EQ(q2.GetCount(), 2);
    EXPECT_EQ(q2.Pop(), 1);
    EXPECT_EQ(q2.Pop(), 2);
}

TEST(TQueueTest, MoveAssignment) 
{
    TQueue<int> q1(3);
    q1.Push(1);
    q1.Push(2);

    TQueue<int> q2;
    q2 = move(q1);

    EXPECT_EQ(q2.GetLen(), 3);
    EXPECT_EQ(q2.GetCount(), 2);
    EXPECT_EQ(q1.GetLen(), 0);
}

TEST(TQueueTest, SelfAssignment) 
{
    TQueue<int> q(3);
    q.Push(1);
    q.Push(2);

    q = q; 

    EXPECT_EQ(q.GetCount(), 2);
    EXPECT_EQ(q.Pop(), 1);
}

// Тесты операторов сравнения
TEST(TQueueTest, EqualityOperator) {
    TQueue<int> q1(3);
    q1.Push(1);
    q1.Push(2);

    TQueue<int> q2(3);
    q2.Push(1);
    q2.Push(2);

    EXPECT_TRUE(q1 == q2);
}

TEST(TQueueTest, InequalityOperator) {
    TQueue<int> q1(3);
    q1.Push(1);
    q1.Push(2);

    TQueue<int> q2(3);
    q2.Push(1);
    q2.Push(3); // Разный элемент

    EXPECT_TRUE(q1 != q2);
}

TEST(TQueueTest, EqualityDifferentSizes) {
    TQueue<int> q1(3);
    q1.Push(1);

    TQueue<int> q2(4);
    q2.Push(1);

    EXPECT_FALSE(q1 == q2);
}

// Тесты методов доступа
TEST(TQueueTest, GetCount) {
    TQueue<int> q(5);

    EXPECT_EQ(q.GetCount(), 0);

    q.Push(1);
    EXPECT_EQ(q.GetCount(), 1);

    q.Push(2);
    EXPECT_EQ(q.GetCount(), 2);

    q.Pop();
    EXPECT_EQ(q.GetCount(), 1);
}

TEST(TQueueTest, IsEmptyAndIsFull) 
{
    TQueue<int> q(2); // Может хранить 1 элемент

    EXPECT_TRUE(q.IsEmpty());
    EXPECT_FALSE(q.IsFull());

    q.Push(1);
    EXPECT_FALSE(q.IsEmpty());
    EXPECT_TRUE(q.IsFull());

    q.Pop();
    EXPECT_TRUE(q.IsEmpty());
    EXPECT_FALSE(q.IsFull());
}


TEST(TQueueTest, FindMin) {
    TQueue<int> q(6);
    q.Push(5);
    q.Push(2);
    q.Push(8);
    q.Push(1);
    q.Push(3);

    EXPECT_EQ(q.FindMin(), 1);
}

TEST(TQueueTest, FindMinSingleElement) {
    TQueue<int> q(3);
    q.Push(42);

    EXPECT_EQ(q.FindMin(), 42);
}

TEST(TQueueTest, FindMinEmptyQueue) {
    TQueue<int> q(3);

    EXPECT_THROW(q.FindMin(), logic_error);
}


TEST(TQueueTest, Resize) {
    TQueue<int> q(3);
    q.Push(1);
    q.Push(2);

    q.Resize(5);
    EXPECT_EQ(q.GetLen(), 5);
    EXPECT_EQ(q.GetCount(), 2);
    EXPECT_EQ(q.Pop(), 1);
    EXPECT_EQ(q.Pop(), 2);
}


TEST(TQueueTest, ResizeTooSmall)
{
    TQueue<int> q(3);
    q.Push(1);
    q.Push(2);

    EXPECT_THROW(q.Resize(1), logic_error); 
}


TEST(TQueueTest, OutputOperator) 
{
    TQueue<int> q(3);
    q.Push(1);
    q.Push(2);

    stringstream ss;
    ss << q;

    string result = ss.str();
    EXPECT_TRUE(result.find("TQueue") != string::npos);
    EXPECT_TRUE(result.find("count=2") != string::npos);
}


TEST(TQueueTest, SaveAndLoadToFile) {
    TQueue<int> q1(5);
    q1.Push(100);
    q1.Push(200);
    q1.Push(300);

    q1.SaveToFile("test_queue.txt");

    TQueue<int> q2;
    q2.LoadFromFile("test_queue.txt");

    EXPECT_EQ(q1.GetCount(), q2.GetCount());
    EXPECT_EQ(q1.Pop(), q2.Pop());
    EXPECT_EQ(q1.Pop(), q2.Pop());
    EXPECT_EQ(q1.Pop(), q2.Pop());
}

TEST(TQueueTest, LoadFromNonExistentFile) {
    TQueue<int> q;

    EXPECT_THROW(q.LoadFromFile("non_existent_file.txt"), runtime_error);
}

TEST(TQueueTest, SaveEmptyQueue) {
    TQueue<int> q(3);

    EXPECT_NO_THROW(q.SaveToFile("empty_queue.txt"));
}


TEST(TQueueTest, DoubleQueue) {
    TQueue<double> q(3);
    q.Push(1.5);
    q.Push(2.7);

    EXPECT_EQ(q.GetCount(), 2);
    EXPECT_DOUBLE_EQ(q.Pop(), 1.5);
    EXPECT_DOUBLE_EQ(q.FindMin(), 2.7);
}

TEST(TQueueTest, StringQueue) {
    TQueue<string> q(4);
    q.Push("apple");
    q.Push("banana");
    q.Push("cherry");

    EXPECT_EQ(q.GetCount(), 3);
    EXPECT_EQ(q.FindMin(), "apple"); 
}



TEST(TQueueTest, SingleElementQueue) 
{
    TQueue<int> q(2); 
    q.Push(42);

    EXPECT_EQ(q.GetCount(), 1);
    EXPECT_FALSE(q.IsEmpty());
    EXPECT_TRUE(q.IsFull());
    EXPECT_EQ(q.Pop(), 42);
    EXPECT_TRUE(q.IsEmpty());
}

TEST(TQueueTest, WrapAround) {
    TQueue<int> q(3); // Может хранить 2 элемента

    // Заполняем и опустошаем несколько раз для проверки циклического поведения
    for (int i = 0; i < 10; i++) {
        q.Push(i * 10);
        q.Push(i * 10 + 1);
        EXPECT_EQ(q.Pop(), i * 10);
        EXPECT_EQ(q.Pop(), i * 10 + 1);
        EXPECT_TRUE(q.IsEmpty());
    }
}
