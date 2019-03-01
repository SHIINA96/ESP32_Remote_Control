#include <WiFi.h>
#include <MySQL_Connection.h>
#include <MySQL_Cursor.h>

#define LED 2

byte mac_addr[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };

IPAddress server_addr(172,20,10,2);  // IP of the MySQL *server* here
char user[] = "bob";              // MySQL user login username
char password[] = "secret";        // MySQL user login password

// WiFi card example
char ssid[] = "Barney";    // your SSID
char pass[] = "SHIINA00";       // your SSID Password

// Sample query
//
// Notice the "%lu" - that's a placeholder for the parameter we will
// supply. See sprintf() documentation for more formatting specifier
// options
const char QUERY_POP[] = "select Actuator_State from Arduino.Actuator order by A_ID DESC LIMIT 1;";
char query[128];

WiFiClient client;            // Use this for WiFi instead of EthernetClient
MySQL_Connection conn((Client *)&client);

void setup() {
  
  pinMode(LED,OUTPUT);
  
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


void loop() {
  delay(1000);

  Serial.println("> Running SELECT with dynamically supplied parameter");

  // Initiate the query class instance
  MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
  // Supply the parameter for the query
  // Here we use the QUERY_POP as the format string and query as the
  // destination. This uses twice the memory so another option would be
  // to allocate one buffer for all formatted queries or allocate the
  // memory as needed (just make sure you allocate enough memory and
  // free it when you're done!).
  sprintf(query, QUERY_POP, 9000000);
  // Execute the query
  cur_mem->execute(query);
  // Fetch the columns and print them
  column_names *cols = cur_mem->get_columns();
  for (int f = 0; f < cols->num_fields; f++) {
    Serial.print(cols->fields[f]->name);
    if (f < cols->num_fields-1) {
      Serial.print(',');
    }
  }
  Serial.println();
  // Read the rows and print them
  row_values *row = NULL;
  do {
    row = cur_mem->get_next_row();
    if (row != NULL) {
      for (int f = 0; f < cols->num_fields; f++) {
        Serial.print(row->values[f]);
//        Serial.println( type(row->values[f]) );
        if (row->values[0][0]=='O' && row->values[0][1]=='N')
          {
            digitalWrite(LED,HIGH);
          }
         if (row->values[0][0]=='O' && row->values[0][1]=='F' && row->values[0][2]=='F')
         {
           digitalWrite(LED,LOW);
         }
        if (f < cols->num_fields-1) {
          Serial.print(',');
        }
      }
      Serial.println();
    }
  } while (row != NULL);
  // Deleting the cursor also frees up memory used
  delete cur_mem;
}
