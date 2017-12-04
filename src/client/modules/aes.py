from Crypto.Cipher import AES
import base64

def encrypt(message):
	obj = AES.new("This is a key123", AES.MODE_CBC, "This is an IV456")
	ciphertext = obj.encrypt(message.ljust(256, '\0'))
	return str(base64.b64encode(ciphertext))

def decrypt(message):
	obj = AES.new("This is a key123", AES.MODE_CBC, "This is an IV456")
	return obj.decrypt(base64.b64decode(message))
