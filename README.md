# Real-Time-Air-Quality-Dashboard
Hands on Esp32 DEVKIT-V1, NEO-6M GPS Sensor, BME688 Sensor, PMS Sensor.
Coding using Arduino-IDE.
Received the developed code for BME and PMS, were tasked to incorporate NEO-6M, database and render it on a dashboard.
![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/3b9e2bb2-369b-4c66-8a94-b1dcfd2d3907)


# SENSORS AND MICROCONTROLLERS USED:
1) Esp32 DEVKIT-V1;
ESP32 is a series of low-cost, low-power system on a chip microcontrollers with integrated Wi-Fi.

   ![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/c5eecb46-f4ea-4a28-b05f-2eaf5515811f)

2) BME688;
The BME688 has temperature, barometric pressure, air humidity, altitude and gas sensor elements inside. All sensor information can be used either as single values or combined in the AI software to recognize certain conditions or states.

   ![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/35fd27ad-ed69-49b2-9259-9dfbdc2dbf6e)

3) PMS(Particulate Matter Sensor);
A particulate matter (PM) sensor measures the concentration of floating particles in the air. PM sensors can be laser-based, and work by using a laser to illuminate a particle and then collecting the light that scatters. The sensor can then count the particles in the air, and provide real-time information  on air pollution.

   ![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/c47f367d-c5e9-4d1a-b230-a92ea2bc23e7)


4) NEO-6M
With its low power consumption, compact size, and high accuracy, the NEO-6M GPS module is a popular choice for GPS applications in various fields, such as navigation, location tracking, and autonomous vehicles. The module has four pins: VCC, GND, RX, and TX.

   ![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/6a70518a-0fca-4620-9b7b-698702b57d6a)



# UML DIAGRAM WHICH DEPICTS THE FLOW OF DATA:

![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/71cf35dd-d56b-452c-ac40-43e76969cabf)


# DATABASE USED: INFLUX DB
Influx DB is the platform purpose-built to collect, store, process and visualize time series data(TSDB).
The Influx DB data model organizes time series data into buckets and measurements. A bucket can contain multiple measurements.
Bucket: Named location where time series data is stored. A bucket can contain multiple measurements .
Measurement: Logical grouping for time series data. All points in a given measurement should have the same tags.
![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/f96f11a0-f097-4770-a14b-55b9c35d3b6f)


# VISUALIZATION TOOL: GRAFANA
Grafana open source software enables you to query, visualize, alert on, and explore your metrics, logs, and traces wherever they are stored.
Popular among IOT based projects.
Whole configuration is already explained. Please refer this document. 
https://docs.google.com/document/d/1KFV7ZiS242wdmRd_CY4sNDocOYhhpRAVSYkmDPeuvKo/edit 

# RESULTS:
![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/61b9bf41-71cb-40c0-8329-5fd743627513)

![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/934bfccc-df21-46c6-865c-d8e90356d77e)

![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/347ba2bb-cc5c-4f6e-85a1-1e7c1ff80c93)

![image](https://github.com/9RP6/AQ-dashboard/assets/96533361/675a6cb8-9839-4c3d-b105-61b08373e385)


