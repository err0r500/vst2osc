#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include "500SimpleSend.h"
#include <string>

    String params::begOfMess = String::empty;
    std::string params::endOfMess [10] = {""};
    int params::port=7000;
    std::string params::destIP = "127.0.0.1";

params::params (){}
std::string params::getDestIP(){
    return destIP;
}


void params::setEndOfMess(int identifier, String endpattern){
    String messToSend = begOfMess;
    messToSend += endpattern;
    std::string s = messToSend.toUTF8 ();
    params::endOfMess[identifier] = s; 
}

void params::setBegOfMess(String begpattern){
    params::begOfMess = begpattern;
}

void params::setPort(int newPort){
    params::port = newPort;
}

void params::setDest(String newDest){
    params::destIP = newDest.toUTF8();
}

osc500::osc500(){};

void osc500::testOSC(int identifier, std::string url, std::string endmess, float OSCval, int Port)
{
    
    UdpTransmitSocket transmitSocket( IpEndpointName( params::getDestIP().c_str(), Port ));
    char buffer[1024];
    osc::OutboundPacketStream p( buffer, 1024 );
    std::string mess = url + endmess;

    p.Clear();
    p << osc::BeginBundleImmediate
        << osc::BeginMessage(mess.c_str()) 
           << OSCval 
        << osc::EndMessage
    << osc::EndBundle;



    transmitSocket.Send( p.Data(), p.Size() );
    p.Clear();
}

