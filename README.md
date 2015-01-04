CASELOT
=========
Set of various common tools used in many projects.

Build and requirements
----------------------
The project is maintained by cmake and can be compiled in various ways. It is compatibile with general *cmake-mantained* projects used by Author.

### Requirements ###
This project depends on:

 1. Google test API - which is included as **ExternalProject** and can be obtained in two ways:
  * Automatically by *cmake*  checking out from repository http://googletest.googlecode.com/svn/trunk/
  * Using local hard copy of this repo in case of working off-line. To use hard copy of *gtest* the repository must be manually cloned somewhere and environmental variable `GTest_SVN_REPOSITORY` must be set to **repo path**.
 2. PBToolset - which is included as **ExternalProject** and can be obtained in two ways:
  * Automatically by *cmake* checking out from repository on https://github.com/baniuk/PBToolset.git
  * Using local hard copy of this repo in case of working off-line. To use hard copy of *PBToolset.git* the repository must be manually cloned into `External_dep/PBToolset` and environmental variable `PBToolset_GIT_REPOSITORY` must be pointing directory with git repository. **This path must be in UNIX mode**
 3. OpenCV - must be installed and:
  * directory with relevant DLLs (must match current VS version) must be in **system** path
  * environmental variable `OPENCV_DIR` must point OPENCV subdirectory where `OpenCVConfig.cmake` is located
 4. clapack - must be located in `External_dep/clapack-3.2.1-CMAKE` - tested version is in `static_resources` dir
 5. levmar - must be located in `External_dep/levmar-2.6` - tested version is in `static_resources` dir
 6. SVN tool shoud be avaiable on system (**not local**) `%PATH%`
 7. Doxygen for documentation building (on local or system path)
 8. Graphviz package (on local or system path)
 9. MscGen package (on local or system path)

### Build ###
The following scripts available:

 * `./clean-build.bat` - clears everything and run cmake and then make, results are in `build` dir. Runs also all tests
 * `./recreate-msvc.bat` - deletes all cmake outputs and generates MSVC projects and solution in `build`
 * `./recreate-cmake.bat` - deletes all cmake outputs and generates MSVC makefiles in `build`
 * `./build_doc.bat` - calls doxygen and builds doc in `doc` dir
 
### Install ###
Use `nmake install` to copy all dlls to `bin` directory. No other installation steps are performed.

Problems
--------
If using Visual Studio solution all environmental variables and paths must be set globally for user (`setx`) or Visual Studio must be started from *.bat* script where are paths are set locally.

Building without internet is limited and may not work correctly, mainly because probelms with local access to SVN repository.
