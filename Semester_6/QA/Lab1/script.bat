echo off
echo Lab 1 Example Test Harness 
mkdir bin
cd src
javac -cp "..\bin;..\junit4.10\junit-4.10.jar" -d ..\bin Math.java
javac -cp "..\bin;..\junit4.10\junit-4.10.jar"  -d ..\bin TestMath.java

echo Running the tests
cd ..
dir
echo Now running the Test Harrness
echo ----------------------------------------------------------------------------
java -cp ".\bin;.\junit4.10\junit-4.10.jar" org.junit.runner.JUnitCore TestMath

pause