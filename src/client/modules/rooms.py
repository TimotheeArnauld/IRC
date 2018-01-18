#!/usr/bin/python
import psycopg2
import sys

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
