# ASCII Drawer

This project creates ASCII art based on a configuration file.

## Prerequisites

To compile and run this project, you need to have MinGW-w64 installed on your system. Follow the steps below to install and set up MinGW-w64 on Windows 10.

### Installing MinGW-w64

1. **Download the MinGW-w64 installer**:
   - Go to [MinGW-w64](https://www.mingw-w64.org/downloads/).
   - Download the appropriate installer for your system (usually the 64-bit version for Windows).

2. **Run the installer**:
   - Choose the installation options for **x86_64** (64-bit Windows).
   - Install MinGW-w64 to a directory, for example: `C:\Program Files\mingw-w64`.

3. **Add MinGW-w64 to the system PATH**:
   - Open the Start Menu, search for "Environment Variables", and select "Edit the system environment variables".
   - In the System Properties window, click the "Environment Variables" button.
   - In the Environment Variables window, find the `Path` variable in the "System variables" section and click "Edit".
   - Click "New" and add the path to the `bin` directory of your MinGW-w64 installation, for example:
     ```
     C:\Program Files\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin
     ```
   - Click "OK" to save and close all the windows.

4. **Verify the installation**:
   - Open Command Prompt and type:
     ```cmd
     g++ --version
     ```
   - You should see the version information of GCC if MinGW-w64 is correctly installed and added to the PATH.

## Compiling and Running the Project

1. **Clone the repository**:
   ```bash
   git clone https://github.com/your-username/your-repo-name.git
   cd your-repo-name
