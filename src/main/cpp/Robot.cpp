/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#include "Robot.h"

void Robot::RobotInit() 
{
  //Get instances of different subsystems
    drivetrain = Drivetrain::GetInstance();
    climber = Climber::GetInstance();
    oi = OI::GetInstance();
    limelight = LL::GetInstance();
    led = LED::GetInstance();
    intake = Intake::GetInstance();
    shooter = Shooter::GetInstance(); 
  
  //Set up auto chooser 
    m_chooser.SetDefaultOption(runTeleop, runTeleop);
    m_chooser.AddOption(barrelRacingPath, barrelRacingPath);
    frc::SmartDashboard::PutData("Auto Modes", &m_chooser);

  limelight->limelight_LED_blink(); //Force limelights to blink on powerup 
  led->colorDetectionInit(); 
  oi->oiInit(); 
  shooter->shooterShuffleInfo(); 
  //climber->climberInit(); 
  setZero = drivetrain->GetHeading();  
  drivetrain->AutonomousInit();

}
 


/**
 * This function is called every robot packet, no matter the mode. Use
 * this for items like diagnostics that you want ran during disabled,
 * autonomous, teleoperated and test.
 *
 * <p> This runs after the mode specific periodic functions, but before
 * LiveWindow and SmartDashboard integrated updating.
 */
void Robot::RobotPeriodic() 
{
  //Pull updated values from network tables 
  limelight->update_Limelight_Track(); 
  shooter->updateSensors();
  drivetrain->GetHeading();

  //Gyro dashboard update 
  frc::SmartDashboard::PutNumber("Gyro Value", drivetrain->GetHeading() - setZero);

  //Control and mptor prints to the dashboard 
  frc::SmartDashboard::PutNumber("Left joystick input", oi->getLeftStick());
  frc::SmartDashboard::PutNumber("Right joystick input", oi->getRightStick());
  frc::SmartDashboard::PutNumber("Left Drive Encoder", drivetrain->getLeftDrivetrainEncoder());
  frc::SmartDashboard::PutNumber("Right Drive Encoder", drivetrain->getRightDrivetrainEncoder());
  std::cout << "Right Drive Encoder: " << drivetrain->getRightDrivetrainEncoder() << std::endl;
  std::cout << "Left Drive Encoder: " << drivetrain->getLeftDrivetrainEncoder() << std::endl;

  frc::SmartDashboard::PutBoolean("LT pressed", oi->isleftTriggerPressed());
  frc::SmartDashboard::PutBoolean("RT pressed", oi->isRightTriggerPressed());
  frc::SmartDashboard::PutNumber("Intake sensor", intake->getIntakeSensor());

  //Limelight prints to the dashboard 
  frc::SmartDashboard::PutNumber("tx", limelight->limelightTX());
  frc::SmartDashboard::PutNumber("ty", limelight->limelightTY());
  frc::SmartDashboard::PutNumber("ta", limelight->limelightTA());
  frc::SmartDashboard::PutNumber("tv", limelight->limelightTV()); 
  frc::SmartDashboard::PutNumber("Shooter Power", shooterSpeed);

  //frc::SmartDashboard::PutBoolean("Is Motor On?", isMotorOn); 
  //frc::SmartDashboard::PutBoolean("Is Motor off", isMotorOff);
  limelight->limelight_LED_on(); //Force limelights on for regular robot use
  led->Standard();

}


/**
 * This autonomous (along with the chooser code above) shows how to select
 * between different autonomous modes using the dashboard. The sendable chooser
 * code works with the Java SmartDashboard. If you prefer the LabVIEW Dashboard,
 * remove all of the chooser code and uncomment the GetString line to get the
 * auto name from the text box below the Gyro.
 *
 * You can add additional auto modes by adding additional comparisons to the
 * if-else structure below with additional strings. If using the SendableChooser
 * make sure to add them to the chooser code above as well.
 */
void Robot::AutonomousInit() 
{

  // m_autoSelected = SmartDashboard::GetString("Auto Selector",
  //     kAutoNameDefault);
  //std::cout << "Auto selected: " << m_autoSelected << std::endl;
  autoDrive = 75;
  autoDrive2 = 75;
  autoWaitTime = 275;
  setZero = drivetrain->GetHeading();
  drivetrain->AutonomousInit();

  /*if(isInitial){
    rightEncoderValue_initial = drivetrain->getRightDrivetrainEncoder(); 
    leftEncoderValue_initial = drivetrain->getLeftDrivetrainEncoder(); 
    isInitial = false;
}*/
    rightEncoderValue_initial = drivetrain->getRightDrivetrainEncoder(); 
    leftEncoderValue_initial = drivetrain->getLeftDrivetrainEncoder(); 
/*
  m_autoSelected = m_chooser.GetSelected();
  autoPathDirections.clear();
  autoPathNames.clear(); 
  if (m_autoSelected == testPathAuto) 
  {
    autoPathNames.push_back("StraightRedGoal");
    autoPathDirections.push_back(drivetrain->FORWARD);
    auto_state = FOLLOW_PATH_STATE; 
  } else if (m_autoSelected == runTeleop)   
  {
    Robot::TeleopPeriodic(); 
  } 
  else 
  {
    Robot::TeleopPeriodic(); 
  }
  */
}

void Robot::AutonomousPeriodic() 
{

//if (m_autoSelected == testPathAuto)
//{ 
    /*if (autoDrive >= 0)
    {
      drivetrain->tankDrive(.3, .3);
      autoDrive--;
    }
    else if (autoWaitTime >=0)
    {
      drivetrain->tankDrive(0, 0);
      //function that decremnt a value here (once per 20 ms)
      //if value equal 0, evaluates true
      shooter->autoShooterSequence(near, 1);
      autoWaitTime--;
    } 
    else if (autoDrive2 >= 0)
      {
        drivetrain->tankDrive(-.3,-.3);
        autoDrive2--;
      }
      else
      {
        drivetrain->tankDrive(0,0);
      shooter->autoShooterSequence(0, 0);
      }*/
    
//}  
rightEncoderValue = drivetrain->getRightDrivetrainEncoder(); 
leftEncoderValue = drivetrain->getLeftDrivetrainEncoder(); 

/*if(leftEncoderValue <= (leftEncoderValue_initial + 60)){
  drivetrain->tankDrive(0.3, 0.3);
  std::cout << "cout 1: " << leftEncoderValue_initial + 50 << " " << leftEncoderValue << std::endl; 
} else{
  std::cout << "cout 2: " << std::endl; 
  if(isFirstTurn){
    rightEncoderValue_firstTurn = drivetrain->getRightDrivetrainEncoder(); 
    leftEncoderValue_firstTurn = drivetrain->getLeftDrivetrainEncoder();
    isFirstTurn = false; 
  }
  if(isFirstTurnFinished == false){
      drivetrain->tankDrive(0.3, 0.1);
  }
  if(leftEncoderValue >= leftEncoderValue_firstTurn + 180){
    if(isFirstTurnFinished == false){
      leftEncoderValue_firstTurnFinished = drivetrain->getLeftDrivetrainEncoder(); 
      isFirstTurnFinished = true;
    }
    std::cout << "cout 3" << std::endl; 
    if(leftEncoderValue <= leftEncoderValue_firstTurnFinished + 65){
      std::cout << "cout 4" << std::endl;
       drivetrain->tankDrive(0.3, 0.3); 
    } else{
      std::cout << "cout 5" << std::endl;
      if(isSecondTurn){
        rightEncoderValue_secondTurn = drivetrain->getRightDrivetrainEncoder(); 
        isSecondTurn = false; 
      } 
      if(isSecondTurnFinished == false){
          drivetrain->tankDrive(0.1, 0.3); 
      }
      if(rightEncoderValue >= rightEncoderValue_secondTurn + 139){
        if(isSecondTurnFinished == false){
          isSecondTurnFinished = true; 
          rightEncoderValue_secondTurnFinished = drivetrain->getRightDrivetrainEncoder(); 
        }
        if(rightEncoderValue <= rightEncoderValue_secondTurnFinished + 53){
          drivetrain->tankDrive(0.3, 0.3);
        } else{
          if(isThirdTurn){
            isThirdTurn = false; 
            rightEncoderValue_thridTurn = drivetrain->getRightDrivetrainEncoder(); 
          }
          if(isThirdTurnFinsihed == false){
            drivetrain->tankDrive(0.1, 0.3); 
          }
          if(rightEncoderValue >= rightEncoderValue_thridTurn + 95.5){
            if(isThirdTurnFinsihed == false){
              isThirdTurnFinsihed = true; 
              rightEncoderValue_thirdTurnFinished = drivetrain->getRightDrivetrainEncoder(); 
            }
            if(rightEncoderValue <= rightEncoderValue_thirdTurnFinished + 155){
              drivetrain->tankDrive(0.3, 0.3); 
            } else{
              drivetrain->tankDrive(0, 0); 

            }
          }
        }
      }
      rightEncoderValue_secondTurn = drivetrain->getRightDrivetrainEncoder(); 
      leftEncoderValue_secondTurn = drivetrain->getLeftDrivetrainEncoder(); 
      if(leftEncoderValue == leftEncoderValue_secondTurn){
        
      }
    }
  }
}*/

    
if(rightEncoderValue <= rightEncoderValue_initial + 10){
  drivetrain->tankDrive(0.3, 0.3); 
} else{
  if(isFirstTurn){
    rightEncoderValue_firstTurn = drivetrain->getRightDrivetrainEncoder(); 
    isFirstTurn = false; 
  }
  if(isFirstTurnFinished == false){
    drivetrain->tankDrive(0.1, 0.3); 
  }
  if(rightEncoderValue >= rightEncoderValue_firstTurn + 35){
    leftEncoderValue_secondTurn = drivetrain->getLeftDrivetrainEncoder(); 
    isFirstTurnFinished = true; 
    if(leftEncoderValue <= leftEncoderValue_secondTurn + 40){
      drivetrain->tankDrive(0.3, 0.1); 
    } else {
      if(isSecondTurnFinished == false){
        isSecondTurnFinished = true; 
        leftEncoderValue_secondTurnFinished = drivetrain->getLeftDrivetrainEncoder(); 
      }
      if(leftEncoderValue <= leftEncoderValue_secondTurnFinished + 75){
        drivetrain->tankDrive(0.3, 0.3); 
      } else{
        if(isThirdTurn){
          leftEncoderValue_thirdTurn = drivetrain->getLeftDrivetrainEncoder();
          isThirdTurn = false; 
        }
        if(leftEncoderValue <= leftEncoderValue_thirdTurn + 40){
          drivetrain->tankDrive(0.3, 0.1); 
        } else{
          rightEncoderValue_thirdTurnFinished = drivetrain->getRightDrivetrainEncoder(); 
          if(rightEncoderValue <= rightEncoderValue_thirdTurnFinished + 30){
            drivetrain->tankDrive(0.3, 0.3); 
          } else{
            if(isFourthTurn){
              
            }
          }
        }

        
      }
    }   
  }
}
}



/*    drivetrain->tankDrive(limelight->limelightLeftTrack(), limelight->limelightRightTrack());
    if(limelight->limelightLeftTrack() <= .01)
      {
        std::cout << "righttrigerpressed" << std::endl;
        shooter->autoShooterSequence(shooterDefault, oi->isRightTriggerPressed());
      }
      
    }
    
} 
  else 
  {
    drivetrain->stopMotors();
  }
  */



void Robot::AutoStateMachine() 
{ 
    //isPathDone = drivetrain->FollowPath(autoPathDirections[path_count]);

    if(isPathDone == true) 
    { 
      drivetrain->stopMotors();
      auto_state = TELEOP_STATE; 
    } 
}

void Robot::TeleopInit() 
{
  //Zero out encoders on init
    //drivetrain->zeroOutLeftEncoder(); 
    //drivetrain->zeroOutRightEncoder();
    oi->oiInit(); 
    shooterSpeed = -0.5;
    calibrateSpeed = 0.5;
    shooter->bumperSolenoidDefault();
    climber->climberInit(); 
    isMotorOn = false;
    climber->SolenoidForward();
    stopClimberMotors = false;
    countDown = 20;
    countDownStarted = false;
    okToLock = false;
    led->Standard();
    setZero = drivetrain->GetHeading();

}

void Robot::TeleopPeriodic() 
{
  shooter->updateSensors(); 
  shooter->shooterShuffleInfo();
  climber->climberShuffleInfo();
  okLeftUp = true;
  okLeftDown = true;
  okRightUp = true;
  okRightDown = true;
  calibrateShooter = false;


  rightClimbValue = climber->getRightEncoder();
  leftClimbValue = climber->getLeftEncoder();
  shooter->sensorFlip();


  //Controls so far including limelight track
 /*   if (oi->isRightTriggerPressed() == true) 
    { 
      drivetrain->tankDrive(limelight->limelightLeftTrack(), limelight->limelightRightTrack());
      if(limelight->limelightLeftTrack() <= .01)
      {
        std::cout << "righttrigerpressed" << std::endl;
        shooter->autoShooterSequence(shooterDefault, oi->isRightTriggerPressed());
        
      }
    } else 
*/   
    if (oi->isRightTriggerPressed() == true)
    {
      drivetrain->tankDrive(limelight->limelightLeftTrack(), limelight->limelightRightTrack());
    } 
    else
    { 
      drivetrain->tankDrive(oi->getLeftStick(), oi->getRightStick());
    }


    
//done

/*    if(oi->isleftTriggerPressed() == true || oi->isLeftBumperPressed() == true || oi->getControllerRightTrigger()) 
    {
      std::cout << "entered if statement" << std::endl;
      if (oi->getControllerRightTrigger() != true)
      {
      std::cout << "(oi->getControllerRightTrigger()" << std::endl;
        intake->SolenoidReverse();
      }
      if (oi->isLeftBumperPressed() != true || oi->getControllerRightTrigger() == true)
      {
              std::cout << "oi->isLeftBumperPressed() != true || oi->getControllerRightTrigger() == true" << std::endl;
        intake->IntakeMotorRun(oi->getRightJoyTrigger());
      } 
    } else 
    {
      intake->SolenoidForward();
      intake->stopIntakeMotor();
    }
    */
//bumper trigger
//if ( oi->isRightTriggerPressed() != true) 
//{
//  if(oi->isShooterActuatorButtonPressed() == true)
  if(oi->isleftTriggerPressed() == true)
  { 
    intake->SolenoidReverse();
    intake->IntakeMotorRun(oi->getLeftJoyTrigger());
  } else
  {
    intake->SolenoidForward();
    intake->stopIntakeMotor();
  }
//}

//    if(oi->isLeftJoyTBPressed() == true) 
//    {
//      isMotorOff = true;
//      isMotorOn = false; 
//      shooter->shooterMotors(0);
//    }



/*    if(oi->isRightJoyTBPressed() == true) 
    {
      std::cout << "inside robot is right joy tb pressed" << std::endl;
      isMotorOn = true; 
      isMotorOff = false; 
      if(oi->isSpeedUpButtonPressed() == true)
      {
          shooterSpeed -= 0.01; 
      } else if (oi->isSpeedDownButtonPressed() == true)
      {
        shooterSpeed += 0.01; 
      } else { 
        shooterSpeed = shooterSpeed;
      }
      std::cout << "shooter speed" << shooterSpeed << std::endl;
      shooter->shooterMotors(shooterSpeed); //Defaults to 0.5
      shooter->kickerMotorFunction(1);
      shooter->loaderMotorFunction(1);
    } 
*/
//    if(oi->isRightJoyRTBPressed() == true) 
//    { 
//      shooter->kickerMotorFunction(oi->getRightRTB());
//    } 
//    else if(oi->isKickerMotorButtonPressed() == true)
//if ( oi->isRightTriggerPressed() != true) 
//{

   if(oi->isKickerMotorButtonPressed() == true)
    {
      shooter->kickerMotorFunction(1);
    }
    else if (autoShooterActive != true)
    {
      shooter->kickerMotorFunction(0);
    }
//}


//if ( oi->isRightTriggerPressed() != true) 
//{
    if(oi->isShooterMotorButtonPressed() == true && calibrateShooter == false)
    {
      //shooter->shooterMotors(-3400);
      //shooter->shooterMotors(-2625);
      calibrateShooter = true;
      shooter->shooterMotors(-calibrateSpeed); //originally 0.5
    }  
    if(oi->isSpeedUpButtonPressed() == true && calibrateShooter == true)
    {
       calibrateSpeed = calibrateSpeed + 0.0125;
       shooter->shooterMotors(-calibrateSpeed);
       std::cout << "Shooter Motor Speed: " << calibrateSpeed << std::endl;
    }
    else if(oi->isSpeedDownButtonPressed() == true && calibrateShooter == true)
    {
      calibrateSpeed = calibrateSpeed - 0.0125;
      shooter->shooterMotors(-calibrateSpeed);
      std::cout << "Shooter Motor Speed: " << calibrateSpeed << std::endl;
    }
    if(oi->isShooterMotorButtonPressed() == true && calibrateShooter == true)
    {
      calibrateShooter = false; 
    }
    else if(oi->isShooterMotorButtonPressed() == true && calibrateShooter == false)
    {
      shooter->shooterMotors(-0.67); //originally 0.452
    }
    else if ((oi->isRightBumperPressed() != true) && (calibrateShooter == false)) //needed to know if autoshooter active    
    {
      shooter->shooterMotors(0);
    }
    

    
//}   


//if ( oi->isRightTriggerPressed

//if ( oi->isRightTriggerPresse() != true) 
//{

//    if(oi->isRightJoyLTBPressed() == true) 
  /*  if(oi->isAButtonPressed() == true)
    {
      shooter->loaderKicker(1);
    } 
    else if (autoShooterActive != true) //needed to know if autoshooter active
    {
      shooter->loaderKicker(0);
    } */
//}

//    if(oi->isRightTriggerPressed() == true) 
//    {
//      shooter->autoShooterSequence(shooterDefault, oi->getRightBumper());
//    } else if (oi->isRightBumperPressed() == false)
//    {
//      shooter->bumperSolenoidDefault();
//    }d() != true) 
//{
/*    if(oi->isRightBumperPressed() == true)  
    {
      shooter->autoShooterSequence(far, oi->getRightBumper());
    } 
    else if(oi->isBButtonPressed() == true)
    {
      shooter->autoShooterSequence(near, oi->isBButtonPressed());
    } 
    else if (oi->isRightBumperPressed() == false && oi->isAButtonPressed() == false && oi->isBButtonPressed() == false)
    {
      shooter->bumperSolenoidDefault();
    } */

    if(oi->isAButtonPressed() == true && oi->isYButtonPressed() == false && oi->isBButtonPressed() == false && oi->isXButtonPressed() == false)
    {
      shooter->greenZoneAutoFire(near, oi->isAButtonPressed()); 
    } 
    else if(oi->isYButtonPressed() == true && oi->isAButtonPressed() == false && oi->isBButtonPressed() == false && oi->isXButtonPressed() == false) 
    {
      shooter->yellowZoneAutoFire(near, oi->isYButtonPressed()); 
    } 
    else if(oi->isXButtonPressed() == true && oi->isAButtonPressed() == false && oi->isYButtonPressed() == false && oi->isBButtonPressed() == false)
    {
      shooter->blueZoneAutoFire(far, oi->isXButtonPressed());
    }
    else if(oi->isBButtonPressed() == true && oi->isAButtonPressed() == false && oi->isYButtonPressed() == false && oi->isXButtonPressed() == false)
    {
      shooter->redZoneAutoFire(far, oi->isBButtonPressed());
    }
    else if(oi->isAButtonPressed() == false && oi->isYButtonPressed() == false && oi->isXButtonPressed() == false && oi->isBButtonPressed() == false)
    {
      shooter->bumperSolenoidDefault();
      shooter->shooterMotors(0);
      shooter->loaderMotorFunction(0);
    }


//}


/*    if(oi->isBackButtonPressed() == true)
    {
      climber->SolenoidReverse();
      climber->climbDrive(oi->getBackButton() / 2, oi->getBackButton() / 2);
      if(leftClimbValue < -96 || rightClimbValue < -96)
      {
      climber->climbDrive(0, 0);
      }
    } 
    else if(oi->isStartButtonPressed() == true)
    {
      climber->SolenoidReverse();
      climber->climbDrive(oi->getStartButton() / 2, oi->getStartButton() / 2);
      
      if(leftClimbValue < -96 || rightClimbValue < -96)
      {
      climber->climbDrive(0, 0);
      }
    } 
    else if (oi->isLeftDPadPressed() == true)
    {
      rightClimbValue -= 2; 
      leftClimbValue += 2; 
      climber->SolenoidReverse();
      climber->climbDrive(leftClimbValue , rightClimbValue / 2);
      if(rightClimbValue > -2)
      {
        climber->SolenoidReverse();
        climber->climbDrive(leftClimbValue , 0);
      } 
      if(leftClimbValue > -2)
      {
        climber->SolenoidReverse();
        climber->climbDrive(0, rightClimbValue);
      }
    } 
    else if (oi->isRightDPadPressed() == true)
    {
      rightClimbValue += 2; 
      leftClimbValue -= 2;
      climber->SolenoidReverse();
      climber->climbDrive(leftClimbValue / 2, rightClimbValue);
      if(rightClimbValue > -2)
      {
        climber->SolenoidReverse();
        climber->climbDrive(leftClimbValue , 0);
      } 
      if(leftClimbValue > -2)
      {
        climber->SolenoidReverse();
        climber->climbDrive(0, rightClimbValue);
      }
    } 
    else 
    {
      climber->climbDrive(0, 0);
      climber->SolenoidForward();
    }
*/

    /*if((oi->isLeftBumperPressed() == true) || (countDownStarted == true))
    { 
      countDownStarted = true;
      //this will now lock the climber solenoid
      --countDown;
      climber->SolenoidReverse(); //locks lift in place
      if (countDown == 0) 
      {
        climber->climbDrive(0,0);
        stopClimberMotors = true;
        countDownStarted = false;
        countDown = -1;
      }
    }*/


  if (leftClimbValue >= -2)
  {
    okLeftDown = false; 
  }
  else
  {  
    okLeftDown = true;
  }

  if (leftClimbValue <= -96)
  {
    okLeftUp = false;
  }
  else
  {
    okLeftUp = true;
  }

  if(rightClimbValue >= -2)
  {
    okRightDown = false;
  }
  else
  {
    okRightDown = true;
  }

  if(rightClimbValue <= -96)
  {
    okRightUp = false;
  }
  else
  {
    okRightUp = true;
  }

  /*std::cout << "rightClimbValue: " << rightClimbValue << std::endl;
  std::cout << "leftClimbValue: " << leftClimbValue << std::endl;
  if(((okLeftDown == false) && (oi->getXboxLeftStick() > 0)) || ((okLeftUp == false) && (oi->getXboxLeftStick() < 0))) 
  {
    leftMotorValue = 0;
    std::cout << "off left down: " << okLeftDown << " " << oi->getXboxLeftStick() << std::endl;
    std::cout << "off left up: " << okLeftUp <<  " " << oi->getXboxLeftStick() << std::endl;
  }
  else
  {
    //leftMotorValue = oi->getXboxLeftStick();
    std::cout << "on left down: " << okLeftDown << " " << oi->getXboxLeftStick() << std::endl;
    std::cout << "on left up: " << okLeftUp <<  " " << oi->getXboxLeftStick() << std::endl;
  }
  if(((okRightDown == false) && (oi->getXboxRightStick() > 0)) || ((okRightUp == false) && (oi->getXboxRightStick() < 0))) 
  {
    rightMotorValue = 0;
    std::cout << "off right down: " << okRightDown << " " << oi->getXboxRightStick() << std::endl;
    std::cout << "off right up: " << okRightUp <<  " " << oi->getXboxRightStick() << std::endl;
  }
  else
  {
    //rightMotorValue = oi->getXboxRightStick();
    std::cout << "right down: " << okRightDown << " " << oi->getXboxRightStick() << std::endl;
    std::cout << "right up: " << okRightUp <<  " " << oi->getXboxRightStick() << std::endl;
  }
  if (stopClimberMotors != true)
    {
      //climber->climbDrive(leftMotorValue / 4, rightMotorValue / 4);
    }
    */
   if(((okLeftUp == false || okRightUp == false) && oi->getXboxRightStick() < 0) || ((okLeftDown == false || okRightDown == false) && oi->getXboxRightStick() > 0))
   {
     rightMotorValue = leftMotorValue = 0;
   }
   else
   {
     rightMotorValue = leftMotorValue = oi->getXboxRightStick();
   }
   if(stopClimberMotors == false)
   {
     climber->climbDrive(leftMotorValue / 4, rightMotorValue / 4);
   }
  //std::cout << rightClimbValue << " " << leftClimbValue << " " << okToLock << std::endl;
  /*if(rightClimbValue <= -3 || leftClimbValue <= -3)
  {
    okToLock = true;
  }*/
  if(oi->isLeftBumperPressed() == true)
  {
    okToLock = true;
    led->Green();
  }
  if(oi->isLeftJoyTBPressed() == true)
  {
    okToLock = false;
    stopClimberMotors = false;
    climber->SolenoidForward();
    led->Standard();
  }

  if((rightClimbValue > -2 || leftClimbValue > -2) && okToLock == true ) 
  {
    climber->SolenoidReverse();
    stopClimberMotors = true;
    climber->climbDrive(0, 0);
    
  }


     /* if((leftClimbValue > -96 && leftClimbValue <= 0) || (rightClimbValue > -96 && rightClimbValue <= 0))
      {
        std::cout << "Inside climbDrive left and right" << leftClimbValue << " " << rightClimbValue << std::endl;
        std::cout << "Inside climbDrive left and right" << oi->getXboxLeftStick() << " " << oi->getXboxRightStick() << std::endl;
        if ((leftClimbValue == 0 || rightClimbValue == 0) && ((oi->getXboxLeftStick() > 0 ) || (oi->getXboxRightStick() > 0)))
        {
             climber->climbDrive(0, 0);
             std::cout << "Veronika was here" << std::endl;
        } 
        else
        {
          std::cout << "Veronika climbDrive left and right" << leftClimbValue << " " << rightClimbValue << std::endl;
          std::cout << "Veronika climbDrive left and right" << oi->getXboxLeftStick() << " " << oi->getXboxRightStick() << std::endl;
          climber->climbDrive(oi->getXboxLeftStick() / 2, oi->getXboxRightStick() / 2);
        }
      }
      else
      {
        climber->climbDrive(0, 0);
        std::cout << "Motor Stop climbDrive left and right" << leftClimbValue << " " << rightClimbValue << std::endl;
        std::cout << "climbDrive left and right" << oi->getXboxLeftStick() << " " << oi->getXboxRightStick() << std::endl;
      }*/
} 


void Robot::TestPeriodic() {}

#ifndef RUNNING_FRC_TESTS
int main() { return frc::StartRobot<Robot>(); }
#endif