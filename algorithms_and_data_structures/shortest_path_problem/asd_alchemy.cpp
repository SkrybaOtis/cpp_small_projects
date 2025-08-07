#include <iostream>
#include <vector>



int main() {
	int T, N, M; // 1 <= n <= 5 000; 1 <= m <= 100 000; no 0
	long long pk, minCost; // 1 <= pk <= 1 000 000 000;  
	int eStart, eEnd, eWeight; // 1 <= weight <= 10 000; no 0
	
	
	std::vector< std::vector<int> > antecedents;
	
	std::vector<long long> vertex; //vertex[1] - złoto
	std::vector< std::vector<long long> > verticies;
	
	std::cin >> T;
	for(int t=0; t<T; t++){
		
		std::cin >> N; vertex.clear(); vertex.push_back(N);
		for(int n=0; n<N; n++){ std::cin >> pk; vertex.push_back(pk/2); } //vertex[1] - złoto
		
		antecedents.clear();
		antecedents = std::vector< std::vector<int> >(N+1, std::vector<int>(N+1, N+2));
		
		
		verticies.clear();
		verticies = std::vector< std::vector<long long> >(N+1, std::vector<long long>(N+1, 50000000));
		
		for(int n=0; n<=N; n++) { verticies[n][n] = 0; antecedents[n][n] = n; }
		
		
		
		
		std::cin >> M; 
		for(int m=0; m<M; m++){ 
			std::cin >> eStart >> eEnd >> eWeight;
			verticies[eStart][eEnd] = eWeight;
			antecedents[eStart][eEnd] = eStart;
		}
		
		
		
		for(int q=1; q<=N; q++){
			for(int i=1; i<=N; i++){
				for(int j=1; j<=N; j++){
					if( verticies[i][j] > verticies[i][q] + verticies[q][j] ) {
						verticies[i][j] = verticies[i][q] + verticies[q][j];
						antecedents[i][j] = antecedents[q][j];
					}
				}
			}
		}
		
		
		
		
		minCost = vertex[1]; 
		
		for(int n=1; n<=N; n++){ 
			if( minCost > verticies[1][n] + verticies[n][1] + vertex[n] ) {
				minCost = verticies[1][n] + verticies[n][1] + vertex[n];
			}
		}
		std::cout << minCost << std::endl;
		
		
		 
	}

	return 0;
}
