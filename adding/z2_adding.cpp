#include <iostream>
#include <vector>

unsigned long long reverse(unsigned long long q){
	unsigned long long v = 0;
	while(q>0){
		v = v + (q % 10);
		v *=10;
		q = q / 10;
	}

	return v/10;
}

int main(){
	unsigned long long n, x, y;
	
	std::cin >> n;
	for(unsigned long long i=0; i<n; i++){
		std::cin >> x >> y;
		std::cout << reverse(reverse(x) + reverse(y)) << std::endl;
	}
	
	return 0;
}
