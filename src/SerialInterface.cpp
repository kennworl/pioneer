#include "SerialInterface.h"

bool landingGearButtonPressed;
bool landingGearButtonReleasedEvent;
bool pitchUp;
bool pitchDown;
bool yawLeft;
bool yawRight;
bool levelPitchButtonPressed;
bool levelPitchButtonReleasedEvent;


// This is a utility class which maintains a state of all input controls.
// Input state is kept so that it can be directly polled by the Lua scripts.
SerialInterface::SerialInterface()
{
	landingGearButtonPressed = false;
	landingGearButtonReleasedEvent = false;
	pitchUp = false;
	pitchDown = false;
	yawLeft = false;
	yawRight = false;
	levelPitchButtonPressed = false;
	levelPitchButtonReleasedEvent = false;

}

// Destructor for SerialInterface.  No use for it just yet.
SerialInterface::~SerialInterface() {};

void SerialInterface::ParseSerialInput(char* buffer, int buflen) {
	if (buflen == 0) return;
	int counter = 0;
	bool loopFinished = false;
	while (!loopFinished) {
		if ((buflen - counter) > 4 && buffer[counter] == 'l' && buffer[counter + 1] == 'g' && buffer[counter + 2] == 'b' && buffer[counter + 4] == '~') {
			// we have a landing gear input
			if (buffer[counter + 3] == 'u') {               // if the button is released
				if (landingGearButtonPressed) {
					landingGearButtonReleasedEvent = true;
				}
				landingGearButtonPressed = false;
			}
			else landingGearButtonPressed = true;        // else it is pressed
			counter += 5;
		}
		else if ((buflen - counter) > 4 && buffer[counter] == 'j' && buffer[counter + 1] == '1' && buffer[counter + 4] == '~') {
			// we have a joystick 1 control input
			if (buffer[counter + 2] == 'p' && buffer[counter + 3] == 'u') {               // if joystick1 is pushed up (Pitch up)
				pitchUp = true;
				pitchDown = false;
			}
			else if (buffer[counter + 2] == 'p' && buffer[counter + 3] == 'd') {               // if joystick1 is pushed down (Pitch down)
				pitchUp = false;
				pitchDown = true;
			}
			else if (buffer[counter + 2] == 'p' && buffer[counter + 3] == 'n') {               // if joystick1 is not up or down (Pitch neutral)
				pitchUp = false;
				pitchDown = false;
			}
			else if (buffer[counter + 2] == 'y' && buffer[counter + 3] == 'l') {               // if joystick1 is pushed left (Yaw left)
				yawLeft = true;
				yawRight = false;
			}
			else if (buffer[counter + 2] == 'y' && buffer[counter + 3] == 'r') {               // if joystick1 is pushed left (Yaw left)
				yawLeft = false;
				yawRight = true;
			}
			else if (buffer[counter + 2] == 'y' && buffer[counter + 3] == 'n') {               // if joystick1 is not left (Yaw neutral)
				yawLeft = false;
				yawRight = false;
			}
			else if (buffer[counter + 2] == 'b' && buffer[counter + 3] == 'd') {               // if joystick1 button pressed
				levelPitchButtonPressed = true;
			}
			else if (buffer[counter + 2] == 'b' && buffer[counter + 3] == 'u') {               // if joystick1 is not pressed
				if (levelPitchButtonPressed) {
					levelPitchButtonReleasedEvent = true;
				}
				levelPitchButtonPressed = false;
			}
			counter += 5;
		}
		if ((buflen == counter)) loopFinished = true;
	}
}

bool SerialInterface::isUnhandledLandingGearButtonReleased() {
	if (landingGearButtonReleasedEvent) {
		landingGearButtonReleasedEvent = false;
		return true;
	}
	return false;
}

bool SerialInterface::isUnhandledLevelPitchButtonReleased() {
	if (levelPitchButtonReleasedEvent) {
		levelPitchButtonReleasedEvent = false;
		return true;
	}
	return false;
}

bool SerialInterface::isPitchUp() { return pitchUp; }
bool SerialInterface::isPitchDown() { return pitchDown; }
bool SerialInterface::isYawLeft() { return yawLeft; }
bool SerialInterface::isYawRight() { return yawRight; }