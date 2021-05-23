# PurePythia

The code to run Pythia simulations of PP collisions with simple configurations.

## Installation
Pythia is required. For example:
```
export PYTHIA8DIR=/path/to/pythia
export PYTHIA8_ROOT_DIR=/path/to/pythia
```

## Build the code
```
mkdir build
cd build
cmake ..
make -j
```

## Run the code
In the build directory, 
```
./Main ../config/test.xml ./
```
The first argument (`../config/test.xml` in the example above) is the path to the XML file storing the configuration information for the simulation. The second argument (`./` in the example above) is the path to the location where the output will be generated.

## Output
The output of the code stores the list of final state particles and is generated in the format of JETSCAPE Ascii.

## The XML Configuration
1. `nEvents`: the number of events.
1. `pTHatMin`: the minimum $p_{\mathrm{T}}$ in the rest frame of the initial hard scattering process.
1. `pTHatMax`: the maximum $p_{\mathrm{T}}$ in the rest frame of the initial hard scattering process.
1. `hadronization`: the flag to turn on and off the hadronization (1: on, 0: off). 
    - In the case of `hadronization=1` (on), the following are automatically set.
      ```
      HadronLevel:all = on
      HadronLevel:Decay = on
      ParticleDecays:limitTau0 = on
      ParticleDecays:tau0Max = 10
      ```
    - In the case of `hadronization=0` (off), the following are automatically set.
      ```
      HadronLevel:all = off
      HadronLevel:Decay = off
      ```
1. `Pythia`: other settings for Pythia.
1. `outputFiles`: the format of the name of output files.
    In the example of `text.xml`, the name of the output files are 
      - `JetscapeHadronListBin130_140.out` (final state particle list, `hadronization=1`)
      - `JetscapePartonListBin130_140.out` (final state particle list, `hadronization=0`)
      - `SigmaHardBin130_140.out` (value and error of $\sigma_{\mathrm{Hard}}$)