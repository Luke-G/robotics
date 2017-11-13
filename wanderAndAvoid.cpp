#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <Aria.h>
#include "wanderAndAvoid.h"

// Constructor
FSM::FSM() : ArAction("FSM")
{
	speed = 50;		// 100m/s, max 200
	deltaHeading = 0;	// Straight line
	setPoint = 500;		// 0.5m from wall (edge following)
}

int timeWandering = 0;
int randomHeading = 0;

double lastError = 0;
double totalError = 0;
bool turning = false;

int randomNumber() {
	return rand() % 360 + 1;
}

ArActionDesired FSM::GoForward(ArActionDesired state)
{
	std::cout << "FORWARD" << std::endl;

	state.setVel(50);

	frontSonar = myRobot->getClosestSonarRange(-20, 20);
	leftSonar = myRobot->getClosestSonarRange(-20, 100);
	rightSonar = myRobot->getClosestSonarRange(-100, 20);

	// Obstacle front -> turn around
	if (frontSonar < maxObstacleDistance) {
		state = Avoid(state, 'F');
		timeWandering = 0;
	}
	// Obstacle left -> turn right
	else if (leftSonar < maxObstacleDistance) {
		state = Avoid(state, 'L');
		timeWandering = 0;
	}
	// Obstacle right -> turn left
	else if (rightSonar < maxObstacleDistance) {
		state = Avoid(state, 'R');
		timeWandering = 0;
	}
	else {
		// If obstacle on the left, edge follow
		if (leftSonar <= 700) {
			state = EdgeFollow(state, 'L', leftSonar);
			return state;
		}
		else if (rightSonar <= 700) {
			state = EdgeFollow(state, 'R', rightSonar);
			return state;
		}

		timeWandering++;

		// Timeout -> turn randomly
		if (timeWandering > 100) {

			// Generate a random number if the robot is not turning
			if (turning == false) {
				 randomHeading = randomNumber();
			}

			turning = true;

			std::cout << "TURNING RANDOMLY: " << randomHeading << std::endl;

			//state.setDeltaHeading(randomHeading);	// Random heading between 1 and 360

			// Allow time for the robot to turn, then stop the turn
			if (timeWandering > 110) {
				timeWandering = 0;
				turning = false;
			}
		}
	} 

	return state;
}

ArActionDesired FSM::Avoid(ArActionDesired state, char direction)
{
	std::cout << "AVOID" << std::endl;

	state.setVel(20);

	switch (direction) {
		// Obstacle in front -> turn around
		case 'F':
			state.setDeltaHeading(180);
		case 'L':
			state.setDeltaHeading(45);
		case 'R':
			state.setDeltaHeading(-45);
	}

	return state;
}

// Event fired by robot
ArActionDesired * FSM::fire(ArActionDesired d)
{
	desiredState.reset();
	desiredState = GoForward(desiredState);
	std::cout << frontSonar << " " << leftSonar << " " << rightSonar << " " << timeWandering << std::endl;

	robotPos = myRobot->getPose();
	
	// Record the starting position when the code begins execution
	if (robotStartingPos == NULL) {
		robotStartingPos = robotPos;
	}

	std::cout << "[Robot Position] x: " << robotPos.getX() << " y: " << robotPos.getY() << " HDG: " << robotPos.getTh() << std::endl;

	// Obstacle detected ahead within range of 1.5m
	if (frontSonar < 1500) {
		ObstacleDetection(desiredState, 'F');
	}

	return &desiredState; // give the desired state to the robot for actioning
}


