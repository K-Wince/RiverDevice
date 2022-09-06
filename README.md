# RiverDevice
The code for a device that monitors the certain aspects of the river to provide useful information to the user. Developed as group project for an undergraduate class using Arduinos.

## Summary
This device is a simplistic solution to allow for monitoring and warnings of certain aspects of the river the device would be placed in. It allows for the rough measurement of the toxicity of the water, the velocity of the river, and also the depth of the water. The various measurements are recorded using a clam for toxicity, a hall-effect sensor and a turbine for the velocity, and a ultrasonic sensor for the depth using the Arduino platform.

## Background
This project was based on providing a residence in the Hunchun Basin, China a means of gaining specific knowledge about the tributary that runs through their property. We were tasked with gaining three pieces of information to inform the residents: water toxicity to prevent sickness in the residents, water flow rate to prevent over-irrigation of crops, and water level to provide flood warnings to the residents. The device should be able to effectively measure these ideas and present it to the residents in a suitable manner.

## Overall Design
My team decided to design the system, as shown in Figure 1, to have two separate shells to house the components of the devices. One of the housings would contain all of the sensors for the river in a water tight box so it can be mostly submerged in the river, while the other housing would have the Arduino and User Interface while being mounted on the side of the river. This design would allow easy access to the system while also allowing all of the sensors to be properly placed in the river.  Each component would have a wire going through a channel to the main box on the side of the river for a connection to the Arduino. As shown in Figure 2, there were several design changes since the original design concept. Instead of having the water turbine on the inside of the box, it was decided to be put on the outside since sending the water through a pipe creates a tunnel effect causing the velocity recorded to be highly inaccurate due to friction on the walls. Another design change was to make the entire bottom part of the box a mesh wire cage to house the clam, to allow for easy access to the water and more room for the clam.

### Toxicity Sensor
Information about the toxicity of the water was decided to be collected using a clam. Clams are able to be used as biomonitors to deduce information about their environment. The freshwater clam Corbicula fluminea are influenced by chemical contaminants on valve closure, filtration rate or burrowing into sediment. [1] These instances can be observed on the clam when there environment poses a risk to the clam. The biggest observation we chose to focus on is that the clam closes its shell if the environment is toxic. We used a magnetic reed switch and a magnet so that when the shell closes, the reed switch and the magnet come close to each other which completes the circuit. The Arduino then reads when the current becomes HIGH and triggers the the water is toxic through the code below:

### Flow-Rate Sensor
The flow rate sensor was used as a test for a system to gather quantifiable data and justify design decisions using that data. Information about the flow rate of the water was decided to be collected using a hall effect sensor and a turbine with embedded magnets. The speed of the water can be calculated in a two-dimensional aspect by determining the circumfrence of the turbine and then dividing that number by the number of spokes with magnets. This will allow us to get the distance it has traveled when the hall effect sensor goes off and then you compare that to the time between each interval that the sensor went off giving you a rough velocity of the flow in meters per second. 

### Depth Sensor
Information about the depth of the water was decided to be collected using an ultrasonic sensor and a tube. It was found through research that ultrasonic waves still has a successful operation within a tube with seamless walls [2]. This would allow the sensor to be mounted outside the water and be mostly protected from the environment. There would be a small puck that would float on top of the surface of the water that would bounce the ultrasonic waves back to the sensor allowing for the length from the sensor to the surface of the water to be found. The depth of the water could then be found by using a previously measured distance from the top of the pipe to the bottom of the river to give a rough estimate of the depth of the river. This would allow the device to notify the users of a low-depth of the river and any problems that may arise from that.

![Device Image](/img/device.png)

#### Sources
[1] Chen, W.-Y., Jou, L.-J., Chen, S.-H., & Liao, C.-M. (2012). A real-time biomonitoring system to detect arsenic toxicity by valve movement in freshwater clam Corbicula fluminea. Ecotoxicology, 21(4), 1177–1187. https://doi.org/10.1007/s10646-012-0872-9
[2] Wielenberg, Scott (2016). Using an Ultrasonic Sensor Inside of a Pipe. https://www.maxbotix.com/Tutorials/124.htm
