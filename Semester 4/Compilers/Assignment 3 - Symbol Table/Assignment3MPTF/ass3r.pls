!< This program calculates the sum and the average
!< of 5 numbers
PLATYPUS {
day5 = 5.;
day4 = 4.;
day3 = 3.;
day2 = 2.;
day1 = 1.;
sum = day1 + day2 + day3 + day4 + day5; 
avg = 0.0;
temp = sum;
USING(temp=sum,temp > 5.0 .OR. temp == 5.0,temp=temp)REPEAT {
  temp = temp - 5.0;
  avg = avg + 1.0;
};
res# = "Results:";
OUTPUT(res#);
OUTPUT(sum);
OUTPUT(avg);
}

