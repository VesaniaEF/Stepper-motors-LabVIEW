#include <Servo.h>

#define STEP 2  // pin STEP de A4988 a pin 2
#define DIR 5   // pin DIR de A4988 a pin 5
#define SLEEP 24   // pin sleep de A4988 a pin 6
Servo motor;
int dato = 0;
int permiso_flame=0;
int permiso_motor=0;
int mediciones=0;
int contador;
int ejecucion=0;
int pasos=0;
int flame=0;
int delay1=0;
int delay2=0;
int delay3=0;

void setup() {
  Serial.begin(9600);
  pinMode(STEP, OUTPUT);  // pin 2 como salida
  pinMode(DIR, OUTPUT);   // pin 5 como salida
  pinMode(SLEEP, OUTPUT);   // pin 6 como salida
  pinMode(2, OUTPUT); // LED rojo
  pinMode(30, OUTPUT); // LED amarillo
  pinMode(8 , OUTPUT); // LED blanco
  pinMode(7, INPUT);
  pinMode(50, OUTPUT);  //Va al Trigger del FLAME
  pinMode(40, INPUT);
  motor.attach(3);
}

void loop() {
  int flame1=digitalRead(40);                 // lectura de los pines 40, 41, 42 que corresponden a los casos enviados desde labview
  int flame2=digitalRead(41);
  int flame3=digitalRead(42);

  digitalWrite(SLEEP, LOW);                   // motor apagado
if (flame1==1 || flame2==1 || flame3==1){     // si ocurre algun evento ==1 en alguno de los casos entra en el if y sellecciona la cantidad de mediciones, pasos y habilita el while 
  //if (Serial.available() > 0 ) {
   // int datoo=Serial.read();
   // dato = Serial.parseInt();

    if (flame1 == 1) {                        // seleccion de casos e inicio de variables 
      digitalWrite(2, HIGH);      delay(200);      digitalWrite(2, LOW);
     mediciones=90;
     ejecucion=1;
     pasos=200;
    delay1=1;     
    } else if (flame2 == 1) {
      digitalWrite(2, HIGH);      delay(200);      digitalWrite(2, LOW);
      delay(200);
      digitalWrite(2, HIGH);      delay(200);      digitalWrite(2, LOW);
    mediciones=180;
    ejecucion=1;
    pasos=100;
    delay2=1;
    } else if (flame3 == 1) {
      digitalWrite(2, HIGH);      delay(200);      digitalWrite(2, LOW);
      delay(200);
      digitalWrite(2, HIGH);      delay(200);      digitalWrite(2, LOW);
      delay(200);
      digitalWrite(2, HIGH);      delay(200);      digitalWrite(2, LOW);
    mediciones=360;
    ejecucion=1;
    pasos=50;
    delay3=1;
    } 

        digitalWrite(SLEEP, HIGH);          // prender motor
    while(ejecucion==1)
    {
    digitalWrite(50, HIGH);                 // señal en alto en pin 50
        for(int j=0;j<mediciones; j++)      // ciclo repetido la cantidad de mediciones
        {
          digitalWrite(50, LOW);            //señal en bajo en pin 50
          digitalWrite(DIR, LOW);	          // se escoge la direccion de giro de motor
            for (int i = 0; i < pasos; i++) {     // movimiento de motor. 100 pasos equivalen a 1 grado
            digitalWrite(STEP, HIGH);       // nivel alto
            delay(1);                       // por 1 ms
            digitalWrite(STEP, LOW);        // nivel bajo 
            delay(1);                       // por 1 ms
            
            }
            if (delay1==1)  {delay(90);  } 
            else if     (delay2==1)  {delay(45);  }   
            else     (delay3==1)  {delay(20);  }                                          // delay 90 ms
            digitalWrite(50,HIGH);          // señal en alto para el flame
            digitalWrite(30,HIGH);          // señal en alto en led indicador
            delay(5);
            digitalWrite(50, LOW);          // señal en bajo para el flame
            digitalWrite(30,LOW);           // señal en bajo en led indicador
            delay(5);
        }
ejecucion=0;

    }  
                                            // movimiento de regreso de motor
            delay(3000);
            digitalWrite(DIR, LOW);		 
            for(int j=0;j<mediciones; j++){
            for (int i = 0; i < pasos; i++) {  
            digitalWrite(STEP, HIGH);   
            delay(1);                  
            digitalWrite(STEP, LOW);    
            delay(1);                  
            }

        }
        digitalWrite(SLEEP, LOW);   // apagar motor motor para no sobrecalentarlo
  } // end if de deteccion 
 
 
} // end loop
