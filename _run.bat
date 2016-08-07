ECHO OFF
rem 1. example of shadow filter on camera man image
rem..\..\..\bin\Release\mytconvolution -i ..\..\..\..\Data\CMan\cman_16bits.raw -x 256 -y 256 -z 1 -d 16 -k shadowS_3x3_16bits.raw -a 3 -b 3 -c 1 -m 0 -n 1 -p 32000 -r -32000 -o shadow256_256_16bits.raw
rem 
rem 2. example of applying separable kernel (multiple kernels) for vertical gradient
rem ..\..\..\bin\Release\tconvolution -i ..\..\..\..\Data\CMan\cman_16bits.raw -x 256 -y 256 -z 1 -d 16 -k gradW_3x1_16bits.raw -a 3 -b 1 -c 1 -m 0 -n 1 -p 32000 -r -32000 -o I1256_256_16bits.raw
rem ..\..\..\bin\Release\mytconvolution -i I1256_256_16bits.raw -x 256 -y 256 -z 1 -d 16 -k gaussV_1x3_16bits.raw -a 1 -b 3 -c 1 -m 0 -n 1 -p 32000 -r -32000 -o GradW_separable256_256_16bits.raw
rem
rem Example of applying single kernel for vertical gradient, the result will be the same as in the example 2.
 ..\..\..\bin\Release\mytconvolution -i ..\..\..\..\Data\CMan\cman_16bits.raw -x 256 -y 256 -z 1 -d 16 -k gradW_3x3_16bits.raw -a 3 -b 3 -c 1 -m 0 -n 1 -p 32000 -r -32000 -o GradW_256_256_16bits.raw

