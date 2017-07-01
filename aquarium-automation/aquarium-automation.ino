/* Felipe Arcaro - Automatizacao Aquario
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 Modificado em 21 Mai 2017
 by Felipe Arcaro
*/

//incluindo biblioteca do motor servo e do visor lcd

#include <Servo.h>
#include <LiquidCrystal.h>

#include <OneWire.h>
#include <DallasTemperature.h>
 
// Porta do pino de sinal do DS18B20
#define ONE_WIRE_BUS 10
 
// Define uma instancia do oneWire para comunicacao com o sensor
OneWire oneWire(ONE_WIRE_BUS);
 
// Armazena temperaturas minima e maxima
float tempMin = 999;
float tempMax = 0;
 
DallasTemperature sensors(&oneWire);
DeviceAddress sensor1;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


void setup() {
  
  Serial.begin(9600);
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
   // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.clear();
  lcd.print("Initializing...");
  delay(3000);


   Serial.begin(9600);
  sensors.begin();
  // Localiza e mostra enderecos dos sensores
  Serial.println("Localizando sensores DS18B20...");
  Serial.print("Foram encontrados ");
  Serial.print(sensors.getDeviceCount(), DEC);
  Serial.println(" sensores.");
  if (!sensors.getAddress(sensor1, 0)) 
     Serial.println("Sensores nao encontrados !"); 
  // Mostra o endereco do sensor encontrado no barramento
  Serial.print("Endereco sensor: ");
  mostra_endereco_sensor(sensor1);
  Serial.println();
  Serial.println();
  lcd.begin(16, 2);
  
}


void mostra_endereco_sensor(DeviceAddress deviceAddress)
{
  for (uint8_t i = 0; i < 8; i++)
  {
    // Adiciona zeros se necessário
    if (deviceAddress[i] < 16) Serial.print("0");
    Serial.print(deviceAddress[i], HEX);
  }
}

void loop() {
    int temp = analogRead(A0);
    myservo.write(180);              // tell servo to go to position in variable 'pos'
    delay(1000);
    myservo.write(0);

    
    for (double i= 28800000; i >=1000; i=i-1000){
    lcd.setCursor(0, 0);
    lcd.print("Felipe Aquarium");
    
    
    lcd.setCursor(10, 1);
    lcd.print("F: ");
    lcd.setCursor(12, 1);
    lcd.print(i/1000, DEC/1000);

      // Le a informacao do sensor
   sensors.requestTemperatures();
  float tempC = sensors.getTempC(sensor1);
  // Atualiza temperaturas minima e maxima
  if (tempC < tempMin)
  {
    tempMin = tempC;
  }
  if (tempC > tempMax)
  {
    tempMax = tempC;
  }
  // Mostra dados no serial monitor
  Serial.print("Temp C: ");
  Serial.print(tempC);
  Serial.print(" Min : ");
  Serial.print(tempMin);
  Serial.print(" Max : ");
  Serial.println(tempMax);
   
  // Mostra dados no LCD  
 
  //lcd.print("Temp.:       ");
  //Simbolo grau
  //lcd.write(223);
  //lcd.print("C");


  lcd.setCursor(0, 1);
    lcd.print("T: ");
    lcd.setCursor(2, 1);
    lcd.print(tempC);
    lcd.setCursor(7, 1);
    lcd.write(223);
    lcd.print("C");
  
  delay(3000);


    

    delay(1000);
    lcd.clear();
  } 
    lcd.setCursor(0, 1);
    lcd.print("Feeding...");



    
    delay(1000);
    lcd.clear();
  }
   
 
 




