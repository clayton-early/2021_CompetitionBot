#pragma once

#include <iostream>
#include <rev/CANSparkMax.h>
#include "math.h"
#include <frc/smartdashboard/SmartDashboard.h>
#include <frc/DoubleSolenoid.h>


class Climber{
    public:
        int LEFT_CLIMBER = 15;
        int RIGHT_CLIMBER = 16;
        frc::DoubleSolenoid *lockingSolenoid;
        static Climber *GetInstance();

        void climbDrive(double left, double right);
        void climberShuffleInfo(); 
        double getRightEncoder();
        double getLeftEncoder();
        void updateClimberShuffleInfo();
        void climberInit();
        void zeroOutClimbCoders(); 
        void SolenoidForward(); 
        void SolenoidReverse(); 
        void SolenoidOff();

    private:
        static Climber *s_instance;

        Climber();

        rev::CANSparkMax *leftClimbMotor;
        rev::CANSparkMax *rightClimbMotor;

        rev::CANEncoder *rightClimbEncoder;
        rev::CANEncoder *leftClimbEncoder;

        

        const rev::CANSparkMax::MotorType BRUSHLESS = rev::CANSparkMax::MotorType::kBrushless;

        double leftPos; 
        double rightPos;

};