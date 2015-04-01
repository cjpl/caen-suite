#!/bin/bash
# -*- mode: shell-script; coding: utf-8; -*-
# by Exaos Lee (exaos.lee@gmail.com)

TARGET="$1"
DEST=${2:-/opt/daq}
ARCH=${ARCH:-x64}
PREFIX=${PREFIX:-CAEN}
INSTALL="$(which install) -p"
INSTALLDIR="cp -ap"

usage () {
    cat <<EOF
Purpose: Script to install caen-suite.

Usage: ./install.sh <target> [dest]

Target:
  - vmelib     -- install library VMELib and headers
  - digitizer  -- install library CAENDigitizer and headers
  - caencomm   -- install library CAENComm and headers
  - libs       -- install all above libraries
  - wavedump   -- install utility wavedump
  - scope      -- install obsolete utility CAENScope (just for test)

Note: To install CAENUSBdrvB, you can follow this step --
  : cd USBdrvB
  : make
  : sudo make install
  : sudo modprobe CAENUSBdrvB

EOF

}

############################################################
# functions

# VMELib
inst_vmelib () {
    echo "Install CAEN VMELib library to ${DEST}/lib/${PREFIX}"
    mkdir -p ${DEST}/lib/${PREFIX}
    if [[ ${ARCH} == "x64" ]] ; then
        ${INSTALL} -m 755 VMELib/lib/x64/libCAENVME.so.2.41 ${DEST}/lib/${PREFIX}
    else
        ${INSTALL} -m 755 VMELib/lib/x86/libCAENVME.so.2.41 ${DEST}/lib/${PREFIX}
    fi
    cd ${DEST}/lib/${PREFIX}
    ln -s libCAENVME.so.2.41 libCAENVME.so
    cd -

    echo "Install CAEN VMELib includes to ${DEST}/include/${PREFIX}"
    mkdir -p ${DEST}/include/${PREFIX}
    ${INSTALL} -m 644 VMELib/include/*.h ${DEST}/include/${PREFIX}

    echo "Install CAEN VMELib samples to ${DEST}/share/${PREFIX}"
    mkdir -p ${DEST}/share/${PREFIX}
    ${INSTALLDIR} VMELib/labview-6.0/ ${DEST}/share/${PREFIX}
    ${INSTALLDIR} VMELib/sample/      ${DEST}/share/${PREFIX}
}

# CAENDigitizer
inst_digitizer () {
    echo "Install CAENDigitizer library to ${DEST}/lib/${PREFIX}"
    mkdir -p ${DEST}/lib/${PREFIX}
    if [[ ${ARCH} == "x64" ]]; then
        ${INSTALL} -m 755 CAENDigitizer/lib/x86_64/libCAENDigitizer.so.2.6.5 ${DEST}/lib/${PREFIX}
    else
        ${INSTALL} -m 755 CAENDigitizer/lib/i686/libCAENDigitizer.so.2.6.5   ${DEST}/lib/${PREFIX}
    fi
    cd ${DEST}/lib/${PREFIX}
    ln -s libCAENDigitizer.so.2.6.5 libCAENDigitizer.so
    cd -

    echo "Install CAENDigitizer includes to ${DEST}/include/${PREFIX}"
    mkdir -p ${DEST}/include/${PREFIX}
    ${INSTALL} -m 644 CAENDigitizer/include/*.h ${DEST}/include/${PREFIX}

    echo "Install CAENDigitizer samples to ${DEST}/share/${PREFIX}"
    mkdir -p ${DEST}/share/${PREFIX}
    ${INSTALLDIR} CAENDigitizer/samples/  ${DEST}/share/${PREFIX}
}

# VMELib
inst_caencomm () {
    echo "Install CAEN CAENComm library to ${DEST}/lib/${PREFIX}"
    mkdir -p ${DEST}/lib/${PREFIX}
    if [[ ${ARCH} == "x64" ]] ; then
        ${INSTALL} -m 755 CAENComm/lib/x64/libCAENComm.so.1.2.0 ${DEST}/lib/${PREFIX}
    else
        ${INSTALL} -m 755 CAENComm/lib/x86/libCAENComm.so.1.2.0 ${DEST}/lib/${PREFIX}
    fi
    cd ${DEST}/lib/${PREFIX}
    ln -s libCAENComm.so.1.2.0 libCAENComm.so
    cd -

    echo "Install CAEN CAENComm includes to ${DEST}/include/${PREFIX}"
    mkdir -p ${DEST}/include/${PREFIX}
    ${INSTALL} -m 644 CAENComm/include/*.h ${DEST}/include/${PREFIX}
}

# USBDrvB
inst_usbdrv () {
    echo "Not ready!"
}

# WaveDump
inst_wavedump () {
    inst_caencomm
    inst_vmelib
    inst_digitizer
    
    mkdir -p build/wavedump
    cd build/wavedump/
    cmake -DCMAKE_INSTALL_PREFIX=${DEST} \
          -DCAEN_INCLUDE_PATH=${DEST}/include/${PREFIX} \
          -DCAEN_LIB_PATH=${DEST}/lib/${PREFIX} \
          ../../WaveDump
    make
    make install
    cd -
    rm -rf build/wavedump/
}

# CAENScope
inst_caenscope () {
    inst_vmelib

    mkdir -p build/scope
    cd build/scope
    cmake -DCMAKE_INSTALL_PREFIX=${DEST} \
          -DCAEN_INCLUDE_PATH=${DEST}/include/${PREFIX} \
          -DCAEN_LIB_PATH=${DEST}/lib/${PREFIX} \
          ../../Scope
    make
    make install
    cd -
    #rm -rf build/scope
    # echo "Not ready!"
}

############################################################

case "${TARGET}" in
    vmelib | v)
        inst_vmelib
        ;;
    digitizer | digi)
        inst_digitizer
        ;;
    caencomm | c)
        inst_caencomm
        ;;
    wavedump | w)
        inst_wavedump
        ;;
    scope | s)
        inst_caenscope
        ;;
    libs | l)
        inst_vmelib
        inst_digitizer
        ;;
    drivers | d | usb | u)
        inst_usbdrv
        ;;
    all)
        inst_vmelib
        inst_caencomm
        inst_digitizer
        inst_wavedump
        inst_caenscope
        ;;
    *)
        usage
        ;;
esac

