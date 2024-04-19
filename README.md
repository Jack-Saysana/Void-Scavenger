# Void Scavenger
Void Scavenger is a rogue-like dogfighting and first-person-shooter inspired by many popular games such as Star Wars:tm: Squadrons and Doom:tm:. The game takes the player through intense firefights and fun, yet challenging, flights through the stars on their path to upgrade their ship and fend off enemies and aliens for as long as possible.

## Building
After cloning the repository, run ```cmake .``` in the project root directory to created the Makefile (Linux) or Ninja build file (Windows). Assuming that the generation completes successfully, run ```make``` on Linux or ```ninja``` on Windows to build the Void Scavenger binary.

#### Supported Platforms:
Linux (Debian-like distributions)
<br>
_Note: Support for other Linux distributions has not been tested_
<br>
Windows (Mingw-w64)
<br>

## License
The Void Scavenger is provided under the MIT license. However, the assets and specific .dll files are not provided to ensure that the source code is still MIT-compatible.

## Creating Assets
Careful inspection of the source code with the help of this [custom .obj exporter for Blender](https://github.com/Jack-Saysana/Blender-Custom-Obj-Exporter) will allow the game to be in a playable state. Assets which have not been exported with this script from Blender are not expected by the engine and will not function properly. In addition, this [font importer](https://github.com/Jack-Saysana/Font-Importer) can be used to create font glyphs which the engine expects. For additional information on the engine behind Void Scavenger, visit the [engine GitHub page](https://github.com/Jack-Saysana/OpenGL-Graphics-Engine).
