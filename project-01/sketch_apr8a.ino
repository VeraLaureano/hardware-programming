// Definir los pines para los leds y los botones
#define led1 10
#define led2 11
#define led3 13
#define sw1 12
#define sw2 7

// Definir longitud del patron
int longitud = 3;

// Definir los arreglos para almacenar las secuencias
int patronOriginal[] = {2, 3, 1}; // Cambia este patrón según desees
int secuenciaUsuario[longitud]; // Se almacenarán las entradas del usuario

void setup() {
  // Inicializar los pines de los leds y los botones
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
}

void loop() {
  // Mostrar el patrón original
  mostrarPatron(patronOriginal);

  // Esperar a que el usuario ingrese la secuencia
  for (int i = 0; i < longitud; i++) {
    while (digitalRead(sw1) == HIGH && digitalRead(sw2) == HIGH) {
      // Esperar a que se presione uno de los botones
    }

    if (digitalRead(sw1) == LOW && digitalRead(sw2) == HIGH) {
      secuenciaUsuario[i] = 1;
      digitalWrite(led1, HIGH);
      delay(500);
      digitalWrite(led1, LOW);
    } else if (digitalRead(sw1) == LOW && digitalRead(sw2) == LOW) {
      secenciaUsuario[i] = 2;
      digitalWrite(led2, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
    } 
    else if (digitalRead(sw2) == LOW && digitalRead(sw1) == HIGH) {
      secuenciaUsuario[i] = 3;
      digitalWrite(led3, HIGH);
      delay(500);
      digitalWrite(led3, LOW);
    }

    // Esperar un breve tiempo antes de la próxima entrada
    delay(100);
  }

  // Comparar las secuencias
  if (compararSecuencias(patronOriginal, secuenciaUsuario)) {
    titilarLed(led1);
  } else {
    titilarLed(led3);
  }

  // Reiniciar la secuencia del usuario
  reiniciarSecuencia(secuenciaUsuario);
}

// Función para mostrar el patrón original de los leds
void mostrarPatron(int patron[]) {
  for (int i = 0; i < longitud; i++) {
    if (patron[i] == 1) {
      digitalWrite(led1, HIGH);
    } else if (patron[i] == 2) {
      digitalWrite(led2, HIGH);
    } else if (patron[i] == 3) {
      digitalWrite(led3, HIGH);
    }

    delay(500);
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
    delay(200); // Breve pausa entre leds
  }
}

// Función para comparar las secuencias
bool compararSecuencias(int patron[], int secuencia[]) {
  for (int i = 0; i < longitud; i++) {
    if (patron[i] != secuencia[i]) {
      return false;
    }
  }
  return true;
}

// Función para hacer titilar un led
void titilarLed(int pinLed) {
  for (int i = 0; i < 3; i++) {
    digitalWrite(pinLed, HIGH);
    delay(200);
    digitalWrite(pinLed, LOW);
    delay(200);
  }
}

// Función para reiniciar la secuencia del usuario
void reiniciarSecuencia(int secuencia[]) {
  for (int i = 0; i < longitud; i++) {
    secuencia[i] = 0;
  }
}
