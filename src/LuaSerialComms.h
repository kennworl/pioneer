// Copyright © 2008-2017 Pioneer Developers. See AUTHORS.txt for details
// Licensed under the terms of the GPL v3. See licenses/GPL-3.txt

#ifndef _LUASERIALCOMMS_H
#define _LUASERIALCOMMS_H

#include <string>

namespace LuaSerialComms {
	void Register();
}

// These are for checking if the output strings to Arduino have changed and should be sent.
static std::string heading = "";
static std::string landingGear = "";

#endif

