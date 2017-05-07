set(blinky_SRCS blinky.cpp)
set(blinky_ARDLIBS ESP8266WiFiMesh)
#set(blinky_LIBS ESP8266WiFiMesh)

arduino_debug_on()
generate_arduino_firmware(blinky)
