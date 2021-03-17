#include "Drivetrain.h"
#include "Constants.h"
Drivetrain *Drivetrain::s_instance = 0;

//Static Singleton Method
Drivetrain *Drivetrain::GetInstance()
{
    if (s_instance == 0)
    {
        s_instance = new Drivetrain();
    }
    return s_instance;
    
}

//Constructor
Drivetrain::Drivetrain() 
{
    //Get new instance of spark object and set ID and motor type
        m_frontRight = new rev::CANSparkMax{FRONT_RIGHT, BRUSHLESS};
        m_frontLeft = new rev::CANSparkMax{FRONT_LEFT, BRUSHLESS};

        //m_midLeft = new rev::CANSparkMax{MID_LEFT, BRUSHLESS};
        //m_midRight = new rev::CANSparkMax{MID_RIGHT, BRUSHLESS};

        m_rearLeft = new rev::CANSparkMax{REAR_LEFT, BRUSHLESS}; 
        m_rearRight = new rev::CANSparkMax{REAR_RIGHT, BRUSHLESS}; 

       // rev::CANEncoder rightDrive_encoder = m_frontRight->GetEncoder();
       // rev::CANEncoder leftDrive_encoder = m_frontLeft->GetEncoder(); 

       rightDrive_encoder = new rev::CANEncoder(*m_frontRight); 
       leftDrive_encoder = new rev::CANEncoder(*m_frontLeft);

        navX = new AHRS(SPI::Port::kMXP);
       // navX = new AHRS(SPI::Port::kMXP);
        //m_odometry = new frc::DifferentialDriveOdometry(frc::Rotation2d(units::degree_t(GetHeading())));

       // leftMotorGroup = new frc::SpeedControllerGroup{*m_rearLeft, *m_midLeft, *m_frontLeft};
        //rightMotorGroup = new frc::SpeedControllerGroup{*m_rearRight, *m_midRight, *m_frontRight};

        //kline_Drive = new frc::DifferentialDrive{*leftMotorGroup, *rightMotorGroup};

        //trajConfig = new frc::TrajectoryConfig(DriveConstants::kMaxSpeed, DriveConstants::kMaxAcc); 

    //Motor inversions for drivetrain
        m_rearLeft->SetInverted(true);
        //m_midLeft->SetInverted(true);
        m_frontLeft->SetInverted(true);
        m_frontRight->SetInverted(false);
        //m_midRight->SetInverted(false);
        m_rearRight->SetInverted(false);

}

//Public Methods
//----------------------------------\\**

//Tank Drive method 
void Drivetrain::tankDrive(double leftValue, double rightValue)
{
    m_frontRight->Set(rightValue);
    m_frontLeft->Set(leftValue); 
    //m_midLeft->Set(leftValue);
    //m_midRight->Set(rightValue); 
    m_rearRight->Set(rightValue);
    m_rearLeft->Set(leftValue);     

    //std::cout << rightValue << "RightV" << std::endl;
}

//Get encoder values for both sides of drivetrain       
double Drivetrain::getLeftDrivetrainEncoder() 
{ 
    return leftDrive_encoder->GetPosition();
}

double Drivetrain::getRightDrivetrainEncoder() 
{ 
    return rightDrive_encoder->GetPosition();
}

//Set both encoders to 0 for proper tuning 
rev::CANError Drivetrain::zeroOutRightEncoder()
{ 
    return (rightDrive_encoder->SetPosition((double) 0.0 ));
}

rev::CANError Drivetrain::zeroOutLeftEncoder() 
{  
    return (leftDrive_encoder->SetPosition((double) 0.0));
}

double Drivetrain::GetLeftVelocity()
{
    return leftDrive_encoder->GetPosition();
}

double Drivetrain::GetRightVelocity() 
{
    return rightDrive_encoder->GetVelocity(); 
}

//Stop all motors | Used in auto calls 
void Drivetrain::stopMotors() 
{ 
    m_frontLeft->Set(stop);
    m_frontRight->Set(stop);
    //m_midLeft->Set(stop);
    //m_midRight->Set(stop); 
    m_rearRight->Set(stop);
    m_rearLeft->Set(stop); 
}

double Drivetrain::GetHeading()
{ 
    return std::remainder(navX->GetAngle(), 360);
    //return 0;
}

/*std::string Drivetrain::Get_Trajectory_file(std::string name) 
{ 
    std::cout << "Enter Get Trajectory File" << std::endl;
    wpi::SmallString<256> path;
    frc::filesystem::GetDeployDirectory(path);
    std::cout << path << "GTF before append" << std::endl;
    wpi::sys::path::append(path, "PathWeaver/Paths", name + ".pf1.csv");
    std::cout << path << "GTF after append" << std::endl;
    std::cout << path.c_str() << std::endl;
    return std::string(path.c_str());
       
    std::cout << "Exit Get Trajectory File" << std::endl;
} */

void Drivetrain::Get_Trajectory_JSON_File(std::string name)
{ 
    wpi::SmallString<64> path; 
    frc::filesystem::GetDeployDirectory(path);
    wpi::sys::path::append(path, "output", name + ".wpilib.json");


    trajectory = frc::TrajectoryUtil::FromPathweaverJson(path);
}

void Drivetrain::AutonomousInit() 
{ 
    navX->ZeroYaw(); 
}


/*void Drivetrain::DrivetrainPeriodic() 
{ 
    m_odometry->Update(frc::Rotation2d(units::degree_t(GetHeading())),
                    units::meter_t(leftDrive_encoder->GetPosition()),
                    units::meter_t(rightDrive_encoder->GetPosition()));
}*/

void Drivetrain::resetEncoders() 
{ 
    leftDrive_encoder->SetPosition(0);
    rightDrive_encoder->SetPosition(0);
}