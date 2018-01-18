#!/usr/bin/python

import psycopg2
import sys

def create_room(idUser, nameSalon):
    con = None
    print idUser
    try:

        conn_string = "host='localhost' dbname='docker' user='docker' password='docker'"
        print "Connecting to database\n	->%s" % (conn_string)
        con = psycopg2.connect(conn_string)
        cursor = con.cursor()
        print "Connected!\n"

        cursor.execute("INSERT INTO rooms(room_name) VALUES ('{0}');".format(nameSalon))
        cursor.execute("SELECT room_id FROM rooms WHERE room_name = ('{0}')".format(nameSalon))

        idRoom = cursor.fetchall()
        cursor.execute("INSERT INTO users_rooms VALUES({0},{1})".format(idUser, idRoom[0][0]))

        return "ok"
        cursor.close()
        con.commit()

    except psycopg2.DatabaseError, e:

        if con:
            con.rollback()

        return "ko"
        print 'Error %s' % e
        sys.exit(1)


    finally:

        if con:
            con.close()

if __name__ == '__main__':
    idUser = 101
    nameSalon = "general"
    create_room(idUser,nameSalon)
