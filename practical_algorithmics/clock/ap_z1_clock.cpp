#include <iostream>
#include <cmath>
#include <iomanip>

#define M_PI 3.14159265358979323846

int main() {
	long double d, h, m, s, u; 
	long double t[2]; 
	long double r;
	
	std::cin >> d;
	
	for(int j=1; j<=d; j++){
		
		for(int i=0; i<2; i++){
			std::cin >> h >> m >> s >> u;
			t[i] = h*360000 + m*6000 + s*100 + u; 
		}
		std::cin >> r;
		std::cout << j << ". " << std::fixed << std::setprecision(3) << ( (t[1] - t[0])/4320000 )*(r*r)*M_PI << std::endl;
	
	}
	
	
	return 0;
}

