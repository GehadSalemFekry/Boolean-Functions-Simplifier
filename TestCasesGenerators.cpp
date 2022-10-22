#include <bits/stdc++.h>
using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int rand(int a, int b) { 
    return a + rng() % (b - a + 1); 
}

int main() {

    freopen("testValid.in", "w", stdout);

    cout << 10 * 5 << "\n";
    for(int i = 2; i < 12; i++) {
        for (int j = 0; j < 5; j++) {
            cout << i << "\n";
            int tot_terms = rand(2, (1 << i) - 1);
            set<int> terms;
            while (terms.size() < tot_terms) {
                terms.insert(rand(1, (1 << i) - 1));
            }
            
            int min_terms = rand(1, terms.size() - 1);
            vector<int> termm(terms.begin(), terms.end());

            for (int t = 0; t < min_terms; t++) {
                cout << termm[t];
                if (t != min_terms - 1) cout << ",";
            } 
            cout << "\n";

            for (int t = min_terms; t < tot_terms; t++) {
                cout << termm[t];
                if (t != tot_terms - 1) cout << ",";
            }
            cout << "\n";
        }
    }

    return 0;   
}