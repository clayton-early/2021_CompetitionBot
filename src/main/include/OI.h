#pragma once 

#include <iostream> 
#include <rev/CANSparkMax.h> 
#include "math.h"
#include <frc/Joystick.h>
#include <frc/XboxController.h>

class OI{ 
    public: 
    //Get Instance of OI class
        static OI *GetInstance();

        double getRightStick(); 
        double getLeftStick();
        double getXboxLeftStick();
        double getXboxRightStick();
        double getLeftJoyTrigger();
        double getRightJoyTrigger();
        double getRightRTB();
        double getRightLTB();
        double getRightBumper(); 
        double getStartButton(); 
        double getBackButton();
        double getRightDPad();
        double getLeftDPad();
        double getLeftBumper();

        bool isleftTriggerPressed();
        bool isRightTriggerPressed();
        bool isDPadUpPressed();
        bool isRightJoyTBPressed(); 
        bool isLeftJoyTBPressed(); 
        bool isRightJoyRTBPressed(); 
        bool isRightJoyLTBPressed(); 
        bool loaderButtonPress();
        bool isRightBumperPressed(); 
        bool getControllerRightTrigger();
        bool isKickerMotorButtonPressed();
        bool isShooterMotorButtonPressed();
        bool isShooterActuatorButtonPressed();
        bool isBackButtonPressed();
        bool isStartButtonPressed();
        bool isRightDPadPressed();
        bool isLeftDPadPressed();
        bool isLeftBumperPressed();
        bool isAButtonPressed();
        bool isBButtonPressed();
        bool isXButtonPressed(); 
        bool isYButtonPressed(); 

        double getSpeedUp(); 
        double getSpeedDown(); 
        bool isSpeedUpButtonPressed(); 
        bool isSpeedDownButtonPressed(); 

        int DPadUp = 0; 
        int DPadRight = 90; 
        int DPadDown = 180; 
        int DPadLeft = 270; 

        bool isMotorOn = false;
        bool isMotorOff = false;  
        bool isAscentOn = false; 
        bool isKickerOn = false; 

        double leftCurrentValue = 0;
        double rightCurrentValue = 0;

        void oiInit(); 



    private: 
        static OI *s_instance; 

        OI();

        //Make objects of controller types used with names of controller 
        frc::Joystick *leftStick; 
        frc::Joystick *rightStick; 
        frc::XboxController *controller;  
        

};