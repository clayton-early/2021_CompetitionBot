//#include <RobotContainer.h>

//include "Constants.h"


/*RobotContainer::RobotContainer()
{
} 
   
   
    frc2::Command* RobotContainer::GetAutonomousCommand(std::string pathName) {
    frc::DifferentialDriveVoltageConstraint autoVoltageConstraint( 
        frc::SimpleMotorFeedforward<units::meters>(DriveConstants::kS, DriveConstants::kV, DriveConstants::kA), DriveConstants::kDriveKinematics, 10_V);
    frc::TrajectoryConfig TrajectoryConfig((units::meters_per_second_t) AutoConstants::kMaxSpeed, 
                                           (units::meters_per_second_squared_t) AutoConstants::kMaxAcceleration);
    TrajectoryConfig.SetKinematics(DriveConstants::kDriveKinematics);
    TrajectoryConfig.AddConstraint(autoVoltageConstraint); 
    wpi::SmallString<64> deployDirectory;
    frc::filesystem::GetDeployDirectory(deployDirectory);
    wpi::sys::path::append(deployDirectory, "output");
    wpi::sys::path::append(deployDirectory, "YourPath.wpilib.json");
    frc::Trajectory trajectory = frc::TrajectoryUtil::FromPathweaverJson(deployDirectory);
    frc2::RamseteCommand ramseteCommand(
        trajectory, [this]() { return kline_Drive.GetPose(); },
        frc::RamseteController(AutoConstants::kRamseteB,
                               AutoConstants::kRamseteZeta),
        frc::SimpleMotorFeedforward<units::meters>(
            DriveConstants::kS, DriveConstants::kV, DriveConstants::kA),
        DriveConstants::kDriveKinematics, 
        [this] { return kline_Drive.GetWheelSpeeds(); }, 
        frc2::PIDController(DriveConstants::kPDriveVelocity, 0, 0), 
        frc2::PIDController(DriveConstants::kPDriveVelocity, 0, 0), 
        [this](auto left, auto right) { kline_Drive.tankDriveVolts(left, right); }, 
        {&kline_Drive});
    return new frc2::SequentialCommandGroup(
        std::move(ramseteCommand), 
        frc2::InstantCommand([this] { kline_Drive.tankDriveVolts(0_V, 0_V); }, {}));  
    
} */