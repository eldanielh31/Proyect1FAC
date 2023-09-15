#include <Arduino.h>

const int trigPin = 9;  // Pin TRIG del sensor HC-SR04 conectado al pin 9 de Arduino
const int echoPin = 10; // Pin ECHO del sensor HC-SR04 conectado al pin 10 de Arduino

const int outBit2 = 8;
const int outBit1 = 7;
const int outBit0 = 6;

void mapToGrayCode2(int num, int &bit2, int &bit1, int &bit0)
{
  // Verificar si el número está en el rango válido (0-20)
  if (num < 0 || num > 20)
  {
    bit2 = 0; // Valores inválidos
    bit1 = 0;
    bit0 = 0;
    return;
  }

  // Mapear el rango 0-20 a 0-7
  int mappedNum = map(num, 0, 20, 0, 7);

  // Crear una tabla de conversión de código Gray para números del 0 al 7
  int grayCodeTable[] = {0, 1, 3, 2, 6, 7, 5, 4};

  // Obtener el código Gray correspondiente al número mapeado
  int grayCode = grayCodeTable[mappedNum];

  // Extraer los bits individuales del código Gray
  bit2 = (grayCode >> 2) & 1;
  bit1 = (grayCode >> 1) & 1;
  bit0 = grayCode & 1;
}

void setup()
{
  Serial.begin(9600); // Inicializamos la comunicación serial
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(outBit0, OUTPUT);
  pinMode(outBit1, OUTPUT);
  pinMode(outBit2, OUTPUT);
}

void loop()
{
  long duration;
  int distance;

  // Generamos un pulso corto en el pin TRIG
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Medimos la duración del pulso en el pin ECHO
  duration = pulseIn(echoPin, HIGH);

  // Convertimos la distancia en centímetros usando la fórmula de tiempo y velocidad del sonido
  distance = (duration * 0.034) / 2;

  int bit2, bit1, bit0;

  mapToGrayCode2(distance, bit2, bit1, bit0);

  // Serial.println(code, BIN);
  Serial.print("Bit 2: ");
  Serial.println(bit2);
  Serial.print("Bit 1: ");
  Serial.println(bit1);
  Serial.print("Bit 0: ");
  Serial.println(bit0);

  digitalWrite(outBit0, bit0);
  digitalWrite(outBit1, bit1);
  digitalWrite(outBit2, bit2);

  // Serial.println(distance);

  delay(500); // Esperamos medio segundo antes de realizar otra lectura
}
