/*#include "subsystem/DriveSubsystem.h"
#include <frc/geometry/Rotation2d.h>
#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>
using namespace DriveConstants; 
DriveSubsystem::DriveSubsystem() 
    : navX{SPI::Port::kMXP},
      m_odometry{frc::Rotation2d(units::degree_t(GetHeading()))} {
          ResetEncoders(); 
      }
void DriveSubsystem::Periodic()
{
    m_odometry.Update(frc::Rotation2d(units::degree_t(GetHeading())),
                    units::meter_t(leftDrive_encoder.GetPosition()),
                    units::meter_t(rightDrive_encoder.GetPosition()));
} 
void DriveSubsystem::tankDrive(double leftValue, double rightValue)
{
    kline_Drive.TankDrive(leftValue, rightValue); 
}
void DriveSubsystem::tankDriveVolts(units::volt_t left, units::volt_t right)
{
    leftMotorGroup.SetVoltage(left); 
    rightMotorGroup.SetVoltage(-right);
    kline_Drive.Feed(); 
}
void DriveSubsystem::ResetEncoders()
{
    leftDrive_encoder.SetPosition(0);
    rightDrive_encoder.SetPosition(0);
}
double DriveSubsystem::getLeftDrivetrainEncoder()
{
    return leftDrive_encoder.GetPosition(); 
}
double DriveSubsystem::getRightDrivetrainEncoder()
{
    return rightDrive_encoder.GetPosition();
}
void DriveSubsystem::setMaxOutput(double maxOutput)
{
    kline_Drive.SetMaxOutput(maxOutput); 
}
double DriveSubsystem::GetHeading()
{
    return std::remainder(navX.GetAngle(), 360);
}
double DriveSubsystem::GetTurnRate()
{
    return navX.GetRate(); 
}
frc::Pose2d DriveSubsystem::GetPose()
{
    return m_odometry.GetPose();
}
frc::DifferentialDriveWheelSpeeds DriveSubsystem::GetWheelSpeeds()
{
    return {units::meters_per_second_t(leftDrive_encoder.GetVelocity()),
            units::meters_per_second_t(rightDrive_encoder.GetVelocity())};
}
void DriveSubsystem::resetOdometry(frc::Pose2d pose)
{
    ResetEncoders();
    m_odometry.ResetPosition(pose, frc::Rotation2d(units::degree_t(GetHeading())));
} */