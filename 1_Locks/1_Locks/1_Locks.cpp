// 1_Locks.cpp : main function

#include <iostream>
#include <thread>
#include <chrono> // std puase
#include <mutex>

using namespace std;

class App {
private:
    int count = 0;
    mutex mtx;

public:
    void operator() () {
        const int ITERATIONS = 1e6;

        for (int i = 0; i < ITERATIONS; ++i) {
            //lock_guard<mutex> guard(mtx);    // lock mutex, unlock the mutex at the end of the loop (out of scope)
            unique_lock<mutex> guard(mtx);  // works the same, but with more functionalities
            count++;
        }
    }

    int getCount() { return count; }
};

void work_0(int &count, mutex &mtx) {
    const int ITERATIONS = 1e6;

    for (int i = 0; i < ITERATIONS; ++i) {
        mtx.lock();     // stop more than one thread at a time
        count++;
        mtx.unlock();   // unstop (unlock, without do the progeam will hang)
    }
}

void Section8_FunctionArguments() {
    int count = 0;
    mutex mtx;

    // std::ref --- return a reference wrapper
    thread t1(work_0, ref(count), ref(mtx));
    thread t2(work_0, ref(count), ref(mtx));

    t1.join();
    t2.join();

    cout << count << endl;
}

void work_1(int& count, mutex& mtx) {
    const int ITERATIONS = 1e6;

    for (int i = 0; i < ITERATIONS; ++i) {
        //lock_guard<mutex> guard(mtx);    // lock mutex, unlock the mutex at the end of the loop (out of scope)
        unique_lock<mutex> guard(mtx);  // works the same, but with more functionalities
        count++;
    }
}

// Section 9: Lock Guards
void Section9_LockGuard() {
    int count = 0;
    mutex mtx;

    // std::ref --- return a reference wrapper
    thread t1(work_1, ref(count), ref(mtx));
    thread t2(work_1, ref(count), ref(mtx));

    t1.join();
    t2.join();

    cout << count << endl;
}


// Section 10: Threads with Callable Objects
void Section10() {
    App app;

    thread t1(ref(app));
    thread t2(ref(app));

    t1.join();
    t2.join();

    cout << app.getCount() << endl;
}

int main()
{
    //Section8_FunctionArguments();
    //Section9_LockGuard();
    Section10();


    return 0;
}