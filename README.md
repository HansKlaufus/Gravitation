# Gravitation
A C++ GUI project for simulating the gravitational forces between objects using Newton's laws.

The GUI offers the possibility to open / sva / close XML-files which describe the names and initial masses, positions, etc. of the objects.

Objects are very general, but a typical example can be to run a simulation on the Solar System.

## Required libraries:
* wxWidgets
  * wxBase
  * wxGTK
  * wxGTK-devel
  * wxGTK-gl
  * wxGTK-media
* wxMathPlot

# Compiler settings:
* `wx-config --cflags`
* -fPIC //Not sure why, needed in Fedora23 since 24JAN2016

# Link libraries:
* GL
* GLU

## Other linker options:
* `wx-config --libs --gl-libs`

