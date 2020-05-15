Welcome!

This project takes a JPEG image uses it to generate a truly random seed for OpenSSL generation of RSA and AES keys.

Contributors:
Jonathan Garner
David Wynne

The project was written in Visual Studio 2019 (with C++ and C#) and has three projects in its solution
 - Image_Entropy: The algorithm that converts the image to a seed and outputs the seeds (C++)
 - testing: A partial implementation of the NIST Statistical Test Suite for testing the randomness of the generator (C/C++)
 - WindowsFormsApp1: A prototype app meant to display the functionality of the algorithm (C#)

To test this project for yourself it is recommended to simply launch the executable in this directory "app.exe"

If you would like to look through the code itself here is a break down of the directories...

\bin: Visual Studio created files
\codeMATLAB: Code written in MATLAB to test certain functionalities of the algorithm or make images for the report
\Debug: Visual Studio created files
\Image_Entropy: The project that contains the algorithm that converts the image to a seed and outputs the seeds
\obj: Visual Studio created files
\packages: Visual Studio created files
\testing: The project that contains a partial implementation of the NIST Statistical Test Suite for testing the randomness of the generator
\WindowsFormsApp1: The project that contains Aaprototype app meant to display the functionality of the algorithm

The rest of the files in this directory are deliverables for the project.

To run the Image_Entropy project by itself you will need to have both OpeSSL and OpenCV installed
opencv: 
https://opencv.org/releases/ 
Using version 4.2.0, follow tutorial below
https://medium.com/@subwaymatch/adding-opencv-4-2-0-to-visual-studio-2019-project-in-windows-using-pre-built-binaries-93a851ed6141

openSSL:
https://www.npcglib.org/~stathis/blog/precompiled-openssl/



