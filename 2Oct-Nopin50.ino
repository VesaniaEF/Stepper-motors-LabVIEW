#include <Servo.h>
#include <Stepper.h>
 

#define STEP 2    // pin STEP de A4988 a pin 2
#define DIR 5     // pin DIR de A4988 a pin 5
#define SLEEP 24  // pin sleep de A4988 a pin 6
#define movmotor 44 
#define condition 46
Servo motor;
int dato = 0;
int permiso_flame = 0;
int permiso_motor = 0;
int mediciones = 0;
int ejecucion = 0;
int pasos = 0;
int flame = 0;
int contador = 0;
int tiempo = 0;
int b1 = 0;
int b2 = 0;
 

void setup() {
  Serial.begin(9600);
  pinMode(STEP, OUTPUT);   // pin 2 como salida
  pinMode(DIR, OUTPUT);    // pin 5 como salida
  pinMode(SLEEP, OUTPUT);  // pin 6 como salida

  pinMode(8, OUTPUT);  // blanco
  pinMode(7, INPUT);
  pinMode(50, OUTPUT);
  pinMode(40, INPUT);
  pinMode(movmotor,OUTPUT);
  pinMode(condition, OUTPUT);
  motor.attach(3);
}

void loop() {
  int flame1 = digitalRead(40);  // lectura de los pines 40, 41, 42 que corresponden a los casos enviados desde labview
contador=0;
tiempo=0;
  

  digitalWrite(SLEEP, LOW);  // motor apagado
  digitalWrite(movmotor, HIGH);    //movmotor apagado
  digitalWrite(condition, HIGH);
int condition2=1;  
  if (flame1 == HIGH ) {         // si ocurre algun evento ==1 en alguno de los casos entra en el if y sellecciona la cantidad de mediciones, pasos y habilita el while
                             //if (Serial.available() > 0 ) {
                             // int datoo=Serial.read();
                             // dato = Serial.parseInt();
          int contador=1;
          b1=1;
          delay(200);

          while (tiempo < 2000) {
              delay(1);
           int   flame1 = digitalRead(40);
              tiempo=tiempo+1;
              if (flame1 == HIGH ) {
              contador++;
              delay(150);
              }
 
            }



    if (contador == 1) {  // seleccion de casos e inicio de variables
      mediciones = 90;
      ejecucion = 1;
      pasos = 200;

    } else if (contador == 2) {
      mediciones = 180;
      ejecucion = 1;
      pasos = 100;

    } else if (contador == 3) {
      mediciones = 360;
      ejecucion = 1;
      pasos = 50;

    }

  
    digitalWrite(SLEEP, HIGH);  // prender motor
    while (ejecucion == 1) {
      
      for (int j = 0; j < mediciones; j++)  // ciclo repetido la cantidad de mediciones
      {
        digitalWrite(DIR, LOW);            // se escoge la direccion de giro de motor
                  digitalWrite(movmotor, HIGH);
        for (int i = 0; i < pasos; i++) {  // movimiento de motor. 100 pasos equivalen a 1 grado

          digitalWrite(STEP, HIGH);        // nivel alto
          delay(1);                        // por 1 ms
          digitalWrite(STEP, LOW);         // nivel bajo
          delay(1);                        // por 1 ms
        }
        digitalWrite(movmotor, LOW);        
        delay(200);
        digitalWrite(50, HIGH);
        delay(2); 
        digitalWrite(50, LOW);
        delay(2); 
        digitalWrite(movmotor, LOW);        
        delay(200);
                // delay 90 ms (90MED), 290ms (180MED), 390ms(360med)
      }
      ejecucion = 0;
    }
    // movimiento de regreso de motor
    digitalWrite(movmotor, HIGH);
    delay(3000);
    digitalWrite(DIR, LOW);
    for (int j = 0; j < mediciones; j++) {
      for (int i = 0; i < pasos; i++) {
        digitalWrite(STEP, HIGH);
        delay(1);
        digitalWrite(STEP, LOW);
        delay(1);
      }
    }
    digitalWrite(SLEEP, LOW);  // apagar motor motor para no sobrecalentarlo
  }                         // end if de deteccion


}  // end loop