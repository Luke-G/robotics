// Signatures

class FSMA : public ArAction // Class action inherits from ArAction
{
public:
	FSMA(); // Constructor
	virtual ~FSMA() {}  // Destructor
	virtual ArActionDesired * fire(ArActionDesired state); // Body of the action

	ArActionDesired desiredState; // Holds state of the robot that we wish to action
protected:

	int speed;

	double setPoint;
	double deltaHeading;

	double frontSonar;
	double leftSonar;
	double rightSonar;
};
