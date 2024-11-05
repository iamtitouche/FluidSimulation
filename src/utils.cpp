//
// Created by dev on 05/11/2024.
//

#include "../headers/utils.hpp"
#include <sstream>
#include <vector>

using namespace std;

vector<int> getAdjacentZones(int n, int subdivPerLine, int NumberSubdiv) {
	vector<int> adj;

	int subdivPerColumn = NumberSubdiv / subdivPerLine;

	int row = n / subdivPerLine;
	int column = n % subdivPerLine;

	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			int new_row = i + row;
			int new_column = j + column;

			if (new_row >= 0 & new_row < subdivPerColumn && new_column >= 0 && new_column < subdivPerLine) {
				adj.push_back(new_row * subdivPerLine + new_column);
			}
		}


	}

	return adj;
}