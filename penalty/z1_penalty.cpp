#include <iostream>
#include <cmath>

bool cntn(long long g, long long t, long long a, long long d){
	if (g==-1 && t==-1 && a==-1 && d==-1) { return false; }
	return true;
}
 
int main() {
    long long G, T, A, D;
    long long X, Y;
    
    long long t, power;
    
    while((std::cin >> G >> T >> A >> D) && cntn(G, T, A, D)){
    
    	X = 0; Y = 0;
    	
    	t = (G*A+D);
    	X = G*( (T*(T-1))/2 );
    	
    	power = log2(t);
    	if ( pow(2, power) != t ) { power = pow(2, power+1); } else { power = t; }
    	Y = power - t;
    	
    	while(power>1){ power/=2; X = X + power; } 

    	std::cout << G << "*" << A << "/" << T << "+" << D << "=" << X << "+" << Y << std::endl;
    	
    	
    }
    
    return 0;
    
}
