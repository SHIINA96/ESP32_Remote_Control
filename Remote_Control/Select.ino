int Remote_Control (char* query, char* QUERY, int ACTUATOR)
{
        Serial.println("> Running SELECT with dynamically supplied parameter");
        
        // Initiate the query class instance
        MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
        sprintf(query, QUERY, 9000000);
        
        // Execute the query
        cur_mem->execute(query);
        
        // Fetch the columns and print them
        column_names *cols = cur_mem->get_columns();
        for (int f = 0; f < cols->num_fields; f++) 
            {
                Serial.print(cols->fields[f]->name);
                if (f < cols->num_fields-1) 
                    {
                        Serial.print(',');
                    }
            }
        Serial.println();
        // Read the rows and print them
        row_values *row = NULL;
            do 
                {
                    row = cur_mem->get_next_row();
                    if (row != NULL) 
                        {
                            for (int f = 0; f < cols->num_fields; f++) 
                                {
                                    Serial.print(ACTUATOR);
                                    Serial.print(row->values[f]);
                                    // Serial.println( type(row->values[f]) );
                                    if (row->values[0][0]=='O' && row->values[0][1]=='N')
                                        {
                                            digitalWrite(ACTUATOR,HIGH);
                                        }
                                    if (row->values[0][0]=='O' && row->values[0][1]=='F' && row->values[0][2]=='F')
                                        {
                                            digitalWrite(ACTUATOR,LOW);
                                        }
                                    if (f < cols->num_fields-1) 
                                        {
                                            Serial.print(',');
                                        }
                                }
                            Serial.println();
                        }
                } 
            while (row != NULL);
            // Deleting the cursor also frees up memory used
            delete cur_mem;
}

int Remote_Control_SERVO (char* query, char* QUERY)
{
        Serial.println("> Running SELECT with dynamically supplied parameter");
        
        // Initiate the query class instance
        MySQL_Cursor *cur_mem = new MySQL_Cursor(&conn);
        sprintf(query, QUERY, 9000000);
        
        // Execute the query
        cur_mem->execute(query);
        
        // Fetch the columns and print them
        column_names *cols = cur_mem->get_columns();
        for (int f = 0; f < cols->num_fields; f++) 
            {
                Serial.print(cols->fields[f]->name);
                if (f < cols->num_fields-1) 
                    {
                        Serial.print(',');
                    }
            }
        Serial.println();
        // Read the rows and print them
        row_values *row = NULL;
            do 
                {
                    row = cur_mem->get_next_row();
                    if (row != NULL) 
                        {
                            for (int f = 0; f < cols->num_fields; f++) 
                                {
                                    Serial.print("SERVO ");
                                    Serial.print(row->values[f]);
                                    // Serial.println( type(row->values[f]) );
                                    if (row->values[0][0]=='O' && row->values[0][1]=='N')
                                        {
                                            for(int posDegrees = 0; posDegrees <= 180; posDegrees++) 
                                                {
                                                    servo1.write(posDegrees);
                                                    delay(20);
                                                }
                                        }
                                    if (row->values[0][0]=='O' && row->values[0][1]=='F' && row->values[0][2]=='F')
                                        {
                                            for(int posDegrees = 180; posDegrees >= 0; posDegrees--)
                                                {
                                                    servo1.write(posDegrees);
                                                    delay(20);
                                                } 
                                        }
                                    if (f < cols->num_fields-1) 
                                        {
                                            Serial.print(',');
                                        }
                                }
                            Serial.println();
                        }
                } 
            while (row != NULL);
            // Deleting the cursor also frees up memory used
            delete cur_mem;
}
