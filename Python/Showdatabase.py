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

modules = db.child("modules").get()
print(modules.val())
