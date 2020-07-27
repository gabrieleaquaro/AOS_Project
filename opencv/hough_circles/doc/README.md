# Hough Circles

The Hough Circle Transform is an image processing technique used to detect
circles in an image. Its original implementation is provided in the OpenCV
library. This is a modified version for the BOSP project, integrating the
Adaptive Execution Model, to make it more adaptive with respect to the assigned
resources.


## Build ##

The sample requires OpenCV packages to be installed on your system.
If a custom build of OpenCV has been performed, you can suggest the
installation path to the BOSP build system by setting the `OpenCV_DIR` variable,
as it follows:

> `export OpenCV_DIR=/opt/opencv/lib/cmake/opencv4/`

Then the sample compilation must be selected through the BOSP configuration
menu, before actually launching the build process.

The sample binary is installed under `$(BOSP_OUT)/usr/bin/`.


## Run ##

The HoughCircles can run with different parameters provided by the user,
they are implemented in HoughCircles main.cc:

1. help, -h: prints the help message.
2. version, -v : prints the program version.
3. conf, -C : to provide a configuration file different from the default one.
4. recipe, -r : to provide the recipe name, by default it is ”HoughCircles”.
5. **filename, -f** : to provide the path to the image to process, by default
the program looks for a file called ”jo.jpg” in the current directory.
6. **threads, -t**: to change the number of threads to exploit, works only in
unmanaged mode.
7. **center** *threshold*, **-c**: to change the threshold for center detection in the
Hough Transform, equals to 30 by default and cannot be greater than
250.
8. **upper** *threshold*, **-u**: to change the upper threshold for the internal
Canny edge detector used by the Hough Transform, equals to 100 by
default and cannot be greater than 500.
9. **jobs -j** : to change the number of jobs to perform, by default OnRun
is called 50 times.
10. **min** *radius*, **-i**: to change the minimum radius of circles to be detected,
equals to 1 by default and cannot be lower than 0.
11. **max** radius, **-a**: to change the maximum radius of circles to be detected,
equals to 30 by default and cannot be greater than 100.
12. **min** *dist*, **-m**: to change the minimum distance between detected cen-
ters, equals to 16 by default and cannot be greater than 64. The higher
the value, the lower the minimum distance between detected centers!
13. **cps** *goal*, **-s**: to set the cycles per second goal for the execution of the
program, by default the program uses the full assigned resources.


