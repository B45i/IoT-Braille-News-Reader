# **IoT Braille News Reader**

Latest technology offers advancement to the world. But the blind people are still in the midst of difficulties where they are unable to know the current affairs. We are going to implement a device known as IoT Braille News Reader which will help the blind to be aware about the surroundings they were being.


It took a text file and displayed the contents in the form of Braille. Now existing system cannot have the opportunity to change the rate at which the news articles read could be either too fast or too slow for users. The proposed system contains a button in the Braille Reader so that it can vary the speed of the news as comfortable for the user.

The system consists of a microcontroller which deals internet login and helps to retrieve news from a cloud. The Braille script character is replaced by an electromechanical device.
The main advantage of our system is that it can be easily used since it produces as much as simple and the cost is also less.
For the last few years the news are heard when the friends or others are read thus it really can change someone’s life.

## **Technical details**
Heart of this device is an **ESP8266 Micro controller**, which is a low cost 32 bit micro-controller with inbuilt WiFi capabilities.
The ESP8266 fetches latest news from a service called **newsapi.org**.
The news is in JSON format, it need to be parsed and converted to braille format on the micro-controller.
The braille is displayed using a 3*2 matrix of solenoid push pulls.
The user can put their hand upon the device and get a tactile feed back.
There is knob to adjust the reading speed. There are two buttons to change the current news being displayed and news source.
## **Schematics**
![Schematics](/images/Schematic.png)
