#include <iostream>
#include <cmath>
#include <iomanip>
#include <thread>
#include <future>

using namespace std;

// ref: Future and Promise (like producer and consumer)
//		--- https://zh.wikipedia.org/wiki/Future%E4%B8%8Epromise

double calculatePI(int terms) {
	double result = 0.0;
	for (int i = 0; i < terms; i++) {
		int sign = pow(-1, i);
		double term = sign * (1.0  / (i * 2 + 1));
		result += term;
	}

	return result * 4;
}

int main() {
	// receive output from thread
	promise<double> promise;

	// [&] catch all local variable
	auto doCalculation = [&](int terms) {
		auto result = calculatePI(terms);
		promise.set_value(result);
	};

	thread t1(doCalculation, 1e8);

	future<double> future = promise.get_future();
	cout << "Get from the future var: ";
	cout << setprecision(15) << future.get() << endl;
	cout << "abababababab" << endl;
	t1.join();

	return 0;
}