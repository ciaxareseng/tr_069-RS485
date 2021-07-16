if (digitalRead(pinSensorMC38A) == HIGH){ //SE A LEITURA DO PINO FOR IGUAL A HIGH, FAZ
        
        aux = 1;
        Serial.println("Porta Aberta.");
        Serial.print("aux: ");
        Serial.println(aux);
        delay(100);
  }
  else if(digitalRead(pinSensorMC38A) == LOW){ //SENÃO, FAZ
      
      aux = 0;
      Serial.println("Porta Fechada. ");
      Serial.print("aux: ");
      Serial.println(aux);
      delay(100);
  }
  delay(1000);
