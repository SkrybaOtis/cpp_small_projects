#include <iostream>
#include <vector>

int bigger(int a, int b){
	if(a>b) { return a; } else { return b; }
}

int main() {

	int largest, sum1, sum2;
    	int n1, n2;
    
    while (std::cin >> n1 && n1 != 0) { 	//sprawdzenie, czy to koniec przypadków testowych
    
        std::vector<int> v1(n1); 		//wczytanie długości 1 ciągu
        for (int i = 0; i < n1; i++) {
            std::cin >> v1[i];			//wczytanie elementów 1 ciągu
        } 
        
        std::cin >> n2; 			//wczytanie długości 2 ciągu
        std::vector<int> v2(n2);
        for (int i = 0; i < n2; i++) {
            std::cin >> v2[i];			//wczytanie elementów 2 ciągu
        }
        
        std::vector<int> intersectionPoints;	//stworzenie wektora elementów wspólnych ciągów
        int i = 0, j = 0;
        
        
        while (i < n1 && j < n2) {	//pętla wczytująca cyfry wspólne do wektora elementów wspólnych ciągu
            if (v1[i] < v2[j]) { i++; }
            else if (v1[i] > v2[j]) { j++; }
            else { intersectionPoints.push_back(v1[i]); i++; j++; }
        }
        
        sum1 = 0; sum2 = 0; largest = 0; 	//largest jest zmienną z największą możliwą sumą liczb ciągów
        i = j = 0; 
        
        for (int k : intersectionPoints) { 	//pętla sumująca grupy liczb między elementami wspólnymi ciągów
            
            while (v1[i] != k) { sum1 += v1[i]; i++; } //sumowanie grupy z 1 ciągu do wspólnego elementu
            
            while (v2[j] != k) { sum2 += v2[j]; j++; } //sumowanie grupy z 2 ciągu do wspólnego elementu
            
            largest += bigger(sum1, sum2) + k; 	//dodanie większej sumy liczb między wspólnymi elementami ciągów
            i++; j++;
            sum1 = sum2 = 0;
        }
        
        while (i < n1) { sum1 += v1[i]; i++; } //sumowanie liczb od ostatniego wspólnego elementu do końca 1 ciągu
        
        while (j < n2) { sum2 += v2[j]; j++; } //sumowanie liczb od ostatniego wspólnego elementu do końca 2 ciągu
        
        largest += bigger(sum1, sum2); 		//dodanie większej sumy liczb końcowych

        std::cout << largest << std::endl;
    }

    return 0;
}
