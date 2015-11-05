Build Instructions
==================
% mkdir build
% cd build
% cmake -DCMAKE_BUILD_TYPE=debug ..
% make install

For a release (optimized) build, replace debug with release.

The installed binary will be in inst/

The sample solution binaries are in sample_solution/

Platforms
=========
The build was tested on the Athena cluster, under Mac OS X and Windows.
There are no external dependencies, so, there should be no issues
building under Windows.

Submission
==========
We only provide official support for developing under the Athena cluster.
Your submission has to build and run on athena.dialup.mit.edu to receive credit.

Please submit your entire source directory (excluding the build
directory) and compiled binary in inst/. Include a README with
(updated) instructions on how to build and run your executable.
