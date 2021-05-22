#include "SetFile.h"
#include "SetXML.h"
//#include "JetScapeLogger.h"
//#include <stdlib.h>

#include <sstream>
#include <iomanip>

SetFile *SetFile::m_pInstance = NULL;

SetFile *SetFile::Instance()
{
  if (!m_pInstance)
  {
    std::cout << "[SetFile] Created SetFile Instance" << std::endl;
    m_pInstance = new SetFile();
  }
  return m_pInstance;
}

void SetFile::Init(std::string m_out_name)
{
  SetOutputDir(m_out_name);
  SetXMLParameters();
}

void SetFile::SetXMLParameters()
{
  output_head_hadron = SetXML::Instance()->GetElementText({"outputFiles", "events", "headHadron"});
  output_head_parton = SetXML::Instance()->GetElementText({"outputFiles", "events", "headParton"});
  output_join = SetXML::Instance()->GetElementText({"outputFiles", "events", "join"});
  output_tail = SetXML::Instance()->GetElementText({"outputFiles", "events", "tail"});
  sigma_head = SetXML::Instance()->GetElementText({"outputFiles", "sigma", "head"});
  sigma_join = SetXML::Instance()->GetElementText({"outputFiles", "sigma", "join"});
  sigma_tail = SetXML::Instance()->GetElementText({"outputFiles", "sigma", "tail"});
}

std::string
SetFile::GetParticleListFileName(std::string ptHatMin, std::string ptHatMax, int hadron )
{
  std::string head;
  if(hadron)
  {
    head = output_head_hadron;
  }else{
    head = output_head_parton;
  }
  return out_dir+'/'+head + ptHatMin + output_join + ptHatMax + output_tail;
}

std::string
SetFile::GetSigmaFileName( std::string ptHatMin, std::string ptHatMax){
  return out_dir+'/'+sigma_head + ptHatMin + sigma_join + ptHatMax+ sigma_tail;
}