#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <Aria.h>
#include "avoid.h"

// Constructor
FSMA::FSMA() : ArAction("FSMA")
{
	speed = 50;			// 100m/s, max 200
	deltaHeading = 0;	// Straight line
	setPoint = 500;		// 0.5m
}

// Event fired by robot
ArActionDesired * FSMA::fire(ArActionDesired state)
{
	desiredState.reset();

	ArPose robotPos;

	// Obstacle avoidance logic

	state.setVel(20);
	frontSonar = myRobot->getClosestSonarRange(-20, 20);
	leftSonar = myRobot->getClosestSonarRange(-20, 100);
	rightSonar = myRobot->getClosestSonarRange(-100, 20);


	if (frontSonar < setPoint) {
		state.setDeltaHeading(90);
	}

	if (leftSonar < setPoint) {
		state.setDeltaHeading(45);
	}

	if (rightSonar < setPoint) {
		state.setDeltaHeading(-45);
	}

	std::cout << "[AVOID]" << std::endl;

	desiredState = state;

	return &desiredState; // give the desired state to the robot for actioning
}

