//#include <frc/kinematics/DifferentialDriveKinematics.h>
//#include <frc/trajectory/constraint/DifferentialDriveKinematicsConstraint.h>
#include <units/units.h>
#include <wpi/math>

#pragma once 

namespace DriveConstants 
    {
      constexpr auto kTrackwidth = 0.2804_m;
     // extern const frc::DifferentialDriveKinematics kDriveKinematics;

      static constexpr auto kS = 0.126_V;  
      static constexpr auto kV = 0.0603 * 1_V * 1_s / 1_m;
      static constexpr auto kA = 0.007 * 1_V * 1_s * 1_s / 1_m;
      static constexpr double kPDriveVelocity = 0.747;

    }

/*namespace AutoConstants 
    {
      constexpr auto kMaxSpeed = 3_mps;
      constexpr auto kMaxAcceleration = 3_mps_sq;
      // Reasonable baseline values for a RAMSETE follower in units of meters and seconds 
      constexpr double kRamseteB = 2;
      constexpr double kRamseteZeta = 0.7;
    }
#pragma once */