#!/usr/bin/python
import psycopg2
import sys

#return a list of the rooms space separated 
def see_available_rooms():
	conn = psycopg2.connect("dbname=docker user=docker host=localhost password=docker")
	cur = conn.cursor()
	rooms = ""
	try:
		sql = "SELECT * FROM rooms;"
		cur.execute(sql)
		if cur.rowcount == 0:
			return "nothing"
		else:
			rows = cur.fetchall()
			for line in rows:
				rooms = rooms + " " + line[1]
			return rooms
	except (Exception, psycopg2.DatabaseError) as error:
		return "nothing"
	finally:
		if conn is not None:
			cur.close()
			conn.close()

#return true if it's created and false if it exists in the database
def create_room(name):
	conn = psycopg2.connect("dbname=docker user=docker host=localhost password=docker")
	cur = conn.cursor()
	try:
		sql = "SELECT * FROM rooms WHERE room_name='"+name+"';"
		cur.execute(sql)
		if cur.rowcount == 0:
			sql2 = "INSERT INTO rooms(room_name) VALUES(%s);"
			cur.execute(sql2, (name,))
			conn.commit()
			return "true"
		else:
			return "false"
	except (Exception, psycopg2.DatabaseError) as error:
		print(error)
		return "false"
	finally:
		if conn is not None:
			cur.close()
			conn.close()