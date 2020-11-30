// 1_Locks.cpp : main function

#include <iostream>
#include <thread>
#include <chrono> // std puase
#include <mutex>

using namespace std;

int main()
{
    // *** Sec 7. Mutexes ***
    int count = 0;  // shared data
    const int ITERATIONS = 1e6;
    mutex mtx;

    auto lambda = [&]() {
        for (int i = 0; i < ITERATIONS; ++i) {
            mtx.lock();     // stop more than one thread at a time
            count++;
            mtx.unlock();   // unstop (unlock, without do the progeam will hang)
        }
    };

    thread t1(lambda);
    thread t2(lambda);

    t1.join();
    t2.join();

    cout << count << endl;

    return 0;
}