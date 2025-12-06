# INDI SV205 PLUS 

I am trying to understand how to compile an SV205 Driver withing the INDI/EKOS framework. 

I am now making some progress I think.


## Building 

I have a simple "1 shot" script - **t.sh**, which clears the build folder and re-compiles everything. Pure CI in action :) 

Failing that, you can do 

    rm -Rf build
    cd build 
    cmake ..
    make 

Which is exactly what **t.sh** does !!

## CMakeLists.txt 

This expects the indilib package to be installed, and that CMAKE can find this object. 

## Running the Code 



