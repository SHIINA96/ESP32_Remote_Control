#include <WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>
#include <Servo.h>

#define LED 2
#define RELAY 25

//Servo Configurations
Servo servo1;
static const int servoPin = 12;
int gate_state = 0;
int input_state = 0;

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(192,168,1,79);  // IP of the MySQL *server* here
char user[] = "bob";              // MySQL user login username
char password[] = "secret";        // MySQL user login password

// WiFi card example
char ssid[] = "TPLINK-EX2G";    // your SSID
char pass[] = "Qwerty123456";       // your SSID Password

// Sample query
//
// Notice the "%lu" - that's a placeholder for the parameter we will
// supply. See sprintf() documentation for more formatting specifier
// options
char QUERY_LED[] = "select Actuator_State from Arduino.Actuator where Actuator_Name = 'LED' order by A_ID DESC LIMIT 1;";
char query_LED[128];
char QUERY_RELAY[] = "select Actuator_State from Arduino.Actuator where Actuator_Name = 'RELAY' order by A_ID DESC LIMIT 1;";
char query_RELAY[128];
char QUERY_SERVO[] = "select Actuator_State from Arduino.Actuator where Actuator_Name = 'SERVO' order by A_ID DESC LIMIT 1;";
char query_SERVO[128];

WiFiClient client;            // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client *)&client);

void setup() {
  
  pinMode(LED,OUTPUT);
  pinMode(RELAY,OUTPUT);
  servo1.attach(servoPin);
  
  Serial.begin(115200);
         WiFi.begin(ssid,pass);    
        while (WiFi.status() != WL_CONNECTED)
            {
                delay(500);
                Serial.print(".");
            }
        
        Serial.println("");
        Serial.println("WiFi connected.");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
        Serial.println();
  
  // End WiFi section

    Serial.println("Connecting...");
    if (conn.connect(server_addr, 3306, user, password)) {
      delay(1000);
  }
  else
    Serial.println("Connection failed.");
}


void loop() 
    {
        delay(1000);
        Remote_Control(query_LED, QUERY_LED, LED);
        //conn.close();
        delay(1000);
        Remote_Control(query_RELAY, QUERY_RELAY, RELAY);
        delay(1000);
        Remote_Control_SERVO(query_SERVO, QUERY_SERVO);
        
        
//        Serial.println("> Running SELECT with dynamically supplied parameter");
//        
//        // Initiate the query class instance
//        MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
//        sprintf(query_LED, QUERY_LED, 9000000);
//        
//        // Execute the query
//        cur_mem->execute(query_LED);
//        
//        // Fetch the columns and print them
//        column_names *cols = cur_mem->get_columns();
//        for (int f = 0; f < cols->num_fields; f++) 
//            {
//                Serial.print(cols->fields[f]->name);
//                if (f < cols->num_fields-1) 
//                    {
//                        Serial.print(',');
//                    }
//            }
//        Serial.println();
//        // Read the rows and print them
//        row_values *row = NULL;
//            do 
//                {
//                    row = cur_mem->get_next_row();
//                    if (row != NULL) 
//                        {
//                            for (int f = 0; f < cols->num_fields; f++) 
//                                {
//                                    Serial.print(row->values[f]);
//                                    // Serial.println( type(row->values[f]) );
//                                    if (row->values[0][0]=='O' && row->values[0][1]=='N')
//                                        {
//                                            digitalWrite(LED,HIGH);
//                                        }
//                                    if (row->values[0][0]=='O' && row->values[0][1]=='F' && row->values[0][2]=='F')
//                                        {
//                                            digitalWrite(LED,LOW);
//                                        }
//                                    if (f < cols->num_fields-1) 
//                                        {
//                                            Serial.print(',');
//                                        }
//                                }
//                            Serial.println();
//                        }
//                } 
//            while (row != NULL);
//            // Deleting the cursor also frees up memory used
//            delete cur_mem;
    }
