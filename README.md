# OpenStreetMap Route Planner

This repo contains my code for the Route Planning project in Course 1 of the Udacity C++ Nanodegree.

<img src="map.png" width="600" height="450" />

## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/pre-eth/OpenStreetMap-Route-Planner.git --recurse-submodules
```
or with SSH:
```
git clone https://github.com/pre-eth/OpenStreetMap-Route-Planner.git --recurse-submodules
```

## Dependencies for Running Locally

This project was built and tested on Fedora. Building on Windows and OS X requires you to build the IO2D library, which can be pretty difficult.

For simplicity's sake I've included a built copy of the IO2D library in the repo, which means if you're on Linux you can skip to the *Compiling and Running* section. Otherwise, good luck building it yourself and here's what else you'll need:

* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* IO2D
  * Installation instructions for all operating systems can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)
  * This library must be built in a place where CMake `find_package` will be able to find it
 
### Compiling and Running
Compiling and running the project is as easy as:
```
mkdir build && cd build
cmake ..
make
./OSM_A_star_search
```

Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```
