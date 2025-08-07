#include <iostream>
#include <vector>

std::vector<long long> minPoint( std::vector< std::vector<long long> >& pnts ){
	std::vector<long long> pnt;
	long long x = 4294967296, y = 4294967296, indx=0;
	
	for(long long i=0; i<pnts.size(); i++){
		if(pnts[i][1] < y){
			y = pnts[i][1]; x = pnts[i][0]; indx = i;
		} else
		if(pnts[i][1] == y){
			if(pnts[i][0] < x){
				x = pnts[i][0]; indx = i;
			}
		}
	}
	pnt.push_back(x);
	pnt.push_back(y);
	
	pnts.erase(pnts.begin()+indx);
	
	return pnt;
}

long long compareAngleV(std::vector<long long> O, std::vector<long long> P, std::vector<long long> Q){
	if( (P[1]-O[1])*(Q[0]-O[0]) == (Q[1]-O[1])*(P[0]-O[0]) ) return 0;
	if( (P[1]-O[1])*(Q[0]-O[0]) < (Q[1]-O[1])*(P[0]-O[0]) ) return 1;
	return 2;
}


std::vector<long long> farestPoint(std::vector<long long> O, std::vector<long long> P, std::vector<long long> Q){
	long long Px2, Py2, Qx2, Qy2;
	Px2 = (P[0]-O[0])*(P[0]-O[0]);
	Py2 = (P[1]-O[1])*(P[1]-O[1]);
	Qx2 = (Q[0]-O[0])*(Q[0]-O[0]);
	Qy2 = (Q[1]-O[1])*(Q[1]-O[1]);
	
	return (Px2+Py2)>(Qx2+Qy2)?P:Q;
}

long long absltV(long long v){ return v<0?-v:v; }

std::vector< std::vector<long long> > mergeV(std::vector< std::vector<long long> >& left, std::vector< std::vector<long long> >& right, std::vector<long long> point){
	std::vector< std::vector<long long> > tbls;
	long long nL = left.size(), nR = right.size();
	long long i = 0, j = 0, k = 0;
	
	while (j < nL && k < nR) {
		while((j < nL && k < nR) && left[j][0] == point[0] && left[j][1] == point[1]){ j++; }
		while((j < nL && k < nR) && right[k][0] == point[0] && right[k][1] == point[1]){ k++; }
		
		if(j < nL && k < nR){
			if ( compareAngleV( point, left[j], right[k]) == 0 ) {
				tbls.push_back(farestPoint(point, left[j], right[k]));
				j++; k++;
			} else
			if ( compareAngleV( point, left[j], right[k]) == 1 ) {
				tbls.push_back(left[j]);
				j++;
			} else {
				tbls.push_back(right[k]);
				k++;
			}
		}
			i++;
	}
	while (j < nL) { tbls.push_back(left[j]); j++; i++; }
	while (k < nR) { tbls.push_back(right[k]); k++; i++; }
	return tbls;
}


std::vector< std::vector<long long> > mergeSortV(std::vector< std::vector<long long> >& tbl, std::vector<long long> point){
	std::vector< std::vector<long long> > nwTbl;
	if (tbl.size() <= 1) { nwTbl = tbl; return nwTbl; }
	
	long long mid = tbl.size()/2;
	std::vector< std::vector<long long> > left, right, nwLeft, nwRight;
	
	for (long long j = 0; j < mid; j++)
		left.push_back(tbl[j]);
	
	for (long long j = 0; j < (tbl.size()-mid); j++)
		right.push_back(tbl[mid + j]);

	nwLeft = mergeSortV(left, point);
	nwRight = mergeSortV(right, point);
	
	return mergeV(nwLeft, nwRight, point);
}

long long ccw(std::vector<long long> P, std::vector<long long> Q, std::vector<long long> R) {
  return (Q[0] - P[0]) * (R[1] - P[1]) - (R[0] - P[0]) * (Q[1] - P[1]);
}


std::vector<long long> beforeLast(std::vector< std::vector<long long> > lifo) {
  return lifo[lifo.size() - 2];
}
std::vector<long long> last(std::vector< std::vector<long long> > lifo) {
  return lifo[lifo.size() - 1];
}


void grahamka(std::vector< std::vector<long long> >& sztos, std::vector< std::vector<long long> >& points ){
	//std::cout << sztos[0][0] << " " << sztos[0][1] << std::endl;
	for(long long i = 0; i < points.size(); i++){
		    while (sztos.size() > 1 && ccw(beforeLast(sztos), last(sztos), points[i]) <= 0) {
		      sztos.pop_back();
		    }
		    sztos.push_back(points[i]);
	}
}

bool isIn(std::vector< std::vector<long long> >& sztos, std::vector<long long> point){
	for(long long j = 0; j < sztos.size(); j++){
		if ( ccw(sztos[j], sztos[( (j+1) % sztos.size() )], point) < 0 ) {
			return false;
		}
	}
	return true;
}

void insidePoints(std::vector< std::vector<long long> >& sztos, std::vector< std::vector<long long> >& points, std::vector< std::vector<long long> >& inside){
	for(long long i = 0; i < points.size(); i++){
		if(isIn(sztos, points[i])){
			inside.push_back(points[i]);
		}
	}
}

int main() {
	long long P, x, y;
	std::vector<long long> point;
	std::vector< std::vector<long long> > points, newPoints, trapped;
	

	std::cin >> P;
	while(P--){
		std::cin >> x >> y;
		point.push_back(x); point.push_back(y);
		points.push_back(point);
		point.clear();
	}
	
	point = minPoint(points);
	
	newPoints = mergeSortV(points, point);
	
	points.clear();
	points.push_back(point);
	grahamka(points, newPoints);
	
	
	point.clear();
	newPoints.clear();
	std::cin >> P;
	while(P--){
		std::cin >> x >> y;
		point.push_back(x); point.push_back(y);
		newPoints.push_back(point);
		point.clear();
	}
	
	insidePoints(points, newPoints, trapped);
	
	std::cout << trapped.size() << std::endl;
	
	
	point.clear();
	points.clear();
	newPoints.clear();
	trapped.clear();

	return 0;
}
