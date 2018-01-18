#!/usr/bin/python
import psycopg2
import sys
import socket
import getpass
import md5

host = "localhost"
port = 1330
server_address = ('localhost', port)

name = raw_input("Connection on IRC server, please enter your name: ")
conn = psycopg2.connect("dbname=docker user=docker host=localhost password=docker")
cur = conn.cursor()

try:
	cur.execute("SELECT * from users where user_name='"+name+"'")
	if cur.rowcount == 0:
		#inscription + connection
		password = getpass.getpass("Mmm You're a stranger, please give me a password to subscribe: ")
		password_hash = md5.new(password).digest()
		sql = "INSERT INTO users(user_name, user_password) VALUES(%s, %s) RETURNING user_id;"
		cur.execute(sql, (name, password_hash))
		conn.commit()
		conn.close()
		socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
		socket.connect(server_address)
		print "You're connected !!  on {}".format(port)
		#print "Close"
		#socket.close()
	else:
		#Connection	
		hash_DB = cur.fetchone()[2]
		i = 0
		while i < 3:	
			password = getpass.getpass("I know you, please put your password to authenticate: ")
			password_hash = md5.new(password).digest()
			if password_hash == hash_DB:
				i = 3
				socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
				socket.connect(server_address)
				print "You're connected !!  on {}".format(port)
				#print "Close"
				#socket.close()
			else:
				tries = 3 - i - 1
				print("incorrect :((((  "+str(tries)+" times left...")
			i = i + 1
except (Exception, psycopg2.DatabaseError) as error:
        print(error)
finally:
    if conn is not None:
    	cur.close()
        conn.close()

