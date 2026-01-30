# Instructivo de uso — Germini Control Panel

Este documento describe el uso del panel de control **Germini Control Panel**, una aplicación de escritorio (Qt) que se comunica por puerto serial con un microcontrolador (por ejemplo, ESP32) para monitorear sensores DHT22 (temperatura y humedad), sensor de luz, y controlar actuadores (Peltier, ventiladores, servo) y un controlador PID de temperatura.

---

## Requisitos previos

- **Conexión serial**: El dispositivo (por ejemplo, ESP32) debe estar conectado por USB y con el firmware compatible cargado.
- **Puerto disponible**: En Windows suele aparecer como `COM3`, `COM4`, etc. En otros sistemas como `/dev/ttyUSB0` o `/dev/ttyACM0`.
- Las pestañas **Control**, **Control PID**, **Graph** y **Consola** solo se habilitan después de establecer la conexión serial.

---

## Barra de conexión serial

En la parte superior de la ventana siempre está la barra de conexión:

- **Puerto**: lista desplegable con los puertos seriales detectados.
- **Conectar**: abre el puerto seleccionado con la velocidad (baud rate) definida en la pestaña Configuración.
- **Desconectar**: cierra el puerto y deshabilita el resto de las pestañas (excepto Configuración).
- **Actualizar**: vuelve a detectar los puertos disponibles (útil si conectas/desconectas el USB).

Solo después de **Conectar** podrás usar las demás pestañas.

---

## 1. Pestaña Configuración

En esta pestaña se definen los parámetros generales antes de conectar. Cuando la aplicación está desconectada, el resto de pestañas aparece bloqueado; la configuración es el primer paso.

![Vista de la pestaña Configuración con las demás pestañas bloqueadas](INSTRUCCIONES/Configuracion%20-%20bloqueado.jpeg)

**Elementos:**

- **Velocidad Serial (Baud Rate)**: debe coincidir con la configurada en el firmware del microcontrolador. Valores típicos: 9600, 19200, 38400, 57600, **115200** (muy usado en ESP32).
- **Intervalo de actualización (ms)**: intervalo en milisegundos para la actualización de datos (entre 100 y 5000 ms; por defecto 1000 ms).

Después de elegir puerto y velocidad, usa **Conectar** en la barra superior. Al conectar, las pestañas **Control**, **Control PID**, **Graph** y **Consola** se habilitan.

---

## 2. Pestaña Control

Aquí se visualizan las lecturas de los sensores y se controlan los actuadores de forma manual.

![Vista de la pestaña Control en funcionamiento](INSTRUCCIONES/Control%20-%20funcionando.jpeg)

**Métricas de sensores:**

- Temperatura DHT22 #1 y #2, y **Temperatura promedio** (°C).
- Humedad DHT22 #1 y #2, y **Humedad promedio** (%).
- **Luz**: valor del sensor de luz.

**Control de motores:**

- **Iniciar todos los actuadores** / **Apagar todos los actuadores**: aplican o ponen a 0 todos los motores PWM según los valores actuales de los controles.

**Control individual:**

- **Peltier (Pin 4)**: slider y spinbox 0–255 (PWM).
- **Abanico caliente (Pin 16)** y **Abanico frío (Pin 17)**: igual, 0–255 PWM.
- **Servo compuerta (Pin 14)**: slider y spinbox de ángulo (p. ej. 20°–155°). El valor se envía al dispositivo al pulsar **Enviar ángulo**.

Los cambios de PWM en sliders/spinboxes se envían en tiempo real; el servo solo se actualiza al pulsar **Enviar ángulo**.

---

## 3. Pestaña Control PID

En esta pestaña se configura y activa/desactiva el controlador PID de temperatura en el dispositivo.

![Vista de la pestaña Control PID en funcionamiento](INSTRUCCIONES/pid%20-%20funcionando.jpeg)

**Parámetros:**

- **Setpoint de temperatura (°C)**: temperatura objetivo. Se envía al dispositivo con **Establecer**.
- **Kp (proporcional), Ki (integral), Kd (derivativo)**: ganancias del PID. Cada una se envía con su botón **Establecer**.

**Acciones:**

- **Activar PID** / **Desactivar PID**: encienden o apagan el control PID en el microcontrolador.

**Estado:**

- **Estado del PID**: indica si está Activado o Desactivado.
- **Salida PID**: muestra el valor de salida que reporta el firmware (si lo envía por serial).

---

## 4. Pestaña Graph

Muestra gráficas en tiempo real de las variables que elijas y permite exportar los datos a CSV.

**Variables a mostrar:**  
Casillas para elegir qué series se dibujan: Temp #1, Temp #2, Temp Promedio, Hum #1, Hum #2, Hum Promedio, Luz. Puedes combinar las que quieras.

**Ejemplos con las capturas:**

- Solo temperatura (por ejemplo Temp #1, #2 o promedio):

![Gráfica mostrando solo temperatura](INSTRUCCIONES/Grafica%20-%20solo%20temperatura.jpeg)

- Solo humedad (por ejemplo Hum #1, #2 o promedio):

![Gráfica mostrando solo humedad](INSTRUCCIONES/Grafica%20-%20solo%20humedad.jpeg)

- Todas las variables seleccionadas:

![Gráfica con todos los elementos](INSTRUCCIONES/Grafica%20-%20todos%20los%20elementos.jpeg)

**Exportar a CSV:**  
Guarda en un archivo CSV los datos registrados (tiempo y las variables que tengas seleccionadas en las casillas). Debes elegir al menos una variable para poder exportar.

---

## 5. Pestaña Consola

Muestra el tráfico serial entre la aplicación y el dispositivo:

- **[TX]**: comandos enviados por la aplicación (p. ej. `SET_MOTOR1:128`, `SET_SETPOINT:25`, `ENABLE_PID`).
- **[RX]**: líneas recibidas del dispositivo (datos, confirmaciones, mensajes de estado).
- **[INFO]**: mensajes internos de la aplicación (conexión, desconexión, acciones).
- **[ERROR]**: errores (por ejemplo, fallo al abrir puerto o comando no enviado).

Opciones:

- **Limpiar consola**: borra el contenido actual.
- **Auto-scroll**: si está activado, la consola se desplaza al final para mostrar siempre la última línea.

Útil para depurar comandos, comprobar formato de datos y ver si el firmware responde.

---

## Resumen del flujo de uso

1. Abrir la aplicación y, si hace falta, **Actualizar** puertos.
2. En **Configuración**, elegir **Velocidad serial** (y opcionalmente intervalo de actualización).
3. En la barra superior elegir **Puerto** y pulsar **Conectar**.
4. Usar **Control** para ver sensores y actuar sobre motores y servo.
5. Usar **Control PID** para fijar setpoint y Kp, Ki, Kd y activar/desactivar el PID.
6. Usar **Graph** para visualizar y exportar datos; **Consola** para revisar el tráfico serial.

Si algo no responde, comprueba en **Consola** que los comandos se envían [TX] y que el dispositivo contesta [RX], y que la velocidad serial coincida con la del firmware.
