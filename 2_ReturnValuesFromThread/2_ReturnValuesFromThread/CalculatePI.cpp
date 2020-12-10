#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>
#include <exception>

using namespace std;

// ref: Future and Promise (like producer and consumer)
//		--- https://zh.wikipedia.org/wiki/Future%E4%B8%8Epromise

double calculatePI(int terms) {
	double result = 0.0;

	if (terms < 1) {
		throw runtime_error("Terms cannot be less than one");
	}

	for (int i = 0; i < terms; i++) {
		int sign = pow(-1, i);
		double term = sign * (1.0  / (i * 2 + 1));
		result += term;
	}

	return result * 4;
}

void promiseAndFutures() {
	// receive output from thread
	promise<double> promise;

	// [&] catch all local variable
	auto doCalculation = [&](int terms) {
		try
		{
			auto result = calculatePI(terms);
			promise.set_value(result);
		}
		catch (...)
		{
			promise.set_exception(current_exception());
		}
	};

	// try catch exception
	//thread t1(doCalculation, 0);
	thread t1(doCalculation, 1e8);

	future<double> future = promise.get_future();

	try
	{
		cout << "Get from the future var: ";
		// get() return value or throw exception
		cout << setprecision(15) << future.get() << endl;
		cout << "abababababab" << endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << endl;
	}


	t1.join();
}

// packed the promise and future 
void packagedTasks() {
	// packaged_task ref: https://blog.csdn.net/fengbingchun/article/details/104127352
	packaged_task<double(int)> task1(calculatePI);

	future<double> f1 = task1.get_future();

	// create thread with argument
	thread t1(move(task1), 0);

	try
	{
		double result = f1.get();
		cout << setprecision(15) << result << endl;
	}
	catch (const std::exception& e)
	{
		cout << "ERROR! " << e.what() << endl;
	}

	t1.join();
}

int main() {
	//promiseAndFutures();
	packagedTasks();

	return 0;
}