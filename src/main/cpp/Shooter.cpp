#include "Shooter.h" 

Shooter *Shooter::s_instance = 0; 
//Static Singleton method 
Shooter *Shooter::GetInstance(){ 
if (s_instance == 0){ 
    s_instance = new Shooter(); 
}
    return s_instance; 
}

//Constructor
Shooter::Shooter(){

    //Create new instance of motor controllers
    leftShooter = new rev::CANSparkMax(LEFT_SHOOTER_ID, BRUSHLESS);
    rightShooter = new rev::CANSparkMax(RIGHT_SHOOTER_ID, BRUSHLESS);
    kickerMotor = new rev::CANSparkMax(KICKER_ID, BRUSHLESS);
    loaderMotor = new rev::CANSparkMax(LOADER_ID, BRUSHLESS);

    intake_sensor = new frc::AnalogInput{INTAKE_S_PORT};
    ascent_sensor = new frc::AnalogInput{ASCENT_S_PORT};
    shooter_sensor = new frc::AnalogInput{SHOOTER_S_PORT};

    leftShooterEncoder = new rev::CANEncoder(*leftShooter);
    rightShooterEncoder = new rev::CANEncoder(*rightShooter);

    sensorFlipTimer = new frc2::Timer; 
    bumperTimer = new frc2::Timer; 
    delayTimer = new frc2::Timer; 
    bumperSolenoid = new frc::DoubleSolenoid{2, 3};
    shooterDistanceControlSolenoid = new frc::DoubleSolenoid{4,5};
    //Motor inversion if needed
    kickerMotor->SetInverted(true); 
    leftShooter->SetInverted(true);    
}


//Any public methods go after 
void Shooter::updateSensors() 
{ 
   intake_s_value = intake_sensor->GetValue(); 
   // ascent_s_value = ascent_sensor->GetValue() - 230; 
   // shooter_s_value = shooter_sensor->GetValue() - 230; 

    leftRPM = leftShooterEncoder->GetVelocity(); 
    rightRPM = rightShooterEncoder->GetVelocity(); 

}

void Shooter::sensorFlip()
{
    intake_s_value = intake_sensor->GetValue(); 
    //std::cout << intake_s_value << std::endl;
    if(intake_s_value >= 4095 && delay % 1 == 0){

        bumperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
        okToStartDelay = true;
        delay = 0;
        //std::cout << "bumper moves" << std::endl;
    } else if(intake_s_value < 3400 && delay % 1 == 0)
    {
        okToStartDelay = false;
        delay = 0;
        bumperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
        //std::cout << "reset timer" << std::endl;
    }
    if(okToStartDelay == true){
        delay++;
        //std::cout << "delay = " << delay << std::endl;
    }

}

void Shooter::SolenoidForward() 
{
    bumperSolenoid->Set(frc::DoubleSolenoid::Value::kForward); 
}

void Shooter::SolenoidReverse() 
{
    bumperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse); 
}


void Shooter::shooterShuffleInfo() 
{ 
    frc::SmartDashboard::PutNumber("Intake Sensor", intake_s_value);
   // std::cout << intake_s_value << "Dashboard call" << std::endl;
    //frc::SmartDashboard::PutNumber("Ascent Sensor", ascent_s_value);
    //frc::SmartDashboard::PutNumber("Shooter Sensor", shooter_s_value);
    frc::SmartDashboard::PutNumber("Left RPM", leftRPM);
    frc::SmartDashboard::PutNumber("Right RPM", rightRPM);

}

void Shooter::shooterMotors(double motor_value) 
{ 
    leftShooter->Set(motor_value);
    rightShooter->Set(motor_value);
    
//    leftShooter->Set(-.452); //shooterDefault
//    rightShooter->Set(-.452); //shooterDefault    
}

void Shooter::kickerMotorFunction(double MV){    
    kickerMotor->Set(MV);
}

void Shooter::loaderMotorFunction(double motorValue)
{
    loaderMotor->Set(motorValue / 3); //5
}

void Shooter::bumperSequence()
{   
    if(bumperTimerOn == false && delayTimerOn == false)
    {
        bumperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
        bumperTimer->Start(); 
        delayTimer->Stop();
        bumperTimerOn = true;
    }

    if(bumperTimer->HasPeriodPassed((units::time::second_t) 0.65) == true && bumperTimerOn == true)
    {
        bumperTimerOn = false;
        bumperTimer->Stop(); 
        bumperTimer->Reset();
        bumperSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
        delayTimer->Start();
        delayTimerOn = true;
    }

    if(delayTimer->HasPeriodPassed((units::time::second_t) 0.25) == true && delayTimerOn == true)
    {
        bumperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
        delayTimerOn = false; 
        delayTimer->Stop();
        delayTimer->Reset();
    }


}

void Shooter::
autoShooterSequence(int distance, double buttonInput)
{
    if (distance == far)
    {
      shooterDistanceControlSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
      shooterMotors(shooterDefault);
      if (leftRPM < -4175)  //target RPM is -4175 
      { 
          okToStartSequence = true;
      }
      else
      {
          okToStartSequence = false;
      }
      
    } else if (distance == near) //distance is near
    {
      shooterDistanceControlSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
      shooterMotors(shooterLowDefault);
      if (leftRPM < -3250)  //target RPM is -4175 
      {
          okToStartSequence = true;
      }
      else
      {
          okToStartSequence = false;
      }
    }
    
    

    if (okToStartSequence == true) 
    {

    //bumperSequence();
    sensorFlip();
    loaderMotorFunction(buttonInput);
    
    kickerMotorFunction(buttonInput / 2);
    }
}

void Shooter::loaderKicker(bool enable)
{
    if (enable == true)
    {
        //bumperSequence();
        sensorFlip();
    }
    loaderMotorFunction(enable);
}


void Shooter::bumperSolenoidDefault()
{
    bumperSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
}

void Shooter::autoLoaderSequence(double buttonInput)
{
    //bumperSequence(); 
    sensorFlip();
    loaderMotorFunction(buttonInput);
}

void Shooter::greenZoneAutoFire(int near, double buttonInput)
{
    if (near == 1)
    {
        shooterDistanceControlSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
        shooterMotors(greenPower);
        if (leftRPM >= -2450 && leftRPM <= -2300)  //target RPM is -4175 
        { 
          okToStartSequence = true;
        }
        else
        {
          okToStartSequence = false;
        }
    }

    if (okToStartSequence == true) 
    {
        //bumperSequence();
        sensorFlip();
        loaderMotorFunction(buttonInput);
    
        kickerMotorFunction(buttonInput / 2);
    }
    
}

void Shooter::yellowZoneAutoFire(int near, double buttonInput)
{
    if (near == 1)
    {
        shooterDistanceControlSolenoid->Set(frc::DoubleSolenoid::Value::kReverse);
        shooterMotors(yellowPower);
        if (leftRPM >= -2575 && leftRPM <= -2400)  //target RPM is -4175 
        { 
          okToStartSequence = true;
        }
        else
        {
          okToStartSequence = false;
        }
    }

    if (okToStartSequence == true) 
    {
        //bumperSequence();
        sensorFlip();
        loaderMotorFunction(buttonInput);
    
        kickerMotorFunction(buttonInput / 2);
    }
    
}

void Shooter::blueZoneAutoFire(int far, double buttonInput)
{
    if (far == 2)
    {
        shooterDistanceControlSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
        shooterMotors(bluePower);
        if (leftRPM >= -4050 && leftRPM <= -3900)  //target RPM is -4175 
        { 
          okToStartSequence = true;
        }
        else
        {
          okToStartSequence = false;
        }
    }

    if (okToStartSequence == true) 
    {
        //bumperSequence();
        sensorFlip();
        loaderMotorFunction(buttonInput);
    
        kickerMotorFunction(buttonInput / 2);
    }
    
}

void Shooter::redZoneAutoFire(int far, double buttonInput)
{
    if (far == 2)
    {
        shooterDistanceControlSolenoid->Set(frc::DoubleSolenoid::Value::kForward);
        shooterMotors(redPower);
        if (leftRPM >= -4200 && leftRPM <= -4000)  //target RPM is -4175 
        { 
          okToStartSequence = true;
        }
        else
        {
          okToStartSequence = false;
        }
    }

    if (okToStartSequence == true) 
    {
        //bumperSequence();
        sensorFlip();
        loaderMotorFunction(buttonInput);
    
        kickerMotorFunction(buttonInput / 2);
    }
    
}
