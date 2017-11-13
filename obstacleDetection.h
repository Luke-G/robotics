// Signatures

class FSM : public ArAction // Class action inherits from ArAction
{
public:
	FSM(); // Constructor
	virtual ~FSM() {}  // Destructor
	virtual void ObstacleDetection(ArActionDesired state, char direction);

	ArActionDesired desiredState; // Holds state of the robot that we wish to action
protected:

	int speed;
	int timeWandering;

	double setPoint;
	double deltaHeading;

	double maxObstacleDistance;	// Max proximity to object before avoid action should fire

	double obstacleX;
	double obstacleY;

	double obstacleGlobalX;		// x: Obstacle coords in global space
	double obstacleGlobalY;		// y: Obstacle coords in global space

	double robotSpaceX;			// x: Obstacle coords relative to robot
	double robotSpaceY;			// y: Obstacle coords relative to robot

	ArPose robotPos;
};
