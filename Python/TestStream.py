import pyrebase

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

def stream_handler(message):
    path = message['path']
    data = message['data']
    event = message['event']
    if event == 'put':
         if len(path) == 1:
             print("Data update: " + str(data))
         else:
             #print("Tap update: " + str(path) + " state to: " + str(data))
             _path = path.split('/')
             #print("Path items: " + str(len(_path)))
             modnum = db.child("/modules/" + _path[2] + "/module").shallow().get()
             tapnum = db.child("/modules/" + _path[2] + "/taps/" + _path[4] + "/tap").shallow().get()
             print("Module: " + str(modnum.val()))
             print("Tap: " + str(tapnum.val()))
             print("State: " + str(data))

my_stream = db.child("").stream(stream_handler)
