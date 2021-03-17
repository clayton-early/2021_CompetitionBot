#pragma once

#include <frc/ADXRS450_Gyro.h>
#include <frc/Encoder.h>
#include <frc/PWMVictorSPX.h>
#include <frc/SpeedControllerGroup.h>
#include <frc/drive/DifferentialDrive.h>
#include <frc/geometry/Pose2d.h>
#include <frc/kinematics/DifferentialDriveOdometry.h>
//#include <frc2/command/SubsystemBase.h>
#include <units/units.h>
#include <rev/CANSparkMax.h>
/*include <rev/SparkMax.h>
#include <AHRS.h>
#include "Constants.h"
class DriveSubsystem : public frc2::SubsystemBase {
 public:
  DriveSubsystem();
   
    Will be called periodically whenever the CommandScheduler runs.
   
  void Periodic() override;
  
  Drives the robot using tank drive controls 
  
  
  @param leftValue controls the left side input 
  @param rightValue controls the right side input 
 
    void tankDrive(double leftValue, double rightValue);
 Controls each side of drive directly with velocity inputs
  
  @param left commands the left outputn
  @param right commands thr right output
 
    void tankDriveVolts(units::volt_t left, units::volt_t right); //Must change to units::Velocity 
 
   Resets the drive encoders to currently read a position of 0.
   
  void ResetEncoders();
  
    Gets the average distance of the TWO encoders.
    @return the average of the TWO encoder readings
   
  double GetAverageEncoderDistance();
  
 Sets max output of the drive, useful to make the drive slower
  @param maxOutput is the maximum output the drive will be limited to 
 
    void setMaxOutput(double maxOutput);
  Resets the odometry to the specified pose 
 
 @param pose is the pose that is set to the odometry
 
    void resetOdometry(frc::Pose2d pose);
 Gets the value of the left encoder on the drive
 
 @returns the value of the left encoder 
 
    double getLeftDrivetrainEncoder();
 Gets the value of the right encoder on the drive 
 
 @returns the value of the right encoder 
 
    double getRightDrivetrainEncoder();
 Returns the heading of the robot.
   
   @return the robot's heading in degrees, from 180 to 180
   
  double GetHeading();
 
    Returns the turn rate of the robot.
   
 @return The turn rate of the robot, in degrees per second
   
  double GetTurnRate();
 
    Returns the currently-estimated pose of the robot.
   
    @return The pose.
   
  frc::Pose2d GetPose();
  
    Returns the current wheel speeds of the robot.
   
   @return The current wheel speeds.
   
  frc::DifferentialDriveWheelSpeeds GetWheelSpeeds();
private: 
    rev::CANSparkMax m_frontLeft{6, BRUSHLESS};
    rev::CANSparkMax m_midLeft {2, BRUSHLESS};
    rev::CANSparkMax m_rearLeft {3, BRUSHLESS};
    rev::CANSparkMax m_frontRight {1, BRUSHLESS};
    rev::CANSparkMax m_midRight {4, BRUSHLESS};
    rev::CANSparkMax m_rearRight {5, BRUSHLESS};
    frc::SpeedControllerGroup leftMotorGroup{m_rearLeft, m_midLeft, m_frontLeft};
    frc::SpeedControllerGroup rightMotorGroup{m_rearRight, m_midRight, m_frontRight};
    frc::DifferentialDrive kline_Drive{leftMotorGroup, rightMotorGroup};
    //Gyro
    AHRS navX;
    frc::DifferentialDriveOdometry m_odometry; 
    const rev::CANSparkMax::MotorType BRUSHLESS = rev::CANSparkMax::MotorType::kBrushless;
    rev::CANEncoder rightDrive_encoder{m_frontLeft}; 
    rev::CANEncoder leftDrive_encoder{m_frontRight}; 
}; 
*/