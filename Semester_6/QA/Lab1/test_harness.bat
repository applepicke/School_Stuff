echo off
echo Lab 1 Example Test Harness 
mkdir bin
cd src
javac -cp "..\bin;..\junit4.10\junit-4.10.jar" -d ..\bin Math.java
javac -cp "..\bin;..\junit4.10\junit-4.10.jar"  -d ..\bin TestMath.java
javac -cp "..\bin;..\junit4.10\junit-4.10.jar"  -d ..\bin lastzero.java

cd ..\test
javac -cp "..\bin;..\junit4.10\junit-4.10.jar"  -d ..\bin LastZeroTest_correct.java
javac -cp "..\bin;..\junit4.10\junit-4.10.jar"  -d ..\bin LastZeroTest_defect.java

echo Running the tests
cd ..
dir
echo Now running the Test Harrness
echo ----------------------------------------------------------------------------
java -cp ".\bin;.\junit4.10\junit-4.10.jar" org.junit.runner.JUnitCore TestMath
java -cp ".\bin;.\junit4.10\junit-4.10.jar" org.junit.runner.JUnitCore LastZeroTest_correct
java -cp ".\bin;.\junit4.10\junit-4.10.jar" org.junit.runner.JUnitCore LastZeroTest_defect



pause