#!/usr/bin/python
import psycopg2
import sys
import socket

#send file, return true after the transfer, need a socket in parameters
def send_file_in_room(room_name, socket, user_name, filename):
	conn = psycopg2.connect("dbname=docker user=docker host=localhost password=docker")
	cur = conn.cursor()
	try:
		sql = "SELECT * FROM rooms WHERE room_name=%s;"
		cur.execute(sql, (room_name,))
		if cur.rowcount > 0:
			f = open(filename, 'rb')
			l = f.read(1024)
			while (l):
				socket.send(l)
				l = f.read(1024)
			f.close()
			socket.close()
			return "true"
		else:
			return "false"
	except (Exception, psycopg2.DatabaseError) as error:
		return "false"
	finally:
		if conn is not None:
			cur.close()
			conn.close()


