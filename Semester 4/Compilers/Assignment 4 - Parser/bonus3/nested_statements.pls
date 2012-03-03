!< This file contains many nested statements, and is synctactically correct

PLATYPUS {
	i = 1;
	n = 2;
	m = 3;
	
	!< Nothing should happen, but is synctactically correct
	IF (i == 1) THEN
	ELSE {
		IF (n == 2) THEN
		ELSE {
			IF (m == 3) THEN
			ELSE {
			
			};
		};
	};	
	
	IF (i != 1) THEN
	ELSE {
		IF (n != 2) THEN
		ELSE {
			IF (m != 3) THEN
			ELSE {
				OUTPUT();
				OUTPUT("WE MADE IT");
				OUTPUT();
			};
		};
	};	

}