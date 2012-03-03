PLATYPUS {
	
	i = 1;
	n = 2;
	m = 3;
	f = 1.5;
	z = 3.5;
	result = 0.0;
	first# = "first";
	second# = "second";
	
	result = 1 + 2 - i + m / f * z;
	first# = first# << second# << "YAY";

	OUTPUT();
	OUTPUT("result = ");
	OUTPUT(result);
	
	OUTPUT();
	OUTPUT("first# = ");
	OUTPUT(first#);
	OUTPUT();
	

}