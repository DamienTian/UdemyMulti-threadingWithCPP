// 0_Introduction.cpp : main function

#include <iostream>
#include <thread>
#include <chrono> // std puase

using namespace std;

void work() {
    for (int i = 0; i < 10; ++i) {
        // make this thread sleep for 500 milliseconds
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "Loop " << i << endl;
    }
}

int main()
{
    // thread: std::thread
    thread t1(work);
    thread t2(work);

    // .join(): Blocks the current thread until the thread identified by *this finishes its execution
    // NOTE:
    //      WITHOUT .join(), t1 will only runs on it own thread, and main func will quit at the end,
    //      so t1's resource was leaked (didn't be collected).
    //      WITH .join(), main() waits the t1 to finish and then terminates.
    t1.join();


    t2.join();

    return 0;
}