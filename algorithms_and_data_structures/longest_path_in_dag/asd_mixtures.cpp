#include <iostream>
#include <vector>

long long maximus( std::vector<long long> vctr, std::vector<long long> values ){
	long long max = 0;
	for(long long inc : vctr){ if(values[inc] > max) { max = values[inc]; } }
	return max;
}

bool boolExist( long long x, std::vector<long long> incs ){
	for(long long inc : incs){ if(x==inc){ return true; } }
	return false;
}

int main() {
	int T, N, M;
	long long a, b, w, x, y, z;
	long long max=0;
	
	
	
	std::vector< std::vector<long long> > A, B, incA;
	std::vector<long long> aVector, bVector, inc, aValues, bMaxis;
	
	std::vector< std::vector<long long> > transmutations; 
	std::vector<long long> transmute;
	
	std::cin >> T;
	for(int i=0; i<T; i++){
		std::cin >> N >> M;
		
		aValues.push_back(0);
		aVector.push_back(N); aVector.push_back(M); A.push_back(aVector); aVector.clear();
		inc.push_back(0); incA.push_back(inc); inc.clear(); 
		
		for(int j=0; j<N; j++){ 
			std::cin >> a; aValues.push_back(a);
			aVector.push_back(a); aVector.push_back(0); A.push_back(aVector); aVector.clear(); 
			inc.push_back(j+1); incA.push_back(inc); inc.clear();			
		} 
		//for(int j=1; j<=N; j++){ std::cout << aValues[j] << ' '; } std::cout << std::endl;
		
		//for(int j=1; j<=N; j++){ std::cout << j << ' '; } std::cout << std::endl;
		//for(int j=1; j<=N; j++){ std::cout << A[j][0] << ' '; } std::cout << std::endl;
		
		for(int j=0; j<M; j++){ 
			std::cin >> x >> y; 
			A[y][1] = A[y][1]+1; 
			transmute.push_back(x); 
			transmute.push_back(y); 
			//if(A[y]-A[x] > 0) {transmute.push_back( A[y]-A[x] );} else {transmute.push_back(0);} transmutations.push_back(transmute); 
			transmute.push_back( A[y][0]-A[x][0]);
			transmutations.push_back(transmute); 
			transmute.clear(); 
			
			incA[x].push_back(y);
		} //std::cout << std::endl;
		
		//for(int j=0; j<M; j++){ std::cout << transmutations[j][0] << '-' << transmutations[j][1] << '=' << transmutations[j][2] << std::endl; } std::cout << std::endl;
		
		/*
		for(int j=1; j<=N; j++){
			for(long long incs : incA[j]){ std::cout << incs << ' '; }
			std::cout << std::endl;
		} std::cout << std::endl;
		*/
		
		//for(int j=1; j<=N; j++){ std::cout << aValues[j] << ' '; } std::cout << std::endl;
		//for(int j=1; j<=N; j++){ std::cout << A[j][0] << " -> " << A[j][1] << ' '; } std::cout << std::endl;
		
		
		z=1;
		while(A[0][0] != 0 && z != 0){
			z=1;
			while(z<A.size() && A[z][1] != 0){  z++; } //search vertex with in-degree == 0 
				// std::cout << A[z][0] << "v0" << std::endl; -: tu git
			if(z==A.size()){ z--; } //std::cout << z << std::endl;
			if(z<A.size() && A[z][1] == 0){ // when vertex 0 in-dgre exist
				bVector.push_back(z);
				bVector.push_back(A[z][0]); 
				B.push_back(bVector);
				bVector.clear();
					 //std::cout << B[0][1] << std::endl; //-: tu git
				A[z][1] = -1;
				A[0][0] -= 1;
					// std::cout << A[0][0] << std::endl; -: tu git
				if(A[0][0] != 0){
					w=0;
					for(std::vector<long long>& transms : transmutations){
						//std::cout << transms[0] << '=' << z << std::endl; //-: tu git
						
						if(transms[0] == z){
							A[transms[1]][1] -= 1;
							//transmutations.erase (transmutations.begin()+w);
							w--;
						}
						w++;
					}
				}
				
			} else { z = 0; }
			
		}
		
		
		//for(int j=1; j<=N; j++){ std::cout << j << ' '; } std::cout << std::endl;
		bMaxis.push_back(0);
		for(int j=1; j<=N; j++){ 
			bMaxis.push_back( maximus( incA[j], aValues ) ); 
			//std::cout << bMaxis[j]<< ' '; 
		} //std::cout << std::endl; //lista incydencji z najwyższą z cen dla danej kolumny dodaną na końcu kolumny
		
		
		
		
		//for (int j=0; j<B.size(); j++) { std::cout << B[j][0] << ' '; } std::cout << std::endl; //posortowana topologicznie tablica
		//for (int j=0; j<B.size(); j++) { std::cout << B[j][1] << ' '; } std::cout << std::endl; std::cout << std::endl;
		
		
		
		
		
		
		
		for(int j=N-1; j>=0; j--) {
			for(int k=1; k<=N; k++){
				if( bMaxis[ (B[j][0]) ] > bMaxis[k] ){
					if( B[j][0] != k && boolExist(B[j][0], incA[k]) ){
						//std::cout << B[j][0] << ' ' << k << std::endl;
						//std::cout << bMaxis[j] << ' '; 
						bMaxis[k] = bMaxis[ (B[j][0]) ];
						if( bMaxis[k] - aValues[k] > bMaxis[0] ) { bMaxis[0] = bMaxis[k]-aValues[k]; }
					}
				} else {
					//std::cout << bMaxis[k] << ' ';
					if( bMaxis[k] - aValues[k] > bMaxis[0] ) { bMaxis[0] = bMaxis[k] - aValues[k]; }
				}
				//if(j==0) { std::cout << bMaxis[k] << ' '; }
			}
			
		}// std::cout << std::endl;
		
		std::cout << bMaxis[0] << std::endl;
		
		
		
		
		
		
		
		A.clear(); aVector.clear(); 
		B.clear(); bVector.clear();
		incA.clear(); inc.clear();
		aValues.clear(); bMaxis.clear();
		transmutations.clear(); transmute.clear();
	}
	
	
	
	return 0;
}
