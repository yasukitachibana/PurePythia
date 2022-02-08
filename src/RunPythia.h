#ifndef RUNPYTHIA_H
#define RUNPYTHIA_H

#include "Pythia8/Pythia.h"


#include <iostream>
#include <vector>

class RunPythia
{

public:
  RunPythia();
  RunPythia(std::string xml_filename, std::string output_dirname);
  ~RunPythia();
  void Init();
  void Exec();

private:

  const std::string xml_filename;
  const std::string output_dirname;

  void SetXMLParameters();
  void SetHadronizationParameters();  
  void ExecOnePtHatBin(int i);

  std::vector<std::string> parameter_strings;
  int nEvents;
  std::vector<std::string> pTHatMin, pTHatMax;
  int hadronization;
  // int running_mode;
  // std::vector< std::string > observables;
  // std::string reconstruction_method;
  // std::string subtraction_method;
  // std::string input_file_style;

  // void ShowSettings();
};

#endif
