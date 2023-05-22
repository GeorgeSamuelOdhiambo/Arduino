// Water flow sensor pins
const int flowSensorPin = 2;   // Attach the signal pin of the water flow sensor to pin 2
unsigned long previousMillis = 0;
const unsigned long interval = 60000;  // 24 hours in milliseconds


// Variables for flow rate and volume
volatile int flowRate;
volatile unsigned int totalMilliLitres;
volatile unsigned long totalMillis;
float totalM;

void setup() {
  // Initialize the serial communication
  Serial.begin(9600);
  
  // Configure the flow sensor pin as input with internal pull-up resistor
  pinMode(flowSensorPin, INPUT_PULLUP);
  
  // Configure the interrupt for the flow sensor pin
  attachInterrupt(digitalPinToInterrupt(flowSensorPin), pulseCounter, FALLING);
  
  // Initialize the flow rate and volume variables
  flowRate = 0;
  totalMilliLitres = 0;
  totalMillis = 0;
  
  // Print the column headers on the serial monitor
  Serial.println("Flow Rate (L/min)\tTotal Volume (L)");
}

void loop() {
  // Calculate the flow rate in liters per minute
  float flowRateLitersPerMinute = ((1000.0 / (millis() - totalMillis)) * flowRate) / 60.0;
  
  // Update the total volume in liters
  float totalVolumeLiters = totalMilliLitres / 1000.0;
  
  // Print the flow rate and total volume on the serial monitor
  if(flowRateLitersPerMinute != 0.00 && totalVolumeLiters != 0.00){
  Serial.print(flowRateLitersPerMinute);
  Serial.print("\t\t\t");
  Serial.println(totalVolumeLiters);
  totalM = totalM + totalVolumeLiters;
  }
  
   unsigned long currentMillis = millis();
  
  // Check if 24 hours have passed
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;  // Reset the previous time
    Serial.println("\t\t\t");
    Serial.print(totalM,2);
    Serial.print("\t");
    Serial.print("Liters used in the last 1 minute");
    totalM = 0;  //Reset total to 0
  }

  // Reset the flow rate and volume variables
  flowRate = 0;
  totalMilliLitres = 0;
  totalMillis = millis();
  
  // Delay for 1 second
  delay(10);
}

void pulseCounter() {
  // Increment the flow rate and total volume counters
  flowRate++;
  totalMilliLitres++;
}
