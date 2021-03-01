# rbl2gif

This is a simple program to convert the label templates included with the Piano Roll LabelMaker in the RBL format to GIF files that can be used in other image editing programs.  The RBL format is a simple obfuscation of the GIF89 format, replacing the GIF89 file tag with PRBLM and shifting all bytes (excepting the final two) up by 0x01, rolling over 0xff to 0x00.  This program returns the file tag to the correct value and shifts the bits back to the correct values.

Usage:  rbl2gif.py \<infile\> \<outfile\>

  The \<infile\> must exist, and cannot be the same value as \<outfile\>.  If \<outfile\> does not end in .gif, a warning will be generated, but the conversion will proceed.  The program doesn't check for a valid RBL file, and will apply the conversion to any input file.  Obviously this will result in a useless output file if anything but a valid RBL file is input.  
  
  Note: This program does not include any RBL files, and I will not provide them.  The demo version of Piano Roll LabelMaker can be found fairly easily using https://archive.org, which includes a small sample of RBL files for testing.  Using this program does not provide the user with any new rights to the RBL or GIF files, so use and distribution of the output GIF files continue to be governed by the license of the Piano Roll LabelMaker software.  
