uint8_t Input=0,l_Input=0,Setpoint=0,Output=0,Left=0,Right=0,PWM=0;
float Proporcional=0,l_Proporcional=0,Integral=0,Derivativo=0,Kp=5,Ki=1,Kd=0.2; 
void setup() {
  Serial.begin(9600);//
  DDRB=0;//Control de los motores
  DDRD=7;//Sensores
  DDRC=0x1F;//Kp,Kd,Ki
  Kp=analogRead(A0)/10.0;
  Ki=analogRead(A1)/1023.0;
  Kd=analogRead(A2)/1023.0;
}

void loop() {
  Input=digitalRead(4)<<3|digitalRead(5)<<2|digitalRead(6)<<1|digitalRead(7);//Se almacena Input
  l_Input=Input;
  Setpoint=0x03&(Input>>1);
  Left=1&(Input>>3);
  Right=1&Input;
  Proporcional=(Input-6);//Cálculo del Valor Proporcional
  Integral=(Integral+l_Proporcional);//Cálculo del Valor Integral
  if(Integral>180){Integral=180;}//Se limita el Valor 'Integral'
  if(Integral<-180){Integral=-180;}
  Derivativo=(Proporcional-l_Proporcional);//Cálculo del Valor Derivativo
  Output=(Kp*Proporcional)+(Ki*Integral)+(Kd*Derivativo);//Salida del PID, Valor PWM
  l_Proporcional=Proporcional;
  PWM=abs(Output);
  if(PWM>255){PWM=255;}
  
  PORTB=0b010001;//Movimiento Ruedas hacia adelante
  //Condicionales del Setpoint
    if(Input==0||Input==15)
    {
      analogWrite(10,0);//Izquierda
      analogWrite(11,0);//Derecha
    }
    else
    {
    if(Input==6)
    {
      analogWrite(10,255);//Izquierda
      analogWrite(11,255);//Derecha
    }
    if(Setpoint==1)
    {
      analogWrite(10,255);//Izquierda
      analogWrite(11,100);//Derecha
    }
    if(Setpoint==2)
    {
      analogWrite(10,100);//Izquierda
      analogWrite(11,255);//Derecha
    }
    else
    {
    if(Left==1)
    {
      analogWrite(10,255-PWM);//Izquierda
      analogWrite(11,PWM);//Derecha
    }
    else
    {
      analogWrite(10,PWM);//Izquierda
      analogWrite(11,255-PWM);//Derecha
    }
    }
    }
  //Visualizacion
  Serial.print("Input: ");
  Serial.print(Input ,BIN);
  /*Serial.print(Setpoint,BIN);
  Serial.print(Right,BIN);*/
  Serial.print("\t");
  Serial.print("PID: ");
  Serial.print(Output);
  Serial.print("\t");
  Serial.print("Kp: ");
  Serial.print(Kp);
  Serial.print("\t");
  Serial.print("Kd: ");
  Serial.print(Kd);
  Serial.print("\t");
  Serial.print("Ki: ");
  Serial.print(Ki);
  Serial.print("\t");
  Serial.print("Output: ");
  Serial.print(PWM);
  Serial.print("\n");  
  _delay_ms(80);
}
