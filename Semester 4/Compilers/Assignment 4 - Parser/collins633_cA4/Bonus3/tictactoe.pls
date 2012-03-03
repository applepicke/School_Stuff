PLATYPUS {
	OUTPUT("Welcome to Pla-Tic-Tac-Toe");
	OUTPUT();
	OUTPUT();
	OUTPUT("Player 1, please enter your name: ");
	INPUT(player1#);
	OUTPUT("Player 2, please enter your name: ");
	INPUT(player2#);
	OUTPUT(player1#);
	OUTPUT(", you will be Xs");
	OUTPUT();
	OUTPUT(player2#);
	OUTPUT(", you will be Os");
	OUTPUT();
!<	col1	col2	col3
	a=0;	b=0;	c=0;!< row1
	d=0;	e=0;	f=0;!< row2
	g=0;	h=0;	i=0;!< row3
	score1 = 0;
	score2 = 0;
	replay = 0;
	turn = 1;
	games = 0;
	winner = 0;
	USING(replay# = "y",replay# == "y",replay# = replay#) REPEAT { 
		USING(moves=0,moves<9 .AND. winner < 1,moves=+moves) REPEAT {
			IF(a==0) THEN
				OUTPUT("a");
			ELSE {
				IF(a==1) THEN
					OUTPUT("X");
				ELSE {
					OUTPUT("O");
				}; 
			};
			OUTPUT("|");
			IF(b==0) THEN
				OUTPUT("b");
			ELSE {
				IF(b==1) THEN
					OUTPUT("X");
				ELSE {
					OUTPUT("O");
				}; 
			};
			OUTPUT("|");
			IF(c==0) THEN
				OUTPUT("c");
			ELSE {
				IF(c==1) THEN
					OUTPUT("X");
				ELSE {
					OUTPUT("O");
				}; 
			};
			OUTPUT();
			OUTPUT("-+-+-");
			OUTPUT();
			IF(d==0) THEN
				OUTPUT("d");
			ELSE {
				IF(d==1) THEN
					OUTPUT("X");
				ELSE {
					OUTPUT("O");
				}; 
			};
			OUTPUT("|");
			IF(e==0) THEN
				OUTPUT("e");
			ELSE {
				IF(e==1) THEN
					OUTPUT("X");
				ELSE {
					OUTPUT("O");
				}; 
			};
			OUTPUT("|");
			IF(f==0) THEN
				OUTPUT("f");
			ELSE {
				IF(f==1) THEN
					OUTPUT("X");
				ELSE {
					OUTPUT("O");
				}; 
			};
			OUTPUT();
			OUTPUT("-+-+-");
			OUTPUT();
			IF(g==0) THEN
				OUTPUT("g");
			ELSE {
				IF(g==1) THEN
					OUTPUT("X");
				ELSE {
					OUTPUT("O");
				}; 
			};
			OUTPUT("|");
			IF(h==0) THEN
				OUTPUT("h");
			ELSE {
				IF(h==1) THEN
					OUTPUT("X");
				ELSE {
					OUTPUT("O");
				}; 
			};
			OUTPUT("|");
			IF(i==0) THEN
				OUTPUT("i");
			ELSE {
				IF(i==1) THEN
					OUTPUT("X");
				ELSE {
					OUTPUT("O");
				}; 
			};
			OUTPUT();
			IF(turn==1) THEN
				OUTPUT(player1#);
			ELSE {
				OUTPUT(player2#);
			};
			OUTPUT(", it's your turn: ");
			USING(badmove=1,badmove==1,move#="") REPEAT {
				INPUT(move#);
				badmove=0;
				IF(move#=="a" .AND. a==0) THEN
					a=turn;
				ELSE {
					IF(move#=="b" .AND. b==0) THEN
						b=turn;
					ELSE {
						IF(move#=="c" .AND. c==0) THEN
							c=turn;
						ELSE {
							IF(move#=="d" .AND. d==0) THEN
								d=turn;
							ELSE {
								IF(move#=="e" .AND. e==0) THEN
									e=turn;
								ELSE {
									IF (move#=="f" .AND. f==0) THEN
										f=turn;
									ELSE {
										IF (move#=="g" .AND. g==0) THEN
											g=turn;
										ELSE {
											IF (move#=="h" .AND. h==0) THEN
												h=turn;
											ELSE {
												IF (move#=="i" .AND. i==0) THEN
													i=turn;
												ELSE {
													badmove=1;
												};
											};
										};
									};
								};
							};
						};
					};
				};
				IF (badmove==1) THEN
					OUTPUT("Invalid move, try again: ");
				ELSE {};
			};
			IF (a == b .AND. b == c .AND. a > 0) THEN
				winner=a;
			ELSE {
				IF (d == e .AND. e == f .AND. e > 0) THEN
					winner=d;
				ELSE {
					IF (g == h .AND. h == i .AND. g > 0) THEN
						winner=g;
					ELSE {
						IF (a == d .AND. d == g .AND. a > 0) THEN
							winner=a;
						ELSE {
							IF (b == e .AND. e == h .AND. b > 0) THEN
								winner=b;
							ELSE {
								IF (c == f .AND. f == i .AND. c > 0) THEN
									winner=c;
								ELSE {
									IF (a == e .AND. e == i .AND. a > 0) THEN
										winner=a;
									ELSE {
										IF (c == e .AND. e == g .AND. c > 0) THEN
											winner=c;
										ELSE {};
									};
								};
							};
						};
					};
				};
			};
			IF (turn==1) THEN
				turn=2;
			ELSE {
				turn=1;
			};
			OUTPUT();
		};
		games=+games;
		OUTPUT();
		IF(a==0) THEN
			OUTPUT("a");
		ELSE {
			IF(a==1) THEN
				OUTPUT("X");
			ELSE {
				OUTPUT("O");
			}; 
		};
		OUTPUT("|");
		IF(b==0) THEN
			OUTPUT("b");
		ELSE {
			IF(b==1) THEN
				OUTPUT("X");
			ELSE {
				OUTPUT("O");
			}; 
		};
		OUTPUT("|");
		IF(c==0) THEN
			OUTPUT("c");
		ELSE {
			IF(c==1) THEN
				OUTPUT("X");
			ELSE {
				OUTPUT("O");
			}; 
		};
		OUTPUT();
		OUTPUT("-+-+-");
		OUTPUT();
		IF(d==0) THEN
			OUTPUT("d");
		ELSE {
			IF(d==1) THEN
				OUTPUT("X");
			ELSE {
				OUTPUT("O");
			}; 
		};
		OUTPUT("|");
		IF(e==0) THEN
			OUTPUT("e");
		ELSE {
			IF(e==1) THEN
				OUTPUT("X");
			ELSE {
				OUTPUT("O");
			}; 
		};
		OUTPUT("|");
		IF(f==0) THEN
			OUTPUT("f");
		ELSE {
			IF(f==1) THEN
				OUTPUT("X");
			ELSE {
				OUTPUT("O");
			}; 
		};
		OUTPUT();
		OUTPUT("-+-+-");
		OUTPUT();
		IF(g==0) THEN
			OUTPUT("g");
		ELSE {
			IF(g==1) THEN
				OUTPUT("X");
			ELSE {
				OUTPUT("O");
			}; 
		};
		OUTPUT("|");
		IF(h==0) THEN
			OUTPUT("h");
		ELSE {
			IF(h==1) THEN
				OUTPUT("X");
			ELSE {
				OUTPUT("O");
			}; 
		};
		OUTPUT("|");
		IF(i==0) THEN
			OUTPUT("i");
		ELSE {
			IF(i==1) THEN
				OUTPUT("X");
			ELSE {
				OUTPUT("O");
			}; 
		};
		OUTPUT();
		IF(winner==0) THEN
			OUTPUT("It's a tie!");
		ELSE {
			IF(winner==1) THEN
				OUTPUT(player1#);
			ELSE {
				OUTPUT(player2#);
			};
			OUTPUT(" is the winner!");
		};
	!<	col1	col2	col3
		a=0;	b=0;	c=0;!< row1
		d=0;	e=0;	f=0;!< row2
		g=0;	h=0;	i=0;!< row3
		IF (winner == 1) THEN
			score1= score1 + 1;
		ELSE {
			IF (winner == 2) THEN
				score2= score2 + 1;
			ELSE {};
		};
		winner=0;
		OUTPUT();
		OUTPUT("Play again? (y/n): ");
		INPUT(replay#);	
	};
	OUTPUT("Results: ");
	OUTPUT();
	OUTPUT(player1#);
	OUTPUT(": ");
	OUTPUT(score1);
	OUTPUT();
	OUTPUT(player2#);
	OUTPUT(": ");
	OUTPUT(score2);
	OUTPUT();
	OUTPUT("Ties: ");
	ties = 0;
	ties = games-(score1+score2);
	OUTPUT(ties);
	OUTPUT();
	OUTPUT("Thanks for playing!");
	OUTPUT();
		
}