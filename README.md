# rbl2gif and gif2rbl

This is a simple program to convert label templates included with the Piano Roll LabelMaker in the RBL format to GIF files that can be used in other image editing programs and back to RBL files that can be imported as templates.  The RBL format is a trivial obfuscation of the GIF89 format, replacing the GIF89 file tag with PRBLM and shifting all bytes (excepting the final two) up by 0x01, rolling over 0xff to 0x00.  This program returns the file tag to the correct value and shifts the bits back to the correct values.

Python version:

  usage:  
  `rbl2gif.py [-h] \<infile\> \<outfile\>`
  
  `gif2rbl.py [-h] \<infile\> \<outfile\>`
  
c++ version:

  usage: 
	
`rbl2gif.exe [-h] \<infile\> \<outfile\>`
  
`gif2rbl.exe [-h] \<infile\> \<outfile\>`

  The \<infile\> must exist, and cannot be the same value as \<outfile\>.  If \<outfile\> does not end in .gif for rbl2gif or .rbl for gif2rbl, a warning will be generated, but the conversion will proceed.  The program doesn't check for a valid file, and will apply the conversion to any input file.  Obviously this will result in a useless output file if anything but a valid RBL or GIF file is input.  

When converting GIF images to RBL files, use GIFs with transparent backgrounds if you intend to use background colors or patterns in the label maker program.  Once the RBL is created, create a GIF thumbnail file that is roughly 100x100 pixels in size with the same name as the RBL file.  There must also be a TXC file with the same name that contains the template layout data.  

The c++ and python versions have the same functionality.  Since many antivirus programs now flag compiled Python programs as malware I decided that learning enough c++ to write a properly compiled version was worth the effort.  I'll try to keep both versions current, but I recommend using the compiled c++ version.  
  
  Note: This program does not include any RBL files, and I will not provide them.  The demo version of Piano Roll LabelMaker can be found fairly easily using https://archive.org, which includes a small sample of RBL files for testing.  Using this program does not provide the user with any new rights to the RBL or GIF files, so use and distribution of the output GIF files continue to be governed by the license of the Piano Roll LabelMaker software.  
