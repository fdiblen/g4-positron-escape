
# Geant4 code for positron escape simulations

## Description

Geant4 code to perform positron escape simulations.

## 1. Building and usage (tested on Linux and OS X)

- Make sure you have [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git) installed.
- Clone this repo and cd into it.
```bash
git clone https://github.com/fdiblen/g4-positron-escape.git
cd g4-positron-escape
```


### 1.1 Building
The code has the dependencies listed below.

|   |   |
|:-:|:-:|
|  ROOT   | v5.X  | 
|  Geant4 | 4.1X  |
|  gcc    |   |


#### 1.1.1 Dockerized version (recommended)

Install [Docker](https://docs.docker.com/install/) and run the commands below.

```bash
chmod +x ./build.sh ./run.sh
./build.sh
```

This will download the base geant4 docker image and dockerize (generates a new image) the source code. The new image then can be used to perform simulations.



#### 1.1.1 Compiling from the source code

```bash
cd code
mkdir build && cd build
cmake ..
make -j4
```

### 1.2 Running

#### 1.2.1 With Docker
If you are using dockerized version:
- Use the following folder structure:

   **job_name/sources**

   **job_name/data**

The macros (radiactive sources) should be added to **sources** folder. Simulation output will be saved in **data** folder. 

- Create input source macros and save them in a **job_name/sources** folder.
- Run the command below.

```bash
./run.sh job_name
```
This command will perform a simulation for each of the source macros in **job_name/sources** folder. The output of the each simulation will be saved in **job_name/data** folder.

An example can be found in **example-job** folder.


#### 1.2.2 Without Docker
If you prefer to use the code without Docker, run:
```bash
./positronEscape macro.mac
```
In this command **macro.mac** includes source definition.
The executable (positronEscape) can be found **build** directory.



## 2. Modifying the source code
The source code can be found in **code** folder.
If you need to change the simulation geometry it is defined in **code/src/positronEscapeDetectorConstruction.cc**.


## Help
For any issues or requests, please create a ticket at [this link](https://github.com/fdiblen/g4-positron-escape/issues/new).
