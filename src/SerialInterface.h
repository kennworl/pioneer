#ifndef _SERIAL_INTERFACE_H
#define _SERIAL_INTERFACE_H

class SerialInterface {
public:

	// getters for Lua
	static bool isUnhandledLandingGearButtonReleased();
	static bool isUnhandledLevelPitchButtonReleased();
	static bool isPitchUp();
	static bool isPitchDown();
	static bool isYawLeft();
	static bool isYawRight();

	//Initialize Serial Interface map with default values on startup of game (assuming all buttons are released)
	SerialInterface();

	//Destructor
	~SerialInterface();

	//Parse any input data from the Serial Port
	static void ParseSerialInput(char * buffer, int buflen);
};

#endif _SERIAL_INTERFACE_H
