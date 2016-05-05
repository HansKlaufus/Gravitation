Needed libraries:
* wxWidgets
** wxBase
** wxGTK
** wxGTK-devel
** wxGTK-gl
** wxGTK-media
* wxMathPlot

Compiler settings:
* `wx-config --cflags`
* -fPIC //Not sure why, needed in Fedora23 since 24JAN2016

Link libraries:
* GL
* GLU

Other linker options:
* `wx-config --libs --gl-libs`

