#include "LED.h"

LED *LED::s_instance = 0; 

LED *LED::GetInstance() 
{ 
    if (s_instance == 0) 
    { 
        s_instance = new LED(); 
    }
    return s_instance; 
}

//Constructor 
LED::LED()
{ 

}

//Public Methods
//----------------------------------\\**

//Standard color for disable and regular run 
void LED::Standard() 
{ 
    for(int i = 0; i < kLength; i++) 
    {
        m_ledBuffer[i].SetRGB(0, 171, 255); 
    }
}

//Display blue | color wheel 
void LED::Blue() 
{ 
    for(int i = 0; i < kLength; i++) 
    {
        m_ledBuffer[i].SetRGB(0, 0, 255); 
    }
}

//Display red | color wheel
void LED::Red() 
{ 
    for(int i = 0; i < kLength; i++) 
    {
        m_ledBuffer[i].SetRGB(255, 0, 0); 
    }
}

//Display green | color wheel
void LED::Green() 
{ 
    for(int i = 0; i < kLength; i++) 
    {
        m_ledBuffer[i].SetRGB(0, 255, 0); 
    }
}

//Display yellow | color wheel
void LED::Yellow() 
{ 
    for(int i = 0; i < kLength; i++) 
    {
        m_ledBuffer[i].SetRGB(239, 255, 0); 
    }
}

//Initialize the color math target, length, buffer and initial color
void LED::colorDetectionInit() 
{ 
  m_colorMatcher.AddColorMatch(kGreenTarget);
  m_colorMatcher.AddColorMatch(kRedTarget);
  m_colorMatcher.AddColorMatch(kBlueTarget);
  m_colorMatcher.AddColorMatch(kYellowTarget);

    m_led.SetLength(kLength); 
    m_led.SetData(m_ledBuffer); 
    m_led.Start();
    Standard(); 

}

//Find what color is detected | print to dashboard and change LED according to color 
void LED::colorDetector() 
{ 
    
   if(matchedColor == kBlueTarget) { 
    colorString = "Blue";
    Blue();  
    m_led.SetData(m_ledBuffer);      
  } else if (matchedColor == kRedTarget){ 
    colorString = "Red";
    Red();
    m_led.SetData(m_ledBuffer); 
  } else if (matchedColor == kGreenTarget){ 
    colorString = "Green";
    Green();
    m_led.SetData(m_ledBuffer); 
  } else if (matchedColor == kYellowTarget){ 
    colorString = "Yellow";
    Yellow();
    m_led.SetData(m_ledBuffer); 
  } else { 
    colorString == "Unknown";
    Standard();
    m_led.SetData(m_ledBuffer); 
  }

} 

//Get proximity of color sensor to color wheel 
double LED::getProximity() 
{ 
    return proximity; 
}