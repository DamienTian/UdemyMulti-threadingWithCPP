// 0_Introduction.cpp : main function

#include <iostream>
#include <thread>
#include <chrono> // std puase

using namespace std;

//void work() {
//    for (int i = 0; i < 10; ++i) {
//        // make this thread sleep for 500 milliseconds
//        this_thread::sleep_for(chrono::milliseconds(500));
//        cout << "Loop " << i << endl;
//    }
//}

int main()
{
    // thread: std::thread
    /*thread t1(work);
    thread t2(work);*/

    // *** Sec 6. Shared Data ***
    // thread with lambda function
    //  NOTE: with atomic, t1 and t2 can increment count without disrupting each other
    //atomic<int> count = 0;

    // *** Sec 7. Mutexes ***
    atomic<int> count = 0;

    // NOTE: with ITERATIONS becomes bigger (WITHOUT atomic), 
    //      the result will be less accurate, because t1 t2 disrupt each others
    const int ITERATIONS = 1e6;

    auto lambda = [&count, &ITERATIONS]() {
        for (int i = 0; i < ITERATIONS; ++i) {
            count++;
        }
    };

    thread t1(lambda);
    thread t2(lambda);

    // .join(): Blocks the current thread until the thread identified by *this finishes its execution
    // NOTE:
    //      WITHOUT .join(), t1 will only runs on it own thread, and main func will quit at the end,
    //      so t1's resource was leaked (didn't be collected).
    //      WITH .join(), main() waits the t1 to finish and then terminates.
    t1.join();
    t2.join();

    cout << count << endl;

    return 0;
}