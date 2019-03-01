Use Arduino;
CREATE table Actuator (
A_ID int  auto_increment  NOT NULL  PRIMARY KEY,
Actuator_Name varchar(255),
Actuator_State varchar(255),
Actuator_Time datetime null default current_timestamp
)