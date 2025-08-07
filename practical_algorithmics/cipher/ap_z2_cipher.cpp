#include <iostream>
#include <vector>

char searchX( std::vector< std::vector<char> > inc){ 
	char x;
	char xd = '\0';
	for(auto& v1 : inc) {
		x = v1[0];
		for(auto& v2 : inc) {
			if(v1[0] == v2[1]){ x = '\0'; }
		}
		if(xd == '\0' && x != '\0'){ xd = x; }
		else if(xd != '\0' && x != '\0' && xd != x){ return '\0'; }
	}	

	return xd;
}


char searchY( std::vector< std::vector<char> > inc){ 
	char y;
	char yd = '\0';
	for(auto& v2 : inc) {
		y = v2[1];
		for(auto& v1 : inc) {
			if(v2[1] == v1[0]){ y = '\0'; }
		}
		if(yd == '\0' && y != '\0'){ yd = y; }
		else if(yd != '\0' && y != '\0'){ return '\0'; }
	}	
	return yd;
}



int main(){
	char alpha[] = "abcdefghijklmnopqrstuvwxyz" ;
	std::vector<char> alphabet( alpha, alpha+sizeof(alpha)-1 ) ;
	
	
	std::vector<char> sub_alphabet; 
	std::vector<char> cipher_alphabet;
		
	std::vector< std::vector<char> > incidents; 
	std::vector<char> incident; 
	
	
	long long a, k, l, m, n;
	char x, y;
	std::string word;
	std::vector<char> word1;
	std::vector<char> word2;
	
	
	std::cin >> n; 
		for(long long i=0; i<n; i++){ 
		
			std::cin >> a >> k;
			
			
			for(long long j=0; j<a; j++){ sub_alphabet.push_back(alphabet[j]); } 
			
			
			std::cin >> word;
			for(char& x : word){ word1.push_back(x); }
			for(long long j=1; j<k; j++){ 
				std::cin >> word;	
				for(char& x : word){ word2.push_back(x); } 
				l=0;
				while(word1[l] && word2[l] && word1[l] == word2[l]){ l++; }
				if(word1[l] && word2[l]){
					incident.push_back(word1[l]);
					incident.push_back(word2[l]);
					incidents.push_back(incident);
					incident.clear();
				}
				word1 = word2;
				word2.clear();
			}
			
			
			l=0;
			for(auto &itr: incidents) { l++; }
				
				x = searchX(incidents); 
				y = searchY(incidents);
				
				
			if( l >= a-1 && x != '\0' && y != '\0'){ 
			
			
			
				while(l>=1 && searchX(incidents) != '\0'){
					x = searchX(incidents);
					cipher_alphabet.push_back(x);
					for(long long itr = 0; itr < incidents.size(); itr++){
						if( incidents[itr][0] == x ) {
							incidents.erase (incidents.begin()+itr); 
							l--;
							itr--;
						}
					}
				}
				cipher_alphabet.push_back(y);
				
				
				
				std::cin >> word;
				for(char& x : word){ 
					m=0;
					while( m < sub_alphabet.size() && x != cipher_alphabet[m] ){ m++; }
					if(x == cipher_alphabet[m]){ std::cout << sub_alphabet[m]; } else { std::cout << x; }
				}
				
				
				
			} else { std::cout << "Message cannot be decrypted"; } 
			std::cout << std::endl;
			incidents.clear();
			incident.clear();
			word1.clear();
			word2.clear();
			alphabet.clear();
			sub_alphabet.clear();
		}

	
	return 0;
}
