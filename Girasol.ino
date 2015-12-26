/*
proyecto GIRASOL
Flavio Ragazzi enero 2015
Como esta experiencia esta realizada en el hemisferio Sur debe orientarse para que la posición 90 del servomotor Horizontal apunte hacia el Norte.
Deberá invertise segun el hemisferio donde se realice.
Componentes
SENSORES 4 LDR conectados a entradas analogicas desde A0 hasta A3
ACTUADORES 2 servomotores uno para movimiento horizontal Este_Oeste (Servo 2) y el segundo para elevacion (servo1)
Adafruit Motor/Stepper/Servo Shield (puede obviarse) 
lse incluye libreria Servo.h (para ser usada con el shield anterior)
*/
// se declara variables  para las entradas analogicas de los LDR
  int este=0; 
  int oeste =1;
  int sube=2;
  int baja=3;
  int pos =90; //posición inicial del servomotor, NORTE
  int alt=90; // posición inicial del servomotor, nivel cero, horizontal
  int tolerancia =3; //define la tolerancia entre las diferencia de lecturas en cada eje

#include <Servo.h>  //se incluye libreria
 Servo myservoH;     // se crea objeto "myservoH"horizontal
 Servo myservoV;  // se crea objeto "myservoV"vertical

void setup(){
  Serial.begin (9600);
  myservoH.attach(9);      //declaracion de la salida de la señal
 myservoV.attach(10);  //declaracion de la salida de la señal
  myservoH.write(pos);     // se ubica el motor al NORTE
    delay(1000);        //espera de inicio entre los servos
  myservoV.write(alt);  // se ubica el motor en nivel cero
  delay(5000);  //delay para dar tiempo y orientar al norte los sensores
}

void loop(){
 //sensa los LDR
  int val_e= analogRead(este);
  int val_o=analogRead(oeste);
   int val_s =analogRead(sube);
   int val_b =analogRead(baja);
   //imprime lectura
  Serial.print ("OESTE:  ");
  Serial.print (val_o);
  Serial.print("   ");
  Serial.print ("ESTE:  ");
  Serial.println (val_e);

  Serial.print ("ARRIBA:  ");
  Serial.print (val_s);
  Serial.print("   ");
  Serial.print ("ABAJO:  ");
  Serial.println (val_b);


  //se hace la diferencia entre las lecturas en cada uno de los ejes
  int difH= val_e-val_o;
  Serial.println (difH);
  int difV= val_s-val_b;
  Serial.println (difV);
  delay (1000);

//se toma la desicion de girar  al Este o al Oeste hasta que no haya diferencia de lecturas
  if (difH>tolerancia){
  pos = pos-(difH/4);
  myservoH.write (pos);
}
else {
  if(difH<-tolerancia){
  pos = pos+(-difH/4);
  myservoH.write (pos);
}
 delay (200);
 }
// se toma la desicion de subir o bajar hasta que no haya diferencia de lecturas
  if (difV>tolerancia){
    alt = alt-(difV/4);
    myservoV.write (alt);
}
else {
  if(difV<-tolerancia){
  alt = alt+(-difV/4);
  myservoV.write (alt);
}
 }
}
