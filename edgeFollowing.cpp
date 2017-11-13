#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <Aria.h>
#include "edgeFollowing.h"

ArActionDesired FSM::EdgeFollow(ArActionDesired state, char direction, double distance) {
	maxObstacleDistance = 200;

	pGain = 0.02;		// Proportional Gain
	iGain = 0.0004;		// Integral Gain
	dGain = 2;			// Derivative Gain

	int heading = 0;

	if (direction == 'L') {
		error = distance - setPoint;
	}
	else {
		error = distance - setPoint;
	}

	if (error < 400) {
		derivative = error - lastError;
		lastError = error;

		pTerm = pGain * error;
		iTerm = iGain * totalError;
		dTerm = dGain * derivative;

		if (error != 0) {
			totalError += error;
			heading = pTerm + iTerm + dTerm;
			if (direction == 'R') {
				heading = -(pTerm + iTerm + dTerm);
			}
		}
		else {
			totalError = 0;
		}

		state.setDeltaHeading(heading);
	}

	std::cout << "EDGE FOLLOWING" << std::endl;
	std::cout << "pTerm: " << pTerm << " iTerm: " << iTerm << " dTerm: " << dTerm << std::endl;
	std::cout << direction << " " << distance << " " << error << " " << " " << heading << std::endl;
	std::cout << std::endl;

	return state;
}