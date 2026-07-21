# Gamma Spectra Processor

## Scintillation Gamma-Spectra Analysis Software

This software analyzes scintillation gamma spectra to determine the activities of the following radionuclides in environmental objects:

- Th-232
- Ra-226
- K-40
- Cs-137
- Be-7

## Analysis Technique

The software utilizes techniques described in the article:

*"Gamma-spectrometric determination of natural radionuclides and 137Cs concentrations in environmental samples. The improved scintillation technique"*

Published in "Radiation Measurements", vol. 43, issue 1, pp. 66-71, January 2008.
https://doi.org/10.1016/j.radmeas.2007.11.006

## Spectrum File Format

The software works with spectrum files in the format specified by the files:

- spc-sample.asw
- spc-sample.gsp

These files serve as reference examples.

## Building

This repository contains the source code for **GSProcessor**, developed primarily in **Embarcadero C++ Builder 10.3** using the **VCL** framework.

The main application can be built using **Embarcadero C++ Builder 10.3** (or a later compatible version) to produce the Windows executable.

The software also includes a **peak-searching module** implemented as a separate **DLL** using **Microsoft Visual Studio** and the **ROOT** framework. To build this module from source, you will need a compatible version of **Microsoft Visual Studio** with the **ROOT** libraries properly installed and configured.

When building the complete project from source, compile both the main application and the peak-searching DLL, then place the generated DLL in the same directory as the GSProcessor executable.
