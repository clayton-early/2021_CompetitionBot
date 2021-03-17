/*----------------------------------------------------------------------------*/
/* Copyright (c) 2017-2018 FIRST. All Rights Reserved.                        */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in the root directory of */
/* the project.                                                               */
/*----------------------------------------------------------------------------*/

#pragma once

#include <string>

#include <array>

#include <frc/TimedRobot.h>

#include <frc/smartdashboard/SendableChooser.h>

#include <iostream>

#include <frc/TimedRobot.h>

#include <frc/smartdashboard/SmartDashboard.h> 

#include <wpi/math>

#include <frc/Compressor.h>


#include "Drivetrain.h"
#include "Climber.h"
#include "OI.h"
#include "LL.h"
#include "LED.h"
#include "Intake.h"
#include "Shooter.h"


class Robot : public frc::TimedRobot {
 public:
 //Distinquish the sides of the joystick
  const frc::XboxController::JoystickHand LEFT_HAND = frc::XboxController::JoystickHand::kLeftHand;
  const frc::XboxController::JoystickHand RIGHT_HAND = frc::XboxController::JoystickHand::kRightHand;


  bool isPathDone; 
  bool calibrateShooter; 

  double calibrateSpeed;
  double setZero;
  const int near = 1;
  const int far = 2;


 
 
  void RobotInit() override;
  void RobotPeriodic() override;
  void AutonomousInit() override;
  void AutonomousPeriodic() override;
  void TeleopInit() override;
  void TeleopPeriodic() override;
  void TestPeriodic() override;


  /**
   * @brief follows path 
   * 
   * to be added: 
   * Drive by limelight implementation
   * 
   * 
   * 
   */ 
      void AutoStateMachine(); 

      //frc2::Command* GetAutonomousCommand(std::string pathName);

      //static frc::DifferentialDriveKinematics kDriveKinematics((units::meter_t) 0.2804);
      


 private:
  frc::SendableChooser<std::string> m_chooser;
  const std::string runTeleop = "Run Teleop Rather than Auto";
  const std::string barrelRacingPath = "Barrel Race";
  std::string m_autoSelected;

//Make objects of the other classes
  Drivetrain *drivetrain;
  Climber *climber;
  OI *oi;
  LL *limelight; 
  LED *led; 
  Intake *intake;  
  Shooter *shooter;

  std::vector<std::string> autoPathNames;
  std::vector<bool> autoPathDirections; 

  bool isMotorOn = false; 
  bool isMotorOff = true; 
  bool okLeftUp = false;
  bool okLeftDown = false;
  bool okRightUp = true;
  bool okRightDown = true;
  bool stopClimberMotors = false;
  double leftMotorValue = 0;
  double rightMotorValue = 0;
  double countDown = 20;
  double autoDrive = 75;
  double autoDrive2 = 75;
  double autoWaitTime = 275;
  double rightEncoderValue_initial;
  double leftEncoderValue_initial;
  double rightEncoderValue_firstTurn; 
  double leftEncoderValue_firstTurn;
  double leftEncoderValue_firstTurnFinished;  
  double rightEncoderValue_secondTurn; 
  double rightEncoderValue_secondTurnFinished; 
  double leftEncoderValue_secondTurn; 
  double leftEncoderValue_secondTurnFinished; 
  double rightEncoderValue_thridTurn; 
  double rightEncoderValue_thirdTurnFinished; 
  double leftEncoderValue_thirdTurn; 
  double leftEncoderValue_thirdTurnFinished; 
  double rightEncoderValue; 
  double leftEncoderValue; 
  bool autoShooterActive = false;
  bool countDownStarted = false;
  bool okToLock = false;
  bool isFirstTurn = true;
  bool isFirstTurnFinished = false; 
  bool isSecondTurn = true; 
  bool isSecondTurnFinished = false; 
  bool isThirdTurn = true; 
  bool isThirdTurnFinsihed = false; 
  bool isFourthTurn = true; 
  bool isFourthTurnFinished = false; 
  
//Auto paths 
  int path_count = 0;
  double leftClimbValue; 
  double rightClimbValue;

  enum auto_states
  { 
    FOLLOW_PATH_STATE,
    TELEOP_STATE 
  };

  enum auto_states auto_state; 

  double shooterSpeed = -0.5; 

    static constexpr double kMaxSpeed = 0.3; 
    static constexpr double kMaxAcc = 0.3; 

  // Have it null by default so that if testing teleop it
  // doesn't have undefined behavior and potentially crash.
  //frc2::Command* m_autonomousCommand = nullptr;

  //RobotContainer m_container; 

  

};