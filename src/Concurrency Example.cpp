//============================================================================
// Name        : Concurrency Example.cpp
// Description : Simple concurrency example with two active threads,
//				with the first counting up to 20 and the second counting
//				down once the first is done.
//============================================================================

#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>

using namespace std;

// Atomic boolean flag acting as a switch between the two threads.
atomic<bool> count_flag{false};

void to_20() {
	// For each item up to twenty, print that item.
	for (int i = 0; i <= 20; i++) {
		cout << "Counting to 20: " << i << endl;
	}
	// Swap the flag to true so that the second thread can operate.
	count_flag.store(true);
}

void from_20() {
	/* Check that if the flag is now allowing this thread to proceed
	 * and if not, sleep and check again. */
	while (!count_flag.load()) {
		this_thread::sleep_for(chrono::milliseconds(100));
	}
	// For each item down from 20, print that item.
	for (int i = 20; i >= 0; i--) {
		cout << "Counting down from 20: " << i << endl;
	}
}

int main() {
	// Identify thread function and begin processing.
	thread thread1(to_20);
	thread thread2(from_20);
	thread1.join();
	thread2.join();
	return 0;
}
