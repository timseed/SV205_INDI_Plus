// indi_sv205.cc  -- minimal INDI CCD driver skeleton
// #include <libindi/baseclient.h>
#ifndef SV205_PLUS
#define SV205_PLUS 

#include <libindi/defaultdevice.h>
#include <libindi/indibase.h>
#include <libindi/indidevapi.h>
#include <libindi/indiccd.h>

//#include <indidevapi.h>
//#include <indicom.h>
#include <memory>
#include <vector>
using namespace std;

class SV205 : public INDI::CCD
{
    public:
        SV205();
        ~SV205(); 

        // Called once at driver init
        bool initProperties() override;

        // Add properties to the client when client connects
        void ISGetProperties(const char *dev) override;
        // Handle CONNECT / DISCONNECT from clients
        bool Connect() override;
        bool Disconnect() override;
        // Called when Ekos/Client sets numbers/switches/text
        bool ISNewNumber(const char *dev, const char *name, double values[], char *names[],int n) override;
        bool ISNewSwitch(const char *dev, const char *name, ISState *states, char *names[],int n) override;
        bool ISNewText(const char * dev, const char * name, char **texts, char *names[], int n) override;
        // Start exposure — Ekos will call this
        bool StartExposure(float exposure) override;
        // Called to actually retrieve image after exposure finishes
        bool processExposureComplete();
        const char* getDefaultName() override;   // <-- add this
  private:
    INumber exposureNP;
    IText imageBP;
};
/*
// Factory function called by INDI library
extern "C" {
    static const char *getDefaultName()
    {
        return "indi_sv205_ccd";
    }

    // driver entry points
 void ISGetProperties(const char *dev);
 void ISNewNumber(const char *dev, const char *name, double *values, char *names[], int n);
*/

#endif
