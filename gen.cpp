#include <bits/stdc++.h>
using namespace std;

int rand(int a, int b) {// [a,b]
    return rand()%(b-a+1) + a;
}

int main(int argc, char** argv) {
    srand(atoi(argv[1]));
	int n = rand(2,10);
	int m = rand(5,min(2*n,15));
	cout << n << ' ';;
	vector<pair<int,int>> sortlins;
	set<int> sorts;
	for(int i = 0; i < m; i++) {
		sorts.insert(rand(0,n*n-1));
	}
	m = sorts.size();
	cout << m << endl;
	for(int i: sorts) {
		sortlins.push_back({i/n,i%n+n});
	}
	//for(int i = 0; i < m; i++) {
	//	sortlins[i].first = rand(0,n-1);
	//	sortlins[i].second = n+rand(0,n-1);
	//}
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
		cout << rand(1,10) << ' ';
	cout << endl;

}
