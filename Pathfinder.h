/*
 * Pathfinder.h
 *
 *  Created on: Mar 10, 2015
 *      Author: bryce14
 */

#ifndef PATHFINDER_H_
#define PATHFINDER_H_

#include "PathfinderInterface.h"

class Pathfinder: public PathfinderInterface {
public:
	Pathfinder();
	virtual ~Pathfinder();

	string getMaze();
	void createRandomMaze();
	bool importMaze(string file_name);
	vector<string> solveMaze();
	bool findPath(int, int, int);

private:
	const int x = 5;
	const int y = 5;
	const int z = 5;
	int Maze[5][5][5];
	int findMaze[5][5][5];
	vector<string> solution;
	vector<string> final_solution;
};

#endif /* PATHFINDER_H_ */



