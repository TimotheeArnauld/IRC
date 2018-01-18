#!/usr/bin/python

import psycopg2
import sys

def drop_room(idUser, nameRoom):
    con = None
    print idUser
    try:

        conn_string = "host='localhost' dbname='docker' user='docker' password='docker'"
        print "Connecting to database\n	->%s" % (conn_string)
        con = psycopg2.connect(conn_string)
        cursor = con.cursor()
        print "Connected!\n"

		cursor.execute("SELECT room_id FROM users_rooms WHERE user_id = (%s)",(idUser))
		idRoom = cursor.fetchall()
		DELETE FROM rooms WHERE room_id IN (SELECT room_id FROM rooms WHERE room_name = (%s) AND room_id = (%s)",(nameRoom,idRoom);
		DELETE FROM rooms WHERE room_id IN (SELECT room_id FROM rooms WHERE room_name = (%s) AND room_id IN (SELECT room_id FROM users_rooms WHERE user_id = (%s)",(idUser)),(nameRoom);

        print "ok\n"
        cursor.close()
        con.commit()

    except psycopg2.DatabaseError, e:

        if con:
            con.rollback()

        print 'Error %s' % e
        sys.exit(1)


    finally:

        if con:
            con.close()

if __name__ == '__main__':
    idUser = 101
    nameSalon = "test"
    create_salon(idUser,nameSalon)
