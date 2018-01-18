#!/usr/bin/python

import psycopg2
import sys

def drop_room(idUser, nameRoom):
    con = None

    try:

        conn_string = "host='localhost' dbname='docker' user='docker' password='docker'"
        print "Connecting to database\n	->%s" % (conn_string)
        con = psycopg2.connect(conn_string)
        cursor = con.cursor()
        print "Connected!\n"

        cursor.execute("SELECT room_id FROM users_rooms WHERE user_id = ('{0}');".format(idUser))
        idRoom = cursor.fetchall()
        cursor.execute("DELETE FROM rooms WHERE room_name = '{0}' AND room_id = {1};".format(nameRoom,idRoom[0][0]))
        cursor.execute("DELETE FROM users_rooms WHERE user_id = '{0}' AND room_id = {1};".format(idUser,idRoom[0][0]))

        return "ok"
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
    nameSalon = "general"
    drop_room(idUser,nameSalon)
