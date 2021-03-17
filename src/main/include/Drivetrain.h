#pragma once 

#include "math.h"

#include <iostream> 

#include "frc/Timer.h"

#include <rev/CANSparkMax.h>

#include <rev/SparkMax.h> 

#include <frc/TimedRobot.h> 

#include "AHRS.h"

#include <frc/Filesystem.h> 

#include <frc/trajectory/TrajectoryUtil.h>

#include <wpi/Path.h>

#include <wpi/SmallString.h>

#include <units/units.h>

#include <frc/kinematics/DifferentialDriveOdometry.h>

#include <frc/drive/DifferentialDrive.h>

#include <frc/geometry/Pose2d.h>

#include <frc/geometry/Rotation2d.h>

#include <frc/kinematics/DifferentialDriveWheelSpeeds.h>

#include <frc/smartdashboard/SmartDashboard.h>

#include <frc/smartdashboard/SendableChooser.h>

#include <frc/SpeedControllerGroup.h>

#include <frc/trajectory/constraint/DifferentialDriveVoltageConstraint.h>

#include <frc/trajectory/TrajectoryConfig.h>

#include <frc/controller/SimpleMotorFeedforward.h>

//#include <frc2/command/CommandScheduler.h>

//#include <frc2/command/Command.h>

//#include <frc2/command/InstantCommand.h>

//#include <frc2/command/PIDCommand.h>

//#include <frc2/command/ParallelRaceGroup.h>

//#include <frc2/command/RunCommand.h>

//#include <frc2/command/RamseteCommand.h>

//#include <frc2/command/SequentialCommandGroup.h>

#include <frc/trajectory/TrajectoryGenerator.h>

using namespace frc; 

class Drivetrain 
{ 
    public: 
    Drivetrain();
        //Set ID values to names according to motor 
        int FRONT_RIGHT = 1;
        int FRONT_LEFT = 2; 
        //int MID_LEFT = 2;
        //int MID_RIGHT = 4;
        int REAR_RIGHT = 5;
        int REAR_LEFT = 3;

        int stop = 0; 
        int rotation = -12; //Encoder value for one full rotation
        double pi = 3.14; 

        const bool FORWARD = false;

        static Drivetrain *GetInstance();


/**
 * Drives the robot using tank drive controls 
 * 
 * 
 * @param leftValue controls the left side input 
 * @param rightValue controls the right side input 
 */
    void tankDrive(double leftValue, double rightValue);

/**
 * Calls Motors to stop when running a routing
 * 
 * @return 0 to input for all motors 
 */
    void stopMotors();

/**
 * Resets the drive encoders to read a potition of 0
 */
    void resetEncoders();

/**
 * Gets the value of the left encoder on the drive
 * 
 * @returns the value of the left encoder 
 */
    double getLeftDrivetrainEncoder();

/**
 * Gets the value of the right encoder on the drive 
 * 
 * @returns the value of the right encoder 
 */ 
    double getRightDrivetrainEncoder();

/**
 * Gets the heading of the robot 
 * 
 * @returns the heading in degrees from 180 - 180
 */
    double GetHeading();

/**
 * Sets the value of the right encoder to 0 on teleop init
 * 
 * @returns 0 to set to the right encoder 
 */
    rev::CANError zeroOutRightEncoder(); 

/**
 * Sets the value of the left encoder to 0 on teleop init
 * 
 * @returns 0 to set to the left encoder 
 */
    rev::CANError zeroOutLeftEncoder();


/**
 * Gets the velocity of the left encoder 
 * 
 * @return the value of velocity for left side 
 */ 
    double GetLeftVelocity(); 

/**
 * Gets the velocity of the right encoder 
 * 
 * @return the value of velocity for the right side 
 */
    double GetRightVelocity(); 
    
/**
 * Pulls pathfinder path from json file and assigns to trajectory 
 * 
 * 
 * @returns the json file the desired path is located in 
 */ 
    void Get_Trajectory_JSON_File(std::string name);

/**
 * Zeros yaw on auto init
 * 
 * @returns 0 for gyro yaw
 */ 
    void AutonomousInit();

/**
 * Will be called periodically whenever in robot periodic
 */
    void DrivetrainPeriodic(); 

    
    private: 
        static Drivetrain *s_instance;

        //Drivetrain();

    //Make objects of rev spark max with names according to motors
        //rev::CANSparkMax *m_midLeft;
        rev::CANSparkMax *m_frontLeft;
        rev::CANSparkMax *m_rearLeft;
        rev::CANSparkMax *m_rearRight;
        //rev::CANSparkMax *m_midRight;
        rev::CANSparkMax *m_frontRight;



    //Make objects of rev encoders with names according to side
        rev::CANEncoder *rightDrive_encoder; 
        rev::CANEncoder *leftDrive_encoder;  

        frc::TrajectoryConfig *trajConfig; 

        frc::Trajectory trajectory; 

    

        static constexpr double kEncoderDistancePerPule = 12; 
       
       static double heading;
       int follow_path_counter;

       double leftVelocity = 0; 
       double rightVelocity = 0;
       double gyro_heading;
       double desiredHeading;
       double angleDifference;  
       double turnAdjustment;

       //static constexpr auto kTrackwidth = 0.2804_m;  

       const rev::CANSparkMax::MotorType BRUSHLESS = rev::CANSparkMax::MotorType::kBrushless;
       const rev::CANSparkMax::MotorType BRUSHED = rev::CANSparkMax::MotorType::kBrushed;
       const rev::CANSparkMax::IdleMode COAST = rev::CANSparkMax::IdleMode::kCoast;
       const rev::CANSparkMax::IdleMode BRAKE = rev::CANSparkMax::IdleMode::kBrake;
 

        //Gyro
        AHRS *navX;


        //Odometry 
        frc::DifferentialDriveOdometry *m_odometry;

        //Pathfinding 
         int left_traj_length = 0; 
         int right_traj_length = 0; 
        
         int length; 

        //Segment leftTrajectory[750];
        //Segment rightTrajectory[750];

       const double PATH_CUTOFF_TIME = 0.25; 

        frc::SpeedControllerGroup *leftMotorGroup;
        frc::SpeedControllerGroup *rightMotorGroup;

        //frc::DifferentialDrive kline_Drive{*leftMotorGroup, *rightMotorGroup}; 
        frc::DifferentialDrive *kline_Drive;
    

};