#include <iostream>
#include <vector>
#include <set>

void mergeV(std::vector< std::vector<long long> >& left, std::vector< std::vector<long long> >& right, std::vector< std::vector<long long> >& tbls){
	long long nL = left.size(), nR = right.size();
	long long i = 0, j = 0, k = 0;
	
	while (j < nL && k < nR) {
		
		if (left[j][0] == right[k][0]){
			if(left[j][1] < right[k][1]){
				tbls[i] = left[j];
				j++;
			} else {
				tbls[i] = right[k];
				k++;
			}
		} else
		if (left[j][0] < right[k][0]) {
			tbls[i] = left[j];
			j++;
		} else {
			tbls[i] = right[k];
			k++;
		}
		
			i++;
	}
	while (j < nL) {
		tbls[i] = left[j];
		j++; i++;
	}
	while (k < nR) {
		tbls[i] = right[k];
		k++; i++;
	}
}


void mergeSortV(std::vector< std::vector<long long> >& tbl){
	if (tbl.size() <= 1) return;
	
	long long mid = tbl.size()/2;
	std::vector< std::vector<long long> > left;
	std::vector< std::vector<long long> > right;
	
	for (long long j = 0; j < mid; j++)
	left.push_back(tbl[j]);
	
	for (long long j = 0; j < (tbl.size()-mid); j++)
	right.push_back(tbl[mid + j]);

	mergeSortV(left);
	mergeSortV(right);
	mergeV(left, right, tbl);
}




void minDystans(std::vector< std::vector<long long> > wspolrzedne, long long n)
{
	long long i;
	long long a, b;
	long long p1, p2;
	
	std::vector< std::vector<long long> > v;
	for (i = 0; i < n; i++) { v.push_back({ wspolrzedne[i][0], wspolrzedne[i][1], wspolrzedne[i][2] }); }


	mergeSortV(v);
	
	
	
	long long d = 2147483647;

	std::set< std::vector<long long> > st;
	
	st.insert({ v[0][0], v[0][1], v[0][2] });
	
	i = 1;
	while( i < n && !(st.lower_bound({ v[i][0]-d, v[i][1]-d }) == st.end()) ) {
		auto l = st.lower_bound( { v[i][0] - d, v[i][1] - d } );
		auto r = st.upper_bound( { v[i][0], v[i][1] + d } );
		for (auto p = l; p != r; p++) {
			std::vector<long long> val = *p;
			
			a = v[i][0] > val[0] ? (v[i][0] - val[0]) : (val[0] - v[i][0]);
			b = v[i][1] > val[1] ? (v[i][1] - val[1]) : (val[1] - v[i][1]);
			long long dyst = a + b;
			
			if (d > dyst) {
				d = dyst;
				
				if ( v[i][2] < val[2] ) { 
					p1 = v[i][2];
					p2 = val[2];
				} else {
					p1 = val[2];
					p2 = v[i][2];
				}
				
			}
		}
		st.insert({ v[i][0], v[i][1], v[i][2] });
		i++;
	}
	
	std::cout << p1 << ' ' << p2 << std::endl;
}

int main()
{

	long long t, k, n, x, y;
	std::vector<long long> plc;
	std::vector< std::vector<long long> > plcs;
	
	std::cin >> t;
	while(t--){
		plcs.clear();
		std::cin >> k;
		for(long long i = 1; i <= k; i++){
			std::cin >> x >> y;
			plcs.push_back({ x, y, i });
		}
		minDystans(plcs, k);
		
	}
	
	return 0;
}

