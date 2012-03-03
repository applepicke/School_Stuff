ass1 ass1.pls fixed 200 15 > fixed.out
ass1 ass1.pls additive 200 15 > additive.out
ass1 ass1.pls multiplicative 200 15 > multi.out
ass1 ass1e.pls fixed 200 15 > error.out
ass1 bigf.pls additive 200 15 > bigfai.out
ass1 bigf.pls additive 200 128 > bigfai128.out
ass1 bigf.pls additive INT_MAX 15 > bigfamax.out
ass1 bigf.pls fixed 200 0 > bigffi0.out
ass1 bigf.pls fixed 200 128 > bigffi128.out
ass1 bigf.pls multiplicative 200 15 > bigfmi.out
ass1 bigf.pls multiplicative INT_MAX-10 9 > bigfmi9.out
ass1 bigf.pls multiplicative INT_MAX 15 > bigfmmax.out
ass1 bigf.pls additive 200 0 > bigfai0.out
ass1 bigf.pls multiplicative 200 0 > bigfmi0.out
ass1 bigf.pls additive 0 15 > bigfac0.out
ass1 bigf.pls multiplicative 0 15 > bigfmc0.out
ass1 bigf.pls multiplicative 200 128 > bigfmi128.out
ass1 bigf.pls fixed 0 15 > bigffc0.out


:diff fixed.out ../outputs/ass1fi.out
:diff additive.out ../outputs/ass1ai.out
:diff multi.out ../outputs/ass1mi.out
:diff error.out ../outputs/ass1e.out
:diff bigfai.out ../outputs/bigfai.out
:diff bigfai128.out ../outputs/bigfai128.out
:diff bigfamax.out ../outputs/bigfamax.out
:diff bigffi0.out ../outputs/bigffi0.out
:diff bigfi128.out ../outputs/bigfi128.out
:diff bigfmi.out ../outputs/bigfmi.out
:diff bigfmi9.out ../outputs/bigfmi9.out
:diff bigfmmax.out ../outputs/bigfmmax.out
:diff bigfai0.out ../outputs/bigfai0.out
:diff bigfmi0.out ../outputs/bigfmi0.out
:diff bigfac0.out ../outputs/bigfac0.out
:diff bigfmc0.out ../outputs/bigfmc0.out
:diff bigfmi128.out ../outputs/bigfmi128.out
:diff bigffc0.out ../outputs/bigffc0.out

pause