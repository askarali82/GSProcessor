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

## Settings Configuration

The software relies on a 'Settings.ini' file to read details about reference and background samples' spectra, for areas of photo peaks, and photo peak efficiency for Be-7.

## Building

This repository provides the source code for the Gamma Sectra Processor, written in Embarcadero C++ Builder 10.3 using the VCL library. You will need to compile the source code using C++ Builder 10.3 or a compatible compiler to build executable binary for Windows.
