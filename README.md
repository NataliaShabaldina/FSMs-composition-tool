# FSMs-composition-tool
This application is the graphical user interface for building finite state machines binary compositions via BALM-II.
User paints composition in graphical redactor. Then application generates and execute script (sequence of BALM-II commands and special python script execution), that builds composition.
All files with FSM description have to be in .aut format.

# Requirments:
1. BALM-II
2. Python3
2. Qt

# The easiest and recommended way to build application:
1. Install BALM-II from deb-package
   - https://ultraespresso.di.univr.it/balmII - deb package and instruction
2. Install Qt Creator 
   - One of the instructions: https://www.osradar.com/install-qtcreator-on-ubuntu-20-04-18-04/
3. Install python3 
   - sudo apt install python3
4. Clone this repository
   - git clone https://github.com/SotnikAP/FSMs-composition-tool
5. Open project via Qt Creator (open .pro file)
   - Open Qt Creator -> Open File or Project -> Choose .pro file
6. Build it
