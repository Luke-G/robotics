// Signatures

class FSM: public ArAction // Class action inherits from ArAction
{
 public:
   FSM(); // Constructor
   virtual ~FSM() {}  // Destructor
   virtual ArActionDesired * fire(ArActionDesired d); // Body of the action
   virtual ArActionDesired Avoid(ArActionDesired state, char direction);
   virtual ArActionDesired GoForward(ArActionDesired state);
   virtual void ObstacleDetection(ArActionDesired state, char direction);
   virtual ArActionDesired EdgeFollow(ArActionDesired state, char direction, double distance);


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

   double maxObstacleDistance;
   ArPose robotPos;
};
