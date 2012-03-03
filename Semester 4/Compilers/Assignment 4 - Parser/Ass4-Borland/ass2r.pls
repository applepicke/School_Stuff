!< This program calculates the sum of 32767 even numbers.
!< The program is "lexically" and "syntactically" correct
!< and should not produce any error
PLATYPUS {
 
 a=+0.0;
 
 sum008 = 7.87050 ;
 INPUT(a,sum008); 
 USING(i = 0,i < 32767 .OR. i == 077777,i = i + 02 )REPEAT{
   a=
   a*i/0.5
   ;
   sum008 = sum008 + a - 1 ;
 };
 IF(text# == "")THEN
   text# = "prog" << "ram";
 ELSE {
   text# = text# << "ram";
 };
 OUTPUT("\* This is a platypus -:)-<-<-- \*");
 OUTPUT(text#);
 
 IF(text# == "program".OR.sum008!=8..AND.i>012)THEN
  OUTPUT(sum008);
  OUTPUT();
 ELSE{};
}
