#include "OI.h" 

OI *OI::s_instance = 0; 

//Static Singleton Method 
OI *OI::GetInstance() { 
    if (s_instance == 0){ 
        s_instance = new OI();
    }
        return s_instance;
}

//Constructor
OI::OI(){ 
    //Get new instance of controller objects with ID's of the usb port they are plugged in to
    leftStick = new frc::Joystick{0}; 
    rightStick = new frc::Joystick{1};
    controller = new frc::XboxController{2};

}

//Public Methods
//----------------------------------\\**

//Get and return joystick value of appropriate side 
double OI::getRightStick() { 
    if(rightCurrentValue != rightStick->GetY())
    {
        rightCurrentValue = rightStick->GetY() / 5 + rightCurrentValue;
    }
    return -(rightStick->GetY());
}

double OI::getLeftStick() { 
    if(leftCurrentValue != leftStick->GetY())
    {
        leftCurrentValue = leftStick->GetY() / 5 + leftCurrentValue;
    }
    return -(leftStick->GetY());
}

double OI::getXboxLeftStick() {
    if(abs(controller->GetY(frc::XboxController::kLeftHand)) > .018) 
    {
        return (controller->GetY(frc::XboxController::kLeftHand) * 0.75);
    }
    else
    {
        return (0);
    }
    
}

double OI::getXboxRightStick() { 
    if(abs(controller->GetY(frc::XboxController::kRightHand)) > .13) 
    {
        return (controller->GetY(frc::XboxController::kRightHand) * 0.75);
    }
    else
    {
        return (0);
    }
}

//Get and return joystick trigger of appropriate side 
double OI::getRightJoyTrigger() 
{ 
    return rightStick->GetTrigger();
}

double OI::getLeftJoyTrigger()
{ 
    return leftStick->GetTrigger();
}

//Check to see if joystick triggers are being pressed 
bool OI::isleftTriggerPressed() 
{ 
    if(leftStick->GetTrigger()) { 
        return true; //Left joystick trigger is being pressed
    } else {
        return false; 
    }
     
    if (leftStick->GetTriggerReleased()) { 
        return false; //Left joystick trigger is not pressed 
    }
    
} 

bool OI::isRightTriggerPressed()
{ 
    if(rightStick->GetTrigger()) 
    { 
        return true; //Right joystick trigger is being pressed
    } 

    if (rightStick->GetTriggerReleased())
    { 
        return false; //Right joystick trigger is not pressed
    } else {
        return false; 
    }
}

/*bool OI::isDPadUpPressed() 
{ 
    if(controller->GetPOV(0)) 
    {
        return true;
    } 
}*/

bool OI::isLeftJoyTBPressed()
{
    if(leftStick->GetRawButtonPressed(2)) 
    { 
        return true;
    } 
    else 
    {
        return false;
    }
}

bool OI::isRightJoyTBPressed()
{
    if(rightStick->GetRawButtonPressed(2)) 
    {   
        isMotorOn = true; 
        isMotorOff = false; 
    }

    if(isMotorOn == true) 
    {
        return true; 
    } 
    else 
    { 
        return false; 
    }

}

void OI::oiInit() 
{
    isMotorOn = false;
    isAscentOn = false; 
    isKickerOn = false;
    isMotorOff = true;
}

bool OI::isRightJoyRTBPressed()
{
    if(rightStick->GetRawButtonPressed(4)) 
    { 
        isKickerOn = true; 
    }

    if(isKickerOn == true) 
    {
        return true; 
    } 
    else 
    { 
        return false; 
    }

}

bool OI::isRightJoyLTBPressed()
{
    if(rightStick->GetRawButtonPressed(3)) 
    { 
        isAscentOn = true; 
    }

    if(isAscentOn == true) 
    {
        return true; 
    } 
    else 
    { 
        return false; 
    }

}

double OI::getRightRTB() 
{ 
    return rightStick->GetRawButton(4);
}

double OI::getRightLTB()
{
    return rightStick->GetRawButton(3);
}

bool OI::loaderButtonPress()
{
    return rightStick->GetRawButton(13);
}

bool OI::isSpeedUpButtonPressed() 
{
    if (leftStick->GetRawButtonPressed(14)) 
    {
        return true; 
    } else {
        return false;
    }
}

bool OI::isSpeedDownButtonPressed()
{
    if(leftStick->GetRawButtonPressed(15))
    {
        return true;
    } else { 
        return false; 
    }
}

double OI::getRightBumper()
{
    return controller->GetRawButton(6);
    
}

bool OI::getControllerRightTrigger()
{
    if (controller->GetRawAxis(3) > 0)
    {
      return true;
    }
    else
    {
      return false;
    }
}

bool OI::isRightBumperPressed()
{
    if(controller->GetRawButton(4)) 
    { 
        return true; 
    } else { 
        return false;
    }

    if (controller->GetRawButtonReleased(4))
    { 
        return false; 
    } 
}

bool OI::isKickerMotorButtonPressed()
{
    if(rightStick->GetRawButton(12))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool OI::isShooterActuatorButtonPressed()
{
//    if(rightStick->GetRawButton(11))
    if(leftStick->GetTriggerPressed())
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool OI::isShooterMotorButtonPressed()
{
    if(rightStick->GetRawButton(11))
    {
        return true;
    }
    else
    {
        return false;
    }
}

double OI::getBackButton()
{
    return -(controller->GetRawButton(7));
}

double OI::getStartButton()
{
    return controller->GetRawButton(8);
}

bool OI::isStartButtonPressed()
{
    if(controller->GetRawButton(8)) 
    { 
        return true; 
    } else { 
        return false;
    }

    if (controller->GetRawButtonReleased(8))
    { 
        return false; 
    } 
}

bool OI::isBackButtonPressed()
{
    if(controller->GetRawButton(7)) 
    { 
        return true; 
    } else { 
        return false;
    }

    if (controller->GetRawButtonReleased(7))
    { 
        return false;
    } 
}

bool OI::isRightDPadPressed()
{
    if(controller->GetPOV(0) == 90) 
    {
        return true;
    } else if(controller->GetPOV(0) == -1) {
        return false;
    } else {
        return false;
    }
}

bool OI::isLeftDPadPressed()
{
    if(controller->GetPOV(0) == 270)
    {
        return true;
    } else if(controller->GetPOV(0) == -1) {
        return false;
    } else {
        return false;
    }
}

bool OI::isLeftBumperPressed()
{
    if(controller->GetRawButton(5)) 
    { 
        return true; 
    } else { 
        return false;
    }

    if (controller->GetRawButtonReleased(5))
    { 
        return false; 
    } 
}

bool OI::isAButtonPressed()
{
    if(controller->GetRawButton(1)) 
    { 
        return true; 
    } else { 
        return false;
    }

    if (controller->GetRawButtonReleased(1))
    { 
        return false; 
    } 
}

bool OI::isBButtonPressed()
{
    if(controller->GetRawButton(2)) 
    { 
        return true; 
    } else { 
        return false;
    }

    if (controller->GetRawButtonReleased(2))
    { 
        return false; 
    } 
}


double OI::getLeftBumper()
{
    return controller->GetRawButton(1);
}

bool OI::isXButtonPressed()
{
    if(controller->GetRawButton(3)) 
    { 
        return true; 
    } else { 
        return false;
    }

    if (controller->GetRawButtonReleased(3))
    { 
        return false; 
    } 
}

bool OI::isYButtonPressed()
{
    if(controller->GetRawButton(4)) 
    { 
        return true; 
    } else { 
        return false;
    }

    if (controller->GetRawButtonReleased(4))
    { 
        return false; 
    } 
}