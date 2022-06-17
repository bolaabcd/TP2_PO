#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {// [a,b]
    return rand()%(b-a+1) + a;
}

int main(int argc, char** argv) {
    srand(atoi(argv[1]));
	int n = 215, m = rand(215,46225);
	cout << n << ' ' << m << endl;
	vector<pair<int,int>> sortlins(m);
	for(int i = 0; i < m; i++) {
		sortlins[i].first = rand(0,n-1);
		do {
			sortlins[i].second = rand(0,n-1);
		} while (sortlins[i].second == sortlins[i].first);
	}
	for (int i = 0; i < 2*n; i++) {
		for (int j = 0; j < m; j++) {
			if (i == sortlins[j].first or i == sortlins[j].second)
				cout << 1 << ' ';
			else
				cout << 0 << ' ';
		}
		cout << endl;
	}
	for (int i = 0; i < m; i++)
		cout << rand(0,10000) << ' ';
	cout << endl;

}
