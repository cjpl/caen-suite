caen-suite
==========

Merge related DAQ codes for Linux from CAEN.

Versions:
  * CAEN USB Driver -- 1.4, 2014-01
  * CAENVME Library -- 2.41, 2013-03
  * CAENDigitizer -- 2.6.5, 2015-02
  * CAENComm -- 1.2, 2013-12
  * WaveDump -- 3.6.6, 2015-02
    * Depends: VMELib, CAENDigitizer, CAENComm
  * CAENScope -- 1.6.1, 2010-07, obsolete
    * Depends: DigitizerSDK, VMELib, wxWidgets (>=2.8.10)
    * CAEN DigitizerSDK -- 1.3, 2010-02-10
  * CAENV1x90 -- 1.1, 2013-07

## Install script ##

How to execute:
> ./install <target> [prefix]

Targets:
* `vmelib`    -- Install CAENVMELib
* `digitizer` -- Install library CAENDigitizer
* `caencomm`  -- Install library CAENComm
* `libs`      -- Install libraries, CAENVMELib and CAENDigitizer
* `wavedump`  -- Install libraries and WaveDump
* `scope`     -- Install related libraries and CAENScope
* `usb`       -- Install USBDrvB


