# **DES Project - Instrument Cluster**

- [**DES Project - Instrument Cluster**](#des-project---instrument-cluster)
  - [Introduction](#introduction)
  - [Background Information](#background-information)
  - [Project Goals and Objectives](#project-goals-and-objectives)
  - [Technical Requirements](#technical-requirements)
  - [Software Design](#software-design)
  - [Installation and Usage](#Installation-and-Usage)
  - [Project Timeline](#project-timeline)
  - [Collaboration and Teamwork](#collaboration-and-teamwork)
  - [Results](#results)
  - [Submission](#submission)
  - [Evaluation](#evaluation)
  - [References](#references)

## Introduction

The PiRacer instrument cluster Qt application project is aimed at creating a real-time speedometer for a PiRacer car. The application will run on a Raspberry Pi and receive speed data from a speed sensor via the in-vehicle communication using Controller Area Network (CAN) protocol. This project will provide an opportunity for students to gain practical experience in software engineering, specifically in the areas of embedded systems, software architecture, and communication protocols. The project will also allow students to gain knowledge of the GUI frameworks (eg. Qt), that are widely used in the automotive industry for developing many embedded applications. The successful completion of this project will demonstrate the students' ability to design and implement a real-world software solution, and their ability to effectively communicate their results.  
</br>


## Background Information

This section would provide background information on the technologies and tools used in the project, including the Raspberry Pi, in-vehicle communication using CAN (Controller Area Network) protocol and Qt framework.

The Raspberry Pi is a small, low-cost computer that is commonly used for hobbyist and educational projects. It provides a versatile platform for developing a wide range of applications, including those in the automotive industry. The Qt framework is a popular cross-platform application development framework that is widely used in the automotive industry for developing embedded applications, such as instrument clusters and infotainment systems. The CAN protocol is a communication standard that is widely used in the automotive industry for interconnecting different ECUs (Electronic Control Units) in a vehicle.
</br>


## Project Goals and Objectives

The main goal of the PiRacer Instrument Cluster Qt Application project is to create a functioning instrument cluster for a PiRacer car that displays real-time speed data from a speed sensor via CAN bus.

The following are the specific objectives of the project:

1. To design and implement a Qt-based graphical user interface (GUI) for the instrument cluster.
2. To integrate an arduino based speed sensor system with the Raspberry Pi using the CAN bus protocol.
3. To display real-time speed data on the instrument cluster GUI.
4. To test the functionality of the instrument cluster using realistic driving scenarios.
5. To document the project in a comprehensive manner, including a detailed explanation of the system architecture, software design, implementation, results, and conclusions.
6. BONUS Part:
   1. To display battery level of PiRacer on Instrument Cluster.
</br>


## Technical Requirements

1. Raspberry Pi: The Raspberry Pi is a small, low-cost, single-board computer that is ideal for developing and testing embedded applications. A Raspberry Pi 3 Model B or later is recommended for this project, as it provides sufficient processing power and memory for running the instrument cluster application and receiving data from the speed sensor via CAN.
2. Qt (Open Source version): Qt Creator is a powerful, cross-platform integrated development environment (IDE) for developing applications with the Qt framework. The Qt libraries for Raspberry Pi include all of the necessary components for building Qt applications for the Raspberry Pi.
3. CAN bus interface: A CAN bus interface is required for connecting the Raspberry Pi to the vehicle's CAN bus and receiving speed data from the speed sensor. Suitable CAN bus interfaces for the Raspberry Pi include the MCP2515 and the TJA1050.
4. Speed sensor: A speed sensor capable of transmitting speed data via CAN is required for this project. The type of speed sensor required will depend on the vehicle being used for testing.
5. OBD-II cable: An OBD-II cable is required for connecting the Raspberry Pi and the speed sensor to the vehicle's CAN bus. This cable provides a convenient and reliable way to tap into the vehicle's CAN bus and receive data from the speed sensor.
6. Voltage regulator: A 12V to 5V voltage regulator is required for powering the Raspberry Pi from the vehicle's electrical system. The voltage regulator ensures that the Raspberry Pi receives a stable, regulated power supply, even when the vehicle's electrical system voltage fluctuates.
7. Display: A display is required for the instrument cluster application. Suitable displays include LCD and OLED displays, and the size and resolution of the display will depend on the specific requirements of the instrument cluster application.
8. Mounting hardware: A suitable method of mounting the display and Raspberry Pi in the vehicle is required. This may involve mounting brackets, enclosures, or other hardware, depending on the specific requirements of the instrument cluster application.
9. Vehicle for testing: Access to a PiRacer for testing the instrument cluster application is required. The PiRacer should have a CAN bus system and should be compatible with the speed sensor and other hardware components.

The students will be responsible for sourcing all of the required hardware components and ensuring that the hardware is compatible with the Raspberry Pi and the CAN bus interface. They will also be responsible for installing and configuring the operating system, the Qt framework, and any necessary drivers or libraries. The students will need to write and test the instrument cluster speedometer application, including the user interface, data processing, and CAN communication code. They will need to integrate the application with the hardware components and test the instrument cluster in a PiRacer. Finally, the students will be expected to document their work and demonstrate the instrument cluster application in a final presentation. This project delivers a solid understanding of software development and embedded systems, as well as the ability to work effectively in a team and to solve complex technical problems.  
</br>


## Software Design

The software design of the PiRacer instrument cluster application is based on the Qt framework, which is a popular cross-platform application development framework. Qt provides a wide range of tools and libraries that make it easy to create user-friendly graphical user interfaces (GUIs) and communicate with hardware devices.

The software design of the PiRacer instrument cluster consists of several key components, including the main application, the CAN communication module, and the data display module.

The main application is responsible for managing the overall functionality of the instrument cluster. It creates the GUI, manages the communication with the speed sensor via the CAN bus, and displays the speed data on the screen.

The CAN communication module is responsible for communicating with the speed sensor via the CAN bus. It receives speed data from the speed sensor and passes it on to the main application for display. This module uses the CAN library provided by Qt to communicate with the speed sensor.

The display module is responsible for displaying the speed data on the screen. It receives speed data from the main application and displays it in an easy-to-read format on the screen. This module can be customized to display the speed data in various ways, such as using a speedometer or a numerical display.

The software design of the PiRacer instrument cluster application is designed to be flexible and scalable, allowing for future modifications and additions. The use of the Qt framework and modular design also makes it easy to maintain and update the application. 
</br>


## - Installation and Usage

Tested on the following Hardware:

- Raspberry Pi 4 Model B 4GB

Tested on the following distributions:

- Raspberry Pi OS Lite "Bookworm (64-Bit)
- Ubuntu Server 20.04.5 LTS (64-Bit)

## - Piracer setup 

```bash
$ cd ~
$ mkdir piracer_test/
$ cd piracer_test/
$ python3 -m venv venv
$ source venv/bin/activate     //activate virtualenvironment   

$ pip install piracer-py

```


## - Raspberry Pi Setup
- CAN configuration
```bash
 $ sudo vim /boot/firmware/config.txt
 add the following line to the end of the config.txt file
 $ dtoverlay=seeed-can-fd-hat-v1 
```
you need to check your CAN-HAT version

- how to activate CAN
```bash
$ apt-get install can-utils
$ sudo ip link set can0 up type can bitrate 500000
$ candump can0
```

- How to enable I2C
```bash
$ sudo raspi-config (select Interfacing Options)
$ Enable I2C
$ reboot
```
How to check which I2C port we are using
```bash
$ i2cdetect -y 1
```
If you want to use Display, add following line to the end of config.txt file. 
[reference for LCD](https://www.waveshare.com/wiki/7.9inch_DSI_LCD)
```bash
dtoverlay=vc4-kms-v3d
#DSI1 Use
dtoverlay=vc4-kms-dsi-waveshare-panel,7_9_inch
#DSI0 Use
#dtoverlay=vc4-kms-dsi-waveshare-panel,7_9_inch,dsi0
```
</br>


## Project Timeline

The PiRacer Instrument Cluster Qt Application project is expected to take approximately 6-8 weeks to complete, with the following estimated timeline:

* Week 1-2:
  * Research and familiarization with the CAN bus protocol, speed sensors, and Qt.
  * Design of the system architecture and software design.

* Week 3-4:
  * Implementation of the Qt-based GUI for the instrument cluster.
  * Integration of the speed sensor with the Raspberry Pi using the CAN bus protocol.

* Week 5-6:
  * Testing and debugging of the instrument cluster.
  * Verification of real-time speed data display on the instrument cluster GUI.

* Week 7-8:
  * Final documentation and report writing, including a detailed explanation of the system architecture, software design, implementation, results, and conclusions.
  * Preparation for final presentation and demonstration.
</br>


