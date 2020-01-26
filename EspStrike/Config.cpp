#include "Config.h"

#include "ActionHandler.h"
#include "ClassMapper.h"
#include "System.h"
#include "Const.h"
#include "Player.h"

/*Read the xml, in this example this is an string array*/
void Config::readXml(vector<String> xml) {
  ActionHandler actionHandler;
  bool playerConfigSwitch= false;
  for(unsigned char i = 0;i<xml.size();i++)
  {
      if(xml[i]=="") continue;
      if(System::printSerial) {
        Serial.println("iteration " + String(i) + " " + xml[i]);
      }
      unsigned char startpos=xml[i].indexOf("<");
      unsigned char endpos=xml[i].indexOf(">",startpos);
      unsigned char firstSpace=xml[i].indexOf(" ",startpos);
      
      bool endTag = 0;
      if (xml[i].indexOf("/",startpos) == startpos+1)
      {
          endTag=1;
          startpos++;
      }
      
      //parameter handling
      String parameterString;
      if(firstSpace > -1 and firstSpace < endpos)
      {
          //There may be a parameter
          parameterString = xml[i].substring(firstSpace+1,endpos - firstSpace -1);
          endpos = firstSpace;
      }
      String tagName = xml[i].substring(startpos+1, endpos - startpos -1);
      if(System::printSerial) {
        Serial.println("tagName: '" + tagName + "' endTag? " + String(endTag));
        Serial.println("parameter: '" + parameterString + "'");
      }

      vector<Parameter_t> params;
      GenericAction *genAct = 0x0;
      genAct = ClassMapper::mapClass(tagName);
      ActionList_t *ptr;
      ActionList_t *addedAction;
      /*Set correct list where to add the action*/
      if(tagName == "onHit") {
          ptr=&System::on_Hit;
          playerConfigSwitch=false;
      }
      else if(tagName == "onTick") {
          ptr=&System::on_Tick;
          playerConfigSwitch=false;
      }
      else if(tagName == "onLifeLoss") {
          ptr=&System::on_LifeLoss;
          playerConfigSwitch=false;
      }
      else if(tagName == "onDeath") {
          ptr=&System::on_Death;
          playerConfigSwitch=false;
      }
      else if(tagName == "player") {
          ptr=0x0;
          if(System::printSerial) {
            Serial.println("found player tag");
          }
          playerConfigSwitch=true;
      }
      if(playerConfigSwitch==true) {
          params=handleParameter(parameterString); 
          evalConfigTag(tagName,params);
      }
      else if (genAct!=0x0 and endTag==0)
      {
          if (!parameterString.equals("") ) { 
              params=handleParameter(parameterString); 
              addedAction = actionHandler.addAction(ptr,tagName);
              addedAction->action->init(params);
              
              /*genAct->execute(params);*/

          }
          else {
              addedAction = actionHandler.addAction(ptr,tagName);
              addedAction->action->init();

          }
      }
      else if (genAct==0x0 and endTag==0) {
          if(System::printSerial) {
            Serial.println("Tag '" + tagName + "' not defined");
          }
      }
  }

}

/*Method to parse the parameter string in XML*/
vector<Parameter_t> Config::handleParameter(String parameterString)
{
    unsigned char count=0;
    for (unsigned char i = 0; i < parameterString.length(); i++) {
        if (parameterString.charAt(i) == '=')    
            count++;
    }
    vector<Parameter_t> params;
    for(unsigned char i=0;i<count;i++) {
      unsigned char startpos;
      unsigned char endpos;
      if (i==0) {
          startpos=0;
      }
      else
      {
          startpos=endpos+1;
      }
       if (endpos==-1) { endpos = parameterString.length(); }
      unsigned char dividor = parameterString.indexOf("=",startpos);
      unsigned char startValue = dividor;
      //Get "-enclosed values correct
      if (parameterString.charAt(dividor+1)== '"') {
      endpos = parameterString.indexOf("\"",dividor+2);
      startValue++;
      }
      else {
        endpos = parameterString.indexOf(" ",startpos);
      }
      params.push_back(Parameter_t());
      params[i].parameterKey=parameterString.substring(startpos,dividor-startpos);
      params[i].parameterValue=parameterString.substring(startValue+1,endpos - startValue-1);
      if(System::printSerial) {
        Serial.println(" parameter_t " + String(i+1) + ": '" + params[i].parameterKey + "' : '" + params[i].parameterValue + "'");
      }
    }
    return params;
}

vector<String> Config::splitXML(String xml) {
    vector<String> ret;
    int lastpos=xml.indexOf("<",0);
    int i=0;
    while(lastpos > -1) {
        ret.push_back(String());
        ret[i]=xml.substring(lastpos,xml.indexOf(">",lastpos) - lastpos+1);
        lastpos=xml.indexOf("<",lastpos+1);
        i++;
    }
    return ret;
}

void Config::evalConfigTag(String tag, vector<Parameter_t> params) {

    for (unsigned char i =0; i<params.size();i++) {
        if(tag == __KEY__HEALTH__ && params[i].parameterKey == __KEY__VAL__) {
            Player::health = params[i].parameterValue.toInt();
            Player::maxHealth = Player::health;
        }            
        else if(tag == __KEY__LIFE__ && params[i].parameterKey == __KEY__VAL__) {
            Player::life = params[i].parameterValue.toInt();
        }
        else
        {
          if(System::printSerial) {
            Serial.println("WARN: unknown config: tagname: '" + tag + "' Key: '" + params[i].parameterKey + "' value '" + params[i].parameterValue + "'");
          }
        }
    }
}
