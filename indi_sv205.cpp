// indi_sv205.cc  -- minimal INDI CCD driver skeleton
// #include <libindi/baseclient.h>
#include "indi_sv205.h"
#include <libindi/defaultdevice.h>
#include <libindi/indibase.h>
#include <libindi/indiccd.h>
#include <libindi/indidevapi.h>
// #include <indidevapi.h>
// #include <indicom.h>
#include <memory>
#include <vector>
#define GAIN_PROPERTY 10
using namespace std;

SV205::SV205() : INDI::CCD() {}
SV205::~SV205() {}
// Called once at driver init
bool SV205::initProperties() {
  // call base first
  INDI::CCD::initProperties();
  IUFillNumber(&exposureNP, "CCD_EXPOSURE", "Exposure Time", "ex time", 0, 1000,
               1, 1.0);
  //      defineNumber(&exposureNP);
  // Add any custom properties here (e.g. sensor temp, gain)
  // Example: a number property for custom gain
  //            IUFillNumber(&GAIN_PROPERTY, "Gain", "gain", 0, 155, 1, 20);
  //           defineNumber(&GAIN_PROPERTY);
  // INDI::CCD::defineNumber("GAIN", "Gain", "Camera", 0, 100, 1, 50);

  return true;
}

// Add properties to the client when client connects
void SV205::ISGetProperties(const char *dev) {
  INDI::CCD::ISGetProperties(dev);
  // publish custom props if connected
  return;
}

// Handle CONNECT / DISCONNECT from clients
bool SV205::Connect() {
  // open camera device here using v4l2/libcamera
  // return true only on success
  IDMessage("Connecting ", " SV205");
  // TODO: open USB device / init capture interface
  return INDI::CCD::Connect();
}

bool SV205::Disconnect() {
  // close camera
  IDMessage("Disconnecting SV205...", "thank you");
  return INDI::CCD::Disconnect();
}

// Called when Ekos/Client sets numbers/switches/text
bool SV205::ISNewNumber(const char *dev, const char *name, double values[],
                        char *names[], int n) {
  // Handle custom numbers like GAIN
  if (strcmp(name, "GAIN") == 0) {
    // apply gain to camera hardware
    return true;
  }
  return INDI::CCD::ISNewNumber(dev, name, values, names, n);
}

bool SV205::ISNewSwitch(const char *dev, const char *name, ISState *states,
                        char *names[], int n) {
  return INDI::CCD::ISNewSwitch(dev, name, states, names, n);
}
bool SV205::ISNewText(const char *dev, const char *name, char **texts,
                      char **names, int n) {
  return INDI::CCD::ISNewText(dev, name, texts, names, n);
}

// Start exposure — Ekos will call this
bool SV205::StartExposure(float exposure) {
  // Implement capture start using your camera API
  // set CCD_EXPOSURE_PROPERTY and CCD_BUSY appropriately
  char buffer[100];
  sprintf(buffer, "Starting Exposure %f s", exposure);
  IDMessage("Sv205", buffer);
  // For demo, we'll simulate capture and call processExposureComplete
  // In real driver spawn thread to wait for exposure time and capture frame
  return true;
}

// Called to actually retrieve image after exposure finishes
bool SV205::processExposureComplete() {
  // acquire image buffer from camera, convert to FITS/INDI_BLOB
  // set BLOB and send with new BLOB data
  // Example (pseudo):
  // char *img = ...; size_t imgLen = ...;
  // sendBLOB(IMAGE_NAME, (uint8_t*)img, imgLen);
  return true;
}

const char* SV205::getDefaultName() {
    return "SV205 PLUS";
}


// Factory function called by INDI library
extern "C" {
static const char *getDefaultName() { return "indi_sv205_plus"; }

// driver entry points
void ISGetProperties(const char *dev) {
  static SV205 *drv = nullptr;
  if (!drv)
   drv = new SV205();
  drv->ISGetProperties(dev);
}

void ISNewNumber(const char *dev, const char *name, double *values,
                 char *names[], int n) {
  // Dispatch to driver instance...
}

// ...and so on. Use INDI driver skeleton docs / examples for full set of entry
// points.
}
