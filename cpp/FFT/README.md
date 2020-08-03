# FFT

Porting of the FFT benchmark application, developed by ACT-LAB and included in
the AxBench suite, to the BOSP Adaptive Execution Model.

The application executes an adapted number of stages of the algorithms on the
basis of the number of assigned CPU cores.

## Build ##

**Dependency**: It requires the installation of the `libfann` package.

## Run ##

**Arguments**:
- input FFT length (2^N value)
- output file

**Example**

`$ ./out/usr/bin/fft 32768 /tmp/output.txt`
