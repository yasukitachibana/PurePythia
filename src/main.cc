#include "RunPythia.h"
#include <iostream>

//#######################################################
bool run_code = false;
std::string xml_filename;
std::string output_dirname;
std::string pthat_min_manual;
std::string pthat_max_manual;
//#######################################################
void Show();
void CheckArg(int argc, char **argv);
//#######################################################
int main(int argc, char **argv)
{

  int StartTime = time(NULL);

  //#######################################################
  Show();
  CheckArg(argc, argv);
  //#######################################################

  //#######################################################
  // Execution
  //#######################################################
  if (run_code)
  {
    std::cout << "\nSTART! 💨\n"
              << std::endl;
    RunPythia run(xml_filename, output_dirname);
    run.Init(pthat_min_manual, pthat_max_manual);
    run.Exec();
    std::cout << "\nFINISH! 🏁\n"
              << std::endl;
  }
  //#######################################################

  //#######################################################
  std::cout << "#########################################################" << std::endl;
  int EndTime = time(NULL);
  int Hour = (EndTime - StartTime) / 3600;
  int Minute = ((EndTime - StartTime) / 60) - Hour * 60;
  int Second = (EndTime - StartTime) - Hour * 60 * 60 - Minute * 60;
  std::cout << "Programme run time = " << Hour << "::" << Minute << "::" << Second << std::endl;
  std::cout << "#########################################################" << std::endl;
  std::cout << std::endl;
  return 0;
}

void CheckArg(int argc, char **argv)
{
  pthat_min_manual = "";
  pthat_max_manual = "";
  std::cout << "=========================================================" << std::endl;
  if (argc > 1 && !strcmp(argv[1], "test"))
  {
    std::cout << "-->test mode<--" << std::endl;
    run_code = true;
    xml_filename = "../config/test.xml";
    output_dirname = "./";
  }
  else if (argc > 2)
  {
    std::cout << "-->run code<--" << std::endl;
    run_code = true;
    xml_filename = argv[1];
    output_dirname = argv[2];

    if (argc > 4)
    {
      pthat_min_manual = argv[3];
      pthat_max_manual = argv[4];
    }
  }
  else
  {
    run_code = false;
    std::cout << "Please Specify XML File, input directory and output directory" << std::endl;
    std::cout << ".Main [XML File] [output directory]" << std::endl;
  }
  std::cout << "=========================================================" << std::endl;
}

void Show()
{
  std::cout << "#########################################################" << std::endl;
  std::cout << std::endl;
  std::cout << "---------------------" << std::endl;
  std::cout << "- Exec Pythia Code  -" << std::endl;
  std::cout << "  Yasuki  Tachibana " << std::endl;
  std::cout << "---------------------" << std::endl;
  std::cout << std::endl;
}
