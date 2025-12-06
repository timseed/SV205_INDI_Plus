# 
# NOT updated; But a framework if you prefer make rather than CMake
#
#
CXX = g++
CXXFLAGS = -Wall -O2 -fPIC -std=c++17

# INDI and OpenCV flags
INDI_CFLAGS  := $(shell pkg-config --cflags libindi)
INDI_LDFLAGS := $(shell pkg-config --libs libindi)
OPENCV_CFLAGS := $(shell pkg-config --cflags opencv4)
OPENCV_LDFLAGS := $(shell pkg-config --libs opencv4)

# Target driver
TARGET = indi_sv205.so

# Source
SRC = indi_sv205.cpp

all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(INDI_CFLAGS) $(OPENCV_CFLAGS) -shared -o $@ $^ $(INDI_LDFLAGS) $(OPENCV_LDFLAGS)

clean:
	rm -f $(TARGET)
