/*
 * Pathfinder.cpp
 *
 *  Created on: Mar 10, 2015
 *      Author: bryce14
 */

#include "Pathfinder.h"
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>
#include <algorithm>
#include <vector>
#include <sstream>


Pathfinder::Pathfinder() {
	// TODO Auto-generated constructor stub
	for (int x = 0; x < 5; x++) {
				for (int y = 0; y < 5; y++) {
					for (int z = 0; z < 5; z++) {
						Maze[x][y][z] = 1;
					}
				}
			}
}


Pathfinder::~Pathfinder() {
	// TODO Auto-generated destructor stub
}


string Pathfinder::getMaze() {
	string result;
	for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 5; y++) {
				for (int z = 0; z < 5; z++) {
					result += to_string(Maze[x][y][z]); //still going to work with test driver cuz of c++11
					if (z < 4) {
						result += " ";
					}
				}
				if (y < 4) {
						result += "\n";
					}
			}
			if (x < 4) {
				result += "\n\n";
			}
		}
	return result;
}


void Pathfinder::createRandomMaze() {
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				int rand_number = (rand() % 2);
				Maze[x][y][z] = rand_number;
			}
		}
	}
	Maze[0][0][0] = 1;
	Maze[4][4][4] = 1;
}


bool Pathfinder::importMaze(string file_name) {
	ifstream in(file_name);
	int tempMaze[5][5][5];
	int temp_value;
	if (in.fail()) { //still going to work with test driver cuz of c++11
		return false;
	}
	else {
		for (int x = 0; x < 5; x++) {
				for (int y = 0; y < 5; y++) {
					for (int z = 0; z < 5; z++) {
						in >> temp_value;
						if (in.fail()) {
							return false;
						}
						if (temp_value != 1 && temp_value != 0) {
							return false;
						}
						tempMaze[x][y][z] = temp_value;
					}
				}
			}
		if (!in.eof()) {
			return false;
		}
		if (tempMaze[0][0][0] != 1) {
			return false;
		}
		if (tempMaze[4][4][4] != 1) {
			return false;
		}
	}
	for (int x = 0; x < 5; x++) {
			for (int y = 0; y < 5; y++) {
				for (int z = 0; z < 5; z++) {
					Maze[x][y][z] = tempMaze[x][y][z];
				}
			}
		}
	return true;
}


vector<string> Pathfinder::solveMaze() {
	for (int x = 0; x < 5; x++) {
		for (int y = 0; y < 5; y++) {
			for (int z = 0; z < 5; z++) {
				findMaze[x][y][z] = Maze[x][y][z];
			}
		}
	}
	while (!solution.empty()) {
		solution.pop_back();
	}
	findPath(0, 0, 0);
	reverse(solution.begin(), solution.end());
	return solution;
}


bool Pathfinder::findPath(int x, int y, int z) {
	int visited = 2;
	if (x < 0 || x > 4 || y < 0 || y > 4 || z < 0 || z > 4) {
		return false;
	}
	if (findMaze[x][y][z] != 1) {
		return false;
	}
	if (x == 4 && y == 4 && z == 4) {
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		solution.push_back(ss.str());
		return true;
	}
	findMaze[x][y][z] = 2;
	if (findPath(x, y, z + 1) || findPath(x, y + 1, z) || findPath(x + 1, y, z) ||
			findPath(x, y, z - 1) || findPath(x, y - 1, z) || findPath(x - 1, y, z)) {
		stringstream ss;
		ss << "(" << x << ", " << y << ", " << z << ")";
		solution.push_back(ss.str());
		return true;
	}
	return false;
}

