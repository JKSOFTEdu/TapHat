from firebase import firebase
firebase = firebase.FirebaseApplication('https://mydatabasename.firebaseio.com/', authentication=None)
result = firebase.get('/taps', None, {'print': 'pretty'})
print result

authentication = firebase.Authentication('', 'myemail@gmail.com', extra={'id': 123})
firebase.authentication = authentication
print authentication.extra

user = authentication.get_user()
print user.firebase_auth_token
