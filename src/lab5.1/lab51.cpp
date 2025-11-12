// #include <LiquidCrystal.h>

// // ==================== LCD MODULE ====================
// LiquidCrystal lcd(13, 12, 7, 6, 5, 4);

// // ==================== RELAY / LED MODULE ====================
// const int relayPin = 8;

// // ==================== SENSOR (TMP36) ====================
// const int tmpPin = A0;

// // ==================== CONTROL VARIABLES ====================
// float setPoint = 25.0;     // Температура уставки (°C)
// float hysteresis = 2.0;    // Гистерезис (°C)
// float currentTemp = 0.0;   // Текущее значение температуры
// bool relayState = false;   // Состояние реле

// // ==================== INITIALIZATION ====================
// void initializeHardware() {
//   pinMode(relayPin, OUTPUT);
//   digitalWrite(relayPin, LOW);
//   lcd.begin(16, 2);
//   lcd.clear();
//   lcd.print("System Ready");
//   delay(1000);
//   lcd.clear();
//   Serial.println("System initialized.");
//   Serial.println("Commands:");
//   Serial.println("SET <value> - set temperature");
//   Serial.println("HYS <value> - set hysteresis");
// }

// // ==================== READ TEMPERATURE ====================
// float readTemperature() {
//   int raw = analogRead(tmpPin);
//   float voltage = raw * (5.0 / 1023.0);
//   float tempC = (voltage - 0.5) * 100.0;
//   return tempC;
// }

// // ==================== CONTROL LOGIC ====================
// void controlHeater() {
//   if (currentTemp < setPoint - hysteresis / 2) {
//     relayState = true;
//     digitalWrite(relayPin, HIGH);
//   } 
//   else if (currentTemp > setPoint + hysteresis / 2) {
//     relayState = false;
//     digitalWrite(relayPin, LOW);
//   }
// }

// // ==================== DISPLAY ON LCD ====================
// void updateDisplay() {
//   lcd.setCursor(0, 0);
//   lcd.print("Temp:");
//   lcd.print(currentTemp, 1);
//   lcd.print((char)223); // символ градуса
//   lcd.print("C    ");

//   lcd.setCursor(0, 1);
//   lcd.print("Set:");
//   lcd.print(setPoint, 1);
//   lcd.print((char)223);
//   lcd.print("C ");
//   lcd.print(relayState ? "ON " : "OFF");
// }

// // ==================== SERIAL COMMAND HANDLER ====================
// void processCommands() {
//   if (Serial.available() > 0) {
//     String command = Serial.readStringUntil('\n');
//     command.trim();

//     if (command.startsWith("SET")) {
//       setPoint = command.substring(3).toFloat();
//       Serial.print("SetPoint updated: ");
//       Serial.println(setPoint);
//     } 
//     else if (command.startsWith("HYS")) {
//       hysteresis = command.substring(3).toFloat();
//       Serial.print("Hysteresis updated: ");
//       Serial.println(hysteresis);
//     } 
//     else {
//       Serial.println("Unknown command. Use:");
//       Serial.println("SET <value> or HYS <value>");
//     }
//   }
// }

// // ==================== MAIN PROGRAM ====================
// void setup() {
//   Serial.begin(9600);
//   initializeHardware();
// }

// void loop() {
//   currentTemp = readTemperature();
//   controlHeater();
//   updateDisplay();
//   processCommands();

//   // Для Arduino Plotter (текущая температура и уставка)
//   Serial.print(currentTemp);
//   Serial.print(",");
//   Serial.println(setPoint);

//   delay(500);
// }