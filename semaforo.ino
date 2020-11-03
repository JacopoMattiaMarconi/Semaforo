#define redTime 20 //dichiarazione globale tempo semaforo rosso 
#define greenTime 20 //dichiarazione globale tempo semaforo verde
#define yellowgreenTime 5 //dichiarazione globale tempo semaforo gialloverde
#define waitTime 1000 //tempo di attesa per delay( );
int red = 5;
int yellow = 4;
int green = 3;
int button = 2;

volatile bool emergenza = false; //inizializzazione variabile booleana emergenza

void setup() {
  Serial.begin(9600); //sincronizzare il monitor seriale
  pinMode(red, OUTPUT); //dichiarazione pin
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(button, INPUT);
  attachInterrupt(digitalPinToInterrupt(button), ISR_button, RISING); //dichiarazione digitale di interrupt tramite button
}

void loop() {
  digitalWrite(red, LOW); //iniziare con rosso spento
  digitalWrite(yellow, LOW);  //iniziare con giallo spento
  digitalWrite(green, LOW); //iniziare con verde spento
  if (!emergenza) { //se il semaforo non è in stato di emergenza...
    digitalWrite(green, HIGH); //semaforo vedre acceso
    for (int i = 0; i < greenTime; i++) { //ciclo for per 20 volte. -->20 volte con tempo di attesa 1
      if (emergenza) {
        return 0;
      }
      delay(waitTime); //tempo di attesa
    }

    digitalWrite(yellow, HIGH); //semaforo giallo acceso

    for (int i = 0; i < yellowgreenTime; i++) { //ciclo for per 5 volte.
      if (emergenza) {
        return 0;
      }
      delay(waitTime);
    }
    digitalWrite(yellow, LOW);   //giallo spento
    digitalWrite(green, LOW); //verde spento
    
    digitalWrite(red, HIGH);  //rosso spento
    for (int i = 0; i < redTime; i++) { //ciclo for per 20 volte
      if (emergenza) {
        return 0;
      }
      delay(waitTime);
    }
  }


  else { //se il semaforo è in stato di emergenza... giallo lampeggiante
    digitalWrite(yellow, HIGH);
    delay (waitTime);
    digitalWrite(yellow, LOW);
    delay(waitTime);
  }
}

void ISR_button() { //gestione monitor seriale
  emergenza = !emergenza;
  if (emergenza) {
    Serial.println("Emergenza"); //scrive a monitor emergenza se il semaforo è in stato di emergenza
  }
  else {
    Serial.println("Normale operazione"); //scrive a monitor normale operazione se il semaforo non è in stato di emergenza
  }
}
