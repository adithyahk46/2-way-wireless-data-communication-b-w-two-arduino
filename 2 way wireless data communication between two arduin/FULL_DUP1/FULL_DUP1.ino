#include <RH_ASK.h>

#define ledt 4
#define ledR 5
RH_ASK rf_driver; // Initialize RF transmitter/receiver object
String message = ""; // Create an empty string to hold the message

void setup() {
  // Initialize serial communication at a baud rate of 9600
  Serial.begin(9600);

  // Initialize RF transmitter/receiver with a data rate of 2000 bps
  if (!rf_driver.init()) {
    Serial.println("RF initialization failed.");
    while (1); // Loop forever if initialization fails
  }
}

void loop() {
  // Read a message from the serial monitor
  if (Serial.available()) {
    message = ""; // Reset the message string
    while (Serial.available()) {
      message += Serial.readStringUntil('\n'); // Read a line and add it to the message
    }

    // Transmit the message through the RF transmitter
    rf_driver.send((uint8_t*)message.c_str(), message.length());
    rf_driver.waitPacketSent(); // Wait for the transmission to complete

    // Print the sent message on the serial monitor
    Serial.print("Sent message: ");
    Serial.println(message);
    digitalWrite(ledt,HIGH);
    delay(200);
    digitalWrite(ledt,LOW);
  }

  // Receive a message through the RF receiver
  uint8_t received_message[64]; // Create a buffer to hold the received message
  uint8_t received_message_length = sizeof(received_message);

  if (rf_driver.recv(received_message, &received_message_length)) {
    // Convert the received message to a string
    String received_string = "";
    for (int i = 0; i < received_message_length; i++) {
      received_string += (char)received_message[i];
    }

    // Print the received message on the serial monitor
    Serial.print("Received message: ");
    Serial.println(received_string);
    digitalWrite(ledR,HIGH);
    delay(200);
    digitalWrite(ledR,LOW);
   
  }
    
   
}
