#include "Intake.h"

Intake *Intake::s_instance = 0; 

//Static Singleton Method 
Intake *Intake::GetInstance(){ 
    if(s_instance == 0) { 
        s_instance = new Intake();
    }
    return s_instance; 
}

//Constructor 
Intake::Intake() 
{ 
    //Establish motors according to ID's 
    IntakeMotor = new TalonSRX(INTAKE_ID);
    //loaderMotor = new rev::CANSparkMax(LOADER_ID, BRUSHLESS);
    intakeSolenoid = new frc::DoubleSolenoid{0,1}; // Change later 
    
    //Motor inversions if necessary 
    //IntakeMotor->SetInverted(true);
}

//Destructor 
/*Intake::~Intake() { 
    //delete Intake();
} */

int Intake::getIntakeSensor()
{ 
    return ballDetector.GetValue();
}

void Intake::IntakeMotorRun(double motorValue)
{
    IntakeMotor->Set(ControlMode::PercentOutput, motorValue);
}

void Intake::stopIntakeMotor() 
{ 
    IntakeMotor->Set(ControlMode::PercentOutput, 0);  
}

/*void Intake::loaderMotorRun(double motorValue)
{
    loaderMotor->Set(motorValue / 4);
} */

void Intake::SolenoidForward() 
{   
    intakeSolenoid->Set(frc::DoubleSolenoid::Value::kForward); 
}

void Intake::SolenoidReverse() 
{
    intakeSolenoid->Set(frc::DoubleSolenoid::Value::kReverse); 
}

void Intake::SolenoidOff() 
{
    intakeSolenoid->Set(frc::DoubleSolenoid::Value::kOff); 
}