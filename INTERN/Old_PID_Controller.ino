const int HALLSEN_A = 15; // Hall sensor A connected to pin 3 (external interrupt)
const int HALLSEN_B = 4;
const int MOTOR1A = 19;
const int MOTOR1B = 21;

// motor one rotation= 3 pulses (we defined as linecount)
int linecount = 3;
float frequency=0;
long encoderValue = 0;
float rpm = 0;

// int the interval of the line count 
int interval = 100;
long previousMillis = 0;
long currentMillis = 0;

//pwm setup
const int pwmfreq = 5000 ;
const int pwmchannel1 = 0 ;
const int pwmchannel2 = 1 ;
const int pwmres = 8 ;

//PID controller setup
long prevT = 0;
float eprev = 0;
float eintegral = 0;
float dedt = 0;
float st_Pt = 5000;
int pwr;
int e;

//PID constant setup
const float kp=3;
const float ki=0.1;
const float kd=0.05;

  void  IRAM_ATTR updateEncoder()
{
  encoderValue++;
}


void setup() {

  Serial.begin(9600);
  encoderValue = 0;
 
  pinMode( MOTOR1A , OUTPUT);
  pinMode( MOTOR1B , OUTPUT);

  pinMode(HALLSEN_A, INPUT); 
  pinMode(HALLSEN_B, INPUT);
  
  attachInterrupt(HALLSEN_A, updateEncoder, FALLING);

  ledcSetup(pwmchannel1,pwmfreq,pwmres); 
  ledcSetup(pwmchannel2,pwmfreq,pwmres); 
  ledcAttachPin(MOTOR1A,pwmchannel1);
  ledcAttachPin(MOTOR1B,pwmchannel2);
}

void loop() {

 
  // Update RPM value on every second
  currentMillis = millis();
  if (currentMillis - previousMillis > interval) {
  previousMillis = currentMillis;
  frequency = (encoderValue / (interval * 0.001));
  rpm = ( frequency * 60 / linecount);
  
  encoderValue = 0;
  }
  motorA_PID( eprev, rpm);
   setMotor(dir,pwr);

   Serial.print("pwr=");
   Serial.print(pwr); 
   Serial.print(" ");
   Serial.print(" ");
   Serial.print("sp:");
   Serial.print(st_Pt);
   Serial.print(" ");
   Serial.print("actual:");
   Serial.println(rpm);
   
   eprev=e;   
}

void motorA_PID(float eprev,float rpm)
{
   long currT = millis();
    float deltaT = ((float) (currT - prevT))/( 1.0e3 );
    prevT = currT;

 
  e =st_Pt - rpm;

  // derivative
   float dedt = (e-eprev)/(deltaT);

  // integral
    eintegral = eintegral + e*deltaT;

  // control signal
    float u = kp*e + kd*dedt + ki*eintegral;

    pwr=map(u,-3.4*e-38,3.4*e+38,0,255);
  
  }


void EncoderInit()
{
 // Attach interrupt at hall sensor A on each rising signal

  attachInterrupt(HALLSEN_A, updateEncoder, RISING);

}
void setMotor(int dir,int pwr){

  if(dir == 1){ 
    // Turn one way
    ledcWrite(pwmchannel1,pwr);
    ledcWrite(pwmchannel2,LOW);
  }
  else if(dir == 2){
    // Turn the other way
    ledcWrite(pwmchannel1,LOW);
    ledcWrite(pwmchannel2,pwr);
  }
  else{
    // Or dont turn
    ledcWrite(pwmchannel1,LOW);
    ledcWrite(pwmchannel2,LOW);   
  }
}
