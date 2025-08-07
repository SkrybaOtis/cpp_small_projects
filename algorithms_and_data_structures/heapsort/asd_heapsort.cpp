#include <iostream>
#include <vector>

//hp_subtree działa

void hp_subtree(std::vector<long long>& heap, long long i, long long n)
{
    long long y = i;
    for(long long z=0; z<2; z++){
    	if(2*i+z <= n){
    	    if(heap[y] < heap[2*i+z]){ y = 2*i+z; }
    	}
    }
    
    if(y != i) { 
    	long long x; x = heap[i]; heap[i] = heap[y]; heap[y] = x; //swap
    	hp_subtree(heap, y, n);
    }
}


void hp_tree(std::vector<long long>& heap)
{
// create tree
	long long k;

	heap = std::vector<long long>();
	std::cin >> k;
	heap.push_back(k);

	for (long long j = 0; j < heap[0]; j++) {
		std::cin >> k;
		heap.push_back(k);
	}

// heap	
	for (int i = heap[0]/2; i > 0; i--){ hp_subtree(heap, i, heap[0]); } 
	
	

	for(int i = heap[0]; i>1; i--){
		hp_subtree(heap, 1, i);
		for (long long j = 1; j <= i; j++){std::cout << heap[j] << " ";}
		k = heap[1]; heap[1] = heap[i]; heap[i] = k;
		std::cout << std::endl;
	}
	      
	      
	      
	      
	for (long long j = 1; j <= heap[0]; j++){std::cout << heap[j] << " ";}
	std::cout << "\n" << std::endl;
    
}


int main()
{
   long long N;
    std::cin >> N;
    
    std::vector<long long> heap;

    for (long long i = 0; i < N; i++) {
        hp_tree(heap);
    }

    return 0;
}

