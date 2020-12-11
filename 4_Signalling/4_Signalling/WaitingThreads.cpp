#include <iostream>
#include <thread>
#include <chrono>

using namespace std;

// Section 15: Waiting for threads
void Section15() {
	// thread_local each thread gets its own copy of variable
	//thread_local bool ready = false;
	//	BUT use atomic works as well
	atomic<bool> ready = false;

	thread t1([&]() {
		this_thread::sleep_for(chrono::milliseconds(2000));
		ready = true;
	});

	t1.join();

	while (!ready) {
		this_thread::sleep_for(chrono::milliseconds(100));
	}

	cout << "ready " << ready << endl;
}


int main() {
	Section15();
	return 0;
}

