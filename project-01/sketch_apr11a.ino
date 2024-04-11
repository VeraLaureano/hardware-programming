// Definir los pines para los leds y los botones
#define led1 10
#define led2 11
#define led3 13
#define sw1 12
#define sw2 7

int longitud = 3; // Definir longitud del patron de leds

// Definir estructura para lista de leds
struct Node {
  int led;
  struct Node* sig;
};

class LinkedList {
private:
    Node* head; // Puntero al primer nodo (cabeza)

public:
    // Constructor: inicializa la lista vacía
    LinkedList() {
      head = nullptr;
    }

    // Método para agregar un elemento al principio de la lista
    void insertar(int led) {
      Node* newNode = new Node;
      newNode->led = led;
      newNode->sig = head;
      head = newNode;
    }

    // Método para limpiar la lista (eliminar todos los nodos)
    void clear() {
      while (head != nullptr) {
        Node* temp = head;
        head = head->sig;
        delete temp;
      }
    }

    // Metodo para generar el patron de los leds
    void generarPatron(int longitud) {
      for (int i = 0; longitud > i; i++) {
        insertar(random(1,3));
      }
    }

    // Metodo para mostrar el patrón de los leds
    void mostrarPatron() {
      Node* actual = head;

      while (actual != nullptr) {
        if (actual->led == 1) {
          digitalWrite(led1, HIGH);
        } else if (actual->led == 2) {
          digitalWrite(led2, HIGH);
        } else if (actual->led == 3) {
          digitalWrite(led3, HIGH);
        }

        delay(500);
        digitalWrite(led1, LOW);
        digitalWrite(led2, LOW);
        digitalWrite(led3, LOW);
        delay(200); // Breve pausa entre leds
        actual = actual->sig; // Pasar al siguiente led
      }
    }

    // Metodo para comparar secuencias
    bool sonIguales(const LinkedList& otraLista) const {
      Node* nodoActual1 = head;
      Node* nodoActual2 = otraLista.head;

      while (nodoActual1 != nullptr && nodoActual2 != nullptr) {
        if (nodoActual1->led != nodoActual2->led) {
          return false; // Los valores no coinciden
        }
        nodoActual1 = nodoActual1->sig;
        nodoActual2 = nodoActual2->sig;
      }

      // Ambas listas deben haber llegado al final al mismo tiempo
      return nodoActual1 == nullptr && nodoActual2 == nullptr;
    }
};

LinkedList patronLeds;
LinkedList patronUsuario;

void setup() {
  // Inicializar los pines de los leds y los botones
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP);
}

void loop() {
  // Gererar patron random;
  patronLeds.generarPatron(longitud);
  delay(100);

  // Mostrar el patrón original
  patronLeds.mostrarPatron();

  // Esperar a que el usuario ingrese la secuencia
  for (int i = 0; i < longitud; i++) {
    while (digitalRead(sw1) == HIGH && digitalRead(sw2) == HIGH) {
      // Esperar a que se presione uno de los botones
    }

    if (digitalRead(sw1) == LOW && digitalRead(sw2) == HIGH) {
      presionarBoton(led1, 1);
    } else if (digitalRead(sw1) == LOW && digitalRead(sw2) == LOW) {
      presionarBoton(led2, 2);
    } 
    else if (digitalRead(sw2) == LOW && digitalRead(sw1) == HIGH) {
      presionarBoton(led3, 3);
    }

    // Esperar un breve tiempo antes de la próxima entrada
    delay(100);
  }

  // Comparar las secuencias
  if (patronLeds.sonIguales(patronUsuario)) {
    longitud++;
    titilarLed(led1);
  } else {
    longitud = 3;
    titilarLed(led3);
  }

  // Reiniciar la secuencia del usuario
  patronUsuario.clear();
}

// Funcion para manejar las pulsaciones
void presionarBoton(int pinLed, int valorLed) {
  patronUsuario.insertar(valorLed);
  digitalWrite(pinLed, HIGH);
  delay(500);
  digitalWrite(pinLed, LOW);
}

// Función para hacer titilar un led
void titilarLed(int pinLed) {
  while (digitalRead(sw1) == HIGH && digitalRead(sw2) == HIGH) {
    digitalWrite(pinLed, HIGH);
    delay(200);
    digitalWrite(pinLed, LOW);
    delay(200);
  }
}