==============================================
Multi-Core ArchC RISC-V System Level Simulator
==============================================

This system model has been already tested with the gcc version 5.4.0 on ubuntu 16.04.9

Library Dependencies
--------------------

1. SystemC 2.3.1

2. SCML 2.4.3

3. ArchC 2.4.1 (`modified version <http://gitlab.larc-nthu.net/m104061593/ArchC-mod-2.4.1>`_)

Note:

Make sure the **SYSTEMC_HOME**, **SCML_HOME** and **ARCHC_HOME** is set correctly for CMake to find libraries.

Make sure the LD_LIBBRARY_PATH is set correctly to find libsystemc-2.3.1.so.

Make sure to source the "ARCHC_HOME/etc/env.sh".

How to Build Platform
---------------------

``$ ssh account@ws32``

``$ ssh account@ee3450a -p 6470``

``$ cd platform``

``$ mkdir build``

``$ cd build``

``$ cmake ..``

``$ make``

How to Build Test Program
-------------------------
``$ cd application``

``$ mkdir build``

``$ cd build``

``$ cmake ..``

``$ make``

Temporary test - Pi calculation (4 Cores)
-------------------------

``$ ../../../platform/build/platform.out -a pi_mp``
