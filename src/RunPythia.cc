#include "RunPythia.h"
#include "SetXML.h"
#include "SetFile.h"

#include <iostream>

RunPythia::RunPythia(std::string xml_filename_in, std::string output_dirname_in)
    : xml_filename(xml_filename_in), output_dirname(output_dirname_in)
{
  std::cout << "-@-Creating RunPythia" << std::endl;
}

RunPythia::RunPythia()
{
  std::cout << "-@-Creating RunPythia" << std::endl;
}

RunPythia::~RunPythia()
{
  std::cout << "-$-Deleting RunPythia" << std::endl;
}

void RunPythia::Init()
{
  std::cout << "=========================================================" << std::endl;
  SetXML::Instance()->OpenXMLFile(xml_filename);
  std::cout << "=========================================================" << std::endl;
  SetFile::Instance()->Init(output_dirname);
  std::cout << "=========================================================" << std::endl;
  SetXMLParameters();
}

void RunPythia::SetXMLParameters()
{

  std::cout << "\n============================" << std::endl;
  std::cout << "= Set Parameters in Pythia =" << std::endl;
  std::cout << "----------------------------" << std::endl;

  nEvents = SetXML::Instance()->GetElementInt({"nEvents"});
  pTHatMin = SetXML::Instance()->GetElementText({"pTHatMin"});
  pTHatMax = SetXML::Instance()->GetElementText({"pTHatMax"});
  hadronization = SetXML::Instance()->GetElementInt({"hadronization"});
  std::vector<std::string> xml_parameters = SetXML::Instance()->GetElementVectorText({"Pythia", "Item"});
  //--
  parameter_strings.push_back("Main:numberOfEvents = " + std::to_string(nEvents));
  parameter_strings.push_back("PhaseSpace:pTHatMin = " + pTHatMin);
  parameter_strings.push_back("PhaseSpace:pTHatMax = " + pTHatMax);
  parameter_strings.insert(parameter_strings.end(), xml_parameters.begin(), xml_parameters.end());
  //--
  for (auto param : parameter_strings)
  {
    std::cout << "- " << param << std::endl;
    pythia.readString(param);
  }
  std::cout << "============================\n"
            << std::endl;
}

void RunPythia::SetHadronizationParameters()
{
  if (hadronization)
  {
    parameter_strings.push_back("HadronLevel:all = on");
    parameter_strings.push_back("HadronLevel:Decay = on");
    parameter_strings.push_back("ParticleDecays:limitTau0=on");
    parameter_strings.push_back("ParticleDecays:tau0Max = 10");
  }
  else
  {
    parameter_strings.push_back("HadronLevel:all = off");
    parameter_strings.push_back("HadronLevel:Decay = off");
  }
}

void RunPythia::Exec()
{
  pythia.init();
  std::string particle_list_filename = SetFile::Instance()->GetParticleListFileName(pTHatMin, pTHatMax, hadronization);
  std::string sigma_filename = SetFile::Instance()->GetSigmaFileName(pTHatMin, pTHatMax);
  //-
  std::ofstream f_particle, f_sigma;
  f_particle.open(particle_list_filename, std::ios::out);
  f_sigma.open(sigma_filename, std::ios::out);
  //-
  std::cout << "======================================================================================================" << std::endl;
  std::cout << "[RunPythia] Start RunPythia" << std::endl;
  std::cout << "pTHat: " << pTHatMin << "-" << pTHatMax << " GeV/c" << std::endl;
  std::cout << "output particle list file: " << particle_list_filename << std::endl;
  std::cout << "output sigma_hard file: " << sigma_filename << std::endl;
  std::cout << "======================================================================================================" << std::endl;
  //-
  int p_stat = 0;
  int i_ev = 0;
  for (int i_run = 0; i_run < nEvents; ++i_run)
  {
    //------------------
    if (!pythia.next())
    {
      continue;
    }
    //------------------
    if ((20 * i_ev) % nEvents == 0)
    {
      std::cout << "Event# " << i_ev << "...";
    }
    //------------------
    f_particle << "#\tEvent" << i_ev + 1
               << "ID\tpstat\tE\tPx\tPy\tPz\tEta\tPhi" << std::endl;
    //------------------
    int sn = 0;
    for (int i = 0; i < pythia.event.size(); ++i)
    {
      if (pythia.event[i].isFinal() && fabs(pythia.event[i].eta()) < 20)
      {
        f_particle << sn << "\t"
                   << pythia.event[i].id() << "\t"
                   << p_stat << "\t"
                   << pythia.event[i].e() << "\t"
                   << pythia.event[i].px() << "\t"
                   << pythia.event[i].py() << "\t"
                   << pythia.event[i].pz() << "\t"
                   << pythia.event[i].eta() << "\t"
                   << pythia.event[i].phi() << std::endl;
        sn++;
      }
    }
    //------------------
    i_ev++;
  }
  std::cout << "\nDONE! Total Event Number: " << i_ev << std::endl;
  //------------------
  f_sigma << pythia.info.sigmaGen() << "\t"
          << pythia.info.sigmaErr() << std::endl;
  std::cout << "sigma_hard = "
            << pythia.info.sigmaGen() << "+/-"
            << pythia.info.sigmaErr() << std::endl;
  //------------------
  f_particle.close();
  f_sigma.close();  
}
