# LIBS directory
In this directory, you are required to place all the external libraries your project depends on. 
Although, in principle, you can use git submodules (and place them under this directory), 
for the sake of easily compiling your application, placing the source code of the 
open source libraries is also fine. However, this approach is not applicable to
large dependencies, such as QT.



# List of External Libs

1. [Eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page)
> run: 'sudo apt-get install -y libeigen3-dev' in wsl or Linux system, after installation, it could be found under /usr/include/eigen3, nothing else need to be done. Using #include <Eigen/Dense>, and Vector3d is accessible.
2. [Project2](https://anotherproject.com/download)


> If you are using already compiled library, place it in this folder, and set the linker options appropriately.
> The inlcude files of the dependent library should also be placed in this folder.


