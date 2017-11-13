#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <Aria.h>
#include "obstacleDetection.h"

const long double PI = 3.141592653589793238;

// Obstacle object
struct Obstacle {
	double x;
	double y;
} obs;

// Declare array of obstacles
Obstacle obstacles[100] = { 0 };

// Function to store obstacles in an array - returns obstacle obj if stored
Obstacle storeObstacle(double x, double y)
{
	obs.x = x;
	obs.y = y;

	// Store the obstacle in an array
	for (int i = 0; i < 100; i++) {
		if (obstacles[i].x == 0 && obstacles[i].y == 0) {
			obstacles[i] = obs;
			return obs;
		}
	}

	return obs;
}

void FSM::ObstacleDetection(ArActionDesired state, char direction) {
	ArPose detectedObstaclePosition = myRobot->getPose();

	// Find distance and angle to object
	double angle;
	double dist = (myRobot->checkRangeDevicesCurrentPolar(-20, 20, &angle) - myRobot->getRobotRadius());

	// Calculate coords from robot
	robotSpaceX = cos((angle * PI) / 180) * dist;
	robotSpaceY = sin((angle * PI) / 180) * dist;

	// Rotate to global angle
	double heading = (robotPos.getTh() * PI) / 180;
	obstacleX = (cos(-heading) * robotSpaceX) + (-sin(-heading) * robotSpaceY);
	obstacleY = (sin(-heading) * robotSpaceX) + (cos(-heading) * robotSpaceY);

	// Translate global position
	obstacleGlobalX = obstacleX + detectedObstaclePosition.getX();
	obstacleGlobalY = obstacleY + detectedObstaclePosition.getY();

	Obstacle obstacle = storeObstacle(obstacleGlobalX, obstacleGlobalY);

	std::cout << "[Obstacle Found] x:" << obstacle.x << " y: " << obstacle.y << std::endl;
}