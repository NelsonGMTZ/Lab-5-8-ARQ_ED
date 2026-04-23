import serial, json, time

arduino = serial.Serial('COM14', 115200, timeout=1)  # cambia puerto si es necesario
time.sleep(2)

def enviar(cmd):
    arduino.write((cmd + '\n').encode())

    while True:
        linea = arduino.readline().decode().strip()
        if not linea:
            continue

        print("RECIBIDO:", linea)

        try:
            data = json.loads(linea)
            if 'data' in data:
                return data
        except:
            continue

# Ciclo de monitoreo
for _ in range(5):
    resp = enviar('ALL')
    if resp:
        d = resp['data']
        print(f"Temp: {d['temp']}°C Hum: {d['hum']}% Luz: {d['luz']}")
    time.sleep(3)

# Control de LED
enviar('LED:ON')
time.sleep(1)
enviar('LED:OFF')
