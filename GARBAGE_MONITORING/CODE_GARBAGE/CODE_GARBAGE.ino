#define BLYNK_TEMPLATE_ID "TMPL3GzreFuWp"
#define BLYNK_TEMPLATE_NAME "GARBAGE"
#define BLYNK_AUTH_TOKEN "38IvN_w-TmNpJVOmBMK3bsvWb_2BsJ0N"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <ESP_Mail_Client.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

#define SMTP_server "smtp.gmail.com"
#define SMTP_Port 465
#define sender_email "subash@gmail.com"
#define sender_password "fzuermcodqkiqfyr"
#define Recipient_email "sssubash67@gmail.com"
#define Recipient_name "subash"
SMTPSession smtp;

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Siruvar"; // Change your Wifi/ Hotspot Na
char pass[] = "password"; // Change your Wifi/ Hotspot Password

BlynkTimer timer;
const int trigPin = 12; 
const int echoPin = 13;  
long duration;
int length;

WidgetLED led(V1);

void setup() //Setup function - only function that is run in deep sleep mode
{
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);
  Serial.begin(9600);
  Serial.print("Connecting...");
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED)
  { Serial.print(".");
    delay(200);
   }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  smtp.debug(1);
  
  Blynk.begin(auth, ssid, pass);//Splash screen delay
  delay(2000);
  


  ESP_Mail_Session session;
  session.server.host_name = SMTP_server ;
  session.server.port = SMTP_Port;
  session.login.email = sender_email;
  session.login.password = sender_password;
  session.login.user_domain = "";

  SMTP_Message message;
  message.sender.name = "ESP 32";
  message.sender.email = sender_email;
  message.subject = "ESP32 Testing Email";
  message.addRecipient(Recipient_name,Recipient_email);

  String htmlMsg = "<div style=\"color: #000000;\"><h1> Hello Semicon!</h1><p> Mail Generated from  ESP32</p></div>";
  message.html.content = htmlMsg.c_str();
  message.html.content = htmlMsg.c_str();
  message.text.charSet = "us-ascii";
  message.html.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  String textMsg = "How are you doing";
  message.text.content = textMsg.c_str();
  message.text.charSet = "us-ascii";
  message.text.transfer_encoding = Content_Transfer_Encoding::enc_7bit;

  if (!smtp.connect(&session))
    return;
  if (!MailClient.sendMail(&smtp, &message))
    Serial.println("Error sending Email, " + smtp.errorReason());
}


void loop() //Loop function
{
  Blynk.run();
  
   digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  length= duration*0.034/2; 

  Blynk.virtualWrite(V0, length);
  
   
  if (length <= 15)
  {
    Blynk.logEvent("GARBAGE_ALERT");
    Serial.print("GARBAGE LEVEL ");
    led.on();
  }

  
}