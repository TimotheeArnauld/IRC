#!/usr/bin/python
import psycopg2
import sys
import socket
import getpass
import md5

def inscription_connection(name, password):
	conn = psycopg2.connect("dbname=docker user=docker host=localhost password=docker")
	cur = conn.cursor()
	try:
		cur.execute("SELECT * from users where user_name='"+name+"'")
		if cur.rowcount == 0:
			#inscription
			password_hash = md5.new(password).digest()
			sql = "INSERT INTO users(user_name, user_password) VALUES(%s, %s) RETURNING user_id;"
			cur.execute(sql, (name, password_hash))
			conn.commit()
			return "true"
		else:
			#Connection	
			hash_DB = cur.fetchone()[2]
			i = 0
			while i < 3:	
				password_hash = md5.new(password).digest()
				if password_hash == hash_DB:
					i = 3
					return "true"
				else:
					tries = 3 - i - 1
				i = i + 1
	except (Exception, psycopg2.DatabaseError) as error:
		return "false"
	finally:
		if conn is not None:
			cur.close()
			conn.close()

