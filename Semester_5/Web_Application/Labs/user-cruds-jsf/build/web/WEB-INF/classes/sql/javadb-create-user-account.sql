DROP TABLE user_account;

CREATE TABLE user_account (
	  userID      INTEGER     NOT NULL GENERATED ALWAYS AS IDENTITY (START WITH 1, INCREMENT BY 1)
	, username    VARCHAR(8)  NOT NULL
	, password    VARCHAR(20) NOT NULL
	, description VARCHAR(25)

	, CONSTRAINT pk_userID   PRIMARY KEY ( userID )
	, CONSTRAINT uq_username UNIQUE      ( username  )
);