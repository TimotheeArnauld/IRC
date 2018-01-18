#!/usr/bin/python
import psycopg2
import sys
import md5

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
def create_room(room_name, user_name, user_password):
	conn = psycopg2.connect("dbname=docker user=docker host=localhost password=docker")
	cur = conn.cursor()
	try:
		sql = "SELECT * FROM rooms WHERE room_name='"+room_name+"';"
		cur.execute(sql)
		if cur.rowcount == 0:
			sql2 = "INSERT INTO rooms(room_name) VALUES(%s);"
			cur.execute(sql2, (room_name,))
			conn.commit()
			#insert into users_rooms table
			password = md5.new(user_password).digest()
			sql = "SELECT * FROM users WHERE user_name='"+user_name+"';"
			cur.execute(sql)
			line = cur.fetchone()
			if cur.rowcount > 0 and line[2] == password:
				user_id = line[0]
				sql2 = "SELECT * FROM rooms WHERE room_name='"+room_name+"';"
				cur.execute(sql2)
				if cur.rowcount > 0:
					room_id = cur.fetchone()[0]
					sql3 = "INSERT INTO users_rooms(user_id, room_id) VALUES(%s, %s);"
					cur.execute(sql3, (int(user_id), int(room_id)))
					conn.commit()
					return "true"
		else:
			return "false"
	except (Exception, psycopg2.DatabaseError) as error:
		return "false"
	finally:
		if conn is not None:
			cur.close()
			conn.close()

#return true if room is deleted and false if user isn't the owner/doesn't exist/error database
def delete_room_if_owner(room_name, user_name):
	conn = psycopg2.connect("dbname=docker user=docker host=localhost password=docker")
	cur = conn.cursor()
	try:
		sql = "SELECT * FROM users WHERE user_name='"+user_name+"';"
		cur.execute(sql)
		if cur.rowcount > 0:
			user_id = cur.fetchone()[0]
			sql2 = "SELECT * FROM rooms WHERE room_name='"+room_name+"';"
			cur.execute(sql2)
			if cur.rowcount > 0:
				room_id = cur.fetchone()[0]
				sql3 = "SELECT * FROM users_rooms WHERE room_id=%s AND user_id=%s;"
				cur.execute(sql3, (int(room_id), int(user_id)))
				if cur.rowcount > 0 :
					#User is owner of the room so he can delete it
					delete1 = "DELETE FROM users_rooms WHERE room_id=%s AND user_id=%s;"
					delete2 = "DELETE FROM rooms WHERE room_name=%s;"
					cur.execute(delete, (int(room_id), int(user_id)))
					cur.execute(delete2, room_name)
					conn.commit()
					return "true"
		else:
			print("else")
			return "false"
	except (Exception, psycopg2.DatabaseError) as error:
		print(error)
		return "false"
	finally:
		if conn is not None:
			cur.close()
			conn.close()










