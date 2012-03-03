!<This is a syntactically correct PLATYPUS program
!<Weiler's law:
!<"Nothing is impossible for the man who doesn't have to do it himself."
!<"Parsing is passing." S^R & Compilers' law

PLATYPUS{
 a=-01;
 b=+0.;
 INPUT(c);
 INPUT(d,e,f);
 c=((d+e)/a)*f-(((d-e)*a)/f);
 USING(a = a,a!=b .OR. c==d .AND. e<f .OR. a>0,c = e)REPEAT{
   IF(a==1 .AND. b==0.0)THEN
    c=-(5.9);
   ELSE {c=-c;};  
 };   
 OUTPUT();
 OUTPUT("Results: ");
 OUTPUT(d,e,f,a);
}