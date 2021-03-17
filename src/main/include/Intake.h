#pragma once 

#include <iostream> 
#include <rev/CANSparkMax.h>
#include "math.h"
#include "frc/AnalogInput.h"
#include <ctre/Phoenix.h>
#include <frc/DoubleSolenoid.h>
#include <frc/Compressor.h>

class Intake { 
    public: 
        //Motor ID setup

    static Intake *GetInstance(); 

    int getIntakeSensor(); 
    void IntakeMotorRun(double motorValue);
    void stopIntakeMotor(); 
    //void loaderMotorRun(double motorValue);
    void SolenoidForward(); 
    void SolenoidReverse(); 
    void SolenoidOff(); 

    int INTAKE_ID = 10;
    int LOADER_ID = 13; 

    const rev::CANSparkMax::MotorType BRUSHLESS = rev::CANSparkMax::MotorType::kBrushless;




    private: 
        static Intake *s_instance; 

        Intake();

        frc::AnalogInput ballDetector{1}; 

        TalonSRX *IntakeMotor; 
        rev::CANSparkMax *loaderMotor; 
        frc::DoubleSolenoid *intakeSolenoid; 

};