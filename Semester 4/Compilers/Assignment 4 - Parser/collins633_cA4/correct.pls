!<This file will test the parser for full informal grammar specification
!<This should be regarded as an error free program

PLATYPUS {
	
	!<Initialized variable declarations
	iInit = 1;
	jInit = 2;
	mInit = 010;		!<The number 8 in octal
	nInit = 4;
	float = 1.0;
	anotherFloat = 20.;
	iVar = iInit;
	jVar = jInit;
	
	!<Switch data type
	mVar = 2.0;
	nVar = 0.010;
	
	!<String variables
	iString# = "Pizza";
	aString# = "Fallsview";
	
	!< Some arithmetic statements
	iInit = (iInit + anotherFloat - 3) * 012 /2.3;		!<Mix of integer and floating point
	iString#= iString# << aString# << "Billy Jean";
	
	!<Selection Statement
	IF(iString# == aString#) THEN
		iString# = "GOODLY";
	ELSE {
		iString# = "BADLY";
	};
	
	!<Optional Statements
	IF (iString# == "BADLY") THEN
	ELSE {     };	

	!<Iteration Statement
	USING(i = 0, i < jInit, i = i + 1) REPEAT {
		aString# = aString# << "i";
	};
	
	!<Optional iteration
	USING(i = 0, i < jInit .AND. jInit != 50 .OR. iGo == 1, i = i + 1) REPEAT { };
	
	!<Input and output statements
	INPUT(iInput1);
	OUTPUT(iInput1);
	INPUT(iInput2);
	OUTPUT(iInput2);
	INPUT(iInput1, iInput2);
	OUTPUT();
	OUTPUT(iInput1, iInput2);
	OUTPUT("BINGO");

}