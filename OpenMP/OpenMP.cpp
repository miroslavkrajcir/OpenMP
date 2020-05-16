#include <iostream>
#include <thread>
#include <vector>
#include <omp.h>
#include <stdio.h>

using namespace std;

class Instrument {
public:
	unsigned int id;
	vector<unsigned int> m_date;
	vector<float> m_open;
	vector<float> m_high;
	vector<float> m_low;
	vector<float> m_close;

	Instrument(unsigned int id) {
		this->id = id;
	}

	void generateData() {
		float f = 0;
		for (unsigned int i = 0; i < 280 * 30; ++i) {
			m_date.push_back(i);
			m_open.push_back(f);
			m_high.push_back(f);
			m_low.push_back(f);
			m_close.push_back(f);
			f++;
		}
	}
};

vector<Instrument*> instruments;

void do_work(int me, int total) {
	// printf("%d %d\n", me, total);

	int first = 1024 * me / total;
	int last = 1024 * (me + 1) / total - 1;

	for (int i = first; i <= last; i++) {
		// printf("i = %d\n", i);
		instruments[i]->generateData();
	}
}

int main() {
	for (unsigned int i = 0; i < 1024; ++i) {
		instruments.push_back(new Instrument(i));
	}

	omp_set_num_threads(omp_get_num_procs());
	int me;
	int total = omp_get_num_threads();

#pragma omp parallel default(none), private(me), shared(total) {
	total = omp_get_num_threads();
	me = omp_get_thread_num();
	do_work(me, total); }

	cout << "koniec" << endl;
}


/*
#ifndef _OPENMP
	// cout << "OpenMP IS NOT supported – sorry!" << endl;
	// exit(0);
#endif

#ifdef _OPENMP
	// cout << "OpenMP IS supported" << endl;
	// exit(0);
#endif
*/