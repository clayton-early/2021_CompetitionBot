#pragma once 

#include <iostream> 

#include "math.h"

#include <frc/smartdashboard/SmartDashboard.h>

#include <networktables/NetworkTable.h> 

#include <networktables/NetworkTableInstance.h>

class LL { 
    public: 

    static LL *GetInstance(); 

    void update_Limelight_Track(); 
    void limelight_LED_blink(); 
    void limelight_LED_on();

    double limelightTX(); 
    double limelightTY(); 
    double limelightTV();
    double limelightTA(); 
    double limelightLeftTrack(); 
    double limelightRightTrack();

    bool limeLightHasTarget();

    struct limelight_steer_update 
    { 
        const double min_steer;
        const double max_steer;
        double heading_error;
        double rightTurnCommand;
        double leftTurnCommand;
        const double kP;
        float steering_adjust; 
    };

    struct limelight_drive_update 
    { 
        const double min_drive;
        const double DESIRED_TARGET_AREA;
        const double max_drive;
        float kpDistance; 
        double driving_adjust;
        float distance_error;
    };

    double leftMotorValue; 
    double rightMotorValue; 

     
    private: 

    static LL *s_instance; 

    LL();

    
//Define table to pull values from -- uses limelight name to get proper table
std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");

//Set all needed limelight values into variables to be used throughout limelight.cpp
    double tx = table->GetNumber("tx", 0.0); 
    double ty = table->GetNumber("ty", 0.0); 
    double ta = table->GetNumber("ta", 0.0); 
    double tv = table ->GetNumber("tv", 0.0); 
    


};