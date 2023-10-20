#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

void exporter_csv(string const& filename) {

    vector<int> n_values = { 2, 4, 6, 8, 11, 15, 20 };
    vector<vector<double>> mesures = {
            { 4., 15.3, 35.2, 65.3, 120., 220.22, 399.9 },
            {7.5, 63.3, 217.99, 520.2, 1300.4, 3380., 8080.8}
    };

    ofstream out(filename);

    if(not out.is_open()) {
        cerr << "Pas pu ouvrir le fichier en écriture" << endl;
        return;
    }

    out << "n";
    for(int n : n_values) out << "," << n;
    out << endl;

    for(size_t i : { 0u, 1u }) {
        out << "mesure " << i;
        for (double d : mesures[i])
            out << "," << d;
        out << endl;
    }

}

unsigned long long fonction_a_tester(unsigned i) {
    if (i <= 1) return 1;
    return fonction_a_tester(i-1) + fonction_a_tester( i - 2);
}

template<typename Fn>
void mesure_temps(Fn f) {
    for (unsigned i = 10; i < 40; ++i) {
        auto t1 = std::chrono::high_resolution_clock::now();
        auto r = f(i);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> time_ms = t2 - t1;
        cout << "f(" << i << ") = " << r
             << " en " << time_ms.count() << " ms "
             << endl;
    }
}

class SumCounter {
    int i;
    inline static unsigned cnt = 0;
public:
    explicit SumCounter(int i) : i(i) {}
    friend SumCounter operator+(SumCounter const& lhs, SumCounter const& rhs) {
        ++SumCounter::cnt;
        return SumCounter(lhs.i+rhs.i);
    }
    static unsigned getSumCount() { return cnt; }
};

void mesure_ops() {
    SumCounter s(1);
    for(int i = 1; i < 1000; i*= 2 )
        s = s + SumCounter(i);
    cout << SumCounter::getSumCount() << " addition de SumCounter effectuées." << endl;
}

int main() {
    exporter_csv("../../rapport/csv/example.csv");
    mesure_temps(fonction_a_tester);
    mesure_ops();
}