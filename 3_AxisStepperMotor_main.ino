/* Este codigo utiliza un motor a pasos NEMA 17' de 4kg a 1.4A bipolar de 1.8° como paso minimo controlado con un A4988 
 *  el a4988 está configurado a 0.79volts con el potenciometro limitador de potencia
 * se utilizó la siguiente fórmula considerando una resistencia de 0.01ohms
 * 
 * This code uses a NEMA 17' Stepper 4kg*cm2 17' motor which consumes around 1.4A With a 1.8° as step using a A4988
 * Motor controller.
 * 
 * The A4988 is configured using a reference of 0.79V and considering a SMD resistance of 0.01ohm
 * 
 * WARNING:
 * Following configurations may damaged a different motor or electronics components
 * please verify your motor model before using this parameters.
 * 
 *   ItripMAX=Vref/(8*R)
     Vref= 1.4A(8*0.1)=1.12
     añadiendo un factor de seguridad de 0.7 por  full step
     Vref = 1.12(0.7)=0.784 redondeando a 0.79
*/
int _step;
int _temp;
float _angles;
bool direc;

#define Enable 6
#define _baud (9600)
#define Step 5
#define Direction 4

#define counterwise HIGH
#define clockwise LOW


void setup() {

  Serial.begin(_baud);
  pinMode(Enable,OUTPUT); // Enable
  pinMode(Step,OUTPUT); // Step
  pinMode(Direction,OUTPUT); // Dir
  digitalWrite(Enable,LOW); // Set Enable low ENABLE ON=LOW
}

void loop() 
{
  
  Serial.println("Loop 200 steps (1 rev)");
  fullstep(3,clockwise);
  fullstep(3,counterwise);
  Serial.println("Pause");
  delay(1000); // pause one second
}


/*===============================================================Funciones============================================*/
int fullstep(int x,bool direc){
  digitalWrite(Enable,LOW); // Set Enable low
  digitalWrite(Direction,direc); // Set Dir high
  while( _temp<x){
    for(_step = 0; _step < 200; _step++) // Loop 200 times
  {
    digitalWrite(Step,HIGH); // Output high
    delayMicroseconds(1000); // Wait
    digitalWrite(Step,LOW); // Output low
    delayMicroseconds(1000); // Wait
  }
  _temp++;
   delay(1000);
  }
  _temp=0;
  }
