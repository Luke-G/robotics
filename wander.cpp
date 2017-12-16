#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <Aria.h>
#include "wander.h"

// Constructor
FSM::FSM() : ArAction("FSM")
{
	speed = 50;			// 100m/s, max 200
	deltaHeading = 0;	// Straight line
}

// Event fired by robot
ArActionDesired * FSM::fire(ArActionDesired state)
{
	desiredState.reset();

	ArPose robotPos;
	robotPos = myRobot->getPose();

	// Wandering logic

	state.setVel(100);
	frontSonar = myRobot->getClosestSonarRange(-20, 20);
	leftSonar = myRobot->getClosestSonarRange(-20, 100);
	rightSonar = myRobot->getClosestSonarRange(-100, 20);

	timeWandering++;

	// Timeout -> turn randomly
	if (timeWandering > 100) {
		turning = true;

		// TODO: Replace with random heading change
		std::cout << "TURNING RANDOMLY: " << "30deg" << std::endl;
		state.setDeltaHeading(30);
		timeWandering = 0;
	}


	std::cout << "[WANDER]" << std::endl;
	std::cout << "[Robot Position] x: " << robotPos.getX() << " y: " << robotPos.getY() << " HDG: " << robotPos.getTh() << std::endl;

	desiredState = state;

	return &desiredState; // give the desired state to the robot for actioning
}

