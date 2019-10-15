#include<iostream>
#include<vector>
#include<math.h>
#include <limits>

using namespace std;

typedef pair<int, int> pairs;

double m[100][100];
vector<vector<int>> paths;
int cities[100];
int n, d;

double calcDist(pairs p1, pairs p2){
	return sqrt(pow((p2.first - p1.first), 2) + pow((p2.second - p1.second), 2));
}

void swapIndex(int i, int start){
	int temp = cities[i];
	cities[i] = cities[start];
	cities[start] = temp;
}

void bruteForce(int start, int end){
	if(start == end){
		vector<int> path;
		for(int i = 0; i < n; i++){
			path.push_back(cities[i]);
		}
		paths.push_back(path);
	} else {
		for(int i = start; i <= end; i++){
			swapIndex(i, start);
			bruteForce(start + 1, end);
			swapIndex(i, start);
		}
	}	

}

int main(){
	cin >> n;
	vector<pairs> coords;
	int x, y;
	for(int i = 0; i < n; i++){
		cin >> x >> y;
		coords.push_back(make_pair(x, y));
	}

	for(int i = 0; i < n; i++){
		for(int j = i; j < n; j++){
			double d = calcDist(coords[i], coords[j]);
			m[i][j] = d;
			m[j][i] = d;
		}
	}

	for(int i = 0; i < n; i++){
		cities[i] = i;
	}

	bruteForce(1, n-1);

	double menorDist = std::numeric_limits<double>::infinity();

	int index = 0;

	for(int i = 0; i < paths.size(); i++){
		double respParcial = 0;
		for(int j = 1; j < paths[i].size(); j++){
			respParcial += m[paths[i][j-1]][paths[i][j]]; 
		}
		respParcial += m[paths[i][n-1]][paths[i][0]];

		if(respParcial < menorDist){
			menorDist = respParcial;
			index = i;
		}
	}

	cout << "Distância: " << menorDist << endl << "Caminho: ";
	for(int i = 0; i < paths[index].size(); i++){
		cout << paths[index][i] + 1 << " ";
	}
	cout << endl;




	return 0;
}