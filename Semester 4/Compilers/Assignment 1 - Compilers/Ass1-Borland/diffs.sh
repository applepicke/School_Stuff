#!/bin/bash
echo "--------------------fixed-----------------------"
diff fixed.out ../outputs/ass1fi.out
echo "--------------------additive-----------------------"
diff additive.out ../outputs/ass1ai.out
echo "--------------------multi-----------------------"
diff multi.out ../outputs/ass1mi.out
echo "--------------------error-----------------------"
diff error.out ../outputs/ass1e.out
echo "--------------------bigfai-----------------------"
diff bigfai.out ../outputs/bigfai.out
echo "--------------------bigfai128-----------------------"
diff bigfai128.out ../outputs/bigfai128.out
echo "--------------------bigfamax-----------------------"
diff bigfamax.out ../outputs/bigfamax.out
echo "---------------------bigffi0----------------------"
diff bigffi0.out ../outputs/bigffi0.out
echo "---------------------bigffi128----------------------"
diff bigffi128.out ../outputs/bigffi128.out
echo "-------------------bigfmi------------------------"
diff bigfmi.out ../outputs/bigfmi.out
echo "------------------bigfmi9-------------------------"
diff bigfmi9.out ../outputs/bigfmi9.out
echo "------------------bigfmmax-------------------------"
diff bigfmmax.out ../outputs/bigfmmax.out
echo "-----------------bigfai0--------------------------"
diff bigfai0.out ../outputs/bigfai0.out
echo "------------------bigfmi0-------------------------"
diff bigfmi0.out ../outputs/bigfmi0.out
echo "-----------------bigfac0--------------------------"
diff bigfac0.out ../outputs/bigfac0.out
echo "-------------------bigfmc0------------------------"
diff bigfmc0.out ../outputs/bigfmc0.out
