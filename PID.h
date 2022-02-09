
double PID_KONTROL(
double hata,
double kp,
double ki,
double kd,
double *son_hata, 
unsigned long gecen_zaman,
unsigned long *basla,
double *pid_i) {
  double pid_p = hata*kp;
  *pid_i =* pid_i+ (ki*hata*gecen_zaman);
  double pid_d = (kd * (hata-*son_hata))/gecen_zaman;
  
  *basla= millis();
  
  double PID = pid_p + *pid_i + pid_d;
  /*
  Serial.println("iç değerler ");
  Serial.println("------------------------------------------- ");
  Serial.print("pid_d : ");
  Serial.println(pid_d);
  Serial.print("pid_i  : ");
  Serial.println(*pid_i);
  Serial.print("pid_p  : ");
  Serial.println(pid_p);
  */
  *son_hata = hata;

  
  
  return PID;
  
};
