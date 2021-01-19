#import binascii
import sys
import argparse
#Read line of text


#convert with key, vignere cipher
def Vignere(Key, Plaintext):

	Key=Key.upper()
	#Plaintext = Plaintext.upper()
	_key=[]
	counter = 0
	Size = 0
	chipher=""
	for j in Key:
		d = ord(j)-65
		_key.append(d)
		Size+=1
	for word in Plaintext:
		word = word.upper()
		for char in word:
			p = ord(char)
			p+=_key[counter%Size]
			if(p > 90):
				p-=26
			
			counter+=1
			chipher =  chr(p)+chipher
	return chipher

def VignereDecrypt(Key, Cipher):
	Key=Key.upper()
	for c in Cipher:
		c = c.upper()
	#Cipher = Cipher.upper()
	_key=[]
	counter = 0
	Size = 0
	Plaintext=""
	InvertedCipher=""
	for j in Key:
		d = ord(j)-65
		_key.append(d)
		Size+=1
	for word in Cipher:
		word = word.upper()
		for a in word:
			InvertedCipher =  a+InvertedCipher
		for i in InvertedCipher:
			
			p = ord(i)
			p-=_key[counter%Size]
			if(p < 65):
				p+=26
			counter+=1
			Plaintext =  Plaintext+chr(p)
	return Plaintext
def DecryptFile(Filename):
	plaintext = file.readline(Filename)
	
def main():
	DefaultKey = "ghfdjkweinvekjdfshiofqnqsckliqonskkpxsjvnsuaimxbyudgfqppzlmx"
	
	parser = argparse.ArgumentParser(description='Crypt, decrypt messages.')
	
	parser.add_argument('-d','--decrypt',  type=str, nargs='+',
						help='Decrypt A Message(Spaces will not be included):')
						
	parser.add_argument('-e','--encrypt',  type=str, nargs='+',
						help='Encrypt A Message(Spaces will not be included):')
						
	parser.add_argument('-k','--key',  type=str, nargs='+',
						help='key to use for encryption/decryption of message (if not specified, default will be used)')

	args = parser.parse_args()
	if(args.key):
		DefaultKey=""
		for argument in args.key:
			DefaultKey=DefaultKey+argument
	if (args.encrypt):
		chipher = Vignere(DefaultKey,args.encrypt)
		print (chipher)
	if (args.decrypt):
		Plaintext = VignereDecrypt(DefaultKey,args.decrypt)
		print(Plaintext)
		

main()

