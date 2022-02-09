//###############################################   MPU 6050
#include "MUP.h"
#include "PID.h"
int x,y,z,e; 
unsigned long basla= millis();


//################################################ PID deişkenleri
double  Kp=0.005, Ki=0.05, Kd=0.33,son_hata,pid_i;
           // Ayar parametrelerimizi tanımlayıp belirliyoruz.  Kp=0.003, Ki=0.03, Kd=0.33,son_hata,pid_i

//##################################################   Servo           
#include <Servo.h>



Servo myservo1;  // create servo object to control a servo
Servo myservo2;
int potpin = A0;  // analog pin used to connect the potentiometer
int val=0;    // variable to read the value from the analog pin
int val2=0; 
int a=10;
   
                                    


void setup() {  
myservo1.attach(9);  // attaches the servo on pin 9 to the servo object
myservo2.attach(8); 
initializeIMU();
Serial.begin(9600);
pinMode(potpin,INPUT);
myservo1.write(0);
myservo2.write(0);
windowStartTime = millis();

}

void loop() {
    
  struct Orientation o = getIMUOrientation();
  ///////////////////////////////////////////////////////////////////değerleri alma
  e=o.Error;
  x=o.Roll;
  y=o.Pitch;
  z=o.Yaw;
  
  /////////////////////////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////  maplama
   
   y=map(y,-180,180,-180,180);
   
   ////////////////////////////////////////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////    kutuyu yeniden konumlandırma
 
  if (e == 1){
      Serial.println(" HATA !!!  BAĞLANTILARI KONTROL EDİN ");
  }
  
  else{  ////////////////////////////////////////////////////////////////////////////////////////////////                
  ////////////////////////////////////////////////////////////   Ardinunio daki değerleri pytona atma
  Serial.print(e);
  Serial.print(",");
  Serial.print(x);
  Serial.print(",");
  Serial.print(y);
  Serial.print(",");
  Serial.println(z);
  //////////////////////////////////////////////////////////////////////////////////////////////////////
  ///////////////////////////////////////////////////////////// PID KONTROLÜ

  int setpoint=0, gelendeger=y;      // Değişkenleri tanımlıyoruz.

  

  double error = setpoint - gelendeger;
  if (error != 0){
  unsigned long gecen_zaman = millis()-basla;
   
  /*
  Serial.println("giriş değerleri ");
  Serial.println("------------------------------------------- ");
  Serial.print("hata : ");
  Serial.println(error);
  Serial.print("gecen zaman  : ");
  Serial.println(gecen_zaman);
  Serial.print("pid_i  : ");
  Serial.println(pid_i);
  Serial.println("------------------------------------------- ");
  Serial.print("son_hata  : ");
  Serial.println(son_hata);
  */
    double motor_gucu = PID_KONTROL(error,Kp, Ki, Kd,&son_hata,gecen_zaman,&basla,&pid_i);
    if (-1>(30*motor_gucu)<181 ){
    myservo2.write(30*motor_gucu);
    }
    if (-1>(30*motor_gucu)<181 and  myservo2.read()==0){
      myservo1.write(-30*motor_gucu);
    }
   
  /*
  Serial.println("çıkış değerleri ");
  Serial.println("------------------------------------------- ");
  
  Serial.print("hata : ");
  Serial.println(error);
  Serial.print("gecen zaman  : ");
  Serial.println(gecen_zaman);
  Serial.print("pid_i  : ");
  Serial.println(pid_i);
  Serial.print("motor_gucu  : ");
  Serial.println(motor_gucu);
  Serial.print("son_hata  : ");
  Serial.println(son_hata);
  }
  else pid_i=0;
  
  */
  
  }
  delay(100);
  }

}
