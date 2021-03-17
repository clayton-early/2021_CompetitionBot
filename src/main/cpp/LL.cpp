#include "LL.h"

LL *LL::s_instance = 0; 

//Static Singleton method 
LL *LL::GetInstance() 
{ 
    if(s_instance == 0 ) { 
        s_instance = new LL(); 
    }
    return s_instance; 
}

//Constructor 
LL::LL() 
{ 
    //Limelight setup 

}

//Public Methods
//----------------------------------\\**

LL::limelight_steer_update su = 
    { 
        0.05, //Minimun Steer
        0.1, //Maximum Steer
        0.1, //Heading Error
        0.1, //Right Turn Command
        0.1, //Left Turn Command
        -0.15, //kP
        0.1 //Steering Adjust
    };

LL::limelight_drive_update du = 
    { 
        0.35, //Minimum Drive
        4.0, //Desired Target Area
        0.1, //Maximum Drive
        -0.5, //kpDistance
        0.1, //Driving Adjust
        0.1 //Distance Error
    };

void LL::update_Limelight_Track() 
{ 
//pulling data from network tables for limelight 
    //tx = table->GetNumber("tx", 0.0); 
    ty = table->GetNumber("ty", 0.0); 
    //ta = table->GetNumber("ta", 0.0); 
    tv = table ->GetNumber("tv", 0.0); 
}

double LL::limelightTX() 
{ 
    return tx; //Return tx from Network tables
}

double LL::limelightTY() 
{ 
    return ty; //Return ty from network tables
}

double LL::limelightTA() 
{ 
    return ta; //Return ta from network tables
}

double LL::limelightTV() 
{ 
    return tv; //Return tv from network tables
}

//LED modes for startup and periodic
void LL::limelight_LED_blink()
{
    table->PutNumber("ledMode", 2);
}

void LL::limelight_LED_on() 
{
    table->PutNumber("ledMode", 3);
}

//Method returns value to be inputted into left side drive train
double LL::limelightLeftTrack() 
{ 
    tx = table->GetNumber("tx", tx); //Constantly get updated tx from network tables
    ty = table->GetNumber("ty", ty); //Constantly get updated ty from network tables

    su.heading_error = -tx; 
    du.distance_error = -ty;
    su.steering_adjust = 0.0; 

    if(tx > 1.0) 
    { 
        su.steering_adjust = su.kP * su.heading_error - su.min_steer; 
    } else if (tx < 1.0) 
    { 
        su.steering_adjust = su.kP * su.heading_error + su.min_steer;
    }

    du.driving_adjust = du.kpDistance * du.distance_error; 

    leftMotorValue = -0.1 * (-su.steering_adjust + du.driving_adjust);  //Changed 0.1 to - to fix LL after encoder inversion


    //std::cout << tx << " " << "left tx" << std::endl; 
    //std::cout << ty << " " << "left ty" << std::endl;
    //std::cout << su.steering_adjust << " " << "Left steering adjust" << std::endl;
    //std::cout << leftMotorValue << " " << "Left Motor Value" << std::endl; 


    return leftMotorValue; 

}

double LL::limelightRightTrack() 
{ 
    tx = table->GetNumber("tx", tx); //Constantly get updated tx from network tables
    ty = table->GetNumber("ty", ty); //Constantly get updated ty from network tables 

    su.heading_error = -tx; 
    du.distance_error = -ty;
    su.steering_adjust = 0.0; 

    if(tx > 1.0) 
    { 
        su.steering_adjust = su.kP * su.heading_error - su.min_steer; 
    } else if (tx < 1.0) 
    { 
        su.steering_adjust = su.kP * su.heading_error + su.min_steer;
    }

     du.driving_adjust = du.kpDistance * du.distance_error; 

    rightMotorValue = -0.1 * (su.steering_adjust + du.driving_adjust); //Changed 0.1 to - to fix LL after encoder inversion


    //std::cout << su.steering_adjust << " " << "Right steering adjust" << std::endl;
    //std::cout << rightMotorValue << " " << "Right motor value" << std::endl;
    //std::cout << tx << " " << "Right tx" << std::endl; 
    //std::cout << ty << " " << "Right ty" << std::endl; 


    return rightMotorValue; 
}