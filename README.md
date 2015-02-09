CASELOT
=========
Set of various common tools used in many projects.

Build and requirements
----------------------
The project is maintained by cmake and can be compiled in various ways. It is compatibile with general *cmake-mantained* projects used by Author.

### Requirements ###

This project depends on:

 1. Google test API - which is included as **ExternalProject** and can be obtained in two ways:
  * Automatically (**recommended**) by *cmake*
  * Using local hard copy of this repo in case of working off-line. To use hard copy of *gtest* the repository must be manually cloned somewhere and environmental variable `GTest_SVN_REPOSITORY` must be set to **repo path**.
 2. PBToolset - which is included as **ExternalProject** and can be obtained in two ways:
  * Automatically (**recommended**) by *cmake*
  * Using local hard copy of this repo in case of working off-line. To use hard copy of *PBToolset.git* the repository must be manually cloned into `External_dep/PBToolset` and environmental variable `PBToolset_GIT_REPOSITORY` must be pointing directory with git repository. **This path must be in UNIX mode**
 3. OpenCV - must be installed and:
  * directory with relevant DLLs (must match current VS version) must be at **system** path
  * environmental variable `OPENCV_DIR` must point OPENCV subdirectory where `OpenCVConfig.cmake` is located
 4. clapack - is in `static_resources` dir
 5. levmar - is in `static_resources` dir
 6. SVN tool shoud be avaiable on system (**not local**) `%PATH%`
 7. Doxygen for documentation building (on local or system path)
 8. Graphviz package (on local or system path)
 9. MscGen package (on local or system path)

 #### Optional dependencies ####

 1. Optionally it is posiible to build *Matlab* wrappers to some *LabView* methods. To do so set environment variable `MATLABDIR` pointing to *Matlab* root and re=run *cmake* 

### Build ###
The following scripts available:

 * `./clean-build.bat` - clears everything and run cmake and then make, results are in `build` dir. Runs also all tests
 * `./recreate-msvc.bat` - deletes all cmake outputs and generates MSVC projects and solution in `build`. Typically it is enough to re-run *nmake* tool to rebuild also *cmake* files
 * `./recreate-cmake.bat` - deletes all cmake outputs and generates MSVC makefiles in `build`. Typically it is enough to re-run *nmake* tool to rebuild also *cmake* files
 * `./build_doc.bat` - calls doxygen and builds doc in `doc` dir
 
### Install ###
Use `nmake install` to copy all dlls to `bin` directory. No other installation steps are performed.

Problems
--------
If using Visual Studio solution all environmental variables and paths must be set globally for user (`setx`) or Visual Studio must be started from *.bat* script where are paths are set locally.

Building without internet is limited and may not work correctly, mainly because probelms with local access to SVN repository.
