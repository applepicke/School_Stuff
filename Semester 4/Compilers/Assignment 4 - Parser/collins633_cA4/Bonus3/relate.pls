PLATYPUS {
	ione = 1;
	ifloat = 1.01;
	istring# = "bob";
	
	OUTPUT();
	
	IF ( ione == 1 ) THEN
		OUTPUT("ione == 1");
		OUTPUT();
	ELSE {
		OUTPUT("ione != 1");
		OUTPUT();
	};
	
	IF ( ifloat > 1 ) THEN
		OUTPUT("ifloat > 1");
		OUTPUT();
	ELSE {
		OUTPUT("ifloat < 1");
		OUTPUT();
	};
	
	IF ( istring# == "bob" ) THEN
		OUTPUT("string == bob");
		OUTPUT();
	ELSE {
		OUTPUT("string != bob");
		OUTPUT();
	};
	
	IF ( istring# != "rob" ) THEN
		OUTPUT("string != bob");
		OUTPUT();
	ELSE {
		OUTPUT("string == bob");
		OUTPUT();
	};
	
	IF ( ifloat == 1.01 .AND. ione == 1 ) THEN
		OUTPUT("ifloat == 1.01 .AND. ione == 1");
		OUTPUT();
	ELSE {
		
	};
	
	IF (ifloat < 1 .OR. ione > 0) THEN
		OUTPUT("ifloat < 1 .OR. ione > 0");
		OUTPUT();
	ELSE {
	
	};
	
	IF (ifloat < 1 .AND. ione == 1 .OR. 1 == ione .AND. ione == 2) THEN
	ELSE {
		OUTPUT("nope");
		OUTPUT();
	};
	
	OUTPUT();

}