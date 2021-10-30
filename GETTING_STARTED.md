# How to start developing for the OS

## Operating System
Developing is done on Linux. While most parts will work under Windows, some shell scripts would need to be converted/maintained for batch.

Using the WSL2 in combination with Windows will only work for compiling the OS, due to missing USB support.

If there's an easier way to pass USB devices into the WSL in future Windows updates, feel free to adjust this section.


### Virtual Machines
If you're running Windows, the currently best option is hosting a Linux VM.

If you don't have a reason to choose something else, just go with an Ubuntu Image on VirtualBox or VMWare. VMWare Workstation is obtainable with a [Students License](https://intranetportal.hs-esslingen.de/de/he-portal/meine-hochschule/rechenzentrum/software-und-hardwareangebot.html).

## Prerequirements

* Git
* Python 3.6 or higher

The python module `distutils`
> `sudo apt-get install python3-distutils`


## IDE - VSCode
Install Visual Studio Code
either via snapd, as download [from Microsoft](https://code.visualstudio.com/) or read [this](https://code.visualstudio.com/docs/setup/linux) for more options
> sudo snap install --classic code 

Open the repository with or start VSCode *normally* and choose the folder
> `code ./path_to_repo`
 
or

> F1->File: Open Folder...


### Plugins
You **must** install the following plugins
* C/C++
* PlatformIO IDE

If Platform IO fails to install, see issue [PlatformIO #907](https://github.com/platformio/platformio-vscode-ide/issues/907)  

optional
* C++ Intellisense
* GitLens
* Markdown All in One
* ...

if the language server keeps crashing, try to downgrade the `C/C++` version. 

`1.4.0` seems to work (select `↓` at `Uninstall`, then select the desired version). You can aswell try to install `clangd` instead, but it heavily interfers with the `C/C++` extension and is only a “better than nothing” kind of workaround.

## Compiling

The project requires a `main` function for compilation. Simply add a file `src/main.cpp` which includes a custom `int main();` method. You can use [other projects](https://github.com/Rennstall/Cooling_2020) or the [README](README.md) as a reference.


## Debug Environment

The STLink V2 is used as debugging adapter.
While linux should include all required drivers, Windows requires you to [download them](https://www.st.com/en/development-tools/stsw-link009.html) from STM


### Error: libusb_open() failed...
If this occurs while uploading the binary, you need to update your `/etc/udev/rules.d`. See this [Stackoverflow](https://stackoverflow.com/a/48853773).
You can get the `99-openocd.rules` file on the [OpenOCD Repo](https://raw.githubusercontent.com/bcmi-labs/OpenOCD/master/contrib/99-openocd.rules)


### Pin Mapping
**IMPORTANT**: Make sure to compare the board and revision numbers


*Prototype v1.1 DMa on Header JP17:*
| Board    | Programmer |
|----------|------------|
| 2 - JTCK | 6 - SWCLK  |
| 3 - JTMS | 2 - SWDIO  |
| 4 - GND  | 4 - GND    |
| 5 - 3.3V | 8 - 3.3V   |