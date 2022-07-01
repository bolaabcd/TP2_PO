#include <iostream>
#include <utility>
#include <vector>
#include <queue>
#include <set>
#include <cassert>

using namespace std;

int n, m;

vector<int> y,c; // vetor y dobrado e de custos dobrados
vector<vector<int>> edgs; // vertices incidentes a cada aresta
vector<vector<int>> edg_num; // a partir de i,j encontra o numero da aresta (i,j)

vector<vector<pair<int,int>>> h, g;

void make_h() {
	h.clear();
	h.resize(2*n);
	for(int i = 0; i < n; i++)
		for(auto pa : g[i])
			if(pa.second == y[pa.first] + y[i]){
				h[i].push_back(pa);
				h[pa.first].emplace_back(i,pa.second);
			}
}

vector<int> match, cert;
vector<pair<int,int>> paia;// pra quem e por qual aresta
vector<bool> marc;
vector<int> averts, bverts;
int bfs(int init) {
	queue<int> q;
	q.push(init);
	marc.clear();
	marc.resize(2*n,false);
	marc[init] = true;
	//averts.clear();
	//bverts.clear();
	while(!q.empty()) {
		int i = q.front();
		q.pop();
		
		if(i < n)
			averts.push_back(i);
		else
			bverts.push_back(i);
		int valid_nei = 0;

		for(auto [vis, val] : h[i]) {
			if(i < n) { // estamos saindo de A
				if(!marc[vis]) {
					q.push(vis);
					marc[vis] = true;
					valid_nei++;
					paia[vis] = {i,edg_num[i][vis]};
				}
			} else if(match[edg_num[vis][i]]) {
				if(!marc[vis]){
					q.push(vis);
					marc[vis] =  true;
					valid_nei++;
					paia[vis] = {i,edg_num[vis][i]};
				}
			}
		}
		if(valid_nei == 0 and i >= n)
			return i;
	}
	return -1;
}

int find_perf_matching() {
	match.clear();
	cert.clear();
	marc.clear();
	paia.clear();
	marc.resize(2*n,false);
	match.resize(m,false);
	cert.resize(m,false);
	averts.clear();
	bverts.clear();
	set<int> no_pair, no_other;
	for(int i = 0; i < n; i++) no_pair.insert(i);
	for(int i = n; i < 2*n; i++) no_other.insert(i);
	while(!no_pair.empty()) {
		bool passfor = false;
		for(int i: no_pair) {
			bool breaka = false;
			for(auto pa : h[i])
				if(no_other.count(pa.first)){
					passfor = true;
					no_pair.erase(i);
					no_other.erase(pa.first);
					match[edg_num[i][pa.first]] = true;
					breaka = true;
					break;
				}
			if (breaka)
				break;
		}
		if(!passfor)
			break;
	}
	while(!no_pair.empty()) {
		averts.clear();
		bverts.clear();
		int vert = *no_pair.begin();
		paia.resize(2*n,{-1,-1});
		int foia_ruim = bfs(vert);
		
		if (foia_ruim == -1) {
			//match = averts;
			//cert = bverts;
			match = vector<int>(n,0);
			cert = vector<int>(n,0);
			for(int i:averts)
				match[i] = 1;
			for(int i:bverts)
				cert[i-n] = 2;
			return -2;
		}

		while(foia_ruim != -1) {
			int pai = paia[foia_ruim].first;
			int edg = paia[foia_ruim].second;
			no_pair.erase(foia_ruim);
			no_other.erase(foia_ruim);

			if(pai == -1)
				break;
			match[edg] = !match[edg];

			foia_ruim = pai;
		}
	}
	cert = y;
	int sum = 0;
	for (int i = 0; i < m; i++)
		if(match[i])
			sum += c[i];
	return sum;
}

bool change(int val) {
	assert(averts.size() > bverts.size());
	for(int i: averts)
		y[i] += val;
	for(int i: bverts)
		y[i] -= val;
	for(int i = 0; i < m; i++)
		if (y[edgs[i][0]] + y[edgs[i][1]] > c[i])
			return false;
	return true;
}

int main() {
	cin >> n >> m;
	c.resize(m);
	edgs.resize(m);
	g.resize(2*n);
	h.resize(2*n);
	paia.resize(2*n);
	edg_num.resize(2*n,vector<int>(2*n,-1));
	for (int i = 0; i < 2*n; i++)
		for (int j = 0; j < m; j++) {
			int v;
			cin >> v;
			if(v == 1) edgs[j].push_back(i);
		}

	int mc = 0x7fffffff;
	for(int i = 0; i < m; i++){
		cin >> c[i];
		c[i] *= 2;
		mc = min(mc,c[i]);
	}
	y.resize(2*n,mc/2);

	for(int i = 0; i < m; i++){
		g[edgs[i][0]].emplace_back(edgs[i][1],c[i]);
		g[edgs[i][1]].emplace_back(edgs[i][0],c[i]);
		edg_num[edgs[i][0]][edgs[i][1]] = i;
	}
	while(1) {
		make_h();
		int val = find_perf_matching();
		int matsum = 0, certsum = 0;
		if(val == -2){
			marc.clear();
			marc.resize(2*n,false);
			for(int i = 0; i < n; i++){// conjunto s
				if(!match[i])
					continue;
				matsum += 1;
				for(auto pa:g[i])
					marc[pa.first] = true;
			}
			for(bool b: marc)certsum += b;
		}
		int amtmat = 0;
		if(val != -2)
			for(int ma:match) amtmat += ma != 0;
		if (amtmat == n || (val == -2 and matsum > certsum)) {
			cout << val/2.0 << endl;// retornar -2 se n tiver
			for(int i = 0; i < match.size(); i++) {
				cout << match[i]<< ' ';
			}
			cout << endl;
			for(int i: cert)
				cout << i/2.0 << ' ';// retornar 2*arestas da vizinhanca
			cout << endl;
			break;
		}
		int l = 0, r = 0x00100000;

		while(l != r) {
			int mid = (l + r + 1)/2;
			auto yc = y;
			if(change(mid)) //S e N(S)
				l = mid;
			else
				r = mid-1;
			y = yc;
		}
		assert(l > 0);
		change(l);
	}
	return 0;
}
