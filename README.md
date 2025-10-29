# CAN Controlled Automotive Info Display 
--- 
## Aim 
The main objective of this project is to design and implement an embedded system capable of monitoring and displaying the critical vehicle parameters such as engine temperature, fuel level and indicator status. This system makes effective use of `CAN` protocol to achieve reliable communication between sensor nodes and main dashboard nodes, thereby creating a robust and scalable automative monitoring system. 

--- 
## Block Diagram 

<img width="1027" height="686" alt="image" src="https://github.com/user-attachments/assets/3cea7961-f7e8-4802-8b07-6225ec0ff9da" />

--- 
## MAIN NODE 

The `MAIN NODE` acts as the Central Dashboard display. It continuously reads the engine temperature and RTC values, and displays them on LCD. It also receives fuel level information upon requesting the `FUEL NODE` via the CAN bus and shows the fuel percentage on the LCD. Additionally, The `MAIN NODE` handles the left and right indicator switch inputs, sends their status to the `INDICATOR NODE` via same CAN bus,and updates the indicator status on display. 

--- 
## INDICATOR NODE 

The `INDICATOR NODE` is responsible for controlling the vehicle's left and right indicator lights. It continuously monitors the CAN message from the `MAIN NODE`, and whenever the indicator switch is pressed at `MAIN NODE`, the corresponding signal is received and execute with respect to it. Based on this input, `INDICATOR NODE` activates the left or right indicator LEDs to represents the vehicle's turn signal status. 

--- 
## FUEL NODE 

The `FUEL NODE` is dedicated to monitoring the vehicle’s fuel level. Using the on-chip ADC, it continuously samples the fuel sensor signal and calculates the fuel percentage. The `FUEL NODE` now sends the fuel level information to the `MAIN NODE` upon request from the `MAIN NODE` by receiving a CAN message with the `Remote Transmission Request (RTR = 1)`. Then the `FUEL NODE` responds by transmitting the current fuel data via the CAN bus ensuring efficient communication and avoiding unnecessary bus traffic. 

--- 
## Components 
- ### Hardware Requirements 
    - LPC2129 MCU development Board 
    - CAN Transceiver (MCP2551) 
    - DS18B20 Temperature Sensor 
    - Fuel Guage 
    - 8 LED's 
    - 20x4 LCD 
- ### Software Requirements 
    - Keil uvision4 
    - Flash Magic 
    - Embedded C Programming 

--- 
## OUTPUT 

https://github.com/user-attachments/assets/30ee41b9-9f1e-4a16-bbb4-99c541cd1fb9

---





