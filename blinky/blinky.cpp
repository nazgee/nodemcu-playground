#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMesh.h>

unsigned int request_i = 0;
unsigned int response_i = 0;

String manageRequest(String request);

/* Create the mesh node object */
ESP8266WiFiMesh mesh_node = ESP8266WiFiMesh(ESP.getChipId(), manageRequest);


void blink(int blinksNumber) {
	for (int i = 0; i < blinksNumber; i++) {
		digitalWrite(LED_BUILTIN, LOW);
		delay(30);
		digitalWrite(LED_BUILTIN, HIGH);

		if (i == blinksNumber - 1)
			break;

		delay(100);
	}
}

/**
 * Callback for when other nodes send you data
 *
 * @request The string received from another node in the mesh
 * @returns The string to send back to the other node
 */
String manageRequest(String request)
{
	/* Print out received message */
	Serial.print("received: ");
	Serial.println(request);

	/* return a string to send back */
	char response[60];
	sprintf(response, "Hello world response #%d from Mesh_Node%d.", response_i++, ESP.getChipId());

	blink(1);

	return response;
}

void setup()
{
	Serial.begin(115200);
	delay(10);

	pinMode(LED_BUILTIN, OUTPUT);

	Serial.println();
	Serial.println();
	Serial.printf("Setting up mesh node... me=%d\n", ESP.getChipId());

	/* Initialise the mesh node */
	mesh_node.begin();
}

void loop()
{
	/* Accept any incoming connections */
	mesh_node.acceptRequest();

	/* Scan for other nodes and send them a message */
	char request[60];
	sprintf(request, "Hello world request #%d from Mesh_Node%d.", request_i++, ESP.getChipId());

	blink(2);

	mesh_node.attemptScan(request);
	delay(1000);
}
