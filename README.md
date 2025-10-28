# CAN Controlled Automotive Info Display 
--- 
## Aim 
The main objective of this project is to design and implement an embedded system capable of monitoring and displaying the critical vehicle parameters such as engine temperature, fuel level and indicator status. This system makes effective use of `CAN` protocol to achieve reliable communication between sensor nodes and main dashboard nodes, thereby creating a robust and scalable automative monitoring system. 

--- 
## Block Diagram 

![CAN Controlled Automotive Info Display](https://private-user-images.githubusercontent.com/65908099/506727615-1ad40234-ad39-4bd5-9814-47ddc8ff6657.png?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjE2NzY4MTEsIm5iZiI6MTc2MTY3NjUxMSwicGF0aCI6Ii82NTkwODA5OS81MDY3Mjc2MTUtMWFkNDAyMzQtYWQzOS00YmQ1LTk4MTQtNDdkZGM4ZmY2NjU3LnBuZz9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNTEwMjglMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjUxMDI4VDE4MzUxMVomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPTMwY2UxNTMxZmFlNmVmNGJiZGE4YzE3MmRiNDNiNzk4MmU4MTVlYWZjMzVjNDMxN2VkOGRjYzAxNjllMmJmOTQmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0In0.CLFIncIjS9XMFK1NEjUCFOeoV3tZKv-1l8I2AezzP1o) 

--- 
## MAIN NODE 

The `MAIN NODE` acts as the Central Dashboard display. It also receives fuel level information upon requesting the `FUEL NODE` via the CAN bus and shows the fuel percentage on the LCD. It also receives Fuel level information from `FUEL NODE` via CAN bus and shows the fuel percentage on the LCD. Additionally, The `MAIN NODE` handles the left and right indicator switch inputs, sends their status to the `INDICATOR NODE` via same CAN bus,and updates the indicator status on display. 

--- 
## INDICATOR NODE 

The `INDICATOR NODE` is responsible for controlling the vehicle's left and right indicator lights. It continuously monitors the CAN message from the `MAIN NODE`, and whenever the indicator switch is pressed at `MAIN NODE`, the corresponding signal is received and execute with respect to it. Based on this input, `INDICATOR NODE` activates the left or right indicator LEDs to represents the vehicle's turn signal status. 

--- 
## FUEL NODE 

The `FUEL NODE` is dedicated to monitoring the vehicle’s fuel level. Using the on-chip ADC, it continuously samples the fuel sensor signal and calculates the fuel percentage. The `FUEL NODE` now sends the fuel level information only upon request from the `MAIN NODE`. When the MAIN NODE sends a CAN message with the `Remote Transmission Request (RTR = 1)` bit set, the FUEL NODE responds by transmitting the current fuel data via the CAN bus. This ensures efficient communication and avoids unnecessary bus traffic. 

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

<video controls src="https://private-user-images.githubusercontent.com/65908099/506723203-95c5816d-91f7-4e0b-874d-baf59f0835df.mp4?jwt=eyJ0eXAiOiJKV1QiLCJhbGciOiJIUzI1NiJ9.eyJpc3MiOiJnaXRodWIuY29tIiwiYXVkIjoicmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbSIsImtleSI6ImtleTUiLCJleHAiOjE3NjE2NzYyNjksIm5iZiI6MTc2MTY3NTk2OSwicGF0aCI6Ii82NTkwODA5OS81MDY3MjMyMDMtOTVjNTgxNmQtOTFmNy00ZTBiLTg3NGQtYmFmNTlmMDgzNWRmLm1wND9YLUFtei1BbGdvcml0aG09QVdTNC1ITUFDLVNIQTI1NiZYLUFtei1DcmVkZW50aWFsPUFLSUFWQ09EWUxTQTUzUFFLNFpBJTJGMjAyNTEwMjglMkZ1cy1lYXN0LTElMkZzMyUyRmF3czRfcmVxdWVzdCZYLUFtei1EYXRlPTIwMjUxMDI4VDE4MjYwOVomWC1BbXotRXhwaXJlcz0zMDAmWC1BbXotU2lnbmF0dXJlPTg4MGU0MGU2OWJjNjNkZTYzMWQzYWEzYTdiOGJkNDBiNGRkNzZkMWFmYWU1OTcwYTllNTZiZGQ4NTVjNDg2MDcmWC1BbXotU2lnbmVkSGVhZGVycz1ob3N0In0.RPUeZxJn4c9sBIZZndFnUxmHCswXMKtvkJzF_4fgelI" title="output"></video>

---

