#!/usr/bin/python

import psycopg2
import sys

def create_salon(idUser, nameSalon):
    con = None
    print idUser
    try:

        conn_string = "host='localhost' dbname='docker' user='docker' password='docker'"
        print "Connecting to database\n	->%s" % (conn_string)
        con = psycopg2.connect(conn_string)
        cursor = con.cursor()
        print "Connected!\n"
        query = "INSERT INTO rooms(room_name) VALUES ('{0}');".format(nameSalon)

        cursor.execute(query)
        cursor.execute("INSERT INTO rooms(room_name) VALUES(%s)", (nameSalon))
        cursor.execute("SELECT room_id FROM rooms WHERE room_name = (%s)",(nameSalon))
        idRoom = cursor.fetchall()
        cursor.execute("INSERT INTO users_rooms VALUES(%d,%s)", (idUser,idRoom))

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
