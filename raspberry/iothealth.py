import time
import board
import busio as io
import adafruit_mlx90614
import adafruit_ahtx0
import pyrebase

i2c= board.I2C()
mlx = adafruit_mlx90614.MLX90614(i2c)
aht = adafruit_ahtx0.AHTx0(i2c)

config = {
  "apiKey": "----- chave da API do Firebase -----",
  "authDomain": "--- código do projeto ---.firebaseapp.com",
  "databaseURL": "https://----- id do projeto do realtime database ----.firebaseio.com/",
  "storageBucket": "--- código do projeto ---.appspot.com"
}

firebase = pyrebase.initialize_app(config)
db = firebase.database()

print("Enviando dados a partir da Raspberry Pi")
print()

while True:


  tempAmbMLX = float(mlx.ambient_temperature)
  tempCorpCelsius = float(mlx.object_temperature)
  tempAmbienteAHT = float(aht.temperature)
  umidadeAmbiente = float(aht.relative_humidity)

  print("\nTemperatura Ambiente: {:.2f} °C".format(tempAmbMLX))
  print("\nTemperatura Corporal: {:.2f} °C".format(tempCorpCelsius))
  print("\nTemperatura AHT: {:.2f} °C".format(tempAmbienteAHT))
  print("\nUmidade do Ambiente: {:.2f}%".format(umidadeAmbiente))
  print()

  db.child("temperaturaAmbMLX").set(tempAmbMLX)
  db.child("temperaturaCorp").set(tempCorpCelsius)
  db.child("umidade").set(umidadeAmbiente)
  db.child("temperaturaAmb").set(tempAmbienteAHT)


  time.sleep(2)
