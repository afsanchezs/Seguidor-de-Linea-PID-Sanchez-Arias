//Definición de Variables
int Setpoint=0,Input=0,Output=0,PWM=0;
float l_Input=0,Proporcional=0,l_Proporcional=0,Integral=0,Derivativo=0,Kp=0,Ki=0,Kd=0; 

void setup() {
  Serial.begin(9600);
  //Configuración de los pines
  pinMode(7,INPUT);//Sensor 1
  pinMode(6,INPUT);//Sensor 2
  pinMode(5,INPUT);//Sensor 3
  pinMode(4,INPUT);//Sensor 4
  pinMode(13,OUTPUT);//Motor2  LOW
  pinMode(12,OUTPUT);//Motor2  HIGH
  pinMode(11,OUTPUT);//Salida PWM Motor Izquierda
  pinMode(10,OUTPUT);//Salida PWM Motor Derecha
  pinMode(9,OUTPUT);//Motor1  LOW
  pinMode(8,OUTPUT);//Motor1  HIGH
  pinMode(A0,INPUT);//Kp
  pinMode(A1,INPUT);//Kd
  pinMode(A2,INPUT);//Ki
  
//  DDRB=0x3F;//8-9 Motor 1, 10-11 Enable Motor 1,2 , 12-13 Motor 2
//  DDRC=0x1F;//A0-Kp,A1-Kd,A2-Ki
//  DDRD&=0xF0;//4-7 Sensores
//  Input=(PIND(4))&0x0F;//Se almacenan los pines 4-7 en una variable de 4 bit
  Kp=5;
  Kd=5;
  Ki=1;
  Setpoint=6;//Se establece el punto ideal
}

void loop() {
  Input=digitalRead(4)<<3|digitalRead(5)<<2|digitalRead(6)<<1|digitalRead(7);//Se almacenan los pines 4-7 en una variable de 4 bit.
  if(Input<=15){l_Input=Input;/*Se almacena la posición anterior*/}
   Serial.print(Input,BIN);
   Serial.print("\t");
   Serial.print(Output,DEC);
   Serial.print("\t");
   Serial.print(Kp,DEC);
   Serial.print("\t");
   Serial.print(Ki,DEC);
   Serial.print("\t");
   Serial.print(Kd,DEC);
   Serial.print("\t");
   Serial.print(PWM,DEC);
   Serial.print("\n");
   Proporcional=(Input-6);//Cálculo del Valor Proporcional
   Integral=(Integral+l_Proporcional);//Cálculo del Valor Integral
   Derivativo=(Proporcional-l_Proporcional);//Cálculo del Valor Derivativo
   Output=(Kp*Proporcional)+(Ki*Integral)+(Kd*Derivativo);//Salida del PID, Valor PWM
   if(abs(Output)<50){PWM=50;}
   if(abs(Output)>250){PWM=250;}
   if(Integral>180){Integral=180;}//Se limita el Valor 'Integral'
   if(Integral<-180){Integral=-180;}
   l_Proporcional=Proporcional;
   digitalWrite(8,LOW);digitalWrite(9,HIGH);digitalWrite(12,LOW);digitalWrite(13,HIGH);//Se colocan los motores en modo de giro hacia adelante 01 01
   if(Setpoint){analogWrite(10,255);analogWrite(11,255);}//En el Setpoint
   if((Input!=Setpoint)&&(Input>0))
   {
    if(Output<0){analogWrite(10,PWM);analogWrite(11,255-PWM);}//Gira a la Derecha
    if(Output>0){analogWrite(10,255-PWM);analogWrite(11,PWM);}//Gira a la Izquierda
    if(Input=15){analogWrite(10,0);analogWrite(11,0);}//Frena
   }
   if(Input==00)
   {
    if(l_Input<6){analogWrite(10,255-PWM);analogWrite(11,PWM);}//Gira a la Izquierda
    if(l_Input>6){analogWrite(10,PWM);analogWrite(11,255-PWM);}//Gira a la Derecha
   }
}
