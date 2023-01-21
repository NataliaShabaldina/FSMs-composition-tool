# FSMs-composition-tool
This application is the graphical user interface for building finite state machines binary compositions via BALM-II.
User paints composition in graphical redactor. Then application generates and execute script (sequence of BALM-II commands and special python script execution), that builds composition.
All files with FSM description have to be in .aut format.


# Requirments:
Instruction below is tested under Ubuntu 18 and 20.
As long as Qt and Python are cross platform, application can be run on any platform/distributive, but BALM-II is required.

1. BALM-II
2. Python3
3. Qt

# The easiest and recommended way to build application:
1. Install BALM-II (if BALM-II is already installed, just make sure PATH contains path to it, so balm can be launched by 'balm' command in terminal)
   - Unzip archive balm-II.zip from the root of this repository
   - install dependencies: sudo apt install -y git gcc-multilib
   - copy balm to /usr/bin (sudo cp balm /usr/bin) or add path to balm into PATH)
2. Install Qt Creator 
   - One of the instructions: https://www.osradar.com/install-qtcreator-on-ubuntu-20-04-18-04/ (follow all instructions)
3. Install python3 
   - sudo apt install python3
4. Install git
   - sudo apt install git
5. Make folder and clone repository
   - git clone https://github.com/SotnikAP/FSMs-composition-tool
6. Open project via Qt Creator (open .pro file)
   - Open Qt Creator -> Open File or Project -> Select FSMs-composition-tool.pro file
7. Build it

# Launching application
1. Move to directory with built project (e.g. cd build-FSMs-composition-tool-DesktopRelease)
2. Launch application: ./FSMs-composition-tool

# Interface
- Button FSM adds state machine-object on scene.
- Button Link adds channel-object on scene.
- Button Composition adds composition-object on scene.

Every element can be moved. Names of FSMs and Links can be changed.
Make sure links are in connect with FSMs (there is no space between them) before building composition.
Channels names should be equal to corresponding names from .aut files.
Composition object should cover both FSMs. Inner channels should be fully inside composition-object. Outside channels should be half outside of composition-object.
![image](https://user-images.githubusercontent.com/36838141/213866937-1a3f47b5-17cc-4cf5-9d00-c7aa3297accb.png)

To attach .aut file to corresponding FSM-object right click on FSM-object and choose "Attach file", then choose file.

![image](https://user-images.githubusercontent.com/36838141/213866949-f2d5c445-6a45-4548-9cf3-f758092b1419.png)

To build composition right click on composition-object and press "Form".

![image](https://user-images.githubusercontent.com/36838141/213866959-7c28e7bc-3a57-4959-a1e4-5d3be19263f8.png)

After that files will appear in project folder and output information will be printed in console.

![image](https://user-images.githubusercontent.com/36838141/213866972-ab0ef43b-7e52-420d-9d2e-8f675606d961.png)

If there are no errors, fsm.aut file should be in project folder. This file contains composition.

# Test example
There are files for launching test example in "test_example" folder (there is no need to copy them into the build folder, you can just atach them from whereever you want). To build it you need to form on scene exact the same composition as on picture below and attach .aut files to corresponding FSM-objects.

![image](https://user-images.githubusercontent.com/36838141/213867485-3257386c-b5d3-4112-a25d-4a1eeb65d9d9.png)


# Launch test example instruction (russian instruction)
[Link](https://github.com/SotnikAP/FSMs-composition-tool/blob/master/doc/%D0%A3%D0%BF%D1%80%D0%B0%D0%B2%D0%BB%D0%B5%D0%BD%D0%B8%D0%B5%20%D0%B3%D1%80%D0%B0%D1%84%D0%B8%D1%87%D0%B5%D1%81%D0%BA%D0%B8%D0%BC%20%D1%80%D0%B5%D0%B4%D0%B0%D0%BA%D1%82%D0%BE%D1%80%D0%BE%D0%BC%20%D0%B8%20%D0%B7%D0%B0%D0%BF%D1%83%D1%81%D0%BA%20%D1%82%D0%B5%D1%81%D1%82%D0%BE%D0%B2%D0%BE%D0%B3%D0%BE%20%D0%BF%D1%80%D0%B8%D0%BC%D0%B5%D1%80%D0%B0.pdf)


#### 

