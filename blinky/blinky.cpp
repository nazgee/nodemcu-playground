#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMesh.h>

unsigned int request_i = 0;
unsigned int response_i = 0;

String manageRequest(String request);

/* Create the mesh node object */
ESP8266WiFiMesh mesh_node = ESP8266WiFiMesh(ESP.getChipId(), manageRequest);

#define LEDON() digitalWrite(LED_BUILTIN, LOW)
#define LEDOFF() digitalWrite(LED_BUILTIN, HIGH)

void blink(int blinksNumber) {
	const int offtime = 100;
	const int ontime = 30;


	if (!digitalRead(LED_BUILTIN)) {
		LEDOFF();
		delay(offtime);
	}

	for (int i = 0; i < blinksNumber; i++) {
		LEDON();
		delay(ontime);
		LEDOFF();

		if (i == blinksNumber - 1)
			break;

		delay(offtime);
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

	blink(3);

	return response;
}

void setup()
{
	Serial.begin(115200);
	delay(10);

	pinMode(LED_BUILTIN, OUTPUT);
	blink(5);

	Serial.println();
	Serial.println();
	Serial.printf("Setting up mesh node... me=%d\r\n", ESP.getChipId());


//	randomSeed(ESP.getChipId());
	/* Initialise the mesh node */
	mesh_node.begin();
}

void loop()
{
	/* Accept any incoming connections */
	//Serial.println("accept...");
	mesh_node.acceptRequest();

	static int acceptsNumber = random(25, 100);
	if (acceptsNumber == 0) {
		acceptsNumber = random(25, 100);

		/* Scan for other nodes and send them a message */
		char request[60];
		sprintf(request, "Hello world request #%d from Mesh_Node%d.", request_i++, ESP.getChipId());
		Serial.println("scan...");
		LEDON();
		mesh_node.attemptScan(request);
		LEDOFF();
		Serial.println("scan completed!");
	}
	acceptsNumber--;

	delay(100);
}
