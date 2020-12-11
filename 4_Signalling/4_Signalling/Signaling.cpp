#include <iostream>
#include <thread>
#include <chrono>
#include <condition_variable>

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

// Condition Variables
void Section16() {
	condition_variable condition;
	mutex mtx;
	bool ready = false;

	thread t1([&]() {
		this_thread::sleep_for(chrono::milliseconds(2000));
		cout << "Unlocking the mutex ..." << endl;
		// get the unique lock
		unique_lock<mutex> lock(mtx);
		ready = true;
		this_thread::sleep_for(chrono::milliseconds(2000));
		lock.unlock();
		// weak up one thead
		condition.notify_one();
	});

	// connect two unique_lock together
	unique_lock<mutex> lock(mtx);

	while (!ready) {
		// In this program, this .wait releases the lock that assiciate with the mtx,
		//	so the lock inside the t1 can get the mtx, because the second lock has the 
		//	mtx first, because the time delay in t1. It has to be put into wait state 
		//	in order for the lock in t1 to get mtx
		// .Wait() won't return until some thread notifies it
		cout << "Locking the mutex ..." << endl;
		condition.wait(lock);
	}

	cout << "ready " << ready << endl;

	t1.join();
}

int main() {
	//Section15();
	Section16();
	return 0;
}
