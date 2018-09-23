#ifndef OSC500_qlskdsql
#define OSC500_qlskdsql

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"
#include "../JuceLibraryCode/JuceHeader.h"

#include <string>

class params{
private:
	static String begOfMess;
	static std::string endOfMess [10];
	static int port;
	static std::string destIP;
public:
	params();
	~params(){};
	static std::string getDestIP();

	static void setBegOfMess(String begpattern);
	static void setEndOfMess(int identifier, String endpattern);
	static void setPort(int newPort);
    static void setDest(String newDest); 	
};


class osc500: public params {
public :
	osc500();
	~osc500(){};
	void testOSC(int identifier, float OSCval);
	void testOSC(int identifier, std::string url, std::string endmess, float OSCval, int Port);

	int identifier;

	JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (osc500);
};






#endif