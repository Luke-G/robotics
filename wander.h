// Signatures

class FSM : public ArAction // Class action inherits from ArAction
{
public:
	FSM(); // Constructor
	virtual ~FSM() {}  // Destructor
	virtual ArActionDesired * fire(ArActionDesired state); // Body of the action

	ArActionDesired desiredState; // Holds state of the robot that we wish to action
protected:

	ArPose robotStartingPos;

	int speed;
	int timeWandering;

	double setPoint;
	double deltaHeading;

	double frontSonar;
	double leftSonar;
	double rightSonar;

	bool turning;
};
