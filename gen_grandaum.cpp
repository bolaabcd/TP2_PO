#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {// [a,b]
    return rand()%(b-a+1) + a;
}

int main(int argc, char** argv) {
    srand(atoi(argv[1]));
	int n = 215
	int m = rand(215,min(46225,n*n));
	cout << n << ' ' << m << endl;
	vector<pair<int,int>> sortlins(m);
	for(int i = 0; i < m; i++) {
		sortlins[i].first = rand(0,n-1);
		sortlins[i].second = n+rand(0,n-1);
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
