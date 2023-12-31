#include <Servo.h> 
#include <NewPing.h>
#include <AFMotor.h>  

#define TRIG_PIN A0
#define ECHO_PIN A1
#define distMax 200

NewPing Dist(TRIG_PIN, ECHO_PIN, distMax); //(trig,echo,dist max)
Servo myServo; 

int distancia = 0;
int distanciaD = 0;
int distanciaIz = 0;
boolean Booleano = false;

AF_DCMotor motorLeft1(1, MOTOR12_1KHZ); 
AF_DCMotor motorLeft2(2, MOTOR12_1KHZ);
AF_DCMotor motorRight1(3, MOTOR34_1KHZ);
AF_DCMotor motorRight2(4, MOTOR34_1KHZ);

void setup() {
  myServo.attach(10);  
  myServo.write(115);
  delay(1000); 
  myServo.write(65);
  delay(500);
  myServo.write(160);
  delay(500);
  myServo.write(115);
}

void loop() {
distancia = medirDistancia();
if (distancia >= 25 && distancia <= 250)
{
  Adelante();
}
else if (distancia < 25)
{
  Frenar();
  delay(150);
  Reversa();
  delay(250);
  Frenar();
  delay(250);
  distanciaD = mirarDerecha();
  delay(250);
  distanciaIz = mirarIzquierda();
  delay(250);

  if(distanciaD >= distanciaIz)
    {
      GirarDerecha();
      Frenar();
    }
    else if(distanciaIz >= distanciaD)
    {
      GirarIzquierda();
      Frenar();
    }
  }
}

int mirarDerecha()
{
    myServo.write(60); 
    delay(350);
    int distancia = medirDistancia();
    return distancia;
}

int mirarIzquierda()
{
    myServo.write(165); 
    delay(350);
    int distancia = medirDistancia();
    delay(50);
    myServo.write(115); 
    return distancia;
}

  int medirDistancia() 
  { 
    delay(10);
    int ditanciaCM = Dist.ping_cm();
    if(ditanciaCM <= 0 || ditanciaCM >= 250)
    {
      ditanciaCM = 250;
    }
    return ditanciaCM;
  }

void Frenar() {
  motorLeft1.run(RELEASE); 
  motorLeft2.run(RELEASE);
  motorRight1.run(RELEASE);
  motorRight2.run(RELEASE);
 } 
  
void Adelante() {
 if(Booleano == false)
  {
    Booleano = true;
    motorLeft1.run(FORWARD);      
    motorLeft2.run(FORWARD);
    motorRight1.run(FORWARD); 
    motorRight2.run(FORWARD);     
    controlVelocidad();
  }
}

void Reversa() {
    Booleano = false;
    motorLeft1.run(BACKWARD);      
    motorLeft2.run(BACKWARD);
    motorRight1.run(BACKWARD);
    motorRight2.run(BACKWARD);  
    controlVelocidad();
}  

void GirarDerecha() {
  motorLeft1.run(FORWARD);
  motorLeft2.run(FORWARD);
  motorRight1.run(BACKWARD);
  motorRight2.run(BACKWARD);     
  delay(400);  
} 
 
void GirarIzquierda() {
  motorLeft1.run(BACKWARD);     
  motorLeft2.run(BACKWARD);  
  motorRight1.run(FORWARD);
  motorRight2.run(FORWARD);   
  delay(400);
} 

 void controlVelocidad(){
   for (int velocidad = 0; velocidad < 160; velocidad +=2) 
   {
      motorLeft1.setSpeed(velocidad);
      motorLeft2.setSpeed(velocidad);
      motorRight1.setSpeed(velocidad);
      motorRight2.setSpeed(velocidad);
      delay(3);
   }
  }
