import os
import sys
import yaml
import numpy as np


def GetPthatFromYaml(yaml_file_path):
  with open(yaml_file_path, 'r') as ymlf:
    yaml_data_list = yaml.safe_load(ymlf)
  return yaml_data_list['pt_hat_bins']

def GetCommand(command,xml_path,out_dir,pthatbin):
  return '{} {} {} {} {}'.format(command,xml_path,out_dir,str(pthatbin[0]),str(pthatbin[1]))

def GetSlurmCommand(que,jobname,job_out,job_error,command):
  return 'sbatch -q {} --time 720:00:00 --mem 24G --job-name {} -o {} -e {} -- {}'.format(que,jobname,job_out,job_error,command)

def Main(pthatbin_list, dir_of_this_code, exe, xml_path, out_dir, que, name):

  print('# Start Jobsubmission')  
  print('#------')  
  print('# exe: ', exe) 
  print('# xml: ', xml_path)  
  print('# output: ', out_dir)    
  print('# que: ', que)      


  for pthatbin in pthatbin_list:
    print('#------')
    ##########################################################
    jobname = name+'{}-{}'.format(str(pthatbin[0]),str(pthatbin[1]))
    print('# job: ' +jobname+ ',  pthatbin: ', pthatbin[0], '-', pthatbin[1], 'GeV')

    command = GetCommand(exe,xml_path,out_dir,pthatbin)
    #print(command)

    if que != '' and que != 'no' and que != 'No' and que != 'No':
      job_out = os.path.join(out_dir,'o_'+jobname+'.txt')
      job_error = os.path.join(out_dir,'e_'+jobname+'.txt')
      print('# record: ' +job_out)
      print('# error: ' +job_error)

      command = os.path.join(dir_of_this_code,'JobMaster') + '"{}" "{}"'.format(dir_of_this_code, command)
      command = GetSlurmCommand(que,jobname,job_out,job_error,command)
    print(command)
    os.system(command)

  print('#----------------------------------------')


if __name__ == '__main__':



  #####################################################################
  # manage path info
  path_of_this_code = os.path.abspath(__file__)
  initial_path = os.getcwd()
  dir_of_this_code = os.path.dirname(path_of_this_code)
  print('\n#########################################')
  print('# Python code: SD_ATLAS.py') 
  print('# Path of this code:', path_of_this_code)
  print('# Your current directory:', initial_path)
  print('#----------------------------------------')

  #####################################################################
  # manage arguments
  import argparse
  parser = argparse.ArgumentParser()
  parser.add_argument('--xml', type=str, default=os.path.join(dir_of_this_code,'../config/test.xml'))
  parser.add_argument('--o', type=str, default=os.path.join(dir_of_this_code,'PurePythiaResults'))
  parser.add_argument('--q', type=str, default='primary')
  parser.add_argument('--n', type=str, default='ppyth_')
  parser.add_argument('--exe', type=str, default=os.path.join(dir_of_this_code,'../build/Main'))
  parser.add_argument('--yaml', type=str, default=os.path.join(dir_of_this_code,'pthatbins.yaml'))
  args = parser.parse_args()
  if args.q == "ex":
    args.q = "express -p eamxp"

  #####################################################################
  # Read pthat bins
  yaml_file_path = os.path.join(dir_of_this_code,args.yaml)
  print('# Read Yaml File:', yaml_file_path)  
  pthatbin_list = GetPthatFromYaml(yaml_file_path)
  print('#----------------------------------------')


  #####################################################################
  # Run Code
  Main(pthatbin_list, dir_of_this_code, args.exe, args.xml, args.o, args.q, args.n)
  os.chdir(initial_path)
  print('# You came back to')
  print('#\t', initial_path)
  print('# Done!')
  print('#########################################\n')      