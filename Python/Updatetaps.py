import pyrebase
import simplejson as json

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
jsonmodule = json.JSONEncoder().encode(modules.val())

json = json.loads(jsonmodule)

#print(json)  # the entire json from the Firebase db
for module in json["modules"]:
    print("Module: " + str(module["module"]))
    for tap in module["taps"]:
         print("Tap: " + str(tap["tap"]) + " state: " + str(tap["state"]))
