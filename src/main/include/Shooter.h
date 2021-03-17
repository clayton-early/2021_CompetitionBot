#pragma once 

#include <iostream> 
#include <rev/CANSparkMax.h> 
#include "math.h" 
#include <frc/AnalogInput.h>
#include <frc/smartdashboard/SmartDashboard.h> 
#include <frc/DoubleSolenoid.h>
#include <frc2/Timer.h>

class Shooter{ 
    public: 
        //Space for motor ID assignment 

        static Shooter *GetInstance();

        void updateSensors(); 
        void sensorFlip();
        void shooterShuffleInfo(); 
        void shooterMotors(double motor_value); 
        void SolenoidForward();
        void SolenoidReverse();
        void kickerMotorFunction(double MV);
        void loaderMotorFunction(double motorValue);
        void autoShooterSequence(int distance, double buttonInput); 
        void loaderKicker(bool enable);
        void bumperSequence(); 
        void bumperSolenoidDefault();
        void autoLoaderSequence(double buttonInput);

        //Shooting zone presets. 
        void greenZoneAutoFire(int distance, double buttonInput);
        void yellowZoneAutoFire(int distance, double buttonInput);
        void blueZoneAutoFire(int distance, double buttonInput);
        void redZoneAutoFire(int distance, double buttonInput); 

    private: 

        static Shooter *s_instance; 

        Shooter(); 

        //Object pointers
        rev::CANSparkMax *leftShooter;
        rev::CANSparkMax *rightShooter;
        rev::CANSparkMax *kickerMotor; 
        rev::CANSparkMax *loaderMotor;

        rev::CANEncoder *rightShooterEncoder;
        rev::CANEncoder *leftShooterEncoder; 
        
        frc::AnalogInput *intake_sensor; 
        frc::AnalogInput *ascent_sensor; 
        frc::AnalogInput *shooter_sensor; 

        frc2::Timer *sensorFlipTimer; 
        frc2::Timer *bumperTimer; 
        frc2::Timer *delayTimer; 
        frc::DoubleSolenoid *bumperSolenoid; 
        frc::DoubleSolenoid *shooterDistanceControlSolenoid;
       const rev::CANSparkMax::MotorType BRUSHLESS = rev::CANSparkMax::MotorType::kBrushless; 

       const int INTAKE_S_PORT = 0; //0 
       const int ASCENT_S_PORT = 2;
       const int SHOOTER_S_PORT = 3;

       const int LEFT_SHOOTER_ID = 11; 
       const int RIGHT_SHOOTER_ID = 12; 
       const int KICKER_ID = 14; 
       const int LOADER_ID = 13;
       const int near = 1;
       const int far = 2;
       double const shooterDefault = -.67;
       double const shooterLowDefault = -.5;
       double intake_s_value; 
       double ascent_s_value; 
       double shooter_s_value; 

       double leftRPM; 
       double rightRPM; 
       int delay = 0;

       bool bumperTimerOn = false;
       bool delayTimerOn = false;
       bool okToStartSequence = false;
       bool okToStartDelay = false;
       bool isTimerInProgress = false; 

       double const greenPower = -.425; 
       double const yellowPower = -.4425;
       double const bluePower = -.70; 
       double const redPower = -.725;  

};