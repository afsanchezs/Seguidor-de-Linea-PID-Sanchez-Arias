void setup() {
  // put your setup code here, to run once:
  pinMode(10,OUTPUT);//Salida PID PWM Motor 2
  pinMode(9,OUTPUT);//Salida PID PWM Motor 1
  pinMode(7,INPUT);//4-7 Sensores IR
  pinMode(6,INPUT);
  pinMode(5,INPUT);
  pinMode(4,INPUT);
  pinMode(3,OUTPUT);//2 y 3 señales de control motor 2
  pinMode(2,OUTPUT);
  pinMode(1,OUTPUT);//1 y 0 señales de control motor 1
  pinMode(0,OUTPUT);
  pinMode(A0,INPUT);//Kp
  pinMode(A1,INPUT);//Kd
  pinMode(A2,INPUT);//Ki
}

void loop() {
  // put your main code here, to run repeatedly:
  // Hacer detener los motores sería un gasto innecesario
  // de batería, por lo tanto, siempre giraran en el mismo
  // sentido. 
  //En línea recta. A máxima velocidad 
  if((digitalRead(5)==HIGH)&(digitalRead(6)==HIGH))
  {
    digitalWrite(0,HIGH);
    digitalWrite(1,LOW);
    digitalWrite(2,LOW);
    digitalWrite(3,HIGH);
    analogWrite(9,255);//El PWM será controlado por el PID
    analogWrite(10,255);
  }
  //
