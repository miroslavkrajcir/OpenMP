#include <iostream>
#include <thread>
#include <vector>
#include <stdio.h>

#include <omp.h>

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

int main() {
	vector<Instrument*> instruments;

	// generate instruments
	for (unsigned int i = 0; i < 1024; ++i) {
		instruments.push_back(new Instrument(i));
	}

	// do magic
	omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel default(none)
	{
		printf("omp_get_thread_num() = %d\n", omp_get_thread_num());
	}

	// do magic
	omp_set_num_threads(omp_get_num_procs());
#pragma omp parallel for
	for (int i = 0; i < 1024; ++i) {
		printf("omp_get_thread_num() = %d\n", omp_get_thread_num());
		instruments[i]->generateData();
	}
}