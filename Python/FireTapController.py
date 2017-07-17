import pyrebase
import smbus
import time
import struct

config = {
  "apiKey": "AIdiSyDElQzRPSXk1P3j1t5xjgkBNLP2KvziQzw",
  "authDomain": "dbname.firebaseapp.com",
  "databaseURL": "https://dbname.firebaseio.com",
  "storageBucket": "dbname.appspot.com",
  "serviceAccount": "serviceAccountCredentials.json"
}

firebase = pyrebase.initialize_app(config)

auth = firebase.auth()
user = auth.sign_in_with_email_and_password('myemail@gmail.com', 'MySuperSecurePassword123')

db = firebase.database()

modules = db.child("").get()
smbus = smbus.SMBus(1) # smbus / twi / i2c
address = 0x10  #default address
data = [0x31, 0x3A, 0x31, 0x3B] #default twi data message

def updateTap(module, tap, state):
    ascii_0 = 48
    data[0] = ascii_0 + tap
    data[2] = ascii_0 + state
    modaddr = module
    try:
        smbus.write_i2c_block_data(modaddr, 0, data)
    except OSError:
        print("Module " + str(modaddr) + " not found!")

def stream_handler(message):
    path = message['path']
    data = message['data']
    event = message['event']
    if event == 'put':
         if len(path) == 1:
             print("Data update: " + str(data))
         else:
             _path = path.split('/')
             modnum = db.child("/modules/" + _path[2] + "/module").shallow().get()
             tapnum = db.child("/modules/" + _path[2] + "/taps/" + _path[4] + "/tap").shallow().get()
             print("Module: " + str(modnum.val()))
             print("Tap: " + str(tapnum.val()))
             print("State: " + str(data))
             updateTap(int(modnum.val()), int(str(tapnum.val())), int(str(data)))

firetapstream = db.child("").stream(stream_handler)
