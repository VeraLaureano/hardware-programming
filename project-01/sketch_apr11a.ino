class Boton {
  private:
    int pin; // Numero de pin al que se conecto el boton
  public:
    Boton(int pin) {
      pin = pin;
    }

    // Metodo para saber si el boton esta precionado
    bool estaPrecionado() {
      return digitalRead(pin) == LOW;
    }

    int getPin() const {
      return pin;
    }
};

// Definir botones
Boton botonAlto(7);
Boton botonBajo(12);

// Definir estructura para cada led
class Led {
  private:
    int pin;  // Número del pin al que está conectado el LED
    int id;   // Identificador para saber que color representa
  public:
    Led(int pin, int id) {
      pin = pin;
      id = id;
    }

    // Metodo para encender el led
    void encender() {
      digitalWrite(pin, HIGH);
    }

    // Metodo para apagar el led
    void apagar() {
      digitalWrite(pin, LOW);
    }

    // Metodo para hacer titilar el led
    void titilar() {
      while (!botonAlto.estaPrecionado() && !botonBajo.estaPrecionado()) {
        encender();
        delay(200);
        apagar();
        delay(200);
      }
    }

    // Obtener numero de pin
    int getPin() const {
      return pin;
    }

    // Obtener id
    int getId() const {
      return id;
    }
};

// Definir leds (pin, valor: 1-verde, 2-amarillo, 3-rojo)
Led ledVerde(10, 1);
Led ledAmarillo(11, 2);
Led ledRojo(13, 3);

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
          ledVerde.encender();
        } else if (actual->led == 2) {
          ledAmarillo.encender();
        } else if (actual->led == 3) {
          ledRojo.encender();
        }

        delay(500);
        ledVerde.apagar();
        ledAmarillo.apagar();
        ledRojo.apagar();
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

int longitud = 3; // Definir longitud del patron de leds
LinkedList patronLeds; // Lista que guarda el patron original
LinkedList patronUsuario; // Lista que guarda el patron que ingreso el usuario


void setup() {
  // Inicializar los pines de los leds y los botones
  pinMode(ledVerde.getPin(), OUTPUT);
  pinMode(ledAmarillo.getPin(), OUTPUT);
  pinMode(ledRojo.getPin(), OUTPUT);
  pinMode(botonAlto.getPin(), INPUT_PULLUP);
  pinMode(botonAlto.getPin(), INPUT_PULLUP);
}

void loop() {
  // Gererar patron random;
  patronLeds.generarPatron(longitud);
  delay(100);

  // Mostrar el patrón original
  patronLeds.mostrarPatron();

  // Esperar a que el usuario ingrese la secuencia
  for (int i = 0; i < longitud; i++) {
    while (!botonAlto.estaPrecionado() && !botonBajo.estaPrecionado()) {
      // Esperar a que se presione uno de los botones
    }

    if (botonAlto.estaPrecionado() && !botonBajo.estaPrecionado()) {
      presionarBoton(ledVerde);
    } else if (botonAlto.estaPrecionado() && botonBajo.estaPrecionado()) {
      presionarBoton(ledAmarillo);
    } else if (!botonAlto.estaPrecionado() && botonBajo.estaPrecionado()) {
      presionarBoton(ledRojo);
    }

    // Esperar un breve tiempo antes de la próxima entrada
    delay(100);
  }

  // Comparar las secuencias
  if (patronLeds.sonIguales(patronUsuario)) {
    longitud++;
    ledVerde.titilar();
  } else {
    longitud = 3;
    ledRojo.titilar();
  }

  // Reiniciar la secuencia del usuario
  patronUsuario.clear();
}

// Funcion para manejar las pulsaciones
void presionarBoton(Led led) {
  patronUsuario.insertar(led.getId());
  led.encender();
  delay(500);
  led.apagar();
}