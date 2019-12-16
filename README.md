Building DECENT
---------------

| CI | Status |
| -- | ------ |
| Travis | [![Build Status](https://travis-ci.com/DECENTFoundation/DECENT-GUI.svg?branch=master)](https://travis-ci.com/DECENTFoundation/DECENT-GUI)
| Appveyor | [![Build Status](https://ci.appveyor.com/api/projects/status/github/decentfoundation/DECENT-GUI?svg=true&branch=master)](https://ci.appveyor.com/project/DECENTfoundation/DECENT-GUI) |

### Installing prerequisites in Linux

For Debian 10/Ubuntu 18.04 LTS or later, execute in console:

    sudo apt-get install apt-transport-https curl gnupg lsb-release software-properties-common
    curl https://bintray.com/user/downloadSubjectPublicKey?username=decentfoundation | sudo apt-key add -
    sudo add-apt-repository "deb [arch=amd64] https://dl.bintray.com/decentfoundation/$(lsb_release -is | tr "[:upper:]" "[:lower:]") $(lsb_release -cs) libpbc"
    sudo apt-get install build-essential make cmake g++ git qt5-default qttools5-dev qttools5-dev-tools libreadline-dev libcrypto++-dev libgmp-dev libpbc-dev libssl-dev libcurl4-openssl-dev libboost-all-dev zlib1g-dev
    mkdir ~/dev

    # Download and build JSON 3.7.3
    curl -LO https://github.com/nlohmann/json/archive/v3.7.3.tar.gz
    tar xf v3.7.3.tar.gz
    cd json-3.7.3
    cmake .
    sudo make -j$(nproc) install
    cd ..
    rm -rf json-3.7.3 v3.7.3.tar.gz

> Note for Debian 9/Ubuntu 16.04 LTS legacy systems, the default versions of Boost and CMake installed are too old and not supported. In order to install a supported ones, in addition to the common commands above, execute the following in console (in the same shell session, where you are going to build DECENT itself):

    # Download and build Boost 1.65.1
     curl -LO https://sourceforge.net/projects/boost/files/boost/1.65.1/boost_1_65_1.tar.gz
     tar xf boost_1_65_1.tar.gz
     mkdir boost
     cd boost_1_65_1
     export BOOST_ROOT=$(realpath ../boost)
     ./bootstrap.sh --prefix=$BOOST_ROOT
     ./b2 -j$(nproc) install
     cd ..
     rm -rf boost_1_65_1 boost_1_65_1.tar.gz

    # Download and build CMake 3.13.4
     curl -LO https://cmake.org/files/v3.13/cmake-3.13.4.tar.gz
     tar xf cmake-3.13.4.tar.gz
     mkdir cmake
     cd cmake-3.13.4
     export CMAKE_ROOT=$(realpath ../cmake)
     ./configure --prefix=$CMAKE_ROOT
     make -j$(nproc) install
     export PATH=$CMAKE_ROOT/bin:$PATH
     cd ..
     rm -rf cmake-3.13.4 cmake-3.13.4.tar.gz

For Fedora 30 or later, execute in console:

    sudo dnf install curl
    sudo curl https://bintray.com/user/downloadSubjectPublicKey?username=decentfoundation -o /etc/pki/rpm-gpg/RPM-GPG-KEY-decentfoundation
    sudo curl https://docs.decent.ch/assets/bintray-decentfoundation-fedora.repo -o /etc/yum.repos.d/bintray-decentfoundation.repo
    sudo dnf install make cmake gcc-c++ git qt5-qtbase-devel qt5-linguist readline-devel cryptopp-devel openssl-devel gmp-devel libpbc-devel libcurl-devel json-devel zlib-devel boost-devel boost-static
    mkdir ~/dev

For CentOS 8, execute in console:

    sudo dnf install curl
    sudo curl https://bintray.com/user/downloadSubjectPublicKey?username=decentfoundation -o /etc/pki/rpm-gpg/RPM-GPG-KEY-decentfoundation
    sudo curl https://docs.decent.ch/assets/bintray-decentfoundation-centos.repo -o /etc/yum.repos.d/bintray-decentfoundation.repo
    sudo dnf install https://dl.fedoraproject.org/pub/epel/epel-release-latest-8.noarch.rpm
    sudo dnf install --enablerepo PowerTools make cmake gcc-c++ git qt5-qtbase-devel qt5-linguist readline-devel cryptopp-devel openssl-devel gmp-devel libpbc-devel libcurl-devel json-devel zlib-devel boost-devel boost-static
    mkdir ~/dev

### Installing prerequisites in MacOS

* Install Xcode and Command Line Tools as described in http://railsapps.github.io/xcode-command-line-tools.html
* Install Homebrew, see http://brew.sh

Then, execute in console:

    $ brew install cmake boost cryptopp openssl@1.1 pbc nlohmann-json qt readline git ipfs
    $ brew link --force readline
    $ mkdir ~/dev

### Installing prerequisites in Windows

* Install Git for Windows (https://gitforwindows.org)
* Install CMake tools (https://cmake.org/download)
* Install Visual Studio 2017 Community (https://visualstudio.microsoft.com/downloads)
* Install Boost 1.68 MSVC 14.1 (https://sourceforge.net/projects/boost/files/boost-binaries) (choose *C:\Projects\boost_1_68_0* as installation prefix)
* Install Qt 5.12.6 (https://www.qt.io) for MSVC 14.1 x64 (choose *C:\Projects\Qt* as installation prefix)

Then, start _Visual Studio 2017 x64 Native Tools Command Prompt_ and execute:

    mkdir \Projects
    cd \Projects
    git clone https://github.com/Microsoft/vcpkg.git
    cd vcpkg
    bootstrap-vcpkg.bat
    vcpkg --triplet x64-windows-static install cryptopp curl openssl pbc nlohmann-json

### Obtaining the sources

After all the prerequisites are installed, execute in console (change current path to `~/dev` in Linux/MacOS or to `\Projects` in Windows):

    git clone https://github.com/DECENTfoundation/DECENT-GUI.git
    cd DECENT-GUI
    git submodule update --init --recursive

### Building and installing DECENT in Linux or MacOS

In order to build and install DECENT, execute in console:

    mkdir -p ~/dev/DECENT-GUI-build
    cd ~/dev/DECENT-GUI-build
    cmake -G "Unix Makefiles" -DCMAKE_BUILD_TYPE=Release ~/dev/DECENT-GUI
    cmake --build . --target all -- -j -l 3.0
    cmake --build . --target install

> Note that, in case of "Unix Makefiles" CMake generator, the last two commands are equivalent to:
>
>     $ make -j -l 3.0 install

DECENT artifact is installed at `/usr/local` directory by default. You can specify any other custom install prefix for `cmake` during the initial configuration, for example, by adding `-DCMAKE_INSTALL_PREFIX=~/dev/DECENT-GUI-prefix` to the command line.

You can use any path instead of `~/dev` in the steps above.

You can use Xcode, or any other CMake generator, and then, if it is an IDE generator, instead of building and installing via `cmake` in terminal, open the generated project/solution file in the corresponding IDE and perform `ALL_BUILD` and `INSTALL` (or `install`) actions from there.

### Building and installing DECENT in Windows

In order to build and install DECENT follow the steps:
* start Visual Studio 2017, navigate to _File > Open > Folder_ and choose `C:\Projects\DECENT-GUI`
* navigate to _CMake > Change CMake Settings > DECENT_ and adjust installation prefix and paths to Boost, Qt, Doxygen, Perl and vcpkg (if needed)
* build and install artifacts using _CMake > Install > DECENT_

You can use CMake generator to create a Visual Studio 2017 project files and perform _Build > Build solution_ action from there, just start the _Visual Studio 2017 x64 Native Tools Command Prompt_ and execute:

    cd \Projects\DECENT-GUI
    set BOOST=C:\Projects\boost_1_68_0
    set QT_CMAKE=C:\Projects\Qt\5.12.6\msvc2017_64\lib\cmake
    set VCPKG=C:\Projects\vcpkg
    cmake -DCMAKE_TOOLCHAIN_FILE=%VCPKG%\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows-static -DCMAKE_BUILD_TYPE=Release -DBOOST_ROOT=%BOOST% -DBOOST_LIBRARYDIR=%BOOST%\lib64-msvc-14.1 -DQt5Widgets_DIR=%QT_CMAKE%\Qt5Widgets -DQt5LinguistTools_DIR=%QT_CMAKE%\Qt5LinguistTools -G "Visual Studio 15 2017 Win64" .

You can specify any other custom install prefix for `cmake` during the initial configuration, for example, by adding `-DCMAKE_INSTALL_PREFIX=C:\Projects\DECENT-GUI-prefix` to the command line.

You can use any path instead of `C:\Projects` in the steps above.
