import time
import board
import busio as io
import adafruit_mlx90614
import adafruit_ahtx0
import pyrebase


#i2c = io.I2C(board.SCL, board.SDA, frequency=100000)
i2c= board.I2C()
mlx = adafruit_mlx90614.MLX90614(i2c)
aht = adafruit_ahtx0.AHTx0(i2c)

config = {
  "apiKey": "AIzaSyABYrAOaCWotXFxrXMfFFdyeuShi6vzeyQ",
  "authDomain": "184374708100.firebaseapp.com",
  "databaseURL": "https://iotnanuvem-default-rtdb.firebaseio.com/",
  "storageBucket": "184374708100.appspot.com"
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