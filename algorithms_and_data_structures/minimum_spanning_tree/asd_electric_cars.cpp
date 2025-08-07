#include <iostream>
#include <vector>


void merge(std::vector< std::vector<long long> >& left, std::vector< std::vector<long long> >& right, std::vector< std::vector<long long> >& bars, long long nL, long long nR) {
    long long i = 0, j = 0, k = 0;

    while (j < nL && k < nR) {
        if (left[j][2] < right[k][2]) {
            bars[i] = left[j];
            j++;
        } else {
            bars[i] = right[k];
            k++;
        }
        i++;
    }
    while (j < nL) {
        bars[i] = left[j];
        j++; i++;
    }
    while (k < nR) {
        bars[i] = right[k];
        k++; i++;
    }
}


void mergeSort(std::vector< std::vector<long long> >& bar, long long bSize) {
    if (bSize <= 1) return;

    long long mid = bSize / 2;
    std::vector< std::vector<long long> > left;
    std::vector< std::vector<long long> > right;

    for (long long j = 0; j < mid; j++)
        left.push_back(bar[j]);
    for (long long j = 0; j < (bSize-mid); j++)
        right.push_back(bar[mid + j]);

    mergeSort(left, mid);
    mergeSort(right, (bSize-mid));
    merge(left, right, bar, mid, (bSize-mid));
}






void incidentsListCreate( std::vector< std::vector< std::vector<long long> > >& startIncidentsList, std::vector< std::vector< std::vector<long long> > >& endIncidentsList, 
std::vector< std::vector<long long> >& startIncidents, std::vector< std::vector<long long> >& endIncidents, std::vector<long long>& incident, 
std::vector< std::vector<long long> >& edges, long long edgesCount, long long verticiesCount) {
	
startIncidentsList.clear(); endIncidentsList.clear(); startIncidents.clear(); endIncidents.clear(); incident.clear();

//tworzenie pustych list incydencji (z wagami)
	for( int v=0; v < verticiesCount; v++ ){
		incident.clear();
		incident.push_back(v); incident.push_back(0);
		
		startIncidents.clear(); endIncidents.clear();
		startIncidents.push_back(incident); endIncidents.push_back(incident);
		startIncidentsList.push_back(startIncidents); endIncidentsList.push_back(endIncidents);
	}
	
	for( int e=edgesCount-1; e>=0; e-- ){
		//for startIncidentsList
		incident.clear();
		incident.push_back(edges[e][1]); incident.push_back(edges[e][2]); 
		startIncidentsList[ (edges[e][0]) ].push_back(incident);
		
		//for endIncidentsList
		incident.clear();
		incident.push_back(edges[e][0]); incident.push_back(edges[e][2]); 
		endIncidentsList[ (edges[e][1]) ].push_back(incident);
	}
	
	//std::cout << startIncidentsList.size() << "=?=" << verticiesCount << std::endl;
}


void incidentsListShow( std::vector< std::vector< std::vector<long long> > >& startIncidentsList, std::vector< std::vector< std::vector<long long> > >& endIncidentsList, long long verticiesCount ){
	std::vector<long long> incdnt;
	
	for( int v=0; v < verticiesCount; v++ ){		
		for( int j=0; j<startIncidentsList[v].size(); j++ ){
			std::cout << '{' << startIncidentsList[v][j][0] << '}' << ' ';
		}
		incdnt = startIncidentsList[v].back(); 
		std::cout << '[' << incdnt[1] << ']' << ' ';
		std::cout << std::endl;		
	} std::cout << std::endl;
	
	for( int v=0; v < verticiesCount; v++ ){
		for( int j=0; j<endIncidentsList[v].size(); j++ ){
			std::cout << '{' << endIncidentsList[v][j][0] << '}' << ' ';
		}
		incdnt = endIncidentsList[v].back(); 
		std::cout << '[' << incdnt[1] << ']' << ' ';
		std::cout << std::endl;
	}
}






bool isLower( std::vector<long long>& inc, long long min ){
	if( inc[1] < min ) { return true; } else { return false; }
}

bool isVisited( std::vector<long long>& inc, std::vector<bool>& visited ){
	if( visited[ inc[0] ] ) { return true; } else { return false; }
}

bool isExistWay( std::vector<long long>& inc, std::vector<bool>& existWay ){
	if( existWay[ inc[0] ] ) { return true; } else { return false; }
}

bool isReverse( std::vector<long long>& v1, std::vector<long long>& v2, std::vector< std::vector<long long> > acceptedIncidents){
	for( long long& vi : acceptedIncidents[ v2[0] ] ){ if( vi==v1[0] ){ return true; } } return false;
}


void searchStart( std::vector<bool>& existWay, long long ex, std::vector< std::vector<long long> > acceptedIncidents, std::vector< std::vector< std::vector<long long> > >& startIncidentsList, std::vector<long long>& incident, long long& min_incident_v1, long long& min_incident_v2, long long& min_incident_w, bool& sORe, bool& isAcceptedEdge){

		if( startIncidentsList[ex].size() > 1 && isLower( startIncidentsList[ex].back(), min_incident_w ) ){ 
			if( isExistWay( startIncidentsList[ex].back(), existWay ) ){
			
				if ( !isReverse( startIncidentsList[ex].front(), startIncidentsList[ex].back(), acceptedIncidents ) ) {
					startIncidentsList[ex].pop_back();
				} else {
					incident = startIncidentsList[ex].back();
					min_incident_v1 = ex;
					min_incident_v2 = incident[0];
					min_incident_w = incident[1];
					sORe = 0;
					isAcceptedEdge = 1;
					//std::cout << '{' << min_incident_v1 << ", " << min_incident_v2 << ", " << min_incident_w << '}' << std::endl;
				}
				
			} else { 
					incident = startIncidentsList[ex].back();
					min_incident_v1 = ex;
					min_incident_v2 = incident[0];
					min_incident_w = incident[1];
					sORe = 0; 
					isAcceptedEdge = 0;
					//std::cout << '{' << min_incident_v1 << ", " << min_incident_v2 << ", " << min_incident_w << '}' << std::endl;
			}
		}
		
} // można zmienić na bool


void searchEnd( std::vector<bool>& visited, long long& ex, std::vector< std::vector<long long> > acceptedIncidents, std::vector< std::vector< std::vector<long long> > >& endIncidentsList, std::vector<long long>& incident, long long& min_incident_v1, long long& min_incident_v2, long long& min_incident_w, bool& sORe, bool& isAcceptedEdge){
		
		if( endIncidentsList[ex].size() > 1 && isLower( endIncidentsList[ex].back(), min_incident_w ) ){
			if( isVisited( endIncidentsList[ex].back(), visited ) ){
				if ( !isReverse( endIncidentsList[ex].back(), endIncidentsList[ex].front(), acceptedIncidents ) ) {
					endIncidentsList[ex].pop_back();
				} else {
					incident = endIncidentsList[ex].back();
					min_incident_v1 = incident[0];
					min_incident_v2 = ex;
					min_incident_w = incident[1];
					sORe = 1; 
					isAcceptedEdge = 1;
					//std::cout << '{' << min_incident_v1 << ", " << min_incident_v2 << ", " << min_incident_w << '}' << std::endl;
				}
				
			} else {
				if( isVisited( endIncidentsList[ex].front(), visited ) ){
					endIncidentsList[ex].pop_back();
				} else {
					incident = endIncidentsList[ex].back();
					min_incident_v1 = incident[0];
					min_incident_v2 = ex;
					min_incident_w = incident[1];
					sORe = 1; 
					isAcceptedEdge = 0;
					//std::cout << '{' << min_incident_v1 << ", " << min_incident_v2 << ", " << min_incident_w << '}' << std::endl;
				}
			}
		}
		
} // można zmienić na bool


void searchInc( std::vector<bool>& visited, std::vector<bool>& existWay, std::vector<long long>& vExistWay, std::vector< std::vector<long long> > acceptedIncidents, std::vector< std::vector< std::vector<long long> > >& startIncidentsList, std::vector< std::vector< std::vector<long long> > >& endIncidentsList, std::vector<long long>& incident, long long& min_incident_v1, long long& min_incident_v2, long long& min_incident_w, bool& sORe, bool& isAcceptedEdge){

	for(long long& ex : vExistWay){
		searchStart( existWay, ex, acceptedIncidents, startIncidentsList, incident, min_incident_v1, min_incident_v2, min_incident_w, sORe, isAcceptedEdge);
		searchEnd( visited, ex, acceptedIncidents, endIncidentsList, incident, min_incident_v1, min_incident_v2, min_incident_w, sORe, isAcceptedEdge);
		
	}
	
}






void afterAcceptEdge(std::vector<long long>& edge, long long& minc_v1, long long& minc_v2, long long& minc_w, bool& sORe, bool& isAcceptedEdge , std::vector< std::vector< std::vector<long long> > >& startIncidentsList, std::vector< std::vector< std::vector<long long> > >& endIncidentsList, std::vector<bool>& visited, std::vector<bool>& existWay, std::vector<long long>& vVisited, std::vector<long long>& vExistWay, long long& srch_indx_hlpr, std::vector< std::vector<long long> > acceptedIncidents){

	edge.clear();
	edge.push_back(minc_v1); edge.push_back(minc_v2); edge.push_back(minc_w);
	// minc_v1 ==> minc_v2   [ minc_w ]
	
	if(!sORe){
		startIncidentsList[minc_v1].pop_back();
		
		srch_indx_hlpr = endIncidentsList[minc_v2].size()-1;
		while(endIncidentsList[minc_v2][srch_indx_hlpr][0] != minc_v1 && srch_indx_hlpr > 0){ srch_indx_hlpr--; }
		if(srch_indx_hlpr != 0){ endIncidentsList[minc_v2].erase( endIncidentsList[minc_v2].begin() + srch_indx_hlpr ); }
		
			if(!isAcceptedEdge) { 
				if(existWay[ minc_v2 ] == 0){ vExistWay.push_back(minc_v2); } 
				if(visited[ minc_v2 ] == 0){ vVisited.push_back(minc_v2); }
			} else {
				if(visited[ minc_v2 ] == 0){ vVisited.push_back(minc_v2); }
			}
			
		visited[ minc_v2 ] = 1;
		existWay[ minc_v2 ] = 1;
		acceptedIncidents[minc_v1].push_back(minc_v2);
			
	} else {
		endIncidentsList[minc_v2].pop_back();
		
		srch_indx_hlpr = startIncidentsList[minc_v1].size()-1;
		while(startIncidentsList[minc_v1][srch_indx_hlpr][0] != minc_v2 && srch_indx_hlpr > 0){ srch_indx_hlpr--; }
		if(srch_indx_hlpr != 0){ startIncidentsList[minc_v1].erase( startIncidentsList[minc_v1].begin() + srch_indx_hlpr ); }
				
			if(!isAcceptedEdge) { 
				if(existWay[ minc_v1 ] == 0){ vExistWay.push_back(minc_v1); } 
				if(visited[ minc_v2 ] == 0){ vVisited.push_back(minc_v2); }
			} else {
				if(visited[ minc_v2 ] == 0){ vVisited.push_back(minc_v2); }
			}
		
		visited[ minc_v2 ] = 1;
		existWay[ minc_v1 ] = 1;
		acceptedIncidents[minc_v1].push_back(minc_v2);
				
	}
	
				
}









int main() {
	std::vector<bool> visited, existWay;

	std::vector<long long> verticies, verticiesVisited, verticiesExistWay, edge;
	std::vector< std::vector<long long> > edges, edgesAccepted;
	
	std::vector<long long> incident;
	std::vector< std::vector<long long> > startIncidents, endIncidents, acceptedIncidents;
	std::vector< std::vector< std::vector<long long> > > startIncidentsList, endIncidentsList;
	
	long long min_incident_v1, min_incident_v2, min_incident_w;
	
	bool sORe, isAcceptedEdge;
	long long search_help_indx;
	
	long long ex, max_min_w;
	
	int T, N, M; // 1 <= n <= 1 000; 1 <= m <= 10 000; no 0
	int eStart, eEnd, eWeight; // 1 <= weight <= 999 999; no 0
	
	std::cin >> T;
	
	for(int t=0; t<T; t++){
		std::cin >> N >> M;
		
		for(int n=0; n<N; n++){ verticies.push_back(n); incident.clear(); incident.push_back(n); acceptedIncidents.push_back(incident); } //verticiesToMode = verticies;
		for(int n=0; n<N; n++){ visited.push_back(0); existWay.push_back(0); }
		
		for(int m=0; m<M; m++){ 
			std::cin >> eStart >> eEnd >> eWeight;
			edge.push_back(eStart); edge.push_back(eEnd); edge.push_back(eWeight);
			edges.push_back(edge); edge.clear(); 		
		}
		
		mergeSort(edges, M); // do tego momentu jest bajlando: posortowany według wag wektor listy krawędzi 
		
		incidentsListCreate( startIncidentsList, endIncidentsList, startIncidents, endIncidents, incident, edges, M, N); // bajlando: stworzone listy incydencji (z wagami)
		
		
		//wstęp zrobiony żeby mieć już za sobą pierwsze wierzchołki dla existWay
		
		verticiesExistWay.push_back(edges[0][0]); verticiesExistWay.push_back(edges[0][1]); 
		verticiesVisited.push_back(edges[0][1]);
		
		visited[ edges[0][1] ] = 1;
		existWay[ edges[0][1] ] = 1;
		existWay[ edges[0][0] ] = 1;
		
		startIncidentsList[edges[0][0]].pop_back();
		endIncidentsList[edges[0][1]].pop_back();
		
		max_min_w = edges[0][2];
		
		//koniec wstępu
		
		
		while( verticiesExistWay.size() < N ){
			//incidentsListShow( startIncidentsList, endIncidentsList, N );
		
			incident.clear();
			min_incident_w = 1000000;
			
			
			searchInc( visited, existWay, verticiesExistWay, acceptedIncidents, startIncidentsList, endIncidentsList, incident, min_incident_v1, min_incident_v2, min_incident_w, sORe, isAcceptedEdge);

			
			afterAcceptEdge(edge, min_incident_v1, min_incident_v2, min_incident_w, sORe, isAcceptedEdge, startIncidentsList, endIncidentsList, visited, existWay, verticiesVisited, verticiesExistWay, search_help_indx, acceptedIncidents);

			
			//std::cout << verticiesExistWay.size() << " < " << N << std::endl;
			
			
			//for(int i=0; i<verticiesExistWay.size(); i++){ std::cout << verticiesExistWay[i] << ' '; } std::cout << std::endl;
			//for(int i=0; i<verticiesVisited.size(); i++){ std::cout << verticiesVisited[i] << ' '; } std::cout << std::endl;
			
			if(min_incident_w > max_min_w) { max_min_w = min_incident_w; }
			
		}
		std::cout << max_min_w << std::endl;
		 

		visited.clear(); existWay.clear();

		verticies.clear(); verticiesVisited.clear(); verticiesExistWay.clear(); edge.clear(); 
		edges.clear(); edgesAccepted.clear(); 
		
		incident.clear(); 
		startIncidents.clear(); endIncidents.clear(); acceptedIncidents.clear(); 
		startIncidentsList.clear(); endIncidentsList.clear(); 
		
		
		
	}
	
	
	
	return 0;
}
