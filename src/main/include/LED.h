#pragma once 

#include <iostream> 
#include <array>
#include <rev/ColorSensorV3.h> 
#include <rev/colormatch.h>
#include <frc/AddressableLED.h> 

class LED
{ 
    public: 
        static LED *GetInstance(); 

        void Standard(); 
        void Blue(); 
        void Red(); 
        void Green(); 
        void Yellow(); 
        void colorDetectionInit();  
        void colorDetector(); 

        double getProximity();


        static constexpr auto i2cPort = frc::I2C::Port::kOnboard; //set i2cPort to the onboard port 
        rev::ColorSensorV3 m_colorSensor{i2cPort}; //Show what port to find color sensor 
        rev::ColorMatch m_colorMatcher; 
        
        //Set values for each color target for id by sensor 
        static constexpr frc::Color kBlueTarget = frc::Color(0.143, 0.427, 0.429);
        static constexpr frc::Color kRedTarget = frc::Color(0.561, 0.232, 0.114);
        static constexpr frc::Color kYellowTarget = frc::Color(0.361, 0.524, 0.113);
        static constexpr frc::Color kGreenTarget = frc::Color(0.197, 0.561, 0.240);

        //Set length of led strand
        static constexpr int kLength = 255; 

        //Determine the first pixels hue 
        int firstPixelHue = 0;
        
        //Set the IR value into a variable
        double IR = m_colorSensor.GetIR(); 

        //Set intial value for color sensors confidence (it's a sad sensor)
        double confidence = 0.0; 

        //Set intial value of proximity 
        uint32_t proximity = m_colorSensor.GetProximity();

        //Set detected color to be the color the sensor takes in 
        frc::Color detectedColor = m_colorSensor.GetColor();

        //Match the detected color to the detected color and display the confidence it has 
        frc::Color matchedColor = m_colorMatcher.MatchClosestColor(detectedColor, confidence);

        //Set intial variable to display the detected color on the dashboard 
        std::string colorString; 

        //Set the LED's to the port the PWM port they are in with the arguments of length and buffer
        frc::AddressableLED m_led{0}; 
        std::array<frc::AddressableLED::LEDData, kLength>
            m_ledBuffer;

    private: 
        static LED *s_instance; 

        LED(); 

        

};