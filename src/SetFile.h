
#ifndef SETFILE_H
#define SETFILE_H

#include <string>
#include <iostream>
#include <vector>
//#include<stdexcept>

class SetFile
{
public:
  static SetFile *Instance();

  void SetOutputDir(std::string m_out_name)
  {
    out_dir = m_out_name;
    std::cout << "[SetFile] Output File Directory: " << out_dir << std::endl;
  }

  void Init(std::string m_out_name);

  std::string
  GetParticleListFileName(std::string ptHatMin, std::string ptHatMax, int hadron = 1);
  std::string
  GetSigmaFileName(std::string ptHatMin, std::string ptHatMax);

  // std::string
  // GetSigmaFileName( double ptHatMin, double ptHatMax, int i_seq = 0 );

  // std::string GetOutPath(std::string name);
  // std::string GetOutPath();

private:
  static SetFile *m_pInstance;
  SetFile()
  {
    std::cout << "-@-Creating SetFile" << std::endl;
  }

  SetFile(SetFile const &) {}

  void SetXMLParameters();

  std::string out_dir;
  std::string output_head_hadron;
  std::string output_head_parton;
  std::string output_join;
  std::string output_tail;
  std::string sigma_head;
  std::string sigma_join;
  std::string sigma_tail;
};
#endif
