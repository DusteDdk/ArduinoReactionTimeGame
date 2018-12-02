Teh ReadMeh
===========
This is silly.

The c_cpp_properties.json is probably the most useful file here..
It shows how I convinced the visual-studio-code-arduino-plugin-thing to do nice completion.


The other part you'll like to know, is to add a few line in your vscode usersettings.json file:
"C_Cpp.intelliSenseEngineFallback": "Disabled",
"C_Cpp.intelliSenseEngine": "Tag Parser",
"arduino.path": "/home/dusted/data/Misc/bin/arduino-1.8.6/"

Then you can build your project using "ctrl+alt+u" when the main.ino file is open.
This project will work with the normal Arduino IDE as well, of course.

About
=====
A multiplayer-reaction-tmie-game thing.

Electronics
===========
Connect a led to pin 9, it goes low, the LED turns on.

Usage
=====
Nobody yet knows how to use the thing.