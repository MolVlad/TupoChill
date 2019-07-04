#define R1X -4500
#define R1Y 0

#define R3X -2000
#define R3Y -1200

#define R2X -1200
#define R2Y 0

#define R4X -2000
#define R4Y 1200

#define R5X -3500
#define R5Y -1200

option(PlayingState)
{
  initial_state(demo)
  {
    action
    {
      Stand();
    }
    transition
    {
      goto PlayingWait;
    }
  }
  state(PlayingWait)
  {
    action
    {
      Stand();
    }
    transition
    {
      if((theRobotInfo.number == 2) || (theBallModel.estimate.position.norm() < 2500.f))
        goto PlayingAttack;
      if((theRobotInfo.number == 1) && ((std::abs(theRobotPose.translation.x() - R1X) > 50.f) || (std::abs(theRobotPose.translation.y() - R1Y) > 50.f)))
        goto WalkToTarget_Playing;
      if((theRobotInfo.number == 2) && ((std::abs(theRobotPose.translation.x() - R2X) > 50.f) || (std::abs(theRobotPose.translation.y() - R2Y) > 50.f)))
        goto WalkToTarget_Playing;
      if((theRobotInfo.number == 3) && ((std::abs(theRobotPose.translation.x() - R3X) > 50.f) || (std::abs(theRobotPose.translation.y() - R3Y) > 50.f)))
        goto WalkToTarget_Playing;
      if((theRobotInfo.number == 4) && ((std::abs(theRobotPose.translation.x() - R4X) > 50.f) || (std::abs(theRobotPose.translation.y() - R4Y) > 50.f)))
        goto WalkToTarget_Playing;
    }
  }
  state(WalkToTarget_Playing)
  {
    action
    {
      if(theRobotInfo.number == 1)
        WalkToTargetPathPlanner(Pose2f(50.f, 50.f, 50.f), Pose2f(0.f, R1X, R1Y));
      else if(theRobotInfo.number == 2)
        WalkToTargetPathPlanner(Pose2f(50.f, 50.f, 50.f), Pose2f(0.f, R2X, R2Y));
      else if(theRobotInfo.number == 3)
        WalkToTargetPathPlanner(Pose2f(50.f, 50.f, 50.f), Pose2f(0.f, R3X, R3Y));
      else if(theRobotInfo.number == 4)
        WalkToTargetPathPlanner(Pose2f(50.f, 50.f, 50.f), Pose2f(0.f, R4X, R4Y));
      else if(theRobotInfo.number == 5)
        WalkToTargetPathPlanner(Pose2f(50.f, 50.f, 50.f), Pose2f(0.f, R5X, R5Y));
    }
    transition
    {
      if((theRobotInfo.number == 2) || (theBallModel.estimate.position.norm() < 2500.f))
        goto PlayingAttack;
    }
  }
  state(PlayingAttack)
  {
    action
    {
      Striker();
    }
    transition
    {
      if((theRobotInfo.number == 1) && (theBallModel.estimate.position.norm() > 2000.f))
        goto WalkToTarget_Playing;
    }
  }
}
