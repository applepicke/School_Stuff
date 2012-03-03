!<This file contains many lexical errors.
!<It tests mainly the correctness of the accepting functions
!<5 tabs
					
					
					


a1234567
!<legal, but too long (possible semantic error)
a1234567MORE
b1234567MORE#
!<lexical error: # out of context, allowed only in comments and strings
#OR$
!<lexical error: | allowed only in strings and comments
|
!<another lexical error: # out of context
Not#here
!<another lexical error: .  out of context
.
!<another lexical error: ~  illegal symbol
~
!<legal FPL (will be rounded to 2.0 when displayed)
1.999999999999999911111111111111111111111111111111111111111111111111111111111111111

!< big float number (error: out of range)
999999999999999999999999999999999999999999999999999999999999999999999999999999999.0

!<small float number (error: out of range)
0.00000000000000000000000000000000000000000000000000000000000000000000000000000000001

!< big decimal int number (error: out of range)
99999
!< big octal int number (error: out of range)
0177777
!< gigantic decimal int number (error: out of range)
123456789012345678901234567890
!< gigantic octal int number (error: out of range)
0123456701234567012345670