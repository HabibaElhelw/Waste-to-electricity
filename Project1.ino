#define valve1 2
#define valve2 3
#define valve3 4
#define pump 5
#define methane_sensor A0
#define temp_sensor A1
#define RELAY_PIN 8  // the Arduino pin, which connects to the IN pin of relay

float temp;
int tempPin = 0;
int threshold_value_max = 220; // A variable to store digital output of MQ4
int threshold_value_min = 100; // A variable to store digital output of MQ4
int gas_value;

void setup() {
  pinMode(valve1, OUTPUT); // Configure D8 pin as a digital input pin
  pinMode(valve2, OUTPUT); // Configure D8 pin as a digital input pin
  pinMode(valve3, OUTPUT); // Configure D8 pin as a digital input pin
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(pump, OUTPUT);
  Serial.begin(9600);
}
void loop()
{
  temp_reading();
  gas_reading();
  if (temp > 540 && gas_value > threshold_value_max)
  {
    digitalWrite(valve1, HIGH);
    delay(7000);
    digitalWrite(valve1, LOW);
    while (gas_value > threshold_value_min)
    {
      digitalWrite(valve2, HIGH);
      digitalWrite(pump, HIGH);
    }
    digitalWrite(valve2, LOW);
    digitalWrite(pump, LOW);
    digitalWrite(valve3, HIGH);
    delay(60000);
    digitalWrite(valve3, LOW);
  }
  else
  {
    digitalWrite(valve1, LOW);
    digitalWrite(valve2, LOW);
  }
}
void temp_reading() {
  temp = analogRead(temp_sensor);
  // read analog volt from sensor and save to variable temp
  temp = temp * 0.48828125;
  // convert the analog volt to its temperature equivalent
  Serial.print(temp); // display temperature value
}
/* MQ-4 Methane Sensor module with Arduino */
/* Interfacing with Arduino */

void gas_reading()
{
  gas_value = analogRead(methane_sensor); //Read digital output of MQ4 sensor
}
