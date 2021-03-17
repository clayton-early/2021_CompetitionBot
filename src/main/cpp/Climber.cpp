#include "Climber.h"

Climber *Climber::s_instance = 0;

//Static Singleton Method
Climber *Climber::GetInstance(){
    if (s_instance == 0){
        s_instance = new Climber();
    }
    return s_instance;
}

//Constructor
Climber::Climber()
{
    //Establish climber motors according to ID's
    rightClimbMotor = new rev::CANSparkMax(RIGHT_CLIMBER, BRUSHLESS);
    leftClimbMotor = new rev::CANSparkMax(LEFT_CLIMBER, BRUSHLESS);

    rightClimbEncoder = new rev::CANEncoder(*rightClimbMotor);
    leftClimbEncoder = new rev::CANEncoder(*leftClimbMotor);
    lockingSolenoid = new frc::DoubleSolenoid{6,7}; 
    //reserved for motor inversion
    rightClimbMotor->SetInverted(true);



}

//Destructor 
/*Climber::~Climber(){ 
    delete Climber;
}*/

//Space for any public methods 
void Climber::climbDrive(double left, double right) 
{
    
    rightClimbMotor->Set(right);
    leftClimbMotor->Set(left);
}

double Climber::getRightEncoder()
{
    return (rightClimbEncoder->GetPosition());
}

double Climber::getLeftEncoder()
{
    return (leftClimbEncoder->GetPosition());
}

void Climber::updateClimberShuffleInfo()
{
    leftPos = leftClimbEncoder->GetPosition(); 
    rightPos = rightClimbEncoder->GetPosition();
}

void Climber::climberShuffleInfo() 
{
    leftPos = leftClimbEncoder->GetPosition(); 
    rightPos = rightClimbEncoder->GetPosition();

    frc::SmartDashboard::PutNumber("left climb pos", leftPos);
    frc::SmartDashboard::PutNumber("right climb pos", rightPos);

}

void Climber::SolenoidForward() 
{   
    lockingSolenoid->Set(frc::DoubleSolenoid::Value::kForward); 
}

void Climber::SolenoidReverse() 
{
    lockingSolenoid->Set(frc::DoubleSolenoid::Value::kReverse); 
}

void Climber::SolenoidOff() 
{
    lockingSolenoid->Set(frc::DoubleSolenoid::Value::kOff); 
}

void Climber::climberInit() 
{
    rightClimbMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    leftClimbMotor->SetIdleMode(rev::CANSparkMax::IdleMode::kCoast);
    leftClimbEncoder->SetPosition(0);
    rightClimbEncoder->SetPosition(0);
    SolenoidOff();
}

void Climber::zeroOutClimbCoders()
{
    rightClimbEncoder->SetPosition(0);
    leftClimbEncoder->SetPosition(0);
}