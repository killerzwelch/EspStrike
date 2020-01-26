#ifndef CONFIG_H
#define CONFIG_H

#include <vector>
#include <Arduino.h>
#include "Parameter_t.h"

using namespace std;


class Config {
    public:
        /*Read the xml, in this example this is an string array*/
        void readXml(vector<String> xml);
        void readXml(String xml);
        /*Method to parse the parameter string in XML*/
        vector<Parameter_t> handleParameter(String parameterString);
        vector<String> splitXML(String xml);
        void evalConfigTag(String tag, vector<Parameter_t> params);

};

#endif
