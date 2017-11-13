// Signatures

class FSM : public ArAction // Class action inherits from ArAction
{
public:
	FSM(); // Constructor
	virtual ~FSM() {}  // Destructor
	virtual ArActionDesired EdgeFollow(ArActionDesired state, char direction, double distance);

	ArActionDesired desiredState; // Holds state of the robot that we wish to action
protected:

	int speed;
	int timeWandering;

	double setPoint;
	double deltaHeading;

	double maxObstacleDistance;	// Max proximity to object before avoid action should fire

	double pGain;				// Proportional Gain
	double iGain;				// Integral Gain
	double dGain;				// Derivative Gain

	double pTerm;				// Proportional Term
	double iTerm;				// Integral Term
	double dTerm;				// Derivative Term

	double derivative;
	double error;

	double lastError;
	double totalError;
};
